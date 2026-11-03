#!/usr/bin/env python3
"""Probe IDO 5.3's back end (ugen -> as1) for stage-5/6 scheduling, delay-slot and hoist near-misses.

The `cc -S` + assemble round trip is not faithful (as0 drops `.option O2`), so as1 questions are
answered on ugen's binary output instead: compile FUNC's reduced TU (deadsweep's: the copy's head,
other bodies turned into prototypes, NON_MATCHING resolved) with the file's make flags plus `-K`
(keeps every phase's output), then re-run as1 on edited ugen records and score each result.
Run in the container:

  tools/dk python3 tools/as1probe.py keep <copy.c> <src/seg/file.c> FUNC [--body F] [--out DIR]
  tools/dk python3 tools/as1probe.py dis DIR [--all] [--range A-B]
  tools/dk python3 tools/as1probe.py try DIR [--insert POS:PROBE]... [--delete POS]... [--swap POS]... [--diff]
  tools/dk python3 tools/as1probe.py scan DIR [--range A-B] [--ops insert,delete,swap] [--probes P,...] [--rounds N] [-j N] [--top N]
  tools/dk python3 tools/as1probe.py as1 DIR <records.G> [--keep-obj]
  tools/dk python3 tools/as1probe.py records DIR [--start N] [--count N]
  tools/dk python3 tools/as1probe.py ucode DIR [--cfe]
  tools/dk python3 tools/as1probe.py corpus [--out DIR] [-j N] [--grep REGEX [--context N]] [SRC...]

  keep     writes DIR/t.c and the kept phase files t.B (cfe ucode), t.O (uopt ucode), t.G (ugen output,
           16-byte big-endian binasm records), t.s (ugen's text listing of t.G, one line per record),
           t.T (symbol table), out.o, the as1 command line (DIR/as1.cmd) and FUNC/src (DIR/probe.json);
           prints deadsweep's score of out.o (full/text/reloc/shape). DIR defaults to
           .scratch/as1probe/<seg>_FUNC and is recreated. (The object is out.o, not t.o: on the macOS
           bind mount t.o and t.O are the same file, and as1 used to overwrite uopt's ucode.)
  dis      FUNC's records as `index: <ugen text>` (raw t.G record indices, the positions `try`/`scan` use);
           --all lists the whole file, --range A-B a slice.
  try      applies explicit edits to t.G (positions are original record indices; insert = before that
           record) and prints the score; --diff prints the objdump diff against expected/.
  scan     single-edit search: every probe inserted before every record, every record deleted, every
           adjacent instruction/.loc pair swapped; prints the edits that lower the score, best first,
           with context and what C could produce that record (see PROBES). --rounds N keeps the best edit
           and rescans (greedy, up to N edits; later positions refer to the edited stream). Default -j 4.
  as1      runs DIR's as1 command on <records.G> (an edited copy of DIR/t.G) and prints the same score.
  records  prints t.G records as `index: w0 w1 w2 w3` (hex).
  ucode    disassembles uopt's output t.O (or cfe's t.B with --cfe) with udis (ido-ucode-utils).
  corpus   compiles every src C file (GLOBAL_ASM pragmas dropped; or only the given SRC files) with its
           make flags plus -K and stores ugen's listing as DIR/<src path>.s (default .scratch/ugen_corpus);
           --grep searches the stored listings (function name + context) instead of compiling.

PROBES (records `try --insert` / `scan` can add):
  noop   `addu $0,$0,$0`: as1 deletes it, but only after building its CFG, so before a label it is a
         fall-through predecessor. ugen never emits one: diagnosis only.
  alias  `.alias $1,$sp`: as1-visible, no code. From C: uopt's `unal` reset after a block's jump, which needs
         a register holding a variable address (`la`/`addu sp`) whose region ends in that block.
  loc    `.loc` repeating the previous line: a scheduling barrier. From C: a line break.
  bnext  `b` to the next label: as1 deletes jump-to-next after its hoist/delay-slot decisions. ugen's labelopt
         deletes these first, so diagnosis only.
  label  an unreferenced local label (a block boundary). ugen deletes unreferenced labels: from C only as the
         target of a real branch (a loop head, an `if` join).
  live   `.livereg` with every register live (`live=0xMASK` for one gp mask, bit 31-r = $r): as1 then keeps
         those registers intact across that point. ugen emits `.livereg` only before calls and returns, so a
         hit points at a liveness route (narrow the register with `try --insert POS:live=0xMASK`, then look
         for C that keeps it live there), not at this record.
  A deleted `.loc` = statements joined on one source line; a swap = statement/operand order. Deleting or
  swapping instructions can lower the score by changing the instruction count (n): compare n with the
  target's count before trusting such a hit. A scan covers single edits from this vocabulary only: no hit,
  or only hits C cannot emit, does not show that no C exists (several coordinated stream changes can).

What it found so far: as1 hoists a branch target's first instruction into the branching block's load-use
stall only when the target label has ONE predecessor and the moved register is dead on the other path:
any as1-visible record between the previous block's jump and the label (instruction, `.alias`/`.noalias`,
`.bgnb`/`.endb`, `.frame`, data directive, a jump-to-next it later deletes) is a fall-through predecessor
and stops the hoist, and so does a `.livereg` marking the moved register live before the branch; `.loc`,
`.set`, labels and `.rdata` tables do not; jump-table entries count as references. ugen's labelopt deletes
everything between an unconditional jump and the next label except `unal`/`bgnb`/`endb`/`comm`/`def`/
`lex`/`optn`/`sdef`, so at -O2 -g0 the only C-reachable record there is uopt's `.alias` reset. Store-count
positions decide where ugen places homed FP-argument reloads; `.livereg` masks decide `bnez; move` vs
`bnezl; copy`. Edits to t.G are diagnosis only: the fix must still be C that makes cfe/uopt/ugen emit
that stream.
"""
import argparse, json, os, re, shlex, shutil, struct, subprocess, sys, tempfile
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import deadsweep as ds  # noqa: E402

ROOT = ds.ROOT

# ---- binasm records (include/cmplrs/binasm.h; big-endian bitfields, 16 bytes per record) ----------
ITYPES = """label sym global cpload align ascii asciiz byte comm lcomm data double file float half cprestore
gpword cpadd weakext loopno space text word ocode end sdata rdata ent loc bgnb endb asm0 set cpalias rep
endrep lab vreg mask fmask err globabs verstamp frame extended extern aent option noalias alias mtag
malias struct livereg gjaldef gjallive gjrlive shift_addr restext dword prologue edata alloc""".split()
IT = {n: i for i, n in enumerate(ITYPES)}
# asmcodes (op field), ugen spelling
OPS = """abs add addu and b bc0f bc0t bc1f bc1t bc2f bc2t lgota 12 beq bge bgeu bgez bgt bgtu bgtz ble bleu blez blt
bltu bltz bne break c0 c1 c2 31 div divu j jal la lb lbu lh lhu li lw jr lwc1 lwc2 pref mfhi mflo move jalr
swc1 swc2 53 mthi mtlo mul mulo mulou mult multu neg nop nor or rem remu rfe rol ror sb seq sge sgeu sgt sgtu
sh sle sleu sll slt sltu sne sra srl sub subu sw syscall xor not lwl lwr swl swr vcall mfc0 mfc1 mfc2 99 mtc0
mtc1 mtc2 sync tlbr tlbwi tlbwr tlbp ld sd 110 ldc1 ldc2 tlbr1 tlbp1 sdc1 sdc2 117 l.s l.d l.e s.s s.d s.e
add.s add.d add.e sub.s sub.d sub.e mul.s mul.d mul.e div.s div.d div.e sqrt.s sqrt.d sqrt.e mov.s mov.d mov.e
abs.s abs.d abs.e cvt.s.d cvt.s.e cvt.s.w cvt.d.s cvt.d.e cvt.d.w cvt.e.s cvt.e.d cvt.e.w cvt.w.s cvt.w.d
cvt.w.e c.f.s c.f.d c.f.e c.un.s c.un.d c.un.e c.eq.s c.eq.d c.eq.e c.ueq.s c.ueq.d c.ueq.e c.olt.s c.olt.d
c.olt.e c.ult.s c.ult.d c.ult.e c.ole.s c.ole.d c.ole.e c.ule.s c.ule.d c.ule.e c.sf.s c.sf.d c.sf.e c.ngle.s
c.ngle.d c.ngle.e c.seq.s c.seq.d c.seq.e c.ngl.s c.ngl.d c.ngl.e c.lt.s c.lt.d c.lt.e c.nge.s c.nge.d c.nge.e
c.le.s c.le.d c.le.e c.ngt.s c.ngt.d c.ngt.e lui ulw ulh ulhu usw ush addi addiu slti sltiu andi ori xori 218
negu beqz bnez neg.s neg.d neg.e cfc1 ctc1 bal bgezal bltzal mtc1.d mfc1.d trunc.w.s trunc.w.d trunc.w.e
round.w.s round.w.d round.w.e addou subou truncu.w.s truncu.w.d truncu.w.e roundu.w.s roundu.w.d roundu.w.e
cfc0 cfc2 248 ctc0 ctc2 251 li.s li.d li.e tlt tltu tge tgeu teq tne ll sc ceil.w.s ceil.w.d ceil.w.e
ceilu.w.s ceilu.w.d ceilu.w.e floor.w.s floor.w.d floor.w.e flooru.w.s flooru.w.d flooru.w.e beql beqzl bnel
bnezl blel bleul blezl bgtl bgtul bgtzl bltl bltul bltzl bltzall bgel bgeul bgezl bgezall bc0fl bc0tl bc1fl
bc1tl bc2fl bc2tl 299 300 ldl ldr lld lwu sdl sdr scd daddi daddiu dadd daddu dsub dsubu dsll dsrl dsra dsllv
dsrlv dsrav dmult dmultu ddiv ddivu lsc1 ssc1 dmtc1 dmfc1 dmtc0 dmfc0 dmtc2 dmfc2 dli dla eret trunc.l.s
round.l.s ceil.l.s floor.l.s trunc.l.d round.l.d ceil.l.d floor.l.d trunc.l.e round.l.e ceil.l.e floor.l.e
cvt.l.s cvt.l.d cvt.l.e cvt.l.w cvt.s.l cvt.d.l cvt.e.l cvt.w.l cache cia uld usd dabs dneg dnegu dmul dmulo
dmulou drem dremu drol dror daddou dsubou ulwu movt movf movn movz madd.s madd.d madd.e msub.s msub.d msub.e
nmadd.s nmadd.d nmadd.e nmsub.s nmsub.d nmsub.e recip.s recip.d rsqrt.s rsqrt.d movt.s movt.d movf.s movf.d
movn.s movn.d movz.s movz.d lwxc1 ldxc1 swxc1 sdxc1 pfetch dctr dctw tlbw nada ssnop dsll32 dsrl32 dsra32 bc3f
bc3t c3 lwc3 swc3 mfc3 mtc3 cfc3 ctc3 sllv srlv srav mfpc mtpc mfps mtps bad""".split()
OP = {n: i for i, n in enumerate(OPS)}
FORMS = "rob ra ri rrr rri rr a r rrl rl l orrr ril i oa rrrr".split()
FM = {n: i for i, n in enumerate(FORMS)}
NOREG = 72


def load_records(path):
    data = Path(path).read_bytes()
    return [data[i:i + 16] for i in range(0, len(data), 16)]


def fields(rec):
    w0, w1, w2, w3 = struct.unpack(">iIIi", rec)
    return {"sym": w0, "type": (w1 >> 16) & 0x3F, "op": (w1 >> 1) & 0x1FF, "w1": w1, "w2": w2, "w3": w3,
            "r1": (w2 >> 25) & 0x7F, "r2": (w2 >> 18) & 0x7F, "form": (w2 >> 14) & 0xF, "r3": (w2 >> 7) & 0x7F}


def extra_records(rec):
    """Data records that follow REC (.file name, .ascii/.asciiz text, li.s/li.d/li.e literal text)."""
    f = fields(rec)
    if f["type"] in (IT["file"], IT["ascii"], IT["asciiz"]):
        return (f["w2"] + 15) // 16
    if f["type"] == IT["ocode"] and OPS[f["op"]] in ("li.s", "li.d", "li.e"):
        return (f["w3"] + 15) // 16
    return 0


def logical(recs):
    """[(raw index, record)] without the data records that belong to the previous record."""
    out, i = [], 0
    while i < len(recs):
        out.append((i, recs[i]))
        i += 1 + extra_records(recs[i])
    return out


def mk_inst(op, form, r1=NOREG, r2=NOREG, r3=0, imm=0, sym=0):
    w1 = (IT["ocode"] << 16) | (OP[op] << 1)
    w2 = (r1 << 25) | (r2 << 18) | (FM[form] << 14) | (r3 << 7)
    return struct.pack(">iIIi", sym, w1, w2, imm)


def mk_alias(kind, r1, r2):
    return struct.pack(">iIIi", 0, (IT[kind] << 16) | (r1 << 9) | (r2 << 2), 0, 0)


def mk_loc(file, line):
    return struct.pack(">iIIi", 0, IT["loc"] << 16, file, line)


def reg_name(r):
    return {0: "$0", 29: "$sp", 31: "$31"}.get(r, "$%d" % r) if r < 32 else "$f%d" % (r - 32) if r < 64 else "?"


def render(rec):
    """Approximate ugen text for a record the tool created (kept records use t.s's own line)."""
    f = fields(rec)
    t = ITYPES[f["type"]] if f["type"] < len(ITYPES) else "?%d" % f["type"]
    if t == "label":
        return "$%d:" % -f["sym"] if f["sym"] < 0 else "sym%d:" % f["sym"]
    if t in ("alias", "noalias"):
        return "\t.%s\t%s,%s" % (t, reg_name((f["w1"] >> 9) & 0x7F), reg_name((f["w1"] >> 2) & 0x7F))
    if t == "loc":
        return "\t.loc\t%d %d" % (f["w2"], f["w3"])
    if t == "ocode":
        name, form = OPS[f["op"]], FORMS[f["form"]]
        if form == "l":
            return "\t%s\t$%d" % (name, -f["sym"])
        if form == "rrr":
            return "\t%s\t%s, %s, %s" % (name, reg_name(f["r1"]), reg_name(f["r2"]), reg_name(f["r3"]))
        return "\t%s\t(form %s)" % (name, form)
    return "\t.%s" % t


class Stream:
    """t.G records of a probe directory, with ugen's own text for each logical record (from t.s).
    Edited copies (Stream.edited) keep the text of surviving records; positions are record indices."""

    def __init__(self, d, items=None, info=None):
        self.d = Path(d)
        self.info = info or json.loads((self.d / "probe.json").read_text())
        if items is None:
            recs = load_records(self.d / "t.G")
            lines = [l.rstrip("\n") for l in (self.d / "t.s").read_text().splitlines() if l.strip() and not l.startswith(" #")]
            log = logical(recs)
            text = dict(zip((i for i, _ in log), lines)) if len(lines) == len(log) else {}
            if not text:
                print("note: t.s does not align with t.G; records shown decoded", file=sys.stderr)
            items = [(r, text.get(i)) for i, r in enumerate(recs)]
        self.items = items
        self.recs = [r for r, _ in items]
        self.log = logical(self.recs)
        func = self.info["func"]
        ent = [i for i, r in self.log if fields(r)["type"] == IT["ent"] and (items[i][1] or "").split()[1:2] == [func]]
        end = [i for i, r in self.log if fields(r)["type"] == IT["end"] and func in (items[i][1] or "")]
        self.lo = ent[0] if ent else 0
        self.hi = end[-1] if end else len(self.recs) - 1

    def line(self, i):
        return self.items[i][1] or render(self.recs[i])

    def next_label(self, pos):
        for i, r in self.log:
            if i >= pos and fields(r)["type"] == IT["label"] and fields(r)["sym"] < 0:
                return -fields(r)["sym"]
        return None

    def prev_loc(self, pos):
        for i, r in reversed(self.log):
            if i < pos and fields(r)["type"] == IT["loc"]:
                f = fields(r)
                return f["w2"], f["w3"]
        return 2, 0

    def edited(self, inserts=(), deletes=(), swaps=()):
        """A new Stream; edits use this stream's record indices, inserts go before that index."""
        items = list(self.items)
        for p in swaps:
            items[p], items[p + 1] = items[p + 1], items[p]
        ins = {}
        for p, rec in inserts:
            ins.setdefault(p, []).append((rec, None))
        dels = set(deletes)
        out = []
        for i, it in enumerate(items):
            out.extend(ins.get(i, []))
            if i not in dels:
                out.append(it)
        out.extend(ins.get(len(items), []))
        return Stream(self.d, out, self.info)


def probe_record(stream, kind, pos):
    if kind == "noop":
        return mk_inst("addu", "rrr", 0, 0, 0)
    if kind == "alias":
        return mk_alias("alias", 1, 29)
    if kind == "loc":
        return mk_loc(*stream.prev_loc(pos))
    if kind == "bnext":
        lab = stream.next_label(pos)
        return None if lab is None else mk_inst("b", "l", sym=-lab)
    if kind == "label":
        used = [-fields(r)["sym"] for r in stream.recs if fields(r)["sym"] < 0]
        return struct.pack(">iIIi", -(max(used, default=0) + 1000), IT["label"] << 16, 0, 0)
    if kind == "live" or kind.startswith("live="):
        gp, fp = (int(kind[5:], 16), 0) if "=" in kind else (0xFFFFFFFE, 0xFFFFFFFF)
        return struct.pack(">iIII", 0, IT["livereg"] << 16, gp, fp)
    raise SystemExit("unknown probe %r" % kind)


def as1_cmd(d):
    return shlex.split((Path(d) / "as1.cmd").read_text())


def run_as1(d, info, recs_or_path, tag, keep_obj=False):
    """Assemble edited records with DIR's as1 command; return (score, object path or None)."""
    d = Path(d).resolve()
    if isinstance(recs_or_path, (str, Path)):
        g = Path(recs_or_path).resolve()
    else:
        (d / "scan").mkdir(exist_ok=True)
        g = d / "scan" / (tag + ".G")
        g.write_bytes(b"".join(recs_or_path))
    out = g.with_suffix(".probe.o")
    t = as1_cmd(d)
    i = t.index("-o")
    t[i + 1] = str(out)
    t[i - 1] = str(g)  # as1 ... <input.G> -o <out.o> ...
    try:
        r = subprocess.run(t, cwd=d, capture_output=True, text=True, timeout=60)
    except subprocess.TimeoutExpired:
        return "error: as1 timeout", None
    if r.returncode or not out.exists():
        return "error: as1 failed: " + " ".join((r.stdout + r.stderr).split())[:200], None
    sc = score(out, info)
    if not keep_obj:
        out.unlink()
        return sc, None
    return sc, out


def score_key(s):
    m = re.match(r"full=(\d+) text=(\d+) reloc=(\d+) shape=(\d+)", s)
    return tuple(int(x) for x in m.groups()) if m else (1 << 30,)


def score(obj, info):
    exp = ROOT / "expected" / "build" / (info["src"][:-2] + ".o")
    e, g = ds.dis(exp, info["func"]), ds.dis(obj, info["func"])
    if not g:
        return "error: function not in object"
    txt = lambda x, want=None, mask=False: [ds.REG.sub("R", t) if mask else t for r, t in x if want is None or r == want]
    return "full=%d text=%d reloc=%d shape=%d n=%d" % (
        ds.sdiff(txt(e), txt(g)), ds.sdiff(txt(e, False), txt(g, False)), ds.sdiff(txt(e, True), txt(g, True)),
        ds.sdiff(txt(e, mask=True), txt(g, mask=True)), len(g))


def keep(a):
    head, body, _ = ds.load(a.copy, a.func, a.body)
    seg = Path(a.src).parent.name
    d = Path(a.out) if a.out else ROOT / ".scratch" / "as1probe" / f"{seg}_{a.func}"
    shutil.rmtree(d, ignore_errors=True)
    d.mkdir(parents=True)
    (d / "t.c").write_text(head + "\n" + body + "\n")
    cc, flags = ds.compile_flags(a.src)
    # the TU is compiled in DIR (so -K leaves the phase files there): make relative -I paths absolute
    flags = [str(ROOT / f) if k and flags[k - 1] == "-I" and not f.startswith("/") else
             "-I" + str(ROOT / f[2:]) if f.startswith("-I") and len(f) > 2 and not f[2:].startswith("/") else f
             for k, f in enumerate(flags)]
    r = subprocess.run([cc] + flags + ["-K", "-v", "-c", "-o", "out.o", "t.c"], cwd=d, capture_output=True, text=True)
    msg = r.stdout + r.stderr
    if r.returncode or "cfe: Error" in msg or not (d / "t.G").exists():
        sys.exit("compile failed:\n" + "\n".join(l for l in msg.splitlines() if "Error" in l or "error" in l)[-2000:])
    line = next((l for l in msg.splitlines() if "/as1 " in l), None)
    if not line:
        sys.exit("no as1 command in cc -v output")
    t = shlex.split(line)
    t[0] = str(Path(cc).parent / Path(t[0]).name)  # cc -v prints IDO's own /usr/lib/as1 path
    (d / "as1.cmd").write_text(shlex.join(t) + "\n")
    info = {"func": a.func, "src": a.src}
    (d / "probe.json").write_text(json.dumps(info))
    print(d)
    print(score(d / "out.o", info))


def as1(a):
    d = Path(a.dir)
    info = json.loads((d / "probe.json").read_text())
    sc, obj = run_as1(d, info, a.records, "as1", keep_obj=a.keep_obj)
    print(sc)
    if obj:
        print(obj)


def records(a):
    data = (Path(a.dir) / "t.G").read_bytes()
    n = len(data) // 16
    for k in range(a.start, min(n, a.start + a.count)):
        print("%5d: %08x %08x %08x %08x" % ((k,) + struct.unpack(">4I", data[16 * k:16 * k + 16])))


def parse_range(s, st):
    if not s:
        return st.lo, st.hi
    lo, hi = s.split("-")
    return int(lo), int(hi)


def dis(a):
    st = Stream(a.dir)
    lo, hi = (0, len(st.recs) - 1) if a.all else parse_range(a.range, st)
    for i, _ in st.log:
        if lo <= i <= hi:
            print("%5d: %s" % (i, st.line(i)))


def parse_edits(st, a):
    inserts = []
    for spec in a.insert or []:
        p, kind = spec.split(":")
        rec = probe_record(st, kind, int(p))
        if rec is None:
            sys.exit("no label after %s for bnext" % p)
        inserts.append((int(p), rec))
    return inserts, [int(x) for x in a.delete or []], [int(x) for x in a.swap or []]


def print_diff(info, obj):
    import difflib
    exp = ROOT / "expected" / "build" / (info["src"][:-2] + ".o")
    e = [t for r, t in ds.dis(exp, info["func"]) if not r]
    g = [t for r, t in ds.dis(obj, info["func"]) if not r]
    for l in difflib.unified_diff(e, g, "expected", "edited", lineterm="", n=2):
        print(l)


def try_(a):
    st = Stream(a.dir)
    ins, dels, swaps = parse_edits(st, a)
    base, _ = run_as1(st.d, st.info, st.recs, "base")
    sc, obj = run_as1(st.d, st.info, st.edited(ins, dels, swaps).recs, "try", keep_obj=a.diff)
    print("baseline", base)
    print("edited  ", sc)
    if obj:
        print_diff(st.info, obj)
        obj.unlink()


REACH = {
    "noop": "diagnosis only (ugen never emits it)",
    "alias": "C: uopt .alias reset (needs a register-held variable address whose region ends here)",
    "loc": "C: start a new source line here",
    "bnext": "diagnosis only (ugen labelopt deletes jump-to-next)",
    "label": "C: only as a real branch target (ugen deletes unreferenced labels)",
    "live": "liveness route: narrow with try --insert POS:live=0xMASK, then find C keeping that register live",
    "delete-loc": "C: join this statement onto the previous line",
    "delete": "C: remove the statement/operation that emits it",
    "swap": "C: statement or operand order",
}


def scan_edits(st, lo, hi, ops, probes):
    edits = []
    for i, r in st.log:
        if not lo <= i <= hi:
            continue
        f = fields(r)
        if "insert" in ops:
            for k in probes:
                rec = probe_record(st, k, i)
                if rec is not None:
                    edits.append(("insert %d:%s" % (i, k), k, i, ([(i, rec)], [], [])))
        if "delete" in ops and f["type"] in (IT["ocode"], IT["loc"], IT["alias"], IT["noalias"], IT["livereg"]):
            kind = "delete-loc" if f["type"] == IT["loc"] else "delete"
            edits.append(("delete %d" % i, kind, i, ([], list(range(i, i + 1 + extra_records(r))), [])))
        if "swap" in ops and i + 1 < len(st.recs) and i + 1 <= hi and extra_records(r) == 0:
            g = fields(st.recs[i + 1])
            okt = (IT["ocode"], IT["loc"])
            if f["type"] in okt and g["type"] in okt and st.recs[i] != st.recs[i + 1] and extra_records(st.recs[i + 1]) == 0:
                edits.append(("swap %d,%d" % (i, i + 1), "swap", i, ([], [], [i])))
    return edits


def scan(a):
    st = Stream(a.dir)
    lo, hi = parse_range(a.range, st)
    ops, probes = set(a.ops.split(",")), a.probes.split(",")
    base, _ = run_as1(st.d, st.info, st.recs, "base")
    print("baseline", base, flush=True)
    for rnd in range(1, a.rounds + 1):
        edits = scan_edits(st, lo, hi, ops, probes)
        bkey = score_key(base)

        def job(k):
            ins, dels, swaps = edits[k][3]
            return k, run_as1(st.d, st.info, st.edited(ins, dels, swaps).recs, "e%d" % k)[0]

        results = []
        with ThreadPoolExecutor(a.jobs) as ex:
            for k, sc in ex.map(job, range(len(edits))):
                if score_key(sc) < bkey:
                    results.append((score_key(sc), k, sc))
        shutil.rmtree(st.d / "scan", ignore_errors=True)
        results.sort()
        print("round %d: %d edits over records %d-%d, %d improve" % (rnd, len(edits), lo, hi, len(results)))
        for key, k, sc in results[:a.top]:
            name, kind, pos, _ = edits[k]
            print("%-22s %s   [%s]" % (name, sc, REACH[kind]))
            for j, _ in st.log:
                if pos - 2 <= j <= pos + 1:
                    print("      %s %5d: %s" % (">>" if j == pos else "  ", j, st.line(j)))
        if not results or rnd == a.rounds or results[0][0][0] == 0:
            break
        name, kind, pos, (ins, dels, swaps) = edits[results[0][1]]
        st = st.edited(ins, dels, swaps)
        base = results[0][2]
        hi += len(ins) - len(dels)
        print("round %d keeps `%s` -> %s (later positions refer to the edited stream)" % (rnd, name, base), flush=True)


def ucode(a):
    udis = shutil.which("udis")
    if not udis:
        sys.exit("udis not found (ido-ucode-utils; installed in the dk64-decomp image)")
    f = Path(a.dir) / ("t.B" if a.cfe else "t.O")
    head = f.read_bytes()[:4]
    if head == b"\x7fELF":
        sys.exit("%s is an ELF object: re-run `keep` (older versions wrote the object over t.O)" % f)
    r = subprocess.run([udis, str(f)], capture_output=True, text=True)
    sys.stdout.write(r.stdout)
    if r.returncode:
        sys.exit(r.stderr or "udis failed")


def corpus_compile(src, out):
    dst = out / (src + ".s")
    try:
        cc, flags = ds.compile_flags(src)
    except SystemExit:
        return src, "no compile rule"
    text = re.sub(r"^[ \t]*#pragma GLOBAL_ASM\(.*\)[ \t]*$", "", (ROOT / src).read_text(), flags=re.M)
    flags = [str(ROOT / f) if k and flags[k - 1] == "-I" and not f.startswith("/") else
             "-I" + str(ROOT / f[2:]) if f.startswith("-I") and len(f) > 2 and not f[2:].startswith("/") else f
             for k, f in enumerate(flags)]
    with tempfile.TemporaryDirectory() as d:
        (Path(d) / "t.c").write_text(text)
        r = subprocess.run([cc] + flags + ["-K", "-c", "-o", "out.o", "t.c"], cwd=d, capture_output=True, text=True)
        s = Path(d) / "t.s"
        if not s.exists():
            s = Path(d) / "u.out.s"  # -O3: ujoin/uld/umerge pipeline names its phase files u.out.*
        if not s.exists():
            return src, "compile failed: " + " ".join((r.stdout + r.stderr).split())[:160]
        dst.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy(s, dst)
    return src, None


def corpus(a):
    out = Path(a.out) if a.out else ROOT / ".scratch" / "ugen_corpus"
    if a.grep:
        pat = re.compile(a.grep)
        for f in sorted(out.rglob("*.s")):
            lines = [l.rstrip("\n") for l in f.read_text().splitlines() if not l.startswith(" #")]
            func = "?"
            for i, l in enumerate(lines):
                m = re.match(r"^\t\.ent\t(\S+)", l)
                if m:
                    func = m.group(1)
                if pat.search(l):
                    rel = f.relative_to(out).as_posix()[:-2]
                    print("%s:%s:%d" % (rel, func, i))
                    for j in range(max(0, i - a.context), min(len(lines), i + a.context + 1)):
                        print("    %s %s" % (">" if j == i else " ", lines[j]))
        return
    srcs = a.srcs or sorted(p.relative_to(ROOT).as_posix() for p in (ROOT / "src").rglob("*.c"))
    with ThreadPoolExecutor(a.jobs) as ex:
        res = list(ex.map(lambda s: corpus_compile(s, out), srcs))
    bad = [(s, e) for s, e in res if e]
    print("%d of %d files -> %s" % (len(res) - len(bad), len(res), out))
    for s, e in bad:
        print("  %s: %s" % (s, e))


def main():
    ap = argparse.ArgumentParser(description="as1 probe (see the module docstring)")
    sub = ap.add_subparsers(dest="cmd", required=True)
    p = sub.add_parser("keep")
    p.add_argument("copy"), p.add_argument("src"), p.add_argument("func")
    p.add_argument("--body"), p.add_argument("--out")
    p = sub.add_parser("dis")
    p.add_argument("dir"), p.add_argument("--all", action="store_true"), p.add_argument("--range")
    p = sub.add_parser("try")
    p.add_argument("dir"), p.add_argument("--insert", action="append"), p.add_argument("--delete", action="append")
    p.add_argument("--swap", action="append"), p.add_argument("--diff", action="store_true")
    p = sub.add_parser("scan")
    p.add_argument("dir"), p.add_argument("--range"), p.add_argument("--ops", default="insert,delete,swap")
    p.add_argument("--probes", default="noop,alias,loc,bnext,label,live"), p.add_argument("-j", "--jobs", type=int, default=4)
    p.add_argument("--top", type=int, default=20), p.add_argument("--rounds", type=int, default=1)
    p = sub.add_parser("as1")
    p.add_argument("dir"), p.add_argument("records"), p.add_argument("--keep-obj", action="store_true")
    p = sub.add_parser("records")
    p.add_argument("dir"), p.add_argument("--start", type=int, default=0), p.add_argument("--count", type=int, default=1 << 30)
    p = sub.add_parser("ucode")
    p.add_argument("dir"), p.add_argument("--cfe", action="store_true")
    p = sub.add_parser("corpus")
    p.add_argument("srcs", nargs="*"), p.add_argument("--out"), p.add_argument("-j", "--jobs", type=int, default=6)
    p.add_argument("--grep"), p.add_argument("--context", type=int, default=2)
    a = ap.parse_args()
    {"keep": keep, "dis": dis, "try": try_, "scan": scan, "as1": as1, "records": records,
     "ucode": ucode, "corpus": corpus}[a.cmd](a)


if __name__ == "__main__":
    main()

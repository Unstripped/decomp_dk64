#!/usr/bin/env python3
"""IDO 5.3 matching knowledge base: search, look up and extend `knowledge/ido/`.

    python3 tools/quirks.py search [--symptom TAG]... [--phase P] [--kind all|entry|guide]
                                   [-n N] [--full] WORDS...
    python3 tools/quirks.py func NAME...        # entries/guide sections citing a function
    python3 tools/quirks.py get ID...           # Q0042, guide-slug, guide-slug#3
    python3 tools/quirks.py tags                # phases and symptom tags with counts
    python3 tools/quirks.py add --title T --phase P --symptom S... (--body TEXT | --body-file F)
                                [--function F]... [--source PATH@COMMIT]... [--see-also ID]...
    python3 tools/quirks.py check               # validate every file

Store (`--root DIR` overrides `knowledge/ido`):
  entries/QNNNN.md  one quirk each: `---`, one `key: <JSON literal>` line per key (title,
                    phase, symptoms, functions, section, sources, see_also), `---`, markdown body.
  guides/<slug>.md  long-form notes and runbooks: frontmatter title, description, origin; body.
                    Guides are searched per `##`/`###` section (`slug#n`).

Ranking is BM25 over entries and guide sections (entry titles weigh 3x, tags and function
names 2x), with a small synonym table. `func` resolves names through `symbol_addrs*.txt`, so
an entry recorded under `func_80024000` is found by the function's current name and back.
Stdlib only; runs on the host or in the container.
"""

from __future__ import annotations

import argparse
import json
import math
import re
import sys
from collections import Counter
from dataclasses import dataclass, field
from pathlib import Path
from typing import Dict, Iterable, List, Optional, Sequence, Set, Tuple

REPO = Path(__file__).resolve().parents[1]
DEFAULT_ROOT = REPO / "knowledge" / "ido"

PHASES: Dict[str, str] = {
    "cfe": "front end: C semantics, types, promotions, prototypes, evaluation order, statements to ucode",
    "uopt": "global optimizer: register coloring, CSE, copy propagation, loop-invariant hoisting, "
    "strength reduction, unrolling, dead-store elimination",
    "ugen": "code generator: instruction selection, temp-register ring, spill/temp slots, frame layout, "
    "literal materialisation",
    "as1": "assembler scheduler: instruction order, delay slots, branch-likely, `.loc` source-line ordering",
    "asm-processor": "GLOBAL_ASM/pragma handling, prelude, NON_MATCHING parks, late_rodata migration",
    "splat": "splat configs, symbol files, segment/TU boundaries, rodata splits, `force_migration`",
    "build": "Makefile, linker, `tools/dk`, gates, compression",
    "ido71-g": "IDO 7.1 `-g` audio library",
    "general": "methodology not tied to one phase",
}

SYMPTOMS: Dict[str, str] = {
    "regalloc": "same instructions, different/swapped registers",
    "callee-saved": "different set of saved `$s`/`$f` registers",
    "frame-size": "stack frame size differs",
    "stack-slot": "offsets of locals, spills or temps differ",
    "home-spill": "an argument stored to its caller home slot (`sw aN, off(sp)`) differs",
    "schedule": "same instructions in a different order",
    "delay-slot": "branch/jal delay-slot contents differ",
    "branch-shape": "branch-likely, inverted conditions, block order, loop rotation",
    "loop": "unrolling, strength reduction, induction variables",
    "constant": "constant/address materialisation (`lui/addiu/ori`, `li`, `%hi/%lo`, address CSE)",
    "float": "FP registers, float/double conversions, FP literals",
    "rodata": "literals in `.rodata`/`.late_rodata`, alignment, migration",
    "switch": "jump tables and switch lowering",
    "width": "sign/zero extension, narrow types, masks, casts",
    "call": "prototypes, argument passing, return values, varargs, function pointers",
    "cse-hoist": "common subexpressions, hoisting, copy propagation, value reuse",
    "dead-code": "dead stores, eliminated or kept code, `volatile`",
    "data-layout": "TU boundaries, data/bss placement, symbol definitions, struct layout",
    "fake-match": "codegen hacks and their natural replacements",
    "tooling": "behaviour of repo tools (fdiff, objdiff, permuter, uopt_trace, as1probe, deadsweep, merge_gate)",
}

ENTRY_KEYS = ("title", "phase", "symptoms", "functions", "section", "sources", "see_also")
LIST_KEYS = ("symptoms", "functions", "sources", "see_also")
GUIDE_KEYS = ("title", "description", "origin")
ID_RE = re.compile(r"^Q(\d{4})$")
CHUNK_MAX = 3000

STOPWORDS = frozenset(
    "a an and are as at be but by for from if in into is it its not of on one or same so than "
    "that the then this to was when with".split()
)


def _stem(tok: str) -> str:
    if len(tok) > 4 and tok.isalpha():
        for suf in ("ing", "ed", "s"):
            if tok.endswith(suf):
                if suf == "s" and tok.endswith("ss"):
                    break
                if len(tok) - len(suf) >= 4:
                    return tok[: -len(suf)]
                break
    return tok


def tokens(text: str) -> List[str]:
    out = []
    for raw in re.findall(r"[a-z0-9_$.]+", text.lower()):
        tok = raw.strip(".")
        if len(tok) < 2 or tok in STOPWORDS:
            continue
        out.append(_stem(tok))
    return out


_RAW_SYNONYMS = {
    "regalloc": "register allocation coloring",
    "register": "regalloc",
    "swap": "swapped rotation",
    "frame": "stack sp",
    "stack": "frame",
    "spill": "home slot",
    "schedule": "order scheduling reorder",
    "unroll": "unrolled unrolling",
    "literal": "rodata constant",
    "rodata": "late_rodata literal",
    "switch": "jump jtbl case",
    "prototype": "unprototyped declaration",
    "fake": "volatile deadsweep",
}
SYNONYMS: Dict[str, List[str]] = {}
for _k, _v in _RAW_SYNONYMS.items():
    for _kt in tokens(_k):
        SYNONYMS.setdefault(_kt, [])
        for _vt in tokens(_v):
            if _vt not in SYNONYMS[_kt]:
                SYNONYMS[_kt].append(_vt)


# ---------------------------------------------------------------- store


@dataclass
class Entry:
    id: str
    title: str
    phase: str
    symptoms: List[str]
    functions: List[str]
    section: str
    sources: List[dict]
    see_also: List[str]
    body: str
    path: Path


@dataclass
class Chunk:
    id: str
    heading: str
    text: str


@dataclass
class Guide:
    slug: str
    title: str
    description: str
    origin: str
    body: str
    path: Path
    chunks: List[Chunk] = field(default_factory=list)


@dataclass
class Corpus:
    root: Path
    entries: Dict[str, Entry] = field(default_factory=dict)
    guides: Dict[str, Guide] = field(default_factory=dict)
    problems: List[str] = field(default_factory=list)


class FrontmatterError(ValueError):
    pass


def parse_file(text: str) -> Tuple[dict, str]:
    lines = text.split("\n")
    if not lines or lines[0].strip() != "---":
        raise FrontmatterError("missing opening ---")
    meta = {}
    for i in range(1, len(lines)):
        line = lines[i]
        if line.strip() == "---":
            body = "\n".join(lines[i + 1 :]).strip("\n")
            return meta, body
        if not line.strip():
            continue
        key, sep, val = line.partition(": ")
        if not sep:
            raise FrontmatterError(f"line {i + 1}: expected 'key: <JSON>'")
        try:
            meta[key.strip()] = json.loads(val)
        except json.JSONDecodeError as e:
            raise FrontmatterError(f"line {i + 1}: bad JSON for {key.strip()!r}: {e}") from None
    raise FrontmatterError("missing closing ---")


def format_file(meta: dict, keys: Sequence[str], body: str) -> str:
    out = ["---"]
    for k in keys:
        if k in meta:
            out.append(f"{k}: {json.dumps(meta[k], ensure_ascii=False)}")
    out.append("---")
    return "\n".join(out) + "\n" + body.strip("\n") + "\n"


def chunk_guide(slug: str, body: str) -> List[Chunk]:
    sections: List[Tuple[str, List[str]]] = [("intro", [])]
    for line in body.split("\n"):
        if line.startswith("## ") or line.startswith("### "):
            sections.append((line.lstrip("#").strip(), [line]))
        else:
            sections[-1][1].append(line)
    chunks: List[Chunk] = []
    for heading, lines in sections:
        if heading.lower() == "sources":
            continue
        text = "\n".join(lines).strip("\n")
        if not text.strip():
            continue
        for piece in _split_long(text):
            chunks.append(Chunk(f"{slug}#{len(chunks) + 1}", heading, piece))
    return chunks


def _split_long(text: str) -> List[str]:
    if len(text) <= CHUNK_MAX:
        return [text]
    pieces, cur = [], ""
    for para in re.split(r"\n\s*\n", text):
        if cur and len(cur) + 2 + len(para) > CHUNK_MAX:
            pieces.append(cur)
            cur = para
        else:
            cur = f"{cur}\n\n{para}" if cur else para
    if cur:
        pieces.append(cur)
    return pieces


def _as_list(meta: dict, key: str) -> list:
    v = meta.get(key, [])
    return v if isinstance(v, list) else []


def load(root: Path = DEFAULT_ROOT) -> Corpus:
    root = Path(root)
    corpus = Corpus(root)
    edir, gdir = root / "entries", root / "guides"
    for p in sorted(edir.glob("*.md")) if edir.is_dir() else []:
        try:
            meta, body = parse_file(p.read_text(encoding="utf-8"))
        except FrontmatterError as e:
            corpus.problems.append(f"{p.name}: unparsable frontmatter: {e}")
            continue
        for k in LIST_KEYS:
            if k in meta and not isinstance(meta[k], list):
                corpus.problems.append(f"{p.name}: {k} must be a list")
        eid = p.stem
        corpus.entries[eid] = Entry(
            id=eid,
            title=str(meta.get("title") or ""),
            phase=str(meta.get("phase") or ""),
            symptoms=[str(s) for s in _as_list(meta, "symptoms")],
            functions=[str(s) for s in _as_list(meta, "functions")],
            section=str(meta.get("section") or ""),
            sources=[s for s in _as_list(meta, "sources") if isinstance(s, dict)],
            see_also=[str(s) for s in _as_list(meta, "see_also")],
            body=body,
            path=p,
        )
    for p in sorted(gdir.glob("*.md")) if gdir.is_dir() else []:
        try:
            meta, body = parse_file(p.read_text(encoding="utf-8"))
        except FrontmatterError as e:
            corpus.problems.append(f"guides/{p.name}: unparsable frontmatter: {e}")
            continue
        g = Guide(
            slug=p.stem,
            title=str(meta.get("title") or ""),
            description=str(meta.get("description") or ""),
            origin=str(meta.get("origin") or ""),
            body=body,
            path=p,
        )
        g.chunks = chunk_guide(g.slug, body)
        corpus.guides[g.slug] = g
    return corpus


def _validate(title: str, phase: str, symptoms: Sequence[str]) -> None:
    if not title.strip():
        raise ValueError("title must not be empty")
    if phase not in PHASES:
        raise ValueError(f"unknown phase {phase!r}; allowed: {', '.join(PHASES)}")
    if not symptoms:
        raise ValueError(f"at least one symptom required; allowed: {', '.join(SYMPTOMS)}")
    for s in symptoms:
        if s not in SYMPTOMS:
            raise ValueError(f"unknown symptom {s!r}; allowed: {', '.join(SYMPTOMS)}")


def add_entry(
    root: Path,
    title: str,
    phase: str,
    symptoms: Sequence[str],
    body: str,
    functions: Iterable[str] = (),
    sources: Iterable[dict] = (),
    see_also: Iterable[str] = (),
    section: str = "",
) -> str:
    _validate(title, phase, list(symptoms))
    edir = Path(root) / "entries"
    edir.mkdir(parents=True, exist_ok=True)
    nums = [int(m.group(1)) for p in edir.glob("Q*.md") for m in [ID_RE.match(p.stem)] if m]
    n = max(nums, default=0) + 1
    meta = {
        "title": title,
        "phase": phase,
        "symptoms": list(symptoms),
        "functions": sorted(set(functions)),
        "section": section,
        "sources": list(sources),
        "see_also": list(see_also),
    }
    text = format_file(meta, ENTRY_KEYS, body)
    while True:
        eid = f"Q{n:04d}"
        try:
            with open(edir / f"{eid}.md", "x", encoding="utf-8") as f:
                f.write(text)
            return eid
        except FileExistsError:
            n += 1


def check(corpus: Corpus) -> List[str]:
    probs = list(corpus.problems)
    for e in corpus.entries.values():
        name = e.path.name
        if not ID_RE.match(e.id):
            probs.append(f"{name}: filename must be QNNNN.md")
        if not e.title.strip():
            probs.append(f"{name}: missing title")
        if e.phase not in PHASES:
            probs.append(f"{name}: unknown phase {e.phase!r}")
        if not e.symptoms:
            probs.append(f"{name}: no symptoms")
        for s in e.symptoms:
            if s not in SYMPTOMS:
                probs.append(f"{name}: unknown symptom {s!r}")
        for ref in e.see_also:
            if ref not in corpus.entries:
                probs.append(f"{name}: see_also {ref!r} does not exist")
    for g in corpus.guides.values():
        if not g.title.strip():
            probs.append(f"guides/{g.path.name}: missing title")
    return probs


# ---------------------------------------------------------------- search


@dataclass
class Hit:
    id: str
    kind: str  # "entry" | "guide"
    score: float
    entry: Optional[Entry] = None
    guide: Optional[Guide] = None
    chunk: Optional[Chunk] = None

    @property
    def text(self) -> str:
        return self.entry.body if self.entry else self.chunk.text


def _entry_doc(e: Entry) -> List[str]:
    return (
        tokens(e.title) * 3
        + tokens(" ".join([e.phase] + e.symptoms)) * 2
        + tokens(" ".join(e.functions)) * 2
        + tokens(e.body)
    )


def _chunk_doc(g: Guide, c: Chunk) -> List[str]:
    return tokens(g.title + " " + c.heading) * 3 + tokens(c.text)


def _query_weights(query: str) -> Dict[str, float]:
    w: Dict[str, float] = {}
    for t in tokens(query):
        w[t] = 1.0
    for t in list(w):
        for s in SYNONYMS.get(t, []):
            w.setdefault(s, 0.5)
    return w


def _bm25(docs: List[Tuple[Hit, List[str]]], weights: Dict[str, float], k1=1.2, b=0.75) -> List[Hit]:
    if not docs or not weights:
        return []
    n = len(docs)
    counts = [Counter(toks) for _, toks in docs]
    avgdl = sum(len(t) for _, t in docs) / n or 1.0
    df = Counter()
    for c in counts:
        for t in weights:
            if t in c:
                df[t] += 1
    idf = {t: math.log(1 + (n - df[t] + 0.5) / (df[t] + 0.5)) for t in weights}
    hits = []
    for (hit, toks), c in zip(docs, counts):
        dl = len(toks)
        s = 0.0
        for t, w in weights.items():
            f = c.get(t, 0)
            if f:
                s += w * idf[t] * f * (k1 + 1) / (f + k1 * (1 - b + b * dl / avgdl))
        if s > 0:
            hit.score = s
            hits.append(hit)
    hits.sort(key=lambda h: (-h.score, h.id))
    return hits


def search(
    corpus: Corpus,
    query: str,
    symptoms: Sequence[str] = (),
    phase: Optional[str] = None,
    kind: str = "all",
    limit: Optional[int] = 8,
) -> List[Hit]:
    docs: List[Tuple[Hit, List[str]]] = []
    if kind in ("all", "entry"):
        for e in corpus.entries.values():
            if phase and e.phase != phase:
                continue
            if any(s not in e.symptoms for s in symptoms):
                continue
            docs.append((Hit(e.id, "entry", 0.0, entry=e), _entry_doc(e)))
    if kind in ("all", "guide") and not symptoms and not phase:
        for g in corpus.guides.values():
            for c in g.chunks:
                docs.append((Hit(c.id, "guide", 0.0, guide=g, chunk=c), _chunk_doc(g, c)))
    hits = _bm25(docs, _query_weights(query))
    return hits if limit is None else hits[:limit]


_SYM_RE = re.compile(r"^(\w+) = 0x([0-9A-Fa-f]+);.*type:func")
FUNC_ADDR_RE = re.compile(r"^func_([0-9A-F]{8})$")


def load_symbols(repo: Path = REPO) -> Tuple[Dict[str, Set[int]], Dict[int, Set[str]]]:
    by_name: Dict[str, Set[int]] = {}
    by_addr: Dict[int, Set[str]] = {}
    for p in sorted(Path(repo).glob("symbol_addrs*.txt")):
        for line in p.read_text(encoding="utf-8", errors="replace").splitlines():
            m = _SYM_RE.match(line.strip())
            if m:
                addr = int(m.group(2), 16)
                by_name.setdefault(m.group(1), set()).add(addr)
                by_addr.setdefault(addr, set()).add(m.group(1))
    return by_name, by_addr


def function_aliases(name: str, repo: Path = REPO) -> Set[str]:
    by_name, by_addr = load_symbols(repo)
    out = {name}
    for a in by_name.get(name, ()):
        out.add(f"func_{a:08X}")
    m = FUNC_ADDR_RE.match(name)
    if m:
        out |= by_addr.get(int(m.group(1), 16), set())
    return out


def func_hits(corpus: Corpus, names: Sequence[str], repo: Path = REPO, limit: int = 30):
    aliases: Set[str] = set()
    for n in names:
        aliases |= function_aliases(n, repo)
    hits = [Hit(e.id, "entry", 0.0, entry=e) for e in sorted(corpus.entries.values(), key=lambda e: e.id)
            if aliases & set(e.functions)]
    pat = re.compile(r"\b(?:" + "|".join(re.escape(a) for a in sorted(aliases)) + r")\b")
    for g in sorted(corpus.guides.values(), key=lambda g: g.slug):
        for c in g.chunks:
            if pat.search(c.text) or pat.search(c.heading):
                hits.append(Hit(c.id, "guide", 0.0, guide=g, chunk=c))
    return sorted(aliases), hits[:limit], len(hits)


# ---------------------------------------------------------------- output


def snippet(text: str, qtoks: Sequence[str], width: int = 240) -> str:
    flat = re.sub(r"\s+", " ", text).strip()
    if len(flat) <= width:
        return flat
    low = flat.lower()
    pos = -1
    for t in qtoks:
        i = low.find(t)
        if i >= 0 and (pos < 0 or i < pos):
            pos = i
    start = max(0, pos - 60) if pos >= 0 else 0
    start = min(start, len(flat) - width)
    s = flat[start : start + width]
    return ("…" if start > 0 else "") + s + ("…" if start + width < len(flat) else "")


def hit_line(h: Hit) -> str:
    if h.kind == "entry":
        e = h.entry
        return f"{e.id}  [{e.phase} | {', '.join(e.symptoms)}]  {e.title}"
    return f"{h.id}  [guide]  {h.guide.title} › {h.chunk.heading}"


def print_hits(hits: Sequence[Hit], qtoks: Sequence[str], full: bool) -> None:
    for h in hits:
        print(hit_line(h))
        if full:
            for line in h.text.split("\n"):
                print(("    " + line).rstrip())
            print()
        else:
            print("    " + snippet(h.text, qtoks))


def print_entry(e: Entry) -> None:
    print(f"{e.id}  {e.title}")
    print(f"phase: {e.phase}   symptoms: {', '.join(e.symptoms)}")
    if e.functions:
        print(f"functions: {', '.join(e.functions)}")
    if e.section:
        print(f"section: {e.section}")
    if e.sources:
        parts = []
        for s in e.sources:
            p = s.get("path", "")
            if s.get("commit"):
                p += f" @ {s['commit'][:12]}"
            if s.get("note"):
                p += f" ({s['note']})"
            parts.append(p)
        print(f"sources: {'; '.join(parts)}")
    if e.see_also:
        print(f"see also: {', '.join(e.see_also)}")
    print()
    print(e.body)


def get_text(corpus: Corpus, ident: str) -> str:
    """Guide (`slug`) or guide section (`slug#n`) text; empty when unknown."""
    slug, _, n = ident.partition("#")
    g = corpus.guides.get(slug)
    if g is None:
        return ""
    if not n:
        return f"{g.title}\n{g.description}\n\n{g.body}"
    for c in g.chunks:
        if c.id == ident:
            return f"{g.title} › {c.heading}\n\n{c.text}"
    return ""


# ---------------------------------------------------------------- CLI


def _check_filters(symptoms: Sequence[str], phase: Optional[str]) -> None:
    for s in symptoms:
        if s not in SYMPTOMS:
            print(f"unknown symptom {s!r}; allowed: {', '.join(SYMPTOMS)}", file=sys.stderr)
            sys.exit(2)
    if phase and phase not in PHASES:
        print(f"unknown phase {phase!r}; allowed: {', '.join(PHASES)}", file=sys.stderr)
        sys.exit(2)


def cmd_search(a) -> int:
    _check_filters(a.symptom, a.phase)
    corpus = load(a.root)
    query = " ".join(a.words)
    hits = search(corpus, query, a.symptom, a.phase, a.kind, limit=None)
    if not hits:
        print("no hits; try fewer words or drop --symptom (tags: python3 tools/quirks.py tags)")
        return 0
    shown = hits[: a.n]
    print_hits(shown, tokens(query), a.full)
    print(f"({len(shown)} of {len(hits)} hits; get <ID> for full text, -n for more)")
    return 0


def cmd_func(a) -> int:
    corpus = load(a.root)
    aliases, hits, total = func_hits(corpus, a.names, a.repo)
    print(f"aliases: {', '.join(aliases)}")
    if not hits:
        print("no entries cite it; try: python3 tools/quirks.py search <words from the diff>")
        return 0
    print_hits(hits, [a.lower() for a in aliases], a.full)
    print(f"({len(hits)} of {total} hits; get <ID> for full text)")
    return 0


def cmd_get(a) -> int:
    corpus = load(a.root)
    rc = 0
    for i, ident in enumerate(a.ids):
        if i:
            print("\n" + "-" * 72 + "\n")
        if ident in corpus.entries:
            print_entry(corpus.entries[ident])
            continue
        text = get_text(corpus, ident)
        if not text:
            print(f"unknown id {ident!r}", file=sys.stderr)
            rc = 1
            continue
        print(text)
    return rc


def cmd_tags(a) -> int:
    corpus = load(a.root)
    pc = Counter(e.phase for e in corpus.entries.values())
    sc = Counter(s for e in corpus.entries.values() for s in e.symptoms)
    pw = max(len(k) for k in list(PHASES) + list(SYMPTOMS))
    for k, d in PHASES.items():
        print(f"phase    {k:<{pw}}  {pc[k]:4d}  {d}")
    for k, d in SYMPTOMS.items():
        print(f"symptom  {k:<{pw}}  {sc[k]:4d}  {d}")
    return 0


def _parse_source(s: str) -> dict:
    path, sep, commit = s.rpartition("@")
    if not sep:
        return {"path": s}
    return {"path": path, "commit": commit}


def cmd_add(a) -> int:
    body = a.body if a.body is not None else Path(a.body_file).read_text(encoding="utf-8")
    try:
        eid = add_entry(
            a.root, a.title, a.phase, a.symptom, body,
            functions=a.function, sources=[_parse_source(s) for s in a.source], see_also=a.see_also,
        )
    except ValueError as e:
        print(str(e), file=sys.stderr)
        return 2
    corpus = load(a.root)
    path = corpus.entries[eid].path
    try:
        path = path.relative_to(REPO)
    except ValueError:
        pass
    print(f"added {eid} {path}")
    sim = [h for h in search(corpus, f"{a.title} {body}", limit=4) if h.id != eid][:3]
    if sim:
        print("similar:")
        print_hits(sim, tokens(a.title), False)
    return 0


def cmd_check(a) -> int:
    corpus = load(a.root)
    probs = check(corpus)
    if probs:
        for p in probs:
            print(p)
        return 1
    print(f"quirks OK: {len(corpus.entries)} entries, {len(corpus.guides)} guides")
    return 0


def main(argv: Optional[Sequence[str]] = None) -> int:
    ap = argparse.ArgumentParser(prog="quirks.py", description=__doc__.split("\n\n")[0])
    ap.add_argument("--root", type=Path, default=DEFAULT_ROOT, help="store root (default knowledge/ido)")
    ap.add_argument("--repo", type=Path, default=REPO, help=argparse.SUPPRESS)
    sub = ap.add_subparsers(dest="cmd", required=True)

    p = sub.add_parser("search", help="ranked search over entries and guide sections")
    p.add_argument("--symptom", action="append", default=[], metavar="TAG")
    p.add_argument("--phase")
    p.add_argument("--kind", choices=("all", "entry", "guide"), default="all")
    p.add_argument("-n", type=int, default=8)
    p.add_argument("--full", action="store_true")
    p.add_argument("words", nargs="+")
    p.set_defaults(fn=cmd_search)

    p = sub.add_parser("func", help="entries and guide sections citing a function")
    p.add_argument("--full", action="store_true")
    p.add_argument("names", nargs="+")
    p.set_defaults(fn=cmd_func)

    p = sub.add_parser("get", help="print entries (Q0042), guides (slug) or guide sections (slug#3)")
    p.add_argument("ids", nargs="+")
    p.set_defaults(fn=cmd_get)

    p = sub.add_parser("tags", help="phases and symptom tags with counts")
    p.set_defaults(fn=cmd_tags)

    p = sub.add_parser("add", help="add an entry")
    p.add_argument("--title", required=True)
    p.add_argument("--phase", required=True)
    p.add_argument("--symptom", action="append", default=[], required=True)
    g = p.add_mutually_exclusive_group(required=True)
    g.add_argument("--body")
    g.add_argument("--body-file")
    p.add_argument("--function", action="append", default=[])
    p.add_argument("--source", action="append", default=[], metavar="PATH@COMMIT")
    p.add_argument("--see-also", action="append", default=[], metavar="ID")
    p.set_defaults(fn=cmd_add)

    p = sub.add_parser("check", help="validate the store")
    p.set_defaults(fn=cmd_check)

    a = ap.parse_args(argv)
    return a.fn(a)


if __name__ == "__main__":
    sys.exit(main())

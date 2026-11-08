#!/usr/bin/env python3
"""ugen scratch-ring (FIFO free list) simulator for a ugen listing (`t.s` from `tools/as1probe.py keep`,
or any function slice of it). Host-side, pure Python.

    python3 tools/ringfifo.py sim DIR_or_t.s FUNC [--exclude 11,12] [--range LO-HI]
        print every instruction of FUNC with the queue after it and flag allocations the model
        did not predict (`<-- model expected $N`); the queue printed at a label is the state a
        fall-through enters it with.
    python3 tools/ringfifo.py corpus [DIR]      (default .scratch/ugen_corpus, from `as1probe.py corpus`)
        run the model over every function of every stored listing and summarise mismatches.

Model (validated on the matched corpus, see knowledge/ido Q0554 and its successors):
  * The ring is `$t6 $t7 $t8 $t9 $t3 $t4 $t5` (`14 15 24 25 11 12 13`, in that initial order) minus every
    register uopt coloured anywhere in the function (a web living across a label); `--exclude` names
    those when the heuristic below misses a single-block web.
  * An allocation takes the queue front; a register is appended when its value dies: at its last use
    (operands in textual order), immediately for a dead definition, immediately for the third
    (scratch) operand of `trunc.w.*`.
  * Known gaps, reported as notes rather than modelled: 64-bit pairs and struct-copy idioms take an
    aligned even/odd pair (skipping unaligned fronts) and free it as a unit even-first; `jal $25`
    reserves `$25`; the `cfc1/ctc1` conversion idiom and `$1`-based copies pick registers their own way.
"""
import os
import re
import sys

RING = [14, 15, 24, 25, 11, 12, 13]


def decode(s):
    s = s.strip()
    if not s or s.startswith('#') or s.startswith('.'):
        return None
    if s.endswith(':'):
        return ('label', s, None, [], None)
    parts = s.split(None, 1)
    op = parts[0]
    args = [a.strip() for a in parts[1].split(',')] if len(parts) > 1 else []
    store_like = op in ('sw', 'sb', 'sh', 's.s', 's.d', 'mtc1', 'dmtc1', 'swc1', 'sdc1', 'usw', 'ush') \
        or op.startswith('b') or op in ('j', 'jal')
    dst = None
    if not store_like and args:
        m = re.match(r'^\$(\d+)$', args[0])
        if m:
            dst = int(m.group(1))
    srcs = []
    for a in (args if store_like else args[1:]):
        # `$$24` is a local string/jump-table label, not register 24; `$848` in `lw $25, $848($25)` is a table label
        srcs += [int(x) for x in re.findall(r'(?<!\$)\$(\d+)(?!\d)', a) if int(x) <= 31]
    scratch = None
    if op.startswith('trunc') and len(args) == 3:
        m = re.match(r'^\$(\d+)$', args[2])
        if m:
            scratch = int(m.group(1))
            srcs.remove(scratch)
    return (op, s, dst, srcs, scratch)


def uopt_regs(ins):
    """ring registers used across a label (a uopt web): defined, then after a label used before redefinition"""
    res = set()
    for r in RING:
        defined = crossed = False
        for op, s, dst, srcs, scr in ins:
            if op == 'label':
                crossed = crossed or defined
                continue
            if r in srcs and defined and crossed:
                res.add(r)
                break
            if dst == r or scr == r:
                defined, crossed = True, False
    return res


def simulate(ins, ring):
    n = len(ins)

    def last_use(k, r):
        for j in range(k + 1, n):
            op, s, dst, srcs, scr = ins[j]
            if op == 'label':
                continue
            if r in srcs:
                return False
            if dst == r or scr == r:
                return True
        return True

    q = list(ring)
    live = set()
    out, bad = [], []
    for k, (op, s, dst, srcs, scr) in enumerate(ins):
        if op == 'label':
            out.append(f'{"":5} {s:44} q={q}')
            continue
        note = ''
        for r in srcs:
            if r in ring and r in live and last_use(k, r):
                live.discard(r)
                q.append(r)
        if dst in ring and dst not in live:
            exp = q[0] if q else None
            if dst in q:
                q.remove(dst)
            else:
                note += f' (alloc of live/missing ${dst})'
            if dst != exp:
                note += f'  <-- model expected ${exp}'
                bad.append(k)
            live.add(dst)
            if last_use(k, dst):
                live.discard(dst)
                q.append(dst)
        if scr is not None and scr in ring:
            exp = q[0] if q else None
            if scr in q:
                q.remove(scr)
            if scr != exp:
                note += f'  <-- scratch: model expected ${exp}'
                bad.append(k)
            q.append(scr)
        if op == 'jal' and srcs == [25]:
            note += '  (jal $25: t9 reserved by convention)'
        out.append(f'{k:5d} {s:44} q={q}{note}')
    return out, bad


def functions(path):
    cur, body = None, []
    for line in open(path, errors='replace'):
        m = re.match(r'^([A-Za-z_][A-Za-z0-9_]*):\s*$', line)
        if m:
            if cur:
                yield cur, body
            cur, body = m.group(1), []
        elif cur:
            body.append(line.rstrip('\n'))
    if cur:
        yield cur, body


def cmd_sim(args):
    path = args[0]
    if os.path.isdir(path):
        path = os.path.join(path, 't.s')
    func = args[1]
    exclude = set()
    lo, hi = 0, 1 << 30
    for i, a in enumerate(args):
        if a == '--exclude':
            exclude = {int(x) for x in args[i + 1].split(',')}
        if a == '--range':
            spec = args[i + 1] if '-' in args[i + 1] else args[i + 1] + '-' + args[i + 2]
            lo, hi = (int(x) for x in spec.split('-'))
    for name, body in functions(path):
        if name != func:
            continue
        ins = [d for d in (decode(l) for l in body) if d]
        ex = uopt_regs(ins) | exclude
        ring = [r for r in RING if r not in ex]
        print(f'ring {ring} (uopt-coloured, excluded: {sorted(ex)})')
        out, bad = simulate(ins, ring)
        for k, l in enumerate(out):
            if lo <= k <= hi:
                print(l)
        print(f'mismatches: {len(bad)}')
        return
    raise SystemExit(f'{func}: not found in {path}')


def cmd_corpus(args):
    root = args[0] if args else '.scratch/ugen_corpus'
    total = nbad = 0
    for dp, dn, fn in os.walk(root):
        for f in sorted(fn):
            if not f.endswith('.s'):
                continue
            path = os.path.join(dp, f)
            for name, body in functions(path):
                ins = [d for d in (decode(l) for l in body) if d]
                if not ins:
                    continue
                total += 1
                ring = [r for r in RING if r not in uopt_regs(ins)]
                out, bad = simulate(ins, ring)
                if bad:
                    nbad += 1
                    k = bad[0]
                    print(f'== {path} {name}: {len(bad)} mismatches, first at {k}')
                    for l in out[max(0, k - 6):k + 1]:
                        print('   ', l[:120])
    print(f'functions: {total}, with mismatches: {nbad}')


def main():
    if len(sys.argv) < 2 or sys.argv[1] not in ('sim', 'corpus'):
        raise SystemExit(__doc__)
    (cmd_sim if sys.argv[1] == 'sim' else cmd_corpus)(sys.argv[2:])


if __name__ == '__main__':
    main()

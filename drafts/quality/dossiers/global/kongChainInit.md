# kongChainInit (global, src/global/CC800.c)

## Sites
global:806C8220:other:dc42ce other: `s32 count = 1; s32 n = 4;` dead declaration initialisers (every case overwrites count/n, default returns). After uopt they emit no code (ugen `.loc 2 104` empty); their only effect is uopt candidate numbering: count bit 3 -> $v0, n bit 6 -> $v1, chain bit 9 -> $a0 (forbidden 1,2,4,5), offsets bit 29 -> $a1. Without them `chain = chains` is bit 3 -> $v0, count bit 22 -> $v1, n bit 25 -> $a0 (fdiff 23, register-only).
global:806C8220:dead-store:2d8cdb / 313bb1: RETIRED (folded into dc42ce by HackkongChainInit2).

## Attempts
2026-11-10..15  rounds 8/16/20 + Hackfunc/PermBatch/Polish/TypesOwner (opus low/high): remove/cond/permute/diagnose all nohit; dead stores kept (see quality.py history).
2026-11-15  HackkongChainInit2  anthropic/claude-opus-5-5:high  declaration-initialiser form (Q0802): every table copy and scalar default as a declaration initialiser, 64-placement grid of (count/n, chain, sign) among tbl8/tbl11/tbl4 -> only `tbl8, tbl11, tbl4, count = 1, n = 4, chain = chains, sign = 1.0f` gives fdiff 0 (a063); separate `s32 count = 1; s32 n = 4;` also 0, reversed n/count 13.
2026-11-15  HackkongChainInit2  load-bearing checks (Q0784, compile without the store): no count/n init 23; n only 23; count only 18.
2026-11-15  HackkongChainInit2  live-default forms: case 2 offsets only (count/n from the inits), 64-placement grid -> best 4 (o027: tbl8, count/n, tbl11, chain, tbl4, sign; count/n stack slots move tbl11 to sp+0x40 / tbl4 to sp+0x2C, and case 3's `count = 1` vanishes from the 0x810 delay slot). Case 2 empty + `offsets = tbl4.offsetX` initialiser, 64 placements -> best 27.
2026-11-15  HackkongChainInit2  recipe scan on the result: swap/float(1.0f, 128.0f)/width(count s8/s16) zeros are neutral spellings; springX `0.0` -> `0.0f` gives 9 (kept, ordinary double literal).
2026-11-17  CleankongChainInit  anthropic/claude-opus-5-5  sweep: plain/recipe nohit (no rewrite/no removal).
2026-11-17  CleankongChainInit  uopt_trace -l5/-l6 + as1probe keep (base and no-init): case 2 block `$34` (ugen records 116-122: li $2,1 / li $3,4 / move $5,$9) survives uopt in both bodies; as1 moves it above `beq a2,t5` (0x764/0x768/0x7d4). Colouring is unconstrained bit order (Q0897/Q1063): the init only moves count/n bits ahead of chain. No-init asm is the target with count/n/chain in $v1/$a0/$v0 instead of $v0/$v1/$a0 (fdiff 23).
2026-11-17  CleankongChainInit  no-init natural shapes (variants.py try, fdiff full): if/else chain 2,3,5 35 / 3,2,5 43 / 3,5,2 45 / 5,3,2 49; pre-switch validity test + default-less switch 36; per-case statement orders 18-34 (n,count,offsets 18); chain = chains after the switch 101, in the for init 27; chains[i] indexing 140; param stepped directly 144; register count/n 23; count = 0 live default 34 (no default label / default break), default: count = 0 26; variants scan 45 variants best 23.
2026-11-17  CleankongChainInit  live-default at the base declaration order (inits live for case 2, case 2 sets offsets only): 7 = two independent diffs: uopt keeps the live inits in bb 0 so ugen/as1 place li v0,1 / li v1,4 at their .loc after move a0,a1 (0x7cc/0x7d8, not 0x764/0x768), and uopt deletes case 3's redundant `count = 1` (0x810 delay slot becomes li v1,11).
2026-11-17  CleankongChainInit  permuter 900 s from the live-default body (perm_livedef, base 304, best 185): both 185 outputs re-insert steers (an unreachable `n = 1;` before the first case label feeding `count = n`, or `count = 1; count = 11; n = count;`); nohit.
2026-11-17  CleankongChainInit  review: LAYOUT springY line: split into three lines in the same order = 4 (only swc1 $f2,0x10/0x14 swap at 0x980/0x988, as1); the joined line in the 5 other orders 20-42; chained `angle = offset = velocity = 0.0f` 6, other chains 26-48; split in other orders 16-42.

## Untried ideas
- A natural statement in bb 0, before `chain = chains`, that references count and n without being dead: none found; every live default makes case 3's `count = 1` redundant (uopt deletes it). Candidate bits are created at first appearance in bb order, so count/n must appear in bb 0 before chain while offsets stays after chain (offsets is set in the same case blocks as count/n).
- Lead decision: the LAYOUT springY line fails the "matches in both orders" test (other one-line orders 20-42) although the split form differs only in as1 order (0x980/0x988).

## Evidence
Target 0x720 (frame 0x98): tbl8 copy into sp+0x74 (0x724-0x790) interleaved with li t5,2 (0x758), li v0,1 (0x764), li v1,4 (0x768); tbl11 sp+0x48 copy loop (0x798-0x7b8); tbl4 sp+0x38 (0x7dc-0x804) with move a0,a1 (chain, 0x7d0) and move a1,t1 (offsets=tbl4, 0x7d4); lui 0x3f80 sign (0x7f8). Switch: beq kind,2 -> 0x840 (case 2 has no code), case 3 li v0,1 delay slot 0x810 / li v1,11 0x828 / move a1,t0; case 5 li v0,2 0x81c / li v1,8 / move a1,a3; default b 0xa04.
ugen (as1probe keep, base): init line `.loc 2 104` emits nothing; `$34:` case 2 = li $2,1 / li $3,4 / move $5,$9 (records 116-122) after `$33` case 5; as1 hoists `$34` above `beq $6,$13,$34`.
uopt -l5 (base): count {528} bit 3 -> 1 ($v0), n {464} bit 6 -> 2 ($v1), chain {400} bit 9 -> 3 ($a0), chains P4 bit 11 -> 4 ($a1), kind P8 bit 19 -> 5 ($a2), offsets {272} bit 29 -> 4 ($a1); count live bbs 4/5/6 (case stores) and the loop, none in bb 0.

# n_alFxPull (global, src/global/141EF0.c, IDO 7.1 -g)

## Sites
- df951f: empty `else {}` after `if ((D_807FF0F4[busIndex] != 0) && (busChan == 0))`. Now tagged `// ORIG:`. The target branches over the empty arm with `b 0x748; nop` at 0x740.

## Attempts
- 2026-11-14 U Hackn_alFxPull: classified as ORIG (objdump offset cited); no empty macro in include/.

## Evidence
- Target 0x738 `ori t3,t1,0x4e0`, 0x73c `sw t3,4(t2)`, 0x740 `b 748`, 0x744 `nop`, then 0x748 continues with `ptr++`.

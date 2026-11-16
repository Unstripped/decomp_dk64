# textDrawAnimated (global, src/global/1025E0.c)
## Sites
None left (all three removed 2026-11-16, whole-object fdiff 0). Base keys:
global:806FE078:proto-steer:2ed6ea proto-steer (removed): `#define PROTO_SKIP_textGetCharAdvance`. With the shared `s16 textGetCharAdvance(s16, u8)` an s32 `ch` gets `andi a1,v1,0xff` before the jal at 0x8d0; the target passes the lbu-loaded ch in a1 unmasked.
global:806FE078:proto-steer:69fe0c proto-steer (removed): `extern s16 textGetCharAdvance(s16, s32);`, paired with 2ed6ea. Its s16 first parameter is real (sll/sra of node->font at 0x8c8-0x8cc, `move a0,t1` in the 0x8d4 delay slot).
global:806FE078:other:f0f024 other (removed): loop latch `ch = *(strPos + node->text); strPos += 1;` on the phase-wrap line kept `addu t4,s5,a0` (index first) at 0x1348.
## Attempts
2026-11-09 bootstrap orchestrator: protos.py consolidate of 2ed6ea/69fe0c -> object changes (STEER).
2026-11-11 round 10 Rev10D/Rev10G claude-opus-5-5:low: consolidate (also u8 ch) -> fdiff 1; reconstruct with 3 sites removed -> score 305 (.text 5344 vs 5328); permute f0f024 -> best 10 (only joins lines).
2026-11-11 round 16 Rev16B claude-opus-5-5:xhigh: shared (s16,u8) -> andi a1,v1,0xff (+16 bytes, 235); u8 ch -> beqz + move v1,a1 at 0x8ac, s5 increment moves (890); s16/u32 ch keep andi.
2026-11-11 round 16 Rev16D xhigh: permute f0f024 from node->text[strPos] on own lines -> only joins latch+gDP lines.
2026-11-11 round 16 Rev16I claude-opus-5-5:low: header (s16,u8) -> extra move a0,t1 (.text 5344); u8 ch local -> .text equal, score 890; TextObjectElem *elem rewrite -> .text 4880.
2026-11-12 round 17 Rev17M claude-opus-5-5:low: 100180.h (s16,u8) + u8 ch -> v1/a1 swap of ch vs gScreenWidth/font loads at 0x814-0x8c8, fdiff 1.
2026-11-16 HacktextDrawAnimated anthropic/claude-opus-5-5:high: sweep on the base copy -> 0 hits (f0f024 plain/recipe nohit).
2026-11-16 HacktextDrawAnimated: local decl `(s32, s32)` and K&R `()` -> the font sll/sra disappears (`move a0,v1` at 0x8cc instead of `move a0,t1` at 0x8d4) -> fdiff 1; the caller saw an s16 first parameter, so an unprototyped call / K&R owner definition (Q0779) is excluded.
2026-11-16 HacktextDrawAnimated: uopt trace of the consolidated u8-ch form (no PROTO_SKIP, no local decl, `u8 ch`): bit 61 is `ucvt(ch)` feeding `ch != 0`/`ch != 0x20` (uneq/ucg1 on 675), a new live range coloured v1 while ch/the a1 argument stay in a1; gScreenWidth (0x814-0x82c), the font lbu (0x8c4) and the 0x1220 gTextFonts index move to a2; `move v1,a1` fills the 0x8b0 and 0x1378 delay slots. In the s32 form the compares read the variable itself (no ucvt), so ch coalesces with the a1 argument.
2026-11-16 HacktextDrawAnimated: variants scan (default recipes + declswap) on the u8-ch form -> no variant below baseline 18 except `ch` widened (16, re-adds andi).
2026-11-16 HacktextDrawAnimated: permuter (hack-free weights) from the consolidated u8-ch form, -j 2: stopped after ~11 min once the hand fix landed (not recorded).
2026-11-16 HacktextDrawAnimated: FIX. `u8 ch` + `while (ch)` instead of `while (ch != 0)` -> fdiff 0 with the shared (s16, u8) prototype (trace: the loop test is `uneq{ch},0` on the variable, ucvt(ch) remains only for the 0x20 compare). Then the pre-loop `strPos = 1; ch = node->text[0];` -> `ch = node->text[strPos++];` (fdiff 0; the dead `strPos = 0` had steered s5/s6/s7 at 0x890-0x898, score 70 without it), and finally the latch folded into `while ((ch = node->text[strPos++]))` with the phase wrap on its own lines -> whole-object fdiff 0. `ch != ' '` replaces `ch != 0x20` (same code). Rejected on the way: multi-line latch `ch = node->text[strPos++];` after the wrap (60), latch first on one line (940), `while ((ch = ...) != 0)` (890), `/ 2 - 3` for `/ 2 + -3` (fdiff 1: target add.s with -3.0 at 0x874).
## Untried ideas
None (no sites left).
An owner retype of 100180.c is not needed and is excluded anyway by the callee's u8 home-slot reads (sw a1,28(sp); lbu t3,31(sp); addiu a1,sp,31 for &ch at 0x2340-0x23b0 of 100180.o; Q0025/Q0862).
## Evidence
0x8a8 `lbu a1,0(a0)` first ch; 0x8ac `beqzl a1,0x1380` / `lw a0,0x90(sp)`; 0x8c0 `beq a1,at` (0x20); 0x8c4 `lbu v1,0xc(s2)`; 0x8c8 `sll a0,v1,16`; 0x8cc `sra t1,a0,16`; 0x8d0 jal textGetCharAdvance; 0x8d4 `move a0,t1` (no andi on a1).
0x814/0x818 gScreenWidth `lui/lh v1`; 0x1220 `sll t2,v1,2` (gTextFonts index from the font in v1).
Latch: 0x1348 `addu t4,s5,a0`; 0x135c/0x1368 `lbu a1,0(t4)`; 0x136c `addiu s5,s5,1`; 0x1374 `bnez a1,0x8bc`; 0x1378 `sra s5,t5,16`.
Callee textGetCharAdvance (100180.o 0x2328): `sw a1,28(sp)`, `lbu t3,31(sp)` (ch == ' '), `addiu a1,sp,31` (&ch) — a u8 parameter.

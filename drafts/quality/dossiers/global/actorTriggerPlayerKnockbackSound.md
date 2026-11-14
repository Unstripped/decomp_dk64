# actorTriggerPlayerKnockbackSound (global, src/global/7BA00.c)

## Sites
global:80676D00:noop-arith:abfc8a (base key df25b8) noop-arith: `ps->surfaceTimer == (ps->playerIndex * 0)` gives the `lbu 0x1A4(v0)` result a second use (ucvt * 0), so that load becomes its own web (uopt lr 12, adjsave 3.0) next to `kong` (lr 10, a2, spilled `sb a2,0x37(sp)`). That takes the last of the 6 colourable registers, so `attacker` (param a0, lr 43, adjsave -0.5) gets no register before `jal playerCanTakeHit`: it stays in its home `0x38(sp)` and is reloaded into v1 at 0x6c. Without the FAKE, attacker is coloured a3 (`move a3,a0` at 0x18, `sw a3,0x38(sp)` before the jal, `lw a3` after), and &gPrimaryPlayerActor moves a3 -> a2, kong a2 -> v1 (full=29).

## Attempts
2026-11-14 U HackactorTriggerPlayerKnockbackSound anthropic/claude-opus-5-5: views retired (u8 *beh -> PlayerState *ps, PlayerData view -> PlayerStruct *gPlayerSlots) with the FAKE kept -> fdiff 0.
2026-11-14 U HackactorTriggerPlayerKnockbackSound anthropic/claude-opus-5-5: plain `surfaceTimer == 0` (raw or typed), `!surfaceTimer`, kong load after the stateFlags store (29), inside the surfaceTimer if (30), declaration-initialised `ps` (24), declaration order / s32 pad (27), kong width s8/s16/u16/s32/u32 (29), s32 kong with `(u8)` index (61), variants.py scan swap/float/width/declswap (all 29), `&&`-merged ifs, early return, block-scope declarations (29).
2026-11-14 U HackactorTriggerPlayerKnockbackSound anthropic/claude-opus-5-5: extra natural webs (Q0682): `Actor *player = gPrimaryPlayerActor` for the pre-jal uses (31; also kept for post-jal uses: 29), `PlayerStruct *slot` local (63), kong via `gPrimaryPlayerActor->customState` (25), ps from gPrimaryPlayerActor (80), all through `target->customState` without a local (73).
2026-11-14 U HackactorTriggerPlayerKnockbackSound anthropic/claude-opus-5-5: zeros that are hidden steers (not taken): kong read as `((PlayerState *)target->customState)->playerIndex` beside `ps`, stateFlags written through `target->customState`, or a second PlayerState * local `ps2 = target->customState` for kong. Each makes the customState load a two-use web, the same register-pressure effect as the FAKE.
2026-11-14 U HackactorTriggerPlayerKnockbackSound anthropic/claude-opus-5-5: permuter 900 s (hack-free weights) on the typed, FAKE-free body: base 959, 24 zero outputs, all steer swaps (19 dead ifs such as `if (!ps->playerIndex) {}`, 5 copy temps `new_var = ps->playerIndex; kong = new_var`) -> nohit.

## Untried ideas
A natural second consumer of `target->customState` or of the playerIndex load that exists in the original source (e.g. a macro or inlined helper expanding to a second customState read): not identifiable from the asm alone (Q0682, Q0601).

## Evidence
0x24 `lw v0,0x174(a1)` customState; 0x2c/0x30/0x34 `lw 0x1f0`, `lh 0xd4`, `lbu a2,0x1a4` from v0; 0x3c `bnez t9` (surfaceTimer == 0); 0x04 `sw a3,0x44(sp)` then 0x08 `lui a3,%hi(gPrimaryPlayerActor)` (a3 = &gPrimaryPlayerActor); 0x18 `sw a0,0x38(sp)` (attacker home, no copy); 0x58 `sw a1,0x3c(sp)`, 0x60 `sb a2,0x37(sp)` around `jal playerCanTakeHit`; 0x6c `lw v1,0x38(sp)` attacker, 0x78 `lbu a2,0x37(sp)` kong; 0x80-0xa4 kong * 0x2F0 as sll/subu/sll/subu/sll for gPlayerSlots[kong].unk2C0.

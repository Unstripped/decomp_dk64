// func_806A2A10 (src/global/A7710.c): stage 6, score 285: arg0 = arg0 & 0xFFFF reproduces the narrow s16 home (move t6,a0; sh t6,0x1A); if-body order arg2-- first (285 vs 575); empty if(0) in else (380->285) stops the %hi(D_807FBB40) hoist; remaining = which path rematerialises &D_807FBB44 (2 insns) + temp numbers
/* func_806A2A10 (src/global/A7710.c) - stage 6, best objdiff score 285 (~6 insns).
 * KEY FINDINGS (all verified by compiling):
 *  - `arg0 = arg0 & 0xFFFF;` (reassign the s16 parameter through a narrow mask) is what
 *    makes IDO emit the target's prologue `move t6,a0; sh t6,0x1A` narrow home store.
 *    No declaration form (ANSI s16, K&R, u16, s32+s16 local, address-taken, volatile)
 *    produces it. Without this line the function is 2 insns short.
 *  - the if-body order `arg2--; D_807FBB44->unk15F = 0xB;` (decrement first) is worth
 *    285 vs 575 for the opposite order; it is semantically identical to the target.
 *  - an empty `if (0) { }` before the else store drops the score from 380 to 285: it
 *    stops IDO hoisting `lui t8,%hi(D_807FBB40)` into the `beqz` delay slot, which
 *    restores the target's `lh/lui/lbu/andi` order after the actorSpawn call.
 * REMAINING DIFF (pure allocation): the redundant re-materialisation
 *    `lui v0,%hi(D_807FBB44); addiu v0,v0,%lo(D_807FBB44)`
 * sits in the if-body in the target (0x44-0x48) but in the else-body here, so the
 * delay-slot address is used by the opposite path; temp numbers follow (t0/t6, t1/t8,
 * t2/t0, t3/t6). Everything else, including the epilogue, is instruction-identical.
 */
extern Actor *D_807FBB40;
extern Actor *D_807FBB44;
extern void *D_807FD580;
s32 actorSpawn(s32, s32);

void func_806A2A10(s16 arg0, s16 arg1, u8 arg2) {
    arg0 = arg0 & 0xFFFF;
    actorSpawn(0xB0, 0);
    if (arg0 & 0x8000) {
        arg2--;
        D_807FBB44->unk15F = 0xB;
    } else {
        if (0) {
        }
        D_807FBB44->unk15F = 6;
    }
    D_807FBB40->unk11C = (void *)D_807FBB44;
    *(s32 *)((u8 *)D_807FD580 + 0x1A8) = (s32)D_807FBB44;
    *(s32 *)((u8 *)D_807FBB44->unk174 + 0xC) = arg2;
    D_807FBB44->unk7C = (f32)(s16)(arg0 & 0x7FFF);
    D_807FBB44->unk80 = (f32)arg1;
    D_807FBB44->unk154 = 1;
    D_807FBB44->unk128 = 0;
}

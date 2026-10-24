// func_806A2A10 (src/global/A7710.c): stage 6, score 285: arg0 = arg0 & 0xFFFF reproduces the narrow s16 home (move t6,a0; sh t6,0x1A); remaining diff = which branch rematerialises &D_807FBB44 (2 insns swapped between if/else) + temp numbering
/* func_806A2A10 (src/global/A7710.c) - stage 6, closest 285 (objdiff score), ~6 insns differ.
 * KEY FINDING: `arg0 = arg0 & 0xFFFF;` (a reassigning narrow mask of the s16 parameter)
 * makes IDO emit the target's `move t6,a0; sh t6,0x1A` narrow home store in the prologue.
 * With it the body is instruction-for-instruction identical to the target except:
 *   - the redundant re-materialisation `lui v0,%hi(D_807FBB44); addiu v0,v0,%lo(...)`
 *     sits in the opposite branch (target: taken/if body at 0x44-0x48, ours: else body),
 *     i.e. target keeps the delay-slot address for the else path and recomputes for the
 *     if path; ours does the reverse;
 *   - temp register numbers (t0/t6, t1/t8, t2/t0, t3 ...) differ accordingly.
 * Everything else (prologue, call, reload order lh/lui/lbu/andi, epilogue) matches.
 * The `if (0) {}` empty block (a permuter artefact, semantically inert) is what removes
 * the early `lui t8,%hi(D_807FBB40)` hoist that otherwise fills the beqz delay slot.
 */
extern Actor *D_807FBB40;
extern Actor *D_807FBB44;
extern void *D_807FD580;
s32 actorSpawn(s32, s32);

void func_806A2A10(s16 arg0, s16 arg1, u8 arg2) {
    arg0 = arg0 & 0xFFFF;
    actorSpawn(0xB0, 0);
    if (arg0 & 0x8000) {
        D_807FBB44->unk15F = 0xB;
        arg2--;
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

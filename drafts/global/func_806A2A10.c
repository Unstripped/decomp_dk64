// func_806A2A10 (src/global/A7710.c): stage 6: 2 insns short - missing 'move t6,a0; sh t6,0x1A' narrow home store of the s16 first param; all else identical
// The target prologue issues `move t6,a0; sh t6,0x1A(sp)` (a narrow home store of the
// first s16 parameter) before the actorSpawn call; this source only homes the three
// argument words plus the u8 (sb a2,0x23) and reads the s16 params at 0x1A/0x1E.
// Everything else is instruction-identical (same registers, same &D_807FBB44
// materialisation in both the pre-branch and the if-body). Tried: s16 s16 u8 prototype,
// K&R definition, s32 arg0 + s16 local, `id = arg0` / `id = (s16)arg0`, `arg0 = (s16)arg0`,
// address-taken parameter, volatile local - IDO folds all of them into the a0 home.
extern Actor *D_807FBB40;
extern Actor *D_807FBB44;
extern void *D_807FD580;
s32 actorSpawn(s32, s32);

void func_806A2A10(s16 arg0, s16 arg1, u8 arg2) {
    s16 id;

    id = arg0;
    actorSpawn(0xB0, 0);
    if (id & 0x8000) {
        D_807FBB44->unk15F = 0xB;
        arg2--;
    } else {
        D_807FBB44->unk15F = 6;
    }
    D_807FBB40->unk11C = (void *)D_807FBB44;
    *(s32 *)((u8 *)D_807FD580 + 0x1A8) = (s32)D_807FBB44;
    *(s32 *)((u8 *)D_807FBB44->unk174 + 0xC) = arg2;
    D_807FBB44->unk7C = (f32)(s16)(id & 0x7FFF);
    D_807FBB44->unk80 = (f32)arg1;
    D_807FBB44->unk154 = 1;
    D_807FBB44->unk128 = 0;
}

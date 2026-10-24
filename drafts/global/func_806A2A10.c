// func_806A2A10 (src/global/A7710.c): stage 6: differs only by 2 instructions - the target explicitly stores (s16)arg0 to a halfword home ("move t6,a0; sh t6,0x1A") and materialises &D_807FBB44 twice; all else identical
extern Actor *D_807FBB40;
extern Actor *D_807FBB44;
extern void *D_807FD580;
s32 actorSpawn(s32, s32);

void func_806A2A10(s32 arg0, s16 arg1, u8 arg2) {
    s16 id;

    id = arg0;
    actorSpawn(0xB0, 0);
    if (id & 0x8000) {
        D_807FBB44->unk15F = 0xB;
        arg2--;
    } else {
        D_807FBB44->unk15F = 6;
    }
    D_807FBB40->unk11C = D_807FBB44;
    *(s32 *)((u8 *)D_807FD580 + 0x1A8) = D_807FBB44;
    *(s32 *)((u8 *)D_807FBB44->unk174 + 0xC) = arg2;
    D_807FBB44->unk7C = (f32)(s16)(id & 0x7FFF);
    D_807FBB44->unk80 = (f32)arg1;
    D_807FBB44->unk154 = 1;
    D_807FBB44->unk128 = 0;
}

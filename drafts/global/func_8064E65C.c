// func_8064E65C (src/global/478F0.c): text-identical, reloc only: all instructions match; only .rodata jtbl/double relocs differ (jtbl_80758B7C, D_80758BB0/BB8/BC0 vs .rodata+off). Needs orchestrator paste/ROM check. Key: lazy state ptr as 'if (*(s32**)cs==NULL){alloc} q=*(s32**)cs;' + decl order q,x,y,z,g,bl (no p).
typedef struct CsB16View {
    /* 0x00 */ u8 pad0[0x98];
    /* 0x98 */ s16 unk98;
} CsB16View;
s32 actorSpawn(s32, s32);

void func_8064E65C(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 *q;
    f32 x;
    f32 y;
    f32 z;
    f64 g;
    f64 bl;

    if (b != 11) {
        modelSlotGetNodePos(csId, 1, 1, &x, &y, &z);
    }
    ((CsB16View *)cs)->unk98 = y - D_807F6220;
    if (*(s32 **)cs == NULL) {
        *(s32 **)cs = func_80610FE8(4);
        **(s32 **)cs = 0;
    }
    q = *(s32 **)cs;
    switch (b) {
        case 10:
        case 11:
            func_806086CC(x, y, z, 0x305, 0x64, 0x7F, 0, 0, 0.0f, 0);
            actorSpawn(0xB3, 0x5D);
            D_807FBB44->unk4->unk34 = D_807FBB44->unk4->unk34 * 3.2;
            D_807FBB44->unk4->unk38 = D_807FBB44->unk4->unk38 * 3.2;
            D_807FBB44->unk4->unk3C = D_807FBB44->unk4->unk3C * 3.2;
            D_807FBB44->unk60 |= 0x400;
            actorScriptStart(D_807FBB44, 0x335);
            if (b == 11) {
                D_807FBB44->unk7C = D_807F621C;
                D_807FBB44->unk80 = D_807F6220;
                D_807FBB44->unk84 = D_807F6224;
                break;
            }
            D_807FBB44->unk7C = x;
            D_807FBB44->unk80 = y;
            D_807FBB44->unk84 = z;
        case 1:
        case 3:
        case 4:
            if (*q >= 2) {
                *q -= 2;
            } else {
                *q = 0;
                break;
            }
        case 0:
            if (b == 0) {
                *q = 0xFF;
            }
            lightSetRadius(0x1388);
            g = c != 0 ? (f64)*q * 0.27 : (f64)*q;
            bl = c != 0 ? (f64)*q * 0.63 : (f64)*q;
            lightAdd(x, y - 50.0f, z, 0.0f, 0.0f, 0.0f, 240.0f, 0, (u32)g, (u32)bl, *q);
            break;
    }
}

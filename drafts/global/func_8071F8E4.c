// func_8071F8E4 (src/global/11BC10.c): stage 5: matrix-local declaration reordering reaches target sp+0x78/sp+0x38; initial state pointer is still s0 rather than target v0 followed by move s0,v0.
typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
} M2F8E4State;

typedef struct {
    u8 pad0[0x32C];
    u8 unk32C;
    u8 pad32D[0x13];
    f32 unk340;
    f32 unk344;
    f32 unk348;
    u8 pad34C[0x14];
    f32 unk360;
    f32 unk364;
    u8 pad368[0x1C];
    M2F8E4State *unk384;
} M2F8E4ActorView;

extern s32 D_8071FB08;

void func_8071F8E4(M2F8E4ActorView *arg0, s8 *arg1) {
    f64 dummy;
    f32 sp78[4][4];
    f32 sp38[4][4];
    M2F8E4State *temp_v0;

    temp_v0 = arg0->unk384;
    if (temp_v0 != NULL) {
        temp_v0->unk20 = temp_v0->unk20 + temp_v0->unk24;
        if ((f64)temp_v0->unk20 >= 1.0) {
            *(u8 *)arg1 = 0xFF;
            temp_v0->unk20 = 1.0f;
        }
        arg0->unk340 = (temp_v0->unk14 * temp_v0->unk20) + temp_v0->unk8;
        arg0->unk344 = (temp_v0->unk18 * temp_v0->unk20) + temp_v0->unkC;
        arg0->unk348 = (temp_v0->unk1C * temp_v0->unk20) + temp_v0->unk10;
        if (!(D_8076A064 & 3)) {
            func_807149B8(1);
            func_8071498C(func_8071C818);
            func_80714CC0((s32)&D_8071FB08, 1.6f, arg0->unk340, arg0->unk344, arg0->unk348);
        }
        temp_v0->unk4 = temp_v0->unk4 + temp_v0->unk0;
        guScaleF(sp78, arg0->unk360, arg0->unk364, 0.0f);
        guRotateF(sp38, temp_v0->unk4, 0.0f, 0.0f, 1.0f);
        guMtxCatF(sp78, sp38, sp78);
        guMtxF2L(sp78, (Mtx *)((u8 *)arg0 + (D_807444FC << 6) + 0x128));
        arg0->unk32C = 2;
    }
}

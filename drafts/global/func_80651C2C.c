// func_80651C2C (src/global/55B20.c): near miss; regalloc/scheduling stage
typedef struct M55P1_Unk807F6C18 {
    u8 unk0; u8 unk1; u8 unk2; u8 unk3; u8 unk4; u8 pad5[0xF];
    s32 unk14; u8 pad18[0x4]; s32 unk1C; u8 pad20[0x48];
    s32 unk68; s32 unk6C; s32 unk70; s32 unk74; u8 pad78[0x150];
} M55P1_Unk807F6C18;

extern u8 D_807F7078[];
extern s32 D_807F6C28;
extern M55P1_Unk807F6C18 *D_807F6C18;
extern u8 *D_807F6C1C;
extern s32 D_807F6C20;
extern u8 *D_807F6C2C;
extern s32 D_807F70AC;

void func_80651C2C(s32 arg0, M55P1_Unk51C2C_Out *arg1) {
    s64 a0v;
    s64 a1v;
    s64 a2v;
    s64 b0v;
    s64 b1v;
    s64 b2v;
    s64 dot;
    s64 x;
    s64 y;
    s64 z;
    f32 f0;
    f32 f8;
    f32 len;

    a0v = (s64)(D_807F6C14[arg0].unk0 - D_807F6C14[arg0].unk4);
    a1v = (s64)(D_807F6C14[arg0].unk10 - D_807F6C14[arg0].unk14);
    a2v = (s64)(D_807F6C14[arg0].unk20 - D_807F6C14[arg0].unk24);
    b0v = (s64)(D_807F6C14[arg0].unk0 - D_807F6C14[arg0].unk8);
    b1v = (s64)(D_807F6C14[arg0].unk10 - D_807F6C14[arg0].unk18);
    b2v = (s64)(D_807F6C14[arg0].unk20 - D_807F6C14[arg0].unk28);
    arg1->unk0 = a1v * b2v - a2v * b1v;
    arg1->unk8 = a2v * b0v - a0v * b2v;
    arg1->unk10 = a0v * b1v - a1v * b0v;
    f8 = (f32)arg1->unk8;
    f0 = (f32)arg1->unk0;
    arg1->unk18 = (s64)-(D_807F6C14[arg0].unk24 * (f32)arg1->unk10 + (f0 * D_807F6C14[arg0].unk4 + f8 * D_807F6C14[arg0].unk14));
    dot = arg1->unk8 * arg1->unk8 + arg1->unk0 * arg1->unk0 + arg1->unk10 * arg1->unk10;
    len = (f32)dot;
    arg1->unk24 = len;
    arg1->unk20 = sqrtf(len);
    x = arg1->unk0;
    if (x < 0) {
        x = -x;
    }
    y = arg1->unk8;
    if (y < 0) {
        y = -y;
    }
    z = arg1->unk10;
    if (z < 0) {
        z = -z;
    }
    if ((z >= x) && (z >= y)) {
        arg1->unk28 = 0;
    }
    if ((y >= x) && (y >= z)) {
        arg1->unk28 = 1;
    }
    if ((x >= y) && (x >= z)) {
        arg1->unk28 = 2;
    }
}

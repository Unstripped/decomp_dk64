// func_8070CCC4 (src/global/110F00.c): stage 6: exact store order; 0.0f and 1.0f constants receive / in the opposite order
// func_8070CCC4: exact store order; 0.0f/1.0f constant registers are reversed.
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
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    f32 unk38;
    f32 unk3C;
} M110bMtxF;

void func_8070CCC4(M110bMtxF *arg0) {
    arg0->unk10 = 0.0f;
    arg0->unk20 = 0.0f;
    arg0->unk30 = 0.0f;
    arg0->unk4 = 0.0f;
    arg0->unk24 = 0.0f;
    arg0->unk34 = 0.0f;
    arg0->unk8 = 0.0f;
    arg0->unk18 = 0.0f;
    arg0->unk38 = 0.0f;
    arg0->unkC = 0.0f;
    arg0->unk1C = 0.0f;
    arg0->unk2C = 0.0f;
    arg0->unk0 = 1.0f;
    arg0->unk14 = 1.0f;
    arg0->unk28 = 1.0f;
    arg0->unk3C = 1.0f;
}

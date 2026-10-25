// func_80703850 (src/global/103AB0.c): stage 4 m2c-structured direct D_807FC924 casts: exact body after prologue; remaining target-only saved arg0 shifts the f32 spill from 0x18 to 0x1C, plus late-rodata label relocation
typedef struct {
    u8 pad0[0x270];
    s16 unk270;
    s16 unk272;
    s16 unk274;
    s16 unk276;
    s16 unk278;
    s16 unk27A;
    u8 pad27C[4];
    f32 unk280;
} R1F103AB0cViewportView;

extern s16 D_80744490;
extern s16 D_80744494;
extern s16 D_80744498;
extern s16 D_8074449C;
extern s16 D_807444A0;
extern s16 D_807444A4;
extern s16 D_807444AC;
extern s16 D_807444B0;
extern void *D_807FC924;
s32 func_805FCA64();

void func_80703850(s32 arg0) {
    f32 sp1C;
    f32 temp_fv0;

    temp_fv0 = (f32)((f64)(f32)(u32)(arg0 & 0xFF) / 255.0);
    sp1C = temp_fv0;
    if (func_805FCA64() != 0) {
        ((R1F103AB0cViewportView *)D_807FC924)->unk272 = (s16)(s32)((f32)D_8074449C + ((f32)(((s16)D_80744494 >> 1) - D_8074449C - 1) * temp_fv0));
        ((R1F103AB0cViewportView *)D_807FC924)->unk276 = (s16)(s32)((f32)D_807444A4 + ((f32)(((s16)D_80744494 >> 1) - D_807444A4) * temp_fv0));
    } else {
        ((R1F103AB0cViewportView *)D_807FC924)->unk272 = (s16)(s32)((f32)D_807444AC + ((f32)(((s16)D_80744494 >> 1) - D_807444AC - 1) * temp_fv0));
        ((R1F103AB0cViewportView *)D_807FC924)->unk276 = (s16)(s32)((f32)D_807444B0 + ((f32)(((s16)D_80744494 >> 1) - D_807444B0) * temp_fv0));
    }
    ((R1F103AB0cViewportView *)D_807FC924)->unk270 = (s16)(s32)((f32)D_80744498 + ((f32)(((s16)D_80744490 >> 1) - D_80744498 - 1) * temp_fv0));
    ((R1F103AB0cViewportView *)D_807FC924)->unk274 = (s16)(s32)((f32)D_807444A0 + ((f32)(((s16)D_80744490 >> 1) - D_807444A0) * temp_fv0));
    ((R1F103AB0cViewportView *)D_807FC924)->unk27A = (s16)(((R1F103AB0cViewportView *)D_807FC924)->unk276 - ((R1F103AB0cViewportView *)D_807FC924)->unk272);
    ((R1F103AB0cViewportView *)D_807FC924)->unk278 = (s16)(((R1F103AB0cViewportView *)D_807FC924)->unk274 - ((R1F103AB0cViewportView *)D_807FC924)->unk270);
    ((R1F103AB0cViewportView *)D_807FC924)->unk280 = (f32)((f32)((R1F103AB0cViewportView *)D_807FC924)->unk278 / (f32)((R1F103AB0cViewportView *)D_807FC924)->unk27A);
}

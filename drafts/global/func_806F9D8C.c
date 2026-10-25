// func_806F9D8C (src/global/FCCD0.c): Stage 1 behavioural display-list reconstruction compiles; target frame is 0x78 with only s0, draft is 48 bytes short and command writes/temporary layout need iteration.
// Behavioural stage-1 reconstruction; local display-list and draw-argument views.
typedef struct R3FCCD0fDrawArg { u8 pad0[4]; f32 unk4; f32 unk8; s16 unk10; u8 pad12[2]; void *unk14; } R3FCCD0fDrawArg;
typedef struct R3FCCD0fSlot { u8 pad0[4]; u16 unk4; u8 pad6[2]; s32 unk8; u8 padC[0x20]; u8 unk2C; } R3FCCD0fSlot;
typedef struct R3FCCD0fViewport { u8 pad0[4]; s16 unk4; s16 unk6; s16 unk8; s16 unkA; } R3FCCD0fViewport;
extern u8 D_807FD7E4;
extern void *D_1000118;
extern void *D_2000080;
extern s32 _sprintf(char *, const char *, ...);
extern f32 func_80612794(s16);
extern f32 func_80612E40(f32);
extern s32 func_806FBD5C(s16, s32);
extern s32 func_806FC530();
extern R3FCCD0fViewport *cameraFindViewportEntry(s32);

Gfx *func_806F9D8C(s32 arg0, R3FCCD0fDrawArg *arg1, Gfx *arg2) {
    char text[16];
    u8 alpha;
    s32 width;
    s32 text_offset;
    f32 scale;
    R3FCCD0fSlot *slot;
    R3FCCD0fViewport *viewport;
    void *matrix;

    matrix = arg1->unk14;
    scale = func_80612794(arg1->unk10);
    alpha = (u8)(u32)((f64)scale * 255.0);
    width = 0;
    arg2->words.w0 = 0xDA380007;
    arg2->words.w1 = (u32)D_2000080;
    arg2++;
    guTranslate((Mtx *)((u8 *)matrix + (D_807444FC << 6) + 8), arg1->unk4 * (1.0f - scale), arg1->unk8 * (1.0f - scale), 0.0f);
    text_offset = arg0 * 0x30;
    slot = (R3FCCD0fSlot *)((u8 *)D_80754280 + text_offset);
    if (slot->unk2C == 1) {
        _sprintf(text, "o");
    } else if (slot->unk2C == 2) {
        _sprintf(text, "NA");
    } else {
        if (text_offset == 0xF0) {
            width = (s32)func_80612E40((f32)(u32)slot->unk4 * 0.006666667f);
        } else {
            width = slot->unk4;
        }
        _sprintf(text, "%d", (u16)width);
    }
    arg2->words.w0 = 0xDA380000;
    arg2->words.w1 = (u32)((u8 *)matrix + (D_807444FC << 6) + 8);
    arg2++;
    arg2->words.w0 = 0xE7000000;
    arg2->words.w1 = 0;
    arg2++;
    arg2->words.w0 = 0xFA000000;
    arg2->words.w1 = alpha;
    arg2++;
    D_807FD7E4 = alpha;
    arg2->words.w0 = 0xDE000000;
    arg2->words.w1 = (u32)D_1000118;
    arg2++;
    arg2->words.w0 = 0xFCFF97FF;
    arg2->words.w1 = 0xFF2CFE7F;
    arg2++;
    viewport = cameraFindViewportEntry(0);
    arg2->words.w0 = 0xED000000 | (((s32)(viewport->unk4 * 4.0f) & 0xFFF) << 12) | ((s32)(viewport->unk6 * 4.0f) & 0xFFF);
    arg2->words.w1 = (((s32)(viewport->unk8 * 4.0f) & 0xFFF) << 12) | ((s32)(viewport->unkA * 4.0f) & 0xFFF);
    arg2++;
    if ((f64)D_80744490 * 0.5 < (f64)slot->unk8) {
        width = func_806FBD5C(0x81, (s32)text);
    }
    func_806FC530(arg2, 0x81, (s16)((*(s32 *)matrix - width) * 4), (s16)(*((s32 *)matrix + 1) * 4), text, 0);
    arg2->words.w0 = 0xD8380002;
    arg2->words.w1 = 0x40;
    arg2[1].words.w0 = 0xE7000000;
    arg2[1].words.w1 = 0;
    return arg2 + 2;
}

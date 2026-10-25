// func_80710CA0 (src/global/114270.c): stage 4: behaviour and switch reconstructed; target frame 0x150 and saved-register set reached with six-word pad, but local stack slots and register allocation still diverge
typedef struct L10CA0Gfx { u32 w0; u32 w1; } L10CA0Gfx;
typedef struct L10CA0Header { u16 count; u8 pad2[2]; void *entries; } L10CA0Header;
typedef struct L10CA0Entry {
    s16 unk0; u8 pad2[6]; f32 unk8; f32 unkC; f32 unk10; u8 pad14[0xC];
    s16 unk20; s16 unk22; s16 unk24; u8 pad26[2]; f32 unk28; u8 pad2C[0x84];
    u8 unkB0; u8 unkB1; u8 unkB2; u8 padB3[5];
} L10CA0Entry;
typedef struct L10CA0StateView { u8 pad0[0xB4]; f32 unkB4; u8 padB8[0xBC]; void *unk174; } L10CA0StateView;
typedef struct L10CA0PlayerView { u8 pad0[0x90]; f32 unk90; u8 pad94[0x66]; u8 unkFA; u8 padFB[0x119]; f32 unk214; } L10CA0PlayerView;
typedef struct L10CA0TimerView { u8 pad0[0xBC]; s16 unkBC; } L10CA0TimerView;
extern void *D_807F5D10, *D_807FBB4C, *D_807FD580, *D_807FC924, *D_807FDA20, *D_807FDAB0;
extern u16 *D_807550E0;
extern f32 D_807FD9EC;
extern u8 D_807FDA1A, D_807FDA1B, D_807FDA1C, D_807FDA30, D_80755264[], D_807444FC;
extern s16 D_807FDA1E, D_807FDAB4;
extern s32 (*D_807FDA24)(L10CA0Entry *);
extern u8 D_1000020, D_1000118, D_20000C0;
void func_80612CA0(f32 (*)[4], f32);
Gfx *func_807105D4(Gfx *, s32);
s32 mapChunkContainsPoint(s16, s16, s16);

Gfx *func_80710CA0(arg0, arg1)
Gfx *arg0;
s32 arg1;
{
    L10CA0Gfx *gdl = (L10CA0Gfx *)arg0;
    L10CA0Gfx *gdl2;
    L10CA0Header *header = (L10CA0Header *)D_807550E0;
    L10CA0Entry *entry;
    L10CA0StateView *state = (L10CA0StateView *)D_807F5D10;
    L10CA0PlayerView *player = (L10CA0PlayerView *)state->unk174;
    f32 spC8[4][4];
    f32 sp108[4][4];
    s32 pad0[6];
    u8 spBE = 0;
    u8 spBF = 0;
    s32 sp64;
    s32 var_s6 = 0;
    s8 var_s5;
    u16 temp_s0 = header->count;
    f64 scale;
    f64 absScale;

    if ((((u8 *)D_807FBB4C)[0x154] == 3) || (((u8 *)D_807FBB4C)[0x154] == 5)) {
        f32 rem = 180.0f - state->unkB4;
        if (state->unkB4 > 180.0f) {
            rem = 0.0f;
        }
        D_807FD9EC = (f32)((f64)rem * 0.02 * 240.0);
    } else {
        D_807FD9EC = 240.0f;
    }
    if ((((u8 *)D_807FBB4C)[0x154] == 0x42) && ((((L10CA0TimerView *)D_807FD580)->unkBC == 0x62) || (((L10CA0TimerView *)D_807FD580)->unkBC == 0x88))) {
        spBE = 1;
    }
    if ((player->unkFA != 0) && (((L10CA0PlayerView *)D_807FC924)->unk214 < player->unk90 + 3.0f)) {
        spBF = 1;
    }
    gdl2 = gdl++; gdl2->w0 = 0xE7000000; gdl2->w1 = 0;
    gdl2 = gdl++; gdl2->w0 = 0xDE000000; gdl2->w1 = (u32)&D_1000118;
    gdl2 = gdl++; gdl2->w0 = 0xDE000000; gdl2->w1 = (u32)&D_1000020;
    gdl2 = gdl++; gdl2->w0 = 0xDA380007; gdl2->w1 = (u32)&D_20000C0;
    gdl2 = gdl++; gdl2->w0 = 0xD7000002; gdl2->w1 = 0x80008000;
    gdl2 = gdl++; gdl2->w0 = 0xFC119623; gdl2->w1 = 0xFF2FFFFF;
    gdl2 = gdl++; gdl2->w0 = 0xE3001201; gdl2->w1 = 0x2000;
    gdl2 = gdl++; gdl2->w0 = 0xE200001C; gdl2->w1 = 0x504340;
    if (D_80755264[D_807FDA1C * 0x14] == 1) gdl = (L10CA0Gfx *)func_807105D4((Gfx *)gdl, 0);
    for (var_s5 = 0x7F, sp64 = temp_s0; (var_s5 >= 0) && (sp64 != var_s6); var_s5 = (s8)(s16)(var_s5 - 1)) {
        entry = (L10CA0Entry *)header->entries + var_s5;
        D_807FDAB0 = entry; D_807FDAB4 = D_807FDA1E;
        if ((entry->unkB0 != 0) && ((entry->unk0 == -1) || mapChunkContainsPoint((s16)entry->unk8, (s16)entry->unkC, entry->unk0)) && !spBF && !spBE) {
            gdl2 = gdl++; gdl2->w0 = 0xFA000000; gdl2->w1 = (D_807FDA1B << 24) | (D_807FDA1B << 16) | (D_807FDA1B << 8) | entry->unkB1;
            if (D_807FDA1C == 4) {
                switch (entry->unk20) {
                case 8: case 10: case 12: gdl = (L10CA0Gfx *)func_807105D4((Gfx *)gdl, (((entry->unkB2++ >> 2) % 8) + 2) & 0xFF); break;
                case 15: case 18: case 22: gdl = (L10CA0Gfx *)func_807105D4((Gfx *)gdl, 0); break;
                default: gdl = (L10CA0Gfx *)func_807105D4((Gfx *)gdl, 1); break;
                }
            } else if (D_80755264[D_807FDA1C * 0x14] >= 2) {
                gdl = (L10CA0Gfx *)func_807105D4((Gfx *)gdl, entry->unkB2++ % D_80755264[D_807FDA1C * 0x14]);
            }
            scale = (f64)entry->unk10 * 4.0; absScale = scale > 0.0 ? scale : -scale;
            guScaleF(sp108, (f32)scale, (f32)absScale, 1.0f);
            if (D_807FDA1C == 3) { entry->unk22 = (s16)((f32)entry->unk22 + entry->unk28); func_80612CA0(spC8, (f32)entry->unk22); }
            else if (D_807FDA1C == 4) func_80612CA0(spC8, (f32)entry->unk24);
            else func_80612CA0(spC8, (f32)D_807FDA1E);
            guMtxCatF(sp108, spC8, sp108); guTranslateF(spC8, (f32)((f64)entry->unk8 * 4.0), (f32)((f64)entry->unkC * 4.0), -50.0f); guMtxCatF(sp108, spC8, sp108);
            guMtxF2L(sp108, (Mtx *)((u8 *)entry + (D_807444FC << 6) + 0x30));
            gdl2 = gdl++; gdl2->w0 = 0xDA380003; gdl2->w1 = (u32)((u8 *)entry + (D_807444FC << 6) + 0x30);
            gdl2 = gdl++; gdl2->w0 = 0x01004008; gdl2->w1 = (u32)osVirtualToPhysical(D_807FDA20);
            gdl2 = gdl++; gdl2->w0 = 0x06000204; gdl2->w1 = 0x406;
            gdl2 = gdl++; gdl2->w0 = 0xE7000000; gdl2->w1 = 0;
        }
        if (entry->unkB0 != 0) { var_s6 = (var_s6 + 1) & 0xFFFF; if ((D_807FDA24(entry) != 0) || ((f64)entry->unk10 < 0.01)) { entry->unkB0 = 0; D_807FDA1A = (D_807FDA1A + 1) & 0xFF; (&D_807FDA30)[D_807FDA1A] = var_s5; header->count--; } }
    }
    return (Gfx *)gdl;
}

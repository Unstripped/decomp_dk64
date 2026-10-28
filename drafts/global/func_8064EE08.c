// func_8064EE08 (src/global/478F0.c): text-identical, reloc only: all insns match; only .rodata double relocs (D_80758BC8/BD0 vs .rodata+off). Effect-sprite callback (void*, u8*).
typedef struct CsB16EffState {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ f32 unk4;
} CsB16EffState;
typedef struct CsB16Eff {
    /* 0x000 */ u8 pad0[0x344];
    /* 0x344 */ f32 unk344;
    /* 0x348 */ u8 pad348[0x18];
    /* 0x360 */ f32 unk360;
    /* 0x364 */ f32 unk364;
    /* 0x368 */ u8 pad368[0x1C];
    /* 0x384 */ CsB16EffState *unk384;
} CsB16Eff;
s32 camIsPathPaused(void);
s32 camIsCutsceneActive(void);
extern s8 D_807F6950;
extern s8 D_807F6951;

void func_8064EE08(CsB16Eff *e, u8 *flag) {
    CsB16EffState *s;

    if (e->unk384 == NULL) {
        s = func_80610FE8(8);
        e->unk384 = s;
        s->unk0 = 0;
        s->unk2 = 0;
        s->unk4 = e->unk344;
    }
    s = e->unk384;
    switch (s->unk0) {
        case 0:
            e->unk360 = e->unk360 + 0.015;
            if (e->unk360 > 0.5) {
                e->unk360 = 0.5f;
                s->unk0 = 1;
            }
            break;
        case 1:
            if (camIsPathPaused() != 0) {
                s->unk0 = 2;
            }
            if (camIsCutsceneActive() == 0) {
                s->unk0 = 2;
            }
            break;
        case 2:
            if (camIsPathPaused() == 0 || camIsCutsceneActive() == 0) {
                s->unk0 = 3;
                func_80609140(0x2E8, 0x7FFF, 63.0f, 1.0f, 0, 0);
            }
            break;
        case 3:
            e->unk360 = e->unk360 - 0.015;
            if (e->unk360 < 0.0) {
                D_807F6950 = 1;
                e->unk360 = 0.0f;
                *flag = 1;
            }
            break;
    }
    if (s->unk0 != 3) {
        e->unk344 = func_80612794((D_8076A064 * 0x3C) & 0xFFF) * 2.75f + s->unk4;
    }
    e->unk364 = e->unk360;
}

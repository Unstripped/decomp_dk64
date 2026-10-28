// func_807085D0 (src/global/10D2D0.c): func_807085D0 (src/global/10D2D0.c): Stage 6 near-miss (ratio .976): frame/spill slots match via padded volatile f32 locals; only diffs: second prim-color select (target preloads lwc1 f0,164(sp) before compare = if-form with named float var, which perturbs s-reg allocation: arg1 -> s8), lwc1 f8,160(sp) one slot earlier, pips-1 v0/v1 swap. Tricks: no explicit &0xFF in gDPSetPrimColor alpha, (f32)80 in select, y/x/fs1 assigned inside call args, raw s32 + s16 phase.
typedef struct DaF10D2D0_Player {
    u8 pad0[0x2E0];
    u16 unk2E0;
    u8 unk2E2;
    u8 unk2E3;
    u8 unk2E4;
    u8 unk2E5;
} DaF10D2D0_Player;

#define DaF10D2D0_FLAGS(p) (*(u16 *)&(p)->unk2E2)

typedef struct DaF10D2D0_Hud {
    u8 pad0[0x2FB];
    s8 unk2FB;
    u8 unk2FC;
} DaF10D2D0_Hud;

extern Gfx D_1000118;
extern Mtx D_20000C0;
extern s32 D_8076A064;
extern s32 D_807FBB60;
f32 func_80612794(s16);
s32 func_80714464();
Gfx *func_8068C5A8(Gfx *, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, f32);

Gfx *func_807085D0(Gfx *arg0, DaF10D2D0_Hud *arg1, void *arg2, DaF10D2D0_Player *arg3) {
    s16 i;
    s8 pips;
    u32 amp;
    s16 phase;
    s32 raw;
    f32 fs0;
    volatile f32 spE8;
    volatile f32 padB[16];
    volatile f32 spA4;
    volatile f32 spA0;
    volatile f32 padC[2];
    volatile f32 sp94;
    f32 fs1;
    f32 fs2;
    f32 fs0b;
    f32 wv;
    s16 y;
    s16 x;

    pips = arg1->unk2FB;
    fs0 = (f32)((f64)(u32)arg3->unk2E0 / 65535.0);
    amp = ((arg1->unk2FC * 0x46) - 0x46) & 0xFF;
    if ((D_807FBB60 & 3) || (func_80714464() != 0)) {
        return arg0;
    }
    gSPDisplayList(arg0++, &D_1000118);
    gDPSetCombineMode(arg0++, G_CC_MODULATERGBA_PRIM, G_CC_MODULATERGBA_PRIM);
    gSPSetOtherMode(arg0++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x504240);
    gSPMatrix(arg0++, &D_20000C0, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    i = 0;
    if (arg1->unk2FC > 0) {
        spA4 = fs0 * 511.0f;
        spA0 = (f32)amp;
        sp94 = (f32)(s16)(s32)((f64)fs0 * 200.0);
        do {
            raw = (i << 10) + (D_8076A064 * 0xC8);
            phase = raw;
            spE8 = (f32)(((f64)func_80612794(phase) * 0.3) + 3.0);
            fs2 = (f32)(((f64)func_80612794((s16)(raw + 0x800)) * 0.3) + 3.0);
            fs0b = (f32)((f64)func_80612794((s16)((raw >> 1) + 0x200)) * 10.0);
            wv = (f32)(((f64)func_80612794(phase) * 0.5 + 0.5) * 30.0);
            gDPPipeSync(arg0++);
            gDPSetPrimColor(arg0++, 0, 0, 255, 255, 255, (u32)((spA4 > 80.0f) ? (f32)80 : spA4));
            arg0 = func_8068C5A8(arg0, 0x5D, 0, (0, 2), 0x30, 0x2A, y = (s32)(((f32)((i * 0x8C) + 0x280) + fs0b) - spA0), x = (s32)(sp94 + wv), spE8, fs1 = -fs2, 0, 0.0f);
            gDPPipeSync(arg0++);
            gDPSetPrimColor(arg0++, 0, 0, 255, 255, 255, (u32)((spA4 > 255.0f) ? 255.0f : spA4));
            if (pips > 0) {
                arg0 = func_8068C5A8(arg0, ((pips - 1 < 3 ? pips - 1 : 3) + 0x5A) & 0xFFFF, 0, 2, 0x30, 0x2A, y, x, spE8, fs1, 0, 0.0f);
            }
            if (pips - 4 < 0) {
                pips = 0;
            } else {
                pips = pips - 4;
            }
            i += 1;
        } while (i < arg1->unk2FC);
    }
    gDPPipeSync(arg0++);
    return arg0;
}

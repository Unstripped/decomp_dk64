// func_80655DD0 (src/global/55B20.c): stage5: structure/call sequence/constants match; func 0xDD0 vs 0xDD4, frame 0x148 vs 0x140; target fog flag is a stack word at 0x60 (sw stores) read as lbu 0x63, mine u8 at 0x135; flags local 0x58 vs 0x5C
typedef struct {
    /* 0x000 */ u8 unk0;
    /* 0x001 */ u8 unk1;
    /* 0x002 */ u8 unk2;
    /* 0x003 */ u8 pad3[0x11];
    /* 0x014 */ s32 unk14;
    /* 0x018 */ s32 unk18;
    /* 0x01C */ s32 unk1C;
    /* 0x020 */ s32 unk20;
    /* 0x024 */ s32 unk24;
    /* 0x028 */ u8 pad28[0x4];
    /* 0x02C */ s32 unk2C;
    /* 0x030 */ s32 unk30;
    /* 0x034 */ s32 unk34;
    /* 0x038 */ s32 unk38;
    /* 0x03C */ u8 pad3C[0x1C];
    /* 0x058 */ s32 unk58;
    /* 0x05C */ u8 pad5C[0xC];
    /* 0x068 */ union {
        struct {
            /* 0x068 */ s32 unk68;
            /* 0x06C */ s32 unk6C;
            /* 0x070 */ s32 unk70;
            /* 0x074 */ s32 unk74;
        } w;
        struct {
            /* 0x068 */ s16 pad68;
            /* 0x06A */ s16 unk6A;
            /* 0x06C */ s16 pad6C;
            /* 0x06E */ s16 unk6E;
            /* 0x070 */ s16 pad70;
            /* 0x072 */ s16 unk72;
            /* 0x074 */ s16 pad74;
            /* 0x076 */ s16 unk76;
        } h;
    } tile;
} L55DD0Effect;

typedef struct {
    /* 0x000 */ u8 pad0[0x8];
    /* 0x008 */ s32 unk8;
} L55DD0Arg1;

typedef struct {
    /* 0x000 */ u8 pad0[0x8];
    /* 0x008 */ s32 unk8;
    /* 0x00C */ s32 unkC;
} L55DD0WaterEntry;

typedef struct {
    /* 0x000 */ u8 pad0[0x27C];
    /* 0x27C */ f32 unk27C;
    /* 0x280 */ u8 pad280[0x2F0 - 0x280];
} L55DD0PlayerExtra;

#define L55DD0_EFF(i) (((L55DD0Effect *)D_807F6C18)[(i)])
#define L55DD0_WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (u32)(_w1); }

extern u8 D_807F5FEC;
extern void *D_807F7074;
extern void *D_807F5DE8;
extern void *D_807F5DEC;
extern u8 *D_807F6C0C;
extern s16 D_807F6BF0[];
extern s32 D_807FBB64;
extern u8 D_807F6009;
extern s32 D_807F600C;
extern s32 D_807F5FFC;
extern Gfx D_2000180;

u32 osVirtualToPhysical(void *);
Gfx *func_8062CEA8(Gfx *, void *, s32);
Gfx *func_8062EDA8(Gfx *, u8);
void func_8062EE48(u8);
s32 func_80656B98();
Gfx *func_8063A968(Gfx *, s32);
Gfx *func_8065D994(Gfx *, s16);
Gfx *func_80630B70(Gfx *, s32, s32, s32, f32, s32, s16, s32);
Gfx *func_80027034(Gfx *);
Gfx *effectWaterRenderSurfaces(Gfx *, s16, s16);
Gfx *fogRender(Gfx *);
Gfx *renderDepthSortedTargets(Gfx *);
void func_80658E58();

void func_80655DD0(Gfx *arg0, void *arg1, s32 arg2, s32 arg3, f32 arg4, s32 arg5) {
    s32 flags;
    Gfx *gfx;
    Gfx *v;
    s32 i;
    s16 idx;
    u8 flag;

    flag = (D_807F5FEC != 0);
    if (flag != 0) {
        flag = (((L55DD0PlayerExtra *)D_807FC924)[D_807FC929].unk27C == 45.0);
    }
    L55DD0_WRITE_GFX(arg0, 0xE7000000, 0);
    gfx = arg0 + 1;
    flags = arg5 & 0x10;
    if (flags != 0) {
        L55DD0_WRITE_GFX(gfx++, 0xDA380003, osVirtualToPhysical(D_807F7074));
        L55DD0_WRITE_GFX(gfx++, 0xDB060018, osVirtualToPhysical(D_807F5DE8));
        L55DD0_WRITE_GFX(gfx++, 0xDB06001C, osVirtualToPhysical(D_807F5DEC));
        gfx = func_8062CEA8(gfx, arg1, 1);
        if (((L55DD0Arg1 *)arg1)->unk8 != -1) {
            L55DD0_WRITE_GFX(gfx++, 0xE7000000, 0);
            L55DD0_WRITE_GFX(gfx++, 0xDE000000, osVirtualToPhysical((void *)((L55DD0Arg1 *)arg1)->unk8));
        }
        gfx = effectWaterRenderSurfaces(gfx, 0, 0);
        for (i = 0; i < D_807F6C08; i++) {
            if (((L55DD0WaterEntry *)(D_807F6C0C + (D_807F6BF0[i] * 0x10)))->unk8 != -1) {
                L55DD0_WRITE_GFX(gfx++, 0xE7000000, 0);
                L55DD0_WRITE_GFX(gfx++, 0xDE000000, osVirtualToPhysical((void *)((L55DD0WaterEntry *)(D_807F6C0C + (D_807F6BF0[i] * 0x10)))->unk8));
            }
            if (((L55DD0WaterEntry *)(D_807F6C0C + (D_807F6BF0[i] * 0x10)))->unkC != -1) {
                L55DD0_WRITE_GFX(gfx++, 0xE7000000, 0);
                L55DD0_WRITE_GFX(gfx++, 0xDE000000, osVirtualToPhysical((void *)((L55DD0WaterEntry *)(D_807F6C0C + (D_807F6BF0[i] * 0x10)))->unkC));
            }
        }
        L55DD0_WRITE_GFX(gfx++, 0xDA380003, &D_2000180);
    }
    for (i = D_807F6C80 - 1; i >= 0; i--) {
        idx = D_807F6C58[i];
        if (L55DD0_EFF(idx).unk0 == 1) {
            if (L55DD0_EFF(idx).unk2 != 0) {
                func_8062EE48(idx & 0xFF);
                L55DD0_EFF(idx).unk2 = 0;
            }
            L55DD0_WRITE_GFX(gfx++, 0xE7000000, 0);
            L55DD0_WRITE_GFX(gfx++, ((s32)((f32)L55DD0_EFF(idx).tile.w.unk6C * 4.0f) & 0xFFF) | 0xED000000 | (((s32)((f32)L55DD0_EFF(idx).tile.w.unk68 * 4.0f) & 0xFFF) << 0xC),
                        ((s32)((f32)L55DD0_EFF(idx).tile.w.unk74 * 4.0f) & 0xFFF) | (((s32)((f32)L55DD0_EFF(idx).tile.w.unk70 * 4.0f) & 0xFFF) << 0xC));
            func_80658E58(L55DD0_EFF(idx).tile.h.unk6A, L55DD0_EFF(idx).tile.h.unk6E, L55DD0_EFF(idx).tile.h.unk72, L55DD0_EFF(idx).tile.h.unk76);
            gfx = fogRender(gfx);
            if (flags != 0) {
                gfx = func_8062EDA8(gfx, idx & 0xFF);
                if (L55DD0_EFF(idx).unk2C != -1) {
                    L55DD0_WRITE_GFX(gfx++, 0xDA380003, osVirtualToPhysical(D_807F7074));
                    L55DD0_WRITE_GFX(gfx++, 0xDB060018, osVirtualToPhysical((void *)L55DD0_EFF(idx).unk58));
                    L55DD0_WRITE_GFX(gfx++, 0xDB06001C, osVirtualToPhysical(D_807F5DEC));
                    v = (Gfx *)func_80656B98(gfx, idx, 0);
                    L55DD0_WRITE_GFX(v++, 0xE7000000, 0);
                    L55DD0_WRITE_GFX(v++, 0xDA380003, &D_2000180);
                    gfx = v;
                }
                if (L55DD0_EFF(idx).unk34 != -1) {
                    L55DD0_WRITE_GFX(gfx++, 0xDA380003, osVirtualToPhysical(D_807F7074));
                    L55DD0_WRITE_GFX(gfx++, 0xDB060018, osVirtualToPhysical((void *)L55DD0_EFF(idx).unk58));
                    L55DD0_WRITE_GFX(gfx++, 0xDB06001C, osVirtualToPhysical(D_807F5DEC));
                    v = (Gfx *)func_80656B98(gfx, idx, 2);
                    L55DD0_WRITE_GFX(v++, 0xE7000000, 0);
                    L55DD0_WRITE_GFX(v++, 0xDA380003, &D_2000180);
                    gfx = v;
                }
            }
            L55DD0_WRITE_GFX(gfx++, 0xE7000000, 0);
            if (!(D_807FBB64 & 0x01000000)) {
                gfx = func_8065D994(gfx, idx);
            }
            gfx = func_8063A968(gfx, L55DD0_EFF(idx).unk24);
            D_807F6009 = 0xFF;
            gfx = func_80630B70(gfx, (flag != 0) ? L55DD0_EFF(idx).unk18 : L55DD0_EFF(idx).unk14, arg2, arg3, arg4, arg5, idx, flag);
            if (flags != 0) {
                L55DD0_WRITE_GFX(gfx++, 0xD9000000, 0);
                L55DD0_WRITE_GFX(gfx++, 0xD9FFFFFF, 0x200004);
                gfx = fogRender(gfx);
                gfx = func_8062EDA8(gfx, idx & 0xFF);
                if (L55DD0_EFF(idx).unk30 != -1) {
                    L55DD0_WRITE_GFX(gfx++, 0xDA380003, osVirtualToPhysical(D_807F7074));
                    L55DD0_WRITE_GFX(gfx++, 0xDB060018, osVirtualToPhysical((void *)L55DD0_EFF(idx).unk58));
                    L55DD0_WRITE_GFX(gfx++, 0xDB06001C, osVirtualToPhysical(D_807F5DEC));
                    v = (Gfx *)func_80656B98(gfx, idx, 1);
                    L55DD0_WRITE_GFX(v++, 0xDA380003, &D_2000180);
                    L55DD0_WRITE_GFX(v++, 0xE7000000, 0);
                    gfx = v;
                }
                if (L55DD0_EFF(idx).unk38 != -1) {
                    L55DD0_WRITE_GFX(gfx++, 0xDA380003, osVirtualToPhysical(D_807F7074));
                    L55DD0_WRITE_GFX(gfx++, 0xDB060018, osVirtualToPhysical((void *)L55DD0_EFF(idx).unk58));
                    L55DD0_WRITE_GFX(gfx++, 0xDB06001C, osVirtualToPhysical(D_807F5DEC));
                    v = (Gfx *)func_80656B98(gfx, idx, 3);
                    L55DD0_WRITE_GFX(v++, 0xE7000000, 0);
                    L55DD0_WRITE_GFX(v++, 0xDA380003, &D_2000180);
                    gfx = v;
                }
            }
        }
    }
    if (flags != 0) {
        L55DD0_WRITE_GFX(gfx++, 0xDA380003, osVirtualToPhysical(D_807F7074));
        L55DD0_WRITE_GFX(gfx++, 0xDB060018, osVirtualToPhysical(D_807F5DE8));
        L55DD0_WRITE_GFX(gfx++, 0xDB06001C, osVirtualToPhysical(D_807F5DEC));
        gfx = func_8062CEA8(gfx, arg1, 2);
        if (D_807FBB64 & 0x1000) {
            L55DD0_WRITE_GFX(gfx++, 0xE7000000, 0);
            gfx = func_80027034(gfx);
            L55DD0_WRITE_GFX(gfx++, 0xDA380003, osVirtualToPhysical(D_807F7074));
        }
        gfx = effectWaterRenderSurfaces(gfx, idx, 1);
        L55DD0_WRITE_GFX(gfx++, 0xDA380003, &D_2000180);
        L55DD0_WRITE_GFX(gfx++, 0xE7000000, 0);
        gfx = renderDepthSortedTargets(gfx);
    }
    for (i = D_807F6C80 - 1; i >= 0; i--) {
        idx = D_807F6C58[i];
        if (L55DD0_EFF(idx).unk0 == 1) {
            L55DD0_WRITE_GFX(gfx++, 0xE7000000, 0);
            L55DD0_WRITE_GFX(gfx++, ((s32)((f32)L55DD0_EFF(idx).tile.w.unk6C * 4.0f) & 0xFFF) | 0xED000000 | (((s32)((f32)L55DD0_EFF(idx).tile.w.unk68 * 4.0f) & 0xFFF) << 0xC),
                        ((s32)((f32)L55DD0_EFF(idx).tile.w.unk74 * 4.0f) & 0xFFF) | (((s32)((f32)L55DD0_EFF(idx).tile.w.unk70 * 4.0f) & 0xFFF) << 0xC));
            func_80658E58(L55DD0_EFF(idx).tile.h.unk6A, L55DD0_EFF(idx).tile.h.unk6E, L55DD0_EFF(idx).tile.h.unk72, L55DD0_EFF(idx).tile.h.unk76);
            D_807F6009 = 0xFF;
            gfx = func_80630B70(gfx, (flag != 0) ? L55DD0_EFF(idx).unk20 : L55DD0_EFF(idx).unk1C, arg2, arg3, arg4, arg5, idx, flag);
            if (D_807FBB64 & 0x01000000) {
                gfx = func_8065D994(gfx, idx);
            }
        }
    }
    if (flags != 0) {
        L55DD0_WRITE_GFX(gfx++, 0xDA380003, osVirtualToPhysical(D_807F7074));
        L55DD0_WRITE_GFX(gfx++, 0xDB060018, osVirtualToPhysical(D_807F5DE8));
        L55DD0_WRITE_GFX(gfx++, 0xDB06001C, osVirtualToPhysical(D_807F5DEC));
        v = func_8062CEA8(gfx, arg1, 3);
        L55DD0_WRITE_GFX(v++, 0xDA380003, &D_2000180);
        L55DD0_WRITE_GFX(v++, 0xE7000000, 0);
        gfx = v;
    }
    L55DD0_WRITE_GFX(gfx++, 0xE7000000, 0);
    L55DD0_WRITE_GFX(gfx++, ((s32)((f32)D_807FC924[D_807FC929].unk274 * 4.0f) & 0xFFF) | 0xED000000 | (((s32)((f32)D_807FC924[D_807FC929].unk270 * 4.0f) & 0xFFF) << 0xC),
                ((s32)((f32)D_807FC924[D_807FC929].unk276 * 4.0f) & 0xFFF) | (((s32)((f32)D_807FC924[D_807FC929].unk272 * 4.0f) & 0xFFF) << 0xC));
    func_80658E58(D_807FC924[D_807FC929].unk270, D_807FC924[D_807FC929].unk272, D_807FC924[D_807FC929].unk274, D_807FC924[D_807FC929].unk276);
    D_807F600C = 0;
    gfx = func_80630B70(gfx, D_807F5FFC, arg2, arg3, arg4, arg5, -1, 0);
    func_8065D994(gfx, -1);
}

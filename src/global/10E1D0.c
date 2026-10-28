#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB44;
extern Actor *D_807FBB48;
extern Actor *D_807FBB4C;
extern void *D_807FC924;
extern u8 D_807FC928;
extern u8 D_807FC929;
extern u8 D_807FC950[][0x5E];
extern s32 D_8076A0A8;
extern u8 D_8076A0AB;
extern u8 D_8076A0B1;
extern s16 D_80744490;
extern s16 D_80744494;
extern u8 D_807444F8;
extern u8 D_807444FC;

extern u8 D_807444EC;
extern u8 D_807444F4;
extern s32 D_8076D1F8;
extern s32 D_807FBB64;
extern s8 D_807FD9BC;
extern u8 D_807FD9BD;
extern f32 D_807FD9C4;
extern s32 D_807FD9C8;
void timerQueueCancel(void *);
void n_alSndpPlay(s32, s16, s32, s32, f32, s32, s32 *);

void func_807094D0(arg0)
u8 arg0;
{
    D_807444F4 = D_807444EC;
    switch (arg0) {
    case 2:
        D_807FD9C4 = 1.0f;
        D_807FD9BC = 0;
        D_807444F8 = 1;
        D_807444EC = 6;
        break;
    case 3:
        D_807FD9C4 = 0.5f;
        D_807FD9BC = 0;
        D_807444F8 = 2;
        D_807444EC = 6;
        D_807FD9BD = 2;
        if ((D_807444F4 == 1) && (D_807FBB64 & 1)) {
            timerQueueCancel(0);
        }
        break;
    }
    n_alSndpPlay(D_8076D1F8, 0x1BC, 0x7FFF, 0x3F, 1.0f, 0, &D_807FD9C8);
}

typedef struct EaGridCell {
    s32 offset;
    s32 width;
    s32 height;
} EaGridCell;

extern EaGridCell *D_807FD9B4;

void func_807095E4(s32 arg0, s32 arg1) {
    s32 cols;
    s32 rows;
    s32 remW;
    s32 remH;
    s32 y;
    s32 idx;
    s32 row;
    s32 col;
    s32 x;

    cols = D_80744490 / arg0;
    rows = D_80744494 / arg1;
    remW = D_80744490 - arg0 * cols;
    remH = D_80744494 - arg1 * rows;
    if (remW > 0) {
        cols++;
    }
    if (remH > 0) {
        rows++;
    }
    idx = 0;
    if (remH != 0) {
        y = D_80744494 - remH;
    } else {
        y = D_80744494 - arg1;
    }
    for (row = 0; row < rows; row++) {
        x = 0;
        for (col = 0; col < cols; col++) {
            D_807FD9B4[idx].offset = D_80744490 * y + x;
            if (remW != 0 && col == cols - 1) {
                D_807FD9B4[idx].width = remW;
            } else {
                D_807FD9B4[idx].width = arg0;
            }
            if (remH != 0 && row == 0) {
                D_807FD9B4[idx].height = remH;
            } else {
                D_807FD9B4[idx].height = arg1;
            }
            x += arg0;
            idx++;
        }
        y -= arg1;
    }
}

#ifdef NON_MATCHING
typedef struct EaEntry {
    u32 unk0;
    u8 pad[0x18];
} EaEntry;

typedef struct EaBlockB {
    u32 *unk0;
    s32 *unk4;
    u8 *unk8;
} EaBlockB;

typedef struct EaBlockA {
    s32 unk0;
    s32 unk4;
    u8 *unk8;
    u8 *unkC;
    void *unk10;
    void *unk14;
    u32 *unk18;
    s32 *unk1C;
    s32 *unk20;
} EaBlockA;

void *func_80610FE8(s32);

s32 func_80709890(EaBlockA *arg0, EaBlockA **arg1, EaBlockB **arg2, s32 **arg3) {
    s32 count;
    s32 k;
    s32 sum;
    EaBlockB *b;
    u32 *p;
    EaEntry *q;

    if (arg0 == NULL) {
        return 0;
    }
    if (arg1 == NULL) {
        return 0;
    }
    D_807FD9B4 = func_80610FE8(0x708);
    arg0->unk10 = func_80610FE8(arg0->unk0 * 0x10);
    if (D_807FD9B4 && D_807FD9B4) {}
    arg0->unk14 = func_80610FE8(arg0->unk0 * 0x10);
    arg0->unk8 = (u8 *)arg0 + 0x2C;
    arg0->unkC = arg0->unk8 + arg0->unk0 * 0xC;
    arg0->unk18 = (u32 *)(arg0->unkC + arg0->unk4 * 0x1C);
    count = 1;
    p = arg0->unk18;
    while (*p++ != 0) {
        count++;
    }
    arg0->unk20 = (s32 *)arg0->unk18 + count;
    arg0->unk1C = arg0->unk20 + count;
    *arg1 = arg0;
    if (arg2 != NULL) {
        b = (EaBlockB *)(arg0->unk1C + count);
        b->unk8 = (u8 *)(b + 1);
        q = (EaEntry *)b->unk8;
        if (D_807FD9B4 && D_807FD9B4) {}
        count = 1;
        while ((q++)->unk0 != 0) {
            count++;
        }
        b->unk0 = (u32 *)(b->unk8 + count * 0x1C);
        k = 1;
        p = b->unk0;
        while (*p++ != -1) {
            if (D_807FD9B4 && D_807FD9B4) {}
            k++;
        }
        b->unk4 = (s32 *)((u8 *)b->unk0 + k * 4);
        if (q && q) {}
        count = 0;
        sum = 0;
        if (b->unk0[0] != -1) {
            do {
                b->unk4[count] = (s32)b->unk4 + k * 4 + sum * 2;
                sum += b->unk0[count];
                count++;
            } while (b->unk0[count] != -1);
        }
        *arg2 = b;
    }
    if (arg3 != NULL) {
        if (arg2 == NULL) {
            *arg3 = arg0->unk1C + count;
        } else {
            *arg3 = b->unk4 + count;
        }
    }
    return 1;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/10E1D0/func_80709890.s")
#endif

#ifdef NON_MATCHING
typedef struct EaSortView { s32 unk0, unk4, unk8; u8 *unkC; s32 unk10, unk14; s32 *unk18, *unk1C, *unk20; } EaSortView;
typedef struct EaSortEntry { s32 unk0, unk4, unk8; u8 padC[0x10]; } EaSortEntry;
s32 func_80709ACC(EaSortView *arg0) {
    EaSortEntry *e; s32 min, max, i, out = 0, off = 0;
    while (*(s32 *)((u8 *)arg0->unk18 + out)) {
        e = (EaSortEntry *)(arg0->unkC + off);
        min = max = e->unk0;
        for (i = 0; i < *(s32 *)((u8 *)arg0->unk18 + out); i++, off += 0x1C, e++) {
            if (e->unk0 > max) max = e->unk0; else if (e->unk0 < min) min = e->unk0;
            if (e->unk4 > max) max = e->unk4; else if (e->unk4 < min) min = e->unk4;
            if (e->unk8 > max) max = e->unk8; else if (e->unk8 < min) min = e->unk8;
        }
        *(s32 *)((u8 *)arg0->unk20 + out) = min;
        *(s32 *)((u8 *)arg0->unk1C + out) = max;
        out += 4;
    }
    return 1;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/10E1D0/func_80709ACC.s")
#endif

#pragma GLOBAL_ASM("asm/global/nonmatchings/10E1D0/func_80709BC4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/10E1D0/func_8070A220.s")

void func_8070A848(s32 *arg0, s32 *arg1) {
    s32 i;
    s32 *src = arg1;
    s32 *dst = arg0;

    for (i = 0; i < (D_80744490 * D_80744494) / 16; i++) {
        dst[0] = src[0] | 0x10001;
        dst[1] = src[1] | 0x10001;
        dst[2] = src[2] | 0x10001;
        dst[3] = src[3] | 0x10001;
        dst[4] = src[4] | 0x10001;
        dst[5] = src[5] | 0x10001;
        dst[6] = src[6] | 0x10001;
        dst[7] = src[7] | 0x10001;
        dst += 8;
        src += 8;
    }
}

typedef struct EbBufferSet {
    s32 unk0;
    s32 unk4;
    void *unk8;
    void *unkC;
    void *unk10;
    void *unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
} EbBufferSet;

extern u8 *D_8076A048;
extern Gfx *D_8076A050[];
extern s32 D_8076A064;
extern s32 D_8076A088;
extern s32 D_8076A08C;
extern u8 D_8076A0A4;
extern u8 D_8076A0B2;
extern Mtx D_80767CE8;
extern f32 D_807FD888;
extern EbBufferSet *D_807FD9A8;
extern s32 D_807FD9B0;
extern s32 D_807FD9B8;

void func_805FE71C(Gfx *, u8, s32 *, u8);
void func_805FE7B4(Gfx *, s32, s32 *, u8);
void func_805FF378(s32, s32);
void func_80610044(Gfx *, s32, s32, u8, s32, s32);
void func_8070AC74();
void func_8070AF24(void);
s32 func_8070B7EC(Gfx **, s32, s32);
void heapFreeDeferred(void *);
void assetFreeBuffer(s32, s32, s32);
void camRestartPath(void);

void func_8070A934(s32 arg0, s32 arg1) {
    Gfx *sp34;
    Gfx *sp30;

    func_80610044(D_8076A050[D_807444FC], D_8076A088, 3, 1, 0x4D2, 1);
    D_807444FC ^= 1;
    D_8076A064 += 1;
    D_8076A048 = (D_807444FC * 0x11B0) + (u8 *)&D_80767CE8;
    sp30 = (Gfx *)(D_8076A048 + 0xDB0);
    switch (*(u8 *)&D_807FD9BC) {
    case 1:
        break;
    case 0:
        *(u8 *)&D_807FD9BC = 1;
        func_8070AF24();
        break;
    }
    if ((D_8076A0B1 & 1) && (D_807FD888 == 31.0f)) {
        sp34 = D_8076A050[D_807444FC];
        if (D_8076A0B2 == 1) {
            D_807444EC = D_807444F4;
        }
    } else {
        func_8070AC74(D_8076A048, &sp34, &D_8076A0B1);
        if (func_8070B7EC(&sp34, D_807FD9B8, D_807FD9B0) != 0) {
            switch (D_807444F8) {
            case 1:
                osViBlack(1);
                func_805FF378(arg0, arg1);
                D_807FD888 = 31.0f;
                D_807444F8 = 2;
                break;
            case 2:
                heapFreeDeferred((void *)D_807FD9B0);
                heapFreeDeferred(D_807FD9A8->unk8);
                heapFreeDeferred((void *)D_807FD9B4);
                heapFreeDeferred(D_807FD9A8->unk10);
                heapFreeDeferred(D_807FD9A8->unk14);
                assetFreeBuffer(D_807FD9B8, 0x24B, 0x4A);
                if (((D_807444EC = D_807444F4) == 1) && (D_807FBB64 & 1)) {
                    camRestartPath();
                }
                D_807444F8 = 3;
                D_807FD888 = 0.0f;
                break;
            }
        }
    }
    if (D_807FD9BD != 0) {
        D_807FD9BD--;
        if (D_807FD9BD == 0) {
            D_8076A0B1 |= 2;
        }
    }
    if ((D_8076A0A4 != 0) && (D_807444EC != 6)) {
        func_805FE71C(sp34, D_807444FC, &D_8076A088, 0);
        func_805FE7B4(sp30, (s32)D_8076A048, &D_8076A08C, 1);
        return;
    }
    func_805FE71C(sp34, D_807444FC, &D_8076A088, 1);
}

extern void *D_8076A080;
extern u16 D_8076A09C;
extern Gfx D_1000090[];

Gfx *func_805FCFD8();
Gfx *func_805FE398();
Gfx *func_805FE4D4();

void func_8070AC74(void *arg0, Gfx **arg1) {
    Gfx *dl = D_8076A050[D_807444FC];

    gSPSegment(dl++, 0, 0);
    gSPSegment(dl++, 2, osVirtualToPhysical(arg0));
    gSPSegment(dl++, 1, osVirtualToPhysical(D_8076A080));
    gSPDisplayList(dl++, D_1000090);
    dl = func_805FE398(func_805FCFD8(dl));
    gDPPipeSync(dl++);
    gDPSetCycleType(dl++, G_CYC_1CYCLE);
    guTranslate((Mtx *)arg0 + 6, 0.0f, 0.0f, 0.0f);
    guLookAt((Mtx *)arg0 + 8, 0.0f, 0.0f, 200.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    guPerspective((Mtx *)arg0, &D_8076A09C, 61.9f, 1.3333334f, 10.0f, 1000.0f, 1.0f);
    gDPPipeSync(dl++);
    dl = func_805FE4D4(dl);
    gDPSetColorDither(dl++, G_CD_MAGICSQ);
    gDPSetAlphaDither(dl++, G_AD_PATTERN);
    gDPSetScissor(dl++, G_SC_NON_INTERLACE, 10, 10, 309, 229);
    gDPSetFillColor(dl++, 0xFFC1FFC1);
    gSPSetOtherMode(dl++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0);
    gSPClearGeometryMode(dl++, G_ZBUFFER);
    gDPFillRectangle(dl++, 0, 0, D_80744490 - 1, D_80744494 - 1);
    gSPPerspNormalize(dl++, D_8076A09C);
    gSPClipRatio(dl++, FRUSTRATIO_2);
    *arg1 = dl;
}

extern s32 D_80755068;
extern s32 D_8075506C;
extern void *D_807FD9A4;
extern s32 D_807FD9AC;
extern s32 *D_80744470[];

void *func_80610FE8(s32);
s32 func_8066B0F8();
s32 func_80709890();
s32 func_80709ACC();

void func_8070AF24(void) {
    switch (D_807444F8) {
    case 1:
        D_80755068 = 0;
        D_8075506C = 0;
        break;
    case 2:
        D_80755068 = 0x78;
        break;
    }
    D_807FD9B8 = func_8066B0F8(0x13, 1, 1, 1);
    D_807FD9B0 = (s32)func_80610FE8(D_80744490 * D_80744494 * 2);
    func_8070A848((s32 *)D_807FD9B0, D_80744470[D_807444FC]);
    func_80709890((void *)D_807FD9B8, (void *)&D_807FD9A8, (void *)&D_807FD9AC, 0);
    func_80709ACC((void *)D_807FD9A8);
    D_807FD9A4 = D_807FD9A8->unk8;
    D_807FD9A8->unk8 = func_80610FE8(D_807FD9A8->unk0 * 0xC);
    func_807095E4(D_807FD9A8->unk24, D_807FD9A8->unk28);
}

typedef struct EbMask {
    u16 data[24];
} EbMask;

extern EbMask D_80755074;

void func_8070B05C(u16 *arg0) {
    EbMask temp = D_80755074;
    s32 i;
    u16 *pixels = arg0 + 0x9D;
    s32 t = D_80755068 - 5;
    s32 count = (t * 0xF0) / 0x50;

    for (i = 0; i < count; i++) {
        pixels[0] = pixels[0] & temp.data[(i & 3) * 6];
        pixels[1] = pixels[1] & temp.data[(i & 3) * 6 + 1];
        pixels[2] = pixels[2] & temp.data[(i & 3) * 6 + 2];
        pixels[3] = pixels[3] & temp.data[(i & 3) * 6 + 3];
        pixels[4] = pixels[4] & temp.data[(i & 3) * 6 + 4];
        pixels[5] = pixels[5] & temp.data[(i & 3) * 6 + 5];
        pixels += 0x140;
    }
    for (i = count; i < 0xF0; i++) {
        pixels[0] |= 1;
        pixels[1] |= 1;
        pixels[2] |= 1;
        pixels[3] |= 1;
        pixels[4] |= 1;
        pixels[5] |= 1;
        pixels += 0x140;
    }
}

extern u8 D_80755070;

void func_8070B308(u8 arg0) {
    D_80755070 = arg0;
}

u8 func_8070B318(void) {
    return D_80755070;
}

extern s8 D_8074583C;
extern s32 D_807550A4;

void n_alSndpSetGroupVol(u8, u16);
void seqSetChannelVolumeScale(s32, f32);

void func_8070B324(f32 arg0, s32 arg1, s32 *arg2) {
    s32 sp34;
    u16 sp28;
    u16 temp_s0;
    s32 i;

    sp28 = 25000.0f * arg0;
    temp_s0 = (f64)(sp28 * D_8074583C) / 40.0;
    sp34 = osGetThreadPri(0);
    osSetThreadPri(0, 0x1A);
    n_alSndpSetGroupVol(0, temp_s0);
    if (arg1 != 0) {
        D_807550A4 = 1;
        n_alSndpSetGroupVol(2, temp_s0);
        if ((D_80755070 == 0) && ((D_8076A0B1 & 1) || !(D_8076A0B1 & 0x40))) {
            seqSetChannelVolumeScale(0, arg0);
        }
    } else {
        n_alSndpSetGroupVol(3, (f64)(sp28 * D_8074583C) / 40);
        if (D_807550A4 != 0) {
            D_807550A4 = 0;
            n_alSndpSetGroupVol(2, (f64)(D_8074583C * 25000) / 40.0f);
            n_alSndpSetGroupVol(1, (f64)(D_8074583C * 25000) / 4e1);
        }
    }
    for (i = 0; arg2 != 0 && arg2[i] != 0; i++) {
        seqSetChannelVolumeScale(arg2[i], arg0);
    }
    if (D_807550A4 && D_807550A4) {}
    osSetThreadPri(0, sp34);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/10E1D0/func_8070B7EC.s")

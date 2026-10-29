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
    if (k && k) {}
    arg0->unk10 = func_80610FE8(arg0->unk0 * 0x10);
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
            k++;
        }
        b->unk4 = (s32 *)((u8 *)b->unk0 + k * 4);
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

typedef struct EaSortView { s32 unk0, unk4, unk8; u8 *unkC; s32 unk10, unk14; s32 *unk18, *unk1C, *unk20; } EaSortView;
typedef struct EaSortEntry { s32 unk0, unk4, unk8; u8 padC[0x10]; } EaSortEntry;
s32 func_80709ACC(EaSortView *arg0) {
    EaSortEntry *e;
    s32 new_var;
    s32 min;
    s32 off;
    s32 max;
    s32 i;
    s32 k;
    k = 0;
    min = 0;
    off = 0;
    while (arg0->unk18[k]) {
        e = (EaSortEntry *)(arg0->unkC + off);
        new_var = e->unk8;
        min = max = e->unk0;
        for (i = 0; i < arg0->unk18[k]; i++, off += 0x1C, e++) {
            if (e->unk0 > max) max = e->unk0; else if (e->unk0 < min) min = e->unk0;
            if (e->unk4 > max) max = e->unk4; else if (e->unk4 < min) min = e->unk4;
            new_var = e->unk8;
            if (new_var > max) max = new_var; else if (new_var < min) min = new_var;
        }
        arg0->unk20[k] = min;
        arg0->unk1C[k] = max;
        k++;
    }
    return 1;
}

typedef struct L11Cell {
    s32 v0, v1, v2, st0, st1, st2, texture;
} L11Cell;
typedef struct L11Tex {
    s32 offset, width, height;
} L11Tex;
typedef struct L11Info {
    s32 vertex_count, unk4;
    f32 *vertices;
    L11Cell *cells;
    u8 *screen_vertices[2];
    s32 *column_counts, *column_ends, *column_starts;
} L11Info;
extern L11Tex D_80754F80[];
extern u16 D_80754FC8[];
s16 func_8070C200(f32);

void func_80709BC4(Gfx **arg0, L11Info *arg1, u8 *arg2) {
    Gfx *glist = *arg0;
    s32 j, k, row, texture, prev, base, count;

    for (j = 0; j < arg1->vertex_count; j++) {
        ((s16 *)(arg1->screen_vertices[D_807444FC] + j * 0x10))[0] = func_8070C200(arg1->vertices[j * 3]);
        ((s16 *)(arg1->screen_vertices[D_807444FC] + j * 0x10))[1] = func_8070C200(arg1->vertices[j * 3 + 1]);
        ((s16 *)(arg1->screen_vertices[D_807444FC] + j * 0x10))[2] = func_8070C200(arg1->vertices[j * 3 + 2]);
    }
    k = 0;
    for (row = 0; arg1->column_counts[row] != 0; row++) {
        prev = -0x63;
        base = arg1->column_starts[row];
        count = arg1->column_ends[row] - base + 1;
        gSPVertex(glist++, osVirtualToPhysical(arg1->screen_vertices[D_807444FC] + base * 0x10), count, 0);
        for (j = 0; j < arg1->column_counts[row]; j++) {
            texture = arg1->cells[k].texture;
            if (texture != prev) {
                prev = texture;
                if (texture < 0) {
                    texture = -1 - texture;
                    gDPLoadTextureBlock(glist++, D_80754FC8 + D_80754F80[texture].offset, G_IM_FMT_RGBA, G_IM_SIZ_16b, D_80754F80[texture].width, D_80754F80[texture].height - 1, 0, G_TX_WRAP, G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                } else {
                    gDPLoadTextureTile(glist++, arg2 + D_807FD9B4[texture].offset * 2, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, 0, 0, 0, D_807FD9B4[texture].width, D_807FD9B4[texture].height - 1, 0, G_TX_WRAP, G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                }
            }
            gSPModifyVertex(glist++, arg1->cells[k].v0 - base, G_MWO_POINT_ST, arg1->cells[k].st0);
            gSPModifyVertex(glist++, arg1->cells[k].v1 - base, G_MWO_POINT_ST, arg1->cells[k].st1);
            gSPModifyVertex(glist++, arg1->cells[k].v2 - base, G_MWO_POINT_ST, arg1->cells[k].st2);
            gSP1Triangle(glist++, arg1->cells[k].v0 - base, arg1->cells[k].v1 - base, arg1->cells[k].v2 - base, 0);
            k++;
        }
    }
    *arg0 = glist;
}

typedef f32 LcMatrix[4][4];

typedef struct LcVec3 {
    f32 x;
    f32 y;
    f32 z;
} LcVec3;

typedef struct LcModel {
    s32 unk0;
    s32 unk4;
    LcVec3 *vertices;
} LcModel;

typedef struct LcAnimEntry {
    s32 kind;
    s32 group;
    s32 start;
    s32 end;
    f32 scale;
    u32 source;
    u32 destination;
} LcAnimEntry;

typedef struct LcAnim {
    s32 *counts;
    u16 **indices;
    LcAnimEntry *entries;
} LcAnim;

void mtxMulAffineF(f32 *, f32 *, f32 *);
void mtxRotateZDegF(f32 *, f32);
void func_8070D07C(f32 *, f32 *, f32, f32, f32, f32, f32, f32);

#define LC_MODEL ((LcModel *)arg0)
#define LC_ANIM ((LcAnim *)arg1)

void func_8070A220(void *arg0, s32 arg1, s32 frame) {
    u32 sidx;
    u32 didx;
    LcMatrix m1B8;
    LcMatrix m178;
    LcMatrix m138;
    LcMatrix mF8;
    LcMatrix mB8;
    s16 idx;
    s32 i;
    s32 count;
    u16 *indices;
    s32 end;
    LcVec3 *src;
    LcVec3 *dst;
    f32 angle;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 x;
    f32 y;
    f32 z;
    u32 j;
    s32 kindv;
    if (i && i) {}

    idx = 0;
    while (LC_ANIM->entries[idx].kind != 0) {
        end = frame;
        if (frame < LC_ANIM->entries[idx].start) {
            goto next;
        }
        kindv = LC_ANIM->entries[idx].kind;
        if (i && i) {}
        if (LC_ANIM->entries[idx].end < frame) {
            end = LC_ANIM->entries[idx].end;
        }
        switch (kindv) {
        case 1:
                sidx = LC_ANIM->entries[idx].source;
                didx = LC_ANIM->entries[idx].destination;
                src = &LC_MODEL->vertices[sidx];
                dst = &LC_MODEL->vertices[didx];
                dx = dst->x - src->x;
                if (1) {
                    dy = dst->y - src->y;
                    dz = dst->z - src->z;
                    angle = (f32)(LC_ANIM->entries[idx].start - end) * LC_ANIM->entries[idx].scale;
                }
                func_8070D07C(&m1B8[0][0], &m138[0][0],
                    -dx, -dy, -dz,
                    -src->x, -src->y, -src->z);
                mtxRotateZDegF(&m178[0][0], angle);
                mtxMulAffineF(&m178[0][0], &m1B8[0][0], &mB8[0][0]);
                mtxMulAffineF(&m138[0][0], &mB8[0][0], &mF8[0][0]);
                count = LC_ANIM->counts[LC_ANIM->entries[idx].group];
                indices = LC_ANIM->indices[LC_ANIM->entries[idx].group];
                for (i = 0; i < count; i++) {
                    j = indices[i];
                    x = LC_MODEL->vertices[j].x;
                    y = LC_MODEL->vertices[j].y;
                    z = LC_MODEL->vertices[j].z;
                    LC_MODEL->vertices[j].x = x * mF8[0][0] + y * mF8[1][0] + z * mF8[2][0] + mF8[3][0];
                    LC_MODEL->vertices[j].y = x * mF8[0][1] + y * mF8[1][1] + z * mF8[2][1] + mF8[3][1];
                    LC_MODEL->vertices[j].z = x * mF8[0][2] + y * mF8[1][2] + z * mF8[2][2] + mF8[3][2];
                }
            break;
        case 2:
            sidx = LC_ANIM->entries[idx].source;
            didx = LC_ANIM->entries[idx].destination;
            LC_MODEL->vertices[sidx].x = LC_MODEL->vertices[didx].x;
            LC_MODEL->vertices[sidx].y = LC_MODEL->vertices[didx].y;
            LC_MODEL->vertices[sidx].z = LC_MODEL->vertices[didx].z;
            break;
        }
next:
        idx++;
    }
}

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
u8 func_8070B7EC(Gfx **, s32, s32);
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

typedef struct L11bChannels {
    s32 a[4];
} L11bChannels;

extern L11bChannels D_807550A8;
extern s32 D_807FD9A0;
extern s32 D_807FD9C0;
extern Gfx D_1000020[];
extern Mtx D_2000000;
extern Mtx D_2000200;

void func_8070A220(void *, s32, s32);
void n_alSndpPostEvent();
void n_alSndpStop(s32);

#define L11B_RAW(pkt, a, b)              \
    {                                    \
        Gfx *_g = (Gfx *)(pkt);          \
        _g->words.w0 = (a);              \
        _g->words.w1 = (b);              \
    }
#define L11B_MAX(a, b) (((a) > (b)) ? (a) : (b))
#define L11B_MIN(a, b) (((a) < (b)) ? (a) : (b))

u8 func_8070B7EC(Gfx **arg0, s32 arg1, s32 arg2) {
    Gfx *glist;
    Gfx *start;
    Gfx *out;
    Mtx *matrix;
    f64 value;
    s8 delta;
    s32 i;
    s32 volume;
    L11bChannels channels;

    out = *arg0;
    if (D_807444F8 == 1) {
        delta = 3;
    } else {
        delta = -4;
    }
    channels = D_807550A8;
    glist = func_80610FE8(0x4800);
    heapFreeDeferred(glist);
    start = glist;
    if (D_807FD9C8 != 0) {
        if (D_807444F8 == 1) {
            value = (f64)D_80755068 - 20.0;
            D_807FD9C4 = (f32)((0.9 / ((value * 0.001 * value) + 1.0)) + 0.6);
            if (D_80755068 < 60) {
                volume = 0x7FFF;
            } else {
                volume = 0x7FFF - (((D_80755068 - 60) * 0x7FFF) / 60);
            }
        } else {
            D_807FD9C4 = (f32)(((1.5 / (((((f32)(120 - D_80755068) - 40.0f)) * 0.001 * (((f32)(120 - D_80755068) - 40.0f))) + 1.0)) + (0.0002 * ((f32)(120 - D_80755068) - 30.0f) * ((f32)(120 - D_80755068) - 30.0f))) - 0.2);
            if ((f32)(120 - D_80755068) < 110.0f) {
                volume = 0x7FFF;
            } else {
                volume = (s32)(32767.0f - (((f32)(120 - D_80755068) - 110.0f) * 32767.0f / 10.0f));
            }
        }
        n_alSndpPostEvent(D_807FD9C8, 0x10, *(s32 *)&D_807FD9C4, volume);
        n_alSndpPostEvent(D_807FD9C8, 8, volume);
    }
    {
        f32 progress = (f64)D_80755068 / 120.0;
        func_8070B324(1.0f - progress, D_807444F8 == 1, channels.a);
    }
    gDPSetCycleType(glist++, G_CYC_1CYCLE);
    gSPClearGeometryMode(glist++, 0xFFFFFF);
    gSPSetGeometryMode(glist++, G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH);
    gSPSetOtherMode(glist++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x553078);
    L11B_RAW(glist++, 0xFCFFFFFF, 0xFFFCF279);
    gSPTexture(glist++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gDPSetTexturePersp(glist++, G_TP_PERSP);
    gSPDisplayList(glist++, D_1000020);
    gDPPipeSync(glist++);
    for (i = 0; i < D_807FD9A8->unk0; i++) {
        ((f32 *)D_807FD9A8->unk8)[i * 3] = ((f32 *)D_807FD9A4)[i * 3];
        ((f32 *)D_807FD9A8->unk8)[i * 3 + 1] = ((f32 *)D_807FD9A4)[i * 3 + 1];
        ((f32 *)D_807FD9A8->unk8)[i * 3 + 2] = ((f32 *)D_807FD9A4)[i * 3 + 2];
    }
    func_8070A220(D_807FD9A8, D_807FD9AC, D_80755068);
    if (delta < 0) {
        D_807FD9A0 = ((D_80755068 * 0xF0) - 0x960) / 80;
    } else {
        D_807FD9A0 = ((D_80755068 * 0xF0) - 0x4B0) / 80;
    }
    if (D_80755068 >= 5 && D_80755068 < 0x56) {
        func_8070B05C((u16 *)arg2);
    }
    if (D_80755068 >= 0x6D && (f64)D_80755068 <= 120.0) {
        D_8075506C = 0xDC - D_80755068 * 2;
    }
    gSPMatrix(glist++, &D_2000000, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(glist++, &D_2000200, G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);
    gSPPerspNormalize(glist++, D_8076A09C);
    matrix = func_80610FE8(0x40);
    heapFreeDeferred(matrix);
    guTranslate(matrix, 0.0f, (f32)D_8075506C, 0.0f);
    gSPMatrix(glist++, matrix, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gDPSetColorDither(glist++, G_CD_DISABLE);
    gDPSetAlphaDither(glist++, G_AD_DISABLE);
    func_80709BC4(&glist, (L11Info *)D_807FD9A8, (u8 *)arg2);
    D_80755068 += delta;
    D_807FD9C0 = func_8066B0F8(0xE, 0x6A - L11B_MIN(L11B_MAX((s16)(D_807FD9A0 / 26), 0), 9), 1, 1);
    assetFreeBuffer(D_807FD9C0, 0x381, 0x4A);
    gDPPipeSync(glist++);
    gDPSetCycleType(glist++, G_CYC_1CYCLE);
    gDPSetTexturePersp(glist++, G_TP_NONE);
    L11B_RAW(glist++, 0xFCFFFFFF, 0xFFFCF279);
    gSPSetOtherMode(glist++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x5041C8);
    gDPPipeSync(glist++);
    gDPLoadTextureBlock(glist++, D_807FD9C0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 32, 0, G_TX_WRAP, G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(glist++, 0x260, L11B_MAX((s16)(D_807FD9A0 << 2), 0), 0x2A0, L11B_MAX((s16)((D_807FD9A0 + 0x1F) << 2), 0), 0, 0, -((D_807FD9A0 << 2 < 0) ? L11B_MIN(((s16)(D_807FD9A0 << 2) << 10) >> 7, 0) : 0), 0x400, 0x400);
    gSPEndDisplayList(glist++);
    gSPDisplayList(out++, start);
    *arg0 = out;
    if (D_80755068 < 0 || (f64)D_80755068 > 120.0) {
        n_alSndpStop(D_807FD9C8);
    }
    return D_80755068 < 0 || (f64)D_80755068 > 120.0;
}

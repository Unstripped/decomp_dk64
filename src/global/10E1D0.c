#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB44;
extern Actor *D_807FBB48;
extern Actor *D_807FBB4C;
extern void *gPlayerSlots;
extern u8 gPlayerCount;
extern u8 gCurrentPlayerIndex;
extern u8 D_807FC950[][0x5E];
extern s32 gCurrentMap;
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

typedef struct FbTile {
    s32 offset;
    s32 width;
    s32 height;
} FbTile;

extern FbTile *gFbTileTable;

void fbBuildTileTable(s32 arg0, s32 arg1) {
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
            gFbTileTable[idx].offset = D_80744490 * y + x;
            if (remW != 0 && col == cols - 1) {
                gFbTileTable[idx].width = remW;
            } else {
                gFbTileTable[idx].width = arg0;
            }
            if (remH != 0 && row == 0) {
                gFbTileTable[idx].height = remH;
            } else {
                gFbTileTable[idx].height = arg1;
            }
            x += arg0;
            idx++;
        }
        y -= arg1;
    }
}

#ifdef NON_MATCHING
typedef struct MeshEntry {
    u32 unk0;
    u8 pad[0x18];
} MeshEntry;

typedef struct MeshBlobTail {
    u32 *unk0;
    s32 *unk4;
    u8 *unk8;
} MeshBlobTail;

typedef struct MeshBlobHeader {
    s32 unk0;
    s32 unk4;
    u8 *unk8;
    u8 *unkC;
    void *unk10;
    void *unk14;
    u32 *unk18;
    s32 *unk1C;
    s32 *unk20;
} MeshBlobHeader;

void *heapAlloc(s32);

s32 func_80709890(MeshBlobHeader *arg0, MeshBlobHeader **arg1, MeshBlobTail **arg2, s32 **arg3) {
    s32 count;
    s32 k;
    s32 sum;
    MeshBlobTail *b;
    u32 *p;
    u32 *r;
    MeshEntry *q;

    if (arg0 == NULL) {
        return 0;
    }
    if (arg1 == NULL) {
        return 0;
    }
    gFbTileTable = heapAlloc(0x708);
    arg0->unk10 = heapAlloc(arg0->unk0 * 0x10);
    arg0->unk14 = heapAlloc(arg0->unk0 * 0x10);
    if (arg0 && arg0) {} // FAKE: block split after the 3rd heapAlloc frees $v0 for walker p
    count = 1;
    arg0->unk8 = (u8 *)arg0 + 0x2C;
    arg0->unkC = arg0->unk8 + arg0->unk0 * 0xC;
    arg0->unk18 = (u32 *)(arg0->unkC + arg0->unk4 * 0x1C);
    p = arg0->unk18;
    if (arg0->unk20) {}  // FAKE: dead use steers V8/VC/V18 colouring order
    while (*p++ != 0) {
        if (arg0->unk20) {}  // FAKE: dead use in walker loop steers V8/VC colouring
        count++;
    }
    arg0->unk20 = (s32 *)arg0->unk18 + count;
    arg0->unk1C = arg0->unk20 + count;
    *arg1 = arg0;
    if (arg2 != NULL) {
        b = (MeshBlobTail *)(arg0->unk1C + count);
        b->unk8 = (u8 *)(b + 1);
        q = (MeshEntry *)b->unk8;
        if (gFbTileTable && gFbTileTable) {} // FAKE: block split steering loop-2 walker regalloc
        count = 1;
        while ((q++)->unk0 != 0) {
            count++;
        }
        k = 1;
        b->unk0 = r = (u32 *)(b->unk8 + count * 0x1C);
        while (*r++ != -1) {
            k++;
            if (r == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        }
        count = 0;
        b->unk4 = (s32 *)((u8 *)b->unk0 + k * 4);
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

typedef struct MeshRangeView { s32 unk0, unk4, unk8; u8 *unkC; s32 unk10, unk14; s32 *unk18, *unk1C, *unk20; } MeshRangeView;
typedef struct MeshTriEntry { s32 unk0, unk4, unk8; u8 padC[0x10]; } MeshTriEntry;
s32 meshComputeVertexRanges(MeshRangeView *arg0) {
    MeshTriEntry *e;
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
        e = (MeshTriEntry *)(arg0->unkC + off);
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

typedef struct MeshCell {
    s32 v0, v1, v2, st0, st1, st2, texture;
} MeshCell;
typedef struct MeshTexInfo {
    s32 offset, width, height;
} MeshTexInfo;
typedef struct MeshInfo {
    s32 vertex_count, unk4;
    f32 *vertices;
    MeshCell *cells;
    u8 *screen_vertices[2];
    s32 *column_counts, *column_ends, *column_starts;
} MeshInfo;
extern MeshTexInfo D_80754F80[];
extern u16 D_80754FC8[];
s16 func_8070C200(f32);

void meshDrawTextured(Gfx **arg0, MeshInfo *arg1, u8 *arg2) {
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
                    gDPLoadTextureTile(glist++, arg2 + gFbTileTable[texture].offset * 2, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, 0, 0, 0, gFbTileTable[texture].width, gFbTileTable[texture].height - 1, 0, G_TX_WRAP, G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
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

typedef f32 AnimMatrix[4][4];

typedef struct AnimVec3 {
    f32 x;
    f32 y;
    f32 z;
} AnimVec3;

typedef struct AnimModel {
    s32 unk0;
    s32 unk4;
    AnimVec3 *vertices;
} AnimModel;

typedef struct AnimEntry {
    s32 kind;
    s32 group;
    s32 start;
    s32 end;
    f32 scale;
    u32 source;
    u32 destination;
} AnimEntry;

typedef struct AnimTable {
    s32 *counts;
    u16 **indices;
    AnimEntry *entries;
} AnimTable;

void mtxMulAffineF(f32 *, f32 *, f32 *);
void mtxRotateZDegF(f32 *, f32);
void func_8070D07C(f32 *, f32 *, f32, f32, f32, f32, f32, f32);

#define ANIM_MODEL ((AnimModel *)arg0)
#define ANIM_TABLE ((AnimTable *)arg1)

void meshApplyAnimation(void *arg0, s32 arg1, s32 frame) {
    u32 sidx;
    u32 didx;
    AnimMatrix m1B8;
    AnimMatrix m178;
    AnimMatrix m138;
    AnimMatrix mF8;
    AnimMatrix mB8;
    s16 idx;
    s32 i;
    s32 count;
    u16 *indices;
    s32 end;
    AnimVec3 *src;
    AnimVec3 *dst;
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
    while (ANIM_TABLE->entries[idx].kind != 0) {
        end = frame;
        if (frame < ANIM_TABLE->entries[idx].start) {
            goto next;
        }
        kindv = ANIM_TABLE->entries[idx].kind;
        if (i && i) {}
        if (ANIM_TABLE->entries[idx].end < frame) {
            end = ANIM_TABLE->entries[idx].end;
        }
        switch (kindv) {
        case 1:
                sidx = ANIM_TABLE->entries[idx].source;
                didx = ANIM_TABLE->entries[idx].destination;
                src = &ANIM_MODEL->vertices[sidx];
                dst = &ANIM_MODEL->vertices[didx];
                dx = dst->x - src->x;
                if (1) {
                    dy = dst->y - src->y;
                    dz = dst->z - src->z;
                    angle = (f32)(ANIM_TABLE->entries[idx].start - end) * ANIM_TABLE->entries[idx].scale;
                }
                func_8070D07C(&m1B8[0][0], &m138[0][0],
                    -dx, -dy, -dz,
                    -src->x, -src->y, -src->z);
                mtxRotateZDegF(&m178[0][0], angle);
                mtxMulAffineF(&m178[0][0], &m1B8[0][0], &mB8[0][0]);
                mtxMulAffineF(&m138[0][0], &mB8[0][0], &mF8[0][0]);
                count = ANIM_TABLE->counts[ANIM_TABLE->entries[idx].group];
                indices = ANIM_TABLE->indices[ANIM_TABLE->entries[idx].group];
                for (i = 0; i < count; i++) {
                    j = indices[i];
                    x = ANIM_MODEL->vertices[j].x;
                    y = ANIM_MODEL->vertices[j].y;
                    z = ANIM_MODEL->vertices[j].z;
                    ANIM_MODEL->vertices[j].x = x * mF8[0][0] + y * mF8[1][0] + z * mF8[2][0] + mF8[3][0];
                    ANIM_MODEL->vertices[j].y = x * mF8[0][1] + y * mF8[1][1] + z * mF8[2][1] + mF8[3][1];
                    ANIM_MODEL->vertices[j].z = x * mF8[0][2] + y * mF8[1][2] + z * mF8[2][2] + mF8[3][2];
                }
            break;
        case 2:
            sidx = ANIM_TABLE->entries[idx].source;
            didx = ANIM_TABLE->entries[idx].destination;
            ANIM_MODEL->vertices[sidx].x = ANIM_MODEL->vertices[didx].x;
            ANIM_MODEL->vertices[sidx].y = ANIM_MODEL->vertices[didx].y;
            ANIM_MODEL->vertices[sidx].z = ANIM_MODEL->vertices[didx].z;
            break;
        }
next:
        idx++;
    }
}

void fbCopySetAlpha(s32 *arg0, s32 *arg1) {
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

typedef struct TransitionBuffers {
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
} TransitionBuffers;

extern u8 *D_8076A048;
extern Gfx *D_8076A050[];
extern s32 gFrameCounter;
extern s32 D_8076A088;
extern s32 D_8076A08C;
extern u8 D_8076A0A4;
extern u8 D_8076A0B2;
extern Mtx D_80767CE8;
extern f32 gScreenFadeProgress;
extern TransitionBuffers *D_807FD9A8;
extern s32 D_807FD9B0;
extern s32 D_807FD9B8;

void func_805FE71C(Gfx *, u8, s32 *, u8);
void func_805FE7B4(Gfx *, s32, s32 *, u8);
void func_805FF378(s32, s32);
void schedSubmitGfxTask(Gfx *, s32, s32, u8, s32, s32);
void transitionBeginDisplayList();
void transitionInit(void);
u8 transitionRender(Gfx **, s32, s32);
void heapFreeDeferred(void *);
void assetFreeBuffer(s32, s32, s32);
void camRestartPath(void);

void transitionRunFrame(s32 arg0, s32 arg1) {
    Gfx *sp34;
    Gfx *sp30;

    schedSubmitGfxTask(D_8076A050[D_807444FC], D_8076A088, 3, 1, 0x4D2, 1);
    D_807444FC ^= 1;
    gFrameCounter += 1;
    D_8076A048 = (D_807444FC * 0x11B0) + (u8 *)&D_80767CE8;
    sp30 = (Gfx *)(D_8076A048 + 0xDB0);
    switch (*(u8 *)&D_807FD9BC) {
    case 1:
        break;
    case 0:
        *(u8 *)&D_807FD9BC = 1;
        transitionInit();
        break;
    }
    if ((D_8076A0B1 & 1) && (gScreenFadeProgress == 31.0f)) {
        sp34 = D_8076A050[D_807444FC];
        if (D_8076A0B2 == 1) {
            D_807444EC = D_807444F4;
        }
    } else {
        transitionBeginDisplayList(D_8076A048, &sp34, &D_8076A0B1);
        if (transitionRender(&sp34, D_807FD9B8, D_807FD9B0) != 0) {
            switch (D_807444F8) {
            case 1:
                osViBlack(1);
                func_805FF378(arg0, arg1);
                gScreenFadeProgress = 31.0f;
                D_807444F8 = 2;
                break;
            case 2:
                heapFreeDeferred((void *)D_807FD9B0);
                heapFreeDeferred(D_807FD9A8->unk8);
                heapFreeDeferred((void *)gFbTileTable);
                heapFreeDeferred(D_807FD9A8->unk10);
                heapFreeDeferred(D_807FD9A8->unk14);
                assetFreeBuffer(D_807FD9B8, 0x24B, 0x4A);
                if (((D_807444EC = D_807444F4) == 1) && (D_807FBB64 & 1)) {
                    camRestartPath();
                }
                D_807444F8 = 3;
                gScreenFadeProgress = 0.0f;
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

void transitionBeginDisplayList(void *arg0, Gfx **arg1) {
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

extern s32 gTransitionProgress;
extern s32 D_8075506C;
extern void *D_807FD9A4;
extern s32 D_807FD9AC;
extern s32 *D_80744470[];

void *heapAlloc(s32);
s32 assetLoad();
s32 func_80709890();
s32 meshComputeVertexRanges();

void transitionInit(void) {
    switch (D_807444F8) {
    case 1:
        gTransitionProgress = 0;
        D_8075506C = 0;
        break;
    case 2:
        gTransitionProgress = 0x78;
        break;
    }
    D_807FD9B8 = assetLoad(0x13, 1, 1, 1);
    D_807FD9B0 = (s32)heapAlloc(D_80744490 * D_80744494 * 2);
    fbCopySetAlpha((s32 *)D_807FD9B0, D_80744470[D_807444FC]);
    func_80709890((void *)D_807FD9B8, (void *)&D_807FD9A8, (void *)&D_807FD9AC, 0);
    meshComputeVertexRanges((void *)D_807FD9A8);
    D_807FD9A4 = D_807FD9A8->unk8;
    D_807FD9A8->unk8 = heapAlloc(D_807FD9A8->unk0 * 0xC);
    fbBuildTileTable(D_807FD9A8->unk24, D_807FD9A8->unk28);
}

typedef struct TransitionDitherMask {
    u16 data[24];
} TransitionDitherMask;

extern TransitionDitherMask D_80755074;

void transitionMaskFramebuffer(u16 *arg0) {
    TransitionDitherMask temp = D_80755074;
    s32 i;
    u16 *pixels = arg0 + 0x9D;
    s32 t = gTransitionProgress - 5;
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

void transitionSetAudioVolume(f32 arg0, s32 arg1, s32 *arg2) {
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

typedef struct TransitionChannels {
    s32 a[4];
} TransitionChannels;

extern TransitionChannels D_807550A8;
extern s32 D_807FD9A0;
extern s32 D_807FD9C0;
extern Gfx D_1000020[];
extern Mtx D_2000000;
extern Mtx D_2000200;

void meshApplyAnimation(void *, s32, s32);
void n_alSndpPostEvent();
void n_alSndpStop(s32);

#define TRANS_RAW(pkt, a, b)              \
    {                                    \
        Gfx *_g = (Gfx *)(pkt);          \
        _g->words.w0 = (a);              \
        _g->words.w1 = (b);              \
    }
#define TRANS_MAX(a, b) (((a) > (b)) ? (a) : (b))
#define TRANS_MIN(a, b) (((a) < (b)) ? (a) : (b))

u8 transitionRender(Gfx **arg0, s32 arg1, s32 arg2) {
    Gfx *glist;
    Gfx *start;
    Gfx *out;
    Mtx *matrix;
    f64 value;
    s8 delta;
    s32 i;
    s32 volume;
    TransitionChannels channels;

    out = *arg0;
    if (D_807444F8 == 1) {
        delta = 3;
    } else {
        delta = -4;
    }
    channels = D_807550A8;
    glist = heapAlloc(0x4800);
    heapFreeDeferred(glist);
    start = glist;
    if (D_807FD9C8 != 0) {
        if (D_807444F8 == 1) {
            value = (f64)gTransitionProgress - 20.0;
            D_807FD9C4 = (f32)((0.9 / ((value * 0.001 * value) + 1.0)) + 0.6);
            if (gTransitionProgress < 60) {
                volume = 0x7FFF;
            } else {
                volume = 0x7FFF - (((gTransitionProgress - 60) * 0x7FFF) / 60);
            }
        } else {
            D_807FD9C4 = (f32)(((1.5 / (((((f32)(120 - gTransitionProgress) - 40.0f)) * 0.001 * (((f32)(120 - gTransitionProgress) - 40.0f))) + 1.0)) + (0.0002 * ((f32)(120 - gTransitionProgress) - 30.0f) * ((f32)(120 - gTransitionProgress) - 30.0f))) - 0.2);
            if ((f32)(120 - gTransitionProgress) < 110.0f) {
                volume = 0x7FFF;
            } else {
                volume = (s32)(32767.0f - (((f32)(120 - gTransitionProgress) - 110.0f) * 32767.0f / 10.0f));
            }
        }
        n_alSndpPostEvent(D_807FD9C8, 0x10, *(s32 *)&D_807FD9C4, volume);
        n_alSndpPostEvent(D_807FD9C8, 8, volume);
    }
    {
        f32 progress = (f64)gTransitionProgress / 120.0;
        transitionSetAudioVolume(1.0f - progress, D_807444F8 == 1, channels.a);
    }
    gDPSetCycleType(glist++, G_CYC_1CYCLE);
    gSPClearGeometryMode(glist++, 0xFFFFFF);
    gSPSetGeometryMode(glist++, G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH);
    gSPSetOtherMode(glist++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x553078);
    TRANS_RAW(glist++, 0xFCFFFFFF, 0xFFFCF279);
    gSPTexture(glist++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gDPSetTexturePersp(glist++, G_TP_PERSP);
    gSPDisplayList(glist++, D_1000020);
    gDPPipeSync(glist++);
    for (i = 0; i < D_807FD9A8->unk0; i++) {
        ((f32 *)D_807FD9A8->unk8)[i * 3] = ((f32 *)D_807FD9A4)[i * 3];
        ((f32 *)D_807FD9A8->unk8)[i * 3 + 1] = ((f32 *)D_807FD9A4)[i * 3 + 1];
        ((f32 *)D_807FD9A8->unk8)[i * 3 + 2] = ((f32 *)D_807FD9A4)[i * 3 + 2];
    }
    meshApplyAnimation(D_807FD9A8, D_807FD9AC, gTransitionProgress);
    if (delta < 0) {
        D_807FD9A0 = ((gTransitionProgress * 0xF0) - 0x960) / 80;
    } else {
        D_807FD9A0 = ((gTransitionProgress * 0xF0) - 0x4B0) / 80;
    }
    if (gTransitionProgress >= 5 && gTransitionProgress < 0x56) {
        transitionMaskFramebuffer((u16 *)arg2);
    }
    if (gTransitionProgress >= 0x6D && (f64)gTransitionProgress <= 120.0) {
        D_8075506C = 0xDC - gTransitionProgress * 2;
    }
    gSPMatrix(glist++, &D_2000000, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(glist++, &D_2000200, G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);
    gSPPerspNormalize(glist++, D_8076A09C);
    matrix = heapAlloc(0x40);
    heapFreeDeferred(matrix);
    guTranslate(matrix, 0.0f, (f32)D_8075506C, 0.0f);
    gSPMatrix(glist++, matrix, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gDPSetColorDither(glist++, G_CD_DISABLE);
    gDPSetAlphaDither(glist++, G_AD_DISABLE);
    meshDrawTextured(&glist, (MeshInfo *)D_807FD9A8, (u8 *)arg2);
    gTransitionProgress += delta;
    D_807FD9C0 = assetLoad(0xE, 0x6A - TRANS_MIN(TRANS_MAX((s16)(D_807FD9A0 / 26), 0), 9), 1, 1);
    assetFreeBuffer(D_807FD9C0, 0x381, 0x4A);
    gDPPipeSync(glist++);
    gDPSetCycleType(glist++, G_CYC_1CYCLE);
    gDPSetTexturePersp(glist++, G_TP_NONE);
    TRANS_RAW(glist++, 0xFCFFFFFF, 0xFFFCF279);
    gSPSetOtherMode(glist++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x5041C8);
    gDPPipeSync(glist++);
    gDPLoadTextureBlock(glist++, D_807FD9C0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 32, 0, G_TX_WRAP, G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(glist++, 0x260, TRANS_MAX((s16)(D_807FD9A0 << 2), 0), 0x2A0, TRANS_MAX((s16)((D_807FD9A0 + 0x1F) << 2), 0), 0, 0, -((D_807FD9A0 << 2 < 0) ? TRANS_MIN(((s16)(D_807FD9A0 << 2) << 10) >> 7, 0) : 0), 0x400, 0x400);
    gSPEndDisplayList(glist++);
    gSPDisplayList(out++, start);
    *arg0 = out;
    if (gTransitionProgress < 0 || (f64)gTransitionProgress > 120.0) {
        n_alSndpStop(D_807FD9C8);
    }
    return gTransitionProgress < 0 || (f64)gTransitionProgress > 120.0;
}

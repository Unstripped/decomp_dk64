#include "common.h"
#include "actor.h"
#include "render.h"
#include "proto/global/10E1D0.h"
#include "proto/global/110F00.h"
#include "proto/global/13A7A0.h"
#include "proto/global/14CF0.h"
#include "proto/global/15050.h"
#include "proto/global/201B0.h"
#include "proto/global/3C10.h"
#include "proto/global/450.h"
#include "proto/global/5650.h"
#include "proto/global/6AD90.h"
#include "proto/global/7130.h"
struct AnimTable;
struct MeshBlob;
s32 meshBlobParse(struct MeshBlob *, struct MeshBlob **, struct AnimTable **, void **);
s32 meshComputeVertexRanges(struct MeshBlob *);
void meshDrawTextured(Gfx **, struct MeshBlob *, u16 *);
void meshApplyAnimation(struct MeshBlob *, struct AnimTable *, s32);
u8 transitionRender(Gfx **, void *, u16 *);

extern Actor *gCurrentActor;
extern Actor *gSpawnedActor;
extern Actor *gActivePlayerActor;
extern Actor *gPrimaryPlayerActor;
extern void *gPlayerSlots;
extern u8 gPlayerCount;
extern u8 gCurrentPlayerIndex;
extern s32 gCurrentMap;
extern u8 gCurrentWorldId;
extern u8 gScreenRenderFlags;
extern s16 gScreenWidth;
extern s16 gScreenHeight;
extern u8 gNextGameMode;
extern u8 gGfxBufferIndex;

extern u8 gGameMode;
extern u8 D_807444F4;
extern ALBank *D_8076D1F8;
extern s32 gGlobalOverlayFlags;
extern u8 D_807FD9BC;
extern u8 D_807FD9BD;
extern union { f32 f; s32 bits; } sTransitionSoundPitch; // sound pitch, posted as raw event bits
extern struct GfSndState *sTransitionSound;

void func_807094D0(mode)
u8 mode;
{
    D_807444F4 = gGameMode;
    switch (mode) {
    case 2:
        sTransitionSoundPitch.f = 1.0f;
        D_807FD9BC = 0;
        gNextGameMode = 1;
        gGameMode = 6;
        break;
    case 3:
        sTransitionSoundPitch.f = 0.5f;
        D_807FD9BC = 0;
        gNextGameMode = 2;
        gGameMode = 6;
        D_807FD9BD = 2;
        if ((D_807444F4 == 1) && (gGlobalOverlayFlags & 1)) {
            timerQueueCancel(0);
        }
        break;
    }
    n_alSndpPlay(D_8076D1F8, 0x1BC, 0x7FFF, 0x3F, 1.0f, 0, &sTransitionSound);
}

typedef struct FbTile {
    s32 offset;
    s32 width;
    s32 height;
} FbTile;

extern FbTile *gFbTileTable;

void fbBuildTileTable(s32 tileWidth, s32 tileHeight) {
    s32 cols;
    s32 rows;
    s32 remW;
    s32 remH;
    s32 y;
    s32 idx;
    s32 row;
    s32 col;
    s32 x;

    cols = gScreenWidth / tileWidth;
    rows = gScreenHeight / tileHeight;
    remW = gScreenWidth - tileWidth * cols;
    remH = gScreenHeight - tileHeight * rows;
    if (remW > 0) {
        cols++;
    }
    if (remH > 0) {
        rows++;
    }
    idx = 0;
    if (remH != 0) {
        y = gScreenHeight - remH;
    } else {
        y = gScreenHeight - tileHeight;
    }
    for (row = 0; row < rows; row++) {
        x = 0;
        for (col = 0; col < cols; col++) {
            gFbTileTable[idx].offset = gScreenWidth * y + x;
            if (remW != 0 && col == cols - 1) {
                gFbTileTable[idx].width = remW;
            } else {
                gFbTileTable[idx].width = tileWidth;
            }
            if (remH != 0 && row == 0) {
                gFbTileTable[idx].height = remH;
            } else {
                gFbTileTable[idx].height = tileHeight;
            }
            x += tileWidth;
            idx++;
        }
        y -= tileHeight;
    }
}

typedef struct MeshVertex {
    f32 x;
    f32 y;
    f32 z;
} MeshVertex;

typedef struct MeshCell {
    s32 v0, v1, v2, st0, st1, st2, texture;
} MeshCell;

/* Header of the transition mesh asset; the vertex, cell and column arrays follow it in the blob. */
typedef struct MeshBlob {
    /* 0x00 */ s32 vertexCount;
    /* 0x04 */ s32 cellCount;
    /* 0x08 */ MeshVertex *vertices;
    /* 0x0C */ MeshCell *cells;
    /* 0x10 */ Vtx *screenVerts[2];
    /* 0x18 */ s32 *columnCounts;
    /* 0x1C */ s32 *columnEnds;
    /* 0x20 */ s32 *columnStarts;
    /* 0x24 */ s32 tileWidth;
    /* 0x28 */ s32 tileHeight;
} MeshBlob;

typedef struct AnimEntry {
    s32 kind;
    s32 group;
    s32 start;
    s32 end;
    f32 scale;
    u32 source;
    u32 destination;
} AnimEntry;

/* Animation tail of the blob, after the mesh's column arrays. */
typedef struct AnimTable {
    s32 *counts;
    u16 **indices;
    AnimEntry *entries;
} AnimTable;


s32 meshBlobParse(MeshBlob *blob, MeshBlob **outMesh, AnimTable **outAnim, void **outEnd) {
    s32 count;
    s32 k;
    s32 sum;
    AnimTable *b;

    if (blob == NULL) {
        return 0;
    }
    if (outMesh == NULL) {
        return 0;
    }
    gFbTileTable = heapAlloc(0x708);
    blob->screenVerts[0] = heapAlloc(blob->vertexCount * sizeof(Vtx));
    blob->screenVerts[1] = heapAlloc(blob->vertexCount * sizeof(Vtx));
    blob->vertices = (MeshVertex *)(blob + 1);
    blob->cells = (MeshCell *)(blob->vertices + blob->vertexCount);
    blob->columnCounts = (s32 *)(blob->cells + blob->cellCount);
    count = 0;
    while (blob->columnCounts[count++] != 0) {
    }
    blob->columnStarts = blob->columnCounts + count;
    blob->columnEnds = blob->columnStarts + count;
    *outMesh = blob;
    if (outAnim != NULL) {
        b = (AnimTable *)(blob->columnEnds + count);
        b->entries = (AnimEntry *)(b + 1);
        count = 0;
        while (b->entries[count++].kind != 0) {
        }
        b->counts = (s32 *)(b->entries + count);
        k = 0;
        while (b->counts[k++] != -1) {
        }
        count = 0;
        b->indices = (u16 **)(b->counts + k);
        sum = 0;
        while (b->counts[count] != -1) {
            b->indices[count] = (u16 *)(b->indices + k) + sum;
            sum += b->counts[count];
            count++;
        }
        *outAnim = b;
    }
    if (outEnd != NULL) {
        if (outAnim == NULL) {
            *outEnd = blob->columnEnds + count;
        } else {
            *outEnd = b->indices + count;
        }
    }
    return 1;
}

s32 meshComputeVertexRanges(MeshBlob *mesh) {
    MeshCell *e;
    s32 v2;
    s32 min;
    s32 off;
    s32 max;
    s32 i;
    s32 k;
    k = 0;
    min = 0; // FAKE: dead init (min is set before every use) steers regalloc
    off = 0;
    while (mesh->columnCounts[k]) {
        e = (MeshCell *)((u8 *)mesh->cells + off); // FAKE: byte offset off (v1, +28 per cell at 0x638) re-derives e each column (lw t7,0xC(a0); addu a1,t7,v1 at 0x618/0x620); a cell index or one walker is fdiff 1
        v2 = e->v2; // FAKE: dead pre-loop load of the third vertex steers regalloc
        min = max = e->v0;
        for (i = 0; i < mesh->columnCounts[k]; i++, off += sizeof(MeshCell), e++) {
            if (e->v0 > max) max = e->v0; else if (e->v0 < min) min = e->v0;
            if (e->v1 > max) max = e->v1; else if (e->v1 < min) min = e->v1;
            v2 = e->v2;
            if (v2 > max) max = v2; else if (v2 < min) min = v2;
        }
        mesh->columnStarts[k] = min;
        mesh->columnEnds[k] = max;
        k++;
    }
    return 1;
}

typedef struct MeshTexInfo {
    s32 offset, width, height;
} MeshTexInfo;
extern MeshTexInfo D_80754F80[];
extern u16 D_80754FC8[];
s16 func_8070C200(f32);

void meshDrawTextured(Gfx **gdl, MeshBlob *mesh, u16 *framebuffer) {
    Gfx *glist = *gdl;
    s32 j, k, row, texture, prev, base, count;

    for (j = 0; j < mesh->vertexCount; j++) {
        mesh->screenVerts[gGfxBufferIndex][j].v.ob[0] = func_8070C200(mesh->vertices[j].x);
        mesh->screenVerts[gGfxBufferIndex][j].v.ob[1] = func_8070C200(mesh->vertices[j].y);
        mesh->screenVerts[gGfxBufferIndex][j].v.ob[2] = func_8070C200(mesh->vertices[j].z);
    }
    k = 0;
    for (row = 0; mesh->columnCounts[row] != 0; row++) {
        prev = -0x63;
        base = mesh->columnStarts[row];
        count = mesh->columnEnds[row] - base + 1;
        gSPVertex(glist++, osVirtualToPhysical(&mesh->screenVerts[gGfxBufferIndex][base]), count, 0);
        for (j = 0; j < mesh->columnCounts[row]; j++) {
            texture = mesh->cells[k].texture;
            if (texture != prev) {
                prev = texture;
                if (texture < 0) {
                    texture = -1 - texture;
                    gDPLoadTextureBlock(glist++, D_80754FC8 + D_80754F80[texture].offset, G_IM_FMT_RGBA, G_IM_SIZ_16b, D_80754F80[texture].width, D_80754F80[texture].height - 1, 0, G_TX_WRAP, G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                } else {
                    gDPLoadTextureTile(glist++, framebuffer + gFbTileTable[texture].offset, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, 0, 0, 0, gFbTileTable[texture].width, gFbTileTable[texture].height - 1, 0, G_TX_WRAP, G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                }
            }
            gSPModifyVertex(glist++, mesh->cells[k].v0 - base, G_MWO_POINT_ST, mesh->cells[k].st0);
            gSPModifyVertex(glist++, mesh->cells[k].v1 - base, G_MWO_POINT_ST, mesh->cells[k].st1);
            gSPModifyVertex(glist++, mesh->cells[k].v2 - base, G_MWO_POINT_ST, mesh->cells[k].st2);
            gSP1Triangle(glist++, mesh->cells[k].v0 - base, mesh->cells[k].v1 - base, mesh->cells[k].v2 - base, 0);
            k++;
        }
    }
    *gdl = glist;
}

typedef f32 AnimMatrix[4][4];

void meshApplyAnimation(MeshBlob *model, AnimTable *table, s32 frame) {
    u32 sidx;
    u32 didx;
    AnimMatrix lookMtx;
    AnimMatrix rotMtx;
    AnimMatrix lookInvMtx;
    AnimMatrix xformMtx;
    AnimMatrix tmpMtx;
    s16 idx;
    s32 i;
    s32 count;
    u16 *indices;
    s32 end;
    MeshVertex *src;
    MeshVertex *dst;
    f32 angle;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 x;
    f32 y;
    f32 z;
    u32 j;

    idx = 0;
    for (; table->entries[idx].kind != 0; idx++) {
        end = frame;
        if (frame < table->entries[idx].start) {
            continue;
        }
        if (table->entries[idx].end < frame) {
            end = table->entries[idx].end;
        }
        switch (table->entries[idx].kind) {
        case 1:
            sidx = table->entries[idx].source;
            didx = table->entries[idx].destination;
            src = &model->vertices[sidx];
            dst = &model->vertices[didx];
            x = src->x;
            dx = dst->x - x;
            dy = dst->y - src->y;
            dz = dst->z - src->z;
            angle = (f32)(table->entries[idx].start - end) * table->entries[idx].scale;
            mtxLookDirPosF(lookMtx, lookInvMtx,
                -dx, -dy, -dz,
                -x, -src->y, -src->z);
            mtxRotateZDegF(rotMtx, angle);
            mtxMulAffineF(rotMtx, lookMtx, tmpMtx);
            mtxMulAffineF(lookInvMtx, tmpMtx, xformMtx);
            count = table->counts[table->entries[idx].group];
            indices = table->indices[table->entries[idx].group];
            for (i = 0; i < count; i++) {
                j = indices[i];
                x = model->vertices[j].x;
                y = model->vertices[j].y;
                z = model->vertices[j].z;
                model->vertices[j].x = x * xformMtx[0][0] + y * xformMtx[1][0] + z * xformMtx[2][0] + xformMtx[3][0];
                model->vertices[j].y = x * xformMtx[0][1] + y * xformMtx[1][1] + z * xformMtx[2][1] + xformMtx[3][1];
                model->vertices[j].z = x * xformMtx[0][2] + y * xformMtx[1][2] + z * xformMtx[2][2] + xformMtx[3][2];
            }
            break;
        case 2:
            sidx = table->entries[idx].source;
            didx = table->entries[idx].destination;
            model->vertices[sidx].x = model->vertices[didx].x;
            model->vertices[sidx].y = model->vertices[didx].y;
            model->vertices[sidx].z = model->vertices[didx].z;
            break;
        }
    }
}

void fbCopySetAlpha(void *dstBuf, void *srcBuf) {
    s32 i;
    s32 *src = srcBuf;
    s32 *dst = dstBuf;

    for (i = 0; i < (gScreenWidth * gScreenHeight) / 16; i++) {
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


extern FrameMatrices *gGfxCurrentFrameBuffer;
extern Gfx *gGfxTaskBuffers[];
extern s32 D_8076A088;
extern s32 D_8076A08C;
extern u8 D_8076A0A4;
extern u8 D_8076A0B2;
extern FrameMatrices D_80767CE8[];
extern f32 gScreenFadeProgress;
extern MeshBlob *sTransitionMesh;
extern u16 *sTransitionFramebufferCopy;
extern void *sTransitionMeshAsset;


void transitionRunFrame(s32 map, s32 exit) {
    Gfx *dl;
    Gfx *subDl;

    schedSubmitGfxTask(gGfxTaskBuffers[gGfxBufferIndex], D_8076A088, 3, 1, 0x4D2, 1);
    gGfxBufferIndex ^= 1;
    gFrameCounter += 1;
    gGfxCurrentFrameBuffer = &D_80767CE8[gGfxBufferIndex];
    subDl = gGfxCurrentFrameBuffer->subDisplayList;
    switch (D_807FD9BC) {
    case 1:
        break;
    case 0:
        D_807FD9BC = 1;
        transitionInit();
        break;
    }
    if ((gScreenRenderFlags & 1) && (gScreenFadeProgress == 31.0f)) {
        dl = gGfxTaskBuffers[gGfxBufferIndex];
        if (D_8076A0B2 == 1) {
            gGameMode = D_807444F4;
        }
    } else {
        transitionBeginDisplayList(gGfxCurrentFrameBuffer, &dl);
        if (transitionRender(&dl, sTransitionMeshAsset, sTransitionFramebufferCopy) != 0) {
            switch (gNextGameMode) {
            case 1:
                osViBlack(1);
                mapRequestTransition(map, exit);
                gScreenFadeProgress = 31.0f;
                gNextGameMode = 2;
                break;
            case 2:
                heapFreeDeferred(sTransitionFramebufferCopy);
                heapFreeDeferred(sTransitionMesh->vertices);
                heapFreeDeferred(gFbTileTable);
                heapFreeDeferred(sTransitionMesh->screenVerts[0]);
                heapFreeDeferred(sTransitionMesh->screenVerts[1]);
                assetFreeBuffer(sTransitionMeshAsset, 0x24B, 0x4A);
                gGameMode = D_807444F4;
                if ((gGameMode == 1) && (gGlobalOverlayFlags & 1)) {
                    camRestartPath();
                }
                gNextGameMode = 3;
                gScreenFadeProgress = 0.0f;
                break;
            }
        }
    }
    if (D_807FD9BD != 0) {
        D_807FD9BD--;
        if (D_807FD9BD == 0) {
            gScreenRenderFlags |= 2;
        }
    }
    if ((D_8076A0A4 != 0) && (gGameMode != 6)) {
        gfxEndDisplayList(dl, gGfxBufferIndex, &D_8076A088, 0);
        gfxEndSubDisplayList(subDl, gGfxCurrentFrameBuffer, &D_8076A08C, 1);
        return;
    }
    gfxEndDisplayList(dl, gGfxBufferIndex, &D_8076A088, 1);
}

extern void *D_8076A080;
extern u16 D_8076A09C;
extern Gfx D_1000090[];


void transitionBeginDisplayList(FrameMatrices *frame, Gfx **outDl) {
    Gfx *dl = gGfxTaskBuffers[gGfxBufferIndex];

    gSPSegment(dl++, 0, 0);
    gSPSegment(dl++, 2, osVirtualToPhysical(frame));
    gSPSegment(dl++, 1, osVirtualToPhysical(D_8076A080));
    gSPDisplayList(dl++, D_1000090);
    dl = gfxClearZBuffer(gfxSetViewportDisplayList(dl));
    gDPPipeSync(dl++);
    gDPSetCycleType(dl++, G_CYC_1CYCLE);
    guTranslate(&frame->identity, 0.0f, 0.0f, 0.0f);
    guLookAt(&frame->unk200, 0.0f, 0.0f, 200.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    guPerspective(&frame->perspective, &D_8076A09C, 61.9f, 1.3333334f, 10.0f, 1000.0f, 1.0f);
    gDPPipeSync(dl++);
    dl = gfxSetFrameBufferColorImage(dl);
    gDPSetColorDither(dl++, G_CD_MAGICSQ);
    gDPSetAlphaDither(dl++, G_AD_PATTERN);
    gDPSetScissor(dl++, G_SC_NON_INTERLACE, 10, 10, 309, 229);
    gDPSetFillColor(dl++, 0xFFC1FFC1);
    gSPSetOtherMode(dl++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0);
    gSPClearGeometryMode(dl++, G_ZBUFFER);
    gDPFillRectangle(dl++, 0, 0, gScreenWidth - 1, gScreenHeight - 1);
    gSPPerspNormalize(dl++, D_8076A09C);
    gSPClipRatio(dl++, FRUSTRATIO_2);
    *outDl = dl;
}

extern s32 gTransitionProgress;
extern s32 D_8075506C;
extern MeshVertex *D_807FD9A4;
extern AnimTable *sTransitionAnim;
extern s32 *gFramebuffers[];


void transitionInit(void) {
    switch (gNextGameMode) {
    case 1:
        gTransitionProgress = 0;
        D_8075506C = 0;
        break;
    case 2:
        gTransitionProgress = 0x78;
        break;
    }
    sTransitionMeshAsset = assetLoad(0x13, 1, 1, 1);
    sTransitionFramebufferCopy = heapAlloc(gScreenWidth * gScreenHeight * 2);
    fbCopySetAlpha(sTransitionFramebufferCopy, gFramebuffers[gGfxBufferIndex]);
    meshBlobParse(sTransitionMeshAsset, &sTransitionMesh, &sTransitionAnim, NULL);
    meshComputeVertexRanges(sTransitionMesh);
    D_807FD9A4 = sTransitionMesh->vertices;
    sTransitionMesh->vertices = heapAlloc(sTransitionMesh->vertexCount * sizeof(MeshVertex));
    fbBuildTileTable(sTransitionMesh->tileWidth, sTransitionMesh->tileHeight);
}

typedef struct TransitionDitherMask {
    u16 data[24];
} TransitionDitherMask;

extern TransitionDitherMask D_80755074;

void transitionMaskFramebuffer(u16 *framebuffer) {
    TransitionDitherMask mask = D_80755074;
    s32 i;
    u16 *pixels = framebuffer + 0x9D;
    s32 t = gTransitionProgress - 5;
    s32 count = (t * 0xF0) / 0x50;

    for (i = 0; i < count; i++) {
        pixels[0] = pixels[0] & mask.data[(i & 3) * 6];
        pixels[1] = pixels[1] & mask.data[(i & 3) * 6 + 1];
        pixels[2] = pixels[2] & mask.data[(i & 3) * 6 + 2];
        pixels[3] = pixels[3] & mask.data[(i & 3) * 6 + 3];
        pixels[4] = pixels[4] & mask.data[(i & 3) * 6 + 4];
        pixels[5] = pixels[5] & mask.data[(i & 3) * 6 + 5];
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

extern u8 sTransitionState;

void transitionSetState(u8 state) {
    sTransitionState = state;
}

u8 transitionGetState(void) {
    return sTransitionState;
}

extern s8 gSfxVolume;
extern s32 D_807550A4;


void transitionSetAudioVolume(f32 volumeScale, s32 isGroupActive, s32 *channels) {
    s32 oldPri;
    u16 rawVol;
    u16 scaledVol;
    s32 i;

    rawVol = 25000.0f * volumeScale;
    scaledVol = (f64)(rawVol * gSfxVolume) / 40.0;
    oldPri = osGetThreadPri(0);
    osSetThreadPri(0, 0x1A);
    n_alSndpSetGroupVol(0, scaledVol);
    if (isGroupActive != 0) {
        D_807550A4 = 1;
        n_alSndpSetGroupVol(2, scaledVol);
        if ((sTransitionState == 0) && ((gScreenRenderFlags & 1) || !(gScreenRenderFlags & 0x40))) {
            seqSetChannelVolumeScale(0, volumeScale);
        }
    } else {
        n_alSndpSetGroupVol(3, (f64)(rawVol * gSfxVolume) / 40.0);
        if (D_807550A4 != 0) {
            D_807550A4 = 0;
            n_alSndpSetGroupVol(2, (f64)(gSfxVolume * 25000) / 40.0);
            n_alSndpSetGroupVol(1, (f64)(gSfxVolume * 25000) / 40.0);
        }
    }
    for (i = 0; channels != 0 && channels[i] != 0; i++) {
        seqSetChannelVolumeScale(channels[i], volumeScale);
    }
    if (D_807550A4 && D_807550A4) {} // FAKE: dead read keeps &D_807550A4 from being CSE'd into $v0 for the isGroupActive store
    osSetThreadPri(0, oldPri);
}

typedef struct TransitionChannels {
    s32 a[4];
} TransitionChannels;

extern TransitionChannels D_807550A8;
extern s32 D_807FD9A0;
extern void *sTransitionBarTexture;
extern Gfx D_1000020[];
extern Mtx D_2000000;
extern Mtx D_2000200;



#define TRANS_RAW(pkt, a, b)              \
    {                                    \
        Gfx *_g = (Gfx *)(pkt);          \
        _g->words.w0 = (a);              \
        _g->words.w1 = (b);              \
    }
#define TRANS_MAX(a, b) (((a) > (b)) ? (a) : (b))
#define TRANS_MIN(a, b) (((a) < (b)) ? (a) : (b))

u8 transitionRender(Gfx **gdl, void *asset, u16 *framebuffer) {
    Gfx *glist;
    Gfx *start;
    Gfx *out;
    Mtx *matrix;
    f64 value;
    s8 delta;
    s32 i;
    s32 volume;
    TransitionChannels channels;

    out = *gdl;
    if (gNextGameMode == 1) {
        delta = 3;
    } else {
        delta = -4;
    }
    channels = D_807550A8;
    glist = heapAlloc(0x4800);
    heapFreeDeferred(glist);
    start = glist;
    if (sTransitionSound != 0) {
        if (gNextGameMode == 1) {
            value = (f64)gTransitionProgress - 20.0;
            sTransitionSoundPitch.f = (f32)((0.9 / ((value * 0.001 * value) + 1.0)) + 0.6);
            if (gTransitionProgress < 60) {
                volume = 0x7FFF;
            } else {
                volume = 0x7FFF - (((gTransitionProgress - 60) * 0x7FFF) / 60);
            }
        } else {
            sTransitionSoundPitch.f = (f32)(((1.5 / (((((f32)(120 - gTransitionProgress) - 40.0f)) * 0.001 * (((f32)(120 - gTransitionProgress) - 40.0f))) + 1.0)) + (0.0002 * ((f32)(120 - gTransitionProgress) - 30.0f) * ((f32)(120 - gTransitionProgress) - 30.0f))) - 0.2);
            if ((f32)(120 - gTransitionProgress) < 110.0f) {
                volume = 0x7FFF;
            } else {
                volume = (s32)(32767.0f - (((f32)(120 - gTransitionProgress) - 110.0f) * 32767.0f / 10.0f));
            }
        }
        n_alSndpPostEvent(sTransitionSound, 0x10, sTransitionSoundPitch.bits);
        n_alSndpPostEvent(sTransitionSound, 8, volume);
    }
    {
        f32 progress = (f64)gTransitionProgress / 120.0;
        transitionSetAudioVolume(1.0f - progress, gNextGameMode == 1, channels.a);
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
    for (i = 0; i < sTransitionMesh->vertexCount; i++) {
        sTransitionMesh->vertices[i].x = D_807FD9A4[i].x;
        sTransitionMesh->vertices[i].y = D_807FD9A4[i].y;
        sTransitionMesh->vertices[i].z = D_807FD9A4[i].z;
    }
    meshApplyAnimation(sTransitionMesh, sTransitionAnim, gTransitionProgress);
    if (delta < 0) {
        D_807FD9A0 = ((gTransitionProgress * 0xF0) - 0x960) / 80;
    } else {
        D_807FD9A0 = ((gTransitionProgress * 0xF0) - 0x4B0) / 80;
    }
    if (gTransitionProgress >= 5 && gTransitionProgress < 0x56) {
        transitionMaskFramebuffer(framebuffer);
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
    meshDrawTextured(&glist, sTransitionMesh, framebuffer);
    gTransitionProgress += delta;
    sTransitionBarTexture = assetLoad(0xE, 0x6A - TRANS_MIN(TRANS_MAX((s16)(D_807FD9A0 / 26), 0), 9), 1, 1);
    assetFreeBuffer(sTransitionBarTexture, 0x381, 0x4A);
    gDPPipeSync(glist++);
    gDPSetCycleType(glist++, G_CYC_1CYCLE);
    gDPSetTexturePersp(glist++, G_TP_NONE);
    TRANS_RAW(glist++, 0xFCFFFFFF, 0xFFFCF279);
    gSPSetOtherMode(glist++, G_SETOTHERMODE_L, G_MDSFT_RENDERMODE, 29, 0x5041C8);
    gDPPipeSync(glist++);
    gDPLoadTextureBlock(glist++, sTransitionBarTexture, G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 32, 0, G_TX_WRAP, G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(glist++, 0x260, TRANS_MAX((s16)(D_807FD9A0 << 2), 0), 0x2A0, TRANS_MAX((s16)((D_807FD9A0 + 0x1F) << 2), 0), 0, 0, -((D_807FD9A0 << 2 < 0) ? TRANS_MIN(((s16)(D_807FD9A0 << 2) << 10) >> 7, 0) : 0), 0x400, 0x400);
    gSPEndDisplayList(glist++);
    gSPDisplayList(out++, start);
    *gdl = out;
    if (gTransitionProgress < 0 || (f64)gTransitionProgress > 120.0) {
        n_alSndpStop(sTransitionSound);
    }
    return gTransitionProgress < 0 || (f64)gTransitionProgress > 120.0;
}

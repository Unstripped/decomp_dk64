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

extern u8 gScreenRenderFlags;
extern s16 gScreenWidth;
extern s16 gScreenHeight;
extern u8 gNextGameMode;
extern u8 gGfxBufferIndex;
extern u8 gGameMode;
extern u8 gPrevGameMode;
extern ALBank *gSfxBank;
extern u8 sTransitionStarted;
extern u8 sTransitionRenderDelay;
extern union { f32 f; s32 bits; } sTransitionSoundPitch; // sound pitch, posted as raw event bits
extern struct GfSndState *sTransitionSound;

void transitionStart(mode)
u8 mode;
{
    gPrevGameMode = gGameMode;
    switch (mode) {
    case 2:
        sTransitionSoundPitch.f = 1.0f;
        sTransitionStarted = 0;
        gNextGameMode = 1;
        gGameMode = 6;
        break;
    case 3:
        sTransitionSoundPitch.f = 0.5f;
        sTransitionStarted = 0;
        gNextGameMode = 2;
        gGameMode = 6;
        sTransitionRenderDelay = 2;
        if ((gPrevGameMode == 1) && (gGlobalOverlayFlags & 1)) {
            timerQueueCancel(0);
        }
        break;
    }
    n_alSndpPlay(gSfxBank, 0x1BC, 0x7FFF, 0x3F, 1.0f, 0, &sTransitionSound);
}

/* A texture tile: texel offset into its RGBA16 image (the framebuffer or D_80754FC8), width and height. */
typedef struct TexTile {
    s32 offset;
    s32 width;
    s32 height;
} TexTile;

extern TexTile *gFbTileTable;

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
    s32 groupSlots;
    s32 sum;
    AnimTable *anim;

    if (blob == NULL) {
        return 0;
    }
    if (outMesh == NULL) {
        return 0;
    }
    gFbTileTable = heapAlloc(150 * sizeof(TexTile));
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
        anim = (AnimTable *)(blob->columnEnds + count);
        anim->entries = (AnimEntry *)(anim + 1);
        count = 0;
        while (anim->entries[count++].kind != 0) {
        }
        anim->counts = (s32 *)(anim->entries + count);
        groupSlots = 0;
        while (anim->counts[groupSlots++] != -1) {
        }
        count = 0;
        anim->indices = (u16 **)(anim->counts + groupSlots);
        sum = 0;
        while (anim->counts[count] != -1) {
            anim->indices[count] = (u16 *)(anim->indices + groupSlots) + sum;
            sum += anim->counts[count];
            count++;
        }
        *outAnim = anim;
    }
    if (outEnd != NULL) {
        if (outAnim == NULL) {
            *outEnd = blob->columnEnds + count;
        } else {
            *outEnd = anim->indices + count;
        }
    }
    return 1;
}

s32 meshComputeVertexRanges(MeshBlob *mesh) {
    s32 min;
    s32 cell;
    s32 v;
    s32 max;
    s32 i;
    s32 column;

    cell = 0;
    for (column = 0; mesh->columnCounts[column] != 0; column++) {
        min = mesh->cells[cell].v0;
        max = mesh->cells[cell].v0;
        for (i = 0; i < mesh->columnCounts[column]; i++, cell++) {
            v = mesh->cells[cell].v0;
            if (v > max) max = v; else if (v < min) min = v;
            v = mesh->cells[cell].v1;
            if (v > max) max = v; else if (v < min) min = v;
            v = mesh->cells[cell].v2;
            if (v > max) max = v; else if (v < min) min = v;
        }
        mesh->columnStarts[column] = min;
        mesh->columnEnds[column] = max;
    }
    return 1;
}

/* The solid 4x4 RGBA16 textures in D_80754FC8, drawn by mesh cells with a negative texture index. */
TexTile D_80754F80[] = {
    { 0x00, 4, 4 }, { 0x10, 4, 4 }, { 0x20, 4, 4 }, { 0x30, 4, 4 }, { 0x40, 4, 4 },
};
// Unreferenced: nothing in the ROM points at this display list.
Gfx D_80754FC0[] = {
    gsSPEndDisplayList(),
};
u16 D_80754FC8[] = {
    0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
    0x0843, 0x0843, 0x0843, 0x0843, 0x0843, 0x0843, 0x0843, 0x0843, 0x0843, 0x0843, 0x0843, 0x0843, 0x0843, 0x0843, 0x0843, 0x0843,
    0x7BDF, 0x7BDF, 0x7BDF, 0x7BDF, 0x7BDF, 0x7BDF, 0x7BDF, 0x7BDF, 0x7BDF, 0x7BDF, 0x7BDF, 0x7BDF, 0x7BDF, 0x7BDF, 0x7BDF, 0x7BDF,
    0xC631, 0xC631, 0xC631, 0xC631, 0xC631, 0xC631, 0xC631, 0xC631, 0xC631, 0xC631, 0xC631, 0xC631, 0xC631, 0xC631, 0xC631, 0xC631,
};
s16 func_8070C200(f32);

void meshDrawTextured(Gfx **gdl, MeshBlob *mesh, u16 *framebuffer) {
    Gfx *glist = *gdl;
    s32 j, cell, column, texture, prev, base, count;

    for (j = 0; j < mesh->vertexCount; j++) {
        mesh->screenVerts[gGfxBufferIndex][j].v.ob[0] = func_8070C200(mesh->vertices[j].x);
        mesh->screenVerts[gGfxBufferIndex][j].v.ob[1] = func_8070C200(mesh->vertices[j].y);
        mesh->screenVerts[gGfxBufferIndex][j].v.ob[2] = func_8070C200(mesh->vertices[j].z);
    }
    cell = 0;
    for (column = 0; mesh->columnCounts[column] != 0; column++) {
        prev = -99;
        base = mesh->columnStarts[column];
        count = mesh->columnEnds[column] - base + 1;
        gSPVertex(glist++, osVirtualToPhysical(&mesh->screenVerts[gGfxBufferIndex][base]), count, 0);
        for (j = 0; j < mesh->columnCounts[column]; j++) {
            texture = mesh->cells[cell].texture;
            if (texture != prev) {
                prev = texture;
                if (texture < 0) {
                    texture = -1 - texture;
                    gDPLoadTextureBlock(glist++, D_80754FC8 + D_80754F80[texture].offset, G_IM_FMT_RGBA, G_IM_SIZ_16b, D_80754F80[texture].width, D_80754F80[texture].height - 1, 0, G_TX_WRAP, G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                } else {
                    gDPLoadTextureTile(glist++, framebuffer + gFbTileTable[texture].offset, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, 0, 0, 0, gFbTileTable[texture].width, gFbTileTable[texture].height - 1, 0, G_TX_WRAP, G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                }
            }
            gSPModifyVertex(glist++, mesh->cells[cell].v0 - base, G_MWO_POINT_ST, mesh->cells[cell].st0);
            gSPModifyVertex(glist++, mesh->cells[cell].v1 - base, G_MWO_POINT_ST, mesh->cells[cell].st1);
            gSPModifyVertex(glist++, mesh->cells[cell].v2 - base, G_MWO_POINT_ST, mesh->cells[cell].st2);
            gSP1Triangle(glist++, mesh->cells[cell].v0 - base, mesh->cells[cell].v1 - base, mesh->cells[cell].v2 - base, 0);
            cell++;
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
    s32 clampedFrame;
    MeshVertex *src;
    MeshVertex *dst;
    f32 angle;
    f32 pivotX;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 x;
    f32 y;
    f32 z;
    u32 j;

    idx = 0; // LAYOUT: the init on its own line keeps as1 zeroing idx (s5) before its entry offset (s3); for (idx = 0; ...) swaps the two moves (Q0591)
    for (; table->entries[idx].kind != 0; idx++) {
        clampedFrame = frame;
        if (frame < table->entries[idx].start) {
            continue;
        }
        if (table->entries[idx].end < frame) {
            clampedFrame = table->entries[idx].end;
        }
        switch (table->entries[idx].kind) {
        case 1:
            sidx = table->entries[idx].source;
            didx = table->entries[idx].destination;
            src = &model->vertices[sidx];
            dst = &model->vertices[didx];
            pivotX = src->x;
            dx = dst->x - pivotX;
            dy = dst->y - src->y;
            dz = dst->z - src->z;
            angle = (table->entries[idx].start - clampedFrame) * table->entries[idx].scale;
            mtxLookDirPosF(lookMtx, lookInvMtx,
                -dx, -dy, -dz,
                -pivotX, -src->y, -src->z);
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
extern s32 gGfxListCommandCount;
extern s32 gGfxSubListCommandCount;
extern u8 gGfxSubListEnabled;
extern u8 D_8076A0B2;
extern FrameMatrices gFrameMatrices[];
extern f32 gScreenFadeProgress;
extern MeshBlob *sTransitionMesh;
extern u16 *sTransitionFramebufferCopy;
extern void *sTransitionMeshAsset;

void transitionRunFrame(s32 map, s32 exit) {
    Gfx *dl;
    Gfx *subDl;

    schedSubmitGfxTask(gGfxTaskBuffers[gGfxBufferIndex], gGfxListCommandCount, 3, 1, 1234, 1);
    gGfxBufferIndex ^= 1;
    gFrameCounter++;
    gGfxCurrentFrameBuffer = &gFrameMatrices[gGfxBufferIndex];
    subDl = gGfxCurrentFrameBuffer->subDisplayList;
    switch (sTransitionStarted) {
    case 1:
        break;
    case 0:
        sTransitionStarted = 1;
        transitionInit();
        break;
    }
    if ((gScreenRenderFlags & 1) && (gScreenFadeProgress == 31.0f)) {
        dl = gGfxTaskBuffers[gGfxBufferIndex];
        if (D_8076A0B2 == 1) {
            gGameMode = gPrevGameMode;
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
                gGameMode = gPrevGameMode;
                if ((gGameMode == 1) && (gGlobalOverlayFlags & 1)) {
                    camRestartPath();
                }
                gNextGameMode = 3;
                gScreenFadeProgress = 0.0f;
                break;
            }
        }
    }
    if (sTransitionRenderDelay != 0) {
        sTransitionRenderDelay--;
        if (sTransitionRenderDelay == 0) {
            gScreenRenderFlags |= 2;
        }
    }
    if ((gGfxSubListEnabled != 0) && (gGameMode != 6)) {
        gfxEndDisplayList(dl, gGfxBufferIndex, &gGfxListCommandCount, 0);
        gfxEndSubDisplayList(subDl, gGfxCurrentFrameBuffer, &gGfxSubListCommandCount, 1);
        return;
    }
    gfxEndDisplayList(dl, gGfxBufferIndex, &gGfxListCommandCount, 1);
}

extern void *gSegment1Data;
extern u16 gPerspNorm;
extern Gfx D_1000090[];

void transitionBeginDisplayList(FrameMatrices *frame, Gfx **outDl) {
    Gfx *dl = gGfxTaskBuffers[gGfxBufferIndex];

    gSPSegment(dl++, 0, 0);
    gSPSegment(dl++, 2, osVirtualToPhysical(frame));
    gSPSegment(dl++, 1, osVirtualToPhysical(gSegment1Data));
    gSPDisplayList(dl++, D_1000090);
    dl = gfxClearZBuffer(gfxSetViewportDisplayList(dl));
    gDPPipeSync(dl++);
    gDPSetCycleType(dl++, G_CYC_1CYCLE);
    guTranslate(&frame->identity, 0.0f, 0.0f, 0.0f);
    guLookAt(&frame->unk200, 0.0f, 0.0f, 200.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    guPerspective(&frame->perspective, &gPerspNorm, 61.9f, 1.3333334f, 10.0f, 1000.0f, 1.0f);
    gDPPipeSync(dl++);
    dl = gfxSetFrameBufferColorImage(dl);
    gDPSetColorDither(dl++, G_CD_MAGICSQ);
    gDPSetAlphaDither(dl++, G_AD_PATTERN);
    gDPSetScissor(dl++, G_SC_NON_INTERLACE, 10, 10, 309, 229);
    gDPSetFillColor(dl++, 0xFFC1FFC1);
    gDPSetRenderMode(dl++, G_RM_NOOP, G_RM_NOOP2);
    gSPClearGeometryMode(dl++, G_ZBUFFER);
    gDPFillRectangle(dl++, 0, 0, gScreenWidth - 1, gScreenHeight - 1);
    gSPPerspNormalize(dl++, gPerspNorm);
    gSPClipRatio(dl++, FRUSTRATIO_2);
    *outDl = dl;
}

s32 gTransitionProgress = 0;
s32 sTransitionMeshOffsetY = 0;
extern MeshVertex *sTransitionMeshRestVertices;
extern AnimTable *sTransitionAnim;
extern u16 *gFramebuffers[];

void transitionInit(void) {
    switch (gNextGameMode) {
    case 1:
        gTransitionProgress = 0;
        sTransitionMeshOffsetY = 0;
        break;
    case 2:
        gTransitionProgress = 120;
        break;
    }
    sTransitionMeshAsset = assetLoad(0x13, 1, 1, 1);
    sTransitionFramebufferCopy = heapAlloc(gScreenWidth * gScreenHeight * sizeof(u16));
    fbCopySetAlpha(sTransitionFramebufferCopy, gFramebuffers[gGfxBufferIndex]);
    meshBlobParse(sTransitionMeshAsset, &sTransitionMesh, &sTransitionAnim, NULL);
    meshComputeVertexRanges(sTransitionMesh);
    sTransitionMeshRestVertices = sTransitionMesh->vertices;
    sTransitionMesh->vertices = heapAlloc(sTransitionMesh->vertexCount * sizeof(MeshVertex));
    fbBuildTileTable(sTransitionMesh->tileWidth, sTransitionMesh->tileHeight);
}

u8 sTransitionState = 0;

void transitionMaskFramebuffer(u16 *framebuffer) {
    u16 mask[24] = {
        0xFFFF, 0xFFFE, 0xFFFF, 0xFFFF, 0xFFFE, 0xFFFF,
        0xFFFF, 0xFFFF, 0xFFFF, 0xFFFE, 0xFFFE, 0xFFFE,
        0xFFFF, 0xFFFE, 0xFFFF, 0xFFFF, 0xFFFE, 0xFFFF,
        0xFFFE, 0xFFFE, 0xFFFE, 0xFFFF, 0xFFFF, 0xFFFF,
    };
    s32 i;
    u16 *pixels = framebuffer + 157;
    s32 elapsed = gTransitionProgress - 5;
    s32 count = (elapsed * 240) / 80;

    for (i = 0; i < count; i++) {
        pixels[0] = pixels[0] & mask[(i & 3) * 6];
        pixels[1] = pixels[1] & mask[(i & 3) * 6 + 1];
        pixels[2] = pixels[2] & mask[(i & 3) * 6 + 2];
        pixels[3] = pixels[3] & mask[(i & 3) * 6 + 3];
        pixels[4] = pixels[4] & mask[(i & 3) * 6 + 4];
        pixels[5] = pixels[5] & mask[(i & 3) * 6 + 5];
        pixels += 320;
    }
    for (i = count; i < 240; i++) {
        pixels[0] |= 1;
        pixels[1] |= 1;
        pixels[2] |= 1;
        pixels[3] |= 1;
        pixels[4] |= 1;
        pixels[5] |= 1;
        pixels += 320;
    }
}

void transitionSetState(u8 state) {
    sTransitionState = state;
}

u8 transitionGetState(void) {
    return sTransitionState;
}

extern s8 gSfxVolume;

void transitionSetAudioVolume(f32 volumeScale, s32 isGroupActive, s32 *channels) {
    s32 oldPri;
    u16 rawVol;
    u16 scaledVol;
    s32 i;
    static s32 sGroupVolScaled = 1;

    rawVol = 25000.0f * volumeScale;
    scaledVol = (rawVol * gSfxVolume) / 40.0;
    oldPri = osGetThreadPri(0);
    osSetThreadPri(0, 0x1A);
    n_alSndpSetGroupVol(0, scaledVol);
    if (isGroupActive != 0) {
        sGroupVolScaled = 1;
        n_alSndpSetGroupVol(2, scaledVol);
        if ((sTransitionState == 0) && ((gScreenRenderFlags & 1) || !(gScreenRenderFlags & 0x40))) {
            seqSetChannelVolumeScale(0, volumeScale);
        }
    } else {
        n_alSndpSetGroupVol(3, (rawVol * gSfxVolume) / 40.0);
        if (sGroupVolScaled != 0) {
            sGroupVolScaled = 0;
            n_alSndpSetGroupVol(2, (gSfxVolume * 25000) / 40.0);
            n_alSndpSetGroupVol(1, (gSfxVolume * 25000) / 40.0);
        }
    }
    for (i = 0; channels != NULL && channels[i] != 0; i++) {
        seqSetChannelVolumeScale(channels[i], volumeScale);
    }
    osSetThreadPri(0, oldPri);
}

typedef struct TransitionChannels {
    s32 ids[4];
} TransitionChannels;

/* Sequence channels whose volume follows the transition, 0-terminated. */
TransitionChannels sTransitionChannels = { { 1, 2, 3, 0 } };
extern s32 sTransitionBarY;
extern void *sTransitionBarTexture;
extern Gfx D_1000020[];
extern Mtx D_2000000;
extern Mtx D_2000200;

u8 transitionRender(Gfx **gdl, void *asset, u16 *framebuffer) {
    Gfx *glist;
    Gfx *start;
    Gfx *out;
    Mtx *matrix;
    f64 fromPeak;
    s8 delta;
    s32 i;
    s32 volume;
    TransitionChannels channels;
    f32 progress;

    out = *gdl;
    if (gNextGameMode == 1) {
        delta = 3;
    } else {
        delta = -4;
    }
    channels = sTransitionChannels;
    glist = heapAlloc(0x4800);
    heapFreeDeferred(glist);
    start = glist;
    if (sTransitionSound != NULL) {
        if (gNextGameMode == 1) {
            fromPeak = gTransitionProgress - 20.0;
            sTransitionSoundPitch.f = 0.9 / (fromPeak * 0.001 * fromPeak + 1.0) + 0.6;
            if (gTransitionProgress < 60) {
                volume = 0x7FFF;
            } else {
                volume = 0x7FFF - (((gTransitionProgress - 60) * 0x7FFF) / 60);
            }
        } else {
            sTransitionSoundPitch.f = 1.5 / (((120 - gTransitionProgress) - 40.0f) * 0.001 * ((120 - gTransitionProgress) - 40.0f) + 1.0)
                                    + 0.0002 * ((120 - gTransitionProgress) - 30.0f) * ((120 - gTransitionProgress) - 30.0f) - 0.2;
            if ((120 - gTransitionProgress) < 110.0f) {
                volume = 0x7FFF;
            } else {
                volume = 32767.0f - ((120 - gTransitionProgress) - 110.0f) * 32767.0f / 10.0f;
            }
        }
        n_alSndpPostEvent(sTransitionSound, 0x10, sTransitionSoundPitch.bits);
        n_alSndpPostEvent(sTransitionSound, 8, volume);
    }
    progress = gTransitionProgress / 120.0;
    transitionSetAudioVolume(1.0f - progress, gNextGameMode == 1, channels.ids);
    gDPSetCycleType(glist++, G_CYC_1CYCLE);
    gSPClearGeometryMode(glist++, 0xFFFFFF);
    gSPSetGeometryMode(glist++, G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH);
    gDPSetRenderMode(glist++, G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2);
    gDPSetCombineMode(glist++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gSPTexture(glist++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gDPSetTexturePersp(glist++, G_TP_PERSP);
    gSPDisplayList(glist++, D_1000020);
    gDPPipeSync(glist++);
    for (i = 0; i < sTransitionMesh->vertexCount; i++) {
        sTransitionMesh->vertices[i].x = sTransitionMeshRestVertices[i].x;
        sTransitionMesh->vertices[i].y = sTransitionMeshRestVertices[i].y;
        sTransitionMesh->vertices[i].z = sTransitionMeshRestVertices[i].z;
    }
    meshApplyAnimation(sTransitionMesh, sTransitionAnim, gTransitionProgress);
    if (delta < 0) {
        sTransitionBarY = (gTransitionProgress * 240 - 2400) / 80;
    } else {
        sTransitionBarY = (gTransitionProgress * 240 - 1200) / 80;
    }
    if (gTransitionProgress >= 5 && gTransitionProgress < 86) {
        transitionMaskFramebuffer(framebuffer);
    }
    if (gTransitionProgress >= 109 && gTransitionProgress <= 120.0) {
        sTransitionMeshOffsetY = 220 - gTransitionProgress * 2;
    }
    gSPMatrix(glist++, &D_2000000, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(glist++, &D_2000200, G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);
    gSPPerspNormalize(glist++, gPerspNorm);
    matrix = heapAlloc(sizeof(Mtx));
    heapFreeDeferred(matrix);
    guTranslate(matrix, 0.0f, sTransitionMeshOffsetY, 0.0f);
    gSPMatrix(glist++, matrix, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gDPSetColorDither(glist++, G_CD_DISABLE);
    gDPSetAlphaDither(glist++, G_AD_DISABLE);
    meshDrawTextured(&glist, sTransitionMesh, framebuffer);
    gTransitionProgress += delta;
    sTransitionBarTexture = assetLoad(0xE, 0x6A - MIN(MAX((s16)(sTransitionBarY / 26), 0), 9), 1, 1);
    assetFreeBuffer(sTransitionBarTexture, 0x381, 0x4A);
    gDPPipeSync(glist++);
    gDPSetCycleType(glist++, G_CYC_1CYCLE);
    gDPSetTexturePersp(glist++, G_TP_NONE);
    gDPSetCombineMode(glist++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetRenderMode(glist++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
    gDPPipeSync(glist++);
    gDPLoadTextureBlock(glist++, sTransitionBarTexture, G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 32, 0, G_TX_WRAP, G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPScisTextureRectangle(glist++, 152 << 2, sTransitionBarY << 2, 168 << 2, (sTransitionBarY + 31) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
    gSPEndDisplayList(glist++);
    gSPDisplayList(out++, start);
    *gdl = out;
    if (gTransitionProgress < 0 || gTransitionProgress > 120.0) {
        n_alSndpStop(sTransitionSound);
    }
    return gTransitionProgress < 0 || gTransitionProgress > 120.0;
}

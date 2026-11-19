#include "common.h"
#include "compiler/ido/memory.h"
#include "actor.h"
#include "proto/global/15050.h"
#include "proto/global/17B90.h"
#include "proto/global/19A00.h"
#include "proto/global/61AA0.h"
#include "proto/global/6AD90.h"
#include "proto/global/70FD0.h"
#include "proto/global/8CA50.h"

extern u16 gModelCacheCount;
extern PlayerState *gActivePlayerState;

u8 D_80746B60 = 0;
u8 gDefaultModelBone[0x1C] = { 0xFF };


AnimInitData *controllerAnimStateLoadAsset(actor, assetId, cullSwap)
Actor *actor;
s32 assetId;
unsigned char cullSwap;
{
    s32 i;
    AnimInitData *asset;
    s32 delta;

    for (i = 0; i < gModelCacheCount; i++) {
        if (assetId == gModelCache[i].assetId && gModelCache[i].cullSwap == cullSwap) {
            gModelCache[i].refCount++;
            animListInit(actor, gModelCache[i].asset);
            return gModelCache[i].asset;
        }
    }

    // The original tests the clip cache's count here, not gModelCacheCount.
    if (gAnimClipCacheCount >= 0x20) {
        return gModelCache[0].asset;
    }

    asset = assetLoad(5, assetId - 1, 1, 1);
    gModelCache[i].assetId = assetId;
    gModelCacheCount++;
    gModelCache[i].cullSwap = cullSwap;
    gModelCache[i].refCount = 1;
    gModelCache[i].asset = asset;

    delta = ((u8 *)asset - (u8 *)asset->unk0) + 0x28;
    asset->unk0 = (u8 *)asset->unk0 + delta;
    asset->displayLists = (void **)((u8 *)asset->displayLists + delta);

    for (i = 0; i < asset->displayListCount; i++) {
        asset->displayLists[i] = (u8 *)asset->displayLists[i] + delta;
    }

    if (asset->unk8 != NULL) {
        asset->unk8 = (u8 *)asset->unk8 + delta;
    } else {
        asset->unk8 = gDefaultModelBone;
        asset->boneCount = 1;
    }

    asset->unkC = (u8 *)asset->unkC + delta;
    asset->unk10 = (u8 *)asset->unk10 + delta;

    controllerBuildSubcommandList(*asset->displayLists, asset->displayLists, &asset->segmentNodes);
    renderReplaceSegment6Commands(*asset->displayLists, asset->displayLists);
    controllerCommandRelocateAssets(*asset->displayLists, asset->displayLists);
    animListInit(actor, asset);

    if (cullSwap & 1) {
        gfxSwapGeometryModeCullBits(*asset->displayLists, asset->displayLists);
    }

    return asset;
}

void gfxSwapGeometryModeCullBits(Gfx *cmdStart, void *cmdEnd) {
    s32 command;
    s32 w0;
    s32 w1;
    s32 clear;

    for (; cmdStart != cmdEnd; cmdStart++) {
        command = cmdStart->words.w0 >> 24;
        w0 = cmdStart->words.w0;
        w1 = cmdStart->words.w1;
        if (command == G_GEOMETRYMODE) {
            if (w1 == 0) { // gSPClearGeometryMode: w0 holds ~bits; the rewrites below also set the opcode byte to 0xFF (~clear)
                clear = ~w0 & 0xFFFFFF;
                if ((clear & G_CULL_BOTH) == G_CULL_FRONT) {
                    clear |= G_CULL_BACK;
                    clear &= ~G_CULL_FRONT;
                    cmdStart->words.w0 = ~clear | (G_GEOMETRYMODE << 24);
                } else if ((clear & G_CULL_BOTH) == G_CULL_BACK) {
                    clear |= G_CULL_FRONT;
                    clear &= ~G_CULL_BACK;
                    cmdStart->words.w0 = ~clear | (G_GEOMETRYMODE << 24);
                }
            } else if ((w1 & G_CULL_BOTH) == G_CULL_FRONT) {
                cmdStart->words.w1 |= G_CULL_BACK;
                cmdStart->words.w1 &= ~G_CULL_FRONT;
            } else if ((w1 & G_CULL_BOTH) == G_CULL_BACK) {
                cmdStart->words.w1 |= G_CULL_FRONT;
                cmdStart->words.w1 &= ~G_CULL_BACK;
            }
        }
    }
}

void controllerAnimLoadStateAsset(Actor *actor, s16 assetId) {
    if (actor->stateModel == NULL) {
        actor->stateModel = controllerAnimStateLoadAsset(actor, assetId, 0);
    }
}

void controllerAnimLoadStateAsset1(Actor *actor, s16 assetId) {
    if (actor->stateModel == NULL) {
        actor->stateModel = controllerAnimStateLoadAsset(actor, assetId, 1);
    }
}

void controllerAnimFreeStateAsset(Actor *actor) {
    if (actor->stateModel != NULL) {
        controllerAnimFreeModel(actor, 2);
        actor->stateModel = NULL;
    }
}


typedef struct ControllerSubNode {
    Gfx *partDl;
    Gfx *skipDl;
    u8 segment;
    struct ControllerSubNode *next;
} ControllerSubNode;


void controllerBuildSubcommandList(Gfx *cmdStart, void *cmdEnd, ControllerSubNode **pNodeList) {
    Gfx *curr;
    Gfx *search;
    ControllerSubNode *node;
    u32 segment;
    s32 found;
    u32 op;
    u32 push;

    for (curr = cmdStart; curr != cmdEnd; curr++) {
        op = curr->words.w0 >> 24;
        push = (curr->words.w0 >> 16) & 0xFF;
        if ((op == G_DL) && (push == G_DL_NOPUSH)) {
            segment = (curr->words.w1 << 4) >> 28;
            search = cmdStart;
            found = 0;
            while (!found && (search != cmdEnd)) {
                op = search->words.w0 >> 24;
                if ((op == G_NOOP) && (segment == search->words.w1)) {
                    found = 1;
                } else {
                    search++;
                }
            }
            node = heapAlloc(sizeof(ControllerSubNode));
            *pNodeList = node;
            pNodeList = &node->next;
            node->segment = segment;
            node->partDl = curr + 1;
            node->skipDl = search;
        }
    }
    *pNodeList = NULL;
}


void controllerSetCommand(Actor *actor, s32 commandIndex, Gfx *command) {
    Gfx *commands;
    Gfx *destination;

    if (actor->flags & 0x10) {
        return;
    }
    commands = ((AnimInitData *)actor->animState)->displayLists[0];
    destination = commands + commandIndex;
    if ((command->words.w0 != destination->words.w0) || (command->words.w1 != destination->words.w1)) {
        memcpy(destination, command, sizeof(Gfx));
    }
}

void controllerCommandRelocateAssets(Gfx *cmdStart, void *cmdEnd) {
    u32 op;

    for (; cmdStart != cmdEnd; cmdStart++) {
        op = cmdStart->words.w0 >> 24;
        if (op == G_SETTIMG) {
            if (((cmdStart->words.w1 << 4) >> 28) == 0) {
                cmdStart->words.w1 = (u32)assetLoad(0x19, cmdStart->words.w1, 0, 0);
            }
        }
    }
}

s32 controllerLookupModelAssetId(Actor *actor) {
    void *model = actor->animState;
    s32 i;
    for (i = gModelCacheCount; i >= 0; i--) {
        if (model == gModelCache[i].asset) {
            break;
        }
    }
    if (i >= 0) {
        return gModelCache[i].assetId;
    }
    return 0;
}

// The block controllerAnimInit allocates for an actor's animation state; two arrays of
// boneCount bone matrices (one per gfx buffer) follow it.
typedef struct AnimStateBlock {
    /* 0x00 */ ActorSub4 anim;
    /* 0x90 */ AnimSlot slots[4];
} AnimStateBlock; // size = 0x170

s32 controllerAnimInit(Actor *actor, u16 assetId) {
    AnimInitData *model;
    s32 i;
    AnimStateBlock *block;
    ActorSub4 *anim;
    model = controllerAnimStateLoadAsset(actor, assetId, 0);
    if (model != NULL) {
        actor->animState = model;
        actor->overrideModel = NULL;
        actor->stateModel = NULL;

        block = heapAlloc(sizeof(AnimStateBlock) + model->boneCount * (2 * sizeof(Mtx)));
        actor->sub4 = &block->anim;
        actor->sub4->model = &block->slots[0];
        actor->sub4->layer = &block->slots[1];
        actor->sub4->blendFrom = &block->slots[2];
        actor->sub4->blendFromLayer = &block->slots[3];
        actor->sub4->boneMtx[0] = (Mtx *)(block + 1);
        actor->sub4->boneMtx[1] = actor->sub4->boneMtx[0] + model->boneCount;

        for (i = 0; i < model->boneCount; i++) {
            guMtxIdent(&actor->sub4->boneMtx[0][i]);
            guMtxIdent(&actor->sub4->boneMtx[1][i]);
        }

        guMtxIdentF(actor->modelMtx);
        anim = actor->sub4;
        anim->boneRotations = NULL;
        anim->boneScales = NULL;
        anim->boneOffsets = NULL;
        anim->scaleX = 0.15f;
        anim->scaleY = 0.15f;
        anim->scaleZ = 0.15f;
        anim->model->frame = 0.0f;
        anim->model->frameFrac = 0.0f;
        anim->model->clip = NULL;
        anim->model->animId = -1;
        anim->model->flags = 0;
        anim->model->firstFrame = 0.0f;
        anim->model->lastFrame = 0.0f;
        anim->model->speed = 1.0f;
        anim->model->speedRampDuration = 0.0f;

        anim->layer->clip = NULL;
        anim->layer->speedRampDuration = 0.0f;
        anim->blendFrom->clip = NULL;
        anim->blendFrom->speedRampDuration = 0.0f;
        anim->blendFromLayer->clip = NULL;
        anim->blendFromLayer->speedRampDuration = 0.0f;

        anim->scriptStart = NULL;
        anim->animId = 0;
        anim->scriptCommand = NULL;
        anim->scriptWaitFlags = 0;
        anim->loopCount = 0;
        anim->waitOnLayer = 0;
        anim->scriptResult = 0;

        anim->blendWeight = 0.0f;
        anim->blendDuration = 0.0f;
        anim->speedRampDuration = 0.0f;
        anim->unk48 = 1.0f;
        anim->waitFrame = 0.0;

        return 1;
    }
    return 0;
}

void controllerAnimFree(Actor *actor) {
    BoneRotation *rotations;
    BoneVector *scales;
    BoneVector *offsets;

    controllerAnimFreeModel(actor, 0);
    controllerAnimFreeModel(actor, 1);
    controllerAnimFreeModel(actor, 2);
    animListFree(&actor->animList);
    controllerAnimCacheFree(actor, actor->sub4->model);
    controllerAnimCacheFree(actor, actor->sub4->layer);
    controllerAnimCacheFree(actor, actor->sub4->blendFrom);
    controllerAnimCacheFree(actor, actor->sub4->blendFromLayer);
    rotations = actor->sub4->boneRotations;
    if (rotations != NULL) {
        heapFreeDeferred(rotations);
    }
    scales = actor->sub4->boneScales;
    if (scales != NULL) {
        heapFreeDeferred(scales);
    }
    offsets = actor->sub4->boneOffsets;
    if (offsets != NULL) {
        heapFreeDeferred(offsets);
    }
    heapFreeDeferred(actor->sub4);
}

void controllerAnimFreeModel(Actor *actor, u8 modelIndex) {
    AnimInitData *model;
    Gfx *cmd;
    void *dlEnd;
    u32 op;
    s32 i;
    switch (modelIndex) {
    case 0:
        model = actor->animState;
        actor->animState = NULL;
        break;
    case 1:
        model = actor->overrideModel;
        actor->overrideModel = NULL;
        break;
    case 2:
        model = actor->stateModel;
        actor->stateModel = NULL;
        break;
    }

    if (model != NULL) {
        for (i = 0; i < 32; i++) {
            if (gModelCache[i].asset == model) {
                break;
            }
        }
        if (i == 32) {
            return;
        }
        if (--gModelCache[i].refCount == 0) {
            dlEnd = model->displayLists;
            for (cmd = model->displayLists[0]; cmd != dlEnd; cmd++) {
                op = cmd->words.w0 >> 24;
                if (op == G_SETTIMG) {
                    if (IS_KSEG0(cmd->words.w1)) {
                        assetFreeBuffer((void *)cmd->words.w1, 0x270, 0x15);
                    }
                }
            }

            gModelCacheCount--;
            gModelCache[i].assetId = gModelCache[gModelCacheCount].assetId;
            gModelCache[i].asset = gModelCache[gModelCacheCount].asset;
            gModelCache[i].cullSwap = gModelCache[gModelCacheCount].cullSwap;
            gModelCache[i].refCount = gModelCache[gModelCacheCount].refCount;

            gModelCache[gModelCacheCount].assetId = 0;
            gModelCache[gModelCacheCount].asset = NULL;
            gModelCache[gModelCacheCount].cullSwap = 0;
            gModelCache[gModelCacheCount].refCount = 0;

            assetFreeBuffer(model, 0x281, 0x15);
        }
    }
}

void controllerAnimCacheFree(Actor *actor, AnimSlot *slot) {
    AnimClip *clip;
    s32 i;

    clip = slot->clip;
    if (clip != NULL) {
        for (i = 0; i < gAnimClipCacheCount; i++) {
            if (clip == gAnimClipCache[i].asset) {
                if (--gAnimClipCache[i].refCount == 0) {
                    assetFreeBuffer(gAnimClipCache[i].asset, 0x298, 0x15);
                    gAnimClipCacheCount--;
                    gAnimClipCache[i].id = gAnimClipCache[gAnimClipCacheCount].id;
                    gAnimClipCache[i].asset = gAnimClipCache[gAnimClipCacheCount].asset;
                    gAnimClipCache[i].refCount = gAnimClipCache[gAnimClipCacheCount].refCount;
                    gAnimClipCache[gAnimClipCacheCount].id = 0xFFFF;
                    gAnimClipCache[gAnimClipCacheCount].asset = NULL;
                    gAnimClipCache[gAnimClipCacheCount].refCount = 0;
                }
                break;
            }
        }
        slot->clip = NULL;
    }
    if (slot == actor->sub4->layer) {
        actor->sub4->waitOnLayer = 0;
    }
}

void controllerAnimScaleInterpolate(Actor *actor, s8 offset) {
    f32 frame;
    s16 modelFrames = (s32)((actor->sub4->model->lastFrame - actor->sub4->model->firstFrame) + 1.0f);
    s16 blendFrames = (s32)((actor->sub4->blendFrom->lastFrame - actor->sub4->blendFrom->firstFrame) + 1.0f);
    frame = actor->sub4->blendFrom->frame * modelFrames / blendFrames;
    frame += offset;
    controllerApplyMotionWindow(actor, actor->sub4->model, frame);
}

extern u16 *gActorScriptAnimTable;

void controllerAnimSetStateRemap(Actor *actor, s16 animIndex, f32 animSpeed, f32 blend) {
    s16 keepLayer;
    s32 tableIndex;
    if (animIndex >= 0) {
        keepLayer = animIndex & 0x4000;
        animIndex -= keepLayer;
        gActivePlayerState->unk4E = animIndex;
        tableIndex = (animIndex * 7 + actor->actorType - 2) & 0xFFFF;
        animIndex = gActorScriptAnimTable[tableIndex] + keepLayer;
    } else {
        gActivePlayerState->unk4E = animIndex;
    }
    controllerAnimSetStateIfChanged(actor, animIndex, animSpeed, blend);
}


void controllerAnimSetStateRemapDirect(Actor *actor, s16 animIndex, f32 animSpeed, f32 blend) {
    s16 keepLayer;
    s32 tableIndex;
    if (animIndex >= 0) {
        keepLayer = animIndex & 0x4000;
        animIndex -= keepLayer;
        gActivePlayerState->unk4E = animIndex;
        tableIndex = (animIndex * 7 + actor->actorType - 2) & 0xFFFF;
        animIndex = gActorScriptAnimTable[tableIndex] + keepLayer;
    } else {
        gActivePlayerState->unk4E = animIndex;
    }
    controllerAnimSetState(actor, animIndex, animSpeed, blend);
}

void controllerAnimSetStateIfChanged(Actor *actor, s16 animId, f32 animSpeed, f32 blend) {
    AnimSlot *slot;

    slot = actor->sub4->model;
    if (animId == slot->animId) {
        slot->speed = slot->clip->speed;
        return;
    }
    controllerAnimSetState(actor, animId, animSpeed, blend);
}

void controllerAnimSetState(Actor *actor, s16 animId, f32 animSpeed, f32 blend) {
    void *pad;
    ActorSub4 *anim;
    AnimSlot *oldModel;
    AnimSlot *oldLayer;
    AnimSlot *newModel;
    AnimSlot *newLayer;
    AnimClip *clip;
    f32 speed;
    u8 oldLayerWeight;

    anim = actor->sub4;
    oldModel = anim->model;
    newModel = anim->blendFrom;
    oldLayer = anim->layer;
    newLayer = anim->blendFromLayer;

    if (newModel->clip != NULL) {
        controllerAnimCacheFree(actor, newModel);
    }
    if (newLayer->clip != NULL) {
        controllerAnimCacheFree(actor, newLayer);
    }

    if ((animId & 0x4000) == 0x4000) {
        animId -= 0x4000;
        if (oldLayer->clip != NULL) {
            newLayer->clip = controllerAnimCacheGetOrLoad(oldLayer->animId);
            newLayer->frame = oldLayer->frame;
            newLayer->frameFrac = oldLayer->frameFrac;
            newLayer->frameIndex = oldLayer->frameIndex;
            newLayer->nextFrameIndex = oldLayer->nextFrameIndex;
            newLayer->animId = oldLayer->animId;
            newLayer->flags = oldLayer->flags;
            newLayer->firstFrame = oldLayer->firstFrame;
            newLayer->lastFrame = oldLayer->lastFrame;
            newLayer->speedRampDuration = oldLayer->speedRampDuration;
            newLayer->speed = oldLayer->speed;
            newLayer->speedTo = oldLayer->speedTo;
            newLayer->speedFrom = oldLayer->speedFrom;
            newLayer->speedRampTime = oldLayer->speedRampTime;
            anim->blendFromLayerWeight = anim->layerWeight;
        } else {
            anim->blendFromLayerWeight = 0;
        }
    }

    if (blend > 0.0f) {
        speed = anim->unk48;
        if (speed > 0) {
            anim->blendTime = speed;
        } else {
            anim->blendTime = -speed;
        }
        if (anim->blendTime < blend) {
            anim->blendDuration = blend;
        } else {
            anim->blendDuration = anim->blendTime;
        }
        anim->blendWeight = (anim->blendDuration - anim->blendTime) / anim->blendDuration;
    } else {
        if (oldModel->clip != NULL) {
            controllerAnimCacheFree(actor, oldModel);
        }
        if (oldLayer->clip != NULL) {
            controllerAnimCacheFree(actor, oldLayer);
        }
    }

    clip = controllerAnimCacheGetOrLoad(animId);
    if (clip != NULL) {
        newModel->clip = clip;
        newModel->animId = animId;
        newModel->flags = clip->flags;
        newModel->firstFrame = 0.0f;
        newModel->lastFrame = clip->frameCount - 1;
        newModel->speedRampDuration = 0.0f;
        newModel->speed = clip->speed;
        newModel->speedTo = clip->speed;
        newModel->speedFrom = clip->speed;
        newModel->speedRampTime = 0.0f;
    } else {
        newModel->clip = NULL;
        newModel->animId = -1;
        newModel->flags = 0;
        newModel->firstFrame = 0.0f;
        newModel->lastFrame = 0.0;
        newModel->speedRampDuration = 0.0f;
        newModel->speed = 0.0f;
        newModel->speedTo = 0.0f;
        newModel->speedFrom = 0.0f;
        newModel->speedRampTime = 0.0f;
    }

    anim->scriptWaitFlags = 0;
    anim->loopCount = 0;
    anim->waitFrame = 0.0;
    anim->blendFrom = oldModel;
    oldLayerWeight = anim->layerWeight;
    anim->blendFromLayer = oldLayer;
    anim->model = newModel;
    anim->layer = newLayer;
    anim->layerWeight = anim->blendFromLayerWeight;
    anim->blendFromLayerWeight = oldLayerWeight;
    controllerApplyMotionWindow(actor, newModel, animSpeed);
}

void controllerAnimSetFromTable(Actor *actor, u16 animIndex, f32 animSpeed, u8 flags) {
    u16 tableIndex = animIndex * 7 + actor->actorType - 2;

    animIndex = gActorScriptAnimTable[tableIndex];
    controllerAnimSetDirect(actor, animIndex, animSpeed, flags);
}

void controllerAnimSetDirect(Actor *actor, u16 animId, f32 animSpeed, u8 flags) {
    AnimSlot *slot;
    AnimClip *clip;

    slot = actor->sub4->layer;
    if (slot->clip != NULL) {
        controllerAnimCacheFree(actor, slot);
    }
    clip = controllerAnimCacheGetOrLoad(animId);
    if (clip != NULL) {
        slot->clip = clip;
        slot->animId = animId;
        slot->flags = clip->flags;
        slot->firstFrame = 0.0f;
        slot->lastFrame = clip->frameCount - 1;
        slot->speedRampDuration = 0.0f;
        slot->speed = clip->speed;
        slot->speedTo = clip->speed;
        slot->speedFrom = clip->speed;
        slot->speedRampTime = 0.0f;
        actor->sub4->layerWeight = 0;
        actor->sub4->layerWeightTarget = 0xFF;
        actor->sub4->layerWeightStep = flags;
    } else {
        slot->clip = NULL;
        slot->animId = -1;
        slot->flags = 0;
        slot->firstFrame = 0.0f;
        slot->speedRampDuration = 0.0f;
        slot->speed = 0.0f;
        slot->speedTo = 0.0f;
        slot->speedFrom = 0.0f;
        slot->speedRampTime = 0.0f;
        slot->lastFrame = 0;
    }
    controllerApplyMotionWindow(actor, slot, animSpeed);
}

AnimClip *controllerAnimCacheGetOrLoad(s32 id) {
    AnimCacheEntry *entry;
    u32 i;
    AnimClip *clip;
    s32 count;
    s32 slot;

    if (id < 0) {
        return NULL;
    }

    count = gAnimClipCacheCount;
    i = 0;
    if (count != 0) {
        entry = gAnimClipCache;
        do {
            if (id == entry->id) {
                entry->refCount++;
                return entry->asset;
            }
            entry++;
        } while (++i < count);
    }

    if (gAnimClipCacheCount >= 0x20) {
        return NULL;
    }

    clip = assetLoad(0xB, id, 1, 1);
    clip->unk6 += 6;
    slot = gAnimClipCacheCount;
    entry = &gAnimClipCache[slot];
    entry->asset = clip;
    entry->refCount++;
    gAnimClipCacheCount = slot + 1;
    entry->id = id;
    return clip;
}

extern u32 gFrameDelta;

void controllerStepMotionWindows(Actor *actor) {
    ActorSub4 *anim;
    AnimSlot *model;
    AnimSlot *layer;
    AnimSlot *blendFrom;
    AnimSlot *blendFromLayer;
    f32 frame;
    f32 rate;
    f32 step;

    anim = actor->sub4;
    model = anim->model;
    layer = anim->layer;
    blendFrom = anim->blendFrom;
    blendFromLayer = anim->blendFromLayer;
    frame = model->frame;
    if (anim->motionFlags & 1) {
        rate = gFrameDelta * 0.5;
    } else {
        rate = 1.0f;
    }
    anim->motionFlags &= ~1;
    if (D_80746B60 == 0) {
        anim->motionFlags |= (anim->model->flags & 1);
    }
    if (anim->speedRampDuration > 0.0f) {
        anim->speedRampTime += rate;
        if (anim->speedRampTime < anim->speedRampDuration) {
            anim->unk48 = anim->speedFrom + (((anim->speedTo - anim->speedFrom) * anim->speedRampTime) / anim->speedRampDuration);
        } else {
            anim->speedRampDuration = 0.0f;
            anim->unk48 = anim->speedTo;
        }
    }
    step = anim->unk48 * rate;
    if (model->speedRampDuration > 0.0f) {
        model->speedRampTime += (step > 0) ? step : -step;
        if (model->speedRampTime < model->speedRampDuration) {
            model->speed = model->speedFrom + (((model->speedTo - model->speedFrom) * model->speedRampTime) / model->speedRampDuration);
        } else {
            model->speedRampDuration = 0.0f;
            model->speed = model->speedTo;
        }
    }
    if (layer->speedRampDuration > 0.0f) {
        layer->speedRampTime += (step > 0) ? step : -step;
        if (layer->speedRampTime < layer->speedRampDuration) {
            layer->speed = layer->speedFrom + (((layer->speedTo - layer->speedFrom) * layer->speedRampTime) / layer->speedRampDuration);
        } else {
            layer->speedRampDuration = 0.0f;
            layer->speed = layer->speedTo;
        }
    }
    if (blendFrom->clip != NULL) {
        anim->blendTime += (step > 0) ? step : -step;
        if (anim->blendTime < anim->blendDuration) {
            anim->blendWeight = (anim->blendDuration - anim->blendTime) / anim->blendDuration;
        } else {
            controllerAnimCacheFree(actor, blendFrom);
            controllerAnimCacheFree(actor, blendFromLayer);
            anim->scriptWaitFlags &= ~0x10;
        }
        frame += ((step * model->speed) / 2) * (1.0f - anim->blendWeight);
    } else {
        frame += step * model->speed;
    }
    controllerApplyMotionWindow(actor, model, frame);
    if (layer->clip != NULL) {
        if (anim->layerWeight < anim->layerWeightTarget) {
            anim->layerWeight += anim->layerWeightStep;
            if (anim->layerWeight > anim->layerWeightTarget) {
                anim->layerWeight = anim->layerWeightTarget;
            }
        } else if (anim->layerWeight > anim->layerWeightTarget) {
            anim->layerWeight -= anim->layerWeightStep;
            if (anim->layerWeight < anim->layerWeightTarget) {
                anim->layerWeight = anim->layerWeightTarget;
            }
        }
        frame = layer->frame + layer->speed;
        controllerApplyMotionWindow(actor, layer, frame);
        if ((layer->speed == 0) && (layer->flags & 0x10)) {
            anim->layerWeightTarget = 0;
            if (anim->layerWeight == 0) {
                controllerAnimCacheFree(actor, layer);
            }
        }
    }
    actorScriptExecute(actor);
}

void controllerApplyMotionWindow(Actor *actor, AnimSlot *slot, f32 frame) {
    f32 diff;
    f32 waitFrame;
    f32 prevFrame;
    f32 firstFrame;
    f32 lastFrame;
    s16 frameIndex;
    s32 loopCount;
    s32 pad;
    AnimSlot *watched;
    s32 wrapped;
    s32 bounced;
    s32 waitFlags;
    u16 flags;
    ActorSub4 *anim;

    anim = actor->sub4;
    flags = slot->flags;
    firstFrame = slot->firstFrame;
    lastFrame = slot->lastFrame;
    wrapped = 0;
    bounced = 0;
    if (anim->waitOnLayer != 0) {
        watched = anim->layer;
    } else {
        watched = anim->model;
    }
    if (flags & 8) {
        diff = frame - slot->jumpFrom;
        if (diff > 0) {
            slot->frameFrac = diff;
        } else {
            slot->frameFrac = -diff;
        }
        if (slot->frameFrac < 1.0) {
            slot->frame = frame;
            slot->frameIndex = slot->jumpFrom;
            slot->nextFrameIndex = slot->jumpTo;
            return;
        }
        frame += (slot->jumpTo - slot->jumpFrom) - (s32)diff;
        slot->flags &= ~8;
        if (slot == watched) {
            anim->scriptWaitFlags &= ~0x20;
        }
    }
    if (flags & 4) {
        if (lastFrame < frame) {
            bounced = 1;
            frame = (2 * lastFrame) - frame;
        } else if (frame < firstFrame) {
            bounced = 1;
            wrapped = 1;
            frame = (2 * firstFrame) - frame;
        }
        if (bounced != 0) {
            slot->speed = 0.0f - slot->speed;
            if (slot->speedRampDuration != 0) {
                slot->speedTo = 0.0f - slot->speedTo;
                slot->speedFrom = 0.0f - slot->speedFrom;
            }
            if (slot == watched) {
                anim->scriptWaitFlags &= ~4;
            }
        }
    } else if (flags & 2) {
        if (lastFrame + 1.0 <= frame) {
            wrapped = 1;
            frame -= (1.0f + lastFrame) - firstFrame;
        } else if (frame < firstFrame) {
            wrapped = 1;
            frame += (1.0f + lastFrame) - firstFrame;
        }
    } else if (lastFrame <= frame) {
        frame = lastFrame;
        if (slot->speed >= 0.0f) {
            slot->speed = 0.0f;
            slot->speedRampDuration = 0.0f;
            wrapped = 1;
        }
    } else if (frame < firstFrame) {
        frame = firstFrame;
        wrapped = 1;
        if (slot->speed <= 0.0f) {
            slot->speed = 0.0f;
            slot->speedRampDuration = 0.0f;
        }
    }
    if (slot == watched) {
        waitFlags = anim->scriptWaitFlags;
        if (waitFlags & 0x3F) {
            if (wrapped != 0) {
                loopCount = anim->loopCount;
                anim->scriptWaitFlags = waitFlags & ~1;
                if (loopCount != 0) {
                    anim->loopCount = loopCount - 1;
                    waitFlags = anim->scriptWaitFlags;
                } else {
                    anim->scriptWaitFlags &= ~2;
                    waitFlags = anim->scriptWaitFlags;
                }
            }
            if (waitFlags & 8) {
                waitFrame = anim->waitFrame;
                prevFrame = slot->frame;
                if (frame == waitFrame) {
                    if (prevFrame != waitFrame) {
                        anim->scriptWaitFlags = waitFlags & ~8;
                    }
                } else if (waitFrame < frame) {
                    if ((prevFrame < waitFrame) && (wrapped == 0)) {
                        anim->scriptWaitFlags = waitFlags & ~8;
                    } else if ((waitFrame < prevFrame) && (wrapped != 0)) {
                        anim->scriptWaitFlags = waitFlags & ~8;
                    }
                } else if ((waitFrame < prevFrame) && (wrapped == 0)) {
                    anim->scriptWaitFlags = waitFlags & ~8;
                } else if ((prevFrame < waitFrame) && (wrapped != 0)) {
                    anim->scriptWaitFlags = waitFlags & ~8;
                }
            }
        }
    }
    slot->frame = frame;
    slot->frameIndex = (s16) frame;
    frameIndex = slot->frameIndex;
    slot->nextFrameIndex = frameIndex + 1;
    slot->frameFrac = frame - frameIndex;
    if (lastFrame < slot->nextFrameIndex) {
        if (flags & 2) {
            slot->nextFrameIndex = (s16) firstFrame;
            return;
        }
        slot->nextFrameIndex = frameIndex;
    }
}


f32 actorGetAnimProgress(Actor *actor) {
    return actor->sub4->model->frame;
}

extern u8 gGfxBufferIndex;
void actorBuildBoneMatrices(Actor *);
void actorCheckWorldBounds(Actor *actor) {
    f32 x = actor->x;
    if (x >= -8192.0f) {
        f32 y = actor->y;
        if (y >= -8192.0f) {
            f32 z = actor->z;
            if ((z >= -8192.0f) && (x <= 8192.0f) && (y <= 8192.0f) && (z <= 8192.0f)) {
                actor->boneMtx = actor->sub4->boneMtx[gGfxBufferIndex];
                actorBuildBoneMatrices(actor);
                actorTouchSub140Timestamp(actor);
                actor->flags |= 0x200;
            }
        }
    }
}

Gfx *renderActorDisplayList(Gfx *gdl, Actor *actor) {
    AnimInitData *model = actor->animState;
    s32 i;

    if (actor->overrideModel != NULL) {
        model = actor->overrideModel;
    }
    if (actor->stateModel != NULL) {
        model = actor->stateModel;
    }
    gdl = animSetSegments(gdl, actor);
    gdl = renderEmitSegmentNodes(gdl, actor, model);
    gSPSegment(gdl++, 4, osVirtualToPhysical(actor->boneMtx));
    gSPSegment(gdl++, 3, osVirtualToPhysical(model->unk0));
    for (i = 0; i < model->displayListCount; i++) {
        gSPDisplayList(gdl++, model->displayLists[i]);
    }
    return gdl;
}

Gfx *renderEmitSegmentNodes(Gfx *gdl, Actor *actor, AnimInitData *model) {
    u16 flags = actor->segmentFlags;
    ControllerSubNode *node = model->segmentNodes;
    s32 shift;

    while (node != NULL) {
        shift = (node->segment - 7) & 0xFF;
        if ((flags >> shift) & 1) {
            gSPSegment(gdl++, node->segment, osVirtualToPhysical(node->partDl));
        } else {
            gSPSegment(gdl++, node->segment, osVirtualToPhysical(node->skipDl));
        }
        node = node->next;
    }
    return gdl;
}

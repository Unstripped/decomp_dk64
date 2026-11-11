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

extern u16 D_807FBB30;
extern u16 D_807FBB32;
extern PlayerState *gActivePlayerState;

typedef struct ControllerStateEntryView {
    u16 unk0;
    u16 unk2;
    void *unk4;
    u8 unk8;
} ControllerStateEntryView;

typedef struct ControllerStateEntry {
    u16 unk0;
    u16 unk2;
    u32 unk4;
    u32 unk8;
} ControllerStateEntry;

extern ControllerStateEntry D_807FB630[];
// Users needing a u8 unk8 go through CONTROLLER_STATE_ENTRY.
#define CONTROLLER_STATE_ENTRY(i) (((ControllerStateEntryView *)D_807FB630)[i])
extern void *D_807FB634;
extern u8 D_80746B64[];


void *controllerAnimStateLoadAsset(controller, assetId, cullSwap)
void *controller;
s32 assetId;
unsigned char cullSwap;
{
    s32 i;
    AnimInitData *asset;
    s32 delta;

    for (i = 0; i < D_807FBB30; i++) {
        if (assetId == CONTROLLER_STATE_ENTRY(i).unk0 && CONTROLLER_STATE_ENTRY(i).unk8 == cullSwap) {
            CONTROLLER_STATE_ENTRY(i).unk2++;
            animListInit(controller, CONTROLLER_STATE_ENTRY(i).unk4);
            return CONTROLLER_STATE_ENTRY(i).unk4;
        }
    }

    if (D_807FBB32 >= 0x20) {
        return D_807FB634;
    }

    asset = assetLoad(5, assetId - 1, 1, 1);
    CONTROLLER_STATE_ENTRY(i).unk0 = assetId;
    D_807FBB30++;
    CONTROLLER_STATE_ENTRY(i).unk8 = cullSwap;
    CONTROLLER_STATE_ENTRY(i).unk2 = 1;
    CONTROLLER_STATE_ENTRY(i).unk4 = asset;

    delta = ((u8 *)asset - (u8 *)asset->unk0) + 0x28;
    asset->unk0 = (u8 *)asset->unk0 + delta;
    asset->unk4 = (void **)((u8 *)asset->unk4 + delta);

    for (i = 0; i < asset->unk21; i++) {
        asset->unk4[i] = (u8 *)asset->unk4[i] + delta;
    }

    if (asset->unk8 != NULL) {
        asset->unk8 = (u8 *)asset->unk8 + delta;
    } else {
        asset->unk8 = D_80746B64;
        asset->unk20 = 1;
    }

    asset->unkC = (u8 *)asset->unkC + delta;
    asset->unk10 = (u8 *)asset->unk10 + delta;

    controllerBuildSubcommandList(*asset->unk4, asset->unk4, &asset->unk14);
    renderReplaceSegment6Commands(*asset->unk4, asset->unk4);
    controllerCommandRelocateAssets(*asset->unk4, asset->unk4);
    animListInit(controller, asset);

    if (cullSwap & 1) {
        gfxSwapGeometryModeCullBits(*asset->unk4, asset->unk4);
    }

    return asset;
}

typedef struct GfxCmdWords {
    u32 unk0;
    u32 unk4;
} GfxCmdWords;
void gfxSwapGeometryModeCullBits(GfxCmdWords *cmdStart, void *cmdEnd) {
    u32 command;
    u32 op;
    u32 w0;
    u32 w1;

    op = 0; // FAKE: orders the mask candidate before the command-word candidate
    if (cmdStart != cmdEnd) {
        do {
            w0 = cmdStart->unk0;
            command = w0 >> 24;
            if ((w0 & 0x600) && (w0 & 0x600)) {} // FAKE: preserves the cull-mask expression's live range
            w1 = cmdStart->unk4;
            if (command == 0xD9) {
                if (cmdStart->unk4 == 0) {
                    w0 = ~w0 & 0xFFFFFF;
                    if ((w0 & 0x600) == 0x200) {
                        op = w0 | 0x400;
                        w0 = 0; // FAKE: prevents forwarding the mask expression out of op
                        op = (s32)op & ~0x200;
                        cmdStart->unk0 = ~op | 0xD9000000;
                    } else if ((w0 & 0x600) == 0x400) {
                        op = w0 | 0x200;
                        w0 = 0; // FAKE: prevents forwarding the mask expression out of op
                        op = (s32)op & ~0x400;
                        cmdStart->unk0 = ~op | 0xD9000000;
                    }
                } else {
                    op = w1 & 0x600;
                    if (op == 0x200) {
                        cmdStart->unk4 |= 0x400;
                        cmdStart->unk4 &= ~0x200;
                    } else if ((op | 0) == 0x400) { // FAKE: preserves comparison operand order
                        cmdStart->unk4 |= 0x200;
                        cmdStart->unk4 &= ~0x400;
                    }
                }
            }
            if (command && command) {} // FAKE: retains the opcode variable rather than a forwarded shift
        } while (++cmdStart != cmdEnd);
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
        controllerAnimFreeSub(actor, 2);
        actor->stateModel = NULL;
    }
}

typedef struct ControllerSubCmd {
    u32 unk0;
    u32 unk4;
} ControllerSubCmd;

typedef struct ControllerSubNode {
    ControllerSubCmd *unk0;
    ControllerSubCmd *unk4;
    u8 unk8;
    struct ControllerSubNode *next;
} ControllerSubNode;


void controllerBuildSubcommandList(ControllerSubCmd *cmdStart, void *cmdEnd, ControllerSubNode **pNodeList) {
    ControllerSubCmd *curr;
    ControllerSubCmd *search;
    ControllerSubNode *node;
    u32 cmd0;
    u32 id;
    s32 found;
    u32 op;
    u32 sub;
    u32 search_cmd;
    curr = cmdStart;
    if (cmdStart != cmdEnd) {
        do {
            cmd0 = curr->unk0;
            op = cmd0 >> 24;
            sub = (cmd0 >> 16) & 0xFF;
            if (op) {} // FAKE: dead statement (op stays a coloured web)
            if (sub) {} // FAKE: dead statement (sub computed before the branch)
            if ((op == 0xDE) && (sub == 1)) {
                id = (curr->unk4 << 4) >> 28;
                if (op && op) {} // FAKE: dead statement (steers uopt colouring)
                search = cmdStart;
                found = 0;
                if (cmdStart != cmdEnd) {
                    do {
                        search_cmd = search->unk0;
                        if (((search_cmd >> 24) == 0) && (id == search->unk4)) {
                            found = 1;
                        } else {
                            search++;
                        }
                    } while (!found && (search != cmdEnd));
                }
                node = heapAlloc(sizeof(ControllerSubNode));
                *pNodeList = node;
                pNodeList = &node->next;
                node->unk8 = id;
                node->unk0 = curr + 1;
                node->unk4 = search;
            }
            curr++;
        } while (curr != cmdEnd);
    }
    *pNodeList = NULL;
}

typedef struct ControllerCommand {
    u32 unk0;
    u32 unk4;
} ControllerCommand;

typedef struct {
    ControllerCommand *unk0;
} ControllerCommandArray;

typedef struct {
    u8 pad0[4];
    ControllerCommandArray *unk4;
} ControllerCommandStorage;

typedef struct ControllerCommandOwner {
    ControllerCommandStorage *unk0;
    u8 pad4[0x5C];
    u32 unk60;
} ControllerCommandOwner;

void controllerSetCommand(ControllerCommandOwner *owner, s32 commandIndex, ControllerCommand *command) {
    ControllerCommand *commands;
    ControllerCommand *destination;

    if (owner->unk60 & 0x10) {
        return;
    }
    commands = owner->unk0->unk4->unk0;
    destination = commands + commandIndex;
    if ((command->unk0 != destination->unk0) || (command->unk4 != destination->unk4)) {
        memcpy(destination, command, 8);
    }
}

void controllerCommandRelocateAssets(ControllerCommand *cmdStart, void *cmdEnd) {
    u32 op;

    if (cmdStart != cmdEnd) {
        do {
            op = cmdStart->unk0 >> 0x18;
            if (op == 0xFD) {
                if (((cmdStart->unk4 * 0x10) >> 0x1C) == 0) {
                    cmdStart->unk4 = (u32)assetLoad(0x19, cmdStart->unk4, 0, 0);
                }
            }
            cmdStart++;
        } while (cmdStart != cmdEnd);
    }
}

u16 controllerLookupStateByHash(Actor *actor) {
    u32 val = (u32)actor->animState;
    s32 i;
    for (i = D_807FBB30; i >= 0; i--) {
        if (val == D_807FB630[i].unk4) {
            break;
        }
    }
    if (i >= 0) {
        return D_807FB630[i].unk0;
    }
    return 0;
}

typedef struct {
    u8 pad[0x20];
    u8 unk20;
} AnimAssetEntry;

s32 controllerAnimInit(Actor *actor, u16 assetId) {
    AnimAssetEntry *resource;
    s32 i;
    void *alloc;
    ActorSub4 *anim;
    resource = controllerAnimStateLoadAsset(actor, assetId, 0);
    if (resource != NULL) {
        actor->animState = resource;
        actor->overrideModel = NULL;
        actor->stateModel = NULL;

        alloc = heapAlloc((resource->unk20 << 7) + 0x170);
        actor->sub4 = (ActorSub4 *)alloc;
        actor->sub4->model = (AnimSlot *)((u8 *)alloc + 0x90);
        actor->sub4->layer = (AnimSlot *)((u8 *)alloc + 0xC8);
        actor->sub4->blendFrom = (AnimSlot *)((u8 *)alloc + 0x100);
        actor->sub4->blendFromLayer = (AnimSlot *)((u8 *)alloc + 0x138);
        actor->sub4->boneMtx[0] = (Mtx *)((u8 *)alloc + 0x170);
        actor->sub4->boneMtx[1] = (Mtx *)((u8 *)actor->sub4->boneMtx[0] + (resource->unk20 << 6));

        for (i = 0; i < resource->unk20; i++) {
            guMtxIdent((Mtx *)((u8 *)actor->sub4->boneMtx[0] + (i << 6)));
            guMtxIdent((Mtx *)((u8 *)actor->sub4->boneMtx[1] + (i << 6)));
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
    void *rotations;
    void *scales;
    void *offsets;

    controllerAnimFreeSub(actor, 0);
    controllerAnimFreeSub(actor, 1);
    controllerAnimFreeSub(actor, 2);
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

typedef struct {
    u32 unk0;
    u32 unk4;
} ControllerCmdB;

typedef struct {
    ControllerCmdB *start;
} ControllerCmdListB;

typedef struct {
    u8 pad0[4];
    ControllerCmdListB *commands;
} ControllerSubB;


struct AnimCacheEntry {
    s32 id;
    s32 refCount;
    void *asset;
};
extern struct AnimCacheEntry D_807FB7B0[];
typedef struct {
    u16 unk0;
    u16 unk2;
    u32 unk4;
    u8 unk8;
} AnimStateSlot;

#define FREESUB_SLOT(i) (((AnimStateSlot *)D_807FB630)[i])
void controllerAnimFreeSub(Actor *controller, u8 slotIndex) {
    ControllerSubB *sub;
    ControllerCmdB *cmd;
    ControllerCmdListB *cmdList;
    u32 val;
    s32 i;
    switch (slotIndex) {
    case 0:
        sub = controller->animState;
        controller->animState = NULL;
        break;
    case 1:
        sub = controller->overrideModel;
        controller->overrideModel = NULL;
        break;
    case 2:
        sub = controller->stateModel;
        controller->stateModel = NULL;
        break;
    }

    if (sub != NULL) {
        for (i = 0; i < 32; i++) {
            if (D_807FB630[i].unk4 == (u32)sub) {
                break;
            }
        }
        if (i == 32) {
            return;
        }
        if (--FREESUB_SLOT(i).unk2 == 0) {
            cmd = sub->commands->start;
            cmdList = sub->commands;
            if (cmd != (ControllerCmdB *)cmdList) {
                do {
                    val = cmd->unk0 >> 24;
                    if (val == 0xFD) {
                        val = cmd->unk4;
                        if ((val >= 0x80000000) && (val < 0xA0000000)) {
                            assetFreeBuffer((void *)(val ^ 0), 0x270, 0x15); // FAKE: no-op xor keeps val a separate temp from the range test
                        }
                    }
                } while (++cmd != (ControllerCmdB *)cmdList);
            }

            D_807FBB30--;
            FREESUB_SLOT(i).unk0 = FREESUB_SLOT(D_807FBB30).unk0;
            FREESUB_SLOT(i).unk4 = FREESUB_SLOT(D_807FBB30).unk4;
            FREESUB_SLOT(i).unk8 = FREESUB_SLOT(D_807FBB30).unk8;
            FREESUB_SLOT(i).unk2 = FREESUB_SLOT(D_807FBB30).unk2;

            FREESUB_SLOT(D_807FBB30).unk0 = 0;
            FREESUB_SLOT(D_807FBB30).unk4 = 0;
            FREESUB_SLOT(D_807FBB30).unk8 = 0;
            FREESUB_SLOT(D_807FBB30).unk2 = 0;

            assetFreeBuffer((void *)sub, 0x281, 0x15);
        }
    }
}

int controllerAnimCacheFree(Actor *actor, AnimSlot *slot) {
    void *asset;
    s32 i;
    s32 count;

    asset = slot->clip;
    if (asset != NULL) {
        count = D_807FBB32;
        for (i = 0; i + 1 <= count; i++) { // LAYOUT: plain `i < count` is rewritten to a bne latch by uopt's LFTR
            if (asset == D_807FB7B0[i].asset) {
                if (--D_807FB7B0[i].refCount == 0) {
                    assetFreeBuffer(D_807FB7B0[i].asset, 0x298, 0x15);
                    D_807FBB32--;
                    D_807FB7B0[i].id = D_807FB7B0[D_807FBB32].id;
                    D_807FB7B0[i].asset = D_807FB7B0[D_807FBB32].asset;
                    D_807FB7B0[i].refCount = D_807FB7B0[D_807FBB32].refCount;
                    D_807FB7B0[D_807FBB32].id = 0xFFFF;
                    D_807FB7B0[D_807FBB32].asset = NULL;
                    D_807FB7B0[D_807FBB32].refCount = 0;
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
    f32 temp;
    s16 count = (s32)((actor->sub4->model->lastFrame - actor->sub4->model->firstFrame) + 1.0f);
    s16 span = (s32)((actor->sub4->blendFrom->lastFrame - actor->sub4->blendFrom->firstFrame) + 1.0f);
    temp = (actor->sub4->blendFrom->frame * (f32)count) / (f32)span;
    temp += (f32)offset;
    controllerApplyMotionWindow(actor, actor->sub4->model, temp);
}

extern u16 *gActorScriptAnimTable;

void controllerAnimSetStateRemap(Actor *actor, s16 animIndex, f32 animSpeed, f32 blend) {
    s16 flag;
    s32 sum;
    if (animIndex >= 0) {
        flag = animIndex & 0x4000;
        animIndex -= flag;
        gActivePlayerState->unk4E = animIndex;
        sum = (animIndex * 7 + actor->actorType - 2) & 0xFFFF;
        animIndex = gActorScriptAnimTable[sum] + flag;
    } else {
        gActivePlayerState->unk4E = animIndex;
    }
    controllerAnimSetStateIfChanged(actor, animIndex, animSpeed, blend);
}


void controllerAnimSetStateRemapDirect(Actor *actor, s16 animIndex, f32 animSpeed, f32 blend) {
    s16 flag;
    s32 sum;
    if (animIndex >= 0) {
        flag = animIndex & 0x4000;
        animIndex -= flag;
        gActivePlayerState->unk4E = animIndex;
        sum = (animIndex * 7 + actor->actorType - 2) & 0xFFFF;
        animIndex = gActorScriptAnimTable[sum] + flag;
    } else {
        gActivePlayerState->unk4E = animIndex;
    }
    controllerAnimSetState(actor, animIndex, animSpeed, blend);
}

void controllerAnimSetStateIfChanged(Actor *actor, s16 animId, f32 animSpeed, f32 blend) {
    AnimSlot *state;

    state = actor->sub4->model;
    if (animId == state->animId) {
        state->speed = state->clip->speed;
        return;
    }
    controllerAnimSetState(actor, animId, animSpeed, blend);
}

void controllerAnimSetState(Actor *actor, s16 animId, f32 animSpeed, f32 blend) {
    void *pad;
    ActorSub4 *anim;
    AnimSlot *slot0;
    AnimSlot *slot4;
    AnimSlot *slot8;
    AnimSlot *slotC;
    AnimClip *resource;
    f32 animTimer;
    u8 slotFlags;

    anim = actor->sub4;
    slot0 = anim->model;
    slot8 = anim->blendFrom;
    slot4 = anim->layer;
    slotC = anim->blendFromLayer;

    if (slot8->clip != NULL) {
        controllerAnimCacheFree(actor, slot8);
    }
    if (slotC->clip != NULL) {
        controllerAnimCacheFree(actor, slotC);
    }

    if ((animId & 0x4000) == 0x4000) {
        animId -= 0x4000;
        if (slot4->clip != NULL) {
            slotC->clip = controllerAnimCacheGetOrLoad(slot4->animId);
            slotC->frame = slot4->frame;
            slotC->frameFrac = slot4->frameFrac;
            slotC->frameIndex = slot4->frameIndex;
            slotC->nextFrameIndex = slot4->nextFrameIndex;
            slotC->animId = slot4->animId;
            slotC->flags = slot4->flags;
            slotC->firstFrame = slot4->firstFrame;
            slotC->lastFrame = slot4->lastFrame;
            slotC->speedRampDuration = slot4->speedRampDuration;
            slotC->speed = slot4->speed;
            slotC->speedTo = slot4->speedTo;
            slotC->speedFrom = slot4->speedFrom;
            slotC->speedRampTime = slot4->speedRampTime;
            anim->blendFromLayerWeight = anim->layerWeight;
        } else {
            anim->blendFromLayerWeight = 0;
        }
    }

    if (blend > 0.0f) {
        animTimer = anim->unk48;
        if (animTimer > (f32)0) {
            anim->blendTime = animTimer;
        } else {
            anim->blendTime = -animTimer;
        }
        if (anim->blendTime < blend) {
            anim->blendDuration = blend;
        } else {
            anim->blendDuration = anim->blendTime;
        }
        anim->blendWeight = (anim->blendDuration - anim->blendTime) / anim->blendDuration;
    } else {
        if (slot0->clip != NULL) {
            controllerAnimCacheFree(actor, slot0);
        }
        if (slot4->clip != NULL) {
            controllerAnimCacheFree(actor, slot4);
        }
    }

    resource = controllerAnimCacheGetOrLoad(animId);
    if (resource != NULL) {
        slot8->clip = resource;
        slot8->animId = animId;
        slot8->flags = resource->flags;
        slot8->firstFrame = 0.0f;
        slot8->lastFrame = (f32)(resource->frameCount - 1);
        slot8->speedRampDuration = 0.0f;
        slot8->speed = resource->speed;
        slot8->speedTo = resource->speed;
        slot8->speedFrom = resource->speed;
        slot8->speedRampTime = 0.0f;
    } else {
        slot8->clip = NULL;
        slot8->animId = -1;
        slot8->flags = 0;
        slot8->firstFrame = 0.0f;
        slot8->lastFrame = 0.0;
        slot8->speedRampDuration = 0.0f;
        slot8->speed = 0.0f;
        slot8->speedTo = 0.0f;
        slot8->speedFrom = 0.0f;
        slot8->speedRampTime = 0.0f;
    }

    anim->scriptWaitFlags = 0;
    anim->loopCount = 0;
    anim->waitFrame = 0.0;
    anim->blendFrom = slot0;
    slotFlags = anim->layerWeight;
    anim->blendFromLayer = slot4;
    anim->model = slot8;
    anim->layer = slotC;
    anim->layerWeight = anim->blendFromLayerWeight;
    anim->blendFromLayerWeight = slotFlags;
    controllerApplyMotionWindow(actor, slot8, animSpeed);
}

void controllerAnimSetFromTable(Actor *actor, u16 animIndex, f32 animSpeed, u8 flags) {
    u16 x = animIndex;
    u16 idx = (u16)(7 * x + actor->actorType - 2);
    if (x) {} // FAKE: dead test makes the copy of animIndex a ring temp (move t6,a1) and the sum v0
    controllerAnimSetDirect(actor, gActorScriptAnimTable[idx], animSpeed, flags);
}

void controllerAnimSetDirect(Actor *actor, u16 animId, f32 animSpeed, u8 flags) {
    AnimSlot *slot;
    AnimClip *resource;

    slot = actor->sub4->layer;
    if (slot->clip != NULL) {
        controllerAnimCacheFree(actor, slot);
    }
    resource = controllerAnimCacheGetOrLoad(animId);
    if (resource != NULL) {
        slot->clip = resource;
        slot->animId = animId;
        slot->flags = resource->flags;
        slot->firstFrame = 0.0f;
        slot->lastFrame = (f32)(resource->frameCount - 1);
        slot->speedRampDuration = 0.0f;
        slot->speed = resource->speed;
        slot->speedTo = resource->speed;
        slot->speedFrom = resource->speed;
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

typedef struct AnimCacheEntry AnimCacheEntry;
extern AnimCacheEntry D_807FB7B0[];

void *controllerAnimCacheGetOrLoad(s32 id) {
    AnimCacheEntry *entry;
    u32 i;
    AnimClip *asset;
    s32 count;
    s32 bound;

    if (id < 0) {
        return NULL;
    }

    count = D_807FBB32;
    i = 0;
    if ((bound = count) != 0) { // FAKE: assigned bound and the (u32) latch keep the bound in a0 (Q0428)
        entry = D_807FB7B0;
        do {
            if (id == entry->id) {
                entry->refCount++;
                return entry->asset;
            }
            entry++;
        } while (++i < (u32)bound);
    }

    if (count >= 0x20) {
        return NULL;
    }

    asset = assetLoad(0xB, id, 1, 1);
    asset->unk6 += 6;
    bound = D_807FBB32;
    entry = &D_807FB7B0[bound];
    entry->asset = asset;
    entry->refCount++;
    D_807FBB32 = bound + 1;
    entry->id = id;
    return asset;
}

extern u32 gFrameDelta;
extern u8 D_80746B60;

void controllerStepMotionWindows(Actor *owner) {
    ActorSub4 *core;
    AnimSlot *win0;
    AnimSlot *win4;
    AnimSlot *unk8;
    AnimSlot *unkC;
    f32 pos;
    f32 rate;
    f32 step;

    core = owner->sub4;
    win0 = core->model;
    win4 = core->layer;
    unk8 = core->blendFrom;
    unkC = core->blendFromLayer;
    pos = win0->frame;
    if (core->motionFlags & 1) {
        rate = (f32) ((f64) (u32) gFrameDelta * 0.5);
    } else {
        rate = 1.0f;
    }
    core->motionFlags &= ~1;
    if (D_80746B60 == 0) {
        core->motionFlags |= (core->model->flags & 1);
    }
    if (core->speedRampDuration > 0.0f) {
        core->speedRampTime += rate;
        if (core->speedRampTime < core->speedRampDuration) {
            core->unk48 = core->speedFrom + (((core->speedTo - core->speedFrom) * core->speedRampTime) / core->speedRampDuration);
        } else {
            core->speedRampDuration = 0.0f;
            core->unk48 = core->speedTo;
        }
    }
    step = core->unk48 * rate;
    if (win0->speedRampDuration > 0.0f) {
        win0->speedRampTime += (step > 0) ? step : -step;
        if (win0->speedRampTime < win0->speedRampDuration) {
            win0->speed = win0->speedFrom + (((win0->speedTo - win0->speedFrom) * win0->speedRampTime) / win0->speedRampDuration);
        } else {
            win0->speedRampDuration = 0.0f;
            win0->speed = win0->speedTo;
        }
    }
    if (win4->speedRampDuration > 0.0f) {
        win4->speedRampTime += (step > 0) ? step : -step;
        if (win4->speedRampTime < win4->speedRampDuration) {
            win4->speed = win4->speedFrom + (((win4->speedTo - win4->speedFrom) * win4->speedRampTime) / win4->speedRampDuration);
        } else {
            win4->speedRampDuration = 0.0f;
            win4->speed = win4->speedTo;
        }
    }
    if (unk8->clip != NULL) {
        core->blendTime += (step > 0) ? step : -step;
        if (core->blendTime < core->blendDuration) {
            core->blendWeight = (core->blendDuration - core->blendTime) / core->blendDuration;
        } else {
            controllerAnimCacheFree(owner, unk8);
            controllerAnimCacheFree(owner, unkC);
            core->scriptWaitFlags &= ~0x10;
        }
        pos += ((step * win0->speed) / 2) * (1.0f - core->blendWeight);
    } else {
        pos += step * win0->speed;
    }
    controllerApplyMotionWindow(owner, win0, pos);
    if (win4->clip != NULL) {
        if (core->layerWeight < core->layerWeightTarget) {
            core->layerWeight += core->layerWeightStep;
            if (core->layerWeight > core->layerWeightTarget) {
                core->layerWeight = core->layerWeightTarget;
            }
        } else if (core->layerWeight > core->layerWeightTarget) {
            core->layerWeight -= core->layerWeightStep;
            if (core->layerWeight < core->layerWeightTarget) {
                core->layerWeight = core->layerWeightTarget;
            }
        }
        pos = win4->frame + win4->speed;
        controllerApplyMotionWindow(owner, win4, pos);
        if ((win4->speed == 0) && (win4->flags & 0x10)) {
            core->layerWeightTarget = 0;
            if (core->layerWeight == 0) {
                controllerAnimCacheFree(owner, win4);
            }
        }
    }
    actorScriptExecute(owner);
}

void controllerApplyMotionWindow(Actor *actor, AnimSlot *slot, f32 frame) {
    s8 notJump;
    f32 diff;
    f32 waitFrame;
    f32 prevFrame;
    f32 firstFrame;
    f32 lastFrame;
    s16 frameIndex;
    s32 loopCount;
    s32 span;
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
        diff = frame - (f32) slot->jumpFrom;
        if (diff > 0) {
            slot->frameFrac = diff;
        } else {
            slot->frameFrac = -diff;
        }
        if ((f64) slot->frameFrac < 1.0) {
            slot->frame = frame;
            slot->frameIndex = slot->jumpFrom;
            slot->nextFrameIndex = slot->jumpTo;
            return;
        }
        frame += (f32) ((slot->jumpTo - slot->jumpFrom) - (s32) diff);
        notJump = ~8;
        slot->flags = slot->flags & notJump;
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
        if (((f64) lastFrame + 1.0) <= (f64) frame) {
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
                    waitFlags = (anim->scriptWaitFlags &= ~2);
                }
            }
            if (waitFlags & 8) {
                waitFrame = anim->waitFrame;
                prevFrame = slot->frame;
                if (frame == waitFrame) {
                    if (prevFrame != waitFrame) anim->scriptWaitFlags = waitFlags & ~8;
                } else if (waitFrame < frame) {
                    if ((prevFrame < waitFrame) && (wrapped == 0)) anim->scriptWaitFlags = waitFlags & ~8;
                    else if ((waitFrame < prevFrame) && (wrapped != 0)) anim->scriptWaitFlags = waitFlags & ~8;
                } else if ((waitFrame < prevFrame) && (wrapped == 0)) anim->scriptWaitFlags = waitFlags & ~8;
                else if ((prevFrame < waitFrame) && (wrapped != 0)) anim->scriptWaitFlags = waitFlags & ~8;
            }
        }
    }
    slot->frame = frame;
    slot->frameIndex = (s16) frame;
    frameIndex = slot->frameIndex;
    slot->nextFrameIndex = frameIndex + 1;
    slot->frameFrac = frame - (f32) frameIndex;
    if (lastFrame < (f32) slot->nextFrameIndex) {
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
void func_806195D0(f32, f32);
void actorCheckWorldBounds(Actor *actor) {
    f32 x = actor->x;
    if (x >= -8192.0f) {
        f32 y = actor->y;
        if (y >= -8192.0f) {
            f32 z = actor->z;
            if ((z >= -8192.0f) && (x <= 8192.0f) && (y <= 8192.0f) && (z <= 8192.0f)) {
                actor->boneMtx = actor->sub4->boneMtx[gGfxBufferIndex];
                func_806195D0(z, 8192.0f);
                actorTouchSub140Timestamp(actor);
                actor->flags |= 0x200;
            }
        }
    }
}

typedef struct SegmentNode {
    void *unk0;
    void *unk4;
    u8 unk8;
    struct SegmentNode *unkC;
} SegmentNode;

typedef struct DisplayListGroup {
    void *unk0;
    Gfx **unk4;
    u8 pad8[0xC];
    SegmentNode *unk14;
    u8 pad18[9];
    u8 unk21;
} DisplayListGroup;

Gfx *renderActorDisplayList(Gfx *gdl, Actor *actor) {
    DisplayListGroup *display = actor->animState;
    s32 i;

    if (actor->overrideModel != NULL) {
        display = actor->overrideModel;
    }
    if (actor->stateModel != NULL) {
        display = actor->stateModel;
    }
    gdl = animSetSegments(gdl, actor);
    gdl = renderEmitSegmentNodes(gdl, actor, display);
    gSPSegment(gdl++, 4, osVirtualToPhysical(actor->boneMtx));
    gSPSegment(gdl++, 3, osVirtualToPhysical(display->unk0));
    for (i = 0; i < display->unk21; i++) {
        gSPDisplayList(gdl++, display->unk4[i]);
    }
    return gdl;
}

Gfx *renderEmitSegmentNodes(Gfx *gdl, Actor *actor, DisplayListGroup *group) {
    u16 flags = actor->unk146;
    SegmentNode *node = group->unk14;
    s32 shift;

    if (node != NULL) {
        do {
            shift = (node->unk8 - 7) & 0xFF;
            if ((flags >> shift) & 1) {
                gSPSegment(gdl++, node->unk8, osVirtualToPhysical(node->unk0));
            } else {
                gSPSegment(gdl++, node->unk8, osVirtualToPhysical(node->unk4));
            }
            node = node->unkC;
        } while (node != NULL);
    }
    return gdl;
}

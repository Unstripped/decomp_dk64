#include "common.h"
#include "actor.h"

extern s16 D_807FBB30;
extern s16 D_807FBB32;
extern PlayerState *gActivePlayerState;

typedef struct ControllerView {
    u8 unk0[0x50];
    void *unk50;
} ControllerView;


void *controllerAnimStateLoadAsset();
void controllerAnimFreeSub();

typedef struct ControllerStateEntryView {
    u16 unk0;
    u16 unk2;
    void *unk4;
    u8 unk8;
} ControllerStateEntryView;

typedef struct ControllerAnimAssetView {
    void *unk0;
    void **unk4;
    void *unk8;
    void *unkC;
    void *unk10;
    void *unk14;
    u8 pad18[8];
    u8 unk20;
    u8 unk21;
} ControllerAnimAssetView;

// D_807FB630 is declared with its full type (ControllerStateEntry) further down; this function needs a u8 unk8 view, so it goes through a cast.
struct ControllerStateEntry;
extern struct ControllerStateEntry D_807FB630[];
#define CONTROLLER_STATE_ENTRY(i) (((ControllerStateEntryView *)D_807FB630)[i])
extern void *D_807FB634;
void *assetLoad(s32, s32, s32, s32);  // FAKE: callee prototype steer
extern u8 D_80746B64[];

void animListInit(void *, void *);
void controllerBuildSubcommandList();
void renderReplaceSegment6Commands();
void controllerCommandRelocateAssets();
void gfxSwapGeometryModeCullBits();

void *controllerAnimStateLoadAsset(controller, assetId, cullSwap)
void *controller;
s32 assetId;
unsigned char cullSwap;
{
    s32 i;
    ControllerAnimAssetView *asset;
    s32 delta;

    for (i = 0; i < (u16)D_807FBB30; i++) {
        if (assetId == CONTROLLER_STATE_ENTRY(i).unk0 && CONTROLLER_STATE_ENTRY(i).unk8 == cullSwap) {
            CONTROLLER_STATE_ENTRY(i).unk2++;
            animListInit(controller, CONTROLLER_STATE_ENTRY(i).unk4);
            return CONTROLLER_STATE_ENTRY(i).unk4;
        }
    }

    if ((u16)D_807FBB32 >= 0x20) {
        return D_807FB634;
    }

    asset = (ControllerAnimAssetView *)assetLoad(5, assetId - 1, 1, 1);
    CONTROLLER_STATE_ENTRY(i).unk0 = assetId;
    D_807FBB30 = (u16)D_807FBB30 + 1;
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
void gfxSwapGeometryModeCullBits(GfxCmdWords *cmdStart, GfxCmdWords *cmdEnd) {
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

void controllerAnimLoadStateAsset(ControllerView *controller, s16 assetId) {
    if (controller->unk50 == NULL) {
        controller->unk50 = controllerAnimStateLoadAsset(controller, assetId, 0);
    }
}

void controllerAnimLoadStateAsset1(ControllerView *controller, s16 assetId) {
    if (controller->unk50 == NULL) {
        controller->unk50 = controllerAnimStateLoadAsset(controller, assetId, 1);
    }
}

void controllerAnimFreeStateAsset(ControllerView *controller) {
    if (controller->unk50 != NULL) {
        controllerAnimFreeSub(controller, 2);
        controller->unk50 = NULL;
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

void *heapAlloc(s32);

void controllerBuildSubcommandList(ControllerSubCmd *cmdStart, ControllerSubCmd *cmdEnd, ControllerSubNode **pNodeList) {
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
    u32 *arg2_words;
    ControllerCommand *commands;
    ControllerCommand *destination;

    if (owner->unk60 & 0x10) {
        return;
    }
    arg2_words = &command->unk0;
    commands = owner->unk0->unk4->unk0;
    destination = commands + commandIndex;
    if ((destination->unk0 != *arg2_words) || (command->unk4 != destination->unk4)) {
        memcpy(destination, command, 8);
    }
}

void controllerCommandRelocateAssets(ControllerCommand *cmdStart, ControllerCommand *cmdEnd) {
    u32 word;

    if (cmdStart != cmdEnd) {
        do {
            word = cmdStart->unk0;
            if ((word >> 0x18) == (0, 0xFD)) { // FAKE: keeps bnel operand order
                if (((cmdStart->unk4 * 0x10) >> 0x1C) == 0) {
                    cmdStart->unk4 = (u32)assetLoad(0x19, cmdStart->unk4, 0, 0);
                }
            }
            cmdStart++;
        } while (cmdStart != cmdEnd);
    }
}

typedef struct ControllerStateEntry {
    u16 unk0;
    u16 unk2;
    u32 unk4;
    u32 unk8;
} ControllerStateEntry;

extern ControllerStateEntry D_807FB630[];

u16 controllerLookupStateByHash(u32 *pHash) {
    u32 val = *pHash;
    s32 i;
    for (i = (u16)D_807FBB30; i >= 0; i--) {
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
    void *unk0;
    void *unk4;
    void *unk8;
    void *unkC;
    u8 pad10[0xC];
    void *unk1C;
    void *unk20;
    void *unk24;
} ControllerAnimData;

typedef struct ControllerAnimView {
    void *unk0;
    ControllerAnimData *unk4;
} ControllerAnimView;

void animListFree(void *);
void heapFreeDeferred();

typedef struct {
    void *unk0;
    f32 unk4;
    f32 unk8;
    u8 padC[4];
    s16 unk10;
    u8 pad12[2];
    f32 unk14;
    f32 unk18;
    u16 unk1C;
    u8 pad1E[6];
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
} AnimSlotInit;

typedef struct {
    AnimSlotInit *unk0;
    AnimSlotInit *unk4;
    AnimSlotInit *unk8;
    AnimSlotInit *unkC;
    f32 unk10;
    Mtx *unk14;
    Mtx *unk18;
    void *unk1C;
    void *unk20;
    void *unk24;
    u8 pad28[0xC];
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    u8 pad40[4];
    f32 unk44;
    f32 unk48;
    u8 pad4C[0xC];
    f32 unk58;
    u8 pad5C[8];
    s16 unk64;
    u8 pad66[2];
    s32 unk68;
    u8 pad6C[4];
    s32 unk70;
    u8 pad74[4];
    s32 unk78;
    s32 unk7C;
    f32 unk80;
    s32 unk84;
    s32 unk88;
} AnimStateInit;

typedef struct AnimControllerInit {
    void *unk0;
    AnimStateInit *unk4;
    u8 pad8[4];
    f32 unkC[4][4];
    s32 unk4C;
    s32 unk50;
} AnimControllerInit;

typedef struct {
    u8 pad[0x20];
    u8 unk20;
} AnimAssetEntry;

s32 controllerAnimInit(AnimControllerInit *controller, u16 assetId) {
    AnimAssetEntry *resource;
    s32 i;
    void *alloc;
    AnimStateInit *anim;
    resource = controllerAnimStateLoadAsset(controller, assetId, 0);
    if (resource != NULL) {
        controller->unk0 = resource;
        controller->unk4C = 0;
        controller->unk50 = 0;

        alloc = heapAlloc((resource->unk20 << 7) + 0x170);
        controller->unk4 = (AnimStateInit *)alloc;
        controller->unk4->unk0 = (AnimSlotInit *)((u8 *)alloc + 0x90);
        controller->unk4->unk4 = (AnimSlotInit *)((u8 *)alloc + 0xC8);
        controller->unk4->unk8 = (AnimSlotInit *)((u8 *)alloc + 0x100);
        controller->unk4->unkC = (AnimSlotInit *)((u8 *)alloc + 0x138);
        controller->unk4->unk14 = (Mtx *)((u8 *)alloc + 0x170);
        controller->unk4->unk18 = (Mtx *)((u8 *)controller->unk4->unk14 + (resource->unk20 << 6));

        for (i = 0; i < resource->unk20; i++) {
            guMtxIdent((Mtx *)((u8 *)controller->unk4->unk14 + (i << 6)));
            guMtxIdent((Mtx *)((u8 *)controller->unk4->unk18 + (i << 6)));
        }

        guMtxIdentF(controller->unkC);
        anim = controller->unk4;
        anim->unk1C = NULL;
        anim->unk20 = NULL;
        anim->unk24 = NULL;
        anim->unk34 = 0.15f;
        anim->unk38 = 0.15f;
        anim->unk3C = 0.15f;
        anim->unk0->unk4 = 0.0f;
        anim->unk0->unk8 = 0.0f;
        anim->unk0->unk0 = NULL;
        anim->unk0->unk10 = -1;
        anim->unk0->unk1C = 0;
        anim->unk0->unk14 = 0.0f;
        anim->unk0->unk18 = 0.0f;
        anim->unk0->unk24 = 1.0f;
        anim->unk0->unk34 = 0.0f;

        anim->unk4->unk0 = NULL;
        anim->unk4->unk34 = 0.0f;
        anim->unk8->unk0 = NULL;
        anim->unk8->unk34 = 0.0f;
        anim->unkC->unk0 = NULL;
        anim->unkC->unk34 = 0.0f;

        anim->unk68 = 0;
        anim->unk64 = 0;
        anim->unk70 = 0;
        anim->unk78 = 0;
        anim->unk7C = 0;
        anim->unk84 = 0;
        anim->unk88 = 0;

        anim->unk10 = 0.0f;
        anim->unk44 = 0.0f;
        anim->unk58 = 0.0f;
        anim->unk48 = 1.0f;
        anim->unk80 = 0.0;

        return 1;
    }
    return 0;
}

void controllerAnimFree(ControllerAnimView *controller) {
    void *buffer1;
    void *temp_a1_2;
    void *temp_a1_3;

    controllerAnimFreeSub((ControllerView *)controller, 0);
    controllerAnimFreeSub((ControllerView *)controller, 1);
    controllerAnimFreeSub((ControllerView *)controller, 2);
    animListFree((u8 *)controller + 0x158);
    controllerAnimCacheFree(controller, controller->unk4->unk0);
    controllerAnimCacheFree(controller, controller->unk4->unk4);
    controllerAnimCacheFree(controller, controller->unk4->unk8);
    controllerAnimCacheFree(controller, controller->unk4->unkC);
    buffer1 = controller->unk4->unk1C;
    if (buffer1 != NULL) {
        heapFreeDeferred(buffer1);
    }
    temp_a1_2 = controller->unk4->unk20;
    if (temp_a1_2 != NULL) {
        heapFreeDeferred(temp_a1_2);
    }
    temp_a1_3 = controller->unk4->unk24;
    if (temp_a1_3 != NULL) {
        heapFreeDeferred(temp_a1_3);
    }
    heapFreeDeferred(controller->unk4);
}
typedef struct ControllerViewB {
    void *unk0;
    u8 pad4[0x48];
    void *unk4C;
    void *unk50;
} ControllerViewB;

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

void assetFreeBuffer(void *, s32, s32);

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
void controllerAnimFreeSub(controller, slotIndex)
ControllerViewB *controller;
u8 slotIndex;
{
    ControllerSubB *sub;
    ControllerCmdB *cmd;
    ControllerCmdListB *cmdList;
    u32 val;
    s32 i;
    switch (slotIndex) {
    case 0:
        sub = controller->unk0;
        controller->unk0 = NULL;
        break;
    case 1:
        sub = controller->unk4C;
        controller->unk4C = NULL;
        break;
    case 2:
        sub = controller->unk50;
        controller->unk50 = NULL;
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
                    val = cmd->unk0;
                    if ((val >> 24) == (0, 0xFD)) {
                        val = cmd->unk4;
                        if ((val >= 0x80000000) && (val < 0xA0000000)) {
                            assetFreeBuffer((void *)(val ^ 0), 0x270, 0x15);
                        }
                    }
                } while (++cmd != (ControllerCmdB *)cmdList);
            }

            D_807FBB30 = (u16)D_807FBB30 - 1;
            FREESUB_SLOT(i).unk0 = FREESUB_SLOT((u16)D_807FBB30).unk0;
            FREESUB_SLOT(i).unk4 = FREESUB_SLOT((u16)D_807FBB30).unk4;
            FREESUB_SLOT(i).unk8 = FREESUB_SLOT((u16)D_807FBB30).unk8;
            FREESUB_SLOT(i).unk2 = FREESUB_SLOT((u16)D_807FBB30).unk2;

            FREESUB_SLOT((u16)D_807FBB30).unk0 = 0;
            FREESUB_SLOT((u16)D_807FBB30).unk4 = 0;
            FREESUB_SLOT((u16)D_807FBB30).unk8 = 0;
            FREESUB_SLOT((u16)D_807FBB30).unk2 = 0;

            assetFreeBuffer((void *)sub, 0x281, 0x15);
        }
    }
}


typedef struct {
    void *unk0;
    void *unk4;
    void *unk8;
    void *unkC;
} ControllerAnimDataView;

typedef struct {
    void *unk0;
    ControllerAnimDataView *unk4;
} ControllerAnimRefView;

typedef struct {
    u8 pad0[0x84];
    s32 unk84;
} ControllerAnimDataBlock;


int controllerAnimCacheFree(void *controller, void *pSlot) {
    void *asset;
    s32 i;
    s32 count;

    asset = *(void **)pSlot;
    if (asset != NULL) {
        count = *(u16 *)&D_807FBB32;
        for (i = 0; i + 1 <= count; i++) { // LAYOUT: plain `i < count` is rewritten to a bne latch by uopt's LFTR
            if (asset == D_807FB7B0[i].asset) {
                if (--D_807FB7B0[i].refCount == 0) {
                    assetFreeBuffer(D_807FB7B0[i].asset, 0x298, 0x15);
                    *(u16 *)&D_807FBB32 -= 1;
                    D_807FB7B0[i].id = D_807FB7B0[*(u16 *)&D_807FBB32].id;
                    D_807FB7B0[i].asset = D_807FB7B0[*(u16 *)&D_807FBB32].asset;
                    D_807FB7B0[i].refCount = D_807FB7B0[*(u16 *)&D_807FBB32].refCount;
                    D_807FB7B0[*(u16 *)&D_807FBB32].id = 0xFFFF;
                    D_807FB7B0[*(u16 *)&D_807FBB32].asset = NULL;
                    D_807FB7B0[*(u16 *)&D_807FBB32].refCount = 0;
                }
                break;
            }
        }
        *(void **)pSlot = NULL;
    }
    if ((void *)pSlot == ((ControllerAnimRefView *)controller)->unk4->unk4) {
        ((ControllerAnimDataBlock *)((ControllerAnimRefView *)controller)->unk4)->unk84 = 0;
    }
}

typedef struct AnimScaleState { u8 pad[0x14]; f32 a; f32 b; } AnimScaleState;
typedef struct { u8 pad[4]; f32 scale; u8 pad2[0xC]; f32 a; f32 b; } AnimScaleSpan;
typedef struct { AnimScaleState *state; u8 pad[4]; AnimScaleSpan *scale; } AnimScaleHolder;
typedef struct AnimScaleController { u8 pad[4]; AnimScaleHolder *holder; } AnimScaleController;
void controllerApplyMotionWindow(AnimScaleController *controller, AnimScaleState *scaleState, f32 timePos);

void controllerAnimScaleInterpolate(AnimScaleController *controller, s8 offset) {
    f32 temp;
    s16 count = (s32)((controller->holder->state->b - controller->holder->state->a) + 1.0f);
    s16 span = (s32)((controller->holder->scale->b - controller->holder->scale->a) + 1.0f);
    temp = (controller->holder->scale->scale * (f32)count) / (f32)span;
    temp += (f32)offset;
    controllerApplyMotionWindow(controller, controller->holder->state, temp);
}


typedef struct {
    u8 pad0[0x4E];
    s16 unk4E;
} GlobalPlayerAnimView;

typedef struct {
    u8 pad0[0x58];
    s32 unk58;
} ControllerStateParamView;

extern u16 *gActorScriptAnimTable;
struct ControllerStateView;
void controllerAnimSetStateIfChanged(struct ControllerStateView *stateView, s16 animId, f32 animSpeed, f32 blend);

void controllerAnimSetStateRemap(struct ControllerStateView *stateView, s16 animIndex, f32 animSpeed, f32 blend) {
    s16 flag;
    s32 sum;
    if (animIndex >= 0) {
        flag = animIndex & 0x4000;
        animIndex -= flag;
        ((GlobalPlayerAnimView *)gActivePlayerState)->unk4E = animIndex;
        sum = (animIndex * 7 + ((ControllerStateParamView *)stateView)->unk58 - 2) & 0xFFFF;
        animIndex = gActorScriptAnimTable[sum] + flag;
    } else {
        ((GlobalPlayerAnimView *)gActivePlayerState)->unk4E = animIndex;
    }
    controllerAnimSetStateIfChanged(stateView, animIndex, animSpeed, blend);
}

void controllerAnimSetState(struct ControllerStateView *stateView, s16 animId, f32 animSpeed, f32 blend);

void controllerAnimSetStateRemapDirect(struct ControllerStateView *stateView, s16 animIndex, f32 animSpeed, f32 blend) {
    s16 flag;
    s32 sum;
    if (animIndex >= 0) {
        flag = animIndex & 0x4000;
        animIndex -= flag;
        ((GlobalPlayerAnimView *)gActivePlayerState)->unk4E = animIndex;
        sum = (animIndex * 7 + ((ControllerStateParamView *)stateView)->unk58 - 2) & 0xFFFF;
        animIndex = gActorScriptAnimTable[sum] + flag;
    } else {
        ((GlobalPlayerAnimView *)gActivePlayerState)->unk4E = animIndex;
    }
    controllerAnimSetState(stateView, animIndex, animSpeed, blend);
}

typedef struct {
    void *unk0;
    u8 pad4[0xC];
    s16 unk10;
    u8 pad12[0x12];
    f32 unk24;
} ControllerState;

typedef struct {
    ControllerState *unk0;
} ControllerStateHolder;

typedef struct ControllerStateView {
    u8 pad0[4];
    ControllerStateHolder *unk4;
} ControllerStateView;


void controllerAnimSetState(ControllerStateView *, s16, f32, f32);

void controllerAnimSetStateIfChanged(ControllerStateView *stateView, s16 animId, f32 animSpeed, f32 blend) {
    ControllerState *state;

    state = stateView->unk4->unk0;
    if (animId == state->unk10) {
        state->unk24 = *(f32 *)state->unk0;
        return;
    }
    controllerAnimSetState(stateView, animId, animSpeed, blend);
}

typedef struct {
    f32 unk0;
    u16 unk4;
    u8 pad6[0xC];
    u8 unk12;
} AnimResourceState;

typedef struct {
    AnimResourceState *unk0;
    f32 unk4;
    f32 unk8;
    s16 unkC;
    s16 unkE;
    s16 unk10;
    u8 pad12[2];
    f32 unk14;
    f32 unk18;
    s16 unk1C;
    u8 pad1E[6];
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
} AnimSlotState;

typedef struct {
    AnimSlotState *unk0;
    AnimSlotState *unk4;
    AnimSlotState *unk8;
    AnimSlotState *unkC;
    f32 unk10;
    u8 pad14[0x14];
    s16 unk28;
    s16 unk2A;
    u8 pad2C[0x14];
    f32 unk40;
    f32 unk44;
    f32 unk48;
    u8 pad4C[0x2C];
    s32 unk78;
    s32 unk7C;
    f32 unk80;
} AnimDataState;
void *controllerAnimCacheGetOrLoad(s32 id);

void controllerAnimSetState(ControllerStateView *stateView, s16 animId, f32 animSpeed, f32 blend) {
    void *pad;
    AnimDataState *anim;
    AnimSlotState *slot0;
    AnimSlotState *slot4;
    AnimSlotState *slot8;
    AnimSlotState *slotC;
    AnimResourceState *resource;
    f32 animTimer;
    u8 slotFlags;

    anim = (AnimDataState *)stateView->unk4;
    slot0 = anim->unk0;
    slot8 = anim->unk8;
    slot4 = anim->unk4;
    slotC = anim->unkC;

    if (slot8->unk0 != NULL) {
        controllerAnimCacheFree(stateView, slot8);
    }
    if (slotC->unk0 != NULL) {
        controllerAnimCacheFree(stateView, slotC);
    }

    if ((animId & 0x4000) == 0x4000) {
        animId -= 0x4000;
        if (slot4->unk0 != NULL) {
            slotC->unk0 = controllerAnimCacheGetOrLoad(slot4->unk10);
            slotC->unk4 = slot4->unk4;
            slotC->unk8 = slot4->unk8;
            slotC->unkC = slot4->unkC;
            slotC->unkE = slot4->unkE;
            slotC->unk10 = slot4->unk10;
            slotC->unk1C = slot4->unk1C;
            slotC->unk14 = slot4->unk14;
            slotC->unk18 = slot4->unk18;
            slotC->unk34 = slot4->unk34;
            slotC->unk24 = slot4->unk24;
            slotC->unk2C = slot4->unk2C;
            slotC->unk28 = slot4->unk28;
            slotC->unk30 = slot4->unk30;
            anim->unk2A = anim->unk28;
        } else {
            anim->unk2A = 0;
        }
    }

    if (blend > 0.0f) {
        animTimer = anim->unk48;
        if (animTimer > (f32)0) {
            anim->unk40 = animTimer;
        } else {
            anim->unk40 = -animTimer;
        }
        if (anim->unk40 < blend) {
            anim->unk44 = blend;
        } else {
            anim->unk44 = anim->unk40;
        }
        anim->unk10 = (anim->unk44 - anim->unk40) / anim->unk44;
    } else {
        if (slot0->unk0 != NULL) {
            controllerAnimCacheFree(stateView, slot0);
        }
        if (slot4->unk0 != NULL) {
            controllerAnimCacheFree(stateView, slot4);
        }
    }

    resource = controllerAnimCacheGetOrLoad(animId);
    if (resource != NULL) {
        slot8->unk0 = resource;
        slot8->unk10 = animId;
        slot8->unk1C = resource->unk4;
        slot8->unk14 = 0.0f;
        slot8->unk18 = (f32)(resource->unk12 - 1);
        slot8->unk34 = 0.0f;
        slot8->unk24 = resource->unk0;
        slot8->unk2C = resource->unk0;
        slot8->unk28 = resource->unk0;
        slot8->unk30 = 0.0f;
    } else {
        slot8->unk0 = NULL;
        slot8->unk10 = -1;
        slot8->unk1C = 0;
        slot8->unk14 = 0.0f;
        slot8->unk18 = 0.0;
        slot8->unk34 = 0.0f;
        slot8->unk24 = 0.0f;
        slot8->unk2C = 0.0f;
        slot8->unk28 = 0.0f;
        slot8->unk30 = 0.0f;
    }

    anim->unk78 = 0;
    anim->unk7C = 0;
    anim->unk80 = 0.0;
    anim->unk8 = slot0;
    slotFlags = ((u8 *)&anim->unk28)[1];
    anim->unkC = slot4;
    anim->unk0 = slot8;
    anim->unk4 = slotC;
    anim->unk28 = anim->unk2A;
    anim->unk2A = slotFlags;
    controllerApplyMotionWindow((AnimScaleController *)stateView, (AnimScaleState *)slot8, animSpeed);
}


typedef struct ControllerActorTypeView {
    u8 pad0[0x58];
    s32 unk58;
} ControllerActorTypeView;
extern u16 *gActorScriptAnimTable;
struct AnimControllerRef;
void controllerAnimSetDirect(struct AnimControllerRef *controller, u16 animId, f32 animSpeed, u8 flags);

void controllerAnimSetFromTable(ControllerActorTypeView *actorView, u16 animIndex, f32 animSpeed, u8 flags) {
    u16 x = animIndex;
    u16 idx = (u16)(7 * x + actorView->unk58 - 2);
    if (x) {} // FAKE: dead test makes the copy of animIndex a ring temp (move t6,a1) and the sum v0
    controllerAnimSetDirect((struct AnimControllerRef *)actorView, gActorScriptAnimTable[idx], animSpeed, flags);
}

typedef struct {
    f32 unk0;
    u16 unk4;
    u8 pad6[0xC];
    u8 unk12;
} AnimResourceSlot;

typedef struct {
    AnimResourceSlot *unk0;
    u8 pad4[0xC];
    s16 unk10;
    f32 unk14;
    f32 unk18;
    u16 unk1C;
    u8 pad1E[6];
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
} AnimSlotRef;

typedef struct {
    void *unk0;
    AnimSlotRef *unk4;
    u8 pad8[0x20];
    s16 unk28;
    u8 pad2A[2];
    s16 unk2C;
    s16 unk2E;
} AnimDataRef;

typedef struct AnimControllerRef {
    void *unk0;
    AnimDataRef *unk4;
} AnimControllerRef;


void controllerAnimSetDirect(AnimControllerRef *controller, u16 animId, f32 animSpeed, u8 flags) {
    AnimSlotRef *slot;
    AnimResourceSlot *resource;

    slot = controller->unk4->unk4;
    if (slot->unk0 != NULL) {
        controllerAnimCacheFree(controller, slot);
    }
    resource = controllerAnimCacheGetOrLoad(animId);
    if (resource != NULL) {
        slot->unk0 = resource;
        slot->unk10 = animId;
        slot->unk1C = resource->unk4;
        slot->unk14 = 0.0f;
        slot->unk18 = (f32)(resource->unk12 - 1);
        slot->unk34 = 0.0f;
        slot->unk24 = resource->unk0;
        slot->unk2C = resource->unk0;
        slot->unk28 = resource->unk0;
        slot->unk30 = 0.0f;
        controller->unk4->unk28 = 0;
        controller->unk4->unk2C = 0xFF;
        controller->unk4->unk2E = flags;
    } else {
        slot->unk0 = NULL;
        slot->unk10 = -1;
        slot->unk1C = 0;
        slot->unk14 = 0.0f;
        slot->unk34 = 0.0f;
        slot->unk24 = 0.0f;
        slot->unk2C = 0.0f;
        slot->unk28 = 0.0f;
        slot->unk30 = 0.0f;
        slot->unk18 = 0;
    }
    controllerApplyMotionWindow((AnimScaleController *)controller, (AnimScaleState *)slot, animSpeed);
}

typedef struct AnimCacheEntry AnimCacheEntry;
extern AnimCacheEntry D_807FB7B0[];

void *controllerAnimCacheGetOrLoad(s32 id) {
    AnimCacheEntry *entry;
    u32 i;
    void *asset;
    s32 count;
    s32 bound;

    if (id < 0) {
        return NULL;
    }

    count = (u16)D_807FBB32;
    i = 0;
    if ((bound = count) != 0) {
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
    *(u16 *)((u8 *)asset + 6) += 6;
    bound = (u16)D_807FBB32;
    entry = &D_807FB7B0[bound];
    entry->asset = asset;
    entry->refCount++;
    D_807FBB32 = bound + 1;
    entry->id = id;
    return asset;
}

extern u32 gFrameDelta;
extern u8 D_80746B60;
void actorScriptExecute(void *);

typedef struct {
    void *unk0;
    f32 unk4;
    f32 unk8;
    s16 unkC;
    s16 unkE;
    u8 pad10[4];
    f32 unk14;
    f32 unk18;
    u16 unk1C;
    s16 unk1E;
    s16 unk20;
    u8 pad22[2];
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
} MotionWindow;

typedef struct {
    MotionWindow *unk0;
    MotionWindow *unk4;
    void *unk8;
    void *unkC;
    f32 unk10;
    u8 pad14[0x14];
    s16 unk28;
    u8 pad2A[2];
    s16 unk2C;
    s16 unk2E;
    s16 unk30;
    u8 pad32[0xE];
    f32 unk40;
    f32 unk44;
    f32 unk48;
    f32 unk4C;
    f32 unk50;
    f32 unk54;
    f32 unk58;
    u8 pad5C[0x1C];
    s32 unk78;
    s32 unk7C;
    f32 unk80;
    s32 unk84;
} MotionCore;

typedef struct MotionOwner {
    u8 pad0[4];
    MotionCore *unk4;
} MotionOwner;

void controllerStepMotionWindows(MotionOwner *owner) {
    MotionCore *core;
    MotionWindow *win0;
    MotionWindow *win4;
    void *unk8;
    void *unkC;
    f32 pos;
    f32 rate;
    f32 step;

    core = owner->unk4;
    win0 = core->unk0;
    win4 = core->unk4;
    unk8 = core->unk8;
    unkC = core->unkC;
    pos = win0->unk4;
    if (core->unk30 & 1) {
        rate = (f32) ((f64) (u32) gFrameDelta * 0.5);
    } else {
        rate = 1.0f;
    }
    core->unk30 &= ~1;
    if (D_80746B60 == 0) {
        core->unk30 |= (*(s16 *)&core->unk0->unk1C & 1);
    }
    if (core->unk58 > 0.0f) {
        core->unk54 += rate;
        if (core->unk54 < core->unk58) {
            core->unk48 = core->unk4C + (((core->unk50 - core->unk4C) * core->unk54) / core->unk58);
        } else {
            core->unk58 = 0.0f;
            core->unk48 = core->unk50;
        }
    }
    step = core->unk48 * rate;
    if (win0->unk34 > 0.0f) {
        win0->unk30 += (step > 0) ? step : -step;
        if (win0->unk30 < win0->unk34) {
            win0->unk24 = win0->unk28 + (((win0->unk2C - win0->unk28) * win0->unk30) / win0->unk34);
        } else {
            win0->unk34 = 0.0f;
            win0->unk24 = win0->unk2C;
        }
    }
    if (win4->unk34 > 0.0f) {
        win4->unk30 += (step > 0) ? step : -step;
        if (win4->unk30 < win4->unk34) {
            win4->unk24 = win4->unk28 + (((win4->unk2C - win4->unk28) * win4->unk30) / win4->unk34);
        } else {
            win4->unk34 = 0.0f;
            win4->unk24 = win4->unk2C;
        }
    }
    if (*(s32 *)unk8 != 0) {
        core->unk40 += (step > 0) ? step : -step;
        if (core->unk40 < core->unk44) {
            core->unk10 = (core->unk44 - core->unk40) / core->unk44;
        } else {
            controllerAnimCacheFree(owner, unk8);
            controllerAnimCacheFree(owner, unkC);
            core->unk78 &= ~0x10;
        }
        pos += ((step * win0->unk24) / 2) * (1.0f - core->unk10);
    } else {
        pos += step * win0->unk24;
    }
    controllerApplyMotionWindow((AnimScaleController *)owner, (AnimScaleState *)win0, pos);
    if (win4->unk0 != NULL) {
        if (core->unk28 < core->unk2C) {
            core->unk28 += core->unk2E;
            if (core->unk28 > core->unk2C) {
                core->unk28 = core->unk2C;
            }
        } else if (core->unk28 > core->unk2C) {
            core->unk28 -= core->unk2E;
            if (core->unk28 < core->unk2C) {
                core->unk28 = core->unk2C;
            }
        }
        pos = win4->unk4 + win4->unk24;
        controllerApplyMotionWindow((AnimScaleController *)owner, (AnimScaleState *)win4, pos);
        if ((win4->unk24 == 0) && (*(s16 *)&win4->unk1C & 0x10)) {
            core->unk2C = 0;
            if (core->unk28 == 0) {
                controllerAnimCacheFree(owner, win4);
            }
        }
    }
    actorScriptExecute(owner);
}

void controllerApplyMotionWindow(AnimScaleController *arg0_raw, AnimScaleState *arg1_raw, f32 timePos) {
    MotionOwner *controller = (MotionOwner *)arg0_raw;
    MotionWindow *scaleState = (MotionWindow *)arg1_raw;
    s8 new_var;
    f32 diff;
    f32 temp_fa0_2;
    f32 invSpan;
    f32 basePos;
    f32 lerpFactor;
    s16 temp_v0_2;
    s32 animData;
    s32 span;
    void *targetIdx;
    s32 prevIdx;
    s32 nextIdx;
    s32 rotOffset;
    u16 clampedPos;
    MotionCore *scaledPos;


    scaledPos = controller->unk4;
    clampedPos = scaleState->unk1C;
    basePos = scaleState->unk14;
    lerpFactor = scaleState->unk18;
    prevIdx = 0;
    nextIdx = 0;
    if (scaledPos->unk84 != 0) {
        targetIdx = scaledPos->unk4;
    } else {
        targetIdx = scaledPos->unk0;
    }
    if (clampedPos & 8) {
        diff = timePos - (f32) scaleState->unk1E;
        if (diff > 0) {
            scaleState->unk8 = diff;
        } else {
            scaleState->unk8 = -diff;
        }
        if ((f64) scaleState->unk8 < 1.0) {
            scaleState->unk4 = timePos;
            scaleState->unkC = scaleState->unk1E;
            scaleState->unkE = scaleState->unk20;
            return;
        }
        timePos += (f32) ((scaleState->unk20 - scaleState->unk1E) - (s32) diff);
        new_var = ~8;
        scaleState->unk1C = (u16) ((s16) scaleState->unk1C & new_var);
        if (scaleState == targetIdx) {
            scaledPos->unk78 &= ~0x20;
        }
    }
    if (clampedPos & 4) {
        if (lerpFactor < timePos) {
            nextIdx = 1;
            timePos = (2 * lerpFactor) - timePos;
        } else if (timePos < basePos) {
            nextIdx = 1;
            prevIdx = 1;
            timePos = (2 * basePos) - timePos;
        }
        if (nextIdx != 0) {
            scaleState->unk24 = 0.0f - scaleState->unk24;
            if (scaleState->unk34 != 0) {
                scaleState->unk2C = 0.0f - scaleState->unk2C;
                scaleState->unk28 = 0.0f - scaleState->unk28;
            }
            if (scaleState == targetIdx) {
                scaledPos->unk78 &= ~4;
            }
        }
    } else if (clampedPos & 2) {
        if (((f64) lerpFactor + 1.0) <= (f64) timePos) {
            prevIdx = 1;
            timePos -= (1.0f + lerpFactor) - basePos;
        } else if (timePos < basePos) {
            prevIdx = 1;
            timePos += (1.0f + lerpFactor) - basePos;
        }
    } else if (lerpFactor <= timePos) {
        timePos = lerpFactor;
        if (scaleState->unk24 >= 0.0f) {
            scaleState->unk24 = 0.0f;
            scaleState->unk34 = 0.0f;
            prevIdx = 1;
        }
    } else if (timePos < basePos) {
        timePos = basePos;
        prevIdx = 1;
        if (scaleState->unk24 <= 0.0f) {
            scaleState->unk24 = 0.0f;
            scaleState->unk34 = 0.0f;
        }
    }
    if (scaleState == targetIdx) {
        rotOffset = scaledPos->unk78;
        if (rotOffset & 0x3F) {
            if (prevIdx != 0) {
                animData = scaledPos->unk7C;
                scaledPos->unk78 = rotOffset & ~1;
                if (animData != 0) {
                    scaledPos->unk7C = animData - 1;
                    rotOffset = scaledPos->unk78;
                } else {
                    rotOffset = (scaledPos->unk78 &= ~2);
                }
            }
            if (rotOffset & 8) {
                temp_fa0_2 = scaledPos->unk80;
                invSpan = scaleState->unk4;
                if (timePos == temp_fa0_2) {
                    if (invSpan != temp_fa0_2) scaledPos->unk78 = rotOffset & ~8;
                } else if (temp_fa0_2 < timePos) {
                    if ((invSpan < temp_fa0_2) && (prevIdx == 0)) scaledPos->unk78 = rotOffset & ~8;
                    else if ((temp_fa0_2 < invSpan) && (prevIdx != 0)) scaledPos->unk78 = rotOffset & ~8;
                } else if ((temp_fa0_2 < invSpan) && (prevIdx == 0)) scaledPos->unk78 = rotOffset & ~8;
                else if ((invSpan < temp_fa0_2) && (prevIdx != 0)) scaledPos->unk78 = rotOffset & ~8;
            }
        }
    }
    scaleState->unk4 = timePos;
    scaleState->unkC = (s16) timePos;
    temp_v0_2 = scaleState->unkC;
    scaleState->unkE = temp_v0_2 + 1;
    scaleState->unk8 = timePos - (f32) temp_v0_2;
    if (lerpFactor < (f32) scaleState->unkE) {
        if (clampedPos & 2) {
            scaleState->unkE = (s16) basePos;
            return;
        }
        scaleState->unkE = temp_v0_2;
    }
}


typedef struct {
    u8 pad0[4];
    f32 unk4;
} ControllerParent;

typedef struct {
    ControllerParent *unk0;
} ControllerSubState;

typedef struct ControllerStateOwner {
    u8 pad0[4];
    ControllerSubState *unk4;
} ControllerStateOwner;

f32 actorGetAnimProgress(ControllerStateOwner *actor) {
    return actor->unk4->unk0->unk4;
}

typedef struct ControllerActorView {
    u8 pad0[4];
    void *unk4;
    s32 unk8;
    u8 padC[0x54];
    s32 unk60;
    u8 pad64[0x18];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
} ControllerActorView;

extern u8 gGfxBufferIndex;
void func_806195D0(f32, f32);
void actorTouchSub140Timestamp();
void actorCheckWorldBounds(ControllerActorView *actor) {
    f32 x = actor->unk7C;
    if (x >= -8192.0f) {
        f32 y = actor->unk80;
        if (y >= -8192.0f) {
            f32 z = actor->unk84;
            if ((z >= -8192.0f) && (x <= 8192.0f) && (y <= 8192.0f) && (z <= 8192.0f)) {
                actor->unk8 = *(s32 *) ((u8 *) actor->unk4 + (gGfxBufferIndex * 4) + 0x14);
                func_806195D0(z, 8192.0f);
                actorTouchSub140Timestamp(actor);
                actor->unk60 |= 0x200;
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

typedef struct RenderActorView {
    DisplayListGroup *unk0;
    u8 pad4[4];
    void *unk8;
    u8 padC[0x40];
    DisplayListGroup *unk4C;
    DisplayListGroup *unk50;
    u8 pad54[0xF2];
    u16 unk146;
} RenderActorView;

Gfx *animSetSegments(Gfx *, void *);
Gfx *renderEmitSegmentNodes(Gfx *, RenderActorView *, DisplayListGroup *);

Gfx *renderActorDisplayList(Gfx *gdl, RenderActorView *actor) {
    DisplayListGroup *display = actor->unk0;
    s32 i;

    if (actor->unk4C != NULL) {
        display = actor->unk4C;
    }
    if (actor->unk50 != NULL) {
        display = actor->unk50;
    }
    gdl = animSetSegments(gdl, actor);
    gdl = renderEmitSegmentNodes(gdl, actor, display);
    gSPSegment(gdl++, 4, osVirtualToPhysical(actor->unk8));
    gSPSegment(gdl++, 3, osVirtualToPhysical(display->unk0));
    for (i = 0; i < display->unk21; i++) {
        gSPDisplayList(gdl++, display->unk4[i]);
    }
    return gdl;
}

Gfx *renderEmitSegmentNodes(Gfx *gdl, RenderActorView *actor, DisplayListGroup *group) {
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

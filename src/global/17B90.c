#include "common.h"
#include "actor.h"

extern s16 D_807FBB30;
extern s16 D_807FBB32;
extern Struct807FD580 *gActivePlayerState;

typedef struct {
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
void *assetLoad(s32, s32, s32, s32);
extern u8 D_80746B64[];

void animListInit(void *, void *);
void controllerBuildSubcommandList();
void renderReplaceSegment6Commands();
void controllerCommandRelocateAssets();
void gfxSwapGeometryModeCullBits();

void *controllerAnimStateLoadAsset(arg0, arg1, arg2)
void *arg0;
s32 arg1;
unsigned char arg2;
{
    s32 i;
    ControllerAnimAssetView *asset;
    s32 delta;

    for (i = 0; i < (u16)D_807FBB30; i++) {
        if (arg1 == CONTROLLER_STATE_ENTRY(i).unk0 && CONTROLLER_STATE_ENTRY(i).unk8 == arg2) {
            CONTROLLER_STATE_ENTRY(i).unk2++;
            animListInit(arg0, CONTROLLER_STATE_ENTRY(i).unk4);
            return CONTROLLER_STATE_ENTRY(i).unk4;
        }
    }

    if ((u16)D_807FBB32 >= 0x20) {
        return D_807FB634;
    }

    asset = (ControllerAnimAssetView *)assetLoad(5, arg1 - 1, 1, 1);
    CONTROLLER_STATE_ENTRY(i).unk0 = arg1;
    D_807FBB30 = (u16)D_807FBB30 + 1;
    CONTROLLER_STATE_ENTRY(i).unk8 = arg2;
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
    animListInit(arg0, asset);

    if (arg2 & 1) {
        gfxSwapGeometryModeCullBits(*asset->unk4, asset->unk4);
    }

    return asset;
}

#ifdef NON_MATCHING
typedef struct GfxCmdWords {
    u32 unk0;
    u32 unk4;
} GfxCmdWords;
void gfxSwapGeometryModeCullBits(GfxCmdWords *arg0, GfxCmdWords *arg1) {
    u32 w0;
    u32 w1;
    s32 x1;
    s32 x2;
    w1 = 0; // FAKE: pre-loop def, extends w1 web over the loop (regalloc)
    w0 = 0; // FAKE: pre-loop def (regalloc)
    x2 = 0; // FAKE: pre-loop def (regalloc)
    if (arg0 != arg1) {
        do {
            w0 = arg0->unk0;
            w1 = arg0->unk4;
            if ((w0 >> 24) == 0xD9) {
                if (arg0->unk4 == 0) {
                    w0 = ~w0 & 0xFFFFFF;
                    if ((w0 & 0x600) == 0x200) {
                        x1 = w0 | 0x400;
                        x1 &= ~0x200;
                        arg0->unk0 = ~x1 | 0xD9000000;
                    } else if ((w0 & 0x600) == 0x400) {
                        x2 = w0 | 0x200;
                        x2 &= ~0x400;
                        arg0->unk0 = ~x2 | 0xD9000000;
                    }
                } else {
                    if ((w1 & 0x600) == 0x200) {
                        arg0->unk4 |= 0x400;
                        arg0->unk4 &= ~0x200;
                    } else if ((w1 & 0x600) == 0x400) {
                        arg0->unk4 |= 0x200;
                        if (x2 && x2) {} // FAKE: dead test, steers uopt colouring
                        arg0->unk4 &= ~0x400;
                    }
                    if (w0 && w0) {} // FAKE: dead test, steers uopt colouring
                }
            }
            arg0++;
            if (arg0 == arg1) {
                break;
            }
        } while (1);
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/gfxSwapGeometryModeCullBits.s")
#endif

void func_80613194(ControllerView *arg0, s16 arg1) {
    if (arg0->unk50 == NULL) {
        arg0->unk50 = controllerAnimStateLoadAsset(arg0, arg1, 0);
    }
}

void func_806131D4(ControllerView *arg0, s16 arg1) {
    if (arg0->unk50 == NULL) {
        arg0->unk50 = controllerAnimStateLoadAsset(arg0, arg1, 1);
    }
}

void func_80613214(ControllerView *arg0) {
    if (arg0->unk50 != NULL) {
        controllerAnimFreeSub(arg0, 2);
        arg0->unk50 = NULL;
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

void controllerBuildSubcommandList(ControllerSubCmd *arg0, ControllerSubCmd *arg1, ControllerSubNode **arg2) {
    ControllerSubCmd *curr;
    ControllerSubCmd *search;
    ControllerSubNode *node;
    u32 cmd0;
    u32 id;
    s32 found;
    u32 op;
    u32 sub;
    u32 search_cmd;
    curr = arg0;
    if (arg0 != arg1) {
        do {
            cmd0 = curr->unk0;
            op = cmd0 >> 24;
            sub = (cmd0 >> 16) & 0xFF;
            if (op) {} // FAKE: dead statement (op stays a coloured web)
            if (sub) {} // FAKE: dead statement (sub computed before the branch)
            if ((op == 0xDE) && (sub == 1)) {
                id = (curr->unk4 << 4) >> 28;
                if (op && op) {} // FAKE: dead statement (steers uopt colouring)
                search = arg0;
                found = 0;
                if (arg0 != arg1) {
                    do {
                        search_cmd = search->unk0;
                        if (((search_cmd >> 24) == 0) && (id == search->unk4)) {
                            found = 1;
                        } else {
                            search++;
                        }
                    } while (!found && (search != arg1));
                }
                node = heapAlloc(sizeof(ControllerSubNode));
                *arg2 = node;
                arg2 = &node->next;
                node->unk8 = id;
                node->unk0 = curr + 1;
                node->unk4 = search;
            }
            curr++;
        } while (curr != arg1);
    }
    *arg2 = NULL;
}

typedef struct {
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

typedef struct {
    ControllerCommandStorage *unk0;
    u8 pad4[0x5C];
    u32 unk60;
} ControllerCommandOwner;

void func_80613358(ControllerCommandOwner *arg0, s32 arg1, ControllerCommand *arg2) {
    u32 *arg2_words;
    ControllerCommand *commands;
    ControllerCommand *destination;

    arg2_words = &arg2->unk0;
    if (!(arg0->unk60 & 0x10)) {
        goto command_lookup;
command_lookup:
        commands = arg0->unk0->unk4->unk0;
        destination = commands + arg1;
        if ((destination->unk0 != *arg2_words) || (arg2->unk4 != destination->unk4)) {
            memcpy(destination, arg2, 8);
        }
    }
}

void controllerCommandRelocateAssets(ControllerCommand *arg0, ControllerCommand *arg1) {
    u32 temp_v0;

    if (arg0 != arg1) {
        do {
            temp_v0 = arg0->unk0;
            if ((temp_v0 >> 0x18) == (0, 0xFD)) { // FAKE: keeps bnel operand order
                temp_v0 = arg0->unk4;
                if (((temp_v0 * 0x10) >> 0x1C) == 0) {
                    arg0->unk4 = (u32)assetLoad(0x19, temp_v0 ^ 0, 0, 0); // FAKE: steers move a1, v0 into delay slot
                }
            }
            arg0++;
        } while (arg0 != arg1);
    }
}

typedef struct ControllerStateEntry {
    u16 unk0;
    u16 unk2;
    u32 unk4;
    u32 unk8;
} ControllerStateEntry;

extern ControllerStateEntry D_807FB630[];

u16 controllerLookupStateByHash(u32 *arg0) {
    u32 val = *arg0;
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

typedef struct {
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

typedef struct {
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

s32 controllerAnimInit(AnimControllerInit *arg0, u16 arg1) {
    AnimAssetEntry *resource;
    s32 i;
    void *alloc;
    AnimStateInit *anim;
    resource = controllerAnimStateLoadAsset(arg0, arg1, 0);
    if (resource != NULL) {
        arg0->unk0 = resource;
        arg0->unk4C = 0;
        arg0->unk50 = 0;

        alloc = heapAlloc((resource->unk20 << 7) + 0x170);
        arg0->unk4 = (AnimStateInit *)alloc;
        arg0->unk4->unk0 = (AnimSlotInit *)((u8 *)alloc + 0x90);
        arg0->unk4->unk4 = (AnimSlotInit *)((u8 *)alloc + 0xC8);
        arg0->unk4->unk8 = (AnimSlotInit *)((u8 *)alloc + 0x100);
        arg0->unk4->unkC = (AnimSlotInit *)((u8 *)alloc + 0x138);
        arg0->unk4->unk14 = (Mtx *)((u8 *)alloc + 0x170);
        arg0->unk4->unk18 = (Mtx *)((u8 *)arg0->unk4->unk14 + (resource->unk20 << 6));

        for (i = 0; i < resource->unk20; i++) {
            guMtxIdent((Mtx *)((u8 *)arg0->unk4->unk14 + (i << 6)));
            guMtxIdent((Mtx *)((u8 *)arg0->unk4->unk18 + (i << 6)));
        }

        guMtxIdentF(arg0->unkC);
        anim = arg0->unk4;
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

void func_806136B4(ControllerAnimView *arg0) {
    void *temp_a1;
    void *temp_a1_2;
    void *temp_a1_3;

    controllerAnimFreeSub((ControllerView *)arg0, 0);
    controllerAnimFreeSub((ControllerView *)arg0, 1);
    controllerAnimFreeSub((ControllerView *)arg0, 2);
    animListFree((u8 *)arg0 + 0x158);
    controllerAnimCacheFree(arg0, arg0->unk4->unk0);
    controllerAnimCacheFree(arg0, arg0->unk4->unk4);
    controllerAnimCacheFree(arg0, arg0->unk4->unk8);
    controllerAnimCacheFree(arg0, arg0->unk4->unkC);
    temp_a1 = arg0->unk4->unk1C;
    if (temp_a1 != NULL) {
        heapFreeDeferred(temp_a1);
    }
    temp_a1_2 = arg0->unk4->unk20;
    if (temp_a1_2 != NULL) {
        heapFreeDeferred(temp_a1_2);
    }
    temp_a1_3 = arg0->unk4->unk24;
    if (temp_a1_3 != NULL) {
        heapFreeDeferred(temp_a1_3);
    }
    heapFreeDeferred(arg0->unk4);
}
typedef struct {
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

#ifdef NON_MATCHING
void controllerAnimFreeSub(arg0, arg1)
ControllerViewB *arg0;
u8 arg1;
{
    ControllerSubB *sub;
    AnimStateSlot *entry;
    ControllerCmdB *cmd;
    ControllerCmdListB *cmdList;
    AnimStateSlot *last;
    u32 val;
    s16 idx;
    s32 i;
    switch (arg1) {
    case 0:
        sub = arg0->unk0;
        arg0->unk0 = NULL;
        break;
    case 1:
        sub = arg0->unk4C;
        arg0->unk4C = NULL;
        break;
    case 2:
        sub = arg0->unk50;
        arg0->unk50 = NULL;
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
        entry = (AnimStateSlot *)&D_807FB630[i];
        if (--entry->unk2 == 0) {
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

            idx = (u16)D_807FBB30 - 1;
            last = (AnimStateSlot *)&D_807FB630[(u16)idx];
            D_807FBB30 = idx;

            entry->unk0 = last->unk0;
            entry->unk4 = last->unk4;
            entry->unk8 = last->unk8;
            entry->unk2 = last->unk2;

            last->unk0 = 0;
            last->unk4 = 0;
            last->unk8 = 0;
            last->unk2 = 0;

            assetFreeBuffer((void *)sub, 0x281, 0x15);
            if (idx != 0) {} // FAKE: dead test, keeps idx referenced (colours the lhu temp)
        }
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/controllerAnimFreeSub.s")
#endif


#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/controllerAnimCacheFree.s")

typedef struct { u8 pad[0x14]; f32 a; f32 b; } AnimScaleState;
typedef struct { u8 pad[4]; f32 scale; u8 pad2[0xC]; f32 a; f32 b; } AnimScaleSpan;
typedef struct { AnimScaleState *state; u8 pad[4]; AnimScaleSpan *scale; } AnimScaleHolder;
typedef struct { u8 pad[4]; AnimScaleHolder *holder; } AnimScaleController;
void controllerApplyMotionWindow(AnimScaleController *, AnimScaleState *, f32);

void controllerAnimScaleInterpolate(AnimScaleController *arg0, s8 arg1) {
    f32 temp;
    s16 count = (s32)((arg0->holder->state->b - arg0->holder->state->a) + 1.0f);
    s16 span = (s32)((arg0->holder->scale->b - arg0->holder->scale->a) + 1.0f);
    temp = (arg0->holder->scale->scale * (f32)count) / (f32)span;
    temp += (f32)arg1;
    controllerApplyMotionWindow(arg0, arg0->holder->state, temp);
}


#ifdef NON_MATCHING
typedef struct {
    u8 pad0[0x4E];
    s16 unk4E;
} GlobalPlayerAnimView;

typedef struct {
    u8 pad0[0x58];
    s32 unk58;
} ControllerStateParamView;

extern u16 *D_807FBB58;
struct ControllerStateView;
void func_80613C48(struct ControllerStateView *, s16, f32, f32);

void func_80613AF8(struct ControllerStateView *arg0, s16 arg1, f32 arg2, f32 arg3) {
    s16 flag;
    s16 index;
    s32 sum;
    if (arg1 >= 0) {
        flag = arg1 & 0x4000;
        index = arg1 - flag;
        arg1 = arg1 & -1; // FAKE: no-code def, advances ugen ring / raises arg1 refs
        ((GlobalPlayerAnimView *)gActivePlayerState)->unk4E = index;
        if (flag == 0) {} // FAKE: dead test, steers flag into v1
        sum = index * 7 + ((ControllerStateParamView *)arg0)->unk58;
        sum -= 2;
        sum = sum & 0xFFFF;
        arg1 = D_807FBB58[sum] + flag;
    } else {
        ((GlobalPlayerAnimView *)gActivePlayerState)->unk4E = arg1;
    }
    func_80613C48(arg0, arg1, arg2, arg3);
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_80613AF8.s")
#endif


#ifdef NON_MATCHING
void controllerAnimSetState(struct ControllerStateView *, s16, f32, f32);

void func_80613BA0(struct ControllerStateView *arg0, s16 arg1, f32 arg2, f32 arg3) {
    s16 flag;
    s16 index;
    s32 sum;
    if (arg1 >= 0) {
        flag = arg1 & 0x4000;
        index = arg1 - flag;
        arg1 = arg1 & -1; // FAKE: no-code def, advances ugen ring / raises arg1 refs
        ((GlobalPlayerAnimView *)gActivePlayerState)->unk4E = index;
        if (flag == 0) {} // FAKE: dead test, steers flag into v1
        sum = index * 7 + ((ControllerStateParamView *)arg0)->unk58;
        sum -= 2;
        sum = sum & 0xFFFF;
        arg1 = D_807FBB58[sum] + flag;
    } else {
        ((GlobalPlayerAnimView *)gActivePlayerState)->unk4E = arg1;
    }
    controllerAnimSetState(arg0, arg1, arg2, arg3);
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_80613BA0.s")
#endif

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

void func_80613C48(ControllerStateView *arg0, s16 arg1, f32 arg2, f32 arg3) {
    ControllerState *state;

    state = arg0->unk4->unk0;
    if (arg1 == state->unk10) {
        state->unk24 = *(f32 *)state->unk0;
        return;
    }
    controllerAnimSetState(arg0, arg1, arg2, arg3);
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

void controllerAnimSetState(ControllerStateView *arg0, s16 arg1, f32 arg2, f32 arg3) {
    void *pad; // FAKE: frame pad (removing it changes the frame)
    AnimDataState *anim;
    AnimSlotState *slot0;
    AnimSlotState *slot4;
    AnimSlotState *slot8;
    AnimSlotState *slotC;
    AnimResourceState *resource;
    f32 temp_f;
    u8 temp_u;

    anim = (AnimDataState *)arg0->unk4;
    slot0 = anim->unk0;
    slot8 = anim->unk8;
    slot4 = anim->unk4;
    slotC = anim->unkC;

    if (slot8->unk0 != NULL) {
        controllerAnimCacheFree(arg0, slot8);
    }
    if (slotC->unk0 != NULL) {
        controllerAnimCacheFree(arg0, slotC);
    }

    if ((arg1 & 0x4000) == 0x4000) {
        arg1 -= 0x4000;
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

    if (arg3 > 0.0f) {
        temp_f = anim->unk48;
        if (temp_f > (f32)0) {
            anim->unk40 = temp_f;
        } else {
            anim->unk40 = -temp_f;
        }
        if (anim->unk40 < arg3) {
            anim->unk44 = arg3;
        } else {
            anim->unk44 = anim->unk40;
        }
        anim->unk10 = (anim->unk44 - anim->unk40) / anim->unk44;
    } else {
        if (slot0->unk0 != NULL) {
            controllerAnimCacheFree(arg0, slot0);
        }
        if (slot4->unk0 != NULL) {
            controllerAnimCacheFree(arg0, slot4);
        }
    }

    resource = controllerAnimCacheGetOrLoad(arg1);
    if (resource != NULL) {
        slot8->unk0 = resource;
        slot8->unk10 = arg1;
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
    temp_u = ((u8 *)&anim->unk28)[1];
    anim->unkC = slot4;
    anim->unk0 = slot8;
    anim->unk4 = slotC;
    anim->unk28 = anim->unk2A;
    anim->unk2A = temp_u;
    controllerApplyMotionWindow((AnimScaleController *)arg0, (AnimScaleState *)slot8, arg2);
}


typedef struct {
    u8 pad0[0x58];
    s32 unk58;
} ControllerActorTypeView;
extern u16 *D_807FBB58;
struct AnimControllerRef;
void func_80614014(struct AnimControllerRef *, u16, f32, u8);

void controllerAnimSetFromTable(ControllerActorTypeView *arg0, u16 arg1, f32 arg2, u8 arg3) {
    u16 x = arg1;
    u16 idx = (u16)(7 * x + arg0->unk58 - 2);
    if (x) {} // FAKE: dead test makes the copy of arg1 a ring temp (move t6,a1) and the sum v0
    func_80614014((struct AnimControllerRef *)arg0, D_807FBB58[idx], arg2, arg3);
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


void func_80614014(AnimControllerRef *arg0, u16 arg1, f32 arg2, u8 arg3) {
    AnimSlotRef *slot;
    AnimResourceSlot *resource;

    slot = arg0->unk4->unk4;
    if (slot->unk0 != NULL) {
        controllerAnimCacheFree(arg0, slot);
    }
    resource = controllerAnimCacheGetOrLoad(arg1);
    if (resource != NULL) {
        slot->unk0 = resource;
        slot->unk10 = arg1;
        slot->unk1C = resource->unk4;
        slot->unk14 = 0.0f;
        slot->unk18 = (f32)(resource->unk12 - 1);
        slot->unk34 = 0.0f;
        slot->unk24 = resource->unk0;
        slot->unk2C = resource->unk0;
        slot->unk28 = resource->unk0;
        slot->unk30 = 0.0f;
        arg0->unk4->unk28 = 0;
        arg0->unk4->unk2C = 0xFF;
        arg0->unk4->unk2E = arg3;
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
    controllerApplyMotionWindow((AnimScaleController *)arg0, (AnimScaleState *)slot, arg2);
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

extern u32 D_80744478;
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

typedef struct {
    u8 pad0[4];
    MotionCore *unk4;
} MotionOwner;

void controllerStepMotionWindows(MotionOwner *arg0) {
    MotionCore *core;
    MotionWindow *win0;
    MotionWindow *win4;
    void *unk8;
    void *unkC;
    f32 pos[1]; // FAKE: one-element array keeps pos memory-resident (not coloured)
    f32 rate;
    f32 step;

    core = arg0->unk4;
    win0 = core->unk0;
    win4 = core->unk4;
    unk8 = core->unk8;
    unkC = core->unkC;
    pos[0] = win0->unk4;
    if (core->unk30 & 1) {
        rate = (f32) ((f64) (u32) D_80744478 * 0.5);
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
            controllerAnimCacheFree(arg0, unk8);
            controllerAnimCacheFree(arg0, unkC);
            core->unk78 &= ~0x10;
        }
        pos[0] += ((step * win0->unk24) / 2) * (1.0f - core->unk10);
    } else {
        pos[0] += step * win0->unk24;
    }
    controllerApplyMotionWindow((AnimScaleController *)arg0, (AnimScaleState *)win0, pos[0]);
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
        pos[0] = win4->unk4 + win4->unk24;
        controllerApplyMotionWindow((AnimScaleController *)arg0, (AnimScaleState *)win4, pos[0]);
        if ((win4->unk24 == 0) && (*(s16 *)&win4->unk1C & 0x10)) {
            core->unk2C = 0;
            if (core->unk28 == 0) {
                controllerAnimCacheFree(arg0, win4);
            }
        }
    }
    actorScriptExecute(arg0);
}

void controllerApplyMotionWindow(AnimScaleController *arg0_raw, AnimScaleState *arg1_raw, f32 arg2) {
    MotionOwner *arg0 = (MotionOwner *)arg0_raw;
    MotionWindow *arg1 = (MotionWindow *)arg1_raw;
    s8 new_var;
    f32 temp_fa0;
    f32 temp_fa0_2;
    f32 temp_ft4;
    f32 temp_fv0;
    f32 temp_fv1;
    s16 temp_v0_2;
    s32 temp_a0;
    s32 temp_t2;
    void *var_a0;
    s32 var_a2;
    s32 var_a3;
    s32 var_v1;
    u16 temp_v1;
    MotionCore *temp_v0;


    temp_v0 = arg0->unk4;
    temp_v1 = arg1->unk1C;
    temp_fv0 = arg1->unk14;
    temp_fv1 = arg1->unk18;
    var_a2 = 0;
    var_a3 = 0;
    if (temp_v0->unk84 != 0) {
        var_a0 = temp_v0->unk4;
    } else {
        var_a0 = temp_v0->unk0;
    }
    if (temp_v1 & 8) {
        temp_fa0 = arg2 - (f32) arg1->unk1E;
        if (temp_fa0 > 0) {
            arg1->unk8 = temp_fa0;
        } else {
            arg1->unk8 = -temp_fa0;
        }
        if ((f64) arg1->unk8 < 1.0) {
            arg1->unk4 = arg2;
            arg1->unkC = arg1->unk1E;
            arg1->unkE = arg1->unk20;
            return;
        }
        arg2 += (f32) ((arg1->unk20 - arg1->unk1E) - (s32) temp_fa0);
        new_var = ~8;
        arg1->unk1C = (u16) ((s16) arg1->unk1C & new_var);
        if (arg1 == var_a0) {
            temp_v0->unk78 &= ~0x20;
        }
    }
    if (temp_v1 & 4) {
        if (temp_fv1 < arg2) {
            var_a3 = 1;
            arg2 = (2 * temp_fv1) - arg2;
        } else if (arg2 < temp_fv0) {
            var_a3 = 1;
            var_a2 = 1;
            arg2 = (2 * temp_fv0) - arg2;
        }
        if (var_a3 != 0) {
            arg1->unk24 = 0.0f - arg1->unk24;
            if (arg1->unk34 != 0) {
                arg1->unk2C = 0.0f - arg1->unk2C;
                arg1->unk28 = 0.0f - arg1->unk28;
            }
            if (arg1 == var_a0) {
                temp_v0->unk78 &= ~4;
            }
        }
    } else if (temp_v1 & 2) {
        if (((f64) temp_fv1 + 1.0) <= (f64) arg2) {
            var_a2 = 1;
            arg2 -= (1.0f + temp_fv1) - temp_fv0;
        } else if (arg2 < temp_fv0) {
            var_a2 = 1;
            arg2 += (1.0f + temp_fv1) - temp_fv0;
        }
    } else if (temp_fv1 <= arg2) {
        arg2 = temp_fv1;
        if (arg1->unk24 >= 0.0f) {
            arg1->unk24 = 0.0f;
            arg1->unk34 = 0.0f;
            var_a2 = 1;
        }
    } else if (arg2 < temp_fv0) {
        arg2 = temp_fv0;
        var_a2 = 1;
        if (arg1->unk24 <= 0.0f) {
            arg1->unk24 = 0.0f;
            arg1->unk34 = 0.0f;
        }
    }
    if (arg1 == var_a0) {
        var_v1 = temp_v0->unk78;
        if (var_v1 & 0x3F) {
            if (var_a2 != 0) {
                temp_a0 = temp_v0->unk7C;
                temp_v0->unk78 = var_v1 & ~1;
                if (temp_a0 != 0) {
                    temp_v0->unk7C = temp_a0 - 1;
                    var_v1 = temp_v0->unk78;
                } else {
                    var_v1 = (temp_v0->unk78 &= ~2);
                }
            }
            if (var_v1 & 8) {
                temp_fa0_2 = temp_v0->unk80;
                temp_ft4 = arg1->unk4;
                if (arg2 == temp_fa0_2) {
                    if (temp_ft4 != temp_fa0_2) temp_v0->unk78 = var_v1 & ~8;
                } else if (temp_fa0_2 < arg2) {
                    if ((temp_ft4 < temp_fa0_2) && (var_a2 == 0)) temp_v0->unk78 = var_v1 & ~8;
                    else if ((temp_fa0_2 < temp_ft4) && (var_a2 != 0)) temp_v0->unk78 = var_v1 & ~8;
                } else if ((temp_fa0_2 < temp_ft4) && (var_a2 == 0)) temp_v0->unk78 = var_v1 & ~8;
                else if ((temp_ft4 < temp_fa0_2) && (var_a2 != 0)) temp_v0->unk78 = var_v1 & ~8;
            }
        }
    }
    arg1->unk4 = arg2;
    arg1->unkC = (s16) arg2;
    temp_v0_2 = arg1->unkC;
    arg1->unkE = temp_v0_2 + 1;
    arg1->unk8 = arg2 - (f32) temp_v0_2;
    if (temp_fv1 < (f32) arg1->unkE) {
        if (temp_v1 & 2) {
            arg1->unkE = (s16) temp_fv0;
            return;
        }
        arg1->unkE = temp_v0_2;
    }
}


typedef struct {
    u8 pad0[4];
    f32 unk4;
} ControllerParent;

typedef struct {
    ControllerParent *unk0;
} ControllerSubState;

typedef struct {
    u8 pad0[4];
    ControllerSubState *unk4;
} ControllerStateOwner;

f32 func_80614A54(ControllerStateOwner *arg0) {
    return arg0->unk4->unk0->unk4;
}

typedef struct {
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

extern u8 D_807444FC;
void func_806195D0(f32, f32);
void actorTouchSub140Timestamp();
void func_80614A64(ControllerActorView *arg0) {
    f32 x = arg0->unk7C;
    if (x >= -8192.0f) {
        f32 y = arg0->unk80;
        if (y >= -8192.0f) {
            f32 z = arg0->unk84;
            if ((z >= -8192.0f) && (x <= 8192.0f) && (y <= 8192.0f) && (z <= 8192.0f)) {
                arg0->unk8 = *(s32 *) ((u8 *) arg0->unk4 + (D_807444FC * 4) + 0x14);
                func_806195D0(z, 8192.0f);
                actorTouchSub140Timestamp(arg0);
                arg0->unk60 |= 0x200;
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

typedef struct {
    void *unk0;
    Gfx **unk4;
    u8 pad8[0xC];
    SegmentNode *unk14;
    u8 pad18[9];
    u8 unk21;
} DisplayListGroup;

typedef struct {
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

Gfx *renderEmitSegmentNodes(Gfx *gdl, RenderActorView *arg1, DisplayListGroup *arg2) {
    u16 flags = arg1->unk146;
    SegmentNode *node = arg2->unk14;
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

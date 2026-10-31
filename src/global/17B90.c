#include "common.h"
#include "actor.h"

extern s16 D_807FBB30;
extern s16 D_807FBB32;
extern Struct807FD580 *D_807FD580;

typedef struct {
    u8 unk0[0x50];
    void *unk50;
} ControllerView;


void *func_80612E90(void *, s32, s32);
void func_80613794();

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_80612E90.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_806130A4.s")

void func_80613194(ControllerView *arg0, s16 arg1) {
    if (arg0->unk50 == NULL) {
        arg0->unk50 = func_80612E90(arg0, arg1, 0);
    }
}

void func_806131D4(ControllerView *arg0, s16 arg1) {
    if (arg0->unk50 == NULL) {
        arg0->unk50 = func_80612E90(arg0, arg1, 1);
    }
}

void func_80613214(ControllerView *arg0) {
    if (arg0->unk50 != NULL) {
        func_80613794(arg0, 2);
        arg0->unk50 = NULL;
    }
}

typedef struct RvD2_Cmd {
    u32 unk0;
    u32 unk4;
} RvD2_Cmd;

typedef struct RvD2_Node {
    RvD2_Cmd *unk0;
    RvD2_Cmd *unk4;
    u8 unk8;
    struct RvD2_Node *next;
} RvD2_Node;

void *heapAlloc(s32);

#ifdef NON_MATCHING
void func_8061324C(RvD2_Cmd *arg0, RvD2_Cmd *arg1, RvD2_Node **arg2) {
    RvD2_Cmd *curr;
    RvD2_Cmd *search;
    RvD2_Node **tail;
    RvD2_Node *node;
    u32 cmd0;
    u32 id;
    s32 found;
    u32 search_cmd;

    curr = arg0;
    tail = arg2;
    if (arg0 != arg1) {
        do {
            cmd0 = curr->unk0;
            if (((cmd0 >> 24) == (0, 0xDE)) && (((cmd0 >> 16) & 0xFF) == (0, 1))) {
                id = (u32)(curr->unk4 * 0x10) >> 0x1C;
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
                node = heapAlloc(sizeof(RvD2_Node));
                *tail = node;
                tail = &node->next;
                node->unk8 = id;
                node->unk0 = curr + 1;
                node->unk4 = search;
            }
            curr++;
        } while (curr != arg1);
    }
    *tail = NULL;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_8061324C.s")
#endif

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
void *assetLoad(s32, s32, s32, s32);

void func_806133C8(ControllerCommand *arg0, ControllerCommand *arg1) {
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

typedef struct {
    u16 unk0;
    u16 unk2;
    u32 unk4;
    u32 unk8;
} RvD_StateEntry;

extern RvD_StateEntry D_807FB630[];

u16 func_80613448(u32 *arg0) {
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
} RvT2_SlotB;

typedef struct {
    RvT2_SlotB *unk0;
    RvT2_SlotB *unk4;
    RvT2_SlotB *unk8;
    RvT2_SlotB *unkC;
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
} RvT2_AnimB;

typedef struct {
    void *unk0;
    RvT2_AnimB *unk4;
    u8 pad8[4];
    f32 unkC[4][4];
    s32 unk4C;
    s32 unk50;
} RvT2_ControllerB;

#ifdef NON_MATCHING
s32 func_806134B4(RvT2_ControllerB *arg0, u16 arg1) {
    void *resource;
    s32 i;
    void *alloc;
    RvT2_AnimB *anim;
    resource = func_80612E90(arg0, arg1, 0);
    if (resource != NULL) {
        arg0->unk0 = resource;
        arg0->unk4C = 0;
        arg0->unk50 = 0;

        alloc = heapAlloc((*(u8 *)((u8 *)resource + 0x20) << 7) + 0x170);
        arg0->unk4 = (RvT2_AnimB *)alloc;
        arg0->unk4->unk0 = (RvT2_SlotB *)((u8 *)alloc + 0x90);
        arg0->unk4->unk4 = (RvT2_SlotB *)((u8 *)alloc + 0xC8);
        arg0->unk4->unk8 = (RvT2_SlotB *)((u8 *)alloc + 0x100);
        arg0->unk4->unkC = (RvT2_SlotB *)((u8 *)alloc + 0x138);
        arg0->unk4->unk14 = (Mtx *)((u8 *)alloc + 0x170);
        arg0->unk4->unk18 = (Mtx *)((u8 *)arg0->unk4->unk14 + (*(u8 *)((u8 *)resource + 0x20) << 6));

        for (i = 0; i < *(u8 *)((u8 *)resource + 0x20); i++) {
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
        anim->unk80 = 0.0f;

        return 1;
    }
    return 0;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_806134B4.s")
#endif

void func_806136B4(ControllerAnimView *arg0) {
    void *temp_a1;
    void *temp_a1_2;
    void *temp_a1_3;

    func_80613794((ControllerView *)arg0, 0);
    func_80613794((ControllerView *)arg0, 1);
    func_80613794((ControllerView *)arg0, 2);
    animListFree((u8 *)arg0 + 0x158);
    func_80613944(arg0, arg0->unk4->unk0);
    func_80613944(arg0, arg0->unk4->unk4);
    func_80613944(arg0, arg0->unk4->unk8);
    func_80613944(arg0, arg0->unk4->unkC);
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
} RvT2_ControllerView;

typedef struct {
    u32 unk0;
    u32 unk4;
} RvT2_ControllerCommand;

typedef struct {
    RvT2_ControllerCommand *start;
} RvT2_ControllerCommandList;

typedef struct {
    u8 pad0[4];
    RvT2_ControllerCommandList *commands;
} RvT2_ControllerSub;

void assetFreeBuffer(void *, s32, s32);

struct RvE2_CacheEntry {
    s32 id;
    s32 refCount;
    void *asset;
};
extern struct RvE2_CacheEntry D_807FB7B0[];

#ifdef NON_MATCHING
void func_80613794(arg0, arg1)
RvT2_ControllerView *arg0;
u8 arg1;
{
    RvT2_ControllerSub *sub;
    RvD_StateEntry *entry;
    RvT2_ControllerCommand *cmd;
    RvT2_ControllerCommandList *cmdList;
    RvD_StateEntry *last;
    u32 val;

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
        entry = D_807FB630;
        do {
            if (entry->unk4 == (u32)sub) {
                break;
            }
        } while (++entry != (RvD_StateEntry *)D_807FB7B0);

        if (entry == (RvD_StateEntry *)D_807FB7B0) {
            return;
        }

        if (--entry->unk2 == 0) {
            cmdList = sub->commands;
            cmd = cmdList->start;
            if (cmd != (RvT2_ControllerCommand *)cmdList) {
                do {
                    if ((cmd->unk0 >> 24) == (0, 0xFD)) {
                        val = cmd->unk4;
                        if ((val >= 0x80000000) && (val < 0xA0000000)) {
                            assetFreeBuffer((void *)(val ^ 0), 0x270, 0x15);
                        }
                    }
                    cmd++;
                } while ((RvT2_ControllerCommand *)cmdList != cmd);
            }

            val = D_807FBB30 - 1;
            last = &D_807FB630[(u16)val];
            D_807FBB30 = val;

            entry->unk0 = last->unk0;
            entry->unk4 = last->unk4;
            entry->unk8 = last->unk8;
            entry->unk2 = last->unk2;

            last->unk0 = 0;
            last->unk4 = 0;
            last->unk8 = 0;
            last->unk2 = 0;

            assetFreeBuffer((void *)sub, 0x281, 0x15);
        }
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_80613794.s")
#endif

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_80613944.s")

typedef struct { u8 pad[0x14]; f32 a; f32 b; } RvE_State;
typedef struct { u8 pad[4]; f32 scale; u8 pad2[0xC]; f32 a; f32 b; } RvE_Scale;
typedef struct { RvE_State *state; u8 pad[4]; RvE_Scale *scale; } RvE_Holder;
typedef struct { u8 pad[4]; RvE_Holder *holder; } RvE_Controller;
void func_80614644(RvE_Controller *, RvE_State *, f32);

void func_80613A50(RvE_Controller *arg0, s8 arg1) {
    f32 temp;
    s16 count = (s32)((arg0->holder->state->b - arg0->holder->state->a) + 1.0f);
    s16 span = (s32)((arg0->holder->scale->b - arg0->holder->scale->a) + 1.0f);
    temp = (arg0->holder->scale->scale * (f32)count) / (f32)span;
    temp += (f32)arg1;
    func_80614644(arg0, arg0->holder->state, temp);
}


#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_80613AF8.s")


#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_80613BA0.s")

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


void func_80613CA8(ControllerStateView *, s16, f32, f32);

void func_80613C48(ControllerStateView *arg0, s16 arg1, f32 arg2, f32 arg3) {
    ControllerState *state;

    state = arg0->unk4->unk0;
    if (arg1 == state->unk10) {
        state->unk24 = *(f32 *)state->unk0;
        return;
    }
    func_80613CA8(arg0, arg1, arg2, arg3);
}

typedef struct {
    f32 unk0;
    u16 unk4;
    u8 pad6[0xC];
    u8 unk12;
} RvT2_Resource;

typedef struct {
    RvT2_Resource *unk0;
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
} RvT2_Slot;

typedef struct {
    RvT2_Slot *unk0;
    RvT2_Slot *unk4;
    RvT2_Slot *unk8;
    RvT2_Slot *unkC;
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
} RvT2_AnimData;
void *func_80614130(s32 id);

#ifdef NON_MATCHING
void func_80613CA8(ControllerStateView *arg0, s16 arg1, f32 arg2, f32 arg3) {
    void *pad;
    RvT2_AnimData *anim;
    RvT2_Slot *slot0;
    RvT2_Slot *slot4;
    RvT2_Slot *slot8;
    RvT2_Slot *slotC;
    RvT2_Resource *resource;
    f32 temp_f;
    s16 temp_s;
    u8 temp_u;

    anim = (RvT2_AnimData *)arg0->unk4;
    slot0 = anim->unk0;
    slot8 = anim->unk8;
    slot4 = anim->unk4;
    slotC = anim->unkC;

    if (slot8->unk0 != NULL) {
        func_80613944(arg0, slot8);
    }
    if (slotC->unk0 != NULL) {
        func_80613944(arg0, slotC);
    }

    if ((arg1 & 0x4000) == 0x4000) {
        arg1 -= 0x4000;
        if (slot4->unk0 != NULL) {
            slotC->unk0 = func_80614130(slot4->unk10);
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
        if (temp_f > 0.0f) {
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
            func_80613944(arg0, slot0);
        }
        if (slot4->unk0 != NULL) {
            func_80613944(arg0, slot4);
        }
    }

    resource = func_80614130(arg1);
    if (resource != NULL) {
        slot8->unk0 = resource;
        slot8->unk10 = arg1;
        slot8->unk1C = resource->unk4;
        slot8->unk14 = 0.0f;
        slot8->unk34 = 0.0f;
        slot8->unk18 = (f32)(resource->unk12 - 1);
        slot8->unk24 = resource->unk0;
        slot8->unk2C = resource->unk0;
        slot8->unk28 = resource->unk0;
        slot8->unk30 = 0.0f;
    } else {
        slot8->unk0 = NULL;
        slot8->unk10 = -1;
        slot8->unk1C = 0;
        slot8->unk14 = 0.0f;
        slot8->unk18 = 0.0f;
        slot8->unk34 = 0.0f;
        slot8->unk24 = 0.0f;
        slot8->unk2C = 0.0f;
        slot8->unk28 = 0.0f;
        slot8->unk30 = 0.0f;
    }

    anim->unk78 = 0;
    anim->unk7C = 0;
    anim->unk80 = 0.0f;
    temp_u = ((u8 *)&anim->unk28)[1];
    temp_s = anim->unk2A;
    anim->unkC = slot4;
    anim->unk0 = slot8;
    anim->unk4 = slotC;
    anim->unk8 = slot0;
    anim->unk2A = temp_u;
    anim->unk28 = temp_s;
    func_80614644((RvE_Controller *)arg0, (RvE_State *)slot8, arg2);
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_80613CA8.s")
#endif


#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_80613FB0.s")

typedef struct {
    f32 unk0;
    u16 unk4;
    u8 pad6[0xC];
    u8 unk12;
} RvE3_Resource;

typedef struct {
    RvE3_Resource *unk0;
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
} RvE3_Slot;

typedef struct {
    void *unk0;
    RvE3_Slot *unk4;
    u8 pad8[0x20];
    s16 unk28;
    u8 pad2A[2];
    s16 unk2C;
    s16 unk2E;
} RvE3_Anim;

typedef struct {
    void *unk0;
    RvE3_Anim *unk4;
} RvE3_Controller;


void func_80614014(RvE3_Controller *arg0, u16 arg1, f32 arg2, u8 arg3) {
    RvE3_Slot *slot;
    RvE3_Resource *resource;

    slot = arg0->unk4->unk4;
    if (slot->unk0 != NULL) {
        func_80613944(arg0, slot);
    }
    resource = func_80614130(arg1);
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
    func_80614644((RvE_Controller *)arg0, (RvE_State *)slot, arg2);
}

typedef struct RvE2_CacheEntry RvE2_CacheEntry;
extern RvE2_CacheEntry D_807FB7B0[];

void *func_80614130(s32 id) {
    RvE2_CacheEntry *entry;
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
void func_80614D90(void *);

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
} RvR1_MotionWindow;

typedef struct {
    RvR1_MotionWindow *unk0;
    RvR1_MotionWindow *unk4;
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
} RvR1_MotionCore;

typedef struct {
    u8 pad0[4];
    RvR1_MotionCore *unk4;
} RvR1_MotionOwner;

#ifdef NON_MATCHING
void func_8061421C(RvR1_MotionOwner *arg0) {
    RvR1_MotionCore *core;
    RvR1_MotionWindow *win0;
    RvR1_MotionWindow *win4;
    void *unk8;
    void *unkC;
    f32 pos;
    f32 rate;
    f32 step;

    core = arg0->unk4;
    win0 = core->unk0;
    win4 = core->unk4;
    unk8 = core->unk8;
    pos = win0->unk4;
    unkC = core->unkC;
    rate = 1.0f;
    if (core->unk30 & 1) {
        rate = (f32) ((f64) (u32) D_80744478 * 0.5);
    }
    core->unk30 &= ~1;
    if (D_80746B60 == 0) {
        core->unk30 |= (win0->unk1C & 1);
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
            func_80613944(arg0, unk8);
            func_80613944(arg0, unkC);
            core->unk78 &= ~0x10;
        }
        pos += ((step * win0->unk24) / 2.0f) * (1.0f - core->unk10);
    } else {
        pos += step * win0->unk24;
    }
    func_80614644((RvE_Controller *)arg0, (RvE_State *)win0, pos);
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
        func_80614644((RvE_Controller *)arg0, (RvE_State *)win4, pos);
        if ((win4->unk24 == 0.0f) && (win4->unk1C & 0x10)) {
            core->unk2C = 0;
            if (core->unk28 == 0) {
                func_80613944(arg0, win4);
            }
        }
    }
    func_80614D90(arg0);
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_8061421C.s")
#endif

#ifdef NON_MATCHING
void func_80614644(RvE_Controller *arg0_raw, RvE_State *arg1_raw, f32 arg2) {
    RvR1_MotionOwner *arg0 = (RvR1_MotionOwner *)arg0_raw;
    RvR1_MotionWindow *arg1 = (RvR1_MotionWindow *)arg1_raw;
    f32 temp_fa0;
    f32 temp_fa0_2;
    f32 temp_ft4;
    f32 temp_fv0;
    f32 temp_fv1;
    s16 temp_v0_2;
    s32 temp_a0;
    s32 temp_t2;
    s8 mask;
    void *var_a0;
    s32 var_a2;
    s32 var_a3;
    s32 var_v1;
    u16 temp_v1;
    RvR1_MotionCore *temp_v0;


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
        mask = 0xFFF7;
        arg1->unk1C = (u16) ((s16) arg1->unk1C & mask);
        if (arg1 == var_a0) {
            temp_v0->unk78 &= ~0x20;
        }
    }
    mask = ~8;
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
            if (arg1->unk34 != 0.0f) {
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
                temp_t2 = var_v1 & ~1;
                temp_v0->unk78 = temp_t2;
                if (temp_a0 != 0) {
                    temp_v0->unk7C = temp_a0 - 1;
                    var_v1 = temp_t2;
                } else {
                    var_v1 = temp_v0->unk78 & ~2;
                    temp_v0->unk78 = var_v1;
                }
            }
            if (var_v1 & 8) {
                temp_fa0_2 = temp_v0->unk80;
                temp_ft4 = arg1->unk4;
                if (arg2 == temp_fa0_2) {
                    if (temp_ft4 != temp_fa0_2) temp_v0->unk78 = var_v1 & mask;
                } else if (temp_fa0_2 < arg2) {
                    if ((temp_ft4 < temp_fa0_2) && (var_a2 == 0)) temp_v0->unk78 = var_v1 & mask;
                    else if ((temp_fa0_2 < temp_ft4) && (var_a2 != 0)) temp_v0->unk78 = var_v1 & mask;
                } else if ((temp_fa0_2 < temp_ft4) && (var_a2 == 0)) temp_v0->unk78 = var_v1 & mask;
                else if ((temp_fa0_2 < temp_ft4) && (var_a2 != 0)) temp_v0->unk78 = var_v1 & mask;
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
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_80614644.s")
#endif

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

typedef struct RvF_SegmentNode {
    void *unk0;
    void *unk4;
    u8 unk8;
    struct RvF_SegmentNode *unkC;
} RvF_SegmentNode;

typedef struct {
    void *unk0;
    Gfx **unk4;
    u8 pad8[0xC];
    RvF_SegmentNode *unk14;
    u8 pad18[9];
    u8 unk21;
} RvF_Display;

typedef struct {
    RvF_Display *unk0;
    u8 pad4[4];
    void *unk8;
    u8 padC[0x40];
    RvF_Display *unk4C;
    RvF_Display *unk50;
    u8 pad54[0xF2];
    u16 unk146;
} RvF_Actor;

Gfx *animSetSegments(Gfx *, void *);
Gfx *func_80614C38(Gfx *, RvF_Actor *, RvF_Display *);

Gfx *func_80614B34(Gfx *gdl, RvF_Actor *actor) {
    RvF_Display *display = actor->unk0;
    s32 i;

    if (actor->unk4C != NULL) {
        display = actor->unk4C;
    }
    if (actor->unk50 != NULL) {
        display = actor->unk50;
    }
    gdl = animSetSegments(gdl, actor);
    gdl = func_80614C38(gdl, actor, display);
    gSPSegment(gdl++, 4, osVirtualToPhysical(actor->unk8));
    gSPSegment(gdl++, 3, osVirtualToPhysical(display->unk0));
    for (i = 0; i < display->unk21; i++) {
        gSPDisplayList(gdl++, display->unk4[i]);
    }
    return gdl;
}

Gfx *func_80614C38(Gfx *gdl, RvF_Actor *arg1, RvF_Display *arg2) {
    u16 flags = arg1->unk146;
    RvF_SegmentNode *node = arg2->unk14;
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

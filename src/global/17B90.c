#include "common.h"
#include "actor.h"

extern s16 D_807FBB30;
extern s16 D_807FBB32;
extern Struct807FD580 *D_807FD580;

typedef struct {
    u8 unk0[0x50];
    void *unk50;
} ControllerView;


void *func_80612E90(void *, s16, s32);
void func_80613794(ControllerView *, s32);

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

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_806134B4.s")

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

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_80613794.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_80613944.s")

typedef struct { u8 pad[0x14]; f32 a; f32 b; } RvE_State;
typedef struct { u8 pad[4]; f32 scale; u8 pad2[0xC]; f32 a; f32 b; } RvE_Scale;
typedef struct { RvE_State *state; u8 pad[4]; RvE_Scale *scale; } RvE_Holder;
typedef struct { u8 pad[4]; RvE_Holder *holder; } RvE_Controller;
void func_80614644(RvE_Controller *, RvE_State *, f32, s16);

void func_80613A50(RvE_Controller *arg0, s8 arg1) {
    f32 temp;
    s16 count = (s32)((arg0->holder->state->b - arg0->holder->state->a) + 1.0f);
    s16 span = (s32)((arg0->holder->scale->b - arg0->holder->scale->a) + 1.0f);
    temp = (arg0->holder->scale->scale * (f32)count) / (f32)span;
    temp += (f32)arg1;
    func_80614644(arg0, arg0->holder->state, temp, count);
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

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_80613CA8.s")


#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_80613FB0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_80614014.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_80614130.s")
#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_8061421C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/17B90/func_80614644.s")

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

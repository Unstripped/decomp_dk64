#include "common.h"
#include "actor.h"

typedef struct ActorPayloadA69C {
    f32 unk0;
    f32 unk4;
    u8 unk8;
    u8 unk9;
} ActorPayloadA69C;

typedef struct ActorPayloadA70C {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    u8 unkC;
    u8 unkD;
} ActorPayloadA70C;

typedef struct ActorPayloadAAB8 {
    s16 unk0;
    f32 unk4;
    s16 unk8;
} ActorPayloadAAB8;

typedef struct ActorPayloadA7EC {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    s32 unkC;
    u8 unk10;
} ActorPayloadA7EC;

typedef struct ActorPayloadABC0 {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    s16 unkC;
    s16 unkE;
} ActorPayloadABC0;

extern u16 D_8074D624[];
extern u8 D_807F94B4;
extern ActorEntry D_807FB930[];
extern u16 D_807FBB34;
extern Actor *D_807FBB40;
extern Actor *D_807FBB44;
extern Actor *D_807FBB48;
extern ActorGlobalState D_807FBB70;
extern u8 D_807FBE08;
extern u8 D_807FBE09;
extern Actor *D_807FBE10[];
extern s16 D_807FBF10;
extern ActorQueueEntry D_807FBF18[16];
extern s16 D_807FBFD8;
extern ActorCallbackNode *D_807FBFE0[];
extern s32 D_807FBFF0[];
extern s16 D_807FC3F0;

void *func_80610FE8(s32);
void func_8061421C();
void func_80614A64(Actor *);
ActorSub140 *func_80665F24(Actor *);
void func_806663F8(Actor *);
void func_80669A6C(Actor *);
void func_80672B1C(Actor *);
void func_80675EE0(Actor *);
void func_806761EC(Actor *);
void func_80677EC8(s32);
s32 func_80678014(s32);
s32 func_80678050(s32);
void func_806782C0(Actor *);
s32 func_806782E8(Actor *);
void func_806783BC(void);
void func_80678428(Actor *);
void func_80678530(s32);
void func_806785D4(Actor *);
void func_806787CC(void);
static void func_806787EC(void);
static void func_806787F4(void);
static void func_806787FC(void);
static void func_80678804(void);
static void func_8067880C(void);
static void func_80678814(void);
static void func_8067881C(void);
void func_80678B04(void);
void func_80678BBC(Actor *);
void func_80678DD8(Actor *);
void func_80678E14(Actor *);
void func_80678F64(Actor *);
void func_80678F9C(Actor *, s32);
s32 func_80679010(Actor *, s32);
void func_80679064(ActorCallbackNode *);
void func_80679178(Actor *);
void func_806791DC(Actor *, s32);
void func_806791EC(Actor *, s32);
void func_80679200(Actor *, s32, s32, u8, s32, void *);
void func_80679290(s32, s32, s32, u8, s32, void *, s32);
ActorCallbackNode *func_80679490(s32, s32, u8, s32, void *);
void func_806794EC(Actor *);
void func_8067A170(s32, u8);
void func_8067A69C(s32, Actor *, f32, f32, u8, u8);
void func_8067A70C(s32, Actor *, f32, f32, f32, u8, u8);
void func_8067A784(s32, Actor *, s16, f32, s16);
void func_8067A7EC(s32, Actor *, f32, f32, f32, s32, u8);
void func_8067A99C(s32, Actor *, s32);
void func_8067A9F0(s32, Actor *, f32, f32, f32);
void func_8067AA58(s32, Actor *, f32, f32);
void func_8067AAB8(s32, Actor *, s16, f32, s16);
void func_8067ABC0(s32, Actor *, u8, s16, s16, f32, f32, f32);
void func_8067AC38(void);
void func_8067ACB4(Actor *);
u16 func_8067ACC0(u16);
void func_8067AE58(void);
s32 func_8067AF44();
s32 func_8067AF74();
void func_8067B100(Actor *);
void func_8067B2B0(s32);
void func_8067B2B8(s32);
s32 func_8067B2C0(s32);
s32 func_8067B3F4(s32);
s32 func_8067B42C(s32);
void func_80689418(void);
void func_806897F0(void);
void func_806EB194(void);
void func_80732354(s32, s32, s32, s32);
void heapFree(void *);

typedef struct R3B_StructFB630 {
    s16 unk0;
    s16 unk2;
    s32 unk4;
    s32 unk8;
} R3B_StructFB630;

typedef struct R3B_StructFB7B0 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} R3B_StructFB7B0;

typedef struct R3B_Header {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} R3B_Header;

extern R3B_StructFB630 D_807FB630[32];
extern R3B_StructFB7B0 D_807FB7B0[32];
extern s16 D_807FBB30;
extern s16 D_807FBB32;
extern R3B_Header *D_807FBB50;
extern void *D_807FBB54;
extern void *D_807FBB58;
extern void *D_807FBB5C;
extern s32 D_807FBB38;

void *func_8066B0F8(s32, s32, s32, s32);

void func_80677D80(void) {
    u16 i;

    for (i = 0; i < 32; i++) {
        D_807FB630[i].unk0 = 0;
        D_807FB630[i].unk2 = 0;
        D_807FB630[i].unk4 = 0;
    }
    D_807FBB30 = 0;

    for (i = 0; i < 32; i++) {
        D_807FB7B0[i].unk0 = 0xFFFF;
        D_807FB7B0[i].unk4 = 0;
        D_807FB7B0[i].unk8 = 0;
    }
    D_807FBB32 = 0;

    D_807FBB50 = (R3B_Header *)func_8066B0F8(0xD, 0, 1, 1);
    D_807FBB54 = (void *)(D_807FBB50->unkC + (s32)D_807FBB50);
    D_807FBB58 = (void *)(D_807FBB50->unk8 + (s32)D_807FBB50);
    D_807FBB5C = (void *)(D_807FBB50->unk4 + (s32)D_807FBB50);

    for (i = 0; i < 64; i++) {
        D_807FB930[i].actor = NULL;
        D_807FB930[i].unk4 = 0;
    }
    D_807FBB34 = 0;

    func_8067AE58();

    D_807FBB38 = 0;
    D_807FBE09 = 0;
    D_807FBFD8 = 0;
    D_807FBB48 = NULL;
}

void func_80677EC8(s32 arg0) {
}

typedef struct R2ASpawnInfo {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    s16 unk18;
    s16 unk1A;
    s32 unk1C;
} R2ASpawnInfo;
void func_80614EBC(Actor *, s32);
extern u8 D_8074D8D4[];
extern s32 (*D_8074DA30[])(s32 *);

s32 func_80677ED0(R2ASpawnInfo *arg0) {
    u8 temp;
    if (func_80678050((u16)arg0->unk0)) {
        temp = D_8074D8D4[arg0->unk0];
        if (D_8074DA30[temp](&arg0->unk4)) {
            D_807FBB44->unk7C = arg0->unkC;
            D_807FBB44->unk80 = arg0->unk10;
            D_807FBB44->unk84 = arg0->unk14;
            D_807FBB44->unk124 = arg0->unk1C;
            D_807FBB44->unkE6 = arg0->unk18;
            D_807FBB44->unk15C = arg0->unk1A;
            if (arg0->unk8 != 0) {
                func_80614EBC(D_807FBB44, arg0->unk8);
            }
            return 1;
        }
    }
    return 0;
}
s32 func_80677FA8(s32 arg0, s32 arg1) {
    u8 temp;
    if (func_80678050((u16)arg0)) {
        temp = D_8074D8D4[arg0];
        if (D_8074DA30[temp](&arg1)) {
            return 1;
        }
    }
    return 0;
}

s32 func_80678014(s32 arg0) {
    if (func_80678050(arg0 & 0xFFFF) != 0) {
        func_8067B2C0(0);
        return 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/7CA80/func_80678050.s")

void func_806782C0(Actor *arg0) {
    func_806897F0();
    func_806782E8(arg0);
}

s32 func_806782E8(Actor *arg0) {
    s32 i;

    if (D_807FBE09 != 0) {
        if (D_807FBF10 == 0x40) {
            func_80732354(0xC, 0, 0, 0);
        }
        if (arg0 == D_807FBB40) {
            D_807FBE08 = 1;
        }
        for (i = 0; i < D_807FBF10; i++) {
            if (arg0 == D_807FBE10[i]) {
                return 0;
            }
        }
        D_807FBE10[D_807FBF10] = arg0;
        D_807FBF10++;
    } else {
        func_806785D4(arg0);
    }
    return 1;
}

void func_806783BC(void) {
    s32 i;
    for (i = 0; i < D_807FBF10; i++) {
        func_806785D4(D_807FBE10[i]);
    }
    D_807FBF10 = 0;
}

void func_80678428(Actor *arg0) {
    D_807FB930[D_807FBB34].actor = arg0;
    D_807FB930[D_807FBB34].unk4 = 0;
    D_807FBB34++;
}

void func_80605314(Actor *, s32);
void func_8062D26C(Actor *);
void func_80678458(Actor *arg0) {
    s16 i;

    func_80605314(arg0, 0);
    func_80605314(arg0, 1);
    i = 0;
    if (arg0 != D_807FB930[0].actor && D_807FBB34 > 0) {
        do {
            i++;
            if (arg0 == D_807FB930[i].actor) {
                break;
            }
        } while (i < D_807FBB34);
    }
    if (--D_807FBB34 != 0) {
        D_807FB930[i].actor = D_807FB930[D_807FBB34].actor;
        D_807FB930[i].unk4 = D_807FB930[D_807FBB34].unk4;
    }
    func_8062D26C(arg0);
    arg0->unk150 = 0;
}

void func_80678530(s32 arg0) {
    s32 i;

    D_807FBE09 = 1;
    D_807FBF10 = 0;
    for (i = 0; i < D_807FBB34; i++) {
        Actor *actor = D_807FB930[i].actor;
        if (arg0 == actor->unk11C) {
            func_806782C0(actor);
            actor->unk11C = 0;
        }
    }
    D_807FBE09 = 0;
    func_806783BC();
}

void func_806136B4(void);
void func_8071586C(Actor *);
void func_807233B4(Actor *);
void func_8066E21C(ActorSub140 *);
void func_8072F09C(Actor *);
void func_8070DA74(Actor *);
void func_8068C2F8(Actor *);
void func_8067AEFC();
typedef struct R2EActor {
    /* 0x000 */ s32 unk0;
    /* 0x004 */ u8 pad04[0x54];
    /* 0x058 */ s32 unk58;
    /* 0x05C */ u8 pad5C[0xBC];
    /* 0x118 */ void *unk118;
    /* 0x11C */ Actor *unk11C;
    /* 0x120 */ u8 pad120[0x20];
    /* 0x140 */ ActorSub140 *unk140;
    /* 0x144 */ u8 pad144[4];
    /* 0x148 */ void *unk148;
    /* 0x14C */ void *unk14C;
} R2EActor;

void func_806785D4(Actor *arg0) {
    s16 i;
    Actor *temp;

    if (((R2EActor *)arg0)->unk0 != 0) {
        func_806136B4();
    }
    temp = (Actor *)arg0->unk11C;
    if (temp != NULL) {
        func_80679200(temp, (s32)arg0, 0x80000, 0, 0, NULL);
    }
    for (i = 0; i < D_807FBB34; i++) {
        if ((s32)arg0 == D_807FB930[i].actor->unk11C) {
            D_807FB930[i].actor->unk11C = 0;
        }
    }
    i = 0;
    func_8071586C(arg0);
    func_807233B4(arg0);
    func_80605314(arg0, 0);
    func_80605314(arg0, 1);
    if (D_807FB930[0].actor != arg0) {
        if (D_807FBB34 > 0) {
            do {
                i++;
                if (D_807FB930[i].actor == arg0) {
                    break;
                }
            } while (i < D_807FBB34);
        }
    }
    if (i != D_807FBB34) {
        if (--D_807FBB34 != 0) {
            D_807FB930[i].actor = D_807FB930[D_807FBB34].actor;
            D_807FB930[i].unk4 = D_807FB930[D_807FBB34].unk4;
        }
    }
    func_8066E21C(arg0->unk140);
    func_8072F09C(arg0);
    if (((R2EActor *)arg0)->unk118 != NULL) {
        heapFree(((R2EActor *)arg0)->unk118);
    }
    if (((R2EActor *)arg0)->unk148 != NULL) {
        heapFree(((R2EActor *)arg0)->unk148);
    }
    if (((R2EActor *)arg0)->unk14C != NULL) {
        heapFree(((R2EActor *)arg0)->unk14C);
    }
    func_8062D26C(arg0);
    if (arg0->unk58 != 0x12B) {
        func_8070DA74(arg0);
    }
    func_8068C2F8(arg0);
    func_8067AEFC(arg0);
    heapFree(arg0);
}

void func_806787CC(void) {
    func_80689418();
}

static void func_806787EC(void) {}
static void func_806787F4(void) {}
static void func_806787FC(void) {}
static void func_80678804(void) {}
static void func_8067880C(void) {}
static void func_80678814(void) {}
static void func_8067881C(void) {}

#pragma GLOBAL_ASM("asm/global/nonmatchings/7CA80/func_80678824.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7CA80/func_8067889C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7CA80/func_806789E4.s")

void func_80678B04(void) {
    s32 i;
    for (i = 0; i < D_807FBB34; i++) {
        Actor *actor = D_807FB930[i].actor;
        if (!(actor->unk60 & 0x08000000) && (actor->unk60 & 0x500) && (actor->unk60 & 0x4000)) {
            func_80614A64(actor);
        }
        actor->unk60 &= ~0x100;
    }
}

void func_80678BBC(Actor *arg0) {
    func_806663F8(arg0);
    if (arg0->unk5C & 1) {
        func_8067B100(arg0);
    }
    arg0->unk88 = arg0->unk7C;
    arg0->unk8C = arg0->unk80;
    arg0->unk90 = arg0->unk84;
    arg0->unkBC = arg0->unkB8;
    D_807F94B4 = 0;
    if (arg0->unk140 != NULL) {
        arg0->unk140->unk68 = 0;
    }
    func_80678F64(arg0);
    if (arg0 == D_807FBB48) {
        func_80675EE0(arg0);
    } else {
        func_806761EC(arg0);
    }
    func_806794EC(arg0);
    if (arg0 == D_807FBB48) {
        func_806EB194();
    }
    if (arg0->unk144 & 4) {
        func_80672B1C(arg0);
    } else if (arg0->unk140 != NULL) {
        arg0->unk140->unk6C = 0;
    }
    if (arg0->unk110 != 0) {
        func_80669A6C(arg0);
    }
}

typedef struct R3B_Actor {
    u8 pad[0x156];
    u8 unk156;
} R3B_Actor;

void func_80665FB4(Actor *);
void func_80678E6C(Actor *);
void func_8066EBF4(Actor *);
void func_806790F4(s32);
void func_8067A1DC(Actor *);
void func_80685D84(Actor *);
void func_80687F7C(Actor *);

void func_80678CC8(Actor *actor) {
    if ((void *)func_8067B3F4 == (void *)D_8074DA30[D_8074D8D4[actor->unk58]]) {
        guTranslateF((void *)((u8 *)actor + 0xC), actor->unk7C, actor->unk80, actor->unk84);
    }
    func_80665FB4(actor);
    func_80678E6C(actor);
    if (!(actor->unk60 & 0x08000000)) {
        actor->unk60 &= ~0x200;
        if (actor->unk4 != NULL) {
            func_8061421C(actor);
            if (((actor->unk60 & 0x500) || ((R3B_Actor *)actor)->unk156 != 0) && !(actor->unk60 & 0x4000)) {
                func_80614A64(actor);
            }
        }
    }
    func_80678E14(actor);
    func_8066EBF4(actor);
    func_806790F4(0);
    func_8067A1DC(actor);
    func_80679178(actor);
    func_80685D84(actor);
    func_80687F7C(actor);
    actor->unk60 |= 0x10;
}

void func_80678DD8(Actor *actor) {
    func_8061421C();
    if (actor->unk60 & 0x500) {
        func_80614A64(actor);
    }
}

void func_80678E14(Actor *actor) {
    f32 temp_fv0 = actor->unk80;

    if (actor->unk8C < temp_fv0) {
        actor->unk9C = temp_fv0;
        return;
    }
    if (actor->unk6A & 5) {
        if (actor->unk6C & 5) {
            actor->unk9C = temp_fv0;
            return;
        }
        actor->unkA0 = actor->unk9C;
    }
}

u8 func_8066F250();
extern u8 D_807FBC55;
void func_806EB0C0(s32, s32, u8);
extern u8 D_807FC929;

void func_80678E6C(Actor *actor) {
    u8 sp27;

    if ((actor->unk144 & 4) && (D_807FBE08 == 0)) {
        if (actor->unk60 & 0x10000) {
            actor->unkFC = 0;
            actor->unkFD = 0;
        }
        actor->unkFC |= func_8066F250(actor, &actor->unkF4, &actor->unkF6, &sp27);
        sp27 |= D_807FBC55;
        if (sp27 != 0) {
            if (!(actor->unk6A & 0x10)) {
                actor->unk6A |= 0x10;
                if (actor == D_807FBB48) {
                    func_806EB0C0(4, 0, D_807FC929);
                }
            }
        }
        if (sp27 == 0) {
            actor->unk6A &= ~0x10;
        }
    } else {
        actor->unkFC = 0;
        actor->unkFD = 0;
        actor->unk6A &= ~0x10;
    }
}

void func_80678F64(Actor *actor) {
    if (actor->unk114 != NULL) {
        heapFree(actor->unk114);
        actor->unk114 = NULL;
    }
}

void func_80678F9C(Actor *actor, s32 item) {
    if (actor->unk114 == NULL) {
        actor->unk114 = func_80610FE8(sizeof(ActorList));
        actor->unk114->count = 0;
    }
    if (actor->unk114->count != 4) {
        actor->unk114->items[actor->unk114->count] = item;
        actor->unk114->count++;
    }
}

s32 func_80679010(Actor *actor, s32 item) {
    ActorList *list = actor->unk114;
    s32 i;

    if (list == NULL) {
        return 0;
    }
    for (i = 0; i < list->count; i++) {
        if (list->items[i] == item) {
            return 1;
        }
    }
    return 0;
}

void func_80679064(ActorCallbackNode *arg0) {
    s32 i = 0;
    s32 found = 0;

    while ((i < 4) && (!found)) {
        if (D_807FBFE0[i] == NULL) {
            found = 1;
        } else {
            i++;
        }
    }
    if (!found) {
        func_80732354(0xE, 0, 0, 0);
    } else {
        D_807FBFE0[i] = arg0;
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/7CA80/func_806790F4.s")

void func_80679178(Actor *actor) {
    ActorCallbackNode *node = actor->unk13C;
    ActorCallbackNode *next;

    if (node != NULL) {
        actor->unk13C = NULL;
    }
    while (node != NULL) {
        next = node->next;
        if (node->unk10 != NULL) {
            heapFree(node->unk10);
        }
        heapFree(node);
        node = next;
    }
}

void func_806791DC(Actor *actor, s32 mask) {
    actor->unk138 |= mask;
}

void func_806791EC(Actor *actor, s32 mask) {
    actor->unk138 &= ~mask;
}

void func_80679200(Actor *actor, s32 arg1, s32 arg2, u8 arg3, s32 arg4, void *arg5) {
    s32 pad;
    ActorCallbackNode **link;
    ActorCallbackNode *prev;
    ActorCallbackNode *curr;
    ActorCallbackNode *node;

    prev = NULL;
    if (func_8067AF44(actor)) {
        curr = actor->unk13C;
        link = &actor->unk13C;
        if (curr != NULL) {
            do {
                link = &curr->next;
                prev = curr;
                curr = curr->next;
            } while (curr != NULL);
        }
        node = func_80679490(arg1, arg2, arg3, arg4, arg5);
        *link = node;
        node->prev = prev;
    }
}

void func_80679290(s32 arg0, s32 arg1, s32 arg2, u8 arg3, s32 arg4, void *arg5, s32 arg6) {
    if (D_807FBFD8 == 16) {
        func_80732354(0xF, 0, 0, 0);
    }
    D_807FBF18[D_807FBFD8].node = func_80679490(arg1, arg2, arg3, arg4, arg5);
    D_807FBF18[D_807FBFD8].arg0 = arg0;
    D_807FBF18[D_807FBFD8].arg6 = arg6;
    D_807FBFD8++;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/7CA80/func_80679334.s")

ActorCallbackNode *func_80679490(s32 arg0, s32 arg1, u8 arg2, s32 arg3, void *arg4) {
    ActorCallbackNode *node = func_80610FE8(sizeof(ActorCallbackNode));

    node->callback = (void *)arg1;
    node->unk4 = arg2;
    node->unk8 = arg0;
    node->unkC = arg3;
    node->unk10 = arg4;
    node->next = NULL;
    return node;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/7CA80/func_806794EC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7CA80/func_80679DC4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7CA80/func_8067A09C.s")

void func_8067A170(s32 arg0, u8 arg1) {
    s32 i;

    for (i = 0; i < D_807FBB70.unk201; i++) {
        if ((D_807FBB70.unk244[i] == arg1) && (D_807FBB70.unk204[i] == arg0)) {
            D_807FBB70.unk244[i] = 0;
        }
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/7CA80/func_8067A1DC.s")

void func_8067A69C(s32 arg0, Actor *arg1, f32 arg2, f32 arg3, u8 arg4, u8 arg5) {
    ActorPayloadA69C *temp = func_80610FE8(sizeof(ActorPayloadA69C));
    temp->unk0 = arg2;
    temp->unk4 = arg3;
    temp->unk8 = arg4;
    temp->unk9 = arg5;
    func_80679200(arg1, arg0, 0x10, 0, 1, temp);
}

void func_8067A70C(s32 arg0, Actor *arg1, f32 arg2, f32 arg3, f32 arg4, u8 arg5, u8 arg6) {
    ActorPayloadA70C *temp = func_80610FE8(sizeof(ActorPayloadA70C));
    temp->unk0 = arg2;
    temp->unk4 = arg3;
    temp->unk8 = arg4;
    temp->unkC = arg5;
    temp->unkD = arg6;
    func_80679200(arg1, arg0, 0x20, 0, 1, temp);
}

void func_8067A784(s32 arg0, Actor *arg1, s16 arg2, f32 arg3, s16 arg4) {
    ActorPayloadAAB8 *temp = func_80610FE8(sizeof(ActorPayloadAAB8));
    temp->unk0 = arg2;
    temp->unk4 = arg3;
    temp->unk8 = arg4;
    func_80679200(arg1, arg0, 0x4000, 0, 1, temp);
}

void func_8067A7EC(s32 arg0, Actor *arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, u8 arg6) {
    ActorPayloadA7EC *temp = func_80610FE8(sizeof(ActorPayloadA7EC));
    temp->unk0 = arg2;
    temp->unk4 = arg3;
    temp->unk8 = arg4;
    temp->unkC = arg5;
    temp->unk10 = arg6;
    func_80679200(arg1, arg0, 0x1, 0, 1, temp);
}

typedef struct R2DActorPayloadA864 {
    s16 unk0;
    s16 unk2;
    u8 unk4[0xC];
    u8 unk10[0x24];
    s32 unk34;
    s32 unk38;
    s32 unk3C;
} R2DActorPayloadA864;

void func_8067A864(s32 arg0, Actor *arg1, s16 arg2, s16 arg3, void *arg4, void *arg5, s32 arg6, s32 arg7, s32 arg8) {
    R2DActorPayloadA864 *temp = func_80610FE8(sizeof(R2DActorPayloadA864));
    temp->unk0 = arg2;
    temp->unk2 = arg3;
    memcpy(temp->unk4, arg4, 0xC);
    memcpy(temp->unk10, arg5, 0x24);
    temp->unk34 = arg6;
    temp->unk38 = arg7;
    temp->unk3C = arg8;
    func_80679200(arg1, arg0, 0x10000, 0, 1, temp);
}

typedef struct R2DActorPayloadA908 {
    u8 unk0[0xC];
    u8 unkC[0x24];
    s32 unk30;
    s32 unk34;
    s32 unk38;
} R2DActorPayloadA908;

void func_8067A908(s32 arg0, Actor *arg1, void *arg2, void *arg3, s32 arg4, s32 arg5, s32 arg6) {
    R2DActorPayloadA908 *temp = func_80610FE8(sizeof(R2DActorPayloadA908));
    memcpy(temp, arg2, 0xC);
    memcpy((u8 *)temp + 0xC, arg3, 0x24);
    temp->unk30 = arg4;
    temp->unk34 = arg5;
    temp->unk38 = arg6;
    func_80679200(arg1, arg0, 0x20000, 0, 1, temp);
}

void func_8067A99C(s32 arg0, Actor *arg1, s32 arg2) {
    s32 *temp = func_80610FE8(sizeof(s32));
    *temp = arg2;
    func_80679200(arg1, arg0, 0x40000, 0, 1, temp);
}

void func_8067A9F0(s32 arg0, Actor *arg1, f32 arg2, f32 arg3, f32 arg4) {
    f32 *temp = func_80610FE8(3 * sizeof(f32));
    temp[0] = arg2;
    temp[1] = arg3;
    temp[2] = arg4;
    func_80679200(arg1, arg0, 0x100000, 0, 1, temp);
}

void func_8067AA58(s32 arg0, Actor *arg1, f32 arg2, f32 arg3) {
    f32 *temp = func_80610FE8(2 * sizeof(f32));
    temp[0] = arg2;
    temp[1] = arg3;
    func_80679200(arg1, arg0, 0x200000, 0, 1, temp);
}

void func_8067AAB8(s32 arg0, Actor *arg1, s16 arg2, f32 arg3, s16 arg4) {
    ActorPayloadAAB8 *temp = func_80610FE8(sizeof(ActorPayloadAAB8));
    temp->unk4 = arg3;
    temp->unk8 = arg4;
    temp->unk0 = arg2;
    func_80679200(arg1, arg0, 0x400, 0, 1, temp);
}

void func_8067AB20(s32 arg0, Actor *arg1, s32 arg2, u8 arg3, void *arg4, u8 arg5) {
    void *temp = func_80610FE8(8);
    memcpy(temp, arg4, 8);
    if (!arg5) {
        func_80679200(arg1, arg0, arg2, arg3, 1, temp);
    } else {
        func_80679290((s32)arg1, arg0, arg2, arg3, 1, temp, 1);
    }
}

void func_8067ABC0(s32 arg0, Actor *arg1, u8 arg2, s16 arg3, s16 arg4, f32 arg5, f32 arg6, f32 arg7) {
    ActorPayloadABC0 *temp = func_80610FE8(sizeof(ActorPayloadABC0));
    temp->unk0 = arg5;
    temp->unk4 = arg6;
    temp->unk8 = arg7;
    temp->unkC = arg3;
    temp->unkE = arg4;
    func_80679200(arg1, arg0, 0x800000, arg2, 1, temp);
}

void func_8067AC38(void) {
    D_807FBB70.unkE5 = 0;
    D_807FBB70.unk15 = 0;
    D_807FBB70.unk16 = 0;
    D_807FBB70.unk17 = 0;
    D_807FBB70.unk18 = 0;
    D_807FBB70.unk19 = 0;
    D_807FBB70.unk1B = 0;
    D_807FBB70.unk1A = 0;
    D_807FBB70.unk1C = 0;
    D_807FBB70.unk24 = 0;
    D_807FBB70.unk25 = 0;
    D_807FBB70.unk2C = 0;
    D_807FBB70.unk38 = 0;
    D_807FBB70.unkE4 = 0;
    D_807FBB70.unk90 = 0;
    D_807FBB70.unk39 = 0;
    D_807FBB70.unk91 = 0;
    D_807FBB70.unk1F8 = 0;
    D_807FBB70.unk1FC = 0;
    D_807FBB70.unk200 = 0;
    D_807FBB70.unk201 = 0;
    D_807FBB70.unk254 = 0;
    D_807FBB70.unk2 = 0;
    D_807FBB70.unk0 = 0;
    D_807FBB70.unkE8 = 0.0f;
    D_807FBB70.unkF0 = 0.0f;
    D_807FBB70.unkF4 = 0.0f;
}

void func_8067ACB4(Actor *arg0) {
    arg0->unk6C = arg0->unk6A;
}

u16 func_8067ACC0(u16 arg0) {
    return D_8074D624[arg0];
}

s32 func_8067ACDC(arg0, arg1, arg2)
s32 arg0;
u16 arg1;
s32 (*arg2)(Actor *);
{
    u16 count = 0;
    s32 i;

    for (i = 0; i < D_807FBB34; i++) {
        Actor *actor = D_807FB930[i].actor;
        if (arg0 == actor->unk11C && actor->unk5C == arg1) {
            if (arg2 == NULL || arg2(actor)) {
                count++;
            }
        }
    }
    return count;
}

typedef struct R2CEntry2F0 {
    u8 unk0;
    char pad1[3];
    s32 unk4;
    char pad8[0x2F0 - 8];
} R2CEntry2F0;
extern R2CEntry2F0 *D_807FC924;
extern u8 D_807FC928;

void func_8067B01C(void);

Actor *func_8067ADB4(u16 arg0) {
    s32 i;
    for (i = 0; i < D_807FBB34; i++) {
        Actor *actor = D_807FB930[i].actor;
        if (actor->unk58 == arg0) {
            return actor;
        }
    }
    return NULL;
}

s32 func_8067AE0C(Actor *arg0) {
    s32 i;
    for (i = 0; i < D_807FBB34; i++) {
        Actor *actor = D_807FB930[i].actor;
        if (arg0 == actor) {
            return 1;
        }
    }
    return 0;
}

void func_8067AE58(void) {
    s32 i;
    for (i = 0; i < 256; i++) {
        D_807FBFF0[i] = -1;
    }
    D_807FC3F0 = 0;
}

void func_8067AE90(Actor *arg0) {
    if (D_807FC3F0 < 256) {
        D_807FBFF0[D_807FC3F0++] = (s32)arg0;
    } else {
        func_80732354(0x13, arg0->unk58, 0, 0);
    }
    func_8067B01C();
}

void func_8067AEFC() {
    s32 res = func_8067AF74();
    s16 idx = res;
    if ((u32)res != (u32)-1) {
        D_807FBFF0[idx] = -1;
        func_8067B01C();
    }
}

s32 func_8067AF44(void) {
    if (func_8067AF74() != -1) {
        return 1;
    }
    return 0;
}

s32 func_8067AF74(u32 arg0) {
    s16 low = 0;
    s16 high = D_807FC3F0 - 1;

    if (D_807FC3F0 == 0) {
        return -1;
    }
    while (low <= high) {
        s16 mid = (low + high) >> 1;

        if (arg0 == D_807FBFF0[mid]) {
            return mid;
        }
        if (arg0 < D_807FBFF0[mid]) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return -1;
}

void func_8067B01C(void) {
    s32 done = FALSE;
    s16 i;
    s16 j;

    for (i = 1; i < D_807FC3F0; i++) {
        u32 val = D_807FBFF0[i];

        j = i;
        if (val < (u32)D_807FBFF0[j - 1]) {
            do {
                D_807FBFF0[j] = D_807FBFF0[j - 1];
                j--;
            } while (val < (u32)D_807FBFF0[j - 1]);
        }
        D_807FBFF0[j] = val;
    }
    D_807FC3F0 = 0;
    do {
        if (D_807FBFF0[D_807FC3F0] == -1) {
            done = TRUE;
        } else {
            D_807FC3F0++;
        }
    } while (!done);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/7CA80/func_8067B100.s")

u8 func_8067B1E0(s32 arg0) {
    s32 i;
    for (i = 0; i < D_807FC928; i++) {
        if (D_807FC924[i].unk0 != 0 && arg0 == D_807FC924[i].unk4) {
            return (u8)i;
        }
    }
    return 0;
}

void func_8067B238(Actor *arg0, Actor *arg1, f32 arg2) {
    arg0->unk7C = arg1->unk7C;
    arg0->unk80 = arg1->unk80;
    arg0->unk84 = arg1->unk84;
    arg0->unkE6 = arg1->unkE6;
    if (arg0->unk4 != NULL) {
        arg0->unk4->unk34 = arg2;
        arg0->unk4->unk38 = arg2;
        arg0->unk4->unk3C = arg2;
    }
}

void func_8067B280(void) {}
void func_8067B288(void) {}
void func_8067B290(void) {}
void func_8067B298(void) {}
void func_8067B2A0(void) {}
void func_8067B2A8(void) {}

void func_8067B2B0(s32 arg0) {
}

void func_8067B2B8(s32 arg0) {
}

s32 func_8067B2C0(s32 arg0) {
    D_807FBB44->unk144 = 1;
    return 1;
}

s32 func_806134B4(Actor *, u16, void *);

typedef struct R2EActorSub140 {
    u8 pad0[0xC];
    s32 unkC;
} R2EActorSub140;

typedef struct R2EArgB2DC {
    u8 pad0[2];
    u16 unk2;
} R2EArgB2DC;

s32 func_8067B2DC(R2EArgB2DC *arg0) {
    if (func_806134B4(D_807FBB44, arg0->unk2, arg0) != 0) {
        D_807FBB44->unk140 = func_80665F24(D_807FBB44);
        D_807FBB44->unk15E = (u32)(((f64)((R2EActorSub140 *)D_807FBB44->unk140)->unkC * 0.15) * 0.5);
        return 1;
    }
    return 0;
}

s32 func_8067B3F4(s32 arg0) {
    D_807FBB44->unk140 = func_80665F24(D_807FBB44);
    return 1;
}

s32 func_8067B42C(s32 arg0) {
    D_807FBB44->unk60 |= 0x2000;
    return 1;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/7CA80/D_80759260.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7CA80/D_80759268.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7CA80/D_80759270.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7CA80/D_80759278.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7CA80/D_80759280.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7CA80/D_80759288.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7CA80/D_80759290.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7CA80/D_80759298.s")

#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB44;
extern Actor *D_807FBB48;
extern Actor *D_807FBB4C;
extern void *D_807FC924;
extern u8 D_807FC928;
extern u8 D_807FC929;
extern u8 D_807FC950[][0x5E];
extern s32 D_8076A0A8;
extern u8 D_8076A0AB;
extern u8 D_8076A0B1;
extern s16 D_80744490;
extern s16 D_80744494;
extern u8 D_807444F8;
extern u8 D_807444FC;

extern s32 func_806FBD5C(s16, s32);
void func_806FC530(s32, s16, s16, s16, s32, u8);

void func_806FD8E0(s32 arg0, s16 arg1, s32 arg2, s16 arg3, u8 arg4) {
    s16 width;
    s16 height;

    width = (D_80744490 - func_806FBD5C(arg1, arg2)) * 2;
    height = arg3 * 4;
    func_806FC530(arg0, arg1, width, height, arg2, arg4);
}

void func_806FD950(s32 arg0, s16 arg1, s32 arg2, s16 arg3) {
    func_806FC530(arg0, arg1, 0x60, (s16)(arg3 * 4), arg2, 1);
}

typedef struct R1F1025E0Entry {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
} R1F1025E0Entry;

typedef struct R1F1025E0Node {
    struct R1F1025E0Node *next;
    void *unk4;
    R1F1025E0Entry *unk8;
    s8 unkC;
    u8 unkD;
    u8 unkE[6];
    f32 unk14;
    f32 unk18;
    s16 unk1C;
} R1F1025E0Node;

extern R1F1025E0Node *D_80754AD0;
extern s16 D_80754AD4;

void gfxResourceListReset(void) {
    D_80754AD0 = NULL;
    D_80754AD4 = 0;
}

R1F1025E0Node *gfxResourceFindById(s16 arg0) {
    R1F1025E0Node *var_v1;

    var_v1 = D_80754AD0;
    if ((var_v1 != NULL) && (arg0 != var_v1->unk1C)) {
loop_2:
        var_v1 = var_v1->next;
        if ((var_v1 != NULL) && (arg0 != var_v1->unk1C)) {
            goto loop_2;
        }
    }
    return var_v1;
}

R1F1025E0Entry *gfxResourceCopyEntry(R1F1025E0Entry *arg0, s16 arg1, s16 arg2) {
    *arg0 = gfxResourceFindById(arg1)->unk8[arg2];
    return arg0;
}

f32 func_806FDA8C(s16 arg0) {
    return gfxResourceFindById(arg0)->unk18;
}

void func_806FDAB8(s16 arg0, f32 arg1) {
    gfxResourceFindById(arg0)->unk18 = arg1;
}

void heapFree(void *);

void func_806FDAEC(s16 arg0) {
    R1F1025E0Node *var_a1;
    R1F1025E0Node *var_v0;

    var_a1 = D_80754AD0;
    var_v0 = NULL;
    if ((var_a1 != NULL) && (arg0 != var_a1->unk1C)) {
loop_2:
        var_v0 = var_a1;
        var_a1 = var_a1->next;
        if ((var_a1 != NULL) && (arg0 != var_a1->unk1C)) {
            goto loop_2;
        }
    }
    if (var_v0 != NULL) {
        var_v0->next = var_a1->next;
    } else {
        D_80754AD0 = var_a1->next;
    }
    heapFree(var_a1->unk4);
    heapFree(var_a1->unk8);
    heapFree(var_a1);
}

void _strcpy(s32, s32);
extern u8 D_8074450C;
s32 randomNonNegative();
s32 strlen(char *);
void *func_80610FE8(s32);
void heapClearBlock(void *);
s16 func_806FBEAC(char *);

s16 func_806FDB8C(s16 arg0, char *arg1, u8 arg2, f32 arg3, f32 arg4, f32 arg5) {
    R1F1025E0Node *node;
    R1F1025E0Node *tail;
    R1F1025E0Entry *entries;
    void *name;
    u8 count;
    s16 i;

    func_806FBD5C(arg0, (s32)arg1);
    node = func_80610FE8(0x20);
    heapClearBlock(node);
    if (D_80754AD0 == NULL) {
        D_80754AD0 = node;
        node->next = NULL;
        D_80754AD4 = 0;
    } else {
        tail = D_80754AD0;
        while (tail->next != NULL) {
            tail = tail->next;
        }
        tail->next = node;
        node->next = NULL;
    }
    node->unk1C = (s16)(D_80754AD4 & 0xFFFF);
    D_80754AD4++;
    if (D_80754AD4 && D_80754AD4) {
    }
    name = func_80610FE8(strlen(arg1) + 1);
    node->unk4 = name;
    _strcpy((s32)name, (s32)arg1);
    count = func_806FBEAC(arg1);
    node->unkD = count;
    entries = func_80610FE8(count * sizeof(R1F1025E0Entry));
    node->unk8 = entries;
    heapClearBlock(entries);
    node->unkC = arg0;
    i = 0;
    if (node->unkD > 0) {
        do {
            if (arg2 == 3) {
                node->unk8[i].unk0 = (randomNonNegative() >> 15) % 1440 - 0x50;
                node->unk8[i].unk4 = (randomNonNegative() >> 15) % 1120 - 0x50;
                node->unk8[i].unk20 = (randomNonNegative() >> 15) % 6283 / 1000.0;
                node->unk14 = 0.1f;
            } else {
                node->unk8[i].unk0 = arg3 * 4.0f;
                node->unk8[i].unk4 = arg4 * 4.0f;
                node->unk8[i].unk8 = arg5 * 4.0f;
                node->unk8[i].unk30 = (D_8074450C == 2) ? 1.0 : 0.1;
                node->unk14 = 0.2f;
            }
            i++;
        } while (i < node->unkD);
    }
    return node->unk1C;
}

void func_806FDF1C(s16 arg0, s32 arg1) {
    _strcpy((s32)gfxResourceFindById(arg0)->unk4, arg1);
}

s16 func_806CC190(s16, s16, f32);

void func_806FDF54(f32 *arg0, f32 *arg1) {
    if (*arg1 < 0.0f) {
        do {
            *arg1 += 6.2831855f;
        } while (*arg1 < 0.0f);
    }
    if (*arg1 >= 6.2831855f) {
        do {
            *arg1 -= 6.2831855f;
        } while (*arg1 >= 6.2831855f);
    }
    *arg0 = (f32)((f64)((f32)func_806CC190((s16)(s32)(((f64)*arg0 * 2048.0) / 3.1415927410125732), (s16)(s32)(((f64)*arg1 * 2048.0) / 3.1415927410125732), 5.0f) * 3.1415927410125732f) * 0.00048828125);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/1025E0/func_806FE078.s")

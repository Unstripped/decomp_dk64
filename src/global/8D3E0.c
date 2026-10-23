#include "common.h"
#include "actor.h"

typedef struct ActorListRecord {
    /* 0x00 */ f32 unk00;
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ char unk10[0x20];
    /* 0x30 */ s16 unk30;
    /* 0x32 */ s16 unk32;
    /* 0x34 */ s16 unk34;
    /* 0x36 */ char pad36[2];
} ActorListRecord;

typedef struct ActorListEntry4 {
    /* 0x0 */ u8 unk0;
    /* 0x1 */ u8 unk1;
    /* 0x2 */ s16 unk2;
} ActorListEntry4;

typedef struct ActorListSub20 {
    s32 words[8];
} ActorListSub20;

typedef struct ActorListNode {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ char unk24[0x20];
    /* 0x44 */ Actor *unk44;
    /* 0x48 */ u8 unk48;
    /* 0x49 */ u8 unk49;
    /* 0x4A */ s16 unk4A;
    /* 0x4C */ u8 unk4C;
    /* 0x4D */ char unk4D[3];
    /* 0x50 */ s32 unk50;
    /* 0x54 */ f32 unk54;
    /* 0x58 */ s16 unk58;
    /* 0x5A */ s16 unk5A;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ s32 unk60;
    /* 0x64 */ struct ActorListNode *prev;
    /* 0x68 */ struct ActorListNode *next;
} ActorListNode;

extern s32 D_8076A0A8;
extern ActorListSub20 D_807500B4;
extern ActorListSub20 D_807500D4;
extern Actor *D_807FBB40;
extern ActorListNode *D_807FC400;
extern ActorListEntry4 *D_807FC5C4;
extern u8 D_807FC5C8;
extern s16 D_807FC5D0[16];
extern s16 D_807FC5F0[16];
extern u8 D_807FC610;
extern u8 D_807FC611;

void *memcpy(void *, const void *, size_t);
void heapFree(void *);
void actorDespawn(Actor *);
s16 func_806531B8(f32, f32, f32, s32);
s32 func_80652E58(s32, void *);
void func_8066E6C8(Actor *, s32, s32);
void func_8067AB20(s32, Actor *, s32, u8, void *, u8);
s32 func_80688C84(u16);
s16 func_80688E08(void);
ActorListNode *func_80689250(s16, f32, f32, f32, s16, f32, void *, u8, s32, s16);
void func_80689710();
f32 func_80689DD4(f32, f32, f32);
s32 func_80689F2C(void);
u8 func_80689F80(ActorListNode *);
u8 func_80689FEC(ActorListNode *);
void func_8068A1B8(void);

#pragma GLOBAL_ASM("asm/global/nonmatchings/8D3E0/func_806886E0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/8D3E0/func_80688940.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/8D3E0/func_80688A6C.s")

s32 func_80688C30(u16 arg0) {
    s32 i;

    for (i = 0; i < D_807FC5C8; i++) {
        if (arg0 == D_807FC5C4[i].unk0) {
            return D_807FC5C4[i].unk2;
        }
    }
    return -1;
}

s32 func_80688C84(u16 arg0) {
    switch (arg0) {
    case 0x5B:
    case 0x6F:
    case 0x70:
    case 0x71:
    case 0x72:
    case 0x8B:
        return 1;
    default:
        return 0;
    }
}

void func_80688CC4(Actor *actor, s16 arg1, f32 arg2) {
    if (arg1 < 8) {
        ((f32 *)actor->unk124)[arg1] = arg2;
    }
}

void func_80688CF4(Actor *actor, s16 arg1, s32 arg2) {
    if (arg1 < 8) {
        ((s32 *)actor->unk124)[arg1] = arg2;
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/8D3E0/func_80688D20.s")

s16 func_80688E08(void) {
    s16 id;
    s32 found;
    ActorListNode *node;

    id = 0;
    do {
        found = 0;
        node = D_807FC400;
        if (node != NULL) {
            do {
                if (node->unk5A == id) {
                    found = 1;
                }
                node = node->next;
            } while (node != NULL && !found);
        }
        if (found) {
            id++;
        }
    } while (found);

    return id;
}

s16 func_80688E68(Actor *arg0) {
    ActorListNode *node;

    for (node = D_807FC400; node != NULL; node = node->next) {
        if (node->unk44 == arg0) {
            return node->unk5A;
        }
    }
    return 0;
}

Actor *func_80688EA4(s16 arg0) {
    ActorListNode *node;

    for (node = D_807FC400; node != NULL; node = node->next) {
        if (node->unk5A == arg0) {
            return node->unk44;
        }
    }
}

void func_80688EE4(s16 arg0, f32 arg1, f32 arg2, f32 arg3) {
    ActorListNode *node;

    for (node = D_807FC400; node != NULL; node = node->next) {
        if (node->unk5A == arg0) {
            node->unk04 = arg1;
            node->unk08 = arg2;
            node->unk0C = arg3;
            node->unk10 = arg1;
            node->unk14 = arg2;
            node->unk18 = arg3;
            node->unk4A = func_806531B8(arg1, arg2, arg3, 0);
            return;
        }
    }
}

void func_80688F74(Actor *arg0, f32 arg1, f32 arg2, f32 arg3) {
    ActorListNode *node;

    for (node = D_807FC400; node != NULL; node = node->next) {
        if (node->unk44 == arg0) {
            node->unk04 = arg1;
            node->unk08 = arg2;
            node->unk0C = arg3;
            return;
        }
    }
}

void func_80688FC0(s32 *arg0) {
    ActorListRecord *item;
    s32 i;
    void *var_s2;
    s32 count;

    D_807FC400 = NULL;
    if (arg0 != NULL) {
        count = *arg0++;
        item = (ActorListRecord *)arg0;
        for (i = 0, var_s2 = (char *)item + 0x10; i < count; i++, item++, var_s2 = (char *)var_s2 + 0x38) {
            func_80689250(item->unk32, item->unk00, item->unk04, item->unk08, item->unk30, item->unk0C, var_s2, 0, 0, item->unk34);
        }
        func_8068A1B8();
    }
}

void func_80689064(s16 arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4, f32 arg5) {
    ActorListSub20 sp38;

    sp38 = D_807500B4;
    func_80689250(arg0, arg1, arg2, arg3, (s32)arg4, arg5, &sp38, 0, 0, func_80688E08());
}

void func_80689114(s16 arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4, f32 arg5, s32 arg6) {
    ActorListSub20 sp38;

    sp38 = D_807500D4;
    func_80689250((s16)(arg0 - 0x10), arg1, arg2, arg3, (s32)arg4, arg5, &sp38, 1, arg6, func_80688E08());
}

void func_806891D8(s16 arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4, f32 arg5, s32 arg6, s32 arg7) {
    func_80689250((s16)(arg0 - 0x10), arg1, arg2, arg3, (s32)arg4, arg5, (void *)arg7, 1, arg6, func_80688E08());
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/8D3E0/func_80689250.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/8D3E0/func_80689418.s")

void func_806896D0(s32 arg0) {
    func_80689710(arg0, 1);
}

void func_806896F0(s32 arg0) {
    func_80689710(arg0, 0);
}

void func_80689710(arg0, arg1)
ActorListNode *arg0;
u8 arg1;
{
    ActorListNode *node;
    ActorListNode *prev;
    s32 found;

    found = 0;
    node = D_807FC400;
    prev = NULL;
    if (node != NULL) {
        do {
            if (node == arg0) {
                found = 1;
                if (arg1 != 0 && node->unk44 != NULL) {
                    actorDespawn(node->unk44);
                }
                if (prev != NULL) {
                    prev->next = node->next;
                } else {
                    D_807FC400 = node->next;
                }
                if (node->next != NULL) {
                    node->next->prev = prev;
                }
                heapFree(node);
            } else {
                prev = node;
                node = node->next;
            }
        } while (found == 0 && node != NULL);
    }
}

void func_806897F0(Actor *arg0) {
    ActorListNode *node;
    ActorListNode *prev;
    s32 found;

    found = 0;
    node = D_807FC400;
    prev = NULL;
    if (node != NULL) {
        do {
            if (arg0 == node->unk44) {
                found = 1;
                if (prev != NULL) {
                    prev->next = node->next;
                } else {
                    D_807FC400 = node->next;
                }
                if (node->next != NULL) {
                    node->next->prev = prev;
                }
                heapFree(node);
            } else {
                prev = node;
                node = node->next;
            }
        } while (found == 0 && node != NULL);
    }
}

void func_806898A8(void) {
    ActorListNode *node;
    ActorListNode *next;

    node = D_807FC400;
    if (node != NULL) {
        do {
            next = node->next;
            heapFree(node);
            node = next;
        } while (node != NULL);
    }
    D_807FC400 = NULL;
}

s32 func_806898F8(void) {
    ActorListNode *node;
    s32 count;

    node = D_807FC400;
    count = 0;
    if (node != NULL) {
        do {
            if (node->unk4C == 0 || (node->unk44 != NULL && (node->unk44->unk64 & 0x400))) {
                count++;
            }
            node = node->next;
        } while (node != NULL);
    }
    return (count * 0x38) + 4;
}

void func_80689958(s32 *arg0) {
    ActorListNode *node;
    u8 *dst;
    ActorListRecord item;
    s32 count;
    node = D_807FC400;
    count = 0;
    if (node != NULL) {
        do {
            if (node->unk4C == 0 || (node->unk44 != NULL && (node->unk44->unk64 & 0x400))) {
                count++;
            }
            node = node->next;
        } while (node != NULL);
    }
    *arg0 = count;
    node = D_807FC400;
    dst = (u8 *)(arg0 + 1);
    if (node != NULL) {
        do {
            if (node->unk4C == 0 || (node->unk44 != NULL && (node->unk44->unk64 & 0x400))) {
                item.unk32 = node->unk00;
                item.unk0C = node->unk20;
                item.unk30 = node->unk1C;
                item.unk00 = node->unk04;
                item.unk04 = node->unk08;
                item.unk08 = node->unk0C;
                item.unk34 = node->unk5A;
                memcpy(item.unk10, node->unk24, 0x20);
                memcpy(dst, &item, sizeof(item));
                dst += sizeof(item);
            }
            node = node->next;
        } while (node != NULL);
    }
}

void func_80689A80(s16 arg0, void *arg1) {
    ActorListNode *node = D_807FC400;
    s32 found = 0;

    if (node != NULL) {
        do {
            if (arg0 == node->unk5A) {
                found = 1;
            } else {
                node = node->next;
            }
        } while (node != NULL && found == 0);
    }
    if (found) {
        if (node->unk44 != NULL) {
            func_8067AB20((s32)D_807FBB40, node->unk44, 0x1000000, 1, arg1, 0);
        }
    }
}

s32 func_80689B10(s16 arg0, u8 arg1, u8 arg2) {
    ActorListNode *node;
    s32 found = 0;

    node = D_807FC400;
    if (node != NULL) {
        do {
            if (arg0 == node->unk5A) {
                found = 1;
            } else {
                node = node->next;
            }
        } while (node != NULL && found == 0);
    }
    if (!found) {
        return 0;
    }
    if (node->unk44 == NULL) {
        return 0;
    }
    if (arg2 != 0) {
        node->unk44->unk154 = arg1;
    }
    return node->unk44->unk154;
}

s32 func_80689BAC(s16 arg0) {
    ActorListNode *node;
    s32 found = 0;

    node = D_807FC400;
    if (node != NULL) {
        do {
            if (arg0 == node->unk5A) {
                found = 1;
            } else {
                node = node->next;
            }
        } while (node != NULL && found == 0);
    }
    if (!found) {
        return 0;
    }
    if (node->unk48 != 0) {
        return 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/8D3E0/func_80689C20.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/8D3E0/func_80689DD4.s")

s32 func_80689E98(s32 arg0) {
    return 1;
}

void func_80689EA4(ActorListNode *arg0) {
    if (func_80689F2C()) {
        func_80652E58(arg0->unk4A, arg0);
    } else {
        func_80689F80(arg0);
    }
}

u8 func_80689EE4(ActorListNode *arg0) {
    if (func_80689F2C()) {
        return func_80652E58(*(s16 *)&arg0->unk44->unk12C, arg0) == 0;
    }
    return func_80689FEC(arg0);
}

s32 func_80689F2C(void) {
    switch (D_8076A0A8) {
        case 0x2A:
        case 0xA9:
        case 0xAA:
        case 0xAD:
        case 0xAE:
        case 0xAF:
        case 0xB2:
        case 0xC1:
        case 0xC2:
        case 0xC3:
            return 1;
        default:
            return 0;
    }
}

u8 func_80689F80(ActorListNode *arg0) {
    s32 var_a0 = func_80652E58(arg0->unk4A, arg0) != 0;
    if (var_a0 != 0) {
        f32 dist = func_80689DD4(arg0->unk10, arg0->unk14, arg0->unk18);
        var_a0 = 0;
        if (dist < arg0->unk54) {
            var_a0 = 1;
        }
    }
    return var_a0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/8D3E0/func_80689FEC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/8D3E0/func_8068A074.s")

s32 func_8068A10C(s32 arg0) {
    return 0;
}

u8 func_8068A118(ActorListNode *arg0) {
    s32 var_v1;
    f32 dist = func_80689DD4(arg0->unk10, arg0->unk14, arg0->unk18);
    var_v1 = 0;
    if (dist < arg0->unk54) {
        var_v1 = 1;
    }
    return var_v1;
}

u8 func_8068A164(ActorListNode *arg0) {
    return !(func_80689DD4(arg0->unk44->unk7C, arg0->unk44->unk80, arg0->unk44->unk84) < arg0->unk54);
}

void func_8068A1B8(void) {
    D_807FC610 = 0;
    D_807FC611 = 0;
}

void func_8068A1CC(s16 arg0) {
    if (D_807FC610 != 0x10) {
        D_807FC5D0[D_807FC610++] = arg0;
    }
}

void func_8068A20C(s16 arg0) {
    if (D_807FC611 != 0x10) {
        D_807FC5F0[D_807FC611++] = arg0;
    }
}

s32 func_8068A24C(ActorListNode *arg0) {
    s32 i;
    for (i = 0; i < D_807FC610; i++) {
        if (arg0->unk5A == D_807FC5D0[i] && arg0->unk48 == 0) {
            return 1;
        }
    }
    return 0;
}

s32 func_8068A2A4(ActorListNode *arg0) {
    s32 i;
    for (i = 0; i < D_807FC611; i++) {
        if (arg0->unk5A == D_807FC5F0[i] && arg0->unk48 != 0) {
            return 1;
        }
    }
    return 0;
}

void func_8068A2FC(Actor *arg0) {
    arg0->unk128 = 0;
    arg0->unk60 &= ~0x8000;
    arg0->unk144 = 1;
    arg0->unk138 = 0;
    arg0->unk154 = 0x63;
    func_8066E6C8(arg0, 0, 0);
}

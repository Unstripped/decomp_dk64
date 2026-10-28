// func_806FA7BC (src/global/FCCD0.c): stage 5: frame 0x58 + s0-s4 match, 14 diff lines left: scheduling of the a0/s0/s1 copies around the func_806FA7A4(arg0,*p,unk4) call (target: lhu a2; move a0,s4; beqz v1; lhu a1 delay; move s0,a1; jal; move s1,a2 delay), step/abs temps use a1/a3 instead of a3/a0/v0, join reload uses v1/t4 vs t4/a1. Needs 3-arg call (extern s32 func_806FA7A4() block redeclaration), FCC_SLOT inline address expr, flag compare spelled *p == ((u16*)slot)[2]. parked under NON_MATCHING
typedef struct FcCNode {
    s32 unk0;
    u8 pad4[8];
    s32 unkC;
    s16 unk10;
    u8 pad12[6];
    struct FcCNode *unk18;
} FcCNode;

typedef struct FcCSlot {
    u16 *unk0;
    u16 unk4;
    u8 unk6;
    u8 unk7;
    u8 pad8[0x18];
    s32 unk20;
    u8 pad24[4];
    FcCNode *unk28;
} FcCSlot;

extern void *D_80754280;
s32 func_806FA504(s32, void *, s32, s32);
void func_806F8CB0(s32);
int slotQueueCancel();

#define FCC_SLOT ((FcCSlot *)((u8 *)D_80754280 + (arg0 * 0x30)))

s32 func_806FA7BC(s32 arg0, s32 arg1) {
    extern s32 func_806FA7A4();
    s32 s1;
    FcCNode *node;
    u8 flag;
    u16 *p;
    s32 x;
    s32 step;
    s32 absd;
    s32 sign;
    s32 tmp;

    node = FCC_SLOT->unk28;
    s1 = 0;
    p = FCC_SLOT->unk0;
    if (p != NULL) {
        flag = *p == ((u16 *)FCC_SLOT)[2];
    } else {
        flag = 1;
    }
    if (node != NULL) {
        do {
            arg1 = func_806FA504(arg0, node, s1, arg1);
            if (node->unk0 == 1) {
                s1 += 1;
            }
            node = node->unk18;
        } while (node != NULL);
    }
    if (flag == 0) {
        if (FCC_SLOT->unk0 != NULL) {
            x = *FCC_SLOT->unk0;
            s1 = FCC_SLOT->unk4;
            step = func_806FA7A4(arg0, *FCC_SLOT->unk0, FCC_SLOT->unk4);
            if ((x - s1) > 0) {
                absd = (x - s1);
            } else {
                absd = -(x - s1);
            }
            sign = -1;
            if (absd < step) {
                if ((x - s1) > 0) {
                    tmp = (x - s1);
                } else {
                    tmp = -(x - s1);
                }
                step = tmp;
            }
            if ((x - s1) >= 0) {
                sign = 1;
            }
            FCC_SLOT->unk4 += sign * step;
        }
        flag = *FCC_SLOT->unk0 == ((u16 *)FCC_SLOT)[2];
    }
    if ((FCC_SLOT->unk7 == 0) && (flag != 0)) {
        FCC_SLOT->unk20 = 3;
        func_806F8CB0(arg0);
        if ((arg0 * 0x30) == 0x180) {
            slotQueueCancel(9, 5);
        }
        return arg1;
    } else if ((FCC_SLOT->unk7 != 0) && (FCC_SLOT->unk6 == 0)) {
        FCC_SLOT->unk7 = FCC_SLOT->unk7 - 1;
    }
    return arg1;
}

#undef FCC_SLOT

// slotQueueStateMoveToTarget (src/global/FCCD0.c): stage 5 (NM9): 4 diff lines vs 7; regs all match (shape ok), only as1 schedule around beqz/jal differs: target 'move a0,s4; beqz; lhu a1 (delay); move s0,a1; jal; move s1,a2 (delay)', ours 'lhu a1; move s1,a2; beqz; move s0,a1 (delay); jal; move a0,s4 (delay)'. KEY: use 'absd' (existing local) for the +-1 direction instead of 'sign' (sign merged with x in s0, target sign=a0; a NEW local grows frame). Tried: all placements/orders of sign/x/s1 stmts (identical text), embedded assignments in call args (E2 gets a3), line joins, deadsweep -extra all locals, permuter 500s: no gain.
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

extern void *gSlotQueue;
s32 slotQueueNodeUpdate(s32, void *, s32, s32);
void slotQueueStaggerNodeDelays(s32);
int slotQueueCancel();

#define FCC_SLOT ((FcCSlot *)((u8 *)gSlotQueue + (arg0 * 0x30)))

s32 slotQueueStateMoveToTarget(s32 arg0, s32 arg1) {
    extern s32 slotQueueGetCountStep();
    s32 s1;
    FcCNode *node;
    u8 flag;
    u16 *p;
    s32 x;
    s32 step;
    s32 absd;
    s32 sign;
    s32 tmp;
    if (step == 0) {}

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
            arg1 = slotQueueNodeUpdate(arg0, node, s1, arg1);
            if (node->unk0 == 1) {
                s1 += 1;
            }
            node = node->unk18;
        } while (node != NULL);
    }
    if (flag == 0) {
        sign = *FCC_SLOT->unk0;
        if (FCC_SLOT->unk0 != NULL) {
            x = sign;
            s1 = FCC_SLOT->unk4;
            step = slotQueueGetCountStep(arg0, *FCC_SLOT->unk0, FCC_SLOT->unk4);
            if ((x - s1) > 0) {
                absd = (x - s1);
            } else {
                absd = -(x - s1);
            }
            if (absd < step) {
                if ((x - s1) > 0) {
                    tmp = (x - s1);
                } else {
                    tmp = -(x - s1);
                }
                step = tmp;
            }
            if ((x - s1) >= 0) {
                absd = 1;
            } else {
                absd = -1;
            }
            FCC_SLOT->unk4 += absd * step;
        }
        flag = *FCC_SLOT->unk0 == ((u16 *)FCC_SLOT)[2];
    }
    if ((FCC_SLOT->unk7 == 0) && (flag != 0)) {
        FCC_SLOT->unk20 = 3;
        slotQueueStaggerNodeDelays(arg0);
        if ((arg0 * 0x30) == 0x180) {
            slotQueueCancel(9, 5);
        }
        return arg1;
    } else if ((FCC_SLOT->unk7 != 0) && (FCC_SLOT->unk6 == 0)) {
        FCC_SLOT->unk7 = FCC_SLOT->unk7 - 1;
    }
    return arg1;
}

// slotQueueAddValue (src/global/FCCD0.c): stage 4: frame 0x50, no callee-saved regs, K&R (s32,u8,s16). 160 insns = target 160 now (was 161) after REMOVING the dummy 'pb = &arg2;' (diff 123 -> 96 lines; declaration 's16 *pb;' stays: it reserves frame word -12). Left: (1) CSE spills of arg0*0x30 / slot ptr sit at 0x20/0x1C vs target 0x24/0x20 -- uopt -l 5 shows an extra 2-byte M var (-42vreg, {1296}, stored from a call return) occupying the word at 0x24 that the target lacks (not removed by flagGridIndex prototype changes (s16/s32/K&R), arg2 as s32, separate temp for the GetMaxValue result (shifts everything down), nopa/nopb); (2) arg2 is a uopt candidate (v0) in ours but plain re-loaded 'lh t1,90(sp)' in the target; (3) arg0*0x30 spill stored at definition ('sw t2,32(sp)') instead of inside each branch before the call; (4) CSE temp ring t1/t5 vs t3/t1.
typedef struct SlotQueueStatSlot {
    u16 *unk0;
    u8 pad4[0x28];
    u8 unk2C;
    u8 unk2D;
    u8 pad2E[2];
} SlotQueueStatSlot;

extern u8 D_8074E77C;
extern s32 func_805FEF10(s16 *);
extern void func_80687C48(void);
extern void flagSet(s16, s32, s32);
extern s16 flagGridIndex(s32, s32, u8, s32);
extern void sfxAllocateChannel(s32, f32);

void slotQueueAddValue(arg0, arg1, arg2)
s32 arg0;
u8 arg1;
s16 arg2;
{
    u8 *pa;
    u8 *sp48;
    s16 *pb;
    s32 temp_v0;
    s32 sp3C;
    s32 temp_a3;
    s32 temp_v0_2;
    u16 *temp_v1;
    SlotQueueStatSlot *temp_a0;
    s32 sp28;

    pa = &arg1;
    sp28 = arg1;
    temp_v0_2 = func_806C8DE0(arg1);
    sp48 = (u8 *)D_807FC950 + (arg1 * 0x306 + temp_v0_2 * 0x5E);
    temp_v0 = slotQueueGetAddress(arg1);
    temp_a0 = (SlotQueueStatSlot *)(temp_v0 + (arg0 * 0x30));
    if (((temp_a0->unk2D == 0) || (arg2 >= 0)) && (temp_a0->unk2C == 0)) {
        if ((arg0 != 0xA) && (arg0 != 0xC)) {
            temp_v1 = temp_a0->unk0;
            if ((*temp_v1 + arg2) < 0) {
                *temp_v1 = 0;
            } else {
                temp_v1 = *((u16 **)(temp_v0 + (arg0 * 0x30)));
                *temp_v1 += arg2;
                temp_v0_2 = slotQueueGetMaxValue(arg0, sp28);
                temp_v1 = *((u16 **)(temp_v0 + (arg0 * 0x30)));
                if (temp_v0_2 < *temp_v1) {
                    *temp_v1 = temp_v0_2;
                }
                if (((arg0 * 0x30) == 0x180) && (func_805FEF10(&sp3C) != 0)) {
                    flagSet(sp3C, 1, 0);
                }
                if ((arg2 > 0) && ((arg0 * 0x30) == 0)) {
                    temp_v0_2 = func_805FF030(D_8076A0AB, 1);
                    temp_a3 = *(u16 *)(sp48 + (temp_v0_2 * 2) + 0x26) + *(u16 *)(sp48 + (temp_v0_2 * 2) + 0xA);
                    if ((temp_a3 >= 0x4B) && ((temp_a3 - arg2) < 0x4B)) {
                        flagSet(flagGridIndex(0x225, temp_v0_2, (&D_8074E77C)[arg1], temp_a3), 1, 0);
                        func_80687C48();
                    }
                    if ((temp_a3 == 0x64) && ((temp_a3 - arg2) < 0x64)) {
                        sfxAllocateChannel(0xAC, 1.0f);
                    }
                }
            }
        }
        if ((arg0 * 0x30) == 0x180) {
            func_806F8278(arg1);
        }
    }
}

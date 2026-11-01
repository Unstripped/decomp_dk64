// slotQueueAddValue (src/global/FCCD0.c): R2Frm1 (wave 2): stage 4, frame 0x50 = target, 159 insns = target, 86 diff lines (tools/fdiff-style objdump diff; was 88). K&R (s32,u8,s16). Applied: slot pointer written as '(SlotQueueStatSlot *)temp_v0 + arg0' (base-first addu a0,v0,t2 like target); dummy 'pb = &arg2' stays removed. Left: (1) cfe nested-call temp for flagSet(flagGridIndex(..)) takes word 36 so uopt spills land at 32/28 vs target 36/32 (removing the nesting drops the whole frame to 72, so the target's extra 8 bytes sit BELOW its spills; every flagGridIndex/flagSet prototype spelling s16/s32/K&R/3-arg/4-arg/(s16) cast gives byte-identical code); (2) arg2 is P candidate web 124 coloured v0 (lh v0 sits after 'addu a0' because v0 is the call result), target has plain 'lh t1,90(sp)' hoisted above the sll chain and CSE'd across blocks; 'pb = &arg2' (alias) makes the load plain/early but un-CSE'd (160 insns, 81 lines, lh reloaded per use); (s16)/(s32)/(+0) casts on any arg2 site: no change; (3) uopt -l 6: arg0*0x30 (candidate 28) is 'not colored (-ve save)' in ours so it is a ugen temp spilled at DEFINITION (sw t2,32), target colours it t2 as a web and stores before each call per branch; named locals idx=arg0*0x30 / slotp are copy-propagated back to the same temp (frame +8). Tried without gain: declaration-order + pad-local hill-climb (500 s, 3 workers), single and greedy dead-use sweeps over all locals (best 74 only via 'if (pa) {}'/'if (temp_a3) {}' junk that adds insns), deadsweep.py cannot parse the K&R definition.
typedef struct SlotQueueStatSlot {
    u16 *unk0;
    u8 pad4[0x28];
    u8 unk2C;
    u8 unk2D;
    u8 pad2E[2];
} SlotQueueStatSlot;

extern u8 gPlayerCharacterId;
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
    temp_a0 = (SlotQueueStatSlot *)temp_v0 + arg0;
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
                        flagSet(flagGridIndex(0x225, temp_v0_2, (&gPlayerCharacterId)[arg1], temp_a3), 1, 0);
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

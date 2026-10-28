// func_806F91B4 (src/global/FCCD0.c): stage 4 (parked): frame 0x50 + no callee-saved match, K&R params (s32,u8,s16); pa/pb dummy &arg1/&arg2 + 10 named locals (arg1/arg2 memory resident, prologue/arg0 in a3 match). Left (46 diff lines): CSE spills of arg0*0x30/a2 at 0x20/0x1C vs 0x24/0x20 (need one more named word after sp28 without growing frame), t1/t5 vs t3/t1 temp ring, lw/sw ordering around slot ptr; naming var_t2/temp_a2 grows frame to 0x58
typedef struct NM2StatSlot {
    u16 *unk0;
    u8 pad4[0x28];
    u8 unk2C;
    u8 unk2D;
    u8 pad2E[2];
} NM2StatSlot;

extern u8 D_8074E77C;
extern s32 func_805FEF10(s16 *);
extern void func_80687C48(void);
extern void flagSet(s16, s32, s32);
extern s16 flagGridIndex(s32, s32, u8, s32);
extern void sfxAllocateChannel(s32, f32);

void func_806F91B4(arg0, arg1, arg2)
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
    NM2StatSlot *temp_a0;
    s32 sp28;

    pa = &arg1;
    pb = &arg2;
    sp28 = arg1;
    temp_v0_2 = func_806C8DE0(arg1);
    sp48 = (u8 *)D_807FC950 + (arg1 * 0x306 + temp_v0_2 * 0x5E);
    temp_v0 = slotQueueGetAddress(arg1);
    temp_a0 = (NM2StatSlot *)(temp_v0 + (arg0 * 0x30));
    if (((temp_a0->unk2D == 0) || (arg2 >= 0)) && (temp_a0->unk2C == 0)) {
        if ((arg0 != 0xA) && (arg0 != 0xC)) {
            temp_v1 = temp_a0->unk0;
            if ((*temp_v1 + arg2) < 0) {
                *temp_v1 = 0;
            } else {
                temp_v1 = *((u16 **)(temp_v0 + (arg0 * 0x30)));
                *temp_v1 += arg2;
                temp_v0_2 = func_806F8EDC(arg0, sp28);
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

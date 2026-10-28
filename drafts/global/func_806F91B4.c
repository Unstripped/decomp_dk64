// func_806F91B4 (src/global/FCCD0.c): stage 4-: size equal (13488), structure matches; frame 0x60 vs 0x50 (pa/pb dummy &arg1/&arg2 hack makes arg1/arg2 memory-resident), regs t1/t2/a0/v1 shifted, sp48=(u8*)D_807FC950+(arg1*0x306+row*0x5E)
typedef struct FcAStatSlot {
    u16 *unk0;
    u8 pad4[0x28];
    u8 unk2C;
    u8 unk2D;
    u8 pad2E[2];
} FcAStatSlot;

extern s32 func_805FEF10(s16 *);
extern s32 func_806F8EDC(s32, s32);
extern void func_80687C48(void);
extern void flagSet(s16, s32, s32);
extern s16 flagGridIndex(s32, s32, u8, s32);
extern void sfxAllocateChannel(s32, f32);
extern u8 D_8074E77C[];

void func_806F91B4(s32 arg0, u8 arg1, s16 arg2) {
    s16 sp3C;
    s32 sp38;
    s32 sp28;
    s32 temp_a3;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_t2;
    u16 **temp_a2;
    u16 *temp_v1;
    u16 *temp_v1_2;
    u8 *sp48;
    FcAStatSlot *temp_a0;
    u8 *pa;
    s16 *pb;

    pa = &arg1;
    pb = &arg2;
    sp28 = arg1;
    temp_v0_2 = func_806C8DE0(arg1);
    sp48 = (u8 *)D_807FC950 + (arg1 * 0x306 + temp_v0_2 * 0x5E);
    temp_v0 = slotQueueGetAddress(arg1);
    var_t2 = arg0 * 0x30;
    temp_a0 = (FcAStatSlot *)(temp_v0 + var_t2);
    if (((temp_a0->unk2D == 0) || (arg2 >= 0)) && (temp_a0->unk2C == 0)) {
        if ((arg0 != 0xA) && (arg0 != 0xC)) {
            temp_v1 = temp_a0->unk0;
            temp_a2 = (u16 **)(temp_v0 + var_t2);
            if ((*temp_v1 + arg2) < 0) {
                *temp_v1 = 0;
                            } else {
                temp_v1_2 = *temp_a2;
                *temp_v1_2 += arg2;
                temp_v0_2 = func_806F8EDC(arg0, sp28);
                temp_v1_2 = *temp_a2;
                if (temp_v0_2 < *temp_v1_2) {
                    *temp_v1_2 = temp_v0_2;
                }
                if ((var_t2 == 0x180) && (func_805FEF10(&sp3C) != 0)) {
                    flagSet(sp3C, 1, 0);
                }
                if ((arg2 > 0) && (var_t2 == 0)) {
                    temp_v0_2 = func_805FF030(D_8076A0AB, 1);
                    temp_a3 = *(u16 *)(sp48 + (temp_v0_2 * 2) + 0x26) + *(u16 *)(sp48 + (temp_v0_2 * 2) + 0xA);
                    if ((temp_a3 >= 0x4B) && ((temp_a3 - arg2) < 0x4B)) {
                        sp38 = temp_a3;
                        flagSet(flagGridIndex(0x225, temp_v0_2, D_8074E77C[arg1], temp_a3), 1, 0);
                        func_80687C48();
                    }
                    if ((temp_a3 == 0x64) && ((temp_a3 - arg2) < 0x64)) {
                        sfxAllocateChannel(0xAC, 1.0f);
                    }
                }
            }
            var_t2 = var_t2;
        }
        if (var_t2 == 0x180) {
            func_806F8278(arg1);
        }
    }
}

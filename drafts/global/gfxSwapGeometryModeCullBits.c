// func_806130A4 (src/global/17B90.c): stage 3: body logic and bnel tail match; while(1)+break avoids IDO 2x-unroll; remaining diff is s0-s3 allocation / 0x18 frame for duplicated mask constants
typedef struct RvR2_Cmd {
    u32 unk0;
    u32 unk4;
} RvR2_Cmd;

void func_806130A4(RvR2_Cmd *arg0, RvR2_Cmd *arg1) {
    if (arg0 != arg1) {
        do {
            u32 w0 = arg0->unk0;
            u32 w1 = arg0->unk4;

            if ((w0 >> 24) == 0xD9) {
                if (w1 == 0) {
                    u32 inv = ~w0 & 0xFFFFFF;
                    u32 mask = inv & 0x600;
                    if (mask == 0x200) {
                        arg0->unk0 = ~((inv | 0x400) & ~0x200) | 0xD9000000;
                    } else if (mask == 0x400) {
                        arg0->unk0 = ~((inv | 0x200) & ~0x400) | 0xD9000000;
                    }
                } else {
                    u32 mask = w1 & 0x600;
                    if (mask == 0x200) {
                        arg0->unk4 |= 0x400;
                        arg0->unk4 &= ~0x200;
                    } else if (mask == 0x400) {
                        arg0->unk4 |= 0x200;
                        arg0->unk4 &= ~0x400;
                    }
                }
            }
            arg0++;
            if (arg0 == arg1) {
                break;
            }
        } while (1);
    }
}

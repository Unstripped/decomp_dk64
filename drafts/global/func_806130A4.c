// func_806130A4 (src/global/17B90.c): stage 2; typed m2c candidate exposes D9 command bit rewrites but compiler unrolls the pointer loop; remaining loop form and register allocation
typedef struct { u32 unk0; s32 unk4; } P17c3Command;

void func_806130A4(P17c3Command *arg0, P17c3Command *arg1) {
    P17c3Command *var_a0 = arg0;
    if (var_a0 != arg1) {
        do {
            u32 temp_v1 = var_a0->unk0;
            s32 temp_t0 = var_a0->unk4;
            if ((temp_v1 >> 24) == 0xD9) {
                s32 temp_v0 = temp_t0 & 0x600;
                if (temp_t0 == 0) {
                    s32 temp_v1_2 = ~temp_v1 & 0xFFFFFF;
                    s32 temp_a3 = temp_v1_2 & 0x600;
                    if (temp_a3 == 0x200) {
                        var_a0->unk0 = ~((temp_v1_2 | 0x400) & ~0x200) | 0xD9000000;
                    } else if (temp_a3 == 0x400) {
                        var_a0->unk0 = ~((temp_v1_2 | 0x200) & ~0x400) | 0xD9000000;
                    }
                } else if (temp_v0 == 0x200) {
                    var_a0->unk4 = (temp_t0 | 0x400) & ~0x200;
                } else if (temp_v0 == 0x400) {
                    var_a0->unk4 = (temp_t0 | 0x200) & ~0x400;
                }
            }
            var_a0++;
        } while (var_a0 != arg1);
    }
}

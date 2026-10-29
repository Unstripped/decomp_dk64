// func_8068ABE0 (src/global/8F4B0.c): Stage 5, score 911 (frame 0x38, all stack offsets match: sp36/sp24/sp20/sp1C, exact sparse switch and tail, minor loop regalloc v0/v1, jtbl in .late_rodata)
s32 flagGet(s16, s32);
void flagSet(s16, s32, s32);
void func_805FF378(s16, s32);
void func_80712524(s32, s32);
extern s8 D_8074452C;
extern u16 D_80744734[];
extern s32 D_8076A0A8;

s32 func_8068ABE0(s16 arg0) {
    s16 sp36;
    s32 found;
    s32 i;
    s16 temp_a0;
    s32 sp24;
    s32 sp20;

    sp36 = -1;
    found = 0;
    i = 0;
    do {
        if (D_8076A0A8 == D_80744734[i]) {
            found = 1;
        } else {
            i++;
        }
    } while (!found && i < 8);

    if (found) {
        temp_a0 = i + 0x1C5;
        if (flagGet(temp_a0, 0) == 0) {
            sp20 = 0;
            switch (arg0) {
            case 0x7:
                sp24 = 0x1C;
                sp36 = 0xF;
                break;
            case 0x26:
                sp24 = 0x1C;
                sp36 = 0x10;
                break;
            case 0x1A:
                sp24 = 0x1C;
                sp36 = 0x11;
                break;
            case 0x1E:
                sp24 = 0x1C;
                sp36 = 0x12;
                break;
            case 0x30:
                sp24 = 0x1C;
                sp36 = 0x13;
                break;
            case 0x48:
                sp24 = 0x1C;
                sp36 = 0x14;
                break;
            case 0x57:
                sp24 = 0x1C;
                sp36 = 0x15;
                sp20 = 0x15;
                break;
            case 0x11:
                sp24 = 0x1C;
                sp36 = 0x16;
                break;
            }
            if (sp36 != -1) {
                flagSet(temp_a0, 1, 0);
                if (D_8074452C != 0) {
                    func_805FF378(arg0, sp20);
                    return 1;
                }
                func_80712524(sp24, sp36);
                return 1;
            }
        }
    }
    return 0;
}

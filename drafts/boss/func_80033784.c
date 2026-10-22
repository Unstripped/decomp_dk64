// func_80033784 (src/boss/F0D0.c): from .scratch/Boss3D/func_80033784_best.c
void func_8063DA40(s16, u8);
extern u8 D_80035BDC[];
extern u8 D_80035BE4[];

void func_80033784(arg0, arg1)
u8 *arg0;
s32 arg1;
{
    if (arg1 != 0) {
        do {
            arg0[4] = D_80035BDC[(u8)((func_80611A44() >> 15) % 8)];
        } while (arg0[0] + 0x10 == arg0[4] ||
                 arg0[3] + 0x10 == arg0[4] ||
                 arg0[3] + 0x0F == arg0[4] ||
                 arg0[3] + 0x11 == arg0[4] ||
                 arg0[3] + 0x0C == arg0[4] ||
                 arg0[3] + 0x14 == arg0[4]);

        do {
            arg0[5] = D_80035BE4[(u8)((func_80611A44() >> 15) % 8)];
        } while (arg0[0] + 0x10 == arg0[5] ||
                 arg0[3] + 0x10 == arg0[5] ||
                 arg0[3] + 0x0F == arg0[5] ||
                 arg0[3] + 0x11 == arg0[5] ||
                 arg0[3] + 0x0C == arg0[5] ||
                 arg0[3] + 0x14 == arg0[5]);
    }

    if (arg0[4] != 0) {
        func_8063DA40((s16)arg0[4], arg1);
    }
    if (arg0[5] != 0) {
        func_8063DA40((s16)arg0[5], arg1);
    }
    if (arg1 == 0) {
        arg0[4] = 0;
        arg0[5] = 0;
    }
}

// func_80658624 (src/global/55B20.c): from .scratch/S55f/func_80658624_best.c
typedef struct M55P6Vec3 {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
} M55P6Vec3;

extern f32 D_807F6D78[];
s32 camProjectToScreen(f32, f32, f32, f32 *, f32 *, s32, f32, s32);

void func_80658624(s32 arg0, s32 *arg1, s32 *arg2, s32 *arg3, s32 *arg4) {
    f32 sp7C;
    f32 sp78;
    M55P6Vec3 *p;
    s16 x;
    s16 y;
    s32 i;
    u8 flag;

    *arg1 = D_807FC924[D_807FC929].unk274;
    *arg2 = D_807FC924[D_807FC929].unk276;
    *arg3 = D_807FC924[D_807FC929].unk270;
    *arg4 = D_807FC924[D_807FC929].unk272;
    i = 0;
    flag = 0;
    if (arg0 > 0) {
        p = (M55P6Vec3 *)D_807F6D78;
        do {
            flag |= camProjectToScreen(p->unk0, p->unk4, p->unk8, &sp7C, &sp78, 0, 1.0f, D_807FC929);
            x = (s16)sp7C;
            y = (s16)sp78;
            if (x < D_807FC924[D_807FC929].unk270) {
                x = D_807FC924[D_807FC929].unk270;
            }
            if (y < D_807FC924[D_807FC929].unk272) {
                y = D_807FC924[D_807FC929].unk272;
            }
            if (D_807FC924[D_807FC929].unk274 < x) {
                x = D_807FC924[D_807FC929].unk274;
            }
            if (D_807FC924[D_807FC929].unk276 < y) {
                y = D_807FC924[D_807FC929].unk276;
            }
            if (x < *arg1) {
                *arg1 = x;
            }
            if (y < *arg2) {
                *arg2 = y;
            }
            if (*arg3 < x) {
                *arg3 = x;
            }
            if (*arg4 < y) {
                *arg4 = y;
            }
            i++;
            p++;
        } while (i < arg0);
    }
    if ((*arg1 == *arg3) || (*arg2 == *arg4) || (flag != 0)) {
        *arg1 = -1;
        *arg2 = -1;
        *arg3 = -1;
        *arg4 = -1;
    }
}

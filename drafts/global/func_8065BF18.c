// func_8065BF18 (src/global/5E2F0.c): Stage 5/6: frame size 160 matched, case 1 matched 100%, remaining diff is branch likely in case 0
#include <ultra64.h>

typedef struct Cam2_Struct_3C {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 x;
    /* 0x1C */ f32 y;
    /* 0x20 */ f32 z;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ s16 unk30;
    /* 0x32 */ s16 unk32;
    /* 0x34 */ s16 unk34;
    /* 0x36 */ u8 unk36;
    /* 0x37 */ u8 unk37;
    /* 0x38 */ u8 unk38;
    /* 0x39 */ u8 unk39;
    /* 0x3A */ u8 unk3A;
    /* 0x3B */ u8 pad3B;
} Cam2_Struct_3C;

void func_8062A944(f32, f32, f32);
void func_8062AC68(Mtx *);
void func_8062AD28(f32, f32, f32, void *, void *);
void func_8062DB70(f32, f32, f32, f32, f32, f32);
s32 func_8062DBDC(s16, s16, s16, s16, s32, s32, f32, f32, f32, f32, void *);
extern u8 D_807F5E20[];
extern u8 D_807F5E68[];

#define Cam2_SQ(x) ((x) * (x))

s32 func_8065BF18(Cam2_Struct_3C *arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9, s32 arg10) {
    Mtx sp60;
    f32 dx, dy;

    if ((arg0->unk3A & 2) && (arg10 != arg0->unk30) && (arg4 != -0x8000)) {
        return 0;
    }

    dx = arg0->x - arg1;
    dy = arg0->y - arg2;
    if (sqrtf((dx * dx) + (dy * dy) + Cam2_SQ(arg0->z - arg3)) < (f32)arg0->unk32) {
        if (arg4 == -0x8000) {
            return 1;
        }
        switch (arg0->unk39) {
        case 0:
            if (arg0->x < (f32)arg4 - arg0->unk14) goto fail;
            if (arg0->y < (f32)arg5 - arg0->unk14) goto fail;
            if (arg0->z < (f32)arg6 - arg0->unk14) goto fail;
            if ((f32)arg7 + arg0->unk14 < arg0->x) goto fail;
            if ((f32)arg8 + arg0->unk14 < arg0->y) goto fail;
            if ((f32)arg9 + arg0->unk14 < arg0->z) goto fail;
            return 1;
        case 1:
            guLookAt(&sp60, arg0->x, arg0->y, arg0->z, (arg0->x == arg0->unk24) ? (arg0->unk24 + 0.2f) : arg0->unk24, arg0->unk28, arg0->unk2C, 0.0f, 1.0f, 0.0f);
            func_8062A944(arg0->unk8 * 2, 1.0f, (f32)arg0->unk34);
            func_8062AC68(&sp60);
            func_8062AD28(arg0->x, arg0->y, arg0->z, &D_807F5E68, &D_807F5E20);
            func_8062DB70(arg0->x, arg0->y, arg0->z, arg0->unk24, arg0->unk28, arg0->unk2C);
            return func_8062DBDC(arg4, arg5, arg6, arg7, arg8, arg9, arg0->x, arg0->y, arg0->z, (f32)arg0->unk34, &D_807F5E68);
        }
    }
fail:
    return 0;
}

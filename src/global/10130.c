#include "common.h"

typedef struct {
    u8 unk0[0x7C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 unk88[0x5E];
    s16 unkE6;
} SmallARecord;

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    s16 unkC;
    u8 unkE[2];
    u8 unk10;
    u8 unk11;
    u8 unk12[];
} SmallAInputRecord;

extern u8 D_807FC950[];

void func_8060B430(SmallARecord *arg0, SmallAInputRecord *arg1) {
    arg0->unk7C = arg1->unk0;
    arg0->unk80 = arg1->unk4;
    arg0->unk84 = arg1->unk8;
    arg0->unkE6 = arg1->unkC;
    memcpy(&D_807FC950[arg1->unk10 * 0x5E], arg1->unk12, 0x5E);
}

extern s16 D_807463B0;
extern s8 D_807463B8;
extern SmallAInputRecord D_807ECE20;

s16 func_8060B49C(SmallARecord *arg0, s32 arg1) {
    D_807463B8 = 2;
    func_8060B430(arg0, &D_807ECE20);
    return D_807463B0;
}

extern s16 D_807463AC;
extern u16 D_807463B4;
extern u16 *D_807ECE94;
extern s16 *D_807ECE98;

void func_8060B4D4(u8 *arg0) {
    if (D_807463AC < (D_807463B0 - 1)) {
        arg0[2] = ((s8 *) D_807ECE98)[2];
        arg0[3] = ((s8 *) D_807ECE98)[3];
        if (*D_807ECE98 & 0x8000) {
            D_807463B4 = *D_807ECE94;
            D_807ECE94++;
        }
        *(s16 *) arg0 = D_807463B4 & 0xEFFF;
    }
}

void func_8060B55C(s16 *arg0) {
    if (D_807463AC < (D_807463B0 - 1)) {
        *arg0 = *D_807ECE98 & 0x7FFF;
        D_807ECE98 += 2;
        D_807463AC++;
    } else {
        D_807463B8 = 0;
    }
}

extern s16 D_807463A0;
extern s16 *D_807463A8;
extern s16 *D_807ECE90;


#pragma GLOBAL_ASM("asm/global/nonmatchings/10130/func_8060B5C0.s")


void func_8060B6CC(void) {
    D_807463A8 = NULL;
    D_807ECE90 = NULL;
    D_807463AC = 0;
    D_807463B0 = 0;
    D_807463A0 = 0;
    D_807463B8 = 0;
}

void heapFree(void *);

void func_8060B700(void) {
    if (D_807463A8 != NULL) {
        heapFree(D_807463A8);
    }
    if (D_807ECE90 != NULL) {
        heapFree(D_807ECE90);
    }
    func_8060B6CC();
}

s32 func_8066B0F8(s32, s32, s32, s32);
void assetFreeBuffer(s32, s32, s32);
void func_8060B5C0(s32);

void func_8060B750(s32 arg0) {
    s32 sp1C;

    sp1C = func_8066B0F8(0x11, arg0, 1, 1);
    func_8060B5C0(sp1C);
    assetFreeBuffer(sp1C, 0xF8, 0x33);
    D_807ECE98 = D_807463A8;
    D_807ECE94 = D_807ECE90;
    D_807463AC = 0;
    D_807463B4 = 0;
}

extern u8 D_807ECE30;

u8 func_8060B7C4(void) {
    return D_807ECE30;
}


void func_8060B7D0(s32 *arg0, s32 *arg1) {
    *arg0 = ((u8 *) &D_807ECE20)[0xE];
    *arg1 = ((u8 *) &D_807ECE20)[0xF];
}

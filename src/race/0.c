#include "common.h"

#ifdef NON_MATCHING
typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    u8 pad6;
    u8 unk7;
    u8 unk8;
    u8 pad9;
} RaceC_Entry;

typedef struct {
    u8 pad0[0x10];
    s16 unk10;
    u8 pad12[0x14 - 0x12];
    RaceC_Entry *unk14;
} RaceC_DCA0;

typedef struct {
    u8 pad0[0x24];
    u8 unk24;
    u8 unk25;
} RaceC_DC90;

typedef struct {
    s16 unk0;
    u8 pad2[2];
    f32 unk4;
    u8 unk8;
    u8 pad9[3];
} RaceC_Row;

typedef struct {
    u8 pad0[0x6A];
    u16 unk6A;
    u8 pad6C[0x7C - 0x6C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xB8 - 0x88];
    f32 unkB8;
    u8 padBC[0xC0 - 0xBC];
    f32 unkC0;
    f32 unkC4;
    u8 padC8[0xDC - 0xC8];
    s16 unkDC;
    u8 padDE[0xE0 - 0xDE];
    f32 unkE0;
    u8 padE4[0xEE - 0xE4];
    s16 unkEE;
    u8 padF0[0x154 - 0xF0];
    u8 unk154;
} RaceC_Act;

extern s32 D_8076A0A8;
extern void *D_807FBB40;
extern void *D_807FBB48;
extern RaceC_DC90 *D_807FDC90;
extern RaceC_DCA0 *D_807FDCA0;
extern RaceC_Row D_8002FB10[];
extern RaceC_Row D_8002FB70[];
#define RC_A ((RaceC_Act *)D_807FBB40)
#define RC_B ((RaceC_Act *)D_807FBB48)
f32 func_80611BB4(f32, f32);
f32 func_80612790(s16);
f32 func_80612794(s16);
void actorScriptStart(void *, s32);

void func_80024000(void) {
    f32 sp54;
    f32 sp50;
    f32 fs0;
    f32 fs1;
    f32 sp44;
    f32 sp40;
    RaceC_Entry *a0;
    f32 fv0;
    u8 sp37;
    int a1;
    s16 v1;
    RaceC_Row *sp30;

    sp37 = D_807FDC90->unk24;
    if (D_8076A0A8 == 0x52) {
        sp30 = D_8002FB10;
    } else {
        sp30 = D_8002FB70;
    }
    sp44 = RC_A->unkB8;
    sp40 = func_80612794((s16)(s32)(RC_A->unkE0 * 11.4)) * 20.0f;
    a0 = &D_807FDCA0->unk14[D_807FDC90->unk25];
    fs1 = RC_A->unk84 - a0->unk4;
    fs0 = RC_A->unk7C - a0->unk0;
    if (sqrtf(fs1 * fs1 + fs0 * fs0) < (a0 = &D_807FDCA0->unk14[a1 = D_807FDC90->unk25])->unk7) {
        if ((a0->unk2 < RC_A->unk80 ? RC_A->unk80 - a0->unk2 : -(RC_A->unk80 - a0->unk2)) < 80.0f && a1 < D_807FDCA0->unk10 - 1) {
            RaceC_Row *row = &sp30[sp37];
            if (a1 == row->unk0) {
                RC_A->unkC4 = row->unk4;
                if (row->unk8 == 1) {
                    actorScriptStart(D_807FBB40, 0x286);
                    RC_A->unkC0 = 200.0f;
                    RC_A->unk154 += 1;
                }
                D_807FDC90->unk24 += 1;
                a1 = D_807FDC90->unk25;
            }
            D_807FDC90->unk25 = a1 + 1;
            a0 = &D_807FDCA0->unk14[D_807FDC90->unk25];
        }
    }
    sp54 = (f64)(a0->unk8 - RC_A->unkB8 / 10.0f) * 0.8;
    fv0 = (f64)(RC_A->unk80 - RC_B->unk80) * 0.25;
    if (fv0 > 6.0f) {
        fv0 = 6.0f;
    }
    if (fv0 < -6.0f) {
        fv0 = -6.0f;
    }
    sp54 = sp54 + fv0;
    v1 = (s32)((f64)func_80611BB4(-fs0, -fs1) * 4096.0 / 6.2831854820251465) - RC_A->unkEE;
    if (v1 >= 0x800) {
        v1 = (f64)v1 - 4096.0;
    }
    if (v1 < -0x800) {
        v1 = (f64)v1 + 4096.0;
    }
    sp50 = (f64)(RC_A->unkB8 * v1) / 10000.0;
    fs0 = func_80612794(RC_A->unkEE) * sp44;
    fs1 = func_80612790(RC_A->unkEE) * sp44;
    if (RC_A->unk6A & 1) {
        fs0 += func_80612794(RC_A->unkDC) * sp40;
        fs1 += func_80612790(RC_A->unkDC) * sp40;
    }
    fs0 += func_80612794(RC_A->unkEE) * sp54;
    fs1 += func_80612790(RC_A->unkEE) * sp54;
    fs0 += func_80612790(RC_A->unkEE) * sp50;
    fs1 -= func_80612794(RC_A->unkEE) * sp50;
    sp44 = sqrtf(fs0 * fs0 + fs1 * fs1);
    fv0 = func_80611BB4(fs0, fs1);
    if (RC_A->unkC4 != -20.0f && RC_A->unkC4 != -360.0f) {
        RC_A->unkB8 = D_807FDCA0->unk14[D_807FDC90->unk25].unk8 * 10.0;
    } else {
        RC_A->unkB8 = sp44;
    }
    RC_A->unkEE = (f64)fv0 * 4096.0 / 6.2831854820251465;
    if (RC_A->unk6A & 1) {
        fv0 = RC_A->unkB8;
        RC_A->unkB8 = fv0 - (f32)((f64)(fv0 * fv0) / 15000.0);
        if (RC_A->unkB8 < 0.0f) {
            RC_A->unkB8 = 0.0f;
        }
    }
}
#else

#pragma GLOBAL_ASM("asm/race/nonmatchings/0/func_80024000.s")
#endif

typedef struct {
    u8 pad0[0x1A];
    s16 unk1A;
    s32 unk1C;
} RaceC_Arg1;

typedef struct {
    u8 pad0[0x36];
    u8 unk36;
} RaceC_Arg0;

s32 flagGet(s16, s32);
extern u16 D_80750AC4;

int func_80024634(RaceC_Arg0 *arg0, RaceC_Arg1 *arg1) {
    return arg0->unk36 != 0 && flagGet(arg1->unk1A, 0) == 0 && D_80750AC4 >= arg1->unk1C;
}

#pragma GLOBAL_ASM("asm/race/nonmatchings/0/func_80024690.s")

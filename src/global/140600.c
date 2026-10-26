#include "common.h"

typedef struct SynVoiceParam {
    struct SynVoiceParam *next;
    s32 delta;
    s16 type;
    union {
        f32 f;
        s32 i;
    } data;
} SynVoiceParam;

typedef struct {
    u8 unk0[0x88];
    s32 delta;
} SynPVoice;

extern ALSynth *D_807563E4;
SynVoiceParam *__n_allocParam(void);
s32 n_alEnvmixerParam(void *, s32, SynVoiceParam *);

void n_alSynSetPitch(ALVoice *voice, f32 pitch) {
    SynVoiceParam *param;

    if (voice->pvoice != NULL) {
        param = __n_allocParam();
        if (param == NULL) {
            return;
        }
        param->delta = D_807563E4->paramSamples + ((SynPVoice *)voice->pvoice)->delta;
        param->type = 7;
        param->data.f = pitch;
        param->next = NULL;
        n_alEnvmixerParam(voice->pvoice, 3, param);
    }
}

void n_alSynSetPan(ALVoice *voice, f32 pan) {
    SynVoiceParam *param;

    if (voice->pvoice != NULL) {
        param = __n_allocParam();
        if (param == NULL) {
            return;
        }
        param->delta = D_807563E4->paramSamples + ((SynPVoice *)voice->pvoice)->delta;
        param->type = 0x13;
        param->data.f = pan;
        param->next = NULL;
        n_alEnvmixerParam(voice->pvoice, 3, param);
    }
}

void n_alSynSetFXMix(ALVoice *voice, u8 fxmix) {
    SynVoiceParam *param;

    if (voice->pvoice != NULL) {
        param = __n_allocParam();
        if (param == NULL) {
            return;
        }
        param->delta = D_807563E4->paramSamples + ((SynPVoice *)voice->pvoice)->delta;
        param->type = 0x12;
        param->data.i = fxmix;
        param->next = NULL;
        n_alEnvmixerParam(voice->pvoice, 3, param);
    }
}


typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
} LpfNMBiquad;


#pragma GLOBAL_ASM("asm/global/nonmatchings/140600/func_8073BB10.s")

typedef struct {
    s16 unk0;
    s16 unk2;
    u32 unk4;
    s16 coeff[16];
    s32 state;
} SynLPFilter;

void _init_lpfilter(SynLPFilter *filter) {
    s32 sp14;
    s32 sp10;
    s16 spE;
    f32 sp8;
    f32 sp4;
    f32 sp0;

    sp10 = (s32)((f32)filter->unk0 * 16384.0f);
    spE = (s16)(sp10 >> 0xF);
    filter->unk2 = (s16)(s32)(16384.0f - (f32)spE);
    filter->state = 0;
    sp14 = 0;
    do {
        filter->coeff[sp14] = 0;
    } while (++sp14 < 8);
    filter->coeff[sp14++] = spE;
    sp0 = 16384.0f;
    sp4 = sp8 = (f32)spE / sp0;
    if (sp14 < 0x10) {
        do {
            sp4 *= sp8;
            filter->coeff[sp14] = (s16)(s32)(sp4 * sp0);
        } while (++sp14 < 0x10);
    }
}

f32 func_8073BDC4(s32 arg0) {
    f32 sp4;
    f32 sp0;

    sp0 = 1.0f;
    if (arg0 >= 0) {
        sp4 = 1.0594631f;
    } else {
        sp4 = 0.9438743f;
        arg0 = -arg0;
    }
    if (arg0 != 0) {
        do {
            if (arg0 & 1) {
                sp0 *= sp4;
            }
            sp4 *= sp4;
            arg0 = arg0 >> 1;
        } while (arg0 != 0);
    }
    return sp0;
}

void func_8073BB10(f32, f32, f32, LpfNMBiquad *, LpfNMBiquad *);

void func_8073BE54(SynLPFilter *filter, f32 arg1) {
    s32 sp3C;
    LpfNMBiquad sp30;
    LpfNMBiquad sp24;

    if (filter->unk2 == 0) {
        return;
    }
    if (filter->unk2 < 10) {
        filter->unk2 = 10;
    }
    func_8073BB10(arg1, (f32)filter->unk0 + 10.0f, (f32)filter->unk2 / 10.0f, &sp30, &sp24);
    sp3C = 3;
    do {
        filter->coeff[sp3C] = 0;
    } while (++sp3C < 8);
    filter->coeff[0] = (s16)(s32)(((f32 *)&sp30)[0] * (26768.0f - ((f32)filter->unk2 * 128.0f)));
    filter->coeff[1] = (s16)(s32)(((f32 *)&sp30)[1] * (26768.0f - ((f32)filter->unk2 * 128.0f)));
    filter->coeff[2] = 0;
    filter->coeff[8] = (s16)(s32)(((f32 *)&sp24)[1] * -16384.0f);
    filter->coeff[9] = (s16)(s32)(((f32 *)&sp24)[2] * -16384.0f);
    sp3C = 10;
    do {
        filter->coeff[sp3C] = 0;
    } while (++sp3C < 16);
}

typedef struct {
    u8 unk0[0x14];
    void *unk14;
    void *unk18;
    u8 unk1C[8];
    f32 unk24;
    s32 unk28;
} LpfNMDelay;

typedef struct {
    SynLPFilter base;
    void *unk2C;
    void *unk30;
} LpfNMFilter;

typedef struct {
    s32 unk0;
    s32 unk4;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    u8 unkE[2];
    f32 unk10;
    f32 unk14;
    s32 unk18;
    f32 unk1C;
    LpfNMFilter *unk20;
    LpfNMDelay *unk24;
} LpfNMFx;

typedef struct {
    s32 unk0;
    LpfNMFx *unk4;
    u8 unk8;
    u8 unk9[0x17];
    s16 *unk20;
    s16 *unk24;
    s16 *unk28;
    s16 *unk2C;
} LpfNMFxState;


#pragma GLOBAL_ASM("asm/global/nonmatchings/140600/n_alFxNew.s")

typedef struct {
    u8 unk0[0xC];
    void *unkC;
    void *unk10;
    u8 unk14[0x14];
    s32 unk28;
    u8 unk2C[8];
    s32 unk34;
    s32 unk38;
    s32 unk3C;
    void *unk40;
    f32 unk44;
    s32 unk48;
    f32 unk4C;
    s32 unk50;
    void *unk54;
    s16 unk58;
    s16 unk5A;
    s16 unk5C;
    s16 unk5E;
    s16 unk60;
    s16 unk62;
    s16 unk64;
    s16 unk66;
    s16 unk68;
    u8 unk6A[4];
    s16 unk6E;
    s32 unk70;
    s32 unk74;
    s32 unk78;
    s32 unk7C;
    s32 unk80;
    s32 unk84;
    u8 unk88[4];
    u8 unk8C;
    u8 unk8D[3];
    s16 unk90;
    s16 unk92;
    u8 unk94[0x24];
    s32 unkB8;
    void *unkBC;
} SynPVoiceInit;

void alN_PVoiceNew(SynPVoiceInit *arg0, s32 (*arg1)(void *), ALHeap *arg2) {
    arg0->unkC = alHeapDBAlloc(NULL, 0, arg2, 1, 0x20);
    arg0->unk10 = alHeapDBAlloc(NULL, 0, arg2, 1, 0x20);
    arg0->unk28 = arg1(arg0->unk2C);
    arg0->unk34 = 0;
    arg0->unk38 = 1;
    arg0->unk3C = 0;
    arg0->unk40 = alHeapDBAlloc(NULL, 0, arg2, 1, 0x20);
    arg0->unk4C = 0.0f;
    arg0->unk50 = 1;
    arg0->unk44 = 1.0f;
    arg0->unk48 = 0;
    arg0->unk54 = alHeapDBAlloc(NULL, 0, arg2, 1, 0x50);
    arg0->unk78 = 1;
    arg0->unk84 = 0;
    arg0->unk5A = 1;
    arg0->unk68 = 1;
    arg0->unk6E = 1;
    arg0->unk5C = 1;
    arg0->unk5E = 1;
    arg0->unk60 = 0;
    arg0->unk62 = 0;
    arg0->unk66 = 1;
    arg0->unk64 = 0;
    arg0->unk66 = 1;
    arg0->unk64 = 0;
    arg0->unk70 = 0;
    arg0->unk74 = 0;
    arg0->unk58 = 0;
    arg0->unk7C = 0;
    arg0->unk80 = 0;
    arg0->unk8C = 0;
    arg0->unk92 = 0;
    arg0->unk90 = 0;
    arg0->unkBC = alHeapDBAlloc(NULL, 0, arg2, 1, 8);
    arg0->unkB8 = 0;
}


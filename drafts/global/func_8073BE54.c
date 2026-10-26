// func_8073BE54 (src/global/140600.c): stage 4: frame 0x40 and slots match; closest C is 8 bytes short because direct struct field loads replace target addiu-plus-load forms
typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
} SynVoiceBiquad;

typedef struct {
    s16 unk0;
    s16 unk2;
    u32 unk4;
    s16 coeff[16];
    s32 state;
} SynVoiceLPFilter;

void func_8073BB10(f32, f32, f32, SynVoiceBiquad *, SynVoiceBiquad *);

void func_8073BE54(SynVoiceLPFilter *filter, f32 arg1) {
    s32 sp3C;
    SynVoiceBiquad sp30;
    SynVoiceBiquad sp24;

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
    filter->coeff[0] = (s16)(s32)(sp30.unk0 * (26768.0f - ((f32)filter->unk2 * 128.0f)));
    filter->coeff[1] = (s16)(s32)(sp30.unk4 * (26768.0f - ((f32)filter->unk2 * 128.0f)));
    filter->coeff[2] = 0;
    filter->coeff[8] = (s16)(s32)(sp24.unk4 * -16384.0f);
    filter->coeff[9] = (s16)(s32)(sp24.unk8 * -16384.0f);
    sp3C = 10;
    do {
        filter->coeff[sp3C] = 0;
    } while (++sp3C < 16);
}

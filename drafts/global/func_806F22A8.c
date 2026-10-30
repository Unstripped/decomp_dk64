// func_806F22A8 (src/global/F56F0.c): Stage 5: frame 0xD0 + stack slots + instruction stream match; diffs: kind in s6 vs s3 / arg1 s3 vs s4, loop lb/sb order and entry-ptr increment position (target loads 0/4(s2) before addiu s2), lwc1 140(sp) order after func_806F1AE0. Uses F56A* types (identical to src) + s8 value[4] to keep byte in memory, f64 pad2 frame pad
typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
} F5N1Spring;

void func_806F1A18(f32 arg0, f32 arg1, F5N1Spring *arg2, f32 *arg3);

typedef struct {
    u8 pad0[0x14];
    u8 unk14;
    u8 pad15[3];
    s32 unk18;
} F5N1Predicate;

s32 func_806F1B58(F5BActor *arg0, F5N1Predicate *arg1, s32 arg2);

typedef struct {
    F5N1Spring unk0;
    F5N1Spring unkC;
} F56APair;

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    u8 padC[4];
    f32 unk10;
    u8 unk14;
    u8 pad15[3];
    s32 unk18;
    F56APair unk1C[8];
    u8 padDC[0x60];
} F56AState;

typedef struct {
    u8 pad0[0x10];
    s16 unk10;
} F56AIdxMeta;

typedef struct {
    F56AIdxMeta *unk0;
} F56AIdxSub;

typedef struct {
    u8 pad0[0x60];
    u32 unk60;
    u8 pad64[0x114];
    F56AState *unk178;
} F56AActor;

void actorGetNodePos(Actor *, s32, f32 *, f32 *, f32 *);
s32 randomNonNegative(void);
extern s8 D_80752D4E[];
extern f32 D_80752F4C;

void func_806F22A8(Actor *arg0, F5BSlot *arg1, s32 *arg2) {
    F56AState *state;
    F56APair *pair;
    s32 index;
    s32 kind;
    s32 active;
    s32 i;
    s32 pad;
    f32 spB0;
    f32 spAC;
    f32 spA8;
    f32 spA4;
    f32 fs3;
    f32 fs2;
    f32 fs1;
    f32 fs0;
    f32 z;
    f32 y;
    f32 x;
    s8 value[4];
    f32 target;
    f32 dz;
    f32 result;
    f64 pad2;

    state = ((F56AActor *) arg0)->unk178;
    index = *arg2;
    kind = 0x1A;
    pair = state->unk1C;
    spAC = 0.0f;
    spB0 = 0.0f;
    fs3 = 0.0f;
    fs2 = 0.0f;
    spA8 = 0.0003f;
    spA4 = 1.0f;
    fs1 = 0.06f;
    active = func_806F1B58((F5BActor *) arg0, (F5N1Predicate *) state, 3);
    value[3] = -0x80;
    actorGetNodePos(arg0, 5, &x, &y, &z);
    if (active == 0) {
        state->unk0 = (f32) arg0->unkE6;
        state->unk4 = y;
        D_80752F4C = 0.0f;
        if ((state->unk14 != 0) && (((F56AActor *) arg0)->unk60 & 0x100) && (state->unk18 == 3)) {
            state->unk14 -= 1;
        }
    } else {
        fs2 = y - state->unk4;
        dz = fs2 - state->unk8;
        fs0 = state->unk0 - (f32) arg0->unkE6;
        if (((F56AIdxSub *) arg0->unk4)->unk0->unk10 >= 0) {
            target = (f32) D_80752D4E[((F56AIdxSub *) arg0->unk4)->unk0->unk10];
        } else {
            target = -128.0f;
        }
        state->unk0 = (f32) arg0->unkE6;
        state->unk10 = (f32) ((f64) state->unk10 + ((f64) (target - state->unk10) * 0.3));
        value[3] = (s8) state->unk10;
        if (arg0->unk154 == 0x4F) {
            fs1 = 0.01f;
            spA8 = 0.0001f;
            spA4 = 0.4f;
        }
        result = func_806F1AE0((F5BActor *) arg0, (F5BAccel *) state, 0.011f);
        state->unk8 = fs2;
        state->unk4 = y;
        fs3 = (-result - ((0.005f * dz) + (0.0008f * fs2))) * spA4;
        if ((32.0f + ((1.0f - spA4) * 8.0f)) < (f32) ((randomNonNegative() >> 15) % 40)) {
            D_80752F4C = (f32) (0x14 - ((randomNonNegative() >> 15) % 40)) * spA8;
        }
        if (fs0 > 2048.0f) {
            fs0 = 4096.0f - fs0;
        } else if (fs0 < -2048.0f) {
            fs0 = -(4096.0f + fs0);
        }
        fs2 = (f32) ((f64) ((1.0f - (arg0->unkB8 / 130.0f)) * D_80752F4C) + (2e-05 * (f64) fs0));
    }
    i = 0;
    do {
        if (active != 0) {
            func_806F1A18(fs3, fs1, &pair->unk0, &spB0);
            func_806F1A18(fs2, fs1, &pair->unkC, &spAC);
        }
        arg1[index].unk1 = kind;
        i += 1;
        arg1[index].unk0 = value[3];
        arg1[index].unk2 = (s16) (s32) ((f64) (pair->unk0.unk4 + pair->unk0.unk0) * 10430.218905280077);
        arg1[index].unk4 = (s16) (s32) ((f64) (pair->unkC.unk4 + pair->unkC.unk0) * 10430.218905280077);
        arg1[index].unk6 = 0;
        pair++;
        index++;
        kind++;
    } while (i != 11);
    *arg2 = index;
}

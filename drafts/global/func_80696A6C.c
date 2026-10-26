// func_80696A6C (src/global/936B0.c): 407/417 insns matched; exact 0x48 frame, rodata, and control flow match; 10 insns differ only in v0 vs v1 temporary allocation across two blocks (sp44->unk10 countdown and D_807FBB40->unk11C check)
typedef struct M93K_Actor174 {
    /* 0x00 */ u32 unk0;
    /* 0x04 */ u8 pad4[4];
    /* 0x08 */ f32 unk8;
    /* 0x0C */ u8 padC[4];
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 unk11;
    /* 0x12 */ u8 pad12[6];
    /* 0x18 */ s16 unk18;
} M93K_Actor174;

typedef struct M93K_Actor {
    /* 0x00 */ u8 pad0[0x58];
    /* 0x58 */ s32 unk58;
    /* 0x5C */ u8 pad5C[4];
    /* 0x60 */ u32 unk60;
    /* 0x64 */ u8 pad64[0x6E - 0x64];
    /* 0x6E */ s16 unk6E;
    /* 0x70 */ u8 pad70[0x7C - 0x70];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
    /* 0x84 */ f32 unk84;
    /* 0x88 */ u8 pad88[0xAC - 0x88];
    /* 0xAC */ f32 unkAC;
    /* 0xB0 */ u8 padB0[0xB8 - 0xB0];
    /* 0xB8 */ f32 unkB8;
    /* 0xBC */ u8 padBC[4];
    /* 0xC0 */ f32 unkC0;
    /* 0xC4 */ f32 unkC4;
    /* 0xC8 */ u8 padC8[0xE6 - 0xC8];
    /* 0xE6 */ s16 unkE6;
    /* 0xE8 */ u8 padE8[0xEE - 0xE8];
    /* 0xEE */ s16 unkEE;
    /* 0xF0 */ s16 unkF0;
    /* 0xF2 */ u8 padF2[0xFD - 0xF2];
    /* 0xFD */ u8 unkFD;
    /* 0xFE */ u8 padFE[0x11C - 0xFE];
    /* 0x11C */ struct M93K_Actor *unk11C;
    /* 0x120 */ u8 pad120[4];
    /* 0x124 */ M93D_Actor124 *unk124;
    /* 0x128 */ u8 pad128[2];
    /* 0x12A */ s16 unk12A;
    /* 0x12C */ u8 pad12C[0x154 - 0x12C];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[0x15E - 0x156];
    /* 0x15E */ u8 unk15E;
    /* 0x15F */ u8 pad15F[0x174 - 0x15F];
    /* 0x174 */ M93K_Actor174 *unk174;
} M93K_Actor;

#define M93K_ACTOR ((M93K_Actor *)D_807FBB40)
#define M93K_TARGET ((M93K_Actor *)D_807FBB4C)

extern s16 D_80770628[];
extern f32 D_80770B68[];
extern f32 D_80770BC0[];
void func_80604CBC(Actor *, s32, s32, s32, s32, s32, f32, s32);
void func_80605314(Actor *, s32);
void func_8067E278(s32, s32);
void actorSetUniformScale(Actor *, f32);
f32 func_80665E94(f32, f32, f32, f32, f32, f32, s32);
f32 func_80612794(s16);
void func_807149A8(s32);
void func_8071AF30(void);

void func_80696A6C(void) {
    M93K_Actor174 *sp44;
    s16 temp_v0;
    s16 sp40;

    sp44 = M93K_ACTOR->unk174;
    func_80695724(15.0f, 0);
    if (D_8076A0A8 == 0x6F) {
        if (M93K_ACTOR->unk80 < M93K_ACTOR->unkAC) {
            M93K_ACTOR->unk80 = M93K_ACTOR->unkAC;
            M93K_ACTOR->unkC0 = M93K_ACTOR->unkC4;
        }
    }
    func_8065D254(D_807FBB40, 0x3C8, 0x40, 0x40, 100, 100, 1, 0x4B, 0x78, 0, 1.0f);
    if (!(M93K_ACTOR->unk60 & 0x10)) {
        sp44->unk18 = (s32)M93K_ACTOR->unkB8;
        M93K_ACTOR->unk12A = 1000;
        M93K_ACTOR->unk60 |= 0x400;
        sp44->unk0 += 0x78;
        if (M93K_ACTOR->unk6E == -1) {
            func_80604CBC(D_807FBB40, 0x114, 0x1E, 1, 0, 0xFF, 1.0f, 0);
            D_80770B68[D_80770628[M93K_ACTOR->unk6E]] = 0.75f;
            D_80770BC0[D_80770628[M93K_ACTOR->unk6E]] = 1.0f;
        }
        sp44->unk10 = 0xF;
        sp44->unk11 = 0;
        actorSetUniformScale(D_807FBB40, (f64)M93K_ACTOR->unk124->unkC * 0.15);
    }
    sp44->unk11++;
    if (sp44->unk10 < sp44->unk11) {
        func_806086CC(M93K_ACTOR->unk7C, M93K_ACTOR->unk80, M93K_ACTOR->unk84, 0x15B, 0xFF, 0x6E, 0, 0x1E, 0.3f, 0);
        sp44->unk11 = 0;
        if (sp44->unk10 >= 3) {
            sp44->unk10--;
        }
    }
    if ((u32)(sp44->unk0 - 100) < D_8076A068) {
        M93K_ACTOR->unk60 &= ~0x80000;
    }
    if (((u32)(sp44->unk0 + D_80750344) < D_8076A068) || ((M93K_ACTOR->unkFD != 0) && (M93K_ACTOR->unk58 != 0xA9)) || (D_807FBB85 != 0)) {
        func_8067E278(0, 1);
        func_80605314(D_807FBB40, 0);
        actorDespawn(D_807FBB40);
        if ((M93K_ACTOR->unk11C != NULL) && (M93K_ACTOR->unk11C->unk58 == 0xB9) && (M93K_ACTOR->unk11C->unk154 != 0x37)) {
            M93K_ACTOR->unk11C->unk155++;
        }
    }
    temp_v0 = func_80665DE0(M93K_TARGET->unk7C, M93K_TARGET->unk84, M93K_ACTOR->unk7C, M93K_ACTOR->unk84);
    if (temp_v0 < M93K_ACTOR->unkE6) {
        sp40 = M93K_ACTOR->unkE6 - temp_v0;
    } else {
        sp40 = temp_v0 - M93K_ACTOR->unkE6;
    }
    M93K_ACTOR->unkE6 = func_806CC190(M93K_ACTOR->unkE6, temp_v0, 10.0f);
    switch (M93K_ACTOR->unk154) {
    case 0:
        if (sp40 > 1000) {
            M93K_ACTOR->unk154 = 1;
            M93K_ACTOR->unk155 = 0;
        }
        /* fallthrough */
    case 2:
        if (M93K_ACTOR->unk154 == 2) {
            if (M93K_ACTOR->unkB8 > 100.0f) {
                M93K_ACTOR->unk154 = 0;
            }
        }
        if (M93K_ACTOR->unkB8 + 20.0f < sp44->unk18) {
            M93K_ACTOR->unkB8 += 20.0f;
        } else {
            M93K_ACTOR->unkB8 = sp44->unk18;
        }
        M93K_ACTOR->unkEE = func_806CC190(M93K_ACTOR->unkEE, M93K_ACTOR->unkE6, 1.0f);
        M93K_ACTOR->unkF0 = func_806CC190(M93K_ACTOR->unkF0, (s16)(s32)(((f64)func_80665E94(M93K_TARGET->unk7C, M93K_TARGET->unk80 + (f32)(u32)M93K_TARGET->unk15E, M93K_TARGET->unk84, M93K_ACTOR->unk7C, M93K_ACTOR->unk80, M93K_ACTOR->unk84, 20) * 2048.0) / 3.1415927410125732), 30.0f);
        M93K_ACTOR->unkC0 = func_80612794(M93K_ACTOR->unkF0) * -M93K_ACTOR->unkB8;
        sp44->unk8 = -(func_80611BB4(M93K_ACTOR->unkC0, M93K_ACTOR->unkB8) * 57.295776f);
        break;
    case 1:
        if (M93K_ACTOR->unkB8 - 10.0f > 5.0f) {
            M93K_ACTOR->unkB8 -= 10.0f;
        } else {
            M93K_ACTOR->unkB8 = 5.0f;
        }
        if (M93K_ACTOR->unkB8 <= 5.0f) {
            M93K_ACTOR->unk154 = 2;
            M93K_ACTOR->unk155 = 0;
        }
        break;
    }
    if (M93K_ACTOR->unk58 == 0x59) {
        func_807149B8(1);
        func_8071498C(func_8071AF30);
        func_807149A8(1000);
        func_80714950((s32)D_807FBB40);
        func_80714C08(&D_80720120, 1.0f, D_807FBB40, 1, 0);
    }
    func_806319C4(D_807FBB40, 0);
}

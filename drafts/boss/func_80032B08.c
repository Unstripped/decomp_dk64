// func_80032B08 (src/boss/C920.c): from .scratch/Boss3E/func_80032B08_best.c
typedef struct Boss2E_Sub4_0 {
    char pad0[4];
    f32 unk4;
    char pad8[8];
    s16 unk10;
} Boss2E_Sub4_0;

typedef struct Boss2E_Sub4 {
    Boss2E_Sub4_0 *unk0;
} Boss2E_Sub4;

typedef struct Boss2E_Sub174_0_174 {
    char pad0[4];
    f32 unk4;
    char pad8[0xA];
    s8 unk12;
    char pad13[1];
    s8 unk14;
    char pad15[2];
    s8 unk17;
} Boss2E_Sub174_0_174;

typedef struct Boss2E_Sub174_0 {
    char pad0[0x7C];
    f32 unk7C;
    char pad80[4];
    f32 unk84;
    char pad88[0xCC];
    u8 unk154;
    char pad155[0x1F];
    Boss2E_Sub174_0_174 *unk174;
} Boss2E_Sub174_0;

typedef struct Boss2E_Sub174 {
    Boss2E_Sub174_0 *unk0;
    s8 unk4;
    s8 unk5;
} Boss2E_Sub174;

typedef struct Boss2E_Actor {
    char pad0[4];
    Boss2E_Sub4 *unk4;
    char pad8[0x58];
    s32 unk60;
    char pad64[0x18];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0x5C];
    s16 unkE4;
    s16 unkE6;
    s16 unkE8;
    char padEA[0x40];
    s16 unk12A;
    char pad12C[0x18];
    u8 unk144;
    char pad145[0x25];
    u8 unk16A;
    u8 unk16B;
    u8 unk16C;
    char pad16D[7];
    Boss2E_Sub174 *unk174;
} Boss2E_Actor;

void func_80613C48(void *, s16, f32, f32);
void func_80609140(s32, s32, f32, f32, s32, s32);
void func_80614644(void *, void *, f32);
void func_806782C0(void *);
void func_806907F0(f32, f32, f32);
void func_80690A28(s32, s32, f32, f32, f32, f32, f32, void *);
void actorUpdateModelMatrix(void *, s32);
extern s16 D_80035B00[];
extern s16 D_80035B08[];
extern s16 D_80035B10[];
extern s16 D_80035B18[];
extern s16 D_80035B20[];
extern s8 D_80035B28;
extern s16 D_80035B2C;
extern f32 D_80035B3C;
extern s16 D_80035B74;
extern f32 D_80036DC4;

#define ACTOR ((Boss2E_Actor *)D_807FBB40)

void func_80032B08(void) {
    Boss2E_Sub174 *sub174 = ACTOR->unk174;
    Boss2E_Sub174_0_174 *sp30 = sub174->unk0->unk174;
    Boss2E_Sub4_0 *sub4_0 = ACTOR->unk4->unk0;

    if (sub174->unk5 == 0) {
        f32 dx = D_807FBB4C->unk7C - ACTOR->unk7C;
        f32 dz = D_807FBB4C->unk84 - ACTOR->unk84;
        D_80036DC4 = dx * dx + dz * dz;
    }
    if (!(ACTOR->unk60 & 0x10)) {
        func_80613C48(ACTOR, sub174->unk4 + 0x668, 0.0f, 0.0f);
        ACTOR->unk12A = 0xFA0;
    }
    if (D_80035B28 & (1 << sub174->unk4)) {
        ACTOR->unkE8 = (s16)((s32)((f64)sp30->unk4 * 1024.0) - 0x400);
        ACTOR->unkE4 = D_80035B2C;
        if (sub4_0 != NULL) {
            if (D_80035B3C != sub4_0->unk4) {
                func_80614644(ACTOR, sub4_0, D_80035B3C);
            }
        }
    } else {
        ACTOR->unkE8 = 0;
        if (sub4_0 != NULL) {
            s32 v0 = sub174->unk4 + 0x66B;
            if (v0 != sub4_0->unk10) {
                func_80613C48(ACTOR, v0, 0.0f, 0.0f);
                func_80609140(0x38D, 0x7D00, 63.0f, 1.0f, 0, 0);
            } else {
                func_80614644(ACTOR, sub4_0, sub4_0->unk4 + 0.75f);
            }
            if (sub174->unk4 == 1) {
                if (sub4_0->unk4 > 24.0f) {
                    sub4_0->unk4 = 24.0f;
                }
                if (sub4_0->unk4 > 15.0f) {
                    ACTOR->unk80 -= 10.0f;
                }
            } else {
                if (sub4_0->unk4 > 37.0f) {
                    sub4_0->unk4 = 37.0f;
                }
                if (sub4_0->unk4 > 26.0f) {
                    ACTOR->unk80 -= 10.0f;
                }
            }
            if ((f64)ACTOR->unk80 < 0.0) {
                func_80609140(0x384, 0x7D00, 63.0f, 1.0f, 0, 0);
                func_806782C0(ACTOR);
            }
        }
    }
    if (sub174->unk5 == 0) {
        ACTOR->unk144 = 0xC;
        if (sub174->unk4 == 0) {
            if (sp30->unk17 == 1) {
                s16 temp_v1;
                if (sub174->unk0->unk154 == 0) {
                    D_80035B74 = 0x28;
                }
                temp_v1 = D_80035B74 - 1;
                D_80035B74 = temp_v1;
                if (temp_v1 < 0) {
                    f32 x = ACTOR->unk7C + D_80035B18[sp30->unk14];
                    f32 y = ACTOR->unk80 + 270.0f;
                    f32 z = ACTOR->unk84 + D_80035B20[sp30->unk14];
                    D_80035B74 = 0xA;
                    func_806907F0(x, y, z);
                    func_80690A28(0x2C, 1, 0.25f, D_807FBB4C->unk7C, D_807FBB4C->unk80, D_807FBB4C->unk84, 2400.0f, ACTOR);
                }
            } else {
                D_80035B74 = 0;
            }
        }
        ACTOR->unk7C = D_80035B00[sp30->unk14] + sub174->unk0->unk7C;
        ACTOR->unk84 = D_80035B08[sp30->unk14] + sub174->unk0->unk84;
        ACTOR->unkE6 = D_80035B10[sp30->unk14];
    } else {
        s32 var_v0;
        ACTOR->unk144 = 1;
        var_v0 = sp30->unk14 + 2;
        if (var_v0 >= 4) {
            var_v0 -= 4;
        }
        ACTOR->unk7C = D_80035B00[var_v0] + sub174->unk0->unk7C;
        ACTOR->unk84 = D_80035B08[var_v0] + sub174->unk0->unk84;
        ACTOR->unkE6 = D_80035B10[var_v0];
        ACTOR->unk60 |= 0x800000;
        ACTOR->unk16A = 0x23;
        ACTOR->unk16B = 0x23;
        ACTOR->unk16C = 0x46;
        if (sp30->unk12 != 1) {
            ACTOR->unk60 &= ~4;
        } else {
            ACTOR->unk60 |= 4;
        }
    }
    actorUpdateModelMatrix(ACTOR, 0);
}
#undef ACTOR

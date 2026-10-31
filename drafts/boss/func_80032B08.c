// func_80032B08 (src/boss/C920.c): stage 5 (OlT revisit): frame -56, s0/s1, 370-371 insns. sfx consts must be int-bit args (0x427C0000,0x3F800000) with K&R sfxPlayOnFreeSlot (old 63.0f/1.0f promoted to doubles: +9 insns). (s16)((s16)((s32)(f64*1024.0))-0x400) fixes mfc1 t9. Remaining ~11 opcode diffs: uopt hoists the D_80035B74 LOAD's lui above the unk17==1 bne (target keeps lui v1 right before lh v1); NOT a spelling issue: 243 assignments of 5 accesses over B74/B70[2]/B6C[4]/B68[6]/B60[10] spellings, dead reads, static/defined D_80035B74 all keep the hoist. Also target evaluates z(B20 table) lui first/x second, y add in jal delay slot (xyz,xzy,zyx,inline-arg orders tried: arg order never moves the y add). Park uses decls B70/B6C from the 31AA0 park block.
typedef struct BossAnimState {
    char pad0[4];
    f32 unk4;
    char pad8[8];
    s16 unk10;
} BossAnimState;

typedef struct BossModelRef {
    BossAnimState *unk0;
} BossModelRef;

typedef struct BossParentState {
    char pad0[4];
    f32 unk4;
    char pad8[0xA];
    s8 unk12;
    char pad13[1];
    s8 unk14;
    char pad15[2];
    s8 unk17;
} BossParentState;

typedef struct BossParentActor {
    char pad0[0x7C];
    f32 unk7C;
    char pad80[4];
    f32 unk84;
    char pad88[0xCC];
    u8 unk154;
    char pad155[0x1F];
    BossParentState *unk174;
} BossParentActor;

typedef struct BossFollowerLink {
    BossParentActor *unk0;
    s8 unk4;
    s8 unk5;
} BossFollowerLink;

typedef struct BossFollowerActor {
    char pad0[4];
    BossModelRef *unk4;
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
    BossFollowerLink *unk174;
} BossFollowerActor;

void func_80613C48(void *, s16, f32, f32);
void sfxPlayOnFreeSlot();
void controllerApplyMotionWindow(void *, void *, f32);
void actorDespawn(void *);
void projectileSetTargetCoords(f32, f32, f32);
void projectileAimAndSpawn(s32, s32, f32, f32, f32, f32, f32, void *);
extern s16 D_80035B00[];
extern s16 D_80035B08[];
extern s16 D_80035B10[];
extern s16 D_80035B18[];
extern s16 D_80035B20[];
extern s8 D_80035B28;
extern s16 D_80035B2C;
extern f32 D_80035B3C;
extern s16 D_80035B74;
extern s16 D_80035B70; /* declared in the func_80031AA0 park block of C920.c */
extern s8 D_80035B6C;
extern f32 D_80036DC4;

#define ACTOR ((BossFollowerActor *)D_807FBB40)

void func_80032B08(void) {
    BossFollowerLink *sub174 = ACTOR->unk174;
    BossParentState *sp30 = sub174->unk0->unk174;
    BossAnimState *sub4_0 = ACTOR->unk4->unk0;

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
                controllerApplyMotionWindow(ACTOR, sub4_0, D_80035B3C);
            }
        }
    } else {
        ACTOR->unkE8 = 0;
        if (sub4_0 != NULL) {
            s32 v0 = sub174->unk4 + 0x66B;
            if (v0 != sub4_0->unk10) {
                func_80613C48(ACTOR, v0, 0.0f, 0.0f);
                sfxPlayOnFreeSlot(0x38D, 0x7D00, 0x427C0000, 0x3F800000, 0, 0);
            } else {
                controllerApplyMotionWindow(ACTOR, sub4_0, sub4_0->unk4 + 0.75f);
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
                sfxPlayOnFreeSlot(0x384, 0x7D00, 0x427C0000, 0x3F800000, 0, 0);
                actorDespawn(ACTOR);
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
                (&D_80035B70)[2] = temp_v1;
                if (temp_v1 < 0) {
                    f32 x = ACTOR->unk7C + D_80035B18[sp30->unk14];
                    f32 y = ACTOR->unk80 + 270.0f;
                    f32 z = ACTOR->unk84 + D_80035B20[sp30->unk14];
                    ((s16 *)&D_80035B6C)[4] = 0xA;
                    projectileSetTargetCoords(x, y, z);
                    projectileAimAndSpawn(0x2C, 1, 0.25f, D_807FBB4C->unk7C, D_807FBB4C->unk80, D_807FBB4C->unk84, 2400.0f, ACTOR);
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

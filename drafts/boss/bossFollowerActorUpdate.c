// bossFollowerActorUpdate (src/boss/DAA0.c): Ovl (leftovers7): stage 5, count exact (419 lines = expected, same frame/saves), deadsweep full 37 text 27 reloc 10 shape 32 (was full 83 text 77 reloc 6 shape 26). Levers found: (1) function-local 'static s16 D_80035B74 = 0x78;' (only user; needs .data carve; reloc 10 = '.data' vs absolute symbol) replaces the (&D_80035B6C)[4] hack, giving the exact lui/sh/lui/lh B74 pattern; then plain 'D_80035B74 -= 1; if (D_80035B74 < 0)' (no temp_v1) makes the whole decrement chain exact incl. v1; (2) ugen t-ring is LRU-by-last-use: target mfc1 t9/addiu t8/lh t7/lw t1 = oldest regs = 2 ring temps burned inside the unkE8 statement: 'ACTOR->unkE8 = (s16)(s32)((f64)sp30->unk4 * 1024.0) - 0x400;' (no-code (s16) before the subtract; grid of {s16,u16,s32,u32}^0..3 wrapper chains at inner/outer positions) fixed the ring phase of ~100 lines (text 156 -> 42); (3) f32 z declared before x in the projectile block. FAKEs left: the static, the (s16) wrapper, 'if (ACTOR->unk80) {}' (needed for the late FP block), 'if (D_80035B18) {}' (needed, deleting costs 6). Remaining text diff 27: early FP lines 185-192 (ours colours ACTOR->unk80 f0 because of the dead test, target ring f4; zero pair f6 vs f8), li 35 coloured v0 (target a1), final projectileSetTargetCoords FP block (target colours the two cvt.s.w in f0/f2 and loads 'lw a0' after the first mtc1; ours ring f10/f4). Tried: deadsweep 3 rounds x3 bases (no gain), 5 random hill-climbs (dead tests + (T*)(x|0) ring burners, count-exact), exhaustive replace-one-FAKE, FP dead tests on cvt operands (worse), named f32 conversion locals (66), local temp type grids. Parked in Ovl copy under NON_MATCHING.
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
extern s16 D_80035B70;
extern s8 D_80035B6C;
extern f32 D_80036DC4;

#define ACTOR ((BossFollowerActor *)D_807FBB40)

void bossFollowerActorUpdate(void) {
    BossFollowerLink *sub174 = ACTOR->unk174;
    BossParentState *sp30 = sub174->unk0->unk174;
    BossAnimState *sub4_0 = ACTOR->unk4->unk0;
    static s16 D_80035B74 = 0x78; // FAKE: function-local static (only user; shadows the file-scope definition, which the .data carve moves here) keeps uopt from pointerizing D_80035B74

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
        ACTOR->unkE8 = (s16)(s32)((f64)sp30->unk4 * 1024.0) - 0x400;  // FAKE: no-code (s16) narrowing of the truncated value burns ugen ring temps
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
                if (ACTOR->unk80) {}  // FAKE: dead test steers uopt colouring
                sfxPlayOnFreeSlot(0x384, 0x7D00, 0x427C0000, 0x3F800000, 0, 0);
                actorDespawn(ACTOR);
            }
        }
    }
    if (sub174->unk5 == 0) {
        ACTOR->unk144 = 0xC;
        if (sub174->unk4 == 0) {
            if (sp30->unk17 == 1) {
                if (sub174->unk0->unk154 == 0) {
                    D_80035B74 = 0x28;
                }
                D_80035B74 -= 1;
                if (D_80035B74 < 0) {
                    f32 z = ACTOR->unk84 + D_80035B20[sp30->unk14];
                    f32 x = ACTOR->unk7C + D_80035B18[sp30->unk14];
                    f32 y = ACTOR->unk80 + 270.0f;
                    D_80035B74 = 0xA;
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
        if (D_80035B18) {}  // FAKE: deadsweep dead statement (steers uopt)
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

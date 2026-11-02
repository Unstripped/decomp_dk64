#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB4C;

#ifdef NON_MATCHING
typedef struct LgBObj {
    /* 0x00 */ u8 pad0[0x10];
    /* 0x10 */ s16 unk10;
} LgBObj;

typedef struct LgBModel {
    /* 0x00 */ LgBObj *unk0;
    /* 0x04 */ u8 pad4[0x34];
    /* 0x38 */ f32 unk38;
} LgBModel;

typedef struct LgBState {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ s16 unk34;
    /* 0x36 */ s8 unk36;
    /* 0x37 */ s8 unk37;
    /* 0x38 */ u8 unk38;
    /* 0x39 */ u8 unk39;
} LgBState;

typedef struct LgBActor {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ LgBModel *unk4;
    /* 0x008 */ u8 pad8[0x58];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u8 pad64[0x18];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x94];
    /* 0x11C */ Actor *unk11C;
    /* 0x120 */ u8 pad120[8];
    /* 0x128 */ s16 unk128;
    /* 0x12A */ u8 pad12A[0x34];
    /* 0x15E */ u8 unk15E;
    /* 0x15F */ u8 pad15F[0x19];
    /* 0x178 */ LgBState *unk178;
} LgBActor;

#define LGB ((LgBActor *)D_807FBB40)

extern s8 D_80750650;
extern s8 D_807FC8C0[16];
extern u16 D_807ECD58;
extern u16 D_807ECD60;
Gfx *func_806BCF98(Gfx *, Actor *);
void behaviourFrameBegin(void);
void func_806BD0CC(void);
void currentActorClearFlag(void);
s32 flagGet(s32, s32);
void camStartPath();
s32 currentActorTestClearFlag(void);
void renderCallbacksRegister(void *, void *, s32);
void camResumePath(void);
void playerResumeLocomotion(void *);
s32 camIsCutsceneActive(void);
void actorScriptStart(void *, s32);
void hudSpawnCountdownTimer(s32, s32, s32);
void flagSet();
void sfxAllocateChannel(s32, f32);
void sfxStopChannel(s32, s32);
void actorSetStateTwo(void *);
void actorDespawn(void *);
void csModelStateSetFirstByte(s16, s32);
void csModelStateSetByte(s16, s32, s32);
f32 randomFloat(void);
void sfxPlayFromActorWithAltitudeCheck(void *, s32, s32, s32, s32);
void func_80613C48(void *, s32, f32, f32);
void controllerApplyMotionWindow(void *, void *, f32);
void actorUpdateModelMatrix(void *, s32);

extern s8 D_807FC8D0;

void func_806BC1E0(void) {
    f32 old;
    f32 b;
    f32 t;
    f32 acc;
    f32 a;
    f32 sp70;
    s16 i;
    LgBState *st;
    LgBObj *obj;
    s32 j;
    s16 adx;
    s16 dx;
    s16 best;
    s8 v;
    s16 dy;
    s16 n;
    s8 cand[16];
    s16 ones;
    s16 zeros;
    f64 fx;

    st = LGB->unk178;
    obj = LGB->unk4->unk0;
    behaviourFrameBegin();
    if (!(LGB->unk60 & 0x10)) {
        st->unk4 = 0.0f;
        func_806BD0CC();
        LGB->unk128 = 0x80;
        LGB->unk60 &= 0xFFFF7FFF;
        st->unk24 = LGB->unk7C;
        st->unk28 = LGB->unk80;
        st->unk2C = LGB->unk84;
        if (sp70 != 0) {}  // FAKE: dummy statement steers uopt
        st->unk30 = LGB->unk4->unk38;
        currentActorClearFlag();
    }
    switch (st->unk38) {
    case 0:
        if (flagGet(0x10F, 0) == 0) {
            if ((LGB->unk7C - D_807FBB4C->unk7C) * (LGB->unk7C - D_807FBB4C->unk7C) + (LGB->unk84 - D_807FBB4C->unk84) * (LGB->unk84 - D_807FBB4C->unk84) < 14400.0) {
                camStartPath(D_807FBB40, 0, 1);
                st->unk39 = 0;
                st->unk38 = 1;
            }
        }
        break;
    case 1:
        if (currentActorTestClearFlag() != 0) {
            st->unk38 = 2;
        }
        break;
    case 2:
        switch (st->unk39) {
        case 0:
            renderCallbacksRegister(func_806BCF98, D_807FBB40, 5);
            if ((D_807ECD58 & 0x8000) && !(D_807ECD60 & 0x8000)) {
                camResumePath();
                st->unk39 = 1;
                D_807FBB4C->unk154 = 0xC;
                D_807FBB4C->unk155[0] = 0;
                playerResumeLocomotion(D_807FBB4C);
            }
            if ((D_807ECD58 & 0x4000) && !(D_807ECD60 & 0x4000)) {
                camResumePath();
                st->unk39 = 2;
                D_807FBB4C->unk154 = 0xC;
                D_807FBB4C->unk155[0] = 0;
                playerResumeLocomotion(D_807FBB4C);
            }
            break;
        case 1:
            camStartPath(D_807FBB40, 1, 1);
            st->unk39 = 3;
            break;
        case 3:
            if (currentActorTestClearFlag() != 0) {
                D_80750650 = 1;
                st->unk38 = 3;
                st->unk4 = 0.025f;
                st->unk0 = 0.0f;
                st->unk8 = LGB->unk7C;
                st->unkC = LGB->unk80;
                st->unk10 = LGB->unk84;
                st->unk14 = 294.0f;
                st->unk18 = 0.0f;
                st->unk1C = 359.0f;
                st->unk36 = 3;
                st->unk37 = 0;
                st->unk20 = -500.0f;
                actorScriptStart(D_807FBB40, 0x31C);
                hudSpawnCountdownTimer(0xDC, 0x2A, 0x3C);
                flagSet(0x30, 1, 2);
                sfxAllocateChannel(0x78, 1.0f);
                actorSetStateTwo(LGB->unk11C);
            }
            break;
        case 2:
            if (camIsCutsceneActive() == 0) {
                if ((LGB->unk7C - D_807FBB4C->unk7C) * (LGB->unk7C - D_807FBB4C->unk7C) + (LGB->unk84 - D_807FBB4C->unk84) * (LGB->unk84 - D_807FBB4C->unk84) > 25600.0) {
                    st->unk39 = 0;
                    st->unk38 = 0;
                }
            }
            break;
        }
        break;
    case 3:
    case 4:
        if (st->unk4 == 0.0f) {
            if (st->unk38 == 3) {
                st->unk38 = 4;
            }
            if (LGB->unk11C != NULL && LGB->unk11C->unk154 == 5) {
                ones = 0;
                zeros = 0;
                j = 0;
                do {
                    if (D_807FC8C0[j] == 1) {
                        ones++;
                    }
                    if (D_807FC8C0[j] == 0) {
                        zeros++;
                    }
                    j++;
                } while (&D_807FC8C0[j] < &D_807FC8D0); // FAKE: pointer-compare bound steers loop strength reduction
                flagSet(0x30, 0, 2, ones);
                actorScriptStart(D_807FBB40, 0x31C);
                D_80750650 = 1;
                if (ones < zeros) {
                    st->unk38 = 6;
                } else {
                    st->unk38 = 7;
                }
                st->unk4 = 0.0125f;
                st->unk0 = 0.0f;
                st->unk8 = LGB->unk7C;
                st->unkC = 0.0f;
                st->unk10 = LGB->unk84;
                st->unk14 = st->unk24;
                st->unk18 = st->unk28;
                st->unk1C = st->unk2C;
                st->unk20 = -500.0f;
                st->unk34 = 0x1E;
            } else {
                actorScriptStart(D_807FBB40, 0);
                D_80750650 = 0;
                best = 4;
                n = 0;
                for (i = 0; i < 16; i++) {
                    if (D_807FC8C0[i] == 0 || D_807FC8C0[i] == -1) {
                        dx = (i & 3) - st->unk36;
                        dy = (i >> 2) - st->unk37;
                        if (dx > 0) {
                            adx = dx;
                        } else {
                            adx = -dx;
                        }
                        if (adx < (dy > 0 ? dy : -dy)) {
                            if (dy > 0) {
                                adx = dy;
                            } else {
                                adx = -dy;
                            }
                        }
                        if (adx > 0) {
                            if (adx < best) {
                                cand[0] = i;
                                n = 1;
                                best = adx;
                            } else if (adx == best) {
                                cand[n++] = i;
                            }
                        }
                    }
                }
                if (n > 0) {
                    acc = randomFloat();
                    v = cand[(s32)(acc * (f32)(n - 1))];
                    dx = (v & 3) - st->unk36;
                    dy = (v >> 2) - st->unk37;
                    if (dx < -1) {
                        dx = -1;
                        if (ones == 0) {}  // FAKE: dummy statement steers uopt
                    }
                    if (dx >= 2) {
                        dx = 1;
                    }
                    if (dy < -1) {
                        dy = -1;
                        if (n == 0) {}  // FAKE: dummy statement steers uopt
                    }
                    if (dy >= 2) {
                        dy = 1;
                    }
                    st->unk36 += dx;
                    st->unk37 += dy;
                }
                st->unk4 = 0.01369863f;
                st->unk0 = 0.0f;
                st->unk8 = st->unk14;
                st->unkC = 0.0f;
                st->unk10 = st->unk1C;
                fx = st->unk36;
                st->unk14 = fx * -11.666666666666666 + 329.0 + (f64)st->unk37 * -28.666666666666668;
                st->unk18 = 0.0f;
                st->unk1C = fx * 28.333333333333332 + 274.0 + (f64)st->unk37 * -11.333333333333334;
                st->unk20 = -250.0f;
            }
        }
        break;
    case 6:
        if (st->unk34 == 0 && st->unk4 == 0.0f) {
            sfxStopChannel(0x78, 1);
            sfxAllocateChannel(0x56, 1.0f);
            actorScriptStart(D_807FBB40, 0x31C);
            actorDespawn(LGB->unk11C);
            camStartPath(D_807FBB40, 2, 1);
            st->unk38 = 8;
        }
        break;
    case 8:
        if (currentActorTestClearFlag() != 0) {
            func_806BD0CC();
            if (flagGet(0x10F, 0) == 0) {
                csModelStateSetFirstByte(0x10, 0xA);
            }
            st->unk38 = 0xA;
            sfxStopChannel(0x56, 1);
            sfxAllocateChannel(0x67, 1.0f);
        }
        break;
    case 10:
        break;
    case 7:
        if (st->unk34 == 0 && st->unk4 == 0.0f) {
            actorDespawn(LGB->unk11C);
            actorScriptStart(D_807FBB40, 0x31C);
            camStartPath(D_807FBB40, 3, 1);
            st->unk38 = 9;
            sfxStopChannel(0x78, 1);
            sfxAllocateChannel(0x57, 1.0f);
        }
        break;
    case 9:
        if (currentActorTestClearFlag() != 0) {
            sfxStopChannel(0x57, 1);
            sfxAllocateChannel(0x67, 1.0f);
            func_806BD0CC();
            st->unk39 = 0;
            st->unk38 = 2;
        }
        break;
    default:
        if (adx && adx) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        break;
    }
    LGB->unk60 |= 0x400;
    LGB->unk15E = 0x14;
    st->unk34--;
    if (st->unk34 < 0) {
        st->unk34 = 0;
    }
    acc = 0.0f; // FAKE: dead store, keeps the 0.0 constant candidate in $f18
    sp70 = st->unk30;
    if (st->unk4 != 0.0f && st->unk34 == 0) {
        b = st->unk4;
        old = st->unk0;
        st->unk0 = old + b;
        if (D_80750650 == 0) {
            if (old < 0.63f && st->unk0 >= 0.63f) {
                csModelStateSetByte(st->unk36 + st->unk37 * 4, 1, 1);
                sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x361, 0xFF, 0x7F, 0xA);
            }
        } else {
            sp70 += (st->unk0 - 0.5f) * 0.25f;
        }
        if ((f64)st->unk0 >= 1.0) {
            st->unk0 = 0.0; // FAKE: double zero literal (constant register)
            st->unk4 = 0.0; // FAKE: double zero literal (constant register)
            LGB->unk7C = st->unk14;
            LGB->unk80 = st->unk18;
            LGB->unk84 = st->unk1C;
        } else {
            t = st->unk0;
            if (D_80750650 == 0) {
                t = st->unk0;
                if (t == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                t = 2.0 * (f64)t;
                if ((f64)t > 1.0) {
                    t = 1.0f;
                }
            }
            LGB->unk7C = st->unk8 + t * (st->unk14 - st->unk8);
            LGB->unk84 = st->unk10 + t * (st->unk1C - st->unk10);
            if (D_80750650 == 0) {
                a = st->unkC;
                LGB->unk80 = a + t * (st->unk18 - a);
            } else {
                t = st->unk20;
                a = st->unkC;
                b = st->unk0;
                acc = (f32)((f64)(st->unk18 - a) - (f64)t * 0.5);
                LGB->unk80 = (f64)a + ((f64)(acc * b) + (f64)(b * b * t) * 0.5);
            }
        }
        if (D_80750650 == 0 && obj != NULL && st->unk0 != 0.0f) {
            if (obj->unk10 != 0x5C3) {
                func_80613C48(D_807FBB40, 0x5C3, 0.0f, 0.0f);
            }
            controllerApplyMotionWindow(D_807FBB40, obj, st->unk0 * 40.0f);
        }
    }
    LGB->unk4->unk38 = LGB->unk4->unk38 + (sp70 - LGB->unk4->unk38) * 0.25f;
    actorUpdateModelMatrix(D_807FBB40, 0);
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/C0EE0/func_806BC1E0.s")
#endif

extern u8 D_1000118[];
extern u8 D_2000180[];
#define R1C0C1_WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (u32)(_w1); }

Gfx *textDrawStringVtx(Gfx *, s32, s32, s32, char *, s32);

Gfx *func_806BCF98(Gfx *dl, Actor *actor) {
    R1C0C1_WRITE_GFX(dl++, 0xDE000000, D_1000118);
    R1C0C1_WRITE_GFX(dl++, 0xE200001C, 0x504240);
    gDPSetPrimColor(dl++, 0, 0, 255, 255, 255, 255);
    R1C0C1_WRITE_GFX(dl++, 0xFC119623, 0xFF2FFFFF);
    R1C0C1_WRITE_GFX(dl++, 0xDA380003, D_2000180);
    dl = textDrawStringVtx(dl, 1, 0x208, 0xC8, "q YES", 1);
    return textDrawStringVtx(dl, 1, 0x208, 0x12C, "b NO", 1);
}

extern s8 D_807FC8C0[];

void func_806BD094(s16 idx, s8 val) {
    if (idx >= 0 && idx < 0x10) {
        D_807FC8C0[idx] = val;
    }
}

void flagSet(s32, s32, s32);
void csModelStateSetFirstByte(s16, s32);

void func_806BD0CC(void) {
    s32 i;

    flagSet(0x30, 0, 2);
    for (i = 0; i < 0x10; i++) {
        D_807FC8C0[i] = -1;
        csModelStateSetFirstByte(i, 0);
    }
    D_807FC8C0[5] = 0;
    D_807FC8C0[6] = 1;
    D_807FC8C0[9] = 1;
    D_807FC8C0[0xA] = 0;
}

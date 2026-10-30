// func_806A5868 (src/global/A8400.c): stage 6, regalloc only (text diff 13): switch(unk154) + `!(f < unk18)` + unk1D `>= 0x34 ? 0x33 : x` + bare `if (sub->unk1D)` + v0 hoisted before the else-if matched structure; remaining: first-load temp a1 + move v0,a1 (expected single v0), ori/andi t0/t9 order in unk55 &~4 / |4 arm, FP temp ring f10/f8/f18 in case 2. FAKE `if (v0) {}` in flag block
#include "common.h"
#include "actor.h"

typedef struct SpriteBehaviour {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u8 pad2[0x2];
    /* 0x04 */ void *unk4;
    /* 0x08 */ u8 pad8[0x4];
    /* 0x0C */ void *unkC;
    /* 0x10 */ u8 pad10[0x4];
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ u8 pad1C[0x1];
    /* 0x1D */ u8 unk1D;
    /* 0x1E */ u8 pad1E[0x2];
    /* 0x20 */ f32 unk20;
    /* 0x24 */ u8 pad24[0x10];
    /* 0x34 */ void *unk34;
    /* 0x38 */ s16 unk38;
    /* 0x3A */ s16 unk3A;
    /* 0x3C */ u8 pad3C[0x19];
    /* 0x55 */ u8 unk55;
} SpriteBehaviour;

extern Actor *D_807FBB40;
extern u16 D_807ECD58;
extern u16 D_807ECD66;
extern u8 D_807503F0;

void *heapAlloc(s32);
void camResumePath(void);
void func_806A4DDC(Actor *);
void func_806A5174(Actor *, SpriteBehaviour *, f32);
void resNodeListFree(SpriteBehaviour *);
void resQueueRemove(void *);
void renderCallbacksRegister(void *, void *, s32);

void func_806A5868(void) {
    SpriteBehaviour *sub;
    f32 sp18;
    u8 state;
    u8 v0;
    f32 f;

    sub = D_807FBB40->unk174;
    sp18 = 0.05f;
    if (!(D_807FBB40->unk60 & 0x10)) {
        sp18 = 1.0f;
        sub->unk34 = heapAlloc(0x280);
        sub->unk55 = 0;
    } else {
        v0 = sub->unk55;
        if (!(v0 & 1)) {
            if (D_807FBB40->unk154 != 4 && D_807FBB40->unk154 != 5) {
                if (15.0 < (f64)sub->unk0) {
                    if (D_807ECD66 & 0x4000) {
                        v0 = (sub->unk55 |= 1);
                    }
                    if (D_807ECD58 & 0x2000) {
                        sub->unk55 = v0 | 2;
                    } else {
                        sub->unk55 = v0 & 0xFFFD;
                    }
                    if (v0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    v0 = sub->unk55;
                    if ((v0 & 2) || D_807ECD58 != 0x8000) {
                        sub->unk55 = v0 & 0xFFFB;
                    } else {
                        sub->unk55 = v0 | 4;
                    }
                    if (sub->unk55 & 1) {
                        camResumePath();
                        D_807FBB40->unk154 = 5;
                    }
                }
            }
        }
    }
    sub->unk38 = sub->unk38 + 0x14;
    sub->unk3A = sub->unk3A + 0x32;
    switch (D_807FBB40->unk154) {
    case 0:
        if (sub->unk0 < 0x1E) {
            sub->unk0 = sub->unk0 + 1;
        } else {
            D_807FBB40->unk154 = 1;
            sub->unk1D = D_807503F0;
            func_8070E808(D_807FBB40, sub->unk4);
            renderCalcChainCenterOffset((ChainRowHead *)sub);
        }
        break;
    case 2:
        f = 2.0f;
        if (sub->unk55 & 4) {
            f = f * 3.0f;
        } else if (sub->unk55 & 2) {
            f = f * 0.5f;
        }
        if (!(f < sub->unk18)) {
            f = sub->unk18;
        }
        sub->unk18 = sub->unk18 - f;
        sub->unk14 = sub->unk14 - f;
        if ((f64)sub->unk18 < 0.0001) {
            D_807FBB40->unk154 = 1;
        }
        break;
    case 4:
        if (sub->unk1D) {
            sub->unk1D -= (sub->unk1D >= 0x34) ? 0x33 : sub->unk1D;
        } else if (sub->unk0 != 0) {
            if (sub->unkC != NULL) {
                resNodeListFree(sub);
            }
            sub->unk0 = sub->unk0 - 1;
        } else {
            D_807FBB40->unk154 = 5;
        }
        break;
    case 5:
        resQueueRemove(sub->unk4);
        break;
    }
    if (D_807FBB40->unk154 != 5) {
        sub->unk20 = (f32)sub->unk0 * 0.033333335f;
        func_806A5174(D_807FBB40, sub, sp18);
        if (sub->unk0 != 0) {
            func_806A4DDC(D_807FBB40);
            renderCallbacksRegister(func_806A4284, D_807FBB40, 3);
        }
    }
}

// raceRacerSteerTowardWaypoint (src/race/52B0.c): func_8002978C (src/race/52B0.c): stage 5, 511 insns, frame 0x80/s0, deadsweep score 51 (614/614 lines, reloc=0): single FP-register swap (sp4C in f8 ring reload vs f16, thr in f16 vs f12; cascades f6<->f8). Leftovers-5 Boss: target has n=(sp4C-lo) f12, d=(thr-lo) f14 as coloured-looking temps, thr f16, sp4C reload f8 ring. Tried with no gain: x=x no-code defs (free, no effect), FP no-code defs (x*1.0f etc), named n/d locals on the pad slots (fold away unless dead-tested; dead FP tests change frame/colouring: 150-270), copies of sp4C/thr/lo (1500+10k combos), dropping dx/dz/lo/thr/fr, inline thr, FP literal spellings (0.0f/0.00f/.0f, 1.0f/1.00f), statement-order permutations of the head, thr placement, exhaustive dead-test pairs (150 singles x pairs) and Metropolis dead-test hill-climb (100k evals), removing each FAKE (F2 needed, F1 +1 only).
#include "common.h"
extern f32 D_8002FC28;
extern f32 D_8002FC58;
f32 func_8002DF38(void *, f32, void *, void *);
void *raceGetRoute(u8);
f32 func_8002F784(void *, void *, void *);
f32 raceGetProgressPercent(void *, void *, void *);
s32 randomLcgNext(void);
s16 mathAngleSignedDistance(s16, s16);
s16 mathAngleEaseToward(s16, s16, f32);
s32 mathAngleBetweenPoints2D(f32, f32, f32, f32);
s16 mathAngleDiscrete(f32, f32, f32, f32, f32);
extern f32 sqrtf(f32);

typedef struct {
    s16 unk0;
    s16 unk2;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    u8 pad10[0x20];
    void *unk30;
    u8 unk34;
    u8 unk35;
} RaceRacerState;

typedef struct {
    RaceC_Actor *unk0;
    void *unk4;
    u8 pad8[7];
    u8 unkF;
    u8 unk10;
} RaceTargetView;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    u8 pad6;
    u8 unk7;
    u8 unk8;
    u8 pad9;
} RaceWaypoint;

#define G2_WP ((RaceWaypoint *)((u8 *)D_807FDCA0->unk14 + idx * 10))
#define G2_F(o) (*(f32 *)((u8 *)D_807FBB40 + (o)))

f32 raceRacerSteerTowardWaypoint(void) {
    s32 idx;
    RaceRacerState *s0;
    RaceTargetView *sp74;
    RaceC_Actor *tmp;
    RaceC_State *sp6C;
    void *sp68;
    s32 pad_g64;
    s32 pad_g60;
    f32 sp5C;
    f32 sp58;
    f32 dx;
    f32 dz;
    f32 sp4C;
    s32 pad_g48;
    volatile u8 sp47;
    u8 sp46;
    u8 sp45;
    f32 lo;
    f32 thr;
    f32 fr;
    s16 ang;

    s0 = (RaceRacerState *)RC_A->unk178;
    sp74 = (RaceTargetView *)RC_A->unk180;
    tmp = s0->unk30;
    sp6C = tmp->unk174;
    sp68 = raceGetRoute(sp6C->unk26);
    sp5C = func_8002F784(sp68, s0, sp74->unk4);
    sp58 = 0.0f;
    sp47 = RC_A->unk6A & 1;
    sp45 = s0->unk35;
    idx = D_807FDC98->unk20[D_807FDC90->unk25 * 2];
    dx = (f32)G2_WP->x - RC_A->unk7C;
    dz = (f32)G2_WP->z - RC_A->unk84;
    sp4C = sqrtf(dx * dx + dz * dz);
    if (sp4C < (f32)G2_WP->unk7) {
        D_807FDC90->unk25 += 1;
        D_807FDC90->unk25 = D_807FDC90->unk25 % D_807FDC9C->unk11;
        sp74->unk10 = (G2_WP->unk8 == 0) && (sp74->unkF != 0);
        switch (G2_WP->unk8) {
            case 2:
                if (sp5C < 0.0f) {
                    actorScriptStart(D_807FBB40, 0x29E);
                    if (sp74->unkF >= 2) {
                        func_8002DE78(sp74, 1, D_8002FC20, D_8002FC50);
                    }
                    s0->unk35 = 1;
                }
                break;
            case 3:
                actorScriptStart(D_807FBB40, 0x2A1);
                break;
        }
    }
    ang = mathAngleDiscrete((f32)G2_WP->x, (f32)G2_WP->z, RC_A->unk7C, RC_A->unk84, sp4C);
    ang = mathAngleSignedDistance(ang, s0->unk0);
    thr = G2_WP->unk7 * 1.2;
    if (D_8002FC20) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    if (sp4C < thr) {
        lo = G2_WP->unk7;
        fr = (sp4C - lo) / (thr - lo);
        ang = ang * (1.0 + (1.0f - fr) * 1.5 * (2.0f * s0->unk4));
        if (sp4C && sp4C) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    }
    s0->unkC = s0->unkC + (ang * 0.0033333334f - s0->unkC) * 0.5f;
    if (s0->unk34 < 2 || s0->unk34 >= 5) {
        return sp5C;
    }
    if (sp74->unkF != 0 && raceGetProgressPercent(sp68, s0, sp6C) > 0.75) {
        func_8002DE78(sp74, 0, D_8002FC20, D_8002FC50);
    }
    switch (sp74->unkF) {
        case 0:
        case 1:
            switch (s0->unk35) {
                case 0:
                    if (RC_A->unk4->unk64 == 0x29E && sp74->unk10 != 0 && D_8002FC28 < sp5C && sp5C < D_8002FC30 && (randomLcgNext() & 0xFF) < 0xFU) {
                        actorScriptStart(D_807FBB40, 0x29F);
                    }
                    break;
                case 1:
                    sp58 = D_8002FC58;
                    G2_F(0xC4) = -50.0f;
                    break;
                case 2:
                    G2_F(0xC0) = 500.0f;
                    s0->unk35 += 1;
                    break;
                case 4:
                    if (sp47 != 0) {
                        actorScriptStart(D_807FBB40, 0x2A2);
                        s0->unk35 += 1;
                        G2_F(0xC4) = -30.0f;
                    }
                    break;
                case 5:
                    if (RC_A->unk80 <= G2_F(0xAC)) {
                        actorScriptStart(D_807FBB40, 0x29D);
                        s0->unk35 = 0;
                        sp74->unk10 = sp74->unkF != 0;
                    }
                    break;
            }
            break;
        case 4:
            ang = 0;
            switch (s0->unk35) {
                case 1:
                    s0->unk35 += 1;
                    break;
                case 2:
                    ang = mathAngleBetweenPoints2D(RC_A->unk7C, RC_A->unk84, sp74->unk0->unk7C, sp74->unk0->unk84) - s0->unk0;
                    ang = ang & 0xFFF;
                    break;
                case 4:
                    func_8002DE78(sp74, 5, D_8002FC20, D_8002FC50);
                    s0->unk2 = 0;
                    break;
            }
            s0->unk2 = mathAngleEaseToward(s0->unk2, ang, 5.0f);
            break;
    }
    if (sp58 == 0.0f) {
        sp46 = sp74->unkF;
        sp58 = func_8002DF38(sp74, sp5C, D_8002FC20, D_8002FC50);
        if (sp46 == 2 && sp74->unkF == 3) {
            actorScriptStart(D_807FBB40, 0x2A0);
        }
        if (sp46 == 3 && sp74->unkF == 4) {
            s0->unk35 = sp45;
        }
    }
    if (sp47 != 0) {
        sp58 = sp58 * 0.9;
        s0->unk8 = 0.1f;
        if (RC_A->unkB8 < 350.0f) {
            RC_A->unkB8 = RC_A->unkB8;
        } else {
            RC_A->unkB8 = 350.0f;
        }
    } else {
        s0->unk8 = 0.0f;
    }
    s0->unk4 = sp58;
    return sp5C;
}

// func_8002978C (src/race/52B0.c): OlU FE4c: stage 5 (not matched), frame 0x80/s0, temp slot 0x2C and ang slot 0x36 match, 51 raw diff lines (deadsweep score) = FP ring only: ours colours named thr (f32 candidate, adjsave 1.5, 'thr = unk7*1.2') f12 and reloads sp4C in f16; target thr=f16, sp4C reload f8, and (sp4C-lo)/(thr-lo) temps in f12/f14, so every later FP temp is one ring slot off (mtc1 a0/f6 vs f8 etc.). Found this round: raceGetRoute (not func_8002E960) callee; unnest ang = mathAngleSignedDistance(mathAngleDiscrete(..)) into 2 statements (drops the -78 narrow temp); extra named f32 'fr' + 'f32 lo,thr,fr,ang' decl order puts ang at 0x36 with temp slot 0x2C; deadsweep 'if (D_8002FC20) {}' after thr and 'if (sp4C && sp4C) {}' in the if (133->68); 'ang = mathAngleBetweenPoints2D(..)-unk0; ang = ang & 0xFFF;' split (68->51, permuter). Tried no effect: thr/lo inline or (thr = ..) in the if, named fa/fb (dx/dz reuse), w=G2_WP pointer, void->s32 on callees, 10k-variant deadsweep, 20 min permuter.
#include "common.h"

extern void *D_807FBB40;
typedef struct {
    u8 pad0[0x4];
    f32 unk4;
    u8 pad8[0x10 - 0x8];
    f32 unk10;
    u8 pad14[0x1C - 0x14];
    u16 unk1C;
    u8 pad1E[0x25 - 0x1E];
    u8 unk25;
    u8 unk26;
    u8 unk27;
    u8 unk28;
    u8 pad29[0x30 - 0x29];
    void *unk30;
    u8 unk34;
    u8 unk35;
    u8 unk36;
    u8 pad37[0x44 - 0x37];
    u8 unk44;
    u8 pad45[0x104 - 0x45];
    s32 unk104;
} RaceC_State;

typedef struct RaceC_Actor RaceC_Actor;

typedef struct {
    RaceC_Actor *unk0;
    s32 unk4;
    u8 unk8;
    u8 pad9;
    u16 unkA;
} RaceC_Target;

typedef struct {
    u8 pad0[0x10];
    s16 unk10;
    u8 pad12[0xB8 - 0x12];
    f32 unkB8;
} RaceC_Obj;

typedef struct {
    RaceC_Obj *unk0;
    u8 pad4[0x64 - 0x4];
    u16 unk64;
} RaceC_Sub;

struct RaceC_Actor {
    u8 pad0[0x4];
    RaceC_Sub *unk4;
    u8 pad8[0x60 - 0x8];
    u32 unk60;
    u8 pad64[0x6A - 0x64];
    u16 unk6A;
    u8 pad6C[0x6E - 0x6C];
    s16 unk6E[2];
    u8 pad72[0x7C - 0x72];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xB8 - 0x88];
    f32 unkB8;
    u8 padBC[0xE4 - 0xBC];
    s16 unkE4;
    u8 padE6[0xE8 - 0xE6];
    s16 unkE8;
    u8 padEA[0x12A - 0xEA];
    s16 unk12A;
    u8 pad12C[0x144 - 0x12C];
    u8 unk144;
    u8 pad145[0x174 - 0x145];
    RaceC_State *unk174;
    RaceC_State *unk178;
    void *unk17C;
    RaceC_Target *unk180;
};

typedef struct {
    u8 pad0[4];
    RaceC_Actor *unk4;
    u8 pad8[0x2F0 - 8];
} RaceC_Player;

#define RC_A ((RaceC_Actor *)D_807FBB40)

typedef struct {
    u8 pad0[0x25];
    u8 unk25;
    u8 pad26[2];
    u8 unk28;
} RaceC_DC90;

typedef struct {
    u8 pad0[0x20];
    u8 *unk20;
} RaceC_DC98;

typedef struct {
    u8 pad0[0x11];
    u8 unk11;
} RaceC_DC9C;

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    u8 pad6[4];
} RaceC_Waypoint;

typedef struct {
    u8 pad0[0x14];
    RaceC_Waypoint *unk14;
} RaceC_DCA0;

extern RaceC_DC90 *D_807FDC90;
extern RaceC_DC98 *D_807FDC98;
extern RaceC_DC9C *D_807FDC9C;
extern RaceC_DCA0 *D_807FDCA0;
extern s16 D_80750AC8;
extern u8 D_8002FC20[];
extern u8 D_8002FC50[];
extern f32 D_8002FC30;
void actorScriptStart(void *, s32);
void func_8002DE78(void *, s32, void *, void *);
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
} RaceG2_Racer;

typedef struct {
    RaceC_Actor *unk0;
    void *unk4;
    u8 pad8[7];
    u8 unkF;
    u8 unk10;
} RaceG2_Tgt;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    u8 pad6;
    u8 unk7;
    u8 unk8;
    u8 pad9;
} RaceG2_Wp;

#define G2_WP ((RaceG2_Wp *)((u8 *)D_807FDCA0->unk14 + idx * 10))
#define G2_F(o) (*(f32 *)((u8 *)D_807FBB40 + (o)))

f32 func_8002978C(void) {
    s32 idx;
    RaceG2_Racer *s0;
    RaceG2_Tgt *sp74;
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

    s0 = (RaceG2_Racer *)RC_A->unk178;
    sp74 = (RaceG2_Tgt *)RC_A->unk180;
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

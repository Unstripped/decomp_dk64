// func_8068F72C (src/global/936B0.c): stage 5-6: frame 0x60 + s0-s2 saved set equal, only regalloc/stack-slot diffs (fdiff score 11369->2380, ~120 diff lines). K&R def (u8 arg2 volatile // FAKE) needs the file's prototype changed to 'void func_8068F72C();'. Open: target keeps actor ptr in s0, temp_v0 (s16 ret of func_806CC10C) enregistered in s0, arg3 reloaded by lbu each use (mine caches arg3 in s0); stack slot map for sp54/sp40/sp3C/sp38 offset +-4; f2/f12 FP numbering. Tried: arg2/arg3 volatile/&arg3, decl-order hill climb, deadsweep by hand (-155 only, not kept).
typedef struct L6919E02State {
    s16 unk0;
    s16 unk2;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    u8 pad14[0x27 - 0x14];
    u8 unk27;
    u8 unk28;
    u8 pad29[0x34 - 0x29];
    u8 unk34;
    u8 unk35;
} L6919E02State;

typedef struct L6919E02Step {
    u8 pad0[4];
    u8 unk4;
} L6919E02Step;

typedef struct L6919E02Player {
    u8 pad0[4];
    Actor *actor;
    u8 pad8[0x2F0 - 8];
} L6919E02Player;

typedef struct L6919E02Actor {
    u8 pad0[0x58];
    s32 unk58;
    u8 pad5C[4];
    u32 unk60;
    u8 pad64[6];
    u16 unk6A;
    u16 unk6C;
    u8 pad6E[0x80 - 0x6E];
    f32 unk80;
    u8 pad84[0xAC - 0x84];
    f32 unkAC;
    u8 padB0[0xB8 - 0xB0];
    f32 unkB8;
    f32 unkBC;
    f32 unkC0;
    f32 unkC4;
    f32 unkC8;
    u8 padCC[0xDC - 0xCC];
    s16 unkDC;
    s16 unkDE;
    u8 padE0[4];
    s16 unkE4;
    s16 unkE6;
    s16 unkE8;
    u8 padEA[4];
    s16 unkEE;
    u8 padF0[8];
    s16 unkF8;
    u8 padFA[0x144 - 0xFA];
    u8 unk144;
    u8 pad145[0x154 - 0x145];
    u8 unk154;
    u8 unk155;
} L6919E02Actor;

#define G_L6919E02 ((L6919E02Actor *)D_807FBB40)

extern Actor *D_807FBB40;
extern s16 D_8075033C;
extern u32 D_807FBB64;
extern struct PlayerTrackEntry *D_807FC924;
f32 func_80611BB4(f32, f32);
f32 func_80612790(s16);
f32 func_80612794(s16);
s32 func_806CC10C(s16, s16);
s16 func_806CC190(s16, s16, f32);
void actorStepPhysics(Actor *, s16, s16);
void actorApplyVelocity(Actor *);
void func_80665564(Actor *, f32);
void func_8002F490(void *);

#define S ((L6919E02State *)arg0)
void func_8068F72C(arg0, arg1, arg2, arg3)
void *arg0;
s32 arg1;
volatile u8 arg2; // FAKE: keeps arg2 re-loaded from its home (lbu) instead of cached in a register
u8 arg3;
{
    f32 fa0;
    s32 sp58;
    f32 sp54;
    f32 sp50;
    f32 fv0;
    s16 ang[2];
    u8 fl[4];
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    s16 temp_v0;
    s16 sp34;
    s16 var_a0;

    var_a0 = (s32)((L6919E02Player *)D_807FC924)[S->unk28].actor;
    sp58 = ((L6919E02Actor *)var_a0)->unk58;
    ang[1] = 0;
    ang[0] = 0;
    fl[3] = G_L6919E02->unk80 <= G_L6919E02->unkAC + 1.0f;
    fl[2] = G_L6919E02->unk6A & 1;
    if (!(G_L6919E02->unk60 & 0x10)) {
        G_L6919E02->unk60 |= 0x10400;
        G_L6919E02->unk154 = 0;
        G_L6919E02->unk155 = 0;
        G_L6919E02->unkB8 = 0.0f;
        S->unk34 = 0;
        S->unk35 = 0;
        if (S->unk27 == 0) {
            G_L6919E02->unk144 = 0x3C;
            G_L6919E02->unkC4 = -20.0f;
        } else {
            G_L6919E02->unk144 |= 0x18;
            G_L6919E02->unkC4 = -30.0f;
        }
        G_L6919E02->unkC8 = -900.0f;
        G_L6919E02->unkF8 = 0x12C;
    }
    sp40 = func_80612794(G_L6919E02->unkEE) * G_L6919E02->unkB8;
    sp3C = func_80612790(G_L6919E02->unkEE) * G_L6919E02->unkB8;
    if (fl[3] != 0) {
        sp38 = S->unk4 * 50.0f;
        if (sp58 == 2) {
            fa0 = 5000.0f;
        } else {
            fa0 = 10000.0f;
        }
        sp54 = 1.0f / fa0 * (G_L6919E02->unkB8 * G_L6919E02->unkB8) + S->unk8;
        if (S->unk4 != 0.0f) {
            sp54 = sp54 + 30.0f;
        } else {
            sp54 = sp54 + 3.0f;
        }
    } else {
        fv0 = 2.0f;
        if (fl[2] != 0) {
            sp38 = S->unk4 * 4.0f;
            sp54 = S->unk8 + G_L6919E02->unkB8 * G_L6919E02->unkB8 * 0.00002f + fv0;
        } else {
            sp38 = S->unk4 * fv0;
            sp54 = S->unk8 + G_L6919E02->unkB8 * G_L6919E02->unkB8 * 0.00002f + fv0;
        }
    }
    sp40 += func_80612794(S->unk0) * sp38;
    sp3C += func_80612790(S->unk0) * sp38;
    G_L6919E02->unkB8 = sqrtf(sp40 * sp40 + sp3C * sp3C);
    G_L6919E02->unkEE = (s16)(s32)(func_80611BB4(sp40, sp3C) * 4096.0 / 6.2831854820251465);
    if (fl[2] != 0) {
        sp34 = 0x400 - G_L6919E02->unkDE;
        temp_v0 = func_806CC10C(G_L6919E02->unkDC, S->unk0);
        fv0 = (f32)sp34;
        ang[1] = (s16)(s32)(func_80612790(temp_v0) * fv0);
        ang[0] = (s16)(s32)(func_80612794(temp_v0) * fv0);
    } else if (arg3 == 0) {
        G_L6919E02->unkE8 = func_806CC190(G_L6919E02->unkE8, 0, 4.0f);
        G_L6919E02->unkE4 = func_806CC190(G_L6919E02->unkE4, 0, 5.0f);
    }
    sp50 = S->unk10 * S->unkC;
    if (arg3 != 0) {
        ang[0] = (s32)((f32)ang[0] + sp50 * 200.0f) & 0xFFF;
        if (fl[3] != 0 || fl[2] != 0) {
            var_a0 = G_L6919E02->unkE8;
            ang[1] = (s32)((f64)ang[1] + ((f64)(S->unk4 * -50.0f) + (f64)G_L6919E02->unkB8 * -0.5)) & 0xFFF;
        } else {
            var_a0 = G_L6919E02->unkE8;
            ang[1] = var_a0;
        }
        G_L6919E02->unkE8 = func_806CC190(var_a0, ang[1], 4.0f);
        G_L6919E02->unkE4 = func_806CC190(G_L6919E02->unkE4, ang[0], 5.0f);
    }
    G_L6919E02->unkB8 = G_L6919E02->unkB8 - sp54;
    fv0 = G_L6919E02->unkB8;
    if (fv0 < 0.0f) {
        G_L6919E02->unkB8 = 0.0f;
        fv0 = G_L6919E02->unkB8;
    }
    fv0 = fv0 - G_L6919E02->unkBC;
    if (fv0 < 0.0f) {
        fv0 = 0.0f;
    }
    var_a0 = -0x28;
    if (sp58 == 2) {
        var_a0 = -0x1E;
    }
    S->unk0 = (s32)((f64)S->unk0 + (f64)(sp50 * (f32)var_a0) * (1.0 + (f64)fv0 * 0.05));
    S->unk0 = S->unk0 & 0xFFF;
    if (arg2 != 0) {
        fa0 = G_L6919E02->unk80;
        fv0 = G_L6919E02->unkAC;
        if (fa0 < fv0) {
            G_L6919E02->unkC0 = G_L6919E02->unkC0 + ((fv0 - fa0) * 3.0f + 15.0f);
            fv0 = G_L6919E02->unkC0;
            if (fv0 > 0.0f) {
                fa0 = fv0;
            } else {
                fa0 = -fv0;
            }
            if (fa0 > 20.0f) {
                G_L6919E02->unkC0 = fv0 - fv0 / 12.0f;
            }
        }
    }
    G_L6919E02->unkC0 = G_L6919E02->unkC0 + G_L6919E02->unkC4;
    if (((L6919E02Step *)arg1)->unk4 != 0) {
        ((L6919E02Step *)arg1)->unk4 = 0;
        if (fl[3] != 0) {
            if (sp58 == 2) {
                G_L6919E02->unkC0 = 200.0f;
            } else {
                G_L6919E02->unkC0 = (f32)D_8075033C;
            }
        } else if (fl[2] != 0) {
            G_L6919E02->unkC0 = G_L6919E02->unkC0 + 200.0f;
        }
    }
    fv0 = G_L6919E02->unkC8;
    if (G_L6919E02->unkC0 < fv0) {
        G_L6919E02->unkC0 = fv0;
    }
    actorStepPhysics(D_807FBB40, G_L6919E02->unkE6, S->unk0);
    actorApplyVelocity(D_807FBB40);
    func_80665564(D_807FBB40, 0.0f);
    if (arg2 == 0) {
        if (G_L6919E02->unk80 < G_L6919E02->unkAC) {
            G_L6919E02->unk80 = G_L6919E02->unkAC;
            G_L6919E02->unkC0 = G_L6919E02->unkC4;
        }
    }
    if (D_807FBB64 & 0x2000) {
        func_8002F490(arg0);
    }
    if (fl[2] != 0 && !(G_L6919E02->unk6C & 1)) {
        G_L6919E02->unkC0 = -10.0f;
    }
    G_L6919E02->unkE6 = (S->unk0 + S->unk2) & 0xFFF;
}
#undef S

// func_80698120 (src/global/9CE20.c): stage 5-6: frame 0x80, saved set {s0,ra} and data in t1 spilled 0x7c now MATCH (needed: K&R u8 arg0 formal, two FAKE 'if (D_807FBB40 == 0) {}' after data=, deadsweep ifs data->unk8/unk4/unk14, int-typed callee protos u8/s16, sinApprox/randomNonNegative names, case order 0x44/0x74 before 0x21/0x45, (f64)unkC < 1.5707964f). 947 vs 947 insns, ~150 diff hunks left: (1) init block 0.0f stores: target has 4 separate 'mtc1 zero,fN' (const not a uopt candidate there) ours shares $f0; classes tested: only literal-0.0f vs folded forms, max 2 distinct; (2) data->unk4 is an FP candidate (preloaded $f14/$f2) in the sfx-compare regions where target reloads lwc1 4(t1) lazily and keeps the compare constant in $f2; (3) li 80 hoisted out of the unk254 loop (target keeps it inside; named s16 *ptr local gave v0 for the pointer but moved i to t0); (4) node[] store/lwc1 interleave order (sh zero,6 vs lwc1 16(t1))
typedef struct OlK_Node {
    s8 unk0;
    u8 unk1;
    s16 unk2;
    s16 unk4;
    s16 unk6;
} OlK_Node;

typedef struct OlK_Data {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ u8 unk14;
    /* 0x15 */ u8 unk15;
    /* 0x16 */ u8 unk16;
    /* 0x17 */ u8 unk17;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ u8 unk28;
} OlK_Data;

typedef struct OlK_PlayerState {
    /* 0x130 */ u8 pad0[0x130];
    /* 0x130 */ void *unk130;
    /* 0x134 */ u8 pad134[4];
    /* 0x138 */ f32 unk138;
    /* 0x13C */ u8 pad13C[0x10];
    /* 0x14C */ f32 unk14C;
    /* 0x150 */ f32 unk150;
    /* 0x154 */ s16 unk154;
    /* 0x156 */ u8 pad156[0x9A];
    /* 0x1F0 */ u32 unk1F0;
} OlK_PlayerState;

typedef struct OlK_PlayerRoot {
    /* 0x000 */ u8 pad0[0x174];
    /* 0x174 */ OlK_PlayerState *unk174;
} OlK_PlayerRoot;

typedef struct OlK_Main {
    /* 0x0 */ u8 pad0[4];
    /* 0x4 */ OlK_PlayerRoot *unk4;
} OlK_Main;

typedef struct OlK_Actor2 {
    /* 0x06A */ u8 pad0[0x6A];
    /* 0x06A */ u16 unk6A;
    /* 0x06C */ u8 pad6C[0x7A];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 padE8[0x6C];
    /* 0x154 */ u8 unk154;
} OlK_Actor2;

typedef struct OlK_Sub4 {
    /* 0x1C */ u8 pad0[0x1C];
    /* 0x1C */ OlK_Node *unk1C;
} OlK_Sub4;

extern Actor *D_807FBB40;
extern Actor *D_807FBB4C;
extern void *D_807FC924;
extern s32 D_807FBB64;
extern u32 D_80744478;
extern s16 D_8075037C;
extern s16 D_80750380;
extern ActorGlobalState D_807FBB70;

void sfxPlayFromActorWithAltitudeCheck(Actor *, s16, u8, s16, u8);
void actorUpdateModelMatrix(Actor *, s32);
void *heapAlloc(s32);
s32 randomNonNegative(void);
f32 sinApprox(f32);
s32 mathAngleDistance(s16, s16);
s32 func_807142D8(void);
s32 flagGet(s32, s32);
void proxPathAdd(Actor *, u8, u8, u8, u8, f32, f32, f32, f32, f32, f32, u8, f32, f32, u8);
void proxPathSetSegment(Actor *, u8, u8, u8, u8, f32, f32, f32, u8, s16, s16, s16, s16);

void func_80698120(arg0)
u8 arg0;
{
    OlK_Data *data;
    OlK_Node *node;
    s16 i;
    s16 padS16;
    f32 padA;
    OlK_PlayerState *player;
    f32 padC;
    f32 padE;
    u8 dir;
    f32 limit = 15.0f;

    data = D_807FBB40->unk174;
    if (D_807FBB40 == 0) {} // FAKE: keeps D_807FBB40 above data in uopt priority
    if (D_807FBB40 == 0) {} // FAKE: keeps D_807FBB40 above data in uopt priority
    player = ((OlK_Main *)D_807FC924)->unk4->unk174;
    if (!(D_807FBB40->unk60 & 0x10)) {
        data->unk0 = 0.0f;
        data->unk10 = 0.0f;
        data->unk4 = 0.10471976f;
        data->unk8 = 0.75f;
        if (data->unk8 == 0) {} // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        data->unkC = 0.0f;
        data->unk20 = 0.0f;
        data->unk1C = D_807FBB40->unk80;
        data->unk24 = (f32)((f64)(s32)((randomNonNegative() >> 15) % 100) / 1000.0 + 0.1);
        data->unk18 = 0.0f;
        ((OlK_Sub4 *)D_807FBB40->unk4)->unk1C = heapAlloc(0x80);
        proxPathAdd(D_807FBB40, 0, 0, 0, arg0, 0.0f, (f32)((f64)arg0 * 0.333333), 0.15f, 100.0f, 20.0f, 8.0f, 0, 0.0f, 0.0f, 0);
        for (i = 1; i <= arg0; i++) {
            proxPathSetSegment(D_807FBB40, 0, i - 1, i, i + 1, 0.333333f, 0.0f, 0.0f, 0, 0, 0, 0, 0);
        }
        ((u8 *)D_807FBB40)[0x130] = 0x3C;
        ((u8 *)D_807FBB40)[0x131] = 0xC8;
        data->unk14 = 0;
        data->unk15 = 0;
        data->unk28 = flagGet(0x183, 0) != 0 || (D_807FBB64 & 0x10000000) != 0 || func_807142D8() != 0;
    }
    if (D_807FBB4C->unk154 == 0x63 || data->unk28 == 0 ||
        (*(s32 *)D_807FBB40->unk124 == 1 && !(player->unk1F0 & 0x40))) {
        D_807FBB40->unk60 &= 0xFBFFFFFB;
    } else {
        D_807FBB40->unk60 |= 0x04000004;
    }
    for (i = 0; i < D_807FBB70.unk254; i++) {
        if (data->unk4 == 0) {} // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        if (*D_807FBB70.unk278[i] == 0) {
            data->unk16 = 0x50;
        }
    }
    if (data->unk16 != 0) {
        D_807FBB40->unk80 -= 1.0;
        data->unk16--;
        data->unk1C -= 1.0;
    }
    node = ((OlK_Sub4 *)D_807FBB40->unk4)->unk1C;
    if (data->unk0 > 2.0f) {
        if (data->unkC < 3.926991f && data->unkC + data->unk4 >= 3.926991f) {
            if (D_807FBB40->unk58 == 0x74) {
                sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x257, (f64)data->unk0 * 100.0 / limit, 0x7F, 5);
            } else {
                sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x1C, (f64)data->unk0 * 100.0 / limit, 0x7F, 5);
            }
        }
        if (data->unk14 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    }
    if (data->unkC < 0.7853982f && data->unkC + data->unk4 >= 0.7853982f) {
        if (D_807FBB40->unk58 == 0x74) {
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x258, (f64)data->unk0 * 25.0 / limit, 0x7F, 0x14);
        } else {
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x1D, (f64)data->unk0 * 25.0 / limit, 0x7F, 0x14);
        }
    }
    if (D_807FBB40->unk58 != 0x74 && data->unk0 > 10.0f) {
        if (data->unkC < 2.3561945f && data->unkC + data->unk4 >= 2.3561945f) {
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x1E, 0xFF, 0x7F, 0x14);
        }
        if (data->unkC < 5.497787f && data->unkC + data->unk4 >= 5.497787f) {
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x1E, 0xFF, 0x7F, 0x14);
        }
    }
    switch (D_807FBB40->unk58) {
    case 0x44:
    case 0x74:
        dir = 1;
        break;
    case 0x21:
    case 0x45:
        dir = 2;
        break;
    }
    data->unkC = data->unkC + data->unk4 * D_80744478 * 0.5;
    data->unk10 = sinApprox(data->unkC) * data->unk0;
    for (i = 0; i < 0xE; i++) {
        node[i].unk0 = -0x80;
        node[i].unk1 = i + dir;
        node[i].unk4 = 0;
        node[i].unk6 = 0;
        node[i].unk2 = (s16)(s32)((f64)data->unk10 / 360.0 * 65535.0);
        data->unk10 = data->unk10 * data->unk8;
    }
    if (D_807FBB40->unk58 == 0x45 || D_807FBB40->unk58 == 0x21) {
        node[i].unk0 = -0x80;
        node[i].unk1 = 1;
        node[i].unk2 = 0;
        node[i].unk6 = 0;
        node[i].unk4 = (s16)(s32)((f64)data->unk18 / 360.0 * 65535.0);
        i++;
        data->unk18 += 20.0f;
        if (data->unk18 > 360.0f) {
            data->unk18 -= 360.0f;
        }
    }
    node[i].unk0 = 0;
    if (D_807FBB4C->unk154 == 0x58) {
        data->unk15 = 5;
    } else if (data->unk15 != 0) {
        data->unk15--;
    }
    if ((D_807FBB4C->unk6A & 0x40) && data->unk14 == 0 && D_807FBB40 == player->unk130) {
        data->unk0 = 15.0f;
        if (mathAngleDistance(D_807FBB4C->unkE6, D_807FBB40->unkE6) < 0x400) {
            data->unkC = 3.1415927f;
        } else {
            data->unkC = 0.0f;
        }
    }
    if (data->unkC >= 6.2831855f) {
        data->unkC -= 6.2831855f;
    }
    if (data->unkC < 0.0f) {
        data->unkC += 6.2831855f;
    }
    if ((D_807FBB4C->unk6A & 0x40) && D_807FBB40 == player->unk130) {
        data->unk14 = 1;
        data->unk0 += 0.2;
        if (data->unk0 > 15.0f) {
            data->unk0 = 15.0f;
        }
    } else {
        data->unk14 = 0;
        data->unk0 = data->unk0 + (0.0 - data->unk0) * 0.03;
        if (data->unk0 < 2.0) {
            data->unk0 = 0.0f;
        }
    }
    if ((D_807FBB4C->unk6A & 0x40) && D_807FBB40 == player->unk130) {
        if (player->unk138 < 1.5 && (((f64)data->unkC > 4.0 && (f64)data->unkC < 4.712389f) ||
                                     ((f64)data->unkC < 1.5707964f && (f64)data->unkC > 0.9))) {
            player->unk14C = (f32)D_8075037C * (data->unk0 / 15.0f);
            player->unk150 = (f32)D_80750380 * (data->unk0 / 15.0f);
        } else {
            player->unk14C = 200.0f;
            player->unk150 = 200.0f;
        }
        player->unk154 = D_807FBB40->unkE6 & 0xFFF;
        if ((f64)data->unkC < 1.5707964f || data->unkC > 4.712389) {
            player->unk154 = (player->unk154 + 0x800) & 0xFFF;
        }
    }
    if (D_807FBB40->unk58 == 0x21 || D_807FBB40->unk58 == 0x45) {
        D_807FBB40->unk80 = sinApprox(data->unk20) * 5.0 + data->unk1C;
        data->unk20 += data->unk24;
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

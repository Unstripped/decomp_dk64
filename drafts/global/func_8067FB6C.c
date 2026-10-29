// func_8067FB6C (src/global/80150.c): Stage 5 near-miss (score 1030, shape=0): all 802 insns match opcodes/branches/stack/frame, remaining diff is pure temporary register coloring (-). Tried deadsweep, permuter, prototype updates.
typedef struct KaL5_Actor124 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} KaL5_Actor124;

typedef struct KaL5_Actor174_104 {
    u8 pad0[0x104];
    s32 unk104;
} KaL5_Actor174_104;

typedef struct KaL5_SubFB6C {
    Actor *unk0;
    u32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    s16 unk18;
    u8 unk1A;
    u8 unk1B;
    u8 unk1C;
} KaL5_SubFB6C;

typedef struct KaL5_Actor {
    u8 pad0[0xEE];
    s16 unkEE;
} KaL5_Actor;

extern Actor *D_807FBB48;
extern s32 D_807FBB68;
extern s32 D_8071FBC8;
extern u16 D_807FD63C;
void func_806FF01C();

f32 func_80612790(s16);
f32 func_80612794(s16);
f32 sinApprox(f32);
void func_80613194(Actor *, s16);
void func_80613214(Actor *);
void camSetFixedView(s32, f32, f32, f32, f32, f32, f32, u8);
void camSetTargetScaled(s32, Actor *, u8, s16, s16, s16, s16, s16, s16, s16, f32);
s32 camIsCutsceneActive(void);
s32 collisionCheckGroundAtPoint(f32, f32, f32 *);
void actorAppendCallback(Actor *, s32, s32, u8, s32, void *);
void actorQueueDelayedCallback(Actor *, Actor *, s32, s32, s32, s32, s32);
void func_8067A70C(Actor *, Actor *, f32, f32, f32, u8, u8);
void func_8067AAB8(s32, Actor *, s16, f32, s16);
void renderCallbacksRegister(void *, void *, s32);
void func_80714C08(void *, f32, Actor *, s32, s32);

void func_8067FB6C(void) {
    f64 pad;
    f32 sp5C;
    f32 sp58;
    s32 sp54;
    s32 pad2;
    s16 sp4E;
    KaL5_SubFB6C *sub;
    s32 var_v0;
    f32 var_fa1;
    s16 i;

    sub = D_807FBB40->unk174;
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk12A = 0x320;
        D_807FBB40->unk12C[4] = 0x14;
        D_807FBB40->unk12C[5] = 0x14;
        sub->unkC = 90.0f;
        sub->unk8 = D_807FBB40->unk80;
        sub->unk14 = (f64)((KaL5_Actor124 *)D_807FBB40->unk124)->unk0 / 200.0;
        sub->unk10 = ((KaL5_Actor124 *)D_807FBB40->unk124)->unk4;
        sub->unk4 = ((f64)sub->unk14 != 0.0) ? (4.71238899230957031 / (f64)sub->unk14) : (f64)0;
        sub->unk1C = ((KaL5_Actor124 *)D_807FBB40->unk124)->unk8;
        sub->unk18 = D_807FBB40->unkE6;
        D_807FBB40->unkA4 = 99999.0f;
        collisionCheckGroundAtPoint(D_807FBB40->unk7C, D_807FBB40->unk84, &D_807FBB40->unkA4);
        if (sub->unk1C == 3) {
            D_807FBB40->unk132 = 2;
        } else {
            D_807FBB40->unk132 = 1;
        }
        if (((KaL5_Actor124 *)D_807FBB40->unk124)->unkC == 1) {
            D_807FBB40->unk154 = 0x14;
            D_807FBB40->unk144 = 1;
            D_807FBB40->unk60 &= ~0x8000;
            D_807FBB40->unk128 = 0;
        }
    }
    if (D_807FBB70.unk200 == 4) {
        sub->unk0 = (Actor *)D_807FBB70.unk1FC;
        D_807FBB40->unk154 = 1;
        D_807FBB40->unk144 = 1;
        D_807FBB40->unk60 |= 0x400;
        sub->unk1B = 2;
        if (sub->unk1C == 3) {
            sub->unk1A = 1;
        } else {
            sub->unk1A = 2;
        }
    }
    switch (D_807FBB40->unk154) {
    case 0:
        tagBarrelDespawnOnKongDeselect();
        break;
    case 1:
        D_807FBB40->unk60 |= 0x8000;
        switch (sub->unk1C) {
        case 0:
        case 4:
            if (sub->unk1C == 0) {
                D_807FBB40->unk80 = sinApprox((f32)sub->unk4 * sub->unk14) * sub->unk10 + (sub->unk8 + sub->unk10);
            } else {
                D_807FBB40->unk80 = sinApprox((f32)sub->unk4 * sub->unk14) * sub->unk10 + sub->unk8;
            }
            func_8067A70C(D_807FBB40, sub->unk0, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 2, 1);
            sp4E = D_807FBB40->unkE6;
            sub->unk4++;
            break;
        case 2:
            D_807FBB40->unkE6 = (D_807FBB40->unkE6 + (s32)(sub->unk14 * 200.0f)) & 0xFFF;
            sp4E = (D_807FBB40->unkE6 + (s32)(sub->unk14 * 200.0f)) & 0xFFF;
            break;
        case 1:
            D_807FBB40->unkE6 = ((s32)(sinApprox((f32)sub->unk4 * sub->unk14) * ((sub->unk10 * 4096.0f) / 360.0f)) + sub->unk18) & 0xFFF;
            sub->unk4++;
            sp4E = ((s32)(sinApprox((f32)sub->unk4 * sub->unk14) * ((sub->unk10 * 4096.0f) / 360.0f)) + sub->unk18) & 0xFFF;
            break;
        case 3:
            sp4E = D_807FBB40->unkE6;
            break;
        }
        sp5C = func_80612794(sp4E) * 50.0f;
        sp58 = func_80612790(sp4E) * 50.0f;
        if (sub->unk1B == 1) {
            func_80613194(D_807FBB40, 0x75);
        }
        if (sub->unk1B) {
            sub->unk1B--;
        }
        if (sub->unk1A) {
            sub->unk1A--;
        }
        if (((D_807FD63C & 0xE000) || sub->unk1C == 3) && sub->unk1A == 0) {
            KaL5_Actor174_104 *temp_s0_2;
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x18, 0xFF, 0x7F, 1);
            temp_s0_2 = sub->unk0->unk174;
            func_80613214(D_807FBB40);
            if (!(D_807FBB68 & 2)) {
                if (sub->unk1C == 3) {
                    var_v0 = 0x64;
                } else {
                    var_v0 = 0x32;
                }
                camSetTargetScaled(temp_s0_2->unk104, sub->unk0, 4, 0x800, var_v0, 0, 0, 0x1E, 0x14, 0x50, 0.3f);
            }
            D_807FBB48->unkE6 = D_807FBB40->unkE6;
            ((KaL5_Actor *)D_807FBB48)->unkEE = D_807FBB40->unkE6;
            actorAppendCallback(sub->unk0, (s32)D_807FBB40, 0x40, 1, 0, 0);
            if (D_807FBB68 & 2) {
                var_v0 = 0x1F4;
            } else {
                var_v0 = 0x2BC;
            }
            func_8067AAB8((s32)D_807FBB40, sub->unk0, D_807FBB40->unkE6, 0.0f, var_v0);
            actorQueueDelayedCallback(D_807FBB40, D_807FBB40, 0x800, 2, 0, 0, 0xA);
            func_80714998(2);
            func_80714C08(&D_8071FBC8, 1.6f, D_807FBB40, 1, 2);
            D_807FBB40->unk60 &= ~0x400;
            D_807FBB40->unk154 = 2;
            D_807FBB40->unk155[0] = 0x1E;
        } else {
            sp54 = ((KaL5_Actor174_104 *)sub->unk0->unk174)->unk104;
            switch (sub->unk1C) {
            case 0:
                var_fa1 = sinApprox((f32)sub->unk4 * sub->unk14) * sub->unk10 + (sub->unk8 + sub->unk10);
                break;
            case 4:
                var_fa1 = sinApprox((f32)sub->unk4 * sub->unk14) * sub->unk10 + sub->unk8;
                break;
            default:
                var_fa1 = D_807FBB40->unk80;
                break;
            }
            if (D_807FBB68 & 2) {
                var_v0 = 0;
            } else {
                var_v0 = 1;
            }
            camSetFixedView(
                sp54,
                (f64)D_807FBB40->unk7C - (f64)sp5C / 5.0,
                var_fa1,
                (f64)D_807FBB40->unk84 - (f64)sp58 / 5.0,
                D_807FBB40->unk7C + sp5C,
                var_fa1,
                D_807FBB40->unk84 + sp58,
                var_v0
            );
            if (camIsCutsceneActive() == 0) {
                renderCallbacksRegister(func_806FF01C, D_807FBB4C, 3);
            }
        }
        break;
    case 2:
        tagBarrelDespawnOnKongDeselect();
        D_807FBB40->unk155[0]--;
        if (D_807FBB40->unk155[0] == 0) {
            D_807FBB40->unk80 = sub->unk8;
            sub->unk4 = ((f64)sub->unk14 != 0.0) ? (4.71238899230957031 / (f64)sub->unk14) : (f64)0;
            D_807FBB40->unkE6 = sub->unk18;
            D_807FBB40->unk154 = 0;
        }
        break;
    case 20:
        for (i = 0; i < D_807FBB70.unk254; i++) {
            if (D_807FBB70.unk258[i] == 1 && *D_807FBB70.unk278[i] == 0) {
                D_807FBB40->unk144 = 2;
                D_807FBB40->unk154 = 0x15;
            }
        }
        break;
    case 21:
        D_807FBB40->unk128 += 10;
        if (D_807FBB40->unk128 >= 0xF1) {
            D_807FBB40->unk60 |= 0x8000;
            D_807FBB40->unk154 = 0;
        }
        break;
    }
    if (D_8076A0A8 == 0xCB) {
        D_807FBB40->unk60 |= 0x400;
    }
    guRotateF((float (*)[4])&D_807FBB40->unk08[4], sub->unkC, 1.0f, 0, 0.0f);
    actorUpdateModelMatrix(D_807FBB40, 1);
}

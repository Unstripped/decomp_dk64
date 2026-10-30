// func_80033AF0 (src/boss/F0D0.c): stage 5: exact diff = 4 lines (+rodata offsets): 0x20 c5 raw v-1 lands in v0, target v1 (load v0, raw v1, andi t4). Spot 2 fixed via 'unk18 = tbl[..]; unk19 = unk18;', spot 1 via 'D_80035BD8[st->unk18 = --v]'; t-ring now matches
typedef struct BossF_Model {
    struct BossF_ModelSub *unk0;
    u8 padF4[0x38 - 4];
    f32 unk38;
    u8 pad3C[0x64 - 0x3C];
    u16 unk64;
} BossF_Model;

struct BossF_ModelSub {
    u8 pad0[4];
    f32 unk4;
};

typedef struct BossF_State {
    u8 pad0[8];
    s16 unk8;
    u8 padA[0x14 - 0xA];
    u8 unk14;
    u8 unk15;
    u8 unk16;
    u8 unk17;
    u8 unk18;
    u8 unk19;
} BossF_State;

typedef struct BossF_Sub {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    u8 unk4;
    u8 unk5;
    u8 unk6;
} BossF_Sub;

typedef struct BossF_Actor {
    u8 pad0[4];
    BossF_Model *unk4;
    u8 pad8[0x60 - 0x8];
    s32 unk60;
    u8 pad64[0x6A - 0x64];
    u16 unk6A;
    u8 pad6C[2];
    s16 unk6E;
    u8 pad70[0x7C - 0x70];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xC0 - 0x88];
    f32 unkC0;
    f32 unkC4;
    f32 unkC8;
    u8 unkCC;
    u8 padCD[0x110 - 0xCD];
    u8 unk110;
    u8 pad111[0x128 - 0x111];
    s16 unk128;
    u8 pad12A[0x144 - 0x12A];
    u8 unk144;
    u8 pad145;
    s16 unk146;
    u8 pad148[0x154 - 0x148];
    u8 unk154;
    u8 unk155;
    u8 pad156[0x178 - 0x156];
    BossF_State *unk178;
    BossF_Sub *unk17C;
} BossF_Actor;

typedef struct BossF_Extra {
    u8 pad0[0x1A];
    u16 unk1A;
    u8 pad1C[0x2C - 0x1C];
    s16 unk2C;
    u8 pad2E[2];
    f32 unk30;
} BossF_Extra;

typedef struct BossF_Pt {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
} BossF_Pt;

typedef struct BossF_Pts {
    u8 pad0[0x14];
    BossF_Pt *unk14;
} BossF_Pts;

#define BF ((BossF_Actor *)D_807FBB40)
#define BP ((BossF_Actor *)D_807FBB4C)
#define BX ((BossF_Extra *)D_807FDC90)
#define BPTS ((BossF_Pts *)D_807FDCA0)

extern u8 *D_80035B84[];
extern u8 D_80035B98[];
extern u8 D_80035BD8[];
extern u8 D_80035BEC[];
extern u8 D_80036DD0[];
extern f32 D_80036C40[];
extern void *D_807FDC90;
extern u8 D_807FBB85;
extern u8 D_807FBDC4;
extern s32 D_8076A064;
extern s16 D_807502DC;
extern f32 D_807502F0;
extern u8 D_8071EDEC[];
extern u8 D_8071FC58[];
extern u8 D_80720054[];
extern u8 D_80720BE8[];

void lightSetRadius(s32);
void lightAdd(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32);
s32 flagGet(s32, s32);
s32 camStartPath(void *, s32, s32);
void behaviourFrameBegin(void);
void func_8067ACB4(void *);
void actorSetUniformScale(void *, f32);
void actorUpdateModelMatrix(void *, s32);
void actorApplyGravity(void);
void func_8072A450(void);
void func_80614D00(void *, f32, f32);
void actorUpdateFloorContactAndTilt(void *, f32);
void sfxPlayAtPositionPooled(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);
s32 currentActorTestClearFlag(void);
void currentActorClearFlag(void);
void volumeTriggerSetEnabled(s32, s32);
s32 func_80724A20(void);
u8 bossPickWaypointStep(BossE_F0D0_Sub14 *, u8 *);
void func_8003340C(u8 *);
void func_800336C0(void);
void bossInterpolateWaypoints(u8 *, f32);
void bossSpawnObjectAtWaypoint(u8 *);
void func_8072E1A4(s32, void *);
void actorApplyVelocityCustom(void *, f32, f32);
s32 func_800339D8(BossE_F0D0_Sub14 *, u8 *);
void func_80033A80(s8);
void effectSpawnBoneDebris(s32, s32);
void effectSpawnBoneDebrisScaled(s32, s16, s32);
void effectSpawnJointBeam(s32, s32, s32, s32);
void effectSpawnRandomBoneDebris(s32, s32);
void actorSpawnAttachment(void *, f32);
void actorAppendActiveCallback8(void);
s32 camIsCutsceneActive(void);
void camSetSecondTarget(void *, s32, s32);
void actorGetNodePos(void *, s32, f32 *, f32 *, f32 *);
void effectSpawnScatterRandom(void *, s32, f32, s32, s32, s32, s32, s32, s32);
void bossSpawnParticleRing(s32, s16, s16, s16, s32, s32);
void func_80714C08(void *, f32, void *, s32, s32);
void sfxPlayFromActorWithAltitudeCheck(void *, s32, s32, s32, s32);
void sfxPlayActorSound(void *, s32, s32, s32, s32, s32, f32, s32);
void sfxStopSlotSound(void *, u8);
void bossScriptStep(u8 *, s32, f32);

void func_80033AF0(void) {
    BossF_State *st;
    BossF_Sub *sub;
    u8 *tbl;
    struct { u8 pad0[3]; u8 col[3]; u8 pad1; u8 f7F; u8 pad2[3]; u8 f83; } L;
    f32 sx;
    f32 sy;
    u8 idx;
    u8 v;
    s16 i;
    f32 sp68;
    f32 sp64;
    f32 sp60;

#define sp83 L.f83
#define sp7F L.f7F
#define col L.col
    st = BF->unk178;
    sub = BF->unk17C;
    tbl = D_80035B84[st->unk14];
    if (BP->unk80 < BF->unk80 - 10.0f) {
        sp83 = 1;
    } else {
        sp83 = 0;
    }
    sp7F = 0;
    behaviourFrameBegin();
    func_8067ACB4(D_807FBB40);
    if (!(BF->unk60 & 0x10)) {
        BF->unkCC = 1;
        BF->unk144 = 0x24;
        if (flagGet(0x6A, 2) != 0) {
            actorScriptStart(D_807FBB40, 0x226);
            camStartPath(D_807FBB40, 0x14, 1);
            sub->unk0 = 9;
            sub->unk2 = 5;
            BF->unk154 = 0x20;
            BF->unk155 = 0;
            BF->unk155 = 0xB;
            BF->unk110 = 0;
        } else {
            BF->unk146 = 0;
            BX->unk30 = BF->unk4->unk38;
            actorSetUniformScale(D_807FBB40, BX->unk30 * 0.333);
            BF->unk154 = 0x1E;
            BF->unk155 = 0;
            BF->unk80 += 650.0f;
            BF->unk60 &= 0xFFFF7FFF;
            sub->unk0 = 0xF;
        }
        BF->unk6A &= 0xFFFE;
        BF->unkC4 = D_807502F0;
        BF->unkC8 = D_807502DC;
    }
    if (st->unk14 < 2) {
        if (sub->unk4 != 0) {
            idx = sub->unk4 - 0x10;
            col[2] = sub->unk5 - 0x10;
            if (D_80035BEC[idx] != 0) {
                col[1] = 0x46;
            } else {
                col[1] = 0xFF;
            }
            if (D_80035BEC[idx] != 0) {
                col[0] = 0xA0;
            } else {
                col[0] = 0xFF;
            }
            if (idx != sub->unk3) {
                lightSetRadius(0x1388);
                lightAdd(BPTS->unk14[idx].unk0, BPTS->unk14[idx].unk2 - 0x32, BPTS->unk14[idx].unk4, 0.0f, 0.0f, 0.0f, 240.0f, 0, col[1], col[0], 0xFF);
            }
            if (sub->unk3 != col[2]) {
                lightSetRadius(0x1388);
                lightAdd(BPTS->unk14[col[2]].unk0, BPTS->unk14[col[2]].unk2 - 0x32, BPTS->unk14[col[2]].unk4, 0.0f, 0.0f, 0.0f, 240.0f, 0, col[1], col[0], 0xFF);
            }
        }
    }
    if ((BF->unk154 == 0x27 && st->unk14 == 4) || (D_807FBB85 != 0 && BF->unk154 != 0x37)) {
        if (BP->unk154 == 0x36) {
            BF->unk154 = 0x2B;
            BF->unk155 = 0;
        } else {
            actorScriptStart(D_807FBB40, 0x226);
            BF->unk154 = 0x37;
            BF->unk155 = 0;
        }
    }
    if (BF->unk154 == 0x23 && BF->unk155 == 1 && sp83 == 0 && sub->unk6 != 0) {
        BF->unk154 = 0x2B;
        BF->unk155 = 0;
    }
    switch (BF->unk154) {
    case 0x1E:
        for (i = 0; i < 0x10; i++) {
            if (*(u16 *)(D_80035B98 + ((BX->unk2C & 0x1F) << 1)) & (1 << i)) {
                D_80036DD0[i] = 0xFA;
            }
            if (D_80036DD0[i] != 0) {
                sx = D_80035BEC[i] != 0 ? 0.27 : 1.0;
                sy = D_80035BEC[i] != 0 ? 0.62 : 1.0;
                lightSetRadius(0x1388);
                lightAdd(BPTS->unk14[i].unk0, BPTS->unk14[i].unk2 - 0x28A, BPTS->unk14[i].unk4, 0, 0.0f, 0.0f, 240.0f, 0, (u32)((f32)(u32)D_80036DD0[i] * sx), (u32)((f32)(u32)D_80036DD0[i] * sy), D_80036DD0[i]);
                D_80036DD0[i] -= 0x19;
            }
        }
        if (!(D_8076A064 & 7)) {
            BX->unk2C++;
        }
        if (D_807FBDC4 != 0) {
            BF->unk154 = 0x1F;
            BF->unk155 = 0;
        }
        break;
    case 0x1F:
        i = (u8)(u32)(func_80612794((s16)(D_8076A064 * 0x7D)) * 100.0f + 155.0f);
        lightSetRadius(0x1388);
        lightAdd(BPTS->unk14[5].unk0, BPTS->unk14[5].unk2 - 0x28A, BPTS->unk14[5].unk4, 0.0f, 0.0f, 0.0f, 240.0f, 0, i, i, i);
        if (currentActorTestClearFlag() != 0) {
            sfxPlayAtPositionPooled(BF->unk7C, BF->unk80, BF->unk84, 0x19C, 0x64, 0x7F, 0, 0, 0.0f, 0);
            BF->unk154 = 0x20;
            BF->unk155 = 0;
        }
        break;
    case 0x20:
        func_8072A450();
        switch (BF->unk155) {
        case 0:
            effectSpawnBoneDebris(4, 1);
            sp7F = 1;
            actorApplyGravity();
            actorApplyVelocityCustom(D_807FBB40, 0.0f, BF->unkC0);
            actorUpdateFloorContactAndTilt(D_807FBB40, 0.0f);
            if (BF->unk110 == 1) {
                BF->unk155++;
            }
            break;
        case 1:
            if (currentActorTestClearFlag() != 0) {
                BF->unk155++;
            }
            break;
        case 2:
            actorScriptStart(D_807FBB40, 0x225);
            func_80614D90(D_807FBB40);
            st->unk18 = 2;
            sub->unk1 = D_80035BD8[st->unk18];
            sub->unk2 = 0xFF;
            BF->unk155++;
            BF->unk6A |= 1;
        case 3:
            func_80614D00(D_807FBB40, 1.0f, 0.0f);
            BF->unk155++;
        case 4:
            func_8067ACB4(D_807FBB40);
            actorUpdateFloorContactAndTilt(D_807FBB40, 0.0f);
            bossInterpolateWaypoints((u8 *)sub, 0.025f);
            if (BF->unk4->unk0->unk4 >= 40.0f) {
                BF->unk6A |= 1;
            } else {
                BF->unk6A = 0;
                effectSpawnBoneDebris(4, 1);
                sp7F = 1;
            }
            break;
        case 5:
            sub->unk0 = sub->unk1;
            v = st->unk18;
            if (v != 0) {
                sub->unk1 = D_80035BD8[st->unk18 = --v];
                BF->unk155 = 3;
            } else {
                actorScriptStart(D_807FBB40, 0x224);
                BF->unk155++;
            }
            break;
        case 6:
            func_8072E1A4(0xA, D_807FBB4C);
            break;
        case 7:
            actorScriptStart(D_807FBB40, 0x222);
            BF->unk155++;
        case 8:
            if (currentActorTestClearFlag() != 0) {
                BF->unk155++;
                sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x128, 0xFF, 0x19, 0);
            }
            break;
        case 9:
            if (BF->unk4->unk38 < BX->unk30) {
                actorSetUniformScale(D_807FBB40, BF->unk4->unk38 * 1.01);
                func_800336C0();
                sp7F = 1;
            } else {
                actorScriptStart(D_807FBB40, 0x227);
                BF->unk155++;
            }
            break;
        case 11:
            BF->unk6A &= 0xFFFE;
            if (currentActorTestClearFlag() != 0) {
                actorScriptStart(D_807FBB40, 0x22C);
                BF->unk155++;
            }
            break;
        case 13:
            camSetSecondTarget(gCamActor, BPTS->unk14[17].unk0, BPTS->unk14[17].unk4);
            st->unk14 = 0;
            st->unk15 = 0;
            BF->unk154 = tbl[st->unk15];
            st->unk15++;
            BF->unk155 = 0;
            sub->unk2 = 5;
            break;
        }
        break;
    case 0:
        switch (BF->unk155) {
        case 0:
        case 1:
        case 2:
            bossSetRandomObjectPair(sub, 0);
            actorScriptStart(D_807FBB40, 0x226);
            BF->unk155 = 3;
            break;
        case 3:
            if (BP->unk154 != 0x33) {
                st->unk15 = st->unk16;
                BF->unk154 = tbl[st->unk15];
                st->unk15++;
                BF->unk155 = 0;
            }
            break;
        }
        break;
    case 0x23:
        func_8072A450();
        switch (BF->unk155) {
        case 0:
            st->unk18 = tbl[st->unk15++];
            st->unk19 = st->unk18;
            func_8003340C((u8 *)sub);
            sub->unk1 = bossPickWaypointStep((BossE_F0D0_Sub14 *)st, (u8 *)sub);
            BF->unk155 = 1;
            BF->unk6A |= 1;
        case 1:
            BF->unk155 = 2;
            func_80614D00(D_807FBB40, D_80036C40[st->unk14], 0.0f);
            sub->unk6 = sp83;
        case 2:
            func_8067ACB4(D_807FBB40);
            actorUpdateFloorContactAndTilt(D_807FBB40, 0.0f);
            bossInterpolateWaypoints((u8 *)sub, BF->unk4->unk64 == 0x223 ? 0.02173913f : 0.041666664f);
            if (BF->unk4->unk64 == 0x223) {
                v = 0x35;
            } else {
                v = 0x17;
            }
            if ((f32)(s32)v <= BF->unk4->unk0->unk4) {
                BF->unk6A |= 1;
            } else {
                BF->unk6A = 0;
                effectSpawnBoneDebris(4, 1);
                sp7F = 1;
            }
            break;
        case 3:
            sub->unk2 = sub->unk0;
            sub->unk0 = sub->unk1;
            if (sp83 != 0) {
                st->unk18 = st->unk19;
            }
            if (st->unk18 != 0) {
                sub->unk1 = bossPickWaypointStep((BossE_F0D0_Sub14 *)st, (u8 *)sub);
                st->unk18--;
                func_8003340C((u8 *)sub);
                BF->unk155 = 1;
            } else {
                BF->unk154 = tbl[st->unk15];
                st->unk15++;
                BF->unk155 = 0;
            }
            break;
        }
        break;
    case 0x25:
    case 0x28:
        func_8072E1A4(0xA, D_807FBB4C);
        if (func_800339D8((BossE_F0D0_Sub14 *)st, tbl) != 0) {
            bossSetRandomObjectPair(sub, 0);
        } else if (func_80724A20() == 0) {
            switch (BF->unk155) {
            case 0:
                bossSetRandomObjectPair(sub, 0xA);
                st->unk18 = tbl[st->unk15++] - 1;
                st->unk19 = tbl[st->unk15++];
                actorScriptStart(D_807FBB40, 0x229);
                BF->unk155 = 1;
                break;
            case 2:
                if (BF->unk154 == 0x25) {
                    actorScriptStart(D_807FBB40, 0x228);
                    goto block_131;
                }
                if (!(BX->unk1A & 0x8000)) {
                    if (BP->unk110 == 1) {
                        camStartPath(D_807FBB40, 0xF, 1);
                        BX->unk1A |= 0x8000;
                        goto block_130;
                    }
                } else {
block_130:
                    actorScriptStart(D_807FBB40, 0x22F);
block_131:
                    BF->unk155 = 3;
                }
                break;
            case 3:
                if (BF->unk154 == 0x25) {
                    effectSpawnBoneDebris(3, 1);
                    sp7F = 1;
                } else {
                    actorGetNodePos(D_807FBB40, 1, &sp68, &sp64, &sp60);
                    sp68 += (f32)((randomNonNegative() >> 15) % 100 - 0x32);
                    sp64 += (f32)((randomNonNegative() >> 15) % 100 + 0x32);
                    sp60 += (f32)((randomNonNegative() >> 15) % 100 - 0x32);
                    func_807149B8(1);
                    func_8071498C(D_8071EDEC);
                    func_80714950((s32)D_807FBB40);
                    func_80714CC0(D_8071FC58, 1.5f, sp68, sp64, sp60);
                    func_80714C08(D_80720054, 3.0f, D_807FBB40, 1, 2);
                }
                break;
            case 4:
                if (BF->unk154 == 0x25) {
                    projectileGetTargetCoords(D_807FBB40, 3);
                    projectileAimAndSpawn(0x3B, 1, 1.2f, BP->unk7C, BP->unk80 + 5.0f, BP->unk84, 900.0f, D_807FBB40);
                } else {
                    sub->unk1 = bossPickWaypointStep((BossE_F0D0_Sub14 *)st, (u8 *)sub);
                    bossSpawnObjectAtWaypoint((u8 *)sub);
                }
                BF->unk155 = 5;
                break;
            case 6:
                v = st->unk18;
                if (v != 0) {
                    st->unk18 = v - 1;
                    BX->unk2C = st->unk19;
                    BF->unk155 = 7;
                } else {
                    actorScriptStart(D_807FBB40, 0x22D);
                    BF->unk155 = 8;
                }
                break;
            case 7:
                if (BX->unk2C != 0) {
                    if (BP->unk154 == 0x33) {
                        BX->unk2C = st->unk19;
                    } else {
                        BX->unk2C = BX->unk2C - 1;
                    }
                } else {
                    BF->unk155 = 2;
                }
                break;
            case 9:
                bossSetRandomObjectPair(sub, 0);
                actorScriptStart(D_807FBB40, 0x22C);
                BF->unk155 = 0xA;
                break;
            case 11:
                BF->unk154 = tbl[st->unk15];
                st->unk15++;
                BF->unk155 = 0;
                break;
            }
        }
        break;
    case 0x27:
        switch (BF->unk155) {
        case 0:
        case 1:
        case 2:
            actorAppendActiveCallback8();
            bossSetRandomObjectPair(sub, 0);
            actorScriptStart(D_807FBB40, 0x22E);
            camStartPath(D_807FBB40, 2, 1);
            actorSpawnAttachment(D_807FBB40, 1.2f);
            sfxPlayAtPositionPooled(BF->unk7C, BF->unk80, BF->unk84, 0x305, 0xFF, 0x7F, 0, 0, 0.0f, 0);
            BF->unk155 = 3;
            break;
        case 4:
            effectSpawnJointBeam(7, 0xB, 0x11, 0x20);
            effectSpawnJointBeam(0xC, 0x10, 0x11, 0x20);
            break;
        case 5:
            effectSpawnRandomBoneDebris(7, 0x20);
            if (currentActorTestClearFlag() != 0 || camIsCutsceneActive() == 0) {
                BF->unk155++;
            }
            break;
        case 6:
            if (st->unk14 < 3) {
                actorScriptStart(D_807FBB40, 0x22C);
            } else {
                BF->unk155 = BF->unk155 + 1;
            }
            BF->unk155++;
            break;
        case 8:
            currentActorClearFlag();
            st->unk15 = 0;
            st->unk14++;
            tbl = D_80035B84[st->unk14];
            BF->unk154 = tbl[st->unk15];
            st->unk15++;
            BF->unk155 = 0;
            break;
        }
        break;
    case 0x29:
        switch (BF->unk155) {
        case 0:
            BF->unk60 &= 0xFFFF7FFF;
            actorScriptStart(D_807FBB40, 0x231);
            st->unk8 = (s8)tbl[st->unk15++];
            BF->unk155++;
            break;
        case 2:
            effectSpawnBoneDebris(2, 1);
            effectSpawnBoneDebris(3, 1);
            sp7F = 1;
            break;
        case 3:
            effectSpawnBoneDebrisScaled(2, (randomNonNegative() >> 15) % 0x7FFF % 6 + 5, 0x28);
            effectSpawnBoneDebrisScaled(3, (randomNonNegative() >> 15) % 0x7FFF % 6 + 5, 0x28);
            sp7F = 1;
            break;
        case 4:
            func_80033A80(((s8 *)st)[9]);
            break;
        case 5:
            BF->unk154 = tbl[st->unk15];
            st->unk15++;
            BF->unk155 = 0;
            break;
        }
        break;
    case 0x2B:
        switch (BF->unk155) {
        case 0:
            actorScriptStart(D_807FBB40, 0x222);
            BX->unk2C = 0x5A;
            BF->unk155++;
            break;
        case 1:
            if (BX->unk2C != 0) {
                BX->unk2C = BX->unk2C - 1;
            } else {
                st->unk15 = st->unk16;
                BF->unk154 = tbl[st->unk15];
                st->unk15++;
                BF->unk155 = 0;
            }
            break;
        }
        break;
    case 0x37:
        switch (BF->unk155) {
        case 0:
            camStartPath(D_807FBB40, 6, 0x81);
            BF->unk155++;
            break;
        case 1:
            if (currentActorTestClearFlag() != 0) {
                BF->unk155++;
            }
            break;
        case 2:
            func_80033A80(5);
            break;
        case 3:
            if (currentActorTestClearFlag() != 0) {
                func_8063DA40(sub->unk0, 0x1E);
                BF->unk155++;
            }
            break;
        case 4:
            if (currentActorTestClearFlag() != 0) {
                effectSpawnScatterRandom(D_80720BE8, 0, 6.0f, 6, 0x50, 0x64, (s32)BF->unk7C, (s32)(BP->unk80 + 100.0f), (s32)BF->unk84);
                effectSpawnScatterRandom(D_80720BE8, 0x14, 6.0f, 8, 0x96, 0x46, (s32)BF->unk7C, (s32)(BP->unk80 + 100.0f), (s32)BF->unk84);
                BF->unk155++;
            }
            break;
        case 5:
            if (camIsCutsceneActive() == 0) {
                bossSetRandomObjectPair(sub, 0);
                i = 0;
                do {
                    if (i != sub->unk0) {
                        func_8063DA40(i, 0x28);
                    }
                    i++;
                } while (i < 0x10);
                bossSpawnParticleRing(0x8A, BPTS->unk14[sub->unk0].unk0, BPTS->unk14[sub->unk0].unk2, BPTS->unk14[sub->unk0].unk4, 0x5DC, 1);
                BF->unk154 = 0x40;
                i = 0;
                do {
                    volumeTriggerSetEnabled(i, 0);
                    i++;
                } while (i < 7);
            }
            break;
        }
        break;
    default:
        bossScriptStep(tbl, 0, 0.0f);
        break;
    }
    if (sp7F != 0) {
        if (BF->unk6E == -1) {
            sfxPlayActorSound(D_807FBB40, 0x135, 0x4B, 1, 0, 0xB4, 1.0f, 0);
        }
    } else {
        sfxStopSlotSound(D_807FBB40, 0);
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}
#undef sub
#undef tbl
#undef sp83
#undef sp7F
#undef col
#undef BF
#undef BP
#undef BX
#undef BPTS

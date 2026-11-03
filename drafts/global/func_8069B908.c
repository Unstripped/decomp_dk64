// func_8069B908 (src/global/9DD70.c): L1317 r7: STAGE 4 NON_MATCHING park in .scratch/L1317/9DD70.c: 1317/1317 insns, frame 0x140, s0/s1/f20 match, deadsweep score 2 (shape 2) [was 42/shape 5]; only diff: uopt temp spill slot 100(sp) vs 108(sp) for the func_8071A8B0 address (2 lines; 8 bytes of spilltemps/vreg gap, no FAKE/pad/decl/respelling moves it). KEY: both unk58 0x3F-0x42 compare chains are switch(){case 0x3F..0x42} (so the unk58 loads become the shared cfe switch temp = v1 like target), loop uses sp13C->unk2A directly (no p174 FAKE), s32 pad74 before sp70, ghost global D_807FBB94: 'G && G' in the case-4 sp70 loop + 'if (G)' before and inside tail switch(gCurrentMap) = a v0 web overlapping the tail switch temp so the temp lands v1 and the early sp13C piece v0; old case-0 'unk58 && unk58' FAKE and D_807FBB4C FAKE removed. Tried for slot: all single dead tests (4 forms x 19 syms x all points), decl order/pad grids, named switch temps, FAKE deletions, loop access spellings, i/sp70 merge (count +2), function-address spellings.
typedef struct ActorSub174View {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ Actor *unk14;
    /* 0x18 */ u8 pad18[4];
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ u8 unk28;
    /* 0x29 */ u8 pad29[1];
    /* 0x2A */ u16 unk2A;
} ActorSub174View;

typedef struct ActorSub124View {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
} ActorSub124View;

typedef struct ActorNamePair {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ s32 unk4;
} ActorNamePair;

extern Actor *D_807FBB98;
extern u8 D_807FBB85;
extern u8 D_807FBB94;
extern u8 D_807FBB95;
extern u8 D_807FBB9C;
extern u8 D_807FBDC4;
extern f32 D_807FBC60;
extern f32 D_807FBC64;
extern s16 D_807502D0;
extern f32 D_807502E4;
extern u8 D_80720340;
extern ActorNamePair D_807503A4;

s32 actorHasActiveMovementFlags(Actor *);
s32 actorListFindIdByActor(Actor *);
void actorListSetPosByActor(Actor *, f32, f32, f32);
void actorListSpawnNodeEntry(s16, f32, f32, f32, s16, f32, s32, s32);
void actorApplyVelocity(Actor *);
void actorUpdateFloorContactAndTilt(Actor *, f32);
void actorCallbackMaskEnable(Actor *, s32);
void actorCallbackMaskDisable(Actor *, s32);
void actorCollisionEventsCancel(void *, s32);
void func_8068A2FC(Actor *);
void actorReleaseFromPlayerHold(Actor *);
void sfxSetVolumeAndPan(u8, f32, f32);
void actorSpawnNodeEntryScaled(s32, f32, f32, f32, s32, s32, s32, s32);
s32 actorAngleInArc(Actor *, s16);
f32 randomFloat(void);
void func_8071496C(s16);
void func_80714998(s32);
void camStartShake(s32, s32, s32);
void func_8071A8B0(void);
void effectTumbleBounceUpdate(void);

void func_8069B908(void) {
    ActorSub174View *sp13C;
    f32 mtxA[4][4];
    f32 mtxB[4][4];
    f32 dx;
    f32 dy;
    f32 dz;
    f32 spAC;
    f32 spB0;
    f32 spA4;
    ActorNamePair sp9C;
    s32 i;
    s32 var_v0;
    s16 ang;
    s32 pad84[3];
    s32 sp7C[2];
    s32 sp78;
    s32 pad74;  // pad: keeps sp70 at 0x70
    s32 sp70;

    sp13C = D_807FBB40->unk174;
    if (!(D_807FBB40->unk60 & 0x10)) {
        *(s16 *)((u8 *)D_807FBB40 + 0xFA) = 0x270F;
        D_807FBB40->unkA4 = 99999.0f;
        actorUpdateFloorContactAndTilt(D_807FBB40, 0);
        if (actorHasActiveMovementFlags(D_807FBB40) != 0) {
            D_807FBB40->unk144 = 2;
            D_807FBB40->unk68 |= 1;
            D_807FBB40->unk154 = 2;
            *(u8 *)((u8 *)D_807FBB40 + 0x155) = 1;
            sp13C->unk1C = 0x1E;
        }
        sp13C->unk28 = ((ActorSub124View *)D_807FBB40->unk124)->unk0;
        if (sp13C->unk28 != 0) {
            sp13C->unk4 = D_807FBB40->unk7C;
            sp13C->unk8 = D_807FBB40->unk80;
            sp13C->unkC = D_807FBB40->unk84;
            sp13C->unk10 = D_807FBB40->unk4->unk34 / 0.15;
        }
        if (((ActorSub124View *)D_807FBB40->unk124)->unk4 == 1) {
            D_807FBB40->unk132 = 2;
        } else {
            D_807FBB40->unk132 = 1;
        }
        switch (D_807FBB40->unk58) {
        case 0x43:
            if (flagGet(0x9A, 0) != 0) {
                func_8068A2FC(D_807FBB40);
            }
            break;
        case 0x3D:
            if (gCurrentMap == 0xC3) {
                if (flagGet(0x267, 0) != 0) {
                    func_8068A2FC(D_807FBB40);
                }
            }
            if (gCurrentMap == 0x26) {
                D_807FBB40->unk64 |= 0x400;
            }
            break;
        }
        switch (D_807FBB40->unk58) {
        case 0x3F:
        case 0x40:
        case 0x41:
        case 0x42:
            D_807FBB40->unk64 |= 0x420;
            break;
        }
    }
    if (D_807FBB94 != 0) {
        sp13C->unk14 = D_807FBB98;
        D_807FBB40->unk154 = 1;
        actorCallbackMaskDisable(D_807FBB40, 0x8000);
        actorCollisionEventsCancel(sp13C->unk14, 1);
        D_807FBB40->unk144 = 0x2C;
    }
    if (D_807FBB95 != 0) {
        D_807FBB40->unk154 = 2;
        *(u8 *)((u8 *)D_807FBB40 + 0x155) = 0;
        sp13C->unk1C = 0x1E;
        D_807FBB40->unk144 = 0x3C;
        actorCallbackMaskEnable(D_807FBB40, 0x8000);
        if (gCurrentMap == 7 && actorListFindIdByActor(D_807FBB40) == 0x17) {
            actorListSetPosByActor(D_807FBB40, D_807FBB40->unk7C, D_807FBB40->unkA4, D_807FBB40->unk84);
        }
    }
    if (gCurrentMap == 0x22 && D_807FBB40->unk58 == 0x3D &&
        (D_807FBB40->unk154 == 0 || D_807FBB40->unk154 == 2)) {
        if (D_807FBB40->unk7C >= 3242.0 && D_807FBB40->unk84 >= 252.0 &&
            D_807FBB40->unk7C <= 3842.0 && D_807FBB40->unk84 <= 852.0) {
            D_807FBB40->unk154 = 4;
        }
    }
    if (D_807FBB85 != 0 || D_807FBD70 == 9) {
        D_807FBB40->unk154 = 4;
        actorReleaseFromPlayerHold(D_807FBB40);
    }
    if (D_807FBB9C != 0) {
        D_807FBB40->unk154 = 3;
        D_807FBB40->unk144 = 0x3C;
        actorCallbackMaskEnable(D_807FBB40, 0x8000);
        D_807FBB40->unkE6 = *(s16 *)((u8 *)&D_807FBB70 + 0x36);
        *(s16 *)((u8 *)D_807FBB40 + 0xEE) = *(s16 *)((u8 *)&D_807FBB70 + 0x36);
        *(f32 *)((u8 *)D_807FBB40 + 0xC0) = *(f32 *)((u8 *)&D_807FBB70 + 0x30);
        D_807FBB40->unkB8 = (f32)*(s16 *)((u8 *)&D_807FBB70 + 0x34);
        actorCollisionEventsCancel(sp13C->unk14, 1);
        if (D_807FBB40->unk58 == 0x43 && gCurrentMap == 0x1E) {
            D_807FBB40->unk60 |= 0x200000;
            sp13C->unk0 = D_8076A068;
        }
    }
    if (D_807FBB40->unk58 == 0x55) {
        if (actorHasActiveMovementFlags(D_807FBB40) != 0) {
            D_807FBB40->unk60 |= 0x400;
        } else {
            D_807FBB40->unk60 &= ~0x400;
        }
    }
    func_8067ACB4(D_807FBB40);
    switch (D_807FBB40->unk58) {
    case 0x3F:
    case 0x40:
    case 0x41:
    case 0x42:
        for (i = 0; i < D_807FBDC4; i++) {
            if (D_807FBB70.unk258[i] - 1 == 0) {  // FAKE: `- 1 == 0` keeps const 1 from becoming a hoisted typed-constant candidate (target: li at,1 inside the loop)
                sp13C->unk2A = 0;
                D_807FBB40->unk154 = 5;
            }
        }
        break;
    }
    switch (D_807FBB40->unk154) {
    case 0:
        D_807FBB40->unk144 = 2;
        D_807FBB40->unk64 |= 8;
        D_807FBB40->unk60 |= 0x80000000;
        D_807FBB40->unk68 |= 1;
        if (actorHasCallbackTargetThisFrame() != 0) {
            D_807FBB40->unk154 = 4;
        }
        break;
    case 1:
        D_807FBB40->unk68 &= 0xFFFE;
        D_807FBB40->unk64 &= ~8;
        D_807FBB40->unk60 &= 0x7FFFFFFF;
        sp13C->unk20 = (f32)(((f64)sp13C->unk14->unkE6 / 4095.0) * 360.0);
        break;
    case 2:
        D_807FBB40->unk64 &= ~8;
        D_807FBB40->unk60 &= 0x7FFFFFFF;
        if (sp13C->unk1C != 0) {
            sp13C->unk1C--;
        }
        if (sp13C->unk1C == 0 && (D_807FBB40->unk6A & 1)) {
            D_807FBB40->unk154 = 0;
        } else if (actorHasActiveMovementFlags(D_807FBB40) != 0) {
            sp13C->unk1C = 0x1E;
        }
        if ((D_807FBB40->unk6A & 1) && *(u8 *)((u8 *)D_807FBB40 + 0x155) == 0) {
            if (D_807FBB40->unk58 == 0x55) {
                sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x8B, 0x64, 0x7F, 0x14);
                sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x97, 0x64, 0x7F, 0x14);
            } else {
                sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x97, 0xFF, 0x7F, 0x14);
            }
            (*(u8 *)((u8 *)D_807FBB40 + 0x155))++;
        }
        *(f32 *)((u8 *)D_807FBB40 + 0xC0) = -200.0f;
        D_807FBB40->unkB8 = 0.0f;
        D_807FBB40->unk68 |= 1;
        if (actorHasCallbackTargetThisFrame() != 0) {
            D_807FBB40->unk154 = 4;
        }
        break;
    case 3:
        *(f32 *)((u8 *)D_807FBB40 + 0xC0) = *(f32 *)((u8 *)D_807FBB40 + 0xC0) + D_807502E4;
        if (*(f32 *)((u8 *)D_807FBB40 + 0xC0) < (f32)D_807502D0) {
            *(f32 *)((u8 *)D_807FBB40 + 0xC0) = (f32)D_807502D0;
        }
        var_v0 = 0;
        sp13C->unk24 = sp13C->unk24 - 10.0f;
        if (D_807FBB40->unk58 == 0x43 && gCurrentMap == 0x1E &&
            (u32)(D_8076A068 - sp13C->unk0) >= 0x5B) {
            var_v0 = 1;
        }
        if (var_v0 != 0 || (D_807FBB40->unkFC != 0 && actorAngleInArc(D_807FBB40, D_807FBB40->unkE6) == 0)) {
            D_807FBB40->unk154 = 4;
        }
        D_807FBB40->unk68 &= 0xFFFE;
        D_807FBB40->unk64 &= ~8;
        D_807FBB40->unk60 &= 0x7FFFFFFF;
        break;
    case 4:
        if (D_807FBB40->unk58 == 0x3D && sp13C->unk28 == 0) {
            switch (actorListFindIdByActor(D_807FBB40)) {
            case 0x17:
                if (flagGet(0x19, 0) == 0) {
                    actorSpawnNodeEntryScaled(0x2D, D_807FBB40->unk7C, D_807FBB40->unk80 + 10.0f,
                                  D_807FBB40->unk84, 0, 2, 0x19, 0);
                    sfxAllocateChannel(0x14, 1.0f);
                }
                break;
            case 6:
                if (flagGet(0x1D, 0) == 0) {
                    actorSpawnNodeEntryScaled(0x6E, D_807FBB40->unk7C, D_807FBB40->unk80 + 10.0f,
                                  D_807FBB40->unk84, 0, 2, 0x1D, 0);
                }
                break;
            }
        }
        sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x162, 0xFF, 0x7F, 0x1E);
        if (!D_807FBC64) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        if (sp13C->unk28 == 0) {
            actorDespawn(D_807FBB40);
        }
        if (D_807FBB70.unk0 == 0) {
            sp9C = D_807503A4;
            for (sp70 = 0; sp70 != 0x10; sp70 += 2) {
                spAC = (f32)(((f64)((randomNonNegative() >> 15) % 8191) / 200.0) - 20.0);
                spB0 = (f32)(((f64)((randomNonNegative() >> 15) % 8191) / 200.0) - 20.0);
                spA4 = (f32)(((f64)((randomNonNegative() >> 15) % 8191) / 200.0) - 20.0);
                func_8071496C(sp70);
                if (D_807FBB94 && D_807FBB94) {}  // FAKE: ghost candidate: two reads in the sp70 loop make D_807FBB94 a high-priority v0 web (with the two tests below) that forces the shared switch temp to v1 / early sp13C piece to v0
                func_807149B8(1);
                if (sp70 == 0) {
                    func_80714950(0x100FA);
                    func_8071498C(func_8071A8B0);
                } else {
                    func_8071498C(func_80717D4C);
                    func_80714950(-0x96 - ((randomNonNegative() >> 15) % 50));
                }
                func_80714CC0(&D_80720340, 1.6f, D_807FBB40->unk7C + spAC,
                              D_807FBB40->unk80 + spB0, D_807FBB40->unk84 + spA4);
                if (D_807FBB40->unk58 == 0x3D) {
                    spAC = (2.0f * randomFloat()) - 1.0f;
                    spB0 = (2.0f * randomFloat()) - 1.0f;
                    spA4 = (2.0f * randomFloat()) - 1.0f;
                    spAC *= 30.0f;
                    spB0 *= 30.0f;
                    spA4 *= 30.0f;
                    spB0 += 30.0f;
                    func_807149B8(1);
                    func_807149FC(0x3C);
                    func_8071498C(effectTumbleBounceUpdate);
                    func_80714998(2);
                    func_80714950(2);
                    sp78 = randomNonNegative();
                    if (sp78) {}  // FAKE: block split between the sp78 def and the call (steers ugen ring / uopt colouring)
                    func_80714CC0((void *)((s32 *)&sp9C)[(sp78 >> 15) % 2],
                                  (f32)(((f64)randomFloat() * 0.5) + 0.2),
                                  D_807FBB40->unk7C + spAC, D_807FBB40->unk80 + spB0,
                                  D_807FBB40->unk84 + spA4);
                }
            }
            camStartShake(*(s32 *)((u8 *)D_807FBB4C->unk174 + 0x104), 0x14, 0xF);
        }
        if (sp13C->unk28 != 0) {
            D_807FBB40->unk154 = 0xA;
            D_807FBB40->unk138 = 0;
            D_807FBB40->unk144 = 1;
            D_807FBB40->unk60 &= ~4;
        }
        break;
    case 5:
        D_807FBB40->unk64 &= ~8;
        D_807FBB40->unk60 &= 0x7FFFFFFF;
        D_807FBB40->unk68 &= 0xFFFE;
        sp13C->unk2A = sp13C->unk2A + 2;
        if (sp13C->unk2A >= 0xFB) {
            sp13C->unk2A = 0xFA;
        }
        if (*(s16 *)((u8 *)D_807FBB40 + 0x6E) == -1) {
            sfxPlayActorSound(D_807FBB40, 0x11A, 0x64, 1, 0, 0x64, 1.0f, 0);
        } else {
            sfxSetVolumeAndPan(*(s16 *)((u8 *)D_807FBB40 + 0x6E),
                               (f32)(((f64)(u32)sp13C->unk2A / 400.0) + 0.5), 2.0f);
        }
        lightAdd(D_807FBB40->unk7C, D_807FBB40->unk80 + 30.0f, D_807FBB40->unk84,
                 0, 0.0f, .0f, (f32)(((f64)(u32)sp13C->unk2A / 250.0) * 100.0), 0, 0xFF, 0xFF, 0);  // FAKE: .0f spelling = separate zero web (target: two distinct lightAdd zero webs)
        D_807FBB40->unkE6 = D_807FBB40->unkE6 + sp13C->unk2A;
        D_807FBB40->unk80 = D_807FBB40->unkA4;
        break;
    case 10:
        dz = D_807FBB4C->unk84 - sp13C->unkC;
        dx = D_807FBB4C->unk7C - sp13C->unk4;
        dy = D_807FBB4C->unk80 - sp13C->unk8;
        if ((dz * dz) + ((dx * dx) + (dy * dy)) > 2500.0f) {
            sp7C[0] = sp13C->unk28;
            if (D_807FBB40->unk132 == 2) {
                sp7C[1] = 1;
            } else {
                sp7C[1] = 0;
            }
            actorListSpawnNodeEntry(*(s16 *)((u8 *)D_807FBB40 + 0x5A), sp13C->unk4, sp13C->unk8,
                                    sp13C->unkC, 0, sp13C->unk10, 0, (s32)sp7C);
            actorDespawn(D_807FBB40);
        }
        break;
    case 0x63:
        break;
    }
    if (D_807FBB40->unk154 == 2 || D_807FBB40->unk154 == 3) {
        *(s16 *)((u8 *)D_807FBB40 + 0xEE) = D_807FBB40->unkE6;
        actorApplyVelocity(D_807FBB40);
        actorUpdateFloorContactAndTilt(D_807FBB40, 0);
        if (D_807FBB40->unk154 == 3 && (D_807FBB40->unk6A & 1) && !(D_807FBB40->unk6C & 1)) {
            D_807FBB40->unk154 = 4;
        }
        if (D_807FBB40->unk154 == 2 && (D_807FBB40->unk6A & 4)) {
            D_807FBB40->unk154 = 4;
        }
        *(s16 *)((u8 *)D_807FBB40 + 0xDC) = 0x3FF;
        *(s16 *)((u8 *)D_807FBB40 + 0xDE) = 0x3FF;
    } else {
        D_807FBB40->unk110 = 0;
        D_807FBB40->unk6A &= 0xFBF7;
    }
    if (D_807FBB94) {}  // FAKE: ghost candidate, extends the D_807FBB94 web over the gCurrentMap switch temp
    switch (gCurrentMap) {
    case 0x26:
    case 0x71:
    case 0xC2:
        if (D_807FBB40->unk58 == 0x3D) {
            if (D_807FBB40->unk110 == 1) {
                if (D_807FBB94) {}  // FAKE: ghost candidate (see the sp70 loop), keeps the D_807FBB94 web live across the gCurrentMap switch
                D_807FBB40->unk60 |= 0x200000;
            } else {
                D_807FBB40->unk60 &= ~0x200000;
            }
        }
        break;
    }
    if (D_807FBB40->unk154 != 0x63) {
        billboardSubmit(D_807FBB40, 0x3C8, 0x40, 0x40, 0x14, 0x14, 1, 0x64, 0x78, 0, 1.0f);
    }
    guScaleF(mtxA, D_807FBB40->unk4->unk34, D_807FBB40->unk4->unk38, D_807FBB40->unk4->unk3C);
    guRotateF(mtxB, sp13C->unk24, 0.0, 1.0f, 0.0);
    guMtxCatF(mtxA, mtxB, mtxA);
    guRotateF(mtxB, (f32)(((f64)D_807FBB40->unkE6 / 4095.0) * 360.0), 0.0, 1.0f, 0.0);
    guMtxCatF(mtxA, mtxB, mtxA);
    guRotateF(mtxB, (f32)(0.0 - (f64)D_807FBC60), 1.0f, 0.0, 0.0);
    guMtxCatF(mtxA, mtxB, mtxA);
    guRotateF(mtxB, (sp13C->unk20 + 90.0f) - D_807FBC64, 0.0, 1.0f, 0.0);
    guMtxCatF(mtxA, mtxB, mtxA);
    if (D_807FBB40->unk154 == 3) {
        ang = *(s16 *)((u8 *)D_807FBB40 + 0xDE);

        if (ang < 0x3E8) {
            guRotateF(mtxB, (f32)(-(((f64)*(s16 *)((u8 *)D_807FBB40 + 0xDC) / 4095.0) * 360.0)),
                      0.0, 1.0f, 0.0);
            guMtxCatF(mtxA, mtxB, mtxA);
            ang = *(s16 *)((u8 *)D_807FBB40 + 0xDE);
        }
        guRotateF(mtxB, (f32)(90.0 - (((f64)ang / 4095.0) * 360.0)), 1.0f, 0.0, 0.0);
        guMtxCatF(mtxA, mtxB, mtxA);
        if (*(s16 *)((u8 *)D_807FBB40 + 0xDE) < 0x3E8) {
            guRotateF(mtxB, (f32)(((f64)*(s16 *)((u8 *)D_807FBB40 + 0xDC) / 4095.0) * 360.0),
                      0.0, 1.0f, 0.0);
            guMtxCatF(mtxA, mtxB, mtxA);
        }
    }
    guTranslateF(mtxB, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84);
    guMtxCatF(mtxA, mtxB, (f32 (*)[4])((u8 *)D_807FBB40 + 0xC));
}

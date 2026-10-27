// func_80024690 (src/race/0.c): stage 4 (LargeR4, pass 2): same callee-saved set (s0,s1), frame 0x70; text 5984 vs 6000 (missing 'move a0,a1' after the case-2 actorScriptStart reload + 3 other moves); 18 structural + ~270 reg-only lines. Case 9/10/0 dispatch structure now matches (u32 x + reload arm in case 10; s32 y + 'sel = sp54->unk35 + 1' + switch(y) in case 0 gives right regs v1/v0/a0 but copies a0/v0 in swapped order, LargeR1's unsolved diff). Open: (1) ang: sp64[1] array gives exact raw 'mfc1; sh 0x66(sp); addu' shape but t-ring skew (mfc1 t5 vs t3); multi-def 'ang = sp64[1] = X; ang = ang+ang-EE; f(ang&0xFFF)' aligns the first ring temps (t3,t5,t4) but colours the sum a3 instead of a1 and the skew returns downstream; narrowing form (ang = (sp64[1]=X) or ang1) aligns ring but adds sll/sra. (2) case 2: V=lbu 0x25(DC90) a2 vs a1, DCA0 a1 vs a2, missing W copy; named idx/a1 locals, a1 inside sqrtf compare, e = base; e += idx all worse. (3) sched: li v0,0x65 vs addiu v1,%lo(D_80750AC8); li a1/move a0,s0 order in case 2 and 9. Needed: mathAngleStepToward s32, flag s32 local, D_8002FB94 via s32 temp.
/* externs D_807FDC90, D_807FDCA0, D_8002FB10, D_8002FB70 come from the RaceC block (func_80024000 NON_MATCHING); accessed here through casts */
extern s32 D_8076A0A8;
extern void *D_807FBB40;
extern void *D_807FBB48;
typedef struct {
    u8 pad0[0x1C];
    u16 unk1C;
} LargeR4_Child;

typedef struct {
    u8 pad0[0x30];
    struct LargeR4_Kid *unk30;
    u8 unk34;
    u8 unk35;
    u8 unk36;
    u8 pad37[0xD0 - 0x37];
    s16 unkD0;
} LargeR4_Ctl;

struct LargeR4_Kid {
    u8 pad0[0x174];
    LargeR4_Child *unk174;
};

typedef struct {
    u8 pad0[4];
    s32 unk4;
    u8 pad8[0x18 - 0x8];
    union {
        s32 w;
        struct {
            s16 hi;
            s16 lo;
        } h;
    } unk18;
    s32 unk1C;
} LargeR4_Cfg;

typedef struct {
    u8 pad0[0x60];
    u32 unk60;
    u8 pad64[4];
    u16 unk68;
    u16 unk6A;
    u16 unk6C;
    u8 pad6E[0x7C - 0x6E];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xB8 - 0x88];
    f32 unkB8;
    u8 padBC[4];
    f32 unkC0;
    f32 unkC4;
    f32 unkC8;
    u8 padCC[0xDC - 0xCC];
    s16 unkDC;
    u8 padDE[0xE6 - 0xDE];
    s16 unkE6;
    s16 unkE8;
    u8 padEA[0xEE - 0xEA];
    s16 unkEE;
    u8 padF0[0xFC - 0xF0];
    u8 unkFC;
    u8 padFD[0x12A - 0xFD];
    s16 unk12A;
    u8 pad12C[0x132 - 0x12C];
    s16 unk132;
    u8 pad134[0x144 - 0x134];
    u8 unk144;
    u8 pad145[0x154 - 0x145];
    u8 unk154;
    u8 unk155;
    u8 pad156[0x15F - 0x156];
    u8 unk15F;
    u8 pad160[0x178 - 0x160];
    LargeR4_Ctl *unk178;
    LargeR4_Cfg *unk17C;
} LargeR4_Act;

typedef struct {
    u8 pad0[0x24];
    u8 unk24;
    u8 unk25;
    u8 pad26[0x2C - 0x26];
    s16 unk2C;
    s16 unk2E;
    u8 pad30[0x35 - 0x30];
    u8 unk35;
} LargeR4_State;

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    u8 pad6;
    u8 unk7;
    u8 unk8;
    u8 pad9;
} LargeR4_Entry;

typedef struct {
    u8 pad0[0x10];
    s16 unk10;
    u8 pad12[2];
    LargeR4_Entry *unk14;
} LargeR4_Path;

typedef struct {
    s16 unk0;
    u8 pad2[2];
    f32 unk4;
    u8 unk8;
    u8 pad9[3];
} LargeR4_Row;

extern LargeR4_Act *D_807FBB4C;
extern u8 D_807FBD70;
extern u16 D_80750AC8;
extern s32 D_8002FB94[];

#define L4_D ((LargeR4_Act *)D_807FBB40)
#define L4_S ((LargeR4_State *)D_807FDC90)
#define L4_P ((LargeR4_Path *)D_807FDCA0)

void actorApplyGravity(void);
void actorApplyVelocity(void *);
void actorApproachTargetSpeed(s32);
void actorScriptStart(void *, s32);
void actorSetTargetSpeed(void *, s32);
void actorStepPhysics(void *, s16, s16);
void actorUpdateModelMatrix(void *, s32);
void behaviourFrameBegin(void *);
void camResumePath(void);
s32 camStartPath(void *, s16, s32);
void currentActorClearFlag(void);
s32 currentActorTestClearFlag(void);
void flagSet(s16, s32, s32);
void func_80024000(void);
void func_8002D72C(void *);
s32 func_8002E8EC(void *, s32, s32);
void func_8002F490(void *);
void func_805FF544(void);
f32 func_80611BB4(f32, f32);
void func_8063DA40(s32, s32);
f32 sqrtf(f32);
void func_80665564(void *, s32);
void func_8065D254(void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32);
s32 func_806CCC10(void);
void hudSpawnTextScreen(s32);
s32 mathAngleStepToward(s16 *, s16, s32);
void playerStateQueueCallback(s16, void *, u8);
void sfxPlayFromActorWithAltitudeCheck(void *, s32, s32, s32, s32);
s32 sfxStopSlotSound(void *, s32);
void slotQueueCancel(s32, s32);
void slotQueueUpdate(s32, s32, s32);

void func_80024690(void) {
    f32 sp6C;
    f32 sp68;
    s16 sp64[2];
    s32 ang;
    LargeR4_Entry *e;
    u8 sp5B;
    LargeR4_Ctl *sp54;
    LargeR4_Cfg *sp50;
    struct LargeR4_Kid *sp4C;
    LargeR4_Child *sp48;
    LargeR4_Row *sp44;
    s32 flag;
    f32 fv1;
    s32 sel;
    u32 x;
    s32 y;
    f32 dist;

    sp54 = L4_D->unk178;
    sp50 = L4_D->unk17C;
    sp4C = sp54->unk30;
    sp48 = NULL;
    if (D_8076A0A8 == 0x52) {
        sp44 = (LargeR4_Row *)D_8002FB10;
    } else {
        sp44 = (LargeR4_Row *)D_8002FB70;
    }
    if (sp4C != NULL) {
        sp48 = sp4C->unk174;
    }
    behaviourFrameBegin(sp4C);
    if (!(L4_D->unk60 & 0x10)) {
        L4_D->unk144 = 0x1C;
        L4_D->unk60 |= 0x10400;
        L4_D->unk60 &= 0xFFFDFFFF;
        L4_D->unk154 = 0;
        L4_D->unk155 = 0;
        L4_D->unkB8 = 0.0f;
        L4_D->unkC4 = -20.0f;
        flag = 0x65;
        L4_D->unkC8 = -900.0f;
        L4_D->unk12A = 0x7D0;
        L4_S->unk35 = 0;
        L4_S->unk2C = 0x64;
        L4_S->unk2C = 0;
        L4_S->unk24 = 0;
        L4_D->unk68 &= 0xFFBF;
        if (D_8076A0A8 == 0x52) {
            sp50->unk1C = D_80750AC8 = 0x32;
            sp50->unk18.w = 0x103;
        } else {
            sp50->unk1C = D_80750AC8 = 0x32;
            flag = 0x66;
            sp50->unk18.w = 0x4B;
        }
        if (flagGet(flag, 2) == 0 && flagGet(sp50->unk18.h.lo, 0) == 0) {
            camStartPath(D_807FBB40, 0, 1);
            currentActorClearFlag();
            flagSet(flag, 1, 2);
        } else {
            sp54->unk35 = 3;
        }
    }
    sp5B = L4_S->unk24;
    if (sp48 != NULL && sp54->unk34 < 3 && D_807FBD70 == 4) {
        playerStateQueueCallback(0x33, D_807FBB40, 0);
    }
    if (sp54->unk34 < 3 && L4_D->unk154 == 2 && D_807FBD70 == 5) {
        sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x1CA, 0xFF, 0x7F, 0xA);
        sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x209, 0xFF, 0x7F, 0xA);
        L4_D->unkB8 = 0.0f;
        L4_D->unk154 = 0x14;
        L4_D->unkC4 = -40.0f;
        L4_D->unkC0 = 400.0f;
    }
    if (func_806CCC10() != 0) {
        L4_D->unk132 = 1;
    } else {
        L4_D->unk132 = 2;
    }
    switch (L4_D->unk154) {
    case 20:
        L4_D->unkE8 = (L4_D->unkE8 - 0xC8) & 0xFFF;
        if ((L4_D->unk6A & 1) && L4_D->unkC0 <= 0.0f) {
            L4_D->unk154 = 2;
            L4_D->unkE8 = 0;
        }
        break;
    case 0:
        if (sp48 != NULL && sp48->unk1C == 0) {
            L4_D->unk154 = L4_D->unk154 + 1;
            L4_D->unk155 = 0;
            L4_D->unk6A |= 0x200;
        }
        break;
    case 1:
        if (sp54->unk34 == 2) {
            if (D_8076A0A8 == 0x52) {
                actorSetTargetSpeed(D_807FBB40, 0x10E);
            } else {
                actorSetTargetSpeed(D_807FBB40, 0xAA);
            }
            L4_S->unk35 = 0xA;
            actorScriptStart(D_807FBB40, 0x282);
            L4_D->unk154 = L4_D->unk154 + 1;
            break;
        }
    case 2:
        actorApproachTargetSpeed(0);
        sp6C = L4_D->unk7C - (f32)L4_P->unk14[L4_S->unk25].unk0;
        sp68 = L4_D->unk84 - (f32)L4_P->unk14[L4_S->unk25].unk4;
        dist = sqrtf(sp68 * sp68 + sp6C * sp6C);
        if (dist < (f32)L4_P->unk14[L4_S->unk25].unk7) {
            fv1 = L4_D->unk80;
            if ((f32)L4_P->unk14[L4_S->unk25].unk2 < fv1) {
                dist = fv1 - (f32)L4_P->unk14[L4_S->unk25].unk2;
            } else {
                dist = -(fv1 - (f32)L4_P->unk14[L4_S->unk25].unk2);
            }
            if (dist < 80.0f) {
                if (L4_S->unk25 < L4_P->unk10 - 1) {
                    if (L4_P->unk14[L4_S->unk25].unk8 == 0) {
                        actorScriptStart(D_807FBB40, 0x283);
                        L4_D->unk154 = L4_D->unk154 + 1;
                    }
                    if (L4_S->unk25 == sp44[sp5B].unk0) {
                        L4_D->unkC4 = sp44[sp5B].unk4;
                        L4_S->unk24 = L4_S->unk24 + 1;
                    }
                    L4_S->unk25 = L4_S->unk25 + 1;
                }
            }
        }
        sp64[1] = (s32)((f64)func_80611BB4(-sp6C, -sp68) * 4096.0 / 6.2831854820251465);
        mathAngleStepToward(&L4_D->unkE6, (sp64[1] + sp64[1] - L4_D->unkEE) & 0xFFF, 0x32);
        mathAngleStepToward(&L4_D->unkEE, sp64[1], 0xF);
        if (L4_S->unk25 == sp44[L4_S->unk24].unk0 && sp44[L4_S->unk24].unk8 == 2 && sp54->unk34 == 3) {
            if (sp54->unk36 == 1) {
                L4_D->unk154 = 0xA;
            } else {
                L4_D->unk154 = 9;
            }
            actorScriptStart(D_807FBB40, 0);
            L4_D->unk155 = 0;
        }
        break;
    case 3:
        actorApproachTargetSpeed(0x200);
        break;
    case 4:
        actorApproachTargetSpeed(0x200);
        L4_D->unkC0 = 200.0f;
        L4_D->unk154 = L4_D->unk154 + 1;
        break;
    case 5:
        actorApproachTargetSpeed(0x200);
        break;
    case 6:
        if (L4_S->unk2E != 0) {
            L4_S->unk2E = L4_S->unk2E - 1;
        } else if (L4_D->unkFC != 0) {
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0xFF, 0x46, 0x7F, 2);
            L4_S->unk2E = 0x14;
        }
        if (L4_S->unk25 == sp44[L4_S->unk24].unk0 && sp44[L4_S->unk24].unk8 == 1) {
            fv1 = (f32)(L4_D->unkEE - L4_D->unkE6);
            if (fv1 > 2048.0f) {
                fv1 -= 4096.0f;
            }
            if (fv1 < -2048.0f) {
                fv1 += 4096.0f;
            }
            if (fv1 > 50.0f) {
                fv1 = 50.0f;
            }
            if (fv1 < -50.0f) {
                fv1 = -50.0f;
            }
            L4_S->unk2C = (s32)((f32)L4_S->unk2C + fv1);
            L4_S->unk2C = (s32)((f64)L4_S->unk2C - (f64)L4_S->unk2C * 0.3);
        } else {
            if ((L4_D->unk6A & 1) && !(L4_D->unk6C & 1)) {
                actorScriptStart(D_807FBB40, 0x285);
                L4_D->unkC4 = -20.0f;
            }
            fv1 = (f32)(L4_D->unkEE - L4_D->unkDC);
            if (fv1 > 2048.0f) {
                fv1 -= 4096.0f;
            }
            if (fv1 < -2048.0f) {
                fv1 += 4096.0f;
            }
            L4_S->unk2C = (s32)((f64)L4_S->unk2C + (f64)(fv1 * L4_D->unkB8) / 8000.0);
            if (L4_S->unk2C > 500) {
                L4_S->unk2C = 500;
            }
            if (L4_S->unk2C < -500) {
                L4_S->unk2C = -500;
            }
        }
        L4_D->unkE6 = (L4_D->unkE6 + L4_S->unk2C) & 0xFFF;
        func_80024000();
        break;
    case 7:
        if (D_8076A0A8 == 0xE) {
            actorSetTargetSpeed(D_807FBB40, 0xB4);
        }
        func_80024000();
        break;
    case 8:
        L4_D->unk154 = 2;
        L4_D->unkE6 = L4_D->unkEE;
        break;
    case 9:
        L4_S->unk35 = 8;
        actorSetTargetSpeed(D_807FBB40, 0);
        actorApproachTargetSpeed(0x200);
        if (L4_D->unk155 == 0) {
            actorScriptStart(D_807FBB40, 0x287);
            L4_D->unk155 = L4_D->unk155 + 1;
        }
        break;
    case 10:
        x = L4_D->unk155;
        switch (x) {
        case 0:
            actorSetTargetSpeed(D_807FBB40, 0);
            L4_S->unk35 = 8;
            L4_D->unk155 = 1;
            break;
        case 1:
            if (L4_D->unkB8 == 0.0f) {
                L4_D->unk155 = L4_D->unk155 + 1;
            }
            break;
        case 2:
            L4_S->unk35 = 0;
            actorScriptStart(D_807FBB40, 0x288);
            L4_D->unk155 = L4_D->unk155 + 1;
            break;
        }
        actorApproachTargetSpeed(0x200);
        break;
    }
    switch (sp54->unk34) {
    case 0:
        y = sp54->unk35;
        sel = y;
        switch (y) {
        case 0:
            if (L4_D->unk60 & 0x02000000) {
                sel = sp54->unk35 + 1;
                sp54->unk35 = sel;
            }
            break;
        case 1:
            if (!(L4_D->unk60 & 0x02000000)) {
                camResumePath();
                sel = sp54->unk35 = sp54->unk35 + 1;
            }
            break;
        case 2:
            if (currentActorTestClearFlag() != 0) {
                currentActorClearFlag();
                sp54->unk35 = sp54->unk35 + 1;
            }
            sel = sp54->unk35;
            break;
        }
        if (sel < 3) {
            func_8002D72C(sp4C);
        }
        break;
    case 1:
        if (sp54->unk35 == 0) {
            slotQueueUpdate(0xB, 1, 0);
            sp54->unk35 = sp54->unk35 + 1;
        }
        break;
    case 3:
        if (sp54->unk35 == 0) {
            flag = 0x55;
            if (D_807FBB4C->unk6A & 0x200) {
                flag = 0x56;
            }
            playerStateQueueCallback(flag, NULL, 0);
            sp54->unk35 = sp54->unk35 + 1;
        }
        break;
    case 4:
        if (sp54->unk35 == 0) {
            slotQueueCancel(0xB, 0);
            sp54->unkD0 = 0;
            if (flagGet(sp50->unk18.h.lo, 0) == 0) {
                ang = D_8002FB94[func_8002E8EC(sp54, sp50->unk4, sp50->unk1C)];
                camStartPath(D_807FBB40, ang, 1);
                currentActorClearFlag();
            } else {
                func_805FF544();
            }
            sp54->unk35 = sp54->unk35 + 1;
        }
        break;
    case 5:
        sel = sp54->unk35;
        switch (sel) {
        case 0:
            if (flagGet(sp50->unk18.h.lo, 0) == 0) {
                sfxStopSlotSound(D_807FBB48, 0);
                playerStateQueueCallback(0x55, NULL, 0);
                L4_D->unkB8 = 0.0f;
                if (func_80024634((void *)sp54, (void *)sp50) != 0) {
                    L4_D->unk154 = 0xA;
                    L4_D->unk155 = 0;
                } else {
                    L4_D->unk154 = 9;
                    L4_D->unk155 = 0;
                }
            }
            sp54->unk35 = sp54->unk35 + 1;
            break;
        case 1:
            if (L4_D->unk60 & 0x02000000) {
                sp54->unk35 = sel + 1;
            }
            break;
        case 2:
            if (!(L4_D->unk60 & 0x02000000)) {
                camResumePath();
                if (func_80024634((void *)sp54, (void *)sp50) == 0) {
                    sp54->unk35 = 4;
                }
                sp54->unk35 = sp54->unk35 + 1;
                L4_D->unk15F = 0;
            }
            break;
        case 3:
            if (currentActorTestClearFlag() != 0) {
                currentActorClearFlag();
                if (D_8076A0A8 == 0xE) {
                    func_8063DA40(0x48, 0xA);
                } else {
                    func_8063DA40(1, 0xA);
                }
                sp54->unk35 = sp54->unk35 + 1;
            }
            break;
        case 4:
            if (flagGet(sp50->unk18.h.lo, 0) != 0) {
                sp54->unk35 = sp54->unk35 + 1;
            }
            break;
        case 5:
            if (currentActorTestClearFlag() != 0) {
                currentActorClearFlag();
                if (flagGet(sp50->unk18.h.lo, 0) != 0) {
                    func_805FF544();
                } else {
                    hudSpawnTextScreen(1);
                }
                sp54->unk35 = sp54->unk35 + 1;
            }
            break;
        }
        break;
    }
    actorApplyGravity();
    actorStepPhysics(D_807FBB40, L4_D->unkEE, L4_D->unkEE);
    actorApplyVelocity(D_807FBB40);
    func_80665564(D_807FBB40, 0);
    func_8065D254(D_807FBB40, 0x3C8, 0x40, 0x40, 0xE, 0xE, 1, 0x96, 0x78, 0, 1.0f);
    if (sp54->unk34 == 2) {
        func_8002F490(sp54);
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

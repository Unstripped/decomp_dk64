// menuHandleControllerSlotInput (src/menu/3E10.c): stage 6 PARKED NON_MATCHING full=6 (unchanged, W2IntE). Frame 0x88, same blocks. Left: i&0x10 arm: cap(lim) 5/4 coloured v0 vs target v1 and D_80744520 load/copy v1 vs v0 (4 insn pairs, reg-only). uopt: lim isvar adjsave 2.6 colours before the D_80744520 load cand (2.0); target colours the load first. NEW (W2IntE): giving the cap its OWN variable (existing unused local padX/rest/step, so no frame-slot shift; 'if (D_80744520 < padX) D_80744520 += 1;') makes arm-1 regs EXACT, but then the clamp lim and the i=lim web coalesce: 'and s0,t9,t4' instead of 'and v0,t9,t4; move s0,v0' and the i&0x10 tests use s0 not v0 (count 713, full 6 with a far dead test if (rest == cur) {} 80 stmts after i = rest; at 714 full 7-8). Target keeps the pressed mask in v0 for the arm tests and copies to s0 after the calls (one var, live range split). Tried 800+ role grids (cap/clamp/mask var x 8 locals, nat/copy form, dead tests on mask var, arms testing the mask var vs i), 2x13.8k-eval dead-test anneal from that state (best 7 at 714), earlier: edge/padX copy, cap at all 13 decl positions, decl-order anneal 2x9.7k (6).
typedef struct MenuScreenActor {
    char pad0[0x174];
    void *unk174;
} MenuScreenActor;

typedef struct MenuScreenState {
    f32 unk0;
    f32 unk4;
    char pad8[4];
    s16 unkC;
    s16 unkE;
    s16 unk10;
    s8 unk12;
    s8 unk13;
    char pad14;
    s8 unk15;
    s8 unk16;
    s8 unk17;
} MenuScreenState;

extern s8 D_80033FAD;
extern s8 D_80744520;
extern s8 D_80744534;
extern s8 D_8076A0E5;
extern s8 D_8076A0E6;
extern s8 D_8076A0E7;
extern s8 D_80033FAE;
extern s8 D_80033F50;
extern u8 D_80744514;
extern s8 D_80033FAF;
extern s8 D_8074451C;
extern s32 D_8003382C[];
extern s32 D_80033834[];
extern u8 D_8003384C[];
extern s32 D_80033858;
extern s32 D_8003385C[];
extern s8 gPlayerCharacterId[];
extern u8 D_80750ABC;
extern u8 D_80750AC0;
extern s32 D_807552E4[];
extern u8 D_807ECD09;
extern OSContPad D_807ECD10[];
void func_8071458C(void);

void menuHandleControllerSlotInput(MenuScreenActor *arg0, s32 arg1) {
    MenuScreenState *sp84 = arg0->unk174;
    s32 step;
    s32 rest;
    s32 i;
    s32 j;
    s32 edge;
    s32 bits;
    s32 idx;
    s32 sp64;
    s32 padX;
    s32 lim;
    s32 mask;
    s16 cur;

    step = sp84->unkC;
    step = sp84->unkE - step;
    if (step >= 0x15) {
        step = 0x14;
    }
    if (step < -0x14) {
        step = -0x14;
    }
    sp84->unkC += step;
    rest = sp84->unkE - sp84->unkC;
    if (step != 0 && rest == 0) {
        sfxPlayOnFreeSlot(0x3C, 0x4E20, 63.0f, 1.0f, 0, 0);
        D_80033F50 = 3;
    }
    if (D_80033FAE != 0) {
        arg1 = 0;
    }
    if (sp84->unk0 == 0.0f && rest == 0) {
        sp64 = 5;
        if (D_8076A104 == 0) {
            sp64 = 6;
        }
        if (sp84->unk4 == 0.0f) {
            if ((arg1 & 1) && D_80033FAD >= 2) {
                mask = 0;
                D_80750AC0 = 0;
                for (j = 0; j != 4; j++) {
                    bits = 1 << j;
                    if (!(D_8076A0E4[j] & 0x80)) {
                        gPlayerCharacterId[j] = D_8076A0E4[j];
                        mask = (mask | bits) & 0xFF;
                        D_807552E4[4 + D_80750AC0] = D_8076A100[j];
                        D_80750AC0 += 1;
                    }
                }
                controllerSetActiveMask(mask & 0xFF);
                D_807552E4[0] = D_8003382C[D_8076A104];
                D_807552E4[1] = D_80033834[D_8074451C];
                D_807552E4[3] = D_80744520;
                D_807552E4[8] = D_80744538;
                D_80750ABC = D_8003384C[D_80744534];
                D_80033FAE = 1;
                D_80744514 = 2;
                func_8071458C();
            } else {
                if (arg1 & 2) {
                    sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0, 0, 0);
                    sp84->unk16 = 0;
                    sp84->unk13 = 6;
                } else if (arg1 & 0x40) {
                    sp84->unkE = sp84->unkE - 0xF0;
                    if ((D_80033FAD == 2 || D_80033FAD == 3) && D_8076A104 != 1) {
                        lim = -0x1E0;
                    } else {
                        lim = -0xF0;
                    }
                    if (sp84->unkE < lim) {
                        sp84->unkE = lim;
                    } else {
                        sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0, 0, 0);
                    }
                } else if (arg1 & 0x80) {
                    sp84->unkE += 0xF0;
                    if (sp84->unkE > 0) {
                        sp84->unkE = 0;
                    } else {
                        sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0, 0, 0);
                    }
                }
            }
            lim = (arg1 ^ D_80033858) & arg1;
            cur = sp84->unkC;
            i = lim; // FAKE: temp copy keeps the and in its own candidate
            if (cur == 0 && D_80033FAE == 0) {
                i = 0;
                do {
                    bits = 0;
                    if (D_807ECD09 & (1 << i)) {
                        if (D_807ECD10[i].stick_x < -0x28) {
                            bits = 4;
                        } else if (D_807ECD10[i].stick_x >= 0x29) {
                            bits = 8;
                        }
                        if (D_807ECD10[i].stick_y < -0x28) {
                            bits |= 0x20;
                        } else if (D_807ECD10[i].stick_y >= 0x29) {
                            bits |= 0x10;
                        }
                        edge = (D_8003385C[i] ^ bits) & bits;
                        D_8003385C[i] = bits;
                        if (D_8076A0E4[i] & 0x80) {
                            if (((u16 *)&D_807ECD48)[i] & 0x1000) {
                                sfxPlayOnFreeSlot(0x75, 0x7FFF, 63.0f, 1.0f, 0, 0);
                                menuAssignPlayerControllerSlot(i, 0);
                            }
                        } else {
                            if (edge & 8) {
                                sfxPlayOnFreeSlot(0x74, 0x7FFF, 63.0f, 1.0f, 0, 0);
                                idx = D_8076A0E4[i] + 1;
                                if (idx >= 6) {
                                    idx = 0;
                                }
                                while (!(D_80033FAF & (1 << idx))) {
                                    idx += 1;
                                    if (idx >= 6) {
                                        idx = 0;
                                    }
                                }
                                menuAssignPlayerControllerSlot(i, idx);
                            }
                            if (edge & 4) {
                                sfxPlayOnFreeSlot(0x74, 0x7FFF, 63.0f, 1.0f, 0, 0);
                                idx = D_8076A0E4[i] - 1;
                                if (idx < 0) {
                                    idx = 5;
                                }
                                while (!(D_80033FAF & (1 << idx))) {
                                    idx -= 1;
                                    if (idx < 0) {
                                        idx = 5;
                                    }
                                }
                                menuAssignPlayerControllerSlot(i, idx);
                            }
                            if (edge & 0x10) {
                                sfxPlayOnFreeSlot(0x74, 0x7FFF, 63.0f, 1.0f, 0, 0);
                                menuNextFreeControllerSlot(i);
                            }
                            if (edge & 0x20) {
                                sfxPlayOnFreeSlot(0x74, 0x7FFF, 63.0f, 1.0f, 0, 0);
                                menuPrevFreeControllerSlot(i);
                            }
                            if (i != 0 && (((u16 *)&D_807ECD48)[i] & 0x1000)) {
                                sfxPlayOnFreeSlot(0x75, 0x7FFF, 63.0f, 1.0f, 0, 0);
                                menuReleasePlayerControllerSlot(i);
                            }
                        }
                    }
                    i += 1;
                } while (i != 4);
            } else if (cur == -0xF0) {
                if (i & 0x10) {
                    lim = 5;
                    if (D_80033834[D_8074451C] == 5) {
                        lim = 4;
                    }
                    edge = D_80744520; // FAKE: copy of D_80744520 keeps its load in the first candidate colour (v0)
                    if (edge < lim) {
                        D_80744520 = edge + 1;
                        sfxPlayOnFreeSlot(0x74, 0x7FFF, 63.0f, 1.0f, 0, 0);
                    }
                } else if ((i & 0x20) && D_80744520 >= 2) {
                    if (!D_8074451C) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    D_80744520 -= 1;
                    sfxPlayOnFreeSlot(0x74, 0x7FFF, 63.0f, 1.0f, 0, 0);
                }
                menuHandleScrollInput(sp84, sp64, i);
            } else if (cur == -0x1E0) {
                if (i & 0x10) {
                    D_80744534 += 1;
                    if (D_80744534 >= 3) {
                        D_80744534 = 0;
                    }
                    sfxPlayOnFreeSlot(0x74, 0x7FFF, 63.0f, 1.0f, 0, 0);
                } else if (i & 0x20) {
                    D_80744534 -= 1;
                    if (D_80744534 < 0) {
                        D_80744534 = 2;
                    }
                    sfxPlayOnFreeSlot(0x74, 0x7FFF, 63.0f, 1.0f, 0, 0);
                }
            }
        }
        menuUpdateScrollAnimation(sp84, sp64);
    }
    D_80033858 = arg1;
    {
        D_8074451C = sp84->unk17;
        if (D_80033834[D_8074451C] == 5 && D_80744520 >= 5) {
            D_80744520 = 4;
        }
    }
    menuUpdateItemTransition(arg0, sp84, 1);
    D_807FBB60 |= 0x10000;
    menuUpdateCameraPositions();
    D_80033FAD = 0;
    for (i = 0; i < 4; i++) {
        if (!(D_8076A0E4[i] & 0x80)) {
            D_80033FAD += 1;
        }
    }
}

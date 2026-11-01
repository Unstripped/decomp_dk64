// menuHandleControllerSlotInput (src/menu/3E10.c): stage 3 (frame 0x88 OK but no s2: 711 insns vs 714). Fixed this round (vs old draft): (1) head 'step = sp84->unkC; step = sp84->unkE - step;' gives target lh v1,12/lh a2,14/subu v0,a2,v1; (2) j-loop 'bits = 1 << j;' BEFORE the if + 'mask = (mask | bits) & 0xFF' BEFORE the D_807552E4 store gives li/addu/andi/bnez + sllv in the delay slot and 'or a3,a3,t'; (3) 'lim = (arg1 ^ D_80033858) & arg1; m = lim;' gives 'and v1' + 'move s0,v1' in the bnez delay slot. Remaining: ONLY &D_80033FAD never in s2: target keeps ONE lda candidate (lui/addiu s2 at head block 0x30e8, else-chain top 0x322c, tail top 0x37f8 before both calls) - ours has head/else pieces in ugen t7/t8 and tail piece in s0 (cnt local form). Direct-global form has no head/else hoist at all (worse). Dead-stmt/permuter/cnt variants of the previous attempts do not produce s2 without extra insns. Consequences of missing s2: frame spill slots 56 vs 68, ' 5' order at tail, one lw 132(sp) placement in the 0x40 branch.
typedef struct OlR_S174 {
    f32 unk0;
    f32 unk4;
    char pad8[4];
    s16 unkC;
    s16 unkE;
    char pad10[3];
    s8 unk13;
    char pad14[2];
    s8 unk16;
    s8 unk17;
} OlR_S174;

typedef struct OlR_Pad {
    char pad0[2];
    s8 unk2;
    s8 unk3;
    char pad4[2];
} OlR_Pad;

extern s8 D_80033F50;
extern s8 D_80033FAD;
extern s8 D_80033FAE;
extern s8 D_80033FAF;
extern s8 D_8074451C;
extern u8 D_80744514;
extern s32 D_8003382C[];
extern s32 D_80033834[];
extern u8 D_8003384C[];
extern s32 D_80033858;
extern s32 D_8003385C[];
extern s8 D_80744520;
extern s8 D_80744534;
extern s8 gPlayerCharacterId[];
extern u8 D_80750ABC;
extern u8 D_80750AC0;
extern s32 D_807552E4[];
extern s8 D_8076A0E5;
extern s8 D_8076A0E6;
extern s8 D_8076A0E7;
extern u8 D_807ECD09;
extern OlR_Pad D_807ECD10[];
void func_8071458C();

void menuHandleControllerSlotInput(void *arg0, s32 arg1) {
    OlR_S174 *sp84 = *(OlR_S174 **)((u8 *)arg0 + 0x174);
    s32 step;
    s32 rest;
    s32 m;
    s32 i;
    s32 j;
    s32 edge;
    s32 bits;
    s32 sp64;
    s32 idx;
    s32 lim;
    s32 mask;
    s8 *cnt = (s8 *)(s32)&D_80033FAD;
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
            if ((arg1 & 1) && *cnt >= 2) {
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
            } else if (arg1 & 2) {
                sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0, 0, 0);
                sp84->unk16 = 0;
                sp84->unk13 = 6;
            } else if (arg1 & 0x40) {
                sp84->unkE = sp84->unkE - 0xF0;
                if ((*cnt == 2 || *cnt == 3) && D_8076A104 != 1) {
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
                s32 t = sp84->unkE + 0xF0;
                sp84->unkE = t;
                if (t > 0) {
                    sp84->unkE = 0;
                } else {
                    sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0, 0, 0);
                }
            }
            cur = sp84->unkC;
            lim = (arg1 ^ D_80033858) & arg1;
            m = lim; // FAKE: temp copy keeps the and in its own candidate
            if (cur == 0 && D_80033FAE == 0) {
                i = 0;
                do {
                    bits = 0;
                    if (D_807ECD09 & (1 << i)) {
                        if (D_807ECD10[i].unk2 < -0x28) {
                            bits = 4;
                        } else if (D_807ECD10[i].unk2 >= 0x29) {
                            bits = 8;
                        }
                        if (D_807ECD10[i].unk3 < -0x28) {
                            bits |= 0x20;
                        } else if (D_807ECD10[i].unk3 >= 0x29) {
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
                if (m & 0x10) {
                    lim = 5;
                    if (D_80033834[D_8074451C] == 5) {
                        lim = 4;
                    }
                    if (D_80744520 < lim) {
                        D_80744520 += 1;
                        sfxPlayOnFreeSlot(0x74, 0x7FFF, 63.0f, 1.0f, 0, 0);
                    }
                } else if ((m & 0x20) && D_80744520 >= 2) {
                    D_80744520 -= 1;
                    sfxPlayOnFreeSlot(0x74, 0x7FFF, 63.0f, 1.0f, 0, 0);
                }
                menuHandleScrollInput(sp84, sp64, m);
            } else if (cur == -0x1E0) {
                if (m & 0x10) {
                    D_80744534 += 1;
                    if (D_80744534 >= 3) {
                        D_80744534 = 0;
                    }
                    sfxPlayOnFreeSlot(0x74, 0x7FFF, 63.0f, 1.0f, 0, 0);
                } else if (m & 0x20) {
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
        s8 sel = sp84->unk17;
        D_8074451C = sel;
        if (D_80033834[sel] == 5 && D_80744520 >= 5) {
            D_80744520 = 4;
        }
    }
    menuUpdateItemTransition(arg0, sp84, 1);
    D_807FBB60 |= 0x10000;
    menuUpdateCameraPositions();
    *cnt = 0;
    if (!(D_8076A0E4[0] & 0x80)) {
        *cnt += 1;
    }
    if (!(D_8076A0E5 & 0x80)) {
        *cnt += 1;
    }
    if (!(D_8076A0E6 & 0x80)) {
        *cnt += 1;
    }
    if (!(D_8076A0E7 & 0x80)) {
        *cnt += 1;
    }
}

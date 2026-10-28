// func_8002ADC8 (src/menu/3E10.c): stage 3: front/loops/branches structure matches (714 insns = expected), frame 0x90 vs 0x88 and s2 missing. Target keeps &D_80033FAD in s2 (head+tail pieces, lb 0(s2), no store-load forwarding); mine gets s0 for tail only / t-reg head. 0x2C9 calls need 1.0 (not 1.0f) arg4 to give lui a3 vs mfc1 fs1. sp84 stack, sp64 0x64. dummy locals u1-u3 for frame.
typedef struct MenuL3_S174 {
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
} MenuL3_S174;

typedef struct MenuL3_Pad {
    char pad0[2];
    s8 unk2;
    s8 unk3;
    char pad4[2];
} MenuL3_Pad;

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
extern s8 D_8074E77C[];
extern u8 D_80750ABC;
extern u8 D_80750AC0;
extern s32 D_807552E4[];
extern s8 D_8076A0E5;
extern s8 D_8076A0E6;
extern s8 D_8076A0E7;
extern u8 D_807ECD09;
extern MenuL3_Pad D_807ECD10[];
void func_8071458C();

void func_8002ADC8(void *arg0, s32 arg1) {
    MenuL3_S174 *sp84 = *(MenuL3_S174 **)((u8 *)arg0 + 0x174);
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
    s32 u1;
    s32 u2;
    s32 u3;
    s8 *cnt = (s8 *)(s32)&D_80033FAD;
    s16 cur;

    step = sp84->unkE - sp84->unkC;
    if (step >= 0x15) {
        step = 0x14;
    }
    if (step < -0x14) {
        step = -0x14;
    }
    sp84->unkC += step;
    rest = sp84->unkE - sp84->unkC;
    if (step != 0 && rest == 0) {
        func_80609140(0x3C, 0x4E20, 63.0f, 1.0f, 0, 0);
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
                    if (!(D_8076A0E4[j] & 0x80)) {
                        D_8074E77C[j] = D_8076A0E4[j];
                        D_807552E4[4 + D_80750AC0] = D_8076A100[j];
                        mask = (mask | (1 << j)) & 0xFF;
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
                func_80609140(0x2C9, 0x7FFF, 63.0f, 1.0, 0, 0);
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
                    func_80609140(0x2C9, 0x7FFF, 63.0f, 1.0, 0, 0);
                }
            } else if (arg1 & 0x80) {
                s16 t = sp84->unkE + 0xF0;
                sp84->unkE = t;
                if (t > 0) {
                    sp84->unkE = 0;
                } else {
                    func_80609140(0x2C9, 0x7FFF, 63.0f, 1.0, 0, 0);
                }
            }
            cur = sp84->unkC;
            m = (arg1 ^ D_80033858) & arg1;
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
                                func_80609140(0x75, 0x7FFF, 63.0f, 1.0f, 0, 0);
                                menuAssignPlayerControllerSlot(i, 0);
                            }
                        } else {
                            if (edge & 8) {
                                func_80609140(0x74, 0x7FFF, 63.0f, 1.0f, 0, 0);
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
                                func_80609140(0x74, 0x7FFF, 63.0f, 1.0f, 0, 0);
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
                                func_80609140(0x74, 0x7FFF, 63.0f, 1.0f, 0, 0);
                                func_8002ACD4(i);
                            }
                            if (edge & 0x20) {
                                func_80609140(0x74, 0x7FFF, 63.0f, 1.0f, 0, 0);
                                func_8002AD50(i);
                            }
                            if (i != 0 && (((u16 *)&D_807ECD48)[i] & 0x1000)) {
                                func_80609140(0x75, 0x7FFF, 63.0f, 1.0f, 0, 0);
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
                        func_80609140(0x74, 0x7FFF, 63.0f, 1.0f, 0, 0);
                    }
                } else if ((m & 0x20) && D_80744520 >= 2) {
                    D_80744520 -= 1;
                    func_80609140(0x74, 0x7FFF, 63.0f, 1.0f, 0, 0);
                }
                menuHandleScrollInput(sp84, sp64, m);
            } else if (cur == -0x1E0) {
                if (m & 0x10) {
                    D_80744534 += 1;
                    if (D_80744534 >= 3) {
                        D_80744534 = 0;
                    }
                    func_80609140(0x74, 0x7FFF, 63.0f, 1.0f, 0, 0);
                } else if (m & 0x20) {
                    D_80744534 -= 1;
                    if (D_80744534 < 0) {
                        D_80744534 = 2;
                    }
                    func_80609140(0x74, 0x7FFF, 63.0f, 1.0f, 0, 0);
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

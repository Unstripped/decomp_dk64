// func_806A8158 (src/global/ACDC0.c): stage 5: frame 0x58 + stack slots match (decl order hud,i,diff,flag,moved,buttons,step,a2,lim,half); same insn count; remaining: D_807FC924 load order @47c, li a0,1/lui order @d3c, D_807505D4 decrement keeps pointer reg (target uses lui/lb + lui at/sb), D_807FC80C/80D load order @d68. Needs func_806AA304 prototype -> K&R.
typedef struct L10Hud {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ s16 unk8[2];
    /* 0x0C */ s16 unkC[2];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s8 unk12;
    /* 0x13 */ s8 unk13;
    /* 0x14 */ s8 unk14;
    /* 0x15 */ s8 unk15;
    /* 0x16 */ s8 unk16;
    /* 0x17 */ s8 unk17;
    /* 0x18 */ u8 unk18;
} L10Hud;

typedef struct L10Axis {
    u8 pad0[2];
    s8 unk2;
    s8 unk3;
} L10Axis;

typedef struct L10Player {
    u8 pad0[0x214];
    f32 unk214;
} L10Player;

extern L10Axis *D_807ECDEC;
extern u8 D_807467E4;
extern s32 D_8076A098;
extern u8 D_8076A0AB;
extern s32 D_807FBB64;
extern f32 D_807FC7FC;
extern s8 D_807505D4;
extern s8 D_80750580;
extern s16 D_807505A4[];
extern f32 D_80750584[];
extern s8 D_807FC800;
extern s16 D_807FC802;
extern f32 D_807FC804;
extern s8 D_807FC80C;
extern s8 D_807FC80D;
extern s16 D_807FC83A;
extern s8 D_807FC83C;
extern s8 D_807FC8B8;

s32 func_805FF000();
s32 func_805FF030();
s32 func_805FEF74();
s32 func_80712628();
void func_8060DEC8();
void func_80712EDC();
void func_807127B4();
s32 func_806C8DE0();
s32 func_806CC10C(s16, s16);
void func_80600044();
void func_8073129C(s32, s32, s32);
void func_806ABE3C();
s32 func_806ABC94();
Gfx *func_806AC048(Gfx *, Actor *);
Gfx *func_806A92B4(Gfx *, Actor *);
void func_806A9124(void);

#define L10_CC (*(s8 *)D_807505CC)
#define L10_LIST ((s8 *)&D_80750530)

void func_806A8158(void) {
    L10Hud *hud;
    s32 i;
    s32 diff;
    s32 flag;
    s32 moved;
    s32 buttons;
    s32 step;
    s32 a2;
    s32 lim;
    s32 half;

    hud = D_807FBB40->unk174;
    switch (D_8076A0A8) {
        case 0x6:
        case 0xE:
        case 0x1B:
        case 0x27:
        case 0x37:
        case 0x52:
        case 0x6A:
        case 0xB9:
            L10_CC = 1;
            break;
        default:
            if (func_805FF000(D_8076A0A8 & 0xFF) == 9 || (D_807FBB64 & 0x10000000)) {
                L10_CC = 2;
            } else {
                L10_CC = 0;
            }
            break;
    }
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FC7E0 = func_80610FE8(0x6C);
        for (i = 0; i < 0x1B; i++) {
            D_807FC7E0[i] = func_8070E750(0x24, i, 0);
        }
        D_807FC7E8 = func_80610FE8(0x24);
        for (i = 0; i < 9; i++) {
            D_807FC7E8[i] = func_8070E750(0x23, i, 0);
        }
        D_8076A098++;
        D_807FC7FC = ((L10Player *)D_807FC924)->unk214;
        D_807505D4 = 0;
        D_807FC8B8 = 0;
        D_80750580 = 1;
        D_807505D0 = 7;
        while (D_807505D0 >= 0 && func_8073110C(D_807505D0 + 0x1C5, 0) == 0) {
            D_807505D0--;
        }
        D_807505D0++;
        hud->unk12 = 0;
        hud->unk17 = 0;
        hud->unk16 = -1;
        hud->unk0 = 1.0f;
        hud->unk4 = 0.0f;
        hud->unk14 = func_806C8DE0(0);
        hud->unk8[0] = func_806A80C0(func_805FF030(D_8076A0AB, 1));
        if (D_807505D0 < hud->unk8[0]) {
            hud->unk8[0] = 0;
        }
        hud->unk8[1] = hud->unk8[0];
        hud->unkC[0] = 0;
        hud->unkC[1] = 0xF0;
        hud->unk15 = 0;
        hud->unk10 = D_807505A4[hud->unk14];
        D_807FC800 = hud->unk14;
        D_807FC802 = 0;
        D_807FC804 = 0.0f;
        D_807FC808 = 0.0f;
        D_807FC80C = 0;
        D_807FC80D = D_807FC80C;
        D_807FC7F0[0] = func_80610FE8(0x1E0);
        D_807FC7F0[1] = D_807FC7F0[0] + 10;
        D_807FC7F8[0] = 0;
        D_807FC7F8[1] = 0;
        D_8075052C = 0;
        D_807FC80E = 1;
        func_806ABE3C(D_807FC7F8);
        func_806AA304(hud, 0);
        D_807FBB60 &= 0xFFFEFFCF;
        func_806291B4(7);
    }
    if (hud->unk0 == 0.0f && D_807FC8B8 == 0) {
        half = hud->unk15;
        moved = hud->unk8[half] != hud->unk8[1 - half];
        buttons = *D_807FC924->unk298;
        if (moved == 0 && hud->unk4 == 0.0f && D_807FC80C == D_807FC80D) {
            if (buttons & 0x5000) {
                func_80609140(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                if (hud->unk12 == 0 && hud->unk17 == 3) {
                    hud->unk17 = 2;
                } else {
                    hud->unk16 = 1;
                    hud->unk13 = -1;
                }
                buttons = 0;
            }
            if (D_807FC828 > 0) {
                flag = 0;
                if (buttons & 0x10) {
                    hud->unk13 = hud->unk12 + 1;
                    if (hud->unk13 >= 4) {
                        hud->unk13 = 0;
                    }
                    flag = 1;
                } else if (buttons & 0x2000) {
                    hud->unk13 = hud->unk13 - 1;
                    flag = 1;
                    if (hud->unk13 < 0) {
                        hud->unk13 = 3;
                    }
                }
                if (flag != 0) {
                    hud->unk16 = 1;
                    D_8075052C = 0;
                    buttons = 0;
                    func_80609140(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                }
            }
        }
        switch (hud->unk12) {
            case 0:
                if (hud->unk17 != 3) {
                    half = D_807ECDEC->unk3;
                    if (half < -0x32) {
                        if (D_807FC80E == 0) {
                            hud->unk17 = hud->unk17 + 1;
                            buttons = 0;
                            if (hud->unk17 >= 3) {
                                hud->unk17 = 0;
                            }
                            func_80609140(0x2A0, 0x7FFF, 63.0f, 1.0f, 0, 0);
                        }
                        D_807FC80E = 1;
                    } else if (half >= 0x33) {
                        if (D_807FC80E == 0) {
                            hud->unk17 = hud->unk17 - 1;
                            buttons = 0;
                            if (hud->unk17 < 0) {
                                hud->unk17 = 2;
                            }
                            func_80609140(0x2A0, 0x7FFF, 63.0f, 1.0f, 0, 0);
                        }
                        D_807FC80E = 1;
                    } else {
                        D_807FC80E = 0;
                    }
                    if (buttons & 0x8000) {
                        if (hud->unk17 == 2) {
                            hud->unk17 = 3;
                        } else if (hud->unk17 == 1) {
                            if (L10_CC != 0) {
                                func_805FF378(D_8076A0A8, 0);
                            } else if (hud->unk18 == 0) {
                                func_8060DEC8();
                                hud->unk18 = 1;
                            } else if (D_807505D4 == 0) {
                                func_80609140(0x23C, 0x7FFF, 63.0f, 1.0f, 0, 0);
                                D_807505D4 = 0x2D;
                            }
                        } else {
                            hud->unk16 = 1;
                            hud->unk13 = -1;
                        }
                    }
                } else if (buttons & 0x8000) {
                    a2 = func_805FF030(D_8076A0AB, 1);
                    flag = a2 == 8;
                    if (flag) {
                        flag = func_80712628() != 0;
                    }
                    D_807FC8B8 = 1;
                    if (L10_CC == 0 && a2 != 7 && a2 != 0xD && a2 != 9 && flag == 0) {
                        if (a2 == 0xA) {
                            func_80712EDC();
                        } else if (func_805FEF74(D_8076A0A8) == 0) {
                            lim = D_807FBB64 & 1;
                            if (lim != 0 && a2 == 8) {
                                func_8073129C(0x5C, 1, 2);
                                func_805FF378(0x22, 0xC);
                            } else if (lim != 0 && D_8076A0A8 != 0x3C) {
                                func_805FF378(0x2A, 2);
                            } else {
                                func_80600044(a2);
                            }
                        }
                    } else if (L10_CC != 0) {
                        if (L10_CC == 2) {
                            func_805FF898();
                        } else {
                            func_805FF544();
                        }
                    } else if (a2 == 7 || flag != 0) {
                        func_807127B4();
                    }
                }
                break;
            case 1:
                hud->unk10 = D_807505A4[D_807FC800] + (s32)(D_807FC804 * 0.5f * D_807FC802);
                hud->unk10 = hud->unk10 & 0xFFF;
                if (D_807FC804 == 0.0f) {
                    D_807FC802 = 0;
                    if (moved == 0) {
                        half = D_807ECDEC->unk2;
                        if (half < -0x28) {
                            do {
                                D_807FC800 += 1;
                                D_807FC802 -= 0x333;
                                if (D_807FC800 >= 5) {
                                    D_807FC800 = 0;
                                }
                            } while (L10_LIST[D_807FC800] == 0);
                        } else if (half >= 0x29) {
                            do {
                                D_807FC800 -= 1;
                                D_807FC802 += 0x333;
                                if (D_807FC800 < 0) {
                                    D_807FC800 = 4;
                                }
                            } while (L10_LIST[D_807FC800] == 0);
                        }
                        if (hud->unk14 != D_807FC800) {
                            D_807FC804 = 2.0f;
                            func_80609140(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                        }
                    }
                } else {
                    D_807FC804 -= 0.125f;
                    if (D_807FC804 < 0.0f) {
                        D_807FC804 = 0.0f;
                    }
                    hud->unk4 = D_807FC804 - 1.0f;
                    if (hud->unk4 < 0.0f) {
                        hud->unk4 = -hud->unk4;
                    }
                    hud->unk4 = 1.0f - hud->unk4;
                    hud->unk4 = hud->unk4 * 1.3f;
                    if (hud->unk4 > 1.2f && hud->unk14 != D_807FC800) {
                        hud->unk14 = D_807FC800;
                        func_80609140(0x2C9, 0x7FFF, 63.0f, 1.25f, 0, 0);
                        func_806AA304(hud, 1);
                    }
                    if (hud->unk14 == D_807FC800 && hud->unk4 > 1.0f) {
                        hud->unk4 = 1.0f;
                    }
                }
                func_806ABC94(hud, moved, buttons);
                break;
            case 2:
                hud->unk10 = hud->unk10 + 0x28;
                hud->unk10 = hud->unk10 & 0xFFF;
                func_806ABC94(hud, moved, buttons);
                break;
            case 3:
                step = diff = -func_806CC10C(D_807FC80D * D_807FC83A, hud->unk10);
                lim = D_807FC83A / 10;
                if (diff > 0) {
                    if (lim < diff) {
                        step = lim;
                    }
                    hud->unk10 = hud->unk10 + step;
                } else if (diff < 0) {
                    if (diff < -lim) {
                        step = -lim;
                    }
                    hud->unk10 = hud->unk10 + step;
                } else {
                    flag = 0;
                    half = D_807ECDEC->unk2;
                    if (half < -0x28) {
                        D_807FC80D += 1;
                        if (D_807FC80D >= D_807FC83C) {
                            D_807FC80D = 0;
                        }
                        flag = 1;
                    } else if (half >= 0x29) {
                        flag = 1;
                        D_807FC80D -= 1;
                        if (D_807FC80D < 0) {
                            D_807FC80D = D_807FC83C - 1;
                        }
                    }
                    if (flag != 0 && D_807FC80C != D_807FC80D) {
                        func_80609140(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                    }
                }
                hud->unk10 = hud->unk10 & 0xFFF;
                half = D_807FC83A >> 1;
                if (diff < 0) {
                    diff = -diff;
                }
                diff = diff - half;
                if (diff < 0) {
                    diff = -diff;
                }
                if (half < diff) {
                    diff = half;
                }
                hud->unk4 = (f32)(half - diff) / (f32)((f64)(f32)half * 0.9);
                if (hud->unk4 > 1.0f && D_807FC80C != D_807FC80D) {
                    D_807FC80C = D_807FC80D;
                }
                break;
        }
    }
    if (hud->unk16 == 1) {
        hud->unk0 = hud->unk0 + 0.13f;
        if (hud->unk0 > 1.3f) {
            lim = hud->unk13;
            hud->unk0 = 1.0f;
            if (lim == -1) {
                func_806A9124();
            } else {
                hud->unk12 = lim;
                hud->unk16 = -1;
                func_806AA304(hud, 0);
                func_80609140(0x2C9, 0x7FFF, 63.0f, 1.25f, 0, 0);
            }
        }
    } else if (hud->unk0 > 0.0f && D_8075052C == 0) {
        hud->unk0 = hud->unk0 - 0.2f;
        if (hud->unk0 < 0.0f) {
            hud->unk0 = 0.0f;
            D_8075052C = 3;
            func_80609140(0x3C, 0x7FFF, 63.0f, 1.0f, 0, 0);
        }
    }
    if (--D_807505D4 < 0) {
        D_807505D4 = 0;
    }
    if (D_807467E4 == 0x1C) {
        func_80609140(0x23C, 0x7FFF, 63.0f, 1.0f, 0, 0);
    }
    if (D_8075052C != 0) {
        D_8075052C -= 1;
        hud->unk0 = D_80750584[D_8075052C];
        ((L10Player *)D_807FC924)->unk214 = D_807FC7FC + hud->unk0 * 100.0;
    }
    renderCallbacksRegister(func_806AC048, D_807FBB40, 1);
    renderCallbacksRegister(func_806A92B4, D_807FBB40, 5);
}

#undef L10_CC
#undef L10_LIST

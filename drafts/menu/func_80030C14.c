// func_80030C14 (src/menu/3E10.c): stage 6 (parked NON_MATCHING): harness diff 33 -> 2 lines (one store order). Text/frame/regs identical; only 'swc1 f0,0(v1)' (D_80033F68[idx]=-200) is emitted before the 2nd D_80033F98[idx] load instead of after the unk364 store. Cause: the regalloc fix needs E (F68 store) BEFORE the dead 'if (arg0) {}' and D (unk364=F98[idx]) AFTER it so the F80/F98 address temps (298/301) drop to adjsave 1.5 while F68's (295) stays 3.0 (colour order 295, idx(2.4), 298, 301 -> v1,a1,a0,a2 = target); in target source order (D before E) as1 keeps E after D. Recipe: (1) idx *= (s32)sp64; idx -= ...; idx -= ... sequential (no temp for the first product); (2) FAKE 'if (arg0 && arg0 && arg0) {}' in inner case 3 lowers idx priority 3.0->2.4; (3) case 15 order A B C E [FAKE if (arg0) {}] D F. Not tried: any source form that keeps D before E but still gives adj(298)=adj(301)<adj(idx)<adj(295). No other dead stmts left.
typedef struct MenuRgba {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} MenuRgba;

typedef struct MenuL5_Cfg {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    s16 unkC[5];
    char padC[1];
    s8 unk17;
} MenuL5_Cfg;

typedef struct MenuL5_Tgt {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
} MenuL5_Tgt;

typedef struct MenuL5_Actor {
    char pad0[0x340];
    f32 unk340;
    f32 unk344;
    char pad348[0x14];
    MenuL5_Cfg *unk35C;
    f32 unk360;
    f32 unk364;
    char pad368[2];
    u8 unk36A;
    u8 unk36B;
    u8 unk36C;
    u8 unk36D;
    char pad36E[0x16];
    MenuL5_Tgt *unk384;
    char pad388[6];
    s16 unk38E;
    char pad390[2];
    s16 unk392;
} MenuL5_Actor;

extern MenuRgba D_800337DC[];
s32 func_8003155C(void *, s32, f32 *, f32 *, f32 *, s16 *, s16 *);

void func_80030C14(MenuL5_Actor *arg0, u8 *arg1) {
    MenuL5_Cfg *p = arg0->unk35C;
    MenuL5_Tgt *c;
    f32 f;
    f32 sp68;
    f32 sp64;
    s32 off;
    s32 type;
    s32 t;
    s32 idx;
    s32 r;
    s32 sp4C;
    s16 sp4A;
    s16 sp48;

    if (arg0->unk384 != NULL) {
        c = arg0->unk384;
        f = p->unk0;
        off = (s32)((f64)p->unkC[(s32)c->unk4] * 4.0);
        type = (s32)c->unk0;

        switch (type) {
        case 6:
        case 7:
        case 18: {
            r = func_8003155C(p, (s32)c->unk8 >> 2, &arg0->unk340, &arg0->unk344, &sp64, &sp4A, &sp48);
            arg0->unk360 = c->unk10 * sp64 * 4.0f;
            arg0->unk364 = arg0->unk360;
            if (type == 7) {
                t = (gFrameCounter * 0x78) & 0xFFF;
                arg0->unk344 += func_80612794(t) * 10.0f;
            }
            if (type == 0x12) {
                arg0->unk36A = sp4A;
                arg0->unk36B = sp4A;
                arg0->unk36C = sp4A;
                arg0->unk36D = sp48;
                arg0->unk38E = gPlayerSlots->unk270;
                arg0->unk392 = gPlayerSlots->unk274;
                if (arg0->unk344 < 360.0) {
                    if ((f64)arg0->unk340 < 640) {
                        arg0->unk392 = 0x78;
                    } else {
                        arg0->unk38E = 0xC8;
                    }
                }
                if (D_80033F3C != 0.0 && r == 0) {
                    arg0->unk392 = 0;
                }
            }
            break;
        }
        case 4:
        case 5:
        case 8:
            f = 1.0 - p->unk0;
            if (f < 0.0f) {
                f = 0.0f;
            }
            if (f > 1.0f) {
                f = 1.0f;
            }
            arg0->unk36D = (s32)(f * 255.0f);
            if (type == 4) {
                arg0->unk360 = (f64)(c->unk10 * f) * 4.0;
                arg0->unk364 = arg0->unk360;
            }
            f = 0;
            arg0->unk344 = c->unkC + (f32)off;
            if (type == 8) {
                D_80033FAC = 0;
                t = D_807ECDEC->unk2;
                if (t >= 0xB) {
                    arg0->unk340 += (f32)t;
                    if (arg0->unk340 > 960.0f) {
                        arg0->unk340 = 960.0f;
                        D_80033FAC = 1;
                    }
                } else if (t < -0xA) {
                    arg0->unk340 += (f32)t;
                    if (arg0->unk340 < 320.0f) {
                        arg0->unk340 = 320.0f;
                        D_80033FAC = 1;
                    }
                } else {
                    arg0->unk340 = (arg0->unk340 - 640.0) * 0.9 + 640.0;
                }
            } else {
                arg0->unk340 = c->unk8;
            }
            break;
        case 0:
        case 1:
        case 9:
        case 11:
        case 12:
        case 13:
        case 14:
        case 16:
        case 17:
        case 19:
            if (type != 0 && type != 0xB && type != 0x13 && type != 0xD && type != 0xE) {
                f *= 0.5f;
                f += p->unk4;
                f = 2.0f * f - 1.0f;
                if (f < 0.0f) {
                    f = -f;
                }
                f = 1.0f - f;
                if (f < 0.0f) {
                    f = 0.0f;
                }
            }
            arg0->unk340 = c->unk10 * f + c->unk8;
            arg0->unk344 = c->unk14 * f + c->unkC + (f32)off;
            if (type == 9) {
                arg0->unk344 = D_80033F4C - 140.0f;
            }
            if (type == 0xC) {
                arg0->unk344 += (f32)D_80033674;
            }
            if (type == 0) {
                if (off < -0x3BC) {
                    arg0->unk364 = 0.0f;
                } else {
                    arg0->unk364 = arg0->unk360;
                }
            }
            if (type == 0xB || type == 0x13) {
                arg0->unk344 += 960;
                if (off >= -3 || off < -0x77C) {
                    arg0->unk364 = 0.0f;
                } else {
                    arg0->unk364 = arg0->unk360;
                }
            }
            if (type == 0xD) {
                arg0->unk344 += 1920.0f;
                if (off >= -0x3C3) {
                    arg0->unk364 = 0.0f;
                } else {
                    arg0->unk364 = arg0->unk360;
                }
            }
            if (type == 0xE) {
                t = (gFrameCounter * 0x78) & 0xFFF;
                arg0->unk344 += func_80612794(t) * 10.0f;
            }
            if (type == 0x13 && (D_80033FAD == 4 || D_80033FAD == 1 || D_8076A104 == 1)) {
                arg0->unk340 = -400.0f;
            }
            if (type == 0x10 && p->unk17 >= 3) {
                arg0->unk340 = -400.0f;
            }
            if (type == 0x11 && p->unk17 < 3) {
                arg0->unk340 = -400.0f;
            }
            break;
        case 2:
        case 3:
        case 10: {
            idx = (s32)c->unk8;
            switch (type) {
            case 2:
                sp4C = 4;
                sp64 = 1024.0f;
                sp68 = 65.0f;
                break;
            case 3:
                if (arg0 && arg0 && arg0) {} // FAKE: lowers idx colouring priority below the case-15 address temps
                sp4C = 3;
                sp64 = 1365.0f;
                sp68 = 55.0f;
                break;
            case 10:
                sp4C = 2;
                sp64 = 2048.0f;
                sp68 = 50.0f;
                break;
            }
            idx *= (s32)sp64;
            idx -= p->unk17 * (s32)sp64;
            idx -= (s32)(p->unk4 * sp64);
            t = (s16)idx;
            arg0->unk340 = 160.0f - func_80612794(t) * sp68;
            arg0->unk344 = 120.0f - func_80612790(t) * sp68;
            if (func_800317E8(p, arg0->unk340, arg0->unk344, &arg0->unk340, &arg0->unk344, sp4C, 0, 1.0f) == (s32)c->unk8) {
                sp64 = 1.1f;
            } else {
                sp64 = 0.825f;
            }
            f = 0.0f;
            arg0->unk340 *= 4.0f;
            arg0->unk344 *= 4.0f;
            arg0->unk360 = c->unk10 * 4.0f * sp64;
            arg0->unk364 = arg0->unk360;
            break;
        }
        case 15: {
            idx = (s32)c->unk8;
            arg0->unk340 = D_80033F68[idx];
            arg0->unk344 = D_80033F80[idx];
            arg0->unk360 = D_80033F98[idx];
            D_80033F68[idx] = -200.0f;
            if (arg0) {} // FAKE: lowers the two later case-15 address temps below idx
            arg0->unk364 = D_80033F98[idx];
            D_80033F80[idx] = -200.0f;
            if (*(&D_80033804 + idx) == 0) {
                arg0->unk36A = *((u8 *)D_800337DC + (idx << 2));
                arg0->unk36B = *((u8 *)D_800337DC + (idx << 2) + 1);
                arg0->unk36C = *((u8 *)D_800337DC + (idx << 2) + 2);
            }
            break;
        }
        }
        if (f > 1.0f || p->unk0 > 1.0f) {
            *arg1 = 1;
        }
    }
}

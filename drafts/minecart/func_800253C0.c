// func_800253C0 (src/minecart/0.c): stage 5/6: frame 0x130 + s0,s1 match, 1161/1161 insns, all diff is register naming: lw v1 vs v0 (D_8076A0A8 compare), t8/t1 ring swap in D_807F5FD4[..] index block, abs a0 vs v0, f12 vs f2 for 0.0f, move v0,zero order in loop-1 preheader; locals declared in frame order (see decl list) incl. u8 i,cnt,i2,cnt2 + f64 t slot
typedef struct McB_Cart {
    s16 unk0;
    char pad2[2];
    void *unk4;
    char pad8[4];
    McA_V12 *unkC;
    s16 unk10;
    char pad12[2];
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    char pad24[8];
    f32 unk2C;
    char pad30[4];
    u8 *unk34;
    char pad38[1];
    u8 unk39;
    char pad3A[5];
    u8 unk3F;
    u8 unk40;
    u8 unk41;
} McB_Cart;

extern s32 D_807457E4[];
extern s16 D_80770628[];
extern f32 D_80770B68[];
extern s32 D_8076A064;
f32 sqrtf(f32);
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
s32 mathPickCloserTargetPoint3D(f32, f32, f32, McA_V12 *, McA_V12 *, McA_V12 *, McA_V12 *, f32 *, f32 *, f32 *);
void sfxPlayActorSound(void *, s32, s32, s32, s32, s32, f32, s32);
s16 func_806CC190(s16, s16, f32);
f32 func_80611BB4(f32, f32);
f32 func_80612790(s16);
f32 func_80612794(s16);
void func_8067ACB4(void *);
void matrixMakeRotationZ(f32 (*)[4], f32);
void func_80665564(void *, f32);
#define MC ((McB_Cart *)arg0)
void func_800253C0(void *arg0, s16 arg1, u8 arg2) {
    u8 i;
    u8 cnt;
    s8 sp12D;
    McA_V12 *sp128;
    McA_V12 *sp124;
    f32 sp118[3];
    f32 sp10C[3];
    f32 sp100[3];
    f32 spF4[3];
    s32 limit;
    f32 prev;
    s16 spEA;
    s16 n;
    f32 diff;
    f32 spE0, spDC, spD8;
    f32 spD4;
    f32 lim;
    f64 t;
    f32 sp88[4][4];
    u8 i2;
    u8 cnt2;
    s16 sp84;
    s8 sp83;
    u8 sp82;
    s16 v1;
    f32 sp7C, sp78, sp74;
    McA_V12 *q;
    McA_V12 *p;

    sp124 = MC->unkC;
    sp84 = D_807FBB40->unkE6;
    sp83 = 0;
    sp82 = (*MC->unk34 + MC->unk3F) & 0xFF3F;
    func_8067ACB4(D_807FBB40);
    if (MC->unk34 != NULL && sp124 == NULL) {
        D_807FBB40->unk144 = 0x24;
        sp128 = &D_807F5FD4[sp82][MC->unk10++];
        D_807FBB40->unk7C = sp128->x;
        sp128++;
        D_807FBB40->unk80 = sp128[-1].y;
        D_807FBB40->unk84 = sp128[-1].z;
        D_807FBB40->unkA4 = sp128[-1].y;
        D_807FBB40->unkE6 = mathAngleBetweenPoints2D(sp128->x, sp128->z, D_807FBB40->unk7C, D_807FBB40->unk84);
        D_807FBB40->unkE8 = (s16)(s32)(((f64)func_80611BB4(D_807FBB40->unk80 - sp128->y,
                                sqrtf((D_807FBB40->unk7C - sp128->x) * (D_807FBB40->unk7C - sp128->x) + (D_807FBB40->unk84 - sp128->z) * (D_807FBB40->unk84 - sp128->z))) * 2048.0) / 3.1415927410125732);
        MC->unkC = sp128 - 2;
        sfxPlayActorSound(D_807FBB40, 0x113, 0, 1, 0, 0xFF, 1.0f, 0);
        MC->unk41 = 1;
    }
    sp128 = &D_807F5FD4[sp82][MC->unk10];
    if (MC->unk10 >= 2) {
        sp124 = sp128 - 2;
    }
    if (D_807FBB40->unkB8 < 0.0f && D_807FBB40->unk7C == sp128[-1].x && D_807FBB40->unk84 == sp128[-1].z && MC->unk10 >= 2) {
        MC->unk10--;
        sp128--;
    }
    actorGetNodePos(D_807FBB40, 3, &spF4[0], &spF4[1], &spF4[2]);
    actorGetNodePos(D_807FBB40, 4, &sp100[0], &sp100[1], &sp100[2]);
    spD4 = (f64)(D_807FBB40->unk4->unk38 * D_807FBB40->unkB8) * 0.16666666675;
    if (D_8076A0A8 == 0x4D || D_8076A0A8 == 0x81 || D_8076A0A8 == 0x82) {
        spD4 = (f64)spD4 * 1.8;
    } else {
        if ((2.0 * (f64)func_80612794(D_807FBB40->unkE8)) + 1.0 < 0.6) {
            t = 0.6;
        } else {
            t = (2.0 * (f64)func_80612794(D_807FBB40->unkE8)) + 1.0;
        }
        spD4 = (f64)spD4 * (2.5 * t);
    }
    spEA = mathAngleBetweenPoints2D(sp128->x, sp128->z, sp128[-1].x, sp128[-1].z);
    if (MC->unk0 == 0) {
        D_80770B68[D_80770628[D_807FBB40->unk6E]] = ((f64)spD4 / 15.0) + 0.7;
    } else {
        D_80770B68[D_80770628[D_807FBB40->unk6E]] = 0.0f;
    }
    if (D_807FBB40->unkF0 != 0) {
        D_807FBB40->unkF0 = D_807FBB40->unkF0 - 1;
        mathPickCloserTargetPoint3D(spF4[0], spF4[1], spF4[2], sp128, sp128 + 1, sp128 + 1, sp128 + 2, &sp10C[0], &sp10C[1], &sp10C[2]);
        mathPickCloserTargetPoint3D(sp100[0], sp100[1], sp100[2], sp128 - 1, sp128, sp128, sp128 + 1, &sp118[0], &sp118[1], &sp118[2]);
    } else {
        mathPickCloserTargetPoint3D(spF4[0], spF4[1], spF4[2], sp128 - 1, sp128, sp128, sp128 + 1, &sp10C[0], &sp10C[1], &sp10C[2]);
        mathPickCloserTargetPoint3D(sp100[0], sp100[1], sp100[2], sp124, sp124 + 1, sp128 - 1, sp128, &sp118[0], &sp118[1], &sp118[2]);
    }
    D_807FBB40->unkE6 = func_806CC190(D_807FBB40->unkE6, (s16)(f32)mathAngleBetweenPoints2D(sp10C[0], sp10C[2], sp118[0], sp118[2]), 1.7f);
    diff = sqrtf((sp10C[0] - sp118[0]) * (sp10C[0] - sp118[0]) + (sp10C[2] - sp118[2]) * (sp10C[2] - sp118[2]));
    prev = D_807FBB40->unkE8;
    D_807FBB40->unkE8 = (s16)(s32)(((f64)func_80611BB4(sp118[1] - sp10C[1], diff) * 2048.0) / 3.1415927410125732);
    prev = prev - (f32)D_807FBB40->unkE8;
    if (prev > 2048.0f) {
        prev -= 4096.0f;
    }
    if (prev <= -2048.0f) {
        prev += 4096.0f;
    }
    if (prev > 25.0f) {
        cnt = 0;
        i = 0;
        do {
            if (D_807457E4[i] != 0) {
                cnt++;
            }
            i++;
        } while (i < 0x14);
        if (cnt < 5) {
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x20, 0xFF, 0x7F, 0x14);
        }
    }
    spE0 = func_80612794(spEA) * spD4 + D_807FBB40->unk7C;
    spD8 = func_80612790(spEA) * spD4 + D_807FBB40->unk84;
    spDC = D_807FBB40->unkA4;
    if (mathPickCloserTargetPoint3D(spE0, spDC, spD8, sp128 - 1, sp128, sp128, sp128 + 1, &D_807FBB40->unk7C, &D_807FBB40->unk80, &D_807FBB40->unk84) != 0) {
        MC->unk10++;
    }
    D_807FBB40->unk80 = D_807FBB40->unk80 + (f32)MC->unk0;
    n = D_807F5FD4[sp82 + 1] - D_807F5FD4[sp82];
    if (D_807F5FD0 == sp82 + 1) {
        limit = n - 1;
    } else {
        limit = n;
    }
    if (MC->unk10 >= limit) {
        MC->unk34++;
        if (*MC->unk34 == 0xFF) {
            D_807FBB40->unk154++;
        }
        if (D_807FD580->unk1FC != 0 && MC->unk4 == (void *)D_807FBB4C) {
            MC->unk3F = D_807FD580->unk1FC;
            D_807FD580->unk1FC = 0;
        } else if (D_8076A0A8 == 0x6A) {
            D_807FBB40->unkF0 = 0x1E;
            MC->unk2C = 0.0f;
            if (*MC->unk34 & 0x80) {
                MC->unk3F = (u32)MC->unk3F >> 1;
            } else if (!(*MC->unk34 & 0x40)) {
                MC->unk3F = 0;
            } else {
                MC->unk3F = MC->unk3F << 1;
            }
            if (MC->unk3F & 0x80) {
                MC->unk3F = 0;
            }
        } else {
            MC->unk3F = 0;
        }
        MC->unk10 = MC->unk41;
        MC->unkC = sp128 - 1;
        MC->unk41 = 1;
    }
    if (MC->unk2C != 0.0f) {
        q = &D_807F5FD4[(*MC->unk34 + MC->unk40) & 0x3F][MC->unk10];
        mathPickCloserTargetPoint3D(spE0, spDC, spD8, q - 1, q, q, q + 1, &sp7C, &sp78, &sp74);
        D_807FBB40->unk7C = D_807FBB40->unk7C + (sp7C - D_807FBB40->unk7C) * MC->unk2C;
        D_807FBB40->unk84 = D_807FBB40->unk84 + (sp74 - D_807FBB40->unk84) * MC->unk2C;
        MC->unk2C = (f64)MC->unk2C - 0.06;
        if (MC->unk2C < 0.0f) {
            MC->unk2C = 0.0f;
        }
    }
    sp12D = (MC->unk14 > 0.0f) ? 1 : ((MC->unk14 < 0.0f) ? -1 : 0);
    if (arg1 == 0x7FFF) {
        v1 = D_807FBB40->unkE6 - sp84;
        if (v1 >= 0x801) {
            v1 -= 0x1000;
        }
    } else {
        v1 = arg1;
    }
    if ((f64)arg2 < (f64)((f32)(v1 > 0 ? v1 : -v1) * spD4) * 0.25) {
        lim = (f64)arg2;
    } else {
        lim = (f64)((f32)(v1 > 0 ? v1 : -v1) * spD4) * 0.25;
    }
    MC->unk18 = (f64)MC->unk18 + (f64)(lim - MC->unk18) * 0.2;
    if (v1 >= 0x1F && v1 < 0x5A) {
        if (MC->unk14 < lim) {
            func_8002538C(arg0);
            MC->unk14 = MC->unk14 + MC->unk20;
            if (lim < MC->unk14) {
                MC->unk14 = lim;
            }
        }
    } else if (v1 < -0x1E && v1 >= -0x59) {
        if (-lim < MC->unk14) {
            func_8002538C(arg0);
            MC->unk14 = MC->unk14 - MC->unk20;
            if (MC->unk14 < -lim) {
                MC->unk14 = -lim;
            }
        }
    }
    if (MC->unk14 > 1.0f) {
        sp83 = 0x20;
        func_800241A0(arg0, 1, 0xE6);
    } else if (MC->unk14 < -1.0f) {
        sp83 = -0x20;
        func_800241A0(arg0, 0, 0xE6);
    } else {
        func_800241A0(arg0, D_8076A064 & 1, 0xFA);
        actorUpdateModelMatrix(D_807FBB40, 0);
    }
    if (sp83 != 0) {
        if (MC->unk18 < 10.0f) {
            MC->unk20 = 0.0f;
            if (MC->unk14 > 0.0f) {
                MC->unk14 = MC->unk14 - MC->unk1C;
                if (MC->unk14 < 0.0f) {
                    MC->unk14 = 0.0f;
                }
            } else if (MC->unk14 < 0.0f) {
                MC->unk14 = MC->unk14 + MC->unk1C;
                if (MC->unk14 > 0.0f) {
                    MC->unk14 = 0.0f;
                }
            }
            t = (f64)MC->unk1C + 0.5;
            MC->unk1C = (t < 10.0) ? t : 10.0;
        } else {
            MC->unk1C = 0.0f;
            cnt2 = 0;
            i2 = 0;
            do {
                if (D_807457E4[i2] != 0) {
                    cnt2++;
                }
                i2++;
            } while (i2 < 0x14);
            if (cnt2 < 5) {
                sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x21, 0xFF, 0x7F, 0x14);
            }
        }
        guTranslateF(D_807FBB40->unkC, (f32)sp83, 0.0f, 0.0f);
        matrixMakeRotationZ(sp88, MC->unk14);
        guMtxCatF(D_807FBB40->unkC, sp88, D_807FBB40->unkC);
        guTranslateF(sp88, (f32)-sp83, 0.0f, 0.0f);
        guMtxCatF(D_807FBB40->unkC, sp88, D_807FBB40->unkC);
        actorUpdateModelMatrix(D_807FBB40, 1);
        lim = (MC->unk14 > 0.0f) ? MC->unk14 : -MC->unk14;
        if ((f32)MC->unk39 < lim) {
            if (MC->unk14 > 0.0f) {
                MC->unk39 = MC->unk14;
            } else {
                MC->unk39 = -MC->unk14;
            }
        }
    }
    if (((MC->unk14 > 0.0f) ? 1 : ((MC->unk14 < 0.0f) ? -1 : 0)) != sp12D) {
        if (MC->unk39 != 0 && MC->unk0 == 0) {
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x8B, ((MC->unk39 / arg2) * 0x7F + 0x80) & 0xFF, 0x7F, 0x1E);
            MC->unk39 = 0;
        }
    }
    func_80665564(D_807FBB40, 0);
}

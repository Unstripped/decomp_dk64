// func_80603450 (src/global/7130.c): Stage 3/4, 1454-insn audio frame update, regalloc/frame size 0x100 vs 0xE8
typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    u8 unkA;
    u8 unkB;
    u8 unkC;
    u8 unkD;
} Aud7130L2_Struct0;

typedef struct {
    s16 unk0;
    u8 unk2;
    u8 unk3;
    f32 unk4;
    f32 unk8;
} Aud7130L2_Struct1;

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    u8 unk6;
    u8 unk7;
} Aud7130L2_Emitter;

typedef struct {
    char pad[0x1F0];
    u32 unk1F0;
} Aud7130L2_D580;

extern Aud7130L2_Struct0 D_80745F74[];
extern Aud7130L2_Struct0 D_80745FD8[];
extern Aud7130L2_Struct0 D_80746010[];
extern Aud7130L2_Struct0 D_8074603C[];
extern Aud7130L2_Struct0 D_80746074[];
extern Aud7130L2_Struct0 D_807460AC[];
extern Aud7130L2_Struct0 D_807460E4[];
extern Aud7130L2_Struct0 D_80746170[];
extern Aud7130L2_Struct0 D_807461E0[];
extern Aud7130L2_Struct0 D_80746244[];
extern Aud7130L2_Struct0 D_8074627C[];

extern Aud7130L2_Struct1 D_80745B28[];
extern u8 D_80745BDC[][4];

extern u32 D_80767CC0;
extern s32 D_8076D1F8;
extern s32 D_8076D1FC;
extern s32 D_807457DC;
extern u8 D_80745838;
extern u8 D_8077058C[];
extern u8 D_8077058D;
extern u8 D_8077058E;
extern u8 D_80770DC8;
extern u8 D_80770DC9;
extern u8 D_80770DCA;
extern u8 D_80770DCB;
extern f32 D_80770DCC;
extern f32 D_80770DD0;
extern f32 D_80770DD4;
extern u8 D_80770DD9;
extern f32 D_80770DE4;
extern f32 D_80770DE8;
extern f32 D_80770DEC;
extern f32 D_80770DF0;
extern f32 D_80770DF4;
extern s32 D_80770DF8[];
extern u32 D_80770E38[];
extern f32 D_80770E78[];
extern f32 D_80770EB8[];
extern f32 D_80770EF8[];
extern u32 D_807FBB60;
extern Aud7130L2_D580 *D_807FD580;

s32 func_8062F388(Aud7130L2_Emitter **);
void func_80664044(s32, s32, s32, f32);
s32 flagGet(s32, s32);
void n_alSndpPostEvent(s32, s32, ...);
f32 func_80611BB4(f32, f32);
f32 func_80612D1C(f32);
f32 mathAngleBetweenPointsRad(f32, f32, f32, f32);
void n_alSndpPlay(s32, s16, s32, s32, f32, s32, s32 *);
void n_alSndpStop(s32);
void func_8060A634(s32, f32);

void func_80603450(void) {
    s8 spE7;
    u8 spE5;
    f32 spCC;
    s32 spC8;
    Aud7130L2_Struct0 *spC0;
    Aud7130L2_Emitter *spBC;
    s32 var_s1;
    s16 s2;
    s16 s0;
    f32 var_fs0;
    f32 var_fs1;

    spE7 = -1;
    spE5 = 0;

    switch (D_8076A0A8) {
    case 7:
        spC0 = D_80745F74;
        var_s1 = 7;
        break;
    case 0x26:
        spC0 = D_80745FD8;
        var_s1 = 4;
        break;
    case 0x1E:
        spC0 = D_80746010;
        var_s1 = 3;
        break;
    case 0x27:
        spC0 = D_8074603C;
        var_s1 = 4;
        break;
    case 0x1A:
        spC0 = D_80746074;
        var_s1 = 4;
        break;
    case 0xE:
        spC0 = D_807460AC;
        var_s1 = 4;
        break;
    case 0x1B:
        spC0 = D_807460E4;
        var_s1 = 10;
        break;
    case 0x37:
        spC0 = D_807461E0;
        var_s1 = 7;
        break;
    case 0x22:
        spC0 = D_80746244;
        var_s1 = 4;
        break;
    case 0xB0:
        var_s1 = 3;
        spC0 = D_8074627C;
        break;
    case 0x30:
        spC0 = D_80746170;
        var_s1 = 8;
        if (D_807FD580->unk1F0 & 0x100000) {
            func_80602B60(0x46, 0);
            if (func_80602D4C(0x44) < 0.1) {
                func_80602A94(0x46, 1.0f);
            }
        } else {
            func_80602B60(0x44, 0);
            if (func_80602D4C(0x46) < 0.1) {
                func_80602A94(0x44, 1.0f);
            }
        }
        break;
    default:
        var_s1 = 0;
        break;
    }

    if (var_s1 != 0 && D_80745650 != 0 && (s0 = 0, D_80745654 == 0)) {
        D_80770DD4 = 1000000.0f;
        var_fs1 = 0.0f;
        if (var_s1 > 0) {
            do {
                Aud7130L2_Struct0 *entry = &spC0[s0];
                if (entry->unk6 == -1) {
                    D_80770DE4 = sqrtf((D_807FC924->unk210 - (f32)entry->unk0) * (D_807FC924->unk210 - (f32)entry->unk0) + (D_807FC924->unk218 - (f32)entry->unk4) * (D_807FC924->unk218 - (f32)entry->unk4));
                    if (D_80770DE4 < (f32)(entry->unk8 - 20)) {
                        func_80602A94(entry->unkB, 1.0f);
                    } else if (D_80770DE4 > (f32)entry->unk8) {
                        func_80602B60(entry->unkB, 0);
                    }
                } else {
                    D_80770DE4 = sqrtf((D_807FC924->unk210 - (f32)entry->unk0) * (D_807FC924->unk210 - (f32)entry->unk0) + (D_807FC924->unk214 - (f32)entry->unk2) * (D_807FC924->unk214 - (f32)entry->unk2) + (D_807FC924->unk218 - (f32)entry->unk4) * (D_807FC924->unk218 - (f32)entry->unk4));
                    if (s0 == 0 || D_80770DE4 < D_80770DD4) {
                        spE7 = s0;
                        D_80770DD4 = D_80770DE4;
                        var_fs0 = ((f64)func_80611BB4(D_807FC924->unk210 - (f32)entry->unk0, D_807FC924->unk218 - (f32)entry->unk4) * 4096.0) / 6.2831854820251465 - (f64)entry->unk6;
                    }
                }
                s0++;
                D_80770DE8 = 32767.0f - (D_80770DE4 - 50.0f) * 120.0f;
                if (D_80770DE8 > 32767.0f) {
                    D_80770DE8 = 32767.0f;
                }
                if (D_80770DE8 < 0.0f) {
                    D_80770DE8 = 0.0f;
                }
                var_fs1 += D_80770DE8;
            } while (s0 < var_s1);
        }
        D_80770DE4 = D_80770DD4;
        if (spE7 >= 0 && D_80770DE4 < (f32)spC0[spE7].unk8) {
            Aud7130L2_Struct0 *closest = &spC0[spE7];
            if (closest->unk6 >= 0x1001) {
                D_80770DC9 = closest->unk6 & 1;
            } else {
                if (var_fs0 > 2048.0f) {
                    var_fs0 -= 4096.0f;
                }
                if (var_fs0 < -2048.0f) {
                    var_fs0 += 4096.0f;
                }
                if (var_fs0 < 1024.0f && var_fs0 > -1024.0f) {
                    if (D_80770DCB != 0) {
                        D_80770DC9 = 1;
                    }
                } else {
                    D_80770DCB = 1;
                    D_80770DC9 = 0;
                    func_80602A94(closest->unkC, 1.0f);
                }
            }
            if (D_80770DC9 != 0) {
                D_80770DC8 = closest->unkA;
            } else {
                D_80770DC8 = 0;
            }
            D_80770DD9 = closest->unkB;
        } else {
            D_80770DCB = 0;
        }
        if (D_80745838 != 0) {
            var_fs1 = 0.0f;
        } else if (D_80770DC9 != 0) {
            var_fs1 = 32767.0f;
        } else {
            if (var_fs1 > 32767.0f) {
                var_fs1 = 32767.0f;
            }
            if (var_fs1 < 500.0f) {
                var_fs1 = 0.0f;
            }
        }
        if (D_80770DD9 == 0xFF) {
            Aud7130L2_Struct0 *closest = &spC0[spE7];
            D_80770DD9 = closest->unkB;
            D_80770DC8 = closest->unkA;
            if (D_80770DC9 == 0) {
                func_80602A94(closest->unkC, 1.0f);
            }
        }
        if (D_80770DC9 != 0 && D_80770DD9 != 0) {
            func_80602A94(D_80770DD9, 1.0f);
        } else if (D_80745838 != 0) {
            func_8060A60C(0, 1.0f);
        } else {
            func_80602B60(D_80770DD9, 0);
        }
        D_80770DCA = D_80770DC9;
        if (var_fs1 != 0.0f) {
            if (spC0[spE7].unkD != 0) {
                func_80602A94(spC0[spE7].unkD, 1.0f);
            }
        }
        if (D_80770560[2] == 0x26) {
            func_8060A634(2, (f32)((f64)var_fs1 / 32767.0));
        }
        var_fs1 = ((var_fs1 - 28384.0f) * 100.0f) / 4383.0f;
        if (var_fs1 < 0.0f) {
            var_fs1 = 0.0f;
        }
        D_8077058E = (u8)(u32)(f32)((((255.0 - (f64)(u32)D_80745BDC[D_8076A0A8][1]) * ((f64)(u32)D_80770DC8 / 127.0) * (f64)var_fs1) / 255.0) + (f64)(u32)D_80745BDC[D_8076A0A8][1]);
    } else {
        D_8077058E = D_80745BDC[D_8076A0A8][1];
    }

    if (D_80745838 != 0) {
        D_8077058E = 0xFF;
    }

    if (D_8077058D != D_8077058E) {
        f64 v = (f64)(u32)D_8077058E;
        f32 pan = (f32)((v * 0.3) / 255.0);
        f32 vol = (f32)(((v * 0.35) / 255.0) + 1.0);
        if (D_8076A0A8 == 0xE) {
            if (D_8077058E != 0) {
                func_8060A634(0, 1.0f);
            } else {
                func_8060A634(0, 0.6f);
            }
            alCSPSetChlPan(gSeqPlayers[0], pan, vol);
        }
        for (s0 = 0; s0 < 4; s0++) {
            if (D_80745658[D_80770560[s0]] & 1) {
                alCSPSetChlPan(gSeqPlayers[s0], pan, vol);
            } else {
                alCSPSetChlPan(gSeqPlayers[s0], 0.0f, 1.0f);
            }
        }
        D_8077058D = D_8077058E;
    }

    spC8 = func_8062F388(&spBC);
    for (s2 = 0; s2 < 15; s2++) {
        D_80770DE8 = 0.0f;
        D_80770DEC = 0.0f;
        D_80770DF0 = 0.0f;
        D_80770DF4 = 0.0f;
        if ((D_807FBB60 & 2) || !(D_807FBB60 & 0x10)) {
            var_fs1 = 0.0f;
        } else {
            if (s2 == 11 && flagGet(0x302, 0)) {
                var_fs1 = 0.0f;
            } else if (s2 == 13 && flagGet(0x4C, 0)) {
                var_fs1 = 0.0f;
            } else {
                if (s2 == 1) {
                    func_80664044(1, 0xFF, 0xC8, 0.3f);
                }
                for (s0 = spC8 - 1; s0 >= 0; s0--) {
                    if (s2 + 1 == spBC[s0].unk7) {
                        func_80603340((f32)spBC[s0].unk0, (f32)spBC[s0].unk2, (f32)spBC[s0].unk4,
                            (u8)((D_80745B28[s2].unk2 * spBC[s0].unk6) / 255.0),
                            D_80745B28[s2].unk3, D_80745B28[s2].unk4);
                    }
                }
                var_fs1 = D_80770DE8 + D_80770DEC;
                if (var_fs1 > 32767.0f) {
                    var_fs1 = 32767.0f;
                }
                if (var_fs1 < 500.0f) {
                    var_fs1 = 0.0f;
                }
            }
        }
        if (D_80745B28[s2].unk0 == 0x1E) {
            u32 timer = D_80767CC0 / 12U;
            var_fs1 = (f32)((f64)var_fs1 * 0.6);
            if (timer != D_80770E38[s2]) {
                D_80770E38[s2] = timer;
                if (var_fs1 > 10.0f) {
                    n_alSndpPlay(D_8076D1F8, 0x1E, (u16)var_fs1, 0x3F, 0.4f, 0, &D_80770DF8[s2]);
                    D_80770EB8[s2] = var_fs1 + 1.0f;
                    D_80770EF8[s2] = 300.0f;
                }
            }
        }
        if (var_fs1 != D_80770EB8[s2] || D_80770DF8[s2] == 0) {
            if (var_fs1 > 10.0f) {
                if (D_80770DF8[s2] == 0) {
                    if (D_80745B28[s2].unk0 < 0x800) {
                        n_alSndpPlay(D_8076D1F8, D_80745B28[s2].unk0, (u16)var_fs1, 0x3F, D_80745B28[s2].unk8, 0, &D_80770DF8[s2]);
                    } else {
                        n_alSndpPlay(D_8076D1FC, D_80745B28[s2].unk0 - 0x7FF, (u16)var_fs1, 0x3F, D_80745B28[s2].unk8, 0, &D_80770DF8[s2]);
                    }
                    D_80770E78[s2] = 0.0f;
                    D_80770EF8[s2] = 255.0f;
                }
                if (D_80770DF8[s2] != 0) {
                    n_alSndpPostEvent(D_80770DF8[s2], 8, (s32)var_fs1);
                }
                if (D_80770DF0 < D_80770DF4) {
                    spE5 = 0x80;
                }
                if (D_80770DF8[s2] != 0) {
                    n_alSndpPostEvent(D_80770DF8[s2], 0x100, (s32)spE5);
                }
            } else if (D_80770DF8[s2] != 0) {
                n_alSndpStop(D_80770DF8[s2]);
            }
            D_80770EB8[s2] = var_fs1;
        }
        if (D_80770DF8[s2] != 0) {
            if (D_80770DE8 > 32767.0f) {
                D_80770DE8 = 32767.0f;
            }
            if (D_80770DEC > 32767.0f) {
                D_80770DEC = 32767.0f;
            }
            if (D_80770DEC < D_80770DE8) {
                if (D_80770DE8 > 0.0f) {
                    var_fs0 = (f32)(127.0 - (((f64)D_80770DEC * 63.5) / (f64)D_80770DE8));
                } else {
                    var_fs0 = 0.0f;
                }
            } else if (D_80770DEC > 0.0f) {
                var_fs0 = (f32)(((f64)D_80770DE8 * 63.5) / (f64)D_80770DEC);
            } else {
                var_fs0 = 0.0f;
            }
            if (D_80745838 != 0) {
                spCC = (f32)((f64)D_80745B28[s2].unk8 * 0.5);
            } else if (D_80770DC9 != 0 && D_80745B28[s2].unk0 == 0x106) {
                spCC = (f32)(1.0 / (((f64)D_80770DD4 / 800.0) + 1.0));
            } else {
                spCC = D_80745B28[s2].unk8;
            }
            if (var_fs0 != D_80770EF8[s2]) {
                if (D_80770EF8[s2] != 255.0f) {
                    if (D_80770EF8[s2] < var_fs0) {
                        f32 t = D_80770EF8[s2] + 8.0f;
                        if (t < var_fs0) {
                            var_fs0 = t;
                        }
                    } else {
                        f32 t = D_80770EF8[s2] - 8.0f;
                        if (var_fs0 < t) {
                            var_fs0 = t;
                        }
                    }
                }
                n_alSndpPostEvent(D_80770DF8[s2], 4, (s32)var_fs0);
                D_80770EF8[s2] = var_fs0;
            }
            if (spCC != D_80770E78[s2]) {
                n_alSndpPostEvent(D_80770DF8[s2], 0x10, *(s32 *)&spCC);
                D_80770E78[s2] = spCC;
            }
        }
    }

    if ((D_807FBB60 & 2) || !(D_807FBB60 & 0x10)) {
        D_8077058C[0] = 0;
    }
    if (D_8077058C[0] != 0) {
        if (D_807457DC == 0) {
            n_alSndpPlay(D_8076D1F8, 0x125, 0, 0x3F, 1.0f, 0, &D_807457DC);
        }
        if (D_807457DC != 0) {
            n_alSndpPostEvent(D_807457DC, 8, (s32)(((f64)(u32)D_8077058C[0] * 10767.0) / 255.0));
            spCC = (f32)(1.0 - (((f64)(u32)D_8077058E * 0.5) / 255.0));
            if (D_80770DC9 & (D_80770DD4 < 1000.0f)) {
                Aud7130L2_Struct0 *s0 = &spC0[spE7];
                var_fs0 = mathAngleBetweenPointsRad(D_807FC924->unk210, D_807FC924->unk218, (f32)s0->unk0, (f32)s0->unk4) - D_807FC924->unk2C4;
                if (var_fs0 < 0.0f) {
                    var_fs0 += 6.2831855f;
                }
                if (var_fs0 > 1.5707964f && (f64)var_fs0 < 4.71238911151886) {
                    D_80770DD0 = 128.0f;
                } else {
                    D_80770DD0 = 0.0f;
                }
                D_80770DCC = (f32)((f64)(1.0f - func_80612D1C(var_fs0)) * 63.5);
            } else {
                D_80770DCC = 64.0f;
            }
            n_alSndpPostEvent(D_807457DC, 0x10, *(s32 *)&spCC);
            n_alSndpPostEvent(D_807457DC, 0x100, (s32)D_80770DD0);
            n_alSndpPostEvent(D_807457DC, 4, (s32)D_80770DCC);
        }
    } else if (D_807457DC != 0) {
        n_alSndpStop(D_807457DC);
    }
}

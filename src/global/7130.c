#define alCSPSetChlPan alCSPSetChlPan_unused
#include "common.h"
#undef alCSPSetChlPan
#include "actor.h"

void alCSPSetChlPan(ALCSPlayer *, f32, f32);

extern u16 D_80745658[];

u8 func_80602430(arg0)
s16 arg0;
{
    return (D_80745658[arg0] & 6) >> 1;
}

u8 func_8060245C(arg0)
s16 arg0;
{
    return (D_80745658[arg0] & 0x78) >> 3;
}

extern u8 D_80745654;
void func_80602488(arg0)
u8 arg0;
{
    D_80745654 = arg0;
}

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    u8 unk8;
    u8 unk9;
} Aud7130A2_Struct7130_Entry;

typedef struct AudPlayer {
    u8 unk0;
    char pad1[0x20F];
    f32 unk210;
    f32 unk214;
    f32 unk218;
    char pad21C[0xC];
    f32 unk228;
    f32 unk22C;
    f32 unk230;
    char pad234[0x90];
    f32 unk2C4;
    char pad2C8[0x28];
} AudPlayer;

extern s8 D_80745650;
extern u8 D_80770DC9;
extern u8 D_80770DD8[];
extern AudPlayer *D_807FC924;
extern s32 D_8076A0A8;
extern Aud7130A2_Struct7130_Entry D_807459FC[];

s16 func_806531B8(f32, f32, f32, s32);
void func_80602A94(s32, f32);
#ifdef NON_MATCHING
void func_80602498(void) {
    Aud7130A2_Struct7130_Entry *entry;
    s16 count;
    s16 v0;
    u8 i;

    D_80745650 = 1;
    if (D_80745654 != 0) {
        if (D_80770DD8[1] == 0xFF) {
            D_80770DD8[1] = 0;
        }
        return;
    }

    count = 29;
    v0 = func_806531B8(D_807FC924->unk210, D_807FC924->unk214, D_807FC924->unk218, 0);

    i = 0; do {
        entry = &D_807459FC[i];
        if (D_8076A0A8 == entry->unk0 && v0 == entry->unk2) {
            D_80770DC9 = entry->unk8;
            func_80602A94(entry->unk4, 1.0f);
            if (entry->unk6 != 0) {
                count = entry->unk6;
                D_80770DD8[1] = count;
            }
            return;
        }
    } while (++i < count);

    D_80770DD8[1] = 0xFF;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/7130/func_80602498.s")
#endif
void func_80602498(void);
void func_806025AC(u8 arg0, u8 arg1, u8 arg2) {
    func_80602498();
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/7130/func_806025D4.s")

extern s16 D_807458DC[];
extern f32 D_807458F4[];
extern s16 D_80745924[];
extern s32 D_8074593C[][12];

void func_80602A94(s32 arg0, f32 arg1) {
    u8 v0;
    u8 i;
    s32 v1;

    v0 = func_8060245C((s16)arg0);
    if (arg0 != 0) {
        v1 = D_807458DC[v0];
        if (arg0 == v1 && (D_80745658[arg0] & 0x200) == 0) {
            return;
        }
        D_807458DC[v0] = arg0;
        D_807458F4[v0] = arg1;
        D_80745924[v0] = 0;
        for (i = 0; i < 4; i++) {
            D_8074593C[i][v0] = 0;
        }
    }
}

extern u8 D_80770560[];
extern ALCSPlayer *gSeqPlayers[];
void func_80602B60(arg0, arg1)
s32 arg0;
u8 arg1;
{
    u8 v1 = func_8060245C((s16)arg0);
    u8 v0 = func_80602430((s16)arg0);
    if (arg0 != 0 && arg0 == D_807458DC[v1]) {
        D_807458DC[v1] = 0;
        D_80745924[v1] = 0;
        if (arg1 != 0) {
            if (arg0 == D_80770560[v0]) {
                alSeqpStop((ALSeqPlayer *)gSeqPlayers[v0]);
            }
        }
    }
}

void func_80602C0C(void) {
    u8 i;
    for (i = 0; i < 12; i++) {
        if (D_807458DC[i] != 0) {
            func_80602B60(D_807458DC[i], 1);
        }
    }
}


void func_8060A60C(s32, f32);

void func_80602C6C(s32 arg0, f32 arg1) {
    u8 v1 = func_80602430((s16)arg0);
    if ((arg0 == D_807458DC[func_8060245C((s16)arg0)]) && (arg0 == D_80770560[v1])) {
        func_8060A60C(v1, arg1);
    }
}



void func_80602CE0(arg0, arg1, arg2)
s32 arg0;
s32 arg1;
u8 arg2;
{
    s16 a = arg0;
    s32 temp = func_8060245C(a);
    if (arg0 == D_807458DC[temp]) {
        D_8074593C[arg2][temp] = arg1;
    }
}

extern f32 D_80770568[];

f32 func_80602D4C(arg0)
s32 arg0;
{
    s16 a = arg0;
    u8 v0 = func_80602430(a);
    if (arg0 == D_80770560[v0]) {
        if (alCSPGetState(gSeqPlayers[v0]) == 1) {
            return D_80770568[v0];
        }
    }
    return 0.0f;
}

void func_80602DC4(s32 arg0, f32 arg1) {
    u8 v1 = func_80602430((s16)arg0);
    if ((arg0 == D_807458DC[func_8060245C((s16)arg0)]) && (arg0 == D_80770560[v1])) {
        alCSPSetTempo(gSeqPlayers[v1], (s32)((s32)alCSPGetSeq(gSeqPlayers[v1]) * arg1));
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/7130/func_80602E6C.s")

f32 func_80602E6C(f32, f32, f32, u8, u8, f32);
extern f32 D_80770DDC;
extern f32 D_80770DE0;
extern f32 D_80770DE8;
extern f32 D_80770DEC;
extern f32 D_80770DF0;
extern f32 D_80770DF4;

f32 func_80603340(f32 arg0, f32 arg1, f32 arg2, u8 arg3, u8 arg4, f32 arg5)
{
    f32 ret;
    f32 temp;

    ret = func_80602E6C(arg0, arg1, arg2, arg3, arg4, arg5);
    if (ret < 10.0f) {
        return 0.0f;
    }

    temp = (f32)((f64)D_80770DDC * 0.00787401574803149595);
    D_80770DE8 += ret * temp;
    D_80770DEC += ret * (1.0f - temp);

    if (D_80770DE0 > 0.0f) {
        D_80770DF0 += ret * D_80770DE0;
    }
    if (D_80770DE0 < 0.0f) {
        D_80770DF4 -= ret * D_80770DE0;
    }

    return ret;
}

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
extern u8 D_80770DCA;
extern u8 D_80770DCB;
extern f32 D_80770DCC;
extern f32 D_80770DD0;
extern f32 D_80770DD4;
extern u8 D_80770DD9;
extern f32 D_80770DE4;
extern s32 D_80770DF8[];
extern u32 D_80770E38[];
extern f32 D_80770E78[];
extern f32 D_80770EB8[];
extern f32 D_80770EF8[];
extern u32 D_807FBB60;
extern Aud7130L2_D580 *D_807FD580;

s32 func_8062F388(Aud7130L2_Emitter **);
void func_80664044(s32, s32, s32, f32);
s32 func_8073110C(s32, s32);
void func_80737AC4(s32, s32, ...);
f32 func_80611BB4(f32, f32);
f32 func_80612D1C(f32);
f32 mathAngleBetweenPointsRad(f32, f32, f32, f32);
void n_alSndpAllocate(s32, s16, s32, s32, f32, s32, s32 *);
void n_alSndpDeallocate(s32);
void func_8060A634(s32, f32);

#ifdef NON_MATCHING
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
            if (s2 == 11 && func_8073110C(0x302, 0)) {
                var_fs1 = 0.0f;
            } else if (s2 == 13 && func_8073110C(0x4C, 0)) {
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
                    n_alSndpAllocate(D_8076D1F8, 0x1E, (u16)var_fs1, 0x3F, 0.4f, 0, &D_80770DF8[s2]);
                    D_80770EB8[s2] = var_fs1 + 1.0f;
                    D_80770EF8[s2] = 300.0f;
                }
            }
        }
        if (var_fs1 != D_80770EB8[s2] || D_80770DF8[s2] == 0) {
            if (var_fs1 > 10.0f) {
                if (D_80770DF8[s2] == 0) {
                    if (D_80745B28[s2].unk0 < 0x800) {
                        n_alSndpAllocate(D_8076D1F8, D_80745B28[s2].unk0, (u16)var_fs1, 0x3F, D_80745B28[s2].unk8, 0, &D_80770DF8[s2]);
                    } else {
                        n_alSndpAllocate(D_8076D1FC, D_80745B28[s2].unk0 - 0x7FF, (u16)var_fs1, 0x3F, D_80745B28[s2].unk8, 0, &D_80770DF8[s2]);
                    }
                    D_80770E78[s2] = 0.0f;
                    D_80770EF8[s2] = 255.0f;
                }
                if (D_80770DF8[s2] != 0) {
                    func_80737AC4(D_80770DF8[s2], 8, (s32)var_fs1);
                }
                if (D_80770DF0 < D_80770DF4) {
                    spE5 = 0x80;
                }
                if (D_80770DF8[s2] != 0) {
                    func_80737AC4(D_80770DF8[s2], 0x100, (s32)spE5);
                }
            } else if (D_80770DF8[s2] != 0) {
                n_alSndpDeallocate(D_80770DF8[s2]);
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
                func_80737AC4(D_80770DF8[s2], 4, (s32)var_fs0);
                D_80770EF8[s2] = var_fs0;
            }
            if (spCC != D_80770E78[s2]) {
                func_80737AC4(D_80770DF8[s2], 0x10, *(s32 *)&spCC);
                D_80770E78[s2] = spCC;
            }
        }
    }

    if ((D_807FBB60 & 2) || !(D_807FBB60 & 0x10)) {
        D_8077058C[0] = 0;
    }
    if (D_8077058C[0] != 0) {
        if (D_807457DC == 0) {
            n_alSndpAllocate(D_8076D1F8, 0x125, 0, 0x3F, 1.0f, 0, &D_807457DC);
        }
        if (D_807457DC != 0) {
            func_80737AC4(D_807457DC, 8, (s32)(((f64)(u32)D_8077058C[0] * 10767.0) / 255.0));
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
            func_80737AC4(D_807457DC, 0x10, *(s32 *)&spCC);
            func_80737AC4(D_807457DC, 0x100, (s32)D_80770DD0);
            func_80737AC4(D_807457DC, 4, (s32)D_80770DCC);
        }
    } else if (D_807457DC != 0) {
        n_alSndpDeallocate(D_807457DC);
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/7130/func_80603450.s")
#endif

extern ALCSPlayer *D_8076BF24;

void func_80602CE0();

void func_806049CC(s32 arg0) {
    if (D_80745838 != 0) {
        if (arg0 == 0 && (D_80745658[D_80770560[arg0]] & 1)) {
            alCSPSetChlPan(gSeqPlayers[0], 0.3f, 1.35f);
        }
        if (D_80770560[arg0] == 0x38) {
            func_80602CE0(0x38, 0x3C00, 1);
        }
        if (D_80770560[arg0] == 0x60) {
            if (D_8076A0A8 == 0xB8) {
                func_80602CE0(0x60, 0xE, 1);
            } else {
                func_80602CE0(0x60, 8, 1);
                alCSPSetChlVol(D_8076BF24, 1, 0x7F);
                alCSPSetChlVol(D_8076BF24, 2, 0x7F);
            }
            func_80602CE0(0x60, 0x10, 0);
        }
    } else {
        if (arg0 == 0 && (D_80745658[D_80770560[arg0]] & 1)) {
            alCSPSetChlPan(gSeqPlayers[0], 0.0f, 1.0f);
        }
        if (D_80770560[arg0] == 0x38) {
            func_80602CE0(0x38, 0x3C00, 0);
        }
        if (D_80770560[arg0] == 0x60) {
            if (D_8076A0A8 == 0xB8) {
                func_80602CE0(0x60, 0x1E, 1);
                return;
            }
            func_80602CE0(0x60, 0x10, 1);
            func_80602CE0(0x60, 8, 0);
            alCSPSetChlVol(D_8076BF24, 1, 0x64);
            alCSPSetChlVol(D_8076BF24, 2, 0x64);
        }
    }
}

extern s16 D_80770628[];
extern f32 D_80770B68[];
extern f32 D_80770BC0[];
extern f32 D_80770C18[];
extern f32 D_80770C70[];

void func_80604BE8(u8 arg0, f32 arg1, f32 arg2) {
    s32 temp;
    s32 var_v0;

    if (arg0 != -1) {
        if (arg2 == 0.0f) {
            temp = D_80770628[arg0] * 4;
            *(f32 *)((u8 *)D_80770C18 + temp) = arg1;
            var_v0 = temp;
            *(f32 *)((u8 *)D_80770C70 + temp) = arg1;
        } else {
            temp = D_80770628[arg0] * 4; *(f32 *)((u8 *)D_80770B68 + temp) = arg1; var_v0 = temp;
        } *(f32 *)((u8 *)D_80770BC0 + var_v0) = arg2;
    }
}

extern u8 D_80770CE0[];

void func_80604C80(arg0, arg1)
u8 arg0;
u8 arg1;
{
    if (arg0 != -1) {
        D_80770CE0[D_80770628[arg0]] = arg1;
    }
}

typedef struct Aud7130B_Actor {
    char pad0[0x6E];
    s16 unk6E[2];
    s16 unk72;
} Aud7130B_Actor;

extern s16 D_80770710[];

u8 func_80604D70(Actor *, s16, u8, u8, u8, f32, s8);
void func_80605314(Actor *, u8);

void func_80604CBC(Actor *arg0, s16 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, f32 arg6, s8 arg7) {
    if (((Aud7130B_Actor *)arg0)->unk6E[arg4] != -1) {
        if (arg1 == D_80770710[D_80770628[((Aud7130B_Actor *)arg0)->unk6E[arg4]]]) {
            return;
        }
        func_80605314(arg0, arg4);
    }
    ((Aud7130B_Actor *)arg0)->unk6E[arg4] = func_80604D70(arg0, arg1, arg2, arg3, arg5, arg6, arg7);
}
extern s32 D_80745848[];
extern u8 D_807460AE[][2];
extern s16 D_80770658[];
extern u8 D_807706E0[];
extern u8 D_807706F8[];
extern s16 D_80770740[];
extern u8 D_80770788[];
extern s16 D_807707A0[][22];
extern u8 D_80770CC8[];
extern s8 D_80770CF8[];
extern s16 D_80770D10[];
extern s16 D_80770D40[];
extern f32 D_80770D70[];
extern void *D_807705A0[];

u8 func_80604D70(Actor *arg0, s16 arg1, u8 arg2, u8 arg3, u8 arg4, f32 arg5, s8 arg6) {
    u8 i;
    u8 j;
    s16 temp_a0;

    for (i = 0; i < 22; i++) {
        if (D_80770628[i] == -1) {
            break;
        }
    }
    if (i == 22) {
        return 0xFF;
    }

    if (arg3 != 0) {
        j = 22;
    } else {
        for (j = 0; j < 22; j++) {
            if (D_807706F8[j] == 0 && D_80770710[j] == arg1) {
                break;
            }
        }
    }

    if (j == 22) {
        for (j = 0; j < 22; j++) {
            if (D_80770710[j] == 0 && D_80745848[j] == 0) {
                break;
            }
        }
        if (j == 22) {
            return 0xFF;
        }
        D_80770710[j] = arg1;
        D_807706F8[j] = arg3;
        D_80770C18[j] = arg5;
        D_80770C70[j] = arg5;
        D_80770B68[j] = 1.0f;
        D_80770BC0[j] = 0.0f;
        D_80770CC8[j] = 0;
    }

    if (arg2 != 0) {
        D_80770788[i] = arg2;
    } else {
        D_80770788[i] = D_807460AE[D_80770710[j]][0];
    }
    D_80770CE0[j] = arg4;
    D_80770D10[j] = -1;
    D_80770D70[j] = arg5;
    D_80770D40[j] = -1;
    D_80770CF8[j] = arg6;
    D_807706E0[j] = 0;
    temp_a0 = D_80770740[j];
    D_80770628[i] = j;
    D_80770658[i] = temp_a0;
    D_807707A0[j][temp_a0] = i;
    D_80770740[j] = temp_a0 + 1;
    D_807705A0[i] = arg0;
    return i;
}
extern s16 D_807705F8[];

u8 func_80605044(s16 arg0, s16 arg1, u8 arg2, u8 arg3, u8 arg4, f32 arg5, s8 arg6) {
    u8 i;
    u8 j;
    s16 temp_a0;

    for (i = 0; i < 22; i++) {
        if (D_80770628[i] == -1) {
            break;
        }
    }
    if (i == 22) {
        return 0xFF;
    }

    if (arg3 != 0) {
        j = 22;
    } else {
        for (j = 0; j < 22; j++) {
            if (D_807706F8[j] == 0 && D_80770710[j] == arg1) {
                break;
            }
        }
    }

    if (j == 22) {
        for (j = 0; j < 22; j++) {
            if (D_80770710[j] == 0 && D_80745848[j] == 0) {
                break;
            }
        }
        if (j == 22) {
            return 0xFF;
        }
        D_80770710[j] = arg1;
        D_807706F8[j] = arg3;
        D_80770C18[j] = arg5;
        D_80770C70[j] = arg5;
        D_80770B68[j] = 1.0f;
        D_80770BC0[j] = 0.0f;
        D_80770CC8[j] = 0;
    }

    if (arg2 != 0) {
        D_80770788[i] = arg2;
    } else {
        D_80770788[i] = D_807460AE[D_80770710[j]][0];
    }
    D_80770CE0[j] = arg4;
    D_80770D10[j] = -1;
    D_80770D70[j] = arg5;
    D_80770D40[j] = -1;
    D_80770CF8[j] = arg6;
    D_807706E0[j] = 0;
    temp_a0 = D_80770740[j];
    D_80770628[i] = j;
    D_80770658[i] = temp_a0;
    D_807707A0[j][temp_a0] = i;
    D_80770740[j] = temp_a0 + 1;
    D_807705F8[i] = arg0;
    return i;
}

void func_80605380(s16);
void func_80605314(Actor *arg0, u8 arg1) {
    if (((Aud7130B_Actor *)arg0)->unk6E[arg1] >= 0) {
        func_80605380(((Aud7130B_Actor *)arg0)->unk6E[arg1]);
        ((Aud7130B_Actor *)arg0)->unk6E[arg1] = -1;
        if (arg1 == 0) {
            ((Aud7130B_Actor *)arg0)->unk72 = 0;
        }
    }
}


void func_80732354(s32, s32, s32, s32);

#ifdef NON_MATCHING
void func_80605380(s16 arg0) {
    s16 a1 = D_80770628[arg0];
    s16 t0 = --D_80770740[a1];

    if (t0 != 0) {
        s16 v1 = D_807707A0[a1][t0];
        D_80770658[v1] = D_80770658[D_807707A0[a1][D_80770658[arg0]]];
        D_807707A0[a1][D_80770658[arg0]] = v1;
    } else {
        D_80770710[a1] = 0;
        D_807706F8[a1] = 0;
    }

    if (t0 < 0 || t0 >= 23) {
        func_80732354(9, t0, 0, 0);
        a1 = D_80770628[arg0];
        t0 = D_80770740[a1];
    }

    D_807707A0[a1][t0] = -1;
    D_807705F8[arg0] = -1;
    D_807705A0[arg0] = NULL;
    D_80770628[arg0] = -1;
    D_80770658[arg0] = -1;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/7130/func_80605380.s")
#endif

s32 func_8070B318(void);
void n_alSndpSetSound(void);

extern u8 D_80750190;
extern u8 D_80770770[];

void func_80605510(void) {
    u8 i;
    u8 j;

    i = 0;
    if (func_8070B318() == 0) {
        n_alSndpSetSound();
    }
    D_80750190 = 0;
    if (func_8070B318() != 0) {
        i = 1;
    }
    for (; i < 4; i++) {
        alCSPSetChlPan(gSeqPlayers[i], 0.0f, 1.0f);
        if (alCSPGetState(gSeqPlayers[i]) == 1 && D_80770560[i] != 0x12) {
            alSeqpStop((ALSeqPlayer *)gSeqPlayers[i]);
            D_80770560[i] = 0;
        }
    }
    D_8077058C[0] = 0;
    D_8077058C[1] = 0;
    D_8077058C[2] = 0;
    if (func_8070B318() != 0) {
        i = 1;
    } else {
        i = 0;
    }
    for (; i < 12; i++) {
        if (D_807458DC[i] != 0x12) {
            D_807458F4[i] = 0.0f;
            for (j = 0; j < 4; j++) {
                D_8074593C[j][i] = 0;
            }
            D_807458DC[i] = 0;
            D_80745924[i] = 0;
        }
    }
    D_80745650 = 0;
    D_80770DC9 = 0;
    D_80745838 = 0;
    D_80770DD9 = 0xFF;
    for (i = 0; i < 22; i++) {
        D_807705A0[i] = NULL;
        D_807705F8[i] = -1;
        D_80770628[i] = -1;
        D_80770658[i] = -1;
        D_80770770[i] = 0;
        D_80770710[i] = 0;
        D_807706F8[i] = 0;
        D_80770740[i] = 0;
        D_807706E0[i] = 0;
        for (j = 0; j < 22;) {
            D_807707A0[i][j++] = -1;
        }
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/7130/func_806057F8.s")

void func_806086CC(f32, f32, f32, s16, s32, s32, s32, s32, f32, s32);

void func_80608528(Actor *arg0, s16 arg1, u8 arg2, s16 arg3, u8 arg4) {
    s32 var_v0;

    if (arg0->unk80 + 20.0f < arg0->unkAC && (arg1 < 0x355 || arg1 >= 0x35E)) {
        var_v0 = 0x5A;
    } else {
        var_v0 = 0;
    }
    func_806086CC(arg0->unk7C, arg0->unk80, arg0->unk84, arg1, arg2, arg3, arg4, 0x4B, 0.3f, var_v0);
}

typedef struct Aud7130B_Struct807F6000 {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    char padC[0x84];
} Aud7130B_Struct807F6000;
extern Aud7130B_Struct807F6000 *D_807F6000;

void func_806085DC(s16 arg0, s16 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, f32 arg6) {
    func_806086CC(D_807F6000[arg0].unk0, D_807F6000[arg0].unk4, D_807F6000[arg0].unk8, arg1, arg2, arg3, arg4, arg5, arg6, 0);
}

void func_8060956C(f32, f32, f32, s16, s32, f32, s32, s32);

void func_8060866C(Actor *arg0, s16 arg1, u8 arg2, f32 arg3, u8 arg4, u8 arg5) {
    func_8060956C(arg0->unk7C, arg0->unk80, arg0->unk84, arg1, arg2, arg3, arg4, arg5);
}

extern u8 D_807FC928;

void func_8061CF24(s16 *, s16 *, s16 *, s16 *);
s16 func_80609140(s16, s32, f32, f32, u8, u8);

#ifdef NON_MATCHING
void func_806086CC(f32 arg0, f32 arg1, f32 arg2, s16 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, f32 arg8, s32 arg9) {
    s16 pos[4];
    f32 sp74;
    f32 diff;
    f32 angle2;
    s32 var_a1;
    s32 closest_idx;
    u8 i;

    D_80770DE4 = -1.0f;
    closest_idx = 0;
    for (i = 0; i < D_807FC928; i++) {
        if (D_807FC924[i].unk0 != 0) {
            s32 dx = D_807FC924[i].unk210 - arg0;
            s32 dy = D_807FC924[i].unk214 - arg1;
            s32 dz = D_807FC924[i].unk218 - arg2;
            if (D_80770DE4 == -1.0f || (f32)(dx * dx + dy * dy + dz * dz) < D_80770DE4) {
                closest_idx = i;
                D_80770DE4 = dx * dx + dy * dy + dz * dz;
            }
        }
    }

    if (D_80770DE4 == -1.0f) {
        return;
    }

    pos[0] = D_807FC924[closest_idx].unk210;
    pos[1] = D_807FC924[closest_idx].unk214;
    pos[2] = D_807FC924[closest_idx].unk218;
    pos[3] = (D_807FC924[closest_idx].unk2C4 * 4096.0) / 6.2831854820251465;
    func_8061CF24(&pos[0], &pos[1], &pos[2], &pos[3]);

    if (D_80770DE4 < 500.0f) {
        sp74 = 0.0f;
    } else {
        sp74 = (f64)mathAngleBetweenPointsRad(pos[0], pos[2], arg0, arg2) - ((f64)(pos[3] * 6.2831855f) * 0.000244140625);
        if (sp74 < 0.0f) {
            sp74 += 6.2831855f;
        }
        if (sp74 > 1.5707964f && (f64)sp74 < 4.71238911151886) {
            arg9 |= 0x80;
        }
    }

    if (arg7 == 0) {
        var_a1 = ((f64)(u32)arg4 * 32767.0) / 255.0;
    } else {
        D_80770DE4 = sqrtf(D_80770DE4);
        if (D_807FC928 == 1 && (f64)arg8 >= 0.8) {
            arg0 = mathAngleBetweenPointsRad(pos[1], 0.0f, arg1, sqrtf(((arg2 - pos[2]) * (arg2 - pos[2])) + ((arg0 - pos[0]) * (arg0 - pos[0]))));
            angle2 = mathAngleBetweenPointsRad(pos[1], 0.0f, D_807FC924->unk22C, sqrtf(((D_807FC924->unk230 - pos[2]) * (D_807FC924->unk230 - pos[2])) + ((D_807FC924->unk228 - pos[0]) * (D_807FC924->unk228 - pos[0]))));
            diff = arg0 - angle2;
            if (arg0 < angle2) {
                diff += 6.2831855f;
            }
            if (diff > 3.1415927f) {
                diff = 6.2831855f - diff;
            }
            if ((f64)diff > 0.39269909262657166) {
                D_80770DE4 *= 1.0 + ((f64)(diff - 0.3926991f) * 20.0);
            }
        }

        if ((f64)sp74 > 0.7853981852531433 && (f64)sp74 < 5.497787296772003) {
            arg0 = 1.0f;
            D_80770DE4 *= arg0 - (func_80612D1C(((2.0 * (f64)sp74) / 3.0) + 2.617993950843811) * arg8);
        } else {
            arg0 = 1.0f;
        }
        if (D_80770DE4 < arg0) {
            D_80770DE4 = arg0;
        }

        var_a1 = (((f32)(arg7 * 4000) / sqrtf(D_80770DE4)) - (((f32)(arg7 * 4000) / 7.74596600000000013) - 32767.0));
        if (var_a1 >= 0x8000) {
            var_a1 = 0x7FFF;
        }
        var_a1 = (arg4 * var_a1) / 255.0;
    }

    if (var_a1 >= 1001) {
        func_80609140(arg3, var_a1, (arg0 - func_80612D1C(sp74)) * 63.5, (f64)arg5 / 127.0, arg6, arg9);
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/7130/func_806086CC.s")
#endif

u32 func_806119A0(void);
void n_alSndpPlayAt(s32, s32);
extern s32 D_807457D0[];
extern u8 D_807457D8;
extern s32 D_807457E4[];
extern u8 D_80745834;

#ifdef NON_MATCHING
void func_80608DA8(s16 arg0, s32 arg1, s32 arg2, u8 arg3, u8 arg4) {
    f32 orig_pitch;
    s32 vol;
    f32 pitch;
    f32 pan;
    u8 reverb;

    vol = (s32)(((f64)((arg1 & 0xFF) * 0x7FFF)) / 255.0);
    if (vol < 1001) {
        return;
    }

    pitch = (f64)(u32)(arg2 & 0xFF) / 127.0;
    orig_pitch = pitch;
    pan = ((f64)(u32)func_806119A0() / 4294967295.0) * (2.0 * (f64)(u32)(arg3 & 0xFF)) + (63.5 - (f64)(u32)(arg3 & 0xFF));
    reverb = 0;

    if (arg3 != 0) {
        vol = (1.0 - (((f64)(u32)func_806119A0() / 4294967295.0) * ((f64)(u32)(arg3 & 0xFF) / 155.0))) * (f64)vol;
        pitch = (((f64)(u32)func_806119A0() / 4294967295.0) * ((f64)(u32)(arg3 & 0xFF) / 100.0)) + ((f64)orig_pitch - ((f64)(u32)(arg3 & 0xFF) / 255.0));
    }

    if (D_8077058E >= 21) {
        reverb = (D_8077058E * 100) / 255;
    }
    if (arg4 != 0) {
        reverb |= 0x80;
    }

    if (D_807457D0[D_807457D8] != 0) {
        n_alSndpDeallocate(D_807457D0[D_807457D8]);
    }
    n_alSndpAllocate(D_8076D1F8, arg0, (u16)vol, (u8)pan, pitch, reverb, &D_807457D0[D_807457D8]);
    n_alSndpPlayAt(D_807457D0[D_807457D8], 0);
    D_807457D8 ^= 1;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/7130/func_80608DA8.s")
#endif

#ifdef NON_MATCHING
s16 func_80609140(s16 arg0, s32 arg1, f32 arg2, f32 arg3, u8 arg4, u8 arg5) {
    s16 res;
    s16 i;

    if (arg4 != 0) {
        arg1 = (1.0 - (((f64)(u32)func_806119A0() / 4294967295.0) * ((f64)(u32)arg4 / 155.0))) * (f64)arg1;
        arg3 = (((f64)(u32)func_806119A0() / 4294967295.0) * ((f64)(u32)arg4 / 100.0)) + ((f64)arg3 - ((f64)(u32)arg4 / 255.0));
    }

    for (i = 20; i > 0; i--) {
        if (D_807457E4[D_80745834] == 0) {
            break;
        }
        if (++D_80745834 == 20) {
            D_80745834 = 0;
        }
    }

    if (i > 0) {
        osSetThreadPri(NULL, 26);
        if (D_8077058E >= 21) {
            s32 reverb = (D_8077058E * 100) / 255;
            if (reverb < (arg5 & 0x7F)) {
                reverb = arg5 & 0x7F;
            }
            arg5 = reverb | (arg5 & 0x80);
        }

        if (arg0 < 0x800) {
            n_alSndpAllocate(D_8076D1F8, arg0, (u16)arg1, (u8)arg2, arg3, arg5, &D_807457E4[D_80745834]);
        } else {
            n_alSndpAllocate(D_8076D1FC, arg0 - 0x7FF, (u16)arg1, (u8)arg2, arg3, arg5, &D_807457E4[D_80745834]);
        }

        if (arg0 == 0x137) {
            n_alSndpPlayAt(D_807457E4[D_80745834], 100);
        }

        res = -1;
        if (D_807457E4[D_80745834] != 0) {
            res = (s16)D_80745834;
        } else {
            res = -1;
        }
        osSetThreadPri(NULL, 10);
        return res;
    }

    return -1;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/7130/func_80609140.s")
#endif

#pragma GLOBAL_ASM("asm/global/nonmatchings/7130/func_8060956C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7130/func_80609B80.s")

typedef struct {
    u8 pad[0xF8];
} Aud7130C_CSeq;

extern s32 D_8000DDCC;
extern s32 D_8076D200[];
extern void *D_8076BF38[];
extern Aud7130C_CSeq D_8076BF48[];
extern u8 D_80770598[];

void *func_80610FE8(s32);
void heapFree(void *);
void func_8060B140(s32, void *, s32 *, s32, s32, s32, void *);
void n_alCSeqNew(void *, void *);
void func_80737F40(ALCSPlayer *);
void func_8060A398(s32);

void func_8060A1B0(s32 arg0, u8 arg1, f32 arg2) {
    u32 temp;
    temp = 0;
    alSeqpStop((ALSeqPlayer *)gSeqPlayers[arg0]);
    if (alCSPGetState(gSeqPlayers[arg0]) != 0) {
        do {
            temp++;
            if (alCSPGetState(gSeqPlayers[arg0]) == 0) {
                break;
            }
        } while (temp != 0x1E8480);
    }
    if (temp >= 0x1E8480) {
        alSeqpStop((ALSeqPlayer *)gSeqPlayers[arg0]);
        if (alCSPGetState(gSeqPlayers[arg0]) != 0 && temp < 0x3D0900) {
            do {
                temp++;
                if (alCSPGetState(gSeqPlayers[arg0]) == 0) {
                    break;
                }
            } while (temp < 0x3D0900);
        }
    }
    D_80770598[arg0] = 0;
    D_80770568[arg0] = arg2;
    D_80770560[arg0] = arg1;
    temp = (s32)func_80610FE8(0x8000);
    {
        s32 base = D_8076D200[arg1];
        s32 addr = base + D_8000DDCC;
        s32 len = D_8076D200[arg1 + 1] - base;
        if (len & 1) {
            len++;
        }
        func_8060B140(addr, D_8076BF38[arg0], &len, 0x80, 0, 1, (void *)temp);
    }
    heapFree((void *)temp);
    n_alCSeqNew(&D_8076BF48[arg0], D_8076BF38[arg0]);
    alSeqpSetSeq((ALSeqPlayer *)gSeqPlayers[arg0], (ALSeq *)&D_8076BF48[arg0]);
    func_80737F40(gSeqPlayers[arg0]);
    func_8060A398(arg0);
    alCSPPlay(gSeqPlayers[arg0]);
}

extern s8 D_80745840;
extern s8 D_8074583C;
extern s16 D_807454F0[];
extern f32 D_807457B8[];

void func_8060A398(s32 arg0) {
    f32 var_fv0 = D_80745840;
    s32 temp_t7 = D_80770560[arg0] * 2;
    s32 temp_t8 = *(u16 *)((u8 *)D_80745658 + temp_t7) & 0xC00;
    switch (temp_t8) {
    case 0x400:
        var_fv0 = D_8074583C;
        break;
    case 0x800:
        if (!((f32)D_8074583C < var_fv0)) {
            var_fv0 = D_8074583C;
        }
        break;
    }
    alSeqpSetVol((ALSeqPlayer *)gSeqPlayers[arg0], (s16)(s32)((f64)((((f32)*(s16 *)((u8 *)D_807454F0 + temp_t7)) * D_80770568[arg0]) * D_807457B8[arg0]) * ((f64)var_fv0 / 40.0) * 25000.0 / 32767.0));
}

void func_8060A4D0(s32 arg0, f32 arg1) {
    D_807457B8[arg0] = arg1;
    func_8060A398(arg0);
}

extern f32 D_80770578[];

void func_8060A500(void) {
    s8 i;
    for (i = 0; i < 4; i++) {
        if (D_80770598[i]) {
            f32 curr = D_80770568[i];
            f32 target = D_80770578[i];
            f32 diff;
            D_80770568[i] = curr + (target - curr) * 0.075;
            do {} while (0);
            curr = D_80770568[i];
            if (curr < target) {
                diff = target - curr;
            } else {
                diff = -(target - curr);
            }
            if (diff < 0.05) {
                D_80770568[i] = target;
                D_80770598[i] = 0;
            }
            func_8060A398(i);
        }
    }
}


void func_8060A60C(s32 arg0, f32 arg1) {
    D_80770578[arg0] = arg1;
    D_80770598[arg0] = 1;
}


void func_8060A634(s32 arg0, f32 arg1) {
    D_80770578[arg0] = arg1;
    D_80770568[arg0] = arg1;
    func_8060A398(arg0);
}

extern f32 D_80770588;
void func_8060A1B0(s32, u8, f32);

void func_8060A670(s32 arg0, u8 arg1) {
    func_8060A1B0(arg0, arg1, D_80770588);
}

void func_806049CC(s32);
#ifdef NON_MATCHING
void func_8060A6A0(s32 arg0, u8 arg1, f32 arg2) {
    f64 var_fv0;
    f32 pan, vol;

    func_8060A1B0(arg0, arg1, arg2);
    var_fv0 = (f64)(u32)D_8077058E;
    pan = (var_fv0 * 0.3) / 255.0;
    vol = ((var_fv0 * 0.35) / 255.0) + 1.0;
    if (arg0 != 0) {
        if (D_80745658[D_80770560[arg0]] & 1) {
            alCSPSetChlPan(gSeqPlayers[arg0], pan, vol);
        } else {
            alCSPSetChlPan(gSeqPlayers[arg0], 0.0f, 1.0f);
        }
    }
    func_806049CC(arg0);
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/7130/func_8060A6A0.s")
#endif

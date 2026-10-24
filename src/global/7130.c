#define alCSPSetChlPan alCSPSetChlPan_unused
#include "common.h"
#undef alCSPSetChlPan
#include "actor.h"

void alCSPSetChlPan(ALCSPlayer *, f32, f32);

extern u16 D_80745658[];

u8 sfxGetBankIndex(arg0)
s16 arg0;
{
    return (D_80745658[arg0] & 6) >> 1;
}

u8 sfxGetChannelIndex(arg0)
s16 arg0;
{
    return (D_80745658[arg0] & 0x78) >> 3;
}

extern u8 D_80745654;
void sfxSetMode(arg0)
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
} AmbientSfxEntry;

typedef struct AudioPlayer {
    u8 unk0;
    char pad1[3];
    struct AudioPlayerActor *unk4;
    char pad8[0x208];
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
} AudioPlayer;

extern s8 D_80745650;
extern u8 D_80770DC9;
extern u8 D_80770DD8[];
extern AudioPlayer *D_807FC924;
extern s32 D_8076A0A8;
extern AmbientSfxEntry D_807459FC[];

s16 func_806531B8(f32, f32, f32, s32);
void sfxAllocateChannel(s32, f32);
#ifdef NON_MATCHING
void func_80602498(void) {
    AmbientSfxEntry *entry;
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
            sfxAllocateChannel(entry->unk4, 1.0f);
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
void sfxPlayCurrent(u8 arg0, u8 arg1, u8 arg2) {
    func_80602498();
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/7130/func_806025D4.s")

extern s16 D_807458DC[];
extern f32 D_807458F4[];
extern s16 D_80745924[];
extern s32 D_8074593C[][12];

void sfxAllocateChannel(s32 arg0, f32 arg1) {
    u8 v0;
    u8 i;
    s32 v1;

    v0 = sfxGetChannelIndex((s16)arg0);
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
void sfxStopChannel(arg0, arg1)
s32 arg0;
u8 arg1;
{
    u8 v1 = sfxGetChannelIndex((s16)arg0);
    u8 v0 = sfxGetBankIndex((s16)arg0);
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

void sfxStopAllChannels(void) {
    u8 i;
    for (i = 0; i < 12; i++) {
        if (D_807458DC[i] != 0) {
            sfxStopChannel(D_807458DC[i], 1);
        }
    }
}


void seqSetTargetVolume(s32, f32);

void seqRouteChannelVolume(s32 arg0, f32 arg1) {
    u8 v1 = sfxGetBankIndex((s16)arg0);
    if ((arg0 == D_807458DC[sfxGetChannelIndex((s16)arg0)]) && (arg0 == D_80770560[v1])) {
        seqSetTargetVolume(v1, arg1);
    }
}



void sfxSetChannelParam(arg0, arg1, arg2)
s32 arg0;
s32 arg1;
u8 arg2;
{
    s16 a = arg0;
    s32 temp = sfxGetChannelIndex(a);
    if (arg0 == D_807458DC[temp]) {
        D_8074593C[arg2][temp] = arg1;
    }
}

extern f32 D_80770568[];

f32 sfxGetChannelVolume(arg0)
s32 arg0;
{
    s16 a = arg0;
    u8 v0 = sfxGetBankIndex(a);
    if (arg0 == D_80770560[v0]) {
        if (alCSPGetState(gSeqPlayers[v0]) == 1) {
            return D_80770568[v0];
        }
    }
    return 0.0f;
}

void sfxSetChannelTempo(s32 arg0, f32 arg1) {
    u8 v1 = sfxGetBankIndex((s16)arg0);
    if ((arg0 == D_807458DC[sfxGetChannelIndex((s16)arg0)]) && (arg0 == D_80770560[v1])) {
        alCSPSetTempo(gSeqPlayers[v1], (s32)((s32)alCSPGetSeq(gSeqPlayers[v1]) * arg1));
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/7130/func_80602E6C.s")

f32 func_80602E6C(f32, f32, f32, u8, u8, f32);
extern f32 D_80770DDC;
extern f32 D_80770DE0;
extern f32 D_80770DE8;
extern f32 D_80770DEC;
f32 D_80770DF0;
f32 D_80770DF4;

f32 sfxUpdateDistanceVolumeAndPan(f32 arg0, f32 arg1, f32 arg2, u8 arg3, u8 arg4, f32 arg5)
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
} AmbientEmitter;

typedef struct {
    s16 unk0;
    u8 unk2;
    u8 unk3;
    f32 unk4;
    f32 unk8;
} AmbientAudioParam;

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    u8 unk6;
    u8 unk7;
} LevelSoundEmitter;

typedef struct {
    char pad[0x104];
    struct SoundCtxSub104 *unk104;
    char pad108[0xE8];
    u32 unk1F0;
} SoundContextD580;

extern AmbientEmitter D_80745F74[];
extern AmbientEmitter D_80745FD8[];
extern AmbientEmitter D_80746010[];
extern AmbientEmitter D_8074603C[];
extern AmbientEmitter D_80746074[];
extern AmbientEmitter D_807460AC[];
extern AmbientEmitter D_807460E4[];
extern AmbientEmitter D_80746170[];
extern AmbientEmitter D_807461E0[];
extern AmbientEmitter D_80746244[];
extern AmbientEmitter D_8074627C[];

extern AmbientAudioParam D_80745B28[];
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
s32 D_80770DF8[16];
u32 D_80770E38[16];
f32 D_80770E78[16];
f32 D_80770EB8[16];
f32 D_80770EF8[16];
extern u32 D_807FBB60;
extern SoundContextD580 *D_807FD580;

s32 func_8062F388(LevelSoundEmitter **);
void func_80664044(s32, s32, s32, f32);
s32 func_8073110C(s32, s32);
void func_80737AC4(s32, s32, ...);
f32 func_80611BB4(f32, f32);
f32 func_80612D1C(f32);
f32 mathAngleBetweenPointsRad(f32, f32, f32, f32);
void n_alSndpAllocate(s32, s16, s32, s32, f32, s32, s32 *);
void n_alSndpDeallocate(s32);
void seqSetVolumeInstant(s32, f32);

#ifdef NON_MATCHING
void func_80603450(void) {
    s8 spE7;
    u8 spE5;
    f32 spCC;
    s32 spC8;
    AmbientEmitter *spC0;
    LevelSoundEmitter *spBC;
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
            sfxStopChannel(0x46, 0);
            if (sfxGetChannelVolume(0x44) < 0.1) {
                sfxAllocateChannel(0x46, 1.0f);
            }
        } else {
            sfxStopChannel(0x44, 0);
            if (sfxGetChannelVolume(0x46) < 0.1) {
                sfxAllocateChannel(0x44, 1.0f);
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
                AmbientEmitter *entry = &spC0[s0];
                if (entry->unk6 == -1) {
                    D_80770DE4 = sqrtf((D_807FC924->unk210 - (f32)entry->unk0) * (D_807FC924->unk210 - (f32)entry->unk0) + (D_807FC924->unk218 - (f32)entry->unk4) * (D_807FC924->unk218 - (f32)entry->unk4));
                    if (D_80770DE4 < (f32)(entry->unk8 - 20)) {
                        sfxAllocateChannel(entry->unkB, 1.0f);
                    } else if (D_80770DE4 > (f32)entry->unk8) {
                        sfxStopChannel(entry->unkB, 0);
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
            AmbientEmitter *closest = &spC0[spE7];
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
                    sfxAllocateChannel(closest->unkC, 1.0f);
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
            AmbientEmitter *closest = &spC0[spE7];
            D_80770DD9 = closest->unkB;
            D_80770DC8 = closest->unkA;
            if (D_80770DC9 == 0) {
                sfxAllocateChannel(closest->unkC, 1.0f);
            }
        }
        if (D_80770DC9 != 0 && D_80770DD9 != 0) {
            sfxAllocateChannel(D_80770DD9, 1.0f);
        } else if (D_80745838 != 0) {
            seqSetTargetVolume(0, 1.0f);
        } else {
            sfxStopChannel(D_80770DD9, 0);
        }
        D_80770DCA = D_80770DC9;
        if (var_fs1 != 0.0f) {
            if (spC0[spE7].unkD != 0) {
                sfxAllocateChannel(spC0[spE7].unkD, 1.0f);
            }
        }
        if (D_80770560[2] == 0x26) {
            seqSetVolumeInstant(2, (f32)((f64)var_fs1 / 32767.0));
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
                seqSetVolumeInstant(0, 1.0f);
            } else {
                seqSetVolumeInstant(0, 0.6f);
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
                        sfxUpdateDistanceVolumeAndPan((f32)spBC[s0].unk0, (f32)spBC[s0].unk2, (f32)spBC[s0].unk4,
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
                AmbientEmitter *s0 = &spC0[spE7];
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

void sfxSetChannelParam();

void seqUpdateUnderwaterAudio(s32 arg0) {
    if (D_80745838 != 0) {
        if (arg0 == 0 && (D_80745658[D_80770560[arg0]] & 1)) {
            alCSPSetChlPan(gSeqPlayers[0], 0.3f, 1.35f);
        }
        if (D_80770560[arg0] == 0x38) {
            sfxSetChannelParam(0x38, 0x3C00, 1);
        }
        if (D_80770560[arg0] == 0x60) {
            if (D_8076A0A8 == 0xB8) {
                sfxSetChannelParam(0x60, 0xE, 1);
            } else {
                sfxSetChannelParam(0x60, 8, 1);
                alCSPSetChlVol(D_8076BF24, 1, 0x7F);
                alCSPSetChlVol(D_8076BF24, 2, 0x7F);
            }
            sfxSetChannelParam(0x60, 0x10, 0);
        }
    } else {
        if (arg0 == 0 && (D_80745658[D_80770560[arg0]] & 1)) {
            alCSPSetChlPan(gSeqPlayers[0], 0.0f, 1.0f);
        }
        if (D_80770560[arg0] == 0x38) {
            sfxSetChannelParam(0x38, 0x3C00, 0);
        }
        if (D_80770560[arg0] == 0x60) {
            if (D_8076A0A8 == 0xB8) {
                sfxSetChannelParam(0x60, 0x1E, 1);
                return;
            }
            sfxSetChannelParam(0x60, 0x10, 1);
            sfxSetChannelParam(0x60, 8, 0);
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

void sfxSetVolumeAndPan(u8 arg0, f32 arg1, f32 arg2) {
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

void sfxSetChannelPriority(arg0, arg1)
u8 arg0;
u8 arg1;
{
    if (arg0 != -1) {
        D_80770CE0[D_80770628[arg0]] = arg1;
    }
}

typedef struct AudioActorModel {
    char pad0[0x10];
    s16 unk10;
} AudioActorModel;

typedef struct AudioActorSub4 {
    AudioActorModel *unk0;
} AudioActorSub4;

typedef struct AudioActor {
    char pad0[4];
    AudioActorSub4 *unk4;
    char pad8[0x50];
    s32 unk58;
    char pad5C[0x12];
    s16 unk6E[2];
    s16 unk72;
    f32 unk74;
    char pad78[4];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0x1C];
    f32 unkA4;
    char padA8[0x10];
    f32 unkB8;
    char padBC[0x2A];
    s16 unkE6;
    char padE8[0x4C];
    s16 unk134;
} AudioActor;

extern s16 D_80770710[];

u8 sfxSlotAllocateActor(Actor *, s16, u8, u8, u8, f32, s8);
void sfxStopSlotSound(Actor *, u8);

void sfxPlayActorSound(Actor *arg0, s16 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, f32 arg6, s8 arg7) {
    if (((AudioActor *)arg0)->unk6E[arg4] != -1) {
        if (arg1 == D_80770710[D_80770628[((AudioActor *)arg0)->unk6E[arg4]]]) {
            return;
        }
        sfxStopSlotSound(arg0, arg4);
    }
    ((AudioActor *)arg0)->unk6E[arg4] = sfxSlotAllocateActor(arg0, arg1, arg2, arg3, arg5, arg6, arg7);
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

u8 sfxSlotAllocateActor(Actor *arg0, s16 arg1, u8 arg2, u8 arg3, u8 arg4, f32 arg5, s8 arg6) {
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

u8 sfxSlotAllocateSource(s16 arg0, s16 arg1, u8 arg2, u8 arg3, u8 arg4, f32 arg5, s8 arg6) {
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
void sfxStopSlotSound(Actor *arg0, u8 arg1) {
    if (((AudioActor *)arg0)->unk6E[arg1] >= 0) {
        func_80605380(((AudioActor *)arg0)->unk6E[arg1]);
        ((AudioActor *)arg0)->unk6E[arg1] = -1;
        if (arg1 == 0) {
            ((AudioActor *)arg0)->unk72 = 0;
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

void audioResetAll(void) {
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

typedef struct SoundTargetSlotNode {
    char pad0[0x10];
    s16 unk10;
    s16 unk12;
} SoundTargetSlotNode;

typedef struct SoundTargetSlot {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    char padC[0x70];
    SoundTargetSlotNode *unk7C;
    char pad80[0x10];
} SoundTargetSlot;
extern SoundTargetSlot *D_807F6000;

typedef struct SoundWaterState {
    char pad0[0x90];
    f32 unk90;
    char pad94[0x66];
    u8 unkFA;
} SoundWaterState;

typedef struct SoundCtxSub104 {
    char pad0[0x174];
    SoundWaterState *unk174;
} SoundCtxSub104;

typedef struct AudioPlayerActor {
    char pad0[0x174];
    SoundContextD580 *unk174;
} AudioPlayerActor;

extern f32 D_80770590;
extern f32 D_80770594;
extern f32 D_80770688[];
extern u8 D_807FC928;

void actorGetNodePos(Actor *, s32, f32 *, f32 *, f32 *);
void func_806335B0(s16, s32, s32, f32 *, f32 *, f32 *);
void modelAnimEntryGetState(s16, s16, s16 *, f32 *, u8 *);
s32 hashTableLookup(s32);
s16 func_80609140(s16, s32, f32, f32, u8, u8);
u32 func_806119A0(void);
f32 func_80612790(s16);
f32 func_80612794(s16);

#define RAND_UNIT() (func_806119A0() / 4294967295.0)
#define SLOT_ACTOR(idx) ((AudioActor *)D_807705A0[idx])

void func_806057F8(void) {
    static f32 D_80770F38;
    u8 slotIdx;
    f32 posX;
    f32 posY;
    f32 posZ;
    f32 dist[22];
    f32 nearest[2];
    f32 factor;
    f32 volume;
    u8 i;
    u8 fxFlags;
    s16 fxLevel;
    AudioActor *actor;
    SoundWaterState *water;
    s16 j;
    s16 pan;
    SoundCtxSub104 *ctx104;
    s32 slot;
    s16 animFrame;
    f32 animSpeed;
    u8 animFlags;
    s32 unused;

    actor = NULL;
    // Emits no code, but keeps &D_807FD580 out of a register so the store/reload after the loop stays split.
    if (D_807FD580 != NULL) {}
    for (i = 0; i < 22; i++) {
        if (D_80770710[i] == 0x88) {
            D_80770DE8 = 0.0f;
            D_80770DEC = 0.0f;
            D_80770DF0 = 0.0f;
            D_80770DF4 = 0.0f;
            fxFlags = 0;
            for (j = D_80770740[i] - 1; j >= 0; j--) {
                slot = hashTableLookup(D_807705F8[D_807707A0[i][j]]);
                sfxUpdateDistanceVolumeAndPan(D_807F6000[slot].unk0, D_807F6000[slot].unk4, D_807F6000[slot].unk8, 0xFF, 0x50, 0.5f);
                dist[j] = D_80770DE4;
                func_80605380(D_807707A0[i][j]);
                D_807F6000[slot].unk7C->unk12 = -1;
            }
            if (D_80770DE8 > 32767.0f) {
                D_80770DE8 = 32767.0f;
            }
            if (D_80770DEC > 32767.0f) {
                D_80770DEC = 32767.0f;
            }
            volume = D_80770DE8 + D_80770DEC;
            if (D_80770DEC < D_80770DE8) {
                if (D_80770DE8 > 0.0f) {
                    D_80770DDC = 127.0 - ((D_80770DEC * 63.5) / D_80770DE8);
                } else {
                    D_80770DDC = 0.0f;
                }
            } else if (D_80770DEC > 0.0f) {
                D_80770DDC = (D_80770DE8 * 63.5) / D_80770DEC;
            } else {
                D_80770DDC = 0.0f;
            }
            if (volume > 32767.0f) {
                volume = 32767.0f;
            }
            if (volume < 0.0f) {
                volume = 0.0f;
            }
            if (D_80770DF0 < D_80770DF4) {
                fxFlags = 0x80;
            }
            func_80609140(0x88, volume, D_80770DDC, 1.0f, 5, fxFlags);
        } else {
            if (D_80745848[i] != 0) {
                if (D_80770710[i] == 0) {
                    if (D_807706E0[i] != 0) {
                        D_807706E0[i]--;
                    } else {
                        n_alSndpDeallocate(D_80745848[i]);
                        D_80770770[i] = 0;
                        D_807706E0[i] = 10;
                    }
                }
            } else if (D_80770710[i] != 0) {
                if (D_80770710[i] == 0x128 || D_80770710[i] == 0x306) {
                    if (D_80770CC8[i] == 0) {
                        n_alSndpAllocate(D_8076D1F8, D_80770710[i], 0, 0x3F, D_80770C18[i], 0, &D_80745848[i]);
                        D_80770CC8[i] = 1;
                    } else {
                        slotIdx = D_807707A0[i][0];
                        sfxStopSlotSound(D_807705A0[slotIdx], 0);
                    }
                } else if (D_80770710[i] < 0x800) {
                    n_alSndpAllocate(D_8076D1F8, D_80770710[i], 0, 0x3F, D_80770C18[i], 0, &D_80745848[i]);
                } else {
                    n_alSndpAllocate(D_8076D1FC, D_80770710[i] - 0x7FF, 0, 0x3F, D_80770C18[i], 0, &D_80745848[i]);
                }
            }
            if (D_80745848[i] != 0) {
                if (D_807707A0[i][0] != -1 && (D_807705A0[D_807707A0[i][0]] != NULL || D_807705F8[D_807707A0[i][0]] != -1)) {
                    D_80770DE8 = 0.0f;
                    D_80770DEC = 0.0f;
                    if (D_80770710[i] >= 0xFD && D_80770710[i] < 0x142) {
                        factor = D_807460AE[D_80770710[i]][1];
                    } else {
                        factor = 0.3f;
                    }
                    fxLevel = 0;
                    j = 0;
                    if (D_80770740[i] > 0) {
                        do {
                            if (D_807705F8[D_807707A0[i][0]] != -1) {
                                actor = NULL;
                                if (D_80770710[i] == 0x12B) {
                                    slot = hashTableLookup(D_807705F8[D_807707A0[i][j]]);
                                    sfxUpdateDistanceVolumeAndPan(D_807F6000[slot].unk0, D_807F6000[slot].unk4 + 320.0f, D_807F6000[slot].unk8, 0xFF, D_80770788[D_807707A0[i][j]], factor);
                                } else if (D_80770CF8[i] > 0) {
                                    func_806335B0(D_807705F8[D_807707A0[i][j]], 1, D_80770CF8[i], &posX, &posY, &posZ);
                                    sfxUpdateDistanceVolumeAndPan(posX, posY, posZ, 0xFF, D_80770788[D_807707A0[i][j]], factor);
                                } else if (D_80770CF8[i] < 0) {
                                    D_80770DE8 = 32767.0f;
                                    D_80770DEC = 32767.0f;
                                    D_80770DF0 = 32767.0f;
                                    D_80770DF4 = 32767.0f;
                                } else {
                                    slot = hashTableLookup(D_807705F8[D_807707A0[i][j]]);
                                    sfxUpdateDistanceVolumeAndPan(D_807F6000[slot].unk0, D_807F6000[slot].unk4, D_807F6000[slot].unk8, 0xFF, D_80770788[D_807707A0[i][j]], factor);
                                }
                            } else {
                                actor = D_807705A0[D_807707A0[i][j]];
                                if (D_80770CF8[i] > 0) {
                                    actorGetNodePos((Actor *)actor, D_80770CF8[i], &posX, &posY, &posZ);
                                    sfxUpdateDistanceVolumeAndPan(posX, posY, posZ, 0xFF, D_80770788[D_807707A0[i][j]], factor);
                                } else if (D_80770CF8[i] < 0) {
                                    D_80770DE8 = 32767.0f;
                                    D_80770DEC = 32767.0f;
                                    D_80770DF0 = 32767.0f;
                                    D_80770DF4 = 32767.0f;
                                } else if (D_80770710[i] == 0x139 && D_807706F8[i] != 0) {
                                    posY = actor->unk80;
                                    posX = actor->unk7C;
                                    posZ = actor->unk84;
                                    sfxUpdateDistanceVolumeAndPan(posX, posY, posZ, 0xFF, D_80770788[D_807707A0[i][j]], factor);
                                    posX = (func_80612790(actor->unkE6) * 300.0) + actor->unk7C;
                                    posZ = actor->unk84 - (func_80612794(actor->unkE6) * 300.0);
                                    sfxUpdateDistanceVolumeAndPan(posX, posY, posZ, 0xFF, D_80770788[D_807707A0[i][j]], factor);
                                    posX = actor->unk7C - (func_80612790(actor->unkE6) * 300.0);
                                    posZ = (func_80612794(actor->unkE6) * 300.0) + actor->unk84;
                                    sfxUpdateDistanceVolumeAndPan(posX, posY, posZ, 0xFF, D_80770788[D_807707A0[i][j]], factor);
                                } else {
                                    sfxUpdateDistanceVolumeAndPan(actor->unk7C, actor->unk80, actor->unk84, 0xFF, D_80770788[D_807707A0[i][j]], factor);
                                }
                            }
                            dist[j++] = D_80770DE4;
                        } while (j < D_80770740[i]);
                    }
                    if (D_80770DE8 > 32767.0f) {
                        D_80770DE8 = 32767.0f;
                    }
                    if (D_80770DEC > 32767.0f) {
                        D_80770DEC = 32767.0f;
                    }
                    volume = D_80770DE8 + D_80770DEC;
                    if (D_80770DEC < D_80770DE8) {
                        if (D_80770DE8 > 0.0f) {
                            D_80770DDC = 127.0 - ((D_80770DEC * 63.5) / D_80770DE8);
                        } else {
                            D_80770DDC = 0.0f;
                        }
                    } else if (D_80770DEC > 0.0f) {
                        D_80770DDC = (D_80770DE8 * 63.5) / D_80770DEC;
                    } else {
                        D_80770DDC = 0.0f;
                    }
                    if (volume > 32767.0f) {
                        volume = 32767.0f;
                    }
                    if (volume < 0.0f) {
                        volume = 0.0f;
                    }
                    volume *= D_80770CE0[i] / 255.0;
                    if ((D_807FBB60 & 2) || !(D_807FBB60 & 0x10)) {
                        volume = 0.0f;
                    } else {
                        switch (D_80770710[i]) {
                        case 0x12F:
                            volume *= D_80770BC0[i] / 9.0;
                            fxLevel = D_80770BC0[i] * 1.3;
                            break;
                        case 0x12B:
                            modelAnimEntryGetState(slot, 1, &animFrame, &animSpeed, &animFlags);
                            factor = func_80612D1C((animFrame / 27.0) * 3.1415927410125732);
                            volume *= factor;
                            D_80770B68[i] = factor;
                            D_80770C18[i] = (factor * 0.4) + 0.8;
                            break;
                        case 0x113:
                            if (D_80770B68[i] == 0.0f) {
                                volume = 0.0f;
                            } else {
                                D_80770C18[i] = D_80770B68[i];
                            }
                            break;
                        case 0x111:
                            D_80770BC0[i] += 1.0f;
                            if (D_80770BC0[i] > 30.0f) {
                                D_80770C18[i] = 1.0 - ((D_80770BC0[i] - 30.0) / 30.0);
                            }
                            if (D_80770BC0[i] == 40.0f) {
                                func_80605380(D_807707A0[i][0]);
                                D_807F6000[slot].unk7C->unk10 = -1;
                            }
                            break;
                        case 0x11F:
                            if (D_807706F8[i] != 0) {
                                factor = func_80612D1C(D_80770BC0[i] * 0.027925);
                                D_80770C18[i] = (func_80612D1C((D_80770BC0[i] * 0.261799) - 1.570795) * 0.1) + (0.2 * factor) + 0.6;
                                D_80770BC0[i] += 1.0f;
                                if (D_80770788[D_807707A0[i][0]] == 0) {
                                    D_80770DDC = 63.0f;
                                    D_80770DF4 = 100.0f;
                                    D_80770DF0 = 0.0f;
                                }
                            } else {
                                factor = func_80612D1C(D_80770BC0[i] * 0.027925);
                                D_80770C18[i] = (func_80612D1C((D_80770BC0[i] * 0.261799) - 1.570795) * 0.1) + (0.5 * factor) + 0.6;
                                D_80770B68[i] = 1.0 - ((D_80770BC0[i] - 90.0) / 20.0);
                                D_80770B68[i] = (D_80770B68[i] > 1.0f) ? 1.0f : D_80770B68[i];
                                D_80770B68[i] = (D_80770B68[i] < 0.0f) ? 0.0f : D_80770B68[i];
                                volume *= D_80770B68[i];
                                D_80770B68[i] = D_80770BC0[i] / 20.0f;
                                D_80770B68[i] = (D_80770B68[i] < 1.0f) ? D_80770B68[i] : 1.0f;
                                volume *= D_80770B68[i];
                                D_80770BC0[i] += 1.0f;
                                D_80770C18[i] = (D_80770C18[i] > 0.2) ? D_80770C18[i] : 0.2;
                                if (D_80770BC0[i] == 110.0f) {
                                    if (D_807705F8[D_807707A0[i][0]] != -1) {
                                        func_80605380(D_807707A0[i][0]);
                                        D_807F6000[slot].unk7C->unk10 = -1;
                                    } else {
                                        sfxStopSlotSound((Actor *)actor, 0);
                                        sfxStopChannel(0x3B, 0);
                                    }
                                }
                            }
                            break;
                        case 0x131:
                            if (actor->unk58 == 0xB9) {
                                D_80770770[i] = 8;
                                D_80770C18[i] = (actor->unk72 / 80.0) + 1.0;
                                volume *= 1.0f / D_80770C18[i];
                            } else {
                                D_80770B68[i] = 0.0f;
                                D_80770C18[i] = 200.0f;
                                for (j = 0; j < D_80770740[i]; j++) {
                                    if (SLOT_ACTOR(D_807707A0[i][j])->unk72 < D_80770C18[i]) {
                                        D_80770C18[i] = SLOT_ACTOR(D_807707A0[i][j])->unk72;
                                        D_80770B68[i] = j;
                                    }
                                }
                                j = D_80770B68[i];
                                D_80770C18[i] = 2.0 - (((SLOT_ACTOR(D_807707A0[i][j])->unk72 - 120) > 0 ? (SLOT_ACTOR(D_807707A0[i][j])->unk72 - 120) : -(SLOT_ACTOR(D_807707A0[i][j])->unk72 - 120)) / 120.0);
                                D_80770C18[i] = (D_80770C18[i] > 0.2) ? D_80770C18[i] : 0.2;
                                D_80770B68[i] = SLOT_ACTOR(D_807707A0[i][j])->unk74 / 20.0;
                                D_80770B68[i] = (D_80770B68[i] < 1.0f) ? D_80770B68[i] : 1.0f;
                                D_80770B68[i] = (D_80770B68[i] > 0.0f) ? D_80770B68[i] : 0.0f;
                                volume *= D_80770B68[i];
                            }
                            break;
                        case 0x10E:
                            if (actor->unk58 == 0x139) {
                                if (D_80770BC0[i]-- <= 0.0f) {
                                    D_80770BC0[i] = (RAND_UNIT() * 2) + 2.0;
                                    D_80770B68[i] = ((0.925 + (0.15 * RAND_UNIT())) - D_80770C18[i]) / D_80770BC0[i];
                                }
                                volume *= 0.5;
                                break;
                            }
                            if (actor->unk58 == 2) {
                                if (D_80770BC0[i]-- <= 0.0f) {
                                    D_80770BC0[i] = (RAND_UNIT() * 2) + 2.0;
                                    D_80770B68[i] = ((1.2 + (0.15 * RAND_UNIT())) - D_80770C18[i]) / D_80770BC0[i];
                                }
                                fxLevel = 0xE;
                                volume *= 0.9;
                                break;
                            }
                        case 0x108:
                        case 0x10F:
                            if (D_80770BC0[i]-- <= 0.0f) {
                                if (D_80770710[i] == 0x108) {
                                    switch (actor->unk134) {
                                        case 3:
                                            D_80770BC0[i] = (RAND_UNIT() * 2) + 3.0f;
                                            D_80770B68[i] = ((0.95 + (0.1 * RAND_UNIT())) - D_80770C18[i]) / D_80770BC0[i];
                                            break;
                                        case 2:
                                            D_80770BC0[i] = (RAND_UNIT() * 2.0f) + 2.0f;
                                            D_80770B68[i] = ((0.85 + (0.5 * RAND_UNIT())) - D_80770C18[i]) / D_80770BC0[i];
                                            break;
                                        case 0:
                                        case 1:
                                            D_80770BC0[i] = (RAND_UNIT() * 1.0f) + 2.0;
                                            D_80770B68[i] = ((0.9 + (0.5 * RAND_UNIT())) - D_80770C18[i]) / D_80770BC0[i];
                                            break;
                                    }
                                } else {
                                    D_80770BC0[i] = (RAND_UNIT() * 2.0f) + 2.0f;
                                    D_80770B68[i] = (((D_80770C70[i] - 0.075) + (0.15 * RAND_UNIT())) - D_80770C18[i]) / D_80770BC0[i];
                                }
                            }
                            D_80770C18[i] += D_80770B68[i];
                            if (D_80770740[i] >= 2) {
                                nearest[0] = 10000.0f;
                                nearest[1] = 10000.0f;
                                for (j = 0; j < D_80770740[i]; j++) {
                                    if (dist[j] < nearest[0]) {
                                        nearest[1] = nearest[0];
                                        nearest[0] = dist[j];
                                    } else if (dist[j] < nearest[1]) {
                                        nearest[1] = dist[j];
                                    }
                                }
                                fxLevel = 14.0 - ((nearest[1] - nearest[0]) / 20.0);
                                if (fxLevel < 0) {
                                    fxLevel = 0;
                                }
                                D_80770DDC = ((D_80770DDC - 63.5) * (1.0 + (fxLevel / 15.0))) + 63.5;
                                if (D_80770DDC > 127.0f) {
                                    D_80770DDC = 127.0f;
                                }
                                if (D_80770DDC < 0.0f) {
                                    D_80770DDC = 0.0f;
                                }
                            }
                            if (fxLevel != D_80770770[i]) {
                                D_80770770[i] = fxLevel;
                            }
                            break;
                        case 0x104:
                            if (D_80770BC0[i] < 30.0f) {
                                D_80770BC0[i] += 1.0f;
                                D_80770C18[i] *= 1.02;
                            }
                            break;
                        case 0x118:
                            if (actor->unk58 != 0x139) {
                                if (D_80770BC0[i]++ >= 2.0f) {
                                    D_80770BC0[i] = func_806119A0();
                                    if (D_80770DF0 < D_80770DF4) {
                                        fxFlags |= 0x80;
                                    }
                                    func_80609140((func_806119A0() & 3) + 0x90, volume, D_80770DDC, 1.0f, 0x1E, fxFlags);
                                    D_80770BC0[i] = 0.0f;
                                }
                            }
                            D_80770C18[i] *= 0.99;
                            break;
                        case 0x219:
                            if (D_80770BC0[i]-- <= 0.0f) {
                                D_80770BC0[i] = (RAND_UNIT() * 6.0f) + 2.0;
                                D_80770B68[i] = ((0.84089 + (0.21857 * RAND_UNIT())) - D_80770C18[i]) / D_80770BC0[i];
                            }
                            D_80770C18[i] += D_80770B68[i];
                            break;
                        case 0x132:
                            if (D_80770BC0[i]-- <= 0.0f) {
                                D_80770BC0[i] = (RAND_UNIT() * 6.0f) + 2.0;
                                D_80770B68[i] = ((0.8 + (0.2 * RAND_UNIT())) - D_80770C18[i]) / D_80770BC0[i];
                            }
                            D_80770C18[i] += D_80770B68[i];
                            break;
                        case 0x116:
                            if (D_80770BC0[i] > 0.0f) {
                                D_80770C18[i] += (D_80770B68[i] - D_80770C18[i]) / D_80770BC0[i]--;
                            }
                            D_80770DE8 = (D_80770C18[i] - 0.2) * 2.0;
                            if (D_80770DE8 > 1.0) {
                                D_80770DE8 = 1.0f;
                            }
                            if (D_80770DE8 < 0.0f) {
                                D_80770DE8 = 0.0f;
                            }
                            volume *= D_80770DE8;
                            break;
                        case 0x107:
                        case 0x12E:
                            if (D_80770BC0[i] > 0.0f) {
                                D_80770C18[i] += (D_80770B68[i] - D_80770C18[i]) / D_80770BC0[i]--;
                            }
                            volume *= actor->unk74;
                            break;
                        case 0x115:
                            if (D_80770BC0[i] > 0.0f) {
                                D_80770C18[i] += (D_80770B68[i] - D_80770C18[i]) / D_80770BC0[i]--;
                            }
                            D_80770DE8 = 1.0 - ((D_80770C18[i] - 1.0) * 0.9);
                            if (D_80770DE8 > 1.0) {
                                D_80770DE8 = 1.0f;
                            }
                            if (D_80770DE8 < 0.0f) {
                                D_80770DE8 = 0.0f;
                            }
                            volume *= D_80770DE8;
                            break;
                        case 0x12D:
                            if (D_80770BC0[i] > 0.0f) {
                                D_80770C18[i] += (D_80770B68[i] - D_80770C18[i]) / D_80770BC0[i]--;
                            }
                            D_80770DE8 = 1.0 - ((D_80770C18[i] - 1.0f) * 0.9);
                            if (D_80770DE8 > 1.0) {
                                D_80770DE8 = 1.0f;
                            }
                            if (D_80770DE8 < 0.0f) {
                                D_80770DE8 = 0.0f;
                            }
                            volume *= D_80770DE8;
                            break;
                        case 0x12C:
                            volume *= D_80770B68[i];
                            break;
                        case 0x122:
                            D_80770590 = actor->unkB8 / 600.0;
                            D_80770590 = (D_80770590 > 0.8) ? 0.8 : D_80770590;
                            volume *= D_80770590;
                            break;
                        default:
                            if (D_80770BC0[i] > 0.0f) {
                                D_80770C18[i] += (D_80770B68[i] - D_80770C18[i]) / D_80770BC0[i]--;
                            }
                            break;
                        }
                    }
                    switch (D_80770710[i]) {
                    case 0x119:
                        D_80770F38 = 1.0f;
                        volume = D_80770C18[i] * 32767.0f;
                        D_80770DDC = 63.0f;
                        break;
                    case 0xFD:
                    case 0x108:
                    case 0x10E:
                        if (actor->unk58 == 0x139) {
                            if (D_80770DE4 < D_80770688[i]) {
                                factor = D_80770688[i] - D_80770DE4;
                            } else {
                                factor = -(D_80770688[i] - D_80770DE4);
                            }
                            if (factor < 20.0f) {
                                D_80770F38 = ((D_80770688[i] - D_80770DE4) / 30.0) + 1.0;
                                if (D_80770F38 > 1.18) {
                                    D_80770F38 = 1.18f;
                                }
                                if (D_80770F38 < 0.85) {
                                    D_80770F38 = 0.85f;
                                }
                                D_80770F38 = D_80770C18[i] * (D_80770F38 * D_80770F38);
                            } else {
                                D_80770F38 = D_80770C18[i];
                            }
                            D_80770688[i] = D_80770DE4;
                            break;
                        }
                        /* fallthrough */
                    case 0x13F:
                    case 0x140:
                    case 0x141:
                        D_80770F38 = ((D_80770688[i] - D_80770DE4) / 900.0) + 1.0;
                        if (D_80770F38 > 1.18) {
                            D_80770F38 = 1.0f;
                        }
                        if (D_80770F38 < 0.85) {
                            D_80770F38 = 1.0f;
                        }
                        D_80770688[i] = D_80770DE4;
                        D_80770F38 = D_80770C18[i] * (D_80770F38 * D_80770F38);
                        break;
                    case 0x107:
                    case 0x10F:
                    case 0x114:
                    case 0x12E:
                    case 0x130:
                        if (D_80770DE4 < D_80770688[i]) {
                            factor = D_80770688[i] - D_80770DE4;
                        } else {
                            factor = -(D_80770688[i] - D_80770DE4);
                        }
                        if (factor < 20.0f) {
                            D_80770F38 = ((D_80770688[i] - D_80770DE4) / 100.0) + 1.0;
                            if (D_80770F38 > 1.18) {
                                D_80770F38 = 1.18f;
                            }
                            if (D_80770F38 < 0.85) {
                                D_80770F38 = 0.85f;
                            }
                            D_80770688[i] = D_80770DE4;
                            D_80770F38 = D_80770C18[i] * (D_80770F38 * D_80770F38);
                            break;
                        }
                        D_80770688[i] = D_80770DE4;
                    default:
                        D_80770F38 = D_80770C18[i];
                        break;
                    }
                    if (D_80770710[i] == 0x10D) {
                        if (D_8076A0A8 == 0xE || D_8076A0A8 == 0x52) {
                            D_80770590 = actor->unkB8 / 600.0;
                            D_80770590 = (D_80770590 > 0.8) ? 0.8 : D_80770590;
                            volume *= D_80770590;
                            if ((actor->unk80 - actor->unkA4) > 5.0f) {
                                volume = 0.0f;
                            }
                            D_80770594 = actor->unkB8;
                            D_80770F38 = (actor->unkB8 / 550.0f) + 0.5;
                        } else {
                            if (D_80770594 != actor->unkB8) {
                                D_80770F38 = (D_80770594 * 32767.0f) / 200.0f;
                                D_80770590 = D_80770590 + ((D_80770F38 - D_80770590) * 0.3);
                            } else if (D_80770590 > 5000.0f) {
                                D_80770590 = ((D_80770590 - 350.0f) < 5000.0f) ? 5000.0f : (D_80770590 - 350.0f);
                            } else if (D_80770590 < 5000.0f) {
                                D_80770590 = ((D_80770590 + 350.0f) > 5000.0f) ? 5000.0f : (D_80770590 + 350.0f);
                            }
                            volume *= D_80770590 / 32767.0;
                            if ((actor->unk80 - actor->unkA4) > 5.0f) {
                                volume = 0.0f;
                            }
                            D_80770594 = actor->unkB8;
                            D_80770F38 = (actor->unkB8 / 150.0f) + 0.5;
                            D_80770F38 *= D_80770C18[i];
                        }
                    }
                    if (actor != NULL) {
                        if (actor->unk72 != 0 && D_80770710[i] != 0x131 && actor->unk4->unk0->unk10 != actor->unk72) {
                            sfxStopSlotSound((Actor *)actor, 0);
                        }
                    }
                    if (volume > 32767.0f) {
                        volume = 32767.0f;
                    }
                    if (D_80745838 != 0) {
                        switch (D_80770710[i]) {
                            case 0x101:
                            case 0x126:
                                D_80770F38 *= 0.9;
                                volume = ((volume * 2) > 32767.0f) ? 32767.0f : (volume * 2);
                                break;
                        }
                    }
                    if (fxLevel != 0) {
                        fxFlags = fxLevel * 8;
                    } else {
                        fxFlags = 0;
                    }
                    if (D_80770DF0 < D_80770DF4) {
                        fxFlags |= 0x80;
                    }
                    if (D_80770F38 < 0.17) {
                        D_80770F38 = 0.17f;
                    }
                    func_80737AC4(D_80745848[i], 0x100, fxFlags);
                    if (volume != D_80770D10[i]) {
                        if (D_80770D10[i] != -1) {
                            if (D_80770D10[i] < volume) {
                                if ((D_80770D10[i] + 8000) < volume) {
                                    volume = D_80770D10[i] + 8000;
                                }
                            } else if (volume < (D_80770D10[i] - 8000)) {
                                volume = D_80770D10[i] - 8000;
                            }
                        }
                        D_80770D10[i] = volume;
                        func_80737AC4(D_80745848[i], 8, (s32)volume);
                    }
                    pan = D_80770DDC;
                    if (pan != D_80770D40[i]) {
                        if (D_80770D40[i] != -1) {
                            if (D_80770D40[i] < pan) {
                                if ((D_80770D40[i] + 8) < pan) {
                                    pan = D_80770D40[i] + 8;
                                }
                            } else if (pan < (D_80770D40[i] - 8)) {
                                pan = D_80770D40[i] - 8;
                            }
                        }
                        D_80770D40[i] = pan;
                        func_80737AC4(D_80745848[i], 4, pan);
                    }
                    if (D_80770F38 != D_80770D70[i]) {
                        D_80770D70[i] = D_80770F38;
                        func_80737AC4(D_80745848[i], 0x10, *(s32 *)&D_80770F38);
                    }
                }
            }
        }
    }

    D_807FD580 = D_807FC924->unk4->unk174;
    ctx104 = D_807FD580->unk104;
    water = ctx104->unk174;
    if (water->unkFA != 0 && D_807FC924->unk214 < (water->unk90 + 3.0f) && D_80745838 == 0 && D_807FC928 < 2) {
        D_80745838 = 1;
        seqUpdateUnderwaterAudio(0);
        seqUpdateUnderwaterAudio(1);
    }
    if ((water->unkFA == 0 || (water->unk90 + 3.0f) < D_807FC924->unk214) && D_80745838 == 1) {
        D_80745838 = 0;
        seqUpdateUnderwaterAudio(0);
        seqUpdateUnderwaterAudio(1);
    }
}

void func_806086CC(f32, f32, f32, s16, s32, s32, s32, s32, f32, s32);

void sfxPlayFromActorWithAltitudeCheck(Actor *arg0, s16 arg1, u8 arg2, s16 arg3, u8 arg4) {
    s32 var_v0;

    if (arg0->unk80 + 20.0f < arg0->unkAC && (arg1 < 0x355 || arg1 >= 0x35E)) {
        var_v0 = 0x5A;
    } else {
        var_v0 = 0;
    }
    func_806086CC(arg0->unk7C, arg0->unk80, arg0->unk84, arg1, arg2, arg3, arg4, 0x4B, 0.3f, var_v0);
}

void sfxPlayFromTargetSlot(s16 arg0, s16 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, f32 arg6) {
    func_806086CC(D_807F6000[arg0].unk0, D_807F6000[arg0].unk4, D_807F6000[arg0].unk8, arg1, arg2, arg3, arg4, arg5, arg6, 0);
}

void sfxPlayAtPosition(f32, f32, f32, s16, u8, f32, u8, u8);

void sfxPlayFromActorDirect(Actor *arg0, s16 arg1, u8 arg2, f32 arg3, u8 arg4, u8 arg5) {
    sfxPlayAtPosition(arg0->unk7C, arg0->unk80, arg0->unk84, arg1, arg2, arg3, arg4, arg5);
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

extern s32 D_807457C8;
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)

void sfxPlayAtPosition(f32 arg0, f32 arg1, f32 arg2, s16 arg3, u8 arg4, f32 arg5, u8 arg6, u8 arg7) {
    s32 dx, dy, dz;
    s32 vol;
    f32 pan;
    u8 reverb;
    f64 pad;

    reverb = 0;
    dx = D_807FC924->unk210 - arg0;
    dy = D_807FC924->unk214 - arg1;
    dz = D_807FC924->unk218 - arg2;
    D_80770DE4 = sqrtf((f32)(dx * dx + dy * dy + dz * dz));
    if (D_80770DE4 < 1.0f) {
        D_80770DE4 = 1.0f;
    }
    vol = (s32)(((f64)((f32)(arg7 * 4000) / sqrtf(D_80770DE4))) - (((f64)(f32)(arg7 * 4000) / 7.74596600000000013) - 32767.0));
    if (vol >= 0x8000) {
        vol = 0x7FFF;
    }
    vol = (s32)((f64)(arg4 * vol) / 255.0);
    if (vol >= 0x8000) {
        vol = 0x7FFF;
    }
    if (vol < 1001) {
        return;
    }
    vol = (s32)((f64)(arg4 * vol) / 255.0);
    if (arg6 != 0) {
        vol = (s32)((1.0 - (((f64)(u32)func_806119A0() / 4294967295.0) * ((f64)(u32)arg6 / 155.0))) * (f64)vol);
        arg5 = ((f64)arg5 - ((f64)(u32)arg6 / 255.0)) + (((f64)(u32)func_806119A0() / 4294967295.0) * ((f64)(u32)arg6 / 100.0));
    }
    pan = mathAngleBetweenPointsRad(D_807FC924->unk210, D_807FC924->unk218, arg0, arg2) - D_807FC924->unk2C4;
    if (pan < 0.0f) {
        pan += 6.2831855f;
    }
    if (pan > 0.7853982f && (f64)pan < 5.497787296772003) {
        vol = (s32)((((f64)func_80612D1C(((2.0 * (f64)pan) / 3.0) + 2.617993950843811) * 0.3) + 1.0) * (f64)vol);
    }
    pan = (f32)((f64)(1.0f - func_80612D1C(pan)) * 63.5);
    if (D_80745838 != 0) {
        reverb = 30;
    } else if (D_8077058E >= 21) {
        reverb = (D_8077058E * 100) / 255;
    }
    if (D_807457C8 != 0) {
        n_alSndpDeallocate(D_807457C8);
    }
    osSetThreadPri(NULL, 26);
    if (arg3 < 0x800) {
        n_alSndpAllocate(D_8076D1F8, arg3, (u16)vol, (u8)pan, arg5, reverb, &D_807457C8);
    } else {
        n_alSndpAllocate(D_8076D1FC, arg3 - 0x7FF, (u16)vol, (u8)pan, arg5, reverb, &D_807457C8);
    }
    osSetThreadPri(NULL, 10);
}

#pragma intrinsic(sqrtf)

extern u8 D_807FC929;

typedef struct {
    char pad[0xC4];
    s32 unkC4;
} Aud7130M2_SoundContextD580;

void func_80609B80(f32, f32, f32, s16, u8, u8, u8, u8, f32);

void func_80609B80(f32 arg0, f32 arg1, f32 arg2, s16 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7, f32 arg8) {
    s32 dx;
    s32 dy;
    s32 dz;
    s32 vol;
    f32 angle;
    f32 pitch;
    u8 sp47;
    u8 sp46;

    sp47 = 0;
    sp46 = 0;

    if (((Aud7130M2_SoundContextD580 *)D_807FD580)->unkC4 != 0) {
        n_alSndpDeallocate(((Aud7130M2_SoundContextD580 *)D_807FD580)->unkC4);
    }

    angle = mathAngleBetweenPointsRad(D_807FC924[D_807FC929].unk210, D_807FC924[D_807FC929].unk218, arg0, arg2) - D_807FC924[D_807FC929].unk2C4;
    if (angle < 0.0f) {
        angle += 6.2831855f;
    }

    if (angle > 1.5707964f && (f64)angle < 4.71238911151886) {
        sp47 = 1;
    }

    if (arg7 == 0) {
        vol = ((f64)(u32)arg4 * 32767.0) / 255.0;
        if (D_80770DE4 < 23.0f) {
            angle = 0.0f;
        }
    } else {
        dx = D_807FC924[D_807FC929].unk210 - arg0;
        dy = D_807FC924[D_807FC929].unk214 - arg1;
        dz = D_807FC924[D_807FC929].unk218 - arg2;
        D_80770DE4 = sqrtf((f32)(dx * dx + dy * dy + dz * dz));

        if (D_80770DE4 < 23.0f) {
            angle = 0.0f;
            sp47 = 0;
        }

        if (angle > 0.7853982f && (f64)angle < 5.497787296772003) {
            D_80770DE4 = (1.0f - (func_80612D1C(((2.0 * (f64)angle) / 3.0) + 2.617993950843811) * arg8)) * D_80770DE4;
        }

        if (D_80770DE4 < 1.0f) {
            D_80770DE4 = 1.0f;
        }

        vol = (((f32)(arg7 * 4000) / sqrtf(D_80770DE4)) - (((f32)(arg7 * 4000) / 7.74596600000000013) - 32767.0));
        if (vol >= 0x8000) {
            vol = 0x7FFF;
        }
        vol = ((f64)(arg4 * vol)) / 255.0;
    }

    if (vol >= 1001) {
        if (arg6 != 0) {
            vol = (1.0 - (((f64)(u32)func_806119A0() / 4294967295.0) * ((f64)(u32)arg6 / 155.0))) * (f64)vol;
            pitch = (((f64)(u32)func_806119A0() / 4294967295.0) * ((f64)(u32)arg6 / 100.0)) + (1.0 - ((f64)(u32)arg6 / 255.0));
        } else {
            pitch = 1.0f;
        }

        pitch = (f32)(((f64)((f32)(u32)arg5 * pitch)) / 127.0);

        if (D_8077058E >= 21) {
            sp46 = (D_8077058E * 100) / 255;
        }

        angle = (f32)((f64)(1.0f - func_80612D1C(angle)) * 63.5);

        if (sp47 != 0) {
            sp46 |= 0x80;
        }

        n_alSndpAllocate(D_8076D1F8, arg3, (u16)vol, (u8)angle, pitch, sp46, &((Aud7130M2_SoundContextD580 *)D_807FD580)->unkC4);
    }
}

typedef struct {
    u8 pad[0xF8];
} AudioCSeq;

extern s32 D_8000DDCC;
extern s32 D_8076D200[];
extern void *D_8076BF38[];
extern AudioCSeq D_8076BF48[];
extern u8 D_80770598[];

void *func_80610FE8(s32);
void heapFree(void *);
void func_8060B140(s32, void *, s32 *, s32, s32, s32, void *);
void n_alCSeqNew(void *, void *);
void func_80737F40(ALCSPlayer *);
void seqUpdateVolume(s32);

void seqLoadAndPlay(s32 arg0, u8 arg1, f32 arg2) {
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
    seqUpdateVolume(arg0);
    alCSPPlay(gSeqPlayers[arg0]);
}

extern s8 D_80745840;
extern s8 D_8074583C;
extern s16 D_807454F0[];
extern f32 D_807457B8[];

void seqUpdateVolume(s32 arg0) {
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

void seqSetChannelVolumeScale(s32 arg0, f32 arg1) {
    D_807457B8[arg0] = arg1;
    seqUpdateVolume(arg0);
}

extern f32 D_80770578[];

void seqUpdateVolumeFades(void) {
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
            seqUpdateVolume(i);
        }
    }
}


void seqSetTargetVolume(s32 arg0, f32 arg1) {
    D_80770578[arg0] = arg1;
    D_80770598[arg0] = 1;
}


void seqSetVolumeInstant(s32 arg0, f32 arg1) {
    D_80770578[arg0] = arg1;
    D_80770568[arg0] = arg1;
    seqUpdateVolume(arg0);
}

extern f32 D_80770588;
void seqLoadAndPlay(s32, u8, f32);

void seqPlayWithDefaultVolume(s32 arg0, u8 arg1) {
    seqLoadAndPlay(arg0, arg1, D_80770588);
}

void seqUpdateUnderwaterAudio(s32);
#ifdef NON_MATCHING
void func_8060A6A0(s32 arg0, u8 arg1, f32 arg2) {
    f64 var_fv0;
    f32 pan, vol;

    seqLoadAndPlay(arg0, arg1, arg2);
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
    seqUpdateUnderwaterAudio(arg0);
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/7130/func_8060A6A0.s")
#endif

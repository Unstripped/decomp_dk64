#include "common.h"
#include "actor.h"

void alCSPSetChlPanVolume(ALCSPlayer *, f32, f32);
void alCSPSetChlFX1Mix(ALCSPlayer *, u8, u8);

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
extern AudioPlayer *gPlayerSlots;
extern s32 gCurrentMap;
extern AmbientSfxEntry D_807459FC[];

s16 mapChunkFindByPosition(f32, f32, f32, s32);
void sfxAllocateChannel(s32, f32);
void sfxStartAreaAmbient(void) {
    u8 i;
    s16 count;
    s16 v0;

    D_80745650 = 1;
    if (D_80745654 != 0) {
        if (D_80770DD8[1] == 0xFF) {
            D_80770DD8[1] = 0;
        }
        return;
    }

    count = 29;
    if (count) {}  // FAKE: dead use of count steers uopt register priority (t0 instead of a0)
    v0 = mapChunkFindByPosition(gPlayerSlots->unk210, gPlayerSlots->unk214, gPlayerSlots->unk218, 0);

    i = 0; do {
        if (gCurrentMap == D_807459FC[i].unk0 && v0 == D_807459FC[i].unk2) {
            D_80770DC9 = D_807459FC[i].unk8;
            sfxAllocateChannel(D_807459FC[i].unk4, 1.0f);
            if (D_807459FC[i].unk6 != 0) {
                count = D_807459FC[i].unk6;
                D_80770DD8[1] = D_807459FC[i].unk6;
            }
            return;
        }
    } while (++i < count);

    D_80770DD8[1] = 0xFF;
}
void sfxStartAreaAmbient(void);
void sfxPlayCurrent(u8 arg0, u8 arg1, u8 arg2) {
    sfxStartAreaAmbient();
}

extern s16 D_807458DC[];
extern f32 D_807458F4[];
extern s16 D_80745924[];
extern s32 D_8074593C[][12];
extern u8 D_80770560[];
extern f32 D_80770568[];
extern ALCSPlayer *gSeqPlayers[];

/* The two stack arrays are block-copied from these static initialisers (D_80745B20 = -1s, D_80745B24 = 0s):
 * a struct-typed local makes the compiler emit one lw/sw copy and keep &sp68 in a callee-saved register. */
typedef struct {
    s8 b[4];
} SfxSignedBytes4;
typedef struct {
    u8 b[4];
} SfxUnsignedBytes4;
extern SfxSignedBytes4 D_80745B20;
extern SfxUnsignedBytes4 D_80745B24;

void func_8060131C(u8, s32, s32);
void func_806013E8(u8, s32, s32);
void sfxStopChannel();
void seqSetTargetVolume(s32, f32);
void seqLoadAndPlayWithReverb(s32, u8, f32);

// deadsweep round 3: full=62 text=62 inserted `if (D_8074593C && D_8074593C) {}` at line 18
void sfxUpdateChannels(void) {
    u8 i;
    u8 j;
    u8 s1;
    u8 s2;
    SfxSignedBytes4 sp68;
    SfxUnsignedBytes4 sp64;
    s32 s5;
    s32 vol;
    s32 sel;

    sp68 = D_80745B20;
    sp64 = D_80745B24;

    if (*(u8 *)&D_80745650 != 0) {
        i = 0;
        do {
            sp64.b[i] = alCSPGetState(gSeqPlayers[i]);
        } while (++i < 4);

        i = 0; do {
            s5 = D_807458DC[i];
            if (s5 != 0) {
                s1 = sfxGetChannelIndex((s16)s5);
                s2 = sfxGetBankIndex((s16)(u16)s5);  // FAKE: (u16) keeps this conv from being CSE'd with the one above
                if (s5 == D_80770560[s2] && sp64.b[s2] == 1) {
                    if (D_80745924[i] == 1) {
                        D_80745924[i] = 2;
                    }
                    if (D_80745924[i] == 2) {
                        j = 0;
                        do {
                            if (!s2) {}  // FAKE: steers uopt register order (s7/s8)
                            vol = (j & 1) ? 0 : 0xFF;
                            sel = j & 2;
                            if (D_8074593C[j][s1] != 0) {
                                if (sel) {
                                    func_8060131C(s2, D_8074593C[j][s1], vol);
                                } else {
                                    func_806013E8(s2, D_8074593C[j][s1], vol);
                                }
                                D_8074593C[j][s1] = 0;
                            }
                        } while (++j < 4);
                    }
                }
                if (!(D_80745658[s5] & 0x100) && D_80745924[i] == 2) {
                    if (sp64.b[sfxGetBankIndex((s16)(s5 ^ 0))] == 0 || s5 != D_80770560[s2]) {  // FAKE: ^ 0 keeps this conv from being CSE'd with the earlier two
                        sfxStopChannel(s5, 0);
                    }
                }
            }
        } while (++i < 12);

        i = 0;
        do {
            s5 = D_807458DC[i];
            if (s5 != 0) {
                if (D_80745658[s5] & 0x80) {
                    j = 0;
                    do {
                        sp68.b[j] = -1;
                    } while (++j < 4);
                }
                sp68.b[sfxGetBankIndex((s16)s5)] = i;
            }
        } while (++i < 12);

        if (1) {}  // FAKE: steers uopt register order (s7/s8)
        i = 0; do { // LAYOUT:
            s8 idx = sp68.b[i];
            if (sp64.b[i] != 0) {
                if (sp64.b[i] == 1) {
                    if (idx == -1) {
                        seqSetTargetVolume(i, 0.0f);
                        if ((f64)D_80770568[i] < 0.1 || D_80770560[i] == 0x4B) {
                            alSeqpStop((ALSeqPlayer *)gSeqPlayers[i]);
                        }
                    } else {
                                                if (D_80770560[i] != D_807458DC[idx] || (D_80745924[idx] == 0 && (D_80745658[D_807458DC[idx]] & 0x200))) {
                            alSeqpStop((ALSeqPlayer *)gSeqPlayers[i]);
                        } else if (D_80770568[i] == 0.0f) {
                            seqSetTargetVolume(i, D_807458F4[idx]);
                        }
                    }
                }
            } else {
                if (idx != -1) {
                                        if (D_80770560[i] == D_807458DC[idx] && D_80745924[idx] == 2) {
                        seqSetTargetVolume(i, D_807458F4[idx]);
                        alCSPPlay(gSeqPlayers[i]);
                    } else {
                        seqLoadAndPlayWithReverb(i, (u8)D_807458DC[idx], D_807458F4[idx]);
                        D_80745924[sfxGetChannelIndex(D_807458DC[idx])] = 1;
                    }
                }
            }
        } while (++i < 4);
    }
}

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
        alCSPSetTempo(gSeqPlayers[v1], (s32)((s32)alCSPGetTempo(gSeqPlayers[v1]) * arg1));
    }
}

extern f32 D_80770DDC;
extern f32 D_80770DE0;
extern f32 D_80770DE4;
f32 sinApprox(f32);
f32 cosApprox(f32);
f32 mathAngleBetweenPointsRad(f32, f32, f32, f32);
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)

f32 sfxCalcDistanceVolumePan(f32 arg0, f32 arg1, f32 arg2, u8 arg3, u8 arg4, f32 arg5) {
    f32 sp2C;
    f32 dy;
    f32 sp24;
    f32 sp20;
    f32 pad;
    f32 sp18;
    f64 diff;

    sp18 = 0.0f;
    sp2C = gPlayerSlots->unk210 - arg0;
    dy = gPlayerSlots->unk214 - arg1;
    sp24 = gPlayerSlots->unk218 - arg2;

    diff = ((f64)arg5 > 0.8) ? ((f64)arg5 - 0.8) : -((f64)arg5 - 0.8);

    if (diff < 0.1 && dy < 0.0f) {
        dy *= 20.0f;
    }

    D_80770DE4 = sqrtf((sp2C * sp2C) + (dy * dy) + (sp24 * sp24));

    if ((f64)arg5 >= 0.8) {
        f32 l_dz = gPlayerSlots->unk230 - gPlayerSlots->unk218;
        f32 l_dx = gPlayerSlots->unk228 - gPlayerSlots->unk210;
        sp18 = mathAngleBetweenPointsRad(gPlayerSlots->unk214, 0.0f, gPlayerSlots->unk22C, sqrtf((l_dz * l_dz) + (l_dx * l_dx)));

        l_dz = arg2 - gPlayerSlots->unk218;
        l_dx = arg0 - gPlayerSlots->unk210;
        D_80770DDC = mathAngleBetweenPointsRad(gPlayerSlots->unk214, 0.0f, arg1, sqrtf((l_dz * l_dz) + (l_dx * l_dx))) - sp18;

        if (D_80770DDC < 0.0f) {
            D_80770DDC += 6.2831855f;
        }

        if (D_80770DDC > 0.3926991f && (f64)D_80770DDC < 5.890486389398575) {
            D_80770DE4 = (1.0f - (sinApprox((f32)(((f64)D_80770DDC * 4.0 / 7.0) + 2.942101601958275)) * 4.0f)) * D_80770DE4;
        }
    }

    D_80770DDC = mathAngleBetweenPointsRad(gPlayerSlots->unk210, gPlayerSlots->unk218, arg0, arg2) - gPlayerSlots->unk2C4;
    if (D_80770DDC < 0.0f) {
        D_80770DDC += 6.2831855f;
    }

    if (D_80770DDC > 0.7853982f && (f64)D_80770DDC < 5.497787296772003 && (f64)sp18 < 4.0) {
        D_80770DE4 = (1.0f - (sinApprox((f32)(((2.0 * (f64)D_80770DDC) / 3.0) + 2.617993950843811)) * arg5)) * D_80770DE4;
    }

    if (D_80770DE4 < 1.0f) {
        D_80770DE4 = 1.0f;
    }

    {
        f32 dist = (f32)(arg4 * 0xFA0);
        f64 temp = ((f64)(dist / sqrtf(D_80770DE4))) - (((f64)dist * 0.12909946) - 32767.0);
        f64 a3_f64 = (f64)arg3;
        sp20 = (f32)(temp * a3_f64 * 0.00392156862745098);
    }

    if (sp20 < 10.0f) {
        return 0.0f;
    }

    D_80770DE0 = cosApprox(D_80770DDC);
    D_80770DDC = (f32)((f64)(1.0f - sinApprox(D_80770DDC)) * 63.5);

    if (sp20 < 10.0f) {
        return 0.0f;
    }

    if (sp20 > 32767.0f) {
        sp20 = 32767.0f;
    }

    return sp20;
}

f32 sfxCalcDistanceVolumePan(f32, f32, f32, u8, u8, f32);
extern f32 D_80770DE8;
extern f32 D_80770DEC;
f32 D_80770DF0;
f32 D_80770DF4;

f32 sfxUpdateDistanceVolumeAndPan(f32 arg0, f32 arg1, f32 arg2, u8 arg3, u8 arg4, f32 arg5)
{
    f32 ret;
    f32 temp;

    ret = sfxCalcDistanceVolumePan(arg0, arg1, arg2, arg3, arg4, arg5);
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
s32 D_80770DF8[16];
u32 D_80770E38[16];
f32 D_80770E78[16];
f32 D_80770EB8[16];
f32 D_80770EF8[16];
extern u32 D_807FBB60;
extern SoundContextD580 *gActivePlayerState;

s32 func_8062F388(LevelSoundEmitter **);
void actorTargetEntriesUpdateSfx(s32, s32, s32, f32);
s32 flagGet(s32, s32);
void n_alSndpPostEvent(s32, s32, ...);
f32 func_80611BB4(f32, f32);
void n_alSndpPlay(s32, s16, s32, s32, f32, s32, s32 *);
void n_alSndpStop(s32);
void seqSetVolumeInstant(s32, f32);

void sfxUpdateLevelAmbient(void) {
    s8 spE7;
    s8 spE6;
    u8 spE5;
    u8 tD;
    s32 n;
    s32 var_s1;
    s16 s2;
    s16 s0;
    f32 var_fs1;
    f32 var_fs0;
    f32 spCC;
    u32 spC8;
    s16 spC4;
    AmbientEmitter *spC0;
    LevelSoundEmitter *spBC;

    spE7 = -1;
    spE5 = 0;

    switch (gCurrentMap) {
    case 7:
        if (D_8077058C[0] == 0) {}  // FAKE: dead statement steers uopt colouring
        var_s1 = 7;
        spC0 = D_80745F74;
        break;
    case 0x26:
        var_s1 = 4;
        spC0 = D_80745FD8;
        break;
    case 0x1E:
        var_s1 = 3;
        spC0 = D_80746010;
        break;
    case 0x27:
        var_s1 = 4;
        spC0 = D_8074603C;
        break;
    case 0x1A:
        var_s1 = 4;
        spC0 = D_80746074;
        break;
    case 0xE:
        var_s1 = 4;
        spC0 = D_807460AC;
        break;
    case 0x1B:
        var_s1 = 10;
        spC0 = D_807460E4;
        break;
    case 0x37:
        var_s1 = 7;
        spC0 = D_807461E0;
        break;
    case 0x22:
        var_s1 = 4;
        spC0 = D_80746244;
        break;
    case 0xB0:
        var_s1 = 3;
        spC0 = D_8074627C;
        break;
    case 0x30:
        spC0 = D_80746170;
        var_s1 = 8;
        if (gActivePlayerState->unk1F0 & 0x100000) {
            sfxStopChannel(0x44, 0);
            if (sfxGetChannelVolume(0x44) < 0.1) {
                sfxAllocateChannel(0x46, 1.0f);
            }
        } else {
            sfxStopChannel(0x46, 0);
            if (sfxGetChannelVolume(0x46) < 0.1) {
                sfxAllocateChannel(0x44, 1.0f);
            }
        }
        break;
    default:
        var_s1 = 0;
        break;
    }

    if (var_s1 != 0 && *(u8 *)&D_80745650 != 0 && D_80745654 == 0) {
        D_80770DD4 = 1000000.0f;
        var_fs1 = 0.0f;
        s0 = 0;
        n = var_s1;
        if (var_s1 > 0) {
            do {
                AmbientEmitter *entry = (AmbientEmitter *)((s32)spC0 + s0 * 14);
                f32 dx = gPlayerSlots->unk210 - (f32)entry->unk0;
                f32 dz = gPlayerSlots->unk218 - (f32)entry->unk4;
                if (entry->unk6 == -1) {
                    D_80770DE4 = sqrtf(dx * dx + dz * dz);
                    if (D_80770DE4 < (f32)(entry->unk8 - 20)) {
                        sfxAllocateChannel(entry->unkB, 1.0f);
                    } else if (D_80770DE4 > (f32)entry->unk8) {
                        sfxStopChannel(entry->unkB, 0);
                    }
                } else {
                    f32 dy = gPlayerSlots->unk214 - (f32)entry->unk2;
                    D_80770DE4 = sqrtf(dx * dx + dy * dy + dz * dz);
                    if (s0 == 0 || D_80770DE4 < D_80770DD4) {
                        spE7 = s0;
                        D_80770DD4 = D_80770DE4;
                        var_fs0 = ((f64)func_80611BB4(dx, dz) * 4096.0) / 6.2831854820251465 - (f64)entry->unk6;
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
            } while (s0 < n);
        }
        D_80770DE4 = D_80770DD4;
        if (spE7 >= 0 && D_80770DE4 < (f32)spC0[spE7].unk8) {
            if (spC0[spE7].unk6 >= 0x1001) {
                D_80770DC9 = spC0[spE7].unk6 & 1;
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
                    sfxAllocateChannel(spC0[spE7].unkC, 1.0f);
                }
            }
            if (D_80770DC9 != 0) {
                D_80770DC8 = spC0[spE7].unkA;
            } else {
                D_80770DC8 = 0;
            }
            D_80770DD9 = spC0[spE7].unkB;
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
        if (D_80770DD8[1] == 0xFF) {
            D_80770DD8[1] = spC0[spE7].unkB;
            D_80770DC8 = spC0[spE7].unkA;
            if (D_80770DC9 == 0) {
                sfxAllocateChannel(spC0[spE7].unkC, 1.0f);
            }
        }
        if (D_80770DC9 != 0 && D_80770DD8[1] != 0) {
            sfxAllocateChannel(D_80770DD8[1], 1.0f);
        } else if (D_80745838 != 0) {
            seqSetTargetVolume(0, 1.0f);
        } else {
            sfxStopChannel(D_80770DD8[1], 0);
        }
        D_80770DCA = D_80770DC9;
        if (var_fs1 != 0.0f) {
            if ((tD = spC0[spE7].unkD)) {  // FAKE: u8 copy steers the lbu/move a0 pair
                sfxAllocateChannel(tD, 1.0f);
            }
        }
        if (D_80770560[2] == 0x26) {
            seqSetVolumeInstant(2, (f32)((f64)var_fs1 / 32767.0));
        }
        var_fs1 = ((var_fs1 - 28384.0f) * 100.0f) / 4383.0f;
        if (var_fs1 < 0.0f) {
            var_fs1 = 0.0f;
        }
        var_fs1 = (f32)((f64)(u32)D_80745BDC[gCurrentMap][1] + (((255.0 - (f64)(u32)D_80745BDC[gCurrentMap][1]) * ((f64)(u32)D_80770DC8 / 127.0) * (f64)var_fs1) / 255.0));
        D_8077058E = (u8)(u32)var_fs1;
    } else {
        D_8077058E = D_80745BDC[gCurrentMap][1];
    }
    if (D_80770DE8 && D_80770DE8) {}  // FAKE: dead statement steers uopt colouring

    if (D_80745838 != 0) {
        D_8077058E = 0xFF;
    }

    if (D_8077058E != D_8077058D) {
        var_fs0 = (f32)(((f64)(u32)D_8077058E * 0.3) / 255.0);
        var_fs1 = (f32)((((f64)(u32)D_8077058E * 0.35) / 255.0) + 1.0);
        spC8 = D_8077058E;  // FAKE: u32 copy of the byte steers its typed-constant web (spC8 is reassigned below)
        if (gCurrentMap == 0xE) {
            if (spC8 != 0) {
                s0 = 4;  // FAKE: dead store stops uopt hoisting the loop-init s0 = 0 above the seqSetVolumeInstant calls
                seqSetVolumeInstant(0, 1.0f);
            } else {
                seqSetVolumeInstant(0, 0.6f);
            }
            alCSPSetChlPanVolume(gSeqPlayers[0], var_fs0, var_fs1);
        }
        for (s0 = 0; s0 < 4; s0++) {
            if (D_80745658[D_80770560[s0]] & 1) {
                alCSPSetChlPanVolume(gSeqPlayers[s0], var_fs0, var_fs1);
            } else {
                alCSPSetChlPanVolume(gSeqPlayers[s0], 0.0f, 1.0f);
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
                    actorTargetEntriesUpdateSfx(1, 0xFF, 0xC8, 0.3f);
                }
                for (s0 = spC8 - 1; s0 >= 0; s0--) {
                    if (s2 + 1 == spBC[s0].unk7) {
                        sfxUpdateDistanceVolumeAndPan((f32)spBC[s0].unk0, (f32)spBC[s0].unk2, (f32)spBC[s0].unk4,
                            (u8)((spBC[s0].unk6 * D_80745B28[s2].unk2) / 255.0),
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
            var_fs1 = (f32)((f64)var_fs1 * 0.6);
            if ((D_80767CC0 / 12U) != D_80770E38[s2]) {
                D_80770E38[s2] = (D_80767CC0 / 12U);
                if (var_fs1 > 10.0f) {
                    n_alSndpPlay(D_8076D1F8, D_80745B28[s2].unk0, (u16)var_fs1, 0x3F, 0.4f, 0, &D_80770DF8[s2]);
                    D_80770EB8[s2] = var_fs1 + 1.0f;
                    D_80770EF8[s2] = 300.0f;
                }
            }
        }
        if (var_fs1 != D_80770EB8[s2] || D_80770DF8[s2] == 0) {
            if (var_fs1 > 10.0f) {
                if (D_80770DF8[s2] == 0) {
                    spC4 = D_80745B28[s2].unk0;
                    if (spC4 < 0x800) {
                        n_alSndpPlay(D_8076D1F8, spC4, (u16)var_fs1, 0x3F, D_80745B28[s2].unk8, 0, &D_80770DF8[s2]);
                    } else {
                        n_alSndpPlay(D_8076D1FC, spC4 - 0x7FF, (u16)var_fs1, 0x3F, D_80745B28[s2].unk8, 0, &D_80770DF8[s2]);
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
                        if (D_8077058D && D_8077058D) {}  // FAKE: dead statement steers uopt colouring
                        if (D_80770EF8[s2] + 8.0f < var_fs0) {
                            var_fs0 = D_80770EF8[s2] + 8.0f;
                        }
                    } else {
                        if (var_fs0 < D_80770EF8[s2] - 8.0f) {
                            var_fs0 = D_80770EF8[s2] - 8.0f;
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
        if (D_80770DC8) {}  // FAKE: dead statement steers uopt colouring
        D_8077058C[0] = 0;
    }
    if (D_8077058C[0] != 0) {
        if (D_807457DC == 0) {
            n_alSndpPlay(D_8076D1F8, 0x125, 0, 0x3F, 1.0f, 0, &D_807457DC);
        }
        if (D_807457DC != 0) {
            n_alSndpPostEvent(D_807457DC, 8, (s32)(((f64)(u32)D_8077058C[0] * 10767.0) / 255.0));
            spCC = (f32)(1.0 - (((f64)(u32)D_8077058E * 0.5) / 255));
            if (D_80770DC9 & (D_80770DD4 < 1000.0f)) {
                var_fs0 = mathAngleBetweenPointsRad(gPlayerSlots->unk210, gPlayerSlots->unk218, (f32)spC0[spE7].unk0, (f32)spC0[spE7].unk4) - gPlayerSlots->unk2C4;
                if (var_fs0 < 0.0f) {
                    var_fs0 += 6.2831855f;
                }
                if (var_fs0 > 1.5707964f && (f64)var_fs0 < 4.71238911151886) {
                    D_80770DD0 = 128.0f;
                } else {
                    D_80770DD0 = 0.0f;
                }
                D_80770DCC = (f32)((f64)(1.0f - sinApprox(var_fs0)) * 63.5);
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

extern ALCSPlayer *D_8076BF24;

void sfxSetChannelParam();

void seqUpdateUnderwaterAudio(s32 arg0) {
    if (D_80745838 != 0) {
        if (arg0 == 0 && (D_80745658[D_80770560[arg0]] & 1)) {
            alCSPSetChlPanVolume(gSeqPlayers[0], 0.3f, 1.35f);
        }
        if (D_80770560[arg0] == 0x38) {
            sfxSetChannelParam(0x38, 0x3C00, 1);
        }
        if (D_80770560[arg0] == 0x60) {
            if (gCurrentMap == 0xB8) {
                sfxSetChannelParam(0x60, 0xE, 1);
            } else {
                sfxSetChannelParam(0x60, 8, 1);
                alCSPSetChlFX1Mix(D_8076BF24, 1, 0x7F);
                alCSPSetChlFX1Mix(D_8076BF24, 2, 0x7F);
            }
            sfxSetChannelParam(0x60, 0x10, 0);
        }
    } else {
        if (arg0 == 0 && (D_80745658[D_80770560[arg0]] & 1)) {
            alCSPSetChlPanVolume(gSeqPlayers[0], 0.0f, 1.0f);
        }
        if (D_80770560[arg0] == 0x38) {
            sfxSetChannelParam(0x38, 0x3C00, 0);
        }
        if (D_80770560[arg0] == 0x60) {
            if (gCurrentMap == 0xB8) {
                sfxSetChannelParam(0x60, 0x1E, 1);
                return;
            }
            sfxSetChannelParam(0x60, 0x10, 1);
            sfxSetChannelParam(0x60, 8, 0);
            alCSPSetChlFX1Mix(D_8076BF24, 1, 0x64);
            alCSPSetChlFX1Mix(D_8076BF24, 2, 0x64);
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

void sfxSlotFreeSource(s16);
void sfxStopSlotSound(Actor *arg0, u8 arg1) {
    if (((AudioActor *)arg0)->unk6E[arg1] >= 0) {
        sfxSlotFreeSource(((AudioActor *)arg0)->unk6E[arg1]);
        ((AudioActor *)arg0)->unk6E[arg1] = -1;
        if (arg1 == 0) {
            ((AudioActor *)arg0)->unk72 = 0;
        }
    }
}


void faultSetMessage(s32, s32, s32, s32);

void sfxSlotFreeSource(s16 arg0) {
    D_80770740[D_80770628[arg0]]--; if (D_80770740[D_80770628[arg0]] != 0) { // LAYOUT:
        D_80770658[D_807707A0[D_80770628[arg0]][D_80770740[D_80770628[arg0]]]] = D_80770658[D_807707A0[D_80770628[arg0]][D_80770658[arg0]]];
        D_807707A0[D_80770628[arg0]][D_80770658[arg0]] = D_807707A0[D_80770628[arg0]][D_80770740[D_80770628[arg0]]];
    } else {
        D_80770710[D_80770628[arg0]] = 0;
        D_807706F8[D_80770628[arg0]] = 0;
    }

    if (D_80770740[D_80770628[arg0]] < 0 || D_80770740[D_80770628[arg0]] >= 23) {
        faultSetMessage(9, D_80770740[D_80770628[arg0]] * 1, 0, 0);  // FAKE: keeps count out of $a1
    }

    D_807707A0[D_80770628[arg0]][D_80770740[D_80770628[arg0]]] = -1;
    D_807705F8[arg0] = -1;
    D_807705A0[arg0] = NULL;
    D_80770628[arg0] = -1;
    D_80770658[arg0] = -1;
}

s32 func_8070B318(void);
void n_alSndpStopAll(void);

extern u8 D_80750190;
extern u8 D_80770770[];

void audioResetAll(void) {
    u8 i;
    u8 j;

    i = 0;
    if (func_8070B318() == 0) {
        n_alSndpStopAll();
    }
    D_80750190 = 0;
    if (func_8070B318() != 0) {
        i = 1;
    }
    for (; i < 4; i++) {
        alCSPSetChlPanVolume(gSeqPlayers[i], 0.0f, 1.0f);
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
extern u8 gPlayerCount;

void actorGetNodePos(Actor *, s32, f32 *, f32 *, f32 *);
void modelSlotGetNodePos(s16, s32, s32, f32 *, f32 *, f32 *);
void modelAnimEntryGetState(s16, s16, s16 *, f32 *, u8 *);
s32 hashTableLookup(s32);
s16 sfxPlayOnFreeSlot(s16, s32, f32, f32, u8, u8);
u32 randomLcgNext(void);
f32 func_80612790(s16);
f32 func_80612794(s16);

#define RAND_UNIT() (randomLcgNext() / 4294967295.0)
#define SLOT_ACTOR(idx) ((AudioActor *)D_807705A0[idx])

void sfxUpdateSourceGroups(void) {
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
    // Emits no code, but keeps &gActivePlayerState out of a register so the store/reload after the loop stays split.
    if (gActivePlayerState != NULL) {}
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
                sfxSlotFreeSource(D_807707A0[i][j]);
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
            sfxPlayOnFreeSlot(0x88, volume, D_80770DDC, 1.0f, 5, fxFlags);
        } else {
            if (D_80745848[i] != 0) {
                if (D_80770710[i] == 0) {
                    if (D_807706E0[i] != 0) {
                        D_807706E0[i]--;
                    } else {
                        n_alSndpStop(D_80745848[i]);
                        D_80770770[i] = 0;
                        D_807706E0[i] = 10;
                    }
                }
            } else if (D_80770710[i] != 0) {
                if (D_80770710[i] == 0x128 || D_80770710[i] == 0x306) {
                    if (D_80770CC8[i] == 0) {
                        n_alSndpPlay(D_8076D1F8, D_80770710[i], 0, 0x3F, D_80770C18[i], 0, &D_80745848[i]);
                        D_80770CC8[i] = 1;
                    } else {
                        slotIdx = D_807707A0[i][0];
                        sfxStopSlotSound(D_807705A0[slotIdx], 0);
                    }
                } else if (D_80770710[i] < 0x800) {
                    n_alSndpPlay(D_8076D1F8, D_80770710[i], 0, 0x3F, D_80770C18[i], 0, &D_80745848[i]);
                } else {
                    n_alSndpPlay(D_8076D1FC, D_80770710[i] - 0x7FF, 0, 0x3F, D_80770C18[i], 0, &D_80745848[i]);
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
                                    modelSlotGetNodePos(D_807705F8[D_807707A0[i][j]], 1, D_80770CF8[i], &posX, &posY, &posZ);
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
                            factor = sinApprox((animFrame / 27.0) * 3.1415927410125732);
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
                                sfxSlotFreeSource(D_807707A0[i][0]);
                                D_807F6000[slot].unk7C->unk10 = -1;
                            }
                            break;
                        case 0x11F:
                            if (D_807706F8[i] != 0) {
                                factor = sinApprox(D_80770BC0[i] * 0.027925);
                                D_80770C18[i] = (sinApprox((D_80770BC0[i] * 0.261799) - 1.570795) * 0.1) + (0.2 * factor) + 0.6;
                                D_80770BC0[i] += 1.0f;
                                if (D_80770788[D_807707A0[i][0]] == 0) {
                                    D_80770DDC = 63.0f;
                                    D_80770DF4 = 100.0f;
                                    D_80770DF0 = 0.0f;
                                }
                            } else {
                                factor = sinApprox(D_80770BC0[i] * 0.027925);
                                D_80770C18[i] = (sinApprox((D_80770BC0[i] * 0.261799) - 1.570795) * 0.1) + (0.5 * factor) + 0.6;
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
                                        sfxSlotFreeSource(D_807707A0[i][0]);
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
                                    D_80770BC0[i] = randomLcgNext();
                                    if (D_80770DF0 < D_80770DF4) {
                                        fxFlags |= 0x80;
                                    }
                                    sfxPlayOnFreeSlot((randomLcgNext() & 3) + 0x90, volume, D_80770DDC, 1.0f, 0x1E, fxFlags);
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
                        if (gCurrentMap == 0xE || gCurrentMap == 0x52) {
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
                    n_alSndpPostEvent(D_80745848[i], 0x100, fxFlags);
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
                        n_alSndpPostEvent(D_80745848[i], 8, (s32)volume);
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
                        n_alSndpPostEvent(D_80745848[i], 4, pan);
                    }
                    if (D_80770F38 != D_80770D70[i]) {
                        D_80770D70[i] = D_80770F38;
                        n_alSndpPostEvent(D_80745848[i], 0x10, *(s32 *)&D_80770F38);
                    }
                }
            }
        }
    }

    gActivePlayerState = gPlayerSlots->unk4->unk174;
    ctx104 = gActivePlayerState->unk104;
    water = ctx104->unk174;
    if (water->unkFA != 0 && gPlayerSlots->unk214 < (water->unk90 + 3.0f) && D_80745838 == 0 && gPlayerCount < 2) {
        D_80745838 = 1;
        seqUpdateUnderwaterAudio(0);
        seqUpdateUnderwaterAudio(1);
    }
    if ((water->unkFA == 0 || (water->unk90 + 3.0f) < gPlayerSlots->unk214) && D_80745838 == 1) {
        D_80745838 = 0;
        seqUpdateUnderwaterAudio(0);
        seqUpdateUnderwaterAudio(1);
    }
}

s16 sfxPlayAtPositionPooled(f32, f32, f32, s16, u8, s16, u8, u8, f32, u8);

void sfxPlayFromActorWithAltitudeCheck(Actor *arg0, s16 arg1, u8 arg2, s16 arg3, u8 arg4) {
    s32 var_v0;

    if (arg0->unk80 + 20.0f < arg0->unkAC && (arg1 < 0x355 || arg1 >= 0x35E)) {
        var_v0 = 0x5A;
    } else {
        var_v0 = 0;
    }
    sfxPlayAtPositionPooled(arg0->unk7C, arg0->unk80, arg0->unk84, arg1, arg2, arg3, arg4, 0x4B, 0.3f, var_v0);
}

void sfxPlayFromTargetSlot(s16 arg0, s16 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, f32 arg6) {
    sfxPlayAtPositionPooled(D_807F6000[arg0].unk0, D_807F6000[arg0].unk4, D_807F6000[arg0].unk8, arg1, arg2, arg3, arg4, arg5, arg6, 0);
}

void sfxPlayAtPosition(f32, f32, f32, s16, u8, f32, u8, u8);

void sfxPlayFromActorDirect(Actor *arg0, s16 arg1, u8 arg2, f32 arg3, u8 arg4, u8 arg5) {
    sfxPlayAtPosition(arg0->unk7C, arg0->unk80, arg0->unk84, arg1, arg2, arg3, arg4, arg5);
}

extern u8 gPlayerCount;

void camGetPathStartPose(s16 *, s16 *, s16 *, s16 *);
s16 sfxPlayOnFreeSlot(s16, s32, f32, f32, u8, u8);

#pragma intrinsic(sqrtf)

s16 sfxPlayAtPositionPooled(f32 arg0, f32 arg1, f32 arg2, s16 arg3, u8 arg4, s16 arg5, u8 arg6, u8 arg7, f32 arg8, u8 arg9) {
    f32 diff;
    f32 angle2;
    s32 dist;
    s32 var_a1;
    f32 sp74;
    u8 closest_idx;
    u8 i;
    s32 pad0;  // FAKE: unused locals reserve 12 bytes of frame
    s32 pad1;
    s32 pad2;
    s16 pos[4];

    D_80770DE4 = -1.0f;
    closest_idx = 0;
    for (i = 0; i < gPlayerCount; i++) {
        if (gPlayerSlots[i].unk0 != 0) {
            s32 dx = gPlayerSlots[i].unk210 - arg0;
            s32 dy = gPlayerSlots[i].unk214 - arg1;
            s32 dz = gPlayerSlots[i].unk218 - arg2;
            dist = dx * dx + dy * dy + dz * dz;
            if (D_80770DE4 == -1.0f || (f32)dist < D_80770DE4) {
                closest_idx = i;
                D_80770DE4 = dist;
            }
        }
    }

    if (D_80770DE4 == -1.0f) {
        return -1;
    }

    pos[0] = gPlayerSlots[closest_idx].unk210;
    pos[1] = gPlayerSlots[closest_idx].unk214;
    pos[2] = gPlayerSlots[closest_idx].unk218;
    pos[3] = (gPlayerSlots[closest_idx].unk2C4 * 4096.0) / 6.2831854820251465;
    camGetPathStartPose(&pos[0], &pos[1], &pos[2], &pos[3]);

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
        if (gPlayerCount == 1 && (f64)arg8 >= 0.8) {
            arg0 = mathAngleBetweenPointsRad(pos[1], 0.0f, arg1, sqrtf(((arg0 - pos[0]) * (arg0 - pos[0])) + ((arg2 - pos[2]) * (arg2 - pos[2]))));
            angle2 = mathAngleBetweenPointsRad(pos[1], 0.0f, gPlayerSlots->unk22C, sqrtf(((gPlayerSlots->unk228 - pos[0]) * (gPlayerSlots->unk228 - pos[0])) + ((gPlayerSlots->unk230 - pos[2]) * (gPlayerSlots->unk230 - pos[2]))));
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
            D_80770DE4 = (1.0f - (sinApprox(((2.0 * (f64)sp74) / 3.0) + 2.617993950843811) * arg8)) * D_80770DE4;
        }
        if (D_80770DE4 < 1.0f) {
            D_80770DE4 = 1.0f;
        }

        var_a1 = (((f32)(arg7 * 4000) / sqrtf(D_80770DE4)) - (((f32)(arg7 * 4000) / 7.74596600000000013) - 32767.0));
        if (var_a1 >= 0x8000) {
            var_a1 = 0x7FFF;
        }
        var_a1 = (arg4 * var_a1) / 255.0;
    }

    if (var_a1 >= 1001) {
        return sfxPlayOnFreeSlot(arg3, var_a1, (1.0f - sinApprox(sp74)) * 63.5, (f64)arg5 / 127.0, arg6, arg9);
    }
    return -1;
}

u32 randomLcgNext(void);
void n_alSndpSetPriority(s32, s32);
extern s32 D_807457D0[];
extern u8 D_807457D8;
extern s32 D_807457E4[];
extern u8 D_80745834;

void sfxPlayWithRandomPan(arg0, arg1, arg2, arg3, arg4)
s16 arg0;
u8 arg1;
u8 arg2;
u8 arg3;
u8 arg4;
{
    s32 vol;
    f32 pan;
    f32 pitch;
    u8 reverb = 0;

    vol = (s32)(((f64)(arg1 * 0x7FFF)) / 255.0);
    if (vol < 1001) {
        return;
    }

    pitch = (f64)(u32)arg2 / 127.0;
    pan = ((f64)(u32)randomLcgNext() / 4294967295.0) * (2.0 * (f64)(u32)arg3) + (63.5 - (f64)(u32)arg3);

    if (arg3 != 0) {
        vol = (1.0 - (((f64)(u32)randomLcgNext() / 4294967295.0) * ((f64)(u32)arg3 / 155.0))) * (f64)vol;
        pitch = (((f64)(u32)randomLcgNext() / 4294967295.0) * ((f64)(u32)arg3 / 100.0)) + ((f64)pitch - ((f64)(u32)arg3 / 255.0));
    }

    if (D_8077058E >= 21) {
        reverb = (D_8077058E * 100) / 255;
    }
    if (arg4 != 0) {
        reverb |= 0x80;
    }

    if (D_807457D0[D_807457D8] != 0) {
        n_alSndpStop(D_807457D0[D_807457D8]);
    }
    n_alSndpPlay(D_8076D1F8, arg0, (u16)vol, (u8)pan, pitch, reverb, &D_807457D0[D_807457D8]);
    n_alSndpSetPriority(D_807457D0[D_807457D8], 0);
    D_807457D8 ^= 1;
}

s16 sfxPlayOnFreeSlot(s16 arg0, s32 arg1, f32 arg2, f32 arg3, u8 arg4, u8 arg5) {
    s16 res;
    s16 i;

    if (arg4 != 0) {
        arg1 = (1.0 - (((f64)(u32)randomLcgNext() / 4294967295.0) * ((f64)(u32)arg4 / 155.0))) * (f64)arg1;
        arg3 = (((f64)(u32)randomLcgNext() / 4294967295.0) * ((f64)(u32)arg4 / 100.0)) + ((f64)arg3 - ((f64)(u32)arg4 / 255.0));
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
            arg5 = ((((D_8077058E * 100) / 255) < (arg5 & 0x7F)) ? (arg5 & 0x7F) : ((D_8077058E * 100) / 255)) | (arg5 & 0x80);
        }

        if (arg0 < 0x800) {
            n_alSndpPlay(D_8076D1F8, arg0, (u16)arg1, (u8)arg2, arg3, arg5, &D_807457E4[D_80745834]);
        } else {
            n_alSndpPlay(D_8076D1FC, arg0 - 0x7FF, (u16)arg1, (u8)arg2, arg3, arg5, &D_807457E4[D_80745834]);
        }

        if (arg0 == 0x137) {
            n_alSndpSetPriority(D_807457E4[D_80745834], 100);
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

extern s32 D_807457C8;
#pragma intrinsic(sqrtf)

void sfxPlayAtPosition(f32 arg0, f32 arg1, f32 arg2, s16 arg3, u8 arg4, f32 arg5, u8 arg6, u8 arg7) {
    s32 dx, dy, dz;
    s32 vol;
    f32 pan;
    u8 reverb;
    f64 pad;

    reverb = 0;
    dx = gPlayerSlots->unk210 - arg0;
    dy = gPlayerSlots->unk214 - arg1;
    dz = gPlayerSlots->unk218 - arg2;
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
        vol = (s32)((1.0 - (((f64)(u32)randomLcgNext() / 4294967295.0) * ((f64)(u32)arg6 / 155.0))) * (f64)vol);
        arg5 = ((f64)arg5 - ((f64)(u32)arg6 / 255.0)) + (((f64)(u32)randomLcgNext() / 4294967295.0) * ((f64)(u32)arg6 / 100.0));
    }
    pan = mathAngleBetweenPointsRad(gPlayerSlots->unk210, gPlayerSlots->unk218, arg0, arg2) - gPlayerSlots->unk2C4;
    if (pan < 0.0f) {
        pan += 6.2831855f;
    }
    if (pan > 0.7853982f && (f64)pan < 5.497787296772003) {
        vol = (s32)((((f64)sinApprox(((2.0 * (f64)pan) / 3.0) + 2.617993950843811) * 0.3) + 1.0) * (f64)vol);
    }
    pan = (f32)((f64)(1.0f - sinApprox(pan)) * 63.5);
    if (D_80745838 != 0) {
        reverb = 30;
    } else if (D_8077058E >= 21) {
        reverb = (D_8077058E * 100) / 255;
    }
    if (D_807457C8 != 0) {
        n_alSndpStop(D_807457C8);
    }
    osSetThreadPri(NULL, 26);
    if (arg3 < 0x800) {
        n_alSndpPlay(D_8076D1F8, arg3, (u16)vol, (u8)pan, arg5, reverb, &D_807457C8);
    } else {
        n_alSndpPlay(D_8076D1FC, arg3 - 0x7FF, (u16)vol, (u8)pan, arg5, reverb, &D_807457C8);
    }
    osSetThreadPri(NULL, 10);
}

#pragma intrinsic(sqrtf)

extern u8 gCurrentPlayerIndex;

typedef struct {
    char pad[0xC4];
    s32 unkC4;
} SoundContextD580Voice;

void sfxPlayAtPositionForPlayer(f32, f32, f32, s16, u8, u8, u8, u8, f32);

void sfxPlayAtPositionForPlayer(f32 arg0, f32 arg1, f32 arg2, s16 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7, f32 arg8) {
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

    if (((SoundContextD580Voice *)gActivePlayerState)->unkC4 != 0) {
        n_alSndpStop(((SoundContextD580Voice *)gActivePlayerState)->unkC4);
    }

    angle = mathAngleBetweenPointsRad(gPlayerSlots[gCurrentPlayerIndex].unk210, gPlayerSlots[gCurrentPlayerIndex].unk218, arg0, arg2) - gPlayerSlots[gCurrentPlayerIndex].unk2C4;
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
        dx = gPlayerSlots[gCurrentPlayerIndex].unk210 - arg0;
        dy = gPlayerSlots[gCurrentPlayerIndex].unk214 - arg1;
        dz = gPlayerSlots[gCurrentPlayerIndex].unk218 - arg2;
        D_80770DE4 = sqrtf((f32)(dx * dx + dy * dy + dz * dz));

        if (D_80770DE4 < 23.0f) {
            angle = 0.0f;
            sp47 = 0;
        }

        if (angle > 0.7853982f && (f64)angle < 5.497787296772003) {
            D_80770DE4 = (1.0f - (sinApprox(((2.0 * (f64)angle) / 3.0) + 2.617993950843811) * arg8)) * D_80770DE4;
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
            vol = (1.0 - (((f64)(u32)randomLcgNext() / 4294967295.0) * ((f64)(u32)arg6 / 155.0))) * (f64)vol;
            pitch = (((f64)(u32)randomLcgNext() / 4294967295.0) * ((f64)(u32)arg6 / 100.0)) + (1.0 - ((f64)(u32)arg6 / 255.0));
        } else {
            pitch = 1.0f;
        }

        pitch = (f32)(((f64)((f32)(u32)arg5 * pitch)) / 127.0);

        if (D_8077058E >= 21) {
            sp46 = (D_8077058E * 100) / 255;
        }

        angle = (f32)((f64)(1.0f - sinApprox(angle)) * 63.5);

        if (sp47 != 0) {
            sp46 |= 0x80;
        }

        n_alSndpPlay(D_8076D1F8, arg3, (u16)vol, (u8)angle, pitch, sp46, &((SoundContextD580Voice *)gActivePlayerState)->unkC4);
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

void *heapAlloc(s32);
void heapFree(void *);
void dmaReadAssetDecompress(s32, void *, s32 *, s32, s32, s32, void *);
void n_alCSeqNew(void *, void *);
void resetCSPChannelStates(ALCSPlayer *);
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
    temp = (s32)heapAlloc(0x8000);
    {
        s32 base = D_8076D200[arg1];
        s32 addr = base + D_8000DDCC;
        s32 len = D_8076D200[arg1 + 1] - base;
        if (len & 1) {
            len++;
        }
        dmaReadAssetDecompress(addr, D_8076BF38[arg0], &len, 0x80, 0, 1, (void *)temp);
    }
    heapFree((void *)temp);
    n_alCSeqNew(&D_8076BF48[arg0], D_8076BF38[arg0]);
    alSeqpSetSeq((ALSeqPlayer *)gSeqPlayers[arg0], (ALSeq *)&D_8076BF48[arg0]);
    resetCSPChannelStates(gSeqPlayers[arg0]);
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
void seqLoadAndPlayWithReverb(s32 arg0, u8 arg1, f32 arg2) {
    f64 var_fv0;
    f32 pan, vol;

    seqLoadAndPlay(arg0, arg1, arg2);
    var_fv0 = (f64)(u32)D_8077058E;
    pan = (var_fv0 * 0.3) / 255.0;
    vol = ((var_fv0 * 0.35) / 255.0) + 1.0;
    if (arg0 != 0) {
        if (D_80745658[D_80770560[arg0]] & 1) {
            var_fv0 = (f64)(u32)D_8077058E;  // FAKE: dead reload keeps pan/vol computed before the branch
            alCSPSetChlPanVolume(gSeqPlayers[arg0], pan, vol);
        } else {
            alCSPSetChlPanVolume(gSeqPlayers[arg0], 0.0f, 1.0f);
        }
    }
    seqUpdateUnderwaterAudio(arg0);
}

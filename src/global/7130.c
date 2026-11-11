#include "common.h"
#include "seqplayer.h"
#include "map.h"
#include "actor.h"
#include "proto/global/10E1D0.h"
#include "proto/global/135D30.h"
#include "proto/global/136820.h"
#include "proto/global/13A7A0.h"
#include "proto/global/13CB30.h"
#include "proto/global/13CB50.h"
#include "proto/global/13CE70.h"
#include "proto/global/13D020.h"
#include "proto/global/13D0B0.h"
#include "proto/global/13D170.h"
#include "proto/global/13EC00.h"
#include "proto/global/13EC90.h"
#include "proto/global/15050.h"
#include "proto/global/166A0.h"
#include "proto/global/201B0.h"
#include "proto/global/2F550.h"
#include "proto/global/36880.h"
#include "proto/global/54150.h"
#include "proto/global/55B20.h"
#include "proto/global/5A50.h"
#include "proto/global/5E020.h"
#include "proto/global/68AA0.h"
#include "proto/global/69E60.h"
#include "proto/global/70FD0.h"
#include "proto/global/7130.h"
#include "proto/global/FE40.h"


extern u16 sSfxFlagTable[];

u8 sfxGetBankIndex(sfxId)
s16 sfxId;
{
    return (sSfxFlagTable[sfxId] & 6) >> 1;
}

u8 sfxGetChannelIndex(sfxId)
s16 sfxId;
{
    return (sSfxFlagTable[sfxId] & 0x78) >> 3;
}

extern u8 sSfxMode;
void sfxSetMode(mode)
u8 mode;
{
    sSfxMode = mode;
}

typedef struct {
    s16 map;
    s16 chunk;
    s16 sfxId;
    s16 altSfx;
    u8 unk8;
    u8 unk9;
} AmbientSfxEntry;

typedef struct AudioPlayer {
    u8 active;
    char pad1[3];
    Actor *actor;
    char pad8[0x208];
    f32 x;
    f32 y;
    f32 z;
    char pad21C[0xC];
    f32 lookX;
    f32 lookY;
    f32 lookZ;
    char pad234[0x90];
    f32 yaw;
    char pad2C8[0x28];
} AudioPlayer;

extern u8 sSfxAreaAmbientActive;
extern u8 D_80770DC9;
extern u8 D_80770DD8[];
extern AudioPlayer *gPlayerSlots;
extern s32 gCurrentMap;
extern AmbientSfxEntry sAmbientSfxTable[];

void sfxStartAreaAmbient(void) {
    u8 i;
    s16 count;
    s16 chunk;

    sSfxAreaAmbientActive = 1;
    if (sSfxMode != 0) {
        if (D_80770DD8[1] == 0xFF) {
            D_80770DD8[1] = 0;
        }
        return;
    }

    count = 29;
    chunk = mapChunkFindByPosition(gPlayerSlots->x, gPlayerSlots->y, gPlayerSlots->z, 0);

    i = 0; do { // LAYOUT: loop init on the do line keeps as1's order
        if (gCurrentMap == sAmbientSfxTable[i].map && chunk == sAmbientSfxTable[i].chunk) {
            D_80770DC9 = sAmbientSfxTable[i].unk8;
            sfxAllocateChannel(sAmbientSfxTable[i].sfxId, 1.0f);
            if (sAmbientSfxTable[i].altSfx != 0) {
                count = (u8)sAmbientSfxTable[i].altSfx;  // FAKE: reusing the loop bound for the alternate sfx keeps its register (a separate temp recolours the loop)
                D_80770DD8[1] = count;
            }
            return;
        }
    } while (++i < count);

    D_80770DD8[1] = 0xFF;
}
void sfxPlayCurrent(u8 unused0, u8 unused1, u8 unused2) {
    sfxStartAreaAmbient();
}

extern s16 sSfxChannelSounds[];
extern f32 sSfxChannelVolumes[];
extern s16 sSfxChannelStates[];
extern s32 sSfxChannelMasks[][12];
extern u8 D_80770560[];
extern f32 D_80770568[];
extern N_CSPlayer *gSeqPlayers[];

/* The two stack arrays are block-copied from these static initialisers (D_80745B20 = -1s, D_80745B24 = 0s):
 * a struct-typed local makes the compiler emit one lw/sw copy and keep &bankChannel in a callee-saved register. */
typedef struct {
    s8 b[4];
} SfxSignedBytes4;
typedef struct {
    u8 b[4];
} SfxUnsignedBytes4;
extern SfxSignedBytes4 D_80745B20;
extern SfxUnsignedBytes4 D_80745B24;


void sfxUpdateChannels(void) {
    u8 i;
    u8 j;
    u8 channel;
    u8 bank;
    SfxSignedBytes4 bankChannel;
    SfxUnsignedBytes4 seqState;
    s32 sfxId;
    u8 vol;
    s32 sel;

    bankChannel = D_80745B20;
    seqState = D_80745B24;

    if (sSfxAreaAmbientActive != 0) {
        i = 0;
        do {
            seqState.b[i] = alCSPGetState(&gSeqPlayers[i]->al);
        } while (++i < 4);

        i = 0; do { // LAYOUT: loop init on the do line keeps as1's order
            sfxId = sSfxChannelSounds[i];
            if (sfxId != 0) {
                channel = sfxGetChannelIndex((s16)sfxId);
                bank = sfxGetBankIndex((s16)(u16)sfxId);  // FAKE: (u16) keeps this conv from being CSE'd with the one above
                if (sfxId == D_80770560[bank] && seqState.b[bank] == 1) {
                    if (sSfxChannelStates[i] == 1) {
                        sSfxChannelStates[i] = 2;
                    }
                    if (sSfxChannelStates[i] == 2) {
                        j = 0;
                        do {
                            if (!bank) {}  // FAKE: steers uopt register order (s7/s8)
                            vol = (j & 1) ? 0 : 0xFF;
                            sel = j & 2;
                            if (sSfxChannelMasks[j][channel] != 0) {
                                if (sel) {
                                    seqPlayerSetChannelControlMask(bank, sSfxChannelMasks[j][channel], vol);
                                } else {
                                    seqPlayerSetChannelStopControlMask(bank, sSfxChannelMasks[j][channel], vol);
                                }
                                sSfxChannelMasks[j][channel] = 0;
                            }
                        } while (++j < 4);
                    }
                }
                if (!(sSfxFlagTable[sfxId] & 0x100) && sSfxChannelStates[i] == 2) {
                    if (seqState.b[sfxGetBankIndex((s16)(sfxId ^ 0))] == 0 || sfxId != D_80770560[bank]) {  // FAKE: ^ 0 keeps this conv from being CSE'd with the earlier two
                        sfxStopChannel(sfxId, 0);
                    }
                }
            }
        } while (++i < 12);

        i = 0;
        do {
            sfxId = sSfxChannelSounds[i];
            if (sfxId != 0) {
                if (sSfxFlagTable[sfxId] & 0x80) {
                    j = 0;
                    do {
                        bankChannel.b[j] = -1;
                    } while (++j < 4);
                }
                bankChannel.b[sfxGetBankIndex((s16)sfxId)] = i;
            }
        } while (++i < 12);

        if (1) {}  // FAKE: steers uopt register order (s7/s8)
        i = 0; do { // LAYOUT:
            s8 idx = bankChannel.b[i];
            if (seqState.b[i] != 0) {
                if (seqState.b[i] == 1) {
                    if (idx == -1) {
                        seqSetTargetVolume(i, 0.0f);
                        if ((f64)D_80770568[i] < 0.1 || D_80770560[i] == 0x4B) {
                            alSeqpStop((ALSeqPlayer *)gSeqPlayers[i]);
                        }
                    } else {
                        if (D_80770560[i] != sSfxChannelSounds[idx] || (sSfxChannelStates[idx] == 0 && (sSfxFlagTable[sSfxChannelSounds[idx]] & 0x200))) {
                            alSeqpStop((ALSeqPlayer *)gSeqPlayers[i]);
                        } else if (D_80770568[i] == 0.0f) {
                            seqSetTargetVolume(i, sSfxChannelVolumes[idx]);
                        }
                    }
                }
            } else {
                if (idx != -1) {
                    if (D_80770560[i] == sSfxChannelSounds[idx] && sSfxChannelStates[idx] == 2) {
                        seqSetTargetVolume(i, sSfxChannelVolumes[idx]);
                        alCSPPlay(&gSeqPlayers[i]->al);
                    } else {
                        seqLoadAndPlayWithReverb(i, (u8)sSfxChannelSounds[idx], sSfxChannelVolumes[idx]);
                        sSfxChannelStates[sfxGetChannelIndex(sSfxChannelSounds[idx])] = 1;
                    }
                }
            }
        } while (++i < 4);
    }
}

extern s16 sSfxChannelSounds[];
extern f32 sSfxChannelVolumes[];
extern s16 sSfxChannelStates[];
extern s32 sSfxChannelMasks[][12];

void sfxAllocateChannel(s32 sfxId, f32 volume) {
    u8 channel;
    u8 i;
    s32 current;

    channel = sfxGetChannelIndex((s16)sfxId);
    if (sfxId != 0) {
        current = sSfxChannelSounds[channel];
        if (sfxId == current && (sSfxFlagTable[sfxId] & 0x200) == 0) {
            return;
        }
        sSfxChannelSounds[channel] = sfxId;
        sSfxChannelVolumes[channel] = volume;
        sSfxChannelStates[channel] = 0;
        for (i = 0; i < 4; i++) {
            sSfxChannelMasks[i][channel] = 0;
        }
    }
}

extern u8 D_80770560[];
void sfxStopChannel(sfxId, stopSeq)
s32 sfxId;
u8 stopSeq;
{
    u8 channel = sfxGetChannelIndex((s16)sfxId);
    u8 bank = sfxGetBankIndex((s16)sfxId);
    if (sfxId != 0 && sfxId == sSfxChannelSounds[channel]) {
        sSfxChannelSounds[channel] = 0;
        sSfxChannelStates[channel] = 0;
        if (stopSeq != 0) {
            if (sfxId == D_80770560[bank]) {
                alSeqpStop((ALSeqPlayer *)gSeqPlayers[bank]);
            }
        }
    }
}

void sfxStopAllChannels(void) {
    u8 i;
    for (i = 0; i < 12; i++) {
        if (sSfxChannelSounds[i] != 0) {
            sfxStopChannel(sSfxChannelSounds[i], 1);
        }
    }
}



void seqRouteChannelVolume(s32 sfxId, f32 volume) {
    u8 bank = sfxGetBankIndex((s16)sfxId);
    if ((sfxId == sSfxChannelSounds[sfxGetChannelIndex((s16)sfxId)]) && (sfxId == D_80770560[bank])) {
        seqSetTargetVolume(bank, volume);
    }
}



void sfxSetChannelParam(sfxId, mask, slot)
s32 sfxId;
s32 mask;
u8 slot;
{
    s32 channel = sfxGetChannelIndex((s16)sfxId);
    if (sfxId == sSfxChannelSounds[channel]) {
        sSfxChannelMasks[slot][channel] = mask;
    }
}

extern f32 D_80770568[];

f32 sfxGetChannelVolume(sfxId)
s32 sfxId;
{
    u8 bank = sfxGetBankIndex((s16)sfxId);
    if (sfxId == D_80770560[bank]) {
        if (alCSPGetState(&gSeqPlayers[bank]->al) == 1) {
            return D_80770568[bank];
        }
    }
    return 0.0f;
}

void sfxSetChannelTempo(s32 sfxId, f32 scale) {
    u8 bank = sfxGetBankIndex((s16)sfxId);
    if ((sfxId == sSfxChannelSounds[sfxGetChannelIndex((s16)sfxId)]) && (sfxId == D_80770560[bank])) {
        alCSPSetTempo(&gSeqPlayers[bank]->al, (s32)((s32)alCSPGetTempo(&gSeqPlayers[bank]->al) * scale));
    }
}

extern f32 D_80770DDC;
extern f32 D_80770DE0;
extern f32 D_80770DE4;
f32 sinApprox(f32);
f32 cosApprox(f32);
f32 sqrtf(f32);
#pragma intrinsic(sqrtf)

f32 sfxCalcDistanceVolumePan(f32 x, f32 y, f32 z, u8 volume, u8 range, f32 directionality) {
    f32 dx;
    f32 dy;
    f32 dz;
    f32 level;
    f32 pad;
    f32 viewPitch;
    f64 diff;

    viewPitch = 0.0f;
    dx = gPlayerSlots->x - x;
    dy = gPlayerSlots->y - y;
    dz = gPlayerSlots->z - z;

    diff = ((f64)directionality > 0.8) ? ((f64)directionality - 0.8) : -((f64)directionality - 0.8);

    if (diff < 0.1 && dy < 0.0f) {
        dy *= 20.0f;
    }

    D_80770DE4 = sqrtf((dx * dx) + (dy * dy) + (dz * dz));

    if ((f64)directionality >= 0.8) {
        f32 l_dz = gPlayerSlots->lookZ - gPlayerSlots->z;
        f32 l_dx = gPlayerSlots->lookX - gPlayerSlots->x;
        viewPitch = mathAngleBetweenPointsRad(gPlayerSlots->y, 0.0f, gPlayerSlots->lookY, sqrtf((l_dz * l_dz) + (l_dx * l_dx)));

        l_dz = z - gPlayerSlots->z;
        l_dx = x - gPlayerSlots->x;
        D_80770DDC = mathAngleBetweenPointsRad(gPlayerSlots->y, 0.0f, y, sqrtf((l_dz * l_dz) + (l_dx * l_dx))) - viewPitch;

        if (D_80770DDC < 0.0f) {
            D_80770DDC += 6.2831855f;
        }

        if (D_80770DDC > 0.3926991f && (f64)D_80770DDC < 5.890486389398575) {
            D_80770DE4 = (1.0f - (sinApprox((f32)(((f64)D_80770DDC * 4.0 / 7.0) + 2.942101601958275)) * 4.0f)) * D_80770DE4;
        }
    }

    D_80770DDC = mathAngleBetweenPointsRad(gPlayerSlots->x, gPlayerSlots->z, x, z) - gPlayerSlots->yaw;
    if (D_80770DDC < 0.0f) {
        D_80770DDC += 6.2831855f;
    }

    if (D_80770DDC > 0.7853982f && (f64)D_80770DDC < 5.497787296772003 && (f64)viewPitch < 4.0) {
        D_80770DE4 = (1.0f - (sinApprox((f32)(((2.0 * (f64)D_80770DDC) / 3.0) + 2.617993950843811)) * directionality)) * D_80770DE4;
    }

    if (D_80770DE4 < 1.0f) {
        D_80770DE4 = 1.0f;
    }

    {
        f32 dist = (f32)(range * 0xFA0);
        f64 temp = ((f64)(dist / sqrtf(D_80770DE4))) - (((f64)dist * 0.12909946) - 32767.0);
        f64 volumeScale = (f64)volume;
        level = (f32)(temp * volumeScale * 0.00392156862745098);
    }

    if (level < 10.0f) {
        return 0.0f;
    }

    D_80770DE0 = cosApprox(D_80770DDC);
    D_80770DDC = (f32)((f64)(1.0f - sinApprox(D_80770DDC)) * 63.5);

    if (level < 10.0f) {  // FAKE: repeated early-out (the first already returned) keeps the cosApprox/sinApprox stores ahead of the clamp
        return 0.0f;
    }

    if (level > 32767.0f) {
        level = 32767.0f;
    }

    return level;
}

extern f32 D_80770DE8;
extern f32 D_80770DEC;
f32 D_80770DF0;
f32 D_80770DF4;

f32 sfxUpdateDistanceVolumeAndPan(f32 x, f32 y, f32 z, u8 volume, u8 range, f32 directionality)
{
    f32 level;
    f32 panRatio;

    level = sfxCalcDistanceVolumePan(x, y, z, volume, range, directionality);
    if (level < 10.0f) {
        return 0.0f;
    }

    panRatio = (f32)((f64)D_80770DDC * 0.00787401574803149595);
    D_80770DE8 += level * panRatio;
    D_80770DEC += level * (1.0f - panRatio);

    if (D_80770DE0 > 0.0f) {
        D_80770DF0 += level * D_80770DE0;
    }
    if (D_80770DE0 < 0.0f) {
        D_80770DF4 -= level * D_80770DE0;
    }

    return level;
}

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 facing;
    s16 radius;
    u8 reverb;
    u8 sfxId;
    u8 enterSfx;
    u8 extraSfx;
} AmbientEmitter;

typedef struct {
    s16 sfxId;
    u8 volume;
    u8 range;
    f32 directionality;
    f32 pitch;
} AmbientAudioParam;


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

#include "sched.h"
extern SchedStruct gScheduler;
extern ALBank *D_8076D1F8;
extern ALBank *D_8076D1FC;
extern struct GfSndState *D_807457DC;
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
struct GfSndState *D_80770DF8[16];
u32 D_80770E38[16];
f32 D_80770E78[16];
f32 D_80770EB8[16];
f32 D_80770EF8[16];
extern u32 gGlobalPauseFlags;
extern PlayerState *gActivePlayerState;


void sfxUpdateLevelAmbient(void) {
    s8 nearest;
    s8 pad;
    u8 fxFlags;
    u8 extraSfx;
    s32 n;
    s32 emitterCount;
    s16 group;
    s16 k;
    f32 volume;
    f32 angle;
    f32 pitch;
    u32 count;
    s16 sfxId;
    AmbientEmitter *emitters;
    LevelSoundEmitter *soundEmitters;

    nearest = -1;
    fxFlags = 0;

    switch (gCurrentMap) {
    case 7:
        if (D_8077058C[0] == 0) {}  // FAKE: dead statement steers uopt colouring
        emitterCount = 7;
        emitters = D_80745F74;
        break;
    case 0x26:
        emitterCount = 4;
        emitters = D_80745FD8;
        break;
    case 0x1E:
        emitterCount = 3;
        emitters = D_80746010;
        break;
    case 0x27:
        emitterCount = 4;
        emitters = D_8074603C;
        break;
    case 0x1A:
        emitterCount = 4;
        emitters = D_80746074;
        break;
    case 0xE:
        emitterCount = 4;
        emitters = D_807460AC;
        break;
    case 0x1B:
        emitterCount = 10;
        emitters = D_807460E4;
        break;
    case 0x37:
        emitterCount = 7;
        emitters = D_807461E0;
        break;
    case 0x22:
        emitterCount = 4;
        emitters = D_80746244;
        break;
    case 0xB0:
        emitterCount = 3;
        emitters = D_8074627C;
        break;
    case 0x30:
        emitters = D_80746170;
        emitterCount = 8;
        if (gActivePlayerState->stateFlags & 0x100000) {
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
        emitterCount = 0;
        break;
    }

    if (emitterCount != 0 && sSfxAreaAmbientActive != 0 && sSfxMode == 0) {
        D_80770DD4 = 1000000.0f;
        volume = 0.0f;
        for (k = 0, n = emitterCount; k < n; k++) {  // FAKE: n caches emitterCount as the loop bound; k < emitterCount moves emitterCount from s1 to s3 (pre-existing copy, now tagged)
            AmbientEmitter *entry = (AmbientEmitter *)((s32)emitters + k * 14);  // FAKE: byte-address sum keeps emitters in t4 and the k*14 index in t5 (addu operand order)
            f32 dx = gPlayerSlots->x - entry->x;
            f32 dz = gPlayerSlots->z - entry->z;
            if (entry->facing == -1) {
                D_80770DE4 = sqrtf(dx * dx + dz * dz);
                if (D_80770DE4 < entry->radius - 20) {
                    sfxAllocateChannel(entry->sfxId, 1.0f);
                } else if (D_80770DE4 > entry->radius) {
                    sfxStopChannel(entry->sfxId, 0);
                }
            } else {
                f32 dy = gPlayerSlots->y - entry->y;
                D_80770DE4 = sqrtf(dx * dx + dy * dy + dz * dz);
                if (k == 0 || D_80770DE4 < D_80770DD4) {
                    nearest = k;
                    D_80770DD4 = D_80770DE4;
                    angle = (mathAtan2(dx, dz) * 4096.0) / 6.2831854820251465 - entry->facing;
                }
            }
            D_80770DE8 = 32767.0f - (D_80770DE4 - 50.0f) * 120.0f;
            if (D_80770DE8 > 32767.0f) {
                D_80770DE8 = 32767.0f;
            }
            if (D_80770DE8 < 0.0f) {
                D_80770DE8 = 0.0f;
            }
            volume += D_80770DE8;
        }
        D_80770DE4 = D_80770DD4;
        if (nearest >= 0 && D_80770DE4 < emitters[nearest].radius) {
            if (emitters[nearest].facing >= 0x1001) {
                D_80770DC9 = emitters[nearest].facing & 1;
            } else {
                if (angle > 2048.0f) {
                    angle -= 4096.0f;
                }
                if (angle < -2048.0f) {
                    angle += 4096.0f;
                }
                if (angle < 1024.0f && angle > -1024.0f) {
                    if (D_80770DCB != 0) {
                        D_80770DC9 = 1;
                    }
                } else {
                    D_80770DCB = 1;
                    D_80770DC9 = 0;
                    sfxAllocateChannel(emitters[nearest].enterSfx, 1.0f);
                }
            }
            if (D_80770DC9 != 0) {
                D_80770DC8 = emitters[nearest].reverb;
            } else {
                D_80770DC8 = 0;
            }
            D_80770DD9 = emitters[nearest].sfxId;
        } else {
            D_80770DCB = 0;
        }
        if (D_80745838 != 0) {
            volume = 0.0f;
        } else if (D_80770DC9 != 0) {
            volume = 32767.0f;
        } else {
            if (volume > 32767.0f) {
                volume = 32767.0f;
            }
            if (volume < 500.0f) {
                volume = 0.0f;
            }
        }
        if (D_80770DD8[1] == 0xFF) {
            D_80770DD8[1] = emitters[nearest].sfxId;
            D_80770DC8 = emitters[nearest].reverb;
            if (D_80770DC9 == 0) {
                sfxAllocateChannel(emitters[nearest].enterSfx, 1.0f);
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
        if (volume != 0.0f) {
            if ((extraSfx = emitters[nearest].extraSfx)) {
                sfxAllocateChannel(extraSfx, 1.0f);
            }
        }
        if (D_80770560[2] == 0x26) {
            seqSetVolumeInstant(2, volume / 32767.0);
        }
        volume = ((volume - 28384.0f) * 100.0f) / 4383.0f;
        if (volume < 0.0f) {
            volume = 0.0f;
        }
        volume = D_80745BDC[gCurrentMap][1] + (((255.0 - D_80745BDC[gCurrentMap][1]) * (D_80770DC8 / 127.0) * volume) / 255.0);
        D_8077058E = volume;
    } else {
        D_8077058E = D_80745BDC[gCurrentMap][1];
    }
    if (D_80770DE8 && D_80770DE8) {}  // FAKE: dead statement steers uopt colouring

    if (D_80745838 != 0) {
        D_8077058E = 0xFF;
    }

    if (D_8077058E != D_8077058D) {
        angle = (D_8077058E * 0.3) / 255.0;
        volume = ((D_8077058E * 0.35) / 255.0) + 1.0;
        count = D_8077058E;  // FAKE: reusing the emitter-count local for the reverb level keeps one web (a separate temp recolours 50 rows)
        if (gCurrentMap == 0xE) {
            if (count != 0) {
                k = 4;  // FAKE: dead store stops uopt hoisting the loop-init k = 0 above the seqSetVolumeInstant calls
                seqSetVolumeInstant(0, 1.0f);
            } else {
                seqSetVolumeInstant(0, 0.6f);
            }
            alCSPSetChlPanVolume(&gSeqPlayers[0]->al, angle, volume);
        }
        for (k = 0; k < 4; k++) {
            if (sSfxFlagTable[D_80770560[k]] & 1) {
                alCSPSetChlPanVolume(&gSeqPlayers[k]->al, angle, volume);
            } else {
                alCSPSetChlPanVolume(&gSeqPlayers[k]->al, 0.0f, 1.0f);
            }
        }
        D_8077058D = D_8077058E;
    }

    count = mapGetSoundEmitters(&soundEmitters);
    for (group = 0; group < 15; group++) {
        D_80770DE8 = 0.0f;
        D_80770DEC = 0.0f;
        D_80770DF0 = 0.0f;
        D_80770DF4 = 0.0f;
        if ((gGlobalPauseFlags & 2) || !(gGlobalPauseFlags & 0x10)) {
            volume = 0.0f;
        } else {
            if (group == 11 && flagGet(0x302, 0)) {
                volume = 0.0f;
            } else if (group == 13 && flagGet(0x4C, 0)) {
                volume = 0.0f;
            } else {
                if (group == 1) {
                    actorTargetEntriesUpdateSfx(1, 0xFF, 0xC8, 0.3f);
                }
                for (k = count - 1; k >= 0; k--) {
                    if (group + 1 == soundEmitters[k].group) {
                        sfxUpdateDistanceVolumeAndPan(soundEmitters[k].x, soundEmitters[k].y, soundEmitters[k].z,
                            (u8)((soundEmitters[k].volume * D_80745B28[group].volume) / 255.0),
                            D_80745B28[group].range, D_80745B28[group].directionality);
                    }
                }
                volume = D_80770DE8 + D_80770DEC;
                if (volume > 32767.0f) {
                    volume = 32767.0f;
                }
                if (volume < 500.0f) {
                    volume = 0.0f;
                }
            }
        }
        if (D_80745B28[group].sfxId == 0x1E) {
            volume *= 0.6;
            if ((gScheduler.unk280 / 12U) != D_80770E38[group]) {
                D_80770E38[group] = (gScheduler.unk280 / 12U);
                if (volume > 10.0f) {
                    n_alSndpPlay(D_8076D1F8, D_80745B28[group].sfxId, (u16)volume, 0x3F, 0.4f, 0, &D_80770DF8[group]);
                    D_80770EB8[group] = volume + 1.0f;
                    D_80770EF8[group] = 300.0f;
                }
            }
        }
        if (volume != D_80770EB8[group] || D_80770DF8[group] == 0) {
            if (volume > 10.0f) {
                if (D_80770DF8[group] == 0) {
                    sfxId = D_80745B28[group].sfxId;
                    if (sfxId < 0x800) {
                        n_alSndpPlay(D_8076D1F8, sfxId, (u16)volume, 0x3F, D_80745B28[group].pitch, 0, &D_80770DF8[group]);
                    } else {
                        n_alSndpPlay(D_8076D1FC, sfxId - 0x7FF, (u16)volume, 0x3F, D_80745B28[group].pitch, 0, &D_80770DF8[group]);
                    }
                    D_80770E78[group] = 0.0f;
                    D_80770EF8[group] = 255.0f;
                }
                if (D_80770DF8[group] != 0) {
                    n_alSndpPostEvent(D_80770DF8[group], 8, (s32)volume);
                }
                if (D_80770DF0 < D_80770DF4) {
                    fxFlags = 0x80;
                }
                if (D_80770DF8[group] != 0) {
                    n_alSndpPostEvent(D_80770DF8[group], 0x100, (s32)fxFlags);
                }
            } else if (D_80770DF8[group] != 0) {
                n_alSndpStop(D_80770DF8[group]);
            }
            D_80770EB8[group] = volume;
        }
        if (D_80770DF8[group] != 0) {
            if (D_80770DE8 > 32767.0f) {
                D_80770DE8 = 32767.0f;
            }
            if (D_80770DEC > 32767.0f) {
                D_80770DEC = 32767.0f;
            }
            if (D_80770DEC < D_80770DE8) {
                if (D_80770DE8 > 0.0f) {
                    angle = 127.0 - ((D_80770DEC * 63.5) / D_80770DE8);
                } else {
                    angle = 0.0f;
                }
            } else if (D_80770DEC > 0.0f) {
                angle = (D_80770DE8 * 63.5) / D_80770DEC;
            } else {
                angle = 0.0f;
            }
            if (D_80745838 != 0) {
                pitch = D_80745B28[group].pitch * 0.5;
            } else if (D_80770DC9 != 0 && D_80745B28[group].sfxId == 0x106) {
                pitch = 1.0 / ((D_80770DD4 / 800.0) + 1.0);
            } else {
                pitch = D_80745B28[group].pitch;
            }
            if (angle != D_80770EF8[group]) {
                if (D_80770EF8[group] != 255.0f) {
                    if (D_80770EF8[group] < angle) {
                        if (D_8077058D && D_8077058D) {}  // FAKE: dead statement steers uopt colouring
                        if (D_80770EF8[group] + 8.0f < angle) {
                            angle = D_80770EF8[group] + 8.0f;
                        }
                    } else {
                        if (angle < D_80770EF8[group] - 8.0f) {
                            angle = D_80770EF8[group] - 8.0f;
                        }
                    }
                }
                n_alSndpPostEvent(D_80770DF8[group], 4, (s32)angle);
                D_80770EF8[group] = angle;
            }
            if (pitch != D_80770E78[group]) {
                n_alSndpPostEvent(D_80770DF8[group], 0x10, *(s32 *)&pitch);
                D_80770E78[group] = pitch;
            }
        }
    }

    if ((gGlobalPauseFlags & 2) || !(gGlobalPauseFlags & 0x10)) {
        if (D_80770DC8) {}  // FAKE: dead statement steers uopt colouring
        D_8077058C[0] = 0;
    }
    if (D_8077058C[0] != 0) {
        if (D_807457DC == 0) {
            n_alSndpPlay(D_8076D1F8, 0x125, 0, 0x3F, 1.0f, 0, &D_807457DC);
        }
        if (D_807457DC != 0) {
            n_alSndpPostEvent(D_807457DC, 8, (s32)((D_8077058C[0] * 10767.0) / 255.0));
            pitch = 1.0 - ((D_8077058E * 0.5) / 255);
            if (D_80770DC9 & (D_80770DD4 < 1000.0f)) {
                angle = mathAngleBetweenPointsRad(gPlayerSlots->x, gPlayerSlots->z, emitters[nearest].x, emitters[nearest].z) - gPlayerSlots->yaw;
                if (angle < 0.0f) {
                    angle += 6.2831855f;
                }
                if (angle > 1.5707964f && angle < 4.71238911151886) {
                    D_80770DD0 = 128.0f;
                } else {
                    D_80770DD0 = 0.0f;
                }
                D_80770DCC = (1.0f - sinApprox(angle)) * 63.5;
            } else {
                D_80770DCC = 64.0f;
            }
            n_alSndpPostEvent(D_807457DC, 0x10, *(s32 *)&pitch);
            n_alSndpPostEvent(D_807457DC, 0x100, (s32)D_80770DD0);
            n_alSndpPostEvent(D_807457DC, 4, (s32)D_80770DCC);
        }
    } else if (D_807457DC != 0) {
        n_alSndpStop(D_807457DC);
    }
}



void seqUpdateUnderwaterAudio(s32 seqIndex) {
    if (D_80745838 != 0) {
        if (seqIndex == 0 && (sSfxFlagTable[D_80770560[seqIndex]] & 1)) {
            alCSPSetChlPanVolume(&gSeqPlayers[0]->al, 0.3f, 1.35f);
        }
        if (D_80770560[seqIndex] == 0x38) {
            sfxSetChannelParam(0x38, 0x3C00, 1);
        }
        if (D_80770560[seqIndex] == 0x60) {
            if (gCurrentMap == 0xB8) {
                sfxSetChannelParam(0x60, 0xE, 1);
            } else {
                sfxSetChannelParam(0x60, 8, 1);
                alCSPSetChlFX1Mix(&gSeqPlayers[1]->al, 1, 0x7F);
                alCSPSetChlFX1Mix(&gSeqPlayers[1]->al, 2, 0x7F);
            }
            sfxSetChannelParam(0x60, 0x10, 0);
        }
    } else {
        if (seqIndex == 0 && (sSfxFlagTable[D_80770560[seqIndex]] & 1)) {
            alCSPSetChlPanVolume(&gSeqPlayers[0]->al, 0.0f, 1.0f);
        }
        if (D_80770560[seqIndex] == 0x38) {
            sfxSetChannelParam(0x38, 0x3C00, 0);
        }
        if (D_80770560[seqIndex] == 0x60) {
            if (gCurrentMap == 0xB8) {
                sfxSetChannelParam(0x60, 0x1E, 1);
                return;
            }
            sfxSetChannelParam(0x60, 0x10, 1);
            sfxSetChannelParam(0x60, 8, 0);
            alCSPSetChlFX1Mix(&gSeqPlayers[1]->al, 1, 0x64);
            alCSPSetChlFX1Mix(&gSeqPlayers[1]->al, 2, 0x64);
        }
    }
}

extern s16 D_80770628[];
extern f32 D_80770B68[];
extern f32 D_80770BC0[];
extern f32 D_80770C18[];
extern f32 D_80770C70[];

void sfxSetVolumeAndPan(u8 source, f32 pitch, f32 rate) {

    if (source != -1) {
        if (rate == 0.0f) {
            D_80770C18[D_80770628[source]] = pitch;
            D_80770C70[D_80770628[source]] = pitch;
        } else {
            D_80770B68[D_80770628[source]] = pitch;
        }
        D_80770BC0[D_80770628[source]] = rate;
    }
}

extern u8 D_80770CE0[];

void sfxSetChannelPriority(u8 source, u8 volume) {
    if (source != -1) {
        D_80770CE0[D_80770628[source]] = volume;
    }
}

extern s16 D_80770710[];


void sfxPlayActorSound(Actor *actor, s16 sfxId, u8 range, u8 exclusive, u8 slot, u8 volume, f32 pitch, s8 node) {
    if (actor->soundSlots[slot] != -1) {
        if (sfxId == D_80770710[D_80770628[actor->soundSlots[slot]]]) {
            return;
        }
        sfxStopSlotSound(actor, slot);
    }
    actor->soundSlots[slot] = sfxSlotAllocateActor(actor, sfxId, range, exclusive, volume, pitch, node);
}
extern struct GfSndState *sSoundSlotHandles[];
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
extern Actor *D_807705A0[];

u8 sfxSlotAllocateActor(Actor *actor, s16 sfxId, u8 range, u8 exclusive, u8 volume, f32 pitch, s8 node) {
    u8 source;
    u8 voice;
    s16 count;

    for (source = 0; source < 22; source++) {
        if (D_80770628[source] == -1) {
            break;
        }
    }
    if (source == 22) {
        return 0xFF;
    }

    if (exclusive != 0) {
        voice = 22;
    } else {
        for (voice = 0; voice < 22; voice++) {
            if (D_807706F8[voice] == 0 && D_80770710[voice] == sfxId) {
                break;
            }
        }
    }

    if (voice == 22) {
        for (voice = 0; voice < 22; voice++) {
            if (D_80770710[voice] == 0 && sSoundSlotHandles[voice] == 0) {
                break;
            }
        }
        if (voice == 22) {
            return 0xFF;
        }
        D_80770710[voice] = sfxId;
        D_807706F8[voice] = exclusive;
        D_80770C18[voice] = pitch;
        D_80770C70[voice] = pitch;
        D_80770B68[voice] = 1.0f;
        D_80770BC0[voice] = 0.0f;
        D_80770CC8[voice] = 0;
    }

    if (range != 0) {
        D_80770788[source] = range;
    } else {
        D_80770788[source] = D_807460AE[D_80770710[voice]][0];
    }
    D_80770CE0[voice] = volume;
    D_80770D10[voice] = -1;
    D_80770D70[voice] = pitch;
    D_80770D40[voice] = -1;
    D_80770CF8[voice] = node;
    D_807706E0[voice] = 0;
    count = D_80770740[voice];
    D_80770628[source] = voice;
    D_80770658[source] = count;
    D_807707A0[voice][count] = source;
    D_80770740[voice] = count + 1;
    D_807705A0[source] = actor;
    return source;
}
extern s16 D_807705F8[];

u8 sfxSlotAllocateSource(s16 modelSlot, s16 sfxId, u8 range, u8 exclusive, u8 volume, f32 pitch, s8 node) {
    u8 source;
    u8 voice;
    s16 count;

    for (source = 0; source < 22; source++) {
        if (D_80770628[source] == -1) {
            break;
        }
    }
    if (source == 22) {
        return 0xFF;
    }

    if (exclusive != 0) {
        voice = 22;
    } else {
        for (voice = 0; voice < 22; voice++) {
            if (D_807706F8[voice] == 0 && D_80770710[voice] == sfxId) {
                break;
            }
        }
    }

    if (voice == 22) {
        for (voice = 0; voice < 22; voice++) {
            if (D_80770710[voice] == 0 && sSoundSlotHandles[voice] == 0) {
                break;
            }
        }
        if (voice == 22) {
            return 0xFF;
        }
        D_80770710[voice] = sfxId;
        D_807706F8[voice] = exclusive;
        D_80770C18[voice] = pitch;
        D_80770C70[voice] = pitch;
        D_80770B68[voice] = 1.0f;
        D_80770BC0[voice] = 0.0f;
        D_80770CC8[voice] = 0;
    }

    if (range != 0) {
        D_80770788[source] = range;
    } else {
        D_80770788[source] = D_807460AE[D_80770710[voice]][0];
    }
    D_80770CE0[voice] = volume;
    D_80770D10[voice] = -1;
    D_80770D70[voice] = pitch;
    D_80770D40[voice] = -1;
    D_80770CF8[voice] = node;
    D_807706E0[voice] = 0;
    count = D_80770740[voice];
    D_80770628[source] = voice;
    D_80770658[source] = count;
    D_807707A0[voice][count] = source;
    D_80770740[voice] = count + 1;
    D_807705F8[source] = modelSlot;
    return source;
}

void sfxStopSlotSound(Actor *actor, u8 slot) {
    if (actor->soundSlots[slot] >= 0) {
        sfxSlotFreeSource(actor->soundSlots[slot]);
        actor->soundSlots[slot] = -1;
        if (slot == 0) {
            actor->unk72 = 0;
        }
    }
}



void sfxSlotFreeSource(s16 source) {
    D_80770740[D_80770628[source]]--; if (D_80770740[D_80770628[source]] != 0) { // LAYOUT:
        D_80770658[D_807707A0[D_80770628[source]][D_80770740[D_80770628[source]]]] = D_80770658[D_807707A0[D_80770628[source]][D_80770658[source]]];
        D_807707A0[D_80770628[source]][D_80770658[source]] = D_807707A0[D_80770628[source]][D_80770740[D_80770628[source]]];
    } else {
        D_80770710[D_80770628[source]] = 0;
        D_807706F8[D_80770628[source]] = 0;
    }

    if (D_80770740[D_80770628[source]] < 0 || D_80770740[D_80770628[source]] >= 23) {
        faultSetMessage(9, D_80770740[D_80770628[source]], 0, 0);
    }

    D_807707A0[D_80770628[source]][D_80770740[D_80770628[source]]] = -1;
    D_807705F8[source] = -1;
    D_807705A0[source] = NULL;
    D_80770628[source] = -1;
    D_80770658[source] = -1;
}


extern u8 D_80750190;
extern u8 D_80770770[];

void audioResetAll(void) {
    u8 i;
    u8 j;

    i = 0;
    if (transitionGetState() == 0) {
        n_alSndpStopAll();
    }
    D_80750190 = 0;
    if (transitionGetState() != 0) {
        i = 1;
    }
    for (; i < 4; i++) {
        alCSPSetChlPanVolume(&gSeqPlayers[i]->al, 0.0f, 1.0f);
        if (alCSPGetState(&gSeqPlayers[i]->al) == 1 && D_80770560[i] != 0x12) {
            alSeqpStop((ALSeqPlayer *)gSeqPlayers[i]);
            D_80770560[i] = 0;
        }
    }
    D_8077058C[0] = 0;
    D_8077058C[1] = 0;
    D_8077058C[2] = 0;
    if (transitionGetState() != 0) {
        i = 1;
    } else {
        i = 0;
    }
    for (; i < 12; i++) {
        if (sSfxChannelSounds[i] != 0x12) {
            sSfxChannelVolumes[i] = 0.0f;
            for (j = 0; j < 4; j++) {
                sSfxChannelMasks[j][i] = 0;
            }
            sSfxChannelSounds[i] = 0;
            sSfxChannelStates[i] = 0;
        }
    }
    sSfxAreaAmbientActive = 0;
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
    f32 x;
    f32 y;
    f32 z;
    char padC[0x70];
    SoundTargetSlotNode *node;
    char pad80[0x10];
} SoundTargetSlot;
extern SoundTargetSlot *gModelSlots;

extern f32 D_80770590;
extern f32 D_80770594;
extern f32 D_80770688[];
extern u8 gPlayerCount;


#define RAND_UNIT() ((u32)randomLcgNext() / 4294967295.0)

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
    Actor *actor;
    CamState *camState;
    s16 j;
    s16 pan;
    Actor *ctx104;
    s32 slot;
    s16 animFrame;
    f32 animSpeed;
    u8 animFlags;
    s32 pad;

    actor = NULL;
    if (gActivePlayerState != NULL) {}  // FAKE: dead test keeps &gActivePlayerState out of a register so the store/reload after the loop stays split
    for (i = 0; i < 22; i++) {
        if (D_80770710[i] == 0x88) {
            D_80770DE8 = 0.0f;
            D_80770DEC = 0.0f;
            D_80770DF0 = 0.0f;
            D_80770DF4 = 0.0f;
            fxFlags = 0;
            for (j = D_80770740[i] - 1; j >= 0; j--) {
                slot = hashTableLookup(D_807705F8[D_807707A0[i][j]]);
                sfxUpdateDistanceVolumeAndPan(gModelSlots[slot].x, gModelSlots[slot].y, gModelSlots[slot].z, 0xFF, 0x50, 0.5f);
                dist[j] = D_80770DE4;
                sfxSlotFreeSource(D_807707A0[i][j]);
                gModelSlots[slot].node->unk12 = -1;
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
            if (sSoundSlotHandles[i] != 0) {
                if (D_80770710[i] == 0) {
                    if (D_807706E0[i] != 0) {
                        D_807706E0[i]--;
                    } else {
                        n_alSndpStop(sSoundSlotHandles[i]);
                        D_80770770[i] = 0;
                        D_807706E0[i] = 10;
                    }
                }
            } else if (D_80770710[i] != 0) {
                if (D_80770710[i] == 0x128 || D_80770710[i] == 0x306) {
                    if (D_80770CC8[i] == 0) {
                        n_alSndpPlay(D_8076D1F8, D_80770710[i], 0, 0x3F, D_80770C18[i], 0, &sSoundSlotHandles[i]);
                        D_80770CC8[i] = 1;
                    } else {
                        slotIdx = D_807707A0[i][0];
                        sfxStopSlotSound(D_807705A0[slotIdx], 0);
                    }
                } else if (D_80770710[i] < 0x800) {
                    n_alSndpPlay(D_8076D1F8, D_80770710[i], 0, 0x3F, D_80770C18[i], 0, &sSoundSlotHandles[i]);
                } else {
                    n_alSndpPlay(D_8076D1FC, D_80770710[i] - 0x7FF, 0, 0x3F, D_80770C18[i], 0, &sSoundSlotHandles[i]);
                }
            }
            if (sSoundSlotHandles[i] != 0) {
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
                                    sfxUpdateDistanceVolumeAndPan(gModelSlots[slot].x, gModelSlots[slot].y + 320.0f, gModelSlots[slot].z, 0xFF, D_80770788[D_807707A0[i][j]], factor);
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
                                    sfxUpdateDistanceVolumeAndPan(gModelSlots[slot].x, gModelSlots[slot].y, gModelSlots[slot].z, 0xFF, D_80770788[D_807707A0[i][j]], factor);
                                }
                            } else {
                                actor = D_807705A0[D_807707A0[i][j]];
                                if (D_80770CF8[i] > 0) {
                                    actorGetNodePos(actor, D_80770CF8[i], &posX, &posY, &posZ);
                                    sfxUpdateDistanceVolumeAndPan(posX, posY, posZ, 0xFF, D_80770788[D_807707A0[i][j]], factor);
                                } else if (D_80770CF8[i] < 0) {
                                    D_80770DE8 = 32767.0f;
                                    D_80770DEC = 32767.0f;
                                    D_80770DF0 = 32767.0f;
                                    D_80770DF4 = 32767.0f;
                                } else if (D_80770710[i] == 0x139 && D_807706F8[i] != 0) {
                                    posY = actor->y;
                                    posX = actor->x;
                                    posZ = actor->z;
                                    sfxUpdateDistanceVolumeAndPan(posX, posY, posZ, 0xFF, D_80770788[D_807707A0[i][j]], factor);
                                    posX = (mathCosF(actor->yaw) * 300.0) + actor->x;
                                    posZ = actor->z - (mathSinF(actor->yaw) * 300.0);
                                    sfxUpdateDistanceVolumeAndPan(posX, posY, posZ, 0xFF, D_80770788[D_807707A0[i][j]], factor);
                                    posX = actor->x - (mathCosF(actor->yaw) * 300.0);
                                    posZ = (mathSinF(actor->yaw) * 300.0) + actor->z;
                                    sfxUpdateDistanceVolumeAndPan(posX, posY, posZ, 0xFF, D_80770788[D_807707A0[i][j]], factor);
                                } else {
                                    sfxUpdateDistanceVolumeAndPan(actor->x, actor->y, actor->z, 0xFF, D_80770788[D_807707A0[i][j]], factor);
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
                    if ((gGlobalPauseFlags & 2) || !(gGlobalPauseFlags & 0x10)) {
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
                                gModelSlots[slot].node->unk10 = -1;
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
                                        gModelSlots[slot].node->unk10 = -1;
                                    } else {
                                        sfxStopSlotSound(actor, 0);
                                        sfxStopChannel(0x3B, 0);
                                    }
                                }
                            }
                            break;
                        case 0x131:
                            if (actor->actorType == 0xB9) {
                                D_80770770[i] = 8;
                                D_80770C18[i] = (actor->unk72 / 80.0) + 1.0;
                                volume *= 1.0f / D_80770C18[i];
                            } else {
                                D_80770B68[i] = 0.0f;
                                D_80770C18[i] = 200.0f;
                                for (j = 0; j < D_80770740[i]; j++) {
                                    if (D_807705A0[D_807707A0[i][j]]->unk72 < D_80770C18[i]) {
                                        D_80770C18[i] = D_807705A0[D_807707A0[i][j]]->unk72;
                                        D_80770B68[i] = j;
                                    }
                                }
                                j = D_80770B68[i];
                                D_80770C18[i] = 2.0 - (((D_807705A0[D_807707A0[i][j]]->unk72 - 120) > 0 ? (D_807705A0[D_807707A0[i][j]]->unk72 - 120) : -(D_807705A0[D_807707A0[i][j]]->unk72 - 120)) / 120.0);
                                D_80770C18[i] = (D_80770C18[i] > 0.2) ? D_80770C18[i] : 0.2;
                                D_80770B68[i] = D_807705A0[D_807707A0[i][j]]->unk74 / 20.0;
                                D_80770B68[i] = (D_80770B68[i] < 1.0f) ? D_80770B68[i] : 1.0f;
                                D_80770B68[i] = (D_80770B68[i] > 0.0f) ? D_80770B68[i] : 0.0f;
                                volume *= D_80770B68[i];
                            }
                            break;
                        case 0x10E:
                            if (actor->actorType == 0x139) {
                                if (D_80770BC0[i]-- <= 0.0f) {
                                    D_80770BC0[i] = (RAND_UNIT() * 2) + 2.0;
                                    D_80770B68[i] = ((0.925 + (0.15 * RAND_UNIT())) - D_80770C18[i]) / D_80770BC0[i];
                                }
                                volume *= 0.5;
                                break;
                            }
                            if (actor->actorType == 2) {
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
                                    switch (actor->health) {
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
                            if (actor->actorType != 0x139) {
                                if (D_80770BC0[i]++ >= 2.0f) {
                                    D_80770BC0[i] = (u32)randomLcgNext();
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
                            D_80770590 = actor->speedXZ / 600.0;
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
                        if (actor->actorType == 0x139) {
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
                            D_80770590 = actor->speedXZ / 600.0;
                            D_80770590 = (D_80770590 > 0.8) ? 0.8 : D_80770590;
                            volume *= D_80770590;
                            if ((actor->y - actor->floorY) > 5.0f) {
                                volume = 0.0f;
                            }
                            D_80770594 = actor->speedXZ;
                            D_80770F38 = (actor->speedXZ / 550.0f) + 0.5;
                        } else {
                            if (D_80770594 != actor->speedXZ) {
                                D_80770F38 = (D_80770594 * 32767.0f) / 200.0f;
                                D_80770590 = D_80770590 + ((D_80770F38 - D_80770590) * 0.3);
                            } else if (D_80770590 > 5000.0f) {
                                D_80770590 = ((D_80770590 - 350.0f) < 5000.0f) ? 5000.0f : (D_80770590 - 350.0f);
                            } else if (D_80770590 < 5000.0f) {
                                D_80770590 = ((D_80770590 + 350.0f) > 5000.0f) ? 5000.0f : (D_80770590 + 350.0f);
                            }
                            volume *= D_80770590 / 32767.0;
                            if ((actor->y - actor->floorY) > 5.0f) {
                                volume = 0.0f;
                            }
                            D_80770594 = actor->speedXZ;
                            D_80770F38 = (actor->speedXZ / 150.0f) + 0.5;
                            D_80770F38 *= D_80770C18[i];
                        }
                    }
                    if (actor != NULL) {
                        if (actor->unk72 != 0 && D_80770710[i] != 0x131 && actor->sub4->model->animId != actor->unk72) {
                            sfxStopSlotSound(actor, 0);
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
                    n_alSndpPostEvent(sSoundSlotHandles[i], 0x100, fxFlags);
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
                        n_alSndpPostEvent(sSoundSlotHandles[i], 8, (s32)volume);
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
                        n_alSndpPostEvent(sSoundSlotHandles[i], 4, pan);
                    }
                    if (D_80770F38 != D_80770D70[i]) {
                        D_80770D70[i] = D_80770F38;
                        n_alSndpPostEvent(sSoundSlotHandles[i], 0x10, *(s32 *)&D_80770F38);
                    }
                }
            }
        }
    }

    gActivePlayerState = gPlayerSlots->actor->customState;
    ctx104 = gActivePlayerState->camActor;
    camState = ctx104->customState;
    if (camState->unkFA != 0 && gPlayerSlots->y < (camState->unk90 + 3.0f) && D_80745838 == 0 && gPlayerCount < 2) {
        D_80745838 = 1;
        seqUpdateUnderwaterAudio(0);
        seqUpdateUnderwaterAudio(1);
    }
    if ((camState->unkFA == 0 || (camState->unk90 + 3.0f) < gPlayerSlots->y) && D_80745838 == 1) {
        D_80745838 = 0;
        seqUpdateUnderwaterAudio(0);
        seqUpdateUnderwaterAudio(1);
    }
}


s16 sfxPlayFromActorWithAltitudeCheck(Actor *actor, s16 sfxId, u8 volume, s16 pitch, u8 spread) {
    s32 fx;

    if (actor->y + 20.0f < actor->waterY && (sfxId < 0x355 || sfxId >= 0x35E)) {
        fx = 0x5A;
    } else {
        fx = 0;
    }
    return sfxPlayAtPositionPooled(actor->x, actor->y, actor->z, sfxId, volume, pitch, spread, 0x4B, 0.3f, fx);
}

void sfxPlayFromTargetSlot(s16 modelSlot, s16 sfxId, u8 volume, u8 pitch, u8 spread, u8 range, f32 directionality) {
    sfxPlayAtPositionPooled(gModelSlots[modelSlot].x, gModelSlots[modelSlot].y, gModelSlots[modelSlot].z, sfxId, volume, pitch, spread, range, directionality, 0);
}


void sfxPlayFromActorDirect(Actor *actor, s16 sfxId, u8 volume, f32 pitch, u8 spread, u8 range) {
    sfxPlayAtPosition(actor->x, actor->y, actor->z, sfxId, volume, pitch, spread, range);
}

extern u8 gPlayerCount;


s16 sfxPlayAtPositionPooled(f32 x, f32 y, f32 z, s16 sfxId, u8 volume, s16 pitch, u8 spread, u8 range, f32 directionality, u8 fx) {
    f32 diff;
    f32 angle2;
    s32 dist;
    s32 level;
    f32 angle;
    u8 closest;
    u8 i;
    s32 pad0;
    s32 pad1;
    s32 pad2;
    s16 pos[4];

    D_80770DE4 = -1.0f;
    closest = 0;
    for (i = 0; i < gPlayerCount; i++) {
        if (gPlayerSlots[i].active != 0) {
            s32 dx = gPlayerSlots[i].x - x;
            s32 dy = gPlayerSlots[i].y - y;
            s32 dz = gPlayerSlots[i].z - z;
            dist = dx * dx + dy * dy + dz * dz;
            if (D_80770DE4 == -1.0f || (f32)dist < D_80770DE4) {
                closest = i;
                D_80770DE4 = dist;
            }
        }
    }

    if (D_80770DE4 == -1.0f) {
        return -1;
    }

    pos[0] = gPlayerSlots[closest].x;
    pos[1] = gPlayerSlots[closest].y;
    pos[2] = gPlayerSlots[closest].z;
    pos[3] = (gPlayerSlots[closest].yaw * 4096.0) / 6.2831854820251465;
    camGetPathStartPose(&pos[0], &pos[1], &pos[2], &pos[3]);

    if (D_80770DE4 < 500.0f) {
        angle = 0.0f;
    } else {
        angle = (f64)mathAngleBetweenPointsRad(pos[0], pos[2], x, z) - ((f64)(pos[3] * 6.2831855f) * 0.000244140625);
        if (angle < 0.0f) {
            angle += 6.2831855f;
        }
        if (angle > 1.5707964f && (f64)angle < 4.71238911151886) {
            fx |= 0x80;
        }
    }

    if (range == 0) {
        level = ((f64)(u32)volume * 32767.0) / 255.0;
    } else {
        D_80770DE4 = sqrtf(D_80770DE4);
        if (gPlayerCount == 1 && (f64)directionality >= 0.8) {
            x = mathAngleBetweenPointsRad(pos[1], 0.0f, y, sqrtf(((x - pos[0]) * (x - pos[0])) + ((z - pos[2]) * (z - pos[2]))));
            angle2 = mathAngleBetweenPointsRad(pos[1], 0.0f, gPlayerSlots->lookY, sqrtf(((gPlayerSlots->lookX - pos[0]) * (gPlayerSlots->lookX - pos[0])) + ((gPlayerSlots->lookZ - pos[2]) * (gPlayerSlots->lookZ - pos[2]))));
            diff = x - angle2;
            if (x < angle2) {
                diff += 6.2831855f;
            }
            if (diff > 3.1415927f) {
                diff = 6.2831855f - diff;
            }
            if ((f64)diff > 0.39269909262657166) {
                D_80770DE4 *= 1.0 + ((f64)(diff - 0.3926991f) * 20.0);
            }
        }

        if ((f64)angle > 0.7853981852531433 && (f64)angle < 5.497787296772003) {
            D_80770DE4 = (1.0f - (sinApprox(((2.0 * (f64)angle) / 3.0) + 2.617993950843811) * directionality)) * D_80770DE4;
        }
        if (D_80770DE4 < 1.0f) {
            D_80770DE4 = 1.0f;
        }

        level = (((f32)(range * 4000) / sqrtf(D_80770DE4)) - (((f32)(range * 4000) / 7.74596600000000013) - 32767.0));
        if (level >= 0x8000) {
            level = 0x7FFF;
        }
        level = (volume * level) / 255.0;
    }

    if (level >= 1001) {
        return sfxPlayOnFreeSlot(sfxId, level, (1.0f - sinApprox(angle)) * 63.5, (f64)pitch / 127.0, spread, fx);
    }
    return -1;
}

extern struct GfSndState *D_807457D0[];
extern u8 D_807457D8;
extern struct GfSndState *D_807457E4[];
extern u8 D_80745834;

void sfxPlayWithRandomPan(s16 sfxId, u8 volume, u8 pitchByte, u8 spread, u8 behind) {
    s32 vol;
    f32 pan;
    f32 pitch;
    u8 reverb = 0;

    vol = (s32)((volume * 0x7FFF) / 255.0);
    if (vol < 1001) {
        return;
    }

    pitch = (u32)pitchByte / 127.0;
    pan = ((u32)randomLcgNext() / 4294967295.0) * (2.0 * (u32)spread) + (63.5 - (u32)spread);

    if (spread != 0) {
        vol = (1.0 - (((u32)randomLcgNext() / 4294967295.0) * ((u32)spread / 155.0))) * vol;
        pitch = (((u32)randomLcgNext() / 4294967295.0) * ((u32)spread / 100.0)) + (pitch - ((u32)spread / 255.0));
    }

    if (D_8077058E >= 21) {
        reverb = (D_8077058E * 100) / 255;
    }
    if (behind != 0) {
        reverb |= 0x80;
    }

    if (D_807457D0[D_807457D8] != 0) {
        n_alSndpStop(D_807457D0[D_807457D8]);
    }
    n_alSndpPlay(D_8076D1F8, sfxId, (u16)vol, (u8)pan, pitch, reverb, &D_807457D0[D_807457D8]);
    n_alSndpSetPriority(D_807457D0[D_807457D8], 0);
    D_807457D8 ^= 1;
}

s16 sfxPlayOnFreeSlot(s16 sfxId, s32 volume, f32 pan, f32 pitch, u8 spread, u8 fx) {
    s16 res;
    s16 i;

    if (spread != 0) {
        volume = (1.0 - (((u32)randomLcgNext() / 4294967295.0) * ((u32)spread / 155.0))) * volume;
        pitch = (((u32)randomLcgNext() / 4294967295.0) * ((u32)spread / 100.0)) + (pitch - ((u32)spread / 255.0));
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
            fx = ((((D_8077058E * 100) / 255) < (fx & 0x7F)) ? (fx & 0x7F) : ((D_8077058E * 100) / 255)) | (fx & 0x80);
        }

        if (sfxId < 0x800) {
            n_alSndpPlay(D_8076D1F8, sfxId, (u16)volume, (u8)pan, pitch, fx, &D_807457E4[D_80745834]);
        } else {
            n_alSndpPlay(D_8076D1FC, sfxId - 0x7FF, (u16)volume, (u8)pan, pitch, fx, &D_807457E4[D_80745834]);
        }

        if (sfxId == 0x137) {
            n_alSndpSetPriority(D_807457E4[D_80745834], 100);
        }

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

extern struct GfSndState *D_807457C8;

void sfxPlayAtPosition(f32 x, f32 y, f32 z, s16 sfxId, u8 volume, f32 pitch, u8 spread, u8 range) {
    s32 dx, dy, dz;
    s32 vol;
    f32 pan;
    u8 reverb;
    f64 pad;

    reverb = 0;
    dx = gPlayerSlots->x - x;
    dy = gPlayerSlots->y - y;
    dz = gPlayerSlots->z - z;
    D_80770DE4 = sqrtf(dx * dx + dy * dy + dz * dz);
    if (D_80770DE4 < 1.0f) {
        D_80770DE4 = 1.0f;
    }
    vol = (s32)((((range * 4000) / sqrtf(D_80770DE4))) - (((f32)(range * 4000) / 7.74596600000000013) - 32767.0));
    if (vol >= 0x8000) {
        vol = 0x7FFF;
    }
    vol = (s32)((volume * vol) / 255.0);
    if (vol >= 0x8000) {
        vol = 0x7FFF;
    }
    if (vol < 1001) {
        return;
    }
    vol = (s32)((volume * vol) / 255.0);
    if (spread != 0) {
        vol = (s32)((1.0 - (((u32)randomLcgNext() / 4294967295.0) * ((u32)spread / 155.0))) * vol);
        pitch = (pitch - ((u32)spread / 255.0)) + (((u32)randomLcgNext() / 4294967295.0) * ((u32)spread / 100.0));
    }
    pan = mathAngleBetweenPointsRad(gPlayerSlots->x, gPlayerSlots->z, x, z) - gPlayerSlots->yaw;
    if (pan < 0.0f) {
        pan += 6.2831855f;
    }
    if (pan > 0.7853982f && pan < 5.497787296772003) {
        vol = (s32)(((sinApprox(((2.0 * pan) / 3.0) + 2.617993950843811) * 0.3) + 1.0) * vol);
    }
    pan = (1.0f - sinApprox(pan)) * 63.5;
    if (D_80745838 != 0) {
        reverb = 30;
    } else if (D_8077058E >= 21) {
        reverb = (D_8077058E * 100) / 255;
    }
    if (D_807457C8 != 0) {
        n_alSndpStop(D_807457C8);
    }
    osSetThreadPri(NULL, 26);
    if (sfxId < 0x800) {
        n_alSndpPlay(D_8076D1F8, sfxId, (u16)vol, (u8)pan, pitch, reverb, &D_807457C8);
    } else {
        n_alSndpPlay(D_8076D1FC, sfxId - 0x7FF, (u16)vol, (u8)pan, pitch, reverb, &D_807457C8);
    }
    osSetThreadPri(NULL, 10);
}

extern u8 gCurrentPlayerIndex;


void sfxPlayAtPositionForPlayer(f32 x, f32 y, f32 z, s16 sfxId, u8 volume, u8 pitchByte, u8 spread, u8 range, f32 directionality) {
    s32 dx;
    s32 dy;
    s32 dz;
    s32 vol;
    f32 angle;
    f32 pitch;
    u8 behind;
    u8 fx;

    behind = 0;
    fx = 0;

    if (gActivePlayerState->sfxHandle != 0) {
        n_alSndpStop(gActivePlayerState->sfxHandle);
    }

    angle = mathAngleBetweenPointsRad(gPlayerSlots[gCurrentPlayerIndex].x, gPlayerSlots[gCurrentPlayerIndex].z, x, z) - gPlayerSlots[gCurrentPlayerIndex].yaw;
    if (angle < 0.0f) {
        angle += 6.2831855f;
    }

    if (angle > 1.5707964f && angle < 4.71238911151886) {
        behind = 1;
    }

    if (range == 0) {
        vol = ((u32)volume * 32767.0) / 255.0;
        if (D_80770DE4 < 23.0f) {
            angle = 0.0f;
        }
    } else {
        dx = gPlayerSlots[gCurrentPlayerIndex].x - x;
        dy = gPlayerSlots[gCurrentPlayerIndex].y - y;
        dz = gPlayerSlots[gCurrentPlayerIndex].z - z;
        D_80770DE4 = sqrtf(dx * dx + dy * dy + dz * dz);

        if (D_80770DE4 < 23.0f) {
            angle = 0.0f;
            behind = 0;
        }

        if (angle > 0.7853982f && angle < 5.497787296772003) {
            D_80770DE4 = (1.0f - (sinApprox(((2.0 * angle) / 3.0) + 2.617993950843811) * directionality)) * D_80770DE4;
        }

        if (D_80770DE4 < 1.0f) {
            D_80770DE4 = 1.0f;
        }

        vol = (((range * 4000) / sqrtf(D_80770DE4)) - (((f32)(range * 4000) / 7.74596600000000013) - 32767.0));
        if (vol >= 0x8000) {
            vol = 0x7FFF;
        }
        vol = (volume * vol) / 255.0;
    }

    if (vol >= 1001) {
        if (spread != 0) {
            vol = (1.0 - (((u32)randomLcgNext() / 4294967295.0) * ((u32)spread / 155.0))) * vol;
            pitch = (((u32)randomLcgNext() / 4294967295.0) * ((u32)spread / 100.0)) + (1.0 - ((u32)spread / 255.0));
        } else {
            pitch = 1.0f;
        }

        pitch = ((u32)pitchByte * pitch) / 127.0;

        if (D_8077058E >= 21) {
            fx = (D_8077058E * 100) / 255;
        }

        angle = (1.0f - sinApprox(angle)) * 63.5;

        if (behind != 0) {
            fx |= 0x80;
        }

        n_alSndpPlay(D_8076D1F8, sfxId, (u16)vol, (u8)angle, pitch, fx, &gActivePlayerState->sfxHandle);
    }
}

extern s32 D_8000DDCC;
extern s32 D_8076D200[];
extern void *D_8076BF38[];
extern ALCSeq D_8076BF48[];
extern u8 D_80770598[];


void seqLoadAndPlay(s32 seqIndex, u8 seqId, f32 volume) {
    u32 tries;
    tries = 0;
    alSeqpStop((ALSeqPlayer *)gSeqPlayers[seqIndex]);
    if (alCSPGetState(&gSeqPlayers[seqIndex]->al) != 0) {
        do {
            tries++;
            if (alCSPGetState(&gSeqPlayers[seqIndex]->al) == 0) {
                break;
            }
        } while (tries != 0x1E8480);
    }
    if (tries >= 0x1E8480) {
        alSeqpStop((ALSeqPlayer *)gSeqPlayers[seqIndex]);
        if (alCSPGetState(&gSeqPlayers[seqIndex]->al) != 0 && tries < 0x3D0900) {
            do {
                tries++;
                if (alCSPGetState(&gSeqPlayers[seqIndex]->al) == 0) {
                    break;
                }
            } while (tries < 0x3D0900);
        }
    }
    D_80770598[seqIndex] = 0;
    D_80770568[seqIndex] = volume;
    D_80770560[seqIndex] = seqId;
    tries = (s32)heapAlloc(0x8000);  // FAKE: reusing the retry counter as the buffer pointer keeps its stack home at sp+0x44
    {
        s32 base = D_8076D200[seqId];
        s32 addr = base + D_8000DDCC;
        s32 len = D_8076D200[seqId + 1] - base;
        if (len & 1) {
            len++;
        }
        dmaReadAssetDecompress(addr, D_8076BF38[seqIndex], &len, 0x80, 0, 1, (void *)tries);
    }
    heapFree((void *)tries);
    n_alCSeqNew(&D_8076BF48[seqIndex], D_8076BF38[seqIndex]);
    alSeqpSetSeq((ALSeqPlayer *)gSeqPlayers[seqIndex], (ALSeq *)&D_8076BF48[seqIndex]);
    resetCSPChannelStates(gSeqPlayers[seqIndex]);
    seqUpdateVolume(seqIndex);
    alCSPPlay(&gSeqPlayers[seqIndex]->al);
}

extern s8 gMusicVolume;
extern s8 gSfxVolume;
extern s16 D_807454F0[];
extern f32 D_807457B8[];

void seqUpdateVolume(s32 seqIndex) {
    f32 volume = gMusicVolume;
    s32 mode = sSfxFlagTable[D_80770560[seqIndex]] & 0xC00;
    switch (mode) {
    case 0x400:
        volume = gSfxVolume;
        break;
    case 0x800:
        if (!((f32)gSfxVolume < volume)) {
            volume = gSfxVolume;
        }
        break;
    }
    alSeqpSetVol((ALSeqPlayer *)gSeqPlayers[seqIndex], (s16)((f64)((((f32)D_807454F0[D_80770560[seqIndex]]) * D_80770568[seqIndex]) * D_807457B8[seqIndex]) * ((f64)volume / 40.0) * 25000.0 / 32767.0));
}

void seqSetChannelVolumeScale(s32 seqIndex, f32 scale) {
    D_807457B8[seqIndex] = scale;
    seqUpdateVolume(seqIndex);
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
            do {} while (0);  // FAKE: empty loop splits the block so the D_80770568[i] reload stays
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


void seqSetTargetVolume(s32 seqIndex, f32 targetVolume) {
    D_80770578[seqIndex] = targetVolume;
    D_80770598[seqIndex] = 1;
}


void seqSetVolumeInstant(s32 seqIndex, f32 volume) {
    D_80770578[seqIndex] = volume;
    D_80770568[seqIndex] = volume;
    seqUpdateVolume(seqIndex);
}

extern f32 D_80770588;

void seqPlayWithDefaultVolume(s32 seqIndex, u8 seqId) {
    seqLoadAndPlay(seqIndex, seqId, D_80770588);
}

void seqLoadAndPlayWithReverb(s32 seqIndex, u8 seqId, f32 volume) {
    f32 pan, vol;

    seqLoadAndPlay(seqIndex, seqId, volume);
    pan = ((f64)(u32)D_8077058E * 0.3) / 255.0;
    vol = (((f64)(u32)D_8077058E * 0.35) / 255.0) + 1.0;
    if (seqIndex != 0) {
        if (sSfxFlagTable[D_80770560[seqIndex]] & 1) {
            alCSPSetChlPanVolume(&gSeqPlayers[seqIndex]->al, pan, vol);
        } else {
            alCSPSetChlPanVolume(&gSeqPlayers[seqIndex]->al, 0.0f, 1.0f);
        }
    }
    seqUpdateUnderwaterAudio(seqIndex);
}

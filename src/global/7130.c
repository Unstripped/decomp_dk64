#include "common.h"
#include "seqplayer.h"
#include "map.h"
#include "actor.h"
#include "sched.h"
#include "model.h"
#include "cutscene.h"
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

typedef struct {
    s16 map;
    s16 chunk;
    s16 sfxId;
    s16 altSfx;
    u8 indoors;
    u8 pad9;
} AmbientSfxEntry;

s16 sSeqBaseVolume[176] = {
    0x0, 0x4650, 0x6590, 0x59D8, 0x7530, 0x6D60, 0x7FFF, 0x7FFF,
    0x6590, 0x688F, 0x58EF, 0x688F, 0x7FFF, 0x688F, 0x4650, 0x7FFF,
    0x3E80, 0x4650, 0x55F0, 0x7FFF, 0x7FFF, 0x4650, 0x4650, 0x2710,
    0x4650, 0x7D00, 0x7FFF, 0x7FFF, 0x5DC0, 0x6590, 0x7FFF, 0x7FFF,
    0x7530, 0x4650, 0x7FFF, 0x6D60, 0x7FFF, 0x6D60, 0x7FFF, 0x4650,
    0x4650, 0x4650, 0x7FFF, 0x4650, 0x4650, 0x7FFF, 0x7FFF, 0x36B0,
    0x4650, 0x4650, 0x4650, 0x4650, 0x6D60, 0x5DC0, 0x7148, 0x4650,
    0x6590, 0x5FB4, 0x6D60, 0x7FFF, 0x7FFF, 0x6D60, 0x6D60, 0x5DC0,
    0x5DC0, 0x7FFF, 0x4650, 0x7FFF, 0x5DC0, 0x7FFF, 0x5DC0, 0x4650,
    0x4650, 0x4650, 0x5DC0, 0x7FFF, 0x7FFF, 0x6590, 0x6590, 0x6590,
    0x6590, 0x6590, 0x6590, 0x6590, 0x55F0, 0x4650, 0x4650, 0x4650,
    0x4650, 0x4650, 0x4650, 0x4650, 0x4650, 0x4650, 0x4650, 0x4650,
    0x5DC0, 0x4650, 0x4650, 0x4650, 0x4650, 0x4650, 0x61A8, 0x4650,
    0x4650, 0x6D60, 0x55F0, 0x4650, 0x4650, 0x55F0, 0x6D60, 0x4650,
    0x6590, 0x7FFF, 0x4650, 0x4650, 0x61A8, 0x7530, 0x5DC0, 0x5DC0,
    0x5DC0, 0x7FFF, 0x6D60, 0x5DC0, 0x6D60, 0x6D60, 0x6D60, 0x6D60,
    0x6D60, 0x6D60, 0x6D60, 0x6D60, 0x6D60, 0x6D60, 0x6D60, 0x6D60,
    0x6D60, 0x7FFF, 0x6D60, 0x6D60, 0x6D60, 0x6D60, 0x6D60, 0x7530,
    0x7FFF, 0x7148, 0x7530, 0x5DC0, 0x6D60, 0x6D60, 0x7FFF, 0x7FFF,
    0x61A8, 0x6D60, 0x6D60, 0x6D60, 0x6D60, 0x6D60, 0x6D60, 0x6D60,
    0x6D60, 0x7530, 0x6D60, 0x4650, 0x6590, 0x7148, 0x5DC0, 0x5DC0,
    0x5DC0, 0x5DC0, 0x5DC0, 0x5DC0, 0x7FFF, 0x7FFF, 0x7FFF, 0x0,
};
u8 sSfxAreaAmbientActive = 0;
u8 sSfxMode = 0;
u16 sSfxFlagTable[176] = {
    0x0, 0x101, 0x100, 0x188, 0x189, 0x100, 0x100, 0x440,
    0x189, 0x8C2, 0x8C2, 0x8C2, 0x8C2, 0x8C2, 0x100, 0xA34,
    0x19A, 0x19A, 0x8C4, 0x109, 0xABD, 0x101, 0x637, 0x637,
    0x647, 0x100, 0x100, 0x188, 0x100, 0x100, 0x18A, 0x100,
    0x63F, 0x63F, 0x1D4, 0x63F, 0x198, 0x192, 0x914, 0x100,
    0x8CD, 0x85E, 0x89D, 0x854, 0x854, 0x444, 0x8C5, 0x635,
    0x188, 0x100, 0x100, 0x18A, 0x18A, 0x100, 0x89A, 0x100,
    0x101, 0x98, 0x190, 0x934, 0x108, 0x188, 0x18B, 0x100,
    0x100, 0x445, 0x925, 0x447, 0x101, 0x4C5, 0x188, 0x19A,
    0x192, 0x190, 0x100, 0x900, 0x63D, 0x100, 0x100, 0x100,
    0x100, 0x188, 0x188, 0x101, 0x193, 0x102, 0x118, 0x118,
    0x100, 0x188, 0x100, 0x101, 0x100, 0x100, 0x100, 0x100,
    0x912, 0x100, 0x100, 0x100, 0x100, 0x1CA, 0x108, 0x100,
    0x1AA, 0x101, 0x100, 0x19A, 0x190, 0x101, 0x109, 0x101,
    0x101, 0x100, 0x892, 0x892, 0x100, 0x188, 0x100, 0x100,
    0x100, 0x100, 0x100, 0x101, 0x198, 0x110, 0x100, 0x4BC,
    0x43E, 0x100, 0x100, 0x100, 0x100, 0x101, 0x100, 0x100,
    0x100, 0x100, 0x100, 0x100, 0x100, 0x101, 0x100, 0x445,
    0x647, 0x647, 0x645, 0x645, 0x100, 0x100, 0x100, 0x645,
    0x100, 0x100, 0x100, 0x100, 0x100, 0x100, 0x100, 0x100,
    0x101, 0x100, 0x100, 0x100, 0x100, 0x100, 0x100, 0x100,
    0x100, 0x188, 0x1D8, 0x18A, 0x645, 0x18, 0x108, 0x0,
};
f32 sSeqVolumeScale[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
struct GfSndState *gSfxPositionalHandle = NULL;
s32 D_807457CC = 0;
struct GfSndState *sSfxRandomPanHandles[2] = { NULL, NULL };
u8 sSfxRandomPanIndex = 0;
struct GfSndState *sRainSfxHandle = NULL;
s32 D_807457E0 = 0;
struct GfSndState *gSfxFreeSlotHandles[20] = { NULL };
u8 sSfxFreeSlotCursor = 0;
u8 gAudioUnderwater = 0;
s8 gSfxVolume = 0x28;
s8 gMusicVolume = 0x28;
s8 gAudioOutputMode = 0;
struct GfSndState *sSoundSlotHandles[22] = { NULL };
f32 D_807458A0[15] = {
    0.2f, 0.22f, 0.24f, 0.27f, 0.29f,
    0.32f, 0.37f, 0.42f, 0.47f, 0.52f,
    0.6f, 0.7f, 0.8f, 1.0f, 1.0f,
};
s16 sSfxChannelSounds[12] = { 0 };
f32 sSfxChannelVolumes[12] = { 0.0f };
s16 sSfxChannelStates[12] = { 0 };
s32 sSfxChannelMasks[4][12] = { 0 };
AmbientSfxEntry sAmbientSfxTable[29] = {
    { 0x7, 0, 0x1, 0x1E, 0, 0 },
    { 0x7, 2, 0x0, 0x0, 1, 0 },
    { 0x7, 3, 0xA0, 0x0, 0, 0 },
    { 0x7, 6, 0x0, 0x0, 1, 0 },
    { 0x7, 7, 0x1, 0x0, 0, 0 },
    { 0x7, 8, 0x0, 0x0, 1, 0 },
    { 0x7, 10, 0x0, 0x0, 1, 0 },
    { 0x7, 14, 0xA1, 0x0, 0, 0 },
    { 0x7, 15, 0x0, 0x0, 1, 0 },
    { 0x7, 16, 0x0, 0x0, 1, 0 },
    { 0x7, 18, 0x0, 0x0, 1, 0 },
    { 0x26, 0, 0x0, 0x0, 1, 0 },
    { 0x26, 4, 0x0, 0x0, 0, 0 },
    { 0x26, 7, 0x0, 0x0, 1, 0 },
    { 0x26, 9, 0x0, 0x0, 1, 0 },
    { 0x26, 10, 0x0, 0x0, 1, 0 },
    { 0x26, 11, 0x0, 0x0, 1, 0 },
    { 0x26, 12, 0x0, 0x0, 0, 0 },
    { 0x1E, 1, 0x0, 0x0, 1, 0 },
    { 0x1E, 3, 0x0, 0x0, 1, 0 },
    { 0x1E, 6, 0x0, 0x0, 1, 0 },
    { 0x1E, 7, 0x0, 0x0, 1, 0 },
    { 0x1E, 9, 0x0, 0x0, 0, 0 },
    { 0x1E, 12, 0x0, 0x0, 0, 0 },
    { 0x1E, 14, 0x0, 0x0, 0, 0 },
    { 0x1E, 17, 0x0, 0x0, 1, 0 },
    { 0x1A, 5, 0x34, 0x34, 1, 0 },
    { 0x1A, 9, 0x0, 0x0, 0, 0 },
    { 0x1A, 23, 0x33, 0x33, 1, 0 },
};

u8 gSeqCurrentId[4];
f32 gSeqVolume[4];
f32 gSeqTargetVolume[4];
f32 D_80770588;
u8 gAmbientAudioLevels[3];
f32 gSfxSpeedVolume;
f32 gSfxPrevSpeed;
u8 gSeqVolumeFading[4];
Actor *gSfxSourceActor[22];
s16 gSfxSourceModelSlot[24];
s16 gSfxSourceVoice[24];
s16 gSfxSourceListIndex[24];
f32 gSfxVoicePrevDist[22];
u8 gSfxVoiceStopTimer[24];
u8 gSfxVoiceExclusive[24];
s16 gSfxVoiceSoundId[24];
s16 gSfxVoiceSourceCount[24];
u8 gSfxVoiceFxLevel[24];
u8 gSfxSourceRange[24];
s16 gSfxVoiceSources[22][22];
f32 gSfxVoicePitch[22];
f32 gSfxVoiceModCounter[22];
f32 gSfxVoiceCurPitch[22];
f32 gSfxVoiceBasePitch[22];
u8 gSfxVoicePlayedOnce[24];
u8 gSfxVoiceVolume[24];
s8 gSfxVoiceNode[24];
s16 gSfxVoiceSentVolume[24];
s16 gSfxVoiceSentPan[24];
f32 gSfxVoiceSentPitch[22];
u8 gAmbientIndoorReverb;
u8 gAmbientIndoors;
u8 D_80770DCA;
u8 gAmbientWasOutside;
f32 gAmbientNearestPan;
f32 gAmbientNearestFx;
f32 gAmbientNearestDist;
u8 D_80770DD8[4];
f32 D_80770DDC;
f32 gSfxFrontFactor;
f32 gSfxDistance;
f32 D_80770DE8;
f32 gSfxLeftLevel;
f32 gSfxFrontLevel;
f32 gSfxRearLevel;
struct GfSndState *gLoopSfxHandles[16];
u32 gAmbientGroupRetriggerTick[16];
f32 gAmbientGroupSentPitch[16];
f32 gAmbientGroupSentVolume[16];
f32 gAmbientGroupSentPan[16];

u8 sfxGetBankIndex(s16 sfxId) {
    return (sSfxFlagTable[sfxId] & 6) >> 1;
}

u8 sfxGetChannelIndex(s16 sfxId) {
    return (sSfxFlagTable[sfxId] & 0x78) >> 3;
}

void sfxSetMode(mode)
u8 mode;
{
    sSfxMode = mode;
}

extern PlayerStruct *gPlayerSlots;
extern s32 gCurrentMap;

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

    count = sizeof(sAmbientSfxTable) / sizeof(sAmbientSfxTable[0]);  // ORIG: the row count is stored before the call: li t0,29 at 0xb0, sh t0,0x24(sp) (its own home) in the jal delay slot at 0xc8, lh t0,0x24(sp) at 0xd4, slt at 0xf4
    chunk = mapChunkFindByPosition(gPlayerSlots->camX, gPlayerSlots->camY, gPlayerSlots->camZ, 0);

    for (i = 0; i < count; i++) {
        if (gCurrentMap == sAmbientSfxTable[i].map && chunk == sAmbientSfxTable[i].chunk) {
            gAmbientIndoors = sAmbientSfxTable[i].indoors;
            sfxAllocateChannel(sAmbientSfxTable[i].sfxId, 1.0f);
            if (sAmbientSfxTable[i].altSfx != 0) {
                D_80770DD8[1] = sAmbientSfxTable[i].altSfx;
            }
            return;
        }
    }

    D_80770DD8[1] = 0xFF;
}
void sfxPlayCurrent(u8 unused0, u8 unused1, u8 unused2) {
    sfxStartAreaAmbient();
}

extern N_CSPlayer *gSeqPlayers[];

void sfxUpdateChannels(void) {
    u8 i;
    u8 j;
    u8 channel;
    u8 bank;
    s8 bankChannel[4] = { -1, -1, -1, -1 };
    u8 seqState[4] = { 0, 0, 0, 0 };
    s16 sfxId;
    u8 vol;
    s32 sel;

    if (sSfxAreaAmbientActive != 0) {
        for (i = 0; i < 4; i++) {
            seqState[i] = alCSPGetState(&gSeqPlayers[i]->al);
        }

        for (i = 0; i < 12; i++) {
            sfxId = sSfxChannelSounds[i];
            if (sfxId != 0) {
                channel = sfxGetChannelIndex(sfxId);
                bank = sfxGetBankIndex(sfxId);
                if (sfxId == gSeqCurrentId[bank] && seqState[bank] == 1) {
                    if (sSfxChannelStates[i] == 1) {
                        sSfxChannelStates[i] = 2;
                    }
                    if (sSfxChannelStates[i] == 2) {
                        for (j = 0; j < 4; j++) {
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
                        }
                    }
                }
                if (!(sSfxFlagTable[sfxId] & 0x100) && sSfxChannelStates[i] == 2) {
                    if (seqState[sfxGetBankIndex(sfxId)] == 0 || sfxId != gSeqCurrentId[bank]) {
                        sfxStopChannel(sfxId, 0);
                    }
                }
            }
        }

        for (i = 0; i < 12; i++) {
            sfxId = sSfxChannelSounds[i];
            if (sfxId != 0) {
                if (sSfxFlagTable[sfxId] & 0x80) {
                    for (j = 0; j < 4; j++) {
                        bankChannel[j] = -1;
                    }
                }
                bankChannel[sfxGetBankIndex(sfxId)] = i;
            }
        }

        for (i = 0; i < 4; i++) {
            s8 idx = bankChannel[i];
            if (seqState[i] != 0) {
                if (seqState[i] == 1) {
                    if (idx == -1) {
                        seqSetTargetVolume(i, 0.0f);
                        if (gSeqVolume[i] < 0.1 || gSeqCurrentId[i] == 0x4B) {
                            alSeqpStop((ALSeqPlayer *)gSeqPlayers[i]);
                        }
                    } else {
                        if (gSeqCurrentId[i] != sSfxChannelSounds[idx] || (sSfxChannelStates[idx] == 0 && (sSfxFlagTable[sSfxChannelSounds[idx]] & 0x200))) {
                            alSeqpStop((ALSeqPlayer *)gSeqPlayers[i]);
                        } else if (gSeqVolume[i] == 0.0f) {
                            seqSetTargetVolume(i, sSfxChannelVolumes[idx]);
                        }
                    }
                }
            } else {
                if (idx != -1) {
                    if (gSeqCurrentId[i] == sSfxChannelSounds[idx] && sSfxChannelStates[idx] == 2) {
                        seqSetTargetVolume(i, sSfxChannelVolumes[idx]);
                        alCSPPlay(&gSeqPlayers[i]->al);
                    } else {
                        seqLoadAndPlayWithReverb(i, sSfxChannelSounds[idx], sSfxChannelVolumes[idx]);
                        sSfxChannelStates[sfxGetChannelIndex(sSfxChannelSounds[idx])] = 1;
                    }
                }
            }
        }
    }
}

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
            if (sfxId == gSeqCurrentId[bank]) {
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
    if ((sfxId == sSfxChannelSounds[sfxGetChannelIndex((s16)sfxId)]) && (sfxId == gSeqCurrentId[bank])) {
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

f32 sfxGetChannelVolume(sfxId)
s32 sfxId;
{
    u8 bank = sfxGetBankIndex((s16)sfxId);
    if (sfxId == gSeqCurrentId[bank]) {
        if (alCSPGetState(&gSeqPlayers[bank]->al) == 1) {
            return gSeqVolume[bank];
        }
    }
    return 0.0f;
}

void sfxSetChannelTempo(s32 sfxId, f32 scale) {
    u8 bank = sfxGetBankIndex((s16)sfxId);
    if ((sfxId == sSfxChannelSounds[sfxGetChannelIndex((s16)sfxId)]) && (sfxId == gSeqCurrentId[bank])) {
        alCSPSetTempo(&gSeqPlayers[bank]->al, (s32)(alCSPGetTempo(&gSeqPlayers[bank]->al) * scale));
    }
}

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
    dx = gPlayerSlots->camX - x;
    dy = gPlayerSlots->camY - y;
    dz = gPlayerSlots->camZ - z;

    diff = ((f64)directionality > 0.8) ? ((f64)directionality - 0.8) : -((f64)directionality - 0.8);

    if (diff < 0.1 && dy < 0.0f) {
        dy *= 20.0f;
    }

    gSfxDistance = sqrtf((dx * dx) + (dy * dy) + (dz * dz));

    if ((f64)directionality >= 0.8) {
        f32 l_dz = gPlayerSlots->focusZ - gPlayerSlots->camZ;
        f32 l_dx = gPlayerSlots->focusX - gPlayerSlots->camX;
        viewPitch = mathAngleBetweenPointsRad(gPlayerSlots->camY, 0.0f, gPlayerSlots->focusY, sqrtf((l_dz * l_dz) + (l_dx * l_dx)));

        l_dz = z - gPlayerSlots->camZ;
        l_dx = x - gPlayerSlots->camX;
        D_80770DDC = mathAngleBetweenPointsRad(gPlayerSlots->camY, 0.0f, y, sqrtf((l_dz * l_dz) + (l_dx * l_dx))) - viewPitch;

        if (D_80770DDC < 0.0f) {
            D_80770DDC += 6.2831855f;
        }

        if (D_80770DDC > 0.3926991f && (f64)D_80770DDC < 5.890486389398575) {
            gSfxDistance = (1.0f - (sinApprox((f32)(((f64)D_80770DDC * 4.0 / 7.0) + 2.942101601958275)) * 4.0f)) * gSfxDistance;
        }
    }

    D_80770DDC = mathAngleBetweenPointsRad(gPlayerSlots->camX, gPlayerSlots->camZ, x, z) - gPlayerSlots->camYaw;
    if (D_80770DDC < 0.0f) {
        D_80770DDC += 6.2831855f;
    }

    if (D_80770DDC > 0.7853982f && (f64)D_80770DDC < 5.497787296772003 && (f64)viewPitch < 4.0) {
        gSfxDistance = (1.0f - (sinApprox((f32)(((2.0 * (f64)D_80770DDC) / 3.0) + 2.617993950843811)) * directionality)) * gSfxDistance;
    }

    if (gSfxDistance < 1.0f) {
        gSfxDistance = 1.0f;
    }

    {
        f32 dist = (f32)(range * 0xFA0);
        f64 temp = ((f64)(dist / sqrtf(gSfxDistance))) - (((f64)dist * 0.12909946) - 32767.0);
        f64 volumeScale = (f64)volume;
        level = (f32)(temp * volumeScale * 0.00392156862745098);
    }

    if (level < 10.0f) {
        return 0.0f;
    }

    gSfxFrontFactor = cosApprox(D_80770DDC);
    D_80770DDC = (f32)((f64)(1.0f - sinApprox(D_80770DDC)) * 63.5);

    if (level < 10.0f) {
        return 0.0f;
    }

    if (level > 32767.0f) {
        level = 32767.0f;
    }

    return level;
}

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
    gSfxLeftLevel += level * (1.0f - panRatio);

    if (gSfxFrontFactor > 0.0f) {
        gSfxFrontLevel += level * gSfxFrontFactor;
    }
    if (gSfxFrontFactor < 0.0f) {
        gSfxRearLevel -= level * gSfxFrontFactor;
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


AmbientAudioParam sAmbientGroupParams[15] = {
    { 0x106, 0xFF, 0x5A, 0.7f, 1.0f },
    { 0x11D, 0xFF, 0xC8, 0.3f, 1.0f },
    { 0x11B, 0x1E, 0x64, 4.0f, 1.0f },
    { 0x1E, 0xFF, 0x5A, 1.7f, 1.0f },
    { 0x11B, 0x64, 0x64, 0.7f, 1.0f },
    { 0x105, 0xB4, 0x50, 2.0f, 1.0f },
    { 0x138, 0x8C, 0x46, 0.2f, 1.0f },
    { 0x105, 0xFF, 0x5A, 2.0f, 1.0f },
    { 0x138, 0x28, 0x5A, 0.2f, 1.0f },
    { 0x138, 0x5A, 0x5A, 0.7f, 0.595f },
    { 0x12C, 0x3C, 0x5A, 0.7f, 1.8f },
    { 0x808, 0x5A, 0x5A, 0.3f, 1.0f },
    { 0x808, 0x3C, 0x6E, 0.7f, 1.0f },
    { 0x138, 0x3C, 0x4B, 0.7f, 1.0f },
    { 0x138, 0x3C, 0x3C, 0.7f, 1.0f },
};
MapAudioEntry gMapAudioTable[230] = {
    { 0x0, 0x0, 1 }, { 0x6, 0x0, 1 }, { 0x15, 0x0, 1 }, { 0x58, 0x0, 1 }, { 0x5, 0x64, 1 }, { 0x2, 0x32, 6 },
    { 0x58, 0xC8, 1 }, { 0x1, 0x0, 1 }, { 0x64, 0x32, 1 }, { 0x5, 0x96, 1 }, { 0x58, 0x0, 1 }, { 0x58, 0x0, 1 },
    { 0x5, 0x64, 1 }, { 0x5, 0x64, 1 }, { 0x58, 0x0, 1 }, { 0x1D, 0x32, 6 }, { 0x15, 0x64, 1 }, { 0x71, 0x0, 25 },
    { 0x58, 0x0, 1 }, { 0x1A, 0x64, 1 }, { 0x15, 0x64, 1 }, { 0x1A, 0x64, 1 }, { 0x1A, 0x64, 1 }, { 0x1A, 0x64, 1 },
    { 0x1A, 0x64, 1 }, { 0x1F, 0x32, 1 }, { 0x1C, 0x32, 25 }, { 0x58, 0x0, 1 }, { 0x8A, 0x32, 1 }, { 0x1C, 0x32, 1 },
    { 0x38, 0x0, 1 }, { 0x5, 0x32, 1 }, { 0x58, 0x0, 1 }, { 0x5, 0x96, 1 }, { 0x0, 0x0, 1 }, { 0x58, 0x0, 1 },
    { 0x31, 0x32, 1 }, { 0x32, 0x0, 1 }, { 0xE, 0x0, 6 }, { 0x58, 0x0, 1 }, { 0x55, 0x0, 1 }, { 0x37, 0x0, 1 },
    { 0x35, 0x0, 1 }, { 0x4E, 0x0, 7 }, { 0x4F, 0x0, 1 }, { 0x50, 0x0, 1 }, { 0x4E, 0x0, 7 }, { 0x4D, 0x0, 7 },
    { 0x44, 0x0, 1 }, { 0x3F, 0x32, 1 }, { 0x58, 0x0, 1 }, { 0x5B, 0xC8, 25 }, { 0x5D, 0x0, 7 }, { 0x40, 0x0, 1 },
    { 0x5C, 0x0, 1 }, { 0x58, 0x0, 1 }, { 0x5E, 0x0, 5 }, { 0x5F, 0x0, 5 }, { 0x5F, 0x0, 5 }, { 0x5E, 0x0, 5 },
    { 0x63, 0x0, 7 }, { 0x5E, 0x0, 5 }, { 0x5F, 0x0, 5 }, { 0x62, 0x0, 1 }, { 0x63, 0x0, 1 }, { 0x58, 0x0, 5 },
    { 0x58, 0x0, 5 }, { 0x58, 0x0, 5 }, { 0x58, 0x0, 5 }, { 0x58, 0x0, 5 }, { 0x62, 0x0, 1 }, { 0x62, 0x0, 1 },
    { 0x53, 0x46, 1 }, { 0x40, 0x0, 1 }, { 0x58, 0x0, 5 }, { 0x58, 0x0, 5 }, { 0x0, 0x0, 1 }, { 0x58, 0x0, 1 },
    { 0x58, 0x14, 1 }, { 0x58, 0x14, 1 }, { 0x86, 0x0, 1 }, { 0x1, 0x0, 1 }, { 0x58, 0x32, 6 }, { 0x64, 0x0, 1 },
    { 0x67, 0x0, 6 }, { 0x67, 0x0, 6 }, { 0x67, 0x0, 6 }, { 0x69, 0x0, 6 }, { 0x88, 0x50, 6 }, { 0x77, 0x0, 1 },
    { 0x76, 0x0, 5 }, { 0x76, 0x0, 5 }, { 0x76, 0x0, 5 }, { 0x76, 0x0, 5 }, { 0x76, 0x0, 5 }, { 0x67, 0x0, 1 },
    { 0x58, 0x0, 1 }, { 0x70, 0x32, 1 }, { 0x67, 0x0, 6 }, { 0x58, 0x0, 1 }, { 0x67, 0x0, 1 }, { 0x58, 0x0, 1 },
    { 0x58, 0x0, 1 }, { 0x58, 0x0, 1 }, { 0x58, 0x0, 1 }, { 0x8C, 0x32, 1 }, { 0x58, 0x46, 1 }, { 0x40, 0x0, 1 },
    { 0x87, 0x64, 1 }, { 0xA8, 0x0, 1 }, { 0x1C, 0x0, 1 }, { 0x64, 0x0, 1 }, { 0x87, 0x64, 1 }, { 0x8E, 0x64, 1 },
    { 0x96, 0x50, 1 }, { 0x58, 0x0, 1 }, { 0x58, 0x0, 1 }, { 0x58, 0x0, 1 }, { 0x58, 0x0, 1 }, { 0x58, 0x0, 1 },
    { 0x58, 0x0, 1 }, { 0x58, 0x0, 1 }, { 0x58, 0x0, 1 }, { 0x58, 0x0, 1 }, { 0x58, 0x0, 1 }, { 0x58, 0x0, 1 },
    { 0x58, 0x0, 1 }, { 0x58, 0x0, 1 }, { 0x58, 0x0, 1 }, { 0x58, 0x0, 1 }, { 0x58, 0x0, 1 }, { 0x58, 0x0, 1 },
    { 0x58, 0x0, 1 }, { 0x58, 0x0, 1 }, { 0x58, 0x0, 1 }, { 0x58, 0x0, 1 }, { 0x58, 0x0, 1 }, { 0x58, 0x0, 1 },
    { 0x58, 0x0, 1 }, { 0x58, 0x0, 1 }, { 0x58, 0x0, 1 }, { 0x58, 0x0, 1 }, { 0x58, 0x0, 1 }, { 0x58, 0x0, 1 },
    { 0x58, 0x0, 1 }, { 0x58, 0x0, 1 }, { 0x58, 0x0, 1 }, { 0x58, 0x0, 1 }, { 0x58, 0x0, 1 }, { 0x58, 0x0, 1 },
    { 0x58, 0x0, 1 }, { 0x79, 0x32, 1 }, { 0x0, 0x32, 1 }, { 0x0, 0x0, 1 }, { 0x64, 0x0, 1 }, { 0x40, 0x0, 1 },
    { 0x40, 0x0, 1 }, { 0x40, 0x0, 1 }, { 0x40, 0x0, 1 }, { 0x40, 0x0, 1 }, { 0x40, 0x0, 1 }, { 0x40, 0x0, 1 },
    { 0x40, 0x0, 1 }, { 0x81, 0x64, 1 }, { 0x8D, 0x1E, 1 }, { 0x58, 0x0, 1 }, { 0x8B, 0x32, 1 }, { 0x9D, 0x46, 1 },
    { 0x89, 0x14, 1 }, { 0x83, 0x0, 1 }, { 0x9C, 0x1E, 1 }, { 0x7B, 0x0, 5 }, { 0x0, 0x0, 1 }, { 0x82, 0x0, 1 },
    { 0x85, 0x0, 1 }, { 0x84, 0x0, 1 }, { 0x7B, 0x0, 1 }, { 0x58, 0x0, 1 }, { 0x99, 0x0, 1 }, { 0x4E, 0x0, 1 },
    { 0x58, 0x0, 1 }, { 0x58, 0x0, 1 }, { 0x58, 0x0, 1 }, { 0x7E, 0x0, 1 }, { 0x58, 0x0, 1 }, { 0x58, 0x0, 1 },
    { 0xA3, 0x0, 1 }, { 0xA5, 0x0, 1 }, { 0xA4, 0x0, 1 }, { 0x6F, 0x28, 1 }, { 0xA8, 0x0, 1 }, { 0x58, 0x0, 1 },
    { 0xA8, 0x0, 1 }, { 0x9B, 0x46, 1 }, { 0x9A, 0x32, 1 }, { 0xA6, 0x0, 1 }, { 0x64, 0x0, 1 }, { 0x64, 0x0, 1 },
    { 0x0, 0x0, 1 }, { 0x64, 0x0, 1 }, { 0x76, 0x1E, 5 }, { 0x58, 0x0, 1 }, { 0x58, 0x0, 1 }, { 0x64, 0x0, 1 },
    { 0x64, 0x0, 1 }, { 0x64, 0x0, 1 }, { 0x64, 0x0, 1 }, { 0x64, 0x0, 1 }, { 0x0, 0x0, 1 }, { 0x58, 0x0, 1 },
    { 0x58, 0x0, 1 }, { 0x58, 0x0, 1 }, { 0x58, 0x0, 1 }, { 0x0, 0x0, 1 }, { 0x58, 0x1E, 1 }, { 0x64, 0x0, 1 },
    { 0x58, 0x0, 1 }, { 0x58, 0x0, 1 }, { 0x58, 0x0, 1 }, { 0x58, 0x0, 1 }, { 0x58, 0x0, 1 }, { 0x58, 0x0, 1 },
    { 0x58, 0x0, 1 }, { 0x58, 0x0, 1 }, { 0x58, 0x0, 1 }, { 0x58, 0x0, 1 }, { 0x58, 0x0, 1 }, { 0x58, 0x0, 1 },
    { 0x58, 0x0, 1 }, { 0x58, 0x0, 1 },
};
AmbientEmitter D_80745F74[7] = {
    { 1538, 281, 307, 1024, 100, 0x7F, 0x1E, 0x1, 0x26 },
    { 1506, 281, 1281, 2035, 100, 0x7F, 0x1E, 0xA0, 0x26 },
    { 2506, 285, 1691, 503, 100, 0x7F, 0x1E, 0xA0, 0x26 },
    { 2629, 540, 2933, 1288, 100, 0x7F, 0x1E, 0x1, 0x26 },
    { 793, 288, 2294, 3837, 130, 0x7F, 0x1E, 0xA0, 0x26 },
    { 1611, 281, 2179, 4077, 100, 0x7F, 0x1E, 0xA0, 0x26 },
    { 1710, 225, 3386, 2048, 130, 0x7F, 0x1E, 0xA1, 0x26 },
};
AmbientEmitter D_80745FD8[4] = {
    { 1945, 121, 874, 3100, 100, 0x7F, 0x25, 0x0, 0x0 },
    { 2685, 121, 1523, 0, 100, 0x7F, 0x25, 0x0, 0x0 },
    { 3541, 121, 2957, 2048, 100, 0x7F, 0x25, 0x0, 0x0 },
    { 3204, 113, 4437, 0, 100, 0x7F, 0x25, 0x0, 0x0 },
};
AmbientEmitter D_80746010[3] = {
    { 2382, 1621, 2573, 138, 100, 0x7F, 0x3E, 0x0, 0x26 },
    { 2054, 1621, 3533, 1512, 100, 0x7F, 0x3E, 0x0, 0x26 },
    { 2037, 1437, 1477, 2421, 100, 0x0, 0x3E, 0x0, 0x0 },
};
AmbientEmitter D_8074603C[4] = {
    { 1578, 41, 2268, 0, 100, 0xFF, 0x0, 0x0, 0x0 },
    { 1018, 41, 1583, 3072, 100, 0xFF, 0x0, 0x0, 0x0 },
    { 2183, 41, 1583, 1024, 100, 0xFF, 0x0, 0x0, 0x0 },
    { 1578, 41, 899, 2048, 100, 0xFF, 0x0, 0x0, 0x0 },
};
AmbientEmitter D_80746074[4] = {
    { 3363, 1264, 1062, 1137, 120, 0x0, 0x33, 0x0, 0x0 },
    { 4357, 1336, 936, 3140, 120, 0x0, 0x33, 0x0, 0x0 },
    { 142, 7, 1351, 1024, 100, 0x0, 0x34, 0x0, 0x0 },
    { 1098, 7, 1308, 3072, 100, 0x0, 0x34, 0x0, 0x0 },
};
AmbientEmitter D_807460AC[4] = {
    { 1348, 4139, 3419, 3072, 100, 0xFF, 0x0, 0x0, 0x0 },
    { 809, 3763, 2492, 0, 100, 0xFF, 0x0, 0x0, 0x0 },
    { 1338, 2073, 2718, 4000, 100, 0xFF, 0x0, 0x0, 0x0 },
    { 2157, 1548, 4138, 2248, 100, 0xFF, 0x0, 0x0, 0x0 },
};
AmbientEmitter D_807460E4[10] = {
    { 1757, 5, 3369, 22, 100, 0xFF, 0x0, 0x0, 0x0 },
    { 481, 5, 1903, 3562, 100, 0xFF, 0x0, 0x0, 0x0 },
    { 1027, 5, 1362, 1600, 100, 0xFF, 0x0, 0x0, 0x0 },
    { 473, 6, 1411, 2581, 100, 0xFF, 0x0, 0x0, 0x0 },
    { 1002, 5, 1937, 419, 100, 0xFF, 0x0, 0x0, 0x0 },
    { 2821, 5, 1865, 3646, 100, 0xFF, 0x0, 0x0, 0x0 },
    { 2733, 5, 1138, 2390, 100, 0xFF, 0x0, 0x0, 0x0 },
    { 2588, 7, 1534, 3071, 100, 0xFF, 0x0, 0x0, 0x0 },
    { 3294, 5, 1539, 844, 100, 0xFF, 0x0, 0x0, 0x0 },
    { 2695, 5, 3194, 1023, 100, 0xFF, 0x0, 0x0, 0x0 },
};
AmbientEmitter D_80746170[8] = {
    { 1754, 179, 1982, 2844, 100, 0xC8, 0x0, 0x0, 0x0 },
    { 1622, 179, 1556, 625, 100, 0xC8, 0x0, 0x0, 0x0 },
    { 412, 179, 1650, 3663, 100, 0xC8, 0x0, 0x0, 0x0 },
    { 1284, 179, 2700, 1991, 100, 0xC8, 0x0, 0x0, 0x0 },
    { 3267, 166, 2503, 887, 100, 0xC8, 0x0, 0x0, 0x0 },
    { 3567, 166, 3015, 2696, 100, 0xC8, 0x0, 0x0, 0x0 },
    { 2711, 201, 1619, 1934, 100, 0xC8, 0x0, 0x0, 0x0 },
    { 3082, 204, 1230, 4073, 100, 0xC8, 0x0, 0x0, 0x0 },
};
AmbientEmitter D_807461E0[7] = {
    { 356, 1651, 3909, 4097, 100, 0x7F, 0x0, 0x0, 0x0 },
    { 1905, 1453, 1071, 0, 100, 0x7F, 0x0, 0x0, 0x0 },
    { 2368, 1396, 652, 1980, 100, 0x7F, 0x0, 0x0, 0x0 },
    { 2474, 1245, 2369, 1138, 100, 0x7F, 0x0, 0x0, 0x0 },
    { 1644, 1255, 2801, 125, 100, 0x7F, 0x0, 0x0, 0x0 },
    { 4308, 1074, 1526, 4005, 100, 0x7F, 0x0, 0x0, 0x0 },
    { 4160, 1020, 547, 1889, 100, 0x7F, 0x0, 0x0, 0x0 },
};
AmbientEmitter D_80746244[4] = {
    { 2076, 477, 3750, -1, 980, 0x0, 0x6E, 0x0, 0x0 },
    { 2843, 477, 1385, -1, 1420, 0x0, 0x6D, 0x0, 0x0 },
    { 947, 477, 2401, -1, 600, 0x0, 0x6F, 0x0, 0x0 },
    { 3610, 477, 3302, -1, 630, 0x0, 0x70, 0x0, 0x0 },
};
AmbientEmitter D_8074627C[3] = {
    { 1358, 18, 772, 2275, 100, 0x7F, 0x0, 0x0, 0x0 },
    { 2027, 212, 1182, 1024, 100, 0x7F, 0x0, 0x0, 0x0 },
    { 1323, 38, 1701, 0, 100, 0x7F, 0x0, 0x0, 0x0 },
};
u8 sSfxVoiceDefaults[69][2] = {
    { 0x5A, 0x0 }, { 0x5A, 0x0 }, { 0x5A, 0x0 }, { 0x5A, 0x0 }, { 0x5A, 0x4 }, { 0x5A, 0x0 }, { 0x5A, 0x0 }, { 0x5A, 0x0 },
    { 0x0, 0x0 }, { 0x5A, 0x0 }, { 0x50, 0x0 }, { 0x64, 0x0 }, { 0x3C, 0x0 }, { 0x5A, 0x0 }, { 0x32, 0x0 }, { 0x50, 0x0 },
    { 0x50, 0x0 }, { 0x64, 0x0 }, { 0x1E, 0x0 }, { 0x46, 0x0 }, { 0x5A, 0x0 }, { 0x55, 0x0 }, { 0x5A, 0x0 }, { 0x5A, 0x0 },
    { 0x5A, 0x0 }, { 0x5A, 0x0 }, { 0x5A, 0x0 }, { 0x5A, 0x0 }, { 0x5A, 0x0 }, { 0x50, 0x0 }, { 0x3C, 0x0 }, { 0x50, 0x0 },
    { 0x5A, 0x0 }, { 0x3C, 0x0 }, { 0x0, 0x0 }, { 0x50, 0x0 }, { 0x0, 0x0 }, { 0x5A, 0x0 }, { 0x5A, 0x0 }, { 0x5A, 0x0 },
    { 0x5A, 0x0 }, { 0x82, 0x4 }, { 0x1E, 0x0 }, { 0x28, 0x0 }, { 0x5A, 0x0 }, { 0x46, 0x0 }, { 0x5A, 0x0 }, { 0x5A, 0x0 },
    { 0x50, 0x0 }, { 0x50, 0x0 }, { 0x0, 0x0 }, { 0x5A, 0x0 }, { 0x5A, 0x0 }, { 0x64, 0x0 }, { 0x0, 0x0 }, { 0x0, 0x0 },
    { 0x5A, 0x0 }, { 0x5A, 0x0 }, { 0x0, 0x0 }, { 0x28, 0x0 }, { 0x28, 0x0 }, { 0x28, 0x0 }, { 0x28, 0x0 }, { 0x28, 0x0 },
    { 0x28, 0x0 }, { 0x28, 0x0 }, { 0x46, 0x0 }, { 0x3C, 0x0 }, { 0x28, 0x0 },
};

extern SchedStruct gScheduler;
extern ALBank *gSfxBank;
extern ALBank *gSfxBankHigh;
extern u8 D_80770DD9;
extern PlayerState *gActivePlayerState;


void sfxUpdateLevelAmbient(void) {
    s8 nearest;
    s8 pad;
    u8 fxFlags;
    u8 extraSfx;
    u8 emitterCount; // FAKE: u8 width chosen for codegen: the count is a per-map constant (li s1,N at 0x1088..0x1194), never a byte load or store; its int promotion is the ucvt copy uopt colours s3 (move s3,s1 at 0x1254) as the loop bound; u16 matches the same way, s32/s16/u32 counts are 21-22 (replaces the n bound copy of 417de3)
    s16 group;
    s16 k;
    f32 volume;
    f32 pan;
    f32 angle;
    f32 pitch;
    u32 count;
    s16 sfxId;
    s16 seq;
    AmbientEmitter *emitters;
    LevelSoundEmitter *soundEmitters;

    nearest = -1;
    fxFlags = 0;

    switch (gCurrentMap) {
    case 7:
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

    if (emitterCount && sSfxAreaAmbientActive != 0 && sSfxMode == 0) {
        gAmbientNearestDist = 1000000.0f;
        volume = 0.0f;
        for (k = 0; k < emitterCount; k++) {
            f32 dx = gPlayerSlots->camX - emitters[k].x;
            f32 dz = gPlayerSlots->camZ - emitters[k].z;
            if (emitters[k].facing == -1) {
                gSfxDistance = sqrtf(dx * dx + dz * dz);
                if (gSfxDistance < emitters[k].radius - 20) {
                    sfxAllocateChannel(emitters[k].sfxId, 1.0f);
                } else if (gSfxDistance > emitters[k].radius) {
                    sfxStopChannel(emitters[k].sfxId, 0);
                }
            } else {
                f32 dy = gPlayerSlots->camY - emitters[k].y;
                gSfxDistance = sqrtf(dx * dx + dy * dy + dz * dz);
                if (k == 0 || gSfxDistance < gAmbientNearestDist) {
                    nearest = k;
                    gAmbientNearestDist = gSfxDistance;
                    angle = (mathAtan2(dx, dz) * 4096.0) / 6.2831854820251465 - emitters[k].facing;
                }
            }
            D_80770DE8 = 32767.0f - (gSfxDistance - 50.0f) * 120.0f;
            if (D_80770DE8 > 32767.0f) {
                D_80770DE8 = 32767.0f;
            }
            if (D_80770DE8 < 0.0f) {
                D_80770DE8 = 0.0f;
            }
            volume += D_80770DE8;
        }
        gSfxDistance = gAmbientNearestDist;
        if (nearest >= 0 && gSfxDistance < emitters[nearest].radius) {
            if (emitters[nearest].facing >= 0x1001) {
                gAmbientIndoors = emitters[nearest].facing & 1;
            } else {
                if (angle > 2048.0f) {
                    angle -= 4096.0f;
                }
                if (angle < -2048.0f) {
                    angle += 4096.0f;
                }
                if (angle < 1024.0f && angle > -1024.0f) {
                    if (gAmbientWasOutside != 0) {
                        gAmbientIndoors = 1;
                    }
                } else {
                    gAmbientWasOutside = 1;
                    gAmbientIndoors = 0;
                    sfxAllocateChannel(emitters[nearest].enterSfx, 1.0f);
                }
            }
            if (gAmbientIndoors != 0) {
                gAmbientIndoorReverb = emitters[nearest].reverb;
            } else {
                gAmbientIndoorReverb = 0;
            }
            D_80770DD9 = emitters[nearest].sfxId;  // FAKE: the D_80770DD9 linker alias (byte 1 of D_80770DD8) keeps this store on its own lui at/sb t3 at 0x15d0/0x15d8; D_80770DD8[1] joins the &D_80770DD8 web hoisted into s1 (text 7)
        } else {
            gAmbientWasOutside = 0;
        }
        if (gAudioUnderwater != 0) {
            volume = 0.0f;
        } else if (gAmbientIndoors != 0) {
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
            gAmbientIndoorReverb = emitters[nearest].reverb;
            if (gAmbientIndoors == 0) {
                sfxAllocateChannel(emitters[nearest].enterSfx, 1.0f);
            }
        }
        if (gAmbientIndoors != 0 && D_80770DD8[1] != 0) {
            sfxAllocateChannel(D_80770DD8[1], 1.0f);
        } else if (gAudioUnderwater != 0) {
            seqSetTargetVolume(0, 1.0f);
        } else {
            sfxStopChannel(D_80770DD8[1], 0);
        }
        D_80770DCA = gAmbientIndoors;
        if (volume != 0.0f) {
            if ((extraSfx = emitters[nearest].extraSfx)) {
                sfxAllocateChannel(extraSfx, 1.0f);
            }
        }
        if (gSeqCurrentId[2] == 0x26) {
            seqSetVolumeInstant(2, volume / 32767.0);
        }
        volume = ((volume - 28384.0f) * 100.0f) / 4383.0f;
        if (volume < 0.0f) {
            volume = 0.0f;
        }
        volume = gMapAudioTable[gCurrentMap].volume + (((255.0 - gMapAudioTable[gCurrentMap].volume) * (gAmbientIndoorReverb / 127.0) * volume) / 255.0);
        gAmbientAudioLevels[2] = volume;
    } else {
        gAmbientAudioLevels[2] = gMapAudioTable[gCurrentMap].volume;
    }

    if (gAudioUnderwater != 0) {
        gAmbientAudioLevels[2] = 0xFF;
    }

    if (gAmbientAudioLevels[1] != gAmbientAudioLevels[2]) {
        pan = (gAmbientAudioLevels[2] * 0.3) / 255.0;
        volume = ((gAmbientAudioLevels[2] * 0.35) / 255.0) + 1.0;
        if (gCurrentMap == 0xE) {
            if (gAmbientAudioLevels[2]) {
                seqSetVolumeInstant(0, 1.0f);
            } else {
                seqSetVolumeInstant(0, 0.6f);
            }
            alCSPSetChlPanVolume(&gSeqPlayers[0]->al, pan, volume);
        }
        for (seq = 0; seq < 4; seq++) {
            if (sSfxFlagTable[gSeqCurrentId[seq]] & 1) {
                alCSPSetChlPanVolume(&gSeqPlayers[seq]->al, pan, volume);
            } else {
                alCSPSetChlPanVolume(&gSeqPlayers[seq]->al, 0.0f, 1.0f);
            }
        }
        gAmbientAudioLevels[1] = gAmbientAudioLevels[2];
    }

    count = mapGetSoundEmitters(&soundEmitters);
    for (group = 0; group < 15; group++) {
        D_80770DE8 = 0.0f;
        gSfxLeftLevel = 0.0f;
        gSfxFrontLevel = 0.0f;
        gSfxRearLevel = 0.0f;
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
                            (soundEmitters[k].volume * sAmbientGroupParams[group].volume) / 255.0,
                            sAmbientGroupParams[group].range, sAmbientGroupParams[group].directionality);
                    }
                }
                volume = D_80770DE8 + gSfxLeftLevel;
                if (volume > 32767.0f) {
                    volume = 32767.0f;
                }
                if (volume < 500.0f) {
                    volume = 0.0f;
                }
            }
        }
        if (sAmbientGroupParams[group].sfxId == 0x1E) {
            volume *= 0.6;
            if ((gScheduler.tickCount / 12U) != gAmbientGroupRetriggerTick[group]) {
                gAmbientGroupRetriggerTick[group] = (gScheduler.tickCount / 12U);
                if (volume > 10.0f) {
                    n_alSndpPlay(gSfxBank, sAmbientGroupParams[group].sfxId, volume, 0x3F, 0.4f, 0, &gLoopSfxHandles[group]);
                    gAmbientGroupSentVolume[group] = volume + 1.0f;
                    gAmbientGroupSentPan[group] = 300.0f;
                }
            }
        }
        if (volume != gAmbientGroupSentVolume[group] || gLoopSfxHandles[group] == 0) {
            if (volume > 10.0f) {
                if (gLoopSfxHandles[group] == 0) {
                    sfxId = sAmbientGroupParams[group].sfxId;
                    if (sfxId < 0x800) {
                        n_alSndpPlay(gSfxBank, sfxId, volume, 0x3F, sAmbientGroupParams[group].pitch, 0, &gLoopSfxHandles[group]);
                    } else {
                        n_alSndpPlay(gSfxBankHigh, sfxId - 0x7FF, volume, 0x3F, sAmbientGroupParams[group].pitch, 0, &gLoopSfxHandles[group]);
                    }
                    gAmbientGroupSentPitch[group] = 0.0f;
                    gAmbientGroupSentPan[group] = 255.0f;
                }
                if (gLoopSfxHandles[group] != 0) {
                    n_alSndpPostEvent(gLoopSfxHandles[group], 8, volume);
                }
                if (gSfxFrontLevel < gSfxRearLevel) {
                    fxFlags = 0x80;
                }
                if (gLoopSfxHandles[group] != 0) {
                    n_alSndpPostEvent(gLoopSfxHandles[group], 0x100, fxFlags);
                }
            } else if (gLoopSfxHandles[group] != 0) {
                n_alSndpStop(gLoopSfxHandles[group]);
            }
            gAmbientGroupSentVolume[group] = volume;
        }
        if (gLoopSfxHandles[group] != 0) {
            if (D_80770DE8 > 32767.0f) {
                D_80770DE8 = 32767.0f;
            }
            if (gSfxLeftLevel > 32767.0f) {
                gSfxLeftLevel = 32767.0f;
            }
            if (gSfxLeftLevel < D_80770DE8) {
                if (D_80770DE8 > 0.0f) {
                    angle = 127.0 - ((gSfxLeftLevel * 63.5) / D_80770DE8);  // FAKE: angle reused for the per-group pan value (to the n_alSndpPostEvent(.., 4, angle) below); the target keeps it in angle f20 (cvt.s.d $f20 at 0x20cc/0x2100): a separate local here is 561-598 (block scope or any declaration slot), sharing pan with the seq-player block 366 (pre-existing part of 7d249b)
                } else {
                    angle = 0.0f;
                }
            } else if (gSfxLeftLevel > 0.0f) {
                angle = (D_80770DE8 * 63.5) / gSfxLeftLevel;
            } else {
                angle = 0.0f;
            }
            if (gAudioUnderwater != 0) {
                pitch = sAmbientGroupParams[group].pitch * 0.5;
            } else if (gAmbientIndoors != 0 && sAmbientGroupParams[group].sfxId == 0x106) {
                pitch = 1.0 / ((gAmbientNearestDist / 800.0) + 1.0);
            } else {
                pitch = sAmbientGroupParams[group].pitch;
            }
            if (angle != gAmbientGroupSentPan[group]) {
                if (gAmbientGroupSentPan[group] != 255.0f) {
                    if (gAmbientGroupSentPan[group] < angle) {
                        if (gAmbientGroupSentPan[group] + 8.0f < angle) {
                            angle = gAmbientGroupSentPan[group] + 8.0f;
                        }
                    } else {
                        if (angle < gAmbientGroupSentPan[group] - 8.0f) {
                            angle = gAmbientGroupSentPan[group] - 8.0f;
                        }
                    }
                }
                n_alSndpPostEvent(gLoopSfxHandles[group], 4, angle);
                gAmbientGroupSentPan[group] = angle;
            }
            if (pitch != gAmbientGroupSentPitch[group]) {
                n_alSndpPostEvent(gLoopSfxHandles[group], 0x10, *(s32 *)&pitch);  // ORIG: the target passes the raw bits of pitch from its home slot (swc1 $f2,0xcc(sp) at 0x218c, lw a2,0xcc(sp) at 0x2244); an f32 parameter would pass them by mfc1 with no home store (Q0026)
                gAmbientGroupSentPitch[group] = pitch;
            }
        }
    }

    if ((gGlobalPauseFlags & 2) || !(gGlobalPauseFlags & 0x10)) {
        if (gAmbientIndoorReverb) {}  // FAKE: dead read stops &gAmbientIndoorReverb being coloured into $s2 (lui s2/addiu s2 at 0x15ac); a function-local static retires it (Q0981, text 0) but IDO orders .bss by symbol number mod 256 (Q1470): the static is numbered 96 after gSfxVoiceSentPitch and lands at .bss+0x9d8; 0x80770DC8 needs 160 more file-scope definitions
        gAmbientAudioLevels[0] = 0;
    }
    if (gAmbientAudioLevels[0] != 0) {
        if (sRainSfxHandle == 0) {
            n_alSndpPlay(gSfxBank, 0x125, 0, 0x3F, 1.0f, 0, &sRainSfxHandle);
        }
        if (sRainSfxHandle != 0) {
            n_alSndpPostEvent(sRainSfxHandle, 8, (gAmbientAudioLevels[0] * 10767.0) / 255.0);
            pitch = 1.0 - ((gAmbientAudioLevels[2] * 0.5) / 255);
            if (gAmbientIndoors & (gAmbientNearestDist < 1000.0f)) {
                angle = mathAngleBetweenPointsRad(gPlayerSlots->camX, gPlayerSlots->camZ, emitters[nearest].x, emitters[nearest].z) - gPlayerSlots->camYaw;
                if (angle < 0.0f) {
                    angle += 6.2831855f;
                }
                if (angle > 1.5707964f && angle < 4.71238911151886) {
                    gAmbientNearestFx = 128.0f;
                } else {
                    gAmbientNearestFx = 0.0f;
                }
                gAmbientNearestPan = (1.0f - sinApprox(angle)) * 63.5;
            } else {
                gAmbientNearestPan = 64.0f;
            }
            n_alSndpPostEvent(sRainSfxHandle, 0x10, *(s32 *)&pitch);  // ORIG: the target passes the raw bits of pitch from its home slot (swc1 $f2,0xcc(sp) at 0x23d0, lw a2,0xcc(sp) at 0x24fc)
            n_alSndpPostEvent(sRainSfxHandle, 0x100, gAmbientNearestFx);
            n_alSndpPostEvent(sRainSfxHandle, 4, gAmbientNearestPan);
        }
    } else if (sRainSfxHandle != 0) {
        n_alSndpStop(sRainSfxHandle);
    }
}

void seqUpdateUnderwaterAudio(s32 seqIndex) {
    if (gAudioUnderwater != 0) {
        if (seqIndex == 0 && (sSfxFlagTable[gSeqCurrentId[seqIndex]] & 1)) {
            alCSPSetChlPanVolume(&gSeqPlayers[0]->al, 0.3f, 1.35f);
        }
        if (gSeqCurrentId[seqIndex] == 0x38) {
            sfxSetChannelParam(0x38, 0x3C00, 1);
        }
        if (gSeqCurrentId[seqIndex] == 0x60) {
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
        if (seqIndex == 0 && (sSfxFlagTable[gSeqCurrentId[seqIndex]] & 1)) {
            alCSPSetChlPanVolume(&gSeqPlayers[0]->al, 0.0f, 1.0f);
        }
        if (gSeqCurrentId[seqIndex] == 0x38) {
            sfxSetChannelParam(0x38, 0x3C00, 0);
        }
        if (gSeqCurrentId[seqIndex] == 0x60) {
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

void sfxSetVolumeAndPan(u8 source, f32 pitch, f32 rate) {

    if (source != -1) {
        if (rate == 0.0f) {
            gSfxVoiceCurPitch[gSfxSourceVoice[source]] = pitch;
            gSfxVoiceBasePitch[gSfxSourceVoice[source]] = pitch;
        } else {
            gSfxVoicePitch[gSfxSourceVoice[source]] = pitch;
        }
        gSfxVoiceModCounter[gSfxSourceVoice[source]] = rate;
    }
}

void sfxSetChannelPriority(u8 source, u8 volume) {
    if (source != -1) {
        gSfxVoiceVolume[gSfxSourceVoice[source]] = volume;
    }
}


void sfxPlayActorSound(Actor *actor, s16 sfxId, u8 range, u8 exclusive, u8 slot, u8 volume, f32 pitch, s8 node) {
    if (actor->soundSlots[slot] != -1) {
        if (sfxId == gSfxVoiceSoundId[gSfxSourceVoice[actor->soundSlots[slot]]]) {
            return;
        }
        sfxStopSlotSound(actor, slot);
    }
    actor->soundSlots[slot] = sfxSlotAllocateActor(actor, sfxId, range, exclusive, volume, pitch, node);
}

u8 sfxSlotAllocateActor(Actor *actor, s16 sfxId, u8 range, u8 exclusive, u8 volume, f32 pitch, s8 node) {
    u8 source;
    u8 voice;
    s16 count;

    for (source = 0; source < 22; source++) {
        if (gSfxSourceVoice[source] == -1) {
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
            if (gSfxVoiceExclusive[voice] == 0 && gSfxVoiceSoundId[voice] == sfxId) {
                break;
            }
        }
    }

    if (voice == 22) {
        for (voice = 0; voice < 22; voice++) {
            if (gSfxVoiceSoundId[voice] == 0 && sSoundSlotHandles[voice] == 0) {
                break;
            }
        }
        if (voice == 22) {
            return 0xFF;
        }
        gSfxVoiceSoundId[voice] = sfxId;
        gSfxVoiceExclusive[voice] = exclusive;
        gSfxVoiceCurPitch[voice] = pitch;
        gSfxVoiceBasePitch[voice] = pitch;
        gSfxVoicePitch[voice] = 1.0f;
        gSfxVoiceModCounter[voice] = 0.0f;
        gSfxVoicePlayedOnce[voice] = 0;
    }

    if (range != 0) {
        gSfxSourceRange[source] = range;
    } else {
        gSfxSourceRange[source] = sSfxVoiceDefaults[gSfxVoiceSoundId[voice] - 0xFD][0];
    }
    gSfxVoiceVolume[voice] = volume;
    gSfxVoiceSentVolume[voice] = -1;
    gSfxVoiceSentPitch[voice] = pitch;
    gSfxVoiceSentPan[voice] = -1;
    gSfxVoiceNode[voice] = node;
    gSfxVoiceStopTimer[voice] = 0;
    count = gSfxVoiceSourceCount[voice];
    gSfxSourceVoice[source] = voice;
    gSfxSourceListIndex[source] = count;
    gSfxVoiceSources[voice][count] = source;
    gSfxVoiceSourceCount[voice] = count + 1;
    gSfxSourceActor[source] = actor;
    return source;
}

u8 sfxSlotAllocateSource(s16 modelSlot, s16 sfxId, u8 range, u8 exclusive, u8 volume, f32 pitch, s8 node) {
    u8 source;
    u8 voice;
    s16 count;

    for (source = 0; source < 22; source++) {
        if (gSfxSourceVoice[source] == -1) {
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
            if (gSfxVoiceExclusive[voice] == 0 && gSfxVoiceSoundId[voice] == sfxId) {
                break;
            }
        }
    }

    if (voice == 22) {
        for (voice = 0; voice < 22; voice++) {
            if (gSfxVoiceSoundId[voice] == 0 && sSoundSlotHandles[voice] == 0) {
                break;
            }
        }
        if (voice == 22) {
            return 0xFF;
        }
        gSfxVoiceSoundId[voice] = sfxId;
        gSfxVoiceExclusive[voice] = exclusive;
        gSfxVoiceCurPitch[voice] = pitch;
        gSfxVoiceBasePitch[voice] = pitch;
        gSfxVoicePitch[voice] = 1.0f;
        gSfxVoiceModCounter[voice] = 0.0f;
        gSfxVoicePlayedOnce[voice] = 0;
    }

    if (range != 0) {
        gSfxSourceRange[source] = range;
    } else {
        gSfxSourceRange[source] = sSfxVoiceDefaults[gSfxVoiceSoundId[voice] - 0xFD][0];
    }
    gSfxVoiceVolume[voice] = volume;
    gSfxVoiceSentVolume[voice] = -1;
    gSfxVoiceSentPitch[voice] = pitch;
    gSfxVoiceSentPan[voice] = -1;
    gSfxVoiceNode[voice] = node;
    gSfxVoiceStopTimer[voice] = 0;
    count = gSfxVoiceSourceCount[voice];
    gSfxSourceVoice[source] = voice;
    gSfxSourceListIndex[source] = count;
    gSfxVoiceSources[voice][count] = source;
    gSfxVoiceSourceCount[voice] = count + 1;
    gSfxSourceModelSlot[source] = modelSlot;
    return source;
}

void sfxStopSlotSound(Actor *actor, u8 slot) {
    if (actor->soundSlots[slot] >= 0) {
        sfxSlotFreeSource(actor->soundSlots[slot]);
        actor->soundSlots[slot] = -1;
        if (slot == 0) {
            actor->soundAnimId = 0;
        }
    }
}



void sfxSlotFreeSource(s16 source) {
    gSfxVoiceSourceCount[gSfxSourceVoice[source]]--; if (gSfxVoiceSourceCount[gSfxSourceVoice[source]] != 0) { // LAYOUT:
        gSfxSourceListIndex[gSfxVoiceSources[gSfxSourceVoice[source]][gSfxVoiceSourceCount[gSfxSourceVoice[source]]]] = gSfxSourceListIndex[gSfxVoiceSources[gSfxSourceVoice[source]][gSfxSourceListIndex[source]]];
        gSfxVoiceSources[gSfxSourceVoice[source]][gSfxSourceListIndex[source]] = gSfxVoiceSources[gSfxSourceVoice[source]][gSfxVoiceSourceCount[gSfxSourceVoice[source]]];
    } else {
        gSfxVoiceSoundId[gSfxSourceVoice[source]] = 0;
        gSfxVoiceExclusive[gSfxSourceVoice[source]] = 0;
    }

    if (gSfxVoiceSourceCount[gSfxSourceVoice[source]] < 0 || gSfxVoiceSourceCount[gSfxSourceVoice[source]] >= 23) {
        faultSetMessage(9, gSfxVoiceSourceCount[gSfxSourceVoice[source]], 0, 0);
    }

    gSfxVoiceSources[gSfxSourceVoice[source]][gSfxVoiceSourceCount[gSfxSourceVoice[source]]] = -1;
    gSfxSourceModelSlot[source] = -1;
    gSfxSourceActor[source] = NULL;
    gSfxSourceVoice[source] = -1;
    gSfxSourceListIndex[source] = -1;
}


extern u8 gWeatherThunderMuted;

void audioResetAll(void) {
    u8 i;
    u8 j;

    i = 0;
    if (transitionGetState() == 0) {
        n_alSndpStopAll();
    }
    gWeatherThunderMuted = 0;
    if (transitionGetState() != 0) {
        i = 1;
    }
    for (; i < 4; i++) {
        alCSPSetChlPanVolume(&gSeqPlayers[i]->al, 0.0f, 1.0f);
        if (alCSPGetState(&gSeqPlayers[i]->al) == 1 && gSeqCurrentId[i] != 0x12) {
            alSeqpStop((ALSeqPlayer *)gSeqPlayers[i]);
            gSeqCurrentId[i] = 0;
        }
    }
    gAmbientAudioLevels[0] = 0;
    gAmbientAudioLevels[1] = 0;
    gAmbientAudioLevels[2] = 0;
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
    gAmbientIndoors = 0;
    gAudioUnderwater = 0;
    D_80770DD8[1] = 0xFF;
    for (i = 0; i < 22; i++) {
        gSfxSourceActor[i] = NULL;
        gSfxSourceModelSlot[i] = -1;
        gSfxSourceVoice[i] = -1;
        gSfxSourceListIndex[i] = -1;
        gSfxVoiceFxLevel[i] = 0;
        gSfxVoiceSoundId[i] = 0;
        gSfxVoiceExclusive[i] = 0;
        gSfxVoiceSourceCount[i] = 0;
        gSfxVoiceStopTimer[i] = 0;
        for (j = 0; j < 22;) {
            gSfxVoiceSources[i][j++] = -1;
        }
    }
}

extern ModelSlot *gModelSlots;

extern u8 gPlayerCount;


#define RAND_UNIT() ((u32)randomLcgNext() / 4294967295.0)

void sfxUpdateSourceGroups(void) {
    static f32 sFramePitch;
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
    Actor *camActor;
    s32 slot;
    s16 animFrame;
    f32 animSpeed;
    u8 animFlags;
    s32 pad;

    actor = NULL;
    if (gActivePlayerState != NULL) {}  // FAKE: dead test keeps &gActivePlayerState out of a register so the store/reload after the loop stays split
    for (i = 0; i < 22; i++) {
        if (gSfxVoiceSoundId[i] == 0x88) {
            D_80770DE8 = 0.0f;
            gSfxLeftLevel = 0.0f;
            gSfxFrontLevel = 0.0f;
            gSfxRearLevel = 0.0f;
            fxFlags = 0;
            for (j = gSfxVoiceSourceCount[i] - 1; j >= 0; j--) {
                slot = hashTableLookup(gSfxSourceModelSlot[gSfxVoiceSources[i][j]]);
                sfxUpdateDistanceVolumeAndPan(gModelSlots[slot].x, gModelSlots[slot].y, gModelSlots[slot].z, 0xFF, 0x50, 0.5f);
                dist[j] = gSfxDistance;
                sfxSlotFreeSource(gSfxVoiceSources[i][j]);
                gModelSlots[slot].csState->sfxSources[1] = -1;
            }
            if (D_80770DE8 > 32767.0f) {
                D_80770DE8 = 32767.0f;
            }
            if (gSfxLeftLevel > 32767.0f) {
                gSfxLeftLevel = 32767.0f;
            }
            volume = D_80770DE8 + gSfxLeftLevel;
            if (gSfxLeftLevel < D_80770DE8) {
                if (D_80770DE8 > 0.0f) {
                    D_80770DDC = 127.0 - ((gSfxLeftLevel * 63.5) / D_80770DE8);
                } else {
                    D_80770DDC = 0.0f;
                }
            } else if (gSfxLeftLevel > 0.0f) {
                D_80770DDC = (D_80770DE8 * 63.5) / gSfxLeftLevel;
            } else {
                D_80770DDC = 0.0f;
            }
            if (volume > 32767.0f) {
                volume = 32767.0f;
            }
            if (volume < 0.0f) {
                volume = 0.0f;
            }
            if (gSfxFrontLevel < gSfxRearLevel) {
                fxFlags = 0x80;
            }
            sfxPlayOnFreeSlot(0x88, volume, D_80770DDC, 1.0f, 5, fxFlags);
        } else {
            if (sSoundSlotHandles[i] != 0) {
                if (gSfxVoiceSoundId[i] == 0) {
                    if (gSfxVoiceStopTimer[i] != 0) {
                        gSfxVoiceStopTimer[i]--;
                    } else {
                        n_alSndpStop(sSoundSlotHandles[i]);
                        gSfxVoiceFxLevel[i] = 0;
                        gSfxVoiceStopTimer[i] = 10;
                    }
                }
            } else if (gSfxVoiceSoundId[i] != 0) {
                if (gSfxVoiceSoundId[i] == 0x128 || gSfxVoiceSoundId[i] == 0x306) {
                    if (gSfxVoicePlayedOnce[i] == 0) {
                        n_alSndpPlay(gSfxBank, gSfxVoiceSoundId[i], 0, 0x3F, gSfxVoiceCurPitch[i], 0, &sSoundSlotHandles[i]);
                        gSfxVoicePlayedOnce[i] = 1;
                    } else {
                        slotIdx = gSfxVoiceSources[i][0];
                        sfxStopSlotSound(gSfxSourceActor[slotIdx], 0);
                    }
                } else if (gSfxVoiceSoundId[i] < 0x800) {
                    n_alSndpPlay(gSfxBank, gSfxVoiceSoundId[i], 0, 0x3F, gSfxVoiceCurPitch[i], 0, &sSoundSlotHandles[i]);
                } else {
                    n_alSndpPlay(gSfxBankHigh, gSfxVoiceSoundId[i] - 0x7FF, 0, 0x3F, gSfxVoiceCurPitch[i], 0, &sSoundSlotHandles[i]);
                }
            }
            if (sSoundSlotHandles[i] != 0) {
                if (gSfxVoiceSources[i][0] != -1 && (gSfxSourceActor[gSfxVoiceSources[i][0]] != NULL || gSfxSourceModelSlot[gSfxVoiceSources[i][0]] != -1)) {
                    D_80770DE8 = 0.0f;
                    gSfxLeftLevel = 0.0f;
                    if (gSfxVoiceSoundId[i] >= 0xFD && gSfxVoiceSoundId[i] < 0x142) {
                        factor = sSfxVoiceDefaults[gSfxVoiceSoundId[i] - 0xFD][1];
                    } else {
                        factor = 0.3f;
                    }
                    fxLevel = 0;
                    j = 0;
                    if (gSfxVoiceSourceCount[i] > 0) {
                        do {
                            if (gSfxSourceModelSlot[gSfxVoiceSources[i][0]] != -1) {
                                actor = NULL;
                                if (gSfxVoiceSoundId[i] == 0x12B) {
                                    slot = hashTableLookup(gSfxSourceModelSlot[gSfxVoiceSources[i][j]]);
                                    sfxUpdateDistanceVolumeAndPan(gModelSlots[slot].x, gModelSlots[slot].y + 320.0f, gModelSlots[slot].z, 0xFF, gSfxSourceRange[gSfxVoiceSources[i][j]], factor);
                                } else if (gSfxVoiceNode[i] > 0) {
                                    modelSlotGetNodePos(gSfxSourceModelSlot[gSfxVoiceSources[i][j]], 1, gSfxVoiceNode[i], &posX, &posY, &posZ);
                                    sfxUpdateDistanceVolumeAndPan(posX, posY, posZ, 0xFF, gSfxSourceRange[gSfxVoiceSources[i][j]], factor);
                                } else if (gSfxVoiceNode[i] < 0) {
                                    D_80770DE8 = 32767.0f;
                                    gSfxLeftLevel = 32767.0f;
                                    gSfxFrontLevel = 32767.0f;
                                    gSfxRearLevel = 32767.0f;
                                } else {
                                    slot = hashTableLookup(gSfxSourceModelSlot[gSfxVoiceSources[i][j]]);
                                    sfxUpdateDistanceVolumeAndPan(gModelSlots[slot].x, gModelSlots[slot].y, gModelSlots[slot].z, 0xFF, gSfxSourceRange[gSfxVoiceSources[i][j]], factor);
                                }
                            } else {
                                actor = gSfxSourceActor[gSfxVoiceSources[i][j]];
                                if (gSfxVoiceNode[i] > 0) {
                                    actorGetNodePos(actor, gSfxVoiceNode[i], &posX, &posY, &posZ);
                                    sfxUpdateDistanceVolumeAndPan(posX, posY, posZ, 0xFF, gSfxSourceRange[gSfxVoiceSources[i][j]], factor);
                                } else if (gSfxVoiceNode[i] < 0) {
                                    D_80770DE8 = 32767.0f;
                                    gSfxLeftLevel = 32767.0f;
                                    gSfxFrontLevel = 32767.0f;
                                    gSfxRearLevel = 32767.0f;
                                } else if (gSfxVoiceSoundId[i] == 0x139 && gSfxVoiceExclusive[i] != 0) {
                                    posY = actor->y;
                                    posX = actor->x;
                                    posZ = actor->z;
                                    sfxUpdateDistanceVolumeAndPan(posX, posY, posZ, 0xFF, gSfxSourceRange[gSfxVoiceSources[i][j]], factor);
                                    posX = (mathCosF(actor->yaw) * 300.0) + actor->x;
                                    posZ = actor->z - (mathSinF(actor->yaw) * 300.0);
                                    sfxUpdateDistanceVolumeAndPan(posX, posY, posZ, 0xFF, gSfxSourceRange[gSfxVoiceSources[i][j]], factor);
                                    posX = actor->x - (mathCosF(actor->yaw) * 300.0);
                                    posZ = (mathSinF(actor->yaw) * 300.0) + actor->z;
                                    sfxUpdateDistanceVolumeAndPan(posX, posY, posZ, 0xFF, gSfxSourceRange[gSfxVoiceSources[i][j]], factor);
                                } else {
                                    sfxUpdateDistanceVolumeAndPan(actor->x, actor->y, actor->z, 0xFF, gSfxSourceRange[gSfxVoiceSources[i][j]], factor);
                                }
                            }
                            dist[j++] = gSfxDistance;
                        } while (j < gSfxVoiceSourceCount[i]);
                    }
                    if (D_80770DE8 > 32767.0f) {
                        D_80770DE8 = 32767.0f;
                    }
                    if (gSfxLeftLevel > 32767.0f) {
                        gSfxLeftLevel = 32767.0f;
                    }
                    volume = D_80770DE8 + gSfxLeftLevel;
                    if (gSfxLeftLevel < D_80770DE8) {
                        if (D_80770DE8 > 0.0f) {
                            D_80770DDC = 127.0 - ((gSfxLeftLevel * 63.5) / D_80770DE8);
                        } else {
                            D_80770DDC = 0.0f;
                        }
                    } else if (gSfxLeftLevel > 0.0f) {
                        D_80770DDC = (D_80770DE8 * 63.5) / gSfxLeftLevel;
                    } else {
                        D_80770DDC = 0.0f;
                    }
                    if (volume > 32767.0f) {
                        volume = 32767.0f;
                    }
                    if (volume < 0.0f) {
                        volume = 0.0f;
                    }
                    volume *= gSfxVoiceVolume[i] / 255.0;
                    if ((gGlobalPauseFlags & 2) || !(gGlobalPauseFlags & 0x10)) {
                        volume = 0.0f;
                    } else {
                        switch (gSfxVoiceSoundId[i]) {
                        case 0x12F:
                            volume *= gSfxVoiceModCounter[i] / 9.0;
                            fxLevel = gSfxVoiceModCounter[i] * 1.3;
                            break;
                        case 0x12B:
                            modelAnimEntryGetState(slot, 1, &animFrame, &animSpeed, &animFlags);
                            factor = sinApprox((animFrame / 27.0) * 3.1415927410125732);
                            volume *= factor;
                            gSfxVoicePitch[i] = factor;
                            gSfxVoiceCurPitch[i] = (factor * 0.4) + 0.8;
                            break;
                        case 0x113:
                            if (gSfxVoicePitch[i] == 0.0f) {
                                volume = 0.0f;
                            } else {
                                gSfxVoiceCurPitch[i] = gSfxVoicePitch[i];
                            }
                            break;
                        case 0x111:
                            gSfxVoiceModCounter[i] += 1.0f;
                            if (gSfxVoiceModCounter[i] > 30.0f) {
                                gSfxVoiceCurPitch[i] = 1.0 - ((gSfxVoiceModCounter[i] - 30.0) / 30.0);
                            }
                            if (gSfxVoiceModCounter[i] == 40.0f) {
                                sfxSlotFreeSource(gSfxVoiceSources[i][0]);
                                gModelSlots[slot].csState->sfxSources[0] = -1;
                            }
                            break;
                        case 0x11F:
                            if (gSfxVoiceExclusive[i] != 0) {
                                factor = sinApprox(gSfxVoiceModCounter[i] * 0.027925);
                                gSfxVoiceCurPitch[i] = (sinApprox((gSfxVoiceModCounter[i] * 0.261799) - 1.570795) * 0.1) + (0.2 * factor) + 0.6;
                                gSfxVoiceModCounter[i] += 1.0f;
                                if (gSfxSourceRange[gSfxVoiceSources[i][0]] == 0) {
                                    D_80770DDC = 63.0f;
                                    gSfxRearLevel = 100.0f;
                                    gSfxFrontLevel = 0.0f;
                                }
                            } else {
                                factor = sinApprox(gSfxVoiceModCounter[i] * 0.027925);
                                gSfxVoiceCurPitch[i] = (sinApprox((gSfxVoiceModCounter[i] * 0.261799) - 1.570795) * 0.1) + (0.5 * factor) + 0.6;
                                gSfxVoicePitch[i] = 1.0 - ((gSfxVoiceModCounter[i] - 90.0) / 20.0);
                                gSfxVoicePitch[i] = (gSfxVoicePitch[i] > 1.0f) ? 1.0f : gSfxVoicePitch[i];
                                gSfxVoicePitch[i] = (gSfxVoicePitch[i] < 0.0f) ? 0.0f : gSfxVoicePitch[i];
                                volume *= gSfxVoicePitch[i];
                                gSfxVoicePitch[i] = gSfxVoiceModCounter[i] / 20.0f;
                                gSfxVoicePitch[i] = (gSfxVoicePitch[i] < 1.0f) ? gSfxVoicePitch[i] : 1.0f;
                                volume *= gSfxVoicePitch[i];
                                gSfxVoiceModCounter[i] += 1.0f;
                                gSfxVoiceCurPitch[i] = (gSfxVoiceCurPitch[i] > 0.2) ? gSfxVoiceCurPitch[i] : 0.2;
                                if (gSfxVoiceModCounter[i] == 110.0f) {
                                    if (gSfxSourceModelSlot[gSfxVoiceSources[i][0]] != -1) {
                                        sfxSlotFreeSource(gSfxVoiceSources[i][0]);
                                        gModelSlots[slot].csState->sfxSources[0] = -1;
                                    } else {
                                        sfxStopSlotSound(actor, 0);
                                        sfxStopChannel(0x3B, 0);
                                    }
                                }
                            }
                            break;
                        case 0x131:
                            if (actor->actorType == 0xB9) {
                                gSfxVoiceFxLevel[i] = 8;
                                gSfxVoiceCurPitch[i] = (actor->soundTimer / 80.0) + 1.0;
                                volume *= 1.0f / gSfxVoiceCurPitch[i];
                            } else {
                                gSfxVoicePitch[i] = 0.0f;
                                gSfxVoiceCurPitch[i] = 200.0f;
                                for (j = 0; j < gSfxVoiceSourceCount[i]; j++) {
                                    if (gSfxSourceActor[gSfxVoiceSources[i][j]]->soundTimer < gSfxVoiceCurPitch[i]) {
                                        gSfxVoiceCurPitch[i] = gSfxSourceActor[gSfxVoiceSources[i][j]]->soundTimer;
                                        gSfxVoicePitch[i] = j;
                                    }
                                }
                                j = gSfxVoicePitch[i];
                                gSfxVoiceCurPitch[i] = 2.0 - (((gSfxSourceActor[gSfxVoiceSources[i][j]]->soundTimer - 120) > 0 ? (gSfxSourceActor[gSfxVoiceSources[i][j]]->soundTimer - 120) : -(gSfxSourceActor[gSfxVoiceSources[i][j]]->soundTimer - 120)) / 120.0);
                                gSfxVoiceCurPitch[i] = (gSfxVoiceCurPitch[i] > 0.2) ? gSfxVoiceCurPitch[i] : 0.2;
                                gSfxVoicePitch[i] = gSfxSourceActor[gSfxVoiceSources[i][j]]->soundVolume / 20.0;
                                gSfxVoicePitch[i] = (gSfxVoicePitch[i] < 1.0f) ? gSfxVoicePitch[i] : 1.0f;
                                gSfxVoicePitch[i] = (gSfxVoicePitch[i] > 0.0f) ? gSfxVoicePitch[i] : 0.0f;
                                volume *= gSfxVoicePitch[i];
                            }
                            break;
                        case 0x10E:
                            if (actor->actorType == 0x139) {
                                if (gSfxVoiceModCounter[i]-- <= 0.0f) {
                                    gSfxVoiceModCounter[i] = (RAND_UNIT() * 2) + 2.0;
                                    gSfxVoicePitch[i] = ((0.925 + (0.15 * RAND_UNIT())) - gSfxVoiceCurPitch[i]) / gSfxVoiceModCounter[i];
                                }
                                volume *= 0.5;
                                break;
                            }
                            if (actor->actorType == 2) {
                                if (gSfxVoiceModCounter[i]-- <= 0.0f) {
                                    gSfxVoiceModCounter[i] = (RAND_UNIT() * 2) + 2.0;
                                    gSfxVoicePitch[i] = ((1.2 + (0.15 * RAND_UNIT())) - gSfxVoiceCurPitch[i]) / gSfxVoiceModCounter[i];
                                }
                                fxLevel = 0xE;
                                volume *= 0.9;
                                break;
                            }
                            /* fallthrough */
                        case 0x108:
                        case 0x10F:
                            if (gSfxVoiceModCounter[i]-- <= 0.0f) {
                                if (gSfxVoiceSoundId[i] == 0x108) {
                                    switch (actor->health) {
                                        case 3:
                                            gSfxVoiceModCounter[i] = (RAND_UNIT() * 2) + 3.0f;
                                            gSfxVoicePitch[i] = ((0.95 + (0.1 * RAND_UNIT())) - gSfxVoiceCurPitch[i]) / gSfxVoiceModCounter[i];
                                            break;
                                        case 2:
                                            gSfxVoiceModCounter[i] = (RAND_UNIT() * 2.0f) + 2.0f;
                                            gSfxVoicePitch[i] = ((0.85 + (0.5 * RAND_UNIT())) - gSfxVoiceCurPitch[i]) / gSfxVoiceModCounter[i];
                                            break;
                                        case 0:
                                        case 1:
                                            gSfxVoiceModCounter[i] = (RAND_UNIT() * 1.0f) + 2.0;
                                            gSfxVoicePitch[i] = ((0.9 + (0.5 * RAND_UNIT())) - gSfxVoiceCurPitch[i]) / gSfxVoiceModCounter[i];
                                            break;
                                    }
                                } else {
                                    gSfxVoiceModCounter[i] = (RAND_UNIT() * 2.0f) + 2.0f;
                                    gSfxVoicePitch[i] = (((gSfxVoiceBasePitch[i] - 0.075) + (0.15 * RAND_UNIT())) - gSfxVoiceCurPitch[i]) / gSfxVoiceModCounter[i];
                                }
                            }
                            gSfxVoiceCurPitch[i] += gSfxVoicePitch[i];
                            if (gSfxVoiceSourceCount[i] >= 2) {
                                nearest[0] = 10000.0f;
                                nearest[1] = 10000.0f;
                                for (j = 0; j < gSfxVoiceSourceCount[i]; j++) {
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
                            if (fxLevel != gSfxVoiceFxLevel[i]) {
                                gSfxVoiceFxLevel[i] = fxLevel;
                            }
                            break;
                        case 0x104:
                            if (gSfxVoiceModCounter[i] < 30.0f) {
                                gSfxVoiceModCounter[i] += 1.0f;
                                gSfxVoiceCurPitch[i] *= 1.02;
                            }
                            break;
                        case 0x118:
                            if (actor->actorType != 0x139) {
                                if (gSfxVoiceModCounter[i]++ >= 2.0f) {
                                    gSfxVoiceModCounter[i] = randomLcgNext();
                                    if (gSfxFrontLevel < gSfxRearLevel) {
                                        fxFlags |= 0x80;
                                    }
                                    sfxPlayOnFreeSlot((randomLcgNext() & 3) + 0x90, volume, D_80770DDC, 1.0f, 0x1E, fxFlags);
                                    gSfxVoiceModCounter[i] = 0.0f;
                                }
                            }
                            gSfxVoiceCurPitch[i] *= 0.99;
                            break;
                        case 0x219:
                            if (gSfxVoiceModCounter[i]-- <= 0.0f) {
                                gSfxVoiceModCounter[i] = (RAND_UNIT() * 6.0f) + 2.0;
                                gSfxVoicePitch[i] = ((0.84089 + (0.21857 * RAND_UNIT())) - gSfxVoiceCurPitch[i]) / gSfxVoiceModCounter[i];
                            }
                            gSfxVoiceCurPitch[i] += gSfxVoicePitch[i];
                            break;
                        case 0x132:
                            if (gSfxVoiceModCounter[i]-- <= 0.0f) {
                                gSfxVoiceModCounter[i] = (RAND_UNIT() * 6.0f) + 2.0;
                                gSfxVoicePitch[i] = ((0.8 + (0.2 * RAND_UNIT())) - gSfxVoiceCurPitch[i]) / gSfxVoiceModCounter[i];
                            }
                            gSfxVoiceCurPitch[i] += gSfxVoicePitch[i];
                            break;
                        case 0x116:
                            if (gSfxVoiceModCounter[i] > 0.0f) {
                                gSfxVoiceCurPitch[i] += (gSfxVoicePitch[i] - gSfxVoiceCurPitch[i]) / gSfxVoiceModCounter[i]--;
                            }
                            D_80770DE8 = (gSfxVoiceCurPitch[i] - 0.2) * 2.0;
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
                            if (gSfxVoiceModCounter[i] > 0.0f) {
                                gSfxVoiceCurPitch[i] += (gSfxVoicePitch[i] - gSfxVoiceCurPitch[i]) / gSfxVoiceModCounter[i]--;
                            }
                            volume *= actor->soundVolume;
                            break;
                        case 0x115:
                            if (gSfxVoiceModCounter[i] > 0.0f) {
                                gSfxVoiceCurPitch[i] += (gSfxVoicePitch[i] - gSfxVoiceCurPitch[i]) / gSfxVoiceModCounter[i]--;
                            }
                            D_80770DE8 = 1.0 - ((gSfxVoiceCurPitch[i] - 1.0) * 0.9);
                            if (D_80770DE8 > 1.0) {
                                D_80770DE8 = 1.0f;
                            }
                            if (D_80770DE8 < 0.0f) {
                                D_80770DE8 = 0.0f;
                            }
                            volume *= D_80770DE8;
                            break;
                        case 0x12D:
                            if (gSfxVoiceModCounter[i] > 0.0f) {
                                gSfxVoiceCurPitch[i] += (gSfxVoicePitch[i] - gSfxVoiceCurPitch[i]) / gSfxVoiceModCounter[i]--;
                            }
                            D_80770DE8 = 1.0 - ((gSfxVoiceCurPitch[i] - 1.0f) * 0.9);
                            if (D_80770DE8 > 1.0) {
                                D_80770DE8 = 1.0f;
                            }
                            if (D_80770DE8 < 0.0f) {
                                D_80770DE8 = 0.0f;
                            }
                            volume *= D_80770DE8;
                            break;
                        case 0x12C:
                            volume *= gSfxVoicePitch[i];
                            break;
                        case 0x122:
                            gSfxSpeedVolume = actor->speedXZ / 600.0;
                            gSfxSpeedVolume = (gSfxSpeedVolume > 0.8) ? 0.8 : gSfxSpeedVolume;
                            volume *= gSfxSpeedVolume;
                            break;
                        default:
                            if (gSfxVoiceModCounter[i] > 0.0f) {
                                gSfxVoiceCurPitch[i] += (gSfxVoicePitch[i] - gSfxVoiceCurPitch[i]) / gSfxVoiceModCounter[i]--;
                            }
                            break;
                        }
                    }
                    switch (gSfxVoiceSoundId[i]) {
                    case 0x119:
                        sFramePitch = 1.0f;
                        volume = gSfxVoiceCurPitch[i] * 32767.0f;
                        D_80770DDC = 63.0f;
                        break;
                    case 0xFD:
                    case 0x108:
                    case 0x10E:
                        if (actor->actorType == 0x139) {
                            if (gSfxDistance < gSfxVoicePrevDist[i]) {
                                factor = gSfxVoicePrevDist[i] - gSfxDistance;
                            } else {
                                factor = -(gSfxVoicePrevDist[i] - gSfxDistance);
                            }
                            if (factor < 20.0f) {
                                sFramePitch = ((gSfxVoicePrevDist[i] - gSfxDistance) / 30.0) + 1.0;
                                if (sFramePitch > 1.18) {
                                    sFramePitch = 1.18f;
                                }
                                if (sFramePitch < 0.85) {
                                    sFramePitch = 0.85f;
                                }
                                sFramePitch = gSfxVoiceCurPitch[i] * (sFramePitch * sFramePitch);
                            } else {
                                sFramePitch = gSfxVoiceCurPitch[i];
                            }
                            gSfxVoicePrevDist[i] = gSfxDistance;
                            break;
                        }
                        /* fallthrough */
                    case 0x13F:
                    case 0x140:
                    case 0x141:
                        sFramePitch = ((gSfxVoicePrevDist[i] - gSfxDistance) / 900.0) + 1.0;
                        if (sFramePitch > 1.18) {
                            sFramePitch = 1.0f;
                        }
                        if (sFramePitch < 0.85) {
                            sFramePitch = 1.0f;
                        }
                        gSfxVoicePrevDist[i] = gSfxDistance;
                        sFramePitch = gSfxVoiceCurPitch[i] * (sFramePitch * sFramePitch);
                        break;
                    case 0x107:
                    case 0x10F:
                    case 0x114:
                    case 0x12E:
                    case 0x130:
                        if (gSfxDistance < gSfxVoicePrevDist[i]) {
                            factor = gSfxVoicePrevDist[i] - gSfxDistance;
                        } else {
                            factor = -(gSfxVoicePrevDist[i] - gSfxDistance);
                        }
                        if (factor < 20.0f) {
                            sFramePitch = ((gSfxVoicePrevDist[i] - gSfxDistance) / 100.0) + 1.0;
                            if (sFramePitch > 1.18) {
                                sFramePitch = 1.18f;
                            }
                            if (sFramePitch < 0.85) {
                                sFramePitch = 0.85f;
                            }
                            gSfxVoicePrevDist[i] = gSfxDistance;
                            sFramePitch = gSfxVoiceCurPitch[i] * (sFramePitch * sFramePitch);
                            break;
                        }
                        gSfxVoicePrevDist[i] = gSfxDistance;
                        /* fallthrough */
                    default:
                        sFramePitch = gSfxVoiceCurPitch[i];
                        break;
                    }
                    if (gSfxVoiceSoundId[i] == 0x10D) {
                        if (gCurrentMap == 0xE || gCurrentMap == 0x52) {
                            gSfxSpeedVolume = actor->speedXZ / 600.0;
                            gSfxSpeedVolume = (gSfxSpeedVolume > 0.8) ? 0.8 : gSfxSpeedVolume;
                            volume *= gSfxSpeedVolume;
                            if ((actor->y - actor->floorY) > 5.0f) {
                                volume = 0.0f;
                            }
                            gSfxPrevSpeed = actor->speedXZ;
                            sFramePitch = (actor->speedXZ / 550.0f) + 0.5;
                        } else {
                            if (gSfxPrevSpeed != actor->speedXZ) {
                                sFramePitch = (gSfxPrevSpeed * 32767.0f) / 200.0f;
                                gSfxSpeedVolume = gSfxSpeedVolume + ((sFramePitch - gSfxSpeedVolume) * 0.3);
                            } else if (gSfxSpeedVolume > 5000.0f) {
                                gSfxSpeedVolume = ((gSfxSpeedVolume - 350.0f) < 5000.0f) ? 5000.0f : (gSfxSpeedVolume - 350.0f);
                            } else if (gSfxSpeedVolume < 5000.0f) {
                                gSfxSpeedVolume = ((gSfxSpeedVolume + 350.0f) > 5000.0f) ? 5000.0f : (gSfxSpeedVolume + 350.0f);
                            }
                            volume *= gSfxSpeedVolume / 32767.0;
                            if ((actor->y - actor->floorY) > 5.0f) {
                                volume = 0.0f;
                            }
                            gSfxPrevSpeed = actor->speedXZ;
                            sFramePitch = (actor->speedXZ / 150.0f) + 0.5;
                            sFramePitch *= gSfxVoiceCurPitch[i];
                        }
                    }
                    if (actor != NULL) {
                        if (actor->soundAnimId != 0 && gSfxVoiceSoundId[i] != 0x131 && actor->sub4->model->animId != actor->soundAnimId) {
                            sfxStopSlotSound(actor, 0);
                        }
                    }
                    if (volume > 32767.0f) {
                        volume = 32767.0f;
                    }
                    if (gAudioUnderwater != 0) {
                        switch (gSfxVoiceSoundId[i]) {
                            case 0x101:
                            case 0x126:
                                sFramePitch *= 0.9;
                                volume = ((volume * 2) > 32767.0f) ? 32767.0f : (volume * 2);
                                break;
                        }
                    }
                    if (fxLevel != 0) {
                        fxFlags = fxLevel * 8;
                    } else {
                        fxFlags = 0;
                    }
                    if (gSfxFrontLevel < gSfxRearLevel) {
                        fxFlags |= 0x80;
                    }
                    if (sFramePitch < 0.17) {
                        sFramePitch = 0.17f;
                    }
                    n_alSndpPostEvent(sSoundSlotHandles[i], 0x100, fxFlags);
                    if (volume != gSfxVoiceSentVolume[i]) {
                        if (gSfxVoiceSentVolume[i] != -1) {
                            if (gSfxVoiceSentVolume[i] < volume) {
                                if ((gSfxVoiceSentVolume[i] + 8000) < volume) {
                                    volume = gSfxVoiceSentVolume[i] + 8000;
                                }
                            } else if (volume < (gSfxVoiceSentVolume[i] - 8000)) {
                                volume = gSfxVoiceSentVolume[i] - 8000;
                            }
                        }
                        gSfxVoiceSentVolume[i] = volume;
                        n_alSndpPostEvent(sSoundSlotHandles[i], 8, volume);
                    }
                    pan = D_80770DDC;
                    if (pan != gSfxVoiceSentPan[i]) {
                        if (gSfxVoiceSentPan[i] != -1) {
                            if (gSfxVoiceSentPan[i] < pan) {
                                if ((gSfxVoiceSentPan[i] + 8) < pan) {
                                    pan = gSfxVoiceSentPan[i] + 8;
                                }
                            } else if (pan < (gSfxVoiceSentPan[i] - 8)) {
                                pan = gSfxVoiceSentPan[i] - 8;
                            }
                        }
                        gSfxVoiceSentPan[i] = pan;
                        n_alSndpPostEvent(sSoundSlotHandles[i], 4, pan);
                    }
                    if (sFramePitch != gSfxVoiceSentPitch[i]) {
                        gSfxVoiceSentPitch[i] = sFramePitch;
                        n_alSndpPostEvent(sSoundSlotHandles[i], 0x10, *(s32 *)&sFramePitch);  // ORIG: the target passes the static's raw bits by an integer reload (lw a2,0x148(a2) at 0x5f98) although the value is already in $f4 (lwc1 at 0x5f74, swc1 $f4 at 0x5f90); an s32 value argument would emit cvt.w.s, an f32 one mfc1 (Q0026)
                    }
                }
            }
        }
    }

    gActivePlayerState = gPlayerSlots->actor->customState;
    camActor = gActivePlayerState->camActor;
    camState = camActor->customState;
    if (camState->hasWater != 0 && gPlayerSlots->camY < (camState->waterY + 3.0f) && gAudioUnderwater == 0 && gPlayerCount < 2) {
        gAudioUnderwater = 1;
        seqUpdateUnderwaterAudio(0);
        seqUpdateUnderwaterAudio(1);
    }
    if ((camState->hasWater == 0 || (camState->waterY + 3.0f) < gPlayerSlots->camY) && gAudioUnderwater == 1) {
        gAudioUnderwater = 0;
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
    f32 lookPitch;
    s32 dist;
    s32 level;
    f32 angle;
    u8 closest;
    u8 i;
    f32 srcPitch;
    s32 pad1;
    s32 pad2;
    s16 pos[4];

    gSfxDistance = -1.0f;
    closest = 0;
    for (i = 0; i < gPlayerCount; i++) {
        if (gPlayerSlots[i].active != 0) {
            s32 dx = gPlayerSlots[i].camX - x;
            s32 dy = gPlayerSlots[i].camY - y;
            s32 dz = gPlayerSlots[i].camZ - z;
            dist = dx * dx + dy * dy + dz * dz;
            if (gSfxDistance == -1.0f || (f32)dist < gSfxDistance) {
                closest = i;
                gSfxDistance = dist;
            }
        }
    }

    if (gSfxDistance == -1.0f) {
        return -1;
    }

    pos[0] = gPlayerSlots[closest].camX;
    pos[1] = gPlayerSlots[closest].camY;
    pos[2] = gPlayerSlots[closest].camZ;
    pos[3] = (gPlayerSlots[closest].camYaw * 4096.0) / 6.2831854820251465;
    camGetPathStartPose(&pos[0], &pos[1], &pos[2], &pos[3]);

    if (gSfxDistance < 500.0f) {
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
        gSfxDistance = sqrtf(gSfxDistance);
        if (gPlayerCount == 1 && (f64)directionality >= 0.8) {
            srcPitch = mathAngleBetweenPointsRad(pos[1], 0.0f, y, sqrtf(((x - pos[0]) * (x - pos[0])) + ((z - pos[2]) * (z - pos[2]))));
            lookPitch = mathAngleBetweenPointsRad(pos[1], 0.0f, gPlayerSlots->focusY, sqrtf(((gPlayerSlots->focusX - pos[0]) * (gPlayerSlots->focusX - pos[0])) + ((gPlayerSlots->focusZ - pos[2]) * (gPlayerSlots->focusZ - pos[2]))));
            diff = srcPitch - lookPitch;
            if (srcPitch < lookPitch) {
                diff += 6.2831855f;
            }
            if (diff > 3.1415927f) {
                diff = 6.2831855f - diff;
            }
            if ((f64)diff > 0.39269909262657166) {
                gSfxDistance *= 1.0 + ((f64)(diff - 0.3926991f) * 20.0);
            }
        }

        if ((f64)angle > 0.7853981852531433 && (f64)angle < 5.497787296772003) {
            gSfxDistance = (1.0f - (sinApprox(((2.0 * (f64)angle) / 3.0) + 2.617993950843811) * directionality)) * gSfxDistance;
        }
        if (gSfxDistance < 1.0f) {
            gSfxDistance = 1.0f;
        }

        level = (((f32)(range * 4000) / sqrtf(gSfxDistance)) - (((f32)(range * 4000) / 7.74596600000000013) - 32767.0));
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

    if (gAmbientAudioLevels[2] >= 21) {
        reverb = (gAmbientAudioLevels[2] * 100) / 255;
    }
    if (behind != 0) {
        reverb |= 0x80;
    }

    if (sSfxRandomPanHandles[sSfxRandomPanIndex] != 0) {
        n_alSndpStop(sSfxRandomPanHandles[sSfxRandomPanIndex]);
    }
    n_alSndpPlay(gSfxBank, sfxId, (u16)vol, (u8)pan, pitch, reverb, &sSfxRandomPanHandles[sSfxRandomPanIndex]);
    n_alSndpSetPriority(sSfxRandomPanHandles[sSfxRandomPanIndex], 0);
    sSfxRandomPanIndex ^= 1;
}

s16 sfxPlayOnFreeSlot(s16 sfxId, s32 volume, f32 pan, f32 pitch, u8 spread, u8 fx) {
    s16 slot;
    s16 i;

    if (spread != 0) {
        volume = (1.0 - ((randomLcgNext() / 4294967295.0) * ((u32)spread / 155.0))) * volume;
        pitch = ((randomLcgNext() / 4294967295.0) * ((u32)spread / 100.0)) + (pitch - ((u32)spread / 255.0));
    }

    for (i = 20; i > 0; i--) {
        if (gSfxFreeSlotHandles[sSfxFreeSlotCursor] == NULL) {
            break;
        }
        if (++sSfxFreeSlotCursor == 20) {
            sSfxFreeSlotCursor = 0;
        }
    }

    if (i > 0) {
        osSetThreadPri(NULL, 26);
        if (gAmbientAudioLevels[2] >= 21) {
            fx = ((((gAmbientAudioLevels[2] * 100) / 255) < (fx & 0x7F)) ? (fx & 0x7F) : ((gAmbientAudioLevels[2] * 100) / 255)) | (fx & 0x80);
        }

        if (sfxId < 0x800) {
            n_alSndpPlay(gSfxBank, sfxId, (u16)volume, (u8)pan, pitch, fx, &gSfxFreeSlotHandles[sSfxFreeSlotCursor]);
        } else {
            n_alSndpPlay(gSfxBankHigh, sfxId - 0x7FF, (u16)volume, (u8)pan, pitch, fx, &gSfxFreeSlotHandles[sSfxFreeSlotCursor]);
        }

        if (sfxId == 0x137) {
            n_alSndpSetPriority(gSfxFreeSlotHandles[sSfxFreeSlotCursor], 100);
        }

        if (gSfxFreeSlotHandles[sSfxFreeSlotCursor] != NULL) {
            slot = sSfxFreeSlotCursor;
        } else {
            slot = -1;
        }
        osSetThreadPri(NULL, 10);
        return slot;
    }

    return -1;
}

void sfxPlayAtPosition(f32 x, f32 y, f32 z, s16 sfxId, u8 volume, f32 pitch, u8 spread, u8 range) {
    s32 dx, dy, dz;
    s32 vol;
    f32 pan;
    u8 reverb;
    f64 pad;

    reverb = 0;
    dx = gPlayerSlots->camX - x;
    dy = gPlayerSlots->camY - y;
    dz = gPlayerSlots->camZ - z;
    gSfxDistance = sqrtf(dx * dx + dy * dy + dz * dz);
    if (gSfxDistance < 1.0f) {
        gSfxDistance = 1.0f;
    }
    vol = (s32)((((range * 4000) / sqrtf(gSfxDistance))) - (((f32)(range * 4000) / 7.74596600000000013) - 32767.0));
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
    pan = mathAngleBetweenPointsRad(gPlayerSlots->camX, gPlayerSlots->camZ, x, z) - gPlayerSlots->camYaw;
    if (pan < 0.0f) {
        pan += 6.2831855f;
    }
    if (pan > 0.7853982f && pan < 5.497787296772003) {
        vol = (s32)(((sinApprox(((2.0 * pan) / 3.0) + 2.617993950843811) * 0.3) + 1.0) * vol);
    }
    pan = (1.0f - sinApprox(pan)) * 63.5;
    if (gAudioUnderwater != 0) {
        reverb = 30;
    } else if (gAmbientAudioLevels[2] >= 21) {
        reverb = (gAmbientAudioLevels[2] * 100) / 255;
    }
    if (gSfxPositionalHandle != 0) {
        n_alSndpStop(gSfxPositionalHandle);
    }
    osSetThreadPri(NULL, 26);
    if (sfxId < 0x800) {
        n_alSndpPlay(gSfxBank, sfxId, (u16)vol, (u8)pan, pitch, reverb, &gSfxPositionalHandle);
    } else {
        n_alSndpPlay(gSfxBankHigh, sfxId - 0x7FF, (u16)vol, (u8)pan, pitch, reverb, &gSfxPositionalHandle);
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

    angle = mathAngleBetweenPointsRad(gPlayerSlots[gCurrentPlayerIndex].camX, gPlayerSlots[gCurrentPlayerIndex].camZ, x, z) - gPlayerSlots[gCurrentPlayerIndex].camYaw;
    if (angle < 0.0f) {
        angle += 6.2831855f;
    }

    if (angle > 1.5707964f && angle < 4.71238911151886) {
        behind = 1;
    }

    if (range == 0) {
        vol = ((u32)volume * 32767.0) / 255.0;
        if (gSfxDistance < 23.0f) {
            angle = 0.0f;
        }
    } else {
        dx = gPlayerSlots[gCurrentPlayerIndex].camX - x;
        dy = gPlayerSlots[gCurrentPlayerIndex].camY - y;
        dz = gPlayerSlots[gCurrentPlayerIndex].camZ - z;
        gSfxDistance = sqrtf(dx * dx + dy * dy + dz * dz);

        if (gSfxDistance < 23.0f) {
            angle = 0.0f;
            behind = 0;
        }

        if (angle > 0.7853982f && angle < 5.497787296772003) {
            gSfxDistance = (1.0f - (sinApprox(((2.0 * angle) / 3.0) + 2.617993950843811) * directionality)) * gSfxDistance;
        }

        if (gSfxDistance < 1.0f) {
            gSfxDistance = 1.0f;
        }

        vol = (((range * 4000) / sqrtf(gSfxDistance)) - (((f32)(range * 4000) / 7.74596600000000013) - 32767.0));
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

        if (gAmbientAudioLevels[2] >= 21) {
            fx = (gAmbientAudioLevels[2] * 100) / 255;
        }

        angle = (1.0f - sinApprox(angle)) * 63.5;

        if (behind != 0) {
            fx |= 0x80;
        }

        n_alSndpPlay(gSfxBank, sfxId, (u16)vol, (u8)angle, pitch, fx, &gActivePlayerState->sfxHandle);
    }
}

extern s32 D_8000DDCC;
extern s32 sSeqRomOffsets[];
extern void *gSeqBuffers[];
extern ALCSeq gSeqCSeqs[];


void seqLoadAndPlay(s32 seqIndex, u8 seqId, f32 volume) {
    u32 tries;
    void *buf;
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
    gSeqVolumeFading[seqIndex] = 0;
    gSeqVolume[seqIndex] = volume;
    gSeqCurrentId[seqIndex] = seqId;
    buf = heapAlloc(0x8000);
    {
        s32 addr = sSeqRomOffsets[seqId] + D_8000DDCC;
        u32 len = sSeqRomOffsets[seqId + 1] - sSeqRomOffsets[seqId];
        if (len & 1) {
            len++;
        }
        dmaReadAssetDecompress(addr, gSeqBuffers[seqIndex], &len, 0x80, 0, 1, buf);
    }
    heapFree(buf);
    n_alCSeqNew(&gSeqCSeqs[seqIndex], gSeqBuffers[seqIndex]);
    alSeqpSetSeq((ALSeqPlayer *)gSeqPlayers[seqIndex], (ALSeq *)&gSeqCSeqs[seqIndex]);
    resetCSPChannelStates(gSeqPlayers[seqIndex]);
    seqUpdateVolume(seqIndex);
    alCSPPlay(&gSeqPlayers[seqIndex]->al);
}

void seqUpdateVolume(s32 seqIndex) {
    f32 volume = gMusicVolume;
    s32 mode = sSfxFlagTable[gSeqCurrentId[seqIndex]] & 0xC00;
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
    alSeqpSetVol((ALSeqPlayer *)gSeqPlayers[seqIndex], (s16)((f64)((((f32)sSeqBaseVolume[gSeqCurrentId[seqIndex]]) * gSeqVolume[seqIndex]) * sSeqVolumeScale[seqIndex]) * ((f64)volume / 40.0) * 25000.0 / 32767.0));
}

void seqSetChannelVolumeScale(s32 seqIndex, f32 scale) {
    sSeqVolumeScale[seqIndex] = scale;
    seqUpdateVolume(seqIndex);
}

void seqUpdateVolumeFades(void) {
    s8 i;
    for (i = 0; i < 4; i++) {
        if (gSeqVolumeFading[i]) {
            f32 diff;
            gSeqVolume[i] += (gSeqTargetVolume[i] - gSeqVolume[i]) * 0.075;
            if (gSeqVolume[i] < gSeqTargetVolume[i]) {
                diff = gSeqTargetVolume[i] - gSeqVolume[i];
            } else {
                diff = -(gSeqTargetVolume[i] - gSeqVolume[i]);
            }
            if (diff < 0.05) {
                gSeqVolume[i] = gSeqTargetVolume[i];
                gSeqVolumeFading[i] = 0;
            }
            seqUpdateVolume(i);
        }
    }
}


void seqSetTargetVolume(s32 seqIndex, f32 targetVolume) {
    gSeqTargetVolume[seqIndex] = targetVolume;
    gSeqVolumeFading[seqIndex] = 1;
}


void seqSetVolumeInstant(s32 seqIndex, f32 volume) {
    gSeqTargetVolume[seqIndex] = volume;
    gSeqVolume[seqIndex] = volume;
    seqUpdateVolume(seqIndex);
}

void seqPlayWithDefaultVolume(s32 seqIndex, u8 seqId) {
    seqLoadAndPlay(seqIndex, seqId, D_80770588);
}

void seqLoadAndPlayWithReverb(s32 seqIndex, u8 seqId, f32 volume) {
    f32 pan, vol;

    seqLoadAndPlay(seqIndex, seqId, volume);
    pan = ((f64)(u32)gAmbientAudioLevels[2] * 0.3) / 255.0;
    vol = (((f64)(u32)gAmbientAudioLevels[2] * 0.35) / 255.0) + 1.0;
    if (seqIndex != 0) {
        if (sSfxFlagTable[gSeqCurrentId[seqIndex]] & 1) {
            alCSPSetChlPanVolume(&gSeqPlayers[seqIndex]->al, pan, vol);
        } else {
            alCSPSetChlPanVolume(&gSeqPlayers[seqIndex]->al, 0.0f, 1.0f);
        }
    }
    seqUpdateUnderwaterAudio(seqIndex);
}

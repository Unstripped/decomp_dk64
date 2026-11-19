#include "common.h"
#include "audio_synth.h"
#include "proto/global/13E160.h"
#include "proto/global/1435C0.h"
#include "proto/global/144E00.h"
#include "proto/global/145950.h"

  

// Equal-power pan/mix curve (libultra eqpower[128]); the right channel reads it backwards from entry 127.
s16 D_80756490[128] = {
    0x7FFF, 0x7FFC, 0x7FF5, 0x7FE8, 0x7FD7, 0x7FC0, 0x7FA5, 0x7F84,
    0x7F5F, 0x7F34, 0x7F05, 0x7ED0, 0x7E97, 0x7E58, 0x7E15, 0x7DCD,
    0x7D7F, 0x7D2D, 0x7CD6, 0x7C7A, 0x7C1A, 0x7BB4, 0x7B49, 0x7ADA,
    0x7A66, 0x79ED, 0x796F, 0x78ED, 0x7866, 0x77DA, 0x7749, 0x76B4,
    0x761A, 0x757B, 0x74D8, 0x7430, 0x7384, 0x72D3, 0x721E, 0x7164,
    0x70A6, 0x6FE3, 0x6F1C, 0x6E51, 0x6D81, 0x6CAD, 0x6BD5, 0x6AF9,
    0x6A18, 0x6933, 0x684A, 0x675D, 0x666C, 0x6577, 0x647E, 0x6381,
    0x6280, 0x617C, 0x6073, 0x5F67, 0x5E57, 0x5D43, 0x5C2C, 0x5B11,
    0x59F2, 0x58D0, 0x57AA, 0x5681, 0x5555, 0x5425, 0x52F2, 0x51BC,
    0x5082, 0x4F46, 0x4E06, 0x4CC3, 0x4B7D, 0x4A35, 0x48E9, 0x479B,
    0x4649, 0x44F5, 0x439E, 0x4245, 0x40E9, 0x3F8A, 0x3E29, 0x3CC6,
    0x3B60, 0x39F8, 0x388D, 0x3721, 0x35B2, 0x3441, 0x32CE, 0x3159,
    0x2FE2, 0x2E69, 0x2CEF, 0x2B72, 0x29F4, 0x2875, 0x26F3, 0x2570,
    0x23EC, 0x2266, 0x20DF, 0x1F57, 0x1DCE, 0x1C43, 0x1AB7, 0x192A,
    0x179C, 0x160E, 0x147E, 0x12ED, 0x115C, 0x0FCA, 0x0E38, 0x0CA5,
    0x0B11, 0x097D, 0x07E9, 0x0654, 0x04C0, 0x032A, 0x0195, 0x0000,
};

extern u8 gAudioSurroundEnabled;
extern u8 gAudioMonoEnabled;
extern u8 D_807FF0F2;

Acmd *n_alEnvmixerPull(void *filter, s32 time, Acmd *cmdList) {
    Acmd *cmd;
    N_PVoice *f;
    s16 outOffset;
    s32 lastTime;
    s32 curTime;
    s32 subSamples;
    s16 samplePtr;
    s32 volume;
    SynCoreParam *node;
    s32 samplesLeft;
    SynStartParam *paramNode;
    s32 startVolume;
    SynCoreParam *segNode;
    SynCoreParam *freeNode;

    cmd = cmdList;
    f = filter;
    curTime = time;
    samplePtr = 0;
    samplesLeft = 0xB8;
    outOffset = 0;
    while (f->em_ctrlList != NULL) {
        lastTime = curTime;
        curTime = f->em_ctrlList->delta;
        subSamples = ((curTime - lastTime + 0xB7) / 184) * 0xB8;
        if (subSamples == 0) {
            curTime = lastTime;
        }
        if (subSamples > samplesLeft) {
            break;
        }
        switch (f->em_ctrlList->type) {
        case 13:
            paramNode = (SynStartParam *)f->em_ctrlList;
            if (paramNode->unity != 0) {
                f->rs_upitch = 1;
            }
            _decodeChunk(f, 5, paramNode->wave);
            f->em_motion = 1;
            f->em_first = 1;
            f->em_delta = 0;
            f->em_segEnd = ((paramNode->samples + 0xB7) / 184) * 0xB8;
            startVolume = (paramNode->volume + paramNode->volume) / 2;
            f->em_volume = startVolume;
            f->em_pan = paramNode->pan;
            f->em_dryamt = (D_80756490[paramNode->fxmix & 0x7F] & 0xFFFE) | (paramNode->fxmix >> 7);
            if (gAudioSurroundEnabled == 0) {
                f->em_dryamt &= 0xFFFE;
            }
            f->em_wetamt = D_80756490[127 - (paramNode->fxmix & 0x7F)] & 0xFFFE;
            if (D_807FF0F2 != 0) {
                f->em_pan = (f->em_pan >> 1) + 0x20;
            } else if (gAudioMonoEnabled != 0) {
                f->em_pan = 0x40;
            }
            if (paramNode->samples != 0) {
                f->em_cvolL = 1;
                f->em_cvolR = 1;
            } else {
                f->em_cvolL = (D_80756490[f->em_pan] * f->em_volume) >> 15;
                f->em_cvolR = (D_80756490[127 - f->em_pan] * f->em_volume) >> 15;
            }
            f->rs_ratio = paramNode->pitch;
            f->lowpass.fgain = paramNode->fxPitch;
            f->lowpass.fc = paramNode->fxVolume;
            f->lowpass.first = 1;
            f->unk8C = paramNode->fxDelay;
            break;
        case 11:
        case 12:
        case 16:
            cmd = _pullSubFrame(f, &outOffset, &samplePtr, subSamples, cmd);
            if (f->em_delta >= f->em_segEnd) {
                f->em_ltgt = (D_80756490[f->em_pan] * f->em_volume) >> 15;
                f->em_rtgt = (D_80756490[127 - f->em_pan] * f->em_volume) >> 15;
                f->em_delta = f->em_segEnd;
                f->em_cvolL = f->em_ltgt;
                f->em_cvolR = f->em_rtgt;
            } else {
                f->em_cvolL = _getVol(f->em_cvolL, f->em_delta, f->em_lratm, f->em_lratl);
                f->em_cvolR = _getVol(f->em_cvolR, f->em_delta, f->em_rratm, f->em_rratl);
            }
            if (f->em_cvolL == 0) {
                f->em_cvolL = 1;
            }
            if (f->em_cvolR == 0) {
                f->em_cvolR = 1;
            }
            if (f->em_ctrlList->type == 0xC) {
                if (D_807FF0F2 != 0) {
                    f->em_pan = (f->em_ctrlList->data.s.s1 >> 1) + 0x20;
                } else if (gAudioMonoEnabled != 0) {
                    f->em_pan = 0x40;
                } else {
                    f->em_pan = f->em_ctrlList->data.i;
                }
            }
            if (f->em_ctrlList->type == 0xB) {
                f->em_delta = 0;
                volume = f->em_ctrlList->data.i;
                volume = (volume + volume) / 2;
                f->em_volume = volume;
                f->em_segEnd = ((f->em_ctrlList->moredata.i + 0xB7) / 184) * 0xB8;
            }
            if (f->em_ctrlList->type == 0x10) {
                if (((((f->em_dryamt ^ f->em_wetamt) & 1) ^ ((f->em_ctrlList->data.i + 1) >> 7)) != 0) && (gAudioSurroundEnabled != 0)) {
                    if (f->em_pan >= 0x41) {
                        f->em_dryamt ^= 1;
                    } else {
                        f->em_wetamt ^= 1;
                    }
                }
                f->em_dryamt = (D_80756490[f->em_ctrlList->data.i & 0x7F] & 0xFFFE) | (f->em_dryamt & 1);
                f->em_wetamt = (D_80756490[127 - (f->em_ctrlList->data.i & 0x7F)] & 0xFFFE) | (f->em_wetamt & 1);
            }
            f->em_first = 1;
            break;
        case 14:
            segNode = f->em_ctrlList;
            if (segNode->unity != 0) {
                f->rs_upitch = 1;
            }
            _decodeChunk(f, 5, segNode->data.ptr);
            f->em_motion = 1;
            break;
        case 15:
            cmd = _pullSubFrame(f, &outOffset, &samplePtr, subSamples, cmd);
            n_alEnvmixerParam(f, 4, 0);
            break;
        case 0:
            freeNode = f->em_ctrlList;
            ((N_PVoice *)freeNode->data.ptr)->delta = 0;
            _n_freePVoice(freeNode->data.ptr);
            break;
        case 7:
            cmd = _pullSubFrame(f, &outOffset, &samplePtr, subSamples, cmd);
            f->rs_ratio = f->em_ctrlList->data.f;
            break;
        case 8:
            cmd = _pullSubFrame(f, &outOffset, &samplePtr, subSamples, cmd);
            f->rs_upitch = 1;
            break;
        case 5:
            cmd = _pullSubFrame(f, &outOffset, &samplePtr, subSamples, cmd);
            _decodeChunk(f, 5, f->em_ctrlList->data.ptr);
            break;
        default:
            cmd = _pullSubFrame(f, &outOffset, &samplePtr, subSamples, cmd);
            n_alEnvmixerParam(f, f->em_ctrlList->type, f->em_ctrlList->data.ptr);
            break;
        }
        samplePtr += subSamples * 2;
        samplesLeft -= subSamples;
        node = f->em_ctrlList;
        f->em_ctrlList = f->em_ctrlList->next;
        if (f->em_ctrlList == NULL) {
            f->em_ctrlTail = 0;
        }
        __n_freeParam(node);
    }
    cmd = _pullSubFrame(f, &outOffset, &samplePtr, samplesLeft, cmd);
    if (f->em_delta > f->em_segEnd) {
        f->em_delta = f->em_segEnd;
    }
    return cmd;
}

s32 n_alEnvmixerParam(void *filter, s32 paramID, void *paramVal) {
    N_PVoice *env;

    env = filter;
    switch (paramID) {
    case 3:
        if (env->em_ctrlTail != NULL) {
            env->em_ctrlTail->next = paramVal;
        } else {
            env->em_ctrlList = paramVal;
        }
        env->em_ctrlTail = paramVal;
        break;
    case 4:
        env->em_first = 1;
        env->em_motion = 0;
        env->em_volume = 1;
        env->em_segEnd = 0;
        env->rs_delta = 0.0f;
        env->rs_first = 1;
        env->rs_upitch = 0;
        alResampleParam(env, 4, paramVal);
        break;
    case 9:
        env->em_motion = 1;
        break;
    default:
        alResampleParam(env, paramID, paramVal);
        break;
    }
    return 0;
}

Acmd *_pullSubFrame(N_PVoice *filter, s16 *outp, s16 *samplePtr, s32 count, Acmd *cmdList) {
    Acmd *ptr;
    N_PVoice *env;

    ptr = cmdList;
    env = filter;
    if ((env->em_motion != 1) || (count == 0)) {
        return ptr;
    }
    ptr = n_alResamplePull(env, outp, count, cmdList);
    if (env->em_first != 0) {
        env->em_first = 0;
        env->em_ltgt = (D_80756490[env->em_pan] * env->em_volume) >> 15;
        env->em_lratm = _getRate(env->em_cvolL, env->em_ltgt, env->em_segEnd, &env->em_lratl);
        env->em_rtgt = (D_80756490[127 - env->em_pan] * env->em_volume) >> 15;
        env->em_rratm = _getRate(env->em_cvolR, env->em_rtgt, env->em_segEnd, &env->em_rratl);
        aSetVolume(ptr++, A_VOL | A_LEFT, env->em_cvolL, env->em_dryamt, env->em_wetamt);
        aSetVolume(ptr++, A_VOL | A_RIGHT, env->em_rtgt, env->em_rratm, env->em_rratl);
        aSetVolume(ptr++, A_RATE, env->em_ltgt, env->em_lratm, env->em_lratl);
        {
            Acmd *cmd;

            cmd = ptr++;
            cmd->words.w0 = (A_ENVMIXER << 24) | (A_INIT << 16) | (env->em_cvolR & 0xFFFF);
            cmd->words.w1 = osVirtualToPhysical(env->em_state);
        }
    } else {
        aEnvMixer(ptr++, A_CONTINUE, osVirtualToPhysical(env->em_state));
    }
    *outp += 0x170;
    env->em_delta += 0xB8;
    return ptr;
}

s16 _getRate(f32 curVol, f32 targetVol, s32 delta, u16 *ratem) {
    s16 rate;
    s16 round;
    f32 invDelta;
    f32 rawRate;
    f32 frac;

    if (delta == 0) {
        if (curVol <= targetVol) {
            *ratem = 0xFFFF;
            return 0x7FFF;
        } else {
            *ratem = 0;
            return -0x8000;
        }
    }
    invDelta = 1.0f / (f32)delta;
    if (targetVol < 1.0f) {
        targetVol = 1.0f;
    }
    if (curVol <= 0.0f) {
        curVol = 1.0f;
    }
    rawRate = (targetVol - curVol) * invDelta * 8.0f;
    rate = (s16)(s32)rawRate;
    frac = rawRate - (f32)rate;
    rate -= 1;
    frac += 1.0f;
    round = (s16)(s32)frac;
    rate += round;
    frac -= (f32)round;
    *ratem = (u32)(65535.0f * frac);
    return rate;
}

s16 _getVol(s16 init, s32 delta, s16 rate, u16 ratem) {
    s32 change;

    delta >>= 3;
    if (delta == 0) {
        return init;
    }
    change = ratem * delta;
    change = change >> 0x10;
    change += rate * delta;
    init += change;
    return init;
}

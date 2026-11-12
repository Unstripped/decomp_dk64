#include "common.h"
#include "audio_synth.h"
#include "proto/global/13E160.h"
#include "proto/global/1435C0.h"
#include "proto/global/144E00.h"
#include "proto/global/145950.h"

  

extern s16 D_80756490[];
extern s16 D_8075658E[];

extern u8 D_807FF0F0;
extern u8 D_807FF0F1;
extern u8 D_807FF0F2;

Acmd *n_alEnvmixerPull(void *filter, s32 time, Acmd *cmdList) {
    Acmd *cmd;
    N_PVoice *f;
    s16 outOffset;
    s32 lastTime;
    s32 curTime;
    s32 subSamples;
    s16 samplePtr;
    s32 ratio;
    SynCoreParam *node;
    s32 samplesLeft;
    SynStartParam *paramNode;
    s32 scaledVol;
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
            scaledVol = (paramNode->volume + paramNode->volume) / 2;
            f->em_volume = scaledVol;
            f->em_pan = paramNode->pan;
            f->em_dryamt = (D_80756490[paramNode->fxmix & 0x7F] & 0xFFFE) | ((s32)paramNode->fxmix >> 7);
            if (D_807FF0F0 == 0) {
                f->em_dryamt &= 0xFFFE;
            }
            f->em_wetamt = D_8075658E[-(paramNode->fxmix & 0x7F)] & 0xFFFE;
            if (D_807FF0F2 != 0) {
                f->em_pan = (f->em_pan >> 1) + 0x20;
            } else if (D_807FF0F1 != 0) {
                f->em_pan = 0x40;
            }
            if (paramNode->samples != 0) {
                f->em_cvolL = 1;
                f->em_cvolR = 1;
            } else {
                f->em_cvolL = (D_80756490[f->em_pan] * f->em_volume) >> 15;
                f->em_cvolR = (D_8075658E[-f->em_pan] * f->em_volume) >> 15;
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
                f->em_rtgt = (D_8075658E[-f->em_pan] * f->em_volume) >> 15;
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
                } else if (D_807FF0F1 != 0) {
                    f->em_pan = 0x40;
                } else {
                    f->em_pan = f->em_ctrlList->data.i;
                }
            }
            if (f->em_ctrlList->type == 0xB) {
                f->em_delta = 0;
                ratio = f->em_ctrlList->data.i;
                ratio = (ratio + ratio) / 2;
                f->em_volume = ratio;
                f->em_segEnd = ((f->em_ctrlList->moredata.i + 0xB7) / 184) * 0xB8;
            }
            if (f->em_ctrlList->type == 0x10) {
                if (((((f->em_dryamt ^ f->em_wetamt) & 1) ^ ((f->em_ctrlList->data.i + 1) >> 7)) != 0) && (D_807FF0F0 != 0)) {
                    if (f->em_pan >= 0x41) {
                        f->em_dryamt ^= 1;
                    } else {
                        f->em_wetamt ^= 1;
                    }
                }
                f->em_dryamt = (D_80756490[f->em_ctrlList->data.i & 0x7F] & 0xFFFE) | (f->em_dryamt & 1);
                f->em_wetamt = (D_8075658E[-(f->em_ctrlList->data.i & 0x7F)] & 0xFFFE) | (f->em_wetamt & 1);
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
        env->em_lratm = _getRate((f32)env->em_cvolL, (f32)env->em_ltgt, env->em_segEnd, &env->em_lratl);
        env->em_rtgt = (D_8075658E[-env->em_pan] * env->em_volume) >> 15;
        env->em_rratm = _getRate((f32)env->em_cvolR, (f32)env->em_rtgt, env->em_segEnd, &env->em_rratl);
        {
            Acmd *cmd;

            cmd = ptr++;
            cmd->words.w0 = 0x09060000 | (env->em_cvolL & 0xFFFF);
            cmd->words.w1 = ((env->em_dryamt & 0xFFFF) << 16) | (env->em_wetamt & 0xFFFF);
        }
        {
            Acmd *cmd;

            cmd = ptr++;
            cmd->words.w0 = 0x09040000 | (env->em_rtgt & 0xFFFF);
            cmd->words.w1 = ((env->em_rratm & 0xFFFF) << 16) | (env->em_rratl & 0xFFFF);
        }
        {
            Acmd *cmd;

            cmd = ptr++;
            cmd->words.w0 = 0x09000000 | (env->em_ltgt & 0xFFFF);
            cmd->words.w1 = ((env->em_lratm & 0xFFFF) << 16) | (env->em_lratl & 0xFFFF);
        }
        {
            Acmd *cmd;

            cmd = ptr++;
            cmd->words.w0 = 0x03010000 | (env->em_cvolR & 0xFFFF);
            cmd->words.w1 = osVirtualToPhysical(env->em_state);
        }
    } else {
        Acmd *cmd;

        cmd = ptr++;
        cmd->words.w0 = 0x03000000;
        cmd->words.w1 = osVirtualToPhysical(env->em_state);
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

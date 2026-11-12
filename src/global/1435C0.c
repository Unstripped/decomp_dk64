#include "common.h"
#include "proto/global/13E160.h"
#include "proto/global/1435C0.h"
#include "proto/global/144E00.h"
#include "proto/global/145950.h"



typedef struct EnvMixerEnv {
    u8 unk0[0x44];
    f32 unk44;
    s32 unk48;
    f32 unk4C;
    s32 unk50;
    u8 *unk54;
    s16 unk58;
    s16 unk5A;
    s16 unk5C;
    s16 unk5E;
    s16 unk60;
    s16 unk62;
    u16 unk64;
    s16 unk66;
    s16 unk68;
    u16 unk6A;
    s16 unk6C;
    s16 unk6E;
    s32 unk70;
    s32 unk74;
    s32 unk78;
    void *unk7C;
    void *unk80;
    s32 unk84;
} EnvMixerEnv;

  


extern s16 D_80756490[];
extern s16 D_8075658E[];

typedef union EnvNodeData {
    f32 f;
    s32 i;
    void *ptr;
    struct {
        s16 s0;
        s16 s1;
    } s;
} EnvNodeData;

typedef struct EnvNode {
    struct EnvNode *next;
    s32 unk4;
    s16 type;
    s16 unkA;
    EnvNodeData data;
    s16 unk10;
    u8 unk12;
    u8 unk13;
    u8 unk14;
    u8 unk15;
    u8 pad16[2];
    f32 unk18;
    s32 unk1C;
    void *unk20;
} EnvNode;

typedef struct EnvPVoice {
    u8 pad0[0x88];
    s32 unk88;
} EnvPVoice;

typedef struct EnvMixerPullView {
    u8 pad0[0x44];
    f32 unk44;
    s32 unk48;
    f32 unk4C;
    s32 unk50;
    u8 *unk54;
    s16 unk58;
    s16 unk5A;
    s16 unk5C;
    s16 unk5E;
    s16 unk60;
    s16 unk62;
    u16 unk64;
    s16 unk66;
    s16 unk68;
    u16 unk6A;
    s16 unk6C;
    s16 unk6E;
    s32 unk70;
    s32 unk74;
    s32 unk78;
    EnvNode *unk7C;
    void *unk80;
    s32 unk84;
    u8 pad88[4];
    u8 unk8C;
    u8 pad8D[3];
    s16 unk90;
    s16 unk92;
    u8 pad94[0x24];
    s32 unkB8;
} EnvMixerPullView;

extern u8 D_807FF0F0;
extern u8 D_807FF0F1;
extern u8 D_807FF0F2;

Acmd *n_alEnvmixerPull(void *filter, s32 time, Acmd *cmdList) {
    Acmd *cmd;
    EnvMixerPullView *f;
    s16 outOffset;
    s32 lastTime;
    s32 curTime;
    s32 subSamples;
    s16 samplePtr;
    s32 ratio;
    EnvNode *node;
    s32 samplesLeft;
    EnvNode *paramNode;
    s32 scaledVol;
    EnvNode *segNode;
    EnvNode *freeNode;

    cmd = cmdList;
    f = filter;
    curTime = time;
    samplePtr = 0;
    samplesLeft = 0xB8;
    outOffset = 0;
    while (f->unk7C != NULL) {
        lastTime = curTime;
        curTime = f->unk7C->unk4;
        subSamples = ((curTime - lastTime + 0xB7) / 184) * 0xB8;
        if (subSamples == 0) {
            curTime = lastTime;
        }
        if (subSamples > samplesLeft) {
            break;
        }
        switch (f->unk7C->type) {
        case 13:
            paramNode = f->unk7C;
            if (paramNode->unkA != 0) {
                f->unk48 = 1;
            }
            _decodeChunk(f, 5, paramNode->unk20);
            f->unk84 = 1;
            f->unk78 = 1;
            f->unk70 = 0;
            f->unk74 = ((paramNode->unk1C + 0xB7) / 184) * 0xB8;
            scaledVol = (paramNode->unk10 + paramNode->unk10) / 2;
            f->unk5A = scaledVol;
            f->unk58 = paramNode->unk12;
            f->unk60 = (D_80756490[paramNode->unk13 & 0x7F] & 0xFFFE) | ((s32)paramNode->unk13 >> 7);
            if (D_807FF0F0 == 0) {
                f->unk60 &= 0xFFFE;
            }
            f->unk62 = D_8075658E[-(paramNode->unk13 & 0x7F)] & 0xFFFE;
            if (D_807FF0F2 != 0) {
                f->unk58 = (f->unk58 >> 1) + 0x20;
            } else if (D_807FF0F1 != 0) {
                f->unk58 = 0x40;
            }
            if (paramNode->unk1C != 0) {
                f->unk5C = 1;
                f->unk5E = 1;
            } else {
                f->unk5C = (D_80756490[f->unk58] * f->unk5A) >> 15;
                f->unk5E = (D_8075658E[-f->unk58] * f->unk5A) >> 15;
            }
            f->unk44 = paramNode->data.f;
            f->unk92 = paramNode->unk15;
            f->unk90 = paramNode->unk18;
            f->unkB8 = 1;
            f->unk8C = paramNode->unk14;
            break;
        case 11:
        case 12:
        case 16:
            cmd = _pullSubFrame((EnvMixerEnv *)f, &outOffset, &samplePtr, subSamples, cmd);
            if (f->unk70 >= f->unk74) {
                f->unk68 = (D_80756490[f->unk58] * f->unk5A) >> 15;
                f->unk6E = (D_8075658E[-f->unk58] * f->unk5A) >> 15;
                f->unk70 = f->unk74;
                f->unk5C = f->unk68;
                f->unk5E = f->unk6E;
            } else {
                f->unk5C = _getVol(f->unk5C, f->unk70, f->unk66, f->unk64);
                f->unk5E = _getVol(f->unk5E, f->unk70, f->unk6C, f->unk6A);
            }
            if (f->unk5C == 0) {
                f->unk5C = 1;
            }
            if (f->unk5E == 0) {
                f->unk5E = 1;
            }
            if (f->unk7C->type == 0xC) {
                if (D_807FF0F2 != 0) {
                    f->unk58 = (f->unk7C->data.s.s1 >> 1) + 0x20;
                } else if (D_807FF0F1 != 0) {
                    f->unk58 = 0x40;
                } else {
                    f->unk58 = f->unk7C->data.i;
                }
            }
            if (f->unk7C->type == 0xB) {
                f->unk70 = 0;
                ratio = f->unk7C->data.i;
                ratio = (ratio + ratio) / 2;
                f->unk5A = ratio;
                f->unk74 = ((*(s32 *)&f->unk7C->unk10 + 0xB7) / 184) * 0xB8;
            }
            if (f->unk7C->type == 0x10) {
                if (((((f->unk60 ^ f->unk62) & 1) ^ ((f->unk7C->data.i + 1) >> 7)) != 0) && (D_807FF0F0 != 0)) {
                    if (f->unk58 >= 0x41) {
                        f->unk60 ^= 1;
                    } else {
                        f->unk62 ^= 1;
                    }
                }
                f->unk60 = (D_80756490[f->unk7C->data.i & 0x7F] & 0xFFFE) | (f->unk60 & 1);
                f->unk62 = (D_8075658E[-(f->unk7C->data.i & 0x7F)] & 0xFFFE) | (f->unk62 & 1);
            }
            f->unk78 = 1;
            break;
        case 14:
            segNode = f->unk7C;
            if (segNode->unkA != 0) {
                f->unk48 = 1;
            }
            _decodeChunk(f, 5, segNode->data.ptr);
            f->unk84 = 1;
            break;
        case 15:
            cmd = _pullSubFrame((EnvMixerEnv *)f, &outOffset, &samplePtr, subSamples, cmd);
            n_alEnvmixerParam(f, 4, 0);
            break;
        case 0:
            freeNode = f->unk7C;
            ((EnvPVoice *)freeNode->data.ptr)->unk88 = 0;
            _n_freePVoice(freeNode->data.ptr);
            break;
        case 7:
            cmd = _pullSubFrame((EnvMixerEnv *)f, &outOffset, &samplePtr, subSamples, cmd);
            f->unk44 = f->unk7C->data.f;
            break;
        case 8:
            cmd = _pullSubFrame((EnvMixerEnv *)f, &outOffset, &samplePtr, subSamples, cmd);
            f->unk48 = 1;
            break;
        case 5:
            cmd = _pullSubFrame((EnvMixerEnv *)f, &outOffset, &samplePtr, subSamples, cmd);
            _decodeChunk(f, 5, f->unk7C->data.ptr);
            break;
        default:
            cmd = _pullSubFrame((EnvMixerEnv *)f, &outOffset, &samplePtr, subSamples, cmd);
            n_alEnvmixerParam(f, f->unk7C->type, f->unk7C->data.ptr);
            break;
        }
        samplePtr += subSamples * 2;
        samplesLeft -= subSamples;
        node = f->unk7C;
        f->unk7C = f->unk7C->next;
        if (f->unk7C == NULL) {
            f->unk80 = 0;
        }
        __n_freeParam(node);
    }
    cmd = _pullSubFrame((EnvMixerEnv *)f, &outOffset, &samplePtr, samplesLeft, cmd);
    if (f->unk70 > f->unk74) {
        f->unk70 = f->unk74;
    }
    return cmd;
}


s32 n_alEnvmixerParam(void *filter, s32 paramID, void *paramVal) {
    EnvMixerEnv *env;

    env = filter;
    switch (paramID) {
    case 3:
        if (env->unk80 != NULL) {
            *(void **)env->unk80 = paramVal;
        } else {
            env->unk7C = paramVal;
        }
        env->unk80 = paramVal;
        break;
    case 4:
        env->unk78 = 1;
        env->unk84 = 0;
        env->unk5A = 1;
        env->unk74 = 0;
        env->unk4C = 0.0f;
        env->unk50 = 1;
        env->unk48 = 0;
        alResampleParam(env, 4, paramVal);
        break;
    case 9:
        env->unk84 = 1;
        break;
    default:
        alResampleParam(env, paramID, paramVal);
        break;
    }
    return 0;
}

Acmd *_pullSubFrame(EnvMixerEnv *filter, s16 *outp, s16 *samplePtr, s32 count, Acmd *cmdList) {
    Acmd *ptr;
    EnvMixerEnv *env;

    ptr = cmdList;
    env = filter;
    if ((env->unk84 != 1) || (count == 0)) {
        return ptr;
    }
    ptr = n_alResamplePull(env, outp, count, cmdList);
    if (env->unk78 != 0) {
        env->unk78 = 0;
        env->unk68 = (D_80756490[env->unk58] * env->unk5A) >> 15;
        env->unk66 = _getRate((f32)env->unk5C, (f32)env->unk68, env->unk74, &env->unk64);
        env->unk6E = (D_8075658E[-env->unk58] * env->unk5A) >> 15;
        env->unk6C = _getRate((f32)env->unk5E, (f32)env->unk6E, env->unk74, &env->unk6A);
        {
            Acmd *cmd;

            cmd = ptr++;
            cmd->words.w0 = 0x09060000 | (env->unk5C & 0xFFFF);
            cmd->words.w1 = ((env->unk60 & 0xFFFF) << 16) | (env->unk62 & 0xFFFF);
        }
        {
            Acmd *cmd;

            cmd = ptr++;
            cmd->words.w0 = 0x09040000 | (env->unk6E & 0xFFFF);
            cmd->words.w1 = ((env->unk6C & 0xFFFF) << 16) | (env->unk6A & 0xFFFF);
        }
        {
            Acmd *cmd;

            cmd = ptr++;
            cmd->words.w0 = 0x09000000 | (env->unk68 & 0xFFFF);
            cmd->words.w1 = ((env->unk66 & 0xFFFF) << 16) | (env->unk64 & 0xFFFF);
        }
        {
            Acmd *cmd;

            cmd = ptr++;
            cmd->words.w0 = 0x03010000 | (env->unk5E & 0xFFFF);
            cmd->words.w1 = osVirtualToPhysical(env->unk54);
        }
    } else {
        Acmd *cmd;

        cmd = ptr++;
        cmd->words.w0 = 0x03000000;
        cmd->words.w1 = osVirtualToPhysical(env->unk54);
    }
    *outp += 0x170;
    env->unk70 += 0xB8;
    return ptr;
}

s16 _getRate(f32 curVol, f32 targetVol, s32 delta, s16 *ratem) {
    s16 rate;
    s16 round;
    f32 invDelta;
    f32 rawRate;
    f32 frac;

    if (delta == 0) {
        if (curVol <= targetVol) {
            *(u16 *)ratem = 0xFFFF;
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
    *ratem = (s16)(u32)(65535.0f * frac);
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

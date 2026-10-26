#include "common.h"



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

  


#pragma GLOBAL_ASM("asm/global/nonmatchings/1435C0/n_alEnvmixerPull.s")

s32 n_alEnvmixerParam(EnvMixerEnv *arg0, s32 arg1, void *arg2) {
    EnvMixerEnv *sp24;

    sp24 = arg0;
    switch (arg1) {
    case 3:
        if (sp24->unk80 != NULL) {
            *(void **)sp24->unk80 = arg2;
        } else {
            sp24->unk7C = arg2;
        }
        sp24->unk80 = arg2;
        break;
    case 4:
        sp24->unk78 = 1;
        sp24->unk84 = 0;
        sp24->unk5A = 1;
        sp24->unk74 = 0;
        sp24->unk4C = 0.0f;
        sp24->unk50 = 1;
        sp24->unk48 = 0;
        alResampleParam(sp24, 4, arg2);
        break;
    case 9:
        sp24->unk84 = 1;
        break;
    default:
        alResampleParam(sp24, arg1, arg2);
        break;
    }
    return 0;
}

typedef struct EnvAcmd {
    u32 w0;
    u32 w1;
} EnvAcmd;

extern s16 D_80756490[];
extern s16 D_8075658E[];
extern EnvAcmd *n_alResamplePull();
s16 _getRate(f32, f32, s32, s16 *);


EnvAcmd *_pullSubFrame(EnvMixerEnv *arg0, s16 *arg1, s32 arg2, s32 arg3, EnvAcmd *arg4) {
    EnvAcmd *ptr;
    EnvMixerEnv *env;

    ptr = arg4;
    env = arg0;
    if ((env->unk84 != 1) || (arg3 == 0)) {
        return ptr;
    }
    ptr = n_alResamplePull(env, arg1, arg3, arg4);
    if (env->unk78 != 0) {
        env->unk78 = 0;
        env->unk68 = (D_80756490[env->unk58] * env->unk5A) >> 15;
        env->unk66 = _getRate((f32)env->unk5C, (f32)env->unk68, env->unk74, &env->unk64);
        env->unk6E = (D_8075658E[-env->unk58] * env->unk5A) >> 15;
        env->unk6C = _getRate((f32)env->unk5E, (f32)env->unk6E, env->unk74, &env->unk6A);
        {
            EnvAcmd *cmd;

            cmd = ptr++;
            cmd->w0 = 0x09060000 | (env->unk5C & 0xFFFF);
            cmd->w1 = ((env->unk60 & 0xFFFF) << 16) | (env->unk62 & 0xFFFF);
        }
        {
            EnvAcmd *cmd;

            cmd = ptr++;
            cmd->w0 = 0x09040000 | (env->unk6E & 0xFFFF);
            cmd->w1 = ((env->unk6C & 0xFFFF) << 16) | (env->unk6A & 0xFFFF);
        }
        {
            EnvAcmd *cmd;

            cmd = ptr++;
            cmd->w0 = 0x09000000 | (env->unk68 & 0xFFFF);
            cmd->w1 = ((env->unk66 & 0xFFFF) << 16) | (env->unk64 & 0xFFFF);
        }
        {
            EnvAcmd *cmd;

            cmd = ptr++;
            cmd->w0 = 0x03010000 | (env->unk5E & 0xFFFF);
            cmd->w1 = osVirtualToPhysical(env->unk54);
        }
    } else {
        EnvAcmd *cmd;

        cmd = ptr++;
        cmd->w0 = 0x03000000;
        cmd->w1 = osVirtualToPhysical(env->unk54);
    }
    *arg1 += 0x170;
    env->unk70 += 0xB8;
    return ptr;
}

s16 _getRate(f32 arg0, f32 arg1, s32 arg2, s16 *arg3) {
    s16 spE;
    s16 spC;
    f32 sp8;
    f32 sp4;
    f32 sp0;

    if (arg2 == 0) {
        if (arg0 <= arg1) {
            *(u16 *)arg3 = 0xFFFF;
            return 0x7FFF;
        } else {
            *arg3 = 0;
            return -0x8000;
        }
    }
    sp8 = 1.0f / (f32)arg2;
    if (arg1 < 1.0f) {
        arg1 = 1.0f;
    }
    if (arg0 <= 0.0f) {
        arg0 = 1.0f;
    }
    sp4 = (arg1 - arg0) * sp8 * 8.0f;
    spE = (s16)(s32)sp4;
    sp0 = sp4 - (f32)spE;
    spE -= 1;
    sp0 += 1.0f;
    spC = (s16)(s32)sp0;
    spE += spC;
    sp0 -= (f32)spC;
    *arg3 = (s16)(u32)(65535.0f * sp0);
    return spE;
}


s16 _getVol(s16 arg0, s32 arg1, s16 arg2, u16 arg3) {
    s32 sp4;

    arg1 >>= 3;
    if (arg1 == 0) {
        return arg0;
    }
    sp4 = arg3 * arg1;
    sp4 = sp4 >> 0x10;
    sp4 += arg2 * arg1;
    arg0 += sp4;
    return arg0;
}

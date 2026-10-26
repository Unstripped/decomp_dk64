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

  


typedef struct EnvAcmd EnvAcmd;

extern s16 D_80756490[];
extern s16 D_8075658E[];
extern EnvAcmd *_pullSubFrame(EnvMixerEnv *, s16 *, s16 *, s32, EnvAcmd *);
extern s16 _getVol(s16, s32, s16, u16);
extern s32 n_alEnvmixerParam(EnvMixerEnv *, s32, void *);

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

s32 n_alEnvmixerPull(void *arg0, s32 arg1, s32 arg2) {
    s32 sp54;
    EnvMixerPullView *sp50;
    s16 sp4E;
    s32 sp48;
    s32 sp44;
    s32 sp40;
    s16 sp3E;
    s32 sp38;
    EnvNode *sp34;
    s32 sp30;
    EnvNode *sp2C;
    s32 sp28;
    EnvNode *sp24;
    EnvNode *sp20;

    sp54 = arg2;
    sp50 = arg0;
    sp44 = arg1;
    sp3E = 0;
    sp30 = 0xB8;
    sp4E = 0;
    while (sp50->unk7C != NULL) {
        sp48 = sp44;
        sp44 = sp50->unk7C->unk4;
        sp40 = ((sp44 - sp48 + 0xB7) / 184) * 0xB8;
        if (sp40 == 0) {
            sp44 = sp48;
        }
        if (sp40 > sp30) {
            break;
        }
        switch (sp50->unk7C->type) {
        case 13:
            sp2C = sp50->unk7C;
            if (sp2C->unkA != 0) {
                sp50->unk48 = 1;
            }
            _decodeChunk(sp50, 5, sp2C->unk20);
            sp50->unk84 = 1;
            sp50->unk78 = 1;
            sp50->unk70 = 0;
            sp50->unk74 = ((sp2C->unk1C + 0xB7) / 184) * 0xB8;
            sp28 = (sp2C->unk10 + sp2C->unk10) / 2;
            sp50->unk5A = sp28;
            sp50->unk58 = sp2C->unk12;
            sp50->unk60 = (D_80756490[sp2C->unk13 & 0x7F] & 0xFFFE) | ((s32)sp2C->unk13 >> 7);
            if (D_807FF0F0 == 0) {
                sp50->unk60 &= 0xFFFE;
            }
            sp50->unk62 = D_8075658E[-(sp2C->unk13 & 0x7F)] & 0xFFFE;
            if (D_807FF0F2 != 0) {
                sp50->unk58 = (sp50->unk58 >> 1) + 0x20;
            } else if (D_807FF0F1 != 0) {
                sp50->unk58 = 0x40;
            }
            if (sp2C->unk1C != 0) {
                sp50->unk5C = 1;
                sp50->unk5E = 1;
            } else {
                sp50->unk5C = (D_80756490[sp50->unk58] * sp50->unk5A) >> 15;
                sp50->unk5E = (D_8075658E[-sp50->unk58] * sp50->unk5A) >> 15;
            }
            sp50->unk44 = sp2C->data.f;
            sp50->unk92 = sp2C->unk15;
            sp50->unk90 = sp2C->unk18;
            sp50->unkB8 = 1;
            sp50->unk8C = sp2C->unk14;
            break;
        case 11:
        case 12:
        case 16:
            sp54 = _pullSubFrame((EnvMixerEnv *)sp50, &sp4E, &sp3E, sp40, (EnvAcmd *)sp54);
            if (sp50->unk70 >= sp50->unk74) {
                sp50->unk68 = (D_80756490[sp50->unk58] * sp50->unk5A) >> 15;
                sp50->unk6E = (D_8075658E[-sp50->unk58] * sp50->unk5A) >> 15;
                sp50->unk70 = sp50->unk74;
                sp50->unk5C = sp50->unk68;
                sp50->unk5E = sp50->unk6E;
            } else {
                sp50->unk5C = _getVol(sp50->unk5C, sp50->unk70, sp50->unk66, sp50->unk64);
                sp50->unk5E = _getVol(sp50->unk5E, sp50->unk70, sp50->unk6C, sp50->unk6A);
            }
            if (sp50->unk5C == 0) {
                sp50->unk5C = 1;
            }
            if (sp50->unk5E == 0) {
                sp50->unk5E = 1;
            }
            if (sp50->unk7C->type == 0xC) {
                if (D_807FF0F2 != 0) {
                    sp50->unk58 = (sp50->unk7C->data.s.s1 >> 1) + 0x20;
                } else if (D_807FF0F1 != 0) {
                    sp50->unk58 = 0x40;
                } else {
                    sp50->unk58 = sp50->unk7C->data.i;
                }
            }
            if (sp50->unk7C->type == 0xB) {
                sp50->unk70 = 0;
                sp38 = sp50->unk7C->data.i;
                sp38 = (sp38 + sp38) / 2;
                sp50->unk5A = sp38;
                sp50->unk74 = ((*(s32 *)&sp50->unk7C->unk10 + 0xB7) / 184) * 0xB8;
            }
            if (sp50->unk7C->type == 0x10) {
                if (((((sp50->unk60 ^ sp50->unk62) & 1) ^ ((sp50->unk7C->data.i + 1) >> 7)) != 0) && (D_807FF0F0 != 0)) {
                    if (sp50->unk58 >= 0x41) {
                        sp50->unk60 ^= 1;
                    } else {
                        sp50->unk62 ^= 1;
                    }
                }
                sp50->unk60 = (D_80756490[sp50->unk7C->data.i & 0x7F] & 0xFFFE) | (sp50->unk60 & 1);
                sp50->unk62 = (D_8075658E[-(sp50->unk7C->data.i & 0x7F)] & 0xFFFE) | (sp50->unk62 & 1);
            }
            sp50->unk78 = 1;
            break;
        case 14:
            sp24 = sp50->unk7C;
            if (sp24->unkA != 0) {
                sp50->unk48 = 1;
            }
            _decodeChunk(sp50, 5, sp24->data.ptr);
            sp50->unk84 = 1;
            break;
        case 15:
            sp54 = _pullSubFrame((EnvMixerEnv *)sp50, &sp4E, &sp3E, sp40, (EnvAcmd *)sp54);
            n_alEnvmixerParam(sp50, 4, 0);
            break;
        case 0:
            sp20 = sp50->unk7C;
            ((EnvPVoice *)sp20->data.ptr)->unk88 = 0;
            _n_freePVoice(sp20->data.ptr);
            break;
        case 7:
            sp54 = _pullSubFrame((EnvMixerEnv *)sp50, &sp4E, &sp3E, sp40, (EnvAcmd *)sp54);
            sp50->unk44 = sp50->unk7C->data.f;
            break;
        case 8:
            sp54 = _pullSubFrame((EnvMixerEnv *)sp50, &sp4E, &sp3E, sp40, (EnvAcmd *)sp54);
            sp50->unk48 = 1;
            break;
        case 5:
            sp54 = _pullSubFrame((EnvMixerEnv *)sp50, &sp4E, &sp3E, sp40, (EnvAcmd *)sp54);
            _decodeChunk(sp50, 5, sp50->unk7C->data.ptr);
            break;
        default:
            sp54 = _pullSubFrame((EnvMixerEnv *)sp50, &sp4E, &sp3E, sp40, (EnvAcmd *)sp54);
            n_alEnvmixerParam((EnvMixerEnv *)sp50, sp50->unk7C->type, sp50->unk7C->data.ptr);
            break;
        }
        sp3E += sp40 * 2;
        sp30 -= sp40;
        sp34 = sp50->unk7C;
        sp50->unk7C = sp50->unk7C->next;
        if (sp50->unk7C == NULL) {
            sp50->unk80 = 0;
        }
        __n_freeParam(sp34);
    }
    sp54 = _pullSubFrame((EnvMixerEnv *)sp50, &sp4E, &sp3E, sp30, (EnvAcmd *)sp54);
    if (sp50->unk70 > sp50->unk74) {
        sp50->unk70 = sp50->unk74;
    }
    return sp54;
}


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

struct EnvAcmd {
    u32 w0;
    u32 w1;
};

extern EnvAcmd *n_alResamplePull();
s16 _getRate(f32, f32, s32, s16 *);

EnvAcmd *_pullSubFrame(EnvMixerEnv *arg0, s16 *arg1, s16 *arg2, s32 arg3, EnvAcmd *arg4) {
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

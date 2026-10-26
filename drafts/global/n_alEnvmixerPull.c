// n_alEnvmixerPull (src/global/1435C0.c): stage 4: exact 4064-byte text size and 0x58 frame; early case-13 body matches through 0x3CC, remaining statement-shape and register differences
typedef struct EnvAcmd EnvAcmd;

extern s16 D_80756490[];
extern s16 D_8075658E[];
extern EnvAcmd *_pullSubFrame(EnvMixerEnv *, s16 *, s32, s32, EnvAcmd *);
extern s32 n_alEnvmixerParam(EnvMixerEnv *, s32, void *);
extern s16 _getVol(s16, s32, s16, u16);

/* Envmixer control list view. */
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
    u16 type;
    s16 unkA;
    EnvNodeData data;
    s16 unk10;
    u8 unk12;
    u8 unk13;
    u8 unk14;
    s8 unk15;
    u8 pad16[2];
    s32 unk18;
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
    if (sp50->unk7C != NULL) {
loop_1:
        sp48 = sp44;
        sp44 = sp50->unk7C->unk4;
        sp40 = ((sp44 - sp48 + 0xB7) / 184) * 0xB8;
        if (sp40 == 0) {
            sp44 = sp48;
        }
        if (sp40 > sp30) {
        } else {
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
                sp54 = _pullSubFrame((EnvMixerEnv *)sp50, &sp4E, sp3E, sp40, (EnvAcmd *)sp54);
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
                        sp50->unk58 = sp50->unk7C->data.s.s0;
                    }
                }
                if (sp50->unk7C->type == 0xB) {
                    sp50->unk70 = 0;
                    sp38 = sp50->unk7C->data.i;
                    sp38 = (sp38 + sp38) / 2;
                    sp50->unk5A = sp38;
                    sp50->unk74 = ((sp50->unk7C->unk10 + 0xB7) / 184) * 0xB8;
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
                sp54 = _pullSubFrame((EnvMixerEnv *)sp50, &sp4E, sp3E, sp40, (EnvAcmd *)sp54);
                n_alEnvmixerParam(sp50, 4, 0);
                break;
            case 0:
                sp20 = sp50->unk7C;
                ((EnvPVoice *)sp20->data.ptr)->unk88 = 0;
                _n_freePVoice(sp20->data.ptr);
                break;
            case 7:
                sp54 = _pullSubFrame((EnvMixerEnv *)sp50, &sp4E, sp3E, sp40, (EnvAcmd *)sp54);
                sp50->unk44 = sp50->unk7C->data.f;
                break;
            case 8:
                sp54 = _pullSubFrame((EnvMixerEnv *)sp50, &sp4E, sp3E, sp40, (EnvAcmd *)sp54);
                sp50->unk48 = 1;
                break;
            case 5:
                sp54 = _pullSubFrame((EnvMixerEnv *)sp50, &sp4E, sp3E, sp40, (EnvAcmd *)sp54);
                _decodeChunk(sp50, 5, sp50->unk7C->data.ptr);
                break;
            default:
                sp54 = _pullSubFrame((EnvMixerEnv *)sp50, &sp4E, sp3E, sp40, (EnvAcmd *)sp54);
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
            if (sp50->unk7C != NULL) {
                goto loop_1;
            }
        }
    }
    sp54 = _pullSubFrame((EnvMixerEnv *)sp50, &sp4E, sp3E, sp30, (EnvAcmd *)sp54);
    if (sp50->unk74 < sp50->unk70) {
        sp50->unk70 = sp50->unk74;
    }
    return sp54;
}

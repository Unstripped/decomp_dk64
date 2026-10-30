// func_806CA5F8 (src/global/CEAE0.c): stage 6, 9 diff lines (shape 1; regalloc only). Fixed vs old park: effectFreeAndUnlink ONE-arg; camProjectToScreen declared s32 (its real return type) - needed to get D_807FBB48 ptr v1; removed the two 'if (D_807FBB48 && D_807FBB48) {}' dead stmts; added dead 'if (D_807FBB40 && D_807FBB40) {}' as first statement (deadsweep). ONLY remaining: fx (LCA_P->unk254): target keeps it in a1 over arms/join test (lw a1; bnez a1; move a0,a1; reload lw a1 after create/free) and 'move s0,a1' in the delay slot of the join beqz (live range split, s0 only in body); ours s0 whole, no move. actorGetNodePos s32 (real return) breaks the file (another fn declares it void).
typedef struct LCA5F8Fx {
    /* 0x000 */ u8 pad0[0x340];
    /* 0x340 */ f32 unk340;
    /* 0x344 */ f32 unk344;
    /* 0x348 */ f32 unk348;
    /* 0x34C */ u8 pad34C[0x360 - 0x34C];
    /* 0x360 */ f32 unk360;
    /* 0x364 */ f32 unk364;
} LCA5F8Fx;

typedef struct LCA5F8P {
    /* 0x000 */ s16 unk0;
    /* 0x002 */ u8 pad2[0x8D - 2];
    /* 0x08D */ u8 unk8D;
    /* 0x08E */ u8 pad8E[0xCA - 0x8E];
    /* 0x0CA */ u8 unkCA;
    /* 0x0CB */ u8 padCB[0xD4 - 0xCB];
    /* 0x0D4 */ s16 unkD4;
    /* 0x0D6 */ s16 unkD6;
    /* 0x0D8 */ u8 padD8[0xE8 - 0xD8];
    /* 0x0E8 */ u8 unkE8;
    /* 0x0E9 */ u8 padE9[0xFC - 0xE9];
    /* 0x0FC */ s32 unkFC;
    /* 0x100 */ s32 unk100;
    /* 0x104 */ u8 pad104[0x10E - 0x104];
    /* 0x10E */ s16 unk10E;
    /* 0x110 */ s16 unk110;
    /* 0x112 */ s16 unk112;
    /* 0x114 */ u8 pad114[0x120 - 0x114];
    /* 0x120 */ s32 unk120;
    /* 0x124 */ u8 pad124[0x1A4 - 0x124];
    /* 0x1A4 */ u8 unk1A4;
    /* 0x1A5 */ u8 pad1A5[0x1C0 - 0x1A5];
    /* 0x1C0 */ f32 unk1C0;
    /* 0x1C4 */ u8 pad1C4[0x1CC - 0x1C4];
    /* 0x1CC */ f32 unk1CC;
    /* 0x1D0 */ u8 pad1D0[0x1F0 - 0x1D0];
    /* 0x1F0 */ s32 unk1F0;
    /* 0x1F4 */ u8 pad1F4[4];
    /* 0x1F8 */ s32 unk1F8;
    /* 0x1FC */ u8 pad1FC[0x244 - 0x1FC];
    /* 0x244 */ u8 unk244;
    /* 0x245 */ u8 unk245;
    /* 0x246 */ u8 pad246[2];
    /* 0x248 */ s8 unk248;
    /* 0x249 */ s8 unk249;
    /* 0x24A */ u8 unk24A;
    /* 0x24B */ u8 pad24B[0x250 - 0x24B];
    /* 0x250 */ s32 unk250;
    /* 0x254 */ LCA5F8Fx *unk254;
    /* 0x258 */ u8 pad258[0x268 - 0x258];
    /* 0x268 */ u8 unk268;
} LCA5F8P;

typedef struct LCA5F8Slot {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ Actor *unk4;
    /* 0x008 */ u8 pad8[0x210 - 8];
    /* 0x210 */ f32 unk210;
    /* 0x214 */ f32 unk214;
    /* 0x218 */ f32 unk218;
    /* 0x21C */ u8 pad21C[0x27C - 0x21C];
    /* 0x27C */ f32 unk27C;
    /* 0x280 */ u8 pad280[0x28C - 0x280];
    /* 0x28C */ f32 unk28C;
    /* 0x290 */ u8 pad290[0x2B4 - 0x290];
    /* 0x2B4 */ f32 unk2B4;
    /* 0x2B8 */ f32 unk2B8;
    /* 0x2BC */ f32 unk2BC;
    /* 0x2C0 */ u8 pad2C0[0x2F0 - 0x2C0];
} LCA5F8Slot;

typedef struct LCA5F8Pad {
    /* 0x00 */ u8 pad0[0x2A];
    /* 0x2A */ u16 unk2A;
    /* 0x2C */ u8 pad2C[2];
    /* 0x2E */ s8 unk2E;
    /* 0x2F */ s8 unk2F;
    /* 0x30 */ u8 pad30[4];
} LCA5F8Pad;

typedef struct LCA5F8Fn {
    /* 0x0 */ void (*fn)(void);
    /* 0x4 */ s32 pad4;
} LCA5F8Fn;

#define LCA_P ((LCA5F8P *)D_807FD580)
#define LCA_SLOT(i) (((LCA5F8Slot *)D_807FC924)[i])

extern LCA5F8Fn D_80750B50[];
extern s32 D_8076A068;
extern s32 D_8076A090;
extern s32 D_8076A094;
extern s32 D_8076A098;
extern s32 D_807552E4;
extern s32 D_807FBB60;
extern s32 D_8076A0A8;
extern u8 D_80770561;
extern u8 D_807463B8;
extern u8 D_807FBB8C;
extern s16 D_807F5FE4;
extern s16 D_807F5FE6;
extern s16 D_807F5FE8;
extern s16 D_807F5FEA;
extern s32 D_80720020;

void func_806CB53C();
void func_806CBE44(void);
void func_806CF580(void);
void func_806CF9CC(void);
void sfxStopChannel(s32, s32);
void func_806F4D70(u8, f32, f32, f32, f32);
void proxPathUpdateAllPlayers(void);
s32 collisionGetHitStatus();
u8 func_80666A94();
u8 func_80666AA0();
u8 func_80666AAC();
u8 func_80666AB8();
void func_80026D40(void *, u8);
void func_805FF188(s32, s32);
void func_805FF1B0(u8);
void func_805FF2F4();
void healthRefill(u8);
void func_8071495C();
void func_807149C8(s32, s32, s32, s32);
void effectFreeAndUnlink(void *);
s32 camProjectToScreen(f32, f32, f32, f32 *, f32 *, f32 *, f32, s32);
s32 playerStateQueueCallback(s32, Actor *, u8);
void actorGetNodePos(void *, s32, f32 *, f32 *, f32 *);
f32 sqrtf(f32);
void func_807149FC(s32);
void func_80714998(s32);
s32 func_80714CC0(void *, f32, f32, f32, f32);

void func_806CA5F8(s32 arg0) {
    f32 dy;
    f32 sp70;
    f32 sp6C;
    u8 sp6B;
    u8 sp6A;
    u8 sp69;
    u8 sp68;
    Actor *sp64;
    f32 dz;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 dx;
    f32 sp4C;
    f32 sp48;
    LCA5F8Fx *fx;
    s16 flags;
    if (D_807FBB40 && D_807FBB40) {}  // FAKE: steers uopt candidate colouring (D_807FBB48 pointer v1)

    sp64 = D_807FBB40;
    D_807FD580 = D_807FBB40->unk174;
    if (D_807463B8 == 0) {
        D_807FBB40->unk60 |= 0x400000;
    } else {
        D_807FBB40->unk60 &= 0xFFBFFFFF;
    }
    D_807FBB40->unk60 &= 0xF7FFFFFF;
    LCA_SLOT(D_807FC929).unk28C = LCA_SLOT(D_807FC929).unk27C;
    if (D_807FBB40->unk64 & 0x100) {
        LCA_P->unk120 = D_8076A068;
    }
    if (LCA_P->unk1CC == LCA_P->unk1C0 && D_807FBB40->unk154 != 0x54) {
        if (D_807FBB40->unk58 == 4) {
            D_807FBB40->unk15E = 0xB;
        } else {
            D_807FBB40->unk15E = D_807FBB40->unk140->unkC * 0.15 * 0.5;
        }
    }
    func_806CBE44();
    flags = D_80750B54[D_807FBB40->unk154][0];
    if (flags & 8) {
        D_807FBB40->unk68 |= 2;
    } else {
        D_807FBB40->unk68 &= 0xFFFD;
    }
    if ((flags & 0x20) && LCA_P->unkFC == 0 && D_807FBB40->unk58 != 8 && D_807FBB40->unk58 != 9) {
        D_807FBB40->unk68 |= 0x10;
    } else {
        D_807FBB40->unk68 &= 0xFFEF;
        D_807FBB40->unk60 &= ~0x800;
    }
    if (LCA_P->unkFC != 0) {
        LCA_P->unkFC = LCA_P->unkFC - 1;
    }
    if (flags & 0x40) {
        D_807FBB40->unk60 |= 0x4000;
    } else {
        D_807FBB40->unk60 &= ~0x4000;
    }
    if ((flags & 0x80) && LCA_P->unk100 == 0 && D_807FBB40->unk58 != 8 && D_807FBB40->unk58 != 9) {
        D_807FBB40->unk68 |= 0x20;
    } else {
        D_807FBB40->unk68 &= 0xFFDF;
    }
    if (LCA_P->unk100 != 0) {
        LCA_P->unk100 = LCA_P->unk100 - 1;
    }
    if (LCA_P->unk245 != 0) {
        LCA_P->unk245 = LCA_P->unk245 - 1;
    }
    func_806CB53C();
    func_806CA2E4();
    func_806CA540();
    if (D_80770561 == 0x6B && D_807FBB40->unk154 != 0x6E) {
        sfxStopChannel(0x6B, 0);
    }
    if (LCA_P->unkCA != 0) {
        LCA_P->unkCA = LCA_P->unkCA - 1;
    }
    if (D_807FBB40->unk68 & 0x20) {
        proxPathUpdateAllPlayers();
    }
    func_806F4D70(D_807FC929, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, D_807FBB40->unk4->unk38 / 0.15 * 20.0);
    if (D_807FC928 == 1) {
        if (D_807FBB40->unk64 & 0x1000) {
            D_807FBB40->unk64 |= 0x200;
        }
    }
    D_807FBB40->unk64 &= ~0x1000;
    D_80750B50[D_807FBB40->unk154].fn();
    LCA_P->unk8D = collisionGetHitStatus();
    if (D_807FC928 == 1) {
        D_807FBB40->unk64 &= ~0x200;
    }
    if ((D_807FD580->unk1F0 & 0x01000000) && D_807FBB8C != 0 && D_807FBB40->unk154 != 0x47) {
        playerStateQueueCallback(3, NULL, D_807FC929);
    }
    sp6B = func_80666AA0();
    sp6A = func_80666A94();
    sp69 = func_80666AAC();
    sp68 = func_80666AB8();
    if (D_807FBB40->unk68 & 0x10) {
        func_806CF9CC();
    }
    LCA_P->unkE8 = 0;
    D_807FD580->unk1F0 &= 0xBFFFFFFF;
    func_806CF580();
    if (!D_8076A0A8 && !D_8076A0A8) {
    }
    LCA_P->unk0 = D_807FBB48->unk154;
    if (D_807FC928 >= 2) {
        if (D_807FBB40->unk6A & 1) {
            if (LCA_P->unk24A != 0) {
                LCA_P->unk24A = LCA_P->unk24A - 1;
            } else {
                LCA_P->unk248 = -1;
                LCA_P->unk249 = 0;
            }
        }
        func_806CA26C();
        {
            s8 v = LCA_P->unk248;
            if (v >= 0 && (u32)v != LCA_P->unk1A4) {
                sp64 = LCA_SLOT(v).unk4;
            } else {
                s8 w = LCA_P->unk249;
                if (w > 0) {
                    sp64 = spawnNodeActivate(w, 0);
                }
            }
        }
        if (D_807552E4 == 0) {
            if (D_807FBB48->unk154 == 0x3C) {
                if (LCA_P->unk250 != 0) {
                    LCA_P->unk250 = LCA_P->unk250 - 1;
                }
                fx = LCA_P->unk254;
                if (fx == NULL) {
                    func_807149FC(-1);
                    func_80714998(0);
                    func_807149C8(0xFF, 0xFF, 0xFF, 0x78);
                    func_8071495C();
                    LCA_P->unk254 = (LCA5F8Fx *)func_80714CC0(&D_80720020, 0.7f, D_807FBB48->unk7C, D_807FBB48->unk80, D_807FBB48->unk84);
                    if (D_807FC924 && D_807FC924) {
                    }
                    fx = LCA_P->unk254;
                }
            } else {
                if (LCA_P->unk250 < 0x78) {
                    LCA_P->unk250 = LCA_P->unk250 + 1;
                }
                fx = LCA_P->unk254;
                if (fx != NULL) {
                    LCA_P->unk254 = NULL;
                    effectFreeAndUnlink(fx);
                    fx = LCA_P->unk254;
                }
            }
            if (fx != NULL) {
                actorGetNodePos(D_807FBB48, 1, &sp5C, &sp58, &sp54);
                camProjectToScreen(sp5C, sp58, sp54, &sp4C, &sp48, NULL, 1.0f, 0);
                fx->unk340 = sp4C * 4.0f;
                fx->unk344 = sp48 * 4.0f;
                fx->unk348 = 5.0f;
                dz = LCA_SLOT(0).unk218 - sp54;
                dx = LCA_SLOT(0).unk210 - sp5C;
                dy = LCA_SLOT(0).unk214 - sp58;
                dz = sqrtf(dz * dz + (dx * dx + dy * dy));
                fx->unk360 = D_807FBB40->unk4->unk34 * (1000.0f / dz) * 6.666666666666667 * 0.7 * 0.008333334f * (f32)LCA_P->unk250;
                fx->unk364 = fx->unk360;
            }
        }
    }
    if (LCA_P->unkD4 != 0) {
        LCA_P->unkD4 = LCA_P->unkD4 - 1;
    }
    if (sp6A != 0) {
        playerStateQueueCallback(0x3F, sp64, D_807FC929);
    }
    if (sp6B == 1) {
        goto case1;
    }
    if (sp6B == 2) {
        goto case2;
    }
    LCA_P->unkD6 = 0;
    goto done;
case1:
    if (LCA_P->unk1F0 & 0x10) {
        LCA_P->unkD6 = 0;
    } else {
        LCA_P->unkD6 = LCA_P->unkD6 + 1;
        playerStateQueueCallback(0x2E, sp64, D_807FC929);
        if (D_807FBB40->unk154 != 0x36 && D_807FBB40->unk154 != 0x3B && LCA_P->unkD4 == 0) {
            s32 snd = 0x2C0;
            if (D_8076A0A8 == 0x30) {
                snd = 0x3B0;
            }
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, snd, 0xFF, 0x7F, 0);
        }
    }
    goto done;
case2:
    LCA_P->unk1F0 |= 0x1000;
    if (!(LCA_P->unk1F0 & 0x10)) {
        if (D_807FBB40->unk154 != 0x36 && D_807FBB40->unk154 != 0x3B && LCA_P->unkD4 == 0) {
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x2C0, 0xFF, 0x7F, 0);
        }
        if (D_8076A0A8 == 0x53 || D_8076A0A8 == 0xC5) {
        playerStateQueueCallback(0x40, sp64, D_807FC929);
    } else {
        playerStateQueueCallback(0x30, sp64, D_807FC929);
        }
    }
done:
    if (sp69 != 0) {
        playerStateQueueCallback(0, sp64, D_807FC929);
        if (LCA_P->unkD4 == 0) {
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x2C0, 0xFF, 0x7F, 0);
        }
    }
    actorGetNodePos(D_807FBB48, 6, &LCA_SLOT(D_807FC929).unk2B4, &LCA_SLOT(D_807FC929).unk2B8, &LCA_SLOT(D_807FC929).unk2BC);
    camProjectToScreen(D_807FBB48->unk7C, LCA_SLOT(D_807FC929).unk2B8, D_807FBB48->unk84, &sp70, &sp6C, NULL, 1.0f, D_807FC929);
    LCA_P->unk10E = sp70;
    LCA_P->unk110 = sp6C;
    camProjectToScreen(D_807FBB48->unk7C, D_807FBB48->unk80, D_807FBB48->unk84, &sp70, &sp6C, NULL, 1.0f, D_807FC929);
    LCA_P->unk112 = sp6C;
    LCA_P->unk1F8 = LCA_P->unk1F0;
    if (LCA_P->unk268 != 0) {
        LCA_P->unk268 = LCA_P->unk268 - 1;
    }
    if ((D_807FBB40->unk7C < (f32)D_807F5FE4 || D_807FBB40->unk84 < (f32)D_807F5FE6 || (f32)D_807F5FE8 < D_807FBB40->unk7C || (f32)D_807F5FEA < D_807FBB40->unk84 || sp68 != 0) && LCA_P->unk244 == 0 && (u32)D_8076A064 >= 0x65 && !(D_807FBB64 & 0x4000) && D_8076A0A8 != 0xE) {
        if (D_807FC928 == 1) {
            if (flagGet(0x186, 0) == 0) {
                func_805FF188(0xB0, 1);
            }
            if (!D_807FC929 && !D_807FC929) {
            }
            healthRefill(D_807FC929);
            func_805FF1B0(D_807FC929);
            LCA_P->unk244 = 1;
        } else {
            func_80026D40(D_807FBB40, D_807FC929);
        }
    }
    if (D_807FC929 == 0) {
        switch (D_8076A0A8) {
            case 0x7:
            case 0x1A:
            case 0x1E:
            case 0x22:
            case 0x26:
            case 0x30:
            case 0x48:
            case 0x57:
                if (D_8076A094 >= 0x5DD && LCA_P->unk244 == 0) {
                    func_805FF2F4();
                    LCA_P->unk244 = 1;
                }
                if (D_8076A098 >= 0x5DD && !(D_807FBB60 & 2) && LCA_P->unk244 == 0) {
                    func_805FF2F4();
                    LCA_P->unk244 = 1;
                }
                if ((D_807FBB40->unk7C != D_807FBB40->unk88 || D_807FBB40->unk80 != D_807FBB40->unk8C || D_807FBB40->unk84 != D_807FBB40->unk90 || D_807FD610[D_807FC929].unk2A != 0 || D_807FD610[D_807FC929].unk2E != 0 || D_807FD610[D_807FC929].unk2F != 0) && !(D_807FBB60 & 2)) {
                    if (++D_8076A090 == 0x69780) {
                        func_805FF2F4();
                        LCA_P->unk244 = 1;
                    }
                }
                break;
        }
    }
}

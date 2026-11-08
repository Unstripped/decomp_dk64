#include "common.h"
#include "actor.h"

extern Actor *gCurrentActor;
extern Actor *gActivePlayerActor;
extern ActorGlobalState gActorGlobalState;
extern u8 gPlayerCount;
extern u8 gCurrentPlayerIndex;
extern PlayerState *gActivePlayerState;
extern s16 gCurrentCharacterIndex;
extern u16 D_807FD63C;

void playerUpdateCommon(s32);
void func_806F3190(Actor *, s32);
void actorOrNodeFlags(Actor *, s32, s32);

void playerUpdateSoundEffect0(void) {
    playerUpdateCommon(0);
    func_806F3190(gCurrentActor, 0);
}

void playerUpdateSoundEffect2(void) {
    playerUpdateCommon(0);
    func_806F3190(gCurrentActor, 2);
}

void playerUpdateSoundEffect3(void) {
    playerUpdateCommon(0);
    func_806F3190(gCurrentActor, 3);
}

void playerUpdateSoundEffect4(void) {
    playerUpdateCommon(0);
    func_806F3190(gCurrentActor, 4);
}

void playerUpdateSoundEffect6(void) {
    playerUpdateCommon(0);
    func_806F3190(gCurrentActor, 6);
}

void playerUpdateSoundEffect1(void) {
    playerUpdateCommon(0);
    func_806F3190(gCurrentActor, 1);
}

void playerUpdateSoundEffect7(void) {
    actorOrNodeFlags(gCurrentActor, 3, 8);
    playerUpdateCommon(0);
    func_806F3190(gCurrentActor, 7);
}

void playerUpdateSoundEffect5(void) {
    playerUpdateCommon(0);
    func_806F3190(gCurrentActor, 5);
}

extern s16 gPlayerStateFlags[][4];
void func_806EAB44(Actor *, u8);

void func_806E9964(PlayerState *);

void playerCheckAndResetCarriedActor(Actor *arg0) {
    u8 temp_v0 = arg0->state;
    s16 flags = gPlayerStateFlags[temp_v0][0];

    if (flags & 0x200) {
        func_806EAB44(arg0, temp_v0 != 2);
    } else if (flags & 0x100) {
        func_806E9964(gActivePlayerState);
    }
}

Actor *actorResolveKillCreditOwner(Actor *arg0) {
    Actor *temp_v1 = arg0;

    if (arg0 == NULL) {
        return arg0;
    }
    switch (arg0->collisionFlags) {
        case 4:
            arg0 = arg0->parentActor;
            break;
        case 8:
            arg0 = arg0->parentActor;
            break;
    }
    if (arg0 != NULL && (arg0->collisionFlags == 1 || arg0->collisionFlags == 2)) {
        return arg0;
    }
    return temp_v1;
}

typedef struct G02ModelRef {
    /* 0x00 */ u8 pad0[0x10];
    /* 0x10 */ s16 unk10;
} G02ModelRef;

typedef struct G02PlayerState {
    /* 0x000 */ u8 pad0[0x2C];
    /* 0x02C */ f32 unk2C;
    /* 0x030 */ f32 unk30;
    /* 0x034 */ u8 pad34[0x48 - 0x34];
    /* 0x048 */ s16 unk48;
    /* 0x04A */ u8 pad4A[0xC2 - 0x4A];
    /* 0x0C2 */ s16 unkC2;
    /* 0x0C4 */ u8 padC4[4];
    /* 0x0C8 */ s16 unkC8;
    /* 0x0CA */ u8 padCA[0x1A4 - 0xCA];
    /* 0x1A4 */ u8 unk1A4;
    /* 0x1A5 */ u8 pad1A5[0x246 - 0x1A5];
    /* 0x246 */ s8 unk246;
    /* 0x247 */ s8 unk247;
    /* 0x248 */ s8 unk248;
    /* 0x249 */ u8 unk249;
    /* 0x24A */ u8 unk24A;
    /* 0x24B */ u8 pad24B;
    /* 0x24C */ u16 unk24C;
    /* 0x24E */ u16 unk24E;
} G02PlayerState;

#define G02_P ((G02PlayerState *)gActivePlayerState)
#define G02_ACTOR_P(a) ((G02PlayerState *)(a)->customState)
#define G02_MODEL(a) (*(G02ModelRef **)(a)->sub4)

void sfxStopSlotSound(Actor *, s32);
s8 spawnNodeIdForActor(Actor *);

void playerSetRecentAttacker(Actor *arg0, G02PlayerState *arg1) {
    s32 flag = 0;
    G02PlayerState *p;

    if (arg0 == NULL) {
        flag = 1;
    } else if (arg0->collisionFlags & 1) {
        p = G02_ACTOR_P(arg0);
        arg1->unk248 = p->unk1A4;
        arg1->unk249 = 0;
    } else if (arg0->collisionFlags & 2) {
        arg1->unk248 = -1;
        arg1->unk249 = spawnNodeIdForActor(arg0);
    } else {
        flag = 1;
    }
    if (flag != 0) {
        G02_P->unk246 = 0;
        G02_P->unk247 = -1;
    }
    arg1->unk24A = 5;
}

void playerRecordHitSource(Actor *arg0, Actor *arg1, s32 arg2) {
    G02PlayerState *temp_v1 = G02_ACTOR_P(arg0);
    G02PlayerState *p;
    s32 bad;
    s32 ok;

    ok = 0;
    bad = 0;
    if (arg1 == NULL) {
        bad = 1;
    } else if (arg1->collisionFlags == 1) {
        ok = 1;
        p = G02_ACTOR_P(arg1);
        temp_v1->unk247 = p->unk1A4;
        temp_v1->unk246 = 0;
    } else if (arg1->collisionFlags == 2) {
        temp_v1->unk246 = spawnNodeIdForActor(arg1);
        ok = 1;
        temp_v1->unk247 = -1;
    } else {
        bad = 1;
    }
    if (bad != 0) {
        temp_v1->unk246 = 0;
        temp_v1->unk247 = -1;
    }
    if (ok != 0) {
        temp_v1->unk24C = G02_MODEL(arg1)->unk10;
        temp_v1->unk24E = arg2;
    }
}

typedef struct G03PlayerSlot {
    /* 0x000 */ u8 pad0[0x2C0];
    /* 0x2C0 */ u8 unk2C0;
    /* 0x2C1 */ u8 pad2C1[0x2F];
} G03PlayerSlot;

extern G03PlayerSlot *gPlayerSlots;
s32 playerHitSourceIsStale(s32);

typedef struct G02PlayerSlot {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ Actor *unk4;
    /* 0x8 */ u8 pad8[0x2E8];
} G02PlayerSlot;

Actor *spawnNodeActivate(s32, s32);

s32 playerHitSourceIsStale(s32 arg0) {
    s8 idx = G02_P->unk247;
    s32 ret = 1;
    Actor *actor = NULL;

    if (idx >= 0) {
        actor = ((G02PlayerSlot *)gPlayerSlots)[idx].unk4;
    } else {
        s8 temp = G02_P->unk246;

        if (temp > 0) {
            actor = spawnNodeActivate(temp, 0);
        }
    }
    if (actor != NULL && G02_MODEL(actor)->unk10 == *(u16 *)((u8 *)gActivePlayerState + 0x24C) && (s32)G02_P->unk24E >= arg0) {
        ret = 0;
    }
    return ret;
}

void playerClearStaleHitSource(void) {
    if (playerHitSourceIsStale(-1) != 0) {
        G02_P->unk247 = -1;
        G02_P->unk246 = 0;
    }
}

void playerClearCarriedItemState(void) {
    G02_P->unkC8 = -1;
    sfxStopSlotSound(gCurrentActor, 1);
}

typedef struct G02ActorView {
    /* 0x00 */ u8 pad0[0x6A];
    /* 0x6A */ u16 unk6A;
    /* 0x6C */ u16 unk6C;
    /* 0x6E */ s16 unk6E;
    /* 0x70 */ u8 pad70[8];
    /* 0x78 */ u8 unk78;
    /* 0x79 */ u8 pad79[0xB8 - 0x79];
    /* 0xB8 */ f32 unkB8;
    /* 0xBC */ u8 padBC[0xC8 - 0xBC];
    /* 0xC8 */ f32 unkC8;
    /* 0xCC */ u8 padCC[0xD8 - 0xCC];
    /* 0xD8 */ s16 unkD8;
    /* 0xDA */ u8 padDA[0xDE - 0xDA];
    /* 0xDE */ s16 unkDE;
    /* 0xE0 */ f32 unkE0;
    /* 0xE4 */ u8 padE4[0xE6 - 0xE4];
    /* 0xE6 */ s16 unkE6;
    /* 0xE8 */ u8 padE8[0xEE - 0xE8];
    /* 0xEE */ s16 unkEE;
    /* 0xF0 */ u8 padF0[0x154 - 0xF0];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
} G02ActorView;

#define G02_A ((G02ActorView *)gCurrentActor)

extern s32 gFrameCounter;
extern s32 gGlobalOverlayFlags;
extern u16 D_807FD63A[][0x1A];
s32 flagGet(s32, s32);
s32 slotQueueGetValue(s32, u8);
void effectSpawnBurst(s32);
void sfxPlayActorSound(Actor *, s32, s32, s32, s32, s32, f32, s32);
void slotQueueUpdate(s32, s32, s32);
s32 slotQueueGetCountStep(s32);
void slotQueueAddValue(s32, u8, s16);
void actorScriptStartByIndex(Actor *, s32);
s32 sfxPlayFromActorWithAltitudeCheck(Actor *, s32, s32, s32, s32);

void playerCheckAndClearCarriedItem(void) {
    if (G02_P->unkC8 != -1 && (flagGet(0x179, 0) == 0 || G02_A->unkE0 != 0.0f || (gGlobalOverlayFlags & 0x800000) || slotQueueGetValue(5, G02_P->unk1A4) == 0)) {
        playerClearCarriedItemState();
        G02_P->unkC8 = -1;
        return;
    }
    if (G02_P->unkC8 != -1) {
        if (D_807FD63A[gCurrentPlayerIndex][0] & 0x4000) {
            if (G02_P->unkC8 > 0) {
                if (G02_P->unkC8 < 0x1E && !(gFrameCounter & 3)) {
                    effectSpawnBurst(0);
                }
                G02_P->unkC8 = G02_P->unkC8 - 1;
                if (G02_P->unkC8 == 0x1E) {
                    sfxPlayActorSound(gCurrentActor, 0x104, 0x3C, 1, 1, 0xFF, 1.0f, 0);
                }
            } else if (!(gFrameCounter & 1)) {
                effectSpawnBurst(1);
            }
        } else {
            if (G02_P->unkC8 == 0 && (G02_A->unk6A & 1)) {
                G02_A->unk154 = 0x2D;
                G02_A->unk155 = 0;
                slotQueueUpdate(5, 0, 0);
                slotQueueAddValue(5, G02_P->unk1A4, -slotQueueGetCountStep(5));
                actorScriptStartByIndex(gCurrentActor, 0x42);
                sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0xF2, 0xFF, 0x7F, 0);
                G02_A->unkB8 = 0.0f;
            }
            playerClearCarriedItemState();
        }
    }
}

void func_806CA540(void) {
    if ((G02_A->unk6A & 0x221) == 1) {
        if (G02_A->unkE0 != 0.0f) {
            if (!(G02_A->unk6C & 1) || G02_A->unkDE < 0x226 || (G02_A->unk78 == 0xC && G02_A->unkB8 > 40.0f)) {
                G02_P->unkC2 = 0x32;
            }
            G02_P->unkC2 = G02_P->unkC2 + 1;
        } else {
            G02_P->unkC2 = 0;
        }
    }
}

typedef struct PadInputState {
    /* 0x00 */ u8 pad0[0x2A];
    /* 0x2A */ u16 unk2A;
    /* 0x2C */ u16 unk2C;
    /* 0x2E */ s8 unk2E;
    /* 0x2F */ s8 unk2F;
    /* 0x30 */ u8 pad30[4];
} PadInputState;

extern PadInputState gPlayerPadState[];
typedef struct PlayerEffectObj {
    /* 0x000 */ u8 pad0[0x340];
    /* 0x340 */ f32 unk340;
    /* 0x344 */ f32 unk344;
    /* 0x348 */ f32 unk348;
    /* 0x34C */ u8 pad34C[0x360 - 0x34C];
    /* 0x360 */ f32 unk360;
    /* 0x364 */ f32 unk364;
} PlayerEffectObj;

typedef struct PlayerUpdateState {
    /* 0x000 */ s16 unk0;
    /* 0x002 */ u8 pad2[0x8D - 2];
    /* 0x08D */ u8 hitStatus;
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
    /* 0x254 */ PlayerEffectObj *unk254;
    /* 0x258 */ u8 pad258[0x268 - 0x258];
    /* 0x268 */ u8 unk268;
} PlayerUpdateState;

typedef struct PlayerUpdateSlot {
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
} PlayerUpdateSlot;

typedef struct PadInputStateView {
    /* 0x00 */ u8 pad0[0x2A];
    /* 0x2A */ u16 unk2A;
    /* 0x2C */ u8 pad2C[2];
    /* 0x2E */ s8 unk2E;
    /* 0x2F */ s8 unk2F;
    /* 0x30 */ u8 pad30[4];
} PadInputStateView;

typedef struct PlayerStateFn {
    /* 0x0 */ void (*fn)(void);
    /* 0x4 */ s32 pad4;
} PlayerStateFn;

#define PLAYER_STATE ((PlayerUpdateState *)gActivePlayerState)
#define PLAYER_SLOT(i) (((PlayerUpdateSlot *)gPlayerSlots)[i])

extern PlayerStateFn gPlayerStateHandlers[];
extern s32 gGameFrameCounter;
extern s32 D_8076A090;
extern s32 D_8076A094;
extern s32 D_8076A098;
extern s32 D_807552E4;
extern s32 gGlobalPauseFlags;
extern s32 gCurrentMap;
extern u8 D_80770561;
extern u8 D_807463B8;
extern u8 D_807FBB8C;
extern s16 D_807F5FE4;
extern s16 D_807F5FE6;
extern s16 D_807F5FE8;
extern s16 D_807F5FEA;
extern s32 D_80720020;

void func_806CB53C();
void playerCheckQueueDropCallback(void);
void func_806CF580(void);
void playerCheckLedgeGrab(void);
void sfxStopChannel(s32, s32);
void func_806F4D70(u8, f32, f32, f32, f32);
void proxPathUpdateAllPlayers(void);
s32 collisionGetHitStatus();
u8 func_80666A94();
u8 func_80666AA0();
u8 func_80666AAC();
u8 func_80666AB8();
void func_80026D40(void *, u8);
void mapSetPendingTransition(s32, s32);
void mapExecuteDeathTransition(u8);
void mapExecuteVoidTransition();
void healthRefill(u8);
void effectEnableFade();
void effectSetColor(s32, s32, s32, s32);
void effectFreeAndUnlink(void *);
s32 camProjectToScreen(f32, f32, f32, f32 *, f32 *, f32 *, f32, s32);
s32 playerStateQueueCallback(s32, Actor *, u8);
void actorGetNodePos(void *, s32, f32 *, f32 *, f32 *);
f32 sqrtf(f32);
void effectSetDuration(s32);
void effectSetMode(s32);
s32 effectCreateAtPosition(void *, f32, f32, f32, f32);

void playerUpdateCommon(s32 arg0) {
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
    PlayerEffectObj *fx;
    s16 flags;
    if (gCurrentActor && gCurrentActor) {}  // FAKE: steers uopt candidate colouring (gActivePlayerActor pointer v1)

    sp64 = gCurrentActor;
    gActivePlayerState = gCurrentActor->customState;
    if (D_807463B8 == 0) {
        gCurrentActor->flags |= 0x400000;
    } else {
        gCurrentActor->flags &= 0xFFBFFFFF;
    }
    gCurrentActor->flags &= 0xF7FFFFFF;
    PLAYER_SLOT(gCurrentPlayerIndex).unk28C = PLAYER_SLOT(gCurrentPlayerIndex).unk27C;
    if (gCurrentActor->renderFlags & 0x100) {
        PLAYER_STATE->unk120 = gGameFrameCounter;
    }
    if (PLAYER_STATE->unk1CC == PLAYER_STATE->unk1C0 && gCurrentActor->state != 0x54) {
        if (gCurrentActor->actorType == 4) {
            gCurrentActor->eyeHeight = 0xB;
        } else {
            gCurrentActor->eyeHeight = gCurrentActor->collision->scaledRadius * 0.15 * 0.5;
        }
    }
    playerCheckQueueDropCallback();
    flags = gPlayerStateFlags[gCurrentActor->state][0];
    if (flags & 8) {
        gCurrentActor->flags2 |= 2;
    } else {
        gCurrentActor->flags2 &= 0xFFFD;
    }
    if ((flags & 0x20) && PLAYER_STATE->unkFC == 0 && gCurrentActor->actorType != 8 && gCurrentActor->actorType != 9) {
        gCurrentActor->flags2 |= 0x10;
    } else {
        gCurrentActor->flags2 &= 0xFFEF;
        gCurrentActor->flags &= ~0x800;
    }
    if (PLAYER_STATE->unkFC != 0) {
        PLAYER_STATE->unkFC = PLAYER_STATE->unkFC - 1;
    }
    if (flags & 0x40) {
        gCurrentActor->flags |= 0x4000;
    } else {
        gCurrentActor->flags &= ~0x4000;
    }
    if ((flags & 0x80) && PLAYER_STATE->unk100 == 0 && gCurrentActor->actorType != 8 && gCurrentActor->actorType != 9) {
        gCurrentActor->flags2 |= 0x20;
    } else {
        gCurrentActor->flags2 &= 0xFFDF;
    }
    if (PLAYER_STATE->unk100 != 0) {
        PLAYER_STATE->unk100 = PLAYER_STATE->unk100 - 1;
    }
    if (PLAYER_STATE->unk245 != 0) {
        PLAYER_STATE->unk245 = PLAYER_STATE->unk245 - 1;
    }
    func_806CB53C();
    playerCheckAndClearCarriedItem();
    func_806CA540();
    if (D_80770561 == 0x6B && gCurrentActor->state != 0x6E) {
        sfxStopChannel(0x6B, 0);
    }
    if (PLAYER_STATE->unkCA != 0) {
        PLAYER_STATE->unkCA = PLAYER_STATE->unkCA - 1;
    }
    if (gCurrentActor->flags2 & 0x20) {
        proxPathUpdateAllPlayers();
    }
    func_806F4D70(gCurrentPlayerIndex, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, gCurrentActor->sub4->scaleY / 0.15 * 20.0);
    if (gPlayerCount == 1) {
        if (gCurrentActor->renderFlags & 0x1000) {
            gCurrentActor->renderFlags |= 0x200;
        }
    }
    gCurrentActor->renderFlags &= ~0x1000;
    gPlayerStateHandlers[gCurrentActor->state].fn();
    PLAYER_STATE->hitStatus = collisionGetHitStatus();
    if (gPlayerCount == 1) {
        gCurrentActor->renderFlags &= ~0x200;
    }
    if ((gActivePlayerState->stateFlags & 0x01000000) && D_807FBB8C != 0 && gCurrentActor->state != 0x47) {
        playerStateQueueCallback(3, NULL, gCurrentPlayerIndex);
    }
    sp6B = func_80666AA0();
    sp6A = func_80666A94();
    sp69 = func_80666AAC();
    sp68 = func_80666AB8();
    if (gCurrentActor->flags2 & 0x10) {
        playerCheckLedgeGrab();
    }
    PLAYER_STATE->unkE8 = 0;
    gActivePlayerState->stateFlags &= 0xBFFFFFFF;
    func_806CF580();
    PLAYER_STATE->unk0 = gActivePlayerActor->state;
    if (gPlayerCount >= 2) {
        if (gCurrentActor->contactFlags & 1) {
            if (PLAYER_STATE->unk24A != 0) {
                PLAYER_STATE->unk24A = PLAYER_STATE->unk24A - 1;
            } else {
                PLAYER_STATE->unk248 = -1;
                PLAYER_STATE->unk249 = 0;
            }
        }
        playerClearStaleHitSource();
        {
            s8 v = PLAYER_STATE->unk248;
            if (v >= 0 && (u32)v != PLAYER_STATE->unk1A4) {
                sp64 = PLAYER_SLOT(v).unk4;
            } else {
                s8 w = PLAYER_STATE->unk249;
                if (w > 0) {
                    sp64 = spawnNodeActivate(w, 0);
                }
            }
        }
        if (D_807552E4 == 0) {
            if (gActivePlayerActor->state == 0x3C) {
                if (PLAYER_STATE->unk250 != 0) {
                    PLAYER_STATE->unk250 = PLAYER_STATE->unk250 - 1;
                }
                if (PLAYER_STATE->unk254 == NULL) {
                    effectSetDuration(-1);
                    effectSetMode(0);
                    effectSetColor(0xFF, 0xFF, 0xFF, 0x78);
                    effectEnableFade();
                    PLAYER_STATE->unk254 = (PlayerEffectObj *)effectCreateAtPosition(&D_80720020, 0.7f, gActivePlayerActor->x, gActivePlayerActor->y, gActivePlayerActor->z);
                }
            } else {
                if (PLAYER_STATE->unk250 < 0x78) {
                    PLAYER_STATE->unk250 = PLAYER_STATE->unk250 + 1;
                }
                if (PLAYER_STATE->unk254 != NULL) {
                    fx = PLAYER_STATE->unk254;
                    PLAYER_STATE->unk254 = NULL;
                    effectFreeAndUnlink(fx);
                }
            }
            fx = PLAYER_STATE->unk254;
            if (fx != NULL) {
                actorGetNodePos(gActivePlayerActor, 1, &sp5C, &sp58, &sp54);
                camProjectToScreen(sp5C, sp58, sp54, &sp4C, &sp48, NULL, 1.0f, 0);
                fx->unk340 = sp4C * 4.0f;
                fx->unk344 = sp48 * 4.0f;
                fx->unk348 = 5.0f;
                dz = PLAYER_SLOT(0).unk218 - sp54;
                dx = PLAYER_SLOT(0).unk210 - sp5C;
                dy = PLAYER_SLOT(0).unk214 - sp58;
                dz = sqrtf(dz * dz + (dx * dx + dy * dy));
                fx->unk360 = gCurrentActor->sub4->scaleX * (1000.0f / dz) * 6.666666666666667 * 0.7 * 0.008333334f * (f32)PLAYER_STATE->unk250;
                fx->unk364 = fx->unk360;
            }
        }
    }
    if (PLAYER_STATE->unkD4 != 0) {
        PLAYER_STATE->unkD4 = PLAYER_STATE->unkD4 - 1;
    }
    if (sp6A != 0) {
        playerStateQueueCallback(0x3F, sp64, gCurrentPlayerIndex);
    }
    if (sp6B == 1) {
        goto case1;
    }
    if (sp6B == 2) {
        goto case2;
    }
    PLAYER_STATE->unkD6 = 0;
    goto done;
case1:
    if (PLAYER_STATE->unk1F0 & 0x10) {
        PLAYER_STATE->unkD6 = 0;
    } else {
        PLAYER_STATE->unkD6 = PLAYER_STATE->unkD6 + 1;
        playerStateQueueCallback(0x2E, sp64, gCurrentPlayerIndex);
        if (gCurrentActor->state != 0x36 && gCurrentActor->state != 0x3B && PLAYER_STATE->unkD4 == 0) {
            s32 snd = 0x2C0;
            if (gCurrentMap == 0x30) {
                snd = 0x3B0;
            }
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, snd, 0xFF, 0x7F, 0);
        }
    }
    goto done;
case2:
    PLAYER_STATE->unk1F0 |= 0x1000;
    if (!(PLAYER_STATE->unk1F0 & 0x10)) {
        if (gCurrentActor->state != 0x36 && gCurrentActor->state != 0x3B && PLAYER_STATE->unkD4 == 0) {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x2C0, 0xFF, 0x7F, 0);
        }
        if (gCurrentMap == 0x53 || gCurrentMap == 0xC5) {
        playerStateQueueCallback(0x40, sp64, gCurrentPlayerIndex);
    } else {
        playerStateQueueCallback(0x30, sp64, gCurrentPlayerIndex);
        }
    }
done:
    if (sp69 != 0) {
        playerStateQueueCallback(0, sp64, gCurrentPlayerIndex);
        if (PLAYER_STATE->unkD4 == 0) {
            sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x2C0, 0xFF, 0x7F, 0);
        }
    }
    actorGetNodePos(gActivePlayerActor, 6, &PLAYER_SLOT(gCurrentPlayerIndex).unk2B4, &PLAYER_SLOT(gCurrentPlayerIndex).unk2B8, &PLAYER_SLOT(gCurrentPlayerIndex).unk2BC);
    camProjectToScreen(gActivePlayerActor->x, PLAYER_SLOT(gCurrentPlayerIndex).unk2B8, gActivePlayerActor->z, &sp70, &sp6C, NULL, 1.0f, gCurrentPlayerIndex);
    PLAYER_STATE->unk10E = sp70;
    PLAYER_STATE->unk110 = sp6C;
    camProjectToScreen(gActivePlayerActor->x, gActivePlayerActor->y, gActivePlayerActor->z, &sp70, &sp6C, NULL, 1.0f, gCurrentPlayerIndex);
    PLAYER_STATE->unk112 = sp6C;
    PLAYER_STATE->unk1F8 = PLAYER_STATE->unk1F0;
    if (PLAYER_STATE->unk268 != 0) {
        PLAYER_STATE->unk268 = PLAYER_STATE->unk268 - 1;
    }
    if ((gCurrentActor->x < (f32)D_807F5FE4 || gCurrentActor->z < (f32)D_807F5FE6 || (f32)D_807F5FE8 < gCurrentActor->x || (f32)D_807F5FEA < gCurrentActor->z || sp68 != 0) && PLAYER_STATE->unk244 == 0 && (u32)gFrameCounter >= 0x65 && !(gGlobalOverlayFlags & 0x4000) && gCurrentMap != 0xE) {
        if (gPlayerCount == 1) {
            if (flagGet(0x186, 0) == 0) {
                mapSetPendingTransition(0xB0, 1);
            }
            if (!gCurrentPlayerIndex && !gCurrentPlayerIndex) { // FAKE: steers uopt candidate colouring
            }
            healthRefill(gCurrentPlayerIndex);
            mapExecuteDeathTransition(gCurrentPlayerIndex);
            PLAYER_STATE->unk244 = 1;
        } else {
            func_80026D40(gCurrentActor, gCurrentPlayerIndex);
        }
    }
    if (gCurrentPlayerIndex == 0) {
        switch (gCurrentMap) {
            case 0x7:
            case 0x1A:
            case 0x1E:
            case 0x22:
            case 0x26:
            case 0x30:
            case 0x48:
            case 0x57:
                if (D_8076A094 >= 0x5DD && PLAYER_STATE->unk244 == 0) {
                    mapExecuteVoidTransition();
                    PLAYER_STATE->unk244 = 1;
                }
                if (D_8076A098 >= 0x5DD && !(gGlobalPauseFlags & 2) && PLAYER_STATE->unk244 == 0) {
                    mapExecuteVoidTransition();
                    PLAYER_STATE->unk244 = 1;
                }
                if ((gCurrentActor->x != gCurrentActor->prevX || gCurrentActor->y != gCurrentActor->prevY || gCurrentActor->z != gCurrentActor->prevZ || gPlayerPadState[gCurrentPlayerIndex].unk2A != 0 || gPlayerPadState[gCurrentPlayerIndex].unk2E != 0 || gPlayerPadState[gCurrentPlayerIndex].unk2F != 0) && !(gGlobalPauseFlags & 2)) {
                    if (++D_8076A090 == 0x69780) {
                        mapExecuteVoidTransition();
                        PLAYER_STATE->unk244 = 1;
                    }
                }
                break;
        }
    }
}

typedef struct LCEAE0bPlayer {
    /* 0x000 */ u8 pad0[0x2C];
    /* 0x02C */ f32 unk2C;
    /* 0x030 */ u8 pad30[8];
    /* 0x038 */ f32 unk38;
    /* 0x03C */ u8 pad3C[0xC];
    /* 0x048 */ s16 unk48;
    /* 0x04A */ u8 pad4A[0x8A];
    /* 0x0D4 */ s16 unkD4;
    /* 0x0D6 */ u8 padD6[0xCE];
    /* 0x1A4 */ u8 unk1A4;
    /* 0x1A5 */ u8 pad1A5[7];
    /* 0x1AC */ s32 unk1AC;
    /* 0x1B0 */ u8 pad1B0[0x10];
    /* 0x1C0 */ f32 unk1C0;
    /* 0x1C4 */ u8 pad1C4[8];
    /* 0x1CC */ f32 unk1CC;
    /* 0x1D0 */ u8 pad1D0[0x20];
    /* 0x1F0 */ s32 unk1F0;
    /* 0x1F4 */ s32 unk1F4;
    /* 0x1F8 */ u8 pad1F8[5];
    /* 0x1FD */ u8 unk1FD;
    /* 0x1FE */ u16 unk1FE;
    /* 0x200 */ s16 unk200;
    /* 0x202 */ u8 pad202[0x3C];
    /* 0x23E */ u8 unk23E;
    /* 0x23F */ u8 unk23F;
} LCEAE0bPlayer;

#define LB_P ((LCEAE0bPlayer *)gActivePlayerState)
#define LB_UNK120 (*(f32 *)&gCurrentActor->unk120)

extern f32 D_807531FC[];
extern f32 D_80753234[];
extern s16 D_8075326C[];
extern f32 D_80753218[];
extern s32 gCurrentMap;
extern u8 D_807463B8;
extern s32 D_8071FB08;
extern s32 sEffectSparkConfig;
extern s32 effectZSpinMatrixUpdate;
extern s32 func_80717930;
s32 randomNonNegative();
s32 camIsCutsceneActive();
void func_80687400();
void actorScriptStart(Actor *, s32);
void effectSetCallback(void *);
void effectSetDepth(s32);
void effectSetDuration(s32);
void effectSetFlags(s32);
void effectSetSpeed(s32);
void effectCreateAtActorBone(void *, f32, void *, s32, s32);
s32 effectCreateAtPosition(void *, f32, f32, f32, f32);
s32 playerStateQueueCallback(s32, Actor *, u8);
void playerInitNormalMoveParams(void);
void playerSetSizeMode(Actor *, u8);
void playerScaleTransitionStep(void);
void sfxStopChannel(s32, s32);
void playerTransformAnimalEndSfx(Actor *);
void playerResumeLocomotion(Actor *);
void playerCheckAndResetCarriedActor(Actor *);

void func_806CB53C(void) {
    s32 a0;
    s32 v0;
    s32 flag;
    f32 scale;
    s32 w;

    if ((gActivePlayerActor->actorType == 8 || gActivePlayerActor->actorType == 9) && LB_P->unk1FD != 0) {
        if ((LB_P->unk1F0 & 0x800) && LB_P->unk23E == 0) {
            LB_P->unk23E = 0x1E;
            func_80687400();
        }
        v0 = LB_P->unk23E;
        if ((gPlayerPadState[gCurrentPlayerIndex].unk2C & 2) && (gPlayerPadState[gCurrentPlayerIndex].unk2A & 0x2000) && v0 == 0) {
            LB_P->unk23E = 0x1E;
            v0 = LB_P->unk23E;
        }
        if (v0 != 0) {
            effectSetSpeed((randomNonNegative() >> 15) % 10 + 0x8008);
            effectSetDuration(2);
            effectSetCallback(&func_80717930);
            effectSetDepth(1);
            effectSetFlags(6);
            effectCreateAtActorBone(&sEffectSparkConfig, ((randomNonNegative() >> 15) % 50) / 80.0 + 0.5, gCurrentActor, 2, 0);
            LB_P->unk23E = LB_P->unk23E - 1;
            v0 = LB_P->unk23E;
        }
        if (v0 == 1) {
            playerStateQueueCallback(0x3B, NULL, gCurrentPlayerIndex);
            LB_P->unk1FD = 0;
        }
    } else {
        LB_P->unk23E = 0;
    }
    LB_P->unk1F0 &= ~0x800;
    if (gPlayerSlots[gCurrentPlayerIndex].unk2C0 != 1 || (LB_P->unk1F0 & 0x30)) {
        if ((LB_P->unk1F0 & 0x80000000) && LB_P->unk23F == 0) {
            LB_P->unk23F = 0x1E;
            func_80687400();
        }
        a0 = LB_P->unk23F;
        if (a0 != 0) {
            LB_P->unk23F = a0 - 1;
            a0 = LB_P->unk23F;
        }
        if (a0 == 1) {
            gPlayerPadState[gCurrentPlayerIndex].unk2C |= 2;
            gPlayerPadState[gCurrentPlayerIndex].unk2A |= 0x2000;
        }
        if (!(gPlayerStateFlags[gCurrentActor->state][0] & 0x300) && !(LB_P->unk1F0 & 0x14000) && camIsCutsceneActive() == 0 && !(LB_P->unk1F4 & 0x10)) {
            slotQueueAddValue(5, LB_P->unk1A4, -1);
        }
    } else {
        LB_P->unk23F = 0;
    }
    LB_P->unk1F0 &= 0x7FFFFFFF;
    if (((gPlayerPadState[gCurrentPlayerIndex].unk2C & 2) && (gPlayerPadState[gCurrentPlayerIndex].unk2A & 0x2000) && gPlayerCount == 1) || slotQueueGetValue(5, LB_P->unk1A4) == 0) {
        if (!(LB_P->unk1F0 & 0x2000) && gCurrentMap != 0xCF) {
            flag = 0;
            if (gPlayerSlots[gCurrentPlayerIndex].unk2C0 != 1) {
                playerSetSizeMode(gActivePlayerActor, 1);
                flag = 1;
                if (LB_P->unk1AC != 0 && gActivePlayerActor->actorType == 6 && gActivePlayerActor->state != 0x4A) {
                    gActivePlayerActor->state = 0x4A;
                    gActivePlayerActor->unk155[0] = 0;
                    actorScriptStart(gActivePlayerActor, 0x1CD);
                }
            }
            if (LB_P->unk1F0 & 0x10) {
                LB_P->unk1F0 &= ~0x10;
                flag = 1;
                gActivePlayerActor->flags |= 0x8000;
                gActivePlayerActor->alpha = 0xFF;
            }
            if (LB_P->unk1F0 & 0x20) {
                LB_P->unk1F0 &= ~0x20;
                flag = 1;
                playerInitNormalMoveParams();
            }
            if (flag != 0) {
                playerCheckAndResetCarriedActor(gCurrentActor);
            }
        }
    }
    if (LB_P->unk1F0 & 0x10) {
        LB_P->unkD4 = 2;
    }
    if (LB_P->unk1CC != LB_P->unk1C0) {
        gCurrentActor->renderFlags |= 0x800;
        switch (gCurrentActor->actorType) {
            default:
                LB_UNK120 = 0.15f;
                break;
            case 5:
                LB_UNK120 = 0.15f;
                break;
            case 6:
                LB_UNK120 = 0.3f;
                break;
        }
        playerScaleTransitionStep();
    } else {
        gCurrentActor->renderFlags &= ~0x800;
    }
    if (LB_P->unk1F0 & 0x40) {
        if (gCurrentActor->actorType != 6) {
            gCurrentActor->flags &= 0xFFFF7FFF;
            gCurrentActor->alpha -= 4;
            if (gCurrentActor->alpha < 0x64) {
                gCurrentActor->alpha = 0x64;
            }
        }
        if (LB_P->unk1FE != -1) {
            LB_P->unk1FE = LB_P->unk1FE - 1;
            if (!(LB_P->unk1FE & 7)) {
                effectSetCallback(&effectZSpinMatrixUpdate);
                effectSetDepth(1);
                effectSetDuration(3);
                effectCreateAtPosition(&D_8071FB08, 1.0f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
            }
            if (LB_P->unk1FE == 0) {
                sfxStopChannel(0x6C, 0);
                gCurrentActor->flags |= 0x8000;
                playerTransformAnimalEndSfx(gCurrentActor);
            }
        }
    }
    if (LB_P->unk200 != 0) {
        if (LB_P->unk1F0 & 0x8000000) {
            scale = 1.0f;
            if (LB_P->unk200 >= 2) {
                scale = 0.5f;
            }
            LB_P->unk38 = D_807531FC[gCurrentCharacterIndex] * scale;
            LB_P->unk2C = D_80753234[gCurrentCharacterIndex] * scale;
            LB_P->unk48 = (s32)(D_8075326C[gCurrentCharacterIndex] * scale);
            w = LB_P->unk200;
        }
        if (gCurrentActor->state != 0x7C || (gCurrentActor->state == 0x7C && LB_P->unk200 == 1)) {
            LB_P->unk200 = LB_P->unk200 - 1;
        }
        if (LB_P->unk200 == 0) {
            LB_P->unk1F0 &= 0xF7FFFF7F;
            if (gCurrentActor->state == 0x7C) {
                playerResumeLocomotion(gCurrentActor);
            }
        }
    }
    if ((LB_P->unk1F0 & 0x20) || D_807463B8 == 3) {
        if (gCurrentMap == 0x30) {
            LB_P->unk38 = 200.0f;
            return;
        }
        LB_P->unk38 = D_80753218[gCurrentCharacterIndex];
    }
}




void playerCheckQueueDropCallback(void) {
    if (gActorGlobalState.unk2 != 0 && gActorGlobalState.unk3[0x11] == 1) {
        playerStateQueueCallback(0x20, NULL, gCurrentPlayerIndex);
    }
}

extern f32 D_80753250[];
s32 mathAngleDistance(s16, s16);
void actorScriptExecute(Actor *);

void playerCheckLandingSfx(void) {
    if ((G02_A->unk6A & 0x21) == 1) {
        if (G02_A->unk6A & 0x200) {
            if (G02_A->unk6E == -1) {
                sfxPlayActorSound(gCurrentActor, 0x10D, 0, 1, 0, 0xFF, 1.0f, 0);
            }
            G02_A->unk154 = 0xF;
            G02_A->unk155 = 0;
            G02_A->unkC8 = -900.0f;
            G02_P->unk48 = D_8075326C[gCurrentCharacterIndex];
            G02_P->unk30 = D_80753250[gCurrentCharacterIndex];
            G02_P->unk2C = D_80753234[gCurrentCharacterIndex];
            actorScriptStartByIndex(gCurrentActor, 0x5E);
            G02_A->unk6A |= 0x20;
            actorScriptExecute(gCurrentActor);
            return;
        }
        if (G02_A->unkE0 != 0.0f && G02_P->unkC2 >= 0x15 && G02_A->unk154 != 0x17) {
            if (mathAngleDistance(G02_A->unkD8, G02_A->unkE6) < 0x200) {
                if (gPlayerStateFlags[gActivePlayerActor->state][0] & 0x200) {
                    func_806EAB44(gCurrentActor, 0);
                }
                playerStateQueueCallback(0x21, NULL, gCurrentPlayerIndex);
                return;
            }
            if (mathAngleDistance(G02_A->unkD8, G02_A->unkEE) < 0x400 || G02_A->unkB8 < 15.0f) {
                if (gPlayerStateFlags[gActivePlayerActor->state][0] & 0x200) {
                    func_806EAB44(gCurrentActor, 0);
                }
                playerStateQueueCallback(0x22, NULL, gCurrentPlayerIndex);
            }
        }
    }
}

s16 mathAngleSignedDistance(arg0, arg1) s16 arg0; s16 arg1; {
    s16 d = arg1 - arg0;
    s16 temp = d & 0xFFF;
    s16 var_v1 = temp;

    if (temp > 0x800) {
        var_v1 = temp - 0x1000;
    }
    return var_v1;
}

s32 mathAngleDistance(arg0, arg1) s16 arg0; s16 arg1; {
    s16 d = arg1 - arg0;
    s16 temp = d & 0xFFF;
    s16 var_v1 = temp;

    if (temp > 0x800) {
        var_v1 = 0x1000 - temp;
    }
    return var_v1;
}

s16 mathAngleEaseToward(s16 arg0, s16 arg1, f32 arg2) {
    s16 diff;
    s16 absd;
    s16 sign;
    f32 dist;

    diff = arg1 - arg0;
    if (diff > 0) {
        absd = diff;
    } else {
        absd = -diff;
    }
    if (arg2 != 0.0f && (diff & 0xFFF)) {
        if (diff >= 0) {
            sign = 1;
        } else {
            sign = -1;
        }
        if (absd >= 0x801) {
            absd = 0x1000 - absd;
            sign = -sign;
        }
        dist = absd;
        if (dist < arg2) {
            arg2 = dist;
        }
        arg0 += sign * (s16)(dist / arg2);
    }
    return arg0 & 0xFFF;
}

s16 mathAngleLerp(s16 arg0, s16 arg1, f32 arg2) {
    s16 diff;
    s16 absd;
    s16 sign;

    diff = arg1 - arg0;
    if (diff > 0) {
        absd = diff;
    } else {
        absd = -diff;
    }
    if (arg2 != 0.0f && (diff & 0xFFF)) {
        if (diff >= 0) {
            sign = 1;
        } else {
            sign = -1;
        }
        if (absd >= 0x801) {
            absd = 0x1000 - absd;
            sign = -sign;
        }
        arg0 += sign * (s16)(absd * arg2);
    }
    return arg0 & 0xFFF;
}

typedef struct G03ActorView {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ ActorSub4 *unk4;
    /* 0x08 */ u8 pad8[0x58];
    /* 0x60 */ u32 unk60;
    /* 0x64 */ u8 pad64[6];
    /* 0x6A */ u16 unk6A;
    /* 0x6C */ u8 pad6C[0x10];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
    /* 0x84 */ f32 unk84;
    /* 0x88 */ f32 unk88;
    /* 0x8C */ u8 pad8C[4];
    /* 0x90 */ f32 unk90;
    /* 0x94 */ u8 pad94[0x10];
    /* 0xA4 */ f32 unkA4;
    /* 0xA8 */ u8 padA8[4];
    /* 0xAC */ f32 unkAC;
    /* 0xB0 */ u8 padB0[4];
    /* 0xB4 */ f32 unkB4;
    /* 0xB8 */ f32 unkB8;
    /* 0xBC */ u8 padBC[4];
    /* 0xC0 */ f32 unkC0;
    /* 0xC4 */ f32 unkC4;
    /* 0xC8 */ f32 unkC8;
    /* 0xCC */ u8 padCC[0xE];
    /* 0xDA */ s16 unkDA;
    /* 0xDC */ u8 padDC[0xA];
    /* 0xE6 */ s16 unkE6;
    /* 0xE8 */ s16 unkE8;
    /* 0xEA */ u8 padEA[4];
    /* 0xEE */ s16 unkEE;
} G03ActorView;

typedef struct G03PlayerView {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ u8 pad8[2];
    /* 0x0A */ s16 unkA;
    /* 0x0C */ u8 padC[4];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ u8 pad14[0xC];
    /* 0x20 */ f32 unk20;
    /* 0x24 */ u8 pad24[2];
    /* 0x26 */ s16 unk26;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ u8 pad2A[2];
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ u8 pad34[4];
    /* 0x38 */ f32 unk38;
    /* 0x3C */ u8 pad3C[0x14];
    /* 0x50 */ s16 unk50;
    /* 0x52 */ u8 pad52[0x84];
    /* 0xD6 */ s16 unkD6;
} G03PlayerView;

#define G03_A ((G03ActorView *)gCurrentActor)
#define G03_P ((G03PlayerView *)gActivePlayerState)

void playerUpdateHorizontalVelocity(s32);
void playerCheckLandingSfx(void);
void playerApplyMotion(void);
void playerApplyGravity(void);
f32 mathApproachF32(f32, f32, f32);

extern s16 D_80753A3C[];
extern s16 D_80753A4C[];
f32 mathCosF(s16);
f32 mathSinF(s16);

#define G03_ABS(x) ((x) > 0.0f ? (x) : -(x))

void func_806CC364(u8 arg0) {
    f32 sum;
    f32 a;

    if (gPlayerSlots[gCurrentPlayerIndex].unk2C0 == 1) {
        a = D_80753A3C[gCurrentCharacterIndex];
    } else {
        a = D_80753A4C[gCurrentCharacterIndex];
    }
    sum = G03_ABS(mathSinF(G03_A->unkE8) * a) + 1.5;
    sum += G03_ABS(mathCosF(G03_A->unkDA) * a);
    if (G03_A->unkB4 < sum) {
        if (G03_A->unkDA < 500) {
            G03_A->unkB8 = (G03_A->unkB8 < 50.0f) ? G03_A->unkB8 : 50.0f;
        }
        if (arg0) {
            if (G03_A->unkC0 < 0.0f) {
                G03_A->unkC0 = 0.0f;
            }
        }
        if (a < G03_A->unkAC - G03_A->unk80) {
            G03_A->unk80 = G03_A->unkA4 + sum;
        }
    }
}

extern f32 D_807539C0[];

void playerDecelerateAndApplyMotion(void) {
    gCurrentActor->speedXZ = mathApproachF32(gCurrentActor->speedXZ, 0.0f, D_807539C0[gCurrentCharacterIndex]);
    playerApplyMotion();
    func_806CC364(1);
}

extern s16 D_80753A2C[];
extern f32 D_80753A5C[];
void actorApplyVelocityCustom(Actor *, f32, f32);
void actorStepPhysics(Actor *, s16, s16);
void actorApplyVelocity(Actor *);
void actorUpdateFloorContactAndTilt(Actor *, f32);

void func_806CC638(f32 arg0) {
    f32 vx;
    f32 vz;
    f32 adj;
    f32 rate;
    f32 sn;
    f32 cs;

    if (G03_P->unk10 != 0) {
        G03_P->unk10--;
        sn = mathCosF(G03_P->unk12);
        cs = mathSinF(G03_P->unk12);
        vx = G03_P->unk38 * sn;
        cs = G03_P->unk38 * -cs;
        vz = cs;
        adj = 0.0f;
        if (G03_P->unk38 < G03_A->unkB8) {
            rate = G03_P->unk2C * 8.0f;
        } else {
            rate = G03_P->unk2C;
        }
    } else {
        cs = mathSinF(G03_A->unkE8);
        vz = G03_A->unkB8 * -cs;
        G03_A->unkC0 = mathApproachF32(G03_A->unkC0, vz, 2.0f);
        vx = 0.0f;
        adj = 0.0f;
        rate = G03_P->unk30;
    }
    if (0.0f <= vz) {
        if (G03_A->unkAC - G03_A->unk80 < D_80753A2C[gCurrentCharacterIndex]) {
            adj = G03_ABS(D_80753A5C[gCurrentCharacterIndex]);
        }
    }
    vz += adj;
    if (G03_A->unkB4 == 0.0f) {
        if (G03_A->unkC0 < -0.1) {
            G03_A->unkC0 = -0.1f;
        }
    }
    G03_A->unkC0 = mathApproachF32(G03_A->unkC0, vz, rate * 2.0);
    G03_A->unkB8 = mathApproachF32(G03_A->unkB8, vx, rate);
    G03_A->unkEE = G03_A->unkE6;
    actorStepPhysics(gCurrentActor, G03_A->unkEE, G03_A->unkE6);
    actorApplyVelocityCustom(gCurrentActor, G03_A->unkB8, G03_A->unkC0);
    actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
    func_806CC364(0);
}

extern u8 D_807FD586;

void playerSetUnk586Flag(void) {
    D_807FD586 = 1;
}

void playerApplyFullPhysics(void) {
    playerApplyGravity();
    playerCheckLandingSfx();
    playerUpdateHorizontalVelocity(1);
    playerApplyMotion();
}

void playerApplyMotionWithHorizontalVelocity(void) {
    playerCheckLandingSfx();
    playerUpdateHorizontalVelocity(1);
    playerApplyMotion();
}

void playerApplyHorizontalMotion(void) {
    playerUpdateHorizontalVelocity(1);
    playerApplyMotion();
}

void playerApplyGravityAndMotion(void) {
    playerApplyGravity();
    playerApplyMotion();
}

f32 sqrtf(f32);
extern u32 gFrameDelta;

#define G03_MAX(a, b) ((a) < (b) ? (b) : (a))

void playerApplyMotion(void) {
    s16 angle;
    f32 dx;
    f32 dz;

    playerUpdateHorizontalVelocity(0);
    if (mathAngleDistance(G03_A->unkE6, G03_A->unkEE) < 0x400) {
        angle = G03_A->unkE6;
    } else {
        angle = (G03_A->unkE6 + 0x800) & 0xFFF;
    }
    actorStepPhysics(gCurrentActor, angle, angle);
    actorApplyVelocity(gCurrentActor);
    actorUpdateFloorContactAndTilt(gCurrentActor, G03_MAX(-G03_P->unkD6 * 0.125, -6.0));
    G03_A->unk60 |= 1;
    dx = G03_A->unk7C - G03_A->unk88;
    dz = G03_A->unk84 - G03_A->unk90;
    G03_P->unk20 = sqrtf(dx * dx + dz * dz) / gFrameDelta * 80.0 * 0.15 / G03_A->unk4->scaleX;
}

void playerApplyGravity(void) {
    if (G03_P->unk50 != 0) {
        G03_P->unk50--;
        return;
    }
    G03_A->unkC0 += G03_A->unkC4;
    if (G03_A->unkC0 < G03_A->unkC8) {
        G03_A->unkC0 = G03_A->unkC8;
    }
    if (-G03_A->unkC8 < G03_A->unkC0) {
        G03_A->unkC0 = -G03_A->unkC8;
    }
}

f32 mathScaleByAngleDeltaCos(f32, s16, s16);
void playerApproachVelocity(s16, f32, f32);
void playerApplyDeceleration(void);

void func_806CCB94(void) {
    f32 temp = mathScaleByAngleDeltaCos(G03_P->unk4, G03_P->unkA, G03_A->unkE6);

    if (temp > 0.0f) {
        playerApproachVelocity(G03_A->unkE6, temp, G03_P->unk38);
    } else {
        playerApplyDeceleration();
    }
}

s32 playerIsDamageOrKnockbackState(void) {
    switch (gActivePlayerActor->state) {
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
            return 1;
    }
    return 0;
}

typedef struct NmCEAE0bSub174 {
    /* 0x00 */ u8 pad0[0x14];
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
} NmCEAE0bSub174;

typedef struct NmCEAE0bP88 {
    /* 0x000 */ u8 pad0[0x174];
    /* 0x174 */ NmCEAE0bSub174 *unk174;
} NmCEAE0bP88;

typedef struct NmCEAE0bPlayer {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ u8 pad8[2];
    /* 0x0A */ s16 unkA;
    /* 0x0C */ u8 padC[0x24];
    /* 0x30 */ f32 unk30;
    /* 0x34 */ u8 pad34[4];
    /* 0x38 */ f32 unk38;
    /* 0x3C */ u8 pad3C[0x4C];
    /* 0x88 */ NmCEAE0bP88 *unk88;
    /* 0x8C */ u8 pad8C[0x36];
    /* 0xC2 */ s16 unkC2;
    /* 0xC4 */ u8 padC4[0x14];
    /* 0xD8 */ u8 unkD8;
} NmCEAE0bPlayer;

typedef struct NmCEAE0bActor {
    /* 0x00 */ u8 pad0[0x6A];
    /* 0x6A */ u16 unk6A;
    /* 0x6C */ u8 pad6C[0x48];
    /* 0xB4 */ f32 unkB4;
    /* 0xB8 */ f32 unkB8;
    /* 0xBC */ u8 padBC[0x20];
    /* 0xDC */ s16 unkDC;
    /* 0xDE */ u8 padDE[2];
    /* 0xE0 */ f32 unkE0;
    /* 0xE4 */ u8 padE4[0xA];
    /* 0xEE */ s16 unkEE;
    /* 0xF0 */ u8 padF0[0xC];
    /* 0xFC */ u8 unkFC;
    /* 0xFD */ u8 padFD[0x57];
    /* 0x154 */ u8 unk154;
} NmCEAE0bActor;

#define NMB_A ((NmCEAE0bActor *)gCurrentActor)
#define NMB_P ((NmCEAE0bPlayer *)gActivePlayerState)

f32 mathAtan2(f32, f32);

void playerUpdateHorizontalVelocity(arg0) u8 arg0; {
    f32 fa1;
    f32 fv1;
    f32 sp44;
    f32 sp40;
    f32 speed;
    f32 sp38;
    s16 ang;
    s16 m;
    NmCEAE0bSub174 *sub;

    switch (NMB_A->unk154) {
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
            speed = NMB_A->unkB8;
            ang = NMB_A->unkEE;
            sub = NMB_P->unk88->unk174;
            if (!sub) {
            }
            if (!sub) {
            }
            if (!sub) {
            }
            NMB_P->unkD8 = NMB_A->unkFC;
            if (D_807FD586) {}
            D_807FD586 = 0;
            sp38 = mathSinF((s16)(s32)(NMB_A->unkE0 * 11.4)) * 10.0;
            fa1 = gPlayerPadState[gCurrentPlayerIndex].unk2F;
            if (fa1 < 0.0f) {
                fa1 = fa1 * (NMB_A->unkB8 / 1600.0);
                if (NMB_A->unkB8 < 210.0f) {
                    fa1 = 0.0f;
                }
            } else {
                fa1 = fa1 / 10.0;
            }
            m = (ang - NMB_A->unkDC > 0 ? ang - NMB_A->unkDC : -(ang - NMB_A->unkDC)) % 4096;
            if ((m >= 0x401 && m < 0xC00) || !(NMB_A->unk6A & 0x200)) {
                fa1 = 0.0f;
            }
            fv1 = -gPlayerPadState[gCurrentPlayerIndex].unk2E / 5.5;
            if (NMB_A->unkB8 < 50.0f) {
                fv1 = fv1 * 0.21739130434782608;
            } else if (NMB_A->unkB8 < 230.0f) {
                fv1 = (NMB_A->unkB8 * fv1) / 230.0;
            }
            if (sub->unk14 < sub->unk18) {
                fa1 = 0.0f;
            }
            sp44 = mathSinF(ang) * speed;
            sp40 = mathCosF(ang) * speed;
            if (NMB_A->unk6A & 1) {
                sp44 += mathSinF(NMB_A->unkDC) * sp38;
                sp40 += mathCosF(NMB_A->unkDC) * sp38;
                sp44 += mathSinF(NMB_A->unkEE) * fa1;
                sp40 += mathCosF(NMB_A->unkEE) * fa1;
                sp44 += mathCosF(NMB_A->unkEE) * fv1;
                sp40 -= mathSinF(NMB_A->unkEE) * fv1;
            } else if ((NMB_A->unkB4 > 30.0f || sp38 == 0.0f || m < 0x400 || m >= 0xC01) &&
                       sub->unk18 == sub->unk14) {
                sp44 += (mathSinF(NMB_P->unkA) * NMB_P->unk4) / 40.0;
                sp40 += (mathCosF(NMB_P->unkA) * NMB_P->unk4) / 40.0;
            }
            speed = sqrtf(sp44 * sp44 + sp40 * sp40);
            if (!(NMB_A->unk6A & 0x1000) && 700.0f < speed) {
                speed = 700.0f;
            }
            fv1 = mathAtan2(sp44, sp40);
            if (arg0 != 0) {
                NMB_A->unkB8 = speed;
                NMB_A->unkEE = (s32)((fv1 * 4096.0) / 6.2831855f);
                if (NMB_A->unk6A & 1) {
                    if (!(NMB_A->unk6A & 0x200)) {
                        NMB_P->unk30 = 20.0f;
                    } else {
                        NMB_P->unk30 = (NMB_A->unkB8 * NMB_A->unkB8) / 35000.0;
                    }
                    playerApplyDeceleration();
                    return;
                }
            }
            return;
        default:
            if (NMB_P->unkC2 >= 0x15) {
                sp38 = NMB_A->unkE0;
            } else {
                sp38 = 0.0f;
            }
            if (sp38 != 0.0f && NMB_P->unkC2 >= 0x15 && (NMB_A->unk6A & 1)) {
                speed = NMB_A->unkB8;
                ang = NMB_A->unkEE;
            } else {
                speed = NMB_P->unk4;
                ang = NMB_P->unkA;
            }
            if (D_807FD586 == 0 && NMB_P->unkD8 != 0 && NMB_A->unkFC == 0) {
                NMB_A->unkEE = ang;
            }
            NMB_P->unkD8 = NMB_A->unkFC;
            D_807FD586 = 0;
            if (D_807FD586) {}
            if (D_807FD586) {}
            if (D_807FD586) {}
            fa1 = mathSinF(ang) * speed;
            sp44 = mathSinF(NMB_A->unkDC) * sp38;
            sp44 = fa1 + sp44;
            fa1 = mathCosF(ang) * speed;
            sp40 = mathCosF(NMB_A->unkDC) * sp38;
            sp40 = fa1 + sp40;
            speed = sqrtf(sp44 * sp44 + sp40 * sp40);
            ang = (s32)((mathAtan2(sp44, sp40) * 4096.0) / 6.2831855f);
            if (arg0 != 0) {
                if (speed != 0.0f) {
                    playerApproachVelocity(ang, speed, NMB_P->unk38);
                } else {
                    playerApplyDeceleration();
                }
            }
            break;
    }
}


void playerApproachVelocity(s16 arg0, f32 arg1, f32 arg2) {
    f32 vA;
    f32 vB;
    f32 cur;
    f32 tgt;
    f32 dist;
    f32 rate;
    f32 lim1;
    f32 lim2;
    f32 f;
    s16 d;
    s16 prev;
    s16 wrap;

    if (G03_A->unkB8 == 0.0f) {
        G03_A->unkEE = arg0;
    }
    prev = G03_A->unkEE;
    f = 0.0f;
    if (G03_A->unk6A & 1) {
        rate = G03_P->unk2C * (G03_P->unk26 * 3 + 100) / 400.0f;
        if (G03_P->unk28 != 0) {
            d = (arg0 - prev) & 0xFFF;
            wrap = d;
            if (d > 0x800) {
                wrap = 0x1000 - d;
            }
            f = G03_P->unk26 * ((f32)wrap / 2048) / 100.0f;
        }
    } else {
        rate = G03_P->unk2C;
    }
    cur = mathSinF(prev) * G03_A->unkB8;
    tgt = mathSinF(arg0) * arg1;
    if (f != 0.0f) {
        if (cur < tgt) {
            dist = tgt - cur;
        } else {
            dist = -(tgt - cur);
        }
        dist = dist * ((G03_P->unk26 * 63.0 + 100.0) / 6400.0);
        lim1 = (dist - rate) * f + rate;
    } else {
        if (0.0f < mathSinF(arg0) * rate) {
            lim1 = mathSinF(arg0) * rate;
        } else {
            lim1 = -(mathSinF(arg0) * rate);
        }
        if (0.0f < mathCosF(arg0) * rate) {
            lim2 = mathCosF(arg0) * rate;
        } else {
            lim2 = -(mathCosF(arg0) * rate);
        }
    }
    vA = mathApproachF32(cur, tgt, lim1);
    cur = mathCosF(prev) * G03_A->unkB8;
    tgt = mathCosF(arg0) * arg1;
    if (f != 0.0f) {
        if (cur < tgt) {
            dist = tgt - cur;
        } else {
            dist = -(tgt - cur);
        }
        dist = dist * ((G03_P->unk26 * 63.0 + 100.0) / 6400.0);
        lim2 = (dist - rate) * f + rate;
    }
    vB = mathApproachF32(cur, tgt, lim2);
    G03_A->unkB8 = sqrtf(vA * vA + vB * vB);
    if (arg2 < G03_A->unkB8) {
        G03_A->unkB8 = arg2;
    }
    if (G03_A->unkB8 != 0.0) {
        G03_A->unkEE = mathAtan2(vA, vB) * 4096.0 / 6.2831855f;
    }
}

f32 mathApproachF32(f32 current, f32 target, f32 step) {
    if (current < target) {
        current += step;
        if (target < current) {
            current = target;
        }
    } else {
        current -= step;
        if (current < target) {
            current = target;
        }
    }
    return current;
}

void playerApplyDeceleration(void) {
    f32 sub;

    if ((G03_A->unk6A & 1) && !(G03_A->unk6A & 0x200)) {
        sub = G03_P->unk30 * (G03_P->unk26 * 15 + 100) / 1600.0f;
    } else {
        sub = G03_P->unk30;
    }
    G03_A->unkB8 -= sub;
    if (G03_A->unkB8 < 0.0f) {
        G03_A->unkB8 = 0.0f;
    }
}


s16 actorGetStateFlags(Actor *arg0) {
    s16 ret = gPlayerStateFlags[arg0->state][0];
    return ret;
}

extern f32 D_80753170[];
extern f32 D_8075318C[];
extern f32 D_807531A8[];
extern f32 D_807531C4[];
extern f32 D_807531E0[];
extern u8 gGameMode;

s16 playerSelectMoveTier(Actor *arg0, f32 arg1, f32 arg2, s16 arg3, s16 arg4) {
    f32 max;

    if (arg2 < arg1) {
        max = arg1;
    } else {
        max = arg2;
    }
    if ((arg0->contactFlags | arg0->prevContactFlags) & 1) {
        switch (arg3) {
            case 0:
            case 1:
            case 2:
                if (arg2 != 0.0f) {
                    if (arg2 < D_8075318C[arg4]) {
                        arg3 = 3;
                    } else if (arg2 < D_807531C4[arg4]) {
                        arg3 = 4;
                    } else {
                        arg3 = 5;
                    }
                }
                break;
            case 3:
                if (arg2 == 0.0f && arg1 < D_80753170[arg4]) {
                    arg3 = 0;
                    break;
                }
                if (D_807531C4[arg4] < arg2) {
                    arg3 = 5;
                } else if (D_8075318C[arg4] < arg2) {
                    arg3 = 4;
                }
                break;
            case 4:
                if (max < D_807531A8[arg4]) {
                    if (arg2 < D_80753170[arg4]) {
                        arg3 = 0;
                    } else {
                        arg3 = 3;
                    }
                } else if (D_807531C4[arg4] < arg2) {
                    arg3 = 5;
                }
                break;
            case 5:
                if (max < D_807531E0[arg4]) {
                    arg3 = 4;
                }
                break;
            default:
                if (arg1 < D_80753170[arg4]) {
                    arg3 = 0;
                } else if (arg1 < D_807531A8[arg4]) {
                    arg3 = 3;
                } else if (arg1 < D_807531E0[arg4]) {
                    arg3 = 4;
                } else {
                    arg3 = 5;
                }
                break;
        }
        if (gActivePlayerState->stateFlags & 0x100) {
            if (arg3 == 4 || arg3 == 5) {
                arg3 = 3;
            }
        }
        if (arg3 == 0) {
            if (gCurrentMap == 1 || gCurrentMap == 5 || gCurrentMap == 0x19 || gCurrentMap == 0xF) {
                arg3 = 2;
                goto end;
            }
        }
        if (arg3 == 0) {
            if (gPlayerCount >= 2 || (gActivePlayerState->stateFlags & 0x40) || !(arg0->flags & 4) || gGameMode == 1) {
                arg3 = 1;
                goto end;
            }
        }
        if (arg3 == 1) {
            if (gPlayerCount < 2 && !(gActivePlayerState->stateFlags & 0x40) && (arg0->flags & 4) && gGameMode != 1) {
                arg3 = 0;
                goto end;
            }
        }
    } else {
        arg3 = 6;
    }
end:
    return arg3;
}

typedef struct G04PlayerView {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ u8 pad8[0x26 - 8];
    /* 0x26 */ s16 unk26;
    /* 0x28 */ u8 pad28[0x4C - 0x28];
    /* 0x4C */ s16 unk4C;
    /* 0x4E */ u8 pad4E[0x1F0 - 0x4E];
    /* 0x1F0 */ s32 unk1F0;
} G04PlayerView;

#define G04_P ((G04PlayerView *)gActivePlayerState)

typedef struct G04Model {
    /* 0x00 */ u8 pad0[0x24];
    /* 0x24 */ f32 unk24;
} G04Model;

typedef struct G04ActorView {
    /* 0x00 */ u8 pad0[0xB8];
    /* 0xB8 */ f32 unkB8;
    /* 0xBC */ u8 padBC[4];
    /* 0xC0 */ f32 unkC0;
} G04ActorView;

s16 func_806CE7A0(Actor *, f32, f32, s16, s16);
void scriptSetActorRampTarget(Actor *, f32, f32);
void controllerAnimSetStateIfChanged(void *, s16, f32, f32);
void controllerAnimScaleInterpolate(Actor *, s32);

extern u8 gPlayerCharacterId[];
void controllerAnimSetStateRemap(void *, s32, f32, f32);
void playerInitMoveParams(void);

s16 func_806CDD24(Actor *arg0, f32 arg1, f32 arg2, s32 arg3) {
    s16 sp36;
    f32 scale;
    s16 sp2E;
    s16 sp2C;

    sp36 = arg0->state;
    sp2E = G04_P->unk4C;
    sp2C = playerSelectMoveTier(arg0, arg1, arg2, G04_P->unk4C, gCurrentCharacterIndex);
    if (sp2C != 6) {
        ((G04ActorView *)arg0)->unkC0 = 0.0f;
    }
    if (sp2E < 0) {
        playerInitMoveParams();
    }
    if (sp2E != sp2C) {
        switch (sp2C) {
            case 0:
                if (G04_P->unk1F0 & 0x100) {
                    actorScriptStart(arg0, 0x1AD);
                } else {
                    actorScriptStartByIndex(arg0, 9);
                }
                scriptSetActorRampTarget(arg0, 1.0f, 0.0f);
                sp36 = 0xC;
                break;
            case 1:
                if (G04_P->unk1F0 & 0x100) {
                    actorScriptStart(arg0, 0x1AD);
                } else {
                    actorScriptStart(arg0, 0x13);
                }
                scriptSetActorRampTarget(arg0, 1.0f, 0.0f);
                sp36 = 0xC;
                break;
            case 2:
                actorScriptStartByIndex(arg0, 0x87);
                scriptSetActorRampTarget(arg0, 1.0f, 0.0f);
                sp36 = 0xC;
                break;
            case 3:
                if (G04_P->unk1F0 & 0x100) {
                    actorScriptStart(arg0, 0x76);
                    controllerAnimSetStateIfChanged(arg0, 0x2AC, 0.0f, 6.0f);
                } else {
                    controllerAnimSetStateRemap(arg0, 2, 0.0f, 6.0f);
                    actorScriptStartByIndex(arg0, 1);
                }
                if (sp2E == 4 || sp2E == 5) {
                    controllerAnimScaleInterpolate(arg0, 2);
                }
                sp36 = 0xD;
                break;
            case 4:
                actorScriptStartByIndex(arg0, 2);
                controllerAnimSetStateRemap(arg0, 3, 0.0f, 6.0f);
                if (sp2E == 3) {
                    switch (gPlayerCharacterId[gCurrentPlayerIndex]) {
                        case 0:
                        case 1:
                        case 2:
                        case 3:
                            controllerAnimScaleInterpolate(arg0, 4);
                            break;
                    }
                }
                if (sp2E == 5) {
                    controllerAnimScaleInterpolate(arg0, 2);
                }
                sp36 = 0xD;
                break;
            case 5:
                actorScriptStartByIndex(arg0, 3);
                controllerAnimSetStateRemap(arg0, 4, 0.0f, 6.0f);
                if (sp2E == 3 || sp2E == 4) {
                    controllerAnimScaleInterpolate(arg0, 4);
                }
                sp36 = 0xD;
                break;
            case 6:
                actorScriptStartByIndex(arg0, 0x1B);
                actorScriptExecute(arg0);
                gCurrentActor->peakY = gCurrentActor->y;
                sp36 = 0x1E;
                break;
        }
        G04_P->unk4C = sp2C;
    }
    if (G04_P->unk4C >= 3) {
        if (G04_P->unk26 == 100) {
            scale = ((G04ActorView *)arg0)->unkB8;
        } else {
            scale = G04_P->unk4;
        }
        scale = scale * 0.025;
        if (G04_P->unk4C == 5) {
            scale = scale * 0.6;
        }
        if (scale > 1.25f) {
            scale = scale - (scale - 1.25f) * 0.4;
        }
        if ((*(G04Model **)arg0->sub4)->unk24 != 0.0f) {
            if (G04_P->unk26 == 100) {
                scriptSetActorRampTarget(arg0, scale, 2.0f);
            } else {
                if (scale < 0.5) {
                    scale = 0.5f;
                }
                scriptSetActorRampTarget(arg0, scale, 10.0f);
            }
        }
    }
    return sp36;
}

s16 func_806CE174(Actor *arg0, f32 arg1, f32 arg2, s32 arg3) {
    s16 sp36;
    f32 scale;
    s16 sp2E;
    s16 sp2C;

    sp36 = arg0->state;
    sp2E = G04_P->unk4C;
    sp2C = playerSelectMoveTier(arg0, arg1, arg2, G04_P->unk4C, gCurrentCharacterIndex);
    ((G04ActorView *)arg0)->unkC0 = 0.0f;
    if (sp2E < 0) {
        playerInitMoveParams();
    }
    if (sp2E != sp2C) {
        switch (sp2C) {
            case 0:
                actorScriptStartByIndex(arg0, 0x51);
                scriptSetActorRampTarget(arg0, 1.0f, 0.0f);
                sp36 = 0x5D;
                break;
            case 1:
                actorScriptStart(arg0, 0x23);
                scriptSetActorRampTarget(arg0, 1.0f, 0.0f);
                sp36 = 0x5D;
                break;
            case 3:
                actorScriptStartByIndex(arg0, 0x57);
                controllerAnimSetStateRemap(arg0, 0x5C, 0.0f, 6.0f);
                if (sp2E == 4 || sp2E == 5) {
                    controllerAnimScaleInterpolate(arg0, 2);
                }
                sp36 = 0x5E;
                break;
            case 4:
                actorScriptStartByIndex(arg0, 0x56);
                controllerAnimSetStateRemap(arg0, 0x58, 0.0f, 6.0f);
                if (sp2E == 3) {
                    switch (gPlayerCharacterId[gCurrentPlayerIndex]) {
                        case 0:
                        case 1:
                        case 2:
                        case 3:
                            controllerAnimScaleInterpolate(arg0, 4);
                            break;
                    }
                }
                if (sp2E == 5) {
                    controllerAnimScaleInterpolate(arg0, 0xA);
                }
                sp36 = 0x5E;
                break;
            case 5:
                actorScriptStartByIndex(arg0, 0x55);
                controllerAnimSetStateRemap(arg0, 0x60, 0.0f, 6.0f);
                switch (gPlayerCharacterId[gCurrentPlayerIndex]) {
                    case 4:
                    case 5:
                        if (sp2E == 3) {
                            controllerAnimScaleInterpolate(arg0, 8);
                        }
                        break;
                    default:
                        if (sp2E == 3 || sp2E == 4) {
                            controllerAnimScaleInterpolate(arg0, 0);
                        }
                        break;
                }
                sp36 = 0x5E;
                break;
            case 6:
                actorScriptStartByIndex(arg0, 0x58);
                actorScriptExecute(arg0);
                gCurrentActor->peakY = gCurrentActor->y;
                sp36 = 0x1F;
                break;
        }
        G04_P->unk4C = sp2C;
    }
    if (G04_P->unk4C >= 3) {
        scale = ((G04ActorView *)arg0)->unkB8;
        scale = scale * 0.025;
        if (G04_P->unk4C == 5) {
            scale = scale * 0.6;
        }
        if (scale > 1.25f) {
            scale = scale - (scale - 1.25f) * 0.4;
        }
        if ((*(G04Model **)arg0->sub4)->unk24 != 0.0f) {
            scriptSetActorRampTarget(arg0, scale, 2.0f);
        }
    }
    return sp36;
}

s16 func_806CE4E4(Actor *arg0, f32 arg1, f32 arg2, s32 arg3) {
    s16 sp36;
    f32 scale;
    s16 sp2E;
    s16 sp2C;

    sp36 = arg0->state;
    sp2E = G04_P->unk4C;
    sp2C = func_806CE7A0(arg0, arg1, arg2, G04_P->unk4C, gCurrentCharacterIndex);
    ((G04ActorView *)arg0)->unkC0 = 0.0f;
    if (sp2E < 0) {
        playerInitNormalMoveParams();
    }
    if (sp2E != sp2C) {
        switch (sp2C) {
            case 0:
            case 1:
            case 2:
                actorScriptStart(arg0, 0x150);
                scriptSetActorRampTarget(arg0, 1.0f, 0.0f);
                sp36 = 0x3F;
                break;
            case 4:
                actorScriptStart(arg0, 0x151);
                controllerAnimSetStateIfChanged(arg0, 0x163, 0.0f, 6.0f);
                if (sp2E == 5) {
                    controllerAnimScaleInterpolate(arg0, 4);
                }
                sp36 = 0x40;
                break;
            case 5:
                actorScriptStart(arg0, 0x152);
                controllerAnimSetStateIfChanged(arg0, 0x162, 0.0f, 6.0f);
                if (sp2E == 4) {
                    controllerAnimScaleInterpolate(arg0, 0xC);
                }
                sp36 = 0x40;
                break;
            case 6:
                actorScriptStartByIndex(arg0, 0x1B);
                actorScriptExecute(arg0);
                gCurrentActor->peakY = gCurrentActor->y;
                sp36 = 0x1E;
                break;
        }
        G04_P->unk4C = sp2C;
    }
    if (G04_P->unk4C >= 3) {
        if (G04_P->unk26 == 100) {
            scale = ((G04ActorView *)arg0)->unkB8;
        } else {
            scale = G04_P->unk4;
        }
        scale = scale * 0.025;
        if (G04_P->unk4C == 5) {
            scale = scale * 0.6;
        }
        if (scale > 1.25f) {
            scale = scale - (scale - 1.25f) * 0.4;
        }
        if ((*(G04Model **)arg0->sub4)->unk24 != 0.0f) {
            if (G04_P->unk26 == 100) {
                scriptSetActorRampTarget(arg0, scale, 2.0f);
            } else {
                if (scale < 0.5) {
                    scale = 0.5f;
                }
                scriptSetActorRampTarget(arg0, scale, 10.0f);
            }
        }
    }
    return sp36;
}

s16 func_806CE7A0(Actor *arg0, f32 arg1, f32 arg2, s16 arg3, s16 arg4) {
    f32 max;

    if (arg2 < arg1) {
        max = arg1;
    } else {
        max = arg2;
    }
    if ((arg0->contactFlags | arg0->prevContactFlags) & 1) {
        switch (arg3) {
            case 0:
            case 1:
            case 2:
                if (arg2 != 0.0f) {
                    if (arg2 < D_807531C4[arg4]) {
                        arg3 = 4;
                    } else {
                        arg3 = 5;
                    }
                }
                break;
            case 4:
                if (arg2 < D_80753170[arg4]) {
                    arg3 = 0;
                } else if (D_807531C4[arg4] < arg2) {
                    arg3 = 5;
                }
                break;
            case 5:
                if (max < D_807531E0[arg4]) {
                    arg3 = 4;
                }
                break;
            default:
                if (arg1 < D_80753170[arg4]) {
                    arg3 = 0;
                } else if (arg1 < D_807531E0[arg4]) {
                    arg3 = 4;
                } else {
                    arg3 = 5;
                }
                break;
        }
    } else {
        arg3 = 6;
    }
    return arg3;
}

typedef struct G05PlayerView {
    /* 0x000 */ s16 unk0;
    /* 0x002 */ u8 pad2[0x4C - 2];
    /* 0x04C */ s16 unk4C;
    /* 0x04E */ u8 pad4E[0x78 - 0x4E];
    /* 0x078 */ f32 unk78;
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ s16 unk80;
    /* 0x082 */ u8 pad82[2];
    /* 0x084 */ u32 unk84;
    /* 0x088 */ u8 pad88[0xD0 - 0x88];
    /* 0x0D0 */ u32 unkD0;
    /* 0x0D4 */ u8 padD4[0x1AC - 0xD4];
    /* 0x1AC */ Actor *unk1AC;
    /* 0x1B0 */ Actor *unk1B0;
    /* 0x1B4 */ u8 pad1B4[4];
    /* 0x1B8 */ u16 unk1B8;
    /* 0x1BA */ u8 pad1BA[2];
    /* 0x1BC */ f32 unk1BC;
} G05PlayerView;

#define G05_P ((G05PlayerView *)gActivePlayerState)

typedef struct G05Model {
    /* 0x00 */ u8 pad0[0x24];
    /* 0x24 */ f32 unk24;
} G05Model;

s32 playerSelectCarryMoveTier(f32, f32);

s16 playerSelectCarryMoveState(Actor *arg0, f32 arg1, f32 arg2, s32 arg3) {
    s16 sp26;
    s16 sp24;
    f32 scale;
    s16 sp1E;
    s16 sel;

    sp26 = arg0->state;
    sp1E = G05_P->unk4C;
    sel = playerSelectCarryMoveTier(arg1, arg2);
    if (sp1E < 0) {
        playerInitMoveParams();
    }
    if (sp1E != sel) {
        switch (sel) {
            case 0:
                switch ((u32)G05_P->unk1AC->actorType) {
                    case 0x3D:
                    case 0x3F:
                    case 0x40:
                    case 0x41:
                    case 0x42:
                    case 0x55:
                    case 0x82:
                        actorScriptStart(gActivePlayerActor, 0x1C9);
                        break;
                    default:
                        actorScriptStartByIndex(arg0, 0x2E);
                        break;
                }
                G05_P->unk4C = 0;
                sp26 = 0x48;
                break;
            case 1:
                switch ((u32)G05_P->unk1AC->actorType) {
                    case 0x3D:
                    case 0x3F:
                    case 0x40:
                    case 0x41:
                    case 0x42:
                    case 0x43:
                    case 0x55:
                    case 0x82:
                        actorScriptStart(gActivePlayerActor, 0x1CA);
                        break;
                    default:
                        actorScriptStartByIndex(arg0, 0x2F);
                        break;
                }
                G05_P->unk4C = 1;
                sp26 = 0x49;
                break;
        }
    }
    if (G05_P->unk4C > 0) {
        scale = arg0->speedXZ * 0.025;
        scale = scale * 0.75 + 0.25;
        if ((*(G05Model **)arg0->sub4)->unk24 != 0.0f) {
            scriptSetActorRampTarget(arg0, scale, 2.0f);
        }
    }
    return sp26;
}

extern f32 D_807532B8[];

s32 playerSelectCarryMoveTier(f32 arg0, f32 arg1) {
    s32 ret = G05_P->unk4C;

    switch (ret) {
        case 0:
            if (arg1 != 0.0f) {
                ret = 1;
            }
            break;
        case 1:
            if (arg1 == 0.0f && arg0 < D_807532B8[gCurrentCharacterIndex]) {
                ret = 0;
            }
            break;
        default:
            if (arg0 < D_807532B8[gCurrentCharacterIndex]) {
                ret = 0;
            } else {
                ret = 1;
            }
            break;
    }
    return ret;
}

extern s16 D_807532A8[];
f32 mathAngleBetweenPointsDeg(s16, s16, s16, s16);

void playerStartPickupApproach(Actor *arg0) {
    f32 radius;
    f32 ang;
    f32 sp40[4][4];
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    s32 div = 15;

    switch ((u32)arg0->actorType) {
        case 0x3D:
        case 0x3F:
        case 0x40:
        case 0x41:
        case 0x42:
        case 0x43:
        case 0x55:
        case 0x82:
            radius = 30.0f;
            break;
        default:
            radius = D_807532A8[gCurrentCharacterIndex];
            break;
    }
    if (gActivePlayerState->stateFlags & 0x01000000) {
        ang = gCurrentActor->yaw * 0x168 / 4096;
    } else {
        ang = mathAngleBetweenPointsDeg(arg0->x, arg0->z, gCurrentActor->x, gCurrentActor->z);
        ang = 360.0 - ang;
    }
    G05_P->unk80 = ang * 4095.0 / 360.0;
    guRotateF(sp40, ang, 0.0f, 1.0f, 0.0f);
    guMtxXFMF(sp40, 0.0f, 0.0f, radius, &sp3C, &sp38, &sp34);
    G05_P->unk78 = ((arg0->x - sp3C) - gCurrentActor->x) / (f32)div;
    G05_P->unk7C = ((arg0->z - sp34) - gCurrentActor->z) / (f32)div;
}

typedef struct G05Node {
    /* 0x00 */ void *unk0;
    /* 0x04 */ u8 unk4;
    /* 0x05 */ u8 pad5[3];
    /* 0x08 */ f32 unk8;
    /* 0x0C */ Actor *unkC;
    /* 0x10 */ Actor *unk10;
} G05Node;

void playerHeldActorFollowStep();
void *heapAlloc(s32);
void actorRegisterGlobalCallback(void *);

void playerRegisterHeldActorFollow(f32 arg0) {
    G05Node *node;

    if (G05_P->unk1AC != NULL) {
        node = heapAlloc(0x14);
        node->unk0 = playerHeldActorFollowStep;
        node->unk8 = arg0;
        node->unkC = gCurrentActor;
        node->unk10 = G05_P->unk1AC;
        node->unk4 = 0;
        actorRegisterGlobalCallback(node);
    }
}

s32 playerGetHoldNodeIndices(s32 *, s32 *);
void actorGetNodePos(void *, s32, f32 *, f32 *, f32 *);

void playerComputePickupHoldPitch(void) {
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    f32 dist;
    f32 sp28;
    s32 sp24;
    s32 sp20;

    playerGetHoldNodeIndices(&sp24, &sp20);
    actorGetNodePos(gCurrentActor, sp24, &sp40, &sp38, &sp30);
    actorGetNodePos(gCurrentActor, sp20, &sp44, &sp3C, &sp34);
    sp28 = sp3C - sp38;
    dist = sqrtf((sp34 - sp30) * (sp34 - sp30) + (sp44 - sp40) * (sp44 - sp40));
    G05_P->unk1BC = 0.0 - mathAtan2(sp28, dist) * 57.29577637f + 270.0;
}


typedef struct HeldActorFollowArg {
    /* 0x0 */ f32 unk0;
    /* 0x4 */ Actor *unk4;
    /* 0x8 */ Actor *unk8;
} HeldActorFollowArg;

void actorAppendCallbackPayloadA70C(s32, Actor *, f32, f32, f32, u8, u8);

void playerHeldActorFollowStep(HeldActorFollowArg *arg0) {
    f32 nodeX[2];
    f32 nodeY[2];
    f32 nodeZ[2];
    f32 midX;
    f32 midY;
    f32 midZ;
    f32 outX;
    f32 outY;
    f32 outZ;
    s32 idxA;
    s32 idxB;

    playerGetHoldNodeIndices(&idxA, &idxB);
    actorGetNodePos(arg0->unk4, idxA, &nodeX[0], &nodeY[0], &nodeZ[0]);
    actorGetNodePos(arg0->unk4, idxB, &nodeX[1], &nodeY[1], &nodeZ[1]);
    midX = (nodeX[0] + nodeX[1]) / 2;
    midY = (nodeY[0] + nodeY[1]) / 2;
    midZ = (nodeZ[0] + nodeZ[1]) / 2;
    outX = (midX - arg0->unk8->x) * arg0->unk0 + arg0->unk8->x;
    outY = (midY - arg0->unk8->y) * arg0->unk0 + arg0->unk8->y;
    outZ = (midZ - arg0->unk8->z) * arg0->unk0 + arg0->unk8->z;
    actorAppendCallbackPayloadA70C((s32)arg0->unk4, arg0->unk8, outX, outY, outZ, 2, 1);
}

typedef struct G05Node2 {
    /* 0x00 */ void *unk0;
    /* 0x04 */ u8 unk4;
    /* 0x05 */ u8 pad5[3];
    /* 0x08 */ Actor *unk8;
    /* 0x0C */ Actor *unkC;
    /* 0x10 */ s32 unk10;
} G05Node2;

void func_806CF138();

void playerRegisterHeldActorAlign(void) {
    G05Node2 *node;

    if (G05_P->unk1AC != NULL) {
        node = heapAlloc(0x14);
        node->unk0 = func_806CF138;
        node->unk8 = gCurrentActor;
        node->unkC = G05_P->unk1AC;
        node->unk4 = 0;
        actorRegisterGlobalCallback(node);
    }
}

typedef struct G05CbArg2 {
    /* 0x0 */ Actor *unk0;
    /* 0x4 */ Actor *unk4;
} G05CbArg2;

f32 acosApprox(f32);
f32 asinApprox(f32);
void func_8067AA58(Actor *, Actor *, f32, f32);

void func_806CF138(G05CbArg2 *arg0) {
    f32 sp74;
    f32 sp70;
    f32 sp6C;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 dir[2];
    f32 delta[2];
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    s32 sp30;
    s32 sp2C;

    playerGetHoldNodeIndices(&sp30, &sp2C);
    actorGetNodePos(arg0->unk0, sp30, &sp70, &sp68, &sp60);
    actorGetNodePos(arg0->unk0, sp2C, &sp74, &sp6C, &sp64);
    sp5C = sp6C - sp68;
    sp58 = sqrtf((sp64 - sp60) * (sp64 - sp60) + ((sp74 - sp70) * (sp74 - sp70) + sp5C * sp5C));
    sp54 = asinApprox(sp5C / sp58) * 57.29577637f;
    dir[0] = mathSinF(arg0->unk0->yaw) * 50.0f;
    dir[1] = mathCosF(arg0->unk0->yaw) * 50.0f;
    delta[0] = sp74 - sp70;
    delta[1] = sp64 - sp60;
    sp3C = dir[0] * delta[0] + dir[1] * delta[1];
    sp38 = sqrtf(dir[0] * dir[0] + dir[1] * dir[1]);
    sp34 = sqrtf(delta[0] * delta[0] + delta[1] * delta[1]);
    func_8067AA58(arg0->unk0, arg0->unk4, sp54, 90.0 - acosApprox(sp3C / (sp38 * sp34)) * 57.29577637f);
}

s32 playerGetHoldNodeIndices(s32 *arg0, s32 *arg1) {
    s32 ret = 0;

    if (gCurrentActor->actorType == 6) {
        switch (G05_P->unk1B8) {
            case 0x82:
                *arg0 = 0x13;
                *arg1 = 0x14;
                ret = 1;
                break;
            case 0x3D:
            case 0x3F:
            case 0x40:
            case 0x41:
            case 0x42:
            case 0x43:
            case 0x55:
                *arg0 = 0x12;
                *arg1 = 0x11;
                ret = 1;
                break;
                return ret;
        }
    }
    if (ret == 0) {
        *arg0 = 2;
        *arg1 = 3;
    }
}

extern s32 D_80753428[];
extern f32 D_8075340C[];
void actorAppendCallback4000(Actor *, Actor *, s16, s32, s32);

void playerThrowHeldActor(Actor *arg0) {
    G05PlayerView *p;

    if (arg0->collisionFlags & 1) {
        p = arg0->customState;
        if (p->unk1AC != NULL) {
            actorAppendCallback4000(gCurrentActor, p->unk1AC, gActivePlayerActor->yaw, D_80753428[gCurrentCharacterIndex], (s32)D_8075340C[gCurrentCharacterIndex]);
            p->unk1AC = NULL;
            p->unk1B0 = NULL;
        }
    }
}

void actorAppendCallback(Actor *, s32, s32, u8, s32, void *);

void playerDropHeldActor(Actor *arg0) {
    G05PlayerView *p;

    if (arg0->collisionFlags & 1) {
        p = arg0->customState;
        if (p->unk1AC != NULL) {
            actorAppendCallback(p->unk1AC, (s32)arg0, 8, 0, 0, NULL);
        } else if (p->unk1B0 != NULL) {
            actorAppendCallback(p->unk1B0, (s32)arg0, 8, 0, 0, NULL);
        }
        p->unk1AC = NULL;
        p->unk1B0 = NULL;
    }
}

typedef struct G05Slot {
    /* 0x0 */ u8 unk0;
    /* 0x1 */ u8 pad1[3];
    /* 0x4 */ Actor *unk4;
    /* 0x8 */ u8 pad8[0x2E8];
} G05Slot;

#define G05_SLOTS ((G05Slot *)gPlayerSlots)


void actorReleaseFromPlayerHold(Actor *arg0) {
    s32 i;
    G05PlayerView *p;

    for (i = 0; i < gPlayerCount; i++) {
        if (G05_SLOTS[i].unk0 != 0) {
            p = G05_SLOTS[i].unk4->customState;
            if ((arg0 == p->unk1AC && p->unk1AC != NULL) || (arg0 == p->unk1B0 && p->unk1B0 != NULL)) {
                p->unk1AC = NULL;
                p->unk1B0 = NULL;
                playerResumeLocomotion(G05_SLOTS[i].unk4);
            }
        }
    }
}

extern u8 D_80750AD0;
extern u8 D_8071FC40;
void effectWobbleRiseUpdate(void);
void animSetSpeed(void *, s32, f32);
void animSetLoopMode(void *, s32, s32);
void animSetDirection(void *, s32, s32);
void animResetEndFrame(void *, s32);
void animSetStartFrame(void *, s32, s32);
void animSetLoopLimit(void *, s32, s32);
void animSetFrameAndSubframe(void *, s32, s16, f32);
s32 func_8072881C(s32, void *);
u32 randomLcgNext(void);

void func_806CF580(void) {
    if (!(gCurrentActor->flags & 0x10)) {
        G05_P->unk84 = gFrameCounter;
        G05_P->unkD0 = gFrameCounter;
    }
    if (gPlayerCharacterId[gCurrentPlayerIndex] == 1) {
        if (gCurrentActor->state == 0x36 && G05_P->unk0 != 0x36) {
            animSetFrameAndSubframe(gCurrentActor, 1, 0, 6.0f);
        }
        if (gCurrentActor->state == 0x36) {
            animSetSpeed(gCurrentActor, 0, 0.5f);
            animSetLoopMode(gCurrentActor, 0, 0);
            animSetDirection(gCurrentActor, 0, 0);
            animResetEndFrame(gCurrentActor, 0);
            animSetStartFrame(gCurrentActor, 0, 4);
            animSetLoopLimit(gCurrentActor, 0, 2);
            animSetSpeed(gCurrentActor, 1, 0.5f);
            animSetLoopMode(gCurrentActor, 1, 0);
            animSetDirection(gCurrentActor, 1, 0);
            animResetEndFrame(gCurrentActor, 1);
            animSetStartFrame(gCurrentActor, 1, 4);
            animSetLoopLimit(gCurrentActor, 1, 2);
        }
        if (gCurrentActor->state != 0x36) {
            if (G05_P->unk0 == 0x36) {
                G05_P->unk84 = 0;
            }
        }
    }
    if (gCurrentActor->state != 0x36 && func_8072881C(0, &G05_P->unk84) != 0 &&
        (gPlayerCharacterId[gCurrentPlayerIndex] == 1 || (gPlayerCount == 1 && gPlayerCharacterId[gCurrentPlayerIndex] == 3))) {
        func_8072881C(0x81, &G05_P->unk84);
    }
    if ((gCurrentActor->state == 0x4F || gCurrentActor->state == 0x7F) && D_80750AD0 == 0 &&
        (u32)(G05_P->unkD0 + 9) < (u32)gFrameCounter && randomLcgNext() % 2500 / 200 == 0) {
        effectSetCallback(effectWobbleRiseUpdate);
        effectSetDepth(1);
        effectSetDuration(-1);
        effectCreateAtActorBone(&D_8071FC40, 0, gCurrentActor, 4, 0);
        G05_P->unkD0 = gFrameCounter;
    }
}

void effectSetMode(s32);

void func_806CF878(void) {
    if (!(gFrameCounter & 3) && G02_A->unk155 >= 5 && G03_A->unkC0 > 30.0f) {
        effectSetMode(2);
        effectSetDepth(1);
        effectSetCallback(&effectZSpinMatrixUpdate);
        effectCreateAtPosition(&D_8071FB08, 0.8f, G03_A->unk7C, G03_A->unk80, G03_A->unk84);
    }
}

extern s32 D_8071FF40;
extern s32 effectSpiralDriftMatrixUpdate;

void func_806CF918(void) {
    s32 i;

    for (i = 0; i != 0xC8; i += 0x28) {
        effectSetCallback(&effectSpiralDriftMatrixUpdate);
        effectSetDepth(1);
        effectSetSpeed(i);
        effectSetDuration(0x45);
        effectCreateAtActorBone(&D_8071FF40, 0.05f, gCurrentActor, 6, 2);
    }
}

typedef struct G06PlayerView {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ u8 pad8[0x20];
    /* 0x28 */ s16 unk28;
    /* 0x2A */ u8 pad2A[2];
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ u8 pad3C[0xC];
    /* 0x48 */ s16 unk48;
    /* 0x4A */ u8 pad4A[2];
    /* 0x4C */ s16 unk4C;
    /* 0x4E */ u8 pad4E[2];
    /* 0x50 */ s16 unk50;
    /* 0x52 */ u8 pad52[0x36];
    /* 0x88 */ Actor *unk88;
    /* 0x8C */ u8 unk8C;
    /* 0x8D */ u8 pad8D[0xE8 - 0x8D];
    /* 0xE8 */ u8 unkE8;
    /* 0xE9 */ u8 padE9[0xF0 - 0xE9];
    /* 0xF0 */ f32 unkF0;
    /* 0xF4 */ u8 padF4[0x10C - 0xF4];
    /* 0x10C */ u8 unk10C;
    /* 0x10D */ u8 pad10D[0x1AC - 0x10D];
    /* 0x1AC */ s32 unk1AC;
    /* 0x1B0 */ u8 pad1B0[0x1F0 - 0x1B0];
    /* 0x1F0 */ s32 unk1F0;
} G06PlayerView;

#define G06_P ((G06PlayerView *)gActivePlayerState)

u8 playerProbeLedgeAhead(Actor *, f32 *, u8, f32);
s32 actorAngleInArc(Actor *, s16);
s32 func_80666AEC(void);
void collisionGetCoords(void *, s16 *);
extern f32 D_80753E10[];
extern s16 D_80753E00[];

void playerCheckLedgeGrab(void) {
    f32 sp3C;
    u8 sp3B;
    s16 sp38;
    s16 sp36;
    u8 notWall;
    u8 hit;
    u8 flag;
    s32 pad[2];

    if (!(gGlobalOverlayFlags & 0x20000) && gCurrentActor->hasArcBounds != 0 && G06_P->unk8C == 0 && !(gCurrentActor->contactFlags & 1) && G06_P->unkE8 != 0) {
        flag = (gCurrentMap == 0x53 || gCurrentMap == 0xC5) ? 1 : 0;
        notWall = actorAngleInArc(gCurrentActor, gCurrentActor->yaw) == 0;
        if (notWall || !(D_80753E10[gCurrentCharacterIndex] < gCurrentActor->speedXZ) || flag != 0) {
            sp3B = playerProbeLedgeAhead(gCurrentActor, &sp3C, notWall, flag ? 30.0 : 15.0);
            collisionGetCoords(&sp38, &sp36);
            hit = 0;
            if (sp3B != 0 && G03_A->unkC0 < 0.0 && sp36 >= 0x385) {
                hit = 0;
                if (func_80666AEC() != 0) {
                    if (gCurrentActor->y - gCurrentActor->floorY > 15.0f) {
                        if (flag != 0) {
                            if (D_80753E00[gCurrentCharacterIndex] + gCurrentActor->y < sp3C + 15.0f && sp3C - D_80753E00[gCurrentCharacterIndex] - gCurrentActor->y < 80.0f) {
                                hit = 1;
                            }
                        } else {
                            if (D_80753E00[gCurrentCharacterIndex] + gCurrentActor->y < sp3C - 5.0f && sp3C - D_80753E00[gCurrentCharacterIndex] - gCurrentActor->y < 15.0f) {
                                hit = 1;
                            }
                        }
                    }
                }
            }
            if (hit != 0 && playerStateQueueCallback(0xA, NULL, gCurrentPlayerIndex) != 0) {
                G06_P->unkF0 = sp3C;
            }
        }
    }
}

u8 collisionCheckActorFloor(Actor *, f32, f32, f32, f32 *);
u8 func_80666AE0(void);

u8 playerProbeLedgeAhead(Actor *arg0, f32 *arg1, u8 arg2, f32 arg3) {
    f32 dx;
    f32 dz;
    s16 angle;
    u8 ret;

    angle = arg0->yaw;
    if (!arg2) {
        angle = (angle + 0x800) & 0xFFF;
    }
    dx = mathSinF(angle) * arg3;
    dz = mathCosF(angle) * arg3;
    ret = collisionCheckActorFloor(arg0, arg0->x + dx, arg0->y + 30.0f, arg0->z + dz, arg1);
    ((G02ActorView *)arg0)->unk78 = func_80666AE0();
    return ret;
}

void playerSetBaseGravity(void);

void playerSetBaseGravityIfFalling(void) {
    if (G03_A->unkC0 < 0.0f) {
        playerSetBaseGravity();
    }
}

extern f32 D_80753700[];

void playerSetTerminalVelocity700(void) {
    if (G03_A->unkC0 < 0.0f) {
        ((G03ActorView *)gCurrentActor)->unkC4 = D_80753700[gCurrentCharacterIndex];
    }
}

extern f32 D_80753658[];

void playerSetTerminalVelocity658(void) {
    if (G03_A->unkC0 < 0.0f) {
        ((G03ActorView *)gCurrentActor)->unkC4 = D_80753658[gCurrentCharacterIndex];
    }
}

extern f32 D_80753754[];

void playerSetTerminalVelocity754(void) {
    if (G03_A->unkC0 < 0.0f) {
        ((G03ActorView *)gActivePlayerActor)->unkC4 = D_80753754[gCurrentCharacterIndex];
    }
}

extern f32 D_80753578[];

void playerSetBaseGravity(void) {
    ((G03ActorView *)gActivePlayerActor)->unkC4 = D_80753578[gCurrentCharacterIndex];
}

extern f32 D_80753594[];

void playerSetTerminalVelocity594(void) {
    ((G03ActorView *)gActivePlayerActor)->unkC4 = D_80753594[gCurrentCharacterIndex];
}

extern f32 D_807535B0[];

void playerSetTerminalVelocity5B0(void) {
    ((G03ActorView *)gActivePlayerActor)->unkC4 = D_807535B0[gCurrentCharacterIndex];
}

extern f32 D_807536E4[];

void playerSetTerminalVelocity6E4(void) {
    ((G03ActorView *)gActivePlayerActor)->unkC4 = D_807536E4[gCurrentCharacterIndex];
}

void playerEnterFall(Actor *arg0) {
    G03_A->unkC0 = 0.0f;
    actorScriptStartByIndex(arg0, 0x1B);
    actorScriptExecute(arg0);
    gCurrentActor->peakY = gCurrentActor->y;
    if (G06_P->unk8C) {
        arg0->state = 0x1F;
        arg0->unk155[0] = 0;
    } else {
        arg0->state = 0x1E;
        arg0->unk155[0] = 0;
    }
}

s16 func_806CDD24(Actor *, f32, f32, s32);
s16 func_806CE174(Actor *, f32, f32, s32);
s16 func_806CE4E4(Actor *, f32, f32, s32);
void actorSetInteractionTimer(Actor *);
void func_806D0150(Actor *);

void playerResumeLocomotion(Actor *arg0) {
    G06PlayerView *p = arg0->customState;
    u8 temp;

    arg0->contactFlags &= ~0x20;
    p->unk4C = -1;
    p->unk10C = 0;
    if (arg0->unk144 == 1) {
        actorSetInteractionTimer(arg0);
    }
    if (gGlobalOverlayFlags & 0x80000) {
        if (p->unk88 != NULL && p->unk88->actorType == 0x1D) {
            func_806D0150(arg0);
            return;
        }
    }
    if (gPlayerCharacterId[gCurrentPlayerIndex] == 7) {
        arg0->state = 0x7E;
        arg0->unk155[0] = 0;
        return;
    }
    if ((p->unk1F0 & 0x20) && gPlayerCount == 1) {
        temp = func_806CE4E4(arg0, arg0->speedXZ, p->unk4, 1);
        arg0->state = temp;
        arg0->unk155[0] = 0;
        if (temp == 0x3F) {
            arg0->unk155[0] = 1;
        }
    } else if (p->unk1AC != 0) {
        arg0->state = playerSelectCarryMoveState(arg0, arg0->speedXZ, p->unk4, 1);
        arg0->unk155[0] = 0;
    } else if (p->unk8C != 0) {
        temp = func_806CE174(arg0, arg0->speedXZ, p->unk4, 1);
        if (arg0->state != 2) {
            arg0->state = temp;
            arg0->unk155[0] = 0;
        }
    } else {
        temp = func_806CDD24(arg0, arg0->speedXZ, p->unk4, 1);
        if (arg0->state != 2) {
            arg0->state = temp;
            arg0->unk155[0] = 0;
        }
    }
}

void func_806D0150(Actor *arg0) {
    arg0->contactFlags &= ~0x20;
    G06_P->unk4C = -1;
    G06_P->unk10C = 0;
    actorScriptStartByIndex(arg0, 0x7A);
    arg0->state = 7;
    arg0->unk155[0] = 0;
}

extern s16 D_80753328[];
extern f32 D_807532F0[];
extern f32 D_8075330C[];
extern f32 D_807532B8[];
extern f32 D_807532D4[];

void playerSetCarryMoveParams(void) {
    G06_P->unk48 = D_80753328[gCurrentCharacterIndex];
    G06_P->unk2C = D_807532F0[gCurrentCharacterIndex];
    G06_P->unk30 = D_8075330C[gCurrentCharacterIndex];
    G06_P->unk34 = D_807532B8[gCurrentCharacterIndex];
    G06_P->unk38 = D_807532D4[gCurrentCharacterIndex];
}

extern f32 D_80753338[];

void playerSetNormalMoveParams(void) {
    G06_P->unk48 = D_8075326C[gCurrentCharacterIndex];
    G06_P->unk2C = D_80753234[gCurrentCharacterIndex];
    G06_P->unk30 = D_80753250[gCurrentCharacterIndex];
    G06_P->unk34 = D_80753170[gCurrentCharacterIndex];
    if (G06_P->unk8C != 0) {
        G06_P->unk38 = D_80753338[gCurrentCharacterIndex];
        return;
    }
    if ((gActivePlayerState->stateFlags & 0x20) || D_807463B8 == 3) {
        if (gCurrentMap == 0x30) {
            G06_P->unk38 = 200.0f;
            return;
        }
        G06_P->unk38 = D_80753218[gCurrentCharacterIndex];
        return;
    }
    G06_P->unk38 = D_807531FC[gCurrentCharacterIndex];
}

void playerSetTerminalVelocity578(void) {
    ((G03ActorView *)gActivePlayerActor)->unkC4 = D_80753578[gCurrentCharacterIndex];
    G06_P->unk50 = 0;
    G06_P->unk28 = 1;
}

void playerSetNormalMoveParams(void);

void playerInitMoveParams(void) {
    if (G06_P->unk1AC != 0) {
        playerSetCarryMoveParams();
    } else {
        playerSetNormalMoveParams();
    }
    playerSetTerminalVelocity578();
}

void playerInitNormalMoveParams(void) {
    playerSetNormalMoveParams();
    playerSetTerminalVelocity578();
}

extern f32 gPlayerLargeModeScale;

void playerSetLargeModeScale(f32 arg0) {
    if (arg0 != 0.0f) {
        gPlayerLargeModeScale = arg0;
    } else {
        gPlayerLargeModeScale = 0.3f;
    }
}

typedef struct G07PlayerSlot {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ void *unk4;
    /* 0x008 */ u8 pad8[0x2B8];
    /* 0x2C0 */ u8 unk2C0;
    /* 0x2C1 */ u8 pad2C1[0x2F];
} G07PlayerSlot;

typedef struct G07StateB {
    /* 0x000 */ u8 pad0[0x104];
    /* 0x104 */ void *unk104;
    /* 0x108 */ u8 pad108[0x1A4 - 0x108];
    /* 0x1A4 */ u8 unk1A4;
    /* 0x1A5 */ u8 pad1A5[0x1C0 - 0x1A5];
    /* 0x1C0 */ f32 unk1C0[3];
    /* 0x1CC */ f32 unk1CC[3];
    /* 0x1D8 */ f32 unk1D8;
    /* 0x1DC */ f32 unk1DC;
    /* 0x1E0 */ f32 unk1E0;
    /* 0x1E4 */ s32 unk1E4;
} G07StateB;

void camSetZoomLevel(void *, s32);

void playerSetSizeMode(Actor *arg0, u8 arg1) {
    G07StateB *state = arg0->customState;
    u8 slot = state->unk1A4;
    s32 i;
    f32 diff;
    f32 temp;

    state->unk1DC = 0.4f;
    state->unk1D8 = 0.004f;
    switch (arg1) {
        case 0:
            state->unk1C0[0] = 0.05f;
            state->unk1C0[1] = 0.05f;
            state->unk1C0[2] = 0.05f;
            break;
        case 2:
            state->unk1C0[0] = gPlayerLargeModeScale;
            state->unk1C0[1] = gPlayerLargeModeScale;
            state->unk1C0[2] = gPlayerLargeModeScale;
            break;
        default:
            state->unk1C0[0] = 0.15f;
            state->unk1C0[1] = 0.15f;
            state->unk1C0[2] = 0.15f;
            if (((G07PlayerSlot *)gPlayerSlots)[slot].unk2C0 == 0) {
                state->unk1DC = 0.05f;
                state->unk1D8 = 0.001f;
            }
            break;
    }
    if (arg1 != 1) {
        if (gPlayerCount == 1) {
            for (i = 0; i < 3; i++) {
                state->unk1CC[i] = state->unk1C0[i];
                (&arg0->sub4->scaleX)[i] = state->unk1C0[i];
            }
        }
    }
    ((G07PlayerSlot *)gPlayerSlots)[slot].unk2C0 = arg1;
    ((G07PlayerSlot *)gPlayerSlots)[slot].pad2C1[0] = 1;
    state->unk1E4 = 0;
    if (arg1 == 1 || gPlayerCount >= 2) {
        if (state->unk1CC[0] < state->unk1C0[0]) {
            diff = state->unk1C0[0] - state->unk1CC[0];
        } else {
            diff = -(state->unk1C0[0] - state->unk1CC[0]);
        }
        temp = diff / state->unk1D8;
        if (temp != 0.0f) {
            state->unk1E0 = state->unk1DC / temp;
        } else {
            state->unk1E0 = 99999.0f;
        }
    }
    camSetZoomLevel(state->unk104, 2);
}

#define G07_P ((G07StateB *)gActivePlayerState)

f32 sinApprox(f32);

void playerScaleTransitionStep(void) {
    if (G07_P->unk1CC[0] < G07_P->unk1C0[0]) {
        G07_P->unk1CC[0] = G07_P->unk1CC[0] + G07_P->unk1D8;
        G07_P->unk1CC[1] = G07_P->unk1CC[1] + G07_P->unk1D8;
        G07_P->unk1CC[2] = G07_P->unk1CC[2] + G07_P->unk1D8;
        if (G07_P->unk1C0[0] < G07_P->unk1CC[0]) {
            G07_P->unk1CC[0] = G07_P->unk1C0[0];
            G07_P->unk1CC[1] = G07_P->unk1C0[1];
            G07_P->unk1CC[2] = G07_P->unk1C0[2];
        }
    } else {
        G07_P->unk1CC[0] = G07_P->unk1CC[0] - G07_P->unk1D8;
        G07_P->unk1CC[1] = G07_P->unk1CC[1] - G07_P->unk1D8;
        G07_P->unk1CC[2] = G07_P->unk1CC[2] - G07_P->unk1D8;
        if (G07_P->unk1CC[0] < G07_P->unk1C0[0]) {
            G07_P->unk1CC[0] = G07_P->unk1C0[0];
            G07_P->unk1CC[1] = G07_P->unk1C0[1];
            G07_P->unk1CC[2] = G07_P->unk1C0[2];
        }
    }
    if (G07_P->unk1CC[0] == G07_P->unk1C0[0]) {
        gCurrentActor->sub4->scaleX = G07_P->unk1CC[0];
        gCurrentActor->sub4->scaleY = G07_P->unk1CC[1];
        gCurrentActor->sub4->scaleZ = G07_P->unk1CC[2];
        return;
    }
    gCurrentActor->sub4->scaleX = G07_P->unk1CC[0] + sinApprox(G07_P->unk1E4 * 0.11) * G07_P->unk1DC;
    gCurrentActor->sub4->scaleY = G07_P->unk1CC[1] + sinApprox(G07_P->unk1E4 * 0.2352) * G07_P->unk1DC;
    gCurrentActor->sub4->scaleZ = G07_P->unk1CC[2] + sinApprox(G07_P->unk1E4 * 0.176) * G07_P->unk1DC;
    G07_P->unk1DC = G07_P->unk1DC - G07_P->unk1E0;
    if (G07_P->unk1DC < 0.0) {
        G07_P->unk1DC = 0.0f;
    }
    G07_P->unk1E4 = G07_P->unk1E4 + 1;
}

s32 func_806D0964(s32 arg0, u8 arg1) {
    s16 type = *(s16 *)((u8 *)((G07PlayerSlot *)gPlayerSlots)[arg1].unk4 + 0x5A);

    if (type != 6) {
        if (type == 8) {
            if (arg0 & 2) {
                return 1;
            }
        }
    } else {
        if ((arg0 & 1) && ((G07PlayerSlot *)gPlayerSlots)[arg1].unk2C0 != 1) {
            return 1;
        }
    }
    return 0;
}

extern s32 gGlobalCutsceneFlags;
s32 collisionGetHitStatus();

typedef struct G07ActorD1 {
    /* 0x00 */ u8 pad0[0xD1];
    /* 0xD1 */ u8 unkD1;
} G07ActorD1;

void func_806D09E8(Actor *arg0) {
    u8 id;

    if (arg0->actorType == 4) {
        id = arg0->state;
        if (id == 0x3F || id == 0x40) {
            if (!(gGlobalCutsceneFlags & 0x40)) {
                if (collisionGetHitStatus() == 0) {
                    ((G07ActorD1 *)arg0)->unkD1 = 0x10;
                }
            }
        }
    }
}

void func_806D0A54(Actor *arg0, s32 arg1, s32 arg2) {
    if (arg1) {
        arg0->flags |= 4;
    } else {
        arg0->flags &= ~4;
    }
}

typedef struct G07TargetRef {
    /* 0x00 */ u8 pad0[0x64];
    /* 0x64 */ u16 unk64;
} G07TargetRef;

typedef struct G07Target {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ G07TargetRef *unk4;
    /* 0x08 */ u8 pad8[0x4C];
    /* 0x54 */ s32 unk54;
} G07Target;

typedef struct G07StateA {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ G07Target *unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u16 unkC;
    /* 0x0E */ u8 padE[2];
    /* 0x10 */ f32 unk10;
} G07StateA;

typedef struct G07ActorA {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ ActorSub4 *unk4;
    /* 0x008 */ u8 pad8[0x58];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u8 pad64[0x18];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x30];
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ u8 padBC[4];
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ u8 padC4[0x90];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 pad155[0x13];
    /* 0x168 */ s16 unk168;
    /* 0x16A */ u8 pad16A[6];
    /* 0x170 */ s32 pad170;
    /* 0x174 */ G07StateA *unk174;
} G07ActorA;

#define G07_A ((G07ActorA *)gCurrentActor)

void actorDespawn(Actor *);
s32 actorTableContains(void *);
void actorCopyPoseAndScale(void *, void *, s32, void *);
void actorUpdateModelMatrix(Actor *, s32);

void actorChildEffectUpdate(void) {
    G07StateA *state = G07_A->unk174;
    G07Target *target = state->unk4;
    f32 speed;
    s32 pad[1];
    f32 temp;

    if (!(G07_A->unk60 & 0x10)) {
        actorScriptStart(gCurrentActor, state->unk0);
        G07_A->unk60 |= 0x400;
        G07_A->unk168 = (randomNonNegative() >> 15) % 4096;
    }
    speed = (G07_A->unk4 != NULL ? G07_A->unk4->scaleY : 0.15f) * 6.66666667;
    if (actorTableContains(target) == 0 || target->unk54 != state->unk8) {
        actorDespawn(gCurrentActor);
        return;
    }
    switch (G07_A->unk154) {
        case 0:
            if (target->unk4->unk64 != state->unkC) {
                actorScriptStart(gCurrentActor, state->unk2);
            } else {
                actorCopyPoseAndScale(gCurrentActor, target, *(s32 *)&G07_A->unk4->scaleX, state);
                G07_A->unk80 += state->unk10;
            }
            break;
        case 1:
            G07_A->unkC0 = G07_A->unkC0 + 0.2;
            G07_A->unk80 = G07_A->unk80 + speed * G07_A->unkC0;
            break;
        case 2:
            G07_A->unkC0 = G07_A->unkC0 - 0.2;
            G07_A->unk80 = G07_A->unk80 + speed * G07_A->unkC0;
            break;
        case 3:
            G07_A->unk168 += 0x28;
            G07_A->unk168 &= 0xFFF;
            if (G07_A->unkB8 < 1.2) {
                G07_A->unkB8 = G07_A->unkB8 + 0.15;
            }
            temp = G07_A->unkB8 * speed;
            G07_A->unk7C += temp * mathSinF(G07_A->unk168);
            G07_A->unk84 += temp * mathCosF(G07_A->unk168);
            if (G07_A->unkC0 < 2.5) {
                G07_A->unkC0 = G07_A->unkC0 + 0.2;
            }
            G07_A->unk80 = G07_A->unk80 + speed * G07_A->unkC0;
            break;
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

typedef struct G07StateView {
    /* 0x000 */ u8 pad0[0x1A4];
    /* 0x1A4 */ u8 unk1A4;
} G07StateView;

u8 playerIsSmallerThanAttacker(Actor *arg0, Actor *arg1) {
    s32 var_a0;
    s32 var_a2;
    u8 var_v0;
    u8 var_v1;
    G07StateView *st0;
    G07StateView *st1;

    var_v0 = 1;
    var_v1 = 1;
    var_a2 = 1;
    if ((gPlayerCount < 2) || ((arg0->collisionFlags & 4) != 0) || ((arg1->collisionFlags & 4) != 0)) {
        return 0;
    }
    if (arg0->collisionFlags & 1) {
        st0 = (G07StateView *)arg0->customState;
        var_v0 = ((G07PlayerSlot *)gPlayerSlots)[st0->unk1A4].unk2C0;
    }
    if (arg1->collisionFlags & 1) {
        st1 = (G07StateView *)arg1->customState;
        var_v1 = ((G07PlayerSlot *)gPlayerSlots)[st1->unk1A4].unk2C0;
        var_a2 = arg1->state != 0x7C;
    }
    var_a0 = var_v0 < var_v1;
    if (var_a0 != 0) {
        var_a0 = var_a2 != 0;
    }
    return var_a0;
}

extern s16 D_8075388C[];
extern s16 D_807538C8[];
extern s16 D_8075387C[];
extern s16 D_807538B8[];

void func_806D0EBC(s32 arg0) {
    f32 height;
    f32 limit;
    s32 pad[1];
    u8 type;

    type = ((G07PlayerSlot *)gPlayerSlots)[gCurrentPlayerIndex].unk2C0;
    if (type == 1) {
        height = D_8075388C[gCurrentCharacterIndex];
    } else {
        height = D_807538C8[gCurrentCharacterIndex];
    }
    if (type == 1) {
        limit = D_8075387C[gCurrentCharacterIndex];
    } else {
        limit = D_807538B8[gCurrentCharacterIndex];
    }
    if (G03_A->unkAC - G03_A->unkA4 < limit) {
        playerStateQueueCallback(2, NULL, gCurrentPlayerIndex);
        return;
    }
    if (G03_A->unkAC < G03_A->unk80 + height) {
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x10, 0xFF, 0x7F, 1);
        G03_A->unk80 = G03_A->unkAC - height;
        G03_A->unkC0 = 0.0f;
        actorScriptStartByIndex(gCurrentActor, 0x3D);
        G06_P->unk30 = D_80753250[gCurrentCharacterIndex];
        gCurrentActor->state = 0x4E;
        G02_A->unk155 = 0;
    }
}

s16 mathAngleFromVector2D(f32 arg0, f32 arg1) {
    s16 angle = (s32)(mathAtan2(arg0, arg1) * 4096.0f / 6.2831855f);

    angle -= 0x400;
    return angle & 0xFFF;
}

s32 func_806D10D0(Actor *arg0) {
    s32 ret = 1;

    if (arg0->collisionFlags & 1) {
        if (gPlayerStateFlags[arg0->state][0] & 0x400) {
            ret = 0;
        }
    }
    return ret;
}

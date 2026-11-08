#include "common.h"

// DAA0: hidden translation-unit boundary at 0x80031AA0 (C920's .data/.rodata end 16-/8-aligned before it)
s16 D_80035B00[4] = { 0, 0x26C, 0, -0x26C };
s16 D_80035B08[4] = { 0x26C, 0, -0x26C, 0 };
s16 D_80035B10[4] = { 0x800, 0xC00, 0, 0x400 };
s16 D_80035B18[4] = { 0, -0x4B, 0, 0x4B };
s16 D_80035B20[4] = { -0x4B, 0, 0x4B, 0 };
s8 D_80035B28 = -1;
s16 D_80035B2C = 0;
s8 D_80035B30[4] = { 7, 3, 1, 0 };
s8 D_80035B34 = 0;
u8 D_80035B38 = 0xFF;
f32 D_80035B3C = 0.0f;
s8 D_80035B40 = 0;
s8 D_80035B44[5] = { 2, 3, 4, 0, 1 };
s16 D_80035B4C[5] = { 2, 3, 4, 5, 6 };
u8 D_80035B58[5] = { 2, 1, 3, 4, 0 };
s16 D_80035B60[4] = { 0xDC, 0xDD, 0xDE, 0xDF };
s8 D_80035B68 = 0;
s8 D_80035B6C = 0;

typedef struct BossD_Actor {
    u8 pad0[0x7C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xE6 - 0x88];
    s16 unkE6;
    u8 padE8[0xEE - 0xE8];
    s16 unkEE;
    u8 padF0[0x144 - 0xF0];
    u8 unk144;
    u8 pad145[0x154 - 0x145];
    u8 unk154;
    u8 pad155[0x160 - 0x155];
    f64 unk160;
} BossD_Actor;

extern BossD_Actor *gCurrentActor;
extern BossD_Actor *gPrimaryPlayerActor;

void camStartPath(void *, s32, u8);
s32 camIsCutsceneActive(void);
f32 mathSinF(s16);
void actorUpdateModelMatrix(void *, s32);

typedef struct BossModelInfo {
    u8 pad0[0x34];
    f32 unk34;
    f32 unk38;
    f32 unk3C;
} BossModelInfo;

typedef struct BossSpawnState {
    void *unk0;
    s8 unk4;
    s8 unk5;
} BossSpawnState;

typedef struct BossSpawnerState {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    s16 unkC;
    s16 unkE;
    s16 unk10;
    s8 unk12;
    s8 unk13;
    s8 unk14;
    s8 unk15;
    s8 unk16;
    s8 unk17;
} BossSpawnerState;

typedef struct BossSpawnerActor {
    u8 pad0[4];
    BossModelInfo *unk4;
    u8 pad8[0x60 - 8];
    s32 unk60;
    u8 pad64[0x7C - 0x64];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xA4 - 0x88];
    u8 unkA4;
    u8 padA5[0xE6 - 0xA5];
    s16 unkE6;
    u8 padE8[0x128 - 0xE8];
    s16 unk128;
    s16 unk12A;
    u8 pad12C[0x144 - 0x12C];
    u8 unk144;
    u8 pad145;
    s16 unk146;
    u8 pad148[0x154 - 0x148];
    u8 unk154;
    u8 unk155;
    u8 pad156[0x174 - 0x156];
    BossSpawnerState *unk174;
} BossSpawnerActor;

typedef struct BossSpawnedActor {
    u8 pad0[4];
    BossModelInfo *unk4;
    u8 pad8[0x60 - 8];
    s32 unk60;
    u8 pad64[0x80 - 0x64];
    f32 unk80;
    u8 pad84[0x174 - 0x84];
    BossSpawnState *unk174;
} BossSpawnedActor;

extern BossSpawnedActor *gSpawnedActor;
extern u8 D_807FBDC4;
extern s8 D_80036DC0;
extern f32 D_80036DC4;

s32 actorSpawn(s32, s32);
void *actorListFindActorById(s16);
void actorDespawn(void *);
s32 mapRequestTransition(s32, s32);
void collisionCheckActorFloor(void *, f32, f32, f32, void *);
void func_8068A764(void *, u8);
void playerSetKongByActorType(s16);
void func_806F09F0(void *, u16);
void func_8067AAB8(void *, void *, s32, f32, s32);
void sfxPlayOnFreeSlot();
void camPausePath(void);
void camResumePath(void);
void func_80724994(s32, s32, s32, s32, s32);
s32 randomLcgNext(void);
f32 randomFloat(void);
s32 sfxAllocateChannel();
void bossSpawnParticleRing(s32, s16, s16, s16, s32, s32);
void lightAdd(f32, f32, f32, f32, f32, f32, f32, u8, u8, u8, u8);
void lightSetColor(f32, f32, f32, s32);
void enemyAggroEnable(void);

#define SPAWNER_ACTOR ((BossSpawnerActor *)gCurrentActor)
#define SPAWNER_PLAYER ((BossSpawnerActor *)gPrimaryPlayerActor)

void bossSpawnerUpdate(void) {
    f32 dx;
    f32 dz;
    s32 k;
    s32 i;
    BossSpawnerState *s;
    s8 prevSubState;
    s8 hitPlayer;
    s8 bounceDir;
    s8 spawnParticle;
    s8 topReached;
    BossSpawnState *st;
    s32 cutsceneId;
    f32 lx;
    f32 lz;
    s16 j;
    s16 u;
    static s16 D_80035B70 = 0;

    s = SPAWNER_ACTOR->unk174;
    topReached = 0;
    spawnParticle = 0;
    hitPlayer = 0;
    if (!(SPAWNER_ACTOR->unk60 & 0x10)) {
        D_80035B28 = 0xF;
        D_80035B34 = 0;
        D_80035B3C = 0.0f;
        s->unkC = 0x1E;
        s->unkE = 1;
        s->unk0 = SPAWNER_ACTOR->unk80;
        s->unk14 = 0;
        D_80035B6C = 0;
        s->unk12 = 0;
        D_80035B70 = 5;
        for (i = 0; i != 8; i++) {
            if (actorSpawn(0xA6, D_80035B60[i >> 1]) != 0) {
                st = gSpawnedActor->unk174;
                st->unk0 = SPAWNER_ACTOR;
                st->unk4 = i >> 1;
                st->unk5 = i & 1;
                gSpawnedActor->unk80 = SPAWNER_ACTOR->unk80 + 50.0f;
                gSpawnedActor->unk4->unk34 = 0.1;
                gSpawnedActor->unk4->unk38 = 0.1;
                gSpawnedActor->unk4->unk3C = 0.1;
                gSpawnedActor->unk60 |= 0x400;
            }
        }
        D_80036DC4 = 160000.0f;
        D_80036DC0 = 0;
        if (gPrimaryPlayerActor != NULL) {
            SPAWNER_PLAYER->unk154 = 0x77;
            SPAWNER_PLAYER->unk155 = 0;
        }
        SPAWNER_ACTOR->unk12A = 0x7D0;
        collisionCheckActorFloor(SPAWNER_ACTOR, SPAWNER_ACTOR->unk7C, SPAWNER_ACTOR->unk80, SPAWNER_ACTOR->unk84, &SPAWNER_ACTOR->unkA4);
        SPAWNER_ACTOR->unk154 = 2;
        camStartPath(0, 3, 1);
    }
    switch (SPAWNER_ACTOR->unk154) {
    case 0:
        SPAWNER_PLAYER->unk7C = SPAWNER_ACTOR->unk7C;
        SPAWNER_PLAYER->unk80 = SPAWNER_ACTOR->unk80;
        SPAWNER_PLAYER->unk84 = SPAWNER_ACTOR->unk84;
        if (D_80035B38 == -1) {
            D_80035B38 = SPAWNER_PLAYER->unk144;
        }
        SPAWNER_PLAYER->unk60 &= ~4;
        SPAWNER_PLAYER->unk144 = 1;
        if (D_807FBDC4 != 0) {
            cutsceneId = D_80035B44[D_80036DC0];
            SPAWNER_ACTOR->unk146 = 0;
            for (i = 4; D_80036DC0 < i; i--) {
                func_8068A764(gCurrentActor, D_80035B58[D_80035B44[i]]);
            }
            D_80036DC0++;
            cutsceneId = D_80035B4C[cutsceneId];
            playerSetKongByActorType(cutsceneId);
            func_806F09F0(gPrimaryPlayerActor, cutsceneId);
            SPAWNER_PLAYER->unk154 = 0xC;
            SPAWNER_PLAYER->unk155 = 0;
            func_8067AAB8(gCurrentActor, gPrimaryPlayerActor, 0, 180.0f, 0x46);
            SPAWNER_ACTOR->unk154 = 1;
            SPAWNER_PLAYER->unk144 = D_80035B38;
        }
        break;
    case 1:
        SPAWNER_PLAYER->unk60 |= 4;
        dx = SPAWNER_PLAYER->unk7C - SPAWNER_ACTOR->unk7C;
        lz = SPAWNER_PLAYER->unk84 - SPAWNER_ACTOR->unk84;
        if (dx > 700.0 || dx < -700.0 || lz > 700.0 || lz < -700.0) {
            if (D_80036DC0 < 5) {
                SPAWNER_ACTOR->unk154 = 0;
                camStartPath(0, 2, 1);
            } else {
                mapRequestTransition(0x2A, 2);
                SPAWNER_ACTOR->unk154 = 3;
            }
        }
        break;
    case 2:
        s->unkE--;
        if (s->unkE < 0) {
            SPAWNER_ACTOR->unk154 = 0;
            playerSetKongByActorType(4);
            func_806F09F0(gPrimaryPlayerActor, 4);
            s->unk13 = 1;
        }
        break;
    case 3:
        break;
    }
    SPAWNER_ACTOR->unkE6 += 0x32;
    SPAWNER_ACTOR->unkE6 &= 0xFFF;
    SPAWNER_ACTOR->unk80 = mathSinF(SPAWNER_ACTOR->unkE6) * 5.0 + s->unk0;
    if (SPAWNER_PLAYER->unk154 == 0x45 && SPAWNER_PLAYER->unk155 >= 2 && D_80036DC4 < 10000.0) {
        hitPlayer = 1;
    }
    bounceDir = 0;
    s->unk4 += s->unk8;
    dx = 1.0f;
    if (s->unk4 > dx) {
        s->unk4 = dx;
        bounceDir = 1;
    }
    if (s->unk4 < (f32)0) {
        s->unk4 = (f32)0;
        bounceDir = -1;
    }
    if (bounceDir != 0 && camIsCutsceneActive() == 0) {
        s->unk10++;
    }
    s->unk17 = 0;
    prevSubState = s->unk13;
    switch (s->unk13) {
    case 0:
        i = 5;
        if (s->unk12 == 2) {
            j = 0xC;
            s->unk8 = -0.2f;
        } else {
            i = 0x3C;
            j = 4;
            s->unk8 = -0.1f;
        }
        if (i < s->unk10) {
            s->unk15++;
            if (s->unk15 < j) {
                s->unk13 = 1;
                sfxPlayOnFreeSlot(0x37D, 0x7D00, 0x427C0000, 0x3F800000, 0, 0);
                if (s->unk12 == 2) {
                    sfxPlayOnFreeSlot(0x381, 0x7D00, 0x427C0000, 0x3F800000, 0, 0);
                } else {
                    sfxPlayOnFreeSlot(0x37F, 0x7D00, 0x427C0000, 0x3F800000, 0, 0);
                }
            } else {
                s->unk13 = 2;
                s->unk15 = 0;
            }
        }
        if (bounceDir != 0 && D_80035B40 == 0) {
            spawnParticle = 1;
            D_80035B2C = 0;
        }
        break;
    case 1:
        switch (s->unk12) {
        case 2:
            i = 0xA;
            s->unk8 = 0.2f;
            break;
        case 3:
            i = 0x3C;
            s->unk8 = 0.1f;
            break;
        default:
            i = 0xB4;
            s->unk8 = 0.1f;
            break;
        }
        if (bounceDir == 1) {
            topReached = 1;
            if (i < s->unk10) {
                s->unk13 = 0;
                s->unk15++;
                sfxPlayOnFreeSlot(0x17D, 0x3E80, 0x427C0000, 0x3F800000, 0, 0);
            }
            if (hitPlayer != 0) {
                sfxPlayOnFreeSlot(0x97, 0x7D00, 0x427C0000, 0x3F800000, 0, 0);
                s->unk16++;
                s->unk15 = 0;
                s->unk13 = 2;
                if (s->unk16 == 3) {
                    sfxPlayOnFreeSlot(0x385, 0x7D00, 0x427C0000, 0x3F800000, 0, 0);
                    s->unk16 = 0;
                    camPausePath();
                    if (D_80035B68 == 0) {} // FAKE: dead test steers uopt colouring/ring (case 1 arm)
                    s->unk13 = 4;
                } else {
                    sfxPlayOnFreeSlot(0x38E, 0x7D00, 0x427C0000, 0x3F800000, 0, 0);
                    sfxPlayOnFreeSlot(0x383, 0x7D00, 0x427C0000, 0x3F800000, 0, 0);
                }
            }
        }
        break;
    case 2:
        s->unk8 = -0.1f;
        if (s->unk10 >= 0x5B) {
            s->unk15++;
            if (s->unk15 < 3) {
                s->unk13 = 3;
                sfxPlayOnFreeSlot(0x37D, 0x7D00, 0x427C0000, 0x3F800000, 0, 0);
                sfxPlayOnFreeSlot(0x380, 0x7D00, 0x427C0000, 0x3F800000, 0, 0);
            } else {
                s->unk13 = 0;
                s->unk15 = 0;
            }
        }
        if (bounceDir != 0 && D_80035B40 == 0) {
            spawnParticle = 1;
        }
        break;
    case 3:
        s->unk8 = 0.1f;
        if (s->unk10 >= 0x1F) {
            s->unk13 = 2;
            sfxPlayOnFreeSlot(0x17D, 0x3E80, 0x427C0000, 0x3F800000, 0, 0);
        }
        if (bounceDir != 0) {
            s->unk17 = 1;
        }
        break;
    case 4:
        D_80035B3C += 1.0;
        if (D_80035B3C > 24.0) {
            D_80035B3C = 24.0f;
            s->unk10++;
            D_80035B2C = mathSinF(s->unk10 << 5) * 200.0f;
            if (s->unk10 == 0x3F) {
                D_80035B3C = 0.0f;
                D_80035B2C = 0;
                D_80035B28 = D_80035B30[D_80035B34];
                D_80035B34 += 1;
                s->unk13 = 5;
            }
        }
        break;
    case 5:
        s->unk10++;
        if (s->unk10 >= 0x3D) {
            s->unk8 = -0.1f;
            camResumePath();
            s->unk13 = 0;
            s->unk12++;
            if (s->unk12 == 1) {
                func_80724994(1, 7, 0, 0, 0);
            }
            if (s->unk12 == 3) {
                s->unk13 = 7;
            }
        }
        break;
    case 6:
        s->unk8 = -0.1f;
        if (bounceDir == -1) {
            topReached = 1;
            if (D_80035B70 < s->unk10) {
                sfxPlayOnFreeSlot(0x17D, 0x3E80, 0x427C0000, 0x3F800000, 0, 0);
                D_80035B70 = D_80035B70 + 1;
                s->unk10 = 0;
                if (D_80035B70 >= 0x10) {
                    D_80035B70 += 1;
                }
                if (D_80035B70 >= 0x1A) {
                    D_80035B70 = (randomLcgNext() & 3) + 4;
                    s->unk13 = 1;
                    s->unk15++;
                    sfxPlayOnFreeSlot(0x37F, 0x7D00, 0x427C0000, 0x3F800000, 0, 0);
                    sfxPlayOnFreeSlot(0x381, 0x7D00, 0x427C0000, 0x3F800000, 0, 0);
                }
                spawnParticle = 1;
            }
            D_80035B68 = 0x1E;
        }
        break;

    case 7:
        s->unk10++;
        s->unk8 = -0.1f;
        if (s->unk10 >= 0x10) {
            for (j = 0; j < 4; j++) {
                actorDespawn(actorListFindActorById(j));
            }
            SPAWNER_ACTOR->unk60 &= ~0x8000;
            SPAWNER_ACTOR->unk128 = 0;
            camStartPath(0, 4, 1);
            s->unk13 = 8;
        }
        break;
    case 8:
        s->unk8 = -0.1f;
        if (D_807FBDC4 != 0) {
            sfxAllocateChannel(0x35, 0x3F800000);
            bossSpawnParticleRing(0x13D, SPAWNER_ACTOR->unk7C, SPAWNER_ACTOR->unk80 + 200.0f, SPAWNER_ACTOR->unk84 + 40.0f, 0x800, 1);
            s->unk13 = 9;
        }
        break;
    case 9:
        break;
    }
    if (s->unk12 == 3 && s->unk13 == 0) {
        if (s->unk15 < 2) {
            s->unk13 = 6;
        } else {
            s->unk15 = 0x14;
        }
    }
    if (prevSubState != s->unk13) {
        s->unk10 = 0;
    }
    if (spawnParticle != 0) {
        if (s->unk12 == 2 || s->unk12 == 3) {
            s->unk14++;
        } else {
            dx = randomFloat();
            s->unk14 += (s32)(dx * 2.99f) + 1;
        }
        k = s->unk14;
        if (k >= 4) {
            s->unk14 = k - 4;
        }
    }
    D_80035B68++;
    if (topReached != 0) {
        cutsceneId = (D_80035B68 & 0x1F) - 0x10;
        i = cutsceneId;
        k = s->unk14;
        if (cutsceneId < 0) {
            i = -cutsceneId;
        }
        if (i >= 0x10) {
            i = 0xF;
        }
        cutsceneId = (i << 4) & 0xFF;
        if (cutsceneId && cutsceneId) {} // FAKE: pins the cutsceneId def before the lx/lz loads
        lx = (f32)((f64)D_80035B00[k] * 0.33 + (f64)SPAWNER_ACTOR->unk7C);
        lz = (f32)((f64)D_80035B08[k] * 0.33 + (f64)SPAWNER_ACTOR->unk84);
        lightAdd(lx, 400.0f, lz, lx, 300.0f, lz, 200.0f, 0, cutsceneId, cutsceneId, cutsceneId);
        if (s->unk12 == 1) {
            k = s->unk14 + 2;
            if (k >= 4) {
                k -= 4;
            }
            lx = (f32)((f64)D_80035B00[k] * 0.33 + (f64)SPAWNER_ACTOR->unk7C);
            lz = (f32)((f64)D_80035B08[k] * 0.33 + (f64)SPAWNER_ACTOR->unk84);
            lightAdd(lx, 400.0f, lz, lx, 300.0f, lz, 200.0f, 0, cutsceneId, cutsceneId, cutsceneId);
        }
    }
    s->unkC--;
    if (s->unkC < 0) {
        s->unkC = (randomLcgNext() & 0x7F) + 0x5A;
        lightSetColor(0.5f, 0.5f, 0.5f, -1);
        enemyAggroEnable();
    }
    D_80035B40 = bounceDir;
    actorUpdateModelMatrix(gCurrentActor, 0);
}


typedef struct BossAnimState {
    char pad0[4];
    f32 unk4;
    char pad8[8];
    s16 unk10;
} BossAnimState;

typedef struct BossModelRef {
    BossAnimState *unk0;
} BossModelRef;

typedef struct BossParentState {
    char pad0[4];
    f32 unk4;
    char pad8[0xA];
    s8 unk12;
    char pad13[1];
    s8 unk14;
    char pad15[2];
    s8 unk17;
} BossParentState;

typedef struct BossParentActor {
    char pad0[0x7C];
    f32 unk7C;
    char pad80[4];
    f32 unk84;
    char pad88[0xCC];
    u8 unk154;
    char pad155[0x1F];
    BossParentState *unk174;
} BossParentActor;

typedef struct BossFollowerLink {
    BossParentActor *unk0;
    s8 unk4;
    s8 unk5;
} BossFollowerLink;

typedef struct BossFollowerActor {
    char pad0[4];
    BossModelRef *unk4;
    char pad8[0x58];
    s32 unk60;
    char pad64[0x18];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0x5C];
    s16 unkE4;
    s16 unkE6;
    s16 unkE8;
    char padEA[0x40];
    s16 unk12A;
    char pad12C[0x18];
    u8 unk144;
    char pad145[0x25];
    u8 unk16A;
    u8 unk16B;
    u8 unk16C;
    char pad16D[7];
    BossFollowerLink *unk174;
} BossFollowerActor;

void controllerAnimSetStateIfChanged(void *, s16, f32, f32);
void controllerApplyMotionWindow(void *, void *, f32);
void projectileSetTargetCoords(f32, f32, f32);
void projectileAimAndSpawn(s16, s16, f32, f32, f32, f32, f32, void *);

#define ACTOR ((BossFollowerActor *)gCurrentActor)

void bossFollowerActorUpdate(void) {
    BossFollowerLink *sub174 = ACTOR->unk174;
    BossParentState *parentState = sub174->unk0->unk174;
    BossAnimState *sub4_0 = ACTOR->unk4->unk0;
    static s16 D_80035B74 = 0x78; // function-local static (only user; shadows the file-scope definition, which the .data carve moves here) keeps uopt from pointerizing D_80035B74

    if (sub174->unk5 == 0) {
        f32 dx = gPrimaryPlayerActor->unk7C - ACTOR->unk7C;
        f32 dz = gPrimaryPlayerActor->unk84 - ACTOR->unk84;
        D_80036DC4 = dx * dx + dz * dz;
    }
    if (!(ACTOR->unk60 & 0x10)) {
        controllerAnimSetStateIfChanged(ACTOR, sub174->unk4 + 0x668, 0.0f, 0.0f);
        ACTOR->unk12A = 0xFA0;
    }
    if (D_80035B28 & (1 << sub174->unk4)) {
        ACTOR->unkE8 = (s16)(parentState->unk4 * 1024.0) - 0x400;
        ACTOR->unkE4 = D_80035B2C;
        if (sub4_0 != NULL) {
            if (D_80035B3C != sub4_0->unk4) {
                controllerApplyMotionWindow(ACTOR, sub4_0, D_80035B3C);
            }
        }
    } else {
        ACTOR->unkE8 = 0;
        if (sub4_0 != NULL) {
            s32 v0 = sub174->unk4 + 0x66B;
            if (v0 != sub4_0->unk10) {
                controllerAnimSetStateIfChanged(ACTOR, v0, 0.0f, 0.0f);
                sfxPlayOnFreeSlot(0x38D, 0x7D00, 0x427C0000, 0x3F800000, 0, 0);
            } else {
                controllerApplyMotionWindow(ACTOR, sub4_0, sub4_0->unk4 + 0.75f);
            }
            if (sub174->unk4 == 1) {
                if (sub4_0->unk4 > 24.0f) {
                    sub4_0->unk4 = 24.0f;
                }
                if (sub4_0->unk4 > 15.0f) {
                    ACTOR->unk80 -= 10.0f;
                }
            } else {
                if (sub4_0->unk4 > 37.0f) {
                    sub4_0->unk4 = 37.0f;
                }
                if (sub4_0->unk4 > 26.0f) {
                    ACTOR->unk80 -= 10.0f;
                    if (sub4_0->unk10 == 1) {} // FAKE: steers uopt colouring (const 35 -> a1)
                }
            }
            if ((f64)ACTOR->unk80 < 0.0) {
                sfxPlayOnFreeSlot(0x384, 0x7D00, 0x427C0000, 0x3F800000, 0, 0);
                actorDespawn(ACTOR);
            }
        }
    }
    if (sub174->unk5 == 0) {
        ACTOR->unk144 = 0xC;
        if (sub174->unk4 == 0) {
            if (parentState->unk17 == 1) {
                if (sub174->unk0->unk154 == 0) {
                    D_80035B74 = 0x28;
                }
                D_80035B74 -= 1;
                if (D_80035B74 < 0) {
                    f32 zo = D_80035B20[parentState->unk14];
                    f32 xo = D_80035B18[parentState->unk14];
                    D_80035B74 = 0xA;
                    projectileSetTargetCoords(ACTOR->unk7C + xo, ACTOR->unk80 + 270.0f, ACTOR->unk84 + zo);
                    projectileAimAndSpawn(0x2C, 1, 0.25f, gPrimaryPlayerActor->unk7C, gPrimaryPlayerActor->unk80, gPrimaryPlayerActor->unk84, 2400.0f, ACTOR);
                }
            } else {
                D_80035B74 = 0;
            }
        }
        ACTOR->unk7C = D_80035B00[parentState->unk14] + sub174->unk0->unk7C;
        ACTOR->unk84 = D_80035B08[parentState->unk14] + sub174->unk0->unk84;
        ACTOR->unkE6 = D_80035B10[parentState->unk14];
    } else {
        s32 oppSide;
        ACTOR->unk144 = 1;
        oppSide = parentState->unk14 + 2;
        if (oppSide >= 4) {
            oppSide -= 4;
        }
        ACTOR->unk7C = D_80035B00[oppSide] + sub174->unk0->unk7C;
        if (D_80035B18) {}  // FAKE: deadsweep dead statement (steers uopt)
        ACTOR->unk84 = D_80035B08[oppSide] + sub174->unk0->unk84;
        ACTOR->unkE6 = D_80035B10[oppSide];
        ACTOR->unk60 |= 0x800000;
        ACTOR->unk16A = 0x23;
        if (sub174->unk5 && sub174->unk5) {} // FAKE: steers uopt colouring (const 35 -> a1)
        ACTOR->unk16B = 0x23;
        ACTOR->unk16C = 0x46;
        if (parentState->unk12 != 1) {
            ACTOR->unk60 &= ~4;
        } else {
            ACTOR->unk60 |= 4;
        }
    }
    actorUpdateModelMatrix(ACTOR, 0);
}
#undef ACTOR

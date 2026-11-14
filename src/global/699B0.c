#include "common.h"
#include "actor.h"
#include "sched.h"
#include "proto/global/119370.h"
#include "proto/global/11BC10.h"
#include "proto/global/166A0.h"
#define PROTO_SKIP_particleFindPathIndices
#include "proto/global/699B0.h"
void particleFindPathIndices(s16 pathType);

typedef struct ParticlePath {
    /* 0x00 */ u8 level;
    /* 0x01 */ u8 pad1;
    /* 0x02 */ s16 startX;
    /* 0x04 */ s16 startY;
    /* 0x06 */ s16 startZ;
    /* 0x08 */ s16 endX;
    /* 0x0A */ s16 endY;
    /* 0x0C */ s16 endZ;
    /* 0x0E */ u8 padE[2];
    /* 0x10 */ f32 trailStep;
    /* 0x14 */ s16 radius;
    /* 0x16 */ u8 pad16[2];
    /* 0x18 */ f32 trailScale;
    /* 0x1C */ f32 sparkScale;
} ParticlePath;

extern ParticlePath D_80748BA0[];
extern u8 D_807F9440[];
extern s32 D_807F9448;

void particleFindPathIndices(s16 levelIndex) {
    s32 limit;
    ParticlePath *ptr;
    s32 i;

    limit = 13; // FAKE: bound local blocks unrolling (a literal 13 peels iteration 0 and unrolls the scan, Q0228, Q0410)
    D_807F9448 = 0;
    for (i = 0, ptr = D_80748BA0; i < limit; i++, ptr++) {
        if (levelIndex == ptr->level && D_807F9448 != 8) {
            D_807F9440[D_807F9448++] = i;
        }
    }
}

extern PlayerStruct *gPlayerSlots;
extern u8 gPlayerCount;
extern s32 D_8072140C;
extern s32 D_8071FF18;

void particleSpawnPathTrail(void) {
    s32 i;
    u8 idx;
    ParticlePath *node;
    PlayerStruct *player;
    f32 dz;
    f32 dx;
    f32 dy;
    f32 t;
    f32 factor;

    if (gPlayerCount < 2) {
        for (i = 0; i < D_807F9448; i++) {
            idx = D_807F9440[i];
            player = gPlayerSlots;
            node = &D_80748BA0[idx];
            dz = player->eyeZ - node->startZ;
            dx = player->eyeX - node->startX;
            dy = player->eyeY - node->startY;
            if (sqrtf((dz * dz) + ((dx * dx) + (dy * dy))) < node->radius) {
                if ((gFrameCounter % 18) == 0) {
                    for (t = 0.0f; t <= 1.0; t += node->trailStep) {
                        effectSetDepth(1);
                        effectSetMode(3);
                        effectSetColor(0xFF, 0xFF, 0xFF, 0x96);
                        effectSetFlags(4);
                        effectSetCallback(effectPlayerDistanceFadeUpdate);
                        effectSetDuration(2);
                        effectSetParam((randomNonNegative() % 10000) % 6);
                        effectSetMaxDistance(node->radius);
                        effectCreateAtPosition(&D_8072140C, node->trailScale,
                                               (node->endX - node->startX) * t + node->startX,
                                               (node->endY - node->startY) * t + node->startY,
                                               (node->endZ - node->startZ) * t + node->startZ);
                    }
                }
                if ((gFrameCounter % 10) == 0) {
                    effectSetDepth(1);
                    effectSetMode(3);
                    effectSetColor(0xFF, 0xFF, 0xFF, 0x96);
                    effectSetFlags(4);
                    effectSetCallback(func_80717D4C);
                    effectSetSpeed(-0xAA);
                    effectSetMaxDistance(node->radius);
                    factor = ((randomNonNegative() % 10000) % 1000) / 1000.0;
                    effectCreateAtPosition(&D_8071FF18, node->sparkScale,
                                           (node->endX - node->startX) * factor + node->startX,
                                           (node->endY - node->startY) * factor + node->startY,
                                           (node->endZ - node->startZ) * factor + node->startZ);
                }
            }
        }
    }
}

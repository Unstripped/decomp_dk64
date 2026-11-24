#include "common.h"
#include "actor.h"
#include "boss.h"
#define PROTO_SKIP_csModelStateSetFirstByte // ORIG: hides the shared (s16, s16) prototype; the target passes the u8 stateByte unextended (lbu a1,39(sp) at 0x81c), see the declaration below
#include "proto/boss/3840.h"
#include "proto/boss/F0D0.h"
#include "proto/global/119370_effect_grid.h"
#include "proto/global/11BC10_effect_update.h"
#include "proto/global/1295B0_spawn_nodes.h"
#include "proto/global/12E800_behaviour.h"
#include "proto/global/1332B0_volume_trigger.h"
#include "proto/global/135D30_flags.h"
#include "proto/global/166A0_random.h"
#include "proto/global/19A00_actor_script.h"
#include "proto/global/201B0_camera.h"
#include "proto/global/2C910.h"
#include "proto/global/35000_render_entry.h"
#include "proto/global/42630_cutscene_interp.h"
#include "proto/global/5E2F0_light.h"
#include "proto/global/69E60_actor_physics.h"
#include "proto/global/70FD0_collision_geometry.h"
#include "proto/global/7130_sfx.h"
#include "proto/global/7CA80_actor_manager.h"
#include "proto/global/89250_effect_spawn.h"
#include "proto/global/936B0_projectile.h"
#include "proto/global/CEAE0_player_update.h"
#include "proto/global/EFDC0_player_state_enter.h"

extern Actor *gCurrentActor;
extern Actor *gPrimaryPlayerActor;

extern void *gPuffSprites[];
typedef struct {
    u8 b[4];
} BossWaypointPick;

extern const u8 D_80036C10[8];
extern const u8 D_80036C18[8];
extern const u8 D_80036C20[8];
extern const u8 D_80036C28[8];
extern const u8 D_80036C30[16];

BossWaypointPick gBossCenterWaypoints = { { 5, 6, 9, 10 } };
const u8 *gBossWaypointPhaseScripts[5] = { D_80036C10, D_80036C18, D_80036C20, D_80036C28, D_80036C30 };
u16 gBossWaypointLightPatterns[32] = {
    0x000F, 0x00F0, 0x0F00, 0xF000, 0x1111, 0x2222, 0x4444, 0x8888,
    0x0001, 0x0012, 0x0124, 0x1248, 0x2480, 0x4800, 0x8000, 0x0000,
    0x0001, 0x0002, 0x0004, 0x0008, 0x0080, 0x0040, 0x0020, 0x0010,
    0x0100, 0x0200, 0x0400, 0x0800, 0x8000, 0x4000, 0x2000, 0x1000,
};
u8 gBossIntroWaypointPath[4] = { 9, 10, 14, 0 };
u8 gBossPlainPillarObjects[8] = { 0x10, 0x12, 0x15, 0x17, 0x18, 0x1A, 0x1D, 0x1F };
u8 gBossSpecialPillarObjects[8] = { 0x11, 0x13, 0x14, 0x16, 0x19, 0x1B, 0x1C, 0x1E };
u8 gBossWaypointIsSpecial[16] = { 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0 };

// Waypoint component of the boss actor (Actor+0x17C): indices into the 16 gBehaviourZone pillar entries.
typedef struct BossWaypointState {
    /* 0x00 */ u8 current;
    /* 0x01 */ u8 next; // bossPickWaypointStep result; bossInterpolateWaypoints moves current -> next
    /* 0x02 */ u8 previous;
    /* 0x03 */ u8 playerNearest; // entry nearest to the player
    /* 0x04 */ u8 objectA; // lit object pair (bossSetRandomObjectPair), 0x10 + entry
    /* 0x05 */ u8 objectB;
    /* 0x06 */ u8 playerWasAbove;
} BossWaypointState;

u8 bossPickWaypointStep(BossScriptState *scriptState, BossWaypointState *waypoints) {
    s32 min_dist;
    s32 dists[16];
    u8 i;
    s8 diff_row;
    s8 diff_col;
    u8 val;
    u8 start_val;

    val = waypoints->current;
    min_dist = 9999999;
    start_val = val;
    for (i = 0; i < 16; i++) {
        dists[i] = (gBehaviourZone->entries[i].x - gPrimaryPlayerActor->x) * (gBehaviourZone->entries[i].x - gPrimaryPlayerActor->x) + (gBehaviourZone->entries[i].z - gPrimaryPlayerActor->z) * (gBehaviourZone->entries[i].z - gPrimaryPlayerActor->z);
        if (dists[i] < min_dist) {
            min_dist = dists[i];
            waypoints->playerNearest = i;
        }
    }

    if (gPrimaryPlayerActor->y < gCurrentActor->y - 10.0f) {
        BossWaypointPick center = gBossCenterWaypoints;
        return center.b[(randomNonNegative() >> 15) % 4];
    }

    diff_row = waypoints->current / 4 - waypoints->playerNearest / 4;
    diff_col = waypoints->current % 4 - waypoints->playerNearest % 4;

    if (diff_row > 0) {
        val -= 4;
    } else if (diff_row < 0) {
        val += 4;
    } else if (diff_col > 0) {
        val -= 1;
    } else if (diff_col < 0) {
        val += 1;
    }

    if (scriptState->phase >= 3) {
        return val;
    }
    if (val == waypoints->previous || val == start_val) {
        if (diff_row != 0 || val == start_val) {
            if (dists[(start_val - 1) & 0xF] < dists[(start_val + 1) & 0xF] && (start_val & 3) != 0) {
                start_val--;
            } else if (dists[(start_val + 1) & 0xF] < dists[(start_val - 1) & 0xF] && (start_val & 3) != 3) {
                start_val++;
            }
        }

        if ((diff_row == 0 && diff_col != 0) || val == start_val) {
            if (dists[(start_val - 4) & 0xF] < dists[(start_val + 4) & 0xF] && start_val >= 4) {
                return start_val - 4;
            } else if (dists[(start_val + 4) & 0xF] < dists[(start_val - 4) & 0xF] && start_val < 12) {
                start_val += 4;
            }
        }

        return start_val;
    }
    return val;
}

void bossSetAnimationByWaypoint(BossWaypointState *waypoints) {
    s32 animId;

    animId = gCurrentActor->sub4->animId;
    if (animId != 0x223 && waypoints->next == waypoints->playerNearest) {
        actorScriptStart(gCurrentActor, 0x223);
        actorScriptExecute(gCurrentActor);
        return;
    }
    if (animId != 0x224 && waypoints->next != waypoints->playerNearest) {
        actorScriptStart(gCurrentActor, 0x224);
        actorScriptExecute(gCurrentActor);
    }
}


void bossInterpolateWaypoints(BossWaypointState *waypoints, f32 progress) {
    f64 val;
    f32 factor;

    val = gCurrentActor->sub4->model->frame * progress;

    factor = 1.0 + mathSinF((f32)(1.0 - (1.0 < val ? 1.0 : val)) * 1024.0f + 3072.0f);

    gCurrentActor->x = gBehaviourZone->entries[waypoints->next].x + (gBehaviourZone->entries[waypoints->current].x - gBehaviourZone->entries[waypoints->next].x) * factor;
    gCurrentActor->z = gBehaviourZone->entries[waypoints->next].z + (gBehaviourZone->entries[waypoints->current].z - gBehaviourZone->entries[waypoints->next].z) * factor;

    gCurrentActor->yaw = mathAngleEaseToward(gCurrentActor->yaw, mathAngleBetweenPoints2D(gBehaviourZone->entries[waypoints->next].x, gBehaviourZone->entries[waypoints->next].z, gBehaviourZone->entries[waypoints->current].x, gBehaviourZone->entries[waypoints->current].z), 10.0f);
}

void bossSpawnPuffDebris(void) {
    f32 scale;

    scale = gCurrentActor->sub4->scaleY / 0.15;
    effectSetFrameDelay(2);
    effectSetCallback(effectPuffRiseUpdate);
    effectSetDepth(1);
    effectSetSpeed(1);
    effectCreateAtPosition(gPuffSprites[((randomNonNegative() >> 15) % 1000) % 3], (f64)scale, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z); // ORIG: the target round-trips the stored scale through double before passing it (lwc1 36(sp) 0x660, cvt.d.s 0x668, cvt.s.d 0x674, mfc1 a1 0x68c); plain scale drops both cvts (.text 10192 vs 10208)
}

void csModelStateSetFirstByte(s16, u8); // ORIG: target sign-extends the model index (sll a0,v0,0x10 / sra t0,a0,0x10 at 0x824-0x828) but passes stateByte as a plain lbu a1,39(sp) at 0x81c (the shared (s16, s16) prototype adds sll/sra of a1 there): the original TU declared an unsigned narrow second parameter

void bossSetRandomObjectPair(BossWaypointState *waypoints, u8 stateByte) {
    u8 idx;
    u8 val;
    if (stateByte) {
        do {
            idx = (randomNonNegative() >> 15) % 8;
        } while (waypoints->current + 0x10 == (val = gBossPlainPillarObjects[idx]) ||
                  waypoints->playerNearest + 0x10 == gBossPlainPillarObjects[idx] ||
                  waypoints->playerNearest + 0x0F == gBossPlainPillarObjects[idx] ||
                  waypoints->playerNearest + 0x11 == gBossPlainPillarObjects[idx] ||
                  waypoints->playerNearest + 0x0C == gBossPlainPillarObjects[idx] ||
                  waypoints->playerNearest + 0x14 == gBossPlainPillarObjects[idx]);
        waypoints->objectA = val;
        do {
            idx = (randomNonNegative() >> 15) % 8;
        } while (waypoints->current + 0x10 == (val = gBossSpecialPillarObjects[idx]) ||
                  waypoints->playerNearest + 0x10 == gBossSpecialPillarObjects[idx] ||
                  waypoints->playerNearest + 0x0F == gBossSpecialPillarObjects[idx] ||
                  waypoints->playerNearest + 0x11 == gBossSpecialPillarObjects[idx] ||
                  waypoints->playerNearest + 0x0C == gBossSpecialPillarObjects[idx] ||
                  waypoints->playerNearest + 0x14 == gBossSpecialPillarObjects[idx]);
        waypoints->objectB = val;
    }

    if (waypoints->objectA != 0) {
        csModelStateSetFirstByte(waypoints->objectA, stateByte);
    }
    if (waypoints->objectB != 0) {
        csModelStateSetFirstByte(waypoints->objectB, stateByte);
    }
    if (stateByte == 0) {
        waypoints->objectA = 0;
        waypoints->objectB = 0;
    }
}

void bossSpawnObjectAtWaypoint(BossWaypointState *waypoints) {
    projectileGetTargetCoords(gCurrentActor, 1);
    projectileAimAndSpawn(0x2C, 2, gCurrentActor->sub4->scaleY, gBehaviourZone->entries[waypoints->playerNearest].x, gBehaviourZone->entries[waypoints->playerNearest].y, gBehaviourZone->entries[waypoints->playerNearest].z, 1200.0f, gCurrentActor);
}

s32 bossCheckPlayerBelow(BossScriptState *scriptState, const u8 *scriptOpcodes) {
    if ((gPrimaryPlayerActor->y < (gCurrentActor->y - 10.0f)) && (scriptState->phase < 5)) {
        scriptState->scriptPos = scriptState->loopPos;
        gCurrentActor->state = scriptOpcodes[scriptState->scriptPos++];
        gCurrentActor->subState = 0;
        actorScriptStart(gCurrentActor, 0);
        return 1;
    }
    return 0;
}


void bossAdjustHealth(s8 healthDelta) {
    gCurrentActor->alpha += healthDelta;
    if (gCurrentActor->alpha < 0) {
        gCurrentActor->alpha = 0;
        gCurrentActor->subState++;
    } else if (gCurrentActor->alpha >= 0x100) {
        gCurrentActor->alpha = 0xFF;
        gCurrentActor->subState++;
    }
}

// Boss actor with its script state (0x178) and waypoint state (0x17C) components.
typedef struct BossWaypointActor {
    /* 0x000 */ Actor base;
    /* 0x178 */ BossScriptState *scriptState;
    /* 0x17C */ BossWaypointState *waypoints;
} BossWaypointActor;

extern u8 gBossWaypointLightFade[];
extern const f32 gBossWaypointPhaseAnimSpeeds[];
extern s16 gWaypointBossTerminalSpeedY;
extern f32 gWaypointBossAccelY;
extern u8 gEffectSpriteSparklePurple[];
extern u8 gEffectSpriteGlowRed[];
extern u8 gEffectSpriteSmokeCloud[];

void bossMainStep(void) {
    BossScriptState *scriptState;
    BossWaypointState *waypoints;
    const u8 *tbl;
    u8 playerAbove;
    u8 pad2[3];
    u8 debrisSfx;
    u8 pad1;
    u8 nextIdx;
    u8 red;
    u8 green;
    f32 sx;
    f32 sy;
    u8 idx;
    u8 v;
    s16 i;
    f32 boneX;
    f32 boneY;
    f32 boneZ;
    u8 left;
    u8 bright;

    scriptState = ((BossWaypointActor *)gCurrentActor)->scriptState;
    waypoints = ((BossWaypointActor *)gCurrentActor)->waypoints;
    tbl = gBossWaypointPhaseScripts[scriptState->phase];
    if (gPrimaryPlayerActor->y < gCurrentActor->y - 10.0f) {
        playerAbove = 1;
    } else {
        playerAbove = 0;
    }
    debrisSfx = 0;
    behaviourFrameBegin();
    actorUpdatePrevContactFlags(gCurrentActor);
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->floorNodeId = 1;
        gCurrentActor->collisionMode = 0x24;
        if (flagGet(0x6A, 2) != 0) {
            actorScriptStart(gCurrentActor, 0x226);
            camStartPath(gCurrentActor, 0x14, 1);
            waypoints->current = 9;
            waypoints->previous = 5;
            gCurrentActor->state = 0x20;
            gCurrentActor->subState = 0;
            gCurrentActor->subState = 0xB;
            gCurrentActor->attachMode = 0;
        } else {
            gCurrentActor->segmentFlags = 0;
            gBehaviourWorkState->scale = gCurrentActor->sub4->scaleY;
            actorSetUniformScale(gCurrentActor, gBehaviourWorkState->scale * 0.333);
            gCurrentActor->state = 0x1E;
            gCurrentActor->subState = 0;
            gCurrentActor->y += 650.0f;
            gCurrentActor->flags &= ~0x8000;
            waypoints->current = 0xF;
        }
        gCurrentActor->contactFlags &= ~1;
        gCurrentActor->accelY = gWaypointBossAccelY;
        gCurrentActor->terminalSpeedY = gWaypointBossTerminalSpeedY;
    }
    if (scriptState->phase < 2) {
        if (waypoints->objectA != 0) {
            idx = waypoints->objectA - 0x10;
            nextIdx = waypoints->objectB - 0x10;
            if (gBossWaypointIsSpecial[idx] != 0) {
                red = 0x46;
            } else {
                red = 0xFF;
            }
            if (gBossWaypointIsSpecial[idx] != 0) {
                green = 0xA0;
            } else {
                green = 0xFF;
            }
            if (idx != waypoints->playerNearest) {
                lightSetRadius(0x1388);
                lightAdd(gBehaviourZone->entries[idx].x, gBehaviourZone->entries[idx].y - 0x32, gBehaviourZone->entries[idx].z, 0.0f, 0.0f, 0.0f, 240.0f, 0, red, green, 0xFF);
            }
            if (nextIdx != waypoints->playerNearest) {
                lightSetRadius(0x1388);
                lightAdd(gBehaviourZone->entries[nextIdx].x, gBehaviourZone->entries[nextIdx].y - 0x32, gBehaviourZone->entries[nextIdx].z, 0.0f, 0.0f, 0.0f, 240.0f, 0, red, green, 0xFF);
            }
        }
    }
    if ((gCurrentActor->state == 0x27 && scriptState->phase == 4) || (gActorGlobalState.damaged != 0 && gCurrentActor->state != 0x37)) {
        if (gPrimaryPlayerActor->state == 0x36) {
            gCurrentActor->state = 0x2B;
            gCurrentActor->subState = 0;
        } else {
            actorScriptStart(gCurrentActor, 0x226);
            gCurrentActor->state = 0x37;
            gCurrentActor->subState = 0;
        }
    }
    if (gCurrentActor->state == 0x23 && gCurrentActor->subState == 1 && playerAbove == 0 && waypoints->playerWasAbove != 0) {
        gCurrentActor->state = 0x2B;
        gCurrentActor->subState = 0;
    }
    switch (gCurrentActor->state) {
    case 0x1E:
        for (i = 0; i < 0x10; i++) {
            if (gBossWaypointLightPatterns[gBehaviourWorkState->timer & 0x1F] & (1 << i)) {
                gBossWaypointLightFade[i] = 0xFA;
            }
            if (gBossWaypointLightFade[i] != 0) {
                sx = gBossWaypointIsSpecial[i] != 0 ? 0.27 : 1.0;
                sy = gBossWaypointIsSpecial[i] != 0 ? 0.62 : 1.0;
                lightSetRadius(0x1388);
                lightAdd(gBehaviourZone->entries[i].x, gBehaviourZone->entries[i].y - 0x28A, gBehaviourZone->entries[i].z, 0, 0.0f, 0.0f, 240.0f, 0, gBossWaypointLightFade[i] * sx, gBossWaypointLightFade[i] * sy, gBossWaypointLightFade[i]);
                gBossWaypointLightFade[i] -= 0x19;
            }
        }
        if (!(gFrameCounter & 7)) {
            gBehaviourWorkState->timer++;
        }
        if (gActorGlobalState.volumeTriggerQueueCount != 0) {
            gCurrentActor->state = 0x1F;
            gCurrentActor->subState = 0;
        }
        break;
    case 0x1F:
        bright = mathSinF(gFrameCounter * 0x7D) * 100.0f + 155.0f;
        lightSetRadius(0x1388);
        lightAdd(gBehaviourZone->entries[5].x, gBehaviourZone->entries[5].y - 0x28A, gBehaviourZone->entries[5].z, 0.0f, 0.0f, 0.0f, 240.0f, 0, bright, bright, bright);
        if (currentActorTestClearFlag() != 0) {
            sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x19C, 0x64, 0x7F, 0, 0, 0.0f, 0);
            gCurrentActor->state = 0x20;
            gCurrentActor->subState = 0;
        }
        break;
    case 0x20:
        behaviourUpdateShadowAlpha();
        switch (gCurrentActor->subState) {
        case 0:
            effectSpawnBoneDebris(4, 1);
            debrisSfx = 1;
            actorApplyGravity();
            actorApplyVelocityCustom(gCurrentActor, 0.0f, gCurrentActor->speedY);
            actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
            if (gCurrentActor->attachMode == 1) {
                gCurrentActor->subState++;
            }
            break;
        case 1:
            if (currentActorTestClearFlag() != 0) {
                gCurrentActor->subState++;
            }
            break;
        case 2:
            actorScriptStart(gCurrentActor, 0x225);
            actorScriptExecute(gCurrentActor);
            scriptState->byteVars[0] = 2;
            waypoints->next = gBossIntroWaypointPath[scriptState->byteVars[0]];
            waypoints->previous = 0xFF;
            gCurrentActor->subState++;
            gCurrentActor->contactFlags |= 1;
        case 3:
            scriptSetActorRampTarget(gCurrentActor, 1.0f, 0.0f);
            gCurrentActor->subState++;
        case 4:
            actorUpdatePrevContactFlags(gCurrentActor);
            actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
            bossInterpolateWaypoints(waypoints, 0.025f);
            if (gCurrentActor->sub4->model->frame >= 40.0f) {
                gCurrentActor->contactFlags |= 1;
            } else {
                gCurrentActor->contactFlags = 0;
                effectSpawnBoneDebris(4, 1);
                debrisSfx = 1;
            }
            break;
        case 5:
            waypoints->current = waypoints->next;
            v = scriptState->byteVars[0];
            left = v - 1;
            if (v) {
                scriptState->byteVars[0] = left;
                waypoints->next = gBossIntroWaypointPath[left];
                gCurrentActor->subState = 3;
            } else {
                actorScriptStart(gCurrentActor, 0x224);
                gCurrentActor->subState++;
            }
            break;
        case 6:
            actorTurnTowardActorYaw(0xA, gPrimaryPlayerActor);
            break;
        case 7:
            actorScriptStart(gCurrentActor, 0x222);
            gCurrentActor->subState++;
        case 8:
            if (currentActorTestClearFlag() != 0) {
                gCurrentActor->subState++;
                sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x128, 0xFF, 0x19, 0);
            }
            break;
        case 9:
            if (gCurrentActor->sub4->scaleY < gBehaviourWorkState->scale) {
                actorSetUniformScale(gCurrentActor, gCurrentActor->sub4->scaleY * 1.01);
                bossSpawnPuffDebris();
                debrisSfx = 1;
            } else {
                actorScriptStart(gCurrentActor, 0x227);
                gCurrentActor->subState++;
            }
            break;
        case 11:
            gCurrentActor->contactFlags &= ~1;
            if (currentActorTestClearFlag() != 0) {
                actorScriptStart(gCurrentActor, 0x22C);
                gCurrentActor->subState++;
            }
            break;
        case 13:
            camSetSecondTarget(gCamActor, gBehaviourZone->entries[17].x, gBehaviourZone->entries[17].z);
            scriptState->phase = 0;
            scriptState->scriptPos = 0;
            gCurrentActor->state = tbl[scriptState->scriptPos++];
            gCurrentActor->subState = 0;
            waypoints->previous = 5;
            break;
        }
        break;
    case 0:
        switch (gCurrentActor->subState) {
        case 0:
        case 1:
        case 2:
            bossSetRandomObjectPair(waypoints, 0);
            actorScriptStart(gCurrentActor, 0x226);
            gCurrentActor->subState = 3;
            break;
        case 3:
            if (gPrimaryPlayerActor->state != 0x33) {
                scriptState->scriptPos = scriptState->loopPos;
                gCurrentActor->state = tbl[scriptState->scriptPos++];
                gCurrentActor->subState = 0;
            }
            break;
        }
        break;
    case 0x23:
        behaviourUpdateShadowAlpha();
        switch (gCurrentActor->subState) {
        case 0:
            scriptState->byteVars[0] = tbl[scriptState->scriptPos++];
            scriptState->byteVars[1] = scriptState->byteVars[0];
            bossSetAnimationByWaypoint(waypoints);
            waypoints->next = bossPickWaypointStep(scriptState, waypoints);
            gCurrentActor->subState = 1;
            gCurrentActor->contactFlags |= 1;
        case 1:
            gCurrentActor->subState = 2;
            scriptSetActorRampTarget(gCurrentActor, gBossWaypointPhaseAnimSpeeds[scriptState->phase], 0.0f);
            waypoints->playerWasAbove = playerAbove;
        case 2:
            actorUpdatePrevContactFlags(gCurrentActor);
            actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
            bossInterpolateWaypoints(waypoints, gCurrentActor->sub4->animId == 0x223 ? 0.02173913f : 0.041666664f);
            if (gCurrentActor->sub4->animId == 0x223) {
                v = 0x35;
            } else {
                v = 0x17;
            }
            if ((f32)(s32)v <= gCurrentActor->sub4->model->frame) { // FAKE: v (case 5's unk18[0] counter copy) reused for the hit frame 0x35/0x17; a separate u8 or s32 local in any declaration slot changes regalloc
                gCurrentActor->contactFlags |= 1;
            } else {
                gCurrentActor->contactFlags = 0;
                effectSpawnBoneDebris(4, 1);
                debrisSfx = 1;
            }
            break;
        case 3:
            waypoints->previous = waypoints->current;
            waypoints->current = waypoints->next;
            if (playerAbove != 0) {
                scriptState->byteVars[0] = scriptState->byteVars[1];
            }
            if (scriptState->byteVars[0] != 0) {
                waypoints->next = bossPickWaypointStep(scriptState, waypoints);
                scriptState->byteVars[0]--;
                bossSetAnimationByWaypoint(waypoints);
                gCurrentActor->subState = 1;
            } else {
                gCurrentActor->state = tbl[scriptState->scriptPos++];
                gCurrentActor->subState = 0;
            }
            break;
        }
        break;
    case 0x25:
    case 0x28:
        actorTurnTowardActorYaw(0xA, gPrimaryPlayerActor);
        if (bossCheckPlayerBelow(scriptState, tbl) != 0) {
            bossSetRandomObjectPair(waypoints, 0);
        } else if (volumeTriggerApplyActorState() == 0) {
            switch (gCurrentActor->subState) {
            case 0:
                bossSetRandomObjectPair(waypoints, 0xA);
                scriptState->byteVars[0] = tbl[scriptState->scriptPos++] - 1;
                scriptState->byteVars[1] = tbl[scriptState->scriptPos++];
                actorScriptStart(gCurrentActor, 0x229);
                gCurrentActor->subState = 1;
                break;
            case 2:
                if (gCurrentActor->state == 0x25) {
                    actorScriptStart(gCurrentActor, 0x228);
                } else {
                    if (!(gBehaviourWorkState->flags & 0x8000)) {
                        if (gPrimaryPlayerActor->attachMode != 1) {
                            break;
                        }
                        camStartPath(gCurrentActor, 0xF, 1);
                        gBehaviourWorkState->flags |= 0x8000;
                    }
                    actorScriptStart(gCurrentActor, 0x22F);
                }
                gCurrentActor->subState = 3;
                break;
            case 3:
                if (gCurrentActor->state == 0x25) {
                    effectSpawnBoneDebris(3, 1);
                    debrisSfx = 1;
                } else {
                    actorGetNodePos(gCurrentActor, 1, &boneX, &boneY, &boneZ);
                    boneX += (randomNonNegative() >> 15) % 100 - 0x32;
                    boneY += (randomNonNegative() >> 15) % 100 + 0x32;
                    boneZ += (randomNonNegative() >> 15) % 100 - 0x32;
                    effectSetDepth(1);
                    effectSetCallback(effectEaseToTargetNodeUpdate);
                    effectSetSpeed((s32)gCurrentActor);
                    effectCreateAtPosition(gEffectSpriteSparklePurple, 1.5f, boneX, boneY, boneZ);
                    effectCreateAtActorBone(gEffectSpriteGlowRed, 3.0f, gCurrentActor, 1, 2);
                }
                break;
            case 4:
                if (gCurrentActor->state == 0x25) {
                    projectileGetTargetCoords(gCurrentActor, 3);
                    projectileAimAndSpawn(0x3B, 1, 1.2f, gPrimaryPlayerActor->x, gPrimaryPlayerActor->y + 5.0f, gPrimaryPlayerActor->z, 900.0f, gCurrentActor);
                } else {
                    waypoints->next = bossPickWaypointStep(scriptState, waypoints);
                    bossSpawnObjectAtWaypoint(waypoints);
                }
                gCurrentActor->subState = 5;
                break;
            case 6:
                if (scriptState->byteVars[0] != 0) {
                    scriptState->byteVars[0]--;
                    gBehaviourWorkState->timer = scriptState->byteVars[1];
                    gCurrentActor->subState = 7;
                } else {
                    actorScriptStart(gCurrentActor, 0x22D);
                    gCurrentActor->subState = 8;
                }
                break;
            case 7:
                if (gBehaviourWorkState->timer != 0) {
                    if (gPrimaryPlayerActor->state == 0x33) {
                        gBehaviourWorkState->timer = scriptState->byteVars[1];
                    } else {
                        gBehaviourWorkState->timer--;
                    }
                } else {
                    gCurrentActor->subState = 2;
                }
                break;
            case 9:
                bossSetRandomObjectPair(waypoints, 0);
                actorScriptStart(gCurrentActor, 0x22C);
                gCurrentActor->subState = 0xA;
                break;
            case 11:
                gCurrentActor->state = tbl[scriptState->scriptPos++];
                gCurrentActor->subState = 0;
                break;
            }
        }
        break;
    case 0x27:
        switch (gCurrentActor->subState) {
        case 0:
        case 1:
        case 2:
            actorAppendActiveCallback8();
            bossSetRandomObjectPair(waypoints, 0);
            actorScriptStart(gCurrentActor, 0x22E);
            camStartPath(gCurrentActor, 2, 1);
            actorSpawnAttachment(gCurrentActor, 1.2f);
            sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x305, 0xFF, 0x7F, 0, 0, 0.0f, 0);
            gCurrentActor->subState = 3;
            break;
        case 4:
            effectSpawnJointBeam(7, 0xB, 0x11, 0x20);
            effectSpawnJointBeam(0xC, 0x10, 0x11, 0x20);
            break;
        case 5:
            effectSpawnRandomBoneDebris(7, 0x20);
            if (currentActorTestClearFlag() != 0 || camIsCutsceneActive() == 0) {
                gCurrentActor->subState++;
            }
            break;
        case 6:
            if (scriptState->phase < 3) {
                actorScriptStart(gCurrentActor, 0x22C);
            } else {
                gCurrentActor->subState++;
            }
            gCurrentActor->subState++;
            break;
        case 8:
            currentActorClearFlag();
            scriptState->scriptPos = 0;
            scriptState->phase++;
            tbl = gBossWaypointPhaseScripts[scriptState->phase];
            gCurrentActor->state = tbl[scriptState->scriptPos++];
            gCurrentActor->subState = 0;
            break;
        }
        break;
    case 0x29:
        switch (gCurrentActor->subState) {
        case 0:
            gCurrentActor->flags &= ~0x8000;
            actorScriptStart(gCurrentActor, 0x231);
            scriptState->vars[0] = (s8)tbl[scriptState->scriptPos++];
            gCurrentActor->subState++;
            break;
        case 2:
            effectSpawnBoneDebris(2, 1);
            effectSpawnBoneDebris(3, 1);
            debrisSfx = 1;
            break;
        case 3:
            effectSpawnBoneDebrisScaled(2, (randomNonNegative() >> 15) % 0x7FFF % 6 + 5, 0x28);
            effectSpawnBoneDebrisScaled(3, (randomNonNegative() >> 15) % 0x7FFF % 6 + 5, 0x28);
            debrisSfx = 1;
            break;
        case 4:
            bossAdjustHealth(scriptState->vars[0]);
            break;
        case 5:
            gCurrentActor->state = tbl[scriptState->scriptPos++];
            gCurrentActor->subState = 0;
            break;
        }
        break;
    case 0x2B:
        switch (gCurrentActor->subState) {
        case 0:
            actorScriptStart(gCurrentActor, 0x222);
            gBehaviourWorkState->timer = 0x5A;
            gCurrentActor->subState++;
            break;
        case 1:
            if (gBehaviourWorkState->timer != 0) {
                gBehaviourWorkState->timer--;
            } else {
                scriptState->scriptPos = scriptState->loopPos;
                gCurrentActor->state = tbl[scriptState->scriptPos++];
                gCurrentActor->subState = 0;
            }
            break;
        }
        break;
    case 0x37:
        switch (gCurrentActor->subState) {
        case 0:
            camStartPath(gCurrentActor, 6, 0x81);
            gCurrentActor->subState++;
            break;
        case 1:
            if (currentActorTestClearFlag() != 0) {
                gCurrentActor->subState++;
            }
            break;
        case 2:
            bossAdjustHealth(5);
            break;
        case 3:
            if (currentActorTestClearFlag() != 0) {
                csModelStateSetFirstByte(waypoints->current, 0x1E);
                gCurrentActor->subState++;
            }
            break;
        case 4:
            if (currentActorTestClearFlag() != 0) {
                effectSpawnScatterRandom(gEffectSpriteSmokeCloud, 0, 6.0f, 6, 0x50, 0x64, gCurrentActor->x, gPrimaryPlayerActor->y + 100.0f, gCurrentActor->z);
                effectSpawnScatterRandom(gEffectSpriteSmokeCloud, 0x14, 6.0f, 8, 0x96, 0x46, gCurrentActor->x, gPrimaryPlayerActor->y + 100.0f, gCurrentActor->z);
                gCurrentActor->subState++;
            }
            break;
        case 5:
            if (camIsCutsceneActive() == 0) {
                bossSetRandomObjectPair(waypoints, 0);
                for (i = 0; i < 0x10; i++) {
                    if (i != waypoints->current) {
                        csModelStateSetFirstByte(i, 0x28);
                    }
                }
                bossSpawnParticleRing(0x8A, gBehaviourZone->entries[waypoints->current].x, gBehaviourZone->entries[waypoints->current].y, gBehaviourZone->entries[waypoints->current].z, 0x5DC, 1);
                gCurrentActor->state = 0x40;
                for (i = 0; i < 7; i++) {
                    volumeTriggerSetEnabled(i, 0);
                }
            }
            break;
        }
        break;
    default:
        bossScriptStep(tbl, 0, 0.0f);
        break;
    }
    if (debrisSfx != 0) {
        if (gCurrentActor->soundSlots[0] == -1) {
            sfxPlayActorSound(gCurrentActor, 0x135, 0x4B, 1, 0, 0xB4, 1.0f, 0);
        }
    } else {
        sfxStopSlotSound(gCurrentActor, 0);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

void bossShockwaveTriggerDamage(void) {
    f32 dx, dz;

    switch (gCurrentActor->subState) {
    case 1:
        if (gCurrentActor->state == 0) {
            dx = gPrimaryPlayerActor->x - gCurrentActor->x;
            dz = gPrimaryPlayerActor->z - gCurrentActor->z;
            if (dx * dx + dz * dz < 4225.0f) {
                if (gPrimaryPlayerActor->state != 0x31) {
                    playerStateQueueCallback(0x2E, gCurrentActor, 0);
                }
                gCurrentActor->state++;
            }
        }
        break;
    case 3:
        actorDespawn(gCurrentActor);
        break;
    }
    camStartShakeFromPoint(gCamActor, 5, 0x14, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 200.0f, 400.0f);
    actorUpdateModelMatrix(gCurrentActor, 0);
}

const u8 D_80036C10[8] = { 0x4F, 0x23, 0x08, 0x25, 0x06, 0x32, 0x50, 0x00 };
const u8 D_80036C18[8] = { 0x4F, 0x23, 0x0A, 0x25, 0x05, 0x2D, 0x50, 0x00 };
const u8 D_80036C20[8] = { 0x4F, 0x23, 0x0B, 0x25, 0x04, 0x28, 0x50, 0x00 };
const u8 D_80036C28[8] = { 0x4F, 0x23, 0x0C, 0x28, 0x04, 0x05, 0x50, 0x00 };
const u8 D_80036C30[16] = { 0x5F, 0x0A, 0x54, 0x29, 0xFB, 0x54, 0x4F, 0x23, 0x0E, 0x28, 0x04, 0x01, 0x50, 0x00, 0x00, 0x00 };
const f32 gBossWaypointPhaseAnimSpeeds[5] = { 0.8f, 0.9f, 1.0f, 1.1f, 1.2f };

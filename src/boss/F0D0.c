#include "common.h"
#include "actor.h"
#include "boss.h"
#define PROTO_SKIP_csModelStateSetFirstByte // ORIG: hides the shared (s16, s16) prototype; the target passes the u8 stateByte unextended (lbu a1,39(sp) at 0x81c), see the declaration below
#include "proto/boss/3840.h"
#include "proto/boss/F0D0.h"
#include "proto/global/119370.h"
#include "proto/global/11BC10.h"
#include "proto/global/1295B0.h"
#include "proto/global/12E800.h"
#include "proto/global/1332B0.h"
#include "proto/global/135D30.h"
#include "proto/global/166A0.h"
#include "proto/global/19A00.h"
#include "proto/global/201B0.h"
#include "proto/global/2C910.h"
#include "proto/global/35000.h"
#include "proto/global/42630.h"
#include "proto/global/5E2F0.h"
#include "proto/global/69E60.h"
#include "proto/global/70FD0.h"
#include "proto/global/7130.h"
#include "proto/global/7CA80.h"
#include "proto/global/89250.h"
#include "proto/global/936B0.h"
#include "proto/global/CEAE0.h"
#include "proto/global/EFDC0.h"



extern Actor *gCurrentActor;
extern Actor *gPrimaryPlayerActor;
extern Actor *gCamActor;
extern void *D_8074E880[];
typedef struct {
    u8 b[4];
} BossWaypointPick;
extern BossWaypointPick D_80035B80;

u8 bossPickWaypointStep(BossScriptState *scriptState, u8 *waypointIndices) {
    s32 min_dist;
    s32 dists[16];
    u8 i;
    s8 diff_row;
    s8 diff_col;
    u8 val;
    u8 start_val;

    val = waypointIndices[0];
    min_dist = 0x98967F;
    start_val = val;
    for (i = 0; i < 16; i++) {
        dists[i] = (D_807FDCA0->entries[i].x - gPrimaryPlayerActor->x) * (D_807FDCA0->entries[i].x - gPrimaryPlayerActor->x) + (D_807FDCA0->entries[i].z - gPrimaryPlayerActor->z) * (D_807FDCA0->entries[i].z - gPrimaryPlayerActor->z);
        if (dists[i] < min_dist) {
            min_dist = dists[i];
            waypointIndices[3] = i;
        }
    }

    if (gPrimaryPlayerActor->y < gCurrentActor->y - 10.0f) {
        BossWaypointPick center = D_80035B80;
        return center.b[(randomNonNegative() >> 15) % 4];
    }

    diff_row = waypointIndices[0] / 4 - waypointIndices[3] / 4;
    diff_col = waypointIndices[0] % 4 - waypointIndices[3] % 4;

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
    if (waypointIndices[2] - val == 0) {}  // FAKE: steers temp ring / beq operand order
    if (waypointIndices[2] - val == 0 || val == start_val) {  // FAKE: a - b == 0 keeps the load as first beq operand
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

void bossSetAnimationByWaypoint(u8 *waypointIndices) {
    s32 animId;

    animId = gCurrentActor->sub4->animId;
    if (animId != 0x223 && waypointIndices[3] == waypointIndices[1]) {
        actorScriptStart(gCurrentActor, 0x223);
        actorScriptExecute(gCurrentActor);
        return;
    }
    if (animId != 0x224 && waypointIndices[3] != waypointIndices[1]) {
        actorScriptStart(gCurrentActor, 0x224);
        actorScriptExecute(gCurrentActor);
    }
}


void bossInterpolateWaypoints(u8 *waypointPair, f32 progress) {
    f64 val;
    f32 factor;

    val = (f64)(gCurrentActor->sub4->model->frame * progress);

    factor = (f32)(1.0 + (f64)mathSinF((s16)((f32)(1.0 - (1.0 < val ? 1.0 : val)) * 1024.0f + 3072.0f)));

    gCurrentActor->x = (f32)D_807FDCA0->entries[waypointPair[1]].x + (f32)(D_807FDCA0->entries[waypointPair[0]].x - D_807FDCA0->entries[waypointPair[1]].x) * factor;
    gCurrentActor->z = (f32)D_807FDCA0->entries[waypointPair[1]].z + (f32)(D_807FDCA0->entries[waypointPair[0]].z - D_807FDCA0->entries[waypointPair[1]].z) * factor;

    gCurrentActor->yaw = mathAngleEaseToward(gCurrentActor->yaw, mathAngleBetweenPoints2D(D_807FDCA0->entries[waypointPair[1]].x, D_807FDCA0->entries[waypointPair[1]].z, D_807FDCA0->entries[waypointPair[0]].x, D_807FDCA0->entries[waypointPair[0]].z), 10.0f);
}

void bossSpawnPuffDebris(void) {
    f32 scale;

    scale = gCurrentActor->sub4->scaleY / 0.15;
    effectSetMode(2);
    effectSetCallback(effectPuffRiseUpdate);
    effectSetDepth(1);
    effectSetSpeed(1);
    effectCreateAtPosition(D_8074E880[((randomNonNegative() >> 15) % 1000) % 3], (f32) (f64) scale, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
}

void csModelStateSetFirstByte(s16, u8); // ORIG: target sign-extends the model index (sll a0,v0,0x10 / sra t0,a0,0x10 at 0x824-0x828) but passes stateByte as a plain lbu a1,39(sp) at 0x81c (the shared (s16, s16) prototype adds sll/sra of a1 there): the original TU declared an unsigned narrow second parameter
extern u8 D_80035BDC[];
extern u8 D_80035BE4[];

void bossSetRandomObjectPair(pairArray, stateByte)
u8 *pairArray;
u8 stateByte;
{
    u8 idx;
    u8 val;
    if (stateByte) {
        do {
            idx = (randomNonNegative() >> 15) % 8;
        } while (pairArray[0] + 0x10 == (val = D_80035BDC[idx]) ||
                  pairArray[3] + 0x10 == D_80035BDC[idx] ||
                  pairArray[3] + 0x0F == D_80035BDC[idx] ||
                  pairArray[3] + 0x11 == D_80035BDC[idx] ||
                  pairArray[3] + 0x0C == D_80035BDC[idx] ||
                  pairArray[3] + 0x14 == D_80035BDC[idx]);
        pairArray[4] = val;
        do {
            idx = (randomNonNegative() >> 15) % 8;
        } while (pairArray[0] + 0x10 == (val = D_80035BE4[idx]) ||
                  pairArray[3] + 0x10 == D_80035BE4[idx] ||
                  pairArray[3] + 0x0F == D_80035BE4[idx] ||
                  pairArray[3] + 0x11 == D_80035BE4[idx] ||
                  pairArray[3] + 0x0C == D_80035BE4[idx] ||
                  pairArray[3] + 0x14 == D_80035BE4[idx]);
        pairArray[5] = val;
    }

    if (pairArray[4] != 0) {
        csModelStateSetFirstByte(pairArray[4], stateByte);
    }
    if (pairArray[5] != 0) {
        csModelStateSetFirstByte(pairArray[5], stateByte);
    }
    if (stateByte == 0) {
        pairArray[4] = 0;
        pairArray[5] = 0;
    }
}

void bossSpawnObjectAtWaypoint(u8 *waypointIndex) {
    projectileGetTargetCoords(gCurrentActor, 1);
    projectileAimAndSpawn(0x2C, 2, gCurrentActor->sub4->scaleY, D_807FDCA0->entries[waypointIndex[3]].x, D_807FDCA0->entries[waypointIndex[3]].y, D_807FDCA0->entries[waypointIndex[3]].z, 1200.0f, gCurrentActor);
}

s32 bossCheckPlayerBelow(BossScriptState *scriptState, u8 *scriptOpcodes) {
    if ((gPrimaryPlayerActor->y < (gCurrentActor->y - 10.0f)) && (scriptState->phase < 5)) {
        scriptState->scriptPos = scriptState->loopPos;
        gCurrentActor->state = scriptOpcodes[scriptState->scriptPos];
        scriptState->scriptPos++;
        gCurrentActor->unk155 = 0;
        actorScriptStart(gCurrentActor, 0);
        return 1;
    }
    return 0;
}


void bossAdjustHealth(s8 healthDelta) {
    gCurrentActor->alpha += healthDelta;
    if (gCurrentActor->alpha < 0) {
        gCurrentActor->alpha = 0;
        gCurrentActor->unk155++;
    } else if (gCurrentActor->alpha >= 0x100) {
        gCurrentActor->alpha = 0xFF;
        gCurrentActor->unk155++;
    }
}

// Waypoint component of the boss actor (Actor+0x17C): indices into the 16 D_807FDCA0 pillar entries.
typedef struct BossWaypointState {
    /* 0x00 */ u8 current;
    /* 0x01 */ u8 next; // bossPickWaypointStep result; bossInterpolateWaypoints moves current -> next
    /* 0x02 */ u8 previous;
    /* 0x03 */ u8 playerNearest; // entry nearest to the player
    /* 0x04 */ u8 objectA; // lit object pair (bossSetRandomObjectPair), 0x10 + entry
    /* 0x05 */ u8 objectB;
    /* 0x06 */ u8 playerWasAbove;
} BossWaypointState;

// Boss actor with its script state (0x178) and waypoint state (0x17C) components.
typedef struct BossWaypointActor {
    /* 0x000 */ Actor base;
    /* 0x178 */ BossScriptState *scriptState;
    /* 0x17C */ BossWaypointState *waypoints;
} BossWaypointActor;

extern u8 *D_80035B84[];
extern u8 D_80035B98[];
extern u8 D_80035BD8[];
extern u8 D_80035BEC[];
extern u8 D_80036DD0[];
extern f32 D_80036C40[];
extern u8 D_807FBDC4;
extern s16 D_807502DC;
extern f32 D_807502F0;
extern u8 D_8071EDEC[];
extern u8 D_8071FC58[];
extern u8 D_80720054[];
extern u8 D_80720BE8[];

void bossMainStep(void) {
    BossScriptState *scriptState;
    BossWaypointState *waypoints;
    u8 *tbl;
    u8 playerAbove;
    u8 pad2[3];
    u8 flag7F;
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
    tbl = D_80035B84[scriptState->phase];
    if (gPrimaryPlayerActor->y < gCurrentActor->y - 10.0f) {
        playerAbove = 1;
    } else {
        playerAbove = 0;
    }
    flag7F = 0;
    behaviourFrameBegin();
    actorUpdatePrevContactFlags(gCurrentActor);
    if (!(gCurrentActor->flags & 0x10)) {
        gCurrentActor->floorNodeId = 1;
        gCurrentActor->unk144 = 0x24;
        if (flagGet(0x6A, 2) != 0) {
            actorScriptStart(gCurrentActor, 0x226);
            camStartPath(gCurrentActor, 0x14, 1);
            waypoints->current = 9;
            waypoints->previous = 5;
            gCurrentActor->state = 0x20;
            gCurrentActor->unk155 = 0;
            gCurrentActor->unk155 = 0xB;
            gCurrentActor->attachMode = 0;
        } else {
            gCurrentActor->unk146 = 0;
            gBehaviourWorkState->scale = gCurrentActor->sub4->scaleY;
            actorSetUniformScale(gCurrentActor, gBehaviourWorkState->scale * 0.333);
            gCurrentActor->state = 0x1E;
            gCurrentActor->unk155 = 0;
            gCurrentActor->y += 650.0f;
            gCurrentActor->flags &= 0xFFFF7FFF;
            waypoints->current = 0xF;
        }
        gCurrentActor->contactFlags &= 0xFFFE;
        gCurrentActor->accelY = D_807502F0;
        gCurrentActor->terminalSpeedY = D_807502DC;
    }
    if (scriptState->phase < 2) {
        if (waypoints->objectA != 0) {
            idx = waypoints->objectA - 0x10;
            nextIdx = waypoints->objectB - 0x10;
            if (D_80035BEC[idx] != 0) {
                red = 0x46;
            } else {
                red = 0xFF;
            }
            if (D_80035BEC[idx] != 0) {
                green = 0xA0;
            } else {
                green = 0xFF;
            }
            if (idx != waypoints->playerNearest) {
                lightSetRadius(0x1388);
                lightAdd(D_807FDCA0->entries[idx].x, D_807FDCA0->entries[idx].y - 0x32, D_807FDCA0->entries[idx].z, 0.0f, 0.0f, 0.0f, 240.0f, 0, red, green, 0xFF);
            }
            if (nextIdx != waypoints->playerNearest) {
                lightSetRadius(0x1388);
                lightAdd(D_807FDCA0->entries[nextIdx].x, D_807FDCA0->entries[nextIdx].y - 0x32, D_807FDCA0->entries[nextIdx].z, 0.0f, 0.0f, 0.0f, 240.0f, 0, red, green, 0xFF);
            }
        }
    }
    if ((gCurrentActor->state == 0x27 && scriptState->phase == 4) || (gActorGlobalState.unk15 != 0 && gCurrentActor->state != 0x37)) {
        if (gPrimaryPlayerActor->state == 0x36) {
            gCurrentActor->state = 0x2B;
            gCurrentActor->unk155 = 0;
        } else {
            actorScriptStart(gCurrentActor, 0x226);
            gCurrentActor->state = 0x37;
            gCurrentActor->unk155 = 0;
        }
    }
    if (gCurrentActor->state == 0x23 && gCurrentActor->unk155 == 1 && playerAbove == 0 && waypoints->playerWasAbove != 0) {
        gCurrentActor->state = 0x2B;
        gCurrentActor->unk155 = 0;
    }
    switch (gCurrentActor->state) {
    case 0x1E:
        for (i = 0; i < 0x10; i++) {
            if (((u16 *)D_80035B98)[gBehaviourWorkState->timer & 0x1F] & (1 << i)) {
                D_80036DD0[i] = 0xFA;
            }
            if (D_80036DD0[i] != 0) {
                sx = D_80035BEC[i] != 0 ? 0.27 : 1.0;
                sy = D_80035BEC[i] != 0 ? 0.62 : 1.0;
                lightSetRadius(0x1388);
                lightAdd(D_807FDCA0->entries[i].x, D_807FDCA0->entries[i].y - 0x28A, D_807FDCA0->entries[i].z, 0, 0.0f, 0.0f, 240.0f, 0, (u32)(D_80036DD0[i] * sx), (u32)(D_80036DD0[i] * sy), D_80036DD0[i]);
                D_80036DD0[i] -= 0x19;
            }
        }
        if (!(gFrameCounter & 7)) {
            gBehaviourWorkState->timer++;
        }
        if (D_807FBDC4 != 0) {
            gCurrentActor->state = 0x1F;
            gCurrentActor->unk155 = 0;
        }
        break;
    case 0x1F:
        bright = (u32)(mathSinF(gFrameCounter * 0x7D) * 100.0f + 155.0f);
        lightSetRadius(0x1388);
        lightAdd(D_807FDCA0->entries[5].x, D_807FDCA0->entries[5].y - 0x28A, D_807FDCA0->entries[5].z, 0.0f, 0.0f, 0.0f, 240.0f, 0, bright, bright, bright);
        if (currentActorTestClearFlag() != 0) {
            sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x19C, 0x64, 0x7F, 0, 0, 0.0f, 0);
            gCurrentActor->state = 0x20;
            gCurrentActor->unk155 = 0;
        }
        break;
    case 0x20:
        behaviourUpdateShadowAlpha();
        switch (gCurrentActor->unk155) {
        case 0:
            effectSpawnBoneDebris(4, 1);
            flag7F = 1;
            actorApplyGravity();
            actorApplyVelocityCustom(gCurrentActor, 0.0f, gCurrentActor->speedY);
            actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
            if (gCurrentActor->attachMode == 1) {
                gCurrentActor->unk155++;
            }
            break;
        case 1:
            if (currentActorTestClearFlag() != 0) {
                gCurrentActor->unk155++;
            }
            break;
        case 2:
            actorScriptStart(gCurrentActor, 0x225);
            actorScriptExecute(gCurrentActor);
            scriptState->unk18[0] = 2;
            waypoints->next = D_80035BD8[scriptState->unk18[0]];
            waypoints->previous = 0xFF;
            gCurrentActor->unk155++;
            gCurrentActor->contactFlags |= 1;
        case 3:
            scriptSetActorRampTarget(gCurrentActor, 1.0f, 0.0f);
            gCurrentActor->unk155++;
        case 4:
            actorUpdatePrevContactFlags(gCurrentActor);
            actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
            bossInterpolateWaypoints((u8 *)waypoints, 0.025f);
            if (gCurrentActor->sub4->model->frame >= 40.0f) {
                gCurrentActor->contactFlags |= 1;
            } else {
                gCurrentActor->contactFlags = 0;
                effectSpawnBoneDebris(4, 1);
                flag7F = 1;
            }
            break;
        case 5:
            waypoints->current = waypoints->next;
            v = scriptState->unk18[0];
            if (v != 0) {
                left = v;
                left--;
                if (v) {} // FAKE: keeps v live past the decrement so the raw temp does not share its register
                scriptState->unk18[0] = left;
                waypoints->next = D_80035BD8[left];
                gCurrentActor->unk155 = 3;
            } else {
                actorScriptStart(gCurrentActor, 0x224);
                gCurrentActor->unk155++;
            }
            break;
        case 6:
            actorTurnTowardActorYaw(0xA, gPrimaryPlayerActor);
            break;
        case 7:
            actorScriptStart(gCurrentActor, 0x222);
            gCurrentActor->unk155++;
        case 8:
            if (currentActorTestClearFlag() != 0) {
                gCurrentActor->unk155++;
                sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x128, 0xFF, 0x19, 0);
            }
            break;
        case 9:
            if (gCurrentActor->sub4->scaleY < gBehaviourWorkState->scale) {
                actorSetUniformScale(gCurrentActor, gCurrentActor->sub4->scaleY * 1.01);
                bossSpawnPuffDebris();
                flag7F = 1;
            } else {
                actorScriptStart(gCurrentActor, 0x227);
                gCurrentActor->unk155++;
            }
            break;
        case 11:
            gCurrentActor->contactFlags &= 0xFFFE;
            if (currentActorTestClearFlag() != 0) {
                actorScriptStart(gCurrentActor, 0x22C);
                gCurrentActor->unk155++;
            }
            break;
        case 13:
            camSetSecondTarget(gCamActor, D_807FDCA0->entries[17].x, D_807FDCA0->entries[17].z);
            scriptState->phase = 0;
            scriptState->scriptPos = 0;
            gCurrentActor->state = tbl[scriptState->scriptPos];
            scriptState->scriptPos++;
            gCurrentActor->unk155 = 0;
            waypoints->previous = 5;
            break;
        }
        break;
    case 0:
        switch (gCurrentActor->unk155) {
        case 0:
        case 1:
        case 2:
            bossSetRandomObjectPair(waypoints, 0);
            actorScriptStart(gCurrentActor, 0x226);
            gCurrentActor->unk155 = 3;
            break;
        case 3:
            if (gPrimaryPlayerActor->state != 0x33) {
                scriptState->scriptPos = scriptState->loopPos;
                gCurrentActor->state = tbl[scriptState->scriptPos];
                scriptState->scriptPos++;
                gCurrentActor->unk155 = 0;
            }
            break;
        }
        break;
    case 0x23:
        behaviourUpdateShadowAlpha();
        switch (gCurrentActor->unk155) {
        case 0:
            scriptState->unk18[0] = tbl[scriptState->scriptPos++];
            scriptState->unk18[1] = scriptState->unk18[0];
            bossSetAnimationByWaypoint((u8 *)waypoints);
            waypoints->next = bossPickWaypointStep(scriptState, (u8 *)waypoints);
            gCurrentActor->unk155 = 1;
            gCurrentActor->contactFlags |= 1;
        case 1:
            gCurrentActor->unk155 = 2;
            scriptSetActorRampTarget(gCurrentActor, D_80036C40[scriptState->phase], 0.0f);
            waypoints->playerWasAbove = playerAbove;
        case 2:
            actorUpdatePrevContactFlags(gCurrentActor);
            actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
            bossInterpolateWaypoints((u8 *)waypoints, gCurrentActor->sub4->animId == 0x223 ? 0.02173913f : 0.041666664f);
            if (gCurrentActor->sub4->animId == 0x223) {
                v = 0x35;
            } else {
                v = 0x17;
            }
            if ((f32)(s32)v <= gCurrentActor->sub4->model->frame) {
                gCurrentActor->contactFlags |= 1;
            } else {
                gCurrentActor->contactFlags = 0;
                effectSpawnBoneDebris(4, 1);
                flag7F = 1;
            }
            break;
        case 3:
            waypoints->previous = waypoints->current;
            waypoints->current = waypoints->next;
            if (playerAbove != 0) {
                scriptState->unk18[0] = scriptState->unk18[1];
            }
            if (scriptState->unk18[0] != 0) {
                waypoints->next = bossPickWaypointStep(scriptState, (u8 *)waypoints);
                scriptState->unk18[0]--;
                bossSetAnimationByWaypoint((u8 *)waypoints);
                gCurrentActor->unk155 = 1;
            } else {
                gCurrentActor->state = tbl[scriptState->scriptPos];
                scriptState->scriptPos++;
                gCurrentActor->unk155 = 0;
            }
            break;
        }
        break;
    case 0x25:
    case 0x28:
        actorTurnTowardActorYaw(0xA, gPrimaryPlayerActor);
        if (bossCheckPlayerBelow(scriptState, tbl) != 0) {
            bossSetRandomObjectPair(waypoints, 0);
        } else if (func_80724A20() == 0) {
            switch (gCurrentActor->unk155) {
            case 0:
                bossSetRandomObjectPair(waypoints, 0xA);
                scriptState->unk18[0] = tbl[scriptState->scriptPos++] - 1;
                scriptState->unk18[1] = tbl[scriptState->scriptPos++];
                actorScriptStart(gCurrentActor, 0x229);
                gCurrentActor->unk155 = 1;
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
                gCurrentActor->unk155 = 3;
                break;
            case 3:
                if (gCurrentActor->state == 0x25) {
                    effectSpawnBoneDebris(3, 1);
                    flag7F = 1;
                } else {
                    actorGetNodePos(gCurrentActor, 1, &boneX, &boneY, &boneZ);
                    boneX += (f32)((randomNonNegative() >> 15) % 100 - 0x32);
                    boneY += (f32)((randomNonNegative() >> 15) % 100 + 0x32);
                    boneZ += (f32)((randomNonNegative() >> 15) % 100 - 0x32);
                    effectSetDepth(1);
                    effectSetCallback(D_8071EDEC);
                    effectSetSpeed((s32)gCurrentActor);
                    effectCreateAtPosition(D_8071FC58, 1.5f, boneX, boneY, boneZ);
                    effectCreateAtActorBone(D_80720054, 3.0f, gCurrentActor, 1, 2);
                }
                break;
            case 4:
                if (gCurrentActor->state == 0x25) {
                    projectileGetTargetCoords(gCurrentActor, 3);
                    projectileAimAndSpawn(0x3B, 1, 1.2f, gPrimaryPlayerActor->x, gPrimaryPlayerActor->y + 5.0f, gPrimaryPlayerActor->z, 900.0f, gCurrentActor);
                } else {
                    waypoints->next = bossPickWaypointStep(scriptState, (u8 *)waypoints);
                    bossSpawnObjectAtWaypoint((u8 *)waypoints);
                }
                gCurrentActor->unk155 = 5;
                break;
            case 6:
                v = scriptState->unk18[0];
                if (v != 0) {
                    scriptState->unk18[0] = v - 1;
                    gBehaviourWorkState->timer = scriptState->unk18[1];
                    gCurrentActor->unk155 = 7;
                } else {
                    actorScriptStart(gCurrentActor, 0x22D);
                    gCurrentActor->unk155 = 8;
                }
                break;
            case 7:
                if (gBehaviourWorkState->timer != 0) {
                    if (gPrimaryPlayerActor->state == 0x33) {
                        gBehaviourWorkState->timer = scriptState->unk18[1];
                    } else {
                        gBehaviourWorkState->timer = gBehaviourWorkState->timer - 1;
                    }
                } else {
                    gCurrentActor->unk155 = 2;
                }
                break;
            case 9:
                bossSetRandomObjectPair(waypoints, 0);
                actorScriptStart(gCurrentActor, 0x22C);
                gCurrentActor->unk155 = 0xA;
                break;
            case 11:
                gCurrentActor->state = tbl[scriptState->scriptPos];
                scriptState->scriptPos++;
                gCurrentActor->unk155 = 0;
                break;
            }
        }
        break;
    case 0x27:
        switch (gCurrentActor->unk155) {
        case 0:
        case 1:
        case 2:
            actorAppendActiveCallback8();
            bossSetRandomObjectPair(waypoints, 0);
            actorScriptStart(gCurrentActor, 0x22E);
            camStartPath(gCurrentActor, 2, 1);
            actorSpawnAttachment(gCurrentActor, 1.2f);
            sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0x305, 0xFF, 0x7F, 0, 0, 0.0f, 0);
            gCurrentActor->unk155 = 3;
            break;
        case 4:
            effectSpawnJointBeam(7, 0xB, 0x11, 0x20);
            effectSpawnJointBeam(0xC, 0x10, 0x11, 0x20);
            break;
        case 5:
            effectSpawnRandomBoneDebris(7, 0x20);
            if (currentActorTestClearFlag() != 0 || camIsCutsceneActive() == 0) {
                gCurrentActor->unk155++;
            }
            break;
        case 6:
            if (scriptState->phase < 3) {
                actorScriptStart(gCurrentActor, 0x22C);
            } else {
                gCurrentActor->unk155++;
            }
            gCurrentActor->unk155++;
            break;
        case 8:
            currentActorClearFlag();
            scriptState->scriptPos = 0;
            scriptState->phase++;
            tbl = D_80035B84[scriptState->phase];
            gCurrentActor->state = tbl[scriptState->scriptPos];
            scriptState->scriptPos++;
            gCurrentActor->unk155 = 0;
            break;
        }
        break;
    case 0x29:
        switch (gCurrentActor->unk155) {
        case 0:
            gCurrentActor->flags &= 0xFFFF7FFF;
            actorScriptStart(gCurrentActor, 0x231);
            scriptState->unk8[0] = (s8)tbl[scriptState->scriptPos++];
            gCurrentActor->unk155++;
            break;
        case 2:
            effectSpawnBoneDebris(2, 1);
            effectSpawnBoneDebris(3, 1);
            flag7F = 1;
            break;
        case 3:
            effectSpawnBoneDebrisScaled(2, (randomNonNegative() >> 15) % 0x7FFF % 6 + 5, 0x28);
            effectSpawnBoneDebrisScaled(3, (randomNonNegative() >> 15) % 0x7FFF % 6 + 5, 0x28);
            flag7F = 1;
            break;
        case 4:
            bossAdjustHealth(scriptState->unk8[0]);
            break;
        case 5:
            gCurrentActor->state = tbl[scriptState->scriptPos];
            scriptState->scriptPos++;
            gCurrentActor->unk155 = 0;
            break;
        }
        break;
    case 0x2B:
        switch (gCurrentActor->unk155) {
        case 0:
            actorScriptStart(gCurrentActor, 0x222);
            gBehaviourWorkState->timer = 0x5A;
            gCurrentActor->unk155++;
            break;
        case 1:
            if (gBehaviourWorkState->timer != 0) {
                gBehaviourWorkState->timer = gBehaviourWorkState->timer - 1;
            } else {
                scriptState->scriptPos = scriptState->loopPos;
                gCurrentActor->state = tbl[scriptState->scriptPos];
                scriptState->scriptPos++;
                gCurrentActor->unk155 = 0;
            }
            break;
        }
        break;
    case 0x37:
        switch (gCurrentActor->unk155) {
        case 0:
            camStartPath(gCurrentActor, 6, 0x81);
            gCurrentActor->unk155++;
            break;
        case 1:
            if (currentActorTestClearFlag() != 0) {
                gCurrentActor->unk155++;
            }
            break;
        case 2:
            bossAdjustHealth(5);
            break;
        case 3:
            if (currentActorTestClearFlag() != 0) {
                csModelStateSetFirstByte(waypoints->current, 0x1E);
                gCurrentActor->unk155++;
            }
            break;
        case 4:
            if (currentActorTestClearFlag() != 0) {
                effectSpawnScatterRandom(D_80720BE8, 0, 6.0f, 6, 0x50, 0x64, (s32)gCurrentActor->x, (s32)(gPrimaryPlayerActor->y + 100.0f), (s32)gCurrentActor->z);
                effectSpawnScatterRandom(D_80720BE8, 0x14, 6.0f, 8, 0x96, 0x46, (s32)gCurrentActor->x, (s32)(gPrimaryPlayerActor->y + 100.0f), (s32)gCurrentActor->z);
                gCurrentActor->unk155++;
            }
            break;
        case 5:
            if (camIsCutsceneActive() == 0) {
                bossSetRandomObjectPair(waypoints, 0);
                i = 0;
                do {
                    if (i != waypoints->current) {
                        csModelStateSetFirstByte(i, 0x28);
                    }
                    i++;
                } while (i < 0x10);
                bossSpawnParticleRing(0x8A, D_807FDCA0->entries[waypoints->current].x, D_807FDCA0->entries[waypoints->current].y, D_807FDCA0->entries[waypoints->current].z, 0x5DC, 1);
                gCurrentActor->state = 0x40;
                i = 0;
                do {
                    volumeTriggerSetEnabled(i, 0);
                    i++;
                } while (i < 7);
            }
            break;
        }
        break;
    default:
        bossScriptStep(tbl, 0, 0.0f);
        break;
    }
    if (flag7F != 0) {
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

    switch (gCurrentActor->unk155) {
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

#pragma GLOBAL_ASM("asm/boss/nonmatchings/F0D0/D_80036C10.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/F0D0/D_80036C18.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/F0D0/D_80036C20.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/F0D0/D_80036C28.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/F0D0/D_80036C30.s")

#pragma GLOBAL_ASM("asm/boss/nonmatchings/F0D0/D_80036C40.s")

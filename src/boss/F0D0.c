#include "common.h"
#include "actor.h"
#define PROTO_SKIP_csModelStateSetFirstByte // FAKE: callee prototype steer
#include "proto/boss/3840.h"
#include "proto/boss/F0D0.h"
#include "proto/global/119370.h"
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


typedef struct BossE_F0D0_Sub14 {
    u8 pad0[0x14];
    u8 unk14;
    u8 unk15;
    u8 unk16;
} BossE_F0D0_Sub14;

extern Actor *gCurrentActor;
extern Actor *gPrimaryPlayerActor;
extern void *gCamActor;
extern void *effectPuffRiseUpdate;
extern void *D_8074E880[];
typedef struct {
    u8 b[4];
} BossWaypointPick;
extern BossWaypointPick D_80035B80;

u8 bossPickWaypointStep(BossE_F0D0_Sub14 *sub14, u8 *waypointIndices) {
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

    if (sub14->unk14 >= 3) {
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

f32 mathSinF(s16);

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
    effectSetCallback(&effectPuffRiseUpdate);
    effectSetDepth(1);
    effectSetSpeed(1);
    effectCreateAtPosition(D_8074E880[((randomNonNegative() >> 15) % 1000) % 3], (f32) (f64) scale, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
}

void csModelStateSetFirstByte(s16, u8); // FAKE: callee prototype steer
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

s32 bossCheckPlayerBelow(BossE_F0D0_Sub14 *sub14, u8 *scriptOpcodes) {
    if ((gPrimaryPlayerActor->y < (gCurrentActor->y - 10.0f)) && (sub14->unk14 < 5)) {
        sub14->unk15 = sub14->unk16;
        gCurrentActor->state = scriptOpcodes[sub14->unk15];
        sub14->unk15++;
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

typedef struct BossF_State {
    u8 pad0[8];
    s16 unk8;
    u8 padA[0x14 - 0xA];
    u8 unk14;
    u8 unk15;
    u8 unk16;
    u8 unk17;
    u8 unk18;
    u8 unk19;
} BossF_State;

typedef struct BossF_Sub {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    u8 unk4;
    u8 unk5;
    u8 unk6;
} BossF_Sub;

typedef struct BossF_Actor {
    u8 pad0[0x60];
    s32 unk60;
    u8 pad64[0x6A - 0x64];
    u16 unk6A;
    u8 pad6C[2];
    s16 unk6E;
    u8 pad70[0x7C - 0x70];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xC0 - 0x88];
    f32 unkC0;
    f32 unkC4;
    f32 unkC8;
    u8 unkCC;
    u8 padCD[0x110 - 0xCD];
    u8 unk110;
    u8 pad111[0x128 - 0x111];
    s16 unk128;
    u8 pad12A[0x144 - 0x12A];
    u8 unk144;
    u8 pad145;
    s16 unk146;
    u8 pad148[0x154 - 0x148];
    u8 unk154;
    u8 unk155;
    u8 pad156[0x178 - 0x156];
    BossF_State *unk178;
    BossF_Sub *unk17C;
} BossF_Actor;

#define BF ((BossF_Actor *)gCurrentActor)
#define BP ((BossF_Actor *)gPrimaryPlayerActor)

extern u8 *D_80035B84[];
extern u8 D_80035B98[];
extern u8 D_80035BD8[];
extern u8 D_80035BEC[];
extern u8 D_80036DD0[];
extern f32 D_80036C40[];
extern u8 D_807FBDC4;
extern s32 gFrameCounter;
extern s16 D_807502DC;
extern f32 D_807502F0;
extern u8 D_8071EDEC[];
extern u8 D_8071FC58[];
extern u8 D_80720054[];
extern u8 D_80720BE8[];

void bossMainStep(void) {
    BossF_State *st;
    BossF_Sub *sub;
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

    st = BF->unk178;
    sub = BF->unk17C;
    tbl = D_80035B84[st->unk14];
    if (BP->unk80 < BF->unk80 - 10.0f) {
        playerAbove = 1;
    } else {
        playerAbove = 0;
    }
    flag7F = 0;
    behaviourFrameBegin();
    actorUpdatePrevContactFlags(gCurrentActor);
    if (!(BF->unk60 & 0x10)) {
        BF->unkCC = 1;
        BF->unk144 = 0x24;
        if (flagGet(0x6A, 2) != 0) {
            actorScriptStart(gCurrentActor, 0x226);
            camStartPath(gCurrentActor, 0x14, 1);
            sub->unk0 = 9;
            sub->unk2 = 5;
            BF->unk154 = 0x20;
            BF->unk155 = 0;
            BF->unk155 = 0xB;
            BF->unk110 = 0;
        } else {
            BF->unk146 = 0;
            gBehaviourWorkState->scale = gCurrentActor->sub4->scaleY;
            actorSetUniformScale(gCurrentActor, gBehaviourWorkState->scale * 0.333);
            BF->unk154 = 0x1E;
            BF->unk155 = 0;
            BF->unk80 += 650.0f;
            BF->unk60 &= 0xFFFF7FFF;
            sub->unk0 = 0xF;
        }
        BF->unk6A &= 0xFFFE;
        BF->unkC4 = D_807502F0;
        BF->unkC8 = D_807502DC;
    }
    if (st->unk14 < 2) {
        if (sub->unk4 != 0) {
            idx = sub->unk4 - 0x10;
            nextIdx = sub->unk5 - 0x10;
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
            if (idx != sub->unk3) {
                lightSetRadius(0x1388);
                lightAdd(D_807FDCA0->entries[idx].x, D_807FDCA0->entries[idx].y - 0x32, D_807FDCA0->entries[idx].z, 0.0f, 0.0f, 0.0f, 240.0f, 0, red, green, 0xFF);
            }
            if (nextIdx != sub->unk3) {
                lightSetRadius(0x1388);
                lightAdd(D_807FDCA0->entries[nextIdx].x, D_807FDCA0->entries[nextIdx].y - 0x32, D_807FDCA0->entries[nextIdx].z, 0.0f, 0.0f, 0.0f, 240.0f, 0, red, green, 0xFF);
            }
        }
    }
    if ((BF->unk154 == 0x27 && st->unk14 == 4) || (gActorGlobalState.unk15 != 0 && BF->unk154 != 0x37)) {
        if (BP->unk154 == 0x36) {
            BF->unk154 = 0x2B;
            BF->unk155 = 0;
        } else {
            actorScriptStart(gCurrentActor, 0x226);
            BF->unk154 = 0x37;
            BF->unk155 = 0;
        }
    }
    if (BF->unk154 == 0x23 && BF->unk155 == 1 && playerAbove == 0 && sub->unk6 != 0) {
        BF->unk154 = 0x2B;
        BF->unk155 = 0;
    }
    switch (BF->unk154) {
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
            BF->unk154 = 0x1F;
            BF->unk155 = 0;
        }
        break;
    case 0x1F:
        bright = (u32)(mathSinF(gFrameCounter * 0x7D) * 100.0f + 155.0f);
        lightSetRadius(0x1388);
        lightAdd(D_807FDCA0->entries[5].x, D_807FDCA0->entries[5].y - 0x28A, D_807FDCA0->entries[5].z, 0.0f, 0.0f, 0.0f, 240.0f, 0, bright, bright, bright);
        if (currentActorTestClearFlag() != 0) {
            sfxPlayAtPositionPooled(BF->unk7C, BF->unk80, BF->unk84, 0x19C, 0x64, 0x7F, 0, 0, 0.0f, 0);
            BF->unk154 = 0x20;
            BF->unk155 = 0;
        }
        break;
    case 0x20:
        behaviourUpdateShadowAlpha();
        switch (BF->unk155) {
        case 0:
            effectSpawnBoneDebris(4, 1);
            flag7F = 1;
            actorApplyGravity();
            actorApplyVelocityCustom(gCurrentActor, 0.0f, BF->unkC0);
            actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
            if (BF->unk110 == 1) {
                BF->unk155++;
            }
            break;
        case 1:
            if (currentActorTestClearFlag() != 0) {
                BF->unk155++;
            }
            break;
        case 2:
            actorScriptStart(gCurrentActor, 0x225);
            actorScriptExecute(gCurrentActor);
            st->unk18 = 2;
            sub->unk1 = D_80035BD8[st->unk18];
            sub->unk2 = 0xFF;
            BF->unk155++;
            BF->unk6A |= 1;
        case 3:
            scriptSetActorRampTarget(gCurrentActor, 1.0f, 0.0f);
            BF->unk155++;
        case 4:
            actorUpdatePrevContactFlags(gCurrentActor);
            actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
            bossInterpolateWaypoints((u8 *)sub, 0.025f);
            if (gCurrentActor->sub4->model->frame >= 40.0f) {
                BF->unk6A |= 1;
            } else {
                BF->unk6A = 0;
                effectSpawnBoneDebris(4, 1);
                flag7F = 1;
            }
            break;
        case 5:
            sub->unk0 = sub->unk1;
            v = st->unk18;
            if (v != 0) {
                left = v;
                left--;
                if (v) {} // FAKE: keeps v live past the decrement so the raw temp does not share its register
                st->unk18 = left;
                sub->unk1 = D_80035BD8[left];
                BF->unk155 = 3;
            } else {
                actorScriptStart(gCurrentActor, 0x224);
                BF->unk155++;
            }
            break;
        case 6:
            actorTurnTowardActorYaw(0xA, gPrimaryPlayerActor);
            break;
        case 7:
            actorScriptStart(gCurrentActor, 0x222);
            BF->unk155++;
        case 8:
            if (currentActorTestClearFlag() != 0) {
                BF->unk155++;
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
                BF->unk155++;
            }
            break;
        case 11:
            BF->unk6A &= 0xFFFE;
            if (currentActorTestClearFlag() != 0) {
                actorScriptStart(gCurrentActor, 0x22C);
                BF->unk155++;
            }
            break;
        case 13:
            camSetSecondTarget(gCamActor, D_807FDCA0->entries[17].x, D_807FDCA0->entries[17].z);
            st->unk14 = 0;
            st->unk15 = 0;
            BF->unk154 = tbl[st->unk15];
            st->unk15++;
            BF->unk155 = 0;
            sub->unk2 = 5;
            break;
        }
        break;
    case 0:
        switch (BF->unk155) {
        case 0:
        case 1:
        case 2:
            bossSetRandomObjectPair(sub, 0);
            actorScriptStart(gCurrentActor, 0x226);
            BF->unk155 = 3;
            break;
        case 3:
            if (BP->unk154 != 0x33) {
                st->unk15 = st->unk16;
                BF->unk154 = tbl[st->unk15];
                st->unk15++;
                BF->unk155 = 0;
            }
            break;
        }
        break;
    case 0x23:
        behaviourUpdateShadowAlpha();
        switch (BF->unk155) {
        case 0:
            st->unk18 = tbl[st->unk15++];
            st->unk19 = st->unk18;
            bossSetAnimationByWaypoint((u8 *)sub);
            sub->unk1 = bossPickWaypointStep((BossE_F0D0_Sub14 *)st, (u8 *)sub);
            BF->unk155 = 1;
            BF->unk6A |= 1;
        case 1:
            BF->unk155 = 2;
            scriptSetActorRampTarget(gCurrentActor, D_80036C40[st->unk14], 0.0f);
            sub->unk6 = playerAbove;
        case 2:
            actorUpdatePrevContactFlags(gCurrentActor);
            actorUpdateFloorContactAndTilt(gCurrentActor, 0.0f);
            bossInterpolateWaypoints((u8 *)sub, gCurrentActor->sub4->animId == 0x223 ? 0.02173913f : 0.041666664f);
            if (gCurrentActor->sub4->animId == 0x223) {
                v = 0x35;
            } else {
                v = 0x17;
            }
            if ((f32)(s32)v <= gCurrentActor->sub4->model->frame) {
                BF->unk6A |= 1;
            } else {
                BF->unk6A = 0;
                effectSpawnBoneDebris(4, 1);
                flag7F = 1;
            }
            break;
        case 3:
            sub->unk2 = sub->unk0;
            sub->unk0 = sub->unk1;
            if (playerAbove != 0) {
                st->unk18 = st->unk19;
            }
            if (st->unk18 != 0) {
                sub->unk1 = bossPickWaypointStep((BossE_F0D0_Sub14 *)st, (u8 *)sub);
                st->unk18--;
                bossSetAnimationByWaypoint((u8 *)sub);
                BF->unk155 = 1;
            } else {
                BF->unk154 = tbl[st->unk15];
                st->unk15++;
                BF->unk155 = 0;
            }
            break;
        }
        break;
    case 0x25:
    case 0x28:
        actorTurnTowardActorYaw(0xA, gPrimaryPlayerActor);
        if (bossCheckPlayerBelow((BossE_F0D0_Sub14 *)st, tbl) != 0) {
            bossSetRandomObjectPair(sub, 0);
        } else if (func_80724A20() == 0) {
            switch (BF->unk155) {
            case 0:
                bossSetRandomObjectPair(sub, 0xA);
                st->unk18 = tbl[st->unk15++] - 1;
                st->unk19 = tbl[st->unk15++];
                actorScriptStart(gCurrentActor, 0x229);
                BF->unk155 = 1;
                break;
            case 2:
                if (BF->unk154 == 0x25) {
                    actorScriptStart(gCurrentActor, 0x228);
                } else {
                    if (!(gBehaviourWorkState->flags & 0x8000)) {
                        if (BP->unk110 != 1) {
                            break;
                        }
                        camStartPath(gCurrentActor, 0xF, 1);
                        gBehaviourWorkState->flags |= 0x8000;
                    }
                    actorScriptStart(gCurrentActor, 0x22F);
                }
                BF->unk155 = 3;
                break;
            case 3:
                if (BF->unk154 == 0x25) {
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
                if (BF->unk154 == 0x25) {
                    projectileGetTargetCoords(gCurrentActor, 3);
                    projectileAimAndSpawn(0x3B, 1, 1.2f, BP->unk7C, BP->unk80 + 5.0f, BP->unk84, 900.0f, gCurrentActor);
                } else {
                    sub->unk1 = bossPickWaypointStep((BossE_F0D0_Sub14 *)st, (u8 *)sub);
                    bossSpawnObjectAtWaypoint((u8 *)sub);
                }
                BF->unk155 = 5;
                break;
            case 6:
                v = st->unk18;
                if (v != 0) {
                    st->unk18 = v - 1;
                    gBehaviourWorkState->timer = st->unk19;
                    BF->unk155 = 7;
                } else {
                    actorScriptStart(gCurrentActor, 0x22D);
                    BF->unk155 = 8;
                }
                break;
            case 7:
                if (gBehaviourWorkState->timer != 0) {
                    if (BP->unk154 == 0x33) {
                        gBehaviourWorkState->timer = st->unk19;
                    } else {
                        gBehaviourWorkState->timer = gBehaviourWorkState->timer - 1;
                    }
                } else {
                    BF->unk155 = 2;
                }
                break;
            case 9:
                bossSetRandomObjectPair(sub, 0);
                actorScriptStart(gCurrentActor, 0x22C);
                BF->unk155 = 0xA;
                break;
            case 11:
                BF->unk154 = tbl[st->unk15];
                st->unk15++;
                BF->unk155 = 0;
                break;
            }
        }
        break;
    case 0x27:
        switch (BF->unk155) {
        case 0:
        case 1:
        case 2:
            actorAppendActiveCallback8();
            bossSetRandomObjectPair(sub, 0);
            actorScriptStart(gCurrentActor, 0x22E);
            camStartPath(gCurrentActor, 2, 1);
            actorSpawnAttachment(gCurrentActor, 1.2f);
            sfxPlayAtPositionPooled(BF->unk7C, BF->unk80, BF->unk84, 0x305, 0xFF, 0x7F, 0, 0, 0.0f, 0);
            BF->unk155 = 3;
            break;
        case 4:
            effectSpawnJointBeam(7, 0xB, 0x11, 0x20);
            effectSpawnJointBeam(0xC, 0x10, 0x11, 0x20);
            break;
        case 5:
            effectSpawnRandomBoneDebris(7, 0x20);
            if (currentActorTestClearFlag() != 0 || camIsCutsceneActive() == 0) {
                BF->unk155++;
            }
            break;
        case 6:
            if (st->unk14 < 3) {
                actorScriptStart(gCurrentActor, 0x22C);
            } else {
                BF->unk155++;
            }
            BF->unk155++;
            break;
        case 8:
            currentActorClearFlag();
            st->unk15 = 0;
            st->unk14++;
            tbl = D_80035B84[st->unk14];
            BF->unk154 = tbl[st->unk15];
            st->unk15++;
            BF->unk155 = 0;
            break;
        }
        break;
    case 0x29:
        switch (BF->unk155) {
        case 0:
            BF->unk60 &= 0xFFFF7FFF;
            actorScriptStart(gCurrentActor, 0x231);
            st->unk8 = (s8)tbl[st->unk15++];
            BF->unk155++;
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
            bossAdjustHealth(st->unk8);
            break;
        case 5:
            BF->unk154 = tbl[st->unk15];
            st->unk15++;
            BF->unk155 = 0;
            break;
        }
        break;
    case 0x2B:
        switch (BF->unk155) {
        case 0:
            actorScriptStart(gCurrentActor, 0x222);
            gBehaviourWorkState->timer = 0x5A;
            BF->unk155++;
            break;
        case 1:
            if (gBehaviourWorkState->timer != 0) {
                gBehaviourWorkState->timer = gBehaviourWorkState->timer - 1;
            } else {
                st->unk15 = st->unk16;
                BF->unk154 = tbl[st->unk15];
                st->unk15++;
                BF->unk155 = 0;
            }
            break;
        }
        break;
    case 0x37:
        switch (BF->unk155) {
        case 0:
            camStartPath(gCurrentActor, 6, 0x81);
            BF->unk155++;
            break;
        case 1:
            if (currentActorTestClearFlag() != 0) {
                BF->unk155++;
            }
            break;
        case 2:
            bossAdjustHealth(5);
            break;
        case 3:
            if (currentActorTestClearFlag() != 0) {
                csModelStateSetFirstByte(sub->unk0, 0x1E);
                BF->unk155++;
            }
            break;
        case 4:
            if (currentActorTestClearFlag() != 0) {
                effectSpawnScatterRandom(D_80720BE8, 0, 6.0f, 6, 0x50, 0x64, (s32)BF->unk7C, (s32)(BP->unk80 + 100.0f), (s32)BF->unk84);
                effectSpawnScatterRandom(D_80720BE8, 0x14, 6.0f, 8, 0x96, 0x46, (s32)BF->unk7C, (s32)(BP->unk80 + 100.0f), (s32)BF->unk84);
                BF->unk155++;
            }
            break;
        case 5:
            if (camIsCutsceneActive() == 0) {
                bossSetRandomObjectPair(sub, 0);
                i = 0;
                do {
                    if (i != sub->unk0) {
                        csModelStateSetFirstByte(i, 0x28);
                    }
                    i++;
                } while (i < 0x10);
                bossSpawnParticleRing(0x8A, D_807FDCA0->entries[sub->unk0].x, D_807FDCA0->entries[sub->unk0].y, D_807FDCA0->entries[sub->unk0].z, 0x5DC, 1);
                BF->unk154 = 0x40;
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
        if (BF->unk6E == -1) {
            sfxPlayActorSound(gCurrentActor, 0x135, 0x4B, 1, 0, 0xB4, 1.0f, 0);
        }
    } else {
        sfxStopSlotSound(gCurrentActor, 0);
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}
#undef sub
#undef tbl
#undef BF
#undef BP

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

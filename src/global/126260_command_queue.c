#include "common.h"
#include "render.h"
#include "actor.h"
#include "sched.h"
#include "proto/global/126260_command_queue.h"
#include "proto/global/15050_heap.h"
#include "proto/global/69E60_actor_physics.h"
#include "proto/global/70FD0_collision_geometry.h"

extern FrameMatrices *gGfxCurrentFrameBuffer;
extern u8 gLightCommandCount;
extern u8 gLightSetIndex;
extern s16 gLightAngleOffset;
extern s16 gLightDistance;
extern s16 gLightHeightOffset;
extern u8 gLightAmbientTint;
extern u8 gLightDirectionalTint;
extern u8 gLightRed;
extern u8 gLightGreen;
extern u8 gLightBlue;

s16 gPlayerLightHeight = 0;
f32 gPlayerLightRed = 255.0f;
f32 gPlayerLightBlue = 255.0f;
f32 gPlayerLightGreen = 255.0f;

typedef struct {
    s32 unk0;
    s16 x;
    s16 y;
    s16 z;
    u8 radius;
    u8 red;
    u8 green;
    u8 blue;
    s8 type;
} CommandState;

typedef struct Command {
    Actor *actor;
    s16 x;
    s16 y;
    s16 z;
    u8 radius;
    u8 red;
    u8 green;
    u8 blue;
    u8 type;
} Command;

extern CommandState gLightAmbient;
extern Command *gLightCommandQueue;

void commandSetParameters(s16 angleOffset, s16 distance, s16 heightOffset, u8 red, u8 green, u8 blue) {
    gLightAngleOffset = angleOffset;
    gLightDistance = distance;
    gLightHeightOffset = heightOffset;
    gLightRed = red;
    gLightGreen = green;
    gLightBlue = blue;
}

void commandSetColor(s8 red, s8 green, s8 blue) {
    gLightAmbient.red = red;
    gLightAmbient.green = green;
    gLightAmbient.blue = blue;
}

void commandSetFlags(s8 ambientFlag, s8 directionalFlag) {
    gLightAmbientTint = ambientFlag;
    gLightDirectionalTint = directionalFlag;
}

void commandStateInit(void) {
    gLightAmbient.z = 0;
    gLightAmbient.red = 0x6B;
    gLightAmbient.green = 0x30;
    gLightAmbient.blue = 0x50;
    gLightAmbient.type = 7;
    gLightAmbient.y = gLightAmbient.z;
    gLightAmbient.x = gLightAmbient.z;
    gLightCommandQueue = heapAlloc(0x200);
    commandSetParameters(0x320, 0x82, 0, 0xFF, 0xFF, 0xFF);
    commandSetFlags(1, 1);
}

void lightEasePlayerTarget(s16 targetRed, s16 targetBlue, s16 targetGreen, s16 targetHeight) {
    gPlayerLightHeight += (targetHeight - gPlayerLightHeight) * 0.1;
    gPlayerLightRed += (targetRed - gPlayerLightRed) * 0.1;
    gPlayerLightBlue += (targetBlue - gPlayerLightBlue) * 0.1;
    gPlayerLightGreen += (targetGreen - gPlayerLightGreen) * 0.1;
}

void commandQueuePush(Actor *actor, s16 x, s16 y, s16 z, u8 radius, u8 red, u8 green, u8 blue, u8 type) {
    Command *cmd;

    if (gLightCommandCount >= 0x20) {
        gLightCommandCount--;
    }
    cmd = &gLightCommandQueue[gLightCommandCount++];
    cmd->actor = actor;
    cmd->x = x;
    cmd->y = y;
    cmd->z = z;
    cmd->radius = radius;
    cmd->red = red;
    cmd->green = green;
    cmd->blue = blue;
    cmd->type = type;
}

s32 commandApplyToLight(u8 lightIndex, Command *cmd, f32 actorX, f32 actorY, f32 actorZ, s16 playerSlotIndex) {
    f32 dist;
    f64 dist_d;
    Light *lights;
    Ambient *ambient;
    Light *slot_light;
    f32 intensity;
    f64 falloff;
    f64 dy_d;
    u8 c;
    f32 factor;
    FrameMatrices *fb;

    fb = gGfxCurrentFrameBuffer;
    lights = fb->lightSets[gLightSetIndex].l;
    ambient = &fb->lightSets[gLightSetIndex].a;
    slot_light = &fb->lightSets[gLightSetIndex].l[lightIndex];

    if (lightIndex >= 7) {
        return 0;
    }

    if (cmd->type == 5) {
        dist_d = sqrtf(SQ(actorX - cmd->x) + SQ(actorZ - cmd->z));
        dist = MAX(dist_d, 0.001);
        factor = MAX(1.0, dist - cmd->radius / 2);
        falloff = (f32)cmd->radius / (0.5 * factor * factor);
        intensity = MIN(1.0, falloff);
        if (cmd->y + 50 < actorY) {
            dy_d = MIN(20.0, actorY - cmd->y - 50.0f);
            intensity *= 1.0 - dy_d / 20.0;
        }
    } else {
        dist_d = sqrtf(SQ(actorX - cmd->x) + SQ(actorY - cmd->y) + SQ(actorZ - cmd->z));
        dist = MAX(dist_d, 0.001);
        intensity = 1.0f;
    }

    if (cmd->type == 5) {
        if (intensity > 0.1) {
            c = lights->l.col[0] + (cmd->red - lights->l.col[0]) * intensity;
            lights->l.colc[0] = c;
            lights->l.col[0] = c;

            c = lights->l.col[1] + (cmd->green - lights->l.col[1]) * intensity;
            lights->l.colc[1] = c;
            lights->l.col[1] = c;

            c = lights->l.col[2] + (cmd->blue - lights->l.col[2]) * intensity;
            lights->l.colc[2] = c;
            lights->l.col[2] = c;

            c = ambient->l.col[0] + (ambient->l.col[0] / 2.0 - ambient->l.col[0]) * intensity;
            ambient->l.colc[0] = c;
            ambient->l.col[0] = c;

            c = ambient->l.col[1] + (ambient->l.col[1] / 2.0 - ambient->l.col[1]) * intensity;
            ambient->l.colc[1] = c;
            ambient->l.col[1] = c;

            c = ambient->l.col[2] + (ambient->l.col[2] / 2.0 - ambient->l.col[2]) * intensity;
            ambient->l.colc[2] = c;
            ambient->l.col[2] = c;
        }
        return 0;
    }

    if (intensity > 0.02) {
        c = cmd->red * intensity;
        slot_light->l.colc[0] = c;
        slot_light->l.col[0] = c;

        c = cmd->green * intensity;
        slot_light->l.colc[1] = c;
        slot_light->l.col[1] = c;

        c = cmd->blue * intensity;
        slot_light->l.colc[2] = c;
        slot_light->l.col[2] = c;

        factor = 127.0f / dist; // FAKE: reuse of factor for 127/dist raises adjsave 1.5->3.0, colours factor $f2
        slot_light->l.dir[0] = (cmd->x - actorX) * factor;
        slot_light->l.dir[1] = (cmd->y - actorY) * factor;
        slot_light->l.dir[2] = (cmd->z - actorZ) * factor;
        return 1;
    }

    return 0;
}

void commandQueueReset(void) {
    gLightCommandCount = 0;
    gLightSetIndex = 0;
}

extern Actor *gPrimaryPlayerActor;
extern f32 *gChunkLightR;
extern f32 *gChunkLightG;
extern f32 *gChunkLightB;
extern PlayerStruct *gPlayerSlots;
extern f32 gHiliteKeyDirX;
extern f32 gHiliteKeyDirY;
extern f32 gHiliteKeyDirZ;
extern f32 gHiliteFillDirX;
extern f32 gHiliteFillDirY;
extern f32 gHiliteFillDirZ;


Gfx *actorBuildLightDisplayList(Gfx *glist, Actor *targetActor, s16 playerSlotIndex) {
    u8 is_player;
    FrameMatrices *frame;
    Light *secondary;
    Ambient *primary;
    u8 num_lights;
    s32 pad;
    s16 height_offset;
    s16 angle;
    s16 chunk;
    s16 i;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 inv_distance;
    f32 scale;
    f32 dest_blue;
    f32 dest_green;
    f32 dest_red;
    f32 x;
    f32 y;
    f32 z;
    f32 color[3];

    if (targetActor == gPrimaryPlayerActor) {
        is_player = 1;
    } else {
        is_player = 0;
    }
    num_lights = 1;
    frame = gGfxCurrentFrameBuffer;
    primary = &frame->lightSets[gLightSetIndex].a;
    secondary = &frame->lightSets[gLightSetIndex].l[0];

    if (targetActor->lightNodeId) {
        actorGetNodePos(targetActor, targetActor->lightNodeId, &x, &y, &z);
    } else {
        x = targetActor->x;
        y = targetActor->y;
        z = targetActor->z;
    }

    if (is_player) {
        dest_red = gPlayerLightRed;
        dest_green = gPlayerLightGreen;
        dest_blue = gPlayerLightBlue;
        height_offset = gPlayerLightHeight;
    } else {
        dest_red = gLightRed;
        dest_green = gLightGreen;
        dest_blue = gLightBlue;
        height_offset = 0;
    }

    chunk = targetActor->chunkIndex;
    if (chunk == -1) {
        chunk = 0;
    }

    if (targetActor->renderFlags & 1) {
        scale = 1.0f;
    } else {
        scale = targetActor->tintA / 15.0f;
    }

    if (targetActor->flags & 0x800000) {
        color[0] = targetActor->tintR / 255.0;
        color[1] = targetActor->tintG / 255.0;
        color[2] = targetActor->tintB / 255.0;
    } else {
        color[0] = gChunkLightR[chunk];
        color[1] = gChunkLightG[chunk];
        color[2] = gChunkLightB[chunk];
    }

    primary->l.col[0] = primary->l.colc[0] = (u8)((gLightAmbientTint ? color[0] * scale : 1.0) * gLightAmbient.red);
    primary->l.col[1] = primary->l.colc[1] = (u8)((gLightAmbientTint ? color[1] * scale : 1.0) * gLightAmbient.green);
    primary->l.col[2] = primary->l.colc[2] = (u8)((gLightAmbientTint ? color[2] * scale : 1.0) * gLightAmbient.blue);

    secondary->l.col[0] = (u8)(s32)((gLightDirectionalTint ? color[0] * scale : 1.0) * dest_red);
    secondary->l.col[1] = (u8)(s32)((gLightDirectionalTint ? color[1] * scale : 1.0) * dest_green);
    secondary->l.col[2] = (u8)(s32)((gLightDirectionalTint ? color[2] * scale : 1.0) * dest_blue);
    secondary->l.colc[0] = secondary->l.col[0];
    secondary->l.colc[1] = secondary->l.col[1];
    secondary->l.colc[2] = secondary->l.col[2];

    angle = mathAngleBetweenPoints2D(x, z, gPlayerSlots[playerSlotIndex].eyeX, gPlayerSlots[playerSlotIndex].eyeZ) + gLightAngleOffset;
    dx = (gPlayerSlots[playerSlotIndex].eyeX - (mathSinF(angle) * gLightDistance)) - x;
    dy = height_offset + gLightHeightOffset;
    dz = (gPlayerSlots[playerSlotIndex].eyeZ - (mathCosF(angle) * gLightDistance)) - z;
    inv_distance = 127.0f / sqrtf((dx * dx) + (dy * dy) + (dz * dz));
    secondary->l.dir[0] = (s8)(dx * inv_distance);
    secondary->l.dir[1] = (s8)(dy * inv_distance);
    secondary->l.dir[2] = (s8)(dz * inv_distance);

    if (is_player) {
        gHiliteKeyDirX = secondary->l.dir[0];
        gHiliteKeyDirY = secondary->l.dir[1];
        gHiliteKeyDirZ = secondary->l.dir[2];
        gHiliteFillDirX = 10.0f;
        gHiliteFillDirY = -10.0f;
        gHiliteFillDirZ = 10.0f;
        gPlayerLightHeight += -gPlayerLightHeight * 0.05;
        gPlayerLightRed += (gLightRed - gPlayerLightRed) * 0.05;
        gPlayerLightBlue += (gLightGreen - gPlayerLightBlue) * 0.05;
        gPlayerLightGreen += (gLightBlue - gPlayerLightGreen) * 0.05;
    }

    for (i = 0; i < gLightCommandCount; i++) {
        if (gLightCommandQueue[i].actor == targetActor && commandApplyToLight(num_lights, &gLightCommandQueue[i], x, y, z, playerSlotIndex) != 0) {
            num_lights++;
        }
    }

    if (!(gGlobalPauseFlags & 2) && (targetActor->collisionFlags & 1)) {
        PlayerState *hit = targetActor->customState;
        if (hit->surfaceTimer != 0 && (gFrameCounter & 2)) {
            secondary->l.col[0] = 0;
            secondary->l.col[1] = 0;
            secondary->l.col[2] = 0;
            secondary->l.colc[0] = 0;
            secondary->l.colc[1] = 0;
            secondary->l.colc[2] = 0;
            primary->l.col[2] = 0;
            primary->l.col[1] = 0;
            primary->l.col[0] = 0;
            primary->l.colc[2] = 0;
            primary->l.colc[1] = 0;
            primary->l.colc[0] = 0;
        }
    }

    for (i = 0; i < num_lights; i++) {
        gSPLight(glist++, &frame->lightSets[gLightSetIndex].l[i], i + 1);
    }
    gSPLight(glist++, &frame->lightSets[gLightSetIndex].a, num_lights + 1);
    gSPNumLights(glist++, num_lights);
    gDPPipeSync(glist++);

    gLightSetIndex++;
    if (gLightSetIndex >= 0x18) {
        gLightSetIndex--;
    }
    return glist;
}



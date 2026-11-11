#include "common.h"
#include "actor.h"
#include "sched.h"
#include "proto/global/126260.h"
#include "proto/global/15050.h"
#include "proto/global/69E60.h"
#include "proto/global/70FD0.h"

extern s32 gGfxCurrentFrameBuffer;
extern u8 gLightCommandCount;
extern u8 gLightSetIndex;
extern s16 D_807FDB76;
extern s16 D_807FDB78;
extern s16 D_807FDB7A;
extern u8 D_807FDB7C;
extern u8 D_807FDB7D;
extern u8 D_807FDB7E;
extern u8 D_807FDB7F;
extern u8 D_807FDB80;

f32 mathCosF(s16);
f32 mathSinF(s16);

typedef struct {
    s32 unk0;
    s16 x;
    s16 y;
    s16 z;
    u8 radius;
    s8 red;
    s8 green;
    s8 blue;
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

extern CommandState D_807FDB60;
extern Command *gLightCommandQueue;

void commandSetParameters(s16 angleOffset, s16 distance, s16 heightOffset, u8 red, u8 green, u8 blue) {
    D_807FDB76 = angleOffset;
    D_807FDB78 = distance;
    D_807FDB7A = heightOffset;
    D_807FDB7E = red;
    D_807FDB7F = green;
    D_807FDB80 = blue;
}

void commandSetColor(s8 red, s8 green, s8 blue) {
    D_807FDB60.red = red;
    D_807FDB60.green = green;
    D_807FDB60.blue = blue;
}

void commandSetFlags(s8 ambientFlag, s8 directionalFlag) {
    D_807FDB7C = ambientFlag;
    D_807FDB7D = directionalFlag;
}

void commandStateInit(void) {
    D_807FDB60.z = 0;
    D_807FDB60.red = 0x6B;
    D_807FDB60.green = 0x30;
    D_807FDB60.blue = 0x50;
    D_807FDB60.type = 7;
    D_807FDB60.y = D_807FDB60.z;
    D_807FDB60.x = D_807FDB60.z;
    gLightCommandQueue = heapAlloc(0x200);
    commandSetParameters(0x320, 0x82, 0, 0xFF, 0xFF, 0xFF);
    commandSetFlags(1, 1);
}

extern s16 D_80755680;
extern f32 D_80755684;
extern f32 D_80755688;
extern f32 D_8075568C;

void func_8072167C(s16 targetRed, s16 targetBlue, s16 targetGreen, s16 targetRot) {
    D_80755680 += (targetRot - D_80755680) * 0.1;
    D_80755684 += (targetRed - D_80755684) * 0.1;
    D_80755688 += (targetBlue - D_80755688) * 0.1;
    D_8075568C += (targetGreen - D_8075568C) * 0.1;
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
    f64 clamped;
    f64 dy_d;
    u8 c;
    f32 base;

    lights = (Light *)((u8 *)gGfxCurrentFrameBuffer + (gLightSetIndex * 0x78) + 0x278);
    ambient = (Ambient *)((u8 *)gGfxCurrentFrameBuffer + (gLightSetIndex * 0x78) + 0x270);
    slot_light = &((Light *)((u8 *)gGfxCurrentFrameBuffer + (gLightSetIndex * 0x78) + 0x278))[lightIndex]; // FAKE: rebuilt from the frame buffer instead of &lights[lightIndex]; the shorter form drops the v1 frame-buffer candidate

    if (gGfxCurrentFrameBuffer == 0) {} // FAKE: makes the base load a uopt candidate (v1)
    if (lightIndex >= 7) {
        return 0;
    }

    if (cmd->type == 5) {
        dist_d = sqrtf((actorX - (f32)cmd->x) * (actorX - (f32)cmd->x) + (actorZ - (f32)cmd->z) * (actorZ - (f32)cmd->z));
        if (dist_d == 0.5) {} // FAKE: dead use of the 0.5 constant starts its web early (splits the ambient piece into f14)
        dist = (dist_d > 0.001) ? dist_d : 0.001;
        base = (dist - (f32)((s32)cmd->radius / 2) < 1.0) ? 1.0 : dist - (f32)((s32)cmd->radius / 2);
        clamped = (f64)(f32)(u32)cmd->radius / (0.5 * base * base);
        if (base == base) {} // FAKE: dead use raises base priority above clamped (f2 / f12)
        if (base == base) {} // FAKE: dead use raises base priority above clamped (f2 / f12)
        intensity = (clamped > 1.0) ? 1.0 : clamped;
        if ((f32)(cmd->y + 50) < actorY) {
            dy_d = ((actorY - (f32)cmd->y) - 50.0f > 20.0) ? 20.0 : (actorY - (f32)cmd->y) - 50.0f;
            intensity = (f64)intensity * (1.0 - (dy_d / 20.0));
        }
    } else {
        dist_d = sqrtf((actorX - (f32)cmd->x) * (actorX - (f32)cmd->x) + (actorY - (f32)cmd->y) * (actorY - (f32)cmd->y) + (actorZ - (f32)cmd->z) * (actorZ - (f32)cmd->z));
        dist = (dist_d > 0.001) ? dist_d : 0.001;
        intensity = 1.0f;
    }

    if (cmd->type == 5) {
        if (intensity > 0.1) {
            c = (u32)((f32)(u32)lights->l.col[0] + ((f32)(cmd->red - lights->l.col[0]) * intensity));
            lights->l.colc[0] = c;
            lights->l.col[0] = c;

            c = (u32)((f32)(u32)lights->l.col[1] + ((f32)(cmd->green - lights->l.col[1]) * intensity));
            lights->l.colc[1] = c;
            lights->l.col[1] = c;

            c = (u32)((f32)(u32)lights->l.col[2] + ((f32)(cmd->blue - lights->l.col[2]) * intensity));
            lights->l.colc[2] = c;
            lights->l.col[2] = c;

            c = (u32)((f64)(u32)ambient->l.col[0] + ((((f64)(u32)ambient->l.col[0] * 0.5) - (f64)(u32)ambient->l.col[0]) * (f64)intensity));
            ambient->l.colc[0] = c;
            ambient->l.col[0] = c;

            c = (u32)((f64)(u32)ambient->l.col[1] + ((((f64)(u32)ambient->l.col[1] * 0.5) - (f64)(u32)ambient->l.col[1]) * (f64)intensity));
            ambient->l.colc[1] = c;
            ambient->l.col[1] = c;

            c = (u32)((f64)(u32)ambient->l.col[2] + ((((f64)(u32)ambient->l.col[2] * 0.5) - (f64)(u32)ambient->l.col[2]) * (f64)intensity));
            ambient->l.colc[2] = c;
            ambient->l.col[2] = c;
        }
        return 0;
    }

    if (intensity > 0.02) {
        c = (u32)((f32)(u32)cmd->red * intensity);
        slot_light->l.colc[0] = c;
        slot_light->l.col[0] = c;

        c = (u32)((f32)(u32)cmd->green * intensity);
        slot_light->l.colc[1] = c;
        slot_light->l.col[1] = c;

        c = (u32)((f32)(u32)cmd->blue * intensity);
        slot_light->l.colc[2] = c;
        slot_light->l.col[2] = c;

        slot_light->l.dir[0] = (s8)(((f32)cmd->x - actorX) * (127.0f / dist));
        slot_light->l.dir[1] = (s8)(((f32)cmd->y - actorY) * (127.0f / dist));
        slot_light->l.dir[2] = (s8)(((f32)cmd->z - actorZ) * (127.0f / dist));
        return 1;
    }

    return 0;
}

void commandQueueReset(void) {
    gLightCommandCount = 0;
    gLightSetIndex = 0;
}

extern Actor *gPrimaryPlayerActor;
extern s32 gGlobalPauseFlags;
extern u32 gFrameCounter;
extern f32 *D_8076A0B4;
extern f32 *D_8076A0B8;
extern f32 *D_8076A0BC;
extern PlayerStruct *gPlayerSlots;
extern f32 D_807444CC;
extern f32 D_807444D0;
extern f32 D_807444D4;
extern f32 D_807444D8;
extern f32 D_807444DC;
extern f32 func_807444E0;


typedef struct {
    u8 pad0[0xD4];
    s16 unkD4;
} FakesLightHitState;

Gfx *actorBuildLightDisplayList(Gfx *glist, Actor *targetActor, s16 playerSlotIndex) {
    u8 is_player;
    u8 *color_base;
    Light *secondary;
    Ambient *primary;
    u8 command;
    s32 pad;
    s16 camera_rotation;
    s16 angle;
    s16 sequence;
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
    command = 1;
    color_base = (u8 *)gGfxCurrentFrameBuffer;
    primary = &((Lights7 *)((u8 *)color_base + 0x270))[gLightSetIndex].a;
    secondary = &((Lights7 *)((u8 *)color_base + 0x270))[gLightSetIndex].l[0];

    if (targetActor->unkCD) {
        actorGetNodePos(targetActor, targetActor->unkCD, &x, &y, &z);
    } else {
        x = targetActor->x;
        y = targetActor->y;
        z = targetActor->z;
    }

    if (is_player) {
        dest_red = D_80755684;
        dest_green = D_8075568C;
        dest_blue = D_80755688;
        camera_rotation = D_80755680;
    } else {
        dest_red = D_807FDB7E;
        dest_green = D_807FDB7F;
        dest_blue = D_807FDB80;
        camera_rotation = 0;
    }

    sequence = targetActor->chunkIndex;
    if (sequence == -1) {
        sequence = 0;
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
        color[0] = D_8076A0B4[sequence];
        color[1] = D_8076A0B8[sequence];
        color[2] = D_8076A0BC[sequence];
    }

    primary->l.col[0] = primary->l.colc[0] = (u8)((D_807FDB7C ? color[0] * scale : 1.0) * (u8)D_807FDB60.red);
    primary->l.col[1] = primary->l.colc[1] = (u8)((D_807FDB7C ? color[1] * scale : 1.0) * (u8)D_807FDB60.green);
    primary->l.col[2] = primary->l.colc[2] = (u8)((D_807FDB7C ? color[2] * scale : 1.0) * (u8)D_807FDB60.blue);

    secondary->l.col[0] = (u8)(s32)((D_807FDB7D ? color[0] * scale : 1.0) * dest_red);
    secondary->l.col[1] = (u8)(s32)((D_807FDB7D ? color[1] * scale : 1.0) * dest_green);
    secondary->l.col[2] = (u8)(s32)((D_807FDB7D ? color[2] * scale : 1.0) * dest_blue);
    secondary->l.colc[0] = secondary->l.col[0];
    secondary->l.colc[1] = secondary->l.col[1];
    secondary->l.colc[2] = secondary->l.col[2];

    angle = mathAngleBetweenPoints2D(x, z, gPlayerSlots[playerSlotIndex].unk21C, gPlayerSlots[playerSlotIndex].unk224) + D_807FDB76;
    dx = (gPlayerSlots[playerSlotIndex].unk21C - (mathSinF(angle) * (f32)D_807FDB78)) - x;
    dy = (f32)(camera_rotation + D_807FDB7A);
    dz = (gPlayerSlots[playerSlotIndex].unk224 - (mathCosF(angle) * (f32)D_807FDB78)) - z;
    inv_distance = 127.0f / sqrtf((dx * dx) + (dy * dy) + (dz * dz));
    secondary->l.dir[0] = (s8)(dx * inv_distance);
    secondary->l.dir[1] = (s8)(dy * inv_distance);
    secondary->l.dir[2] = (s8)(dz * inv_distance);

    if (is_player) {
        D_807444CC = secondary->l.dir[0];
        D_807444D0 = secondary->l.dir[1];
        D_807444D4 = secondary->l.dir[2];
        D_807444D8 = 10.0f;
        D_807444DC = -10.0f;
        func_807444E0 = 10.0f;
        D_80755680 += -D_80755680 * 0.05;
        D_80755684 += (D_807FDB7E - D_80755684) * 0.05;
        D_80755688 += (D_807FDB7F - D_80755688) * 0.05;
        D_8075568C += (D_807FDB80 - D_8075568C) * 0.05;
    }

    for (i = 0; i < gLightCommandCount; i++) {
        if (gLightCommandQueue[i].actor == targetActor && commandApplyToLight(command, &gLightCommandQueue[i], x, y, z, playerSlotIndex) != 0) {
            command++;
        }
    }

    if (!(gGlobalPauseFlags & 2) && (targetActor->collisionFlags & 1)) {
        FakesLightHitState *hit = targetActor->customState;
        if (hit->unkD4 != 0 && (gFrameCounter & 2)) {
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

    for (i = 0; i < command; i++) {
        gSPLight(glist++, &((Lights7 *)(color_base + 0x270))[gLightSetIndex].l[i], i + 1);
    }
    gSPLight(glist++, &((Lights7 *)(color_base + 0x270))[gLightSetIndex].a, command + 1);
    gSPNumLights(glist++, command);
    gDPPipeSync(glist++);

    gLightSetIndex++;
    if (gLightSetIndex >= 0x18) {
        gLightSetIndex--;
    }
    return glist;
}



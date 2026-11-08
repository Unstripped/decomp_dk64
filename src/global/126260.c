#include "common.h"
#include "actor.h"

extern s32 gGfxCurrentFrameBuffer;
extern u8 D_807FDB74;
extern u8 D_807FDB75;
extern s16 D_807FDB76;
extern s16 D_807FDB78;
extern s16 D_807FDB7A;
extern u8 D_807FDB7C;
extern u8 D_807FDB7D;
extern u8 D_807FDB7E;
extern u8 D_807FDB7F;
extern u8 D_807FDB80;

void *heapAlloc(s32);
f32 mathCosF(s16);
f32 mathSinF(s16);

typedef struct {
    s32 unk0;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    u8 unkA;
    s8 unkB;
    s8 unkC;
    s8 unkD;
    s8 unkE;
} CommandState;

typedef struct {
    s32 unk0;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    u8 unkA;
    u8 unkB;
    u8 unkC;
    u8 unkD;
    u8 unkE;
} Command;

extern CommandState D_807FDB60;
extern s32 D_807FDB70;

void commandSetParameters(s16 angleOffset, s16 distance, s16 heightOffset, u8 red, u8 green, u8 blue) {
    D_807FDB76 = angleOffset;
    D_807FDB78 = distance;
    D_807FDB7A = heightOffset;
    D_807FDB7E = red;
    D_807FDB7F = green;
    D_807FDB80 = blue;
}

void commandSetColor(s8 red, s8 green, s8 blue) {
    D_807FDB60.unkB = red;
    D_807FDB60.unkC = green;
    D_807FDB60.unkD = blue;
}

void commandSetFlags(s8 ambientFlag, s8 directionalFlag) {
    D_807FDB7C = ambientFlag;
    D_807FDB7D = directionalFlag;
}

void commandStateInit(void) {
    D_807FDB60.unk8 = 0;
    D_807FDB60.unkB = 0x6B;
    D_807FDB60.unkC = 0x30;
    D_807FDB60.unkD = 0x50;
    D_807FDB60.unkE = 7;
    D_807FDB60.unk6 = D_807FDB60.unk8;
    D_807FDB60.unk4 = D_807FDB60.unk8;
    D_807FDB70 = (s32) heapAlloc(0x200);
    commandSetParameters(0x320, 0x82, 0, 0xFF, 0xFF, 0xFF);
    commandSetFlags(1, 1);
}

extern s16 D_80755680;
extern f32 D_80755684;
extern f32 D_80755688;
extern f32 D_8075568C;

void func_8072167C(s16 targetRed, s16 targetBlue, s16 targetGreen, s16 targetRot) {
    D_80755680 = (s16) (s32) ((f64) D_80755680 + ((f64) (targetRot - D_80755680) * 0.1));
    D_80755684 = (f32) ((f64) D_80755684 + ((f64) ((f32) targetRed - D_80755684) * 0.1));
    D_80755688 = (f32) ((f64) D_80755688 + ((f64) ((f32) targetBlue - D_80755688) * 0.1));
    D_8075568C = (f32) ((f64) D_8075568C + ((f64) ((f32) targetGreen - D_8075568C) * 0.1));
}

void commandQueuePush(s32 actor, s16 x, s16 y, s16 z, u8 radius, u8 red, u8 green, u8 blue, u8 type) {
    s32 queueIndex;
    s32 wrappedIndex;
    Command *cmd;

    queueIndex = D_807FDB74;
    if (queueIndex >= 0x20) {
        wrappedIndex = queueIndex - 1;
        D_807FDB74 = wrappedIndex & 0xFFFF;
        queueIndex = wrappedIndex & 0xFF;
    }
    cmd = (Command *)(D_807FDB70 + queueIndex * 0x10);
    D_807FDB74 = queueIndex + 1;
    cmd->unk0 = actor;
    cmd->unk4 = x;
    cmd->unk6 = y;
    cmd->unk8 = z;
    cmd->unkA = radius;
    cmd->unkB = red;
    cmd->unkC = green;
    cmd->unkD = blue;
    cmd->unkE = type;
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

    lights = (Light *)((u8 *)gGfxCurrentFrameBuffer + (D_807FDB75 * 0x78) + 0x278);
    ambient = (Ambient *)((u8 *)gGfxCurrentFrameBuffer + (D_807FDB75 * 0x78) + 0x270);
    slot_light = &((Light *)((u8 *)gGfxCurrentFrameBuffer + (D_807FDB75 * 0x78) + 0x278))[lightIndex];

    if (gGfxCurrentFrameBuffer == 0) {} // FAKE: makes the base load a uopt candidate (v1)
    if (lightIndex >= 7) {
        return 0;
    }

    if (cmd->unkE == 5) {
        dist_d = sqrtf((actorX - (f32)cmd->unk4) * (actorX - (f32)cmd->unk4) + (actorZ - (f32)cmd->unk8) * (actorZ - (f32)cmd->unk8));
        if (dist_d == 0.5) {} // FAKE: dead use of the 0.5 constant starts its web early (splits the ambient piece into f14)
        dist = (dist_d > 0.001) ? dist_d : 0.001;
        base = (dist - (f32)((s32)cmd->unkA / 2) < 1.0) ? 1.0 : dist - (f32)((s32)cmd->unkA / 2);
        clamped = (f64)(f32)(u32)cmd->unkA / (0.5 * base * base);
        if (base == base) {} // FAKE: dead use raises base priority above clamped (f2 / f12)
        if (base == base) {} // FAKE: dead use raises base priority above clamped (f2 / f12)
        intensity = (clamped > 1.0) ? 1.0 : clamped;
        if ((f32)(cmd->unk6 + 50) < actorY) {
            dy_d = ((actorY - (f32)cmd->unk6) - 50.0f > 20.0) ? 20.0 : (actorY - (f32)cmd->unk6) - 50.0f;
            intensity = (f64)intensity * (1.0 - (dy_d / 20.0));
        }
    } else {
        dist_d = sqrtf((actorX - (f32)cmd->unk4) * (actorX - (f32)cmd->unk4) + (actorY - (f32)cmd->unk6) * (actorY - (f32)cmd->unk6) + (actorZ - (f32)cmd->unk8) * (actorZ - (f32)cmd->unk8));
        dist = (dist_d > 0.001) ? dist_d : 0.001;
        intensity = 1.0f;
    }

    if (cmd->unkE == 5) {
        if ((f64)intensity > 0.1) {
            c = (u32)((f32)(u32)lights->l.col[0] + ((f32)(cmd->unkB - lights->l.col[0]) * intensity));
            lights->l.colc[0] = c;
            lights->l.col[0] = c;

            c = (u32)((f32)(u32)lights->l.col[1] + ((f32)(cmd->unkC - lights->l.col[1]) * intensity));
            lights->l.colc[1] = c;
            lights->l.col[1] = c;

            c = (u32)((f32)(u32)lights->l.col[2] + ((f32)(cmd->unkD - lights->l.col[2]) * intensity));
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

    if ((f64)intensity > 0.02) {
        c = (u32)((f32)(u32)cmd->unkB * intensity);
        slot_light->l.colc[0] = c;
        slot_light->l.col[0] = c;

        c = (u32)((f32)(u32)cmd->unkC * intensity);
        slot_light->l.colc[1] = c;
        slot_light->l.col[1] = c;

        c = (u32)((f32)(u32)cmd->unkD * intensity);
        slot_light->l.colc[2] = c;
        slot_light->l.col[2] = c;

        slot_light->l.dir[0] = (s8)(s32)(((f32)cmd->unk4 - actorX) * (127.0f / dist));
        slot_light->l.dir[1] = (s8)(s32)(((f32)cmd->unk6 - actorY) * (127.0f / dist));
        slot_light->l.dir[2] = (s8)(s32)(((f32)cmd->unk8 - actorZ) * (127.0f / dist));
        return 1;
    }

    return 0;
}

void commandQueueReset(void) {
    D_807FDB74 = 0;
    D_807FDB75 = 0;
}

typedef struct {
    u8 pad0[0x5C];
    u16 unk5C;
    u8 pad5E[2];
    u32 unk60;
    u32 unk64;
    u8 pad68[0x7C - 0x68];
    f32 x;
    f32 y;
    f32 z;
    u8 pad88[0xCD - 0x88];
    u8 unkCD;
    u8 padCE[0x12C - 0xCE];
    s16 unk12C;
    u8 pad12E[0x16A - 0x12E];
    u8 unk16A;
    u8 unk16B;
    u8 unk16C;
    u8 unk16D;
    u8 pad16E[0x174 - 0x16E];
    void *unk174;
} LightActorView;

extern Actor *gPrimaryPlayerActor;
extern s32 gGlobalPauseFlags;
extern u32 gFrameCounter;
extern f32 *D_8076A0B4;
extern f32 *D_8076A0B8;
extern f32 *D_8076A0BC;
extern void *gPlayerSlots;
extern f32 D_807444CC;
extern f32 D_807444D0;
extern f32 D_807444D4;
extern f32 D_807444D8;
extern f32 D_807444DC;
extern f32 func_807444E0;

void actorGetNodePos(Actor *, s32, f32 *, f32 *, f32 *);
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
s32 commandApplyToLight(u8, Command *, f32, f32, f32, s16);

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
    LightActorView *actor;
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

    actor = (LightActorView *)targetActor;
    if (targetActor == gPrimaryPlayerActor) {
        is_player = 1;
    } else {
        is_player = 0;
    }
    command = 1;
    color_base = (u8 *)gGfxCurrentFrameBuffer;
    primary = &((Lights7 *)((u8 *)color_base + 0x270))[D_807FDB75].a;
    secondary = &((Lights7 *)((u8 *)color_base + 0x270))[D_807FDB75].l[0];

    if (actor->unkCD) {
        actorGetNodePos(targetActor, actor->unkCD, &x, &y, &z);
    } else {
        x = actor->x;
        y = actor->y;
        z = actor->z;
    }

    if (is_player) {
        dest_red = D_80755684;
        dest_green = D_8075568C;
        dest_blue = D_80755688;
        camera_rotation = D_80755680;
    } else {
        dest_red = (f32)D_807FDB7E;
        dest_green = (f32)D_807FDB7F;
        dest_blue = (f32)D_807FDB80;
        camera_rotation = 0;
    }

    sequence = actor->unk12C;
    if (sequence == -1) {
        sequence = 0;
    }

    if (actor->unk64 & 1) {
        scale = 1.0f;
    } else {
        scale = (f32)actor->unk16D / 15.0f;
    }

    if (actor->unk60 & 0x800000) {
        color[0] = (f32)((f64)actor->unk16A / 255.0);
        color[1] = (f32)((f64)actor->unk16B / 255.0);
        color[2] = (f32)((f64)actor->unk16C / 255.0);
    } else {
        color[0] = D_8076A0B4[sequence];
        color[1] = D_8076A0B8[sequence];
        color[2] = D_8076A0BC[sequence];
    }

    primary->l.col[0] = primary->l.colc[0] = (u8)(((D_807FDB7C != 0) ? (f64)(color[0] * scale) : 1.0) * (f64)(u8)D_807FDB60.unkB);
    primary->l.col[1] = primary->l.colc[1] = (u8)(((D_807FDB7C != 0) ? (f64)(color[1] * scale) : 1.0) * (f64)(u8)D_807FDB60.unkC);
    primary->l.col[2] = primary->l.colc[2] = (u8)(((D_807FDB7C != 0) ? (f64)(color[2] * scale) : 1.0) * (f64)(u8)D_807FDB60.unkD);

    secondary->l.col[0] = (u8)(s32)(((D_807FDB7D != 0) ? (f64)(color[0] * scale) : 1.0) * (f64)dest_red);
    secondary->l.col[1] = (u8)(s32)(((D_807FDB7D != 0) ? (f64)(color[1] * scale) : 1.0) * (f64)dest_green);
    secondary->l.col[2] = (u8)(s32)(((D_807FDB7D != 0) ? (f64)(color[2] * scale) : 1.0) * (f64)dest_blue);
    secondary->l.colc[0] = secondary->l.col[0];
    secondary->l.colc[1] = secondary->l.col[1];
    secondary->l.colc[2] = secondary->l.col[2];

    angle = mathAngleBetweenPoints2D(x, z, *(f32 *)((u8 *)gPlayerSlots + (playerSlotIndex * 0x2F0) + 0x21C), *(f32 *)((u8 *)gPlayerSlots + (playerSlotIndex * 0x2F0) + 0x224)) + D_807FDB76;
    dx = (*(f32 *)((u8 *)gPlayerSlots + (playerSlotIndex * 0x2F0) + 0x21C) - (mathSinF(angle) * (f32)D_807FDB78)) - x;
    dy = (f32)(camera_rotation + D_807FDB7A);
    dz = (*(f32 *)((u8 *)gPlayerSlots + (playerSlotIndex * 0x2F0) + 0x224) - (mathCosF(angle) * (f32)D_807FDB78)) - z;
    inv_distance = 127.0f / sqrtf((dx * dx) + (dy * dy) + (dz * dz));
    secondary->l.dir[0] = (s8)(s32)(dx * inv_distance);
    secondary->l.dir[1] = (s8)(s32)(dy * inv_distance);
    secondary->l.dir[2] = (s8)(s32)(dz * inv_distance);

    if (is_player) {
        D_807444CC = (f32)secondary->l.dir[0];
        D_807444D0 = (f32)secondary->l.dir[1];
        D_807444D4 = (f32)secondary->l.dir[2];
        D_807444D8 = 10.0f;
        D_807444DC = -10.0f;
        func_807444E0 = 10.0f;
        D_80755680 = (s16)(s32)((f64)D_80755680 + ((f64)-D_80755680 * 0.05));
        D_80755684 = (f32)((f64)D_80755684 + ((f64)((f32)D_807FDB7E - D_80755684) * 0.05));
        D_80755688 = (f32)((f64)D_80755688 + ((f64)((f32)D_807FDB7F - D_80755688) * 0.05));
        D_8075568C = (f32)((f64)D_8075568C + ((f64)((f32)D_807FDB80 - D_8075568C) * 0.05));
    }

    for (i = 0; i < D_807FDB74; i++) {
        if (((Command *)D_807FDB70)[i].unk0 == (s32)targetActor && commandApplyToLight(command, (Command *)(D_807FDB70 + (i << 4)), x, y, z, playerSlotIndex) != 0) {
            command++;
        }
    }

    if (!(gGlobalPauseFlags & 2) && (actor->unk5C & 1)) {
        FakesLightHitState *hit = actor->unk174;
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
        Gfx *dl = glist++;
        dl->words.w0 = (0xDC080000 | ((((i * 0x18 + 0x30) / 8) & 0xFF) << 8)) | 0xA;
        dl->words.w1 = (u32)&((Lights7 *)((u8 *)color_base + 0x270))[D_807FDB75].l[i];
    }
    {
        Gfx *gdl1 = glist++;
        Gfx *gdl2;
        Gfx *gdl3;
        gdl1->words.w0 = (0xDC080000 | ((((command * 0x18 + 0x30) / 8) & 0xFF) << 8)) | 0xA;
        gdl2 = glist++;
        gdl1->words.w1 = (u32)&((Lights7 *)((u8 *)color_base + 0x270))[D_807FDB75].a;
        gdl2->words.w1 = command * 0x18;
        gdl2->words.w0 = 0xDB020000;
        gdl3 = glist++;
        gdl3->words.w1 = 0;
        gdl3->words.w0 = 0xE7000000;
    }

    D_807FDB75++;
    if (D_807FDB75 >= 0x18) {
        D_807FDB75--;
    }
    return glist;
}



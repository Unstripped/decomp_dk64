#include "common.h"
#include "actor.h"

extern s32 D_8076A048;
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

void *func_80610FE8(s32);
f32 func_80612790(s16);
f32 func_80612794(s16);

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

void commandSetParameters(s16 arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4, u8 arg5) {
    D_807FDB76 = arg0;
    D_807FDB78 = arg1;
    D_807FDB7A = arg2;
    D_807FDB7E = arg3;
    D_807FDB7F = arg4;
    D_807FDB80 = arg5;
}

void commandSetColor(s8 arg0, s8 arg1, s8 arg2) {
    D_807FDB60.unkB = arg0;
    D_807FDB60.unkC = arg1;
    D_807FDB60.unkD = arg2;
}

void commandSetFlags(s8 arg0, s8 arg1) {
    D_807FDB7C = arg0;
    D_807FDB7D = arg1;
}

void commandStateInit(void) {
    D_807FDB60.unk8 = 0;
    D_807FDB60.unkB = 0x6B;
    D_807FDB60.unkC = 0x30;
    D_807FDB60.unkD = 0x50;
    D_807FDB60.unkE = 7;
    D_807FDB60.unk6 = D_807FDB60.unk8;
    D_807FDB60.unk4 = D_807FDB60.unk8;
    D_807FDB70 = (s32) func_80610FE8(0x200);
    commandSetParameters(0x320, 0x82, 0, 0xFF, 0xFF, 0xFF);
    commandSetFlags(1, 1);
}

extern s16 D_80755680;
extern f32 D_80755684;
extern f32 D_80755688;
extern f32 D_8075568C;

void func_8072167C(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    D_80755680 = (s16) (s32) ((f64) D_80755680 + ((f64) (arg3 - D_80755680) * 0.1));
    D_80755684 = (f32) ((f64) D_80755684 + ((f64) ((f32) arg0 - D_80755684) * 0.1));
    D_80755688 = (f32) ((f64) D_80755688 + ((f64) ((f32) arg1 - D_80755688) * 0.1));
    D_8075568C = (f32) ((f64) D_8075568C + ((f64) ((f32) arg2 - D_8075568C) * 0.1));
}

void commandQueuePush(s32 arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8) {
    s32 var_v0;
    s32 temp_t3;
    Command *temp_v1;

    var_v0 = D_807FDB74;
    if (var_v0 >= 0x20) {
        temp_t3 = var_v0 - 1;
        D_807FDB74 = temp_t3 & 0xFFFF;
        var_v0 = temp_t3 & 0xFF;
    }
    temp_v1 = (Command *)(D_807FDB70 + var_v0 * 0x10);
    D_807FDB74 = var_v0 + 1;
    temp_v1->unk0 = arg0;
    temp_v1->unk4 = arg1;
    temp_v1->unk6 = arg2;
    temp_v1->unk8 = arg3;
    temp_v1->unkA = arg4;
    temp_v1->unkB = arg5;
    temp_v1->unkC = arg6;
    temp_v1->unkD = arg7;
    temp_v1->unkE = arg8;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/126260/func_80721814.s")

void commandQueueReset(void) {
    D_807FDB74 = 0;
    D_807FDB75 = 0;
}

#ifdef NON_MATCHING
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
} L126b_ActorView;

extern Actor *D_807FBB4C;
extern s32 D_807FBB60;
extern u32 D_8076A064;
extern f32 *D_8076A0B4;
extern f32 *D_8076A0B8;
extern f32 *D_8076A0BC;
extern void *D_807FC924;
extern f32 D_807444CC;
extern f32 D_807444D0;
extern f32 D_807444D4;
extern f32 D_807444D8;
extern f32 D_807444DC;
extern f32 func_807444E0;

void actorGetNodePos(Actor *, s32, f32 *, f32 *, f32 *);
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
s32 func_80721814(s32, Command *, f32, f32, f32, s16);

Gfx *func_80722294(Gfx *arg0, Actor *arg1, s16 arg2) {
    u8 is_player;
    s32 color_base;
    Ambient *primary;
    Light *secondary;
    L126b_ActorView *actor;
    s32 command;
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

    actor = (L126b_ActorView *)arg1;
    if (arg1 == D_807FBB4C) {
        is_player = 1;
    } else {
        is_player = 0;
    }
    command = 1;
    color_base = D_8076A048;
    primary = &((Lights7 *)((u8 *)color_base + 0x270))[D_807FDB75].a;
    secondary = &((Lights7 *)((u8 *)color_base + 0x270))[D_807FDB75].l[0];

    if (actor->unkCD != 0) {
        actorGetNodePos(arg1, actor->unkCD, &x, &y, &z);
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
        camera_rotation = 0;
        dest_red = (f32)D_807FDB7E;
        dest_green = (f32)D_807FDB7F;
        dest_blue = (f32)D_807FDB80;
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
    secondary->l.col[2] = secondary->l.colc[2] = (u8)(s32)(((D_807FDB7D != 0) ? (f64)(color[2] * scale) : 1.0) * (f64)dest_blue);
    secondary->l.colc[0] = secondary->l.col[0];
    secondary->l.colc[1] = secondary->l.col[1];

    angle = mathAngleBetweenPoints2D(x, z, *(f32 *)((u8 *)D_807FC924 + (arg2 * 0x2F0) + 0x21C), *(f32 *)((u8 *)D_807FC924 + (arg2 * 0x2F0) + 0x224)) + D_807FDB76;
    dx = (*(f32 *)((u8 *)D_807FC924 + (arg2 * 0x2F0) + 0x21C) - (func_80612794(angle) * (f32)D_807FDB78)) - x;
    dy = (f32)(camera_rotation + D_807FDB7A);
    dz = (*(f32 *)((u8 *)D_807FC924 + (arg2 * 0x2F0) + 0x224) - (func_80612790(angle) * (f32)D_807FDB78)) - z;
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
        if (((Command *)D_807FDB70)[i].unk0 == (s32)arg1 && func_80721814(command & 0xFF, &((Command *)D_807FDB70)[i], x, y, z, arg2) != 0) {
            command = (command + 1) & 0xFF;
        }
    }

    if (!(D_807FBB60 & 2) && (actor->unk5C & 1) && (*(s16 *)((u8 *)actor->unk174 + 0xD4) != 0) && (D_8076A064 & 2)) {
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

    for (i = 0; i < command; i++) {
        Gfx *dl = arg0++;
        dl->words.w0 = 0xDC08000A | ((((i * 0x18 + 0x30) / 8) & 0xFF) << 8);
        dl->words.w1 = (u32)&((Lights7 *)((u8 *)color_base + 0x270))[D_807FDB75].l[i];
    }
    {
        Gfx *gdl1 = arg0++;
        Gfx *gdl2 = arg0++;
        gdl1->words.w0 = 0xDC08000A | ((((command * 0x18 + 0x30) / 8) & 0xFF) << 8);
        gdl1->words.w1 = (u32)&((Lights7 *)((u8 *)color_base + 0x270))[D_807FDB75].a;
        gdl2->words.w1 = command * 0x18;
        gdl2->words.w0 = 0xDB020000;
        arg0->words.w1 = 0;
        arg0->words.w0 = 0xE7000000;
    }

    D_807FDB75++;
    if (D_807FDB75 >= 0x18) {
        D_807FDB75--;
    }
    return arg0 + 1;
}

#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/126260/func_80722294.s")
#endif

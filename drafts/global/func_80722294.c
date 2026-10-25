// func_80722294 (src/global/126260.c): stage 1 compiled behavioural reconstruction; frame 0xB8 and $s0-$s4 target set not reached; corrected independent input RGB and target RGB paths; NON_MATCHING-side candidate compiles; plain fdiff TEXT OK
// Stage 1 compiled behavioural reconstruction; private source carries the full candidate.
typedef struct { u32 w0; u32 w1; } L2DisplayCommand;
extern Actor *D_807FBB4C;
extern s32 D_807FBB60;
extern u32 D_8076A064;
extern f32 *D_8076A0B4;
extern f32 *D_8076A0B8;
extern f32 *D_8076A0BC;
extern u8 *D_807FC924;
extern f32 D_807444CC;
extern f32 D_807444D0;
extern f32 D_807444D4;
extern f32 D_807444D8;
extern f32 D_807444DC;
extern f32 func_807444E0;
extern s16 D_80755680;
extern f32 D_80755684;
extern f32 D_80755688;
extern f32 D_8075568C;
void actorGetNodePos();
s16 mathAngleBetweenPoints2D();
s32 func_80721814();

L2DisplayCommand *func_80722294(L2DisplayCommand *arg0, Actor *arg1, s16 arg2) {
    L2DisplayCommand *primary;
    L2DisplayCommand *secondary;
    L2DisplayCommand *cmd;
    u8 *color_base;
    u8 *player;
    f32 x;
    f32 y;
    f32 z;
    f32 scale;
    f32 dest_red;
    f32 dest_green;
    f32 dest_blue;
    f32 red;
    f32 green;
    f32 blue;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 inv_distance;
    s16 rotation;
    s16 camera_rotation;
    s16 command;
    s16 i;
    u8 sequence;
    u8 is_player;

    player = (u8 *)arg1;
    is_player = arg1 == D_807FBB4C;
    command = 1;
    color_base = (u8 *)D_8076A048 + (D_807FDB75 * 0x78);
    primary = (L2DisplayCommand *)(color_base + 0x270);
    secondary = (L2DisplayCommand *)(color_base + 0x278);
    if (player[0xCD] != 0) {
        actorGetNodePos(arg1, player[0xCD], &x, &y, &z);
    } else {
        x = *(f32 *)(player + 0x7C);
        y = *(f32 *)(player + 0x80);
        z = *(f32 *)(player + 0x84);
    }
    if (is_player) {
        camera_rotation = D_80755680;
        dest_red = D_80755684;
        dest_green = D_8075568C;
        dest_blue = D_80755688;
    } else {
        camera_rotation = 0;
        dest_red = D_807FDB7E;
        dest_green = D_807FDB7F;
        dest_blue = D_807FDB80;
    }
    if (*(s16 *)(player + 0x12C) == -1) {
        sequence = 0;
    } else {
        sequence = *(s16 *)(player + 0x12C);
    }
    if (*(u32 *)(player + 0x64) & 1) {
        scale = 1.0f;
    } else {
        scale = player[0x16D] / 15.0f;
    }
    if (*(u32 *)(player + 0x60) & 0x800000) {
        red = player[0x16A] / 255.0;
        green = player[0x16B] / 255.0;
        blue = player[0x16C] / 255.0;
    } else {
        red = D_8076A0B4[sequence];
        green = D_8076A0B8[sequence];
        blue = D_8076A0BC[sequence];
    }
    primary->w0 = (u8)(((D_807FDB7C != 0) ? red * scale : 1.0) * D_807FDB60.unkB);
    primary->w0 |= (u32)(u8)(((D_807FDB7C != 0) ? green * scale : 1.0) * D_807FDB60.unkC) << 8;
    primary->w0 |= (u32)(u8)(((D_807FDB7C != 0) ? blue * scale : 1.0) * D_807FDB60.unkD) << 16;
    primary->w1 = primary->w0;
    secondary->w0 = (u8)(((D_807FDB7D != 0) ? red * scale : 1.0) * dest_red);
    secondary->w0 |= (u32)(u8)(((D_807FDB7D != 0) ? green * scale : 1.0) * dest_green) << 8;
    secondary->w0 |= (u32)(u8)(((D_807FDB7D != 0) ? blue * scale : 1.0) * dest_blue) << 16;
    secondary->w1 = secondary->w0;
    rotation = mathAngleBetweenPoints2D(x, z, &D_807FDB60, camera_rotation,
                                        *(f32 *)(D_807FC924 + arg2 * 0x2F0 + 0x21C),
                                        *(f32 *)(D_807FC924 + arg2 * 0x2F0 + 0x224));
    dx = *(f32 *)(D_807FC924 + arg2 * 0x2F0 + 0x21C) - func_80612794(rotation + D_807FDB76) * D_807FDB78 - x;
    dy = camera_rotation + D_807FDB7A;
    dz = *(f32 *)(D_807FC924 + arg2 * 0x2F0 + 0x224) - func_80612790(rotation + D_807FDB76) * D_807FDB78 - z;
    inv_distance = 127.0f / sqrtf(dx * dx + dy * dy + dz * dz);
    ((u8 *)secondary)[8] = (s8)(dx * inv_distance);
    ((u8 *)secondary)[9] = (s8)(dy * inv_distance);
    ((u8 *)secondary)[10] = (s8)(dz * inv_distance);
    if (is_player) {
        D_807444CC = (s8)((u8 *)secondary)[8];
        D_807444D0 = (s8)((u8 *)secondary)[9];
        D_807444D4 = (s8)((u8 *)secondary)[10];
        D_807444D8 = 10.0f;
        D_807444DC = -10.0f;
        func_807444E0 = 10.0f;
        D_80755680 = (s16)(D_80755680 + (-D_80755680 * 0.05));
        D_80755684 += (dest_red - D_80755684) * 0.05;
        D_80755688 += (dest_green - D_80755688) * 0.05;
        D_8075568C += (dest_blue - D_8075568C) * 0.05;
    }
    for (i = 0; i < D_807FDB74; i++) {
        cmd = (L2DisplayCommand *)D_807FDB70 + (i * 2);
        if ((Actor *)cmd->w0 == arg1 && func_80721814(command & 0xFF, cmd, x, y, z, arg2) != 0) {
            command = (command + 1) & 0xFF;
        }
    }
    if (!(D_807FBB60 & 2) && (*(u16 *)(player + 0x5C) & 1)
        && (*(s16 *)(*(u8 **)(player + 0x174) + 0xD4) != 0) && (D_8076A064 & 2)) {
        primary->w0 = primary->w1 = 0;
        secondary->w0 = secondary->w1 = 0;
    }
    for (i = 0; i < command; i++) {
        arg0->w0 = 0xDC08000A | ((((i * 0x18) + 0x30) / 8) & 0xFF) << 8;
        arg0->w1 = (u32)(color_base + 0x278 + i * 0x10);
        arg0++;
    }
    arg0->w0 = 0xDC08000A | ((((command * 0x18) + 0x30) / 8) & 0xFF) << 8;
    arg0->w1 = (u32)(color_base + 0x270);
    arg0[1].w0 = 0xDB020000;
    arg0[1].w1 = command * 0x18;
    arg0[2].w0 = 0xE7000000;
    arg0[2].w1 = 0;
    D_807FDB75++;
    if (D_807FDB75 >= 0x18) {
        D_807FDB75--;
    }
    return arg0 + 3;
}

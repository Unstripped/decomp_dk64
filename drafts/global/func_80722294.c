// func_80722294 (src/global/126260.c): stage 5; frame 0xB8 reached, exact 6304 bytes; $s0-$s4 callee-saved set matched ($s0=i, $s1=arg0, $s2=command, $s3=arg1, $s4=secondary); color[3] array home at 0x60-0x68 matches; secondary Lights7 indexed array matches; remaining diff regalloc s1/s2 swap and 4-byte stack offset shift
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

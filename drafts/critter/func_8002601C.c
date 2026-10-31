// func_8002601C (src/critter/0.c): stage 5 park: struct conversion, dx reuse in first block matches a1-a3; left: f14/f16/f12 register swap in first and second block, t3/t9 swap in int ring
typedef struct CritterZoneShape {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s32 unkC;
    s32 unk10;
} CritterZoneShape;

typedef struct CritterZone {
    s16 x;
    s16 y;
    s16 z;
    s16 unk6;
    CritterZoneShape shape;
    u8 flags;
    u8 pad1D[3];
    f32 distSq;
    u8 frame;
    u8 near;
    u8 alpha;
    u8 pad27;
    s16 unk28;
    u8 pad2A[2];
} CritterZone;

typedef struct CritterObj {
    s16 yaw;
    s16 pitch;
    s16 prevYaw;
    u8 pad6[2];
    f32 x;
    f32 y;
    f32 z;
    f32 yBob;
    f32 offX;
    f32 offY;
    f32 offZ;
    f32 turnRate;
    f32 speed;
    u8 pad2C[4];
    f32 accel;
    f32 targetSpeed;
    f32 scale;
    f32 distSq;
    u8 frame;
    u8 pad41;
    s16 anim;
    s16 prevAnim;
    u8 pad46[2];
    f32 flapA;
    f32 flapB;
    u8 zoneIdx;
    u8 pad51[3];
    CritterZone *zone;
    CritterZone *homeZone;
    u8 pad5C[4];
    Mtx mtx[3][2];
    u8 state;
    u8 flags;
    u8 role;
    u8 pad1E3;
    u16 texId[2];
    s32 tex[2];
} CritterObj;

typedef struct CritterViewer {
    u8 pad0[0x88];
    Mtx projection[2];
    u8 pad108[0x210 - 0x108];
    f32 x;
    f32 y;
    f32 z;
    u8 pad21C[0x2F0 - 0x21C];
} CritterViewer;

typedef struct CritterPlayer {
    u8 pad0[0x7C];
    f32 x;
    f32 y;
    f32 z;
} CritterPlayer;

extern u8 D_807444FC;
extern CritterViewer *D_807FC924;
extern u8 D_807FC929;
extern CritterPlayer *D_807FBB48;
extern CritterZone *critterPlayerZone;

void func_8002601C(CritterObj *obj) {
    CritterViewer *m;
    f32 lim;
    f32 fv0;
    f32 dx;
    f32 dz;
    f32 dist;
    f32 ddy;
    s16 half;
    s32 f;

    fv0 = 0.0f;
    lim = (f32)(obj->homeZone->shape.unk10 + 0x1DE84);
    if (obj->homeZone->frame != D_807444FC) {
        half = (obj->homeZone->shape.unk4 + obj->homeZone->shape.unk8) >> 1;
        dx = (f32)obj->homeZone->x - D_807FBB48->x;
        dz = (f32)obj->homeZone->z - D_807FBB48->z;
        dx = dx * dx + dz * dz;
        fv0 = 0.0f;
        f = critterPlayerZone->y < obj->homeZone->y + half;
        if (f) {
            f = obj->homeZone->y - half < critterPlayerZone->y;
        }
        f = (u8)f != 0;
        if (f) {
            f = 0;
            if (dx < (f32)obj->homeZone->shape.unk10) {
                f = 1;
            }
        }
        obj->homeZone->near = f;
        obj->homeZone->frame = D_807444FC;
        m = &D_807FC924[D_807FC929];
        dz = (f32)obj->homeZone->z - m->z;
        dx = (f32)obj->homeZone->x - m->x;
        ddy = (f32)obj->homeZone->y - m->y;
        dist = dz * dz + (dx * dx + ddy * ddy);
        obj->homeZone->distSq = dist;
        if (dist < lim) {
            fv0 = (lim - dist) * 0.000051020408f;
            if (fv0 > 1.0f) {
                fv0 = 1.0f;
            }
        }
        obj->homeZone->alpha = (u32)(255.0f * fv0);
    }
    if (obj->homeZone->distSq < lim) {
        obj->flags |= 1;
    } else {
        obj->flags &= ~1;
    }
}

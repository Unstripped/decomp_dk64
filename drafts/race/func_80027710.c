// func_80027710 (src/race/36B0.c): stage 5: frame 0x78 and all stack slots match; remaining diff = FP regalloc in the e2 group: expected cur.z in f14 (mine f12), y2 diff (cur.y-out.y) spilled to 60(sp) while mine keeps it in f16; seems f12 is excluded from the candidate FP pool in the target. Tried named ey (frame +8), decl order, RB_SQ operand orders; permuter 2x7min no gain
extern s32 *D_807F5FD4;
s32 raceGetNextWaypointIndex(s32, s32);

typedef struct {
    f32 x, y, z;
} Point3f;

typedef struct {
    u8 unk0;
    u8 unk1;
    u16 unk2;
} Waypoint;

void mathPickCloserTargetPoint3D(f32, f32, f32, Point3f *, Point3f *, Point3f *, Point3f *, f32 *, f32 *, f32 *);

#define RB_SQ(v) ((v) * (v))
f32 func_80027710(s32 arg0, s32 arg1, void *arg2) {
    s32 idx1;
    s32 idx2;
    Point3f *base;
    Point3f *cur;
    Point3f *p1;
    Point3f *p2;
    Point3f out;
    f32 d2;
    f32 e2;

    idx1 = raceGetNextWaypointIndex(arg0, ((Waypoint *)arg2)->unk2);
    idx2 = raceGetNextWaypointIndex(arg0, idx1);
    base = (Point3f *)D_807F5FD4[((Waypoint *)arg2)->unk0];
    p1 = &base[idx1];
    p2 = &base[idx2];
    cur = &base[((Waypoint *)arg2)->unk2];
    mathPickCloserTargetPoint3D(*(f32 *)(arg1 + 0x7C), *(f32 *)(arg1 + 0x80), *(f32 *)(arg1 + 0x84), cur, p1, p1, p2, &out.x, &out.y, &out.z);
    d2 = RB_SQ(cur->x - p1->x) + RB_SQ(cur->y - p1->y) + RB_SQ(cur->z - p1->z);
    e2 = RB_SQ(cur->z - out.z) + (RB_SQ(cur->y - out.y) + RB_SQ(cur->x - out.x));
    return sqrtf(e2 / d2);
}

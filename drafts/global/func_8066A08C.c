// func_8066A08C (src/global/6AD90.c): R2Fp2 stage 5 (unchanged C, 319 target vs 329 ours insns, whole-file diff 143 rows): ours has 4 extra ldc1+lui (2000.0 reloaded at each use; target keeps it in callee-saved f26 from the first ny*2000.0 compare to the end), +1 lw +1 lwc1, bc1fl vs bc1f; d in f18 (target f0), first FP ring temp f6 (999999.0f) vs target f4 (one extra hidden FP touch in ours / f16,f18 used as webs). Tried this round: inline nz (all 8 masks), 4300 decl-order moves, greedy single dead-statement sweeps (27 syms x all positions), new dead-local sweeps (f32/f64/s32): none improves. Target nz=f22, nx f30, ny f20, dx02/dy02 temps f24/f26 reused later, arg2 reloaded lwc1 f28.
typedef struct {
    u8 pad0[0x24];
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    f32 unk40;
    f32 unk44;
    u8 pad48[0x56 - 0x48];
    u8 unk56;
} CollisionBoxTriView;

struct CollisionBoxTriangle;
s32 collisionCheckBoxTriangleBoundsXZ(struct CollisionBoxTriangle *, f32, f32);
u8 func_8066A988(struct CollisionBoxTriangle *, f32, f32);
void collisionTransformPointToActorLocal(s32, Actor *, CollisionVertexBoneRefs *, f32, f32, f32);
void collisionRecordBoxTriangle(void *, f32);

extern s8 D_807F94AD;

s32 func_8066A08C(Actor *arg0, f32 arg1, f32 arg2, f32 arg3, f32 *arg4) {
    f32 pad;
    CollisionBoxTriView *hit_tri;
    f64 nx, ny, nz;
    f64 d;
    f64 dx01, dy01, dz01, dx02, dy02, dz02;
    f32 y;
    s32 hit;
    s32 i;
    s32 j;
    Actor *actor;
    CollisionBoxTriView *tri;
    u16 actor_count;
    f32 pad108[3];
    f32 hit_y;
    f32 padAC[4];
    Actor *hit_actor;
    f32 pad98[2];

    hit = 0;
    hit_y = 999999.0f;
    (void)2000.0; // FAKE: keeps the first 2000.0 rodata literal slot
    actor_count = gActiveActorCount;
    i = 0;
    if ((s32)actor_count > 0) {
        do {
            actor = gActiveActors[i].actor;
            if (!(actor->unk60 & 0x2000)) {
                if (actor->unk140 != NULL && arg0 != actor && (actor->unk60 & 0x10)) {
                    tri = actor->unk140->unk98;
                    j = 0;
                    if (actor->unk140->unk94 > 0) {
                        do {
                            if ((collisionCheckBoxTriangleBoundsXZ((struct CollisionBoxTriangle *)tri, arg1, arg2) != 0) &&
                                (func_8066A988((struct CollisionBoxTriangle *)tri, arg1, arg2) != 0) &&
                                (tri->unk56 != 0)) {
                                dx01 = (f64)(tri->unk24 - tri->unk28);
                                dy01 = (f64)(tri->unk30 - tri->unk34);
                                dz01 = (f64)(tri->unk3C - tri->unk40);
                                dx02 = (f64)(tri->unk24 - tri->unk2C);
                                dy02 = (f64)(tri->unk30 - tri->unk38);
                                dz02 = (f64)(tri->unk3C - tri->unk44);
                                nx = (dy01 * dz02) - (dz01 * dy02);
                                ny = (dz01 * dx02) - (dx01 * dz02);
                                nz = (dx01 * dy02) - (dy01 * dx02);
                                d = -((nx * (f64)tri->unk28) + (ny * (f64)tri->unk34) + (nz * (f64)tri->unk40));
                                if (0.01 < ny * 2000.0 || ny * 2000.0 < -0.01) {
                                    if (arg0 != NULL) {
                                        if (D_807F94BC == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                                        func_80666D88(arg3, (f32)((2000.0 * (0.0 - ((((f64)arg1 * nx) + (ny * -1000.0) + (nz * (f64)arg2) + d) / (ny * 2000.0)))) - 1000.0), 0, arg0, 0);
                                    }
                                    if (arg2) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                                    if (D_807F94BC != 0) {
                                        collisionRecordBoxTriangle(tri, (f32)((2000.0 * (0.0 - ((((f64)arg1 * nx) + (ny * -1000.0) + (nz * (f64)arg2) + d) / (ny * 2000.0)))) - 1000.0));
                                    }
                                    if (collisionCheckBoxTriangleWinding(tri) != 0) {
                                        y = (f32)((2000.0 * (0.0 - ((((f64)arg1 * nx) + (ny * -1000.0) + (nz * (f64)arg2) + d) / (ny * 2000.0)))) - 1000.0);
                                        if (mathCheckCloserFloatThreshold(hit_y, y, (f32)((f64)arg3 + 4.0), 0) != 0) {
                                            hit_tri = tri;
                                            hit_actor = actor;
                                            hit = 1;
                                            hit_y = y;
                                        }
                                    }
                                }
                            }
                            j++;
                            tri++;
                        } while (j < actor->unk140->unk94);
                    }
                }
            }
            i++;
        } while (i < (s32)gActiveActorCount);
    }

    if (hit != 0 && mathCheckCloserFloatThreshold(*arg4, hit_y, (f32)((f64)arg3 + 4.0), 0) != 0) {
        *arg4 = hit_y;
        collisionStoreBoxTriangleNormalAngles(arg0, hit_tri, 1);
        if (hit_actor->unk68 & 8) {
            D_807F94AD = 1;
        }
        if (arg0 != NULL) {
            collisionTransformPointToActorLocal((s32)arg0, hit_actor, (CollisionVertexBoneRefs *)hit_tri, arg1, hit_y, arg2);
            if (D_807F94BC) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        }
    }
    return hit;
}

// collisionTestActorBoxFloor (src/global/6AD90.c): MidA r6: stage 5 (parked in .scratch/MidA/6AD90.c), count EXACT 318, frame 0x130, shape 0, deadsweep full=32 (was 149): only FP ring/colour diffs (hit_y init f0 vs f4, x1 ring f10 vs f6 cascading ring renames, d f2 vs f0). Levers: natural statement order dx01,dy01,dz01,dx02,dy02,dz02; nx=(dy01*dz02)-(dz01*dy02); d declared after nx,ny,nz (home 264); f64 val = 0.0 - (num/(ny*2000.0)) per arm (mul.d 2000.0*val order; frame word -> pad108[1]); one dead test if (hit_y) {} after actor_count (colours the 999999 const, FAKE). Count-weighted hill-climb (full+10*|insns-318|+30*frame) of dead tests got 149->~75, then natural order closed the count. Without the hit_y test: shape 0 but ring +1 (text 98).
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
} CollisionBoxTriangleView;

struct CollisionBoxTriangle;
s32 collisionCheckBoxTriangleBoundsXZ(struct CollisionBoxTriangle *, f32, f32);
u8 collisionCheckBoxTriangleContainsPointXZ(struct CollisionBoxTriangle *, f32, f32);
void collisionTransformPointToActorLocal(s32, Actor *, CollisionVertexBoneRefs *, f32, f32, f32);
void collisionRecordBoxTriangle(void *, f32);


s32 collisionTestActorBoxFloor(Actor *arg0, f32 arg1, f32 arg2, f32 arg3, f32 *arg4) {
    f32 pad;
    CollisionBoxTriangleView *hit_tri;
    f64 nx, ny, nz;
    f64 d;
    f64 val;
    f64 dx01, dy01, dz01, dx02, dy02, dz02;
    f32 y;
    s32 hit;
    s32 i;
    s32 j;
    Actor *actor;
    CollisionBoxTriangleView *tri;
    u16 actor_count;
    f32 pad108[1];
    f32 hit_y;
    f32 padAC[4];
    Actor *hit_actor;
    f32 pad98[2];

    hit = 0;
    hit_y = 999999.0f;
    actor_count = gActiveActorCount;
    if (hit_y) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
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
                                (collisionCheckBoxTriangleContainsPointXZ((struct CollisionBoxTriangle *)tri, arg1, arg2) != 0) &&
                                (tri->unk56 != 0)) {
                                dx01 = (f64)(tri->unk24 - tri->unk28);
                                dy01 = (f64)(tri->unk30 - tri->unk34);
                                dz01 = tri->unk3C - tri->unk40;
                                dx02 = tri->unk24 - tri->unk2C;
                                dy02 = tri->unk30 - tri->unk38;
                                dz02 = tri->unk3C - tri->unk44;
                                nx = (dy01 * dz02) - (dz01 * dy02);
                                ny = (dz01 * dx02) - (dx01 * dz02);
                                nz = (dx01 * dy02) - (dy01 * dx02);
                                d = -(nx * (f64)tri->unk28 + ny * (f64)tri->unk34 + nz * (f64)tri->unk40);
                                if (0.01 < ny * 2000.0 || ny * 2000.0 < -0.01) {
                                    if (arg0 != NULL) {
                                        val = (0.0 - ((((f64)arg1 * nx) + (ny * -1000.0) + (nz * (f64)arg2) + d) / (ny * 2000.0)));  // FAKE: temp var fixes mul.d operand order (2000.0 * val)
                                        func_80666D88(arg3, (f32)((2000.0 * val) - 1000.0), 0, arg0, 0);
                                    }
                                    if (D_807F94BC != 0) {
                                        val = (0.0 - ((((f64)arg1 * nx) + (ny * -1000.0) + (nz * (f64)arg2) + d) / (ny * 2000.0)));  // FAKE: temp var fixes mul.d operand order (2000.0 * val)
                                        collisionRecordBoxTriangle(tri, (f32)((2000.0 * val) - 1000.0));
                                    }
                                    if (collisionCheckBoxTriangleWinding(tri) != 0) {
                                        val = (0.0 - ((((f64)arg1 * nx) + (ny * -1000.0) + (nz * (f64)arg2) + d) / (ny * 2000.0)));  // FAKE: temp var fixes mul.d operand order (2000.0 * val)
                                        y = (f32)((2000.0 * val) - 1000.0);
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
        }
    }
    return hit;
}

// func_8066A08C (src/global/6AD90.c): 309 vs 318 insns (delta 9); exact 0x130 frame, exact 17 saved regs, prologue/epilogue/control flow match; rodata matched with (void)2000.0
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
} R4M_Triangle;

s32 func_8066A834(R4M_Triangle *, f32, f32);
s32 func_8066A988(R4M_Triangle *, f32, f32);
void func_80666D88(f32, f32, s32, s32, s32);
void func_8066A64C(s32, Actor *, R4M_Triangle *, f32, f32, f32);
void func_8066A584(void *, f32);
void func_8066ACA4();
s32 func_8066AC10(void *);
s32 func_80666FC8(f32, f32, f32, s32);

extern s8 D_807F94AD;
extern u8 D_807F94BC;
extern ActorEntry D_807FB930[];
extern u16 D_807FBB34;

s32 func_8066A08C(Actor *arg0, f32 arg1, f32 arg2, f32 arg3, f32 *arg4) {
    f32 pad;
    R4M_Triangle *hit_tri;
    f32 pad128[6];
    f64 sp108;
    f32 pad108[22];
    f32 hit_y;
    f32 padAC[4];
    Actor *hit_actor;
    f32 pad98[2];
    f32 sp8C;
    ActorEntry *entry;
    f32 sp84;
    f32 sp80;
    f32 sp78;
    f32 temp_fa1;
    f32 temp_fs1;
    f32 y;
    f32 temp_ft5;
    f64 temp_fa0;
    f64 ny;
    f64 nz;
    f64 temp_fs2;
    f64 temp_fs3;
    f64 nx;
    f64 temp_ft4;
    f64 temp_fv0;
    f64 temp_fv1;
    f64 d;
    s32 hit;
    s32 i;
    s32 j;
    Actor *actor;
    R4M_Triangle *tri;
    u16 actor_count;

    hit = 0;
    hit_y = 999999.0f;
    (void)2000.0;
    actor_count = D_807FBB34;
    i = 0;
    if ((s32)actor_count > 0) {
        entry = D_807FB930;
        do {
            actor = entry->actor;
            if (!(actor->unk60 & 0x2000)) {
                if (actor->unk140 != NULL && arg0 != actor && (actor->unk60 & 0x10)) {
                    tri = actor->unk140->unk98;
                    j = 0;
                    if (actor->unk140->unk94 > 0) {
                        do {
                            if ((func_8066A834(tri, arg1, arg2) != 0) &&
                                (func_8066A988(tri, arg1, arg2) != 0) &&
                                (tri->unk56 != 0) &&
                                ((temp_fa1 = tri->unk24,
                                  sp8C = tri->unk28,
                                  temp_ft5 = tri->unk30,
                                  sp84 = tri->unk34,
                                  temp_fa0 = (f64)(temp_fa1 - sp8C),
                                  temp_fs1 = tri->unk3C,
                                  sp80 = tri->unk40,
                                  temp_ft4 = (f64)(temp_ft5 - sp84),
                                  temp_fv0 = (f64)(temp_fs1 - sp80),
                                  temp_fs2 = (f64)(temp_fa1 - tri->unk2C),
                                  temp_fs3 = (f64)(temp_ft5 - tri->unk38),
                                  sp78 = sp8C,
                                  temp_fv1 = (f64)(temp_fs1 - tri->unk44),
                                  nx = (temp_ft4 * temp_fv1) - (temp_fv0 * temp_fs3),
                                  ny = (temp_fv0 * temp_fs2) - (temp_fa0 * temp_fv1),
                                  nz = (temp_fa0 * temp_fs3) - (temp_ft4 * temp_fs2),
                                  d = -(((f64)sp80 * nz) + ((nx * (f64)sp78) + (ny * (f64)sp84))),
                                  0.01 < ny * 2000.0) || ny * 2000.0 < -0.01)) {
                                    if (arg0 != NULL) {
                                        func_80666D88(arg3, (f32)((2000.0 * (0.0 - ((((f64)arg1 * nx) + (ny * -1000.0) + (nz * (f64)arg2) + d) / (ny * 2000.0)))) - 1000.0), 0, (s32)arg0, 0);
                                    }
                                    if (D_807F94BC != 0) {
                                        func_8066A584(tri, (f32)((2000.0 * (0.0 - ((((f64)arg1 * nx) + (ny * -1000.0) + (nz * (f64)arg2) + d) / (ny * 2000.0)))) - 1000.0));
                                    }
                                    if (func_8066AC10(tri) != 0) {
                                        y = (f32)((2000.0 * (0.0 - ((((f64)arg1 * nx) + (ny * -1000.0) + (nz * (f64)arg2) + d) / (ny * 2000.0)))) - 1000.0);
                                        if (func_80666FC8(hit_y, y, (f32)((f64)arg3 + 4.0), 0) != 0) {
                                            hit_tri = tri;
                                            hit_actor = actor;
                                            hit = 1;
                                            hit_y = y;
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
            entry++;
        } while (i < (s32)D_807FBB34);
    }

    if (hit != 0 && func_80666FC8(*arg4, hit_y, (f32)((f64)arg3 + 4.0), 0) != 0) {
        *arg4 = hit_y;
        func_8066ACA4(arg0, hit_tri, 1);
        if (hit_actor->unk68 & 8) {
            D_807F94AD = 1;
        }
        if (arg0 != NULL) {
            func_8066A64C((s32)arg0, hit_actor, hit_tri, arg1, hit_y, arg2);
        }
    }
    return hit;
}

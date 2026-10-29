// func_806679BC (src/global/6AD90.c): stage 5: frame 0x158, 5 callee fp regs equal, structure equal (726/729 insns incl. needing prototype changes); diff = h2 in f22 vs f24 (needs nx interfering), temps at 0x90/0x94 vs 0x98/0x9C, lbu s0 vs t5 post-loop, add.d h+map operand order, rodata addends; d f2 only via FAKE if(D_807F9484){} after h chain
/* NEEDS (outside this snippet): func_806679BC prototype 4th param Actor * and caller passes (Actor *)arg3;
   func_80668520 returns u8 (decl+def); func_806689F0 prototyped (s32, CollisionPlaneTriS *, u8) with ANSI def;
   padTop/padB/padC/padE are frame-layout pads; D_8076A0A8 extern s32. */
typedef struct L6679BCTri {
    s16 v[9];
    s16 unk12;
    u8 unk14;
    u8 unk15;
    u8 unk16;
    s8 unk17;
} L6679BCTri;

typedef struct L6679BCBuf {
    u32 unk0;
    u32 unk4;
    u32 pad[3];
} L6679BCBuf;

typedef struct L6679BCSub174 {
    u8 pad0[0x1F0];
    u32 unk1F0;
} L6679BCSub174;

struct CollisionBufferEntry;
struct CollisionTriS;
extern struct CollisionBufferEntry *D_807F9514;
extern u16 D_807F9450;
extern u16 D_807F9452;
extern u16 D_807F9454;
extern u16 D_807F9456;
extern s32 D_807F9518;
extern s32 D_8076A0A8;
extern u8 D_807F5FC0;
extern struct Col6AF83Sub174 *D_807F94B8;
extern u8 D_807F94AB;
extern u8 D_807F94AE;
extern u8 D_807F94AF;
extern u8 D_807F94B0;
extern u8 D_807F94B1;
extern u8 D_807F94B5;
extern u8 D_807F94B7;
extern u8 D_807F946E;
extern u8 D_807F9484;
extern f32 D_807F9488;
extern u8 D_807F94BC;
u8 func_80668520(f32 *, f32, f32, f32 *);
void dynamicBufferAllocateEntry(s32);
s32 collisionCheckTriangleXZBoundsS16();
s32 func_80668C30(s16 *, f32, f32);
f32 mapOffsetSlotGetValue(s8);
void collisionRecordTriangleS(struct CollisionTriS *, f32);
s32 collisionCheckTriangleWindingS16();
struct CollisionPlaneTriS;
void func_806689F0(s32, struct CollisionPlaneTriS *, u8);

u8 func_806679BC(f32 arg0, f32 arg1, f32 *arg2, Actor *arg3) {
    s32 padTop;
    L6679BCTri *sp150;
    L6679BCTri *sp14C;
    s32 cell;
    L6679BCTri *tri;
    f64 h;
    f64 h2;
    f64 nx;
    f64 ny;
    f64 nz;
    f64 d;
    f64 dx01, dy01, dz01, dx02, dy02, dz02;
    f64 val;
    f32 diff;
    f32 t;
    f32 spCC;
    u8 spCB;
    f32 spC4;
    s32 padB;
    u8 spBF;
    s32 padC[3];
    f32 cur;
    s32 sp9C;
    s32 sp98;
    s32 padE[2];

    spCB = 0;
    spCC = 999999.0f;
    cell = ((s32)arg1 / D_807F9452) * D_807F9454 + (s32)arg0 / D_807F9450;
    cur = *arg2;
    spC4 = (f32)((f64)*arg2 + 4.0);
    spC4 = spC4 * 6.0f;
    if (cell >= D_807F9518) {
        return 0;
    }
    if (D_807F9454 <= arg0 / D_807F9450 || arg0 < 0.0) {
        if (D_8076A0A8 == 0x57 && arg3 != NULL) {
            return func_80668520(&spCC, spC4, cur, arg2);
        }
        return 0;
    }
    if (D_807F9456 <= arg1 / D_807F9452 || arg1 < 0.0) {
        if (D_8076A0A8 == 0x57 && arg3 != NULL) {
            return func_80668520(&spCC, spC4, cur, arg2);
        }
        return 0;
    }
    dynamicBufferAllocateEntry(cell);
    arg0 = arg0 * 6.0f;
    arg1 = arg1 * 6.0f;
    if (arg3 != NULL && arg3->unk150 != 0 && collisionCheckTriangleXZBoundsS16(arg3->unk150, (s32)arg0, (s32)arg1) != 0 &&
        func_80668C30((s16 *)arg3->unk150, arg0, arg1) != 0 && D_807F5FC0 == 0) {
        tri = (L6679BCTri *)arg3->unk150;
        sp150 = tri + 1;
    } else {
        tri = (L6679BCTri *)((L6679BCBuf *)D_807F9514)[cell].unk0;
        sp150 = (L6679BCTri *)((L6679BCBuf *)D_807F9514)[cell].unk4;
    }
    if (tri != sp150) {
        sp9C = (s32)arg1;
        sp98 = (s32)arg0;
        do {
            if (collisionCheckTriangleXZBoundsS16(tri, sp98, sp9C) != 0 && func_80668C30((s16 *)tri, arg0, arg1) != 0) {
                dx01 = (f64)(tri->v[0] - tri->v[1]);
                dy01 = (f64)(tri->v[3] - tri->v[4]);
                dz01 = (f64)(tri->v[6] - tri->v[7]);
                dx02 = (f64)(tri->v[0] - tri->v[2]);
                dy02 = (f64)(tri->v[3] - tri->v[5]);
                dz02 = (f64)(tri->v[6] - tri->v[8]);
                nx = (dy01 * dz02) - (dz01 * dy02);
                ny = (dz01 * dx02) - (dx01 * dz02);
                d = -((nx * tri->v[1]) + (ny * tri->v[4]) + (((dx01 * dy02) - (dy01 * dx02)) * tri->v[7]));
                if (ny * 2000.0 > 0.01 || ny * 2000.0 < -0.01) {
                    h = (((arg0 * nx) + (ny * -1000.0)) + (((dx01 * dy02) - (dy01 * dx02)) * arg1) + d) / (ny * 2000.0);
                    h = 0.0 - h;
                    h = 2000.0 * h;
                    h = h - 1000.0;
                    if (D_807F9484) {}  // FAKE: sweep
                    h2 = h;
                    if (tri->unk12 & 4) {
                        h2 = h + (f64)(mapOffsetSlotGetValue(tri->unk17) * 6.0f);
                    }
                    if ((tri->unk12 & 0x4000) && arg3 != NULL && (arg3->unk5C & 1)) {
                        D_807F94B7 = 1;
                    }
                    if ((tri->unk12 & 0x80) && (f64)(*arg2 * 6.0f) < h2) {
                        D_807F94B0 = 1;
                    }
                    if ((tri->unk12 & 0x100) && arg3 != NULL && (arg3->unk5C & 1)) {
                        if ((f64)(*arg2 * 6.0f) < h2 && (f32)(h2 - (f64)(*arg2 * 6.0f)) < 600.0f) {
                            ((L6679BCSub174 *)D_807F94B8)->unk1F0 |= 0x2000;
                        }
                    }
                    if ((tri->unk12 & 0xA00) && arg3 != NULL && (arg3->unk5C & 1)) {
                        if ((f64)(*arg2 * 6.0f) < h2 && (f32)(h2 - (f64)(*arg2 * 6.0f)) < 800.0f) {
                            ((L6679BCSub174 *)D_807F94B8)->unk1F0 |= 0x4000;
                        }
                    }
                    if (tri->unk12 & 0x4850) {
                        if (arg3 != NULL) {
                            if (h2 < (f64)(*arg2 * 6.0f)) {
                                diff = (f64)(*arg2 * 6.0f) - h2;
                            } else {
                                diff = -((f64)(*arg2 * 6.0f) - h2);
                            }
                            if ((tri->unk12 & 0x10) && diff < 40.0f) {
                                D_807F94AE = 1;
                            }
                            if ((tri->unk12 & 0x40) && diff < 40.0f) {
                                D_807F94AF = 1;
                            }
                        }
                    } else {
                        if (D_807F94BC != 0) {
                            collisionRecordTriangleS((struct CollisionTriS *)tri, (f32)h2);
                        }
                        if (!(tri->unk12 & 1)) {
                            func_80666D88(*arg2 * 6.0f, (f32)h2, 1, arg3, 0);
                            func_80666F04(*arg2 * 6.0f, (f32)h2, 1, tri->unk14);
                            spBF = mathCheckCloserFloatThreshold(spCC, (f32)h2, spC4, 1);
                            if (collisionCheckTriangleWindingS16(tri) != 0 && spBF != 0) {
                                spCB = 1;
                                spCC = (f32)h2;
                                sp14C = tri;
                                D_807F94B5 = tri->unk16 & 0xF;
                                if (h2 < (f64)(*arg2 * 6.0f)) {
                                    diff = (f64)(*arg2 * 6.0f) - h2;
                                } else {
                                    diff = -((f64)(*arg2 * 6.0f) - h2);
                                }
                                if (diff > 30.0f) {
                                    t = (diff - 30.0f) / 120.0f;
                                    if ((f64)t > 1.0) {
                                        D_807F94B5 = 0xF;
                                    } else {
                                        D_807F94B5 = (u32)((f32)D_807F94B5 + (f32)(0xF - D_807F94B5) * t);
                                    }
                                }
                                func_806689F0((s32)arg3, (struct CollisionPlaneTriS *)tri, 1);
                                if (arg3 != NULL) {
                                    arg3->unk70[8] = tri->unk15;
                                    arg3->unk16D = D_807F94B5;
                                }
                                D_807F94B1 = tri->unk15;
                                if (tri->unk12 & 2) {
                                    *arg2 = spCC / 6.0f;
                                    if (!(tri->unk12 & 8)) {
                                        D_807F94AB = 1;
                                    }
                                    if (tri->unk12 & 0x2000) {
                                        D_807F946E = 1;
                                    }
                                    if (arg3 != NULL && (tri->unk12 & 0x1000)) {
                                        arg3->unk64 |= 0x40;
                                    }
                                    if (arg3 != NULL) {
                                        arg3->unk150 = (s32)tri;
                                    }
                                    return 1;
                                }
                            }
                        } else {
                            if (arg3 != NULL) {
                                if ((f64)(arg3->unk80 * 6.0f) < h2) {
                                    arg3->unk6A |= 4;
                                    arg3->unkB0[0] = tri->unk16 >> 4;
                                    if (*(s8 *)&arg3->unkB0[0] == 0xF) {
                                        *(s8 *)&arg3->unkB0[0] = -1;
                                    }
                                }
                                arg3->unk6A |= 2;
                                arg3->unkAC = h2 / 6.0;
                            }
                            if (tri->unk12 & 0x20) {
                                func_80666D88(*arg2 * 6.0f, (f32)h2, 1, arg3, 1);
                            }
                            D_807F9484 = 1;
                            D_807F9488 = (f32)(h2 / 6.0);
                        }
                    }
                }
            }
            tri++;
        } while (tri != sp150);
    }
    if (spCB != 0) {
        *arg2 = spCC / 6.0f;
        if (!(sp14C->unk12 & 8)) {
            D_807F94AB = 1;
        }
        if (sp14C->unk12 & 0x2000) {
            D_807F946E = 1;
        }
        if (arg3 != NULL && (sp14C->unk12 & 0x1000)) {
            arg3->unk64 |= 0x40;
        }
    }
    if (D_8076A0A8 == 0x57 && arg3 != NULL) {
        spCB |= func_80668520(&spCC, spC4, cur, arg2);
    }
    if (arg3 != NULL) {
        arg3->unk150 = 0;
    }
    return spCB;
}

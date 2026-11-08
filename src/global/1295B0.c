#include "common.h"
#include "actor.h"

extern Actor *gCurrentActor;
extern Actor *gSpawnedActor;
extern Actor *D_807FBB4C;
extern ActorGlobalState D_807FBB70;
extern void *gPlayerSlots;

void actorSetUniformScale(Actor *actor, f32 scale) {
    actor->unk4->unk34 = scale;
    actor->unk4->unk38 = scale;
    actor->unk4->unk3C = scale;
    if (actor->unk140 != NULL) {
        actor->unk15E = (u32)((f32)actor->unk140->unkC * scale * 0.5);
    }
}

void *heapAlloc(s32);
void heapClearBlock(void *);
void heapFreeDeferred(void *);
void actorFindActiveByType(s32, void *);
void func_8067AB20(void *, void *, s32, s32, s16 *, s32);

void func_80724994(u8 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    s16 *sp24;
    void *sp20;

    sp24 = heapAlloc(8);
    heapFreeDeferred(sp24);
    sp24[0] = arg1;
    sp24[1] = arg2;
    sp24[2] = arg3;
    sp24[3] = arg4;
    actorFindActiveByType(0xB, &sp20);
    func_8067AB20(0, sp20, 0x01000000, arg0, sp24, 0);
}

s32 func_80724A20(void) {
    s32 found;
    s16 i;

    found = 0;
    i = 0;
    if (D_807FBB70.unk254 > 0) {
        do {
            if (D_807FBB70.unk258[i] == 3) {
                found = 1;
                gCurrentActor->state = D_807FBB70.unk278[i][1];
                gCurrentActor->unk155[0] = 0;
            }
            i++;
        } while (found == 0 && i < D_807FBB70.unk254);
    }
    return found;
}

typedef struct ZoneEntry {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ s16 unk4;
    /* 0x6 */ u8 unk6;
    /* 0x7 */ u8 pad7[3];
} ZoneEntry;

typedef struct Zone {
    /* 0x00 */ u8 pad0[0x10];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ u8 pad12[2];
    /* 0x14 */ ZoneEntry *unk14;
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 pad19[0xB];
} Zone; // size = 0x24

typedef struct ZoneTable {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ u8 pad2[2];
    /* 0x4 */ Zone *unk4;
} ZoneTable;

extern ZoneTable *D_80755690;

void zoneEntrySetDisabled(u8 zoneId, u8 entryIndex, u8 disabled) {
    Zone *group;
    s16 i;
    u8 idx;

    group = D_80755690->unk4;
    for (i = 0; i < D_80755690->unk0;) {
        idx = entryIndex;
        if (group->unk18 == zoneId) {
            if (idx < group->unk10) {
                if (disabled != 0) {
                    group->unk14[idx].unk6 |= 0x80;
                } else {
                    group->unk14[idx].unk6 &= 0xFF7F;
                }
            }
            return;
        }
        i++;
        group++;
    }
}

void zoneEntryGetPosition(u8 arg0, u8 arg1, f32 *arg2, f32 *arg3, f32 *arg4) {
    Zone *group;
    s16 i;
    u8 idx;

    group = D_80755690->unk4;
    for (i = 0; i < D_80755690->unk0;) {
        idx = arg1;
        if (group->unk18 == arg0) {
            if (idx < group->unk10) {
                *arg2 = group->unk14[idx].unk0;
                *arg3 = group->unk14[idx].unk2;
                *arg4 = group->unk14[idx].unk4;
            }
            return;
        }
        i++;
        group++;
    }
}

typedef struct A1View {
    /* 0x00 */ u8 pad0[0xB8];
    /* 0xB8 */ f32 unkB8;
    /* 0xBC */ u8 padBC[0x2A];
    /* 0xE6 */ s16 unkE6;
    /* 0xE8 */ u8 padE8[6];
    /* 0xEE */ s16 unkEE;
} A1View;

extern A1View *D_807FBD6C;
#define A1ACT ((A1View *)gCurrentActor)

void func_80724C2C(s16 arg0) {
    s16 angle;

    angle = (D_807FBD6C->unkEE + 0x800) & 0xFFF;
    A1ACT->unkEE = angle;
    A1ACT->unkE6 = angle;
    A1ACT->unkB8 = arg0;
}

extern struct SpawnNodeList *D_80755694;
void spawnNodeListInitFromMap();

void func_80724C78(void *arg0) {
    spawnNodeListInitFromMap(arg0, D_80755690, D_80755694);
}

typedef struct A1Sub4 {
    /* 0x00 */ u8 pad0[0x1C];
    /* 0x1C */ u8 *unk1C;
    /* 0x20 */ struct A1Entry10 *unk20;
    /* 0x24 */ struct A1Entry10 *unk24;
} A1Sub4;

typedef struct A1Entry10 {
    /* 0x0 */ u8 unk0;
    /* 0x1 */ u8 unk1;
    /* 0x2 */ u8 pad2[2];
    /* 0x4 */ f32 unk4;
    /* 0x8 */ f32 unk8;
    /* 0xC */ f32 unkC;
} A1Entry10;

#define A1SUB4 ((A1Sub4 *)gCurrentActor->unk4)

void func_80724CA4(s16 arg0, s16 arg1) {
    u8 *table;

    A1SUB4->unk1C = heapAlloc(arg1 * 8 + 8);
    heapClearBlock(A1SUB4->unk1C);
    table = A1SUB4->unk1C;
    table[0] = 0x7F;
    table[1] = arg0;
    table[arg1 << 3] = 0;
}

void func_80724D28(s16 arg0, s16 arg1) {
    A1Entry10 *table;

    A1SUB4->unk24 = heapAlloc(arg1 * 0x10 + 0x10);
    heapClearBlock(A1SUB4->unk24);
    table = A1SUB4->unk24;
    table[0].unk0 = arg0;
    table[0].unk1 = arg0 + 1;
    ((u8 *)table)[arg1 << 4] = 0xFF;
}

void func_80724DB0(s16 arg0, s16 arg1) {
    A1Entry10 *table;

    A1SUB4->unk20 = heapAlloc(arg1 * 0x10 + 0x10);
    heapClearBlock(A1SUB4->unk20);
    table = A1SUB4->unk20;
    table[0].unk4 = 1.0f;
    table[0].unk8 = 1.0f;
    table[0].unkC = 1.0f;
    table[0].unk0 = arg0;
    table[0].unk1 = arg0;
    ((u8 *)table)[arg1 << 4] = 0xFF;
}

typedef struct SpawnEntry {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ u8 pad4[0xA];
    /* 0x0E */ u8 unkE;
    /* 0x0F */ u8 padF[9];
} SpawnEntry; // size = 0x18

extern SpawnEntry D_8075EB80[];

typedef struct A1Tbl18 {
    /* 0x00 */ u8 pad0[0xC];
    /* 0x0C */ u8 unkC;
    /* 0x0D */ u8 unkD;
    /* 0x0E */ u8 pad0E[0xA];
} A1Tbl18;

typedef struct A1Cam {
    /* 0x0 */ u8 pad0[2];
    /* 0x2 */ s16 unk2;
    /* 0x4 */ u16 unk4;
    /* 0x6 */ s16 unk6;
} A1Cam;

typedef struct A1Plr {
    /* 0x000 */ u8 pad0[0x210];
    /* 0x210 */ f32 unk210;
    /* 0x214 */ f32 unk214;
    /* 0x218 */ f32 unk218;
    /* 0x21C */ u8 pad21C[0x98];
    /* 0x2B4 */ f32 unk2B4;
    /* 0x2B8 */ f32 unk2B8;
    /* 0x2BC */ f32 unk2BC;
} A1Plr;

typedef struct A1S90 {
    /* 0x00 */ u8 pad0[0xA];
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ u8 pad10[0x14];
    /* 0x24 */ u8 unk24;
} A1S90;

typedef struct A1S98 {
    /* 0x00 */ u8 pad0[0x44];
    /* 0x44 */ u8 unk44;
} A1S98;

f32 mathAngleBetweenPointsRad(f32, f32, f32, f32);
f32 mathCalculatePitchAngle(f32, f32, f32, f32, f32, f32, s32);
s16 mathAngleEaseToward(s16, s16, f32);
extern u8 D_807444EC;
#define A1PLR ((A1Plr *)gPlayerSlots)
#define A1DC90 ((A1S90 *)D_807FDC90)
#define A1DC98 ((A1S98 *)D_807FDC98)
#define A1CAM(a) ((A1Cam *)((A1Sub4 *)(a)->unk4)->unk1C)

void func_80724E48(u8 arg0) {
    f32 angle;
    f32 sp38;
    f32 sp34;
    A1Cam *sp30;
    f32 sp2C;
    f32 sp28;
    s32 pitchArg;
    s16 res;

    sp38 = 0.0f;
    angle = 0.0f;
    if (arg0 == 8) {
        pitchArg = 0x46;
        sp34 = D_807FBB4C->yaw * 3.1415927f * (1.0 / 2048.0);
        sp30 = A1CAM(D_807FBB4C);
        sp28 = 1.0431069f;
    } else {
        sp34 = gCurrentActor->yaw * 3.1415927f * (1.0 / 2048.0);
        sp30 = A1CAM(gCurrentActor);
        pitchArg = ((A1Tbl18 *)D_8075EB80)[A1DC98->unk44].unkD;
        sp28 = ((A1Tbl18 *)D_8075EB80)[A1DC98->unk44].unkC * 4 * 3.1415927f * (1.0 / 2048.0);
        if (pitchArg == 0xFF) {
            pitchArg = 0x3E8;
        }
    }
    if ((s32)sp30 != 0) {
        sp2C = (f64)(u32)sp30->unk4 / 65535.0 * 6.2831854820251465;
        if (D_807444EC == 1 && arg0 != 5 && arg0 != 7) {
            arg0 = 6;
        }
        switch (arg0) {
            case 8:
                sp38 = mathCalculatePitchAngle(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, D_807FBB4C->x, D_807FBB4C->y, D_807FBB4C->z, pitchArg);
                angle = mathAngleBetweenPointsRad(gCurrentActor->x, gCurrentActor->z, D_807FBB4C->x, D_807FBB4C->z) - sp34;
                break;
            case 7:
                sp38 = mathCalculatePitchAngle(D_807FDC94->x, D_807FDC94->y, D_807FDC94->z, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, pitchArg);
                angle = mathAngleBetweenPointsRad(D_807FDC94->x, D_807FDC94->z, gCurrentActor->x, gCurrentActor->z) - sp34;
                break;
            case 6:
                sp38 = mathCalculatePitchAngle(A1PLR->unk210, A1PLR->unk214, A1PLR->unk218, gCurrentActor->x, gCurrentActor->y + (u32)gCurrentActor->unk15E, gCurrentActor->z, pitchArg);
                angle = mathAngleBetweenPointsRad(A1PLR->unk210, A1PLR->unk218, gCurrentActor->x, gCurrentActor->z) - sp34;
                break;
            case 0:
                sp38 = mathCalculatePitchAngle(A1PLR->unk2B4, A1PLR->unk2B8, A1PLR->unk2BC, gCurrentActor->x, gCurrentActor->y + (u32)gCurrentActor->unk15E, gCurrentActor->z, pitchArg);
            case 1:
                angle = mathAngleBetweenPointsRad(A1PLR->unk2B4, A1PLR->unk2BC, gCurrentActor->x, gCurrentActor->z) - sp34;
                break;
            case 2:
                angle = A1DC90->unk24 * 2 * 0.017453292f;
                break;
            case 3:
                sp38 = mathCalculatePitchAngle(A1DC90->unkA, A1DC90->unkC, A1DC90->unkE, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, pitchArg);
                angle = mathAngleBetweenPointsRad(A1DC90->unkA, A1DC90->unkE, gCurrentActor->x, gCurrentActor->z) - sp34;
                break;
        }
        if (angle < 0.0f) {
            angle += 6.2831855f;
        }
        if (sp28 != 0.0f) {
            if (sp28 < angle && angle <= 3.1415927f) {
                angle = sp28;
                if (sp2C > 3.1415927f) {
                    angle = sp28 + 6.2831855f;
                }
            } else if (angle < 6.2831855f - sp28 && angle > 3.1415927f) {
                angle = 6.2831855f - sp28;
                if (sp2C < 3.1415927f) {
                    angle = angle - 6.2831855f;
                }
            }
        }
        if (angle > 3.1415927f) {
            angle -= 6.2831855f;
        }
        if (sp2C > 3.1415927f) {
            sp2C -= 6.2831855f;
        }
        res = mathAngleEaseToward((s32)(sp2C * 2048.0 / 3.1415927410125732), (s32)(angle * 2048.0 / 3.1415927410125732), 5.0f);
        sp30->unk2 = (u32)(sp38 / 6.2831855f * 65535.0);
        sp30->unk4 = (u32)(res / 4095.0 * 65535.0);
        sp30->unk6 = 0;
    }
}

s32 lineSegmentIntersect2D(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7, f32 *arg8, f32 *arg9) {
    f32 a1;
    f32 b1;
    f32 c1;
    f32 a2;
    f32 b2;
    f32 c2;
    f32 d1;
    f32 d2;
    f32 d3;
    f32 d4;
    f32 det;
    f32 half;
    f32 y;
    f32 two;
    s16 ix;
    s16 iy;

    a1 = arg3 - arg1;
    b1 = arg0 - arg2;
    c1 = arg2 * arg1 - arg0 * arg3;
    d3 = arg4 * a1 + b1 * arg5 + c1;
    d4 = arg6 * a1 + b1 * arg7 + c1;
    if (d3 != 0.0f && d4 != 0.0f && ((s32)((u32)d3 ^ (u32)d4)) >= 0) {
        return 0;
    }
    a2 = arg7 - arg5;
    b2 = arg4 - arg6;
    c2 = arg6 * arg5 - arg4 * arg7;
    d1 = arg0 * a2 + b2 * arg1 + c2;
    d2 = arg2 * a2 + b2 * arg3 + c2;
    if (d1 != 0.0f && d2 != 0.0f && ((s32)((u32)d1 ^ (u32)d2)) >= 0) {
        return 0;
    }
    det = a1 * b2 - a2 * b1;
    if (det == 0.0f) {
        return 2;
    }
    two = 2.0f;
    if (det < 0.0f) {
        half = -det / two;
    } else {
        half = det / two;
    }
    if (b1 * c2 < b2 * c1) {
        two = (b1 * c2 - b2 * c1) - half;
    } else {
        two = (b1 * c2 - b2 * c1) + half;
    }
    *arg8 = two / det;
    if (a2 * c1 < a1 * c2) {
        two = (a2 * c1 - a1 * c2) - half;
    } else {
        two = (a2 * c1 - a1 * c2) + half;
    }
    y = two / det;
    *arg9 = y;
    ix = (s32)*arg8;
    iy = (s32)y;
    if ((ix == arg0 && iy == arg1) || (ix == arg2 && iy == arg3) || (ix == arg4 && iy == arg5) || (ix == arg6 && iy == arg7)) {
        return 3;
    }
    return 1;
}

u8 rectContainsPoint2D(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5) {
    s32 ret;

    ret = arg0 >= arg2;
    if (ret != 0) {
        ret = arg4 >= arg0;
        if (ret != 0) {
            ret = arg1 >= arg3;
            if (ret != 0) {
                ret = arg5 >= arg1;
            }
        }
    }
    return ret;
}

s32 lineSegmentIntersect2D(s16, s16, s16, s16, s16, s16, s16, s16, f32 *, f32 *);

typedef struct A1PolyVert {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
    /* 0x4 */ s16 z;
} A1PolyVert;

typedef struct A1Poly {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ s16 unk4;
    /* 0x6 */ s16 unk6;
    /* 0x8 */ s16 count;
    /* 0xA */ u8 padA[2];
    /* 0xC */ A1PolyVert *verts;
} A1Poly;

u8 polygonContainsPoint2D(s16 arg0, s16 arg1, A1Poly *arg2) {
    s32 res;
    f32 sp68;
    f32 sp64;
    s16 hits;
    s16 i;
    u8 edgeHits;

    hits = 0;
    if (rectContainsPoint2D(arg0, arg1, arg2->unk0, arg2->unk2, arg2->unk4, arg2->unk6)) {
        edgeHits = 0;
        i = 1;
        if (arg2->count >= 2) {
            do {
                if (i + 1 != arg2->count) {
                    res = lineSegmentIntersect2D(arg0, arg1, -0x8000, -0x8000, arg2->verts[i].x, arg2->verts[i].z, arg2->verts[i + 1].x, arg2->verts[i + 1].z, &sp68, &sp64);
                } else {
                    res = lineSegmentIntersect2D(arg0, arg1, -0x8000, -0x8000, arg2->verts[i].x, arg2->verts[i].z, arg2->verts[1].x, arg2->verts[1].z, &sp68, &sp64);
                }
                hits += res != 0;
                if (res == 3) {
                    edgeHits++;
                }
                i++;
            } while (i < arg2->count);
        }
        if (edgeHits != 0 && !(edgeHits & 1) && hits == edgeHits) {
            hits--;
        }
    }
    return hits & 1;
}

void camClosestPointOnSegment(f32, f32, f32, f32, f32, f32, f32, f32, f32, f32 *, f32 *, f32 *);

s32 segmentIntersectsCircle2D(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6) {
    f32 outX;
    f32 outY;
    f32 outZ;

    camClosestPointOnSegment(arg4, 0.0f, arg5, arg0, 0.0f, arg1, arg2, 0.0f, arg3, &outX, &outY, &outZ);
    return ((outX - arg4) * (outX - arg4) + (outZ - arg5) * (outZ - arg5) < (f32)(arg6 * arg6)) & 0xFF;
}

typedef struct C1ActorView {
    /* 0x000 */ u8 pad0[0x58];
    /* 0x058 */ s32 unk58;
    /* 0x05C */ u16 unk5C;
    /* 0x05E */ u8 pad5E[0xC];
    /* 0x06A */ u16 unk6A;
    /* 0x06C */ u8 pad6C[0x10];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x30];
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ u8 padBC[4];
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ u8 padC4[0x22];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 padE8[6];
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ u8 padF0[0x3C];
    /* 0x12C */ s16 unk12C;
    /* 0x12E */ u8 pad12E[0x26];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[0x1E];
    /* 0x174 */ void *unk174;
} C1ActorView;

typedef struct C1Link {
    /* 0x00 */ u8 pad0[0x1C];
    /* 0x1C */ C1ActorView *unk1C;
} C1Link;

typedef struct SpawnNode {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 pad1[3];
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ u8 padA[7];
    /* 0x11 */ u8 unk11;
    /* 0x12 */ u8 unk12;
    /* 0x13 */ u8 unk13;
    /* 0x14 */ u8 unk14;
    /* 0x15 */ u8 pad15[3];
    /* 0x18 */ C1ActorView *unk18;
    /* 0x1C */ C1Link *unk1C;
    /* 0x20 */ u8 (*unk20)[2];
    /* 0x24 */ s16 unk24;
    /* 0x26 */ u8 pad26[0x16];
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ s16 unk40;
    /* 0x42 */ u8 unk42;
    /* 0x43 */ u8 unk43;
    /* 0x44 */ u8 unk44;
    /* 0x45 */ u8 pad45;
    /* 0x46 */ u16 unk46;
} SpawnNode; // size = 0x48

typedef struct SpawnNodeList {
    /* 0x0 */ s16 count;
    /* 0x2 */ u8 pad2[2];
    /* 0x4 */ SpawnNode *nodes;
} SpawnNodeList;

#define C1ACT44 ((C1ActorView *)gSpawnedActor)

extern SpawnNodeList *D_80755694;
s32 actorSpawn(s32, s32);
void spawnNodeInitActorFromEntry(void *, void *);

typedef struct F1Ent {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
    /* 0x4 */ s16 z;
    /* 0x6 */ u8 flags;
    /* 0x7 */ u8 radius;
    /* 0x8 */ u8 height;
    /* 0x9 */ u8 pad9;
    /* 0xA */ s16 unkA;
} F1Ent; // size = 0xC? (stride 0xA)

typedef struct F1Tbl {
    /* 0x00 */ u8 pad0[8];
    /* 0x08 */ s16 count8;
    /* 0x0A */ u8 padA[2];
    /* 0x0C */ u8 *entsC;
    /* 0x10 */ s16 count10;
    /* 0x12 */ u8 pad12[2];
    /* 0x14 */ u8 *ents14;
} F1Tbl;

#define F1ENT(t, i) ((F1Ent *)((t)->ents14 + (i) * 0xA))


s32 segmentIntersectsCircle2D(s16, s16, s16, s16, s16, s16, s16);
s32 zoneCanReachPoint(Actor *, s16, s16, s16, F1Tbl *);
s32 randomNonNegative(void);
s32 zoneFindBestReachablePoint(arg0, arg1, arg2, arg3, arg4, arg5)
u8 arg0;
Actor *arg1;
F1Tbl *arg2;
s16 *arg3;
s16 *arg4;
s16 *arg5;
{
    s16 i;
    u8 stop;
    u8 found;
    s32 best;
    F1Ent *e;
    s32 d;

    stop = 0;
    found = 0;
    if (arg0 & 1) {
        best = 0;
    } else {
        best = 0xF423F;
    }
    for (i = 0; i < arg2->count10 && !stop; i++) {
        e = F1ENT(arg2, i);
        if (!(e->flags & 0x80) && ((e->flags & 0x7F) == 3)) {
            if (segmentIntersectsCircle2D((s32)arg1->x, (s32)arg1->z, e->x, e->z, (s32)D_807FDC94->x, (s32)D_807FDC94->z, 0x14) == 0) {
                if (zoneCanReachPoint(arg1, e->x, e->y, e->z, arg2) != 0) {
                    if (((arg0 & 1) && (d = (s32)(((D_807FDC94->x - e->x) * (D_807FDC94->x - e->x)) + ((D_807FDC94->z - e->z) * (D_807FDC94->z - e->z))), best < d)) ||
                        ((arg0 & 2) && (d = (s32)(((arg1->x - e->x) * (arg1->x - e->x)) + ((arg1->z - e->z) * (arg1->z - e->z))), d < best))) {
                        best = d;
                        *arg3 = e->x;
                        *arg4 = e->y;
                        *arg5 = e->z;
                        found = 1;
                        if (arg0 & 0x80) {
                            if (((randomNonNegative() >> 0xF) % 100) >= 0x33) {
                                stop = 1;
                            }
                        }
                    }
                }
            }
        }
    }
    return found;
}

typedef struct F1Pt6 {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
    /* 0x4 */ s16 z;
} F1Pt6;


s32 zoneCanReachPoint(Actor *arg0, s16 arg1, s16 arg2, s16 arg3, F1Tbl *arg4) {
    s32 res;
    f32 f1;
    f32 f2;
    f32 x;
    f32 y;
    f32 z;
    s16 i;
    s16 cross;
    u8 edges;

    cross = 0;
    edges = 0;
    x = arg0->x;
    y = arg0->y + (f32)(u32)arg0->unk15E;
    z = arg0->z;
    for (i = 1; i < arg4->count8; i++) {
        if ((i + 1) != arg4->count8) {
            res = lineSegmentIntersect2D(arg1, arg3, -0x8000, -0x8000, ((F1Pt6 *)arg4->entsC)[i].x, ((F1Pt6 *)arg4->entsC)[i].z, ((F1Pt6 *)arg4->entsC)[i + 1].x, ((F1Pt6 *)arg4->entsC)[i + 1].z, &f1, &f2);
        } else {
            res = lineSegmentIntersect2D(arg1, arg3, -0x8000, -0x8000, ((F1Pt6 *)arg4->entsC)[i].x, ((F1Pt6 *)arg4->entsC)[i].z, ((F1Pt6 *)arg4->entsC)[1].x, ((F1Pt6 *)arg4->entsC)[1].z, &f1, &f2);
        }
        cross += (res != 0);
        if (res == 3) {
            edges++;
        }
    }
    if (edges != 0) {
        if (!(edges & 1) && (cross == edges)) {
            cross--;
        }
    }
    res = 1;
    if (cross & 1) {
        for (i = 0; res && i < arg4->count10; i++) {
            if (!(F1ENT(arg4, i)->flags & 0x80)) {
                if (((F1ENT(arg4, i)->flags & 0x7F) == 0) || ((F1ENT(arg4, i)->flags & 0x7F) == 5)) {
                    if (segmentIntersectsCircle2D((s32)x, (s32)z, arg1, arg3, F1ENT(arg4, i)->x, F1ENT(arg4, i)->z, F1ENT(arg4, i)->radius) != 0) {
                        if (((f32)F1ENT(arg4, i)->y <= y) && (y <= (f32)(F1ENT(arg4, i)->height + F1ENT(arg4, i)->y))) {
                            res = 0;
                        }
                    }
                }
            }
        }
    } else {
        res = 0;
    }
    return res;
}

void func_806755A8(s32, s32, s32, s32, void *, void *);

s32 zoneCheckActorInside(Actor *arg0, s32 arg1, s32 arg2, F1Tbl *arg3) {
    f32 x;
    f32 y;
    f32 z;
    s16 i;
    s32 found;
    F1Ent *e;
    u8 sel;

    arg0->unkF4 = 0;
    arg0->unkF6 = 0xFFF;
    found = 0;
    x = arg0->x;
    y = arg0->y;
    z = arg0->z;
    for (i = 0; i < arg3->count10; i++) {
        e = F1ENT(arg3, i);
        sel = e->flags & 0x7F;
        if (!(e->flags & 0x80)) {
            if ((sel == 0) || (sel == 1) ||
                ((sel == 5) && ((f64)arg0->speedXZ < (f64)(u32)((u8 *)D_807FDC9C)[0xD] * 1.4))) {
                if (((f32)e->y <= y) && (y <= (f32)(e->y + e->height))) {
                    if (e->flags != 0) {} // FAKE: live range steers flags/count10 colouring (a1/t0)
                    if (i == 5) {} // FAKE: steer s3 and s8 constant coloring
                    if (((x - (f32)e->x) * (x - (f32)e->x)) + ((z - (f32)e->z) * (z - (f32)e->z)) < (f32)(e->radius * e->radius)) {
                        func_806755A8((s32)x, (s32)z, e->x, e->z, &arg0->unkF4, &arg0->unkF6);
                        found = 1;
                        arg0->unkFC = 1;
                        if (arg3) {} // FAKE: steers ret temps
                        arg0->unkFD = 1;
                    }
                }
            }
        }
    }
    return found;
}

typedef struct F1Pt {
    /* 0x0 */ u8 pad0[2];
    /* 0x2 */ s16 unk2;
    /* 0x4 */ s16 unk4;
    /* 0x6 */ s16 unk6;
    /* 0x8 */ s16 unk8;
} F1Pt;

void actorSetPositionFromPoint(Actor *actor, F1Pt *pt) {
    actor->x = pt->unk4;
    actor->y = pt->unk6;
    actor->prevY = pt->unk6;
    actor->z = pt->unk8;
    actor->yaw = pt->unk2;
}

typedef struct A4Act {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ void *unk4;
    /* 0x008 */ u8 pad8[0x50];
    /* 0x058 */ s32 unk58;
    /* 0x05C */ u8 pad5C[4];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u8 pad64[4];
    /* 0x068 */ u16 unk68;
    /* 0x06A */ u16 unk6A;
    /* 0x06C */ u16 unk6C;
    /* 0x06E */ u8 pad6E[0xE];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x1C];
    /* 0x0A4 */ f32 unkA4;
    /* 0x0A8 */ u8 padA8[0x1C];
    /* 0x0C4 */ f32 unkC4;
    /* 0x0C8 */ f32 unkC8;
    /* 0x0CC */ u8 padCC[0x12];
    /* 0x0DE */ s16 unkDE;
    /* 0x0E0 */ u8 padE0[6];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 padE8[6];
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ u8 padF0[0x20];
    /* 0x110 */ u8 unk110;
    /* 0x111 */ u8 pad111[0x19];
    /* 0x12A */ s16 unk12A;
    /* 0x12C */ s16 unk12C;
    /* 0x12E */ u8 pad12E[2];
    /* 0x130 */ u8 unk130;
    /* 0x131 */ u8 unk131;
    /* 0x132 */ u8 pad132[0x12];
    /* 0x144 */ u8 unk144;
    /* 0x145 */ u8 pad145[0xF];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[0x14];
    /* 0x16A */ u8 unk16A;
    /* 0x16B */ u8 unk16B;
    /* 0x16C */ u8 unk16C;
    /* 0x16D */ u8 pad16D;
    /* 0x16E */ u8 unk16E;
    /* 0x16F */ u8 unk16F;
    /* 0x170 */ u8 pad170[4];
    /* 0x174 */ void *unk174;
    /* 0x178 */ u8 pad178[4];
    /* 0x17C */ s16 *unk17C;
} A4Act;

typedef struct A4Node {
    /* 0x00 */ u8 pad0[6];
    /* 0x06 */ s16 unk6;
    /* 0x08 */ u8 pad8[2];
    /* 0x0A */ u8 unkA;
    /* 0x0B */ u8 padB;
    /* 0x0C */ u8 unkC;
    /* 0x0D */ u8 unkD;
    /* 0x0E */ u8 padE;
    /* 0x0F */ u8 unkF;
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 pad11[7];
    /* 0x18 */ A4Act *unk18;
    /* 0x1C */ u8 pad1C[0x10];
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ u8 pad3C[4];
    /* 0x40 */ s16 unk40;
    /* 0x42 */ u8 unk42;
    /* 0x43 */ u8 unk43;
    /* 0x44 */ u8 unk44;
    /* 0x45 */ u8 pad45;
    /* 0x46 */ u16 unk46;
} A4Node;

typedef struct A4Entry {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ s16 unk4;
    /* 0x06 */ u8 pad6[2];
    /* 0x08 */ u32 unk8;
    /* 0x0C */ u8 padC[2];
    /* 0x0E */ u8 unkE;
    /* 0x0F */ u8 unkF;
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 unk11;
    /* 0x12 */ u8 unk12;
    /* 0x13 */ u8 unk13;
    /* 0x14 */ u8 unk14;
    /* 0x15 */ u8 unk15;
    /* 0x16 */ u8 unk16;
    /* 0x17 */ u8 unk17;
} A4Entry;

typedef struct A4Player {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ void *unk4;
    /* 0x008 */ u8 pad8[0x2E8];
} A4Player;

typedef struct A4St174 {
    /* 0x00 */ A4Node *unk0;
    /* 0x04 */ void *unk4;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ u8 padA[6];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ u8 pad16[8];
    /* 0x1E */ u8 unk1E;
    /* 0x1F */ u8 unk1F;
    /* 0x20 */ u8 pad20;
    /* 0x21 */ u8 unk21;
    /* 0x22 */ u8 unk22;
    /* 0x23 */ u8 unk23;
    /* 0x24 */ u8 pad24;
    /* 0x25 */ u8 unk25;
    /* 0x26 */ u8 pad26[0xE];
    /* 0x34 */ u8 unk34;
    /* 0x35 */ u8 unk35;
    /* 0x36 */ u8 pad36;
    /* 0x37 */ u8 unk37;
} A4St174;

extern f32 D_807502E8;
extern s16 D_807502E0;
extern s16 D_8075570C[];
extern s32 D_807FBB68;
extern u8 gPlayerCount;
extern u8 D_80755698[];
extern s32 gCurrentMap;
void actorScriptStart(void *, s32);
s16 controllerLookupStateByHash(void *);
void actorUpdateFloorContactAndTilt(void *, f32);
void behaviourSetAnimIds(s16, s16, s16, s16);
void actorSetTargetSpeed(void *, u8);
s32 randomNonNegative(void);
#define A4P4 ((A4Player *)gPlayerSlots)

#define A4ENTRY ((A4Entry *)&D_8075EB80[idx])
void spawnNodeInitActorFromEntry(void *arg0, void *arg1) {
    A4St174 *st;
    A4Node *node;
    s16 padA;
    s16 ang;
    A4Act *act;
    u8 type;
    u8 idx;
    A4Entry *entry;
    s32 v;

    act = arg0;
    node = arg1;
    st = act->unk174;
    idx = node->unk44;
    type = D_80755698[idx];
    node->unk42 = 5;
    node->unk18 = act;
    node->unk30 = 1.0f;
    node->unk2C = 0.01f;
    if (A4ENTRY->unk17 != 0) {
        node->unk38 = 1.0 / A4ENTRY->unk17;
    } else {
        node->unk38 = 0.0f;
    }
    ang = A4ENTRY->unk4;
    if (ang != 0) {
        actorScriptStart(act, ang);
    }
    D_807FDC98 = (Struct807FDC98 *)node;
    behaviourSetAnimIds(ang + 0, ang | 0, ang * 1, ang);
    if (act->unk4 != 0) {
        actorSetUniformScale((Actor *)act, ((node->unkF * 5) / 255.0) * 0.15);
    }
    actorSetPositionFromPoint((Actor *)act, (void *)node);
    act->unkDE = 0x400;
    act->unkC4 = D_807502E8;
    act->unkC8 = D_807502E0;
    act->unk12C = node->unk40;
    if (A4ENTRY->unkE == 0) {
        act->unk12A = 0x7D0;
    }
    actorSetTargetSpeed(act, node->unkC);
    st->unk0 = node;
    v = act->unkE6;
    act->unkEE = v;
    st->unk25 = 0;
    st->unk34 = 0xFF;
    st->unk8 = v;
    st->unk10 = act->unk7C;
    st->unk12 = act->unk80;
    st->unk14 = act->unk84;
    act->unk144 = 0x24;
    act->unk60 &= 0xFFFEFFFF;
    act->unk60 |= 0x20000;
    act->unk60 |= A4ENTRY->unk8;
    if (act->unk4 != 0) {
        act->unk68 |= 0xC0;
    }
    act->unk16E = A4ENTRY->unk14;
    act->unk16F = A4ENTRY->unk15;
    v = A4ENTRY->unkF;
    st->unk22 = v;
    st->unk23 = v;
    st->unk1E = A4ENTRY->unk10;
    st->unk1F = A4ENTRY->unk11;
    st->unk21 = A4ENTRY->unk12;
    st->unk35 = A4ENTRY->unk13;
    st->unk37 = A4ENTRY->unk16;
    act->unk154 = node->unk10;
    act->unk155 = 0;
    switch (type) {
        case 0:
        case 2:
        case 3:
            node->unk46 |= 0x4000;
        case 1:
            node->unk46 |= 8;
            break;
        case 10:
            node->unk46 |= 0x80;
            break;
        case 6:
            entry = (A4Entry *)act->unk17C;
            if (act->unk58 == 0xFE) {
                *(s16 *)entry = D_8075570C[node->unkA];
            } else {
                *(s16 *)entry = controllerLookupStateByHash(act);
            }
            break;
    }
    act->unk16A = 0xFF;
    act->unk16B = 0xFF;
    act->unk16C = 0xFF;
    switch (gCurrentMap) {
        case 0x4E:
        case 0x4F:
        case 0x83:
            v = node->unkD + (node->unk43 * 0xA);
            if (v >= 0x100) {
                node->unkD = 0xFF;
            } else {
                node->unkD = v;
            }
            break;
        case 0x53:
        case 0xC5:
            if (type == 6) {
        case 0x4C:
                act->unk130 = 0x3C;
                act->unk131 = 0x3C;
                act->unk154 = 0;
                act->unk155 = 0;
                act->unk144 = 1;
                act->unk60 |= 0x10000000;
        case 0x6:
        case 0xE:
        case 0x1B:
        case 0x1C:
        case 0x27:
        case 0x37:
        case 0x52:
        case 0x6A:
        case 0x98:
        case 0x99:
        case 0xAC:
        case 0xB9:
        case 0xD0:
                node->unk46 |= 0x20;
        case 0x3:
        case 0x43:
        case 0x44:
        case 0x4A:
        case 0xD1:
                act->unk60 |= 0x800000;
            }
            break;
        case 0x45:
            act->unk60 |= 0x800000;
        case 0x42:
        case 0x68:
        case 0x7C:
        case 0x88:
        case 0x89:
        case 0xA5:
            if (node->unk10 != 4) {
                st->unk37 = 7;
            }
            break;
        case 0xD4:
            act->unk12A = 0x7D0;
        case 0xD3:
            node->unk46 |= 4;
            break;
        case 0x50:
            act->unk60 &= 0xFEFFFFFF;
            break;
    }
    if (gPlayerCount >= 2) {
        st->unk4 = A4P4[(randomNonNegative() >> 0xF) % gPlayerCount].unk4;
    } else {
        st->unk4 = (void *)D_807FBB4C;
    }
    node->unk34 = 0.75f;
    act->unkA4 = node->unk6;
    if (type != 8) {
        actorUpdateFloorContactAndTilt(act, 0.0f);
        if (D_807FBB68 & 2) {
            act->unk110 = 0;
        } else if ((type == 4) || (act->unk58 == 0xF8)) {
            node->unk46 |= 0x800;
            act->unk110 = 0;
        } else if (act->unk110 == 1) {
            node->unk46 |= 0x200;
        }
    }
    if (type == 5) {
        ((A4Act *)gCurrentActor)->unk6A |= 4;
        ((A4Act *)gCurrentActor)->unk6C |= 4;
    }
}
#undef A4ENTRY

u8 spawnNodeHasState(u8, u8);

u8 spawnNodeHasActor(u8 arg0) {
    return spawnNodeHasState(arg0, 5) || spawnNodeHasState(arg0, 6);
}

u8 spawnNodeIsInCooldown(u8 arg0) {
    return spawnNodeHasState(arg0, 7);
}

u8 spawnNodeHasState(u8 arg0, u8 arg1) {
    s16 i;
    SpawnNode *node;

    node = D_80755694->nodes;
    for (i = 0; i < D_80755694->count; i++, node++) {
        if (node->unk13 == arg0) {
            return node->unk42 == arg1;
        }
    }
    return 0;
}

void spawnNodesSetActorStateByFlag(u16 arg0, u8 arg1) {
    s16 i;
    SpawnNode *node;

    node = D_80755694->nodes;
    for (i = 0; i < D_80755694->count; i++, node++) {
        if (node->unk42 == 5) {
            if (node->unk18->unk5C & arg0) {
                node->unk18->unk154 = arg1;
            }
        }
    }
}

void actorDespawn(void *);
void actorQueueDelayedCallback(void *, s32, s32, s32, s32, s32, s32);
void camClearActorRefs(void *);

void func_80726EE0(u8 arg0) {
    s16 i;
    SpawnNode *node;
    s32 mode;

    mode = arg0;
    node = D_80755694->nodes;
    for (i = 0; i < D_80755694->count; i++, node++) {
        if (node->unk46 & 0x80) {
            continue;
        }
        if ((node->unk42 == 5) && (node->unk18->unk5C & 2)) {
            actorQueueDelayedCallback(node->unk18, 0, 8, 0, 0, 0, 1);
            do {
            } while (0);
        } else if ((node->unk42 == 6) && (node->unk18->unk5C & 2)) {
            node->unk42 = 7;
            node->unk24 = node->unk14 * 0x1E;
            camClearActorRefs(node->unk18);
            actorDespawn(node->unk18);
        }
        switch (mode) {
            case 0:
            case 1:
                node->unk46 |= 2;
                break;
            case 2:
                node->unk46 &= ~2;
                break;
        }
    }
}

Actor *spawnNodeActivate(s16, u16);

void spawnNodeActivateAndSetState(s16 arg0, u8 arg1, u16 arg2) {
    C1ActorView *a = (C1ActorView *)spawnNodeActivate(arg0, arg2);

    if (a != NULL) {
        a->unk154 = arg1;
        a->unk155 = 0;
    }
}

void actorRegisterActive(void *);

Actor *spawnNodeActivate(s16 arg0, u16 arg1) {
    s16 i;
    SpawnNode *node;

    node = D_80755694->nodes;
    for (i = 0; i < D_80755694->count; i++, node++) {
        if (arg0 == node->unk13) {
            if (node->unk42 == 5) {
                node->unk46 |= arg1;
                return (Actor *)node->unk18;
            } else if ((node->unk42 == 6) && (arg1 & 0x400)) {
                actorRegisterActive(node->unk18);
                node->unk42 = 5;
                return (Actor *)node->unk18;
            }
        }
    }
    return 0;
}

u8 spawnNodeIdForActor(C1ActorView *arg0) {
    s16 i;
    SpawnNode *node;

    node = D_80755694->nodes;
    for (i = 0; i < D_80755694->count; i++, node++) {
        if ((arg0 == node->unk18) && (node->unk42 == 5)) {
            return node->unk13;
        }
    }
    return 0;
}

Actor *spawnNodeSpawnById(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6) {
    s16 i;
    SpawnNode *node;
    SpawnEntry *entry;

    node = D_80755694->nodes;
    for (i = 0; i < D_80755694->count; i++, node++) {
        if ((arg0 == node->unk13) && (node->unk42 != 5)) {
            entry = &D_8075EB80[node->unk44];
            if (actorSpawn(entry->unk0, entry->unk2) != 0) {
                node->unk46 |= 4;
                spawnNodeInitActorFromEntry(gSpawnedActor, node);
                if (arg1 != 0) {
                    C1ACT44->unk7C = arg1;
                    C1ACT44->unk80 = arg2;
                    C1ACT44->unk84 = arg3;
                    C1ACT44->unkEE = arg4;
                    C1ACT44->unkE6 = arg4;
                }
                C1ACT44->unkB8 = arg5;
                C1ACT44->unkC0 = arg6;
                C1ACT44->unk6A = 0;
                return gSpawnedActor;
            }
        }
    }
    return 0;
}

typedef struct C1Pt {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
    /* 0x4 */ s16 z;
    /* 0x6 */ u8 pad6[4];
} C1Pt; // size = 0xA

typedef struct C1Tbl98 {
    /* 0x00 */ u8 pad0[0x20];
    /* 0x20 */ u8 (*unk20)[2];
} C1Tbl98;

typedef struct C1TblA0 {
    /* 0x00 */ u8 pad0[0x14];
    /* 0x14 */ u8 *unk14;
} C1TblA0;

extern C1TblA0 *D_807FDCA0;
f32 mathAngleBetweenPointsDeg(s32, s32, s16, s16);

#define C1PTS ((C1Pt *)D_807FDCA0->unk14)
#define C1PT(i) ((C1Pt *)(D_807FDCA0->unk14 + (i)))

#define C1IDX (((C1Tbl98 *)D_807FDC98)->unk20[arg1][0] * 0xA)

void spawnNodeSpawnAtTablePoint(s16 arg0, u8 arg1) {
    u8 tbl;
    s16 sp34;

    tbl = ((C1Tbl98 *)D_807FDC98)->unk20[arg1][0];
    sp34 = (s16)(s32)((mathAngleBetweenPointsDeg((s32)D_807FDC94->x, (s32)D_807FDC94->z, C1PTS[tbl].x, C1PTS[tbl].z) * 4096.0f) / 360.0f);
    if (spawnNodeSpawnById(arg0, C1PTS[tbl].x, C1PTS[tbl].y, C1PTS[tbl].z, sp34, ((randomNonNegative() >> 0xF) % 100) + 0x64, ((randomNonNegative() >> 0xF) % 100) + 0xC8) != 0) {
        C1ACT44->unk154 = 0x17;
        C1ACT44->unk155 = 0;
    }
}

s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);

void spawnNodeSpawnFacingPoint(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8) {
    s16 sp46;
    f32 sp40;
    s32 dx;
    s32 dy;
    s32 dz;

    dx = arg4 - arg1;
    dy = arg5 - arg2;
    dz = arg6 - arg3;
    sp46 = mathAngleBetweenPoints2D((f32)arg4, (f32)arg6, (f32)arg1, (f32)arg3);
    sp40 = sqrtf((f32)((dx * dx) + (dy * dy) + (dz * dz)));
    dy = (s32)(sqrtf((f32)((dx * dx) + (dz * dz))) / (sp40 / (f32)arg7));
    if (spawnNodeSpawnById(arg0, arg1, arg2, arg3, sp46, dy, arg8) != 0) {
        C1ACT44->unk154 = 0x17;
        C1ACT44->unk155 = 0;
    }
}

extern s32 gCurrentMap;
s32 spawnFlagConditionMet(s16, s16);

void func_80727678(void) {
    s32 pad;
    s16 sp4A;
    SpawnNode *node;
    s16 j;
    s16 *ptr;
    SpawnEntry *entry;

    node = D_80755694->nodes;
    for (sp4A = 0; sp4A < D_80755694->count; sp4A++, node++) {
        for (j = 0; j < D_807FBB70.unk254; j++) {
            ptr = D_807FBB70.unk278[j];
            if (node->unk13 == *ptr) {
                switch (D_807FBB70.unk258[j]) {
                    case 1:
                        if ((node->unk42 == 0) && (spawnFlagConditionMet(((s16 *)&gCurrentMap)[1], node->unk13) != 0) && (entry = &D_8075EB80[node->unk44], actorSpawn(entry->unk0, entry->unk2) != 0)) {
                            spawnNodeInitActorFromEntry(gSpawnedActor, node);
                        } else if ((node->unk42 == 3) && (spawnFlagConditionMet(((s16 *)&gCurrentMap)[1], node->unk13) != 0)) {
                            entry = &D_8075EB80[node->unk44];
                            if (actorSpawn(entry->unk0, entry->unk2) != 0) {
                                spawnNodeInitActorFromEntry(gSpawnedActor, node);
                                C1ACT44->unk154 = 0x36;
                            }
                        }
                        break;
                    case 2:
                        if (node->unk42 == 7) {
                            node->unk42 = node->unk12;
                        }
                        break;
                    case 3:
                    case 4:
                        if (node->unk42 == 5) {
                            func_8067AB20(gCurrentActor, node->unk18, 0x01000000, D_807FBB70.unk258[j] & 0xFF, ptr, 0);
                        }
                        break;
                }
            }
        }
    }
}

extern u8 D_80755698[];
extern Struct807FD580 *gActivePlayerState;

void spawnNodeSelectEntry(SpawnNode *arg0) {
    u8 temp_v0;

    if ((gCurrentMap == 0x30) && (gActivePlayerState->stateFlags & 0x100000) && (temp_v0 = arg0->unk0, (D_80755698[temp_v0] != 0xA))) {
        switch (temp_v0) {
            case 28:
                arg0->unk44 = 0x63;
                return;
            case 9:
                arg0->unk44 = 0x54;
                return;
            case 44:
                arg0->unk44 = 0x67;
                return;
        }
    } else {
        arg0->unk44 = arg0->unk0;
    }
}

typedef struct C1State90 {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ C1ActorView *unk4;
    /* 0x08 */ u8 pad8[0x10];
    /* 0x18 */ u16 unk18;
} C1State90;

typedef struct C1Sub174 {
    /* 0x00 */ u8 pad0[0xD4];
    /* 0xD4 */ s16 unkD4;
} C1Sub174;

typedef struct C1PlayerView {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ C1ActorView *unk4;
    /* 0x008 */ u8 pad8[0x208];
    /* 0x210 */ f32 unk210;
    /* 0x214 */ f32 unk214;
    /* 0x218 */ f32 unk218;
    /* 0x21C */ u8 pad21C[0xD4];
} C1PlayerView; // size = 0x2F0

#define C1S90 ((C1State90 *)D_807FDC90)
#define C1PLAYERS ((C1PlayerView *)gPlayerSlots)
#define C1ACT40 ((C1ActorView *)gCurrentActor)

extern s16 D_8076A0AA;
extern s32 D_807FBB64;
extern u8 gPlayerCount;
void actorDeregisterActive(void *);
s16 mapChunkFindByPosition(f32, f32, f32, s32);
u8 spawnNodeInRangeAndVisible(SpawnNode *, s32);
u8 spawnNodeActorInRangeAndVisible(SpawnNode *, s32);
u8 spawnNodeActorOutOfRangeOrHidden(SpawnNode *, s32);
u8 spawnNodeActorOutOfRangeScaled(SpawnNode *, s32);
void sfxStopChannel(s32, s32);
void sfxStopSlotSound(void *, s32);

void spawnNodesUpdate(void) {
    s16 i;
    SpawnNode *node;
    s32 dist;
    u8 active;
    s32 best;
    s16 p;
    SpawnEntry *entry;
    C1ActorView *pa;
    f32 dz;
    f32 dx;
    s32 d;
    C1Sub174 *sub;

    node = D_80755694->nodes;
    for (i = 0; i < D_80755694->count; i++, node++) {
        active = (node->unk42 >= 5) && (node->unk42 < 7);
        if (active) {
            D_807FDC90 = (Struct807FDC90 *)node->unk18->unk174;
        }
        dist = D_8075EB80[node->unk44].unkE * 0x64;
        dist = dist * dist;
        if (active) {
            node->unk40 = node->unk18->unk12C;
        }
        if ((dist == 0) || (node->unk46 & 4) || (D_807FBB64 & 0x100)) {
            dist = 0x7FFFFFFF;
        }
        if (active && (node->unk18->unk154 == 0x3B)) {
            camClearActorRefs(node->unk18);
            actorDespawn(node->unk18);
            node->unk42 = 0;
        } else if (active && (node->unk18->unk154 == 0x3C)) {
            camClearActorRefs(node->unk18);
            actorDespawn(node->unk18);
            node->unk42 = node->unk12;
            node->unk46 &= 0xFFFB;
        } else if ((node->unk42 == 7) && (node->unk24 != 0)) {
            if (!(node->unk46 & 2)) {
                node->unk24 -= 1;
                if (node->unk24 == 0) {
                    node->unk43 += 1;
                    node->unk42 = node->unk12;
                    node->unk40 = mapChunkFindByPosition((f32)node->unk4, (f32)node->unk6, (f32)node->unk8, 0);
                    spawnNodeSelectEntry(node);
                    entry = &D_8075EB80[node->unk44];
                    if (actorSpawn(entry->unk0, entry->unk2) != 0) {
                        spawnNodeInitActorFromEntry(gSpawnedActor, node);
                        C1ACT44->unk154 = 0x36;
                        node->unk46 |= 1;
                    }
                }
            }
        } else if (node->unk42 == 2) {
            if ((spawnNodeInRangeAndVisible(node, dist) != 0) && (spawnFlagConditionMet(D_8076A0AA, node->unk13) != 0)) {
                spawnNodeSelectEntry(node);
                entry = &D_8075EB80[node->unk44];
                if (actorSpawn(entry->unk0, entry->unk2) != 0) {
                    spawnNodeInitActorFromEntry(gSpawnedActor, node);
                }
            }
        } else if (active && (node->unk18->unk154 == 0x40)) {
            node->unk42 = 7;
            node->unk24 = node->unk14 * 0x1E;
            if (node->unk1C->unk1C == node->unk18) {
                node->unk1C->unk1C = 0;
            }
            camClearActorRefs(node->unk18);
            actorDespawn(node->unk18);
        } else if (active) {
            best = 0xF423F;
            if ((C1S90->unk4->unk5C & 1) && (C1S90->unk4->unk154 == 0x67)) {
                if ((node->unk18->unk5C & 2) && (node->unk42 == 5)) {
                    if ((node->unk18->unk154 != 0x16) && (node->unk18->unk154 != 0x37) && !(node->unk46 & 0x40)) {
                        node->unk18->unk154 = 0x16;
                        node->unk18->unk155 = 0;
                    }
                }
            }
            if (gPlayerCount >= 2) {
                for (p = 0; p < gPlayerCount; p++) {
                    sub = (C1Sub174 *)C1PLAYERS[0].unk4->unk174;
                    dz = C1ACT40->unk84 - C1PLAYERS[p].unk4->unk84;
                    dx = C1ACT40->unk7C - C1PLAYERS[p].unk4->unk7C;
                    d = (s32)((dz * dz) + (dx * dx));
                    if ((d < best) || (sub->unkD4 != 0)) {
                        pa = C1PLAYERS[p].unk4;
                        best = d;
                        C1S90->unk4 = pa;
                    }
                }
            }
            if (node->unk42 == 6) {
                if (spawnNodeActorOutOfRangeScaled(node, dist) != 0) {
                    actorDespawn(node->unk18);
                    node->unk42 = node->unk12;
                } else if (spawnNodeActorInRangeAndVisible(node, dist) != 0) {
                    actorRegisterActive(node->unk18);
                    node->unk42 = 5;
                    node->unk46 |= 0x8000;
                }
            } else if ((node->unk42 == 5) && (spawnNodeActorOutOfRangeOrHidden(node, dist) != 0)) {
                if ((node->unk18->unk154 != 0x16) && (node->unk18->unk154 != 0x37)) {
                    if (node->unk18->unk58 == 0xF8) {
                        sfxStopChannel(0x42, 0);
                    }
                    sfxStopSlotSound(node->unk18, 0);
                    sfxStopSlotSound(node->unk18, 1);
                    actorDeregisterActive(node->unk18);
                    node->unk42 = 6;
                    C1S90->unk18 = 0;
                }
            }
        }
    }
}

s32 mapChunkIsVisibleForPlayer(s32, s16);

u8 spawnNodeInRangeAndVisible(SpawnNode *arg0, s32 arg1) {
    f32 dx;
    f32 dy;
    f32 dz;
    s32 ret;

    dz = C1PLAYERS[0].unk218 - arg0->unk8;
    dx = C1PLAYERS[0].unk210 - arg0->unk4;
    dy = C1PLAYERS[0].unk214 - arg0->unk6;
    ret = 0;
    if (((dz * dz) + ((dx * dx) + (dy * dy))) < arg1) {
        ret = 1;
    }
    if (ret) {
        ret = D_80755698[arg0->unk44] == 6;
        if (!ret) {
            ret = (arg0->unk46 & 0x20) != 0;
            if (!ret) {
                ret = mapChunkIsVisibleForPlayer(0, arg0->unk40) != 0;
            }
        }
    }
    return ret;
}

u8 spawnNodeActorInRangeAndVisible(SpawnNode *arg0, s32 arg1) {
    f32 dx;
    f32 dy;
    f32 dz;
    s32 ret;

    dz = C1PLAYERS[0].unk218 - arg0->unk18->unk84;
    dx = C1PLAYERS[0].unk210 - arg0->unk18->unk7C;
    dy = C1PLAYERS[0].unk214 - arg0->unk18->unk80;
    ret = 0;
    if (((dz * dz) + ((dx * dx) + (dy * dy))) < arg1) {
        ret = 1;
    }
    if (ret) {
        ret = (arg0->unk18->unk5C & 0x40) != 0;
        if (!ret) {
            ret = (arg0->unk46 & 0x20) != 0;
            if (!ret) {
                ret = mapChunkIsVisibleForPlayer(0, arg0->unk40) != 0;
            }
        }
    }
    return ret;
}

u8 spawnNodeActorOutOfRangeOrHidden(SpawnNode *arg0, s32 arg1) {
    f32 dx;
    f32 dy;
    f32 dz;
    s32 ret;

    dz = C1PLAYERS[0].unk218 - arg0->unk18->unk84;
    dx = C1PLAYERS[0].unk210 - arg0->unk18->unk7C;
    dy = C1PLAYERS[0].unk214 - arg0->unk18->unk80;
    ret = arg1 < (dz * dz) + ((dx * dx) + (dy * dy));
    dx = 0.0f; // FAKE: dead store kills the store-forwarding of the compare into the ret test (ret stays v1, bnezl)
    if (ret == 0) {
        ret = (arg0->unk18->unk5C & 0x40) == 0;
        if (ret != 0) {
            ret = (arg0->unk46 & 0x20) == 0;
            if (ret != 0) {
                ret = mapChunkIsVisibleForPlayer(0, arg0->unk40) == 0;
            }
        }
    }
    return ret;
}

u8 spawnNodeActorOutOfRangeScaled(SpawnNode *arg0, s32 arg1) {
    f32 dz;
    f32 dx;
    f32 r;
    s32 t;
    s32 ret;

    r = sqrtf(arg1);
    ret = (arg0->unk18->unk5C & 2) != 0;
    if (ret) {
        ret = (arg0->unk46 & 0x20) == 0;
        if (ret) {
            ret = arg0->unk12 == 2;
            if (ret) {
                t = (s32)(r * 1.5);
                dz = C1PLAYERS[0].unk218 - arg0->unk18->unk84;
                dx = C1PLAYERS[0].unk210 - arg0->unk18->unk7C;
                r = C1PLAYERS[0].unk214 - arg0->unk18->unk80;
                ret = (f32)(t * t) < ((dz * dz) + ((dx * dx) + (r * r)));
            }
        }
    }
    return ret;
}

typedef struct C1Entry24 {
    /* 0x00 */ u8 pad0[0x18];
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 pad19[3];
    /* 0x1C */ void *unk1C;
    /* 0x20 */ u8 unk20;
    /* 0x21 */ u8 pad21[3];
} C1Entry24; // size = 0x24

typedef struct C1Entry24List {
    /* 0x0 */ s16 count;
    /* 0x2 */ u8 pad2[2];
    /* 0x4 */ C1Entry24 *unk4;
} C1Entry24List;

typedef struct C1Holder {
    /* 0x00 */ u8 pad0[0xE];
    /* 0x0E */ u8 unkE;
    /* 0x0F */ u8 padF[0xD];
    /* 0x1C */ C1Entry24 *unk1C;
} C1Holder;

#define C1TBL ((C1Entry24List *)D_80755690)

void zoneAssignToBehaviour(C1Holder *arg0) {
    s16 i;
    C1Entry24 *entry;

    entry = C1TBL->unk4;
    i = 0;
    if (C1TBL->count > 0) {
        do {
            entry->unk1C = 0;
            entry->unk20 = 0;
            if (entry->unk18 == arg0->unkE) {
                arg0->unk1C = entry;
                break;
            }
            i++;
            entry++;
        } while (i < C1TBL->count);
    }
    if (arg0->unk1C == 0) {
        arg0->unk1C = C1TBL->unk4;
    }
}



typedef struct MidAS2 {
    u8 v[2];
} MidAS2;

typedef struct MidAS6 {
    s16 v[3];
} MidAS6;

typedef struct MidAS10 {
    s16 v[5];
} MidAS10;

typedef struct MidAS22 {
    s16 v[11];
} MidAS22;

typedef struct MidARec24 {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ u8 padA[2];
    /* 0x0C */ MidAS6 *unkC;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ u8 pad12[2];
    /* 0x14 */ MidAS10 *unk14;
    /* 0x18 */ s8 unk18;
    /* 0x19 */ s8 unk19;
    /* 0x1A */ u8 pad1A[0xA];
} MidARec24; // size = 0x24

typedef struct MidARec24List {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ u8 pad2[2];
    /* 0x4 */ MidARec24 *unk4;
} MidARec24List;

void spawnNodeListInitFromMap(s16 *arg0, MidARec24List *arg1, SpawnNodeList *arg2) {
    s32 t;
    s16 *src;
    s16 cnt;
    s16 *p;
    s16 *q;
    s16 j;
    void *mem;
    s32 same;
    SpawnNode *node;
    s16 i;
    s16 prev;
    MidARec24 *rec;
    s16 *r;

    src = arg0;
    if (src != NULL) {
        t = *src++;
        cnt = t;
        arg1->unk0 = t;
    } else {
        arg1->unk0 = 0;
        cnt = arg1->unk0;
    }
    rec = heapAlloc(cnt * 0x24);
    arg1->unk4 = rec;
    for (i = 0; i < arg1->unk0; i++) {
        same = 1;
        j = 0;
        if (i != 0) {
            rec++;
        }
        rec->unk0 = 0x7FFF;
        rec->unk2 = rec->unk0;
        rec->unk4 = -0x8000;
        rec->unk6 = rec->unk4;
        if (src != NULL) {
            t = *src++;
            cnt = t;
            rec->unk8 = t;
        } else {
            rec->unk8 = 0;
            cnt = rec->unk8;
        }
        p = src;
        if (cnt != 0) {
            rec->unkC = heapAlloc(cnt * 6U);
        }
        if (cnt > 0) {
            do {
                rec->unkC[j] = *(MidAS6 *)p;
                p += 3;
                rec->unk0 = (rec->unk0 < rec->unkC[j].v[0]) ? rec->unk0 : rec->unkC[j].v[0];
                rec->unk2 = (rec->unk2 < rec->unkC[j].v[2]) ? rec->unk2 : rec->unkC[j].v[2];
                rec->unk4 = (rec->unkC[j].v[0] < rec->unk4) ? rec->unk4 : rec->unkC[j].v[0];
                rec->unk6 = (rec->unkC[j].v[2] < rec->unk6) ? rec->unk6 : rec->unkC[j].v[2];
                if (j == 0) {
                    prev = rec->unkC[j].v[1];
                } else {
                    if (prev != rec->unkC[j].v[1]) {
                        same = 0;
                    }
                    prev = rec->unkC[j].v[1];
                }
                j++;
            } while (j < cnt);
            j = 0;
        }
        src = p;
        if (src != NULL) {
            t = *src++;
            cnt = t;
            rec->unk10 = t;
        } else {
            rec->unk10 = 0;
            cnt = rec->unk10;
        }
        q = src;
        if (cnt != 0) {
            rec->unk14 = heapAlloc(cnt * 10U);
        }
        if (cnt > 0) {
            do {
                rec->unk14[j] = *(MidAS10 *)q;
                j++;
                q += 5;
            } while (j < cnt);
        }
        src = q;
        if (src != NULL) {
            rec->unk18 = *src++;
            rec->unk19 = *src++;
            if (same != 0) {
                rec->unk19 = 1;
            }
        }
    }
    i = 0;
    if (src != NULL) {
        t = *src++;
        arg2->count = t;
        cnt = t;
    } else {
        arg2->count = 0;
        cnt = 0;
    }
    mem = heapAlloc(cnt * 0x48);
    arg2->nodes = mem;
    heapClearBlock(mem);
    r = src;
    node = arg2->nodes;
    for (; i < arg2->count; i++) {
        j = 0;
        if (i != 0) {
            node++;
        }
        *(MidAS22 *)node = *(MidAS22 *)r;
        r += 11;
        node->unk42 = node->unk12;
        node->unk44 = node->unk0;
        node->unk18 = 0;
        node->unk46 = 0;
        node->unk24 = 0;
        node->unk43 = 0;
        node->unk3C = 0.0f;
        node->unk40 = mapChunkFindByPosition((f32)node->unk4, (f32)node->unk6, (f32)node->unk8, 0);
        node->unk20 = heapAlloc(node->unk11 * 2);
        q = r;
        if (node->unk11 > 0) {
            do {
                ((MidAS2 *)node->unk20)[j] = *(MidAS2 *)q;
                j++;
                q += 1;
            } while (j < node->unk11);
        }
        r = q;
        zoneAssignToBehaviour((C1Holder *)node);
    }
}

void animSetLoopLimit(void *, s32, s32);
void animSetFinished(void *, s32, s32);
void animSetFrameAndSubframe(void *, s32, s32, f32);
void animSetSpeed(void *, s32, f32);
void animSetLoopMode(void *, s32, s32);
void animSetDirection(void *, s32, s32);
void animSetEndFrame(void *, s32, s32);
void animClearStartFrame(void *, s32);
s32 animIsPlaying(void *, s32);
extern u32 gFrameCounter;


u8 func_8072881C(u8 arg0, u32 *arg1) {
    u8 ret;

    ret = 0;
    if ((arg0 & 0x80) || (((*arg1 + 0x32) < gFrameCounter) && (((randomNonNegative() >> 0xF) % 1000) >= 0x3C1) && (animIsPlaying(gCurrentActor, arg0) == 0))) {
        arg0 &= 0x7F;
        animSetSpeed(gCurrentActor, arg0, 1.0f);
        animSetLoopMode(gCurrentActor, arg0, 1);
        animSetDirection(gCurrentActor, arg0, 0);
        animSetEndFrame(gCurrentActor, arg0, 3);
        animClearStartFrame(gCurrentActor, arg0);
        animSetFrameAndSubframe(gCurrentActor, arg0, 0, 0.0f);
        animSetLoopLimit(gCurrentActor, arg0, 2);
        *arg1 = gFrameCounter;
        ret = 1;
    }
    return ret;
}


void func_80728950(u8 arg0) {
    animSetLoopLimit(gCurrentActor, arg0, 1);
    animSetFinished(gCurrentActor, arg0, 1);
    animSetFrameAndSubframe(gCurrentActor, arg0, 2, 0.0f);
}

void currentActorAnimSetFrame(u8 frame, u8 subframe) {
    animSetFrameAndSubframe(gCurrentActor, frame, subframe, 0.0f);
}

typedef struct A2PtrPair {
    void *p[2];
} A2PtrPair;

typedef struct A2BytePair {
    u16 w;
} A2BytePair;

typedef struct A2B44 {
    /* 0x00 */ u8 pad0[0x7C];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
    /* 0x84 */ u8 pad84[0xDB];
    /* 0x15F */ u8 unk15F;
    /* 0x160 */ f64 unk160;
} A2B44;

extern A2PtrPair D_80755794;
extern u16 D_8075579C;
extern u8 D_8071FB34[];
extern u8 D_8071FB54[];
extern u8 D_8071FC0C[];
extern u8 D_8071FC40[];
extern u8 D_8071FC58[];
extern u8 D_8071FFA0[];
extern void *D_8074E880[];
extern s32 gCamActor;
#define A2B44V ((A2B44 *)gSpawnedActor)

u32 randomLcgNext(void);
void sfxPlayOnFreeSlot(s32, s32, f32, f32, s32, s32);
void actorScriptStart(void *, s32);
void camStartShake(s32, s32, s32);
void tagBarrelSpawnSmokeAndPuffs(f32, f32, f32, f32, u8, u8);
void effectSpawnDebrisParticles(void *, f32, f32, f32, f32);
void func_8068B80C(void);
void func_8071495C(void);
void func_80714950(s32);
void func_8071496C(s16);
void func_8071498C(void *);
void func_80714998(u8);
void func_807149A8(s32);
void func_807149B8(s32);
void func_807149C8(s32, s32, s32, s32);
void func_807149FC(s32);
void func_80714A28(s32);
s32 func_80714CC0(void *, f32, f32, f32, f32);
void effectPuffRiseUpdate(void);
void effectConfettiPhysicsUpdate(void);
void func_80717D4C(void);
void effectWobbleRiseUpdate(void);
void actorSpawnEffectChild(f32, f32, f32, f32, f32, void *, u8);
void effectSpawnBoneDefault(void *, s16, f32, f32, f32, f32, s32);
void effectSpawnMultiTierRing(f32, s32, f32, f32, f32);

void zoneEntrySpawnEffect(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    Zone *group;
    s16 x;
    s16 y;
    s16 z;
    s16 i;
    f32 ox0;
    f32 oy0;
    f32 oz0;
    A2PtrPair fx6;
    u8 idx6[2];
    u8 sel6;
    s16 ex6;
    s16 ez6;
    s16 ang6;
    f32 scale8;
    f32 kx8;
    f32 kz8;
    s32 rnd10;
    f32 ox10;
    f32 oy10;
    s8 jx;
    s8 jy;
    s8 jz;
    f32 kx14;
    f32 ky14;
    f32 kz14;

    group = D_80755690->unk4;
    x = group->unk14[arg1].unk0;
    y = group->unk14[arg1].unk2;
    z = group->unk14[arg1].unk4;
    switch (arg0) {
        case 0:
            for (i = 0; i < arg3; i++) {
                ox0 = (f32)((randomNonNegative() >> 0xF) % 0x8000 % 40 - 20.0);
                oy0 = (f32)((randomNonNegative() >> 0xF) % 0x8000 % 20);
                oz0 = (f32)((randomNonNegative() >> 0xF) % 0x8000 % 40 - 20.0);
                func_807149C8(0xE6, 0xE6, 0xE6, 0xC8);
                func_8071498C(func_80717D4C);
                func_80714950(-(i * 20));
                func_807149B8(1);
                func_80714998(arg2);
                func_80714CC0(D_8071FFA0, 1.5f, (f32)x + ox0, (f32)y + oy0, (f32)z + oz0);
            }
            return;
        case 7:
            break;
        case 1:
            effectSpawnMultiTierRing(0.36f, 1, (f32)x, (f32)(y + 5), (f32)z);
            camStartShake(gCamActor, 0x14, 0xF);
            return;
        case 2:
            func_8068B80C();
            return;
        case 3:
            actorSpawnEffectChild((f32)x, (f32)y, (f32)z, arg2 * 0.01, arg3 * 0.01, NULL, 0);
            return;
        case 4:
            tagBarrelSpawnSmokeAndPuffs((f32)x, (f32)y, (f32)z, arg2 * 0.01, 0, 0);
            return;
        case 5:
            if (arg2 != 0x14) {
                actorSpawn(0x104, 0);
                A2B44V->unk160 = arg3;
            }
            switch (arg2) {
                case 0:
                    A2B44V->unk7C = 450.0f;
                    A2B44V->unk80 = 500.0f;
                    A2B44V->unk15F = 0x14;
                    break;
                case 1:
                    A2B44V->unk7C = 820.0f;
                    A2B44V->unk80 = 500.0f;
                    A2B44V->unk15F = 0x15;
                    break;
                case 10:
                    sfxPlayOnFreeSlot(0x3F3, 0x7FFF, 63.0f, 1.0f, 0, 0);
                    A2B44V->unk15F = 0;
                    A2B44V->unk7C = 500.0f;
                    A2B44V->unk80 = 80.0f;
                    break;
                case 11:
                    sfxPlayOnFreeSlot(0x3F4, 0x7FFF, 63.0f, 1.0f, 0, 0);
                    A2B44V->unk15F = 0x89;
                    A2B44V->unk7C = 600.0f;
                    A2B44V->unk80 = 80.0f;
                    break;
                case 12:
                    sfxPlayOnFreeSlot(0x3F4, 0x7FFF, 63.0f, 1.0f, 0, 0);
                    A2B44V->unk15F = 0x47;
                    A2B44V->unk7C = 600.0f;
                    A2B44V->unk80 = 80.0f;
                    break;
                case 13:
                    A2B44V->unk15F = 0x23;
                    A2B44V->unk7C = 600.0f;
                    A2B44V->unk80 = 80.0f;
                    break;
                case 20:
                    actorSpawn(0x92, 0x73);
                    actorScriptStart(gSpawnedActor, 0x42A);
                    return;
                case 30:
                case 31:
                case 32:
                case 33:
                case 34:
                case 35:
                    A2B44V->unk15F = arg2;
                    A2B44V->unk7C = 500.0f;
                    A2B44V->unk80 = 80.0f;
                    break;
            }
            break;
        case 15:
            actorSpawn(0x92, 0x73);
            actorScriptStart(gSpawnedActor, 0x42A);
            return;
        case 6:
            for (i = 0; i < arg3; i++) {
                fx6 = D_80755794;
                *(A2BytePair *)idx6 = *(A2BytePair *)&D_8075579C;
                sel6 = (randomNonNegative() >> 0xF) % 2;
                ex6 = ((ZoneEntry *)(group->unk14 + arg2))->unk0;
                ez6 = ((ZoneEntry *)(group->unk14 + arg2))->unk4;
                ang6 = mathAngleBetweenPoints2D((f32)ex6, (f32)ez6, (f32)x, (f32)z);
                func_807149B8(1);
                func_807149FC(idx6[sel6]);
                func_8071498C(effectConfettiPhysicsUpdate);
                func_80714950((ang6 << 16) + 3);
                func_80714CC0(((void **)&fx6)[sel6], (f32)((randomNonNegative() >> 0xF) % 1000 * 0.0005 + 0.2), (f32)x, (f32)(y + 10), (f32)z);
            }
            return;
        case 12:
            func_807149A8(0x7D0);
            func_80714998(1);
            func_80714CC0(D_8071FC0C, arg2 * 0.01, (f32)x, (f32)y, (f32)z);
            return;
        case 8:
            scale8 = arg2 * 0.01;
            for (i = 0; i < arg3; i++) {
                kx8 = ((randomNonNegative() >> 0xF) % 0x8000 % 40 - 20.0) * scale8;
                kz8 = ((randomNonNegative() >> 0xF) % 0x8000 % 40 - 20.0) * scale8;
                func_807149A8(0x7D0);
                func_807149B8(1);
                func_80714CC0(D_8071FB54, scale8 * 1.3, (f32)x + kx8, (f32)y, (f32)z + kz8);
                func_807149C8(0xD2, 0xD2, 0xD2, 0xC8);
                effectSpawnBoneDefault(NULL, 0, scale8 * 1.2, (f32)x + kx8, (f32)y, (f32)z + kz8, -0xB4);
            }
            return;
        case 9:
            for (i = 0; i < arg2; i++) {
                func_80714998(2);
                func_8071498C(effectPuffRiseUpdate);
                func_807149B8(1);
                func_80714950(1);
                func_8071496C(i * 3);
                func_80714CC0(D_8074E880[(randomNonNegative() >> 0xF) % 1000 % 3], arg3 * 0.01, (f32)x, (f32)y, (f32)z);
            }
            return;
        case 10:
            for (i = 0; i < arg2; i++) {
                rnd10 = randomNonNegative() >> 0xF;
                ox10 = (f32)(rnd10 % 300);
                oy10 = (f32)((randomNonNegative() >> 0xF) % 200);
                func_8071495C();
                func_80714CC0(D_8071FB34, arg3 * 0.01, ox10, oy10, -10.0f);
            }
            return;
        case 11:
            for (i = 0; i < arg2; i++) {
                jx = (randomLcgNext() / 10000 % 200) / 10.0 - 10.0;
                jy = (randomLcgNext() / 10000 % 200) / 10.0 - 7.0;
                jz = (randomLcgNext() / 10000 % 200) / 10.0 - 10.0;
                func_807149B8(1);
                func_807149FC(2);
                func_80714950(0x64);
                func_8071498C(func_80717D4C);
                func_8071496C(i / 7);
                func_80714CC0(D_8071FC58, arg3 * 0.01, (f32)(x + jx), (f32)(y + jy), (f32)(z + jz));
            }
            return;
        case 13:
            effectSpawnDebrisParticles(NULL, arg2 * 0.01, (f32)x, (f32)y, (f32)z);
            return;
        case 14:
            for (i = 0; i < arg2; i++) {
                kx14 = (f32)(randomLcgNext() / 10000 % 200) / 10.0 - 5.0;
                ky14 = (f32)(randomLcgNext() / 10000 % 200) / 10.0 - 5.0;
                kz14 = (f32)(randomLcgNext() / 10000 % 200) / 10.0 - 5.0;
                func_807149B8(1);
                func_80714950(2);
                func_807149FC(-1);
                func_8071498C(effectWobbleRiseUpdate);
                func_80714A28(4);
                func_80714CC0(D_8071FC40, 0.0f, (f32)x + kx14, (f32)y + ky14, (f32)z + kz14);
            }
            break;
    }
}



void func_80729AA4(u8 arg0) {
    Actor *a;

    a = spawnNodeActivate(arg0, 0);
    if (a == 0) {
        a = D_807FBB4C;
    }
    a->unk6A |= 0x100;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/1295B0/D_8075EB80.s")

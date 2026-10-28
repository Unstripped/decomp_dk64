#include "common.h"
#include "actor.h"
#include "cutscene.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB4C;
extern ActorGlobalState D_807FBB70;
extern u8 D_807FBD70;
extern f32 D_807F621C;
extern f32 D_807F6220;
extern f32 D_807F6224;
extern CsPlayer *D_807FC924;

extern u8 D_8071FF18[];
extern u8 D_8071FFA0[];
s32 func_806119A0(void);
void func_80714950(s32);
void func_8071498C(void *);
void func_80717D4C(void);
void func_80714998(s32);
void func_807149B8(s32);
void func_807149C8(s32, s32, s32, s32);
void func_80714B84(void *, f32, s16, s32, s32);
s32 func_80714CC0(void *, f32, f32, f32, f32);

void func_80642BF0(CsState *cs, s16 csId, s16 b, s16 c) {
    func_80714B84(D_8071FF18, 0.3f, csId, 1, 0);
    func_80714B84(D_8071FF18, 0.3f, csId, 2, 0);
    func_80714B84(D_8071FF18, 0.3f, csId, 3, 0);
}

typedef struct CsB0SlotAnim {
    /* 0x00 */ u8 pad0[0x2D];
    /* 0x2D */ u8 unk2D;
} CsB0SlotAnim;
typedef struct CsB0Slot {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 w;
    /* 0x10 */ u8 pad10[0x68];
    /* 0x78 */ CsB0SlotAnim *unk78;
    /* 0x7C */ u8 pad7C[0x14];
} CsB0Slot; /* 0x90 */
extern CsB0Slot *D_807F6000;
s32 hashTableLookup();
void modelSlotGetNodePos(s16, s32, s32, f32 *, f32 *, f32 *);

void func_80642C78(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 i;
    u8 type;
    f32 x;
    f32 y;
    f32 z;

    type = D_807F6000[(s16)hashTableLookup(csId)].unk78->unk2D;
    if (type == 0xD || type == 0x15 || type == 0x19) {
        for (i = 1; i != 0xF; i++) {
            modelSlotGetNodePos(csId, 1, i, &x, &y, &z);
            func_807149B8(1);
            func_80714998(2);
            func_80714950(-(s32)((u32)func_806119A0() / 10000 % 50) - 0x14);
            func_807149C8(0xE1, 0x87, 0x38, 0xFF);
            func_8071498C(func_80717D4C);
            func_80714CC0(D_8071FF18, 0.5f, x, y + 2.0f, z);
        }
    }
}

void *func_80610FE8(s32);
void lightAdd(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32);

void func_80642E34(CsState *cs, s16 csId, s16 b, s16 c) {
    f32 x;
    f32 y;
    f32 z;
    s32 *p;
    f32 t;
    s32 g;

    if (*(s32 **)cs == NULL) {
        *(s32 **)cs = func_80610FE8(4);
        **(s32 **)cs = b;
    }
    p = *(s32 **)cs;
    t = (20.0 - *p) / 20.0;
    if (t > 0.7) {
        t = 1.0f;
    }
    modelSlotGetNodePos(csId, 1, 1, &x, &y, &z);
    g = (u32)func_806119A0() / 10000 % 200 + 0x37;
    lightAdd(x, y, z, 0.0f, 0.0f, 0.0f, t * 200.0, 0, 0, g, (u32)func_806119A0() / 10000 % 80 + 0xAF);
    (*p)++;
    if (*p == 0x14) {
        *p = 0;
    }
}

typedef struct CsB0Bounce {
    /* 0x0 */ f32 vy;
    /* 0x4 */ f32 angle;
    /* 0x8 */ f32 speed;
    /* 0xC */ f32 padC;
} CsB0Bounce;
extern f32 D_807F6234;
u8 collisionCheckGroundAtPoint(f32, f32, f32 *);
f32 func_80612790(s16);
f32 func_80612794(s16);

void func_80642FC4(CsState *cs, s16 csId, s16 b, s16 c) {
    CsB0Bounce *p;
    u8 hit;
    f32 groundY;
    CsB0Bounce *n;

    if (*(CsB0Bounce **)cs == NULL) {
        n = func_80610FE8(0x10);
        *(CsB0Bounce **)cs = n;
        n->vy = 7.0f;
        n->angle = (u32)func_806119A0() / 10000 % 1548 + 0x5DC;
        n->speed = (u32)func_806119A0() / 10000 % 100 / 40.0 + 2.5;
        D_807F6234 = (u32)func_806119A0() / 10000 % 100 / 500.0 + 0.14;
    }
    p = *(CsB0Bounce **)cs;
    groundY = D_807F6220;
    hit = collisionCheckGroundAtPoint(D_807F621C, D_807F6224, &groundY);
    p->vy = p->vy + -0.64;
    D_807F621C += p->speed * func_80612794(p->angle);
    D_807F6224 += p->speed * func_80612790(p->angle);
    if (p->vy < -10.0f) {
        p->vy = -10.0f;
    }
    D_807F6220 += p->vy;
    if (hit != 0 && D_807F6220 < groundY) {
        p->vy = (0.0 - p->vy) * 0.7;
        D_807F6220 = groundY;
    }
}

extern u32 D_8076A064;

void func_80643274(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 idx;

    if (D_8076A064 % c == 0) {
        idx = (u32)func_806119A0() / 10000 % b + 1;
        func_807149C8(0xFF, 0xFF, 0xFF, 0x64);
        func_80714950(-0x78);
        func_8071498C(func_80717D4C);
        func_807149B8(1);
        func_80714998(3);
        func_80714B84(D_8071FFA0, 1.5f, csId, idx, 0);
    }
}

typedef struct CsB0Point3f {
    f32 x, y, z;
} CsB0Point3f;
extern CsB0Point3f **D_807F5FD4;

void func_80643354(s32 a, s32 b, u32 c) {
    s32 idx;
    CsB0Point3f *p;

    if (D_8076A064 % c == 0) {
        idx = (u32)func_806119A0() / 10000 % b;
        func_807149C8(0xFF, 0xFF, 0xFF, 0x64);
        func_80714950(-0x78);
        func_8071498C(func_80717D4C);
        func_807149B8(1);
        func_80714998(3);
        p = *D_807F5FD4 + idx;
        func_80714CC0(D_8071FFA0, 1.5f, p->x, p->y, p->z);
    }
}

#ifdef NON_MATCHING
void lightSetRadius(s32);

void func_80643440(CsState *cs, s16 csId, s16 b, s16 c) {
    s16 *ang;
    CsB0Point3f *p;
    f32 fy;
    f32 sn;

    if (*(s16 **)cs == NULL) {
        ang = func_80610FE8(2);
        *(s16 **)cs = ang;
        *ang = 0;
    }
    ang = *(s16 **)cs;
    sn = func_80612794(*ang);
    p = D_807F5FD4[1];
    fy = p[0].y + (sn * 0.5 + 0.5) * (p[1].y - p[0].y);
    lightSetRadius(0x5DC);
    p = D_807F5FD4[1];
    lightAdd(p[0].x, fy, p[0].z, 0.0f, 0.0f, 0.0f, 500.0f, 0, 0xFF, 0xFF, 0xFF);
    sn = func_80612794(*ang + 0x514);
    p = D_807F5FD4[1];
    fy = p[2].y + (sn * 0.5 + 0.5) * (p[3].y - p[2].y);
    lightSetRadius(0x5DC);
    p = D_807F5FD4[1];
    lightAdd(p[2].x, fy, p[2].z, 0.0f, 0.0f, 0.0f, 500.0f, 0, 0xFF, 0xFF, 0xFF);
    sn = func_80612794(*ang + 0xA28);
    p = D_807F5FD4[1];
    fy = (sn * 0.5 + 0.5) * (p[5].y - p[4].y) + p[4].y;
    lightSetRadius(0x5DC);
    p = D_807F5FD4[1];
    lightAdd(p[4].x, fy, p[4].z, 0.0f, 0.0f, 0.0f, 500.0f, 0, 0xFF, 0xFF, 0xFF);
    *ang += 0x32;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80643440.s")
#endif

void func_806436A4(CsState *cs, s16 csId, s16 b, s16 c) {
    func_80643354(0, b, c);
}

typedef struct CsB0Cursor {
    /* 0x0 */ s32 timer;
    /* 0x4 */ s32 idx;
} CsB0Cursor;
extern u8 D_8071FB54[];
void func_8071C004(void);

void func_806436E0(CsState *cs, s16 csId, s16 b, s16 c) {
    CsB0Cursor *st;
    s32 idx;
    s32 x;
    s32 y;
    s32 z;

    if (*(CsB0Cursor **)cs == NULL) {
        st = func_80610FE8(8);
        *(CsB0Cursor **)cs = st;
        st->timer = 0;
        st->idx = 0;
    }
    st = *(CsB0Cursor **)cs;
    if (st->timer == 0) {
        s32 len = D_807F5FD4[1] - D_807F5FD4[0];
        idx = ++st->idx;
        if (len == idx) {
            st->idx = 0;
            idx = 0;
        }
        x = (*D_807F5FD4)[idx].x;
        y = (*D_807F5FD4)[idx].y;
        z = (*D_807F5FD4)[idx].z;
        func_80714998(2);
        func_807149B8(1);
        func_80714950(0);
        func_8071498C(func_8071C004);
        func_80714CC0(D_8071FB54, 0.667f, x, y + 10, z);
        st->timer = 0x19;
    }
    st->timer--;
}

void func_8067DF44(f32, f32, f32, f32, u8, u8);

void func_8064384C(CsState *cs, s16 csId, s16 b, s16 c) {
    CsB0Slot *slot = &D_807F6000[hashTableLookup(csId)];
    func_8067DF44(slot->x, slot->y, slot->z, slot->w, 0, 1);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_806438B8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80643B24.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80643C0C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80643F38.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064409C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064431C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_806443E4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_806449C0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80644A18.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80644CC0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80644D50.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80644E2C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80644EC8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_806450C0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80645238.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80645614.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80645700.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_806458C8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80645A64.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80645B9C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80645C04.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80645D14.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80645F40.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80646058.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80646770.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80646978.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80646DC4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80647108.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80647170.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80647218.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80647508.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80647610.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064774C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80647834.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80647A14.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80647B74.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80647CF4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80647D7C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80648000.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064826C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_806485A0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_806487C4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80648C50.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80648C84.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064911C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_806491F4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_806493C4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064954C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_806496B0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80649BF0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80649D74.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80649E00.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80649E34.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80649F64.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80649FC0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064A180.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064A194.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064A258.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064A804.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064AAC4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064AB1C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064AC28.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064B118.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064B150.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064B190.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064B204.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064B260.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064B2AC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064B370.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064B3F8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064B4AC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064B514.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064B574.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064B5A4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064B798.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064B7C0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064B7D4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064B7E8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064B828.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064B868.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064B900.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064B9E0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064BAF4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064BB4C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064BB78.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064BBD8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064BCB0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064BD2C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064BE58.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064BE80.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064BF58.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064BFD0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064C134.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064C250.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064C3E8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064C544.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064C644.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064C708.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064C814.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064C9F8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064CB3C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064CC80.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064CD3C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064D0C4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064D1E8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064D418.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064D880.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064D978.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064DB98.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064DE04.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064DF5C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064E174.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064E428.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064E48C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064E4F8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064E55C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064E5C0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064E65C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064EA48.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064EAB4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064EB3C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064EB9C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064EC04.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064EC60.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064ED68.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064EE08.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064F028.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064F1C4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064F210.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064F2F0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064F308.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064F358.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064F404.s")

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
void func_80714998(u8);
void func_807149B8(u8);
void func_807149C8(s32, s32, s32, s32);
void func_80714B84(void *, f32, s32, s32, s32);
s32 func_80714CC0(void *, f32, f32, f32, f32);
void *func_80610FE8(s32);
void lightAdd(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32);
u8 collisionCheckGroundAtPoint(f32, f32, f32 *);
f32 func_80612790(s16);
f32 func_80612794(s16);
extern u32 D_8076A064;
typedef struct CsB0Point3f {
    f32 x, y, z;
} CsB0Point3f;
extern CsB0Point3f **D_807F5FD4;
void lightSetRadius(s32);


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
void modelSlotGetNodePos(s32, s32, s32, f32 *, f32 *, f32 *);

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

extern u8 D_8071FE08[];
extern u8 D_8071FE64[];
extern u8 D_8071FE88[];
extern u8 D_8071FEAC[];
void func_807149FC(s32);
void func_8071910C();
void func_8071A8B0();

void func_806438B8(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 i;
    s32 r;
    s32 q;
    f32 x;
    f32 y;
    f32 z;

    if (b == 1) {
        modelSlotGetNodePos(csId, 1, c, &x, &y, &z);
    } else {
        x = D_807F621C;
        y = D_807F6220;
        z = D_807F6224;
    }
    func_807149B8(0);
    func_807149FC(1);
    func_80714950(0x100C8);
    func_8071498C(func_8071A8B0);
    func_80714CC0(D_8071FE08, 1.5f, x, y, z);
    for (i = 0; i != 7; i++) {
        r = (s32)((u32)func_806119A0() / 10000) % 3;
        func_807149B8(1);
        func_807149FC(10);
        func_8071498C(func_8071910C);
        func_80714998(2);
        func_80714950(7);
        switch (r) {
            case 0:
                func_80714CC0(D_8071FE64, 0.5f, x, y, z);
                break;
            case 1:
                func_80714CC0(D_8071FE88, 0.5f, x, y, z);
                break;
            case 2:
                func_80714CC0(D_8071FEAC, 0.5f, x, y, z);
                break;
        }
    }
}


void func_80643B24(CsState *cs, s16 csId, s16 b, s16 c) {
    if ((D_8076A064 % 5) == 0) {
        func_80714950(-0x78);
        func_8071498C(func_80717D4C);
        func_807149B8(1);
        func_80714998(3);
        func_807149C8(0xFF, 0xFF, 0xFF, 0x96);
        func_80714B84(D_8071FFA0, 1.0f, csId, 1, 0);
        func_80714950(-0x78);
        func_8071498C(func_80717D4C);
        func_807149B8(1);
        func_80714998(3);
        func_807149C8(0xFF, 0xFF, 0xFF, 0x96);
        func_80714B84(D_8071FFA0, 1.0f, csId, 2, 0);
    }
}


typedef struct {
    s32 *unk0;
    u8 pad4[0x45];
    u8 unk49;
} CsB1LightView;

extern u8 D_807201D4[];
void func_80717CE8();

#ifdef NON_MATCHING
void func_80643C0C(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 *p;
    s32 *q;
    s32 n;
    f64 t;
    f32 f;

    p = ((CsB1LightView *)cs)->unk0;
    if (p == NULL) {
        q = func_80610FE8(8);
        p = q;
        ((CsB1LightView *)cs)->unk0 = q;
    }
    if (b == 1) {
        *p = 0;
    }
    n = *p;
    *p = n + 1;
    t = (f32)(70 - n) / 70.0f;
    if (t > 0.5) {
        f = 1.0 - 2.0 * (t - 0.5);
    } else {
        f = 2.0 * t;
    }
    lightAdd(D_807F621C, D_807F6220, D_807F6224, 0.0f, 0.0f, 0.0f, 200.0f * f, 0, 0xFF,
             (u32)((-80.0f * f) + 255.0f), (u32)((-205.0f * f) + 255.0f));
    if (t > 0.6 && (D_8076A064 % 6) == 0) {
        func_807149FC(2);
        func_807149B8(1);
        func_80714950(-0x190);
        func_807149C8(0xFF, 0xFF, 0xFF, 1);
        func_8071498C(func_80717CE8);
        func_80714CC0(D_807201D4, 1.2f, D_807F621C, D_807F6220 + 30.0, D_807F6224);
    }
    if (t < 0.1) {
        ((CsB1LightView *)cs)->unk49 = 1;
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80643C0C.s")
#endif

extern void *D_8074E880[];
void func_8071496C(s16);
void func_8071EA24();

void func_80643F38(CsState *cs, s16 csId, s16 b, s16 c) {
    s16 i;

    for (i = 0; i < 30; i++) {
        func_807149B8(1);
        func_807149FC(1);
        func_8071498C(func_8071EA24);
        func_8071496C(i / 7);
        func_80714CC0(D_8074E880[i % 3], 1.4f, D_807F621C, D_807F6220, D_807F6224);
    }
}

typedef struct {
    u32 unk0;
    s32 unk4;
    s32 unk8;
} CsB1SfxState;

typedef struct {
    CsB1SfxState *unk0;
    u8 pad4[0xC];
    s16 unk10;
} CsB1SfxView;

void func_80605380(s16);
void modelSlotSetNodeFrame(s32, s16, s32, s32);
void sfxPlayFromTargetSlot(s16, s32, s32, s32, s32, s32, f32);
s16 sfxSlotAllocateSource(s16, s32, s32, s32, s32, f32, s32);

#ifdef NON_MATCHING
void func_8064409C(CsState *cs, s16 csId, s16 b, s16 c) {
    CsB1SfxState *p;
    CsB1SfxState *q;
    CsB1SfxState *t;
    s32 frame;

    p = ((CsB1SfxView *)cs)->unk0;
    if (p == NULL) {
        t = func_80610FE8(0xC);
        ((CsB1SfxView *)cs)->unk0 = t;
        t->unk0 = 0;
        t->unk4 = 0;
        p = ((CsB1SfxView *)cs)->unk0;
    }
    q = p;
    switch (p->unk0) {
        case 0:
            q->unk4++;
            if (q->unk4 == 4) {
                q->unk8 = 0;
                q->unk0++;
                if (((CsB1SfxView *)cs)->unk10 < 0) {
                    ((CsB1SfxView *)cs)->unk10 = sfxSlotAllocateSource(csId, 0x12C, 0x3C, 1, 0x64, 1.0f, 0);
                }
            }
            frame = q->unk4;
            break;
        case 1:
            q->unk4++;
            if (q->unk4 == 7) {
                q->unk4 = 4;
                q->unk8++;
                if (q->unk8 == 0x1E) {
                    q->unk8 = 0;
                    q->unk0++;
                    if (((CsB1SfxView *)cs)->unk10 >= 0) {
                        func_80605380(((CsB1SfxView *)cs)->unk10);
                        ((CsB1SfxView *)cs)->unk10 = -1;
                    }
                    sfxPlayFromTargetSlot(csId, 0x74, 0xFF, 0x7F, 0, 0x50, 0.3f);
                }
            }
            frame = q->unk4;
            break;
        case 2:
            q->unk4 = 7;
            q->unk8++;
            if (q->unk8 == 0x28) {
                q->unk8 = 0;
                q->unk0++;
                sfxPlayFromTargetSlot(csId, 0x74, 0xFF, 0x7F, 0, 0x50, 0.3f);
            }
            frame = q->unk4;
            break;
        case 3:
            q->unk4 = 8;
            q->unk8++;
            if (q->unk8 == 0x28) {
                q->unk8 = 0;
                q->unk0++;
                sfxPlayFromTargetSlot(csId, 0x75, 0xFF, 0x7F, 0, 0x50, 0.3f);
            }
            frame = q->unk4;
            break;
        case 4:
            frame = 9;
            q->unk4 = frame;
            break;
        default:
            frame = q->unk4;
            break;
    }
    modelSlotSetNodeFrame(csId, 1, frame, 0);
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064409C.s")
#endif

extern s16 D_807480D0;
extern s16 D_807480D4;
extern s16 D_807480D8;

void func_8064431C(CsState *cs, s16 csId, s16 b, s16 c) {
    f32 x1;
    f32 x0;
    f32 y1;
    f32 y0;
    f32 z1;
    f32 z0;

    modelSlotGetNodePos(csId, 1, 1, &x0, &y0, &z0);
    modelSlotGetNodePos(csId, 1, 2, &x1, &y1, &z1);
    lightAdd(x0, y0, z0, x1, y1, z1, 0.0f, 1, D_807480D0, D_807480D4, D_807480D8);
}

typedef struct CsB2Cam {
    /* 0x000 */ u8 pad0[0x1F0];
    /* 0x1F0 */ s32 unk1F0;
} CsB2Cam;

typedef struct CsB2Player {
    /* 0x000 */ u8 pad0[0x210];
    /* 0x210 */ f32 unk210;
    /* 0x214 */ f32 unk214;
    /* 0x218 */ f32 unk218;
    /* 0x21C */ u8 pad21C[0x290 - 0x21C];
    /* 0x290 */ s16 unk290;
} CsB2Player;

typedef struct CsB2Flicker {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ f32 unk4;
    /* 0x8 */ f32 unk8;
    /* 0xC */ f32 unkC;
} CsB2Flicker;

extern u8 D_807444EC;
extern f32 D_807480DC;
extern u8 D_8077058C;
extern u8 D_80770DC9;
extern f32 D_80770DCC;
extern f32 D_80770DD0;
extern f32 D_80770DD4;

s32 randomNonNegative(void);
void func_80608DA8(s32, u8, s32, s32, s32);
void func_80609140(s32, s32, f32, f32, s32, s32);
void func_80711410(f32, s32, f32, s32, f32);
void lightSetColor(f32, f32, f32, s32);

void func_806443E4(CsState *arg0, s16 arg1, s16 arg2, s16 arg3) {
    CsB2Flicker *f;
    f32 dist;
    f32 fade;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 ex;
    f32 ey;
    f32 ez;
    CsB2Flicker *n;
    CsB2Cam *cam;

    cam = D_807FBB4C->unk174;
    if (!(cam->unk1F0 & 0x20000000)) {
        if (*(CsB2Flicker **)arg0 == NULL) {
            n = func_80610FE8(0x10);
            *(CsB2Flicker **)arg0 = n;
            n->unk0 = 0;
            n->unk4 = 0.0f;
            n->unk8 = 0.0f;
            n->unkC = 0.0f;
        }
        f = *(CsB2Flicker **)arg0;
        dz = ((CsB2Player *)D_807FC924)->unk218 - D_807F6224;
        dx = ((CsB2Player *)D_807FC924)->unk210 - D_807F621C;
        dy = ((CsB2Player *)D_807FC924)->unk214 - D_807F6220;
        dist = sqrtf(dz * dz + (dx * dx + dy * dy));
        if (((CsB2Player *)D_807FC924)->unk290 == 0xE && D_807444EC != 1) {
            fade = 1.0f;
        } else if (((CsB2Player *)D_807FC924)->unk290 == 7) {
            fade = 0.0f;
        } else {
            ex = D_807F621C - 1714.0f;
            ey = D_807F6220 - 226.0f;
            ez = D_807F6224 - 3410.0f;
            dist -= sqrtf(ex * ex + ey * ey + ez * ez);
            if (dist < 0.0) {
                dist = 0.0f;
            }
            if (dist > 600.0f) {
                fade = 0.0f;
            } else {
                fade = 1.0 - dist / 600.0f;
            }
        }
        if (((CsB2Player *)D_807FC924)->unk290 == 0xE || (((CsB2Player *)D_807FC924)->unk290 == 0xB && dist < D_807480DC)) {
            func_80711410(2.9f, -0x1E, fade, 0xE, fade < 0.05 ? 0.05 : fade);
        } else {
            D_8077058C = 0;
        }
        if ((randomNonNegative() >> 15) % 50 == 15) {
            f->unk0 = 0x28;
        }
        if (f->unk0 != 0) {
            f->unk0--;
            if ((randomNonNegative() >> 15) % 10 == 5) {
                if (dist < 2200.0f) {
                    if (D_80770DC9 != 0) {
                        if (D_80770DD4 < 600.0f) {
                            func_80609140(0x9C, (s32)(((fade * 32767.0f * 60.0f / 255.0f) * (600.0 - D_80770DD4)) / 1000.0), D_80770DCC, 0.8f, 0x1E, (u32)D_80770DD0);
                        }
                    } else {
                        func_80608DA8(0x9C, (u32)(fade * 60.0f), 0x7F, 0x1E, (randomNonNegative() >> 15) % 3);
                    }
                }
                f->unk4 = 1.0f;
                f->unk8 = 1.0f;
                f->unkC = 1.0f;
            }
        }
        f->unk4 = (0.4 - f->unk4) * 0.2 + f->unk4;
        f->unk8 = (0.3 - f->unk8) * 0.2 + f->unk8;
        f->unkC = (0.3 - f->unkC) * 0.2 + f->unkC;
        lightSetColor(f->unk4, f->unk8, f->unkC, 0xE);
    }
}

extern u8 D_8071FBC8[];

void func_806449C0(CsState *arg0, s16 arg1, s16 arg2, s16 arg3) {
    func_80714998(2);
    func_807149B8(1);
    func_80714B84(D_8071FBC8, 1.5f, arg1, arg2, 1);
}

void func_80644A18(f32 *, s16, s16, f32);

#ifdef NON_MATCHING
f32 splineEvalCubic(f64, f32, f32, f32, f32);

void func_80644A18(f32 *arg0, s16 arg1, s16 arg2, f32 arg3) {
    f32 frac;
    s32 i;
    u8 idx[4];
    f32 px;
    f32 py;
    f32 pz;
    s32 d0;
    s32 d1;
    s32 d2;

    *arg0 -= arg3;
    if (*arg0 < 0.0f) {
        *arg0 = arg2;
    }
    i = *arg0;
    frac = *arg0 - i;
    idx[0] = i - 1 < 0 ? 0 : i - 1;
    idx[1] = i;
    idx[2] = i + 1 >= arg2 ? arg2 - 1 : i + 1;
    idx[3] = i + 2 >= arg2 ? arg2 - 1 : i + 2;
    px = splineEvalCubic(frac, D_807F5FD4[arg1][idx[0]].x, D_807F5FD4[arg1][idx[1]].x, D_807F5FD4[arg1][idx[2]].x, D_807F5FD4[arg1][idx[3]].x);
    py = splineEvalCubic(frac, D_807F5FD4[arg1][idx[0]].y, D_807F5FD4[arg1][idx[1]].y, D_807F5FD4[arg1][idx[2]].y, D_807F5FD4[arg1][idx[3]].y);
    lightAdd(px, py, splineEvalCubic(frac, D_807F5FD4[arg1][idx[0]].z, D_807F5FD4[arg1][idx[1]].z, D_807F5FD4[arg1][idx[2]].z, D_807F5FD4[arg1][idx[3]].z), 0.0f, 0.0f, 0.0f, 250.0f, 0, 0xFF, 0xFF, 0xFF);
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80644A18.s")
#endif

void func_80644CC0(CsState *arg0, s16 arg1, s16 arg2, s16 arg3) {
    f32 *p;
    f32 *n;

    if (*(f32 **)arg0 == NULL) {
        n = func_80610FE8(8);
        *(f32 **)arg0 = n;
        n[0] = 0.0f;
        n[1] = 0.0f;
    }
    p = *(f32 **)arg0;
    func_80644A18(p, 2, 0x16, 1.0f);
    func_80644A18(p + 1, 4, 0x18, 0.8f);
}

void lightSetFovAngles(f32, f32);
extern f32 D_807480E0;
extern f32 D_807480E4;

void func_80644D50(CsState *arg0, s16 arg1, s16 arg2, s16 arg3) {
    f32 x2;
    f32 x1;
    f32 y2;
    f32 y1;
    f32 z2;
    f32 z1;

    modelSlotGetNodePos(arg1, 1, 1, &x1, &y1, &z1);
    modelSlotGetNodePos(arg1, 1, 2, &x2, &y2, &z2);
    lightSetFovAngles(D_807480E0, D_807480E4);
    lightAdd(x1, y1, z1, x2, y2, z2, 0.0f, 1, D_807480D0, D_807480D4, D_807480D8);
}

void func_80717760(void);

void func_80644E2C(CsState *arg0, s16 arg1, s16 arg2, s16 arg3) {
    func_807149FC(-1);
    func_8071498C(func_80717760);
    func_80714950(0x50);
    func_80714CC0(D_8074E880[(randomNonNegative() >> 15) % 1000 % 3], 0.5f, D_807F621C, D_807F6220, D_807F6224);
}

void func_8071AADC(void);
extern u8 D_80720A7C[];

void func_80644EC8(CsState *arg0, s16 arg1, s16 arg2, s16 arg3) {
    s32 sel;

    if ((u32)func_806119A0() / 10000 % arg2 == 0) {
        sel = (u32)func_806119A0() / 10000 % arg3;
        func_80714998(2);
        func_80714950(0x10064);
        func_8071498C(func_8071AADC);
        func_807149C8(0xFF, 0xFF, 0xFF, 0xFF);
        func_80714CC0(D_80720A7C, 1.2f, D_807F5FD4[0][sel].x, D_807F5FD4[0][sel].y, D_807F5FD4[0][sel].z);
    }
    if ((u32)func_806119A0() / 10000 % arg2 == 0) {
        sel = (u32)func_806119A0() / 10000 % arg3;
        func_80714998(2);
        func_80714950(0x10064);
        func_8071498C(func_8071AADC);
        func_807149C8(0xFF, 0xFF, 0xFF, 0xFF);
        func_80714CC0(D_80720A7C, 1.2f, D_807F5FD4[1][sel].x, D_807F5FD4[1][sel].y, D_807F5FD4[1][sel].z);
    }
}

extern f32 D_807480E8;
extern u8 D_807480EF;
extern u8 D_80720CD8[];
void func_80718188(void);

void func_806450C0(CsState *cs, s16 csId, s16 b, s16 c) {
    u32 idx;
    f32 y;

    if ((func_806119A0() / 10000U) % 10U == 0) {
        idx = (func_806119A0() / 10000U) % (u32)c;
        y = D_807F5FD4[b][idx].y;
        if (collisionCheckGroundAtPoint(D_807F5FD4[b][idx].x, D_807F5FD4[b][idx].z, &y)) {
            func_80714950(y + 2.0);
            func_8071498C((void *)func_80718188);
            func_807149FC(-1);
            func_807149B8(1);
            func_807149C8(0xFF, 0xFF, 0xFF, D_807480EF);
            func_80714CC0(D_80720CD8, D_807480E8, D_807F5FD4[b][idx].x, D_807F5FD4[b][idx].y,
                          D_807F5FD4[b][idx].z);
        }
    }
}

extern u8 D_80720E44[];
extern u8 D_80720E5C[];
extern u8 D_80720E74[];
extern u8 D_80720E8C[];
void func_8071910C(void);
void func_8071A8B0(void);

void func_80645238(CsState *cs, s16 csId, s16 b, s16 c) {
    u32 r1;
    u32 r2;
    u32 r3;
    u8 *p;
    s32 i;
    s32 sel;
    f32 x;
    f32 z;
    f32 scale;

    for (i = 0; i < 20; i++) {
        sel = (s32)(func_806119A0() / 10000U) % 4;
        func_807149B8(1);
        func_807149FC(0x3C);
        func_8071498C((void *)func_8071910C);
        func_80714998(2);
        func_80714950(2);
        switch (sel) {
            case 0:
                p = D_80720E44;
                break;
            case 1:
                p = D_80720E5C;
                break;
            case 2:
                p = D_80720E74;
                break;
            case 3:
                p = D_80720E8C;
                break;
        }
        func_80714CC0(p, 0.5f, D_807F621C, D_807F6220, D_807F6224);
    }
    for (i = 0; i != 6; i++) {
        x = (f32)((func_806119A0() / 1000U) % 150U) - 75.0;
        z = (f32)((func_806119A0() / 1000U) % 150U) - 75.0;
        scale = (f32)((func_806119A0() / 1000U) % 50U - 25.0) / 50.0;
        if (i == 0) {
            func_80714950(0x100FA);
            func_8071498C((void *)func_8071A8B0);
        } else {
            func_80714950(-0xAA);
            func_8071498C((void *)func_80717D4C);
        }
        func_807149B8(1);
        func_80714998(3);
        func_807149C8(0xFF, 0xFF, 0xFF, 0x64);
        func_80714CC0(D_8071FFA0, scale + 3.5, D_807F621C + x, D_807F6220 + 30.0, D_807F6224 + z);
    }
}


void func_80645614(CsState *cs, s16 csId, s16 b, s16 c) {
    u32 sp24;

    if ((func_806119A0() / 10000U) % (u32)b == 0) {
        sp24 = (func_806119A0() / 10000U) % (u32)c;
        func_80714998(2);
        func_80714950(0x10064);
        func_8071498C(func_8071AADC);
        func_807149C8(0xFF, 0xFF, 0xFF, 0xFF);
        func_807149B8(1);
        func_80714B84(D_80720A7C, 0.5f, csId, sp24 + 1, 0);
    }
}

typedef struct CsB3Pair {
    f32 a;
    f32 b;
} CsB3Pair;

void func_807149A8(s32);
void func_805FF9AC(s32, s32, s32, s32);
extern u8 D_80720BC4[];
void func_8071E3EC(void);

void func_80645700(CsState *cs, s16 csId, s16 b, s16 c) {
    u32 idx;
    CsB3Pair *p;
    CsB3Pair *q;
    f32 f;

    if (*(CsB3Pair **)cs == NULL && c != 0) {
        q = func_80610FE8(8);
        *(CsB3Pair **)cs = q;
        q->a = 0.0f;
        q->b = 0.0f;
    }
    p = *(CsB3Pair **)cs;

    idx = (func_806119A0() / 10000U) % (u32)b;
    func_807149B8(1);
    func_80714998(3);
    func_80714950(3);
    func_8071498C((void *)func_8071E3EC);
    func_807149A8(0x7D0);
    func_80714CC0(D_80720BC4, 2.5f, (*D_807F5FD4)[idx].x, (*D_807F5FD4)[idx].y, (*D_807F5FD4)[idx].z);
    if (c != 0) {
        if (D_807FBB4C->unk154 == 0x42) {
            p->a = *(f32 *)&D_807FBB4C->unk80;
        }
        f = *(f32 *)&D_807FBB4C->unk80;
        if ((p->a - f > 200.0 || f < 10.0f) && p->b == 0.0) {
            func_805FF9AC(0x48, 0x1C, 0, 0);
            p->b = 1.0f;
        }
    }
}


extern f32 D_807F622C;

void func_806458C8(CsState *cs, s16 csId, s16 b, s16 c) {
    s16 angle;
    s16 dist;
    s32 r1;
    s32 r2;
    f32 s;
    f32 d;

    if (D_8076A064 % (u32)b == 0) {
        r1 = randomNonNegative() >> 15;
        angle = r1 % 2048 + (D_807F622C * 4096.0f / 360.0f - 1024.0f);
        r2 = randomNonNegative() >> 15;
        dist = r2 % 32767 % 6 + 15;
        func_80714950(-0x32 - (randomNonNegative() >> 15) % 80);
        func_8071498C((void *)func_80717D4C);
        func_807149B8(1);
        func_80714998(2);
        s = func_80612794(angle);
        d = dist;
        func_80714CC0(D_8071FFA0, 1.0f, s * d + D_807F621C, D_807F6220 + 50.0f, func_80612790(angle) * d + D_807F6224);
    }
}

void func_80645A64(CsState *cs, s16 csId, s16 b, s16 c) {
    s16 i;

    i = 0;
    if (b > 0) {
        do {
            func_80714950(-0x96 - ((randomNonNegative() >> 15) % 80));
            func_8071498C((void *)func_80717D4C);
            func_807149B8(1);
            func_80714998(2);
            func_80714B84(D_8071FFA0, 1.0f, csId, i + 1, 0);
            i++;
        } while (i < b);
    }
}


void func_80645B9C(CsState *cs, s16 csId, s16 b, s16 c) {
    if ((0x243 - cs->unk44[0]) % 60 == 0) {
        sfxPlayFromTargetSlot(csId, 0x38, 0xFF, 0x7F, 0, 0x3C, 0.0f);
    }
}

void lightSetTargetId(s32);
void lightSetFlags(s32);

void func_80645C04(CsState *cs, s16 csId, s16 b, s16 c) {
    f32 x;
    f32 y;
    f32 z;

    modelSlotGetNodePos(csId, 1, 1, &x, &y, &z);
    lightSetRadius(0x9C4);
    lightSetTargetId(9);
    lightSetFlags(2);
    lightAdd(x, y, z, 0.0f, 0.0f, 0.0f, 600.0f, 0, 0xFF, 0xFF, 0xFF);
    lightSetRadius(0x9C4);
    lightSetTargetId(0xA);
    lightSetFlags(2);
    lightAdd(x, y, z, 0.0f, 0.0f, 0.0f, 600.0f, 0, 0xFF, 0xFF, 0xFF);
}

typedef struct CsB4Obj3 {
    /* 0x00 */ u8 pad0[0x90];
    /* 0x90 */ f32 unk90;
    /* 0x94 */ u8 pad94[0x66];
    /* 0xFA */ u8 unkFA;
} CsB4Obj3;

typedef struct CsB4Obj2 {
    /* 0x000 */ u8 pad0[0x174];
    /* 0x174 */ CsB4Obj3 *unk174;
} CsB4Obj2;

typedef struct CsB4Obj1 {
    /* 0x000 */ u8 pad0[0x104];
    /* 0x104 */ CsB4Obj2 *unk104;
} CsB4Obj1;

typedef struct CsB4Player {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ Actor *unk4;
    /* 0x008 */ u8 pad8[0x20C];
    /* 0x214 */ f32 unk214;
} CsB4Player;

void mapChunkEffectSetFlag(s16, s16, u8, u8);

void func_80645D14(s32 **slot, s16 csId, s16 b, s16 c) {
    s32 *p;
    CsB4Obj1 *a;
    CsB4Obj2 *b2;
    CsB4Obj3 *o;
    u8 near = 0;

    if (*slot == NULL) {
        *slot = func_80610FE8(4);
        **slot = 1;
    }
    p = *slot;
    a = ((CsB4Player *)D_807FC924)->unk4->unk174;
    b2 = a->unk104;
    o = b2->unk174;
    if (o->unkFA != 0 && ((CsB4Player *)D_807FC924)->unk214 < o->unk90 + 3.0f) {
        near = 1;
    }
    if (*p != 0 && near == 0) {
        if (b == 9) {
            mapChunkEffectSetFlag(9, 4, 1, 0);
            mapChunkEffectSetFlag(9, 5, 1, 0);
            mapChunkEffectSetFlag(9, 6, 1, 0);
        } else {
            mapChunkEffectSetFlag(0xF, 0xF, 1, 0);
            mapChunkEffectSetFlag(0xE, 0x11, 1, 0);
            mapChunkEffectSetFlag(0xD, 0x13, 1, 0);
            mapChunkEffectSetFlag(0xC, 0x15, 1, 0);
        }
        *p = 0;
    }
    if (*p == 0 && near != 0) {
        if (b == 9) {
            mapChunkEffectSetFlag(9, 4, 1, 1);
            mapChunkEffectSetFlag(9, 5, 1, 1);
            mapChunkEffectSetFlag(9, 6, 1, 1);
        } else {
            mapChunkEffectSetFlag(0xF, 0xF, 1, 1);
            mapChunkEffectSetFlag(0xE, 0x11, 1, 1);
            mapChunkEffectSetFlag(0xD, 0x13, 1, 1);
            mapChunkEffectSetFlag(0xC, 0x15, 1, 1);
        }
        *p = 1;
    }
}

extern u8 D_80720B00;
void func_8071EB70(void);

void func_80645F40(CsState *cs, s16 csId, s16 b, s16 c) {
    f32 x = 0.0f;
    s32 i;

    if (!(D_8076A064 & 0xF)) {
        for (i = 1; i != 0xB; i++) {
            func_807149B8(1);
            func_80714998(2);
            func_8071498C(func_8071EB70);
            func_80714950(0x2BC);
            func_807149A8(0x2BC);
            func_80714B84(&D_80720B00, x + 1.1, csId, i, 1);
            x += 0.05;
        }
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80646058.s")

typedef struct CsB4Player210 {
    /* 0x000 */ u8 pad0[0x210];
    /* 0x210 */ f32 x;
    /* 0x214 */ f32 y;
    /* 0x218 */ f32 z;
} CsB4Player210;

extern f32 D_807480F0;
f32 sqrtf(f32);

void func_80646770(s32 **slot, s16 csId, s16 b, s16 c) {
    s32 *p;
    s32 cnt;
    s32 start;
    s32 hit;
    CsB0Point3f *v;
    s32 *q;
    CsB4Player210 *pl;
    f32 dx;
    f32 nv;
    f32 dy;
    f32 dz;

    hit = 0;
    if (*slot == NULL) {
        *slot = func_80610FE8(4);
        **slot = 0;
    }
    p = *slot;
    start = *p;
    cnt = D_807F5FD4[1] - D_807F5FD4[0];
    q = *slot;
    *q = start + 1;
    if (cnt == *q) {
        *p = 0;
        do {
        } while (0);
    }
    if (start != *p) {
        do {
            pl = (CsB4Player210 *)D_807FC924;
            v = *p + D_807F5FD4[0];
            nv = pl->z - v->z;
            dx = pl->x - v->x;
            dz = nv;
            dy = pl->y - v->y;
            if (sqrtf(dz * dz + (dx * dx + dy * dy)) < D_807480F0) {
                hit = 1;
                func_807149B8(1);
                func_80714998(3);
                func_80714950(0);
                func_8071498C(func_8071E3EC);
                func_807149A8(0x320);
                v = *p + D_807F5FD4[0];
                func_80714CC0(D_80720BC4, 2.5f, v->x, v->y, v->z);
            } else {
                *p += 1;
                if (cnt == *p) {
                    *p = 0;
                }
            }
        } while (hit == 0 && start != *p);
    }
}

extern f32 D_8074811C;
extern f32 D_80748120;
extern f32 D_80748124;
extern f32 D_80748128;
extern s32 D_8074812C;
extern s32 D_80748130;
extern f32 D_80748140;
extern f32 D_80748144;
extern s32 D_80748148;
extern f32 D_8074814C;
extern s32 D_80748150;
extern u8 D_80748154[];
extern u8 D_80720BE8[];
void func_8071BB14(void);
void func_8071E864(void);
void actorListSpawnNodeEntry(s16, f32, f32, f32, s16, f32, s32, void *);

void func_80646978(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 i;
    f32 fx;
    f32 fy;
    f32 fz;
    s32 e;
    f32 vec[3];
    f64 d0;
    f64 d1;

    i = 0;
    if (D_80748148 > 0) {
        do {
            d0 = (u32)func_806119A0() / 1000 % 100;
            fx = d0 - 50.0;
            d1 = (u32)func_806119A0() / 1000 % 100;
            fy = d1 - 50.0;
            d0 = (u32)func_806119A0() / 1000 % 100;
            fz = d0 - 50.0;
            func_8071496C(i);
            func_807149B8(1);
            if (i == 0) {
                func_80714950(D_80748150 + 0x10000);
                func_8071498C(func_8071AADC);
                func_80714998(D_80748154[3]);
            } else {
                func_8071498C(func_8071BB14);
            }
            func_80714CC0(D_80720BE8, D_80748140, D_807F621C + fx, D_807F6220 + fy, D_807F6224 + fz);
            i++;
        } while (i < D_80748148);
        i = 0;
    }
    do {
        func_8071498C(func_8071E864);
        func_80714950(i);
        func_807149B8(1);
        func_807149C8(0x8C, 0x8C, 0x8C, 0xFF);
        func_80714998(3);
        func_80714CC0(D_8071FFA0, D_80748144, D_807F621C, D_807F6220 + D_8074814C, D_807F6224);
        i++;
    } while (i < 0xC);
    for (i = 0; i != 0x1130; i += 0x190) {
        vec[0] = (f32)((s32)(randomNonNegative() >> 0xF) % D_8074812C) + D_80748120;
        vec[1] = i;
        vec[2] = (f32)((s32)(randomNonNegative() >> 0xF) % D_80748130) + D_80748124;
        actorListSpawnNodeEntry(0x5A, D_807F621C, D_807F6220 + D_8074811C, D_807F6224, 0, D_80748128, 0, vec);
    }
}

f32 func_806119FC(void);

void func_80646DC4(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 pad0;
    f32 x;
    f32 y;
    f32 z;
    f32 scale;
    s32 i;
    s32 n;
    s32 off;
    s32 pad1;
    s32 pad2;
    s32 pad3;
    s32 pad4;
    f32 vec[3];
    s32 pad5;

    if (b != 0) {
        for (i = 1; i != 7; i++) {
            modelSlotGetNodePos(csId, 1, i, &x, &y, &z);
            func_8071496C(i);
            func_807149B8(1);
            func_8071498C(func_8071BB14);
            func_807149C8(0xFF, 0xFF, 0xFF, 0x96);
            func_80714CC0(D_80720BE8, 1.5f, x, y, z);
        }
        return;
    }
    scale = 0.3f;
    n = 7;
    if (c != 0) {
        scale = 0.2f;
        n = 10;
    }
    i = 1;
    if (n >= 2) {
        off = 0x2A8;
        do {
            vec[0] = (f32)(randomNonNegative() % 300 + 300);
            vec[1] = off;
            vec[2] = (f32)(randomNonNegative() % 500 + 150);
            if (c == 0) {
                modelSlotGetNodePos(csId, 1, i, &x, &y, &z);
                y = (f32)((f64)y + 10.0);
            } else {
                x = (f32)((f64)func_806119FC() * 30.0 + (f64)D_807F621C - 15.0);
                y = (f32)((f64)func_806119FC() * 40.0 + (f64)D_807F6220);
                z = (f32)((f64)func_806119FC() * 30.0 + (f64)D_807F6224 - 15.0);
            }
            actorListSpawnNodeEntry(0x5A, x, y, z, 0, scale, 0, vec);
            i++;
            off += 0x2A8;
        } while (i != n);
    }
}

void func_80647108(CsState *cs, s16 csId, s16 b, s16 c) {
    func_80714950(-0x78);
    func_8071498C(func_80717D4C);
    func_807149B8(1);
    func_80714998(3);
    func_80714B84(D_8071FFA0, 1.5f, csId, 1, 0);
}

void func_80647170(CsState *cs, s16 csId, s16 b, s16 c) {
    f32 x;
    f32 y;
    f32 z;
    s32 r;
    s32 g;

    modelSlotGetNodePos(csId, 1, 2, &x, &y, &z);
    if (b != 0) {
        r = 0;
        g = 0;
    } else {
        r = 0xFF;
        g = 0xC8;
    }
    lightAdd(x, y, z, 0.0f, 0.0f, 0.0f, 80.0f, 0, 0xFF, r, g);
}


void func_80647218(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 i;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 sc;

    for (i = 0; i != 6; i++) {
        dx = (f32)((u32)func_806119A0() / 1000 % 20) - 10.0;
        dy = (f32)((u32)func_806119A0() / 1000 % 20) - 10.0;
        dz = (f32)((u32)func_806119A0() / 1000 % 20) - 10.0;
        sc = (u32)func_806119A0() / 1000 % 50 - 25.0;
        sc = sc / 50.0;
        func_80714950(-0xAA);
        func_8071498C(func_80717D4C);
        func_807149B8(1);
        func_80714998(3);
        func_8071496C(i << 1);
        func_80714CC0(D_8071FFA0, sc + 1.5, D_807F621C + dx, D_807F6220 + dy, D_807F6224 + dz);
    }
}

void func_80714944(s32);

void func_80647508(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 node;
    f32 x;
    f32 y;
    f32 z;

    node = (u32)func_806119A0() / 1000 % 10 + 1;
    func_80714950(-0x28A - (u32)func_806119A0() / 1000 % 200);
    func_8071498C(func_80717D4C);
    func_807149B8(1);
    func_80714998(9);
    func_807149C8(0xFF, 0xFF, 0xFF, 0x64);
    func_80714944(5);
    modelSlotGetNodePos(csId, 1, node, &x, &y, &z);
    func_80714CC0(D_8071FFA0, 1.5f, x, y - 70.0f, z);
}

extern u8 D_80720DE0[];

void func_80647610(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 *q;
    s32 idx;
    s32 x;
    s32 y;
    s32 z;
    CsB0Point3f *p;

    q = *(s32 **)cs;
    if (q == NULL) {
        *(s32 **)cs = func_80610FE8(4);
        **(s32 **)cs = 0;
        q = *(s32 **)cs;
    }
    (*q)++;
    if (c == *q) {
        *q = 0;
    }
    idx = *q;
    p = D_807F5FD4[b] + idx;
    x = p->x;
    y = p->y;
    z = p->z;
    func_80714998(2);
    func_807149B8(1);
    func_807149C8(0xFF, 0xFF, 0xFF, 0xC8);
    func_80714CC0(D_80720DE0, 1.0f, x, y + 10, z);
}

extern u8 D_80748168[];
extern f32 D_8074816C;

void func_8064774C(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 i;

    for (i = 1; i != 0xF; i++) {
        func_80714950(-0x78);
        func_8071498C(func_80717D4C);
        func_807149B8(1);
        func_80714998(3);
        func_807149C8(0xFF, 0xFF, 0xFF, D_80748168[3]);
        func_80714B84(D_8071FFA0, D_8074816C, csId, i, 0);
    }
}

extern u8 D_80720EA4[];

void func_80647834(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 i;
    f32 t;

    for (i = 0; i < 12; i++) {
        func_807149B8(1);
        func_807149FC(0x3C);
        func_8071498C(func_8071910C);
        func_80714998(2);
        func_80714950(4);
        t = (u32)func_806119A0() / 1000 % 80;
        func_80714CC0(D_80720EA4, 1.0f, D_807F621C, D_807F6220 + t, D_807F6224);
    }
    for (i = 1; i != 6; i++) {
        func_80714950(-0x78);
        func_8071498C(func_80717D4C);
        func_807149B8(1);
        func_80714998(3);
        func_807149C8(0xFF, 0xFF, 0xFF, 0x78);
        func_80714B84(D_8071FFA0, 3.0f, csId, i, 0);
    }
}

extern u8 D_8071FC8C[];
void func_8071F1D0(void);

void func_80647A14(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 i;
    f32 y;

    y = 0.0f;
    for (i = 0; i != 6; i++) {
        func_8071496C(i << 1);
        func_807149B8(1);
        func_807149FC(7);
        func_8071498C(func_8071F1D0);
        func_80714998(1);
        func_80714950(y);
        func_80714CC0(D_8071FC8C, 0.5f, D_807F621C, D_807F6220, D_807F6224);
        func_80714950(y + 2048.0f);
        func_80714CC0(D_8071FC8C, 0.5f, D_807F621C, D_807F6220, D_807F6224);
        y += 682.0f;
    }
}

typedef struct CsB5Blink {
    /* 0x0 */ u32 time;
    /* 0x4 */ s32 state;
} CsB5Blink;

void func_80647B74(CsState *cs, s16 csId, s16 b, s16 c) {
    CsB5Blink *p;
    CsB5Blink *n;

    if (*(CsB5Blink **)cs == NULL) {
        n = func_80610FE8(8);
        *(CsB5Blink **)cs = n;
        n->time = 0;
        n->state = 0;
    }
    p = *(CsB5Blink **)cs;
    if (p->time + 50 < D_8076A064) {
        if ((randomNonNegative() >> 15) % 1000 >= 0x353) {
            p->state = 1;
            p->time = D_8076A064;
        }
    }
    if (p->state == 0) {
        return;
    }
    switch (p->state) {
        case 1:
            modelSlotSetNodeFrame(csId, 1, 1, 0);
            break;
        case 3:
            modelSlotSetNodeFrame(csId, 1, 2, 0);
            break;
        case 5:
            modelSlotSetNodeFrame(csId, 1, 1, 0);
            break;
        case 7:
            modelSlotSetNodeFrame(csId, 1, 0, 0);
            p->state = 0;
            break;
    }
    if (p->state != 0) {
        p->state++;
    }
}


void func_80647CF4(CsState *cs, s16 csId, s16 b, s16 c) {
    func_80714998(2);
    if (b != 0) {
        func_80714CC0(D_8071FBC8, 3.0f, D_807F621C, D_807F6220, D_807F6224);
    } else {
        func_80714B84(D_8071FBC8, 3.0f, csId, 1, 0);
    }
}

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

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
void modelSlotGetNodePos(s32, u8, s32, f32 *, f32 *, f32 *);

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

void func_80643C0C(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 *q;
    s32 n;
    f32 t;
    f32 f;
    if (((CsB1LightView *)cs)->unk0 == NULL) {
        ((CsB1LightView *)cs)->unk0 = func_80610FE8(8);
    }
    q = ((CsB1LightView *)cs)->unk0;
    if (b == 1) {
        *((CsB1LightView *)cs)->unk0 = 0;
    }
    n = *q;
    t = (f32)(70 - n) / 70.0f;
    *q = n + 1;
    n = 0;
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
s16 sfxSlotAllocateSource(s16, s32, s32, u8, s32, f32, s32);

void func_8064409C(CsState *cs, s16 csId, s16 b, s16 c) {
    CsB1SfxState *q;
    CsB1SfxState *t;

    if (((CsB1SfxView *)cs)->unk0 == NULL) {
        t = func_80610FE8(0xC);
        ((CsB1SfxView *)cs)->unk0 = t;
        t->unk0 = 0;
        t->unk4 = 0;
    }
    q = ((CsB1SfxView *)cs)->unk0;
    switch (q->unk0) {
        case 0:
            q->unk4++;
            if (q->unk4 == 4) {
                q->unk8 = 0;
                q->unk0++;
                if (((CsB1SfxView *)cs)->unk10 < 0) {
                    ((CsB1SfxView *)cs)->unk10 = sfxSlotAllocateSource(csId, 0x12C, 0x3C, 1, 0x64, 1.0f, 0);
                }
            }
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
            break;
        case 2:
            q->unk4 = 7;
            q->unk8++;
            if (q->unk8 == 0x28) {
                q->unk8 = 0;
                q->unk0++;
                sfxPlayFromTargetSlot(csId, 0x74, 0xFF, 0x7F, 0, 0x50, 0.3f);
            }
            break;
        case 3:
            q->unk4 = 8;
            q->unk8++;
            if (q->unk8 == 0x28) {
                q->unk8 = 0;
                q->unk0++;
                sfxPlayFromTargetSlot(csId, 0x75, 0xFF, 0x7F, 0, 0x50, 0.3f);
            }
            break;
        case 4:
            q->unk4 = 9;
            break;
        default:
            break;
    }
    modelSlotSetNodeFrame(csId, 1, q->unk4, 0);
}

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
    f32 tm;
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
    px = splineEvalCubic(frac, D_807F5FD4[arg1][idx[0]].x, (tm = D_807F5FD4[arg1][idx[1]].x), D_807F5FD4[arg1][idx[2]].x, D_807F5FD4[arg1][idx[3]].x);
    py = splineEvalCubic(frac, D_807F5FD4[arg1][idx[0]].y, (tm = D_807F5FD4[arg1][idx[1]].y), D_807F5FD4[arg1][idx[2]].y, D_807F5FD4[arg1][idx[3]].y);
    lightAdd(px, py, splineEvalCubic(frac, D_807F5FD4[arg1][idx[0]].z, (tm = D_807F5FD4[arg1][idx[1]].z), D_807F5FD4[arg1][idx[2]].z, D_807F5FD4[arg1][idx[3]].z), 0.0f, 0.0f, 0.0f, 250.0f, 0, 0xFF, 0xFF, 0xFF);
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

#ifdef NON_MATCHING
typedef struct CsB46State {
    /* 0x00 */ s32 idx;
    /* 0x04 */ s32 timer;
    /* 0x08 */ s32 active;
    /* 0x0C */ s32 delay;
    /* 0x10 */ s32 count;
    /* 0x14 */ s32 flag14;
    /* 0x18 */ s32 flag18;
    /* 0x1C */ s32 flag1C;
} CsB46State;

typedef struct CsB46Player {
    /* 0x000 */ u8 pad0[0x210];
    /* 0x210 */ f32 x;
    /* 0x214 */ f32 y;
    /* 0x218 */ f32 z;
} CsB46Player;

typedef struct CsB46Sub4 {
    /* 0x00 */ u8 pad0[0x64];
    /* 0x64 */ u16 unk64;
} CsB46Sub4;

typedef struct CsB46Act {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ CsB46Sub4 *unk4;
    /* 0x008 */ u8 pad8[0x7C - 8];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x12C - 0x88];
    /* 0x12C */ s16 unk12C;
    /* 0x12E */ u8 pad12E[0x154 - 0x12E];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
} CsB46Act;

extern u32 D_807FBB60;
extern u8 D_80748108;
extern s32 D_807480F4;
extern s32 D_807480F8;
extern s32 D_807480FC;
extern s32 D_80748100;
extern f32 D_80748104;
extern s32 D_8074810C;
extern s32 D_80748110;
extern s32 D_80748114;
extern f32 D_807480F0;
f32 sqrtf(f32);
s32 flagGet(s32, s32);
void flagSet(s32, s32, s32);
void sfxStopChannel(s32, s32);
void sfxAllocateChannel(s32, f32);
void camStartPath(void *, s32, s32);
void actorListSpawnNodeEntry(s16, f32, f32, f32, s16, f32, s32, void *);
Actor *spawnNodeActivate(s16, u16);

#define CsB46A ((CsB46Act *)D_807FBB4C)

void func_80646058(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 start;
    u8 hit;
    CsB46State *p;
    CsB46Player *pl;
    f32 t;
    CsB0Point3f *v;
    CsB46Act *a;
    u8 ok;
    CsB46State *n;
    s32 s;
    f32 u;
    u32 pad0;
    u32 pad1;
    f32 vec[3];
    u8 *hp = &hit;

    hit = 0;
    if (*(CsB46State **)cs == NULL) {
        n = func_80610FE8(0x1C);
        *(CsB46State **)cs = n;
        n->idx = 0;
        n->timer = D_807480F4;
        n->active = 0;
        n->delay = 0;
        n->count = 0;
        n->flag14 = 0;
        n->flag18 = 0;
        n->flag1C = 0;
    }
    p = *(CsB46State **)cs;
    if (b == 0) {
        if (D_80748108 != 0) {
            return;
        }
        if (p->active != 0 && p->flag14 == 0) {
            return;
        }
        start = p->idx;
        p->idx = start + 1;
        if (p->idx == 0x36) {
            p->idx = 0;
        }
        if (start == p->idx) {
            return;
        }
        do {
            if (D_80720BC4) {}
            pl = (CsB46Player *)D_807FC924;
            v = D_807F5FD4[0] + p->idx;
            if (sqrtf((pl->z - v->z) * (pl->z - v->z) + ((pl->x - v->x) * (pl->x - v->x) + (pl->y - v->y) * (pl->y - v->y))) < D_807480F0) {
                if (D_807480F4 && D_807480F4) {}
                hit = 1;
                func_807149B8(1);
                func_80714998(3);
                func_80714950(0);
                func_8071498C(func_8071E3EC);
                func_807149A8(0x320);
                v = D_807F5FD4[0] + p->idx;
                func_80714CC0(D_80720BC4, 2.5f, v->x, v->y, v->z);
            } else {
                p->idx++;
                if (p->idx == 0x36) {
                    p->idx = 0;
                }
            }
        } while (hit == 0 && start != p->idx);
        return;
    }
    if ((~D_807FBB60 & 0x10) || CsB46A->unk154 == 0x63) {
        if (p->timer < 200) {
            p->timer = D_807480F4;
        }
        sfxStopChannel(0x54, 0);
        p->active = 0;
        return;
    }
    if (p->active != 0) {
        if (p->delay == 0) {
            if (p->flag14 != 0) {
                t = (randomNonNegative() >> 15) % 800 - 400.0;
                u = (randomNonNegative() >> 15) % 800 - 400.0;
                actorListSpawnNodeEntry(0x5C, 1820.0f + t, 500.0f, 3614.0f + u, 0, D_80748104, 0, vec);
            } else {
                t = (randomNonNegative() >> 15) % D_8074810C - D_8074810C * 0.5;
                u = (randomNonNegative() >> 15) % D_8074810C - D_8074810C * 0.5;
                actorListSpawnNodeEntry(0x5C, CsB46A->unk7C + t, CsB46A->unk80 + (f32)D_80748100, CsB46A->unk84 + u, 0, D_80748104, 0, vec);
            }
            if (p->flag14) {
                p->delay = D_80748114;
            } else {
                p->delay = D_807480FC;
            }
            p->count--;
            if (p->count == 0) {
                if (flagGet(0x12B, 0) == 0) {
                    p->timer = 0x50;
                } else {
                    p->timer = D_807480F4;
                    sfxStopChannel(0x54, 0);
                }
                p->active = 0;
                p->flag14 = 0;
                flagSet(0x12B, 1, 0);
            }
        } else {
            p->delay--;
        }
        if (p->flag14 != 0) {
            return;
        }
        if (CsB46A->unk154 == 0x63) {
            return;
        }
        s = CsB46A->unk12C;
        if (s == 0 || s == 7 || s == 2 || s == 3) {
            sfxStopChannel(0x54, 0);
            p->timer = D_807480F4;
            p->active = 0;
        }
    } else {
        if (p->flag18 == 0 && flagGet(0x12C, 0)) {
            p->flag18 = 1;
        }
        if (CsB46A->unk12C == 0xD) {
            ok = 0;
            a = (CsB46Act *)spawnNodeActivate(0x1F, 0);
            if (a != NULL && a->unk154 == 0x27 && a->unk4->unk64 == 0x362 && a->unk155 == 2) {
                p->timer = 0x65;
                ok = 1;
            }
        } else {
            ok = 1;
        }
        if (ok == 0 && p->flag1C == 0) {
            return;
        }
        if (p->flag18 != 0) {
            return;
        }
        s = CsB46A->unk12C;
        if (s == 0) {
            return;
        }
        if (s == 7 || s == 2 || s == 3) {
            return;
        }
        p->flag1C = 1;
        p->timer--;
        if (p->timer == 0x64) {
            if (flagGet(0x12C, 0) == 0) {
                sfxAllocateChannel(0x54, 1.0f);
            }
        }
        if (p->timer == 0x32) {
            if (flagGet(0x12B, 0) == 0) {
                camStartPath(0, 0x17, 1);
                p->flag14 = 1;
            }
        }
        if (p->timer == 0) {
            p->active = 1;
            p->flag1C = 0;
            p->count = p->flag14 ? D_80748110 : D_807480F8;
            p->delay = 0;
        }
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80646058.s")
#endif

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

extern u8 D_8071FC40[];
void func_80718BF4(void);

void func_80647D7C(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 i;
    f32 dx;
    f32 dy;
    f32 dz;

    if (!((func_806119A0() / 10000U) & 1)) {
        i = 0;
        do {
            dx = (f32)((func_806119A0() / 10000U) % 200U) * 0.25 - 2.0;
            dy = (f32)((func_806119A0() / 10000U) % 200U) * 0.25 - 2.0;
            dz = (f32)((func_806119A0() / 10000U) % 200U) * 0.25 - 2.0;
            func_807149B8(1);
            func_80714950(1);
            func_807149FC(-1);
            func_8071498C(func_80718BF4);
            func_80714CC0(D_8071FC40, 0.0f, D_807F621C + dx, D_807F6220 + dy, D_807F6224 + dz);
            i++;
        } while (i != 12);
    }
}

typedef struct CsB6State80648000 {
    /* 0x00 */ f32 (*unk0)[4];
    /* 0x04 */ u8 pad4[0x96];
    /* 0x9A */ u8 unk9A;
} CsB6State80648000;

void func_80648000(CsState *cs, s16 csId, s16 b, s16 c) {
    u32 pad[20];
    void *dm = &cs;
    f32 rx;
    f32 rz;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 t;
    f32 (*m)[4];
#define S ((CsB6State80648000 *)cs)

    if (S->unk0 == NULL && (S->unk9A & 1)) {
        m = func_80610FE8(0x44);
        S->unk0 = m;
        modelSlotGetNodePos(csId, 1, 1, &sp40, &m[4][0], &sp38);
        m[4][0] -= 10.0;
        guRotateF(m, D_807F622C, 0.0f, 1.0f, 0.0f);
    }
    if ((S->unk9A & 1) && (func_806119A0() / 10000U) % 20U == 0) {
        m = S->unk0;
        t = (randomNonNegative() >> 15) % 100;
        rx = t / 100.0;
        t = (randomNonNegative() >> 15) % 100;
        rz = t / (f64)100;
        guMtxXFMF(m, rx * 100.0 + -50.0, 0.0f, rz * 150.0 + -75.0, &sp40, &sp3C, &sp38);
        sp40 *= D_807F6234;
        sp38 *= D_807F6234;
        sp40 += D_807F621C;
        sp38 += D_807F6224;
        func_807149B8(1);
        func_80714950(2);
        func_807149FC(-1);
        func_8071498C(func_80718BF4);
        func_80714CC0(D_8071FC40, 0.0f, sp40, m[4][0], sp38);
    }
#undef S
}

typedef struct CsB6Counters {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ s32 unk4;
    /* 0x8 */ s32 unk8;
} CsB6Counters;
extern u8 D_80721200[];
extern u8 D_8072121C[];
extern u8 D_80721238[];
extern u8 D_80721250[];
extern u8 D_8072126C[];
extern u32 D_8076A068;
void func_80716F10(void);
void func_80714A08(f32, f32);
void func_80714A28(s16);

void func_8064826C(CsState *cs, s16 csId, s16 b, s16 c) {
    u8 *tex;
    f32 sa;
    f32 sb;
    CsB6Counters *p;
    f32 sx;
    f32 sz;

    sx = func_80612794((s16)((D_807F622C + 90.0f) * 4096.0f / 360.0f)) * 15.0f;
    sz = func_80612790((s16)((D_807F622C + 90.0f) * 4096.0f / 360.0f)) * 15.0f;
    if (*(CsB6Counters **)cs == NULL) {
        p = func_80610FE8(0xC);
        *(CsB6Counters **)cs = p;
        p->unk0 = 0;
        p->unk4 = 0;
        p->unk8 = 0;
    }
    p = *(CsB6Counters **)cs;
    func_807149B8(1);
    switch (b) {
        case 0:
            tex = D_80721200;
            break;
        case 1:
            tex = D_8072121C;
            break;
        case 2:
            tex = D_80721250;
            break;
        case 3:
            tex = D_80721238;
            break;
    }
    sa = func_80612794(*(s16 *)((u8 *)p + 2)) * 0.1;
    sb = func_80612794(*(s16 *)((u8 *)p + 6)) * 0.1;
    p->unk0 += 0x32;
    p->unk4 += 0x64;
    func_80714A08(sa + 1.0, sb + 1.0);
    func_807149A8(0x578);
    func_80714A28(4);
    func_80714CC0(tex, 0.0f, D_807F621C + sx, func_80612794(*(s16 *)((u8 *)p + 0xA)) * 10.0 + (D_807F6220 + 80.0), D_807F6224 + sz);
    p->unk8 += 0x64;
    if (D_8076A068 % 12U == 0) {
        func_807149B8(1);
        func_80714950(0x5A);
        func_8071498C(func_80716F10);
        func_807149A8(0x578);
        func_80714A28(4);
        func_80714CC0(D_8072126C, 2.0f, D_807F621C + sx, D_807F6220 + 30.0, D_807F6224 + sz);
    }
}


void func_806485A0(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 n;
    s32 i;
    f32 x;
    f32 y;
    f32 z;
    f32 len;
    f32 r;
    f32 pad[2];
    f32 scale;

    n = c & 0xFF;
    switch ((s16)(b >> 8)) {
        case 0:
            scale = 1;
            break;
        case 1:
            scale = 4;
            break;
    }
    i = 0;
    if (n > 0) {
        r = b & 0xFF;
        do {
            func_8071496C(func_806119FC() * (f32)(c >> 8));
            do {
                x = 2.0f * func_806119FC() - 1.0f;
                y = 2.0f * func_806119FC() - 1.0f;
                z = 2.0f * func_806119FC() - 1.0f;
                len = sqrtf(x * x + y * y + z * z);
            } while (len < 0.05f);
            len = r / len;
            x *= len;
            y *= len;
            z *= len;
            y += r;
            func_80714CC0(D_8071FF18, scale * 1.5, D_807F621C + x, D_807F6220 + y, D_807F6224 + z);
            i++;
        } while (i != n);
    }
}

extern u8 D_807212B0[];
extern u8 D_807212C8[];
extern u8 D_80720340[];

void func_806487C4(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 i;
    s16 hi;
    f32 dz;
    s32 n;
    f32 dx;
    f32 r;
    f32 dy;
    f32 base;
    u8 *tbl;
    f32 spread;
    f32 scale;

    hi = b >> 8;
    switch (hi) {
        case 0:
            scale = 1;
            break;
        case 1:
            scale = 4.0f;
            break;
    }
    base = b & 0xFF;
    spread = base;
    tbl = D_807212B0;
    n = 0x14;
    switch (c) {
        case 1:
            break;
        case 2:
            scale *= 1.75;
            break;
        case 3:
            scale *= 1.75;
            break;
        case 4:
            n = 0x28;
            scale *= 4.0;
            spread *= 1.5;
            break;
        default:
            tbl = D_807212C8;
            scale *= 1.75;
            break;
    }
    for (i = 0; i < n; i++) {
        dx = 2.0f * func_806119FC() - 1.0f;
        dy = 2.0f * func_806119FC() - 1.0f;
        dz = 2.0f * func_806119FC() - 1.0f;
        dx *= spread;
        dy *= spread;
        dz *= spread;
        dy += base;
        func_807149B8(1);
        func_807149FC(0x3C);
        func_8071498C(func_8071910C);
        func_80714998(2);
        func_80714950(2);
        func_80714CC0(tbl, (func_806119FC() * 0.5 + 0.2) * scale, D_807F621C + dx, D_807F6220 + dy, D_807F6224 + dz);
        if (i < 6) {
            dx = 2.0f * func_806119FC() - 1.0f;
            dy = 2.0f * func_806119FC() - 1.0f;
            dz = 2.0f * func_806119FC() - 1.0f;
            dx *= spread;
            dy *= spread;
            dz *= spread;
            dy += base;
            r = (u32)func_806119A0() / 1000 % 50 - 25.0;
            r = r / 50.0;
            if (i == 0) {
                func_80714950(0x100FA);
                func_8071498C(func_8071A8B0);
            } else {
                func_80714950(-0xAA);
                func_8071498C(func_80717D4C);
            }
            func_80714998(3);
            func_807149C8(0xFF, 0xFF, 0xFF, 0x64);
            func_80714CC0(D_8071FFA0, (r + 3.5) * scale, D_807F621C + dx, D_807F6220 + dy, D_807F6224 + dz);
        }
    }
    func_807149B8(1);
    func_80714CC0(D_80720340, scale * 2.5, D_807F621C, b + D_807F6220, D_807F6224);
}


typedef struct CsB7Player {
    /* 0x000 */ u8 pad0[0x290];
    /* 0x290 */ s16 unk290;
} CsB7Player;

s32 func_80648C50(void) {
    s16 state = ((CsB7Player *)D_807FC924)->unk290;

    if (state == 4 || state == 0xC) {
        return 1;
    }
    return 0;
}


typedef struct CsB7Fade {
    /* 0x0 */ u8 unk0;
    /* 0x2 */ u16 unk2;
    /* 0x4 */ f32 unk4;
} CsB7Fade;

typedef struct CsB7FadeView {
    /* 0x00 */ CsB7Fade *unk0;
    /* 0x04 */ u8 pad4[0xC];
    /* 0x10 */ s16 unk10;
} CsB7FadeView;

typedef struct CsB7Cam {
    /* 0x00 */ u8 pad0[0xBC];
    /* 0xBC */ s16 unkBC;
} CsB7Cam;

extern CsB7Cam *D_807FD580;
extern s32 D_8076A0A8;
extern s16 D_807F7366;
extern f32 D_807F6940;
void sfxSetChannelPriority(u8, u8);
void func_8068D264(void);
void renderCallbacksRegister(void *, void *, s32);

void func_80648C84(CsState *cs, s16 csId, s16 b, s16 c) {
    CsB7Fade *q;
    u8 flag;

    if (((CsB7FadeView *)cs)->unk0 == NULL) {
        q = func_80610FE8(8);
        ((CsB7FadeView *)cs)->unk0 = q;
        q->unk0 = 0;
        q->unk2 = 0;
        q->unk4 = 0.0f;
    }
    q = ((CsB7FadeView *)cs)->unk0;
    if (D_8076A0A8 == 0x26) {
        flag = 1;
    } else {
        flag = 0;
    }
    switch (q->unk0) {
        case 0:
            if (q->unk2 == 0) {
                if (func_80648C50() != 0 || flag == 0) {
                    q->unk0 = 1;
                    q->unk2 = 0x190;
                    q->unk4 = 0.0f;
                    if (flag != 0) {
                        ((CsB7FadeView *)cs)->unk10 = sfxSlotAllocateSource(csId, 0x11F, 0, 1, 0, 1.0f, 0);
                    }
                }
            } else {
                q->unk2--;
            }
            break;
        case 1:
            q->unk4 += 0.01;
            if (q->unk4 > 1.0) {
                q->unk4 = 1.0f;
                if (--q->unk2 == 0 || (func_80648C50() == 0 && flag != 0)) {
                    q->unk0 = 2;
                }
            }
            if (flag != 0) {
                sfxSetChannelPriority(*((u8 *)cs + 0x11), q->unk4 * 200.0f);
            }
            break;
        case 2:
            q->unk4 -= 0.01;
            if (q->unk4 < 0.0) {
                q->unk0 = 0;
                q->unk2 = 0x190;
                q->unk4 = 0.0f;
                if (flag != 0) {
                    func_80605380(((CsB7FadeView *)cs)->unk10);
                    ((CsB7FadeView *)cs)->unk10 = -1;
                }
            } else if (flag != 0) {
                sfxSetChannelPriority(*((u8 *)cs + 0x11), q->unk4 * 200.0f);
            }
            break;
    }
    if ((D_807FBB4C->unk154 == 0x42 && D_807FD580->unkBC == 0x62) || D_807FBB4C->unk154 == 0x67) {
        q->unk0 = 0;
        q->unk2 = 0x190;
        q->unk4 = 0.0f;
        if (flag != 0) {
            if (((CsB7FadeView *)cs)->unk10 != -1) {
                func_80605380(((CsB7FadeView *)cs)->unk10);
                ((CsB7FadeView *)cs)->unk10 = -1;
            }
        }
    }
    D_807F7366 = q->unk4 * -25.0f + 995.0f;
    D_807F6940 = q->unk4;
    if (q->unk4 != 0.0f) {
        renderCallbacksRegister(func_8068D264, &q->unk4, 5);
    }
}


void func_8064911C(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 i;

    for (i = 1; i != 8; i++) {
        func_80714950(-0x78);
        func_8071498C(func_80717D4C);
        func_807149B8(1);
        func_80714998(3);
        func_807149C8(0xFF, 0xFF, 0xFF, 0x96);
        func_80714B84(D_8071FFA0, 3.5f, csId, i, 0);
    }
}


extern u8 D_8076A0AB;
extern u8 D_807446F0[];
extern s16 D_80744710[];
extern s8 D_80748170[];
extern s8 D_80748178;
extern s16 D_807505AE[];
s32 flagGet(s32, s32);
u8 func_805FF030(u8, u8);
u8 func_805FF0C8(void);

void func_806491F4(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 idx;
    s32 base;
    s8 v;
    s8 add;
    s32 base2;

    if (b == 0) {
        idx = func_805FF030(D_8076A0AB, 0);
        if (idx >= 8) {
            idx = 0;
        }
        base = D_807446F0[idx];
        if (D_807505AE[base]) {}
        if (flagGet(D_80744710[idx], 0)) {
            modelSlotSetNodeFrame(csId, 1, 0xB, 0);
            modelSlotSetNodeFrame(csId, 2, 0xB, 0);
        } else if (func_805FF0C8()) {
            modelSlotSetNodeFrame(csId, 1, D_80748170[base], 0);
            modelSlotSetNodeFrame(csId, 2, D_80748170[base], 0);
        } else {
            modelSlotSetNodeFrame(csId, 1, 0xA, 0);
            modelSlotSetNodeFrame(csId, 2, 0xA, 0);
        }
    } else {
        v = D_80748178 + 1;
        if (D_8076A0AB && D_8076A0AB) {}
        if (v >= 0x15) {
            v = 0;
        }
        idx = v >> 2;
        base2 = D_80748170[idx];
        if (D_807446F0[base]) {}
        D_80748178 = v;
        if (idx > 0 && flagGet(D_807505AE[idx], 0) == 0) {
            add = 5;
        } else {
            add = 0;
        }
        idx = base2;
        idx += add;
        modelSlotSetNodeFrame(csId, 1, idx, 0);
        if (D_80748178 == 0) {}
        modelSlotSetNodeFrame(csId, 2, idx, 0);
    }
}


void func_8071F660(void);
extern u8 D_80721298[];

void func_806493C4(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 i;
    u8 idx;

    for (i = 0; i < b; i++) {
        idx = (randomNonNegative() >> 15) % 32767 % (c + 1);
        func_807149B8(1);
        func_807149A8(0x7D0);
        func_8071498C(func_8071F660);
        func_807149FC(8);
        func_80714CC0(D_80721298, 1.0f, (*D_807F5FD4)[idx].x, (*D_807F5FD4)[idx].y, (*D_807F5FD4)[idx].z);
    }
}
extern u16 D_807446C0[];
extern u16 D_807FC930[];

void func_8064954C(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 i;
    s32 v;
    s32 n;
    s32 t;

    n = func_805FF030(D_8076A0AB, 0);
    if (n >= 8) {
        n = 7;
    }
    v = D_807446C0[n] - D_807FC930[n];
    if (v < 0) {
        v = 0;
    }
    t = v;
    for (i = 1; i != 4; i++) {
        modelSlotSetNodeFrame(csId, i, (10 - i + t % 10) % 10, 0);
        t /= 10;
    }
}

void func_8071F8E4(void);

typedef struct CsB8Cam {
    /* 0x000 */ u8 pad0[0x220];
    /* 0x220 */ f32 unk220;
    /* 0x224 */ f32 unk224;
    /* 0x228 */ f32 unk228;
    /* 0x22C */ f32 unk22C;
    /* 0x230 */ f32 unk230;
    /* 0x234 */ f32 unk234;
} CsB8Cam;

typedef struct CsB8Obj {
    /* 0x000 */ u8 pad0[0x384];
    /* 0x384 */ void *unk384;
} CsB8Obj;

typedef struct CsB8Part {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
} CsB8Part;

void func_806496B0(CsState *cs, s16 csId, s16 b, s16 c) {
    CsB8Cam *p;
    CsB8Obj *obj;
    CsB8Part *q;
    s32 flag;
    s16 ang;
    s32 i;
    f32 t;
    f32 sinA;
    f32 ex;
    f32 ez;
    f32 negCos;
    f32 xs;
    f32 px;
    f32 zo;
    f32 py;
    f32 xo;
    f32 pz;
    void (*cb)(void);

    if (&xs == 0) {}
    if (&px == 0) {}
    if (&zo == 0) {}
    if (&py == 0) {}
    if (&xo == 0) {}
    if (&pz == 0) {}
    ang = D_807F622C * 4096.0f / 360.0f;
    if (c == 2) {
        func_807149B8(0);
        func_80714CC0(D_80720A7C, 0.5f, func_806119FC() * 35.0 + D_807F621C - 15.0, func_806119FC() * 35.0 + D_807F6220, func_806119FC() * 35.0 + D_807F6224 - 15.0);
        return;
    }
    p = (CsB8Cam *)D_807FC924->unk4->unk174;
    p->unk22C = D_807F621C;
    p->unk230 = D_807F6220 + 15.0;
    p->unk234 = D_807F6224;
    p->unk220 = func_80612794(ang);
    p->unk224 = ang;
    p->unk228 = func_80612790(ang);
    if (c == 0) {
        flag = 1;
        func_80609140(0xF2, 0x5DC0, 63.0f, 1.0f, 0, 0);
    } else {
        flag = 0;
        func_80609140(0x2EB, 0x7D00, 63.0f, 0.6f, 0, 0);
    }
    negCos = -p->unk228;
    sinA = p->unk220;
    px = D_807F621C; py = D_807F6220 + 15.0; pz = D_807F6224;
    ex = p->unk220 * 50.0 + px;
    ang = 0;
    cb = func_8071F8E4;
    ez = p->unk228 * 50.0 + pz;
    for (i = 0; i != 4; i++) {
        t = func_80612790(ang) * 100.0;
        xs = t * negCos + ex;
        xo = t * sinA + ez;
        zo = func_80612794(ang) * 100.0 + py;
        ang += 0x400;
        func_807149FC(-1);
        func_807149B8(0);
        func_8071498C(cb);
        obj = (CsB8Obj *)func_80714CC0(D_8074E880[((randomNonNegative() >> 15) % 1000) % 3], 1.8f, px, py, pz);
        q = obj->unk384 = func_80610FE8(0x28);
        q->unk0 = (randomNonNegative() >> 15) % 5 + 10;
        q->unk4 = 0.0f;
        q->unk8 = xs;
        q->unkC = zo;
        q->unk10 = xo;
        q->unk14 = px - xs;
        q->unk18 = py - zo;
        q->unk1C = pz - xo;
        q->unk20 = 0.0f;
        if (flag != 0) {
            q->unk24 = 0.09090909f;
        } else {
            q->unk24 = 0.033333335f;
        }
    }
}

s32 func_806418E8(s16, s16, s16);

extern s16 D_80748180[][2];

typedef struct CsB8BF0State {
    /* 0x0 */ s32 cnt;
    /* 0x4 */ s32 prev;
} CsB8BF0State;

void func_80649BF0(CsState *cs, s16 csId, s16 b, s16 c) {
    CsB8BF0State *st;
    u8 found;
    s32 eq;
    s32 ok;
    s32 i;
    s32 prev;
    s32 d;

    d = *((u8 *)cs + 0x48);
    if (*(CsB8BF0State **)cs == NULL) {
        st = func_80610FE8(8);
        *(CsB8BF0State **)cs = st;
        st->cnt = 0;
        st->prev = -1;
    }
    st = *(CsB8BF0State **)cs;
    prev = st->prev;
    if (prev == -1) {
        st->prev = *((u8 *)cs + 0x48);
    } else {
        ok = 0;
        if (st->prev & 1) {
            if (*((u8 *)cs + 0x48) + 1 == (*st).prev) {
                ok = 1;
            }
        } else {
            eq = *((u8 *)cs + 0x48) == (*st).prev + 1;
            if (eq) {
                ok = 1;
            }
        }
        if (ok) {
            if (++st->cnt == 8) {
                *((u8 *)cs + 0x4B) = 100;
            }
        } else {
            i = (found = 0);
            while (!found) {
                if (D_80748180[i][0] == (*st).prev) {
                    found = 1;
                } else {
                    i++;
                }
            }
            func_806418E8(D_80748180[i][1], 0x28, 0);
            i = 0;
            found = 0;
            while (!found) {
                if (D_80748180[i][0] == *((u8 *)cs + 0x48)) {
                    found = 1;
                } else {
                    i++;
                }
            }
            func_806418E8(D_80748180[i][1], 0x28, 0);
        }
        st->prev = -1;
    }
}

typedef struct CsB8Slot {
    /* 0x00 */ u8 pad0[0x7C];
    /* 0x7C */ void *unk7C;
    /* 0x80 */ u8 pad80[0xA];
    /* 0x8A */ s16 unk8A;
    /* 0x8C */ u8 pad8C[4];
} CsB8Slot; /* 0x90 */

extern s16 D_807481C0[][2];

void func_80649D74(CsState *cs, s16 csId, s16 b, s16 c) {
    s16 key;
    s32 found;
    s16 (*p)[2];

    key = ((CsB8Slot *)D_807F6000)[hashTableLookup(csId)].unk8A;
    found = 0;
    p = D_807481C0;
    do {
        if (key == (*p)[0]) {
            found = 1;
        } else {
            p++;
        }
    } while (found == 0);
    func_806418E8(0x3D, (*p)[1], 1);
}

void func_80649E00(CsState *cs, s16 csId, s16 b, s16 c) {
    cs->unk14[0] = *((u8 *)cs + 0x49);
}

#ifdef NON_MATCHING
extern s16 D_807F6240[];
extern s16 D_807481F4[];
extern s16 D_807481F6[];
extern u8 D_80748212[];
void func_8064199C(void *, s16, s16);

typedef struct CsB8E34State {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ s32 unk4;
} CsB8E34State;

void func_80649E34(CsState *cs, s16 csId, s16 b, s16 c)
{
  CsB8E34State *st;
  s32 found;
  s16 new_var2;
  long new_var;
  s16 *p;
  s32 d;
  if ((*((CsB8E34State **) cs)) == 0)
  {
    st = func_80610FE8(8);
    *((CsB8E34State **) cs) = st;
    st->unk0 = 0;
    st->unk4 = 0;
  }
  st = *((CsB8E34State **) cs);
  found = 0;
  if ((*(((u8 *) cs) + 0x49)) != (*st).unk4)
  {
    p = D_807481F4;
    do
    {
      if ((*p) == (*(((u8 *) cs) + 0x49)))
      {
        found = 1;
      }
      else
      {
        p++;
      }
    }
    while (found == 0);
    new_var2 = p[1];
    if (((u32) p) < (new_var = (u32) D_80748212))
    {
      if (1)
      {
        func_806418E8(new_var2, 0xA, 0);
        func_8064199C(((CsB8Slot *) D_807F6000)[hashTableLookup(D_807F6240[p[1]])].unk7C, 0, 0);
      }
    }
    if (((u32) p) >= ((u32) D_807481F6))
    {
      func_806418E8(p[-1], 0x14, 0);
    }
    st->unk4 = *(((u8 *) cs) + 0x49);
  }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80649E34.s")
#endif

void func_80649F64(CsState *cs, s16 csId, s16 b, s16 c) {
    func_806418E8(0x5F, ((CsB8Slot *)D_807F6000)[hashTableLookup(csId)].unk8A, 1);
}

typedef struct CsB9Timer {
    /* 0x00 */ u64 last;
    /* 0x08 */ s64 duration;
    /* 0x10 */ s64 left;
    /* 0x18 */ s64 fired;
} CsB9Timer; /* 0x20 */
extern u64 D_807445B0;
extern u64 osGetTime(void);
void heapFreeDeferred(void *);
void func_8068DBA4(void);

void func_80649FC0(CsState *cs, s16 csId, s16 b, s16 c) {
    CsB9Timer *t;
    u64 elapsed;

    if (*(CsB9Timer **)cs == NULL) {
        *(CsB9Timer **)cs = func_80610FE8(0x20);
        t = *(CsB9Timer **)cs;
        t->last = osGetTime();
        t->duration = b;
        t->left = 0;
        t->fired = 0;
    }
    t = *(CsB9Timer **)cs;
    t->last += D_807445B0;
    elapsed = (osGetTime() - t->last) * 64;
    t->left = t->duration - elapsed / 3000 / 1000000;
    if (t->fired == 0 && (u64)t->left < (u64)(s64)c) {
        t->fired = 1;
        cs->unk4B[0] = 0x14;
    }
    if (t->left == 0) {
        heapFreeDeferred(*(CsB9Timer **)cs);
        cs->unk4B[0] = 0x1E;
        *(CsB9Timer **)cs = NULL;
    }
    renderCallbacksRegister(func_8068DBA4, t, 5);
}

void func_8064A180(CsState *cs, s16 csId, s16 b, s16 c) {
}

typedef struct CsB9Slot {
    /* 0x00 */ u8 pad0[0x8A];
    /* 0x8A */ s16 unk8A;
    /* 0x8C */ u8 pad8C[4];
} CsB9Slot; /* 0x90 */
extern u8 D_80748214[];
void func_806BD094(s16, s8);

void func_8064A194(CsState *cs, s16 csId, s16 b, s16 c) {
    u8 found;
    s32 i;
    s16 id;
    u8 *p;

    found = 0;
    i = 0;
    id = ((CsB9Slot *)D_807F6000)[hashTableLookup(csId)].unk8A;
    while (!found) {
        if (id == D_80748214[i]) {
            found = 1;
        } else {
            i++;
        }
    }
    if (i == 0x16) {
        p = D_80748214;
    } else {
        p = D_80748214 + ++i;
    }
    func_806418E8(*p, 0xA, 0);
}


extern u64 osGetTime(void);
typedef struct CsB9FxEnt {
    /* 0x0 */ u8 state;
    /* 0x1 */ u8 pad1;
    /* 0x2 */ s16 timer;
    /* 0x4 */ u8 active;
    /* 0x5 */ u8 pad5;
} CsB9FxEnt; /* 0x6 */
typedef struct CsB9Fx {
    /* 0x00 */ u64 last;
    /* 0x08 */ s64 duration;
    /* 0x10 */ s64 left;
    /* 0x18 */ CsB9FxEnt ent[9];
    /* 0x4E */ u8 pad4E;
    /* 0x4F */ u8 cool;
} CsB9Fx; /* 0x50 */
typedef struct CsB9FxRow {
    /* 0x00 */ u8 pad0[0x18];
    /* 0x18 */ u8 state;
    /* 0x19 */ u8 pad19;
    /* 0x1A */ s16 timer;
    /* 0x1C */ u8 active;
    /* 0x1D */ u8 pad1D;
} CsB9FxRow;
typedef struct CsB9FxSel {
    /* 0x00 */ u8 pad0[0x12];
    /* 0x12 */ u8 state;
    /* 0x13 */ u8 pad13[3];
    /* 0x16 */ u8 active;
} CsB9FxSel;
#define CsB9Sel(t, i) ((CsB9FxSel *)((u8 *)(t) + (i) * 6))
typedef struct CsB9FxView {
    /* 0x00 */ u8 pad0[0x10];
    /* 0x10 */ s16 slot;
    /* 0x12 */ u8 pad12[0x4A];
    /* 0x5C */ u8 unk5C;
    /* 0x5D */ u8 pad5D;
    /* 0x5E */ u16 unk5E;
} CsB9FxView;
extern f32 D_80770BC0[];
void modelAnimEntryGetState(s16, s16, s16 *, f32 *, u8 *);
void modelAnimEntrySetUnkC(s16, s16, s16);
void modelAnimEntrySetTime(s16, s16, s16, f32);
void func_806086CC(f32, f32, f32, s16, s32, s32, s32, s32, f32, s32);

void func_8064A258(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 u1; /* unused: reserves frame slots */
    s32 sixth;
    u8 ok;
    s16 st;
    f32 frac;
    u8 spC7;
    s32 i;
    CsB9Fx *t;
    CsB9FxRow *e;
    u8 allDone;
    f32 x;
    f32 y;
    f32 z;
    u8 count;
    u8 timerRan;
    s32 g1;
    s32 g2;
    u64 elapsed;
    s32 g3;

    allDone = 1;
    timerRan = 0;
    count = 0;
    if (*(CsB9Fx **)cs == NULL) {
        t = func_80610FE8(0x50);
        *(CsB9Fx **)cs = t;
        t->pad4E = 0;
        t->ent[0].state = 0;
        t->ent[1].state = 1;
        t->ent[2].state = 3;
        t->ent[3].state = 1;
        t->ent[4].state = 2;
        t->ent[5].state = 1;
        t->ent[6].state = 3;
        t->ent[7].state = 0;
        t->ent[8].state = 1;
        for (i = 0; i != 9; i++) {
            t->ent[i].active = 1;
            t->ent[i].timer = 0x8C;
        }
        t->cool = 0;
        t->last = osGetTime();
        t->duration = 0x3C;
        t->left = 0;
        ((CsB9FxView *)cs)->slot = sfxSlotAllocateSource(csId, 0x12F, 0, 1, 0xFF, 1.0f, 0);
    }
    t = *(CsB9Fx **)cs;
    t->last += D_807445B0;
    for (i = 0, e = (CsB9FxRow *)t; i != 9; i++, e = (CsB9FxRow *)((u8 *)e + 6)) {
        if (e->active != 0) {
            count++;
            modelAnimEntryGetState(csId, i + 1, &st, &frac, &spC7);
            if (st == e->state && frac < 0.1 && e->timer == 0) {
                modelAnimEntrySetUnkC(csId, i + 1, 0);
                modelAnimEntrySetTime(csId, i + 1, st, 0);
                e->active = 0;
                modelSlotGetNodePos(csId, 1, i + 1, &x, &y, &z);
                func_806086CC(x, y, z, 0x1AE, 0xFF, 0x7F, 0x14, 0x50, 0.7f, 0);
            }
            if (e->timer != 0) {
                e->timer--;
                timerRan = 1;
            }
        }
        ok = e->state == 0;
        sixth = i == 6 && e->state == 2;
        ok |= sixth;
        if (e->active != 0 || ok == 0) {
            allDone = 0;
        }
    }
    if (timerRan != 0) {
        t->last = osGetTime();
    }
    if (((CsB9FxView *)cs)->slot != -1) {
        D_80770BC0[((CsB9FxView *)cs)->slot] = count;
        if (count == 0) {
            func_80605380(((CsB9FxView *)cs)->slot);
            ((CsB9FxView *)cs)->slot = -1;
        }
    }
    if (((CsB9FxView *)cs)->unk5C != 0 && ((CsB9FxView *)cs)->unk5E == 0x26) {
        if (CsB9Sel(t, ((CsB9FxView *)cs)->unk5C)->active == 0 && t->cool == 0) {
            CsB9Sel(t, ((CsB9FxView *)cs)->unk5C)->state++;
            CsB9Sel(t, ((CsB9FxView *)cs)->unk5C)->state = CsB9Sel(t, ((CsB9FxView *)cs)->unk5C)->state % 4;
            CsB9Sel(t, ((CsB9FxView *)cs)->unk5C)->active = 1;
            modelAnimEntrySetUnkC(csId, ((CsB9FxView *)cs)->unk5C, 0x19);
            t->cool = 5;
        }
    }
    if (t->cool != 0) {
        t->cool--;
    }
    elapsed = (osGetTime() - t->last) * 64;
    t->left = t->duration - elapsed / 3000 / 1000000;
    if ((u64)t->left <= 0 || allDone) {
        heapFreeDeferred(*(CsB9Fx **)cs);
        if (allDone != 0) {
            cs->unk4B[0] = 0x28;
        } else {
            cs->unk4B[0] = 0x1E;
        }
        *(CsB9Fx **)cs = NULL;
    }
    renderCallbacksRegister(func_8068DBA4, t, 5);
}

typedef struct CsB9Pair {
    /* 0x0 */ s16 a;
    /* 0x2 */ s16 b;
} CsB9Pair;
extern s16 D_8074822C[][2];
extern CsB9Pair D_80748244[];

void func_8064A804(CsState *cs, s16 csId, s16 b, s16 c) {
    u8 *p;
    u8 found;
    s16 idx;
    s32 row;
    s32 col;
    CsB9Pair *pr;

    found = 0;
    if (*(u8 **)cs == NULL) {
        *(u8 **)cs = func_80610FE8(0xA);
        p = *(u8 **)cs;
        for (row = 0; row < 6; row++) p[row] = 0;
        p[6] = 1;
        p[9] = 0;
    }
    p = *(u8 **)cs;
    for (row = 0; row < 6 && !found; row++) {
        for (col = 0; col < 2 && !found; col++) {
            if (D_8074822C[row][col] == ((u8 *)cs)[0x49]) {
                found = 1;
            }
        }
    }
    row--;
    col--;
    if (!(p[row] & (1 << col))) {
        if ((p[row] |= (1 << col)) == 3) {
            pr = &D_80748244[(s16)(row * 2 + col)];
            modelSlotSetNodeFrame(csId, pr->a, 0, 0);
            modelSlotSetNodeFrame(csId, pr->b, 0, 0);
            func_80609140(0x2A1, 0x7FFF, 63.0f, 1.0f, 0, 0);
            p[9]++;
            if (p[9] == 6) {
                cs->unk4B[1] = 0x32;
            }
        } else if (p[6] != 0) {
            idx = row * 2 + col;
            pr = &D_80748244[idx];
            modelSlotSetNodeFrame(csId, pr->a, 0, 0);
            modelSlotSetNodeFrame(csId, pr->b, 0, 0);
            p[8] = idx;
            p[7] = row;
        } else {
            p[p[7]] = 0;
            p[row] = 0;
            modelSlotSetNodeFrame(csId, D_80748244[p[8]].a, 1, 0);
            modelSlotSetNodeFrame(csId, D_80748244[p[8]].b, 1, 0);
            func_80609140(0x2A2, 0x7FFF, 63.0f, 1.0f, 0, 0);
        }
        p[6] ^= 1;
    }
}

void func_8064AAC4(CsState *cs, s16 csId, s16 b, s16 c) {
    func_806BD094(((CsB9Slot *)D_807F6000)[hashTableLookup(csId)].unk8A, b);
}

extern ActorEntry gActiveActors[];
extern u16 gActiveActorCount;
void modelAnimEntryStart(s16, s16, s16);
void func_80641874(s16, s16);

s32 func_8064AB1C(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 i;
    Actor *actor;

    for (i = 0; i < gActiveActorCount; i++) {
        actor = gActiveActors[i].actor;
        if (!(actor->unk60 & 0x2000) && actor->unk58 == 4 && actor->unk110 == 1 && csId == actor->unk10C) {
            if (b != actor->unk10E[0] && actor->unk10E[0] != 0) {
                modelAnimEntryStart(csId, actor->unk10E[0], 2);
                func_80641874(actor->unk10E[0] + 4, 0);
                return 1;
            }
        }
    }
    return 0;
}


#ifdef NON_MATCHING
void modelAnimEntryGetState(s16, s16, s16 *, f32 *, u8 *);
void modelAnimEntrySetTime(s16, s16, s16, f32);
void modelAnimEntrySetUnkC(s16, s16, s16);
void func_806086CC(f32, f32, f32, s16, s32, s32, s32, s32, f32, s32);
void func_8063DA40(s16, s16);
extern u8 D_8074E77C;
typedef struct CsB10Part {
    /* 0x0 */ u8 state;
    /* 0x1 */ u8 pad1;
    /* 0x2 */ s16 timer;
    /* 0x4 */ u8 active;
    /* 0x5 */ u8 pad5;
} CsB10Part;
typedef struct CsB10W {
    /* 0x00 */ u8 pad0[0x18];
    /* 0x18 */ u8 state;
    /* 0x19 */ u8 pad19;
    /* 0x1A */ s16 timer;
    /* 0x1C */ u8 active;
} CsB10W;
typedef struct CsB10Set {
    /* 0x00 */ u8 pad0[0x18];
    /* 0x18 */ CsB10Part part[9];
    /* 0x4E */ u8 unk4E;
    /* 0x4F */ u8 unk4F;
} CsB10Set;
void func_8064AC28(CsState *cs, s16 csId, s16 b, s16 c) {
    CsB10Set *p;
    CsB10W *e;
    s16 j;
    s16 anim;
    f32 animT;
    u8 animFlag;
    s32 i;
    Actor *pl;
    s32 best;
    u8 allDone = 1;
    u8 n = 0;
    f32 x;
    f32 y;
    f32 z;
    f32 d;
    f32 bestD;

    if (*(CsB10Set **)cs == NULL) {
        p = *(CsB10Set **)cs = func_80610FE8(0x50);
        p->unk4E = 0;
        if (flagGet(0x146, 0) != 0) {
            e = (CsB10W *)p;
            for (i = 0; i < 9; i++) { e->state = 3; e = (CsB10W *)((u8 *)e + 6); }
        } else {
            p->part[2].state = 2;
            p->part[5].state = 2;
            p->part[7].state = 2;
            p->part[0].state = 0;
            p->part[1].state = 3;
            p->part[3].state = 0;
            p->part[4].state = 1;
            p->part[6].state = 3;
            p->part[8].state = 1;
        }
        p->part[0].timer = 10;
        p->part[0].active = 1;
        for (i = 1, e = (CsB10W *)((u8 *)p + 6); i < 9; i++, e = (CsB10W *)((u8 *)e + 6)) {
            e->active = 1;
            e->timer = 10;
        }
        p->unk4F = 0;
    }
    p = *(CsB10Set **)cs;
    for (i = 0, e = (CsB10W *)p; i < 9; i++, e = (CsB10W *)((u8 *)e + 6)) {
        if (e->active != 0) {
            j = i + 1;
            n++;
            modelAnimEntryGetState(csId, j, &anim, &animT, &animFlag);
            if (anim == e->state && animT < 0.1 && e->timer == 0) {
                modelAnimEntrySetUnkC(csId, j, 0);
                modelAnimEntrySetTime(csId, j, anim, 0);
                e->active = 0;
                modelSlotGetNodePos(csId, 1, i + 1, &x, &y, &z);
                func_806086CC(x, y, z, 0x1AE, 0xFF, 0x7F, 0x14, 0x50, 0.7f, 0);
            }
            if (e->timer != 0) {
                e->timer--;
            }
        }
        if (e->active != 0 || e->state != 3) {
            allDone = 0;
        }
    }
    if (flagGet(0x146, 0) != 0) {
        p->unk4F = 0x14;
    }
    if (p->unk4F == 0) {
        pl = D_807FC924->unk4;
        if (pl->unk154 == 0x1C && pl->unk155[0] < 7 && D_8074E77C == 0 && pl->unk110 == 1) {
            if (csId == pl->unk10C) {
                bestD = 100000.0f;
                best = -1;
                i = 0;
                do {
                    modelSlotGetNodePos(csId, 1, i + 1, &x, &y, &z);
                    x = D_807FBB4C->unk7C - x;
                    z = D_807FBB4C->unk84 - z;
                    d = x * x + z * z;
                    if (d < bestD) {
                        best = i;
                        bestD = d;
                    }
                    i++;
                } while (i != 9);
                if (best >= 0) {
                    e = (CsB10W *)((u8 *)p + best * 6);
                    e->state++;
                    e->state %= 4;
                    e->active = 1;
                    modelAnimEntrySetUnkC(csId, best + 1, 0x19);
                    p->unk4F = 0x14;
                }
            }
        }
    }
    if (p->unk4F != 0) {
        p->unk4F--;
    }
    if (allDone != 0) {
        func_8063DA40(0xF, 0xA);
        heapFreeDeferred(*(void **)cs);
        cs->unk4B[0] = 0x28;
        *(void **)cs = NULL;
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064AC28.s")
#endif

void func_8002D6F8(s16);
void func_8064B118(CsState *cs, s16 csId, s16 b, s16 c) {
    func_8002D6F8(csId);
}

void func_8064B150(CsState *cs, s16 csId, s16 b, s16 c) {
    cs->unk14[b] = cs->unk14[b] + cs->unk14[c];
}

void func_8064B190(CsState *cs, s16 csId, s16 b, s16 c) {
    f32 t = -10.0 - cs->unk14[b];
    t = t / -10.0;
    cs->unk14[c] = t * -1.0;
}

void func_8064B204(CsState *cs, s16 csId, s16 b, s16 c) {
    cs->unk14[b] = -1.0 - cs->unk14[b];
    cs->unk14[b] = 0.0 - cs->unk14[b];
}

typedef struct CsB10Pos {
    /* 0x000 */ u8 pad0[0x100];
    /* 0x100 */ f32 x;
    /* 0x104 */ f32 y;
    /* 0x108 */ f32 z;
} CsB10Pos;
void func_8064B260(CsState *cs, s16 csId, s16 b, s16 c) {
    cs->unk14[b] = ((CsB10Pos *)D_807FBB4C)->x;
    cs->unk14[b + 1] = ((CsB10Pos *)D_807FBB4C)->y;
    cs->unk14[b + 2] = ((CsB10Pos *)D_807FBB4C)->z;
}

extern f32 D_807F6228;
extern f32 D_807F6230;
extern f32 D_807F6238;
typedef struct CsB10Saved {
    /* 0x00 */ f32 v[10];
} CsB10Saved;
void func_8064B2AC(CsState *cs, s16 csId, s16 b, s16 c) {
    CsB10Saved *p;

    if (*(CsB10Saved **)cs == NULL) {
        *(CsB10Saved **)cs = func_80610FE8(0x28);
    }
    p = *(CsB10Saved **)cs;
    p->v[0] = D_807F621C;
    p->v[1] = D_807F6220;
    p->v[2] = D_807F6224;
    p->v[3] = D_807F6228;
    p->v[4] = D_807F622C;
    p->v[5] = D_807F6230;
    p->v[6] = D_807F6234;
    p->v[7] = D_807F6234;
    p->v[8] = D_807F6234;
    p->v[9] = D_807F6238;
}

void func_8064B370(CsState *cs, s16 csId, s16 b, s16 c) {
    CsB10Saved *p = *(CsB10Saved **)cs;

    D_807F621C = p->v[0];
    D_807F6220 = p->v[1];
    D_807F6224 = p->v[2];
    D_807F6228 = p->v[3];
    D_807F622C = p->v[4];
    D_807F6230 = p->v[5];
    D_807F6234 = p->v[6];
    D_807F6234 = p->v[7];
    D_807F6234 = p->v[8];
    D_807F6238 = p->v[9];
}

void func_8064B3F8(CsState *cs, s16 csId, s16 b, s16 c) {
    CsB10Saved *p = *(CsB10Saved **)cs;
    s32 idx;
    f32 sx;
    f32 sy;
    f32 sz;

    idx = hashTableLookup(csId);
    sx = D_807F6000[idx].x;
    sy = D_807F6000[idx].y;
    sz = D_807F6000[idx].z;

    cs->unk14[c] = (p->v[0] - sx) / b;
    cs->unk14[c + 1] = (p->v[1] - sy) / b;
    cs->unk14[c + 2] = (p->v[2] - sz) / b;
}

extern s16 D_807F6240[];
void func_8064B4AC(CsState *cs, s16 csId, s16 b, s16 c) {
    modelSlotGetNodePos(D_807F6240[b], 1, c, &D_807F621C, &D_807F6220, &D_807F6224);
}

void func_806FAC64(u8);
void slotQueueCancel(s32, s32);
void slotQueueUpdate(s32, u8, s32);
void func_8064B514(CsState *cs, s16 csId, s16 b, s16 c) {
    func_806FAC64(b);
    if (c != 0) {
        slotQueueCancel(0xD, 0);
    } else {
        slotQueueUpdate(0xD, 1, 0);
    }
}

void func_80726EE0(u8);
void func_8064B574(CsState *cs, s16 csId, s16 b, s16 c) {
    func_80726EE0(3);
}

extern f32 D_80748280[];
extern f32 D_8074828C[];
extern f32 D_807482A4;
extern s32 D_807F6C28;
void lightGetColor(f32 *, f32 *, f32 *, s16);
void func_8064B5A4(CsState *cs, s16 csId, s16 b, s16 c) {
    f32 r, g, bl;
    s32 i;
    if (c != 0) {
        for (i = 0; i < D_807F6C28; i++) {
            lightSetColor(D_80748280[0], D_80748280[1], D_80748280[2], (s16)i);
        }
    } else {
        lightGetColor(&r, &g, &bl, 0);
        if (b != 0) {
            r += D_807482A4;
            g += D_807482A4;
            if (D_8074828C[0] < r) {
                r = D_8074828C[0];
            }
            if (D_8074828C[1] < g) {
                g = D_8074828C[1];
            }
            bl += D_807482A4;
            if (D_8074828C[2] < bl) {
                bl = D_8074828C[2];
            }
        } else {
            r -= D_807482A4;
            g -= D_807482A4;
            if (r < D_80748280[0]) {
                r = D_80748280[0];
            }
            if (g < D_80748280[1]) {
                g = D_80748280[1];
            }
            bl -= D_807482A4;
            if (bl < D_80748280[2]) {
                bl = D_80748280[2];
            }
        }
        for (i = 0; i < D_807F6C28; i++) {
            lightSetColor(r, g, bl, (s16)i);
        }
    }
}

void func_8064B798(CsState *cs, s16 csId, s16 b, s16 c) {
    u8 *p = D_807FC924->unk4->unk174;
    p[0x1FC] = b;
}

void func_8064B7C0(CsState *cs, s16 csId, s16 b, s16 c) {
}

void func_8064B7D4(CsState *cs, s16 csId, s16 b, s16 c) {
}

void effectNodeSetUnk4A(s32, u8);
void effectNodeSetUnk4B(s32, u8);
u8 effectNodeGetUnk4B(s32);
void func_8064B7E8(CsState *cs, s16 csId, s16 b, s16 c) {
    effectNodeSetUnk4A(5, 1);
    effectNodeSetUnk4A(6, 1);
}

void func_8064B828(CsState *cs, s16 csId, s16 b, s16 c) {
    effectNodeSetUnk4B(5, 0xFF);
    effectNodeSetUnk4B(6, 0xFF);
}

void func_8064B868(CsState *cs, s16 csId, s16 b, s16 c) {
    u8 v = effectNodeGetUnk4B(5);
    effectNodeSetUnk4B(5, v < 0xFC ? v + 3 : 0xFF);
    effectNodeSetUnk4B(6, v < 0xFC ? v + 3 : 0xFF);
    effectNodeSetUnk4A(5, 0);
    effectNodeSetUnk4A(6, 0);
}

extern Actor *D_807FBB44;
Actor *spawnNodeSpawnById(s16, s16, s16, s16, s16, s16, s16);
Actor *spawnNodeActivate(s16, u16);
void actorScriptStart(void *, s32);
void func_80614D00(void *, f32, f32);
void func_8064B900(CsState *cs, s16 csId, s16 b, s16 c) {
    Actor *a;
    switch (b) {
        case 2:
            spawnNodeSpawnById(8, 0, 0, 0, 0, 0, 0);
            D_807FBB44->unk60 &= ~4;
            break;
        case 1:
            a = spawnNodeActivate(8, 0);
            if (a != NULL) {
                a->unk60 |= 4;
                actorScriptStart(a, 0x35C);
                func_80614D00(a, 0.9f, 0.0f);
            }
            break;
        case 0:
            a = spawnNodeActivate(8, 0);
            if (a != NULL) {
                a->unk154 = 0x3C;
            }
            break;
    }
}

void actorListSetPosById(s16, f32, f32, f32);

void func_8064B9E0(CsState *cs, s16 csId, s16 b, s16 c) {
    s16 x, y, z;
    switch (b) {
        case 0:
            x = 0x3A4; y = 6; z = 0x16A;
            break;
        case 1:
            x = 0x439; y = 0x7A; z = 0x20A;
            break;
        case 2:
            x = 0x35D; y = 0x7A; z = 0x237;
            break;
        case 3:
            x = 0x502; y = 0x11; z = 0x120;
            break;
        case 4:
            x = 0x28A; y = 0x12; z = 0x172;
            break;
    }
    actorListSetPosById(5, (f32)x, (f32)y, (f32)z);
}

s32 func_8064BAF4(CsState *cs, s16 csId, s16 b, s16 c) {
    return (u8)(cs->unk14[b] < cs->unk14[c]);
}

void func_8064BB4C(CsState *cs, s16 csId, s16 b, s16 c) {
    func_805FF0C8();
}

void func_8064BB78(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 idx = func_805FF030(D_8076A0AB, 0);
    if (idx >= 8) {
        idx = 0;
    }
    flagGet(D_80744710[idx], 0);
}

s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
s32 mathAngleDistance(s16, s16);

s32 func_8064BBD8(CsState *cs, s16 csId, s16 b, s16 c) {
    s16 ang = mathAngleBetweenPoints2D((s16)D_807F621C, (s16)D_807F6224, (s16)D_807FBB4C->unk7C, (s16)D_807FBB4C->unk84);
    return (u8)(mathAngleDistance(ang, D_807FBB4C->unkE6) < 0x384);
}

typedef struct CsB12Player {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 pad1[3];
    /* 0x04 */ Actor *unk4;
    /* 0x08 */ u8 pad8[0x2E8];
} CsB12Player; /* 0x2F0 */
extern u8 D_807FC928;

s32 func_8064BCB0(s32 a, s32 b) {
    s32 i = 0;
    CsB12Player *p;
    Actor *q;
    if (D_807FC928 > 0) {
        p = (CsB12Player *)D_807FC924;
        do {
            if (p->unk0 != 0) {
                q = p->unk4;
                if (q->unk110 == 1 && q->unk10C == a && q->unk10E[0] == b) {
                    return i;
                }
            }
            i++;
            p++;
        } while (i < D_807FC928);
    }
    return -1;
}

void modelSlotGetTransformVectors();
void func_8067ABC0(s32, void *, s32, s16, s32, f32, f32, f32);

s32 func_8064BD2C(CsState *cs, s16 csId, s16 b, s16 c) {
    f32 x, y, z;
    f32 u50, u4C, u48, u44, u40;
    s32 id;
    s32 idx;
    u32 pad0;
    u32 pad1;

    idx = func_8064BCB0(csId, c);
    if (idx < 0) {
        return 0;
    }
    id = D_807F6240[b];
    if (func_8064BCB0(id, c) != -1) {
        return 0;
    }
    modelSlotGetTransformVectors(id, &x, &y, &z, &u50, &u4C, &u48, &u44, &u40, 1);
    func_8067ABC0(0, ((CsB12Player *)D_807FC924 + idx)->unk4, 9, (s16)(s32)(u4C * 11.377778f), 0, x, y, z);
    return 0;
}

extern s32 D_807552E8;

s32 func_8064BE58(CsState *cs, s16 csId, s16 b, s16 c) {
    return (D_807552E8 == 5) & 0xFF;
}

extern s32 D_807552F0;
s32 func_806F8AD4(s32, u8);
void func_806F91B4(s32, u8, s16);

s32 func_8064BE80(CsState *cs, s16 csId, s16 b, s16 c) {
    f32 q;
    s32 idx = func_8064BCB0(csId, b);
    if (idx < 0) {
        return 0;
    }
    if (func_806F8AD4(1, (u8)idx)) {
        func_806F91B4(7, (u8)idx, 1);
        q = (f32)func_806F8AD4(7, (u8)idx) / (f32)D_807552F0;
        q = (f32)0.5 * q + 0.5f;
        func_80609140(0x2A1, 0x7FFF, 63.0f, q, 5, 0);
        return 1;
    }
    return 0;
}

s32 func_8064BF58(CsState *cs, s16 csId, s16 b, s16 c) {
    f64 dz = ((CsB2Player *)D_807FC924)->unk218 - 1274.0;
    f64 dx = ((CsB2Player *)D_807FC924)->unk210 - 3081.0;
    if (dz * dz + dx * dx < 10000.0) {
        return 1;
    }
    return 0;
}

void func_8064BFD0(CsState *cs, s16 csId, s16 b, s16 c) {
    f32 absv;
    f32 ratio;

    if (cs->unk14[b] > 0.0f) {
        absv = cs->unk14[b];
    } else {
        absv = -cs->unk14[b];
    }
    ratio = (f64)absv / cs->unk14[c + 1];
    if (cs->unk14[b] > 0.0) {
        if (cs->unk14[c] < ratio) {
            cs->unk14[c] = cs->unk14[c] + 0.1;
        }
    } else if (-ratio < cs->unk14[c]) {
        cs->unk14[c] = cs->unk14[c] - 0.1;
    }
    D_807F6228 += cs->unk14[c];
    if (D_807F6228 > 8.0) {
        D_807F6228 = 8.0f;
    }
    if (D_807F6228 < -8.0) {
        D_807F6228 = -8.0f;
    }
}

void func_8064C134(CsState *cs, s16 csId, s16 b, s16 c) {
    if (D_807F6228 > 1.2 || D_807F6228 < -1.2) {
        if (D_807F6228 > 0.0) {
            if (cs->unk14[b] > -1.0) {
                cs->unk14[b] = cs->unk14[b] - 0.1;
            }
        } else if (cs->unk14[b] < 1.0) {
            cs->unk14[b] = cs->unk14[b] + 0.1;
        }
        D_807F6228 += cs->unk14[b];
    } else {
        D_807F6228 = 0.0f;
        cs->unk14[b] = 0.0f;
    }
}

void actorSpawnNodeEntryScaled(s32, f32, f32, f32, s32, s32, s32, s32);

void func_8064C250(CsState *cs, s16 csId, s16 b, s16 c) {
    actorSpawnNodeEntryScaled(0x2F, D_807F621C, D_807F6220 + 15.0f, D_807F6224, 0, 1, -1, 0);
    actorSpawnNodeEntryScaled(0x2F, D_807F621C, D_807F6220 + 15.0f, D_807F6224, 0x400, 1, -1, 0);
    actorSpawnNodeEntryScaled(0x2F, D_807F621C, D_807F6220 + 15.0f, D_807F6224, 0x800, 1, -1, 0);
    actorSpawnNodeEntryScaled(0x2F, D_807F621C, D_807F6220 + 15.0f, D_807F6224, 0xC00, 1, -1, 0);
    func_807149B8(1);
    func_80714CC0(D_8071FFA0, 2.5f, D_807F621C, D_807F6220 + 30.0f, D_807F6224);
}

void modelAnimEntryGetState(s16, s16, s16 *, f32 *, u8 *);
typedef struct CsB13Cam {
    /* 0x000 */ u8 pad0[0x104];
    /* 0x104 */ s32 unk104;
} CsB13Cam;
typedef struct CsB13Shake {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ s32 unk4;
} CsB13Shake;
void camStartShakeFromPoint(s32, s32, s32, f32, f32, f32, f32, f32);

void func_8064C3E8(CsState *cs, s16 csId, s16 b, s16 c) {
    u32 pad[4];
    s16 pad16;
    s16 anim;
    f32 animT;
    u8 animFlag;
    CsB13Shake *p;
    CsB13Cam *cam;

    cam = D_807FC924->unk4->unk174;
    if (*(CsB13Shake **)cs == NULL) {
        p = func_80610FE8(8);
        *(CsB13Shake **)cs = p;
        p->unk0 = 0;
        p->unk4 = 0;
    }
    p = *(CsB13Shake **)cs;
    modelAnimEntryGetState(csId, 1, &anim, &animT, &animFlag);
    if (anim == 0) {
        p->unk4 = 10;
    }
    if (anim == 2 && animT >= 0.8) {
        if (p->unk4 != 0) {
            camStartShakeFromPoint(cam->unk104, 4, 0xB, D_807F621C, D_807F6220, D_807F6224, 200.0f, 600.0f);
            p->unk4--;
        }
    } else {
        p->unk0 = 0;
    }
    if (anim == 2) {
        cs->unk6E = 1;
    } else {
        cs->unk6E = 0;
    }
}

extern s16 D_80770628[];
extern f32 D_80770B68[];
extern f32 D_80770BC0[];

void func_8064C544(CsState *cs, s16 csId, s16 b, s16 c) {
    s16 anim;
    f32 animT;
    u8 animFlag;
    u8 slot;

    if (cs->unk10[0] >= 0) {
        modelAnimEntryGetState(csId, b, &anim, &animT, &animFlag);
        slot = D_80770628[cs->unk10[0]];
        D_80770B68[slot] = func_80612794((s16)(((f32)anim + animT) * 2048.0 - 1024.0)) * 0.3 + 1.3;
        D_80770BC0[slot] = 1.0f;
    }
}

void func_8064C644(CsState *cs, s16 csId, s16 b, s16 c) {
    s16 anim;
    f32 animT;
    u8 animFlag;
    u8 slot;

    if (cs->unk10[0] >= 0) {
        modelAnimEntryGetState(csId, 1, &anim, &animT, &animFlag);
        slot = D_80770628[cs->unk10[0]];
        D_80770B68[slot] = func_80612794((s16)((anim << 11) / 27)) + 0.3;
        D_80770BC0[slot] = 2.0f;
    }
}


void func_8064C708(CsState *cs, s16 csId, s16 b, s16 c) {
    s16 anim;
    f32 animT;
    u8 animFlag;
    s32 *p;

    if (*(s32 **)cs == NULL) {
        *(s32 **)cs = func_80610FE8(4);
        **(s32 **)cs = 0;
    }
    p = *(s32 **)cs;
    modelAnimEntryGetState(csId, 1, &anim, &animT, &animFlag);
    if (*p == 0xB) {
        if (anim == 3) {
            *p = 3;
            sfxPlayFromTargetSlot(csId, 0x257, 0x78, 0x7F, 0xA, 0x50, 0.3f);
        }
    } else if (anim == 0xB) {
        *p = 0xB;
        sfxPlayFromTargetSlot(csId, 0x258, 0x78, 0x7F, 0xA, 0x50, 0.3f);
    }
}

void func_806086CC(f32, f32, f32, s16, s32, s32, s32, s32, f32, s32);

void func_8064C814(CsState *cs, s16 csId, s16 b, s16 c) {
    f32 x;
    f32 y;
    f32 z;
    s16 anim;
    f32 animT;
    u8 animFlag;
    CsB13Shake *p;

    if (*(CsB13Shake **)cs == NULL) {
        p = func_80610FE8(8);
        *(CsB13Shake **)cs = p;
        p->unk0 = 0;
        p->unk4 = 0;
    }
    p = *(CsB13Shake **)cs;
    modelAnimEntryGetState(csId, 2, &anim, &animT, &animFlag);
    anim = (f32)anim + animT;
    if (anim == 0x28 || anim == 0x32) {
        if (anim != p->unk0) {
            p->unk0 = anim;
            modelSlotGetNodePos(csId, 1, 3, &x, &y, &z);
            func_806086CC(x, y, z, 0x32, 0xFF, 0x7F, 0xA, 0x50, 0.3f, 0);
        }
    }
    modelAnimEntryGetState(csId, 3, &anim, &animT, &animFlag);
    if (anim == 0x14 || anim == 0x18) {
        if (anim != p->unk4) {
            p->unk4 = anim;
            modelSlotGetNodePos(csId, 1, 2, &x, &y, &z);
            func_806086CC(x, y, z, 0x332, 0xFF, 0x7F, 0, 0x50, 0.3f, 0);
        }
    }
}

void func_8064C9F8(CsState *cs, s16 csId, s16 b, s16 c) {
    f32 x;
    f32 y;
    f32 z;
    s16 anim;
    f32 animT;
    u8 animFlag;
    s32 *p;

    if (*(s32 **)cs == NULL) {
        *(s32 **)cs = func_80610FE8(4);
        **(s32 **)cs = 0;
    }
    p = *(s32 **)cs;
    modelAnimEntryGetState(csId, 2, &anim, &animT, &animFlag);
    anim = (f32)anim + animT;
    if (anim == 0x22 || anim == 0x2E) {
        if (anim != *p) {
            *p = anim;
            modelSlotGetNodePos(csId, 1, 2, &x, &y, &z);
            func_806086CC(x, y, z, 0x257 + (anim == 0xA), 0xFF, 0x7F, 0xA, 0x50, 0.3f, 0);
        }
    }
}

void func_8064CB3C(CsState *cs, s16 csId, s16 b, s16 c) {
    f32 x;
    f32 y;
    f32 z;
    s16 anim;
    f32 animT;
    u8 animFlag;
    s32 *p;

    if (*(s32 **)cs == NULL) {
        *(s32 **)cs = func_80610FE8(4);
        **(s32 **)cs = 0;
    }
    p = *(s32 **)cs;
    modelAnimEntryGetState(csId, 2, &anim, &animT, &animFlag);
    anim = (f32)anim + animT;
    if (anim != *p) {
        switch (anim) {
            case 0:
            case 0xC:
            case 0x18:
            case 0x24:
                *p = anim;
                modelSlotGetNodePos(csId, 1, 2, &x, &y, &z);
                func_806086CC(x, y, z, 0x3A, 0x50, 0x7F, 0, 0x50, 0.3f, 0);
                break;
        }
    }
}

void func_8064CC80(CsState *cs, s16 csId, s16 b, s16 c) {
    s16 anim;
    f32 animT;
    u8 animFlag;
    s32 *p;

    if (*(s32 **)cs == NULL) {
        *(s32 **)cs = func_80610FE8(4);
        **(s32 **)cs = 0x64;
    }
    p = *(s32 **)cs;
    modelAnimEntryGetState(csId, 1, &anim, &animT, &animFlag);
    if (anim != *p) {
        *p = anim;
        sfxPlayFromTargetSlot(csId, 0x129, 0xFF, 0x7F, 3, 0x50, 0.3f);
    }
}

typedef struct {
    f32 x, y, z;
} CsB14Pt;

typedef struct {
    CsB14Pt pts[30];
    s32 anim[2];
} CsB14Trail;

extern f32 D_807F61FC;
extern f32 D_807F6200;
extern f32 D_807F6204;
extern s16 D_807482B0;
f32 mathAngleBetweenPointsRad(f32, f32, f32, f32);
u8 collisionGetFloorHeight(f32 *);

void func_8064CD3C(CsState *cs, s16 csId, s16 b, s16 c) {
    u32 pad0;
    u32 pad1;
    u32 pad2;
    CsB14Trail *tr;
    s16 idx;
    s16 prev;
    s32 i;
    s32 snd;
    f32 groundY;
    f32 floorY;
    s16 pad3;
    s16 anim;
    f32 animT;
    u8 animFlag;
    CsB14Pt *pts;

    if (*(CsB14Trail **)cs == NULL) {
        tr = func_80610FE8(0x170);
        *(CsB14Trail **)cs = tr;
        for (i = 0; i < 30; i++) { tr->pts[i].x = D_807F61FC; tr->pts[i].y = D_807F6200; tr->pts[i].z = D_807F6204; }
    }
    tr = *(CsB14Trail **)cs;
    pts = tr->pts;
    groundY = D_807F6220;
    if (collisionCheckGroundAtPoint(D_807F621C, D_807F6224, &groundY)) {
        if (collisionGetFloorHeight(&floorY)) {
            D_807F6220 = floorY;
        }
    } else {
        prev = D_807482B0 - 1;
        if (prev < 0) {
            prev = 29;
        }
        D_807F6220 = pts[prev].y;
    }
    tr->pts[D_807482B0].x = D_807F621C;
    tr->pts[D_807482B0].y = D_807F6220;
    tr->pts[D_807482B0].z = D_807F6224;
    idx = D_807482B0 + 1;
    if (idx == 30) {
        idx = 0;
    }
    D_807F622C = mathAngleBetweenPointsRad(pts[idx].x, pts[idx].z, D_807F621C, D_807F6224) * 57.29577637f + 270.0;
    if (D_807F622C > 360.0) {
        D_807F622C -= 360.0;
    }
    D_807482B0 = idx;
    snd = 0x15;
    for (i = 0; i < 2; i++) {
        modelAnimEntryGetState(csId, i + 1, &anim, &animT, &animFlag);
        if (anim != tr->anim[i]) {
            tr->anim[i] = anim;
            if (anim == 0) {
                sfxPlayFromTargetSlot(csId, (s16)snd, 0xFF, 0x7F, 3, 0x46, 0.3f);
            }
        }
        snd = 0x14;
    }
}

u8 modelAnimEntryIsActive(s16, s16);
void modelAnimEntryStop(s16, s16);

void func_8064D0C4(CsState *cs, s16 csId, s16 b, s16 c) {
    f32 ceil;
    f32 floor;
    u8 active;
    u8 state;

    state = 2;
    ceil = D_807F6220 + 20.0f;
    if (collisionCheckGroundAtPoint(D_807F621C, D_807F6224, &ceil) != 0 && collisionGetFloorHeight(&floor) != 0) {
        if (floor < ceil) {
            state = 0;
            D_807F6220 = ceil;
        } else {
            state = 1;
            D_807F6220 = floor;
        }
    }
    if (b != 0) {
        active = modelAnimEntryIsActive(csId, 1);
        if (state == 1 && active == 0) {
            modelAnimEntryStart(csId, 1, -1);
            modelAnimEntryStart(csId, 2, -1);
            return;
        }
        if (state == 0 && active != 0) {
            modelAnimEntryStop(csId, 1);
            modelAnimEntryStop(csId, 2);
        }
    }
}

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} CsB14State;

void effectNodeSetTargetAndStep(s32, f32, f32);

void func_8064D1E8(CsState *cs, s16 csId, s16 b, s16 c) {
    CsB14State *p;
    CsB14State *t;
    s32 ang;
    s32 d;
    s32 e;

    if (*(CsB14State **)cs == NULL) {
        t = func_80610FE8(0xC);
        *(CsB14State **)cs = t;
        t->unk0 = 0;
        t->unk4 = 0;
        t->unk8 = 0xDAC;
    }
    p = *(CsB14State **)cs;
    effectNodeSetTargetAndStep(0, func_80612794(p->unk8) * 60.0 + 40.0, 20.0f);
    if (p->unk0 == 0) {
        ang = p->unk8;
        if (ang >= 0x2BC && ang < 0x2C6) {
            func_80609140(0x359, 0x7FFF, 63.0f, 0.6f, 0, 0);
            ang = p->unk8;
        }
        if ((ang >= 0x2EE && ang < 0x2F8) || (ang >= 0x960 && ang < 0x96A)) {
            if (cs->unk10[0] >= 0) {
                func_80605380(cs->unk10[0]);
                cs->unk10[0] = -1;
                ang = p->unk8;
            }
        }
        if ((ang >= 0x410 && ang < 0x41A) || (ang >= 0xE74 && ang < 0xE7E)) {
            cs->unk10[0] = sfxSlotAllocateSource(csId, 0x138, 1, 1, 0x78, 1.0f, -1);
            ang = p->unk8;
        }
        e = ang - 0x400 > 0 ? ang - 0x400 : 0x400 - ang;
        if (e < 10 || (d = ang - 0xC00 > 0 ? ang - 0xC00 : 0xC00 - ang, d < 10)) {
            if (p->unk4 == 0) {
                p->unk0 = 0x12C;
            }
        }
        if (p->unk4 != 0) {
            p->unk4--;
        }
        p->unk8 = (p->unk8 + 10) & 0xFFF;
    } else {
        p->unk0--;
        if (p->unk0 == 0) {
            p->unk4 = 10;
        }
    }
}

void modelAnimEntrySetTime(s16, s16, s16, f32);
void modelAnimEntrySetUnkC(s16, s16, s16);
s16 func_80650A70(s16, s16);
extern s32 D_807482B4;
extern s32 D_807482B8;
extern s32 D_807482BC;
extern s32 D_807482C0;
extern s32 D_807482C4;
extern s32 D_807482C8;
extern f32 D_807482CC;
extern s32 D_807482D0;
extern f32 D_807482D8;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
} CsB14Beat;

typedef struct {
    u8 pad0[0x48];
    u8 unk48;
    u8 pad49[2];
    u8 unk4B;
} CsB14View;

void func_8064D418(CsState *cs, s16 csId, s16 b, s16 c) {
    CsB14Beat *p;
    s16 frame;
    s16 anim;
    CsB14Beat *t;
    f32 animT;
    f32 target;
    u8 animFlag;
    f32 d;

    if (*(CsB14Beat **)cs == NULL) {
        t = func_80610FE8(0x18);
        *(CsB14Beat **)cs = t;
        t->unk0 = 0;
        t->unk4 = 0;
        t->unk8 = 0;
        t->unkC = D_807482C4;
        t->unk10 = 0;
        t->unk14 = 0x14;
    }
    p = *(CsB14Beat **)cs;
    frame = func_80650A70(csId, 1);
    switch (p->unk0) {
        case 0:
            if (p->unk4 == 0) {
                p->unk4 = D_807482B8;
                frame = frame + D_807482D0;
                modelAnimEntrySetUnkC(csId, 1, frame);
                if (frame >= D_807482B4) {
                    p->unk0 = 1;
                    p->unk4 = D_807482BC;
                }
            } else {
                p->unk4--;
            }
            break;
        case 1:
            p->unk4--;
            if (p->unk4 == 0) {
                p->unk0 = 2;
            }
            break;
        case 2:
            if (D_807482C0 < frame) {
                frame = frame - 1;
                modelAnimEntrySetUnkC(csId, 1, frame);
            } else {
                modelAnimEntryGetState(csId, 1, &anim, &animT, &animFlag);
                if (p->unk8 != 0) {
                    target = 0.5f;
                } else {
                    target = D_807482D8;
                }
                d = target < animT ? animT - target : -(animT - target);
                if (d < D_807482CC) {
                    modelAnimEntrySetUnkC(csId, 1, 0);
                    modelAnimEntrySetTime(csId, 1, anim, target);
                    p->unk0 = 3;
                    p->unk4 = p->unkC;
                    p->unk8 ^= 1;
                    modelAnimEntryStart(csId, 2, 1);
                }
            }
            break;
        case 3:
            p->unk4--;
            if (((CsB14View *)cs)->unk48 == 2) {
                p->unk4 = 0;
                ((CsB14View *)cs)->unk4B = 1;
                p->unkC = p->unkC - D_807482C8;
            }
            if (p->unk4 == 0) {
                p->unk0 = 0;
                p->unk4 = 0;
                modelAnimEntryStart(csId, 2, 1);
            }
            break;
    }
    modelAnimEntryGetState(csId, 1, &anim, &animT, &animFlag);
    if (p->unk10 != (anim & 2)) {
        sfxPlayFromTargetSlot(csId, 0x1DF, 0xFF, (u8)(frame * 0.25 + 5.0), 0, 0x50, 0.3f);
        p->unk10 = anim & 2;
    }
    p->unk14--;
    if (p->unk14 <= 0) {
        func_80609140((s16)(0x34E + ((randomNonNegative() >> 15) % 100 >= 0x33)), 0x7FFF, 63.0f, 1.0f, 0x1E, 0);
        p->unk14 = (randomNonNegative() >> 15) % 30 + 0x3C;
    }
}


void func_8064D880(CsState *cs, s16 csId, s16 b, s16 c) {
    f32 t;
    s32 idx;

    idx = func_805FF030(D_8076A0AB, 0);
    t = (f32)(u32)D_807FC930[idx] / (f32)(u32)D_807446C0[idx];
    if (t > 1.0) {
        t = 1.0f;
    }
    if (b == 0) {
        t = 1.0f - t;
    }
    modelAnimEntrySetTime(csId, 1, 0, t);
    modelAnimEntrySetUnkC(csId, 1, 0);
}


void func_8064D978(CsState *cs, s16 csId, s16 b, s16 c) {
    s16 anim;
    f32 cur;
    u8 flag;
    f32 ratio;
    u8 idx;

    idx = func_805FF030(D_8076A0AB, 0);
    ratio = (f32)D_807FC930[idx] / (f32)D_807446C0[idx];
    if (ratio > 1.0) {
        ratio = 1.0f;
    }
    if (b == 0) {
        ratio = 1.0f - ratio;
    }
    modelAnimEntryGetState(csId, 1, &anim, &cur, &flag);
    modelAnimEntrySetUnkC(csId, 1, 0);
    if (cur > ratio) {
        cur = cur - 0.1;
        if (cur < ratio) {
            cur = ratio;
        }
    } else {
        cur = cur + 0.1;
        if (ratio < cur) {
            cur = ratio;
        }
    }
    if (b != 0) {
        if (cur >= 0.999 && ratio >= 0.999) {
            ((u8 *)cs)[0x48] = 0x14;
        }
    } else {
        if (cur <= 0.001 && ratio <= 0.001) {
            ((u8 *)cs)[0x48] = 0x14;
        }
    }
    modelAnimEntrySetTime(csId, 1, anim, cur);
    modelAnimEntryStart(csId, 1, 1);
}

void func_8064DB98(CsState *cs, s16 csId, s16 b, s16 c) {
    s16 anim;
    f32 t;
    u8 flag;
    s32 *p;
    f32 v;
    f32 w;

    if (*(s32 **)cs == NULL) {
        p = func_80610FE8(4);
        *(s32 **)cs = p;
        *p = 0;
    }
    p = *(s32 **)cs;
    modelAnimEntryGetState(csId, 1, &anim, &t, &flag);
    if (anim != *p) {
        switch (anim) {
            case 0xF:
                func_806086CC(D_807F6000[csId].x, D_807F6000[csId].y + 300.0f, D_807F6000[csId].z, 0x8E, 0xFF, 0x50, 0, 0x50, 0.3f, 0);
                break;
            case 0:
                func_806086CC(D_807F6000[csId].x, D_807F6000[csId].y + 300.0f, D_807F6000[csId].z, 0x8F, 0xFF, 0x64, 0, 0x50, 0.3f, 0);
                break;
        }
        *p = anim;
    }
    v = ((f32)anim + t) / 31.0 * 11.0;
    w = (v - (s32)v) * 64.0;
    modelSlotSetNodeFrame(csId, 1, (s32)v, (s32)w);
    modelSlotSetNodeFrame(csId, 2, (s32)v, (s32)w);
    modelSlotSetNodeFrame(csId, 3, (s32)v, (s32)w);
    modelSlotSetNodeFrame(csId, 4, (s32)v, (s32)w);
}

typedef struct CsB15Cs5C {
    /* 0x00 */ u8 pad0[0x5C];
    /* 0x5C */ u8 unk5C;
    /* 0x5D */ u8 pad5D;
    /* 0x5E */ u16 unk5E;
} CsB15Cs5C;

void actorAppendCallback(Actor *, s32, s32, u8, s32, void *);

void func_8064DE04(CsState *cs, s16 csId, s16 b, s16 c) {
    Actor *best;
    f32 bestDist;
    Actor *a;
    f32 dx;
    f32 dy;
    f32 dz;
    void *cam;
    f32 d;
    u16 id;
    s32 i;

    best = NULL;
    bestDist = 99999.0f;
    cam = D_807FBB4C->unk174;
    if (((CsB15Cs5C *)cs)->unk5C != 0) {
        id = ((CsB15Cs5C *)cs)->unk5E;
        for (i = 0; i < gActiveActorCount; i++) {
            a = gActiveActors[i].actor;
            if (a->unk58 == id) {
                dx = a->unk7C - D_807F621C;
                dy = a->unk80 - D_807F6220;
                dz = a->unk84 - D_807F6224;
                d = dx * dx + dy * dy + dz * dz;
                if (d < bestDist) {
                    bestDist = d;
                    best = a;
                }
            }
        }
        if (best != NULL) {
            actorAppendCallback(best, 0, 8, 0, 0, NULL);
        }
        if (b == 0 && best != NULL && best->unk58 == 0x55) {
            ((CsB2Cam *)cam)->unk1F0 &= 0xFFDFFFFF;
        }
    }
}

typedef struct CsB15Slot {
    u8 pad0[0x8A];
    s16 unk8A;
    u8 pad8C[4];
} CsB15Slot;

void func_8064DF5C(CsState *cs, s16 csId, s16 b, s16 c) {
    u8 *p;
    u8 full;
    u8 pat[4];
    s8 i;

    full = 0;
    if (*(u8 **)cs == NULL) {
        p = func_80610FE8(6);
        *(u8 **)cs = p;
        p[4] = 0;
        p[5] = 0;
    }
    p = *(u8 **)cs;
    if (b == -1) {
        p[4] = 0;
        p[5] = 0;
        return;
    }
    switch (((CsB15Slot *)D_807F6000)[hashTableLookup(csId)].unk8A) {
        case 0x41:
            pat[0] = 2; pat[1] = 4; pat[2] = 3; pat[3] = 1;
            break;
        case 0x40:
            pat[0] = 4; pat[1] = 2; pat[2] = 1; pat[3] = 3;
            break;
        case 0x3F:
            pat[0] = 1; pat[1] = 3; pat[2] = 2; pat[3] = 4;
            break;
    }
    p[p[4]] = b;
    i = p[4];
    p[4]++;
    if (p[4] == 4) {
        p[4] = 0;
    }
    if (p[5] == p[4]) {
        full = 1;
        p[5]++;
        if ((u8)p[5] == 4) {
            p[5] = 0;
        }
    }
    if (full) {
        s32 k;
        for (k = 0; k < 4; k++) {
            if (pat[k] != *(u8 *)((s32)p + i)) {
                return;
            }
            i--;
            if (i < 0) {
                i = 3;
            }
        }
        cs->unk4B[0] = 5;
    }
}

void func_8064E174(CsState *cs, s16 csId, s16 val, u8 *pat, s32 len, s16 okId, s16 failId) {
    u8 *p;
    s8 i;
    u8 head;
    s32 cnt;
    s32 j;

    if (*(u8 **)cs == NULL) {
        p = func_80610FE8(7);
        *(u8 **)cs = p;
        p[5] = 0;
        p[6] = 0;
    }
    p = *(u8 **)cs;
    p[p[5]] = val;
    i = p[5];
    p[5]++;
    if (len == p[5]) {
        p[5] = 0;
    }
    if (p[6] == p[5]) {
        p[6]++;
        if (len == (u8)p[6]) {
            p[6] = 0;
        }
        cnt = len;
    } else {
        cnt = p[5] - p[6];
    }
    for (j = len - cnt; j < len; j++) {
        if (pat[j] != *(u8 *)((s32)p + i)) {
            if (failId != -1) {
                cs->unk4B[0] = failId;
            }
            p[5] = 0;
            p[6] = 0;
            return;
        }
        i--;
        if (i < 0) {
            i = len - 1;
        }
    }
    if (okId != -1 && len == cnt) {
        cs->unk4B[0] = okId;
    }
}

typedef struct { u8 b[4]; } CsB15Pat4;
extern CsB15Pat4 D_807482DC;

void func_8064E428(CsState *cs, s16 csId, s16 val, s16 c) {
    CsB15Pat4 pat = D_807482DC;

    func_8064E174(cs, csId, val, (u8 *)&pat, 4, 5, 0x14);
}

typedef struct { u8 b[5]; } CsB15Pat5;
extern CsB15Pat5 D_807482E0;

void func_8064E48C(CsState *cs, s16 csId, s16 val, s16 c) {
    CsB15Pat5 pat = D_807482E0;

    func_8064E174(cs, csId, val, (u8 *)&pat, 5, 4, 0x14);
}

typedef struct { u8 b[3]; } CsB15Pat3;
extern CsB15Pat3 D_807482E8;

void func_8064E4F8(CsState *cs, s16 csId, s16 val, s16 c) {
    CsB15Pat3 pat = D_807482E8;

    func_8064E174(cs, csId, val, (u8 *)&pat, 3, 7, 0x14);
}

extern CsB15Pat4 D_807482EC;

void func_8064E55C(CsState *cs, s16 csId, s16 val, s16 c) {
    CsB15Pat4 pat = D_807482EC;

    func_8064E174(cs, csId, val, (u8 *)&pat, 3, 7, 0x14);
}

void func_8064E5C0(CsState *cs, s16 csId, s16 b, s16 c) {
    s16 old;

    old = cs->unk62;
    *(u8 *)&cs->unk66 = 0xFF;
    cs->unk60 = 1;
    if ((randomNonNegative() >> 15) % 100 > 40) {
        cs->unk62 = 0;
    } else {
        cs->unk62 = 0xFF;
    }
    if (old != cs->unk62) {
        func_80609140(0x8A, 0xBB8, 63.0f, 1.0f, 0x1E, 0);
    }
}

typedef struct CsB16View {
    /* 0x00 */ u8 pad0[0x98];
    /* 0x98 */ s16 unk98;
} CsB16View;
s32 actorSpawn(s32, s32);

void func_8064E65C(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 *q;
    f32 x;
    f32 y;
    f32 z;
    f64 g;
    f64 bl;

    if (b != 11) {
        modelSlotGetNodePos(csId, 1, 1, &x, &y, &z);
    }
    ((CsB16View *)cs)->unk98 = y - D_807F6220;
    if (*(s32 **)cs == NULL) {
        *(s32 **)cs = func_80610FE8(4);
        **(s32 **)cs = 0;
    }
    q = *(s32 **)cs;
    switch (b) {
        case 10:
        case 11:
            func_806086CC(x, y, z, 0x305, 0x64, 0x7F, 0, 0, 0.0f, 0);
            actorSpawn(0xB3, 0x5D);
            D_807FBB44->unk4->unk34 = D_807FBB44->unk4->unk34 * 3.2;
            D_807FBB44->unk4->unk38 = D_807FBB44->unk4->unk38 * 3.2;
            D_807FBB44->unk4->unk3C = D_807FBB44->unk4->unk3C * 3.2;
            D_807FBB44->unk60 |= 0x400;
            actorScriptStart(D_807FBB44, 0x335);
            if (b == 11) {
                D_807FBB44->unk7C = D_807F621C;
                D_807FBB44->unk80 = D_807F6220;
                D_807FBB44->unk84 = D_807F6224;
                break;
            }
            D_807FBB44->unk7C = x;
            D_807FBB44->unk80 = y;
            D_807FBB44->unk84 = z;
        case 1:
        case 3:
        case 4:
            if (*q >= 2) {
                *q -= 2;
            } else {
                *q = 0;
                break;
            }
        case 0:
            if (b == 0) {
                *q = 0xFF;
            }
            lightSetRadius(0x1388);
            g = c != 0 ? (f64)*q * 0.27 : (f64)*q;
            bl = c != 0 ? (f64)*q * 0.63 : (f64)*q;
            lightAdd(x, y - 50.0f, z, 0.0f, 0.0f, 0.0f, 240.0f, 0, (u32)g, (u32)bl, *q);
            break;
    }
}

void flagSet(s32, s32, s32);

void func_8064EA48(CsState *cs, s16 csId, s16 b, s16 c) {
    if (func_806F8AD4(1, 0) >= 2) {
        slotQueueUpdate(1, 0, 0);
        func_806F91B4(1, 0, -2);
        flagSet(0x83, 1, 0);
    }
}

void func_8064EAB4(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 sum;

    sum = flagGet(0xE6, 0);
    sum += flagGet(0xE8, 0);
    sum += flagGet(0xE9, 0);
    sum += flagGet(0xE7, 0);
    sum += flagGet(0xEA, 0);
    ((u8 *)cs)[0x4B] = sum;
}

s32 func_8064EB3C(CsState *cs, s16 csId, s16 b, s16 c) {
    if (flagGet(0x82, 0) == 0) {
        return 1;
    }
    if (flagGet(0x83, 0) != 0) {
        return 1;
    }
    return 0;
}

extern u8 D_8074E77C;

u8 func_8064EB9C(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 idx;
    u8 v;

    idx = func_805FF030(D_8076A0AB, 0);
    if (idx >= 8) {
        idx = 0;
    }
    v = D_807446F0[idx];
    return D_8074E77C == v;
}

s32 func_80600530(void);
s32 func_806FB418(void);
extern s16 D_807446D0[];

s32 func_8064EC04(CsState *cs, s16 csId, s16 b, s16 c) {
    s16 idx;

    idx = func_80600530();
    return (u8)((s16)func_806FB418() >= D_807446D0[idx]);
}

extern u8 D_807FC950[][0x5E];

u8 func_8064EC60(CsState *cs, s16 csId, s16 b, s16 c) {
    u32 padA, padB;
    s32 idx;
    u8 res = 0;
    s32 cur;
    u8 *row;
    s32 lim;

    switch (b) {
        default:
            idx = 0;
            break;
        case 3:
            idx = 1;
            break;
        case 4:
            idx = 2;
            break;
        case 5:
            idx = 3;
            break;
        case 6:
            idx = 4;
            break;
    }
    cur = func_80600530();
    row = D_807FC950[idx];
    lim = row[5] & 0x7F;
    if (lim == cur) {
        res = 1;
        if (c == 0 && (row[5] & 0x80)) {
            res = 0;
        }
    } else if (cur < lim) {
        res = 1;
    }
    if (res == 1 && c == 2) {
        row[5] = (row[5] & 0x7F);
    }
    return res;
}

s32 func_8064ED68(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 res = 0;
    u8 i;

    for (i = 2; i < 7; i++) {
        if (func_8064EC60(cs, csId, i, 1) == 0) {
            res = 1;
        }
    }
    return res;
}

typedef struct CsB16EffState {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ f32 unk4;
} CsB16EffState;
typedef struct CsB16Eff {
    /* 0x000 */ u8 pad0[0x344];
    /* 0x344 */ f32 unk344;
    /* 0x348 */ u8 pad348[0x18];
    /* 0x360 */ f32 unk360;
    /* 0x364 */ f32 unk364;
    /* 0x368 */ u8 pad368[0x1C];
    /* 0x384 */ CsB16EffState *unk384;
} CsB16Eff;
s32 camIsPathPaused(void);
s32 camIsCutsceneActive(void);
extern s8 D_807F6950;
extern s8 D_807F6951;

void func_8064EE08(CsB16Eff *e, u8 *flag) {
    CsB16EffState *s;

    if (e->unk384 == NULL) {
        s = func_80610FE8(8);
        e->unk384 = s;
        s->unk0 = 0;
        s->unk2 = 0;
        s->unk4 = e->unk344;
    }
    s = e->unk384;
    switch (s->unk0) {
        case 0:
            e->unk360 = e->unk360 + 0.015;
            if (e->unk360 > 0.5) {
                e->unk360 = 0.5f;
                s->unk0 = 1;
            }
            break;
        case 1:
            if (camIsPathPaused() != 0) {
                s->unk0 = 2;
            }
            if (camIsCutsceneActive() == 0) {
                s->unk0 = 2;
            }
            break;
        case 2:
            if (camIsPathPaused() == 0 || camIsCutsceneActive() == 0) {
                s->unk0 = 3;
                func_80609140(0x2E8, 0x7FFF, 63.0f, 1.0f, 0, 0);
            }
            break;
        case 3:
            e->unk360 = e->unk360 - 0.015;
            if (e->unk360 < 0.0) {
                D_807F6950 = 1;
                e->unk360 = 0.0f;
                *flag = 1;
            }
            break;
    }
    if (s->unk0 != 3) {
        e->unk344 = func_80612794((D_8076A064 * 0x3C) & 0xFFF) * 2.75f + s->unk4;
    }
    e->unk364 = e->unk360;
}

void camStartPath(void *, s32, s32);
void sfxAllocateChannel(s32, f32);
extern u8 D_80721530[];

void func_8064F028(CsState *cs, s16 csId, s16 b, s16 c) {
    func_807149C8(0xFF, 0xFF, 0xFF, 0x80);
    func_8071498C(func_8064EE08);
    func_807149FC(-1);
    func_807149B8(1);
    func_80714998(2);
    func_80714CC0(D_80721530, 0.0f, D_807F621C, D_807F6220 + 17.5, D_807F6224);
    actorSpawn(0x9C, 0x53);
    D_807FBB44->unk7C = D_807F621C;
    D_807FBB44->unk80 = D_807F6220;
    D_807FBB44->unk84 = D_807F6224;
    D_807FBB44->unkE6 = D_807F622C * 4096.0f / 360.0f;
    if (D_8076A0A8 == 0xB2 || (D_8076A0A8 == 0xAD && b == 4)) {
        D_807FBB44->unkE6 += 0x800;
    }
    camStartPath(D_807FBB44, 0x22, 5);
    sfxAllocateChannel(0xAB, 1.0f);
    func_80609140(0x2EA, 0x7FFF, 63.0f, 1.0f, 0, 0);
    D_807F6951 = b;
    D_807F6950 = 0;
}

void sfxStopChannel(s32, s32);

u8 func_8064F1C4(CsState *cs, s16 csId, s16 b, s16 c) {
    if (D_807F6950) {
        sfxStopChannel(0xAB, 0);
    }
    return D_807F6950;
}


u8 func_8064F210(CsState *cs, s16 csId, s16 b, s16 c) {
    f32 s;
    f32 d;
    f32 co;
    f32 r;
    s16 angle;

    angle = D_807F622C * 4096.0f / 360.0f;
    s = func_80612794(angle);
    co = func_80612790(angle);
    d = D_807F621C * s + D_807F6224 * co;
    d = -d;
    r = (D_807FBB4C->unk7C * s + co * D_807FBB4C->unk84) + d;

    return r > 6.0;
}

u8 func_8064F2F0(CsState *cs, s16 csId, s16 b, s16 c) {
    return 1;
}

extern s8 D_807FC8D0;

void func_8064F308(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 flag;

    if (D_807FC8D0 == 5) {
        flag = 0x1C1;
    } else {
        flag = 0x1C2;
    }
    flagSet(flag, 1, 0);
}

extern u8 D_807FC929;

typedef struct {
    u8 pad0[0xA];
    u16 v[0x2A];
} CsNM2Entry;

typedef struct {
    CsNM2Entry e[8];
    u8 pad[0x16];
} CsNM2Slot;

u8 func_8064F358(CsState *cs, s16 csId, s16 b, s16 c) {
    CsNM2Slot *p = (CsNM2Slot *)D_807FC950 + D_807FC929;
    s32 idx = func_805FF030(D_8076A0AB, 0);

    return p->e[(&D_8074E77C)[D_807FC929]].v[idx] > 0;
}

s32 flagCountRange(s32, s32, s32);

u8 func_8064F404(CsState *cs, s16 csId, s16 b, s16 c) {
    return flagCountRange(0x261, 0xA, 0) >= 4;
}


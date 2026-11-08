#include "common.h"
#include "actor.h"
#include "cutscene.h"

extern Actor *gCurrentActor;
extern Actor *gPrimaryPlayerActor;
extern ActorGlobalState gActorGlobalState;
extern u8 gBossFightPhase;
extern f32 gCsPosX;
extern f32 gCsPosY;
extern f32 gCsPosZ;
extern CsPlayer *gPlayerSlots;
extern u8 D_8071FF18[];
extern u8 sEffectSparkConfig[];
s32 randomLcgNext(void);
void effectSetSpeed(s32);
void effectSetCallback(void *);
void func_80717D4C(void);
void effectSetMode(u8);
void effectSetDepth(u8);
void effectSetColor(s32, s32, s32, s32);
void effectCreateAtModelNode(void *, f32, s32, s32, s32);
s32 effectCreateAtPosition(void *, f32, f32, f32, f32);
void *heapAlloc(s32);
void lightAdd(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32);
u8 collisionCheckGroundAtPoint(f32, f32, f32 *);
f32 mathCosF(s16);
f32 mathSinF(s16);
extern u32 gFrameCounter;
typedef struct CsPoint3f {
    f32 x, y, z;
} CsPoint3f;
extern CsPoint3f **D_807F5FD4;
void lightSetRadius(s32);


void csCmdSpawnFixedNodeEffects(CsState *cs, s16 csId, s16 b, s16 c) {
    effectCreateAtModelNode(D_8071FF18, 0.3f, csId, 1, 0);
    effectCreateAtModelNode(D_8071FF18, 0.3f, csId, 2, 0);
    effectCreateAtModelNode(D_8071FF18, 0.3f, csId, 3, 0);
}

typedef struct CsSlotAnim {
    /* 0x00 */ u8 pad0[0x2D];
    /* 0x2D */ u8 unk2D;
} CsSlotAnim;
typedef struct CsSlot {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 w;
    /* 0x10 */ u8 pad10[0x68];
    /* 0x78 */ CsSlotAnim *unk78;
    /* 0x7C */ u8 pad7C[0x14];
} CsSlot; /* 0x90 */
extern CsSlot *gModelSlots;
s32 hashTableLookup();
void modelSlotGetNodePos(s32, u8, s32, f32 *, f32 *, f32 *);

void csCmdSpawnSparksAtNodes(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 i;
    u8 type;
    f32 x;
    f32 y;
    f32 z;

    type = gModelSlots[(s16)hashTableLookup(csId)].unk78->unk2D;
    if (type == 0xD || type == 0x15 || type == 0x19) {
        for (i = 1; i != 0xF; i++) {
            modelSlotGetNodePos(csId, 1, i, &x, &y, &z);
            effectSetDepth(1);
            effectSetMode(2);
            effectSetSpeed(-(s32)((u32)randomLcgNext() / 10000 % 50) - 0x14);
            effectSetColor(0xE1, 0x87, 0x38, 0xFF);
            effectSetCallback(func_80717D4C);
            effectCreateAtPosition(D_8071FF18, 0.5f, x, y + 2.0f, z);
        }
    }
}


void csCmdFlickerLight(CsState *cs, s16 csId, s16 b, s16 c) {
    f32 x;
    f32 y;
    f32 z;
    s32 *p;
    f32 t;
    s32 g;

    if (*(s32 **)cs == NULL) {
        *(s32 **)cs = heapAlloc(4);
        **(s32 **)cs = b;
    }
    p = *(s32 **)cs;
    t = (20.0 - *p) / 20.0;
    if (t > 0.7) {
        t = 1.0f;
    }
    modelSlotGetNodePos(csId, 1, 1, &x, &y, &z);
    g = (u32)randomLcgNext() / 10000 % 200 + 0x37;
    lightAdd(x, y, z, 0.0f, 0.0f, 0.0f, t * 200.0, 0, 0, g, (u32)randomLcgNext() / 10000 % 80 + 0xAF);
    (*p)++;
    if (*p == 0x14) {
        *p = 0;
    }
}

typedef struct CsBounce {
    /* 0x0 */ f32 vy;
    /* 0x4 */ f32 angle;
    /* 0x8 */ f32 speed;
    /* 0xC */ f32 padC;
} CsBounce;
extern f32 gCsScale;

void csCmdBouncePos(CsState *cs, s16 csId, s16 b, s16 c) {
    CsBounce *p;
    u8 hit;
    f32 groundY;
    CsBounce *n;

    if (*(CsBounce **)cs == NULL) {
        n = heapAlloc(0x10);
        *(CsBounce **)cs = n;
        n->vy = 7.0f;
        n->angle = (u32)randomLcgNext() / 10000 % 1548 + 0x5DC;
        n->speed = (u32)randomLcgNext() / 10000 % 100 / 40.0 + 2.5;
        gCsScale = (u32)randomLcgNext() / 10000 % 100 / 500.0 + 0.14;
    }
    p = *(CsBounce **)cs;
    groundY = gCsPosY;
    hit = collisionCheckGroundAtPoint(gCsPosX, gCsPosZ, &groundY);
    p->vy = p->vy + -0.64;
    gCsPosX += p->speed * mathSinF(p->angle);
    gCsPosZ += p->speed * mathCosF(p->angle);
    if (p->vy < -10.0f) {
        p->vy = -10.0f;
    }
    gCsPosY += p->vy;
    if (hit != 0 && gCsPosY < groundY) {
        p->vy = (0.0 - p->vy) * 0.7;
        gCsPosY = groundY;
    }
}


void csCmdPeriodicNodeEffect(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 idx;

    if (gFrameCounter % c == 0) {
        idx = (u32)randomLcgNext() / 10000 % b + 1;
        effectSetColor(0xFF, 0xFF, 0xFF, 0x64);
        effectSetSpeed(-0x78);
        effectSetCallback(func_80717D4C);
        effectSetDepth(1);
        effectSetMode(3);
        effectCreateAtModelNode(sEffectSparkConfig, 1.5f, csId, idx, 0);
    }
}

void csPeriodicPointEffect(s32 a, s32 b, u32 c) {
    s32 idx;
    CsPoint3f *p;

    if (gFrameCounter % c == 0) {
        idx = (u32)randomLcgNext() / 10000 % b;
        effectSetColor(0xFF, 0xFF, 0xFF, 0x64);
        effectSetSpeed(-0x78);
        effectSetCallback(func_80717D4C);
        effectSetDepth(1);
        effectSetMode(3);
        p = *D_807F5FD4 + idx;
        effectCreateAtPosition(sEffectSparkConfig, 1.5f, p->x, p->y, p->z);
    }
}

void csCmdBobbingLights(CsState *cs, s16 csId, s16 b, s16 c) {
    s16 *ang;
    CsPoint3f *p;
    f32 fy;
    f32 sn;

    if (*(s16 **)cs == NULL) {
        ang = heapAlloc(2);
        *(s16 **)cs = ang;
        *ang = 0;
    }
    ang = *(s16 **)cs;
    sn = mathSinF(*ang);
    p = D_807F5FD4[1];
    fy = p[0].y + (p[1].y - p[0].y) * (0, (sn * 0.5 + 0.5)); // FAKE: comma const keeps the M*D operand order
    lightSetRadius(0x5DC);
    p = D_807F5FD4[1];
    lightAdd(p[0].x, fy, p[0].z, 0.0f, 0.0f, 0.0f, 500.0f, 0, 0xFF, 0xFF, 0xFF);
    sn = mathSinF(*ang + 0x514);
    p = D_807F5FD4[1];
    fy = p[2].y + (p[3].y - p[2].y) * (0, (sn * 0.5 + 0.5)); // FAKE: comma const keeps the M*D operand order
    lightSetRadius(0x5DC);
    p = D_807F5FD4[1];
    lightAdd(p[2].x, fy, p[2].z, 0.0f, 0.0f, 0.0f, 500.0f, 0, 0xFF, 0xFF, 0xFF);
    sn = mathSinF(*ang + 0xA28);
    p = D_807F5FD4[1];
    fy = p[4].y + (p[5].y - p[4].y) * (0, (sn * 0.5 + 0.5)); // FAKE: comma const keeps the M*D operand order
    lightSetRadius(0x5DC);
    p = D_807F5FD4[1];
    lightAdd(p[4].x, fy, p[4].z, 0.0f, 0.0f, 0.0f, 500.0f, 0, 0xFF, 0xFF, 0xFF);
    *ang += 0x32;
}

void csCmdPeriodicPointEffect(CsState *cs, s16 csId, s16 b, s16 c) {
    csPeriodicPointEffect(0, b, c);
}

typedef struct CsCursor {
    /* 0x0 */ s32 timer;
    /* 0x4 */ s32 idx;
} CsCursor;
extern u8 D_8071FB54[];
void timedLightPulse(void);

void csCmdPointCycleEffect(CsState *cs, s16 csId, s16 b, s16 c) {
    CsCursor *st;
    s32 idx;
    s32 x;
    s32 y;
    s32 z;

    if (*(CsCursor **)cs == NULL) {
        st = heapAlloc(8);
        *(CsCursor **)cs = st;
        st->timer = 0;
        st->idx = 0;
    }
    st = *(CsCursor **)cs;
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
        effectSetMode(2);
        effectSetDepth(1);
        effectSetSpeed(0);
        effectSetCallback(timedLightPulse);
        effectCreateAtPosition(D_8071FB54, 0.667f, x, y + 10, z);
        st->timer = 0x19;
    }
    st->timer--;
}

void tagBarrelSpawnSmokeAndPuffs(f32, f32, f32, f32, u8, u8);

void csCmdTagBarrelSpawnSmokeAndPuffs(CsState *cs, s16 csId, s16 b, s16 c) {
    CsSlot *slot = &gModelSlots[hashTableLookup(csId)];
    tagBarrelSpawnSmokeAndPuffs(slot->x, slot->y, slot->z, slot->w, 0, 1);
}

extern u8 D_8071FE08[];
extern u8 D_8071FE64[];
extern u8 D_8071FE88[];
extern u8 D_8071FEAC[];
void effectSetDuration(s32);
void effectTumbleBounceUpdate();
void effectLightPulseOscillate();

void csCmdSpawnBurstAtNodeOrPos(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 i;
    s32 r;
    s32 q;
    f32 x;
    f32 y;
    f32 z;

    if (b == 1) {
        modelSlotGetNodePos(csId, 1, c, &x, &y, &z);
    } else {
        x = gCsPosX;
        y = gCsPosY;
        z = gCsPosZ;
    }
    effectSetDepth(0);
    effectSetDuration(1);
    effectSetSpeed(0x100C8);
    effectSetCallback(effectLightPulseOscillate);
    effectCreateAtPosition(D_8071FE08, 1.5f, x, y, z);
    for (i = 0; i != 7; i++) {
        r = (s32)((u32)randomLcgNext() / 10000) % 3;
        effectSetDepth(1);
        effectSetDuration(10);
        effectSetCallback(effectTumbleBounceUpdate);
        effectSetMode(2);
        effectSetSpeed(7);
        switch (r) {
            case 0:
                effectCreateAtPosition(D_8071FE64, 0.5f, x, y, z);
                break;
            case 1:
                effectCreateAtPosition(D_8071FE88, 0.5f, x, y, z);
                break;
            case 2:
                effectCreateAtPosition(D_8071FEAC, 0.5f, x, y, z);
                break;
        }
    }
}


void csCmdPeriodicEffectPair(CsState *cs, s16 csId, s16 b, s16 c) {
    if ((gFrameCounter % 5) == 0) {
        effectSetSpeed(-0x78);
        effectSetCallback(func_80717D4C);
        effectSetDepth(1);
        effectSetMode(3);
        effectSetColor(0xFF, 0xFF, 0xFF, 0x96);
        effectCreateAtModelNode(sEffectSparkConfig, 1.0f, csId, 1, 0);
        effectSetSpeed(-0x78);
        effectSetCallback(func_80717D4C);
        effectSetDepth(1);
        effectSetMode(3);
        effectSetColor(0xFF, 0xFF, 0xFF, 0x96);
        effectCreateAtModelNode(sEffectSparkConfig, 1.0f, csId, 2, 0);
    }
}


typedef struct {
    s32 *unk0;
    u8 pad4[0x45];
    u8 unk49;
} CsLightView;

extern u8 D_807201D4[];
void func_80717CE8();

void csCmdLightPulse(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 *q;
    s32 n;
    f32 t;
    f32 f;
    if (((CsLightView *)cs)->unk0 == NULL) {
        ((CsLightView *)cs)->unk0 = heapAlloc(8);
    }
    q = ((CsLightView *)cs)->unk0;
    if (b == 1) {
        *((CsLightView *)cs)->unk0 = 0;
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
    lightAdd(gCsPosX, gCsPosY, gCsPosZ, 0.0f, 0.0f, 0.0f, 200.0f * f, 0, 0xFF,
             (u32)((-80.0f * f) + 255.0f), (u32)((-205.0f * f) + 255.0f));
    if (t > 0.6 && (gFrameCounter % 6) == 0) {
        effectSetDuration(2);
        effectSetDepth(1);
        effectSetSpeed(-0x190);
        effectSetColor(0xFF, 0xFF, 0xFF, 1);
        effectSetCallback(func_80717CE8);
        effectCreateAtPosition(D_807201D4, 1.2f, gCsPosX, gCsPosY + 30.0, gCsPosZ);
    }
    if (t < 0.1) {
        ((CsLightView *)cs)->unk49 = 1;
    }
}

extern void *D_8074E880[];
void effectSetAngle(s16);
void effectBurstParticleUpdate();

void csCmdSpawnEffectsAtPos(CsState *cs, s16 csId, s16 b, s16 c) {
    s16 i;

    for (i = 0; i < 30; i++) {
        effectSetDepth(1);
        effectSetDuration(1);
        effectSetCallback(effectBurstParticleUpdate);
        effectSetAngle(i / 7);
        effectCreateAtPosition(D_8074E880[i % 3], 1.4f, gCsPosX, gCsPosY, gCsPosZ);
    }
}

typedef struct {
    u32 unk0;
    s32 unk4;
    s32 unk8;
} CsSfxState;

typedef struct {
    CsSfxState *unk0;
    u8 pad4[0xC];
    s16 unk10;
} CsSfxView;

void sfxSlotFreeSource(s16);
void modelSlotSetNodeFrame(s32, s16, s32, s32);
void sfxPlayFromTargetSlot(s16, s32, s32, s32, s32, s32, f32);
s16 sfxSlotAllocateSource(s16, s32, s32, u8, s32, f32, s32);

void csCmdPeriodicSfxAlloc(CsState *cs, s16 csId, s16 b, s16 c) {
    CsSfxState *q;
    CsSfxState *t;

    if (((CsSfxView *)cs)->unk0 == NULL) {
        t = heapAlloc(0xC);
        ((CsSfxView *)cs)->unk0 = t;
        t->unk0 = 0;
        t->unk4 = 0;
    }
    q = ((CsSfxView *)cs)->unk0;
    switch (q->unk0) {
        case 0:
            q->unk4++;
            if (q->unk4 == 4) {
                q->unk8 = 0;
                q->unk0++;
                if (((CsSfxView *)cs)->unk10 < 0) {
                    ((CsSfxView *)cs)->unk10 = sfxSlotAllocateSource(csId, 0x12C, 0x3C, 1, 0x64, 1.0f, 0);
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
                    if (((CsSfxView *)cs)->unk10 >= 0) {
                        sfxSlotFreeSource(((CsSfxView *)cs)->unk10);
                        ((CsSfxView *)cs)->unk10 = -1;
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

void csCmdNodeSpotLight(CsState *cs, s16 csId, s16 b, s16 c) {
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

typedef struct CsCamFlagsView {
    /* 0x000 */ u8 pad0[0x1F0];
    /* 0x1F0 */ s32 unk1F0;
} CsCamFlagsView;

typedef struct CsPlayerView {
    /* 0x000 */ u8 pad0[0x210];
    /* 0x210 */ f32 unk210;
    /* 0x214 */ f32 unk214;
    /* 0x218 */ f32 unk218;
    /* 0x21C */ u8 pad21C[0x290 - 0x21C];
    /* 0x290 */ s16 unk290;
} CsPlayerView;

typedef struct CsFlicker {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ f32 unk4;
    /* 0x8 */ f32 unk8;
    /* 0xC */ f32 unkC;
} CsFlicker;

extern u8 gGameMode;
extern f32 D_807480DC;
extern u8 D_8077058C;
extern u8 D_80770DC9;
extern f32 D_80770DCC;
extern f32 D_80770DD0;
extern f32 D_80770DD4;

s32 randomNonNegative(void);
void sfxPlayWithRandomPan(s32, u8, s32, s32, s32);
void sfxPlayOnFreeSlot(s32, s32, f32, f32, s32, s32);
void func_80711410(f32, s32, f32, s32, f32);
void lightSetColor(f32, f32, f32, s32);

void csCmdStormLightningRain(CsState *arg0, s16 arg1, s16 arg2, s16 arg3) {
    CsFlicker *f;
    f32 dist;
    f32 fade;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 ex;
    f32 ey;
    f32 ez;
    CsFlicker *n;
    CsCamFlagsView *cam;

    cam = gPrimaryPlayerActor->customState;
    if (!(cam->unk1F0 & 0x20000000)) {
        if (*(CsFlicker **)arg0 == NULL) {
            n = heapAlloc(0x10);
            *(CsFlicker **)arg0 = n;
            n->unk0 = 0;
            n->unk4 = 0.0f;
            n->unk8 = 0.0f;
            n->unkC = 0.0f;
        }
        f = *(CsFlicker **)arg0;
        dz = ((CsPlayerView *)gPlayerSlots)->unk218 - gCsPosZ;
        dx = ((CsPlayerView *)gPlayerSlots)->unk210 - gCsPosX;
        dy = ((CsPlayerView *)gPlayerSlots)->unk214 - gCsPosY;
        dist = sqrtf(dz * dz + (dx * dx + dy * dy));
        if (((CsPlayerView *)gPlayerSlots)->unk290 == 0xE && gGameMode != 1) {
            fade = 1.0f;
        } else if (((CsPlayerView *)gPlayerSlots)->unk290 == 7) {
            fade = 0.0f;
        } else {
            ex = gCsPosX - 1714.0f;
            ey = gCsPosY - 226.0f;
            ez = gCsPosZ - 3410.0f;
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
        if (((CsPlayerView *)gPlayerSlots)->unk290 == 0xE || (((CsPlayerView *)gPlayerSlots)->unk290 == 0xB && dist < D_807480DC)) {
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
                            sfxPlayOnFreeSlot(0x9C, (s32)(((fade * 32767.0f * 60.0f / 255.0f) * (600.0 - D_80770DD4)) / 1000.0), D_80770DCC, 0.8f, 0x1E, (u32)D_80770DD0);
                        }
                    } else {
                        sfxPlayWithRandomPan(0x9C, (u32)(fade * 60.0f), 0x7F, 0x1E, (randomNonNegative() >> 15) % 3);
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

void csCmdSpawnEffectAtNode(CsState *arg0, s16 arg1, s16 arg2, s16 arg3) {
    effectSetMode(2);
    effectSetDepth(1);
    effectCreateAtModelNode(D_8071FBC8, 1.5f, arg1, arg2, 1);
}

void csSplineLightStep(f32 *, s16, s16, f32);

f32 splineEvalCubic(f64, f32, f32, f32, f32);

void csSplineLightStep(f32 *arg0, s16 arg1, s16 arg2, f32 arg3) {
    f32 frac;
    s32 i;
    u8 idx[4];
    f32 px;
    f32 py;
    f32 p0;
    f32 p1;
    f32 p2;
    f32 p3;
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
    p0 = D_807F5FD4[arg1][idx[0]].x;
    p1 = D_807F5FD4[arg1][idx[1]].x;
    p2 = D_807F5FD4[arg1][idx[2]].x;
    p3 = D_807F5FD4[arg1][idx[3]].x;
    px = splineEvalCubic(frac, p0, p1, p2, p3);
    p0 = D_807F5FD4[arg1][idx[0]].y;
    p1 = D_807F5FD4[arg1][idx[1]].y;
    p2 = D_807F5FD4[arg1][idx[2]].y;
    p3 = D_807F5FD4[arg1][idx[3]].y;
    py = splineEvalCubic(frac, p0, p1, p2, p3);
    p0 = D_807F5FD4[arg1][idx[0]].z;
    p1 = D_807F5FD4[arg1][idx[1]].z;
    p2 = D_807F5FD4[arg1][idx[2]].z;
    p3 = D_807F5FD4[arg1][idx[3]].z;
    lightAdd(px, py, splineEvalCubic(frac, p0, p1, p2, p3), 0.0f, 0.0f, 0.0f, 250.0f, 0, 0xFF, 0xFF, 0xFF);
}

void csCmdSplineLights(CsState *arg0, s16 arg1, s16 arg2, s16 arg3) {
    f32 *p;
    f32 *n;

    if (*(f32 **)arg0 == NULL) {
        n = heapAlloc(8);
        *(f32 **)arg0 = n;
        n[0] = 0.0f;
        n[1] = 0.0f;
    }
    p = *(f32 **)arg0;
    csSplineLightStep(p, 2, 0x16, 1.0f);
    csSplineLightStep(p + 1, 4, 0x18, 0.8f);
}

void lightSetFovAngles(f32, f32);
extern f32 D_807480E0;
extern f32 D_807480E4;

void csCmdNodeSpotLightFov(CsState *arg0, s16 arg1, s16 arg2, s16 arg3) {
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

void effectTimerCountdownAlphaUpdate(void);

void csCmdSpawnRandomEffectAtPos(CsState *arg0, s16 arg1, s16 arg2, s16 arg3) {
    effectSetDuration(-1);
    effectSetCallback(effectTimerCountdownAlphaUpdate);
    effectSetSpeed(0x50);
    effectCreateAtPosition(D_8074E880[(randomNonNegative() >> 15) % 1000 % 3], 0.5f, gCsPosX, gCsPosY, gCsPosZ);
}

void effectLightFlickerDecay(void);
extern u8 D_80720A7C[];

void csCmdRandomPointEffects(CsState *arg0, s16 arg1, s16 arg2, s16 arg3) {
    s32 sel;

    if ((u32)randomLcgNext() / 10000 % arg2 == 0) {
        sel = (u32)randomLcgNext() / 10000 % arg3;
        effectSetMode(2);
        effectSetSpeed(0x10064);
        effectSetCallback(effectLightFlickerDecay);
        effectSetColor(0xFF, 0xFF, 0xFF, 0xFF);
        effectCreateAtPosition(D_80720A7C, 1.2f, D_807F5FD4[0][sel].x, D_807F5FD4[0][sel].y, D_807F5FD4[0][sel].z);
    }
    if ((u32)randomLcgNext() / 10000 % arg2 == 0) {
        sel = (u32)randomLcgNext() / 10000 % arg3;
        effectSetMode(2);
        effectSetSpeed(0x10064);
        effectSetCallback(effectLightFlickerDecay);
        effectSetColor(0xFF, 0xFF, 0xFF, 0xFF);
        effectCreateAtPosition(D_80720A7C, 1.2f, D_807F5FD4[1][sel].x, D_807F5FD4[1][sel].y, D_807F5FD4[1][sel].z);
    }
}

extern f32 D_807480E8;
extern u8 D_807480EF;
extern u8 D_80720CD8[];
void effectFallUpdate(void);

void csCmdGroundPointEffect(CsState *cs, s16 csId, s16 b, s16 c) {
    u32 idx;
    f32 y;

    if ((randomLcgNext() / 10000U) % 10U == 0) {
        idx = (randomLcgNext() / 10000U) % (u32)c;
        y = D_807F5FD4[b][idx].y;
        if (collisionCheckGroundAtPoint(D_807F5FD4[b][idx].x, D_807F5FD4[b][idx].z, &y)) {
            effectSetSpeed(y + 2.0);
            effectSetCallback((void *)effectFallUpdate);
            effectSetDuration(-1);
            effectSetDepth(1);
            effectSetColor(0xFF, 0xFF, 0xFF, D_807480EF);
            effectCreateAtPosition(D_80720CD8, D_807480E8, D_807F5FD4[b][idx].x, D_807F5FD4[b][idx].y,
                          D_807F5FD4[b][idx].z);
        }
    }
}

extern u8 D_80720E44[];
extern u8 D_80720E5C[];
extern u8 D_80720E74[];
extern u8 D_80720E8C[];
void effectTumbleBounceUpdate(void);
void effectLightPulseOscillate(void);

void csCmdSpawnMultiRingParticles(CsState *cs, s16 csId, s16 b, s16 c) {
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
        sel = (s32)(randomLcgNext() / 10000U) % 4;
        effectSetDepth(1);
        effectSetDuration(0x3C);
        effectSetCallback((void *)effectTumbleBounceUpdate);
        effectSetMode(2);
        effectSetSpeed(2);
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
        effectCreateAtPosition(p, 0.5f, gCsPosX, gCsPosY, gCsPosZ);
    }
    for (i = 0; i != 6; i++) {
        x = (f32)((randomLcgNext() / 1000U) % 150U) - 75.0;
        z = (f32)((randomLcgNext() / 1000U) % 150U) - 75.0;
        scale = (f32)((randomLcgNext() / 1000U) % 50U - 25.0) / 50.0;
        if (i == 0) {
            effectSetSpeed(0x100FA);
            effectSetCallback((void *)effectLightPulseOscillate);
        } else {
            effectSetSpeed(-0xAA);
            effectSetCallback((void *)func_80717D4C);
        }
        effectSetDepth(1);
        effectSetMode(3);
        effectSetColor(0xFF, 0xFF, 0xFF, 0x64);
        effectCreateAtPosition(sEffectSparkConfig, scale + 3.5, gCsPosX + x, gCsPosY + 30.0, gCsPosZ + z);
    }
}


void csCmdChanceNodeEffect(CsState *cs, s16 csId, s16 b, s16 c) {
    u32 sp24;

    if ((randomLcgNext() / 10000U) % (u32)b == 0) {
        sp24 = (randomLcgNext() / 10000U) % (u32)c;
        effectSetMode(2);
        effectSetSpeed(0x10064);
        effectSetCallback(effectLightFlickerDecay);
        effectSetColor(0xFF, 0xFF, 0xFF, 0xFF);
        effectSetDepth(1);
        effectCreateAtModelNode(D_80720A7C, 0.5f, csId, sp24 + 1, 0);
    }
}

typedef struct CsFloatPair {
    f32 a;
    f32 b;
} CsFloatPair;

void effectSetMaxDistance(s32);
void func_805FF9AC(s32, s32, s32, s32);
extern u8 D_80720BC4[];
void effectLightGrowShrinkUpdate(void);

void csCmdInterpolateFloatPair(CsState *cs, s16 csId, s16 b, s16 c) {
    u32 idx;
    CsFloatPair *p;
    CsFloatPair *q;
    f32 f;

    if (*(CsFloatPair **)cs == NULL && c != 0) {
        q = heapAlloc(8);
        *(CsFloatPair **)cs = q;
        q->a = 0.0f;
        q->b = 0.0f;
    }
    p = *(CsFloatPair **)cs;

    idx = (randomLcgNext() / 10000U) % (u32)b;
    effectSetDepth(1);
    effectSetMode(3);
    effectSetSpeed(3);
    effectSetCallback((void *)effectLightGrowShrinkUpdate);
    effectSetMaxDistance(0x7D0);
    effectCreateAtPosition(D_80720BC4, 2.5f, (*D_807F5FD4)[idx].x, (*D_807F5FD4)[idx].y, (*D_807F5FD4)[idx].z);
    if (c != 0) {
        if (gPrimaryPlayerActor->state == 0x42) {
            p->a = *(f32 *)&gPrimaryPlayerActor->y;
        }
        f = *(f32 *)&gPrimaryPlayerActor->y;
        if ((p->a - f > 200.0 || f < 10.0f) && p->b == 0.0) {
            func_805FF9AC(0x48, 0x1C, 0, 0);
            p->b = 1.0f;
        }
    }
}


extern f32 gCsRotY;

void csCmdPeriodicIntervalEffects(CsState *cs, s16 csId, s16 b, s16 c) {
    s16 angle;
    s16 dist;
    s32 r1;
    s32 r2;
    f32 s;
    f32 d;

    if (gFrameCounter % (u32)b == 0) {
        r1 = randomNonNegative() >> 15;
        angle = r1 % 2048 + (gCsRotY * 4096.0f / 360.0f - 1024.0f);
        r2 = randomNonNegative() >> 15;
        dist = r2 % 32767 % 6 + 15;
        effectSetSpeed(-0x32 - (randomNonNegative() >> 15) % 80);
        effectSetCallback((void *)func_80717D4C);
        effectSetDepth(1);
        effectSetMode(2);
        s = mathSinF(angle);
        d = dist;
        effectCreateAtPosition(sEffectSparkConfig, 1.0f, s * d + gCsPosX, gCsPosY + 50.0f, mathCosF(angle) * d + gCsPosZ);
    }
}

void csCmdSpawnEffectsAtNodeRange(CsState *cs, s16 csId, s16 b, s16 c) {
    s16 i;

    i = 0;
    if (b > 0) {
        do {
            effectSetSpeed(-0x96 - ((randomNonNegative() >> 15) % 80));
            effectSetCallback((void *)func_80717D4C);
            effectSetDepth(1);
            effectSetMode(2);
            effectCreateAtModelNode(sEffectSparkConfig, 1.0f, csId, i + 1, 0);
            i++;
        } while (i < b);
    }
}


void csCmdPeriodicSfx(CsState *cs, s16 csId, s16 b, s16 c) {
    if ((0x243 - cs->unk44[0]) % 60 == 0) {
        sfxPlayFromTargetSlot(csId, 0x38, 0xFF, 0x7F, 0, 0x3C, 0.0f);
    }
}

void lightSetTargetId(s32);
void lightSetFlags(s32);

void csCmdNodeTargetLights(CsState *cs, s16 csId, s16 b, s16 c) {
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

typedef struct CsExtraObj3 {
    /* 0x00 */ u8 pad0[0x90];
    /* 0x90 */ f32 unk90;
    /* 0x94 */ u8 pad94[0x66];
    /* 0xFA */ u8 unkFA;
} CsExtraObj3;

typedef struct CsExtraObj2 {
    /* 0x000 */ u8 pad0[0x174];
    /* 0x174 */ CsExtraObj3 *unk174;
} CsExtraObj2;

typedef struct CsExtraObj1 {
    /* 0x000 */ u8 pad0[0x104];
    /* 0x104 */ CsExtraObj2 *unk104;
} CsExtraObj1;

typedef struct CsPlayerHeightView {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ Actor *unk4;
    /* 0x008 */ u8 pad8[0x20C];
    /* 0x214 */ f32 unk214;
} CsPlayerHeightView;

void mapChunkEffectSetFlag(s16, s16, u8, u8);

void csCmdExtraObjectAttach(s32 **slot, s16 csId, s16 b, s16 c) {
    s32 *p;
    CsExtraObj1 *a;
    CsExtraObj2 *b2;
    CsExtraObj3 *o;
    u8 near = 0;

    if (*slot == NULL) {
        *slot = heapAlloc(4);
        **slot = 1;
    }
    p = *slot;
    a = ((CsPlayerHeightView *)gPlayerSlots)->unk4->customState;
    b2 = a->unk104;
    o = b2->unk174;
    if (o->unkFA != 0 && ((CsPlayerHeightView *)gPlayerSlots)->unk214 < o->unk90 + 3.0f) {
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
void effectProximityFadeUpdate(void);

void csCmdPeriodicProximityEffects(CsState *cs, s16 csId, s16 b, s16 c) {
    f32 x = 0.0f;
    s32 i;

    if (!(gFrameCounter & 0xF)) {
        for (i = 1; i != 0xB; i++) {
            effectSetDepth(1);
            effectSetMode(2);
            effectSetCallback(effectProximityFadeUpdate);
            effectSetSpeed(0x2BC);
            effectSetMaxDistance(0x2BC);
            effectCreateAtModelNode(&D_80720B00, x + 1.1, csId, i, 1);
            x += 0.05;
        }
    }
}

typedef struct CsPointHitState {
    /* 0x00 */ s32 idx;
    /* 0x04 */ s32 timer;
    /* 0x08 */ s32 active;
    /* 0x0C */ s32 delay;
    /* 0x10 */ s32 count;
    /* 0x14 */ s32 flag14;
    /* 0x18 */ s32 flag18;
    /* 0x1C */ s32 flag1C;
} CsPointHitState;

typedef struct CsPlayerPosView {
    /* 0x000 */ u8 pad0[0x210];
    /* 0x210 */ f32 x;
    /* 0x214 */ f32 y;
    /* 0x218 */ f32 z;
} CsPlayerPosView;

typedef struct CsActorSub {
    /* 0x00 */ u8 pad0[0x64];
    /* 0x64 */ u16 unk64;
} CsActorSub;

typedef struct CsActorView {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ CsActorSub *unk4;
    /* 0x008 */ u8 pad8[0x7C - 8];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x12C - 0x88];
    /* 0x12C */ s16 unk12C;
    /* 0x12E */ u8 pad12E[0x154 - 0x12E];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
} CsActorView;

extern u32 gGlobalPauseFlags;
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

#define CS_ACTOR ((CsActorView *)gPrimaryPlayerActor)
#define CS_PLAYER ((CsPlayerPosView *)gPlayerSlots)
#define CS_POINT (&D_807F5FD4[0][p->idx])

void csCmdPointHitEffectSpawn(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 start;
    u8 hit;
    CsPointHitState *p;
    s32 pad0;
    f32 t;
    s32 pad1;
    CsActorView *a;
    u8 ok;
    CsPointHitState *n;
    s32 s;
    f32 u;
    s32 pad2;
    s32 pad3;
    f32 vec[3];

    hit = 0;
    if (*(CsPointHitState **)cs == NULL) {
        n = heapAlloc(0x1C);
        *(CsPointHitState **)cs = n;
        n->idx = 0;
        n->timer = D_807480F4;
        n->active = 0;
        n->delay = 0;
        n->count = 0;
        n->flag14 = 0;
        n->flag18 = 0;
        n->flag1C = 0;
    }
    p = *(CsPointHitState **)cs;
    if (b == 0) {
        if (D_80748108 != 0) {
            return;
        }
        if (p->active != 0 && p->flag14 == 0) {
            return;
        }
        start = p->idx;
        p->idx++;
        if (p->idx == 0x36) {
            p->idx = 0;
        }
        while (!hit && start != p->idx) {
            if (sqrtf((CS_PLAYER->x - CS_POINT->x) * (CS_PLAYER->x - CS_POINT->x) + (CS_PLAYER->y - CS_POINT->y) * (CS_PLAYER->y - CS_POINT->y) +
                      (CS_PLAYER->z - CS_POINT->z) * (CS_PLAYER->z - CS_POINT->z)) < D_807480F0) {
                effectSetDepth(1);
                effectSetMode(3);
                effectSetSpeed(0);
                effectSetCallback(effectLightGrowShrinkUpdate);
                effectSetMaxDistance(0x320);
                effectCreateAtPosition(D_80720BC4, 2.5f, CS_POINT->x, CS_POINT->y, CS_POINT->z);
                hit = 1;
            } else {
                p->idx++;
                if (p->idx == 0x36) {
                    p->idx = 0;
                }
            }
        }
        return;
    }
    if ((~gGlobalPauseFlags & 0x10) || CS_ACTOR->unk154 == 0x63) {
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
                actorListSpawnNodeEntry(0x5C, CS_ACTOR->unk7C + t, CS_ACTOR->unk80 + (f32)D_80748100, CS_ACTOR->unk84 + u, 0, D_80748104, 0, vec);
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
        if (CS_ACTOR->unk154 == 0x63) {
            return;
        }
        s = CS_ACTOR->unk12C;
        if (s == 0 || s == 7 || s == 2 || s == 3) {
            sfxStopChannel(0x54, 0);
            p->timer = D_807480F4;
            p->active = 0;
        }
    } else {
        if (p->flag18 == 0 && flagGet(0x12C, 0)) {
            p->flag18 = 1;
        }
        if (CS_ACTOR->unk12C == 0xD) {
            ok = 0;
            a = (CsActorView *)spawnNodeActivate(0x1F, 0);
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
        s = CS_ACTOR->unk12C;
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

typedef struct CsPlayerXYZ {
    /* 0x000 */ u8 pad0[0x210];
    /* 0x210 */ f32 x;
    /* 0x214 */ f32 y;
    /* 0x218 */ f32 z;
} CsPlayerXYZ;

extern f32 D_807480F0;
f32 sqrtf(f32);

void csCmdPlayerProximityPointCheck(s32 **slot, s16 csId, s16 b, s16 c) {
    s32 *p;
    s32 cnt;
    s32 start;
    s32 hit;
    CsPoint3f *v;
    s32 *q;
    CsPlayerXYZ *pl;
    f32 dx;
    f32 nv;
    f32 dy;
    f32 dz;

    hit = 0;
    if (*slot == NULL) {
        *slot = heapAlloc(4);
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
            pl = (CsPlayerXYZ *)gPlayerSlots;
            v = *p + D_807F5FD4[0];
            nv = pl->z - v->z;
            dx = pl->x - v->x;
            dz = nv;
            dy = pl->y - v->y;
            if (sqrtf(dz * dz + (dx * dx + dy * dy)) < D_807480F0) {
                hit = 1;
                effectSetDepth(1);
                effectSetMode(3);
                effectSetSpeed(0);
                effectSetCallback(effectLightGrowShrinkUpdate);
                effectSetMaxDistance(0x320);
                v = *p + D_807F5FD4[0];
                effectCreateAtPosition(D_80720BC4, 2.5f, v->x, v->y, v->z);
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
void effectSpinBillboardingUpdate(void);
void effectDecelDriftFadeUpdate(void);
void actorListSpawnNodeEntry(s16, f32, f32, f32, s16, f32, s32, void *);

void csCmdSpawnDirectionalEffects(CsState *cs, s16 csId, s16 b, s16 c) {
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
            d0 = (u32)randomLcgNext() / 1000 % 100;
            fx = d0 - 50.0;
            d1 = (u32)randomLcgNext() / 1000 % 100;
            fy = d1 - 50.0;
            d0 = (u32)randomLcgNext() / 1000 % 100;
            fz = d0 - 50.0;
            effectSetAngle(i);
            effectSetDepth(1);
            if (i == 0) {
                effectSetSpeed(D_80748150 + 0x10000);
                effectSetCallback(effectLightFlickerDecay);
                effectSetMode(D_80748154[3]);
            } else {
                effectSetCallback(effectSpinBillboardingUpdate);
            }
            effectCreateAtPosition(D_80720BE8, D_80748140, gCsPosX + fx, gCsPosY + fy, gCsPosZ + fz);
            i++;
        } while (i < D_80748148);
        i = 0;
    }
    do {
        effectSetCallback(effectDecelDriftFadeUpdate);
        effectSetSpeed(i);
        effectSetDepth(1);
        effectSetColor(0x8C, 0x8C, 0x8C, 0xFF);
        effectSetMode(3);
        effectCreateAtPosition(sEffectSparkConfig, D_80748144, gCsPosX, gCsPosY + D_8074814C, gCsPosZ);
        i++;
    } while (i < 0xC);
    for (i = 0; i != 0x1130; i += 0x190) {
        vec[0] = (f32)((s32)(randomNonNegative() >> 0xF) % D_8074812C) + D_80748120;
        vec[1] = i;
        vec[2] = (f32)((s32)(randomNonNegative() >> 0xF) % D_80748130) + D_80748124;
        actorListSpawnNodeEntry(0x5A, gCsPosX, gCsPosY + D_8074811C, gCsPosZ, 0, D_80748128, 0, vec);
    }
}

f32 randomFloat(void);

void csCmdSpawnScaledSphereEffects(CsState *cs, s16 csId, s16 b, s16 c) {
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
            effectSetAngle(i);
            effectSetDepth(1);
            effectSetCallback(effectSpinBillboardingUpdate);
            effectSetColor(0xFF, 0xFF, 0xFF, 0x96);
            effectCreateAtPosition(D_80720BE8, 1.5f, x, y, z);
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
                x = (f32)((f64)randomFloat() * 30.0 + (f64)gCsPosX - 15.0);
                y = (f32)((f64)randomFloat() * 40.0 + (f64)gCsPosY);
                z = (f32)((f64)randomFloat() * 30.0 + (f64)gCsPosZ - 15.0);
            }
            actorListSpawnNodeEntry(0x5A, x, y, z, 0, scale, 0, vec);
            i++;
            off += 0x2A8;
        } while (i != n);
    }
}

void csCmdSpawnModelNodeEffects(CsState *cs, s16 csId, s16 b, s16 c) {
    effectSetSpeed(-0x78);
    effectSetCallback(func_80717D4C);
    effectSetDepth(1);
    effectSetMode(3);
    effectCreateAtModelNode(sEffectSparkConfig, 1.5f, csId, 1, 0);
}

void csCmdGetModelNodeAndProject(CsState *cs, s16 csId, s16 b, s16 c) {
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


void csCmdSpawnRandomJitterEffects(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 i;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 sc;

    for (i = 0; i != 6; i++) {
        dx = (f32)((u32)randomLcgNext() / 1000 % 20) - 10.0;
        dy = (f32)((u32)randomLcgNext() / 1000 % 20) - 10.0;
        dz = (f32)((u32)randomLcgNext() / 1000 % 20) - 10.0;
        sc = (u32)randomLcgNext() / 1000 % 50 - 25.0;
        sc = sc / 50.0;
        effectSetSpeed(-0xAA);
        effectSetCallback(func_80717D4C);
        effectSetDepth(1);
        effectSetMode(3);
        effectSetAngle(i << 1);
        effectCreateAtPosition(sEffectSparkConfig, sc + 1.5, gCsPosX + dx, gCsPosY + dy, gCsPosZ + dz);
    }
}

void effectSetParam(s32);

void csCmdSpawnEffectAtRandomNode(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 node;
    f32 x;
    f32 y;
    f32 z;

    node = (u32)randomLcgNext() / 1000 % 10 + 1;
    effectSetSpeed(-0x28A - (u32)randomLcgNext() / 1000 % 200);
    effectSetCallback(func_80717D4C);
    effectSetDepth(1);
    effectSetMode(9);
    effectSetColor(0xFF, 0xFF, 0xFF, 0x64);
    effectSetParam(5);
    modelSlotGetNodePos(csId, 1, node, &x, &y, &z);
    effectCreateAtPosition(sEffectSparkConfig, 1.5f, x, y - 70.0f, z);
}

extern u8 D_80720DE0[];

void csCmdPointListEffect(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 *q;
    s32 idx;
    s32 x;
    s32 y;
    s32 z;
    CsPoint3f *p;

    q = *(s32 **)cs;
    if (q == NULL) {
        *(s32 **)cs = heapAlloc(4);
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
    effectSetMode(2);
    effectSetDepth(1);
    effectSetColor(0xFF, 0xFF, 0xFF, 0xC8);
    effectCreateAtPosition(D_80720DE0, 1.0f, x, y + 10, z);
}

extern u8 D_80748168[];
extern f32 D_8074816C;

void csCmdSpawnFallingSparkles(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 i;

    for (i = 1; i != 0xF; i++) {
        effectSetSpeed(-0x78);
        effectSetCallback(func_80717D4C);
        effectSetDepth(1);
        effectSetMode(3);
        effectSetColor(0xFF, 0xFF, 0xFF, D_80748168[3]);
        effectCreateAtModelNode(sEffectSparkConfig, D_8074816C, csId, i, 0);
    }
}

extern u8 D_80720EA4[];

void csCmdSpawnTumbleBounceRing(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 i;
    f32 t;

    for (i = 0; i < 12; i++) {
        effectSetDepth(1);
        effectSetDuration(0x3C);
        effectSetCallback(effectTumbleBounceUpdate);
        effectSetMode(2);
        effectSetSpeed(4);
        t = (u32)randomLcgNext() / 1000 % 80;
        effectCreateAtPosition(D_80720EA4, 1.0f, gCsPosX, gCsPosY + t, gCsPosZ);
    }
    for (i = 1; i != 6; i++) {
        effectSetSpeed(-0x78);
        effectSetCallback(func_80717D4C);
        effectSetDepth(1);
        effectSetMode(3);
        effectSetColor(0xFF, 0xFF, 0xFF, 0x78);
        effectCreateAtModelNode(sEffectSparkConfig, 3.0f, csId, i, 0);
    }
}

extern u8 D_8071FC8C[];
void effectCircleRiseFadeUpdate(void);

void csCmdSpawnOrbitingPuffs(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 i;
    f32 y;

    y = 0.0f;
    for (i = 0; i != 6; i++) {
        effectSetAngle(i << 1);
        effectSetDepth(1);
        effectSetDuration(7);
        effectSetCallback(effectCircleRiseFadeUpdate);
        effectSetMode(1);
        effectSetSpeed(y);
        effectCreateAtPosition(D_8071FC8C, 0.5f, gCsPosX, gCsPosY, gCsPosZ);
        effectSetSpeed(y + 2048.0f);
        effectCreateAtPosition(D_8071FC8C, 0.5f, gCsPosX, gCsPosY, gCsPosZ);
        y += 682.0f;
    }
}

typedef struct CsBlink {
    /* 0x0 */ u32 time;
    /* 0x4 */ s32 state;
} CsBlink;

void csCmdBlinkNodeFrames(CsState *cs, s16 csId, s16 b, s16 c) {
    CsBlink *p;
    CsBlink *n;

    if (*(CsBlink **)cs == NULL) {
        n = heapAlloc(8);
        *(CsBlink **)cs = n;
        n->time = 0;
        n->state = 0;
    }
    p = *(CsBlink **)cs;
    if (p->time + 50 < gFrameCounter) {
        if ((randomNonNegative() >> 15) % 1000 >= 0x353) {
            p->state = 1;
            p->time = gFrameCounter;
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


void csCmdSpawnPointParticles(CsState *cs, s16 csId, s16 b, s16 c) {
    effectSetMode(2);
    if (b != 0) {
        effectCreateAtPosition(D_8071FBC8, 3.0f, gCsPosX, gCsPosY, gCsPosZ);
    } else {
        effectCreateAtModelNode(D_8071FBC8, 3.0f, csId, 1, 0);
    }
}

extern u8 D_8071FC40[];
void effectWobbleRiseUpdate(void);

void csCmdSpawnDustPuffs(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 i;
    f32 dx;
    f32 dy;
    f32 dz;

    if (!((randomLcgNext() / 10000U) & 1)) {
        i = 0;
        do {
            dx = (f32)((randomLcgNext() / 10000U) % 200U) * 0.25 - 2.0;
            dy = (f32)((randomLcgNext() / 10000U) % 200U) * 0.25 - 2.0;
            dz = (f32)((randomLcgNext() / 10000U) % 200U) * 0.25 - 2.0;
            effectSetDepth(1);
            effectSetSpeed(1);
            effectSetDuration(-1);
            effectSetCallback(effectWobbleRiseUpdate);
            effectCreateAtPosition(D_8071FC40, 0.0f, gCsPosX + dx, gCsPosY + dy, gCsPosZ + dz);
            i++;
        } while (i != 12);
    }
}

typedef struct CsMatrixState {
    /* 0x00 */ f32 (*unk0)[4];
    /* 0x04 */ u8 pad4[0x96];
    /* 0x9A */ u8 unk9A;
} CsMatrixState;

void csCmdCameraLookAtMatrixUpdate(CsState *cs, s16 csId, s16 b, s16 c) {
    u32 pad[20];
    void *dm = &cs;
    f32 rx;
    f32 rz;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 t;
    f32 (*m)[4];
#define S ((CsMatrixState *)cs)

    if (S->unk0 == NULL && (S->unk9A & 1)) {
        m = heapAlloc(0x44);
        S->unk0 = m;
        modelSlotGetNodePos(csId, 1, 1, &sp40, &m[4][0], &sp38);
        m[4][0] -= 10.0;
        guRotateF(m, gCsRotY, 0.0f, 1.0f, 0.0f);
    }
    if ((S->unk9A & 1) && (randomLcgNext() / 10000U) % 20U == 0) {
        m = S->unk0;
        t = (randomNonNegative() >> 15) % 100;
        rx = t / 100.0;
        t = (randomNonNegative() >> 15) % 100;
        rz = t / (f64)100;
        guMtxXFMF(m, rx * 100.0 + -50.0, 0.0f, rz * 150.0 + -75.0, &sp40, &sp3C, &sp38);
        sp40 *= gCsScale;
        sp38 *= gCsScale;
        sp40 += gCsPosX;
        sp38 += gCsPosZ;
        effectSetDepth(1);
        effectSetSpeed(2);
        effectSetDuration(-1);
        effectSetCallback(effectWobbleRiseUpdate);
        effectCreateAtPosition(D_8071FC40, 0.0f, sp40, m[4][0], sp38);
    }
#undef S
}

typedef struct CsOrbitCounters {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ s32 unk4;
    /* 0x8 */ s32 unk8;
} CsOrbitCounters;
extern u8 D_80721200[];
extern u8 D_8072121C[];
extern u8 D_80721238[];
extern u8 D_80721250[];
extern u8 D_8072126C[];
extern u32 gGameFrameCounter;
void effectZRotationMatrixUpdate(void);
void effectSetScale(f32, f32);
void effectSetFlags(s16);

void csCmdSpawnOrbitingSparks(CsState *cs, s16 csId, s16 b, s16 c) {
    u8 *tex;
    f32 sa;
    f32 sb;
    CsOrbitCounters *p;
    f32 sx;
    f32 sz;

    sx = mathSinF((s16)((gCsRotY + 90.0f) * 4096.0f / 360.0f)) * 15.0f;
    sz = mathCosF((s16)((gCsRotY + 90.0f) * 4096.0f / 360.0f)) * 15.0f;
    if (*(CsOrbitCounters **)cs == NULL) {
        p = heapAlloc(0xC);
        *(CsOrbitCounters **)cs = p;
        p->unk0 = 0;
        p->unk4 = 0;
        p->unk8 = 0;
    }
    p = *(CsOrbitCounters **)cs;
    effectSetDepth(1);
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
    sa = mathSinF(*(s16 *)((u8 *)p + 2)) * 0.1;
    sb = mathSinF(*(s16 *)((u8 *)p + 6)) * 0.1;
    p->unk0 += 0x32;
    p->unk4 += 0x64;
    effectSetScale(sa + 1.0, sb + 1.0);
    effectSetMaxDistance(0x578);
    effectSetFlags(4);
    effectCreateAtPosition(tex, 0.0f, gCsPosX + sx, mathSinF(*(s16 *)((u8 *)p + 0xA)) * 10.0 + (gCsPosY + 80.0), gCsPosZ + sz);
    p->unk8 += 0x64;
    if (gGameFrameCounter % 12U == 0) {
        effectSetDepth(1);
        effectSetSpeed(0x5A);
        effectSetCallback(effectZRotationMatrixUpdate);
        effectSetMaxDistance(0x578);
        effectSetFlags(4);
        effectCreateAtPosition(D_8072126C, 2.0f, gCsPosX + sx, gCsPosY + 30.0, gCsPosZ + sz);
    }
}


void csCmdSpawnSphereEffects(CsState *cs, s16 csId, s16 b, s16 c) {
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
            effectSetAngle(randomFloat() * (f32)(c >> 8));
            do {
                x = 2.0f * randomFloat() - 1.0f;
                y = 2.0f * randomFloat() - 1.0f;
                z = 2.0f * randomFloat() - 1.0f;
                len = sqrtf(x * x + y * y + z * z);
            } while (len < 0.05f);
            len = r / len;
            x *= len;
            y *= len;
            z *= len;
            y += r;
            effectCreateAtPosition(D_8071FF18, scale * 1.5, gCsPosX + x, gCsPosY + y, gCsPosZ + z);
            i++;
        } while (i != n);
    }
}

extern u8 D_807212B0[];
extern u8 D_807212C8[];
extern u8 D_80720340[];

void csCmdSpawnPuffBurst(CsState *cs, s16 csId, s16 b, s16 c) {
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
        dx = 2.0f * randomFloat() - 1.0f;
        dy = 2.0f * randomFloat() - 1.0f;
        dz = 2.0f * randomFloat() - 1.0f;
        dx *= spread;
        dy *= spread;
        dz *= spread;
        dy += base;
        effectSetDepth(1);
        effectSetDuration(0x3C);
        effectSetCallback(effectTumbleBounceUpdate);
        effectSetMode(2);
        effectSetSpeed(2);
        effectCreateAtPosition(tbl, (randomFloat() * 0.5 + 0.2) * scale, gCsPosX + dx, gCsPosY + dy, gCsPosZ + dz);
        if (i < 6) {
            dx = 2.0f * randomFloat() - 1.0f;
            dy = 2.0f * randomFloat() - 1.0f;
            dz = 2.0f * randomFloat() - 1.0f;
            dx *= spread;
            dy *= spread;
            dz *= spread;
            dy += base;
            r = (u32)randomLcgNext() / 1000 % 50 - 25.0;
            r = r / 50.0;
            if (i == 0) {
                effectSetSpeed(0x100FA);
                effectSetCallback(effectLightPulseOscillate);
            } else {
                effectSetSpeed(-0xAA);
                effectSetCallback(func_80717D4C);
            }
            effectSetMode(3);
            effectSetColor(0xFF, 0xFF, 0xFF, 0x64);
            effectCreateAtPosition(sEffectSparkConfig, (r + 3.5) * scale, gCsPosX + dx, gCsPosY + dy, gCsPosZ + dz);
        }
    }
    effectSetDepth(1);
    effectCreateAtPosition(D_80720340, scale * 2.5, gCsPosX, b + gCsPosY, gCsPosZ);
}


typedef struct CsPlayerStateView {
    /* 0x000 */ u8 pad0[0x290];
    /* 0x290 */ s16 unk290;
} CsPlayerStateView;

s32 csIsPlayerState4OrC(void) {
    s16 state = ((CsPlayerStateView *)gPlayerSlots)->unk290;

    if (state == 4 || state == 0xC) {
        return 1;
    }
    return 0;
}


typedef struct CsFade {
    /* 0x0 */ u8 unk0;
    /* 0x2 */ u16 unk2;
    /* 0x4 */ f32 unk4;
} CsFade;

typedef struct CsFadeView {
    /* 0x00 */ CsFade *unk0;
    /* 0x04 */ u8 pad4[0xC];
    /* 0x10 */ s16 unk10;
} CsFadeView;

typedef struct CsCamModeView {
    /* 0x00 */ u8 pad0[0xBC];
    /* 0xBC */ s16 unkBC;
} CsCamModeView;

extern CsCamModeView *gActivePlayerState;
extern s32 gCurrentMap;
extern s16 D_807F7366;
extern f32 D_807F6940;
void sfxSetChannelPriority(u8, u8);
void renderScrollingBackdropQuad(void);
void renderCallbacksRegister(void *, void *, s32);

void csCmdSfxFadeLoop(CsState *cs, s16 csId, s16 b, s16 c) {
    CsFade *q;
    u8 flag;

    if (((CsFadeView *)cs)->unk0 == NULL) {
        q = heapAlloc(8);
        ((CsFadeView *)cs)->unk0 = q;
        q->unk0 = 0;
        q->unk2 = 0;
        q->unk4 = 0.0f;
    }
    q = ((CsFadeView *)cs)->unk0;
    if (gCurrentMap == 0x26) {
        flag = 1;
    } else {
        flag = 0;
    }
    switch (q->unk0) {
        case 0:
            if (q->unk2 == 0) {
                if (csIsPlayerState4OrC() != 0 || flag == 0) {
                    q->unk0 = 1;
                    q->unk2 = 0x190;
                    q->unk4 = 0.0f;
                    if (flag != 0) {
                        ((CsFadeView *)cs)->unk10 = sfxSlotAllocateSource(csId, 0x11F, 0, 1, 0, 1.0f, 0);
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
                if (--q->unk2 == 0 || (csIsPlayerState4OrC() == 0 && flag != 0)) {
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
                    sfxSlotFreeSource(((CsFadeView *)cs)->unk10);
                    ((CsFadeView *)cs)->unk10 = -1;
                }
            } else if (flag != 0) {
                sfxSetChannelPriority(*((u8 *)cs + 0x11), q->unk4 * 200.0f);
            }
            break;
    }
    if ((gPrimaryPlayerActor->state == 0x42 && gActivePlayerState->unkBC == 0x62) || gPrimaryPlayerActor->state == 0x67) {
        q->unk0 = 0;
        q->unk2 = 0x190;
        q->unk4 = 0.0f;
        if (flag != 0) {
            if (((CsFadeView *)cs)->unk10 != -1) {
                sfxSlotFreeSource(((CsFadeView *)cs)->unk10);
                ((CsFadeView *)cs)->unk10 = -1;
            }
        }
    }
    D_807F7366 = q->unk4 * -25.0f + 995.0f;
    D_807F6940 = q->unk4;
    if (q->unk4 != 0.0f) {
        renderCallbacksRegister(renderScrollingBackdropQuad, &q->unk4, 5);
    }
}


void csCmdSpawnFallingWhiteSparks(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 i;

    for (i = 1; i != 8; i++) {
        effectSetSpeed(-0x78);
        effectSetCallback(func_80717D4C);
        effectSetDepth(1);
        effectSetMode(3);
        effectSetColor(0xFF, 0xFF, 0xFF, 0x96);
        effectCreateAtModelNode(sEffectSparkConfig, 3.5f, csId, i, 0);
    }
}


extern u8 gCurrentWorldId;
extern u8 D_807446F0[];
extern s16 D_80744710[];
extern s8 D_80748170[];
extern s8 D_80748178;
extern s16 D_807505AE[];
s32 flagGet(s32, s32);
u8 mapGetHubWorldIndex(u8, u8);
u8 mapHasCollectedSufficientItems(void);

void csCmdHubWorldItemsAdjust(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 idx;
    s32 base;
    s8 v;
    s8 add;
    s32 base2;

    if (b == 0) {
        idx = mapGetHubWorldIndex(gCurrentWorldId, 0);
        if (idx >= 8) {
            idx = 0;
        }
        base = D_807446F0[idx];
        if (D_807505AE[base]) {}
        if (flagGet(D_80744710[idx], 0)) {
            modelSlotSetNodeFrame(csId, 1, 0xB, 0);
            modelSlotSetNodeFrame(csId, 2, 0xB, 0);
        } else if (mapHasCollectedSufficientItems()) {
            modelSlotSetNodeFrame(csId, 1, D_80748170[base], 0);
            modelSlotSetNodeFrame(csId, 2, D_80748170[base], 0);
        } else {
            modelSlotSetNodeFrame(csId, 1, 0xA, 0);
            modelSlotSetNodeFrame(csId, 2, 0xA, 0);
        }
    } else {
        v = D_80748178 + 1;
        if (gCurrentWorldId && gCurrentWorldId) {}
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

void csCmdSpawnRandomNodeParticles(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 i;
    u8 idx;

    for (i = 0; i < b; i++) {
        idx = (randomNonNegative() >> 15) % 32767 % (c + 1);
        effectSetDepth(1);
        effectSetMaxDistance(0x7D0);
        effectSetCallback(func_8071F660);
        effectSetDuration(8);
        effectCreateAtPosition(D_80721298, 1.0f, (*D_807F5FD4)[idx].x, (*D_807F5FD4)[idx].y, (*D_807F5FD4)[idx].z);
    }
}
extern u16 D_807446C0[];
extern u16 gLevelCollectibleCounts[];

void csCmdShowRemainingDigits(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 i;
    s32 v;
    s32 n;
    s32 t;

    n = mapGetHubWorldIndex(gCurrentWorldId, 0);
    if (n >= 8) {
        n = 7;
    }
    v = D_807446C0[n] - gLevelCollectibleCounts[n];
    if (v < 0) {
        v = 0;
    }
    t = v;
    for (i = 1; i != 4; i++) {
        modelSlotSetNodeFrame(csId, i, (10 - i + t % 10) % 10, 0);
        t /= 10;
    }
}

void effectLerpPathUpdate(void);

typedef struct CsCamVecView {
    /* 0x000 */ u8 pad0[0x220];
    /* 0x220 */ f32 unk220;
    /* 0x224 */ f32 unk224;
    /* 0x228 */ f32 unk228;
    /* 0x22C */ f32 unk22C;
    /* 0x230 */ f32 unk230;
    /* 0x234 */ f32 unk234;
} CsCamVecView;

typedef struct CsObjStateView {
    /* 0x000 */ u8 pad0[0x384];
    /* 0x384 */ void *unk384;
} CsObjStateView;

typedef struct CsPartF32 {
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
} CsPartF32;

void csCmdCameraVectorTargetUpdate(CsState *cs, s16 csId, s16 b, s16 c) {
    CsCamVecView *p;
    CsObjStateView *obj;
    CsPartF32 *q;
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
    ang = gCsRotY * 4096.0f / 360.0f;
    if (c == 2) {
        effectSetDepth(0);
        effectCreateAtPosition(D_80720A7C, 0.5f, randomFloat() * 35.0 + gCsPosX - 15.0, randomFloat() * 35.0 + gCsPosY, randomFloat() * 35.0 + gCsPosZ - 15.0);
        return;
    }
    p = (CsCamVecView *)gPlayerSlots->unk4->customState;
    p->unk22C = gCsPosX;
    p->unk230 = gCsPosY + 15.0;
    p->unk234 = gCsPosZ;
    p->unk220 = mathSinF(ang);
    p->unk224 = ang;
    p->unk228 = mathCosF(ang);
    if (c == 0) {
        flag = 1;
        sfxPlayOnFreeSlot(0xF2, 0x5DC0, 63.0f, 1.0f, 0, 0);
    } else {
        flag = 0;
        sfxPlayOnFreeSlot(0x2EB, 0x7D00, 63.0f, 0.6f, 0, 0);
    }
    negCos = -p->unk228;
    sinA = p->unk220;
    px = gCsPosX; py = gCsPosY + 15.0; pz = gCsPosZ;
    ex = p->unk220 * 50.0 + px;
    ang = 0;
    cb = effectLerpPathUpdate;
    ez = p->unk228 * 50.0 + pz;
    for (i = 0; i != 4; i++) {
        t = mathCosF(ang) * 100.0;
        xs = t * negCos + ex;
        xo = t * sinA + ez;
        zo = mathSinF(ang) * 100.0 + py;
        ang += 0x400;
        effectSetDuration(-1);
        effectSetDepth(0);
        effectSetCallback(cb);
        obj = (CsObjStateView *)effectCreateAtPosition(D_8074E880[((randomNonNegative() >> 15) % 1000) % 3], 1.8f, px, py, pz);
        q = obj->unk384 = heapAlloc(0x28);
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

s32 csModelStateTrySetByte(s16, s16, s16);

extern s16 D_80748180[][2];

typedef struct CsStepState {
    /* 0x0 */ s32 cnt;
    /* 0x4 */ s32 prev;
} CsStepState;

void csCmdStepSequenceProgress(CsState *cs, s16 csId, s16 b, s16 c) {
    CsStepState *st;
    u8 found;
    s32 eq;
    s32 ok;
    s32 i;
    s32 prev;
    s32 d;

    d = *((u8 *)cs + 0x48);
    if (*(CsStepState **)cs == NULL) {
        st = heapAlloc(8);
        *(CsStepState **)cs = st;
        st->cnt = 0;
        st->prev = -1;
    }
    st = *(CsStepState **)cs;
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
            csModelStateTrySetByte(D_80748180[i][1], 0x28, 0);
            i = 0;
            found = 0;
            while (!found) {
                if (D_80748180[i][0] == *((u8 *)cs + 0x48)) {
                    found = 1;
                } else {
                    i++;
                }
            }
            csModelStateTrySetByte(D_80748180[i][1], 0x28, 0);
        }
        st->prev = -1;
    }
}

typedef struct CsModelSlotView {
    /* 0x00 */ u8 pad0[0x7C];
    /* 0x7C */ void *unk7C;
    /* 0x80 */ u8 pad80[0xA];
    /* 0x8A */ s16 unk8A;
    /* 0x8C */ u8 pad8C[4];
} CsModelSlotView; /* 0x90 */

extern s16 D_807481C0[][2];

void csCmdLookupSlotKey(CsState *cs, s16 csId, s16 b, s16 c) {
    s16 key;
    s32 found;
    s16 (*p)[2];

    key = ((CsModelSlotView *)gModelSlots)[hashTableLookup(csId)].unk8A;
    found = 0;
    p = D_807481C0;
    do {
        if (key == (*p)[0]) {
            found = 1;
        } else {
            p++;
        }
    } while (found == 0);
    csModelStateTrySetByte(0x3D, (*p)[1], 1);
}

void csCmdSetParam49(CsState *cs, s16 csId, s16 b, s16 c) {
    cs->unk14[0] = *((u8 *)cs + 0x49);
}

extern s16 gCsModelIds[];
extern s16 D_807481F4[];
extern s16 D_807481F6[];
extern u8 D_80748212[];
void func_8064199C(void *, s16, s16);

typedef struct CsPairState {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ s32 unk4;
} CsPairState;

void csCmdModelStepAnimation(CsState *cs, s16 csId, s16 b, s16 c)
{
  CsPairState *st;
  s32 found;
  s32 i;
  if ((*((CsPairState **) cs)) == 0)
  {
    st = heapAlloc(8);
    *((CsPairState **) cs) = st;
    st->unk0 = 0;
    st->unk4 = 0;
  }
  st = *((CsPairState **) cs);
  found = 0;
  if ((*(((u8 *) cs) + 0x49)) != (*st).unk4)
  {
    if (D_807481F4) {} // FAKE: early read of the table address (raises its candidate priority)
    i = 0;
    do
    {
      if (D_807481F4[i] == (*(((u8 *) cs) + 0x49)))
      {
        found = 1;
      }
      else
      {
        i++;
      }
    }
    while (found == 0);
    if (&D_807481F4[i] < (s16 *)D_80748212)
    {
      csModelStateTrySetByte(D_807481F4[i + 1], 0xA, 0);
      func_8064199C(((CsModelSlotView *) gModelSlots)[hashTableLookup(gCsModelIds[D_807481F4[i + 1]])].unk7C, 0, 0);
    }
    if (&D_807481F4[i] >= D_807481F6)
    {
      csModelStateTrySetByte(D_807481F4[i - 1], 0x14, 0);
    }
    st->unk4 = *(((u8 *) cs) + 0x49);
  }
}

void csCmdSetModelSlotByte5F(CsState *cs, s16 csId, s16 b, s16 c) {
    csModelStateTrySetByte(0x5F, ((CsModelSlotView *)gModelSlots)[hashTableLookup(csId)].unk8A, 1);
}

typedef struct CsCountdown {
    /* 0x00 */ u64 last;
    /* 0x08 */ s64 duration;
    /* 0x10 */ s64 left;
    /* 0x18 */ s64 fired;
} CsCountdown; /* 0x20 */
extern u64 D_807445B0;
extern u64 osGetTime(void);
void heapFreeDeferred(void *);
void renderCountdownTimerHUD(void);

void csCmdCountdownTimer(CsState *cs, s16 csId, s16 b, s16 c) {
    CsCountdown *t;
    u64 elapsed;

    if (*(CsCountdown **)cs == NULL) {
        *(CsCountdown **)cs = heapAlloc(0x20);
        t = *(CsCountdown **)cs;
        t->last = osGetTime();
        t->duration = b;
        t->left = 0;
        t->fired = 0;
    }
    t = *(CsCountdown **)cs;
    t->last += D_807445B0;
    elapsed = (osGetTime() - t->last) * 64;
    t->left = t->duration - elapsed / 3000 / 1000000;
    if (t->fired == 0 && (u64)t->left < (u64)(s64)c) {
        t->fired = 1;
        cs->unk4B[0] = 0x14;
    }
    if (t->left == 0) {
        heapFreeDeferred(*(CsCountdown **)cs);
        cs->unk4B[0] = 0x1E;
        *(CsCountdown **)cs = NULL;
    }
    renderCallbacksRegister(renderCountdownTimerHUD, t, 5);
}

void csCmdNop(CsState *cs, s16 csId, s16 b, s16 c) {
}

typedef struct CsSlotIdView {
    /* 0x00 */ u8 pad0[0x8A];
    /* 0x8A */ s16 unk8A;
    /* 0x8C */ u8 pad8C[4];
} CsSlotIdView; /* 0x90 */
extern u8 D_80748214[];
void func_806BD094(s16, s8);

void csCmdFindSlotIdMatch(CsState *cs, s16 csId, s16 b, s16 c) {
    u8 found;
    s32 i;
    s16 id;
    u8 *p;

    found = 0;
    i = 0;
    id = ((CsSlotIdView *)gModelSlots)[hashTableLookup(csId)].unk8A;
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
    csModelStateTrySetByte(*p, 0xA, 0);
}


extern u64 osGetTime(void);
typedef struct CsFxEnt {
    /* 0x0 */ u8 state;
    /* 0x1 */ u8 pad1;
    /* 0x2 */ s16 timer;
    /* 0x4 */ u8 active;
    /* 0x5 */ u8 pad5;
} CsFxEnt; /* 0x6 */
typedef struct CsFx {
    /* 0x00 */ u64 last;
    /* 0x08 */ s64 duration;
    /* 0x10 */ s64 left;
    /* 0x18 */ CsFxEnt ent[9];
    /* 0x4E */ u8 pad4E;
    /* 0x4F */ u8 cool;
} CsFx; /* 0x50 */
typedef struct CsFxRow {
    /* 0x00 */ u8 pad0[0x18];
    /* 0x18 */ u8 state;
    /* 0x19 */ u8 pad19;
    /* 0x1A */ s16 timer;
    /* 0x1C */ u8 active;
    /* 0x1D */ u8 pad1D;
} CsFxRow;
typedef struct CsFxSel {
    /* 0x00 */ u8 pad0[0x12];
    /* 0x12 */ u8 state;
    /* 0x13 */ u8 pad13[3];
    /* 0x16 */ u8 active;
} CsFxSel;
#define CS_FX_SEL(t, i) ((CsFxSel *)((u8 *)(t) + (i) * 6))
typedef struct CsFxView {
    /* 0x00 */ u8 pad0[0x10];
    /* 0x10 */ s16 slot;
    /* 0x12 */ u8 pad12[0x4A];
    /* 0x5C */ u8 unk5C;
    /* 0x5D */ u8 pad5D;
    /* 0x5E */ u16 unk5E;
} CsFxView;
extern f32 D_80770BC0[];
void modelAnimEntryGetState(s16, s16, s16 *, f32 *, u8 *);
void modelAnimEntrySetUnkC(s16, s16, s16);
void modelAnimEntrySetTime(s16, s16, s16, f32);
void sfxPlayAtPositionPooled(f32, f32, f32, s16, s32, s32, s32, s32, f32, s32);

void csCmdStepCameraFrac(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 u1; /* unused: reserves frame slots */
    s32 sixth;
    u8 ok;
    s16 st;
    f32 frac;
    u8 spC7;
    s32 i;
    CsFx *t;
    CsFxRow *e;
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
    if (*(CsFx **)cs == NULL) {
        t = heapAlloc(0x50);
        *(CsFx **)cs = t;
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
        ((CsFxView *)cs)->slot = sfxSlotAllocateSource(csId, 0x12F, 0, 1, 0xFF, 1.0f, 0);
    }
    t = *(CsFx **)cs;
    t->last += D_807445B0;
    for (i = 0, e = (CsFxRow *)t; i != 9; i++, e = (CsFxRow *)((u8 *)e + 6)) {
        if (e->active != 0) {
            count++;
            modelAnimEntryGetState(csId, i + 1, &st, &frac, &spC7);
            if (st == e->state && frac < 0.1 && e->timer == 0) {
                modelAnimEntrySetUnkC(csId, i + 1, 0);
                modelAnimEntrySetTime(csId, i + 1, st, 0);
                e->active = 0;
                modelSlotGetNodePos(csId, 1, i + 1, &x, &y, &z);
                sfxPlayAtPositionPooled(x, y, z, 0x1AE, 0xFF, 0x7F, 0x14, 0x50, 0.7f, 0);
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
    if (((CsFxView *)cs)->slot != -1) {
        D_80770BC0[((CsFxView *)cs)->slot] = count;
        if (count == 0) {
            sfxSlotFreeSource(((CsFxView *)cs)->slot);
            ((CsFxView *)cs)->slot = -1;
        }
    }
    if (((CsFxView *)cs)->unk5C != 0 && ((CsFxView *)cs)->unk5E == 0x26) {
        if (CS_FX_SEL(t, ((CsFxView *)cs)->unk5C)->active == 0 && t->cool == 0) {
            CS_FX_SEL(t, ((CsFxView *)cs)->unk5C)->state++;
            CS_FX_SEL(t, ((CsFxView *)cs)->unk5C)->state = CS_FX_SEL(t, ((CsFxView *)cs)->unk5C)->state % 4;
            CS_FX_SEL(t, ((CsFxView *)cs)->unk5C)->active = 1;
            modelAnimEntrySetUnkC(csId, ((CsFxView *)cs)->unk5C, 0x19);
            t->cool = 5;
        }
    }
    if (t->cool != 0) {
        t->cool--;
    }
    elapsed = (osGetTime() - t->last) * 64;
    t->left = t->duration - elapsed / 3000 / 1000000;
    if ((u64)t->left <= 0 || allDone) {
        heapFreeDeferred(*(CsFx **)cs);
        if (allDone != 0) {
            cs->unk4B[0] = 0x28;
        } else {
            cs->unk4B[0] = 0x1E;
        }
        *(CsFx **)cs = NULL;
    }
    renderCallbacksRegister(renderCountdownTimerHUD, t, 5);
}

typedef struct CsNodePair {
    /* 0x0 */ s16 a;
    /* 0x2 */ s16 b;
} CsNodePair;
extern s16 D_8074822C[][2];
extern CsNodePair D_80748244[];

void csCmdResolveNodePair(CsState *cs, s16 csId, s16 b, s16 c) {
    u8 *p;
    u8 found;
    s16 idx;
    s32 row;
    s32 col;
    CsNodePair *pr;

    found = 0;
    if (*(u8 **)cs == NULL) {
        *(u8 **)cs = heapAlloc(0xA);
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
            sfxPlayOnFreeSlot(0x2A1, 0x7FFF, 63.0f, 1.0f, 0, 0);
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
            sfxPlayOnFreeSlot(0x2A2, 0x7FFF, 63.0f, 1.0f, 0, 0);
        }
        p[6] ^= 1;
    }
}

void csCmdUpdateSlotIdView8A(CsState *cs, s16 csId, s16 b, s16 c) {
    func_806BD094(((CsSlotIdView *)gModelSlots)[hashTableLookup(csId)].unk8A, b);
}

extern ActorEntry gActiveActors[];
extern u16 gActiveActorCount;
void modelAnimEntryStart(s16, s16, s16);
void func_80641874(s16, s16);

s32 csCondSyncActorAnim(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 i;
    Actor *actor;

    for (i = 0; i < gActiveActorCount; i++) {
        actor = gActiveActors[i].actor;
        if (!(actor->flags & 0x2000) && actor->actorType == 4 && actor->attachMode == 1 && csId == actor->cutsceneId) {
            if (b != actor->unk10E[0] && actor->unk10E[0] != 0) {
                modelAnimEntryStart(csId, actor->unk10E[0], 2);
                func_80641874(actor->unk10E[0] + 4, 0);
                return 1;
            }
        }
    }
    return 0;
}




void csModelStateSetFirstByte(s16, s16);
extern u8 gPlayerCharacterId;
typedef struct CsEntry {
    /* 0x0 */ u8 state;
    /* 0x1 */ u8 pad1;
    /* 0x2 */ s16 timer;
    /* 0x4 */ u8 active;
    /* 0x5 */ u8 pad5;
} CsEntry;
typedef struct CsEntryView {
    /* 0x00 */ u8 pad0[0x18];
    /* 0x18 */ u8 state;
    /* 0x19 */ u8 pad19;
    /* 0x1A */ s16 timer;
    /* 0x1C */ u8 active;
} CsEntryView;
typedef struct CsEntrySet {
    /* 0x00 */ u8 pad0[0x18];
    /* 0x18 */ CsEntry part[9];
    /* 0x4E */ u8 unk4E;
    /* 0x4F */ u8 unk4F;
} CsEntrySet;
void csCmdStepMultiModelAnimations(CsState *cs, s16 csId, s16 b, s16 c) {
    CsEntrySet *p;
    CsEntryView *e;
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
    CsEntrySet *q;

    if (*(CsEntrySet **)cs == NULL) {
        p = *(CsEntrySet **)cs = heapAlloc(0x50);
        p->unk4E = 0;
        if (flagGet(0x146, 0) != 0) {
            p->part[0].state = 3;
            q = p; // FAKE: second web of p (a copy def kept alive by the differing def in the else arm)
            for (i = 1, e = (CsEntryView *)((u8 *)p + 6); i < 9; i++, e = (CsEntryView *)((u8 *)e + 6)) { e->state = 3; } // LAYOUT: body on the for line
        } else {
            q = (CsEntrySet *)((u32)p | 0); // FAKE: not a plain copy: stops copy-propagating q into the part[0] stores
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
        q->part[0].timer = 10;
        q->part[0].active = 1;
        for (i = 1, e = (CsEntryView *)((u8 *)(CsEntrySet *)((u32)p | 0) + 6); i < 9; i++, e = (CsEntryView *)((u8 *)e + 6)) { // FAKE: p | 0 blocks PRE of p + 6 shared with the first loop
            e->active = 1;
            e->timer = 10;
        }
        p->unk4F = 0;
    }
    p = *(CsEntrySet **)cs;
    for (i = 0, e = (CsEntryView *)p; i < 9; i++, e = (CsEntryView *)((u8 *)e + 6)) {
        if (e->active != 0) {
            j = i + 1;
            n++;
            modelAnimEntryGetState(csId, j, &anim, &animT, &animFlag);
            if (anim == e->state && animT < 0.1 && e->timer == 0) {
                modelAnimEntrySetUnkC(csId, j, 0);
                modelAnimEntrySetTime(csId, j, anim, 0);
                e->active = 0;
                modelSlotGetNodePos(csId, 1, i + 1, &x, &y, &z);
                sfxPlayAtPositionPooled(x, y, z, 0x1AE, 0xFF, 0x7F, 0x14, 0x50, 0.7f, 0);
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
        pl = gPlayerSlots->unk4;
        if (pl->state == 0x1C && pl->unk155[0] < 7 && gPlayerCharacterId == 0 && pl->attachMode == 1) {
            if (csId == pl->cutsceneId) {
                bestD = 100000.0f;
                best = -1;
                i = 0;
                do {
                    modelSlotGetNodePos(csId, 1, i + 1, &x, &y, &z);
                    x = gPrimaryPlayerActor->x - x;
                    z = gPrimaryPlayerActor->z - z;
                    d = x * x + z * z;
                    if (d < bestD) {
                        best = i;
                        bestD = d;
                    }
                    i++;
                } while (i != 9);
                if (best >= 0) {
                    e = (CsEntryView *)((u8 *)p + best * 6);
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
        csModelStateSetFirstByte(0xF, 0xA);
        heapFreeDeferred(*(void **)cs);
        cs->unk4B[0] = 0x28;
        *(void **)cs = NULL;
    }
}


void func_8002D6F8(s16);
void csCmdFreeModelSlotIndex(CsState *cs, s16 csId, s16 b, s16 c) {
    func_8002D6F8(csId);
}

void csCmdVarAdd(CsState *cs, s16 csId, s16 b, s16 c) {
    cs->unk14[b] = cs->unk14[b] + cs->unk14[c];
}

void csCmdCopyTargetPosSub10(CsState *cs, s16 csId, s16 b, s16 c) {
    f32 t = -10.0 - cs->unk14[b];
    t = t / -10.0;
    cs->unk14[c] = t * -1.0;
}

void csCmdVarIncrement(CsState *cs, s16 csId, s16 b, s16 c) {
    cs->unk14[b] = -1.0 - cs->unk14[b];
    cs->unk14[b] = 0.0 - cs->unk14[b];
}

typedef struct CsActorPosView {
    /* 0x000 */ u8 pad0[0x100];
    /* 0x100 */ f32 x;
    /* 0x104 */ f32 y;
    /* 0x108 */ f32 z;
} CsActorPosView;
void csCmdDecayTargetPosDiff(CsState *cs, s16 csId, s16 b, s16 c) {
    cs->unk14[b] = ((CsActorPosView *)gPrimaryPlayerActor)->x;
    cs->unk14[b + 1] = ((CsActorPosView *)gPrimaryPlayerActor)->y;
    cs->unk14[b + 2] = ((CsActorPosView *)gPrimaryPlayerActor)->z;
}

extern f32 gCsRotX;
extern f32 gCsRotZ;
extern f32 gCsGroundOffset;
typedef struct CsSavedTransform {
    /* 0x00 */ f32 v[10];
} CsSavedTransform;
void csCmdTransformSave(CsState *cs, s16 csId, s16 b, s16 c) {
    CsSavedTransform *p;

    if (*(CsSavedTransform **)cs == NULL) {
        *(CsSavedTransform **)cs = heapAlloc(0x28);
    }
    p = *(CsSavedTransform **)cs;
    p->v[0] = gCsPosX;
    p->v[1] = gCsPosY;
    p->v[2] = gCsPosZ;
    p->v[3] = gCsRotX;
    p->v[4] = gCsRotY;
    p->v[5] = gCsRotZ;
    p->v[6] = gCsScale;
    p->v[7] = gCsScale;
    p->v[8] = gCsScale;
    p->v[9] = gCsGroundOffset;
}

void csCmdTransformRestore(CsState *cs, s16 csId, s16 b, s16 c) {
    CsSavedTransform *p = *(CsSavedTransform **)cs;

    gCsPosX = p->v[0];
    gCsPosY = p->v[1];
    gCsPosZ = p->v[2];
    gCsRotX = p->v[3];
    gCsRotY = p->v[4];
    gCsRotZ = p->v[5];
    gCsScale = p->v[6];
    gCsScale = p->v[7];
    gCsScale = p->v[8];
    gCsGroundOffset = p->v[9];
}

void csCmdVarSlotDelta(CsState *cs, s16 csId, s16 b, s16 c) {
    CsSavedTransform *p = *(CsSavedTransform **)cs;
    s32 idx;
    f32 sx;
    f32 sy;
    f32 sz;

    idx = hashTableLookup(csId);
    sx = gModelSlots[idx].x;
    sy = gModelSlots[idx].y;
    sz = gModelSlots[idx].z;

    cs->unk14[c] = (p->v[0] - sx) / b;
    cs->unk14[c + 1] = (p->v[1] - sy) / b;
    cs->unk14[c + 2] = (p->v[2] - sz) / b;
}

extern s16 gCsModelIds[];
void csCmdPosFromNode(CsState *cs, s16 csId, s16 b, s16 c) {
    modelSlotGetNodePos(gCsModelIds[b], 1, c, &gCsPosX, &gCsPosY, &gCsPosZ);
}

void slotQueueSelectPlayerResource(u8);
void slotQueueCancel(s32, s32);
void slotQueueUpdate(s32, u8, s32);
void csCmdSlotQueueSelectPlayer(CsState *cs, s16 csId, s16 b, s16 c) {
    slotQueueSelectPlayerResource(b);
    if (c != 0) {
        slotQueueCancel(0xD, 0);
    } else {
        slotQueueUpdate(0xD, 1, 0);
    }
}

void func_80726EE0(u8);
void csCmdSetAudioUnk3(CsState *cs, s16 csId, s16 b, s16 c) {
    func_80726EE0(3);
}

extern f32 D_80748280[];
extern f32 D_8074828C[];
extern f32 D_807482A4;
extern s32 gMapChunkCount;
void lightGetColor(f32 *, f32 *, f32 *, s16);
void csCmdStepLightColor(CsState *cs, s16 csId, s16 b, s16 c) {
    f32 r, g, bl;
    s32 i;
    if (c != 0) {
        for (i = 0; i < gMapChunkCount; i++) {
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
        for (i = 0; i < gMapChunkCount; i++) {
            lightSetColor(r, g, bl, (s16)i);
        }
    }
}

void csCmdModelApplyTranslation(CsState *cs, s16 csId, s16 b, s16 c) {
    u8 *p = gPlayerSlots->unk4->customState;
    p[0x1FC] = b;
}

void func_8064B7C0(CsState *cs, s16 csId, s16 b, s16 c) {
}

void csCmdAllocSlotPointer(CsState *cs, s16 csId, s16 b, s16 c) {
}

void effectNodeSetUnk4A(s32, u8);
void effectNodeSetUnk4B(s32, u8);
u8 effectNodeGetUnk4B(s32);
void csCmdEnableEffectNodes5And6(CsState *cs, s16 csId, s16 b, s16 c) {
    effectNodeSetUnk4A(5, 1);
    effectNodeSetUnk4A(6, 1);
}

void csCmdResetEffectNodes5And6(CsState *cs, s16 csId, s16 b, s16 c) {
    effectNodeSetUnk4B(5, 0xFF);
    effectNodeSetUnk4B(6, 0xFF);
}

void csCmdEffectNodeStepAlpha(CsState *cs, s16 csId, s16 b, s16 c) {
    u8 v = effectNodeGetUnk4B(5);
    effectNodeSetUnk4B(5, v < 0xFC ? v + 3 : 0xFF);
    effectNodeSetUnk4B(6, v < 0xFC ? v + 3 : 0xFF);
    effectNodeSetUnk4A(5, 0);
    effectNodeSetUnk4A(6, 0);
}

extern Actor *gSpawnedActor;
Actor *spawnNodeSpawnById(s16, s16, s16, s16, s16, s16, s16);
Actor *spawnNodeActivate(s16, u16);
void actorScriptStart(void *, s32);
void scriptSetActorRampTarget(void *, f32, f32);
void csCmdSpawnActorNodeByCase(CsState *cs, s16 csId, s16 b, s16 c) {
    Actor *a;
    switch (b) {
        case 2:
            spawnNodeSpawnById(8, 0, 0, 0, 0, 0, 0);
            gSpawnedActor->flags &= ~4;
            break;
        case 1:
            a = spawnNodeActivate(8, 0);
            if (a != NULL) {
                a->flags |= 4;
                actorScriptStart(a, 0x35C);
                scriptSetActorRampTarget(a, 0.9f, 0.0f);
            }
            break;
        case 0:
            a = spawnNodeActivate(8, 0);
            if (a != NULL) {
                a->state = 0x3C;
            }
            break;
    }
}

void actorListSetPosById(s16, f32, f32, f32);

void csCmdSetPositionPreset(CsState *cs, s16 csId, s16 b, s16 c) {
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

s32 csCondVarLess(CsState *cs, s16 csId, s16 b, s16 c) {
    return (u8)(cs->unk14[b] < cs->unk14[c]);
}

void csCmdCheckCollectedSufficientItems(CsState *cs, s16 csId, s16 b, s16 c) {
    mapHasCollectedSufficientItems();
}

void csCondWorldHubFlagSet(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 idx = mapGetHubWorldIndex(gCurrentWorldId, 0);
    if (idx >= 8) {
        idx = 0;
    }
    flagGet(D_80744710[idx], 0);
}

s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
s32 mathAngleDistance(s16, s16);

s32 csCondActorFacingPos(CsState *cs, s16 csId, s16 b, s16 c) {
    s16 ang = mathAngleBetweenPoints2D((s16)gCsPosX, (s16)gCsPosZ, (s16)gPrimaryPlayerActor->x, (s16)gPrimaryPlayerActor->z);
    return (u8)(mathAngleDistance(ang, gPrimaryPlayerActor->yaw) < 0x384);
}

typedef struct CsPlayerSlot {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 pad1[3];
    /* 0x04 */ Actor *unk4;
    /* 0x08 */ u8 pad8[0x2E8];
} CsPlayerSlot; /* 0x2F0 */
extern u8 gPlayerCount;

s32 csFindPlayerSlotByModel(s32 a, s32 b) {
    s32 i = 0;
    CsPlayerSlot *p;
    Actor *q;
    if (gPlayerCount > 0) {
        p = (CsPlayerSlot *)gPlayerSlots;
        do {
            if (p->unk0 != 0) {
                q = p->unk4;
                if (q->attachMode == 1 && q->cutsceneId == a && q->unk10E[0] == b) {
                    return i;
                }
            }
            i++;
            p++;
        } while (i < gPlayerCount);
    }
    return -1;
}

void modelSlotGetTransformVectors();
void func_8067ABC0(s32, void *, s32, s16, s32, f32, f32, f32);

s32 csCondFindPlayerSlotByModel(CsState *cs, s16 csId, s16 b, s16 c) {
    f32 x, y, z;
    f32 u50, u4C, u48, u44, u40;
    s32 id;
    s32 idx;
    u32 pad0;
    u32 pad1;

    idx = csFindPlayerSlotByModel(csId, c);
    if (idx < 0) {
        return 0;
    }
    id = gCsModelIds[b];
    if (csFindPlayerSlotByModel(id, c) != -1) {
        return 0;
    }
    modelSlotGetTransformVectors(id, &x, &y, &z, &u50, &u4C, &u48, &u44, &u40, 1);
    func_8067ABC0(0, ((CsPlayerSlot *)gPlayerSlots + idx)->unk4, 9, (s16)(s32)(u4C * 11.377778f), 0, x, y, z);
    return 0;
}

extern s32 D_807552E8;

s32 csCondTransitionState5(CsState *cs, s16 csId, s16 b, s16 c) {
    return (D_807552E8 == 5) & 0xFF;
}

extern s32 D_807552F0;
s32 slotQueueGetValue(s32, u8);
void slotQueueAddValue(s32, u8, s16);

s32 csCondDepositItem(CsState *cs, s16 csId, s16 b, s16 c) {
    f32 q;
    s32 idx = csFindPlayerSlotByModel(csId, b);
    if (idx < 0) {
        return 0;
    }
    if (slotQueueGetValue(1, (u8)idx)) {
        slotQueueAddValue(7, (u8)idx, 1);
        q = (f32)slotQueueGetValue(7, (u8)idx) / (f32)D_807552F0;
        q = (f32)0.5 * q + 0.5f;
        sfxPlayOnFreeSlot(0x2A1, 0x7FFF, 63.0f, q, 5, 0);
        return 1;
    }
    return 0;
}

s32 csCondPlayerNearFixedPoint(CsState *cs, s16 csId, s16 b, s16 c) {
    f64 dz = ((CsPlayerView *)gPlayerSlots)->unk218 - 1274.0;
    f64 dx = ((CsPlayerView *)gPlayerSlots)->unk210 - 3081.0;
    if (dz * dz + dx * dx < 10000.0) {
        return 1;
    }
    return 0;
}

void csCmdDecayTargetPosCoord(CsState *cs, s16 csId, s16 b, s16 c) {
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
    gCsRotX += cs->unk14[c];
    if (gCsRotX > 8.0) {
        gCsRotX = 8.0f;
    }
    if (gCsRotX < -8.0) {
        gCsRotX = -8.0f;
    }
}

void csCmdRotXAdjust(CsState *cs, s16 csId, s16 b, s16 c) {
    if (gCsRotX > 1.2 || gCsRotX < -1.2) {
        if (gCsRotX > 0.0) {
            if (cs->unk14[b] > -1.0) {
                cs->unk14[b] = cs->unk14[b] - 0.1;
            }
        } else if (cs->unk14[b] < 1.0) {
            cs->unk14[b] = cs->unk14[b] + 0.1;
        }
        gCsRotX += cs->unk14[b];
    } else {
        gCsRotX = 0.0f;
        cs->unk14[b] = 0.0f;
    }
}

void actorSpawnNodeEntryScaled(s32, f32, f32, f32, s32, s32, s32, s32);

void csCmdSpawnFourNodeEntries(CsState *cs, s16 csId, s16 b, s16 c) {
    actorSpawnNodeEntryScaled(0x2F, gCsPosX, gCsPosY + 15.0f, gCsPosZ, 0, 1, -1, 0);
    actorSpawnNodeEntryScaled(0x2F, gCsPosX, gCsPosY + 15.0f, gCsPosZ, 0x400, 1, -1, 0);
    actorSpawnNodeEntryScaled(0x2F, gCsPosX, gCsPosY + 15.0f, gCsPosZ, 0x800, 1, -1, 0);
    actorSpawnNodeEntryScaled(0x2F, gCsPosX, gCsPosY + 15.0f, gCsPosZ, 0xC00, 1, -1, 0);
    effectSetDepth(1);
    effectCreateAtPosition(sEffectSparkConfig, 2.5f, gCsPosX, gCsPosY + 30.0f, gCsPosZ);
}

typedef struct CsCamObjView {
    /* 0x000 */ u8 pad0[0x104];
    /* 0x104 */ s32 unk104;
} CsCamObjView;
typedef struct CsShake {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ s32 unk4;
} CsShake;
void camStartShakeFromPoint(s32, s32, s32, f32, f32, f32, f32, f32);

void csCmdCamShakeOnAnim(CsState *cs, s16 csId, s16 b, s16 c) {
    u32 pad[4];
    s16 pad16;
    s16 anim;
    f32 animT;
    u8 animFlag;
    CsShake *p;
    CsCamObjView *cam;

    cam = gPlayerSlots->unk4->customState;
    if (*(CsShake **)cs == NULL) {
        p = heapAlloc(8);
        *(CsShake **)cs = p;
        p->unk0 = 0;
        p->unk4 = 0;
    }
    p = *(CsShake **)cs;
    modelAnimEntryGetState(csId, 1, &anim, &animT, &animFlag);
    if (anim == 0) {
        p->unk4 = 10;
    }
    if (anim == 2 && animT >= 0.8) {
        if (p->unk4 != 0) {
            camStartShakeFromPoint(cam->unk104, 4, 0xB, gCsPosX, gCsPosY, gCsPosZ, 200.0f, 600.0f);
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

void csCmdPlayAnimSlotB(CsState *cs, s16 csId, s16 b, s16 c) {
    s16 anim;
    f32 animT;
    u8 animFlag;
    u8 slot;

    if (cs->unk10[0] >= 0) {
        modelAnimEntryGetState(csId, b, &anim, &animT, &animFlag);
        slot = D_80770628[cs->unk10[0]];
        D_80770B68[slot] = mathSinF((s16)(((f32)anim + animT) * 2048.0 - 1024.0)) * 0.3 + 1.3;
        D_80770BC0[slot] = 1.0f;
    }
}

void csCmdPlayAnimSlot1(CsState *cs, s16 csId, s16 b, s16 c) {
    s16 anim;
    f32 animT;
    u8 animFlag;
    u8 slot;

    if (cs->unk10[0] >= 0) {
        modelAnimEntryGetState(csId, 1, &anim, &animT, &animFlag);
        slot = D_80770628[cs->unk10[0]];
        D_80770B68[slot] = mathSinF((s16)((anim << 11) / 27)) + 0.3;
        D_80770BC0[slot] = 2.0f;
    }
}


void csCmdAllocAnimTracking(CsState *cs, s16 csId, s16 b, s16 c) {
    s16 anim;
    f32 animT;
    u8 animFlag;
    s32 *p;

    if (*(s32 **)cs == NULL) {
        *(s32 **)cs = heapAlloc(4);
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


void csCmdCameraShakeOnModelAnim(CsState *cs, s16 csId, s16 b, s16 c) {
    f32 x;
    f32 y;
    f32 z;
    s16 anim;
    f32 animT;
    u8 animFlag;
    CsShake *p;

    if (*(CsShake **)cs == NULL) {
        p = heapAlloc(8);
        *(CsShake **)cs = p;
        p->unk0 = 0;
        p->unk4 = 0;
    }
    p = *(CsShake **)cs;
    modelAnimEntryGetState(csId, 2, &anim, &animT, &animFlag);
    anim = (f32)anim + animT;
    if (anim == 0x28 || anim == 0x32) {
        if (anim != p->unk0) {
            p->unk0 = anim;
            modelSlotGetNodePos(csId, 1, 3, &x, &y, &z);
            sfxPlayAtPositionPooled(x, y, z, 0x32, 0xFF, 0x7F, 0xA, 0x50, 0.3f, 0);
        }
    }
    modelAnimEntryGetState(csId, 3, &anim, &animT, &animFlag);
    if (anim == 0x14 || anim == 0x18) {
        if (anim != p->unk4) {
            p->unk4 = anim;
            modelSlotGetNodePos(csId, 1, 2, &x, &y, &z);
            sfxPlayAtPositionPooled(x, y, z, 0x332, 0xFF, 0x7F, 0, 0x50, 0.3f, 0);
        }
    }
}

void csCmdSpawnSparksOnModelAnim(CsState *cs, s16 csId, s16 b, s16 c) {
    f32 x;
    f32 y;
    f32 z;
    s16 anim;
    f32 animT;
    u8 animFlag;
    s32 *p;

    if (*(s32 **)cs == NULL) {
        *(s32 **)cs = heapAlloc(4);
        **(s32 **)cs = 0;
    }
    p = *(s32 **)cs;
    modelAnimEntryGetState(csId, 2, &anim, &animT, &animFlag);
    anim = (f32)anim + animT;
    if (anim == 0x22 || anim == 0x2E) {
        if (anim != *p) {
            *p = anim;
            modelSlotGetNodePos(csId, 1, 2, &x, &y, &z);
            sfxPlayAtPositionPooled(x, y, z, 0x257 + (anim == 0xA), 0xFF, 0x7F, 0xA, 0x50, 0.3f, 0);
        }
    }
}

void csCmdSpawnPuffsOnModelAnim(CsState *cs, s16 csId, s16 b, s16 c) {
    f32 x;
    f32 y;
    f32 z;
    s16 anim;
    f32 animT;
    u8 animFlag;
    s32 *p;

    if (*(s32 **)cs == NULL) {
        *(s32 **)cs = heapAlloc(4);
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
                sfxPlayAtPositionPooled(x, y, z, 0x3A, 0x50, 0x7F, 0, 0x50, 0.3f, 0);
                break;
        }
    }
}

void csCmdSfxOnAnimChange(CsState *cs, s16 csId, s16 b, s16 c) {
    s16 anim;
    f32 animT;
    u8 animFlag;
    s32 *p;

    if (*(s32 **)cs == NULL) {
        *(s32 **)cs = heapAlloc(4);
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
} CsTrailPoint;

typedef struct {
    CsTrailPoint pts[30];
    s32 anim[2];
} CsTrail;

extern f32 D_807F61FC;
extern f32 D_807F6200;
extern f32 D_807F6204;
extern s16 D_807482B0;
f32 mathAngleBetweenPointsRad(f32, f32, f32, f32);
u8 collisionGetFloorHeight(f32 *);

void csCmdSpawnParticleTrail(CsState *cs, s16 csId, s16 b, s16 c) {
    u32 pad0;
    u32 pad1;
    u32 pad2;
    CsTrail *tr;
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
    CsTrailPoint *pts;

    if (*(CsTrail **)cs == NULL) {
        tr = heapAlloc(0x170);
        *(CsTrail **)cs = tr;
        for (i = 0; i < 30; i++) { tr->pts[i].x = D_807F61FC; tr->pts[i].y = D_807F6200; tr->pts[i].z = D_807F6204; }
    }
    tr = *(CsTrail **)cs;
    pts = tr->pts;
    groundY = gCsPosY;
    if (collisionCheckGroundAtPoint(gCsPosX, gCsPosZ, &groundY)) {
        if (collisionGetFloorHeight(&floorY)) {
            gCsPosY = floorY;
        }
    } else {
        prev = D_807482B0 - 1;
        if (prev < 0) {
            prev = 29;
        }
        gCsPosY = pts[prev].y;
    }
    tr->pts[D_807482B0].x = gCsPosX;
    tr->pts[D_807482B0].y = gCsPosY;
    tr->pts[D_807482B0].z = gCsPosZ;
    idx = D_807482B0 + 1;
    if (idx == 30) {
        idx = 0;
    }
    gCsRotY = mathAngleBetweenPointsRad(pts[idx].x, pts[idx].z, gCsPosX, gCsPosZ) * 57.29577637f + 270.0;
    if (gCsRotY > 360.0) {
        gCsRotY -= 360.0;
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

void csCmdSetCeilAndFloorAtPos(CsState *cs, s16 csId, s16 b, s16 c) {
    f32 ceil;
    f32 floor;
    u8 active;
    u8 state;

    state = 2;
    ceil = gCsPosY + 20.0f;
    if (collisionCheckGroundAtPoint(gCsPosX, gCsPosZ, &ceil) != 0 && collisionGetFloorHeight(&floor) != 0) {
        if (floor < ceil) {
            state = 0;
            gCsPosY = ceil;
        } else {
            state = 1;
            gCsPosY = floor;
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
} CsSineState;

void effectNodeSetTargetAndStep(s32, f32, f32);

void csCmdSineMotionUpdate(CsState *cs, s16 csId, s16 b, s16 c) {
    CsSineState *p;
    CsSineState *t;
    s32 ang;
    s32 d;
    s32 e;

    if (*(CsSineState **)cs == NULL) {
        t = heapAlloc(0xC);
        *(CsSineState **)cs = t;
        t->unk0 = 0;
        t->unk4 = 0;
        t->unk8 = 0xDAC;
    }
    p = *(CsSineState **)cs;
    effectNodeSetTargetAndStep(0, mathSinF(p->unk8) * 60.0 + 40.0, 20.0f);
    if (p->unk0 == 0) {
        ang = p->unk8;
        if (ang >= 0x2BC && ang < 0x2C6) {
            sfxPlayOnFreeSlot(0x359, 0x7FFF, 63.0f, 0.6f, 0, 0);
            ang = p->unk8;
        }
        if ((ang >= 0x2EE && ang < 0x2F8) || (ang >= 0x960 && ang < 0x96A)) {
            if (cs->unk10[0] >= 0) {
                sfxSlotFreeSource(cs->unk10[0]);
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

s16 modelAnimEntryGetUnkC(s16, s16);
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
} CsBeatState;

typedef struct {
    u8 pad0[0x48];
    u8 unk48;
    u8 pad49[2];
    u8 unk4B;
} CsStateByteView;

void csCmdBeatSyncAnimation(CsState *cs, s16 csId, s16 b, s16 c) {
    CsBeatState *p;
    s16 frame;
    s16 anim;
    CsBeatState *t;
    f32 animT;
    f32 target;
    u8 animFlag;
    f32 d;

    if (*(CsBeatState **)cs == NULL) {
        t = heapAlloc(0x18);
        *(CsBeatState **)cs = t;
        t->unk0 = 0;
        t->unk4 = 0;
        t->unk8 = 0;
        t->unkC = D_807482C4;
        t->unk10 = 0;
        t->unk14 = 0x14;
    }
    p = *(CsBeatState **)cs;
    frame = modelAnimEntryGetUnkC(csId, 1);
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
            if (((CsStateByteView *)cs)->unk48 == 2) {
                p->unk4 = 0;
                ((CsStateByteView *)cs)->unk4B = 1;
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
        sfxPlayOnFreeSlot((s16)(0x34E + ((randomNonNegative() >> 15) % 100 >= 0x33)), 0x7FFF, 63.0f, 1.0f, 0x1E, 0);
        p->unk14 = (randomNonNegative() >> 15) % 30 + 0x3C;
    }
}


void csCmdAnimProgressFromCounter(CsState *cs, s16 csId, s16 b, s16 c) {
    f32 t;
    s32 idx;

    idx = mapGetHubWorldIndex(gCurrentWorldId, 0);
    t = (f32)(u32)gLevelCollectibleCounts[idx] / (f32)(u32)D_807446C0[idx];
    if (t > 1.0) {
        t = 1.0f;
    }
    if (b == 0) {
        t = 1.0f - t;
    }
    modelAnimEntrySetTime(csId, 1, 0, t);
    modelAnimEntrySetUnkC(csId, 1, 0);
}


void csCmdAnimProgressFromHubItems(CsState *cs, s16 csId, s16 b, s16 c) {
    s16 anim;
    f32 cur;
    u8 flag;
    f32 ratio;
    u8 idx;

    idx = mapGetHubWorldIndex(gCurrentWorldId, 0);
    ratio = (f32)gLevelCollectibleCounts[idx] / (f32)D_807446C0[idx];
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

void csCmdAnimStepInterpolate(CsState *cs, s16 csId, s16 b, s16 c) {
    s16 anim;
    f32 t;
    u8 flag;
    s32 *p;
    f32 v;
    f32 w;

    if (*(s32 **)cs == NULL) {
        p = heapAlloc(4);
        *(s32 **)cs = p;
        *p = 0;
    }
    p = *(s32 **)cs;
    modelAnimEntryGetState(csId, 1, &anim, &t, &flag);
    if (anim != *p) {
        switch (anim) {
            case 0xF:
                sfxPlayAtPositionPooled(gModelSlots[csId].x, gModelSlots[csId].y + 300.0f, gModelSlots[csId].z, 0x8E, 0xFF, 0x50, 0, 0x50, 0.3f, 0);
                break;
            case 0:
                sfxPlayAtPositionPooled(gModelSlots[csId].x, gModelSlots[csId].y + 300.0f, gModelSlots[csId].z, 0x8F, 0xFF, 0x64, 0, 0x50, 0.3f, 0);
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

typedef struct CsStateFlagView {
    /* 0x00 */ u8 pad0[0x5C];
    /* 0x5C */ u8 unk5C;
    /* 0x5D */ u8 pad5D;
    /* 0x5E */ u16 unk5E;
} CsStateFlagView;

void actorAppendCallback(Actor *, s32, s32, u8, s32, void *);

void csCmdFindNearestActorToCamera(CsState *cs, s16 csId, s16 b, s16 c) {
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
    cam = gPrimaryPlayerActor->customState;
    if (((CsStateFlagView *)cs)->unk5C != 0) {
        id = ((CsStateFlagView *)cs)->unk5E;
        for (i = 0; i < gActiveActorCount; i++) {
            a = gActiveActors[i].actor;
            if (a->actorType == id) {
                dx = a->x - gCsPosX;
                dy = a->y - gCsPosY;
                dz = a->z - gCsPosZ;
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
        if (b == 0 && best != NULL && best->actorType == 0x55) {
            ((CsCamFlagsView *)cam)->unk1F0 &= 0xFFDFFFFF;
        }
    }
}

typedef struct CsAnimSlotView {
    u8 pad0[0x8A];
    s16 unk8A;
    u8 pad8C[4];
} CsAnimSlotView;

void csCmdPatternBufferMatch(CsState *cs, s16 csId, s16 b, s16 c) {
    u8 *p;
    u8 full;
    u8 pat[4];
    s8 i;

    full = 0;
    if (*(u8 **)cs == NULL) {
        p = heapAlloc(6);
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
    switch (((CsAnimSlotView *)gModelSlots)[hashTableLookup(csId)].unk8A) {
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

void csSeqMatch(CsState *cs, s16 csId, s16 val, u8 *pat, s32 len, s16 okId, s16 failId) {
    u8 *p;
    s8 i;
    u8 head;
    s32 cnt;
    s32 j;

    if (*(u8 **)cs == NULL) {
        p = heapAlloc(7);
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

typedef struct { u8 b[4]; } CsPat4;
extern CsPat4 D_807482DC;

void csCmdSeqMatchPattern4(CsState *cs, s16 csId, s16 val, s16 c) {
    CsPat4 pat = D_807482DC;

    csSeqMatch(cs, csId, val, (u8 *)&pat, 4, 5, 0x14);
}

typedef struct { u8 b[5]; } CsPat5;
extern CsPat5 D_807482E0;

void csCmdSeqMatchPattern5(CsState *cs, s16 csId, s16 val, s16 c) {
    CsPat5 pat = D_807482E0;

    csSeqMatch(cs, csId, val, (u8 *)&pat, 5, 4, 0x14);
}

typedef struct { u8 b[3]; } CsPat3;
extern CsPat3 D_807482E8;

void csCmdSeqMatchPattern3(CsState *cs, s16 csId, s16 val, s16 c) {
    CsPat3 pat = D_807482E8;

    csSeqMatch(cs, csId, val, (u8 *)&pat, 3, 7, 0x14);
}

extern CsPat4 D_807482EC;

void csCmdSeqMatchPattern4B(CsState *cs, s16 csId, s16 val, s16 c) {
    CsPat4 pat = D_807482EC;

    csSeqMatch(cs, csId, val, (u8 *)&pat, 3, 7, 0x14);
}

void csCmdRandomizeCutsceneTimer(CsState *cs, s16 csId, s16 b, s16 c) {
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
        sfxPlayOnFreeSlot(0x8A, 0xBB8, 63.0f, 1.0f, 0x1E, 0);
    }
}

typedef struct CsStateTailView {
    /* 0x00 */ u8 pad0[0x98];
    /* 0x98 */ s16 unk98;
} CsStateTailView;
s32 actorSpawn(s32, s32);

void csCmdSpawnBurstColoredLights(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 *q;
    f32 x;
    f32 y;
    f32 z;
    f64 g;
    f64 bl;

    if (b != 11) {
        modelSlotGetNodePos(csId, 1, 1, &x, &y, &z);
    }
    ((CsStateTailView *)cs)->unk98 = y - gCsPosY;
    if (*(s32 **)cs == NULL) {
        *(s32 **)cs = heapAlloc(4);
        **(s32 **)cs = 0;
    }
    q = *(s32 **)cs;
    switch (b) {
        case 10:
        case 11:
            sfxPlayAtPositionPooled(x, y, z, 0x305, 0x64, 0x7F, 0, 0, 0.0f, 0);
            actorSpawn(0xB3, 0x5D);
            gSpawnedActor->sub4->scaleX = gSpawnedActor->sub4->scaleX * 3.2;
            gSpawnedActor->sub4->scaleY = gSpawnedActor->sub4->scaleY * 3.2;
            gSpawnedActor->sub4->scaleZ = gSpawnedActor->sub4->scaleZ * 3.2;
            gSpawnedActor->flags |= 0x400;
            actorScriptStart(gSpawnedActor, 0x335);
            if (b == 11) {
                gSpawnedActor->x = gCsPosX;
                gSpawnedActor->y = gCsPosY;
                gSpawnedActor->z = gCsPosZ;
                break;
            }
            gSpawnedActor->x = x;
            gSpawnedActor->y = y;
            gSpawnedActor->z = z;
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

void csCmdSlotQueuePurchaseFlag(CsState *cs, s16 csId, s16 b, s16 c) {
    if (slotQueueGetValue(1, 0) >= 2) {
        slotQueueUpdate(1, 0, 0);
        slotQueueAddValue(1, 0, -2);
        flagSet(0x83, 1, 0);
    }
}

void csCmdSumFlagsE6ThroughEA(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 sum;

    sum = flagGet(0xE6, 0);
    sum += flagGet(0xE8, 0);
    sum += flagGet(0xE9, 0);
    sum += flagGet(0xE7, 0);
    sum += flagGet(0xEA, 0);
    ((u8 *)cs)[0x4B] = sum;
}

s32 csCondFlags82Or83(CsState *cs, s16 csId, s16 b, s16 c) {
    if (flagGet(0x82, 0) == 0) {
        return 1;
    }
    if (flagGet(0x83, 0) != 0) {
        return 1;
    }
    return 0;
}

extern u8 gPlayerCharacterId;

u8 csCondCheckSlotMapIndex(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 idx;
    u8 v;

    idx = mapGetHubWorldIndex(gCurrentWorldId, 0);
    if (idx >= 8) {
        idx = 0;
    }
    v = D_807446F0[idx];
    return gPlayerCharacterId == v;
}

s32 frameTimingGetMapIndex(void);
s32 func_806FB418(void);
extern s16 D_807446D0[];

s32 csCondCheckFrameTimingMap(CsState *cs, s16 csId, s16 b, s16 c) {
    s16 idx;

    idx = frameTimingGetMapIndex();
    return (u8)((s16)func_806FB418() >= D_807446D0[idx]);
}

extern u8 gPlayerInventoryTable[][0x5E];

u8 csCondCheckKongItems(CsState *cs, s16 csId, s16 b, s16 c) {
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
    cur = frameTimingGetMapIndex();
    row = gPlayerInventoryTable[idx];
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

s32 csCondCheckAllKongs(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 res = 0;
    u8 i;

    for (i = 2; i < 7; i++) {
        if (csCondCheckKongItems(cs, csId, i, 1) == 0) {
            res = 1;
        }
    }
    return res;
}

typedef struct CsEffState {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ f32 unk4;
} CsEffState;
typedef struct CsEffView {
    /* 0x000 */ u8 pad0[0x344];
    /* 0x344 */ f32 unk344;
    /* 0x348 */ u8 pad348[0x18];
    /* 0x360 */ f32 unk360;
    /* 0x364 */ f32 unk364;
    /* 0x368 */ u8 pad368[0x1C];
    /* 0x384 */ CsEffState *unk384;
} CsEffView;
s32 camIsPathPaused(void);
s32 camIsCutsceneActive(void);
extern s8 D_807F6950;
extern s8 D_807F6951;

void func_8064EE08(CsEffView *e, u8 *flag) {
    CsEffState *s;

    if (e->unk384 == NULL) {
        s = heapAlloc(8);
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
                sfxPlayOnFreeSlot(0x2E8, 0x7FFF, 63.0f, 1.0f, 0, 0);
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
        e->unk344 = mathSinF((gFrameCounter * 0x3C) & 0xFFF) * 2.75f + s->unk4;
    }
    e->unk364 = e->unk360;
}

void camStartPath(void *, s32, s32);
void sfxAllocateChannel(s32, f32);
extern u8 D_80721530[];

void csCmdSpawnActorAtPoint(CsState *cs, s16 csId, s16 b, s16 c) {
    effectSetColor(0xFF, 0xFF, 0xFF, 0x80);
    effectSetCallback(func_8064EE08);
    effectSetDuration(-1);
    effectSetDepth(1);
    effectSetMode(2);
    effectCreateAtPosition(D_80721530, 0.0f, gCsPosX, gCsPosY + 17.5, gCsPosZ);
    actorSpawn(0x9C, 0x53);
    gSpawnedActor->x = gCsPosX;
    gSpawnedActor->y = gCsPosY;
    gSpawnedActor->z = gCsPosZ;
    gSpawnedActor->yaw = gCsRotY * 4096.0f / 360.0f;
    if (gCurrentMap == 0xB2 || (gCurrentMap == 0xAD && b == 4)) {
        gSpawnedActor->yaw += 0x800;
    }
    camStartPath(gSpawnedActor, 0x22, 5);
    sfxAllocateChannel(0xAB, 1.0f);
    sfxPlayOnFreeSlot(0x2EA, 0x7FFF, 63.0f, 1.0f, 0, 0);
    D_807F6951 = b;
    D_807F6950 = 0;
}

void sfxStopChannel(s32, s32);

u8 csCondAudioFlag(CsState *cs, s16 csId, s16 b, s16 c) {
    if (D_807F6950) {
        sfxStopChannel(0xAB, 0);
    }
    return D_807F6950;
}


u8 csCondActorInFront(CsState *cs, s16 csId, s16 b, s16 c) {
    f32 s;
    f32 d;
    f32 co;
    f32 r;
    s16 angle;

    angle = gCsRotY * 4096.0f / 360.0f;
    s = mathSinF(angle);
    co = mathCosF(angle);
    d = gCsPosX * s + gCsPosZ * co;
    d = -d;
    r = (gPrimaryPlayerActor->x * s + co * gPrimaryPlayerActor->z) + d;

    return r > 6.0;
}

u8 csCondTrue(CsState *cs, s16 csId, s16 b, s16 c) {
    return 1;
}

extern s8 D_807FC8D0;

void csCmdSetFlag1C1Or1C2(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 flag;

    if (D_807FC8D0 == 5) {
        flag = 0x1C1;
    } else {
        flag = 0x1C2;
    }
    flagSet(flag, 1, 0);
}

extern u8 gCurrentPlayerIndex;

typedef struct {
    u8 pad0[0xA];
    u16 v[0x2A];
} CsFlagRow;

typedef struct {
    CsFlagRow e[8];
    u8 pad[0x16];
} CsFlagTable;

u8 csCondKongHasHubItems(CsState *cs, s16 csId, s16 b, s16 c) {
    CsFlagTable *p = (CsFlagTable *)gPlayerInventoryTable + gCurrentPlayerIndex;
    s32 idx = mapGetHubWorldIndex(gCurrentWorldId, 0);

    return p->e[(&gPlayerCharacterId)[gCurrentPlayerIndex]].v[idx] > 0;
}

s32 flagCountRange(s32, s32, s32);

u8 csCondCountFlags261Ge4(CsState *cs, s16 csId, s16 b, s16 c) {
    return flagCountRange(0x261, 0xA, 0) >= 4;
}


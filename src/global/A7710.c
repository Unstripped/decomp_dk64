#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB44;
extern void *gActivePlayerState;
s32 actorSpawn(s32, s32);

u64 D_807FC7D0;
u8 D_807FC7D8;

void hudSpawnCountdownTimer(s16 x, s16 y, u8 seconds) {
    actorSpawn(0xB0, 0);
    if (x & 0x8000) {
        seconds--;
        D_807FBB44->unk15F = 0xB;
    } else {
        D_807FBB44->unk15F = 6;
    }
    x &= 0x7FFF;
    D_807FBB40->unk11C = (s32)D_807FBB44;
    *(s32 *)((u8 *)gActivePlayerState + 0x1A8) = (s32)D_807FBB44;
    *(s32 *)((u8 *)D_807FBB44->unk174 + 0xC) = seconds;
    D_807FBB44->x = (f32)x;
    D_807FBB44->y = (f32)y;
    D_807FBB44->state = 1;
    D_807FBB44->unk128 = 0;
}

void actorSetStateTwo(Actor *actor) {
    actor->state = 2;
    actor->unk155[0] = 0;
    actor->unk128 = 0xFF;
}

void actorSetStateOne(Actor *actor) {
    if (actor != NULL) {
        actor->state = 1;
        actor->unk155[0] = 0;
    }
}

void hudCountdownTimerSaveElapsed(Actor *actor) {
    D_807FC7D0 = osGetTime() - *(u64 *)actor->unk174;
}

void actorSetStateThree(Actor *actor) {
    actor->state = 3;
    actor->unk155[0] = 0;
}

typedef struct GfxResource {
    /* 0x0 */ u8 pad[4];
    /* 0x4 */ void *unk4;
} GfxResource;

typedef struct RenderActorSub {
    /* 0x00 */ u8 pad[0x10];
    /* 0x10 */ u8 unk10;
} RenderActorSub;

typedef struct RenderState {
    /* 0x276 */ u8 pad[0x276];
    /* 0x276 */ s16 unk276;
} RenderState;

#define WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (_w1); }

extern Gfx D_1000118;
extern Mtx D_2000180;
extern Gfx D_8071FC58;
extern RenderState *gPlayerSlots;
s32 func_805FCA64(void);
Gfx *func_8070068C(Gfx *);
GfxResource *gfxResourceFindById(u8);
Gfx *textDrawStringVtx(Gfx *, s32, s16, s16, void *, s32);
Gfx *textDrawAnimated(Gfx *, u8, s32, f32, f32, f32, f32);
f32 sinApprox(f32);
f32 cosApprox(f32);
void func_8071495C(void);
void func_80714CC0(void *, f32, f32, f32, f32);

Gfx *renderActorSpriteCallback(Gfx *gfx, Actor *actor) {
    RenderActorSub *sub;
    /* unused: the original function reserves 0x18 and 8 bytes of its frame here */
    u8 stackPad0[0x18];
    f32 angle;
    u8 stackPad1[8];
    f32 sinAngle;
    s32 unk15F;
    s32 offset;

    sub = actor->unk174;
    if (func_805FCA64() != 0) {
        WRITE_GFX(gfx++, 0xDE000000, (u32)&D_1000118);
        WRITE_GFX(gfx++, 0xFC119623, 0xFF2FFFFF);
        WRITE_GFX(gfx++, 0xFA000000, (actor->unk128 & 0xFF) | 0xFFFFFF00);
        WRITE_GFX(gfx++, 0xDA380003, (u32)&D_2000180);
        WRITE_GFX(gfx++, 0xE200001C, 0x00504240);
        unk15F = actor->unk15F;
        if (unk15F == 0xB) {
            gfx = func_8070068C(gfx);
            gfx = textDrawStringVtx(gfx, 0x86, (s16)(s32)(actor->x * 4.0f),
                                (s16)((gPlayerSlots->unk276 * 4) - 0x3C),
                                gfxResourceFindById(sub->unk10)->unk4, 1);
        } else {
            angle = (f32)(6.28318548202514648 - 2.0 * actor->unk160);
            offset = 8;
            if (actor->unk168 == 3) {
                offset = -7;
            }
            gfx = textDrawAnimated(gfx, sub->unk10, unk15F, actor->x + (f32)offset,
                                actor->y + 5.0f, 0.0f, 1.0f);
            if (actor->state == 2) {
                gfx = func_8070068C(gfx);
                func_8071495C();
                sinAngle = sinApprox(angle);
                func_80714CC0(&D_8071FC58, 0.5f,
                              (f32)((f64)sinAngle * 40.0 + (f64)(40.0f + actor->x)),
                              (f32)((f64)cosApprox(angle) * 25.0 + (f64)actor->y),
                              0.0f);
            }
        }
    }
    return gfx;
}

typedef struct CountdownTimerState {
    /* 0x00 */ u64 unk0;
    /* 0x08 */ u32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ u8 unk10;
} CountdownTimerState;

extern u64 D_807445B0;
extern u64 gCamPathTimeDelta;
extern s32 gCurrentMap;
u64 __ll_mul(u64, u64);
u64 __ull_div(u64, u64);
u64 __ull_rem(u64, u64);
f64 __ull_to_d(u64);
s32 _sprintf(char *, char *, ...);
s32 strlen(char *);
s16 sfxPlayOnFreeSlot(s32, s32, f32, f32, s32, s32);
s32 randomNonNegative(void);
f32 func_806FDA8C(s16);
void func_806FDAB8(s16, f32);
s16 gfxResourceCreate(s16, char *, u8, f32, f32, f32);
void gfxResourceSetString(s16, char *);
void renderCallbacksRegister(void *, void *, s32);

void hudCountdownTimerUpdate(void) {
    f32 nextBeepAngle;
    f32 angle;
    char text[0x20];
    CountdownTimerState *timer;
    s32 pad;
    u64 usec;
    s32 secsLeft;

    timer = D_807FBB40->unk174;
    if (!(D_807FBB40->flags & 0x10)) {
        if (D_807FBB40->unk15F == 6) {
            _sprintf(text, "%.2d", timer->unkC);
        } else {
            _sprintf(text, "%.2d:%.2d:00", (u32)timer->unkC / 60U, (u32)timer->unkC % 60U);
        }
        timer->unk10 = gfxResourceCreate(D_807FBB40->unk15F == 0xB ? 6 : 3, text, D_807FBB40->unk15F, 0.0f, 0.0f, 0.0f);
    }
    if (D_807FBB40->state == 3) {
        timer->unk0 = osGetTime() - D_807FC7D0;
        D_807FBB40->state = 2;
        D_807FBB40->unk155[0] = 1;
    }
    timer->unk0 += D_807445B0;
    if (D_807FBB40->unk15F == 0xB) {
        timer->unk0 += gCamPathTimeDelta;
    }
    usec = __ull_div(__ll_mul(osGetTime() - timer->unk0, 0x40), 0xBB8);
    timer->unk8 = __ull_div(usec, 0xF4240);
    if (gCamPathTimeDelta == 0) {
        D_807FC7D8 = __ull_rem(__ull_div(usec, 0x2710), 0x64);
    }
    nextBeepAngle = ((f32)(s32)((func_806FDA8C(timer->unk10) - 1.5707964f) / 3.1415927f) * 3.1415927f) + 3.1415927f + 1.5707964f;
    angle = (f32)(((__ull_to_d(usec) / 10000.0) / 100.0) * 3.1415927410125732 + 1.5707963705062866);
    func_806FDAB8(timer->unk10, 0.0f);
    secsLeft = timer->unkC - timer->unk8;
    switch (D_807FBB40->state) {
    case 1:
        if (D_807FBB40->unk128 < 0xFF) {
            if (D_807FBB40->unk128 + 3 >= 0x100) {
                D_807FBB40->unk128 = 0xFF;
            } else {
                D_807FBB40->unk128 = D_807FBB40->unk128 + 3;
            }
        }
        func_806FDAB8(timer->unk10, 1.5707964f);
        D_807FBB40->unk168 = 0;
        break;
    case 4:
        D_807FBB40->state = 2;
        D_807FBB40->unk155[0] = 0xFF;
        // fallthrough
    case 2:
        if (D_807FBB40->unk155[0] == 0) {
            D_807FBB40->unk155[0] = D_807FBB40->unk155[0] + 1;
            timer->unk0 = osGetTime();
            timer->unk8 = 0;
            angle = 1.5707964f;
        }
        secsLeft = timer->unkC - timer->unk8;
        if (secsLeft >= 0) {
            func_806FDAB8(timer->unk10, angle < 0.0f ? 0.0f : angle);
            D_807FBB40->unk160 = angle < 0.0f ? 0.0f : angle;
            if (nextBeepAngle <= angle) {
                if (timer->unk8 >= timer->unkC
                    && (D_807FBB40->unk15F == 6 || timer->unkC < timer->unk8 || D_807FC7D8 >= 0x5B)) {
                    D_807FBB40->state = 5;
                    D_807FBB40->unk155[0] = 0;
                } else if (D_807FBB40->unk15F == 6) {
                    if ((s32)(nextBeepAngle / 3.1415927f) & 1) {
                        sfxPlayOnFreeSlot(0x8E, 0x58EF, 63.0f, 1.0f, 5, 0);
                    } else {
                        sfxPlayOnFreeSlot(0x8F, 0x58EF, 63.0f, 1.0f, 5, 0);
                    }
                }
                if (secsLeft == 0xA) {
                    D_807FBB40->state = 4;
                }
            }
            if (D_807FBB40->unk15F == 6) {
                _sprintf(text, "%.2d", secsLeft);
            } else if (D_807FBB40->state != 5) {
                _sprintf(text, "%.2d:%.2d:%.2d", secsLeft / 60, secsLeft % 60, 0x63 - D_807FC7D8);
            } else {
                _sprintf(text, "00:00:00");
            }
            D_807FBB40->unk168 = strlen(text);
            gfxResourceSetString(timer->unk10, text);
        } else {
            D_807FBB40->state = 5;
            D_807FBB40->unk155[0] = 0;
            gfxResourceSetString(timer->unk10, "00:00:00");
        }
        break;
    case 5:
        switch (gCurrentMap) {
        case 0x35:
        case 0x49:
        case 0x9B:
        case 0x9C:
        case 0x9D:
        case 0x9E:
        case 0x9F:
        case 0xA0:
        case 0xA1:
        case 0xA2:
            switch (D_807FBB40->unk155[0]) {
            case 0:
            case 7:
            case 14:
            case 21:
            case 28:
            case 35:
            case 42:
                sfxPlayOnFreeSlot(0x3BD, 0x7FFF, 63.0f, 1.15f, 1, 0x80);
                break;
            }
            D_807FBB40->unk155[0] = D_807FBB40->unk155[0] + 1;
            break;
        case 0x13:
        case 0x15:
        case 0x16:
        case 0x17:
        case 0x18:
        case 0xCB:
        case 0xCC:
        case 0xCD:
        case 0xCE:
        case 0xCF:
            break;
        case 0x14:
        default:
            if (D_807FBB40->unk155[0] == 0) {
                sfxPlayOnFreeSlot(0x1BB, 0x7FFF, 63.0f, 1.0f, 0, 0);
                D_807FBB40->unk155[0] = D_807FBB40->unk155[0] + 1;
            }
            break;
        }
        D_807FBB40->unk168 = 0;
        if (secsLeft <= 0 && secsLeft >= -2) {
            func_806FDAB8(timer->unk10, (f32)((((f64)((randomNonNegative() >> 15) % 180)) / 180.0) * 3.1415927410125732 + 1.5707963705062866));
        }
        break;
    }
    renderCallbacksRegister(renderActorSpriteCallback, D_807FBB40, 7);
}

void func_806A36F4(void) {
}

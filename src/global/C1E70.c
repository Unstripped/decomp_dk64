#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB4C;

extern Actor *D_807FBB44;
extern s16 D_80744710[];
extern s8 D_807506A4;
extern s8 D_80750660;
extern u8 D_807FC8D0;

s32 flagGet(s16, s32);
s32 actorSpawn();
f32 func_80612790(s16);
f32 func_80612794(s16);

typedef struct R1C0C1Sub174 {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s8 unk2;
    /* 0x04 */ Actor *unk4;
} R1C0C1Sub174;

#define R1C0C1_SPAWNED_146 (((R1C0C1Spawned *)D_807FBB44)->unk146)
typedef struct R1C0C1Spawned {
    /* 0x000 */ u8 pad0[0x146];
    /* 0x146 */ s16 unk146;
} R1C0C1Spawned;

void func_806BD170(void) {
    Actor *activeRingActor;
    s16 i;
    s16 activeRingIdx;
    s16 count;
    s16 pos;
    R1C0C1Sub174 *sub;

    activeRingIdx = -1;
    i = 0;
    count = 0;
    for (; i < 8; i++) {
        if (flagGet(i + 0x1BC, 0) == 0) {
            actorSpawn(0x14E, 0xCD);
            D_807FBB44->unk12A = 0x7D0;
            D_807FBB44->unk60 |= 0x800400;
            pos = i * 0x200 + 0x104;
            D_807FBB44->unk60 &= 0xFFFF7FFF;
            D_807FBB44->unk16A = 0xFF;
            D_807FBB44->unk16B = 0xFF;
            D_807FBB44->unk16C = 0xFF;
            D_807FBB44->unk128 = 0xFF;
            D_807FBB44->x = func_80612794(pos) * 270.0f + D_807FBB40->x;
            D_807FBB44->z = func_80612790(pos) * 270.0f + D_807FBB40->z;
            D_807FBB44->y = 100.0f;
            D_807FBB44->yaw = pos;
            R1C0C1_SPAWNED_146 = 0;
            D_807FBB44->state = 0;
            sub = D_807FBB44->unk174;
            sub->unk0 = 0;
            sub->unk4 = D_807FBB40;
            sub->unk2 = i;
            if (flagGet(D_80744710[i], 0) != 0) {
                activeRingIdx = i;
                activeRingActor = D_807FBB44;
                activeRingActor->state = 5;
                count++;
            }
        }
    }
    D_807506A4 = 0;
    if (flagGet(0x1BB, 0) == 0) {
        activeRingIdx = -1;
    }
    if (D_80750660 == 0 && activeRingIdx != -1) {
        ((R1C0C1Spawned *)activeRingActor)->unk146 = 1;
        activeRingActor->state = 1;
        D_80750660 = 1;
        D_807FC8D0 = activeRingIdx;
    }
}

extern s16 D_8076A0A6;
extern s8 D_807506B4;
extern s8 D_807506A8[];
extern f32 D_807FC8D4;
extern s32 gCamActor;

s32 func_806BDD2C(void);
void actorCopyPoseAndScale(void *, void *, f32);
s32 actorScriptStart(void *, s32);
void actorUpdateModelMatrix(void *, s32);
s32 camStartPath(void *, s32, s32);
s32 currentActorTestClearFlag();
s32 camIsCutsceneActive(void);
void camStartShake(s32, s32, s32);
s32 sfxAllocateChannel(s32, f32);
s16 sfxPlayOnFreeSlot(s16, s32, f32, f32, u8, u8);
void flagSet(s16, s32, s32);

typedef struct RingNodePtr178 {
    /* 0x00 */ Actor *unk0;
} RingNodePtr178;

typedef struct RingNodeSub4 {
    /* 0x00 */ u8 pad0[0x64];
    /* 0x64 */ u16 unk64;
} RingNodeSub4;

typedef struct RingNodeActor178 {
    /* 0x000 */ u8 pad0[0x178];
    /* 0x178 */ RingNodePtr178 *unk178;
} RingNodeActor178;

void actorNodeRingUpdate(void) {
    RingNodePtr178 *nodePtr = ((RingNodeActor178 *)D_807FBB40)->unk178;
    f32 dx;
    f32 dz;
    u8 shakeMagnitude;
    u16 shakeDuration;
    s16 v3 = D_8076A0A6;
    s16 idx;
    s8 *cnt = &D_807506B4;
    s8 n;

    if (!(D_807FBB40->unk60 & 0x10)) {
        if (func_806BDD2C() != 0) {
            D_807FBB40->state = 0x40;
            return;
        }
        D_807FBB40->unk12A = 0x7D0;
        D_807FBB40->unk60 |= 0x400;
        v3 = 0;
        D_807506B4 = 0; actorSpawn(0x73, 0xC4, &D_807FBB40);
        actorCopyPoseAndScale(D_807FBB44, D_807FBB40, D_807FBB40->unk4->unk38);
        D_807FBB44->unk64 |= 0x20;
        D_807FBB44->unk60 |= 0x400;
        D_807FBB44->unk12A = 0x7D0;
        nodePtr->unk0 = D_807FBB44;
        D_807FC8D4 = 1000.0f;
        func_806BD170();
        D_807FBB40->state = 0;
        if (D_80750660 != 0) {
            D_80750660 = 0;
        }
        if (flagGet(0x1BB, 0) == 0) {
            D_807FBB40->state = 1;
        }
    }
    idx = -1;
    if (v3 != 0) {
        idx = 0;
        while (!(v3 & 1)) {
            v3 >>= 1;
            idx++;
        }
    }
    dx = D_807FBB40->x - D_807FBB4C->x;
    dz = D_807FBB40->z - D_807FBB4C->z;
    shakeDuration = 0;
    D_807FC8D4 = dx * dx + dz * dz;
    switch (D_807FBB40->state) {
        case 1:
            actorScriptStart(D_807FBB40, 0x2EF);
            D_807FBB40->state = 2;
            camStartPath(D_807FBB4C, 2, 1);
            break;
        case 2:
            if (currentActorTestClearFlag() != 0) {
                sfxAllocateChannel(0x7D, 1.0f);
                actorScriptStart(D_807FBB40, 0x2F1);
                D_807FBB40->state = 3;
                D_807FBB40->unk155[0] = 0;
            }
            break;
        case 3:
            if (D_807FBB40->unk155[0] & 1) {
                D_807FBB40->unk155[0]++;
                shakeMagnitude = 0xF; shakeDuration = 0x28;
            }
            break;
    }
    if (camIsCutsceneActive() == 0) {
        if (((RingNodeSub4 *)D_807FBB40->unk4)->unk64 != 0x2F0) {
            actorScriptStart(D_807FBB40, 0x2F0);
        }
    }
    if (shakeDuration) {
        camStartShake(gCamActor, shakeMagnitude, shakeDuration);
    }
    if (idx >= 0) {
        n = *cnt;
        if (idx == D_807506A8[n]) {
            n++;
            D_807506B4 = n;
            if (D_807506A8[n] == -1) {
                sfxPlayOnFreeSlot(0x1DA, 0x7FFF, 63.0f, 1.0f, 5, 0);
                flagSet(0x28, 1, 1);
                flagSet(0x26, 1, 1);
                if (D_807506B4 == -1) {} // FAKE: dead test triggers constant web for -1 in v0
                D_807506B4 = -1;
            }
        } else {
            D_807506B4 = 0;
        }
    }
    D_8076A0A6 = 0;
    actorUpdateModelMatrix(D_807FBB40, 0);
}


typedef struct R1C0C1Ptr178 {
    /* 0x00 */ Actor *unk0;
} R1C0C1Ptr178;

typedef struct R1C0C1Act178 {
    /* 0x000 */ u8 pad0[0x178];
    /* 0x178 */ R1C0C1Ptr178 *unk178;
} R1C0C1Act178;

typedef struct R1C0C1Blob8 {
    /* 0x00 */ s8 b[8];
} R1C0C1Blob8;

extern s16 D_80750664[];
extern s16 D_80750684[];
extern R1C0C1Blob8 D_807506B8;
extern u8 D_80720A7C;

void sfxStopChannel(s32, s32);
void csModelStateSetFirstByte(s32, s32);
void camResumePath(void);
void func_80712524(s32, s32);
void func_80714950(s32);
void func_8071498C(void (*)(void));
void func_8071AADC(void);
void func_807149C8(s32, s32, s32, s32);
void func_80714CC0(void *, f32, f32, f32, f32);
f32 randomFloat(void);

void func_806BD7B0(void) {
    R1C0C1Sub174 *st = D_807FBB40->unk174;
    f32 sparkX;
    f32 sparkY;
    f32 sparkZ;
    R1C0C1Ptr178 *p;
    s32 limit;
    R1C0C1Blob8 cutsceneModelIds;

    switch (D_807FBB40->state) {
        case 5:
            if (D_807506A4 != 0 && camIsCutsceneActive() == 0) {
                st->unk0++;
                if (st->unk0 >= 0x29) {
                    D_807506A4 = 0;
                    D_807FBB40->state = 1;
                }
            } else {
                st->unk0 = 0;
            }
            break;
        case 1:
            st->unk0 = 0;
            D_807FBB40->state = 2;
            break;
        case 2:
            if (D_807FC8D4 < 160000.0) {
                D_807FBB40->state = 3;
                st->unk0 = 0;
                sfxAllocateChannel(0x3B, 1.0f);
                sfxPlayOnFreeSlot(0x258, 0x7FFF, 63.0f, 1.0f, 5, 0);
                camStartPath(D_807FBB40, 0, 1);
                actorScriptStart(D_807FBB40, 0x291);
                D_807FBB40->unk155[0] = 0;
                ((R1C0C1Spawned *)D_807FBB40)->unk146 = 1;
            }
            break;
        case 3:
            if (D_807FBB40->unk155[0] == 1) {
                D_807FBB40->unk155[0]++;
            } else if (D_807FBB40->unk155[0] == 2) {
                sfxStopChannel(0x3B, 1);
                D_807FBB40->unk128 -= 8;
                if (D_807FBB40->unk128 <= 0) {
                    D_807FBB40->unk128 = 0;
                    st->unk0++;
                    if (st->unk0 == 1) {
                        sfxPlayOnFreeSlot(0x1F6, 0x7FFF, 63.0f, 1.0f, 5, 0);
                    }
                    if (st->unk0 >= 0xB) {
                        cutsceneModelIds = D_807506B8;
                        D_807FBB40->state = 4;
                        sfxAllocateChannel(0x7D, 1.0f);
                        actorScriptStart(st->unk4, D_80750684[st->unk2]);
                        st->unk0 = 0;
                        st->unk4->state = 3;
                        st->unk4->unk155[0] = 0;
                        camStartPath(0, 1, 1);
                        csModelStateSetFirstByte(cutsceneModelIds.b[st->unk2], 2);
                    }
                }
                if (D_807FBB40->unk128 < 0x80) {
                    D_807FBB40->y -= 6.0;
                }
            } else {
                func_80714950(0x10064);
                func_8071498C(func_8071AADC);
                func_807149C8(0xFF, 0xFF, 0xFF, 0xFF);
                sparkX = randomFloat() * 30.0 + D_807FBB40->x;
                sparkY = randomFloat() * 30.0 + (D_807FBB40->y + 20.0);
                sparkZ = randomFloat() * 30.0 + D_807FBB40->z;
                func_80714CC0(&D_80720A7C, 1.2f, sparkX, sparkY, sparkZ);
            }
            break;
        case 4:
            if (func_806BDD2C() != 0) {
                p = ((R1C0C1Act178 *)st->unk4)->unk178;
                p->unk0->y += 5.0;
                if (st->unk0 == 0x10E) {
                    flagSet(0x315, 1, 0);
                    func_80712524(D_80750664[14], D_80750664[15]);
                }
            }
            limit = 0xB4;
            if (st->unk2 == 2 || st->unk2 == 7) {
                if (func_806BDD2C() == 0) {
                    limit = 0x5A;
                }
            }
            st->unk0++;
            if (limit == st->unk0) {
                if (st->unk2 == 2 || st->unk2 == 7) {
                    flagSet(st->unk2 + 0x1BC, 1, 0);
                    if (func_806BDD2C() == 0) {
                        camResumePath();
                        sfxStopChannel(0x7D, 1);
                        D_807506A4 = 1;
                    }
                } else {
                    func_80712524(D_80750664[st->unk2 * 2], D_80750664[st->unk2 * 2 + 1]);
                }
            }
            break;
        case 0:
            break;
    }
    D_807FBB40->unk15E = 0x28;
    actorUpdateModelMatrix(D_807FBB40, 0);
}

s32 func_806BDD2C(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (flagGet(i + 0x1BC, 0) == 0) {
            return 0;
        }
    }
    return 1;
}

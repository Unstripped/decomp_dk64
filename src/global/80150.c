#include "common.h"
#include "actor.h"

typedef struct ActorMapFlag {
    u16 map;
    u8 unk2;
    s16 unk4;
} ActorMapFlag;

typedef struct TagBarrelState {
    /* 0x00 */ u8 pad0[0x6];
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    union {
        f32 unkC;
        struct {
            u8 unkC_b;
            u8 unkD;
        };
    };
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ s16 unk18;
} TagBarrelState;

typedef struct ActorD580 {
    /* 0x000 */ u8 pad0[0xCA];
    /* 0x0CA */ u8 unkCA;
} ActorD580;

typedef struct ActorAnimLookup {
    struct {
        s16 unk0;
        s16 unk2;
    } arr[5];
} ActorAnimLookup;

typedef struct ActorGroup5 {
    u8 pad0[8];
    Actor *unk8[5];
} ActorGroup5;

typedef struct ActorKongAction {
    u8 pad0[4];
    u8 unk4;
    u8 unk5;
} ActorKongAction;

extern Actor *D_807FBB40;
extern ActorGlobalState D_807FBB70;
extern ActorD580 *D_807FD580;
extern void *D_807FBB4C;
extern u16 *D_807FBB54;
extern s32 D_8076A0A8;
extern s32 D_8071FE08;
extern u8 D_8074E77C;
extern ActorMapFlag D_8074E7A0[];
extern s16 D_8074E7E0[];
extern ActorKongAction D_8074E814[];
extern ActorAnimLookup D_8074E834;
extern s32 D_8074E85C[];
extern u8 D_80720120;
extern u8 D_80720340;
extern u8 D_8072038C;

s32 func_805FF018(s32, s32);
void sfxPlayAtPositionPooled(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);
s32 randomNonNegative(void);
void actorScriptStart();
u16 camStartPath();
void actorUpdateModelMatrix(Actor *, s32);
s32 actorUpdateFloorContactAndTilt(Actor *, f32);
void actorGetNodePos(Actor *, s32, f32 *, f32 *, f32 *);
s32 actorDespawn(Actor *);
void func_8067B4C8(void);
void func_8067BA7C(s32);
s32 tagBarrelCheckProximityAndFall(s32, u8 *, u8 *, u8 *);
void func_8067C71C(void);
void tagBarrelDespawnEffects(void);
void func_8067DF44(f32, f32, f32, f32, u8, u8);
void tagBarrelResetMovement(void);
void tagBarrelTriggerRecoil(void);
void tagBarrelCheckRecoil(void);
void transformBarrelUpdate(void);
void tagBarrelActorUpdate(void);
void tagBarrelUpdate(void);
void animSetFrameAndSubframe(Actor *, s32, s16, f32);
void animSetLoopLimit(Actor *, s32, s32);
void animSetFinished(Actor *, s32, s32);
s32 actorListFindIdByActor(Actor *);
void func_8068A764(Actor *, u8);
void func_8069B908(void);
void slotQueueCancel(s32, s32);
s32 textTableGetString(s32, s32, s32);
void func_80714950();
void func_8071496C(s32);
void func_8071498C(void *);
void func_80714998(u32);
void func_807149B8(u32);
void func_807149FC(s32);
void func_80714CC0(void *, f32, f32, f32, f32);
void effectRadialSprayUpdate(void);
void func_8071B89C(void);
void func_8071BB14(void);
s32 flagGet(s16, s32);
void flagSet(s16, s32, s32);

s32 func_8067B450(void *actor) {
    s32 count = 4;
    s32 val = actorListFindIdByActor(actor);
    s32 i;

    for (i = 0; i < count; i++) {
        if (D_8076A0A8 == D_8074E7A0[i].map && val == D_8074E7A0[i].unk2) {
            return flagGet(D_8074E7A0[i].unk4, 0);
        }
    }
    return 0;
}


typedef struct ActorB4C8Sub4 {
    u8 pad0[0x1C];
    struct ActorB4C8Sub4Data *unk1C;
} ActorB4C8Sub4;

typedef struct ActorB4C8Sub4Data {
    u8 unk0;
    u8 unk1;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    u8 unk8;
} ActorB4C8Sub4Data;

typedef struct ActorB4C8Spawn {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    s32 unk14;
    s32 unk18;
} ActorB4C8Spawn;

typedef struct ActorB4C8State {
    Actor *unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    u8 unk14;
    u8 unk15;
} ActorB4C8State;

typedef struct ActorB4C8PeerState {
    u8 pad0[0xB0];
    f32 unkB0;
    f32 unkB4;
    f32 unkB8;
} ActorB4C8PeerState;

extern u8 D_8071FBC8;
void *heapAlloc(s32);
void scriptSetActorRampTarget(Actor *, f32, f32);
void controllerAnimSetState(Actor *, s16, f32, f32);
void actorAppendCallback(Actor *, s32, s32, u8, s32, void *);
void actorQueueDelayedCallback(Actor *, Actor *, s32, s32, s32, s32, s32);
void func_8067AAB8(s32, Actor *, s16, f32, s16);
void func_80714C08(void *, f32, void *, s32, s32);

void func_8067B4C8(void) {
    ActorB4C8State *sub = D_807FBB40->unk174;
    ActorB4C8PeerState *peer;
    s32 i;

    if (!(D_807FBB40->unk60 & 0x10)) {
        ((ActorB4C8Sub4 *)D_807FBB40->unk4)->unk1C = heapAlloc(0x10);
        ((ActorB4C8Sub4 *)D_807FBB40->unk4)->unk1C->unk0 = 0x7F;
        ((ActorB4C8Sub4 *)D_807FBB40->unk4)->unk1C->unk1 = 2;
        ((ActorB4C8Sub4 *)D_807FBB40->unk4)->unk1C->unk2 = (u32)((((ActorB4C8Spawn *)D_807FBB40->unk124)->unk0 * 65536.0f) / 360.0f);
        ((ActorB4C8Sub4 *)D_807FBB40->unk4)->unk1C->unk4 = 0;
        ((ActorB4C8Sub4 *)D_807FBB40->unk4)->unk1C->unk6 = 0;
        ((ActorB4C8Sub4 *)D_807FBB40->unk4)->unk1C->unk8 = 0;
        sub->unk4 = ((ActorB4C8Spawn *)D_807FBB40->unk124)->unk4;
        sub->unk8 = ((ActorB4C8Spawn *)D_807FBB40->unk124)->unk8;
        sub->unkC = ((ActorB4C8Spawn *)D_807FBB40->unk124)->unkC;
        sub->unk10 = ((ActorB4C8Spawn *)D_807FBB40->unk124)->unk10;
        sub->unk15 = ((ActorB4C8Spawn *)D_807FBB40->unk124)->unk14;
        if (1 == ((ActorB4C8Spawn *)D_807FBB40->unk124)->unk18) {
            if (func_8067B450(D_807FBB40) == 0) {
                D_807FBB40->unk154 = 0x14;
                D_807FBB40->unk144 = 1;
                D_807FBB40->unk60 &= ~0x8000;
                D_807FBB40->unk128 = 0;
            }
        }
        if (D_8076A0A8 == 0x22) {
            D_807FBB40->unk60 |= 0x400;
        }
        if (D_8076A0A8 == 0xC7) {
            D_807FBB40->unk12A = 0x226;
        }
    }
    if (D_807FBB70.unk200 == 4) {
        sub->unk0 = (Actor *)D_807FBB70.unk1FC;
        D_807FBB40->unk154 = 1;
        if (0) {} // FAKE: empty branch steers uopt web colouring (D_807FBB70 address takes v1 not v0)
        sub->unk14 = 0xA;
        D_807FBB40->unk144 = 1;
        sub->unk0->unkE6 = D_807FBB40->unkE6;
        camStartPath(0, sub->unk15, 1u); // FAKE: 1u keeps the constant out of the const-1 web (li a2,1)
    }
    switch (D_807FBB40->unk154) {
        case 1:
            if (--sub->unk14 == 6) {
                scriptSetActorRampTarget(D_807FBB40, 1.0f, 0);
                controllerAnimSetState(D_807FBB40, 0x346, 0, 0.0f); // FAKE: int 0 and 0.0f give separate li a2/li a3 (0.0f twice is one mtc1)
            }
            if (sub->unk14 == 0) {
                D_807FBB40->unk154 = 2;
            }
            break;
        case 2:
            actorAppendCallback(sub->unk0, (s32)D_807FBB40, 0x40, 1, 0, 0);
            peer = sub->unk0->unk174;
            peer->unkB0 = sub->unk8;
            peer->unkB4 = sub->unkC;
            peer->unkB8 = sub->unk10;
            func_8067AAB8((s32)D_807FBB40, sub->unk0, D_807FBB40->unkE6, 0.0f, sub->unk4);
            actorQueueDelayedCallback(D_807FBB40, D_807FBB40, 0x800, 2, 0, 0, 0xA);
            func_80714998(2);
            func_807149B8(1);
            func_80714C08(&D_8071FBC8, 2.0f, D_807FBB40, 1, 2);
            sfxPlayAtPositionPooled(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x17, 0xFF, 0x7F, 0x19, 0x1E, 0.3f, 0);
            D_807FBB40->unk154++;
            sub->unk14 = 4;
            break;
        case 3:
            if (sub->unk14-- == 0) {
                D_807FBB40->unk154 = 0;
            }
            break;
        case 0:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
            break;
        case 20:
            for (i = 0; i < D_807FBB70.unk254; i++) {
                if (D_807FBB70.unk258[i] == 1) {
                    D_807FBB40->unk144 = 2;
                    D_807FBB40->unk154 = 0x15;
                }
            }
            if (func_8067B450(D_807FBB40) != 0) {
                D_807FBB40->unk128 = 0xFF;
                D_807FBB40->unk60 |= 0x8000;
                D_807FBB40->unk154 = 0;
            }
            break;
        case 21:
            D_807FBB40->unk128 += 10;
            if (D_807FBB40->unk128 >= 0xF1) {
                D_807FBB40->unk60 |= 0x8000;
                D_807FBB40->unk154 = 0;
            }
            break;
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
    if (sub) {} // FAKE: extends sub across the final call so it takes a saved register
}

void func_8067BA3C(void) {
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk12A = 0x7D0;
    }
    func_8067B4C8();
}

void animSetSpeed(Actor *, s32, f32);
void animSetLoopMode(Actor *, s32, s32);
void animSetDirection(Actor *, s32, s32);
s32 sfxPlayFromActorWithAltitudeCheck(Actor *, s32, s32, s32, u8);
void actorListSpawnNodeEntryDefault(s16, f32, f32, f32, s16, f32, void *);
extern u8 D_807FBBA8;


void func_8067BA7C(s32 arg0) {
    if (!(D_807FBB40->unk60 & 0x10) && (arg0 == 0x13)) {
        animSetSpeed(D_807FBB40, 0, 0.5f);
        animSetLoopMode(D_807FBB40, 0, 0);
        animSetDirection(D_807FBB40, 0, 0);
        animSetLoopLimit(D_807FBB40, 0, -1);
    }
    switch (D_807FBB40->unk154) {
        case 0:
            break;
        case 10:
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x31, 0xFF, 0x7F, 1);
            func_807149B8(0);
            func_807149FC(1);
            func_80714CC0(&D_8071FE08, 0.5f, D_807FBB40->unk7C, D_807FBB40->unk80 + 7.0f, D_807FBB40->unk84);
            actorListSpawnNodeEntryDefault(arg0, D_807FBB40->unk7C, D_807FBB40->unk80 + 8.3, D_807FBB40->unk84, 0, 1.0f, D_807FBB40);
            D_807FBB40->unk154++;
            break;
        case 11:
            if (D_807FBBA8 != 0) {
                D_807FBB40->unk154 = 0x14;
            }
            break;
        case 20:
            if (arg0 == 0x95) {
                D_807FBB40->unk168 = 0x1E;
                D_807FBB40->unk154 = 0x15;
            }
            break;
        case 21:
            if (D_807FBB40->unk168 != 0) {
                D_807FBB40->unk168--;
            } else {
                D_807FBB40->unk154 = 0xA;
            }
            break;
    }
    if (arg0 == 0x13) {
        actorUpdateModelMatrix(D_807FBB40, 0);
    }
}

void func_8067BC68(void) {
    func_8067BA7C(0x13);
}

void func_8067BC88(void) {
    func_8067BA7C(0x13);
}

void func_8067BCA8(void) {
    func_8067BA7C(0x13);
}

void func_8067BCC8(void) {
    func_8067BA7C(0x13);
}

void func_8067BCE8(void) {
    func_8067BA7C(0x13);
}

void func_8067BD08(void) {
    func_8067BA7C(0x13);
}


void func_8067BD28(void) {
    char *extra;
    s32 var_v1 = 0;

    extra = (char *) ((Actor *) D_807FBB4C)->unk174;
    if ((D_807FBBA8 != 0) && (*(s32 *) (extra + 0x1F0) & 0x200000)) {
        var_v1 = 1;
    }
    if (!(D_807FBB40->unk60 & 0x10) || var_v1) {
        actorListSpawnNodeEntryDefault(0x55, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0, 1.0f, D_807FBB40);
    }
}

void func_8067BDB8(void) {
    func_8067BA7C(0x95);
    actorUpdateFloorContactAndTilt(D_807FBB40, 0.0f);
    D_807FBB40->unk80 = D_807FBB40->unkA4;
}

void func_8067BDF8(void) {
    u8 sp1F;
    u8 *ptr;

    sp1F = 0;
    ptr = D_807FBB40->unk174;
    tagBarrelCheckProximityAndFall(0x13, ptr, ptr + 1, &sp1F);
}

void func_8067BE30(void) {
    u8 *t0 = D_807FBB40->unk174;
    s16 i;

    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk12A = 0x7D0;
        *(s16 *)t0 = 0x1A;
    }
    for (i = 0; i < D_807FBB70.unk254; i++) {
        switch (D_807FBB70.unk258[i]) {
        case 1:
            *(s16 *)t0 = 0x60;
            break;
        case 2:
            *(s16 *)t0 = 0;
            break;
        case 3:
            *(s16 *)t0 = 0x1A;
            break;
        }
    }
    if (*(s16 *)t0 != 0) {
        if (tagBarrelCheckProximityAndFall(*(s16 *)t0, t0 + 2, t0 + 3, t0 + 4)) {
            *(s16 *)t0 = 0x1A;
        }
    } else {
        if (D_807FBB70.unk38 != 0) {
            t0[4] = 1;
        }
        actorUpdateModelMatrix(D_807FBB40, 0);
    }
}

void func_8067BF4C(void) {
    u8 *ptr = D_807FBB40->unk174;
    tagBarrelCheckProximityAndFall(0x1A, ptr + 2, ptr + 3, ptr + 4);
}

extern u8 D_807FC928;
extern struct PlayerData *D_807FC924;
void actorApplyVelocity(Actor *);
s32 actorHasActiveMovementFlags(Actor *);
typedef struct TagBarrelPlayerEntry {
    u8 unk0;
    u8 pad1[3];
    Actor *player;
    u8 pad8[0x2F0 - 8];
} TagBarrelPlayerEntry;
#define TAG_BARREL_PLAYER_TABLE ((TagBarrelPlayerEntry *)D_807FC924)

s32 tagBarrelCheckProximityAndFall(s32 arg0, u8 *arg1, u8 *arg2, u8 *arg3) {
    volatile u8 sp47; // FAKE: force stack home
    s32 pad[2];
    u8 var_a0;
    f32 var_fs0;
    f32 temp_f0;
    f32 temp_f1;
    sp47 = 0;
    var_fs0 = 99999.0f;
    if (D_807FBB40->unk60 & 0x10) {
        animSetSpeed(D_807FBB40, 0, 0.5f);
        animSetLoopMode(D_807FBB40, 0, 0);
        animSetDirection(D_807FBB40, 0, 0);
        animSetLoopLimit(D_807FBB40, 0, -1);
        if (D_807FBBA8 != 0 || *arg1 != 0 || *arg3 != 0) {
            *arg3 = 0;
            sp47 = 1;
        }
        if (sp47 != 0) {
            var_a0 = 0;
            if ((s32)D_807FC928 > 0) {
                do {
                    if (TAG_BARREL_PLAYER_TABLE[var_a0].unk0 != 0) {
                        Actor *player = TAG_BARREL_PLAYER_TABLE[var_a0].player;
                        temp_f0 = player->unk84 - D_807FBB40->unk84;
                        temp_f1 = player->unk7C - D_807FBB40->unk7C;
                        temp_f0 = sqrtf((temp_f0 * temp_f0) + (temp_f1 * temp_f1));
                        if (temp_f0 < var_fs0) {
                            var_fs0 = temp_f0;
                        }
                    }
                    var_a0++;
                } while (var_a0 < D_807FC928);
            }
            if ((f64)var_fs0 > 12.0) {
                *arg1 = 0;
            } else {
                *arg1 = 1;
                sp47 = 0;
            }
        }
    } else {
        sp47 = 1;
        *arg1 = 0;
        D_807FBB40->unkC0 = -10.0f;
        actorApplyVelocity(D_807FBB40);
        actorUpdateFloorContactAndTilt(D_807FBB40, 0.0f);
        if (actorHasActiveMovementFlags(D_807FBB40) != 0) {
            *arg2 = 1;
        } else {
            *arg2 = 0;
        }
    }
    if (sp47 != 0) {
        actorListSpawnNodeEntryDefault(arg0, D_807FBB40->unk7C, (f32)((f64)D_807FBB40->unk80 + 8.3), D_807FBB40->unk84, 0, 1.0f, D_807FBB40);
        if (D_807FBB40->unk60 & 0x10) {
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x31, 0xFF, 0x7F, 1);
            func_807149B8(0);
            func_807149FC(1);
            func_80714CC0(&D_8071FE08, 0.5f, D_807FBB40->unk7C, D_807FBB40->unk80 + 7.0f, D_807FBB40->unk84);
        }
    }
    if (*arg2 != 0) {
        D_807FBB40->unkC0 = -10.0f;
        actorApplyVelocity(D_807FBB40);
        actorUpdateFloorContactAndTilt(D_807FBB40, 0.0f);
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
    return sp47;
}

typedef struct ActorC2B8State {
    u8 unk0;
    u8 pad1[3];
    f32 unk4;
    u8 unk8;
} ActorC2B8State;

typedef struct ActorC2B8 {
    /* 0x000 */ u8 unk00[0x60];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u8 unk64[4];
    /* 0x068 */ u16 unk68;
    /* 0x06A */ u8 unk6A[0x16];
    /* 0x080 */ f32 unk80;
    /* 0x084 */ u8 unk84[0x20];
    /* 0x0A4 */ f32 unkA4;
    /* 0x0A8 */ u8 unkA8[0x10];
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ u8 unkBC[0x32];
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ u8 unkF0[0xA];
    /* 0x0FA */ s16 unkFA;
    /* 0x0FC */ u8 unkFC[0x48];
    /* 0x144 */ u8 unk144;
    /* 0x145 */ u8 unk145[0x2F];
    /* 0x174 */ void *unk174;
} ActorC2B8;

typedef struct ActorC2B8GlobalState {
    /* 0x000 */ u8 unk0[0x90];
    /* 0x090 */ u8 unk90;
    /* 0x091 */ u8 unk91;
    /* 0x092 */ s16 unk92;
    /* 0x094 */ s16 unk94;
} ActorC2B8GlobalState;

#define ACTOR_C2B8 ((ActorC2B8 *)D_807FBB40)
#define STATE_C2B8 ((ActorC2B8GlobalState *)&D_807FBB70)

void sfxPlayActorSound(Actor *, s32, s32, s32, s32, s32, f32, s32);
void sfxStopSlotSound(Actor *, s32);
void actorStepPhysics(Actor *, s16, s16);

void func_8067C2B8(void) {
    ActorC2B8State *temp_v0;
    f32 temp_fv1;
    f32 temp_fv0;
    s16 temp_a1;

    temp_v0 = (ActorC2B8State *) ACTOR_C2B8->unk174;
    if (!(ACTOR_C2B8->unk60 & 0x10)) {
        ACTOR_C2B8->unk68 |= 4;
        ACTOR_C2B8->unk60 |= 0x80;
        temp_v0->unk0 = 0;
        temp_v0->unk8 = 0;
        temp_v0->unk4 = 0.0f;
    }
    if (!(ACTOR_C2B8->unk68 & 4)) {
        ACTOR_C2B8->unkB8 = 0.0f;
    }
    if (STATE_C2B8->unk90 != 0) {
        temp_v0->unk8 = 1;
    }
    if (STATE_C2B8->unk91 != 0) {
        if (temp_v0->unk0 == 0) {
            sfxPlayActorSound(D_807FBB40, 0x10C, 0, 1, 0, 0xFF, 1.0f, 0);
            temp_v0->unk0 = 1;
        }
        temp_v0->unk4 = (f64) STATE_C2B8->unk94 / 1.1;
        ACTOR_C2B8->unkEE = STATE_C2B8->unk92;
        temp_fv1 = ACTOR_C2B8->unkB8;
        if (temp_fv1 < temp_v0->unk4) {
            ACTOR_C2B8->unkB8 = temp_fv1 + 0.8;
            temp_fv0 = temp_v0->unk4;
            if (temp_fv0 < ACTOR_C2B8->unkB8) {
                ACTOR_C2B8->unkB8 = temp_fv0;
            }
        } else {
            ACTOR_C2B8->unkB8 = temp_fv1 - 1.5;
            if (ACTOR_C2B8->unkB8 < 0.0f) {
                ACTOR_C2B8->unkB8 = 0.0f;
            }
        }
        ACTOR_C2B8->unkFA = 0x64;
        temp_a1 = ACTOR_C2B8->unkEE;
        actorStepPhysics(D_807FBB40, temp_a1, temp_a1);
        actorApplyVelocity(D_807FBB40);
        actorUpdateFloorContactAndTilt(D_807FBB40, 0.0f);
        ACTOR_C2B8->unk80 = ACTOR_C2B8->unkA4;
        if (temp_v0->unk8 == 0) {
            ACTOR_C2B8->unk144 = 0x3C;
        }
    } else {
        if ((temp_v0->unk0 != 0) && ((f64) ACTOR_C2B8->unkB8 == 0.0)) {
            temp_v0->unk0 = 0;
            sfxStopSlotSound(D_807FBB40, 0);
        }
        temp_v0->unk4 = 0.0f;
        temp_fv1 = ACTOR_C2B8->unkB8;
        if (temp_fv1 < 0.0f) {
            ACTOR_C2B8->unkB8 = temp_fv1 + 0.8;
            temp_fv0 = temp_v0->unk4;
            if (temp_fv0 < ACTOR_C2B8->unkB8) {
                ACTOR_C2B8->unkB8 = temp_fv0;
            }
        } else {
            ACTOR_C2B8->unkB8 = temp_fv1 - 1.5;
            if (ACTOR_C2B8->unkB8 < 0.0f) {
                ACTOR_C2B8->unkB8 = 0.0f;
            }
        }
        ACTOR_C2B8->unkFA = 0x64;
        temp_a1 = ACTOR_C2B8->unkEE;
        actorStepPhysics(D_807FBB40, temp_a1, temp_a1);
        actorApplyVelocity(D_807FBB40);
        actorUpdateFloorContactAndTilt(D_807FBB40, 0.0f);
        if (temp_v0->unk8 == 0) {
            if (((f64) ACTOR_C2B8->unkB8 == 0.0) || !(ACTOR_C2B8->unk60 & 0x10)) {
                ACTOR_C2B8->unk144 = 2;
            } else {
                ACTOR_C2B8->unk144 = 0x3C;
            }
        }
        ACTOR_C2B8->unk80 = ACTOR_C2B8->unkA4;
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

void func_8067C67C(void) {
    func_8067C71C();
}

void func_8067C69C(void) {
    func_8067C71C();
}

void func_8067C6BC(void) {
    func_8067C71C();
}

void func_8067C6DC(void) {
    func_8069B908();
}

void func_8067C6FC(void) {
    func_8067C71C();
}

extern Actor *D_807FBB44;
typedef f32 ActorC71CMtxF[4][4];

typedef struct ActorC71CState {
    /* 0x00 */ struct Actor *unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 unk19;
    /* 0x1A */ u16 unk1A;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ u8 unk30;
    /* 0x31 */ u8 pad31[3];
    /* 0x34 */ f32 unk34;
    /* 0x38 */ u8 unk38;
    /* 0x39 */ u8 unk39;
    /* 0x3A */ u8 unk3A;
} ActorC71CState;

typedef struct ActorC71CSub118 {
    u8 pad0[0xC];
    u8 unkC;
    u8 padD;
    s16 unkE;
    s16 unk10;
} ActorC71CSub118;

typedef struct ActorC71C {
    /* 0x000 */ u8 pad0[0x4];
    /* 0x004 */ ActorSub4 *unk4;
    /* 0x008 */ u8 pad8[0x50];
    /* 0x058 */ s32 unk58;
    /* 0x05C */ u16 unk5C;
    /* 0x05E */ u8 unk5E[2];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u8 pad64[4];
    /* 0x068 */ u16 unk68;
    /* 0x06A */ u16 unk6A;
    /* 0x06C */ u16 unk6C;
    /* 0x06E */ u8 pad6E[0xE];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ f32 unk88;
    /* 0x08C */ f32 unk8C;
    /* 0x090 */ f32 unk90;
    /* 0x094 */ u8 pad94[8];
    /* 0x09C */ f32 unk9C;
    /* 0x0A0 */ f32 unkA0;
    /* 0x0A4 */ f32 unkA4;
    /* 0x0A8 */ u8 padA8[4];
    /* 0x0AC */ f32 unkAC;
    /* 0x0B0 */ u8 padB0[4];
    /* 0x0B4 */ f32 unkB4;
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ f32 unkBC;
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ u8 padC4[0x18];
    /* 0x0DC */ s16 unkDC;
    /* 0x0DE */ s16 unkDE;
    /* 0x0E0 */ u8 padE0[6];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 padE8[6];
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ u8 padF0[2];
    /* 0x0F2 */ s16 unkF2;
    /* 0x0F4 */ s16 unkF4;
    /* 0x0F6 */ s16 unkF6;
    /* 0x0F8 */ u8 padF8[2];
    /* 0x0FA */ s16 unkFA;
    /* 0x0FC */ u8 unkFC;
    /* 0x0FD */ u8 padFD[0x13];
    /* 0x110 */ u8 unk110;
    /* 0x111 */ u8 pad111[7];
    /* 0x118 */ ActorC71CSub118 *unk118;
    /* 0x11C */ s32 unk11C;
    /* 0x120 */ u8 pad120[8];
    /* 0x128 */ s16 unk128;
    /* 0x12A */ s16 unk12A;
    /* 0x12C */ u8 pad12C[0x18];
    /* 0x144 */ u8 unk144;
    /* 0x145 */ u8 pad145[0xF];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 pad155[0x1F];
    /* 0x174 */ ActorC71CState *unk174;
} ActorC71C;

typedef struct ActorC71CGlobalState {
    /* 0x000 */ u8 pad0[0x15];
    /* 0x015 */ u8 unk15;
    /* 0x016 */ u8 pad16[0xE];
    /* 0x024 */ u8 unk24;
    /* 0x025 */ u8 unk25;
    /* 0x026 */ u8 pad26[2];
    /* 0x028 */ Actor *unk28;
    /* 0x02C */ u8 unk2C;
    /* 0x02D */ u8 pad2D[3];
    /* 0x030 */ f32 unk30;
    /* 0x034 */ s16 unk34;
    /* 0x036 */ s16 unk36;
    /* 0x038 */ u8 pad38[0x1C8];
    /* 0x200 */ u8 unk200;
} ActorC71CGlobalState;

#define ACTOR_C71C ((ActorC71C *)D_807FBB40)
#define STATE_C71C ((ActorC71CGlobalState *)&D_807FBB70)
#define ACTOR44_C71C ((ActorC71C *)D_807FBB44)
#define ACTOR4C_C71C ((ActorC71C *)D_807FBB4C)

extern s32 D_807FBB64;
extern u8 D_807FBBA9;
extern f32 D_807FBC60;
extern f32 D_807FBC64;
extern s16 D_807FD584;
extern u32 D_8076A064;
extern s8 D_80029FA0;
extern u8 D_8071FC40;
extern u8 D_8072030C;
extern s16 D_807502D0;
extern f32 D_807502E4;
extern s16 D_80753444[];

u32 randomLcgNext(void);
f32 sinApprox(f32);
s32 camIsCutsceneActive(void);
void camStartShakeFromPoint(s32, s32, s32, f32, f32, f32, f32, f32);
void lightAdd(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32);
void func_8065D254(Actor *, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32);
void func_8066E6C8(Actor *, s32, s32);
void actorSetNodeFlag(Actor *, s32);
void actorClearNodeFlag(Actor *, s32);
s32 actorAngleInArc(Actor *, s16);
void mathAngleClampToArc(s16, s16, s16, s16, s16 *);
s32 actorSpawn(s32, s32);
void actorCallbackMaskEnable(Actor *, s32);
void actorCallbackMaskDisable(Actor *, s32);
void actorCollisionEventsCancel(Actor *, s32);
void func_8067ACB4(Actor *);
void actorCopyPoseAndScale(Actor *, Actor *, f32);
void func_8067E278();
void func_806CF4B8(Actor *);
void func_807149A8(s32);
void effectWobbleRiseUpdate(void);
void pathFollowUpdateHeading(Actor *, s32);
void animationOwnerFreeBuffer(Actor *);

void func_8067C71C(void) {
    ActorC71CState *temp_s1;
    ActorC71CMtxF spB4;
    ActorC71CMtxF sp74;
    f32 var_fv0;
    f32 var_fv0_2;
    s16 temp_a0;
    u8 *tp;

    temp_s1 = ACTOR_C71C->unk174;
    if (!(ACTOR_C71C->unk60 & 0x10)) {
        ACTOR_C71C->unkFA = 0x270F;
        temp_s1->unk38 = 0;
        temp_s1->unk39 = 0;
        if (ACTOR_C71C->unk58 == 0x1A) {
            ACTOR_C71C->unk60 |= 0x1000;
            func_807149B8(1);
            func_807149FC(-1);
            func_807149A8((s16)((f64)ACTOR_C71C->unk12A * 0.75));
            func_80714C08(&D_8072030C, 0.14f, D_807FBB40, 1, 2);
            actorClearNodeFlag(D_807FBB40, 3);
        }
        ACTOR_C71C->unkA4 = 99999.0f;
        actorUpdateFloorContactAndTilt(D_807FBB40, 0.0f);
        if (actorHasActiveMovementFlags(D_807FBB40)) {
            ACTOR_C71C->unk154 = 2;
            ACTOR_C71C->unk68 |= 1;
            temp_s1->unkC = 0x1E;
            ACTOR_C71C->unk144 = 2;
            temp_s1->unk8 = 360.0f;
            temp_s1->unk14 = 0.0f;
        }
        ACTOR_C71C->unk68 |= 0x40;
    }

    if (STATE_C71C->unk24 != 0) {
        if (temp_s1->unk39 == 0) {
            temp_s1->unk0 = (Actor *)STATE_C71C->unk28;
            ACTOR_C71C->unk154 = 1;
            temp_s1->unk8 = 360.0f;
            actorCallbackMaskDisable(D_807FBB40, 0x8000);
            actorCollisionEventsCancel(temp_s1->unk0, 1);
            ACTOR_C71C->unk144 = 0x2C;
            animationOwnerFreeBuffer(D_807FBB40);
        } else {
            func_806CF4B8(D_807FBB40);
        }
    }

    if (STATE_C71C->unk25 != 0) {
        ACTOR_C71C->unk154 = 2;
        temp_s1->unkC = 0x1E;
        ACTOR_C71C->unk144 = 0x3C;
        actorCallbackMaskEnable(D_807FBB40, 0x8000);
    }

    if (((STATE_C71C->unk15 != 0) || (STATE_C71C->unk200 == 9)) && (temp_s1->unk39 == 0)) {
        ACTOR_C71C->unk154 = 4;
        func_806CF4B8(D_807FBB40);
    }

    if (temp_s1->unk39 != 0 && (STATE_C71C->unk15 != 0 || STATE_C71C->unk200 == 9)) {
        ACTOR_C71C->unk144 = 1;
    }

    if (STATE_C71C->unk2C != 0) {
        ACTOR_C71C->unk154 = 3;
        ACTOR_C71C->unk144 = 0x3C;
        actorCallbackMaskEnable(D_807FBB40, 0x8000);
        ACTOR_C71C->unkE6 = STATE_C71C->unk36;
        ACTOR_C71C->unkEE = STATE_C71C->unk36;
        ACTOR_C71C->unkC0 = STATE_C71C->unk30;
        temp_s1->unk4 = D_8076A064;
        temp_s1->unk18 = 0;
        temp_s1->unk1A = 0;
        ACTOR_C71C->unkB8 = STATE_C71C->unk34;
        actorCollisionEventsCancel(temp_s1->unk0, 1);
    }

    func_8067ACB4(D_807FBB40);
    switch (ACTOR_C71C->unk154) {
    case 0:
        ACTOR_C71C->unk144 = 2;
        temp_s1->unk8 = 360.0f;
        temp_s1->unk14 = 0.0f;
        func_8066E6C8(D_807FBB40, 0, 1);
        func_8066E6C8(D_807FBB40, 1, 0);
        ACTOR_C71C->unk68 |= 1;
        break;
    case 1:
        func_8066E6C8(D_807FBB40, 0, 0);
        func_8066E6C8(D_807FBB40, 1, 0);
        tp = (u8 *)temp_s1->unk0->unk174;
        temp_s1->unk8 = *(f32 *)(tp + 0x1BC);
        if (temp_s1->unk8 < 0.0) {
            temp_s1->unk8 += 360.0;
        }
        temp_s1->unk10 = ((f64)temp_s1->unk0->unkE6 / 4095.0) * 360.0;
        ACTOR_C71C->unk68 &= ~1;
        break;
    case 2:
        func_8066E6C8(D_807FBB40, 0, 1);
        func_8066E6C8(D_807FBB40, 1, 0);
        if (--temp_s1->unkC == 0) {
            ACTOR_C71C->unk154 = 0;
        } else if (actorHasActiveMovementFlags(D_807FBB40)) {
            temp_s1->unkC = 0x1E;
        }
        temp_s1->unk8 += 16.0;
        if (temp_s1->unk8 > 360.0) {
            temp_s1->unk8 = 360.0f;
        }
        ACTOR_C71C->unkC0 = -200.0f;
        ACTOR_C71C->unkB8 = 0.0f;
        ACTOR_C71C->unk68 |= 1;
        break;
    case 3:
        func_8066E6C8(D_807FBB40, 0, 1);
        func_8066E6C8(D_807FBB40, 1, 1);
        ACTOR_C71C->unkC0 += D_807502E4;
        if (ACTOR_C71C->unkC0 < (f32)D_807502D0) {
            ACTOR_C71C->unkC0 = (f32)D_807502D0;
        }
        temp_s1->unk14 -= 10.0f;
        if (ACTOR_C71C->unkFC != 0 && actorAngleInArc(D_807FBB40, ACTOR_C71C->unkE6) == 0) {
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x23, 0xFF, 0x7F, 1);
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x17, 0xFF, 0x7F, 1);
            ACTOR_C71C->unk154 = 8;
        }
        ACTOR_C71C->unk68 &= ~1;
        break;
    case 4:
        temp_s1->unk39 = 1;
        ACTOR_C71C->unk154 = 8;
        break;
    case 5:
        func_8066E6C8(D_807FBB40, 0, 1);
        func_8066E6C8(D_807FBB40, 1, 1);
        temp_s1->unk28 -= 3.0;
        if (temp_s1->unk28 < 270.0) {
            temp_s1->unk28 = 270.0f;
        }
        var_fv0 = sinApprox((f32)temp_s1->unk20 / 12.6);
        ACTOR_C71C->unk80 = temp_s1->unk1C + (f32)(var_fv0 * 1.5);
        var_fv0 = sinApprox((f32)temp_s1->unk20 / 9.34);
        temp_s1->unk8 = temp_s1->unk28 + var_fv0 * 7.0f;
        temp_s1->unk20++;
        var_fv0 = (f32) (-5.0 - temp_s1->unk24);
        var_fv0 = (f32) (var_fv0 / -5.0);
        var_fv0 = (f32) (var_fv0 * -0.5);
        if (D_807FBBA9 == 0) {
            var_fv0 = (f32) (-0.5 - var_fv0);
            var_fv0 = (f32) (0.0 - var_fv0);
        }
        temp_s1->unk24 += var_fv0;
        ACTOR_C71C->unk80 += temp_s1->unk24;
        if (--temp_s1->unk2C == 0 || temp_s1->unk2C == 5 || temp_s1->unk2C == 10 ||
            temp_s1->unk2C == 15 || temp_s1->unk2C == 20 || temp_s1->unk2C == 26) {
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x55, 0xFF, (s16)(0xA7 - temp_s1->unk2C * 2), 0);
        }
        if (temp_s1->unk2C == 0 || ACTOR_C71C->unkAC < ACTOR_C71C->unkA4) {
            ACTOR_C71C->unk154 = 6;
            if (sinApprox((f32)temp_s1->unk20 / 9.34) > 0.0) {
                temp_s1->unk30 = 1;
            } else {
                temp_s1->unk30 = 0;
            }
            temp_s1->unk34 = 0.1f;
        }
        ACTOR_C71C->unkC0 = 0.0f;
        ACTOR_C71C->unkB8 = 35.0f;
        ACTOR_C71C->unk68 |= 1;
        pathFollowUpdateHeading(D_807FBB40, 0);
        if (ACTOR_C71C->unk118->unkC == 0) {
            ACTOR_C71C->unkEE = ACTOR_C71C->unk118->unkE;
            ACTOR_C71C->unkB8 = (f32)ACTOR_C71C->unk118->unk10;
        } else {
            ACTOR_C71C->unkB8 = 0.0f;
        }
        if (ACTOR_C71C->unkFC != 0) {
            temp_a0 = ACTOR_C71C->unkEE;
            mathAngleClampToArc(temp_a0, temp_a0, ACTOR_C71C->unkF4, ACTOR_C71C->unkF6, (s16 *)&ACTOR_C71C->unkF2);
            ACTOR_C71C->unkEE = ACTOR_C71C->unkF2;
        }
        break;
    case 6:
        if (((randomLcgNext() / 100000) % 3) == 0) {
            func_807149B8(1);
            func_807149FC(-1);
            func_8071498C(effectWobbleRiseUpdate);
            func_80714CC0(&D_8071FC40, 0.0f, ACTOR_C71C->unk7C, ACTOR_C71C->unk80, ACTOR_C71C->unk84);
        }
        if (temp_s1->unk30 != 0) {
            if (temp_s1->unk30 == 1) {
                temp_s1->unk8 += 1.5;
                if (temp_s1->unk8 > 360.0) {
                    temp_s1->unk8 = 360.0f;
                }
            }
        } else {
            temp_s1->unk8 -= 1.5;
            if (temp_s1->unk8 < 0.0) {
                temp_s1->unk8 = 0.0f;
            }
        }
        temp_s1->unk2C++;
        if ((temp_s1->unk2C & 3) == 0 && (u32)temp_s1->unk2C < 29) {
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x55, (0xC0 - temp_s1->unk2C * 6) & 0xFF, (s16)(temp_s1->unk2C * 2 + 0x50), 0);
        }
        temp_s1->unk34 += 2.0;
        if (temp_s1->unk34 > 40.0) {
            temp_s1->unk34 = 40.0f;
        }
        ACTOR_C71C->unkC0 = -temp_s1->unk34;
        ACTOR_C71C->unkB8 = 0.0f;
        if ((f64)ACTOR_C71C->unkB4 < 0.5) {
            ACTOR_C71C->unk154 = 7;
            temp_s1->unk2C = 0x78;
        }
        ACTOR_C71C->unk68 &= ~1;
        break;
    case 7:
        ACTOR_C71C->unk80 -= 0.15;
        if (--temp_s1->unk2C == 0) {
            ACTOR_C71C->unk154 = 4;
        }
        ACTOR_C71C->unk68 &= ~1;
        break;
    case 8:
        if ((D_807FBB64 & 1) && camIsCutsceneActive()) {
            actorDespawn(D_807FBB40);
        } else {
            switch (ACTOR_C71C->unk58) {
            case 0x1A:
                func_8067E278(1, 1);
                ACTOR_C71C->unk60 &= ~0x8000;
                ACTOR_C71C->unk128 = 0;
                ACTOR_C71C->unk154 = 9;
                temp_s1->unk3A = 0x14;
                if (!(D_807FBB64 & 1)) {
                    actorSetNodeFlag(D_807FBB40, 3);
                }
                actorClearNodeFlag(D_807FBB40, 1);
                actorClearNodeFlag(D_807FBB40, 2);
                break;
            case 0x95:
                actorSpawn(0xDE, 0xE5);
                actorCopyPoseAndScale(D_807FBB44, D_807FBB40, 0.15f);
                ACTOR44_C71C->unk11C = ACTOR_C71C->unk11C;
                ACTOR_C71C->unk11C = 0;
                ACTOR44_C71C->unk80 = ACTOR_C71C->unkA4;
                goto block_despawn;
            case 0x85:
                D_80029FA0--;
            default:
            block_despawn:
                tagBarrelDespawnEffects();
                actorDespawn(D_807FBB40);
                break;
            }
        }
        break;
    case 9:
        if (temp_s1->unk3A == 0) {
            actorDespawn(D_807FBB40);
        } else {
            temp_s1->unk3A--;
        }
        var_fv0_2 = ((f32)temp_s1->unk3A / 20.0f) * 200.0;
        if (var_fv0_2 > 130.0) {
            var_fv0_2 = 200.0f;
        }
        lightAdd(ACTOR_C71C->unk7C, ACTOR_C71C->unk80, ACTOR_C71C->unk84, 0.0f, 0.0f, 0.0f, var_fv0_2, 0, 0xFF, 0xFF, 0xFF);
        camStartShakeFromPoint(*(s32 *)((u8 *)ACTOR4C_C71C->unk174 + 0x104), 5, 10, ACTOR_C71C->unk7C, ACTOR_C71C->unk80, ACTOR_C71C->unk84, 200.0f, 400.0f);
        break;
    }

    if (ACTOR_C71C->unk154 == 2 || ACTOR_C71C->unk154 == 3 || ACTOR_C71C->unk154 == 5 || ACTOR_C71C->unk154 == 6) {
        if (ACTOR_C71C->unk154 != 5) {
            ACTOR_C71C->unkEE = ACTOR_C71C->unkE6;
        }
        actorApplyVelocity(D_807FBB40);
        actorUpdateFloorContactAndTilt(D_807FBB40, 7.0f);
        if (ACTOR_C71C->unk154 == 2 && temp_s1->unk8 == 360.0f && (ACTOR_C71C->unk80 - ACTOR_C71C->unk8C) < -2.0f && (D_807FBB64 & 1)) {
            func_806CF4B8(D_807FBB40);
            ACTOR_C71C->unk154 = 4;
            temp_s1->unk39 = 1;
        }
        if (ACTOR_C71C->unk154 == 3 && ACTOR_C71C->unk58 == 0x1A && (u32)D_80753444[D_807FD584] < (u32)(D_8076A064 - temp_s1->unk4)) {
            ACTOR_C71C->unk154 = 4;
        }
        if (ACTOR_C71C->unk154 == 3 && (ACTOR_C71C->unk6A & 1) && !(ACTOR_C71C->unk6C & 1)) {
            ACTOR_C71C->unkC0 = 140.0f;
            temp_s1->unk1A++;
            if ((ACTOR_C71C->unk58 == 0x1A && temp_s1->unk1A == 4) || (ACTOR_C71C->unk58 == 0x95 && temp_s1->unk1A == 2)) {
                ACTOR_C71C->unk154 = 4;
            }
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x32, 0xFF, 0x7F, 1);
        }
        if (ACTOR_C71C->unk154 == 2 && (ACTOR_C71C->unk6A & 4)) {
            ACTOR_C71C->unk154 = 5;
            ACTOR_C71C->unk80 = ACTOR_C71C->unkAC;
            temp_s1->unk2C = 1000;
            temp_s1->unk1C = ACTOR_C71C->unk80 - 1.5;
            temp_s1->unk20 = 0;
            temp_s1->unk28 = temp_s1->unk8;
        }
        if (ACTOR_C71C->unk154 == 5) {
            temp_s1->unk1C = ACTOR_C71C->unkAC;
        }
        if (ACTOR_C71C->unk154 == 3 && (ACTOR_C71C->unk6A & 4) && temp_s1->unk19 == 0) {
            switch (temp_s1->unk18) {
            case 0:
                ACTOR_C71C->unkC0 = 180.0f;
                break;
            case 1:
                ACTOR_C71C->unkC0 = 140.0f;
                break;
            case 2:
                ACTOR_C71C->unkC0 = 100.0f;
                break;
            default:
                ACTOR_C71C->unk154 = 5;
                ACTOR_C71C->unk80 = ACTOR_C71C->unkAC;
                temp_s1->unk2C = 1000;
                temp_s1->unk1C = ACTOR_C71C->unk80 - 1.5;
                temp_s1->unk20 = 0;
                temp_s1->unk28 = temp_s1->unk8;
                break;
            }
            temp_s1->unk18++;
            temp_s1->unk19 = 3;
            ACTOR_C71C->unkB8 -= 20.0;
        } else if (temp_s1->unk19 != 0) {
            temp_s1->unk19--;
        }
        ACTOR_C71C->unkDC = 0x3FF;
        ACTOR_C71C->unkDE = 0x3FF;
    } else {
        ACTOR_C71C->unk110 = 0;
        ACTOR_C71C->unk6A &= ~0x408;
    }

    temp_s1->unk38 = ACTOR_C71C->unk154;
    if (ACTOR_C71C->unk154 != 9) {
        func_8065D254(D_807FBB40, 0x3C8, 0x40, 0x40, 0xC, 0xC, 1, 0x64, 0x78, 0, 1.0f);
    }
    guScaleF(spB4, ACTOR_C71C->unk4->unk34, ACTOR_C71C->unk4->unk38, ACTOR_C71C->unk4->unk3C);
    guRotateF(sp74, temp_s1->unk14, 0.0f, 1.0f, 0.0f);
    guMtxCatF(spB4, sp74, spB4);
    guRotateF(sp74, ((f64)ACTOR_C71C->unkE6 / 4095.0) * 360.0, 0.0f, 1.0f, 0.0f);
    guMtxCatF(spB4, sp74, spB4);
    guRotateF(sp74, temp_s1->unk8 - D_807FBC60, 1.0f, 0.0f, 0.0f);
    guMtxCatF(spB4, sp74, spB4);
    guRotateF(sp74, (temp_s1->unk10 + 90.0f) - D_807FBC64, 0.0f, 1.0f, 0.0f);
    guMtxCatF(spB4, sp74, spB4);

    if (ACTOR_C71C->unk154 == 3) {
        if (ACTOR_C71C->unkDE < 1000) {
            guRotateF(sp74, -(((f64)ACTOR_C71C->unkDC / 4095.0) * 360.0), 0.0f, 1.0f, 0.0f);
            guMtxCatF(spB4, sp74, spB4);
        }
        guRotateF(sp74, 90.0 - ((f64)ACTOR_C71C->unkDE / 4095.0) * 360.0, 1.0f, 0.0f, 0.0f);
        guMtxCatF(spB4, sp74, spB4);
        if (ACTOR_C71C->unkDE < 1000) {
            guRotateF(sp74, ((f64)ACTOR_C71C->unkDC / 4095.0) * 360.0, 0.0f, 1.0f, 0.0f);
            guMtxCatF(spB4, sp74, spB4);
        }
    }
    guTranslateF(sp74, ACTOR_C71C->unk7C, ACTOR_C71C->unk80, ACTOR_C71C->unk84);
    guMtxCatF(spB4, sp74, (float (*)[4])((u8 *)D_807FBB40 + 0xC));
}

extern s32 D_8071FE64;
extern s32 D_8071FE88;
extern s32 D_8071FEAC;
void effectTumbleBounceUpdate(void);
void func_8060E7EC(s32, s32, s32);

void tagBarrelDespawnEffects(void) {
    void (*sp5C)(void);
    f32 temp_fs0;
    s32 temp_s0;
    s32 var_s1;

    temp_fs0 = (f64) D_807FBB40->unk4->unk38 / 0.15;
    func_8060E7EC(0, 0xB4, 0xA);
    func_807149B8(0);
    func_807149FC(1);
    func_80714CC0(&D_8071FE08, (f64) temp_fs0 * 0.75, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84);
    sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x23, 0xFF, 0x7F, 1);

    for (var_s1 = 0; var_s1 != 7; var_s1++) {
        temp_s0 = ((s32) (randomLcgNext() / 10000U)) % 3;
        func_807149B8(1);
        func_807149FC(0xA);
        func_8071498C(effectTumbleBounceUpdate);
        func_80714998(2);
        func_80714950(2);
        switch (temp_s0) {
        case 0:
            func_80714CC0(&D_8071FE64, (f64) temp_fs0 * 0.25, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84);
            break;
        case 1:
            func_80714CC0(&D_8071FE88, (f64) temp_fs0 * 0.25, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84);
            break;
        case 2:
            func_80714CC0(&D_8071FEAC, (f64) temp_fs0 * 0.25, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84);
            break;
        }
    }
}

void func_8067DF44(f32 arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4, u8 arg5) {
    f64 sp80;
    f32 sp7C;
    f32 temp_fs2;
    f32 temp_fs1;
    f32 temp_fs0;
    s32 var_s0;

    if (arg5 != 0) {
        sfxPlayAtPositionPooled(arg0, arg1, arg2, 0xF6, 0xFF, 0x7F, 0x19, 0x1E, 0.3f, 0);
    }
    func_807149B8(1);
    func_8071498C(func_8071B89C);
    func_80714CC0(&D_80720120, 0.0f, arg0, arg1 + 5.0f, arg2);
    sp80 = (f64) arg3;
    sp7C = sp80 * 1.5;
    for (var_s0 = 0; var_s0 < 5; var_s0++) {
        temp_fs1 = (f32) (((s32) (randomNonNegative() >> 15) % 20) - 10) * arg3;
        temp_fs2 = (f32) (((s32) (randomNonNegative() >> 15) % 20) - 10) * arg3;
        temp_fs0 = (f32) (((s32) (randomNonNegative() >> 15) % 20) - 10) * arg3;
        func_8071496C(4);
        func_807149B8(1);
        func_807149FC(1);
        func_8071498C(func_8071BB14);
        func_80714CC0(&D_80720340, sp7C, arg0 + temp_fs1, arg1 + temp_fs2, arg2 + temp_fs0);
    }
    func_8071496C(4);
    func_807149B8(1);
    func_807149FC(1);
    func_8071498C(func_8071BB14);
    func_80714CC0(&D_80720340, sp7C, arg0, arg1, arg2);
    if (arg4 != 0) {
        for (var_s0 = 0; var_s0 != 12; var_s0++) {
            func_807149B8(1);
            func_807149FC(2);
            func_80714950(var_s0 + 0x0B020000);
            func_8071498C(effectRadialSprayUpdate);
            func_80714998(1);
            func_80714CC0(&D_8072038C, (f32)(sp80 * 0.5), arg0, arg1, arg2);
        }
    }
}

void func_8067E278(arg0, arg1)
u8 arg0;
u8 arg1;
{
    func_8067DF44(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, (f32) ((f64) D_807FBB40->unk4->unk38 / 0.15), arg0, arg1);
}

void func_8067E2E4(s32 arg0, u8 arg1, f32 arg2) {
    f32 sp2C;
    f32 sp28;
    f32 sp24;

    actorGetNodePos(D_807FBB40, arg1, &sp2C, &sp28, &sp24);
    func_8067DF44(sp2C, sp28, sp24, arg2, 0, 1);
}

void tagBarrelResetMovement(void) {
    TagBarrelState *temp_v0 = D_807FBB40->unk174;

    D_807FBB40->unk4->unk34 = temp_v0->unkC;
    D_807FBB40->unk4->unk38 = temp_v0->unkC;
    D_807FBB40->unk4->unk3C = temp_v0->unkC;
    D_807FBB40->unk80 = temp_v0->unk14;
    temp_v0->unk8 = 0;
    temp_v0->unk18 = 0;
    temp_v0->unk10 = temp_v0->unkC;
    D_807FBB40->unk154 = 0;
    D_807FBB40->unk144 = 2;
    D_807FBB40->unk60 &= ~0x200000;
}

void tagBarrelTriggerRecoil(void) {
    tagBarrelResetMovement();
    D_807FBB40->unk154 = 0x14;
    D_807FBB40->unk144 = 1;
    D_807FBB40->unk60 &= ~0x8000;
    D_807FBB40->unk128 = 0;
    slotQueueCancel(5, 0);
}

void tagBarrelCheckRecoil(void) {
    s16 i;

    for (i = 0; i < D_807FBB70.unk254; i++) {
        if (D_807FBB70.unk258[i] == 1 && *D_807FBB70.unk278[i] == 0xFF) {
            tagBarrelTriggerRecoil();
        }
    }
}

void func_8067E4D4(void) {
    transformBarrelUpdate();
    if (D_807FBB40->unk154 == 0) {
        tagBarrelCheckRecoil();
    }
}

void func_8067E510(void) {
    s16 i;

    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk4->unk34 = (f32)(D_807FBB40->unk4->unk34 * 1.5);
        D_807FBB40->unk4->unk38 = (f32)(D_807FBB40->unk4->unk38 * 1.5);
        D_807FBB40->unk4->unk3C = (f32)(D_807FBB40->unk4->unk3C * 1.5);
        D_807FBB40->unk12A = 0x7D0;
    }
    if (D_807FBB40->unk154 == 0) {
        for (i = 0; i < D_807FBB70.unk254; i++) {
            if (D_807FBB70.unk258[i] == 1) {
                func_807149B8(0);
                func_807149FC(1);
                func_80714CC0(&D_8071FE08, 0.5f, D_807FBB40->unk7C, D_807FBB40->unk80 + 7.0f, D_807FBB40->unk84);
                actorDespawn(D_807FBB40);
            }
        }
    }
    transformBarrelUpdate();
}

void func_8067E69C(void) {
    transformBarrelUpdate();
    tagBarrelCheckRecoil();
}

void func_8067E6C4(void) {
    transformBarrelUpdate();
}

void func_8067E6E4(void) {
    transformBarrelUpdate();
}

void func_8067E704(void) {
    transformBarrelUpdate();
}

void func_8067E724(void) {
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk12A = 0x320;
    }
    transformBarrelUpdate();
}

void func_8067E764(void) {
    transformBarrelUpdate();
}

typedef struct TransformBarrelEntry {
    u8 unk0;
    u8 unk1;
    u8 unk2;
} TransformBarrelEntry;

typedef struct TransformBarrelPlayerStruct {
    u8 pad0[0x2C0];
    u8 unk2C0;
    u8 pad2C1[0x2C8 - 0x2C1];
    s16 unk2C8;
    u8 pad2CA[0x2F0 - 0x2CA];
} TransformBarrelPlayerStruct;

typedef struct TransformBarrelPlayerState {
    /* 0x000 */ u8 pad0[0x88];
    /* 0x088 */ Actor *unk88;
    /* 0x08C */ u8 pad8C[0x104 - 0x8C];
    /* 0x104 */ s32 unk104;
    /* 0x108 */ u8 pad108[0x1A4 - 0x108];
    /* 0x1A4 */ u8 unk1A4;
    /* 0x1A5 */ u8 pad1A5[0x1F0 - 0x1A5];
    /* 0x1F0 */ s32 unk1F0;
    /* 0x1F4 */ u8 pad1F4[0x1FD - 0x1F4];
    /* 0x1FD */ u8 unk1FD;
} TransformBarrelPlayerState;

typedef struct TransformBarrelState {
    s16 unk0;
    s16 unk2;
    Actor *unk4;
    s16 unk8;
    s16 unkA;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    s16 unk18;
    s16 unk1A;
    u8 unk1C;
} TransformBarrelState;

extern TransformBarrelEntry D_8074E7BC[];
extern u8 D_807FC950[][0x5E];

extern s32 D_807FBB60;
extern s32 D_807FBB68;

void sfxAllocateChannel(s32, f32);
void sfxStopChannel(s32, s32);
s32 sfxPlayOnFreeSlot(s32, s32, f32, f32, s32, s32);
void camSetFollowMode(s32);
void func_8067A70C(Actor *, Actor *, f32, f32, f32, u8, u8);
void animResetEndFrame(Actor *, s32);
void animSetEndFrame(Actor *, s32, s32);
void func_806C8D20(Actor *);
s32 slotQueueGetValue(s32, s32);
void slotQueueUpdate(s32, u8, s32);
void slotQueueAddValue(s32, u8, s32);
s32 slotQueueGetCountStep(s32);

void transformBarrelUpdate(void) {
    TransformBarrelState *var_t0;
    f32 spA0;
    f32 sp9C;
    f32 sp98;
    TransformBarrelPlayerState *playerState;
    s32 ret;
    s16 i;
    s16 sp8C;
    s16 sp8A = 8;
    u8 sp89;
    u8 pad[8];
    s32 var_v1_2;
    s32 var_a0c;
    TransformBarrelPlayerState *ps3;

    var_t0 = D_807FBB40->unk174;
    if (!(D_807FBB40->unk60 & 0x10)) {
        sp8C = 0;
        sp89 = 0;
        ret = actorListFindIdByActor(D_807FBB40);
        if ((Actor *)D_807FBB4C) {} // FAKE: raises &D_807FBB4C candidate priority
        var_t0->unk1C = 0;
        do {
            if (D_8076A0A8 == D_8074E7BC[sp8C].unk0 && ret == D_8074E7BC[sp8C].unk1) {
                sp89 = 1;
                var_t0->unk1C = D_8074E7BC[sp8C].unk2;
            } else {
                sp8C++;
            }
        } while (!sp89 && sp8C < sp8A);

        if (*(s32 *)D_807FBB40->unk124 == 1) {
            if (func_8067B450(D_807FBB40) == 0) {
                D_807FBB40->unk154 = 0x14;
                D_807FBB40->unk144 = 1;
                D_807FBB40->unk60 &= ~0x8000;
                D_807FBB40->unk128 = 0;
            }
        }
        D_807FBB40->unkA4 = D_807FBB40->unk80;
        actorUpdateFloorContactAndTilt(D_807FBB40, 0.0f);
        D_807FBB40->unk60 |= 2;
        var_t0->unk10 = D_807FBB40->unk4->unk38;
        var_t0->unkC = D_807FBB40->unk4->unk38;
        var_t0->unk8 = 0;
        var_t0->unk18 = 0;
        var_t0->unk14 = D_807FBB40->unk80;
        if (((u32)D_807FBB40->unk58) == 0x12 || ((u32)D_807FBB40->unk58) == 0x81) {
            var_t0->unk1A = ((s32 *)D_807FBB40->unk124)[1];
        }
    }
    func_8067ACB4(D_807FBB40);

    if (D_807FBB40->unk154 == 0 && D_807FBB70.unk200 == 4) {
        playerState = ((Actor *)D_807FBB4C)->unk174;

        sfxStopChannel(0x6B, 1);
        if (((u32)D_807FBB40->unk58) != 0x60) {
            sfxAllocateChannel(0xF, 1.0f);
        }
        if (var_t0->unk1A != 0) {
            ret = -1;

            if (((u32)D_807FBB40->unk58) == 0x12) {
                ret = 0xF;
            } else if (((u32)D_807FBB40->unk58) == 0x81) {
                ret = 0x10;
            }
            if (ret >= 0) {
                flagSet(ret, 1, 1);
            }
            playerState->unk1FD = 1;
        }
        if (D_807FBB68 & 2) {
            var_t0->unk0 = 0x1E;
        } else {
            switch (((u32)D_807FBB40->unk58)) {
            case 0x60:
                var_t0->unk0 = 0x32;
                break;
            case 0x38:
                var_t0->unk0 = 0x1E;
                break;
            default:
                var_t0->unk0 = 0x64;
                break;
            }
        }
        if (var_t0->unk1C != 0) {
            s32 temp_s0 = slotQueueGetValue(5, playerState->unk1A4);
            s32 temp_lo = slotQueueGetCountStep(5) * var_t0->unk1C;

            if (temp_s0 < temp_lo) {
                slotQueueAddValue(5, playerState->unk1A4, (s16)(temp_lo - temp_s0));
            }
        }
        D_807FBB40->unk154 = 1;
        D_807FBB40->unk144 = 1;
        var_t0->unk4 = (Actor *)D_807FBB70.unk1FC;
        D_807FBB40->unk60 |= 0x200000;
        if (!(D_807FBB64 & 0x2000)) {
            if (var_t0->unk4->unk5C & 1) {
                ps3 = var_t0->unk4->unk174;

                if (ps3->unk88 != NULL) {
                    actorDespawn(ps3->unk88);
                    ps3->unk88 = NULL;
                    camSetFollowMode(ps3->unk104);
                }
            }
        }
        ((Actor *)*(s32 *)&var_t0->unk4)->unk144 = 1; // FAKE: s32 view keeps this load out of the var_t0->unk4 candidate (ring temp, not a1)
    }

    if (D_807FBB40->unk154 < 0x14) {
        s32 var_a0 = 0;
        s32 var_a1 = 0;

        if (D_8074E77C < 5) {
            var_a0 = D_807FC950[D_8074E77C][0];
        }
        if (((u32)((Actor *)D_807FBB4C)->unk58) == 5 && ((u32)D_807FBB40->unk58) == 0x28 && var_a0 > 0) {
            var_a1 = 1;
        }
        if (((u32)((Actor *)D_807FBB4C)->unk58) == 6 && ((u32)D_807FBB40->unk58) == 0x19 && var_a0 > 0) {
            var_a1 = 1;
        }
        if (((u32)((Actor *)D_807FBB4C)->unk58) == 6 && ((u32)D_807FBB40->unk58) == 0x60 && var_a0 > 0) {
            var_a1 = 1;
        }
        if (((u32)((Actor *)D_807FBB4C)->unk58) == 4 && ((u32)D_807FBB40->unk58) == 0x38 && var_a0 >= 3) {
            var_a1 = 1;
        }
        if (((u32)((Actor *)D_807FBB4C)->unk58) == 2 && ((u32)D_807FBB40->unk58) == 0x39 && var_a0 >= 2) {
            var_a1 = 1;
        }
        if (((u32)((Actor *)D_807FBB4C)->unk58) == 4 && ((u32)D_807FBB40->unk58) == 0x81) {
            var_a1 = 1;
        }
        if (((u32)D_807FBB40->unk58) == 0x12) {
            var_a1 = 1;
        }
        if (((u32)D_807FBB40->unk58) == 0x84 && ((u32)((Actor *)D_807FBB4C)->unk58) == 9 && (ret = (s32)((Actor *)D_807FBB4C)->unk174, ((TransformBarrelPlayerState *)ret)->unk88 == NULL)) { // FAKE: ret reused as the temp (takes v0, no ring slot)
            var_a1 = 1;
        }
        if (var_a1 != 0) {
            D_807FBB40->unk60 |= 0x8000;
            *(u16 *)&D_807FBB40->unk132 = 1; // FAKE: unsigned u16 store keeps constant 1 out of the hoisted-constant web
        } else {
            D_807FBB40->unk60 &= ~0x8000;
            D_807FBB40->unk128 = 0x78;
            D_807FBB40->unk132 = 2;
        }
    } else {
        D_807FBB40->unk132 = 1;
    }
    if (D_807FD580->unkCA != 0) {
        D_807FBB40->unk132 = 2;
    }

    switch (D_807FBB40->unk154) {
    case 0:
        if (((u32)D_807FBB40->unk58) != 0x12 && ((u32)D_807FBB40->unk58) != 0x81 && ((u32)D_807FBB40->unk58) != 0x84) {
            animSetSpeed(D_807FBB40, 0, 0.5f);
            animSetLoopMode(D_807FBB40, 0, 0);
            animSetEndFrame(D_807FBB40, 0, 9);
            animSetLoopLimit(D_807FBB40, 0, 0x32);
        }
        break;

    case 1:
        if (var_t0->unk0 < 0x1E) {
            switch (((u32)D_807FBB40->unk58)) {
            case 0x19:
            case 0x60:
                var_t0->unk10 += (((u32)D_807FBB40->unk58) == 0x19) ? 0.004 : 0.008;
                D_807FBB40->unk80 += 0.6;
                if ((D_807FBB40->unk80 - var_t0->unk14) > 25.0f) {
                    D_807FBB40->unk80 = var_t0->unk14 + 25.0f;
                }
                break;
            case 0x28:
                var_t0->unk10 -= 0.001;
                D_807FBB40->unk80 += 0.6;
                if ((D_807FBB40->unk80 - var_t0->unk14) > 25.0f) {
                    D_807FBB40->unk80 = var_t0->unk14 + 25.0f;
                }
                break;
            case 0x12:
            case 0x81:
            case 0x84:
                var_t0->unk10 += 0.006;
                break;
            }
        }
        D_807FBB40->unk4->unk34 = sinApprox(var_t0->unk8 * 0.11) * 0.1 + var_t0->unk10;
        D_807FBB40->unk4->unk38 = sinApprox(var_t0->unk8 * 0.2352) * 0.1 + var_t0->unk10;
        D_807FBB40->unk4->unk3C = sinApprox(var_t0->unk8 * 0.176) * 0.1 + var_t0->unk10;
        var_t0->unk8++;
        if (((u32)D_807FBB40->unk58) != 0x12 && ((u32)D_807FBB40->unk58) != 0x81 && ((u32)D_807FBB40->unk58) != 0x84) {
            D_807FBB40->unkE6 += var_t0->unk18;
            var_t0->unk18 += 10;
            if (var_t0->unk18 >= 0x65) {
                var_t0->unk18 = 0x64;
            }
        }
        func_8067A70C(D_807FBB40, var_t0->unk4, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 2, 1);
        var_t0->unk0--;
        if (var_t0->unk0 == 0) {
            var_t0->unk0 = 0xC;
            D_807FBB40->unk154 = 2;
            if (((u32)D_807FBB40->unk58) != 0x12 && ((u32)D_807FBB40->unk58) != 0x81 && D_8076A0A8 != 0x52 && !(D_807FBB64 & 1)) {
                slotQueueUpdate(5, 1, 0);
            }
        }
        break;

    case 2:
        var_t0->unk0--;
        if (var_t0->unk0 == 0) {
            D_807FBB40->unk154 = 3;
        }
        break;

    case 3: {
        s16 sp62 = 0;
        if (((u32)((Actor *)D_807FBB4C)->unk58) == 9) {}  // FAKE: dead compare steers uopt constant-web (0x81/0x84) colouring order
        switch (((u32)D_807FBB40->unk58)) {
        case 0x28:
            sp62 = 0x10;
            sfxPlayOnFreeSlot(0x1A5, 0x58EF, 63.0f, 1.0f, 0, 0);
            break;
        case 0x19:
            sp62 = 0x11;
            sfxPlayOnFreeSlot(0xC7, 0x7FFF, 63.0f, 1.0f, 0, 0);
            break;
        case 0x12:
            sp62 = 0x24;
            sfxPlayOnFreeSlot(0x2EC, 0x7FFF, 63.0f, 1.0f, 0, 0);
            D_807FBB60 |= 0x400;
            break;
        case 0x39:
            sp62 = 0x47;
            break;
        case 0x38:
            sp62 = 0x49;
            break;
        case 0x81:
            sp62 = 0x7C;
            D_807FBB60 |= 0x400;
            break;
        }
        if (sp62 != 0 && !(D_807FBB68 & 2) && D_8076A0A8 != 3 && D_8076A0A8 != 0x11 && D_8076A0A8 != 0x52 && D_8076A0A8 != 0xD1) {
            if (D_8074E77C) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            sfxAllocateChannel(sp62, 1.0f);
        }
        sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x9C, 0xFF, 0x7F, 0);
        sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x9D, 0xFF, 0x7F, 0);
        if (((u32)D_807FBB40->unk58) != 0x12 && ((u32)D_807FBB40->unk58) != 0x81 && ((u32)D_807FBB40->unk58) != 0x84) {
            animResetEndFrame(D_807FBB40, 0);
            animSetFrameAndSubframe(D_807FBB40, 0, 0xA, 0.0f);
        }
        actorGetNodePos(D_807FBB40, 1, &spA0, &sp9C, &sp98);
        actorAppendCallback(var_t0->unk4, (s32)D_807FBB40, 0x40, 1, 0, NULL);
        {
            s16 angle;
            if (((u32)D_807FBB40->unk58) == 0x12) {
                angle = ((TransformBarrelPlayerStruct *)D_807FC924)->unk2C8 & 0xFFF;
            } else {
                angle = var_t0->unk4->unkE6;
            }
            func_8067AAB8((s32)D_807FBB40, var_t0->unk4, angle, -40.0f, 0);
        }
        func_806C8D20(var_t0->unk4);
        tagBarrelDespawnEffects();
        D_807FBB40->unk154 = 4;
        if (((u32)D_807FBB40->unk58) == 0x39) {
            sfxPlayOnFreeSlot(0x231, 0x58EF, 63.0f, 1.0f, 0, 0);
        }
        if (((u32)D_807FBB40->unk58) == 0x38) {
            sfxPlayOnFreeSlot(0xD4, 0x58EF, 63.0f, 1.0f, 0, 0);
        }
        break;
    }

    case 4: {
        playerState = var_t0->unk4->unk174;
        var_v1_2 = 0;

        switch (((u32)D_807FBB40->unk58)) {
        case 0x19:
        case 0x28:
        case 0x60:
            if (((TransformBarrelPlayerStruct *)D_807FC924)[playerState->unk1A4].unk2C0 != 1) {
                var_v1_2 = 1;
            }
            break;
        case 0x39:
            if (playerState->unk1F0 & 0x10) {
                var_v1_2 = 1;
            }
            break;
        case 0x38:
            if (playerState->unk1F0 & 0x20) {
                var_v1_2 = 1;
            }
            break;
        case 0x12:
            if (((u32)((Actor *)D_807FBB4C)->unk58) == 8) {
                var_v1_2 = 1;
            }
            break;
        case 0x81:
            if (((u32)((Actor *)D_807FBB4C)->unk58) == 9) {
                var_v1_2 = 1;
            }
            break;
        case 0x84:
            if (playerState->unk88 != NULL) {
                var_v1_2 = 1;
            }
            break;
        }

        if (var_v1_2 != 0) {
            D_807FBB40->unk60 &= ~0x8000;
            D_807FBB40->unk128 = 0;
        } else {
            D_807FBB60 &= ~0x400;
            if (((u32)D_807FBB40->unk58) != 0x60) {
                var_a0c = 0;
                switch (((u32)D_807FBB40->unk58)) {
                case 0x38:
                    var_a0c = 0x49;
                    break;
                case 0x81:
                    var_a0c = 0x7C;
                    break;
                case 0x39:
                    var_a0c = 0x47;
                    break;
                case 0x12:
                    var_a0c = 0x24;
                    break;
                case 0x19:
                    var_a0c = 0x11;
                    break;
                case 0x28:
                    var_a0c = 0x10;
                    break;
                }
                sfxStopChannel(var_a0c, 0);
                sfxAllocateChannel(0xF, 1.0f);
            }
            D_807FBB40->unk154 = 5;
            if ((D_807FBB68 & 2) && ((u32)D_807FBB40->unk58) == 0x19) {
                var_t0->unk0 = 1;
            } else {
                var_t0->unk0 = 0x5A;
            }
        }
        break;
    }

    case 5:
        D_807FBB40->unk60 &= ~0x8000;
        D_807FBB40->unk128 = 0;
        var_t0->unk0--;
        if (var_t0->unk0 == 0) {
            if (D_8076A0A8 == 0xCE) {
                tagBarrelTriggerRecoil();
            } else {
                tagBarrelResetMovement();
            }
            if (((u32)D_807FBB40->unk58) != 0x12 && ((u32)D_807FBB40->unk58) != 0x81) {
                slotQueueCancel(5, 0);
            }
            if (((u32)D_807FBB40->unk58) == 0x60) {
                actorDespawn(D_807FBB40);
            }
        }
        break;

    case 20:
        for (i = 0; i < D_807FBB70.unk254; i++) {
            if (D_807FBB70.unk258[i] == 1 && *D_807FBB70.unk278[i] != 0xFF) {
                D_807FBB40->unk144 = 2;
                D_807FBB40->unk154 = 0x15;
            }
        }
        break;

    case 21:
        D_807FBB40->unk128 += 10;
        if (D_807FBB40->unk128 >= 0xF1) {
            D_807FBB40->unk60 |= 0x8000;
            D_807FBB40->unk154 = 0;
        }
        break;
    }

    func_8065D254(D_807FBB40, 0x3C8, 0x40, 0x40, (s32)(D_807FBB40->unk4->unk34 * 100.0f), (s32)(D_807FBB40->unk4->unk3C * 100.0f), 1, 0x64, (u32)(D_807FBB40->unk128 * 0.5), 0, 1.0f);
    actorUpdateModelMatrix(D_807FBB40, 0);
}


void tagBarrelDespawnOnKongDeselect(void) {
    s16 i;

    for (i = 0; i < D_807FBB70.unk254; i++) {
        if (D_807FBB70.unk258[i] == 1 && *D_807FBB70.unk278[i] == 1) {
            tagBarrelDespawnEffects();
            actorDespawn(D_807FBB40);
        }
    }
}

typedef struct ActorFB6CSpawnData {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} ActorFB6CSpawnData;

typedef struct ActorFB6CCamHolder {
    u8 pad0[0x104];
    s32 unk104;
} ActorFB6CCamHolder;

typedef struct ActorFB6CState {
    Actor *unk0;
    u32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    s16 unk18;
    u8 unk1A;
    u8 unk1B;
    u8 unk1C;
} ActorFB6CState;

typedef struct ActorFB6C {
    u8 pad0[0xEE];
    s16 unkEE;
} ActorFB6C;

extern Actor *D_807FBB48;
extern s32 D_807FBB68;
extern u16 D_807FD63C;
void func_806FF01C();

f32 func_80612790(s16);
f32 func_80612794(s16);
void func_80613194(Actor *, s16);
void func_80613214(Actor *);
void camSetFixedView(s32, f32, f32, f32, f32, f32, f32, u8);
void camSetTargetScaled(s32, Actor *, u8, s16, s16, s16, s16, s16, s16, s16, f32);
s32 collisionCheckGroundAtPoint(f32, f32, f32 *);
void func_8067A70C(Actor *, Actor *, f32, f32, f32, u8, u8);
void renderCallbacksRegister(void *, void *, s32);

void func_8067FB6C(void) {
    f64 pad;
    f32 sp5C;
    f32 sp58;
    s32 sp54;
    s32 pad2;
    s16 sp4E;
    ActorFB6CState *sub;
    s32 var_v0;
    f32 var_fa1;
    s16 i;

    sub = D_807FBB40->unk174;
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk12A = 0x320;
        D_807FBB40->unk12C[4] = 0x14;
        D_807FBB40->unk12C[5] = 0x14;
        sub->unkC = 90.0f;
        sub->unk8 = D_807FBB40->unk80;
        sub->unk14 = (f64)((ActorFB6CSpawnData *)D_807FBB40->unk124)->unk0 / 200.0;
        sub->unk10 = ((ActorFB6CSpawnData *)D_807FBB40->unk124)->unk4;
        sub->unk4 = ((f64)sub->unk14 != 0.0) ? (4.71238899230957031 / (f64)sub->unk14) : (f64)0;
        sub->unk1C = ((ActorFB6CSpawnData *)D_807FBB40->unk124)->unk8;
        sub->unk18 = D_807FBB40->unkE6;
        D_807FBB40->unkA4 = 99999.0f;
        collisionCheckGroundAtPoint(D_807FBB40->unk7C, D_807FBB40->unk84, &D_807FBB40->unkA4);
        if (sub->unk1C == 3) {
            D_807FBB40->unk132 = 2;
        } else {
            D_807FBB40->unk132 = 1;
        }
        if (((ActorFB6CSpawnData *)D_807FBB40->unk124)->unkC == 1) {
            D_807FBB40->unk154 = 0x14;
            D_807FBB40->unk144 = 1;
            D_807FBB40->unk60 &= ~0x8000;
            D_807FBB40->unk128 = 0;
        }
    }
    if (D_807FBB70.unk200 == 4) {
        sub->unk0 = (Actor *)D_807FBB70.unk1FC;
        D_807FBB40->unk154 = 1;
        D_807FBB40->unk144 = 1;
        D_807FBB40->unk60 |= 0x400;
        sub->unk1B = 2;
        if (sub->unk1C == 3) {
            sub->unk1A = 1;
        } else {
            sub->unk1A = 2;
        }
    }
    switch (D_807FBB40->unk154) {
    case 0:
        tagBarrelDespawnOnKongDeselect();
        break;
    case 1:
        D_807FBB40->unk60 |= 0x8000;
        switch (sub->unk1C) {
        case 0:
        case 4:
            if (sub->unk1C == 0) {
                D_807FBB40->unk80 = sinApprox((f32)sub->unk4 * sub->unk14) * sub->unk10 + (sub->unk8 + sub->unk10);
            } else {
                D_807FBB40->unk80 = sinApprox((f32)sub->unk4 * sub->unk14) * sub->unk10 + sub->unk8;
            }
            func_8067A70C(D_807FBB40, sub->unk0, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 2, 1);
            sp4E = D_807FBB40->unkE6;
            sub->unk4++;
            break;
        case 2:
            D_807FBB40->unkE6 = (D_807FBB40->unkE6 + (s32)(sub->unk14 * 200.0f)) & 0xFFF;
            sp4E = (D_807FBB40->unkE6 + (s32)(sub->unk14 * 200.0f)) & 0xFFF;
            break;
        case 1:
            D_807FBB40->unkE6 = ((s16)(s32)(sinApprox((f32)sub->unk4 * sub->unk14) * ((sub->unk10 * 4096.0f) / 360.0f)) + sub->unk18) & 0xFFF; // FAKE: (s16) narrowing cast steers the temp register ring
            sub->unk4++;
            sp4E = ((s16)(s32)(sinApprox((f32)sub->unk4 * sub->unk14) * ((sub->unk10 * 4096.0f) / 360.0f)) + sub->unk18) & 0xFFF; // FAKE: (s16) narrowing cast steers the temp register ring
            break;
        case 3:
            sp4E = D_807FBB40->unkE6;
            break;
        }
        sp5C = func_80612794(sp4E) * 50.0f;
        sp58 = func_80612790(sp4E) * 50.0f;
        if (sub->unk1B == 1) {
            func_80613194(D_807FBB40, 0x75);
        }
        if (sub->unk1B) {
            sub->unk1B--;
        }
        if (sub->unk1A) {
            sub->unk1A--;
        }
        if (((D_807FD63C & 0xE000) || sub->unk1C == 3) && sub->unk1A == 0) {
            ActorFB6CCamHolder *temp_s0_2;
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x18, 0xFF, 0x7F, 1);
            temp_s0_2 = sub->unk0->unk174;
            func_80613214(D_807FBB40);
            if (!(D_807FBB68 & 2)) {
                if (sub->unk1C == 3) {
                    var_v0 = 0x64;
                } else {
                    var_v0 = 0x32;
                }
                camSetTargetScaled(temp_s0_2->unk104, sub->unk0, 4, 0x800, var_v0, 0, 0, 0x1E, 0x14, 0x50, 0.3f);
            }
            D_807FBB48->unkE6 = D_807FBB40->unkE6;
            ((ActorFB6C *)D_807FBB48)->unkEE = D_807FBB40->unkE6;
            actorAppendCallback(sub->unk0, (s32)D_807FBB40, 0x40, 1, 0, 0);
            if (D_807FBB68 & 2) {
                var_v0 = 0x1F4;
            } else {
                var_v0 = 0x2BC;
            }
            func_8067AAB8((s32)D_807FBB40, sub->unk0, D_807FBB40->unkE6, 0.0f, var_v0);
            actorQueueDelayedCallback(D_807FBB40, D_807FBB40, 0x800, 2, 0, 0, 0xA);
            func_80714998(2);
            func_80714C08(&D_8071FBC8, 1.6f, D_807FBB40, 1, 2);
            D_807FBB40->unk60 &= ~0x400;
            D_807FBB40->unk154 = 2;
            D_807FBB40->unk155[0] = 0x1E;
        } else {
            sp54 = ((ActorFB6CCamHolder *)sub->unk0->unk174)->unk104;
            switch (sub->unk1C) {
            case 0:
                var_fa1 = sinApprox((f32)sub->unk4 * sub->unk14) * sub->unk10 + (sub->unk8 + sub->unk10);
                break;
            case 4:
                var_fa1 = sinApprox((f32)sub->unk4 * sub->unk14) * sub->unk10 + sub->unk8;
                break;
            default:
                var_fa1 = D_807FBB40->unk80;
                break;
            }
            if (D_807FBB68 & 2) {
                var_v0 = 0;
            } else {
                var_v0 = 1;
            }
            camSetFixedView(
                sp54,
                (f64)D_807FBB40->unk7C - (f64)sp5C / 5.0,
                var_fa1,
                (f64)D_807FBB40->unk84 - (f64)sp58 / 5.0,
                D_807FBB40->unk7C + sp5C,
                var_fa1,
                D_807FBB40->unk84 + sp58,
                var_v0
            );
            if (camIsCutsceneActive() == 0) {
                renderCallbacksRegister(func_806FF01C, D_807FBB4C, 3);
            }
        }
        break;
    case 2:
        tagBarrelDespawnOnKongDeselect();
        D_807FBB40->unk155[0]--;
        if (D_807FBB40->unk155[0] == 0) {
            D_807FBB40->unk80 = sub->unk8;
            sub->unk4 = ((f64)sub->unk14 != 0.0) ? (4.71238899230957031 / (f64)sub->unk14) : (f64)0;
            D_807FBB40->unkE6 = sub->unk18;
            D_807FBB40->unk154 = 0;
        }
        break;
    case 20:
        for (i = 0; i < D_807FBB70.unk254; i++) {
            if (D_807FBB70.unk258[i] == 1 && *D_807FBB70.unk278[i] == 0) {
                D_807FBB40->unk144 = 2;
                D_807FBB40->unk154 = 0x15;
            }
        }
        break;
    case 21:
        D_807FBB40->unk128 += 10;
        if (D_807FBB40->unk128 >= 0xF1) {
            D_807FBB40->unk60 |= 0x8000;
            D_807FBB40->unk154 = 0;
        }
        break;
    }
    if (D_8076A0A8 == 0xCB) {
        D_807FBB40->unk60 |= 0x400;
    }
    guRotateF((float (*)[4])&D_807FBB40->unk08[4], sub->unkC, 1.0f, 0, 0.0f);
    actorUpdateModelMatrix(D_807FBB40, 1);
}

typedef struct PlayerStateD580 {
    /* 0x000 */ char unk0[0xCA];
    /* 0x0CA */ u8 unkCA;
    /* 0x0CB */ char unkCB[0x1F0 - 0xCB];
    /* 0x1F0 */ s32 unk1F0;
    /* 0x1F4 */ s32 unk1F4;
} PlayerStateD580;

typedef struct PlayerData {
    /* 0x000 */ u8 unk0[0x210];
    /* 0x210 */ f32 unk210;
    /* 0x214 */ f32 unk214;
    /* 0x218 */ f32 unk218;
    /* 0x21C */ u8 unk21C[0xA4];
    /* 0x2C0 */ u8 unk2C0;
} PlayerData;

extern PlayerData *D_807FC924;

void tagBarrelUpdateInteractable(void) {
    s32 one = 1;

    if (one != D_807FC924->unk2C0 || (((PlayerStateD580 *)D_807FD580)->unk1F4 & 0x40) || D_8074E77C >= 5) {
        D_807FBB40->unk132 = 4;
        D_807FBB40->unk60 &= ~0x8000;
        D_807FBB40->unk128 = 0x7F;
    } else if (one == D_807FC924->unk2C0 && !(((PlayerStateD580 *)D_807FD580)->unk1F0 & 0x40) && D_8074E77C < 5) {
        D_807FBB40->unk60 |= 0x8000;
        D_807FBB40->unk132 = one;
    }
    if (((PlayerStateD580 *)D_807FD580)->unkCA != 0) {
        D_807FBB40->unk132 = 4;
    }
}

void tagBarrelCheckPlayerCollision(void) {
    if (D_8074E77C >= 5) {
        D_807FBB40->unk132 = 4;
        D_807FBB40->unk60 &= ~0x8000;
        D_807FBB40->unk128 = 0x7F;
    } else {
        D_807FBB40->unk60 |= 0x8000;
        D_807FBB40->unk132 = 1;
    }
    if (D_807FD580->unkCA != 0) {
        D_807FBB40->unk132 = 4;
    }
}

u8 tagBarrelGetKongType(void) {
    u8 ret = 0x64;

    switch (D_8076A0A8) {
    case 0x1A:
        if (actorListFindIdByActor(D_807FBB40) == 0xD || actorListFindIdByActor(D_807FBB40) == 0xF) {
            ret = 2;
        }
        break;
    case 0x3B:
        if (actorListFindIdByActor(D_807FBB40) == 3) {
            ret = 2;
        }
        break;
    case 0x30:
        if (actorListFindIdByActor(D_807FBB40) == 0x12) {
            ret = 2;
        }
        break;
    case 0xAD:
    case 0xC3:
        ret = 2;
        break;
    }
    return ret;
}

typedef struct TagBarrelActorState {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ u8 unkC;
    /* 0x0D */ u8 unkD;
    /* 0x0E */ u8 unkE;
} TagBarrelActorState;

typedef struct TagBarrelSpawnParams {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 pad0C[0xC];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
} TagBarrelSpawnParams;

typedef struct Vec3f {
    f32 x;
    f32 y;
    f32 z;
} Vec3f;

typedef struct TagBarrelPlayerState {
    u8 pad0[0xBC];
    s16 unkBC;
    s16 unkBE;
    u8 padC0[0x1A3 - 0xC0];
    u8 unk1A3;
} TagBarrelPlayerState;

extern Vec3f D_8074E7D4;
extern u8 D_8076A0B1;
extern u8 D_807FBD70;
extern u8 D_807FBDC4;
extern u8 D_8071FC58[];
extern s32 func_80716FB4;
void effectOrbitXZUpdate();

s32 func_8073195C(s16);
void actorListSetPosByActor(Actor *, f32, f32, f32);
void *actorFindByType(s32);
void actorSetCustomFloat(Actor *, s16, f32);
void func_805FF9AC(s16, s16, s16, s16);
void actorSetCustomInt(Actor *, s16, s32);
void actorSpawnNodeEntryScaled(s32, f32, f32, f32, s32, s32, s32, s32);

extern s16 D_80750390;
void func_80714A28(s32);
void sfxAllocateChannel(s32, f32);
void func_806C7BAC(void *, Actor *);

void tagBarrelActorUpdate(void) {
    s16 kong;
    s16 pad0;
    f32 coord[3];
    s32 i;
    Vec3f sp90;
    s16 *ptr;
    s16 sp8A;
    f32 dist;
    u8 sp83;
    TagBarrelActorState *sub;
    f32 temp_f;
    u32 val;
    f32 temp_f2;
    s16 angle;
    f32 yOffset;

    sub = (TagBarrelActorState *)D_807FBB40->unk174;
    if (D_8076A0A8 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    sp90 = D_8074E7D4;
    sp83 = 0;
    if (!(D_807FBB40->unk60 & 0x10)) {
        temp_f = (f64)D_807FBB40->unk4->unk34 / 0.15;
        D_807FBB40->unkA4 = D_807FBB40->unk80;
        actorUpdateFloorContactAndTilt(D_807FBB40, 0.0f);
        D_807FBB40->unk110 = 0;
        D_807FBB40->unk60 |= 2;
        sub->unk0 = D_807FBB40->unk80;
        sub->unk4 = 0;
        sub->unk6 = ((TagBarrelSpawnParams *)D_807FBB40->unk124)->unk0;
        sub->unkA = ((TagBarrelSpawnParams *)D_807FBB40->unk124)->unk8;
        sub->unkE = 0;
        if (D_807FBB40->unk58 == 0x1C) {
            if (flagGet(func_8073195C(sub->unkA), 0)) {
                actorDespawn(D_807FBB40);
            }
        }
        D_807FBB40->unk132 = 1;
        if (((TagBarrelSpawnParams *)D_807FBB40->unk124)->unk1C == 1.0 || ((TagBarrelSpawnParams *)D_807FBB40->unk124)->unk1C == 2.0) {
            D_807FBB40->unk154 = 0xA;
            sub->unkD = 0x14;
            D_807FBB40->unk4->unk34 = 0.02f;
            D_807FBB40->unk4->unk38 = 0.02f;
            D_807FBB40->unk4->unk3C = 0.02f;
            if (((TagBarrelSpawnParams *)D_807FBB40->unk124)->unk1C == 2.0) {
                sub->unkC = 1;
            } else {
                sub->unkC = 0;
            }
        } else if (((TagBarrelSpawnParams *)D_807FBB40->unk124)->unk4 == 1) {
            D_807FBB40->unk154 = 0x14;
            D_807FBB40->unk144 = 1;
            D_807FBB40->unk60 &= ~0x8000;
            D_807FBB40->unk128 = 0;
        } else {
            D_807FBB40->unk154 = 0;
        }
        temp_f = (f64)temp_f - 1.0;
        if ((f64)temp_f < 0.0) {
            temp_f = 0.0f;
        }
        val = (u32)(80.0f * temp_f + 20.0f);
        D_807FBB40->unk12C[4] = val;
        D_807FBB40->unk12C[5] = val;
    }
    for (i = 0; i < D_807FBDC4; i++) {
        ptr = D_807FBB70.unk278[i];
        switch (*ptr) {
            case 2:
                sub->unkE = 0x8C;
                break;
            default:
                break;
        }
    }
    if (sub->unkE != 0) {
        sub->unkE--;
        sub->unk0 = (f64)sub->unk0 + 1.0;
        actorListSetPosByActor(D_807FBB40, D_807FBB40->unk7C, sub->unk0, D_807FBB40->unk84);
    }
    if (D_807FBB40->unk154 != 0x14 && D_807FBB40->unk154 != 0x15) {
        tagBarrelCheckPlayerCollision();
    }
    if (D_8076A0A8 == 0xAA) {
        if (D_807FBB40->unk154 != 0xA && D_807FBB40->unk154 != 0xB && D_807FBB40->unk154 != 0xC && D_807FBB40->unk154 != 0x1E) {
            if (((PlayerStateD580 *)D_807FD580)->unk1F0 & 0x40) {
                D_807FBB40->unk144 = 2;
                D_807FBB40->unk60 |= 0x8000;
            } else {
                sp83 = 1;
                D_807FBB40->unk144 = 1;
                D_807FBB40->unk60 &= ~0x8000;
                D_807FBB40->unk128 = 0;
            }
        }
    }
    if ((D_807FBB40->unk60 & 0x100) && (D_807FBB40->unk154 == 0 || D_807FBB40->unk154 == 1 || (D_807FBB40->unk154 >= 0xA && D_807FBB40->unk154 < 0xD)) && sp83 == 0) {
        dist = (D_807FC924->unk218 - D_807FBB40->unk84) * (D_807FC924->unk218 - D_807FBB40->unk84) +
               ((D_807FC924->unk210 - D_807FBB40->unk7C) * (D_807FC924->unk210 - D_807FBB40->unk7C) +
                (D_807FC924->unk214 - D_807FBB40->unk80) * (D_807FC924->unk214 - D_807FBB40->unk80));
        if (dist < 40000.0f) {
            temp_f2 = (f64)D_807FBB40->unk4->unk34 / 0.15;
            coord[2] = ((f64)((randomNonNegative() >> 15) % (s32)(30.0f * temp_f2)) - (15.0 * (f64)temp_f2)) + D_807FBB40->unk7C;
            coord[1] = ((f64)((randomNonNegative() >> 15) % (s32)(30.0f * temp_f2)) - (15.0 * (f64)temp_f2)) + D_807FBB40->unk80;
            coord[0] = ((f64)((randomNonNegative() >> 15) % (s32)(30.0f * temp_f2)) - (15.0 * (f64)temp_f2)) + D_807FBB40->unk84;
            func_807149B8(1);
            func_80714A28(4);
            if (D_807FBB40->unk154 == 0) {
                func_8071498C(&func_80716FB4);
                func_80714CC0(D_8071FC58, 0.5f, coord[2], coord[1], coord[0]);
            } else {
                func_80714950((s32)(D_807FBB40->unk4->unk34 * 100.0f) + (sub->unk8 << 16));
                func_8071498C(effectOrbitXZUpdate);
                func_80714CC0(D_8071FC58, 0.5f, D_807FBB40->unk7C, coord[1], D_807FBB40->unk84);
            }
        }
    }
    func_8067ACB4(D_807FBB40);
    switch (D_807FBB40->unk154) {
    case 0:
        if (D_807FBD70 == 4) {
            D_807FBB40->unk154 = 1;
            D_807FBB40->unk144 = 1;
            sub->unk8 = 0;
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x261, 0xFF, 0x64, 1);
            camStartPath(NULL, 0x1F, 5);
            if (actorFindByType(0x25) != NULL) {
                actorSetCustomFloat(D_807FBB40, 6, 1.0f);
            } else {
                actorSetCustomFloat(D_807FBB40, 6, 0.0f);
            }
        } else {
            for (i = 0; i < D_807FBDC4; i++) {
                if (D_807FBB70.unk258[i] == 1 && *D_807FBB70.unk278[i] == 1) {
                    D_807FBB40->unk154 = 0x14;
                    D_807FBB40->unk144 = 1;
                    D_807FBB40->unk60 &= ~0x8000;
                    D_807FBB40->unk128 = 0;
                }
            }
        }
        break;
    case 1:
        sub->unk8 += 0x1E;
        if (sub->unk8 >= 0x191) {
            sub->unk8 = 0x190;
        }
        D_807FBB40->unkE6 += sub->unk8;
        if (sub->unk8 >= 0xC9) {
            D_807FBB40->unk4->unk34 = (f64)D_807FBB40->unk4->unk34 - 0.005;
            D_807FBB40->unk4->unk38 = (f64)D_807FBB40->unk4->unk38 - 0.005;
            D_807FBB40->unk4->unk3C = (f64)D_807FBB40->unk4->unk3C - 0.005;
            if ((f64)D_807FBB40->unk4->unk34 < 0.02) {
                D_807FBB40->unk154 = 2;
            }
        }
        break;
    case 2:
        actorSetCustomFloat(D_807FBB40, 7, 1.0f);
        if (!(D_8076A0B1 & 1) || D_807FBB40->unk58 != 0x6B) {
            func_805FF9AC(sub->unk6, 0, 0, 3);
        }
        actorDespawn(D_807FBB40);
        break;
    case 10:
        if (sub->unkD != 0) {
            sub->unkD -= 1;
        }
        if (sub->unkD == 5) {
            D_807FBB40->unk144 = 1;
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x262, 0xFF, 0x64, 1);
        }
        if (sub->unkD == 0) {
            D_807FBB40->unk4->unk34 = (f64)D_807FBB40->unk4->unk34 + 0.005;
            D_807FBB40->unk4->unk38 = (f64)D_807FBB40->unk4->unk38 + 0.005;
            D_807FBB40->unk4->unk3C = (f64)D_807FBB40->unk4->unk3C + 0.005;
            if ((f64)D_807FBB40->unk4->unk34 >= 0.15) {
                D_807FBB40->unk154 = 0xB;
            }
            temp_f = (0.15 - (f64)D_807FBB40->unk4->unk34) / 0.13;
            sub->unk8 = (s32)(temp_f * 400.0f);
            D_807FBB40->unkE6 += sub->unk8;
        }
        break;
    case 11:
        sub->unkD = 0x32;
        sub->unk8 = 0;
        actorAppendCallback(D_807FBB4C, (s32)D_807FBB40, 0x40, 1, 0, 0);
        if (((TagBarrelSpawnParams *)D_807FBB40->unk124)->unk18 == 1.0) {
            angle = D_80750390;
        } else {
            angle = 0xB4;
        }
        func_8067AAB8((s32)D_807FBB40, D_807FBB4C, (s16)((D_807FBB40->unkE6 + 0x800) & 0xFFF), (f32)angle, 0);
        if (((TagBarrelSpawnParams *)D_807FBB40->unk124)->unk18 == 1.0) {
            TagBarrelPlayerState *playerState = ((Actor *)D_807FBB4C)->unk174;
            func_806C7BAC(D_807FBB4C, 0);
            playerState->unk1A3 = 1;
            playerState->unkBC = 0x31;
            playerState->unkBE = -1;
            sfxAllocateChannel(0x48, 1.0f);
        }
        actorSetCustomFloat(D_807FBB40, 1, 0.0f);
        actorSetCustomInt(D_807FBB40, 7, 0);
        if (sub->unkC != 0) {
            D_807FBB40->unk154 = 0xC;
            if (tagBarrelGetKongType() == 2) {
                camStartPath(D_807FBB4C, 0x26, 5);
            }
        } else {
            D_807FBB40->unk132 = 1;
            D_807FBB40->unk154 = 0x1E;
        }
        break;
    case 12:
        sub->unkD--;
        if (sub->unkD < 0x28) {
            sp90.x = ((f64)(u32)((randomLcgNext() / 1000) % 50) - 25.0) / 5.0;
            sp90.y = ((f64)(u32)((randomLcgNext() / 1000) % 50) - 25.0) / 5.0;
            sp90.z = ((f64)(u32)((randomLcgNext() / 1000) % 50) - 25.0) / 5.0;
        }
        if (sub->unkD == 0) {
            tagBarrelDespawnEffects();
            if (sub->unkA != 0) {
                sp8A = func_8073195C(sub->unkA);
            } else {
                sp8A = -1;
            }
            kong = tagBarrelGetKongType();
            switch (D_8076A0A8) {
            case 0xBC:
                flagSet(0x28, 1, 2);
                break;
            case 0xBA:
                flagSet(0x32, 1, 2);
                break;
            default:
                yOffset = -8.0f;
                if (D_8076A0A8 == 0xAD) {
                    yOffset = -10.0f;
                }
                actorSpawnNodeEntryScaled(0x2D, D_807FBB40->unk7C, D_807FBB40->unk80 + yOffset, D_807FBB40->unk84, 0, kong, sp8A, 0);
                sfxAllocateChannel(0x14, 1.0f);
                actorDespawn(D_807FBB40);
                break;
            }
        }
        break;
    case 20:
        for (i = 0; i < D_807FBDC4; i++) {
            if (D_807FBB70.unk258[i] == 1 && *D_807FBB70.unk278[i] == 0) {
                D_807FBB40->unk144 = 2;
                D_807FBB40->unk154 = 0x15;
                sfxAllocateChannel(0x28, 1.0f);
            }
        }
        break;
    case 21:
        D_807FBB40->unk128 += 0xA;
        if (D_807FBB40->unk128 >= 0xF1) {
            D_807FBB40->unk60 |= 0x8000;
            D_807FBB40->unk154 = 0;
        }
        break;
    case 30:
        sub->unkD--;
        if (sub->unkD == 0) {
            D_807FBB40->unk144 = 2;
            D_807FBB40->unk154 = 0;
        }
        break;
    }
    if (D_807FBB40->unk154 != 0x14) {
        func_8065D254(D_807FBB40, 0x3C8, 0x40, 0x40, 0xC, 0xC, 1, 0x64, 0x78, 0, 1.0f);
    }
    D_807FBB40->unkE6 += 0x50;
    D_807FBB40->unk80 = (func_80612794(sub->unk4) * 5.0) + (f64)sub->unk0;
    sub->unk4 += 0x3C;
    guTranslateF((f32 (*)[4])((u8 *)D_807FBB40 + 0xC), sp90.x, sp90.y, sp90.z);
    actorUpdateModelMatrix(D_807FBB40, 1);
}


void func_80681B14(void) {
    TagBarrelState *sub = D_807FBB40->unk174;

    if (!(D_807FBB40->unk60 & 0x10)) {
        if (flagGet(0x302, 0) != 0) {
            actorDespawn(D_807FBB40);
            return;
        }
    }
    tagBarrelActorUpdate();
    if (D_807FBB40->unk154 == 0xC && sub->unkD < 3) {
        flagSet(D_8074E7E0[sub->unkA], 1, 2);
        tagBarrelDespawnEffects();
        actorDespawn(D_807FBB40);
    }
}

void func_80681BD8(void) {
    TagBarrelState *sub = D_807FBB40->unk174;
    s32 sp28;
    s32 count;
    s32 i;

    tagBarrelActorUpdate();
    if (flagGet(0x17F, 0) == 0) {
        D_807FBB40->unk154 = 0x14;
        D_807FBB40->unk144 = 1;
        D_807FBB40->unk60 &= ~0x8000;
        D_807FBB40->unk128 = 0;
    } else {
        if (flagGet(0x187, 0) == 0) {
            count = 0;
            if (D_807FBB40->unk154 == 0xB) {
                i = 0;
                do {
                    count += (flagGet((s16)(i + 0x182), 0) != 0);
                } while (++i != 4);
                if (count == 4) {
                    camStartPath(D_807FBB4C, 3, 1);
                    flagSet(0x187, 1, 0);
                }
            }
        }
        switch (sub->unk6) {
        case 0xB1:
            sp28 = 0x182;
            break;
        case 0xB6:
            sp28 = 0x183;
            break;
        case 0xB4:
            sp28 = 0x184;
            break;
        case 0xB5:
            sp28 = 0x185;
            break;
        }
        if (flagGet(sp28, 0) != 0) {
            sub->unkC_b = 1;
            sub->unkA = 0;
            if (D_807FBB40->unk154 == 0) {
                D_807FBB40->unk154 = 0x14;
                D_807FBB40->unk144 = 1;
                D_807FBB40->unk60 &= ~0x8000;
                D_807FBB40->unk128 = 0;
            }
        } else if (D_807FBB40->unk154 == 0x14) {
            D_807FBB40->unk144 = 2;
            D_807FBB40->unk154 = 0x15;
        }
    }
    if (D_807FBB40->unk154 == 0xC && sub->unkD < 3) {
        tagBarrelDespawnEffects();
        actorDespawn(D_807FBB40);
    }
}

typedef struct RocketbarrelState {
    s16 unk0;
    s16 pad2;
    Actor *unk4;
} RocketbarrelState;

typedef struct PlayerStateD580Grab {
    u8 pad0[0x1A3];
    u8 unk1A3;
} PlayerStateD580Grab;

extern u8 D_807FC950[][0x5E];
extern s16 D_80750390;

void sfxAllocateChannel(s32, f32);
void slotQueueUpdate(s32, u8, s32);
void func_806C7BAC(void *, Actor *);

void rocketbarrelUpdate(void) {
    RocketbarrelState *var_v1;
    s32 pad[3];

    var_v1 = (RocketbarrelState *)D_807FBB40->unk174;
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unkA4 = 99999.0f;
        collisionCheckGroundAtPoint(D_807FBB40->unk7C, D_807FBB40->unk84, &D_807FBB40->unkA4);
        if (1 == *(s32 *)D_807FBB40->unk124) {
            if (func_8067B450(D_807FBB40) == 0) {
                D_807FBB40->unk154 = 0x14;
                D_807FBB40->unk144 = 1;
                D_807FBB40->unk60 &= ~0x8000;
                D_807FBB40->unk128 = 0;
            }
        }
    }
    if ((D_807FBB40->unk154 == 0) && (D_807FBB70.unk200 == 4)) {
        var_v1->unk0 = 0xA;
        D_807FBB40->unk154 = 1;
        D_807FBB40->unk144 = 1;
        var_v1->unk4 = (Actor *)D_807FBB70.unk1FC;
        D_807FBB40->unk60 |= 0x200000;
        if ((D_8076A0A8 == 0x11) || (D_8076A0A8 == 0xC9) || (D_8076A0A8 == 0xCC)) {
        } else {
            sfxAllocateChannel(0x48, 1.0f);
        }
    }
    switch (D_807FBB40->unk154) {
    case 0: {
        s32 sp44;
        if (D_8074E77C < 5) {
            sp44 = D_807FC950[D_8074E77C][0];
        }
        if (((Actor *)D_807FBB4C)->unk58 == 3 && sp44 >= 2) {
            D_807FBB40->unk60 |= 0x8000;
            D_807FBB40->unk132 = 1;
        } else {
            D_807FBB40->unk60 &= ~0x8000;
            D_807FBB40->unk128 = 0x78;
            D_807FBB40->unk132 = 2;
        }
        func_8065D254(D_807FBB40, 0x3C8, 0x40, 0x40, 0xC, 0xC, 1, 0x64, 0x78, 0, 1.0f);
        break;
    }
    case 1:
        var_v1->unk0--;
        if (var_v1->unk0 == 0) {
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x1C6, 0xFF, 0x7F, 0);
            D_807FBB40->unk154 = 2;
            slotQueueUpdate(5, (D_807FBB68 & 2) ? 0 : 1, 0);
        }
        break;
    case 2:
        tagBarrelDespawnEffects();
        D_807FBB40->unk60 &= ~0x8000;
        D_807FBB40->unk128 = 0;
        actorAppendCallback(var_v1->unk4, (s32)D_807FBB40, 0x40, 1, 0, 0);
        func_8067AAB8((s32)D_807FBB40, var_v1->unk4, var_v1->unk4->unkE6, (f32) D_80750390, 0);
        func_806C7BAC(var_v1->unk4, D_807FBB40);
        ((PlayerStateD580Grab *)D_807FD580)->unk1A3 = 1;
        D_807FBB40->unk154 = 3;
        break;
    case 3:
        if (D_807FBB70.unk0 != 0) {
            D_807FBB40->unk60 |= 0x8000;
            D_807FBB40->unk144 = 2;
            D_807FBB40->unk60 &= ~0x200000;
            D_807FBB40->unk154 = 0;
        }
        break;
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
        break;
    case 20: {
        s16 i;
        for (i = 0; i < D_807FBB70.unk254; i++) {
            if (D_807FBB70.unk258[i] == 1) {
                D_807FBB40->unk144 = 2;
                D_807FBB40->unk154 = 0x15;
            }
        }
        break;
    }
    case 21:
        D_807FBB40->unk128 += 10;
        if (D_807FBB40->unk128 >= 0xF1) {
            D_807FBB40->unk60 |= 0x8000;
            D_807FBB40->unk154 = 0;
        }
        break;
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

typedef struct CannonState {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    Actor *unk4;
    s16 unk8;
} CannonState;

typedef struct CannonCamHolder {
    u8 pad0[0x104];
    void *unk104;
} CannonCamHolder;

typedef struct CannonPlayerView {
    u8 pad0[0x210];
    f32 unk210;
    f32 unk214;
    f32 unk218;
    u8 pad21C[0xC];
    f32 unk228;
    f32 unk22C;
    f32 unk230;
} CannonPlayerView;

extern f32 D_8074E7F4;
extern f32 D_8074E7F8;
extern f32 D_8074E7FC;
extern f32 D_8074E800;
extern f32 D_8074E804;
extern f32 D_8074E808;
extern u8 D_8074E810;
extern s8 D_807FD63E;
extern s8 D_807FD63F;

f32 cosApprox(f32);
f32 func_80611BB4(f32, f32);
void csModelStateSetFirstByte(s16, s16);
void hudSpawnCountdownTimer(s32, s32, u8);
void actorSetStateTwo(Actor *);
s32 actorCountOwnedByClass(Actor *, s32, s32);
void func_806CFF9C(Actor *);
void projectileSetTargetCoords(f32, f32, f32);
void projectileSpawnNodeEntry(s16, s16, f32, s16, f32, f32, s32);
Gfx *func_806FEF7C(Gfx *, Actor *);
Gfx *renderRemainingShotsHUD(Gfx *, u8 *);

void cannonUpdate(void) {
    CannonState *sub = D_807FBB40->unk174;
    void *cam;
    f32 sinOff;
    f32 cosOff;
    s32 i;
    u8 resetFlag = 0;
    u8 latchFlag = 0;
    Actor *child;
    f32 x;
    f32 y;
    f32 pitch;
    f32 sinV;
    f32 z;
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk132 = 1;
        sub->unk2 = 0;
        sub->unk8 = 0;
        sub->unk1 = 0;
        sub->unk3 = 0;
    }
    if (D_807FBB40->unk154 == 2 || D_807FBB40->unk154 == 3) {
        if (D_8074E7FC && D_8074E7FC) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        cam = ((CannonCamHolder *)sub->unk4->unk174)->unk104;
        sub->unk8 = sub->unk8 - (f64)D_807FD63E * 0.08 * D_8074E7F8 * 4096.0 / 360.0;
        sub->unk8 = sub->unk8 & 0xFFF;
        sinOff = func_80612794(sub->unk8) * D_8074E7F4;
        cosOff = func_80612790(sub->unk8) * D_8074E7F4;
        D_8074E804 = D_8074E804 - (f64)D_807FD63F * 0.04 * D_8074E800;
        if (D_8074E804 > 50.0) {
            D_8074E804 = 50.0f;
        }
        if (D_8074E804 < -50.0) {
            D_8074E804 = -50.0f;
        }
        x = D_807FBB40->unk7C;
        z = D_807FBB40->unk84;
        if (D_8074E7F8 && D_8074E7F8) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        y = D_807FBB40->unk80 + D_8074E7FC;
        camSetFixedView((s32)cam, x, y, z, x + sinOff, y + D_8074E804, z + cosOff, 0);
        if (camIsCutsceneActive() == 0) {
            renderCallbacksRegister(func_806FF01C, D_807FBB4C, 3);
            renderCallbacksRegister(func_806FEF7C, D_807FBB4C, 3);
        }
        func_8066E6C8(D_807FBB40, 0, 0);
    } else {
        func_8066E6C8(D_807FBB40, 0, 1);
    }
    if (sub->unk2 != 0) {
        renderCallbacksRegister(renderRemainingShotsHUD, sub, 3);
    }
    child = (Actor *)D_807FBB40->unk11C;
    if (child != 0 && sub->unk2 != 0 && child->unk154 == 5 && sub->unk1 == 0) {
        sub->unk1 = 0x1E;
    }
    if (sub->unk1 != 0) {
        sub->unk1--;
        if (sub->unk1 == 0) {
            resetFlag = 1;
        }
    }
    for (i = 0; i < D_807FBB70.unk254; i++) {
        if (D_807FBB70.unk258[i] == 1) {
            latchFlag = 1;
            sub->unk3 = 1;
        }
    }
    if (resetFlag != 0 || latchFlag != 0) {
        sub->unk2 = 0;
        if (D_807FBB40->unk154 == 2 || D_807FBB40->unk154 == 3) {
            D_807FBB40->unk154 = 3;
        } else {
            D_807FBB40->unk154 = 0;
            D_807FBB40->unk144 = 2;
        }
        child = (Actor *)D_807FBB40->unk11C;
        if (child != 0) {
            actorDespawn(child);
            D_807FBB40->unk11C = 0;
        }
        if (resetFlag) {
            csModelStateSetFirstByte(0x30, 0);
            csModelStateSetFirstByte(0x2F, 0);
            csModelStateSetFirstByte(0x31, 0);
        }
    }
    switch (D_807FBB40->unk154) {
    case 0:
        D_807FBB40->unk132 = 1;
        if (D_807FBB70.unk200 == 5 && sub->unk3 == 0) {
            D_807FBB40->unk154 = 1;
            D_807FBB40->unk132 = 2;
        }
        break;
    case 1:
        if (D_807FBB70.unk200 == 4) {
            D_807FBB40->unk154 = 2;
            sub->unk0 = 6;
            sub->unk4 = (Actor *)D_807FBB70.unk1FC;
            if (sub->unk2 == 0) {
                csModelStateSetFirstByte(0x30, 0xA);
                sub->unk2 = 1;
                hudSpawnCountdownTimer(0xC8, 0x20, D_8074E810);
                actorSetStateTwo(D_807FBB44);
                D_807FBB40->unk60 |= 0x200000;
            }
            D_807FBB40->unk60 &= ~4;
            D_807FBB40->unk144 = 1;
        }
        break;
    case 2:
        if ((D_807FD63C & 0x2000) && actorCountOwnedByClass(D_807FBB40, 4, 0) == 0 && sub->unk0 != 0) {
            projectileSetTargetCoords(D_807FBB40->unk7C, D_807FBB40->unk80 + D_8074E7FC, D_807FBB40->unk84);
            x = ((CannonPlayerView *)D_807FC924)->unk230 - ((CannonPlayerView *)D_807FC924)->unk218;
            y = ((CannonPlayerView *)D_807FC924)->unk228 - ((CannonPlayerView *)D_807FC924)->unk210;
            pitch = func_80611BB4(((CannonPlayerView *)D_807FC924)->unk22C - ((CannonPlayerView *)D_807FC924)->unk214, sqrtf(x * x + y * y));
            sinV = sinApprox(pitch) * D_8074E808;
            y = cosApprox(pitch) * D_8074E808;
            projectileSpawnNodeEntry(0x4A, 0, 0.6f, sub->unk8, y, sinV, (s32)D_807FBB40);
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x17, 0xFF, 0x7F, 0x19);
            sub->unk0--;
            if (sub->unk0 == 0) {
                D_807FBB40->unk154 = 3;
            }
        }
        break;
    case 3:
        if (actorCountOwnedByClass(D_807FBB40, 4, 0) == 0) {
            actorAppendCallback(sub->unk4, (s32)D_807FBB40, 0x40, 1, 0, 0);
            func_8067A70C(D_807FBB40, sub->unk4, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84 - 42.0f, 2, 1);
            sub->unk4->unk60 &= ~8;
            func_806CFF9C(sub->unk4);
            D_807FBB40->unk60 |= 4;
            D_807FBB40->unk154 = 0;
            D_807FBB40->unk144 = 2;
        }
        break;
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

typedef struct TagBarrelOrbitKong {
    u8 pad0[4];
    u16 unk4;
    s8 unk6;
    s8 unk7;
    Actor *unk8[5];
    Actor *unk1C;
    s8 unk20;
} TagBarrelOrbitKong;


#ifdef NON_MATCHING
void func_80682AB4(void *arg0) {
    TagBarrelOrbitKong *arg = (TagBarrelOrbitKong *)arg0;
    f32 sp70 = D_807FBB40->unk7C;
    f32 sp6C = D_807FBB40->unk80 - 10.0f;
    f32 sp68 = D_807FBB40->unk84;
    s32 var_s1;
    f32 temp_fs1;
    f32 var_fv0;
    f32 var_fv1;
    s16 temp_s5;
    s16 temp_t0;
    u8 *var_s3;
    Actor *temp_s2;

    temp_fs1 = (f32)(u32)arg->unk4 / 20.0f;
    temp_s5 = D_807FBB40->unkE6;
    temp_s5 = (s16)(s32)(temp_s5 + (819.2 * arg->unk6)) & 0xFFF;
    temp_s5 = (s16)(s32)(temp_s5 - (819.2 * temp_fs1) * arg->unk20) & 0xFFF;
    temp_s5 = (s16)(s32)temp_s5 & 0xFFFF; // FAKE: redundant narrowing burns ugen ring temps (loop-start register ring)
    var_s1 = 0;
    var_s3 = (u8 *)arg0;
    do {
        temp_s2 = *(Actor **)(var_s3 + 8);
        temp_t0 = (s16)((s32)(4096.0 - (var_s1 * 819.2)) + temp_s5) & 0xFFF;
        temp_s2->unk7C = (func_80612794(temp_t0) * 45.0f) + sp70;
        temp_s2->unk84 = (func_80612790(temp_t0) * 45.0f) + sp68;
        var_s3 += 4;
        temp_s2->unk80 = sp6C;
        if (var_s1 == arg->unk6) {
            var_fv0 = 1.0f - temp_fs1;
        } else if (var_s1 == arg->unk7) {
            var_fv0 = temp_fs1;
        } else {
            var_fv0 = 0;
        }
        var_fv0 = (f64)var_fv0 - 0.6;
        var_s1++;
        var_fv0 = (f64)var_fv0 * 2.5;
        if (var_fv0 < 0) {
            var_fv0 = 0.0f;
        } else {
            if (var_fv0 > 1.0f) {
                var_fv1 = 1.0f;
            } else {
                var_fv1 = var_fv0;
            }
            var_fv0 = var_fv1;
        }
        temp_s2->unk15F = (u32)((12.0f * var_fv0) + 3.0f);
    } while (var_s1 != 5);
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/80150/func_80682AB4.s")
#endif

void func_80682DF4(void *arg0, u16 *arg1, s32 arg2) {
    arg2 = arg2 * 7;
    arg2 += *arg1 - 2;
    actorScriptStart(arg0, D_807FBB54[arg2], arg2);
}

typedef struct TagBarrelSpawnArgs {
    u8 pad0[6];
    s8 unk6;
    u8 pad7;
    Actor *unk8[5];
    Actor *unk1C;
} TagBarrelSpawnArgs;

typedef struct KongActionEntry {
    s16 unk0;
    s16 unk2;
    u8 unk4;
    u8 unk5;
} KongActionEntry;

void func_806F09F0(Actor *, u16);
void func_80682AB4(void *);

void tagBarrelSpawnKongs(TagBarrelSpawnArgs *arg0) {
    s32 i;
    s32 actorType;
    s16 model;
    u16 *temp_s0;
    s32 var_a2;
    s32 flag = 0x40000000;
    actorSpawn(0x136, 0xA8);
    arg0->unk1C = D_807FBB44;
    D_807FBB44->unk7C = D_807FBB40->unk7C + func_80612794(D_807FBB40->unkE6) * 35.0f;
    D_807FBB44->unk80 = (D_807FBB40->unk80 - 10.0f) - 2.0f;
    D_807FBB44->unk84 = D_807FBB40->unk84 + func_80612790(D_807FBB40->unkE6) * 35.0f;

    for (i = 0; i < 5; i++) {
        if (flagGet(func_805FF018(D_807FBB40->unk58, i), 0)) {
            actorType = 0x13C;
            model = ((KongActionEntry *)D_8074E814)[i].unk0;
        } else {
            actorType = 0x13D;
            model = 0xD2;
        }
        actorSpawn(actorType, model);
        arg0->unk8[i] = D_807FBB44;
        D_807FBB44->unkE6 = D_807FBB40->unkE6;
        D_807FBB44->unk60 |= flag;
        if (actorType == 0x13C) {
            temp_s0 = D_807FBB44->unk174;
            *temp_s0 = ((KongActionEntry *)D_8074E814)[i].unk2;
            func_806F09F0(D_807FBB44, *temp_s0);
            var_a2 = (i == arg0->unk6) ? 0x8B : 0x8A;
            func_80682DF4(D_807FBB44, temp_s0, var_a2);
        } else {
            u8 *temp = D_807FBB44->unk174;
            *temp = i;
        }
    }
    func_80682AB4(arg0);
}

void tagBarrelUpdateSelectedKong(void) {
    ActorAnimLookup sp2C;
    u8 *sp28;

    if (!(D_807FBB40->unk60 & 0x10)) {
        sp2C = D_8074E834;
        sp28 = D_807FBB40->unk174;
        D_807FBB40->unk60 |= 0x1000;
        animSetLoopLimit(D_807FBB40, 0, 1);
        animSetFinished(D_807FBB40, 0, 1);
        animSetFrameAndSubframe(D_807FBB40, 0, sp2C.arr[*sp28].unk2, 0.0f);
        actorScriptStart(D_807FBB40, 0x329);
    }
    D_807FBB40->unk16D = D_807FBB40->unk15F;
    D_807FBB40->unkE6 += 0x32;
    D_807FBB40->unkE6 &= 0xFFF;
    actorUpdateModelMatrix(D_807FBB40, 0);
}

typedef struct ActorExtra3158 {
    u16 unk0;
    u16 pad2;
    void (*unk4)(Actor *, void *, s32 *);
    u8 unk8[1];
} ActorExtra3158;

typedef struct ActorSub4View3158 {
    u8 pad0[0x1C];
    void *unk1C;
} ActorSub4View3158;

typedef struct ActorView3158 {
    u8 pad0[0xC0];
    f32 unkC0;
    u8 padC4[0x146 - 0xC4];
    s16 unk146;
    u8 pad148[0x168 - 0x148];
    s16 unk168;
    u8 pad16A[0x178 - 0x16A];
    void *unk178;
} ActorView3158;


void heapClearBlock(void *);
void func_806C8220(s32, void *, u16);
void func_806F1C04(Actor *, void *, s32 *);
void func_806F22A8(Actor *, void *, s32 *);
void func_806F1EB0(Actor *, void *, s32 *);
s32 mathAngleBetweenPoints2D(f32, f32, f32, f32);
s32 func_8072881C(s32, void *);

void func_80683158(void) {
    s32 sp3C;
    ActorExtra3158 *extra;
    u8 *extra8;

    sp3C = 0;
    extra = D_807FBB40->unk174;
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk60 |= 0x1000;
        ((ActorSub4View3158 *)D_807FBB40->unk4)->unk1C = heapAlloc(0x100);
        heapClearBlock(((ActorSub4View3158 *)D_807FBB40->unk4)->unk1C);
        func_806C8220(0, ((ActorView3158 *)D_807FBB40)->unk178, extra->unk0);
        switch (extra->unk0) {
        case 2:
            extra->unk4 = func_806F1C04;
            break;
        case 3:
            extra->unk4 = func_806F22A8;
            break;
        case 5:
            extra->unk4 = func_806F1EB0;
            break;
        }
    } else {
        if (extra->unk4 != NULL) {
            extra->unk4(D_807FBB40, ((ActorSub4View3158 *)D_807FBB40->unk4)->unk1C, &sp3C);
        }
    }
    *((u8 *)((ActorSub4View3158 *)D_807FBB40->unk4)->unk1C + sp3C * 8) = 0;
    D_807FBB40->unk16D = D_807FBB40->unk15F;
    D_807FBB40->unkE6 = mathAngleBetweenPoints2D(D_807FC924->unk210, D_807FC924->unk218, D_807FBB40->unk7C, D_807FBB40->unk84);
    extra8 = extra->unk8;
    if (func_8072881C(0, extra8) != 0) {
        if (extra->unk0 == 3 || extra->unk0 == 5) {
            func_8072881C(0x81, extra8);
        }
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

s32 func_805FEF10(void *);

s32 tagBarrelCheckKongFlag(s32 arg0, s32 arg1) {
    struct KongFlagInfo {
        char unk0[2];
        s16 unk2;
        s32 unk4;
        s32 unk8;
        s32 unkC;
    } sp20;
    struct KongFlagInfo *p = &sp20;
    s32 ret;

    sp20.unk4 = 0;
    switch (D_8076A0A8) {
    default:
        return 0;
    case 7:
    case 26:
    case 30:
    case 38:
    case 42:
    case 48:
        sp20.unk8 = func_805FEF10(&sp20);
        if (sp20.unk8 != 0) {
            sp20.unk4 = flagGet(sp20.unk2, 0);
            if (arg1 != 0 && sp20.unk4 == 0) {
                flagSet(sp20.unk2, 1, 0);
                camStartPath(D_807FBB4C, 0x19, 4);
                D_807FBB40->unk144 = 1;
                D_807FBB40->unk155[0] = 0xB;
            }
        }
        ret = p->unk8 != 0; // FAKE: no explicit return: ret/v0 web, operands read via ilod p
        if (ret != 0) {
            return p->unk4 == 0;
        }
    }
}

typedef struct TagBarrelDataN3 {
    /* 0x00 */ Actor *unk0;
    /* 0x04 */ u16 unk4;
    /* 0x06 */ s8 unk6;
    /* 0x07 */ s8 unk7;
    /* 0x08 */ Actor *unk8[5];
    /* 0x1C */ Actor *unk1C;
    /* 0x20 */ s8 unk20;
    /* 0x21 */ u8 pad21;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ u8 pad2A[2];
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ s16 unk38;
    /* 0x3A */ u8 pad3A[2];
    /* 0x3C */ u32 unk3C;
} TagBarrelDataN3;

typedef struct TagBarrelKongSub {
    u8 pad0[0x104];
    Actor *unk104;
    u8 pad108[0x1F0 - 0x108];
    s32 unk1F0;
} TagBarrelKongSub;

typedef struct TagBarrelActorKong {
    u8 pad0[0x5A];
    s16 unk5A;
    u8 pad5C[0x12C - 0x5C];
    s16 unk12C;
} TagBarrelActorKong;

struct TagBarrelData;
extern s32 D_8074E848[];
extern s32 D_807FBB60;

void func_806C93E4(Actor *, void *);
void func_806C9304(Actor *, void *);
void lightGetColor(f32 *, f32 *, f32 *, s16);
void lightSetColor(f32, f32, f32, s32);
void sfxSetChannelParam(s32, s32, s32);
void camSaveYaw(Actor *);
void eepromSavePlayerData(void);
void func_8061B650(Actor *);
void slotQueueClearAllFlags(void);

void tagBarrelStartSelection(struct TagBarrelData *arg0_in) {
#define arg0 ((TagBarrelDataN3 *)arg0_in)
    TagBarrelActorKong *kong;
    f32 dummy;
    Actor *sp34;
    TagBarrelKongSub *sp30;
    s32 sp28_pad; // FAKE: unused home keeps sp28's spill slot below the switch temp (frame 0x40)
    s32 sp28;

    switch (D_807FBB40->unk155[0]) {
    case 0xB:
        if (camIsCutsceneActive() == 0) {
            D_807FBB40->unk144 = 2;
            D_807FBB40->unk155[0] = 0;
        }
        break;
    case 0:
    case 0xA:
        if (D_807FBB70.unk200 == 4) {
            arg0->unk0 = (Actor *)D_807FBB70.unk1FC;
            arg0->unk0->unk144 = 1;
            ((TagBarrelKongSub *)arg0->unk0->unk174)->unk1F0 |= 0x20000000;
            D_807FBB40->unk155[0] = 1;
            arg0->unk4 = 2;
            arg0->unk3C = 0;
        }
        break;
    case 1:
        if (arg0->unk4 != 0) {
            arg0->unk4--;
        } else {
            sp34 = arg0->unk0;
            sp28 = ((TagBarrelActorKong *)sp34)->unk12C;
            sp30 = sp34->unk174;
            if (sp28 == -1) {
                sp28 = 0;
            }
            func_806C93E4(arg0->unk0, sp30);
            func_806C9304(arg0->unk0, sp30);
            lightGetColor(&arg0->unk2C, &arg0->unk30, &arg0->unk34, (s16)sp28);
            kong = (TagBarrelActorKong *)sp34;
            lightSetColor(dummy = 1.0f, 1.0f, 1.0f, (s16)sp28);
            D_807FBB40->unkE6 = arg0->unk22;
            D_807FBB40->unk144 = 1;
            sp28 = kong->unk5A;
            D_807FBB60 &= 0xFFFCFFCF;
            arg0->unk6 = 0;
            if (sp28 != ((KongActionEntry *)D_8074E814)[arg0->unk6].unk2) {
                do {
                    arg0->unk6++;
                } while (sp28 != ((KongActionEntry *)D_8074E814)[arg0->unk6].unk2);
            }
            arg0->unk7 = arg0->unk6;
            if (D_8076A0A8 != 0x11) {
                sfxAllocateChannel(0x65, 1.0f);
                sfxSetChannelParam(0x65, 0x7E - D_8074E848[arg0->unk6], 1);
            }
            flagSet(func_805FF018(D_807FBB40->unk58, arg0->unk6), 1, 0);
            tagBarrelSpawnKongs((TagBarrelSpawnArgs *)arg0);
            camSaveYaw(sp30->unk104);
            arg0->unk38 = sp34->unkE6;
            sp34->unkE6 = D_807FBB40->unkE6;
            eepromSavePlayerData();
            camStartPath(D_807FBB40, 0xE, 0xC);
            func_8061B650(sp30->unk104);
            slotQueueClearAllFlags();
            D_807FBB40->unk154 = 1;
            D_807FBB40->unk155[0] = 0;
        }
        break;
    }
#undef arg0
}

typedef struct TagBarrelInputPad {
    u8 pad0[0x2C];
    u16 unk2C;
    s8 unk2E;
    s8 unk2F;
    u8 unk30;
} TagBarrelInputPad;
extern TagBarrelInputPad D_807FD610;

typedef struct TagBarrelPlayerData {
    u8 pad0[0x2E2];
    u16 unk2E2;
} TagBarrelPlayerData;

typedef struct TagBarrelDataN4 {
    /* 0x00 */ Actor *unk0;
    /* 0x04 */ u16 unk4;
    /* 0x06 */ s8 unk6;
    /* 0x07 */ s8 unk7;
    /* 0x08 */ Actor *unk8[5];
    /* 0x1C */ Actor *unk1C;
    /* 0x20 */ s8 unk20;
    /* 0x21 */ u8 pad21;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ u8 pad2A[2];
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ s16 unk38;
    /* 0x3A */ u8 pad3A[2];
    /* 0x3C */ u32 unk3C;
} TagBarrelDataN4;

typedef struct TagBarrelKongSubState {
    u8 pad0[0x8C];
    u8 unk8C;
    u8 pad8D[0x104 - 0x8D];
    Actor *unk104;
    u8 pad108[0x1F0 - 0x108];
    u32 unk1F0;
} TagBarrelKongSubState;

typedef struct TagBarrelOrbitActor {
    u8 pad0[0x12C];
    s16 unk12C;
} TagBarrelOrbitActor;


s32 func_805FCA64(void);
s32 screenWipeGetState(void);
void screenWipeStart(s32);
void healthRefill(s32);
void sfxStopChannel(s32, s32);
void camRestoreYaw(Actor *);
void camResetPlayer(Actor *, s32);
void func_806C8E58(s16);
s32 sfxPlayOnFreeSlot(s32, s32, f32, f32, s32, s32);
struct TagBarrelData;

void tagBarrelUpdateSelection(struct TagBarrelData *arg0_in) {
    TagBarrelDataN4 *arg0 = (TagBarrelDataN4 *)arg0_in;
    u16 sp4A;
    s32 var_s0;
    s32 pad2;
    s32 pad[2];
    Actor *sp34;
    TagBarrelKongSubState *sp30;
    s32 light;
    s32 sp28;

    var_s0 = arg0->unk4;
    sp4A = var_s0;
    if (var_s0 != 0) {
        arg0->unk4 = var_s0 - 1;
        func_80682AB4(arg0);
        var_s0 = arg0->unk4;
    }
    arg0->unk3C++;
    if (var_s0 == 0 && func_805FCA64() != 0) {
        var_s0 = ((Actor *)arg0->unk8[arg0->unk6])->unk58 == 0x13C;
        sp28 = arg0->unk3C >= 9001;
        if (((D_807FD610.unk30 >= 0x29) && !sp28) || !var_s0) {
            arg0->unk4 = 20;
            if (((Actor *)arg0->unk8[arg0->unk6])->unk58 == 0x13C) {
                func_80682DF4(arg0->unk8[arg0->unk6], (u16 *)((Actor *)arg0->unk8[arg0->unk6])->unk174, 0x8C);
            }
            arg0->unk7 = arg0->unk6;
            if (var_s0) {
                arg0->unk20 = (D_807FD610.unk2E >= 0) ? 1 : -1;
            }
            arg0->unk6 += arg0->unk20;
            if (arg0->unk6 < 0) {
                arg0->unk6 = 4;
            } else if (arg0->unk6 >= 5) {
                arg0->unk6 = 0;
            }
            if (((Actor *)arg0->unk8[arg0->unk6])->unk58 == 0x13C) {
                func_80682DF4(arg0->unk8[arg0->unk6], (u16 *)((Actor *)arg0->unk8[arg0->unk6])->unk174, 0x8B);
            }
        } else {
            if (!sp28 && sp4A != 0) {
                sfxSetChannelParam(0x65, 0x7E - D_8074E848[arg0->unk6], 3);
                sfxSetChannelParam(0x65, D_8074E848[arg0->unk6], 2);
                return;
            }
            if (((sp28 && var_s0) || (D_807FD610.unk2C & 0xE000)) && screenWipeGetState() == 0) {
                if (var_s0) {
                    sp34 = arg0->unk0;
                    sp30 = sp34->unk174;
                    light = ((TagBarrelOrbitActor *)sp34)->unk12C;
                    if (light == -1) {
                        light = 0;
                    }
                    lightSetColor(arg0->unk2C, arg0->unk30, arg0->unk34, (s16)light);
                    D_807FBB60 |= 0x30030;
                    sfxStopChannel(0x48, 0);
                    sfxStopChannel(0x6B, 0);
                    sfxStopChannel(0x49, 0);
                    sfxStopChannel(0x47, 0);
                    sfxStopChannel(0x65, 0);
                    actorDespawn(arg0->unk1C);
                    arg0->unk1C = NULL;
                    for (sp28 = 0; sp28 < 5; sp28++) {
                        actorDespawn(arg0->unk8[sp28]);
                        arg0->unk8[sp28] = NULL;
                    }
                    D_807FBB40->unk154 = 2;
                    D_807FBB40->unk155[0] = 0;
                    arg0->unk4 = 30;
                    sp30->unk1F0 &= ~0x20000000;
                    var_s0 = ((KongActionEntry *)D_8074E814)[arg0->unk6].unk2;
                    func_806C8E58(var_s0);
                    func_806F09F0(sp34, var_s0);
                    *(u8 *)((u8 *)sp30 + 0x8C) = 0;
                    sp34->unkE6 = arg0->unk38;
                    camRestoreYaw(sp30->unk104);
                    camResetPlayer(sp34, 0);
                    screenWipeStart(3);
                    healthRefill(0);
                    ((TagBarrelPlayerData *)D_807FC924)->unk2E2 |= 0x11;
                    return;
                }
                sfxPlayOnFreeSlot(0x98, 0x7FFF, 63.0f, 1.0f, 0, 0);
            }
        }
    }
}

s32 tagBarrelIsKongUnlocked(ActorGroup5 *arg0, s32 arg1) {
    s32 type = arg0->unk8[arg1]->unk58;
    s32 ret = 0;

    if ((type ^ 0x13C) == 0) {
        ret = textTableGetString(2, D_8074E85C[arg1], 1);
    }
    return ret;
}

extern Gfx D_1000118;
extern Mtx D_20000C0;
extern Mtx D_2000180;
extern s16 D_80744490;
extern s16 D_80744494;

Gfx *renderRotatedSprite(Gfx *, u16, s32, s32, u8, u8, s16, s16, f32, f32, s32, f32);
Gfx *hudDrawScaledText(Gfx *, s16, s16, f32, s32);
u32 textGetFontHeight(s32);

Gfx *tagBarrelRenderSelectionHud(Gfx *arg0, Actor *arg1) {
    u8 padF8[0xC];
    f32 spF8;
    s32 pad244;
    f32 spF0;
    f32 temp_fa0_2;
    f32 temp_fa0_3;
    f32 temp_fa1;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;
    f32 temp_fv0_4;
    f32 temp_fv1;
    f32 temp_fv1_2;
    f32 var_fa0;
    f32 var_fa0_2;
    f32 var_fv0;
    f32 var_fv0_2;
    f32 var_fv1;
    f32 var_fv1_2;
    s32 temp_v0;
    TagBarrelDataN3 *temp_s1;
    s32 spX;
    u8 pad70[0x38];
    s32 sp6C;
    s16 sp44;

    temp_s1 = (TagBarrelDataN3 *)arg1->unk174;
    spF0 = (f32)((f64)(D_80744494 - 0x1E) * 4.0);
    if (arg1->unk154 != 1) {
        return arg0;
    }
    gSPDisplayList(arg0++, &D_1000118);
    gDPSetCombineMode(arg0++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gSPMatrix(arg0++, &D_20000C0, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(arg0++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    sp44 = (s16)(s32)spF0;
    arg0 = renderRotatedSprite(arg0, (u16)(((u32)(D_8076A064 >> 1) % 12) + 0x83), 0, 2, 0x20, 0x10, 0xA0, sp44, 5.0f, 5.0f, 0, 0.0f);
    arg0 = renderRotatedSprite(arg0, (u16)(((u32)(D_8076A064 >> 1) % 12) + 0x83), 0, 2, 0x20, 0x10, (s32)((f64)(D_80744490 - 0x28) * 4.0), sp44, 5.0f, 5.0f, 0xB4, 0.0f);
    spF8 = (f32)(u32)temp_s1->unk4 * 0.05f;
    sp6C = tagBarrelIsKongUnlocked((ActorGroup5 *)temp_s1, temp_s1->unk6);
    spF0 -= (f32) textGetFontHeight(1) * 1.2f;
    gDPSetCombineLERP(arg0++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
    if (sp6C != 0) {
        temp_fv0 = 1.0f - spF8;
        temp_fv1 = temp_fv0 * 0.5f;
        var_fa0 = temp_fv1;
        if (temp_s1->unk20 < 0) {
            var_fa0 = 1.0f - temp_fv1;
        }
        temp_fv1_2 = 2.0f * temp_fv0;
        var_fa0 *= (f32)D_80744490 * 4.0f;
        if (temp_fv1_2 < 1.0f) {
            var_fv0 = 0.0f;
        } else {
            temp_fv0_2 = temp_fv1_2 - 1.0f;
            if (temp_fv0_2 > 1.0f) {
                var_fv1 = 1.0f;
            } else {
                var_fv1 = temp_fv0_2;
            }
            var_fv0 = var_fv1;
        }
        var_fv0 *= 255.0f;
        gDPSetPrimColor(arg0++, 0, 0, 255, 255, 255, (u32)var_fv0);
        arg0 = hudDrawScaledText(arg0, (s16)(s32)var_fa0, (s16)(s32)spF0, 0.6f, sp6C);
    }
    if (temp_s1->unk4 != 0) {
        sp6C = tagBarrelIsKongUnlocked((ActorGroup5 *)temp_s1, temp_s1->unk7);
        if (sp6C != 0) {
            temp_fv0_3 = 0.5f * spF8;
            var_fa0_2 = temp_fv0_3;
            if (temp_s1->unk20 > 0) {
                var_fa0_2 = 1.0f - temp_fv0_3;
            }
            temp_fv0_4 = 2.0f * spF8;
            var_fa0_2 *= (f32)D_80744490 * 4.0f;
            if (temp_fv0_4 < 1.0f) {
                var_fv0_2 = 0.0f;
            } else {
                temp_fa1 = temp_fv0_4 - 1.0f;
                if (temp_fa1 > 1.0f) {
                    var_fv1 = 1.0f;
                } else {
                    var_fv1 = temp_fa1;
                }
                var_fv0_2 = var_fv1;
            }
            var_fv0_2 *= 255.0f;
            gDPSetPrimColor(arg0++, 0, 0, 255, 255, 255, (u32)var_fv0_2);
            arg0 = hudDrawScaledText(arg0, (s16)(s32)var_fa0_2, (s16)(s32)spF0, 0.6f, sp6C);
        }
    }
    return arg0;
}

void tagBarrelInitUnlockedKongs(Actor *arg0) {
    s32 i;

    for (i = 0; i < 5; i++) {
        if (flagGet(func_805FF018(arg0->unk58, i), 0)) {
            func_8068A764(arg0, D_8074E814[i].unk4);
        }
    }
}

typedef struct TagBarrelData {
    /* 0x00 */ Actor *unk0;
    /* 0x04 */ u16 unk4;
    /* 0x06 */ s8 unk6;
    /* 0x07 */ s8 unk7;
    /* 0x08 */ Actor *unk8[5];
    /* 0x1C */ Actor *unk1C;
    /* 0x20 */ s8 unk20;
    /* 0x21 */ u8 pad21;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ u8 pad2A[2];
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ s16 unk38;
    /* 0x3A */ u8 pad3A[2];
    /* 0x3C */ u32 unk3C;
} TagBarrelData;

extern u8 D_8071FC8C[];
void func_80714A28(s32);
s32 mapIsBossArena(void);
s32 func_806C9D7C(void);
s32 tagBarrelCheckKongFlag(s32, s32);
void tagBarrelStartSelection(TagBarrelData *);
void tagBarrelUpdateSelection(TagBarrelData *);
Gfx *tagBarrelRenderSelectionHud(Gfx *, Actor *);
void slotQueuePopActiveMask(void);

void tagBarrelUpdate(void) {
    Actor *actor = D_807FBB40;
    TagBarrelData *sub = actor->unk174;

    if (!(actor->unk60 & 0x10)) {
        sub->unk22 = actor->unkE6;
        sub->unk24 = D_807FBB40->unk80;
        *(s16 *)&D_807FBB40->unk145[1] = 0;
        D_807FBB40->unk15E = 0;
        func_80714998(2);
        func_807149FC(-1);
        func_807149B8(1);
        func_807149A8(0x3E8);
        func_80714A28(4);
        actor = D_807FBB40;
        func_80714CC0(&D_8071FC8C, 1.3f, actor->unk7C, (f32)((f64)actor->unk80 + 13.0), actor->unk84);
        if (mapIsBossArena()) {
            D_807FBB40->unk12A = 0x7D0;
        } else {
            D_807FBB40->unk12A = 0x15E;
        }
        actor = D_807FBB40;
        actor->unkA4 = actor->unk80;
        actorUpdateFloorContactAndTilt(D_807FBB40, 0.0f);
        D_807FBB40->unk110 = 0;
        actor = D_807FBB40;
        actor->unk60 |= 2;
        actor = D_807FBB40;
    }
    tagBarrelInitUnlockedKongs(actor);
    tagBarrelUpdateInteractable();
    func_8067ACB4(D_807FBB40);
    actor = D_807FBB40;
    switch (actor->unk154) {
    case 0:
        if (sub->unk4 != 0) {
            sub->unk4--;
            if (sub->unk4 == 0) {
                D_807FBB40->unk144 = 2;
            }
        } else {
            tagBarrelStartSelection(sub);
        }
        actor = D_807FBB40;
        if (actor->unk155[0] == 0xA) {
            if (((Actor *)D_807FBB4C)->unk6A & 4 || func_806C9D7C() != 0) {
                actor = D_807FBB40;
                actor->unk155[0] = 0;
            } else if (((Actor *)D_807FBB4C)->unk110 != 1 && (((Actor *)D_807FBB4C)->unk6A & ((Actor *)D_807FBB4C)->unk6C & 1)) {
                tagBarrelCheckKongFlag(((Actor *)D_807FBB4C)->unk58, 1);
            }
        }
        actor = D_807FBB40;
        break;
    case 1:
        tagBarrelUpdateSelection(sub);
        renderCallbacksRegister(tagBarrelRenderSelectionHud, D_807FBB40, 3);
        actor = D_807FBB40;
        break;
    case 2:
        if (sub->unk4 != 0) {
            sub->unk4--;
        } else {
            func_8067AAB8((s32)actor, sub->unk0, sub->unk38, 180.0f, 0x46);
            actorAppendCallback(sub->unk0, (s32)D_807FBB40, 0x40, 1, 0, 0);
            slotQueuePopActiveMask();
            D_807FBB40->unk154 = 0;
            D_807FBB40->unk155[0] = 0;
            if (tagBarrelCheckKongFlag(((Actor *)D_807FBB4C)->unk58, 0) != 0) {
                D_807FBB40->unk155[0] = 0xA;
            }
            sub->unk4 = 0x1E;
        }
        actor = D_807FBB40;
        break;
    }
    func_8065D254(actor, 0x3C8, 0x40, 0x40, 0x1E, 0x1E, 1, 0x64, 0x78, 0, 1.0f);
    actor = D_807FBB40;
    if (actor->unk154 != 1) {
        actor->unkE6 += 0x32;
        actor = D_807FBB40;
        actor->unkE6 &= 0xFFF;
        D_807FBB40->unk80 = func_80612794(sub->unk28) * 5.0f + sub->unk24;
        sub->unk28 += 0x32;
        sub->unk28 &= 0xFFF;
        actor = D_807FBB40;
    }
    actorUpdateModelMatrix(actor, 0);
}

void func_806844EC(void) {
    tagBarrelUpdate();
}

void func_8068450C(void) {
    tagBarrelUpdate();
}

void func_8068452C(void) {
    tagBarrelUpdate();
}

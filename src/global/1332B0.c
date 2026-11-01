#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB4C;
extern ActorGlobalState D_807FBB70;
extern void *gPlayerSlots;

u8 func_8072E5B0(void) {
    Actor *a = D_807FBB4C;

    return !(a->unk6A & 1) && !(a->unk110 == 1) && !(a->unk154 == 0x63);
}

typedef struct {
    /* 0x00 */ u8 b[0x38];
} VolumeTriggerRaw;

typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ u8 unkC;
    /* 0x0D */ u8 unkD;
    /* 0x0E */ u8 unkE;
    /* 0x0F */ u8 padF;
    /* 0x10 */ struct { s16 unk0; u8 unk2[8]; } subs[4];
    /* 0x38 */ u8 unk38;
    /* 0x39 */ u8 unk39;
} VolumeTrigger; // size = 0x3A

typedef struct {
    /* 0x00 */ s16 count;
    /* 0x04 */ VolumeTrigger *entries;
} VolumeTriggerTable;

extern VolumeTriggerTable *D_80755A14;
void *heapAlloc(s32);

void volumeTriggerTableLoad(s16 *arg0) {
    VolumeTriggerRaw *src;
    VolumeTrigger *e;
    s16 i;

    D_80755A14->count = 0;
    D_80755A14->entries = NULL;
    if (arg0 != NULL) {
        src = (VolumeTriggerRaw *)(arg0 + 1);
        i = 0;
        D_80755A14->count = *arg0;
        while (i < D_80755A14->count) {
            if (i == 0) {
                D_80755A14->entries = heapAlloc(D_80755A14->count * 0x3A);
                e = D_80755A14->entries;
            } else {
                e++;
            }
            *(VolumeTriggerRaw *)e = *src;
            e->unk38 = 0;
            e->unk39 = e->unkD;
            i++;
            src++;
        }
    }
}

typedef struct {
    /* 0x00 */ u8 pad0[2];
    /* 0x02 */ s16 unk2;
    /* 0x04 */ u8 pad4[3];
    /* 0x07 */ u8 unk7;
    /* 0x08 */ Actor *unk8;
    /* 0x0C */ s32 (*unkC)(void);
} VolumeTriggerHook; // size = 0x10

extern VolumeTriggerHook D_807557A0[];
void *assetLoad(s32, s32, s32, s32);
s32 assetFreeBuffer(void *, s32, s32);
s32 actorFindActiveByType(s16, Actor **);

void volumeTriggerTableInit(s32 arg0) {
    VolumeTriggerHook *p;
    s32 i;
    s32 n = 0x27;
    s32 ua0;
    s32 ua1;
    Actor *sp30;
    void *buf;

    buf = assetLoad(0x12, arg0, 1, 0);
    volumeTriggerTableLoad(buf);
    if (buf != NULL) {
        assetFreeBuffer(buf, 0xC1, 0x3D);
    }
    p = D_807557A0;
    for (i = 0; i < n; i++, p++) {
        actorFindActiveByType(p->unk2, &sp30);
        p->unk8 = sp30;
    }
}

typedef struct {
    /* 0x0 */ Actor *actor;
    /* 0x4 */ s32 unk4;
} ActiveActorEntry;

extern ActiveActorEntry gActiveActors[];
extern u16 gActiveActorCount;

s32 actorFindActiveByType(s16 arg0, Actor **arg1) {
    s32 found = 0;
    s32 i = 0;
    Actor *actor;

    if (i) {
    }
    if (gActiveActorCount > 0) {
        do {
            actor = gActiveActors[i].actor;
            if (actor->unk58 == (arg0 & 0xFFFFFFFFu)) {
                found = 1;
            } else {
                i++;
            }
        } while (!found && i < gActiveActorCount);
    }
    *arg1 = actor;
    return found;
}

extern u8 D_807FBDC4;
extern s16 D_807FDCB8;
extern s16 D_807FDCBA;
extern s16 D_807FDCBC;
void func_8067AB20(void *, void *, s32, s32, void *, s32);
s32 volumeTriggerUpdate(VolumeTrigger *);
void volumeTriggerSetEnabled(s32, u8);

typedef struct {
    s16 unk0;
    u8 unk2[8];
} VolumeTriggerSubView;

void volumeTriggerUpdateAll(void) {
    s32 ua0;
    s32 ua1;
    s32 i;
    VolumeTrigger *e;
    s16 *ptr;
    s32 j;
    s32 flag;
    s32 k;
    VolumeTriggerSubView *sub;

    for (k = 0; k < D_807FBDC4; k++) {
        ptr = D_807FBB70.unk278[k];
        switch (D_807FBB70.unk258[k]) {
            case 1:
                volumeTriggerSetEnabled(*ptr, 1);
                break;
            case 2:
                volumeTriggerSetEnabled(*ptr, 0);
                break;
        }
    }
    e = D_80755A14->entries;
    for (i = 0; i < D_80755A14->count; i++, e++) {
        if (volumeTriggerUpdate(e)) {
            for (j = 0; j < e->unkE; j++) {
                sub = (VolumeTriggerSubView *)&e->subs[j];
                if (D_807557A0[e->subs[j].unk0].unkC == NULL || D_807557A0[e->subs[j].unk0].unkC()) {
                    flag = (u16)D_807557A0[sub->unk0].unk2 == 0xA ? 1 : 0;
                    func_8067AB20(D_807FBB40, D_807557A0[sub->unk0].unk8, 0x01000000, D_807557A0[sub->unk0].unk7, e->subs[j].unk2, flag);
                    D_807FDCB8 = e->unk0;
                    D_807FDCBA = e->unk2;
                    D_807FDCBC = e->unk4;
                }
            }
        }
    }
}

typedef struct {
    /* 0x0 */ u8 active;
    /* 0x4 */ Actor *actor;
    /* 0x8 */ u8 pad8[0x2E8];
} PlayerSlot; // size = 0x2F0

extern u8 gPlayerCount;
extern s16 D_8076A0AA;
s32 flagTryTriggerOnce(s16, s16);

s32 volumeTriggerUpdate(VolumeTrigger *arg0) {
    u8 found = 0;
    f32 y;
    u8 result = 0;
    PlayerSlot *players;
    u8 i;

    for (i = 0; i < gPlayerCount; i++) {
        players = &((PlayerSlot *)gPlayerSlots)[i];
        if (players->active) {
            if (arg0->unk8 == -1 || ((f32)arg0->unk2 <= players->actor->unk80 && players->actor->unk80 < (f32)(arg0->unk2 + arg0->unk8))) {
                y = ((f32)arg0->unk4 - players->actor->unk84) * ((f32)arg0->unk4 - players->actor->unk84) + ((f32)arg0->unk0 - players->actor->unk7C) * ((f32)arg0->unk0 - players->actor->unk7C);
                if (y < (f32)(arg0->unk6 * arg0->unk6)) {
                    found = 1;
                }
            }
        }
    }
    switch (arg0->unkC) {
        case 0:
            if (found && arg0->unk38 == 1 && arg0->unk39) {
                result = 1;
            }
            break;
        case 1:
            if (!found && !arg0->unk38 && arg0->unk39) {
                result = 1;
            }
            break;
        case 2:
            if (found && arg0->unk39) {
                result = 1;
            }
            break;
    }
    if (result) {
        if (!flagTryTriggerOnce(D_8076A0AA, arg0->unkA)) {
            result = 0;
        }
    }
    if (found) {
        arg0->unk38 = 0;
    } else {
        arg0->unk38 = 1;
    }
    return result;
}


void volumeTriggerSetEnabled(s32 arg0, u8 arg1) {
    s32 found;
    VolumeTrigger *e;
    s32 i;

    found = 0;
    e = D_80755A14->entries;

    for (i = 0; i < D_80755A14->count && !found; i++, e++) {
        if (arg0 == e->unkA) {
            e->unk39 = arg1;
            found = 1;
        }
    }
}

s32 volumeTriggerSetPosition(s32 arg0, s16 arg1, s16 arg2, s16 arg3) {
    s32 found;
    VolumeTrigger *e;
    s32 i;

    found = 0;
    e = D_80755A14->entries;
    for (i = 0; i < D_80755A14->count && !found; i++, e++) {
        if (arg0 == e->unkA) {
            e->unk0 = arg1;
            e->unk2 = arg2;
            e->unk4 = arg3;
            found = 1;
        }
    }
}

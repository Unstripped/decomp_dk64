#include "common.h"
#include "actor.h"


typedef struct ActorProximityEntry {
    u16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
} ActorProximityEntry;

typedef struct ActorProximitySource {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    u8 pad10[4];
    f32 unk14;
    u8 pad18[0x84 - 0x18];
    s16 unk84;
    u8 pad86[2];
    s16 unk88;
    u8 pad8A[0x90 - 0x8A];
} ActorProximitySource;

extern ActorProximitySource *gModelSlots;
extern s32 D_80747D70;
extern ActorProximityEntry *D_807F9430;
extern s16 D_807F9434;

void *heapAlloc(s32);
s32 actorEntryTypeIsEmitter(s16 actorType);
void actorApplyRotatedOffset(s32 entryIdx, s32 actorType, f32 angle);
void actorInitEntryPoints(void) {
    s32 count;
    s32 i;

    count = 0;
    for (i = 0; i < D_80747D70; i++) {
        if (actorEntryTypeIsEmitter(gModelSlots[i].unk84)) {
            count++;
        }
    }

    D_807F9434 = count;
    if (count != 0) {
        D_807F9430 = heapAlloc(count * sizeof(ActorProximityEntry));
        count = 0;
        for (i = 0; i < D_80747D70; i++) {
            if (actorEntryTypeIsEmitter(gModelSlots[i].unk84)) {
                D_807F9430[count].unk0 = gModelSlots[i].unk84;
                D_807F9430[count].unk2 = gModelSlots[i].unk0;
                D_807F9430[count].unk4 = gModelSlots[i].unk4;
                D_807F9430[count].unk6 = gModelSlots[i].unk8;
                actorApplyRotatedOffset(count, gModelSlots[i].unk84, gModelSlots[i].unk14);
                D_807F9430[count].unk8 = gModelSlots[i].unkC * 100.0;
                D_807F9430[count].unkA = gModelSlots[i].unk88;
                count++;
            }
        }
    }
}

void actorApplyRotatedOffset(s32 entryIdx, s32 actorType, f32 angle) {
    s32 pad[2];
    f32 outX;
    f32 outY;
    f32 outZ;
    f32 rotMtx[4][4];

    if (actorType == 0x138) {
        guRotateF(rotMtx, angle, 0.0f, 1.0f, 0.0f);
        guMtxXFMF(rotMtx, 0.0f, 0.0f, -10.0f, &outX, &outY, &outZ);
        D_807F9430[entryIdx].unk2 += outX;
        D_807F9430[entryIdx].unk6 += outZ;
    }
}

void actorUpdateEntryCoordinates(s16 targetId, f32 x, f32 y, f32 z, f32 scale, f32 angle) {
    s32 i;

    for (i = 0; i < D_807F9434; i++) {
        if (targetId == D_807F9430[i].unkA) {
            D_807F9430[i].unk2 = x;
            D_807F9430[i].unk4 = y;
            D_807F9430[i].unk6 = z;
            actorApplyRotatedOffset(i, D_807F9430[i].unk0, angle);
            D_807F9430[i].unk8 = scale * 100.0;
            return;
        }
    }
}


void actorClearEntrySlot(s16 targetId) {
    s32 i;

    for (i = 0; i < D_807F9434; i++) {
        if (targetId == D_807F9430[i].unkA) {
            D_807F9430[i].unkA = -1;
        }
    }
}

s32 actorEntryTypeIsEmitter(s16 actorType) {
    if ((actorType == 1) || (actorType == 0x10) || (actorType == 0x74) || (actorType == 0xF3) || (actorType == 0x138) || (actorType == 0x288)) {
        return 1;
    }
    return 0;
}

typedef struct PlayerPositionView {
    u8 pad0[0x21C];
    f32 x;
    f32 y;
    f32 z;
} PlayerPositionView;

extern PlayerPositionView *gPlayerSlots;
extern u8 gPlayerCount;

s32 func_8063C2A8(s16);
void actorEntryEmitJitterParticle(s16 entryIdx);
void actorEntryEmitScaledParticle(s16 entryIdx);

void actorUpdateEntryEmitters(void) {
    s32 i;
    f32 dz;
    f32 dx;
    f32 dy;
    f32 sum;

    if (gPlayerCount < 2) {
        for (i = 0; i < D_807F9434; i++) {
            dz = gPlayerSlots->z - D_807F9430[i].unk6;
            dx = gPlayerSlots->x - D_807F9430[i].unk2;
            dy = gPlayerSlots->y - D_807F9430[i].unk4;
            sum = (dz * dz) + ((dx * dx) + (dy * dy));
            dx = D_807F9430[i].unkA;  // FAKE: dead float store steers uopt (sum gets $f14)
            if ((f64)sum < 90000.0) {
                if (D_807F9430[i].unkA != -1 && func_8063C2A8(D_807F9430[i].unkA)) {
                    switch (D_807F9430[i].unk0) {
                        case 1:
                        case 0x10:
                        case 0xF3:
                        case 0x138:
                            actorEntryEmitJitterParticle(i);
                            break;
                        case 0x74:
                        case 0x288:
                            actorEntryEmitScaledParticle(i);
                            break;
                    }
                }
            }
        }
    }
}


s32 randomNonNegative(void);
void effectSetDepth(s32);
void effectSetMode(s32);
void effectSetSpeed(s32);
void effectSetCallback(void *);
void effectSetColor(s32, s32, s32, s32);
void effectSetScale(f32, f32);
void effectSetFlags(s32);
void effectCreateAtPosition(void *, f32, f32, f32, f32);

extern u8 D_807213D0;
void effectDriftXZUpdate(void);

void actorEntryEmitJitterParticle(s16 entryIdx) {
    ActorProximityEntry *entry;
    s32 randX;
    s32 temp;

    if (((randomNonNegative() % 10000) % 12) == 0) {
        effectSetDepth(1);
        effectSetMode(7);
        effectSetSpeed(((randomNonNegative() % 10000) % 50) - 120);
        effectSetCallback(effectDriftXZUpdate);
        effectSetColor(255, 200, 200, 200);
        effectSetScale(0.2f, 0.1f);
        effectSetFlags(4);
        randX = randomNonNegative();
        temp = randomNonNegative();
        entry = (ActorProximityEntry *)((u8 *)D_807F9430 + entryIdx * sizeof(ActorProximityEntry));
        effectCreateAtPosition(&D_807213D0, 0.0f,
            (((f64) ((randX % 10000) % 100) / 20.0) + (f64) entry->unk2) - 2.5,
            (f64) entry->unk4 + 4.0,
            (((f64) ((temp % 10000) % 100) / 20.0) + (f64) entry->unk6) - 2.5);
    }
}


extern u8 D_80720A7C;

void actorEntryEmitScaledParticle(s16 entryIdx) {
    f32 scaleFactor;
    s32 temp;
    s32 randY;
    s32 randX;

    if (((randomNonNegative() % 10000) % 10) == 0) {
        scaleFactor = (f64) D_807F9430[entryIdx].unk8 / 25.0;
        effectSetDepth(1);
        effectSetMode(2);
        effectSetFlags(4);
        randX = randomNonNegative();
        randY = randomNonNegative();
        temp = randomNonNegative();
        effectCreateAtPosition(&D_80720A7C, 0.4f,
            ((((f64) ((randX % 10000) % 300) / 20.0) - 7.5) * (f64) scaleFactor) + (f64) (D_807F9430 + entryIdx)->unk2,
            (((f64) ((randY % 10000) % 600) / 20.0) * (f64) scaleFactor) + (f64) (D_807F9430 + entryIdx)->unk4,
            ((((f64) ((temp % 10000) % 300) / 20.0) - 7.5) * (f64) scaleFactor) + (f64) (D_807F9430 + entryIdx)->unk6);
    }
}


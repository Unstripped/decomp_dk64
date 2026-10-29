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

extern ActorProximitySource *D_807F6000;
extern s32 D_80747D70;
extern ActorProximityEntry *D_807F9430;
extern s16 D_807F9434;

void *func_80610FE8(s32);
s32 func_8066461C(s16);
void actorApplyRotatedOffset(s32, s32, f32);
void actorInitEntryPoints(void) {
    s32 count;
    s32 i;

    count = 0;
    for (i = 0; i < D_80747D70; i++) {
        if (func_8066461C(D_807F6000[i].unk84)) {
            count++;
        }
    }

    D_807F9434 = count;
    if (count != 0) {
        D_807F9430 = func_80610FE8(count * sizeof(ActorProximityEntry));
        count = 0;
        for (i = 0; i < D_80747D70; i++) {
            if (func_8066461C(D_807F6000[i].unk84)) {
                D_807F9430[count].unk0 = D_807F6000[i].unk84;
                D_807F9430[count].unk2 = D_807F6000[i].unk0;
                D_807F9430[count].unk4 = D_807F6000[i].unk4;
                D_807F9430[count].unk6 = D_807F6000[i].unk8;
                actorApplyRotatedOffset(count, D_807F6000[i].unk84, D_807F6000[i].unk14);
                D_807F9430[count].unk8 = D_807F6000[i].unkC * 100.0;
                D_807F9430[count].unkA = D_807F6000[i].unk88;
                count++;
            }
        }
    }
}

void actorApplyRotatedOffset(s32 arg0, s32 arg1, f32 arg2) {
    s32 pad[2];
    f32 sp74;
    f32 sp70;
    f32 sp6C;
    f32 sp2C[4][4];

    if (arg1 == 0x138) {
        guRotateF(sp2C, arg2, 0.0f, 1.0f, 0.0f);
        guMtxXFMF(sp2C, 0.0f, 0.0f, -10.0f, &sp74, &sp70, &sp6C);
        D_807F9430[arg0].unk2 += sp74;
        D_807F9430[arg0].unk6 += sp6C;
    }
}

void actorUpdateEntryCoordinates(s16 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    s32 i;

    for (i = 0; i < D_807F9434; i++) {
        if (arg0 == D_807F9430[i].unkA) {
            D_807F9430[i].unk2 = arg1;
            D_807F9430[i].unk4 = arg2;
            D_807F9430[i].unk6 = arg3;
            actorApplyRotatedOffset(i, D_807F9430[i].unk0, arg5);
            D_807F9430[i].unk8 = arg4 * 100.0;
            return;
        }
    }
}


void actorClearEntrySlot(s16 arg0) {
    s32 i;

    for (i = 0; i < D_807F9434; i++) {
        if (arg0 == D_807F9430[i].unkA) {
            D_807F9430[i].unkA = -1;
        }
    }
}

s32 func_8066461C(s16 arg0) {
    if ((arg0 == 1) || (arg0 == 0x10) || (arg0 == 0x74) || (arg0 == 0xF3) || (arg0 == 0x138) || (arg0 == 0x288)) {
        return 1;
    }
    return 0;
}

typedef struct ColSmall_Player {
    u8 pad0[0x21C];
    f32 x;
    f32 y;
    f32 z;
} ColSmall_Player;

extern ColSmall_Player *D_807FC924;
extern u8 D_807FC928;

s32 func_8063C2A8(s16);
void func_80664834(s16);
void func_80664A38(s16);

void func_8066466C(void) {
    s32 i;
    f32 dz;
    f32 dx;
    f32 dy;
    f32 sum;

    if (D_807FC928 < 2) {
        for (i = 0; i < D_807F9434; i++) {
            dz = D_807FC924->z - D_807F9430[i].unk6;
            dx = D_807FC924->x - D_807F9430[i].unk2;
            dy = D_807FC924->y - D_807F9430[i].unk4;
            sum = (dz * dz) + ((dx * dx) + (dy * dy));
            dx = D_807F9430[i].unkA;  // FAKE: dead float store steers uopt (sum gets $f14)
            if ((f64)sum < 90000.0) {
                if (D_807F9430[i].unkA != -1 && func_8063C2A8(D_807F9430[i].unkA)) {
                    switch (D_807F9430[i].unk0) {
                        case 1:
                        case 0x10:
                        case 0xF3:
                        case 0x138:
                            func_80664834(i);
                            break;
                        case 0x74:
                        case 0x288:
                            func_80664A38(i);
                            break;
                    }
                }
            }
        }
    }
}


s32 randomNonNegative(void);
void func_807149B8(s32);
void func_80714998(s32);
void func_80714950(s32);
void func_8071498C(void *);
void func_807149C8(s32, s32, s32, s32);
void func_80714A08(f32, f32);
void func_80714A28(s32);
void func_80714CC0(void *, f32, f32, f32, f32);

extern u8 D_807213D0;
void func_80717DB4(void);

void func_80664834(s16 arg0) {
    ActorProximityEntry *entry;
    s32 sp20;
    s32 temp;

    if (((randomNonNegative() % 10000) % 12) == 0) {
        func_807149B8(1);
        func_80714998(7);
        func_80714950(((randomNonNegative() % 10000) % 50) - 120);
        func_8071498C(func_80717DB4);
        func_807149C8(255, 200, 200, 200);
        func_80714A08(0.2f, 0.1f);
        func_80714A28(4);
        sp20 = randomNonNegative();
        temp = randomNonNegative();
        entry = (ActorProximityEntry *)((u8 *)D_807F9430 + arg0 * sizeof(ActorProximityEntry));
        func_80714CC0(&D_807213D0, 0.0f,
            (((f64) ((sp20 % 10000) % 100) / 20.0) + (f64) entry->unk2) - 2.5,
            (f64) entry->unk4 + 4.0,
            (((f64) ((temp % 10000) % 100) / 20.0) + (f64) entry->unk6) - 2.5);
    }
}


extern u8 D_80720A7C;

void func_80664A38(s16 arg0) {
    f32 sp34;
    s32 temp;
    s32 sp2C;
    s32 sp28;

    if (((randomNonNegative() % 10000) % 10) == 0) {
        sp34 = (f64) D_807F9430[arg0].unk8 / 25.0;
        func_807149B8(1);
        func_80714998(2);
        func_80714A28(4);
        sp28 = randomNonNegative();
        sp2C = randomNonNegative();
        temp = randomNonNegative();
        func_80714CC0(&D_80720A7C, 0.4f,
            ((((f64) ((sp28 % 10000) % 300) / 20.0) - 7.5) * (f64) sp34) + (f64) (D_807F9430 + arg0)->unk2,
            (((f64) ((sp2C % 10000) % 600) / 20.0) * (f64) sp34) + (f64) (D_807F9430 + arg0)->unk4,
            ((((f64) ((temp % 10000) % 300) / 20.0) - 7.5) * (f64) sp34) + (f64) (D_807F9430 + arg0)->unk6);
    }
}


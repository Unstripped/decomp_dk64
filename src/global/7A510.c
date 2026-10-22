#include "common.h"
#include "actor.h"

#pragma GLOBAL_ASM("asm/global/nonmatchings/7A510/func_80675810.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7A510/func_80675AFC.s")

s32 func_80675C70(s16 arg0, s16 arg1, s16 arg2) {
    if (arg2 == arg0) {
        return 1;
    }
    switch (arg2) {
    case -1:
        if (arg1 == 1) {
            return 1;
        }
        break;
    case -2:
        if (arg1 == 2) {
            return 1;
        }
        break;
    case -8:
        if (arg1 == 0x80) {
            return 1;
        }
        break;
    case -3:
        if (arg1 == 4) {
            return 1;
        }
        break;
    case -4:
        if (arg1 == 8) {
            return 1;
        }
        break;
    case -5:
        if (arg1 == 0x10) {
            return 1;
        }
        break;
    case -6:
        if (arg1 == 0x20) {
            return 1;
        }
        break;
    case -7:
        if (arg1 == 0x40) {
            return 1;
        }
        break;
    }
    return 0;
}

extern ActorGlobalState D_807FBB70;

void func_80675D70(s32 arg0) {
    if (D_807FBB70.unk200 < 2) {
        D_807FBB70.unk1FC = arg0;
        D_807FBB70.unk200 = 1;
    }
    if (D_807FBB70.unk201 < 0xF) {
        D_807FBB70.unk204[D_807FBB70.unk201] = arg0;
        D_807FBB70.unk244[D_807FBB70.unk201] = 2;
        D_807FBB70.unk201++;
    }
}

typedef struct Beh798_Actor {
    /* 0x000 */ u8 pad0[0x58];
    /* 0x058 */ s32 unk58;
    /* 0x05C */ u8 pad5C[0xD8];
    /* 0x134 */ s16 unk134;
    /* 0x136 */ s16 unk136;
} Beh798_Actor;
void actorApplyDamage(Beh798_Actor *arg0, Beh798_Actor *arg1) {
    s32 var_v0;

    if ((arg0->unk134 -= arg1->unk136) <= 0) {
        D_807FBB70.unk200 = 9;
        return;
    }
    var_v0 = D_807FBB70.unk200;
    if (var_v0 == 6) {
        var_v0 = D_807FBB70.unk200 = 4;
    }
    if (var_v0 == 7) {
        D_807FBB70.unk200 = 5;
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/7A510/func_80675E3C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7A510/func_80675EE0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7A510/func_8067605C.s")

extern s32 D_8076A0A8;
void func_8067618C(Actor *arg0, s8 *arg1) {
    if ((D_8076A0A8 == 0x53) && (arg0->unk58 == 6) && (arg0->unk154 == 0x1E)) {
        *arg1 = 0x15;
    }
}


typedef struct Beh798_8074D0C4 {
    s16 unk0;
    s16 unk2;
} Beh798_8074D0C4;
extern Beh798_8074D0C4 D_8074D0C4[];
extern Beh798_8074D0C4 D_8074D0C6[];

void actorInitHealth(Beh798_Actor *arg0) {
    arg0->unk134 = D_8074D0C4[arg0->unk58].unk0;
}

void actorInitDamage(Beh798_Actor *arg0) {
    arg0->unk136 = D_8074D0C6[arg0->unk58].unk0;
}

typedef struct Beh798_8074C608 {
    u8 unk0;
    u8 pad[7];
} Beh798_8074C608;
extern Beh798_8074C608 D_8074C608[];

u8 func_80676208(Actor *arg0) {
    return D_8074C608[arg0->unk58].unk0;
}

s32 func_80676220(s16 arg0) {
    if ((arg0 == 0xBB) || (arg0 == 0xEB) || (arg0 == 0x123)) {
        return 0;
    }
    return 1;
}

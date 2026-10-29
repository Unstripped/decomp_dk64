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

typedef struct KaC1_Entry {
    s16 unk0;
    s32 unk4;
} KaC1_Entry;

s32 func_80675E3C(KaC1_Entry *arg0, s16 arg1, s16 arg2) {
    s32 s1;
    s32 s2;
    s32 match;

    do {
        s2 = arg0->unk0;
        s1 = s2;
        s2 = arg0->unk4;
        match = func_80675C70(arg1, arg2, s1);
        arg0++;
        if (match) {
            break;
        }
    } while (s1 != 0);
    return s2;
}

typedef struct KaC1_ActorSub4_Sub0 {
    u8 pad0[4];
    f32 unk4;
    u8 pad8[8];
    s16 unk10;
} KaC1_ActorSub4_Sub0;

typedef struct KaC1_ActorSub4 {
    KaC1_ActorSub4_Sub0 *unk0;
} KaC1_ActorSub4;

typedef struct KaC1_ActorSub174 {
    u8 pad0[0x11E];
    s16 unk11E;
} KaC1_ActorSub174;

typedef struct KaC1_ActorEE0 {
    u8 pad0[4];
    KaC1_ActorSub4 *unk4;
    u8 pad8[0x5C];
    s32 unk64;
    u8 pad68[0xCA];
    s16 unk132;
    s16 unk134;
    s16 unk136;
    u8 pad138[0x3C];
    KaC1_ActorSub174 *unk174;
} KaC1_ActorEE0;

typedef struct KaC1_80748FE8 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    u8 unk8;
    u8 unk9;
    u8 unkA;
    u8 unkB;
} KaC1_80748FE8;

extern KaC1_80748FE8 D_80748FE8[];
void func_8067605C(Actor *, u8);

void func_80675EE0(KaC1_ActorEE0 *arg0) {
    s16 targetType;
    s16 targetVal;
    s32 a2;
    s32 a3;
    s32 a1;
    KaC1_80748FE8 *entry;
    KaC1_ActorSub174 *sub174;
    u8 pad;
    u8 valid;

    a1 = 0;
    a2 = 0;
    targetType = arg0->unk4->unk0->unk10;
    sub174 = arg0->unk174;
    targetVal = (s32)arg0->unk4->unk0->unk4;
    a3 = 0;
    valid = 1;

    if (targetType == -1) {
        arg0->unk132 = 0;
        return;
    }

    if (sub174->unk11E != -1) {
        a2 = sub174->unk11E;
        a3 = 1;
    }

    do {
        if (D_80748FE8[a2].unk0 == -1) {
            a1 = 1;
        } else if (targetType == D_80748FE8[a2].unk0) {
            if ((targetVal >= D_80748FE8[a2].unk2) && (targetVal <= D_80748FE8[a2].unk4)) {
                entry = &D_80748FE8[a2];
                arg0->unk132 = entry->unk6;
                arg0->unk136 = entry->unk8;
                if (entry->unkA & 1) {
                    arg0->unk64 |= 0x80;
                } else {
                    arg0->unk64 &= ~0x80;
                }
                func_8067605C((Actor *)arg0, entry->unk9);
                if (valid) {
                    sub174->unk11E = a2;
                } else {
                    sub174->unk11E = -1;
                }
                return;
            }
            valid = 0;
        }

        if (a3) {
            a2 = 0;
            a3 = 0;
            a1 = 0;
        } else {
            a2++;
        }
    } while (!a1);

    arg0->unk132 = 0;
    arg0->unk136 = 0;
}

typedef struct KaC1_80748F58 {
    u16 unk0;
    u8 unk2;
    u8 pad3;
    u16 unk4;
} KaC1_80748F58;

extern s8 D_80748E50[][9];
extern KaC1_80748F58 D_80748F58[];

void func_8067618C(Actor *, s8 *);
void actorClearAllNodeFlags(Actor *);
void actorSetNodeFlag(Actor *, s32);
void actorSetNodeValue(Actor *, s32, u16);

void func_8067605C(Actor *arg0, u8 arg1) {
    s32 match;
    s16 i;
    s8 *ptr;

    func_8067618C(arg0, (s8 *)&arg1);
    do {} while (0); // FAKE: regalloc s1/s2 swap
    actorClearAllNodeFlags(arg0);
    ptr = D_80748E50[arg1];
    if (*ptr != -1) {
        do {
            actorSetNodeFlag(arg0, *ptr);
            match = 0;
            i = 0;
            do {
                if ((arg0->unk58 == D_80748F58[i].unk0) && (*ptr == D_80748F58[i].unk2)) {
                    actorSetNodeValue(arg0, *ptr, D_80748F58[i].unk4);
                    match = 1;
                } else {
                    actorSetNodeValue(arg0, *ptr, 0);
                    i++;
                }
            } while ((i < 24) && (!match));
            ptr++;
        } while (*ptr != -1);
    }
}

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

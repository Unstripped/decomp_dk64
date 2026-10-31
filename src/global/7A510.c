#include "common.h"
#include "actor.h"

#ifdef NON_MATCHING
typedef struct W2Col_ActorSub174_810 {
    u8 pad0[0xD4];
    s16 unkD4;
} W2Col_ActorSub174_810;

typedef struct W2Col_Actor810 {
    u8 pad0[0x54];
    s32 unk54;
    union {
        s32 unk58;
        struct {
            s16 unk58_half;
            s16 unk5A;
        };
    };
    u16 unk5C;
    u8 pad5E[2];
    u32 unk60;
    u32 unk64;
    u8 pad68[0xB4];
    struct W2Col_Actor810 *unk11C;
    u8 pad120[0x12];
    s16 unk132;
    s16 unk134;
    s16 unk136;
    u8 pad138[0x3C];
    W2Col_ActorSub174_810 *unk174;
} W2Col_Actor810;

typedef struct W2Col_Arg1_Elem {
    u8 pad0[0x18];
    s32 unk18;
} W2Col_Arg1_Elem;

typedef struct W2Col_Arg1 {
    u8 pad0[0x8];
    W2Col_Actor810 *unk8;
    u8 padC[4];
    W2Col_Arg1_Elem *unk10;
} W2Col_Arg1;

typedef struct W2Col_80675810_Entry {
    s16 unk0;
    s16 unk2;
    s32 (*unk4)(W2Col_Actor810 *, W2Col_Actor810 *, W2Col_Arg1 *);
    u8 unk8;
    u8 unk9;
    u8 unkA;
    u8 unkB;
} W2Col_80675810_Entry;

struct CollisionTableEntry;
struct Beh798_Actor;
typedef struct W2Col_8074C604 {
    struct CollisionTableEntry *unk0;
    u8 pad4[4];
} W2Col_8074C604;

extern W2Col_8074C604 D_8074C604[];
struct Beh798_8074C608;
extern struct Beh798_8074C608 D_8074C608[];
extern ActorGlobalState D_807FBB70;

s32 actorTableContains(void *);
void func_80675D70(s32);
s32 actorCollisionFindTableEntry(struct CollisionTableEntry *, s16, s16);
s32 func_80676220(s16);
void actorApplyDamage(struct Beh798_Actor *, struct Beh798_Actor *);
void actorCollisionRunInteractionTable();

void func_80675810(W2Col_Actor810 *arg0, W2Col_Arg1 *arg1) {
    W2Col_80675810_Entry *entry;
    s32 done;
    W2Col_Actor810 *temp_s2;
    s32 res;
    struct CollisionTableEntry *entries;
    u8 var_v1;
    s32 i;
    W2Col_ActorSub174_810 *sub;
    u8 tv0;
    u8 tv1;

    temp_s2 = arg1->unk8;
    i = 0;
    done = 0;
    if (actorTableContains(temp_s2) && temp_s2->unk54 == arg1->unk10->unk18) {
        entries = D_8074C604[arg0->unk58].unk0;
        if (entries == NULL) {
            if (temp_s2->unk60 & 0x20000) {
                func_80675D70((s32)temp_s2);
            }
        } else {
            res = actorCollisionFindTableEntry(entries, temp_s2->unk5A, temp_s2->unk5C);
            if ((temp_s2->unk60 & 0x80000) || (arg0->unk60 & 0x80000)) {
                if (arg0 == temp_s2->unk11C || temp_s2 == arg0->unk11C) {
                    return;
                }
            }
            if (res == 0) {
                if (temp_s2->unk60 & 0x20000) {
                    func_80675D70((s32)temp_s2);
                }
            } else {
                do {
                    entry = &((W2Col_80675810_Entry *)res)[i];
                    if ((entry->unk0 & arg0->unk132) && (entry->unk2 & temp_s2->unk132)) {
                        if (D_8074C604) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                        if (entry->unk4 != NULL) {
                            var_v1 = entry->unk4(arg0, temp_s2, arg1);
                        } else {
                            var_v1 = 1;
                        }
                        if (var_v1) {
                            tv0 = entry->unk8;
                            tv1 = D_807FBB70.unk200;
                            if (tv1 < tv0) {
                                D_807FBB70.unk1FC = (s32)temp_s2;
                                D_807FBB70.unk200 = ((u8 *)res)[i * 12 + 8];
                            }
                            if (D_807FBB70.unk201 < 0xF) {
                                D_807FBB70.unk204[D_807FBB70.unk201] = (s32)temp_s2;
                                D_807FBB70.unk244[D_807FBB70.unk201] = entry->unk9;
                                D_807FBB70.unk201++;
                                if (temp_s2->unk5C & 1) {
                                    sub = temp_s2->unk174;
                                    if (sub->unkD4 != 0) {
                                        if (((u8 *)D_8074C608)[arg0->unk58 * 8] != 0) {
                                            u8 t = D_807FBB70.unk244[D_807FBB70.unk201 - 1];
                                            if (t == 5 || t == 0xF) {
                                                D_807FBB70.unk201--;
                                            }
                                        }
                                    }
                                    if ((arg0->unk5C & 2) && func_80676220(arg0->unk5A)) {
                                        temp_s2->unk64 |= 0x1000;
                                    }
                                }
                            }
                            if (entry->unkA == 0 || entry->unkA == 2) {
                                done = 1;
                            }
                        }
                    }
                    if (entry->unkA == 0) {
                        done = 1;
                    }
                    i++;
                } while (!done);
                if (arg0->unk60 & 0x20000000) {
                    D_807FBB70.unk200 = 1;
                }
                if (D_807FBB70.unk200 == 6 || D_807FBB70.unk200 == 7) {
                    actorApplyDamage((struct Beh798_Actor *)arg0, (struct Beh798_Actor *)temp_s2);
                }
                actorCollisionRunInteractionTable((void *)arg0, (void *)temp_s2);
            }
        }
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/7A510/func_80675810.s")
#endif

typedef struct InteractionActor {
    u8 pad0[0x5A];
    s16 unk5A;
    s16 unk5C;
} InteractionActor;

typedef struct InteractionEntry {
    s16 unk0;
    s16 unk2;
    s8 unk4;
    s8 unk5;
    void (*unk8)(InteractionActor *, InteractionActor *, s32, s32);
    u8 unkC;
} InteractionEntry;

s32 actorCollisionPatternMatches(s16 arg0, s16 arg1, s16 arg2);
extern ActorGlobalState D_807FBB70;
extern InteractionEntry D_8074ABCC[];

void actorCollisionRunInteractionTable(InteractionActor *arg0, InteractionActor *arg1) {
    InteractionEntry *entry;
    s32 done;
    s16 two;
    s32 found;
    s32 j;

    done = 0;
    entry = D_8074ABCC; do {
        if (actorCollisionPatternMatches(arg0->unk5A, arg0->unk5C, entry->unk0) &&
            actorCollisionPatternMatches(arg1->unk5A, arg1->unk5C, entry->unk2) &&
            ((entry->unk4 == -1) || entry->unk4 == D_807FBB70.unk200)) {
            if (entry->unk5 != -1) {
                if (1) {  // FAKE: extra block lowers D_807FBB70 const priority vs arg1 (s0/s1 swap)
                    found = 0;
                }
                for (j = 0; !found && j < D_807FBB70.unk201;) {
                    if (arg1 == (InteractionActor *)D_807FBB70.unk204[j] && D_807FBB70.unk244[j] == ((s8 *)entry)[5]) {  // FAKE: byte-indexed unk5 read makes IDO emit the load operand first (bnel t2,t0)
                        found = 1;
                    } else {
                        j++;
                    }
                }
            } else {
                found = 1;
            }
            if (found) {
                entry->unk8(arg0, arg1, entry->unk4 & 0xFF, entry->unk5 & 0xFF);
                if (entry->unkC == 0 || entry->unkC == (two = 2)) {  // FAKE: makes the constant 2 a register operand (bnel v0,s6 order)
                    done = 1;
                }
            }
        }
        if (entry->unkC == 0) {
            done = 1;
        }
        entry++;
    } while (!done);
}

s32 actorCollisionPatternMatches(s16 arg0, s16 arg1, s16 arg2) {
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

typedef struct CollisionTableEntry {
    s16 unk0;
    s32 unk4;
} CollisionTableEntry;

s32 actorCollisionFindTableEntry(CollisionTableEntry *arg0, s16 arg1, s16 arg2) {
    s32 s1;
    s32 s2;
    s32 match;

    do {
        s2 = arg0->unk0;
        s1 = s2;
        s2 = arg0->unk4;
        match = actorCollisionPatternMatches(arg1, arg2, s1);
        arg0++;
        if (match) {
            break;
        }
    } while (s1 != 0);
    return s2;
}

typedef struct CollisionActorSub4_Sub0 {
    u8 pad0[4];
    f32 unk4;
    u8 pad8[8];
    s16 unk10;
} CollisionActorSub4_Sub0;

typedef struct CollisionActorSub4 {
    CollisionActorSub4_Sub0 *unk0;
} CollisionActorSub4;

typedef struct CollisionActorSub174 {
    u8 pad0[0x11E];
    s16 unk11E;
} CollisionActorSub174;

typedef struct CollisionBoundingActor {
    u8 pad0[4];
    CollisionActorSub4 *unk4;
    u8 pad8[0x5C];
    s32 unk64;
    u8 pad68[0xCA];
    s16 unk132;
    s16 unk134;
    s16 unk136;
    u8 pad138[0x3C];
    CollisionActorSub174 *unk174;
} CollisionBoundingActor;

typedef struct CollisionThresholdEntry {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    u8 unk8;
    u8 unk9;
    u8 unkA;
    u8 unkB;
} CollisionThresholdEntry;

extern CollisionThresholdEntry D_80748FE8[];
void actorCollisionUpdateNodeFlags(Actor *, u8);

void actorCollisionCheckBoundingBoxes(CollisionBoundingActor *arg0) {
    s16 targetType;
    s16 targetVal;
    s32 a2;
    s32 a3;
    s32 a1;
    CollisionThresholdEntry *entry;
    CollisionActorSub174 *sub174;
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
                actorCollisionUpdateNodeFlags((Actor *)arg0, entry->unk9);
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

typedef struct CollisionNodeFlagEntry {
    u16 unk0;
    u8 unk2;
    u8 pad3;
    u16 unk4;
} CollisionNodeFlagEntry;

extern s8 D_80748E50[][9];
extern CollisionNodeFlagEntry D_80748F58[];

void func_8067618C(Actor *, s8 *);
void actorClearAllNodeFlags(Actor *);
void actorSetNodeFlag(Actor *, s32);
void actorSetNodeValue(Actor *, s32, u16);

void actorCollisionUpdateNodeFlags(Actor *arg0, u8 arg1) {
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


typedef struct ActorTypeStat {
    s16 unk0;
    s16 unk2;
} ActorTypeStat;
extern ActorTypeStat D_8074D0C4[];
extern ActorTypeStat D_8074D0C6[];

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

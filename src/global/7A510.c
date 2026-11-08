#include "common.h"
#include "actor.h"

typedef struct CollisionHitActorSub {
    u8 pad0[0xD4];
    s16 unkD4;
} CollisionHitActorSub;

typedef struct CollisionHitActor {
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
    struct CollisionHitActor *unk11C;
    u8 pad120[0x12];
    s16 unk132;
    s16 unk134;
    s16 unk136;
    u8 pad138[0x3C];
    CollisionHitActorSub *unk174;
} CollisionHitActor;

typedef struct CollisionCallbackElem {
    u8 pad0[0x18];
    s32 unk18;
} CollisionCallbackElem;

typedef struct CollisionCallbackArg {
    u8 pad0[0x8];
    CollisionHitActor *unk8;
    u8 padC[4];
    CollisionCallbackElem *unk10;
} CollisionCallbackArg;

typedef struct CollisionInteractionEntry {
    s16 unk0;
    s16 unk2;
    s32 (*unk4)(CollisionHitActor *, CollisionHitActor *, CollisionCallbackArg *);
    u8 unk8;
    u8 unk9;
    u8 unkA;
    u8 unkB;
} CollisionInteractionEntry;

struct CollisionTableEntry;
struct Beh798_Actor;
typedef struct CollisionTableSlot {
    struct CollisionTableEntry *unk0;
    u8 pad4[4];
} CollisionTableSlot;

extern CollisionTableSlot D_8074C604[];
struct Beh798_8074C608;
extern struct Beh798_8074C608 D_8074C608[];
extern ActorGlobalState D_807FBB70;

s32 actorTableContains(void *);
void func_80675D70(s32);
s32 actorCollisionFindTableEntry(struct CollisionTableEntry *, s16, s16);
s32 func_80676220(s16);
void actorApplyDamage(struct Beh798_Actor *, struct Beh798_Actor *);
void actorCollisionRunInteractionTable();

void actorCollisionProcessHit(CollisionHitActor *targetActor, CollisionCallbackArg *cbArg) {
    CollisionInteractionEntry *entry;
    s32 done;
    CollisionHitActor *attacker;
    s32 res;
    struct CollisionTableEntry *entries;
    u8 entryAllowed;
    s32 i;
    CollisionHitActorSub *sub;
    u8 tv0;
    u8 tv1;

    attacker = cbArg->unk8;
    i = 0;
    done = 0;
    if (actorTableContains(attacker) && attacker->unk54 == cbArg->unk10->unk18) {
        entries = D_8074C604[targetActor->unk58].unk0;
        if (entries == NULL) {
            if (attacker->unk60 & 0x20000) {
                func_80675D70((s32)attacker);
            }
        } else {
            res = actorCollisionFindTableEntry(entries, attacker->unk5A, attacker->unk5C);
            if ((attacker->unk60 & 0x80000) || (targetActor->unk60 & 0x80000)) {
                if (targetActor == attacker->unk11C || attacker == targetActor->unk11C) {
                    return;
                }
            }
            if (res == 0) {
                if (attacker->unk60 & 0x20000) {
                    func_80675D70((s32)attacker);
                }
            } else {
                while (!done) {  // FAKE: while (not do-while) gives the post-loop its own lda web (remat lui/addiu s0)
                    entry = &((CollisionInteractionEntry *)res)[i];
                    if ((entry->unk0 & targetActor->unk132) && (entry->unk2 & attacker->unk132)) {
                        if (D_8074C604) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                        if (entry->unk4 != NULL) {
                            entryAllowed = entry->unk4(targetActor, attacker, cbArg);
                        } else {
                            entryAllowed = 1;
                        }
                        if (entryAllowed) {
                            tv0 = entry->unk8;
                            tv1 = D_807FBB70.unk200;
                            if (tv1 < tv0) {
                                D_807FBB70.unk1FC = (s32)attacker;
                                D_807FBB70.unk200 = ((u8 *)res)[i * 12 + 8];
                            }
                            if (D_807FBB70.unk201 < 0xF) {
                                D_807FBB70.unk204[D_807FBB70.unk201] = (s32)attacker;
                                D_807FBB70.unk244[D_807FBB70.unk201] = entry->unk9;
                                D_807FBB70.unk201++;
                                if (attacker->unk5C & 1) {
                                    sub = attacker->unk174;
                                    if (sub->unkD4 != 0) {
                                        if (((u8 *)D_8074C608)[targetActor->unk58 * 8] != 0) {
                                            u8 t = D_807FBB70.unk244[D_807FBB70.unk201 - 1];
                                            if (t == 5 || t == 0xF) {
                                                D_807FBB70.unk201--;
                                            }
                                        }
                                    }
                                    if ((targetActor->unk5C & 2) && func_80676220(targetActor->unk5A)) {
                                        attacker->unk64 |= 0x1000;
                                    }
                                }
                            }
                            if (D_807FBB70.unk200) {}  // FAKE: dead read steers s0/s1 colouring
                            if (entry->unkA == 0 || entry->unkA == 2) {
                                done = 1;
                            }
                        }
                    }
                    if (entry->unkA == 0) {
                        done = 1;
                    }
                    i++;
                }
                if (targetActor->unk60 & 0x20000000) {
                    D_807FBB70.unk200 = 1;
                }
                if (D_807FBB70.unk200 == 6 || D_807FBB70.unk200 == 7) {
                    actorApplyDamage((struct Beh798_Actor *)targetActor, (struct Beh798_Actor *)attacker);
                }
                actorCollisionRunInteractionTable((void *)targetActor, (void *)attacker);
            }
        }
    }
}

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

s32 actorCollisionPatternMatches(s16 actorType, s16 actorFlags, s16 pattern);
extern ActorGlobalState D_807FBB70;
extern InteractionEntry D_8074ABCC[];

void actorCollisionRunInteractionTable(InteractionActor *actorA, InteractionActor *actorB) {
    InteractionEntry *entry;
    s32 done;
    s32 kind;
    s32 found;
    s32 j;

    done = 0;
    entry = D_8074ABCC; do {
        if (actorCollisionPatternMatches(actorA->unk5A, actorA->unk5C, entry->unk0) &&
            actorCollisionPatternMatches(actorB->unk5A, actorB->unk5C, entry->unk2) &&
            ((entry->unk4 == -1) || entry->unk4 == D_807FBB70.unk200)) {
            if (entry->unk5 != -1) {
                if (1) {  // FAKE: extra block lowers D_807FBB70 const priority vs actorB (s0/s1 swap)
                    found = 0;
                }
                for (j = 0; !found && j < D_807FBB70.unk201;) {
                    if (actorB == (InteractionActor *)D_807FBB70.unk204[j] && D_807FBB70.unk244[j] == ((s8 *)entry)[5]) {  // FAKE: byte-indexed unk5 read makes IDO emit the load operand first (bnel t2,t0)
                        found = 1;
                    } else {
                        j++;
                    }
                }
            } else {
                found = 1;
            }
            if (found) {
                entry->unk8(actorA, actorB, entry->unk4 & 0xFF, entry->unk5 & 0xFF);
                kind = entry->unkC;
                if (kind == 0 || kind == 2) {
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

s32 actorCollisionPatternMatches(s16 actorType, s16 actorFlags, s16 pattern) {
    if (pattern == actorType) {
        return 1;
    }
    switch (pattern) {
    case -1:
        if (actorFlags == 1) {
            return 1;
        }
        break;
    case -2:
        if (actorFlags == 2) {
            return 1;
        }
        break;
    case -8:
        if (actorFlags == 0x80) {
            return 1;
        }
        break;
    case -3:
        if (actorFlags == 4) {
            return 1;
        }
        break;
    case -4:
        if (actorFlags == 8) {
            return 1;
        }
        break;
    case -5:
        if (actorFlags == 0x10) {
            return 1;
        }
        break;
    case -6:
        if (actorFlags == 0x20) {
            return 1;
        }
        break;
    case -7:
        if (actorFlags == 0x40) {
            return 1;
        }
        break;
    }
    return 0;
}


void func_80675D70(s32 actor) {
    if (D_807FBB70.unk200 < 2) {
        D_807FBB70.unk1FC = actor;
        D_807FBB70.unk200 = 1;
    }
    if (D_807FBB70.unk201 < 0xF) {
        D_807FBB70.unk204[D_807FBB70.unk201] = actor;
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
void actorApplyDamage(Beh798_Actor *target, Beh798_Actor *attacker) {
    s32 currentAction;

    if ((target->unk134 -= attacker->unk136) <= 0) {
        D_807FBB70.unk200 = 9;
        return;
    }
    currentAction = D_807FBB70.unk200;
    if (currentAction == 6) {
        currentAction = D_807FBB70.unk200 = 4;
    }
    if (currentAction == 7) {
        D_807FBB70.unk200 = 5;
    }
}

typedef struct CollisionTableEntry {
    s16 unk0;
    s32 unk4;
} CollisionTableEntry;

s32 actorCollisionFindTableEntry(CollisionTableEntry *table, s16 actorType, s16 actorFlags) {
    s32 s1;
    s32 s2;
    s32 match;

    do {
        s2 = table->unk0;
        s1 = s2;
        s2 = table->unk4;
        match = actorCollisionPatternMatches(actorType, actorFlags, s1);
        table++;
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

void actorCollisionCheckBoundingBoxes(CollisionBoundingActor *actor) {
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
    targetType = actor->unk4->unk0->unk10;
    sub174 = actor->unk174;
    targetVal = (s32)actor->unk4->unk0->unk4;
    a3 = 0;
    valid = 1;

    if (targetType == -1) {
        actor->unk132 = 0;
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
                actor->unk132 = entry->unk6;
                actor->unk136 = entry->unk8;
                if (entry->unkA & 1) {
                    actor->unk64 |= 0x80;
                } else {
                    actor->unk64 &= ~0x80;
                }
                actorCollisionUpdateNodeFlags((Actor *)actor, entry->unk9);
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

    actor->unk132 = 0;
    actor->unk136 = 0;
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

void actorCollisionUpdateNodeFlags(Actor *actor, u8 flagIndex) {
    s32 match;
    s16 i;
    s8 *ptr;

    func_8067618C(actor, (s8 *)&flagIndex);
    do {} while (0); // FAKE: regalloc s1/s2 swap
    actorClearAllNodeFlags(actor);
    ptr = D_80748E50[flagIndex];
    if (*ptr != -1) {
        do {
            actorSetNodeFlag(actor, *ptr);
            match = 0;
            i = 0;
            do {
                if ((actor->actorType == D_80748F58[i].unk0) && (*ptr == D_80748F58[i].unk2)) {
                    actorSetNodeValue(actor, *ptr, D_80748F58[i].unk4);
                    match = 1;
                } else {
                    actorSetNodeValue(actor, *ptr, 0);
                    i++;
                }
            } while ((i < 24) && (!match));
            ptr++;
        } while (*ptr != -1);
    }
}

extern s32 gCurrentMap;
void func_8067618C(Actor *actor, s8 *outFlagIndex) {
    if ((gCurrentMap == 0x53) && (actor->actorType == 6) && (actor->state == 0x1E)) {
        *outFlagIndex = 0x15;
    }
}


typedef struct ActorTypeStat {
    s16 unk0;
    s16 unk2;
} ActorTypeStat;
extern ActorTypeStat D_8074D0C4[];
extern ActorTypeStat D_8074D0C6[];

void actorInitHealth(Beh798_Actor *actor) {
    actor->unk134 = D_8074D0C4[actor->unk58].unk0;
}

void actorInitDamage(Beh798_Actor *actor) {
    actor->unk136 = D_8074D0C6[actor->unk58].unk0;
}

typedef struct Beh798_8074C608 {
    u8 unk0;
    u8 pad[7];
} Beh798_8074C608;
extern Beh798_8074C608 D_8074C608[];

u8 func_80676208(Actor *actor) {
    return D_8074C608[actor->actorType].unk0;
}

s32 func_80676220(s16 actorType) {
    if ((actorType == 0xBB) || (actorType == 0xEB) || (actorType == 0x123)) {
        return 0;
    }
    return 1;
}

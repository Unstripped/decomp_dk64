#include "common.h"
#include "actor.h"
#include "proto/global/70FD0.h"
#include "proto/global/7A510.h"
#include "proto/global/7CA80.h"


typedef struct CollisionCallbackPayload {
    u8 pad0[0x18];
    s32 instanceId;
} CollisionCallbackPayload;

typedef struct CollisionInteractionEntry {
    s16 targetMask;
    s16 attackerMask;
    s32 (*filter)(Actor *, Actor *, ActorCallbackNode *);
    u8 phase;
    u8 event;
    u8 chain;
    u8 padB;
} CollisionInteractionEntry;

typedef struct CollisionTableEntry {
    s16 pattern;
    s32 entries;
} CollisionTableEntry;

typedef struct CollisionTableSlot {
    CollisionTableEntry *table;
    u8 unk4;
    u8 pad5[3];
} CollisionTableSlot;

extern CollisionTableSlot D_8074C604[];


void actorCollisionProcessHit(Actor *targetActor, ActorCallbackNode *node) {
    CollisionInteractionEntry *entry;
    s32 done;
    Actor *attacker;
    s32 interactions;
    CollisionTableEntry *table;
    u8 entryAllowed;
    s32 i;
    PlayerState *playerState;
    u8 hitPhase;
    u8 curPhase;

    attacker = node->source;
    i = 0;
    done = 0;
    if (actorTableContains(attacker) && attacker->instanceId == ((CollisionCallbackPayload *)node->unk10)->instanceId) {
        table = D_8074C604[targetActor->actorType].table;
        if (table == NULL) {
            if (attacker->flags & 0x20000) {
                func_80675D70(attacker);
            }
        } else {
            interactions = actorCollisionFindTableEntry(table, attacker->actorType, attacker->collisionFlags);
            if ((attacker->flags & 0x80000) || (targetActor->flags & 0x80000)) {
                if (targetActor == attacker->parentActor || attacker == targetActor->parentActor) {
                    return;
                }
            }
            if (interactions == 0) {
                if (attacker->flags & 0x20000) {
                    func_80675D70(attacker);
                }
            } else {
                while (!done) {
                    entry = &((CollisionInteractionEntry *)interactions)[i];
                    if ((entry->targetMask & targetActor->interactionType) && (entry->attackerMask & attacker->interactionType)) {
                        if (entry->filter != NULL) {
                            entryAllowed = entry->filter(targetActor, attacker, node);
                        } else {
                            entryAllowed = 1;
                        }
                        if (entryAllowed) {
                            hitPhase = entry->phase;
                            curPhase = gActorGlobalState.bossFightPhase;
                            if (curPhase < hitPhase) {
                                gActorGlobalState.targetActor = attacker;
                                gActorGlobalState.bossFightPhase = ((u8 *)interactions)[i * 12 + 8];  // FAKE: byte re-read through interactions (not entry->phase) saves an instruction and keeps the entry induction in $s1 (Q0589)
                            }
                            if (gActorGlobalState.unk201 < 0xF) {
                                gActorGlobalState.unk204[gActorGlobalState.unk201] = attacker;
                                gActorGlobalState.unk244[gActorGlobalState.unk201] = entry->event;
                                gActorGlobalState.unk201++;
                                if (attacker->collisionFlags & 1) {
                                    playerState = attacker->customState;
                                    if (playerState->surfaceTimer != 0) {
                                        if (D_8074C604[targetActor->actorType].unk4 != 0) {
                                            switch (gActorGlobalState.unk244[gActorGlobalState.unk201 - 1]) {
                                            case 5:
                                            case 0xF:
                                                gActorGlobalState.unk201--;
                                                break;
                                            }
                                        }
                                    }
                                    if ((targetActor->collisionFlags & 2) && func_80676220(targetActor->actorType)) {
                                        attacker->renderFlags |= 0x1000;
                                    }
                                }
                            }
                            if (entry->chain == 0 || entry->chain == 2) {
                                done = 1;
                            }
                        }
                    }
                    if (entry->chain == 0) {
                        done = 1;
                    }
                    i++;
                }
                if (targetActor->flags & 0x20000000) {
                    gActorGlobalState.bossFightPhase = 1;
                }
                if (gActorGlobalState.bossFightPhase == 6 || gActorGlobalState.bossFightPhase == 7) {
                    actorApplyDamage(targetActor, attacker);
                }
                actorCollisionRunInteractionTable(targetActor, attacker);
            }
        }
    }
}

typedef struct InteractionEntry {
    s16 patternA;
    s16 patternB;
    s8 phase;
    s8 event;
    void (*handler)(Actor *, Actor *, u8, u8);
    u8 chain;
} InteractionEntry;

extern InteractionEntry D_8074ABCC[];

void actorCollisionRunInteractionTable(Actor *actorA, Actor *actorB) {
    InteractionEntry *entry;
    s32 done;
    s32 kind;
    s32 found;
    s32 j;

    done = 0;
    for (entry = D_8074ABCC; !done; entry++) {
        if (actorCollisionPatternMatches(actorA->actorType, actorA->collisionFlags, entry->patternA) &&
            actorCollisionPatternMatches(actorB->actorType, actorB->collisionFlags, entry->patternB) &&
            ((entry->phase == -1) || entry->phase == gActorGlobalState.bossFightPhase)) {
            if (entry->event != -1) {
                if (1) {  // FAKE: extra block lowers gActorGlobalState const priority vs actorB (s0/s1 swap)
                    found = 0;
                }
                for (j = 0; !found && j < gActorGlobalState.unk201;) {
                    if (actorB == gActorGlobalState.unk204[j] && gActorGlobalState.unk244[j] == ((s8 *)entry)[5]) {  // FAKE: byte-indexed event read makes IDO emit the load operand first (bnel t2,t0)
                        found = 1;
                    } else {
                        j++;
                    }
                }
            } else {
                found = 1;
            }
            if (found) {
                entry->handler(actorA, actorB, entry->phase, entry->event);
                kind = entry->chain;
                if (kind == 0 || kind == 2) {
                    done = 1;
                }
            }
        }
        if (entry->chain == 0) {
            done = 1;
        }
    }
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


void func_80675D70(Actor *actor) {
    if (gActorGlobalState.bossFightPhase < 2) {
        gActorGlobalState.targetActor = actor;
        gActorGlobalState.bossFightPhase = 1;
    }
    if (gActorGlobalState.unk201 < 0xF) {
        gActorGlobalState.unk204[gActorGlobalState.unk201] = actor;
        gActorGlobalState.unk244[gActorGlobalState.unk201] = 2;
        gActorGlobalState.unk201++;
    }
}

void actorApplyDamage(Actor *target, Actor *attacker) {
    if ((target->health -= attacker->damage) <= 0) {
        gActorGlobalState.bossFightPhase = 9;
        return;
    }
    if (gActorGlobalState.bossFightPhase == 6) {
        gActorGlobalState.bossFightPhase = 4;
    }
    if (gActorGlobalState.bossFightPhase == 7) {
        gActorGlobalState.bossFightPhase = 5;
    }
}

s32 actorCollisionFindTableEntry(CollisionTableEntry *table, s16 actorType, s16 actorFlags) {
    s32 pattern;
    s32 entries;
    s32 match;

    do {
        entries = table->pattern;  // FAKE: dead def raises the result uopt priority so it colours $s2 before the parameter copies (Q0385)
        pattern = entries;
        entries = table->entries;
        match = actorCollisionPatternMatches(actorType, actorFlags, pattern);
        table++;
        if (match) {
            break;
        }
    } while (pattern != 0);
    return entries;
}

typedef struct CollisionThresholdEntry {
    s16 animId;
    s16 frameMin;
    s16 frameMax;
    s16 interactionType;
    u8 damage;
    u8 nodeFlagSet;
    u8 flags;
    u8 padB;
} CollisionThresholdEntry;

extern CollisionThresholdEntry D_80748FE8[];

void actorCollisionCheckBoundingBoxes(Actor *actor) {
    s16 animId;
    s16 frame;
    s32 index;
    s32 retry;
    s32 done;
    CollisionThresholdEntry *entry;
    PlayerState *playerState;
    u8 pad;
    u8 valid;

    done = 0;
    index = 0;
    animId = actor->sub4->model->animId;
    playerState = actor->customState;
    frame = actor->sub4->model->frame;
    retry = 0;
    valid = 1;

    if (animId == -1) {
        actor->interactionType = 0;
        return;
    }

    if (playerState->unk11E != -1) {
        index = playerState->unk11E;
        retry = 1;
    }

    do {
        if (D_80748FE8[index].animId == -1) {
            done = 1;
        } else if (animId == D_80748FE8[index].animId) {
            if ((frame >= D_80748FE8[index].frameMin) && (frame <= D_80748FE8[index].frameMax)) {
                entry = &D_80748FE8[index];
                actor->interactionType = entry->interactionType;
                actor->damage = entry->damage;
                if (entry->flags & 1) {
                    actor->renderFlags |= 0x80;
                } else {
                    actor->renderFlags &= ~0x80;
                }
                actorCollisionUpdateNodeFlags(actor, entry->nodeFlagSet);
                if (valid) {
                    playerState->unk11E = index;
                } else {
                    playerState->unk11E = -1;
                }
                return;
            }
            valid = 0;
        }

        if (retry) {
            index = 0;
            retry = 0;
            done = 0;
        } else {
            index++;
        }
    } while (!done);

    actor->interactionType = 0;
    actor->damage = 0;
}

typedef struct CollisionNodeFlagEntry {
    u16 actorType;
    u8 node;
    u8 pad3;
    u16 value;
} CollisionNodeFlagEntry;

extern s8 D_80748E50[][9];
extern CollisionNodeFlagEntry D_80748F58[];


void actorCollisionUpdateNodeFlags(Actor *actor, u8 flagIndex) {
    s32 match;
    s16 i;
    s8 *ptr;

    func_8067618C(actor, &flagIndex);
    actorClearAllNodeFlags(actor);
    ptr = D_80748E50[flagIndex];
    if (*ptr != -1) {
        do {
            actorSetNodeFlag(actor, *ptr);
            match = 0;
            for (i = 0; i < 24 && !match;) {
                if ((actor->actorType == D_80748F58[i].actorType) && (*ptr == D_80748F58[i].node)) {
                    actorSetNodeValue(actor, *ptr, D_80748F58[i].value);
                    match = 1;
                } else {
                    actorSetNodeValue(actor, *ptr, 0);
                    i++;
                }
            }
            ptr++;
        } while (*ptr != -1);
    }
}

extern s32 gCurrentMap;
void func_8067618C(Actor *actor, u8 *outFlagIndex) {
    if ((gCurrentMap == 0x53) && (actor->actorType == 6) && (actor->state == 0x1E)) {
        *outFlagIndex = 0x15;
    }
}


typedef struct ActorTypeStat {
    s16 health;
    s16 damage;
} ActorTypeStat;
extern ActorTypeStat D_8074D0C4[];

void actorInitHealth(Actor *actor) {
    actor->health = D_8074D0C4[actor->actorType].health;
}

void actorInitDamage(Actor *actor) {
    actor->damage = D_8074D0C4[actor->actorType].damage;
}

u8 func_80676208(Actor *actor) {
    return D_8074C604[actor->actorType].unk4;
}

s32 func_80676220(s16 actorType) {
    if ((actorType == 0xBB) || (actorType == 0xEB) || (actorType == 0x123)) {
        return 0;
    }
    return 1;
}

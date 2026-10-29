#include "common.h"

typedef struct ActorConfig8F050 {
    s16 unk0;
    s16 unk2;
    f32 unk4;
    u8 unk8;
    u8 unk9;
    s16 unkA;
    s32 unkC[2];
} ActorConfig8F050;

extern ActorConfig8F050 D_80750100[];
extern s16 D_80750102[];

typedef struct Actor4C {
    u8 pad[0x4C];
    s32 unk4C;
} Actor4C;

typedef struct Actor146 {
    u8 pad[0x146];
    s16 unk146;
} Actor146;

s32 func_80612E90(void *, s32, s32);
void animSetLoopLimit(s32, s32, s32);
void animSetFinished(s32, s32, s32);
void animSetFrameAndSubframe(s32, s32, s16, f32);

void animStopAtFrame(s32 arg0, s32 arg1, s32 arg2) {
    animSetLoopLimit(arg0, arg1, -1);
    animSetFinished(arg0, arg1, 1);
    animSetFrameAndSubframe(arg0, arg1, arg2, 0.0f);
}

s32 actorConfigLookup(s32 arg0, s32 *arg1) {
    ActorConfig8F050 *cfg;
    s32 found;
    u32 i;
    u32 next;

    if (arg0 && arg0 && arg0) {} // FAKE
    cfg = D_80750100;
    found = 0;
    *arg1 = 0;
    i = 0; do {
        next = i + 1;
        if (arg0 == cfg[i].unk0) {
            found = 1;
            next = i;
        } else {
            *arg1 = next;
            i = next;
        }
    } while (next < 7 && !found);
    return found;
}

void func_8068A404(Actor4C *arg0, s32 arg1, s32 arg2) {
    s32 i;
    s32 temp;

    if (arg0->unk4C == 0) {
        arg0->unk4C = func_80612E90(arg0, *(s16 *)((u8 *)D_80750102 + arg1 * 20), 0);
    }
    for (i = 0; i < 8; i += 4) {
        temp = *(s32 *)((u8 *)&D_80750100[arg1] + i + 0xC);
        if (temp != -1) {
            animStopAtFrame((s32)arg0, temp, arg2);
        }
    }
}

s32 actorConfigLookup(s32, s32 *);

void func_8068A4C8(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp1C;

    if (actorConfigLookup(arg1, &sp1C)) {
        func_8068A404((Actor4C *)arg0, sp1C, arg2);
    }
}

#ifdef NON_MATCHING
typedef struct ProximityPlayerPos {
    u8 pad[0x210];
    f32 unk210;
    f32 unk214;
    f32 unk218;
} ProximityPlayerPos;

typedef struct ProximitySub174 {
    u8 pad[0x1A4];
    u8 unk1A4;
} ProximitySub174;

typedef struct ProximityActor {
    u8 pad0[0x4C];
    s32 unk4C;
    u8 pad50[0x8];
    s32 unk58;
    u8 pad5C[0x4];
    s32 unk60;
    u8 pad64[0x18];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xEC];
    ProximitySub174 *unk174;
} ProximityActor;

typedef struct ProximityActorEntry {
    ProximityActor *actor;
    u32 unk4;
} ProximityActorEntry;

extern u16 gActiveActorCount;
extern ProximityActorEntry gActiveActors[];
extern ProximityPlayerPos *D_807FC924;
extern u8 D_807FC928;
extern s32 D_807552F4[];

void func_80613794(void *, u32);
f32 renderScaleDistanceByFov(f32);

void actorProximityUpdate(void) {
    s32 pad;
    s32 sp80;
    s32 pad2[3];
    s32 var_s1;
    ProximityActorEntry *entry_ptr;
    ProximityActor *actor;
    ActorConfig8F050 *entry;
    f32 dist_sq;
    f32 r;
    s32 a2;

    var_s1 = 0;
    if ((s32)gActiveActorCount > 0) {
        entry_ptr = gActiveActors;
        do {
            actor = entry_ptr->actor;
            if (!(actor->unk60 & 0x2000) && (actor->unk60 & 0x100)) {
                dist_sq = ((actor->unk84 - D_807FC924->unk218) * (actor->unk84 - D_807FC924->unk218)) +
                          (((actor->unk7C - D_807FC924->unk210) * (actor->unk7C - D_807FC924->unk210)) +
                           ((actor->unk80 - D_807FC924->unk214) * (actor->unk80 - D_807FC924->unk214)));
                if (actorConfigLookup(actor->unk58, &sp80) != 0) {
                    r = renderScaleDistanceByFov(((ActorConfig8F050 *)((u8 *)D_80750100 + sp80 * 20))->unk4);
                    entry = (ActorConfig8F050 *)((u8 *)D_80750100 + sp80 * 20);
                    switch (entry->unk8) {
                    case 0:
                        if (D_807FC928 >= 2) {
                            pad = actor->unk174->unk1A4;
                            a2 = D_807552F4[pad];
                            if (a2 >= 0) {
                                func_8068A404((Actor4C *)actor, sp80, a2);
                            }
                        }
                        break;
                    case 1:
                        if (r * r < dist_sq) {
                            if (actor->unk4C == 0) {
                                actor->unk4C = func_80612E90(actor, entry->unk2, 0);
                            }
                        } else if (actor->unk4C != 0) {
                            func_80613794(actor, 1);
                        }
                        break;
                    case 2:
                        if (dist_sq < r * r) {
                            if (actor->unk4C == 0) {
                                actor->unk4C = func_80612E90(actor, entry->unk2, 0);
                            }
                        } else if (actor->unk4C != 0) {
                            func_80613794(actor, 1);
                        }
                        break;
                    }
                }
            }
            var_s1++;
            entry_ptr++;
        } while (var_s1 < (s32)gActiveActorCount);
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/8F050/actorProximityUpdate.s")
#endif

void func_8068A764(Actor146 *arg0, u8 arg1) {
    arg0->unk146 |= (1 << arg1);
}

void func_8068A784(Actor146 *arg0, u8 arg1) {
    arg0->unk146 &= ~(1 << arg1);
}

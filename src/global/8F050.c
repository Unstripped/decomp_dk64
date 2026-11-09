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

s32 controllerAnimStateLoadAsset(void *, s32, s32);
void animSetLoopLimit(void *, s32, s16);
void animSetFinished(void *, s32, u8);
void animSetFrameAndSubframe(s32, s32, s16, f32);

void animStopAtFrame(s32 actor, s32 animSlot, s32 frame) {
    animSetLoopLimit(actor, animSlot, -1);
    animSetFinished(actor, animSlot, 1);
    animSetFrameAndSubframe(actor, animSlot, frame, 0.0f);
}

s32 actorConfigLookup(s32 actorType, s32 *outIndex) {
    ActorConfig8F050 *cfg;
    s32 found;
    u32 i;
    u32 next;

    if (actorType && actorType && actorType) {} // FAKE
    cfg = D_80750100;
    found = 0;
    *outIndex = 0;
    i = 0; do {
        next = i + 1;
        if (actorType == cfg[i].unk0) {
            found = 1;
            next = i;
        } else {
            *outIndex = next;
            i = next;
        }
    } while (next < 7 && !found);
    return found;
}

void actorConfigApplyAnimFrame(Actor4C *actor, s32 cfgIndex, s32 frame) {
    s32 i;
    s32 temp;

    if (actor->unk4C == 0) {
        actor->unk4C = controllerAnimStateLoadAsset(actor, *(s16 *)((u8 *)D_80750102 + cfgIndex * 20), 0);
    }
    for (i = 0; i < 8; i += 4) {
        temp = *(s32 *)((u8 *)&D_80750100[cfgIndex] + i + 0xC);
        if (temp != -1) {
            animStopAtFrame((s32)actor, temp, frame);
        }
    }
}

s32 actorConfigLookup(s32, s32 *);

void actorConfigApplyAnimFrameByType(s32 actor, s32 actorType, s32 frame) {
    s32 cfgIndex;

    if (actorConfigLookup(actorType, &cfgIndex)) {
        actorConfigApplyAnimFrame((Actor4C *)actor, cfgIndex, frame);
    }
}

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
extern ProximityPlayerPos *gPlayerSlots;
extern u8 gPlayerCount;
extern s32 D_807552F4[];

void controllerAnimFreeSub(void *, u32);
f32 renderScaleDistanceByFov(f32);

void actorProximityUpdate(void) {
    ProximitySub174 *sub;
    s32 cfgIndex;
    s32 pad[3];
    s32 i;
    ProximityActor *actor;
    f32 dist_sq;
    f32 r;
    s32 a2;

    for (i = 0; i < (s32)gActiveActorCount; i++) {
        actor = gActiveActors[i].actor;
        if (!(actor->unk60 & 0x2000) && (actor->unk60 & 0x100)) {
            dist_sq = ((actor->unk84 - gPlayerSlots->unk218) * (actor->unk84 - gPlayerSlots->unk218)) +
                      (((actor->unk7C - gPlayerSlots->unk210) * (actor->unk7C - gPlayerSlots->unk210)) +
                       ((actor->unk80 - gPlayerSlots->unk214) * (actor->unk80 - gPlayerSlots->unk214)));
            if (actorConfigLookup(actor->unk58, &cfgIndex) != 0) {
                r = renderScaleDistanceByFov(D_80750100[cfgIndex].unk4);
                switch (D_80750100[cfgIndex].unk8) {
                case 0:
                    if (gPlayerCount >= 2) {
                        sub = actor->unk174;
                        a2 = D_807552F4[sub->unk1A4];
                        if (a2 >= 0) {
                            actorConfigApplyAnimFrame((Actor4C *)actor, cfgIndex, a2);
                        }
                    }
                    break;
                case 1:
                    if (r * r < dist_sq) {
                        if (actor->unk4C == 0) {
                            actor->unk4C = controllerAnimStateLoadAsset(actor, D_80750100[cfgIndex].unk2, 0);
                        }
                    } else if (actor->unk4C != 0) {
                        controllerAnimFreeSub(actor, 1);
                    }
                    break;
                case 2:
                    if (dist_sq < r * r) {
                        if (actor->unk4C == 0) {
                            actor->unk4C = controllerAnimStateLoadAsset(actor, D_80750100[cfgIndex].unk2, 0);
                        }
                    } else if (actor->unk4C != 0) {
                        controllerAnimFreeSub(actor, 1);
                    }
                    break;
                }
            }
        }
    }
}

void func_8068A764(Actor146 *actor, u8 bit) {
    actor->unk146 |= (1 << bit);
}

void func_8068A784(Actor146 *actor, u8 bit) {
    actor->unk146 &= ~(1 << bit);
}

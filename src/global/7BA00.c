#include "common.h"
#include "actor.h"

typedef struct PlayerData {
    u8 pad[0x2C0];
    u8 unk2C0;
    u8 pad2[0x2F0 - 0x2C1];
} PlayerData;

extern PlayerData *gPlayerSlots;
extern Actor *gPrimaryPlayerActor;
void sfxPlayAtPositionPooled(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);
s32 playerCanTakeHit(Actor*);

void actorTriggerPlayerKnockbackSound(Actor* attacker, Actor* target, s32 unused2, s32 unused3) {
    u8 kong;
    u8* beh;

    if (target == gPrimaryPlayerActor) {
        beh = target->customState;
        kong = beh[0x1A4];
        *(s32*)(beh + 0x1F0) |= 0x80000;
        if (*(s16*)(beh + 0xD4) == (beh[0x1A4] * 0)) { // FAKE: keeps kong live across check
            if (gPrimaryPlayerActor->state != 0x36) {
                if (playerCanTakeHit(gPrimaryPlayerActor)) {
                    if (gPrimaryPlayerActor->actorType == 6 && gPlayerSlots[kong].unk2C0 == 2) {
                        if (gPrimaryPlayerActor->state != 0x31) {
                            if (attacker->collisionFlags & 0x80) {
                                sfxPlayAtPositionPooled(target->x, target->y, target->z, 0x1E0, 0xFF, 0x64, 0x1E, 0, 0.3f, 0);
                            }
                        }
                    } else if (attacker->actorType == 0xBB) {
                        sfxPlayAtPositionPooled(target->x, target->y, target->z, 0x37, 0xFF, 0x7F, 0x1E, 0x5A, 0.3f, 0);
                    } else {
                        sfxPlayAtPositionPooled(target->x, target->y, target->z, 0x1E0, 0xFF, 0x7F, 0x1E, 0x5A, 0.3f, 0);
                    }
                }
            }
        }
    }
}

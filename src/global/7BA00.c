#include "common.h"
#include "actor.h"

typedef struct PlayerData {
    u8 pad[0x2C0];
    u8 unk2C0;
    u8 pad2[0x2F0 - 0x2C1];
} PlayerData;

extern PlayerData *gPlayerSlots;
extern Actor *D_807FBB4C;
void sfxPlayAtPositionPooled(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);
s32 playerCanTakeHit(Actor*);

void actorTriggerPlayerKnockbackSound(Actor* arg0, Actor* arg1, s32 arg2, s32 arg3) {
    u8 kong;
    u8* beh;

    if (arg1 == D_807FBB4C) {
        beh = arg1->unk174;
        kong = beh[0x1A4];
        *(s32*)(beh + 0x1F0) |= 0x80000;
        if (*(s16*)(beh + 0xD4) == (beh[0x1A4] * 0)) { // FAKE: keeps kong live across check
            if (D_807FBB4C->unk154 != 0x36) {
                if (playerCanTakeHit(D_807FBB4C)) {
                    if (D_807FBB4C->unk58 == 6 && gPlayerSlots[kong].unk2C0 == 2) {
                        if (D_807FBB4C->unk154 != 0x31) {
                            if (arg0->unk5C & 0x80) {
                                sfxPlayAtPositionPooled(arg1->unk7C, arg1->unk80, arg1->unk84, 0x1E0, 0xFF, 0x64, 0x1E, 0, 0.3f, 0);
                            }
                        }
                    } else if (arg0->unk58 == 0xBB) {
                        sfxPlayAtPositionPooled(arg1->unk7C, arg1->unk80, arg1->unk84, 0x37, 0xFF, 0x7F, 0x1E, 0x5A, 0.3f, 0);
                    } else {
                        sfxPlayAtPositionPooled(arg1->unk7C, arg1->unk80, arg1->unk84, 0x1E0, 0xFF, 0x7F, 0x1E, 0x5A, 0.3f, 0);
                    }
                }
            }
        }
    }
}

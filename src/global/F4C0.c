#include "common.h"

typedef struct {
    s16 unk0;
    u8 unk2;
    u8 unk3;
    s16 unk4;
} MapActionEntry;

typedef struct { u8 unk0[0x5C]; u16 unk5C; } PlayerStateContext;
typedef struct { u8 unk0[0x1A4]; u8 playerIndex; } GlobalContextView;
typedef struct { u8 unk0[0x2C0]; u8 unk2C0; u8 pad2C1[0x2F]; } PlayerRaceContext;

extern MapActionEntry D_80746340[];
extern s16 D_80746344[];
extern s16 D_80745BDE[];
extern s32 gCurrentMap;
extern PlayerStateContext *gCurrentActor;
extern GlobalContextView *gActivePlayerState;
extern PlayerRaceContext *gPlayerSlots;

s16 mapActionLookupEntry(s16 actionId, void *actor, u8 subType) {
    s16 lookupAction;
    s32 i;
    s32 found;

    i = 0;
    found = 0;
    while ((i < 14) && (found == 0)) {
        if ((actionId == D_80746340[i].unk0) && (subType == D_80746340[i].unk2)) {
            found = 1;
        } else {
            i++;
        }
    }
    if (found != 0) {
        if ((gCurrentActor->unk5C & 1) && (gPlayerSlots[gActivePlayerState->playerIndex].unk2C0 == 2)) {
            return 0x97;
        }
        if (*((u16 *)((u8 *)actor + 0x6A)) & 4) {
            return 0xA;
        }
        lookupAction = *(s16 *)((u8 *)D_80746344 + i * 6);
        if (lookupAction == 0) {
            return *(s16 *)((u8 *)D_80745BDE + gCurrentMap * 4);
        }
        return lookupAction;
    }
    return actionId;
}

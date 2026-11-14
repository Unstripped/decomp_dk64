#include "common.h"
#include "map.h"
#include "actor.h"
#include "sched.h"
#include "proto/global/F4C0.h"

typedef struct {
    s16 actionId;
    u8 subType;
    u8 pad3;
    s16 mappedAction;
} MapActionEntry;

extern MapActionEntry D_80746340[];
extern s32 gCurrentMap;
extern Actor *gCurrentActor;
extern PlayerState *gActivePlayerState;
extern PlayerStruct *gPlayerSlots;

s16 mapActionLookupEntry(s16 actionId, Actor *actor, u8 subType) {
    s16 lookupAction;
    s32 i;
    s32 found;

    i = 0;
    found = 0;
    while ((i < 14) && (found == 0)) {
        if ((actionId == D_80746340[i].actionId) && (subType == D_80746340[i].subType)) {
            found = 1;
        } else {
            i++;
        }
    }
    if (found != 0) {
        if ((gCurrentActor->collisionFlags & 1) && (gPlayerSlots[gActivePlayerState->playerIndex].unk2C0 == 2)) {
            return 0x97;
        }
        if (actor->contactFlags & 4) {
            return 0xA;
        }
        lookupAction = D_80746340[i].mappedAction;
        if (lookupAction == 0) {
            return D_80745BDC[gCurrentMap].defaultAction;
        }
        return lookupAction;
    }
    return actionId;
}

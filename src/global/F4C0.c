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

MapActionEntry gMapActionRemapTable[14] = {
    { 1, 0, 0, 0 },
    { 1, 1, 0, 3 },
    { 1, 2, 0, 5 },
    { 1, 3, 0, 6 },
    { 1, 4, 0, 7 },
    { 1, 5, 0, 4 },
    { 1, 6, 0, 0xA },
    { 1, 7, 0, 8 },
    { 1, 8, 0, 0x19 },
    { 1, 9, 0, 1 },
    { 1, 10, 0, 2 },
    { 1, 11, 0, 0x1A },
    { 1, 12, 0, 0x1A },
    { 1, 13, 0, 0x3B0 },
};
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
    while (i < 14 && !found) {
        if (actionId == gMapActionRemapTable[i].actionId && subType == gMapActionRemapTable[i].subType) {
            found = 1;
        } else {
            i++;
        }
    }
    if (found) {
        if ((gCurrentActor->collisionFlags & 1) && gPlayerSlots[gActivePlayerState->playerIndex].unk2C0 == 2) {
            return 0x97;
        }
        if (actor->contactFlags & 4) {
            return 0xA;
        }
        lookupAction = gMapActionRemapTable[i].mappedAction;
        if (lookupAction == 0) {
            return gMapAudioTable[gCurrentMap].defaultAction;
        }
        return lookupAction;
    }
    return actionId;
}

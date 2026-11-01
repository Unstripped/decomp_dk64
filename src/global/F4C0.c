#include "common.h"

typedef struct {
    s16 unk0;
    u8 unk2;
    u8 unk3;
    s16 unk4;
} MapActionEntry;

typedef struct { u8 unk0[0x5C]; u16 unk5C; } PlayerStateContext;
typedef struct { u8 unk0[0x1A4]; u8 unk1A4; } GlobalContextView;
typedef struct { u8 unk0[0x2C0]; u8 unk2C0; u8 pad2C1[0x2F]; } PlayerRaceContext;

extern MapActionEntry D_80746340[];
extern s16 D_80746344[];
extern s16 D_80745BDE[];
extern s32 gCurrentMap;
extern PlayerStateContext *D_807FBB40;
extern GlobalContextView *gActivePlayerState;
extern PlayerRaceContext *gPlayerSlots;

s16 mapActionLookupEntry(s16 arg0, void *arg1, u8 arg2) {
    s16 temp_v1;
    s32 var_v0;
    s32 var_v1;

    var_v0 = 0;
    var_v1 = 0;
    while ((var_v0 < 14) && (var_v1 == 0)) {
        if ((arg0 == D_80746340[var_v0].unk0) && (arg2 == D_80746340[var_v0].unk2)) {
            var_v1 = 1;
        } else {
            var_v0++;
        }
    }
    if (var_v1 != 0) {
        if ((D_807FBB40->unk5C & 1) && (gPlayerSlots[gActivePlayerState->unk1A4].unk2C0 == 2)) {
            return 0x97;
        }
        if (*((u16 *)((u8 *)arg1 + 0x6A)) & 4) {
            return 0xA;
        }
        temp_v1 = *(s16 *)((u8 *)D_80746344 + var_v0 * 6);
        if (temp_v1 == 0) {
            return *(s16 *)((u8 *)D_80745BDE + gCurrentMap * 4);
        }
        return temp_v1;
    }
    return arg0;
}

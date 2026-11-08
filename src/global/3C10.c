#include "common.h"
#include "sched.h"
#include "actor.h"

typedef struct {
    u8 unk0;
    u8 pad1;
    s16 unk2;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    s16 unk10;
    s16 unk12;
    u8 unk14;
    u8 pad15[3];
    s32 unk18;
    void *unk1C;
    void *unk20;
    u8 pad24[0xC0 - 0x24];
} Struct8076A160;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Struct807447A0;


typedef struct {
    u16 unk0;
    u16 unk2;
    u8 unk4;
} Struct8074475C;

/* Extern variables */
extern u8 D_807444EC;
extern u8 D_807444F8;
extern s32 D_807444E4;
extern s32 D_807444E8;
extern u8 D_807445E0[];
extern u16 D_807446C0[];
extern s32 D_80744720[];
extern u16 D_80744734[];
extern u16 D_80744736[];
extern u16 D_80744748[];
extern Struct8074475C D_8074475C[11];
extern Struct807447A0 D_807447A0[];
extern u8 D_80744820;
extern u8 D_80744824;
extern u8 D_80744828;
extern Struct807447A0 D_8074482C[];
extern u8 gPlayerCharacterId;
const u8 D_807565E0[80] = {
    0x01, 0x0F, 0x05, 0x19, 0x07, 0x1A, 0x1E, 0x30, 0x48, 0x57, 0x2A, 0x11, 0x26, 0x0A, 0x73, 0x74,
    0x75, 0x12, 0x76, 0x77, 0x78, 0x20, 0x79, 0x7A, 0x7B, 0x42, 0x44, 0x45, 0x7C, 0x43, 0x4A, 0x4B,
    0x7D, 0x7E, 0x7F, 0x80, 0x41, 0x4D, 0x81, 0x82, 0x4E, 0x4F, 0x83, 0x60, 0x84, 0x85, 0x63, 0x86,
    0x87, 0x68, 0x88, 0x89, 0x67, 0x8A, 0x8B, 0x8C, 0x65, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93,
    0x66, 0x94, 0x95, 0x96, 0x35, 0x49, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F, 0xA0, 0xA1, 0xA2, 0x00, 0x00,
};
const u8 D_80756630[80] = {
    0x0A, 0x0B, 0x0C, 0x0D, 0x00, 0x02, 0x03, 0x04, 0x05, 0x06, 0x0E, 0x08, 0x01, 0x0F, 0x0F, 0x0F,
    0x0F, 0x10, 0x10, 0x10, 0x10, 0x11, 0x11, 0x11, 0x11, 0x12, 0x12, 0x12, 0x12, 0x13, 0x13, 0x13,
    0x13, 0x14, 0x14, 0x14, 0x14, 0x15, 0x15, 0x15, 0x16, 0x16, 0x16, 0x17, 0x17, 0x17, 0x18, 0x18,
    0x18, 0x19, 0x19, 0x19, 0x1A, 0x1A, 0x1A, 0x1A, 0x1B, 0x1B, 0x1B, 0x1B, 0x1C, 0x1C, 0x1C, 0x1C,
    0x1D, 0x1D, 0x1D, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x27, 0x23, 0x24, 0x25, 0x22, 0x26, 0x00, 0x00,
};
extern s32 D_80767CC4;
extern s32 gCurrentMap;
extern u8 D_8076A0AB;
extern u8 D_8076A0B1;
extern s8 D_8076A0B2;
extern s16 D_8076A172;
extern u8 D_8076A220;
extern s16 D_8076A232;
extern Struct8076A160 D_8076A2E0[];
extern s32 D_807F6010;
extern Actor *D_807FBB4C;
extern s32 D_807FBB60;
extern s32 D_807FBB64;
extern s32 D_807FBB68;
extern u16 D_807FC930[];
extern f32 gScreenFadeRate;

/* Function declarations */
s32 func_805FEF74(s32 map);
u8 mapGetWorldIndex(u8 map);
s32 mapGetConfigValue(u8 unused, s32 index);
u8 mapGetHubWorldIndex(u8 map, u8 checkBossMap);
u8 mapHasCollectedSufficientItems(void);
void mapSlotArrayInit(void);
void screenSetTransitionFadeType(u8 fadeType);
void screenApplyTransitionFadeType(void);
void mapSetPendingTransition(s16 map, u8 exitIndex);
void mapExecuteDeathTransition(s32 unused);
void mapExecuteVoidTransition(void);
void mapRequestTransition(s32 map, s32 exitIndex);
void mapRequestTransitionFast(s32 map, s32 exitIndex);
void mapCheckAutoTransition(void);
void func_805FF5A0();
void mapTransitionExitCurrent(s32 map, s32 exitIndex);
void mapSetTransitionExtraCounter(s8 count);
void func_805FF670(void);
s32 mapFindPreviousSavedMap(s32 *outMap, s32 *outExitIndex);
void mapTransitionToPreviousOrExit(void);
void mapTransitionToMenuOrPrevious(void);
s32 mapFindSlotByMap(s16 target);
s32 func_805FFE50(s32 map, s16 recordId, s16 value);
void mapSlotFree(s32 map);
void mapSlotArrayResetAll(void);
s32 mapFindSlotIndex();
s16 func_80600174(f32 *, f32 *, f32 *);
s32 func_80600340(s32 actorType, u8 flags, s32 *outMap);
void modelAssetGetSubtables(s32, s32 *, s32 *);
void func_806003EC(s16 index);
s32 func_8060042C(s16 index);
u8 func_80600454(s16 id, u8 *outVal);

/* External functions */
void func_8002920C(void);
void sfxAllocateChannel(s32, f32);
void heapUnregisterSurvivor(void *);
f32 func_80612790(s16);
f32 func_80612794(s16);
void camStartPath(void *, s32, s32);
void modelRecordFindAndSet(void *, void *, s16, s16);
s32 actorListFindClosestTargetIndex(s32, s32, u8, f32, f32, f32);
void actorSpawnNodeEntryScaled(s32, f32, f32, f32, s32, s32, s32, s32);
u8 playerGetResolvedKongId(s32);
void func_806F5378(void);
void slotQueueUpdate(s32, s32, s32);
s32 menuIsTransitionActive(void);
void func_80712F10(s32 *, s32 *);
s32 menuIsTransitionTypeD(void);
s32 menuIsTransitionTypeC(void);
s32 flagGet(s32, s32);
void flagSet();
void func_807313BC(void);
void heapFree(void *);

// .bss 0x8076A160-0x8076AF00
Struct8076A160 D_8076A160[18];
u8 D_8076AEE0;
u8 D_8076AEE1;
s16 D_8076AEE2;
f32 D_8076AEE4;
f32 D_8076AEE8;
f32 D_8076AEEC;
s16 D_8076AEF0;
s16 D_8076AEF2;
u16 D_8076AEF4;
u8 D_8076AEF6;
u8 D_8076AEF7;
u8 D_8076AEF8[8];

typedef struct {
    s32 unk0;
    s32 unk4;
} KeyValuePair;


extern KeyValuePair D_80744800[];

s32 func_805FEF10(s32 *outValue) {
    s32 i;
    s32 found;

    found = 0;
    for (i = 0; (u32)i < 4 && !found; i++) {
        found = D_807FBB4C->actorType == D_80744800[i].unk0;
        if (found) {
            *outValue = D_80744800[i].unk4;
        }
    }
    return found;
}

s32 func_805FEF74(s32 map) {
    s32 i;

    if (map == D_80744734[0]) {
        return 1;
    }
    for (i = 0; i < 8; i++) {
        if (map == D_80744736[i]) {
            return 1;
        }
    }
    return 0;
}

u8 mapGetWorldIndex(u8 map) {
    return D_807445E0[map];
}

s32 mapGetConfigValue(u8 unused, s32 index) {
    s32 ret = D_80744720[index];
    return ret;
}

u8 mapGetHubWorldIndex(u8 map, u8 checkBossMap) {
    u8 val;
    s32 targetMap;
    s32 exitIndex;
    s32 pad;

    targetMap = map;
    val = D_807445E0[targetMap];
    if (val == 0xD || val == 9) {
        if (mapFindPreviousSavedMap(&targetMap, &exitIndex)) {
            val = D_807445E0[targetMap];
        }
    }
    if (checkBossMap != 0) {
        if (func_805FEF74(targetMap)) {
            val = 7;
        }
    }
    return val;
}

u8 mapHasCollectedSufficientItems(void) {
    s32 index = mapGetHubWorldIndex(D_8076A0AB, 0);
    return D_807FC930[index] >= D_807446C0[index];
}

void mapSlotArrayInit(void) {
    s32 i;
    for (i = 0; i < 18; i++) {
        D_8076A160[i].unk0 = 0;
    }
}

void screenSetTransitionFadeType(u8 fadeType) {
    D_80744824 = fadeType;
}

void screenApplyTransitionFadeType(void) {
    D_8076AEE0 = D_80744824;
    D_80744824 = 1;
}

void mapSetPendingTransition(s16 map, u8 exitIndex) {
    D_80744828 = 1;
    D_8076AEF4 = map;
    D_8076AEF6 = exitIndex;
}

void mapExecuteDeathTransition(s32 unused) {
    u16 pad;
    u16 a3;
    s32 limit;
    s32 i;
    u16 t1;
    u8 found;

    limit = 11;
    i = 0;
    t1 = 0;
    found = 0;

    if (D_80744828 != 0) {
        a3 = D_8076AEF4;
        t1 = D_8076AEF6;
    } else {
        if (func_805FEF74(gCurrentMap) != 0) {
            a3 = ((u16 *)&gCurrentMap)[1];
        } else {
            unused = mapGetHubWorldIndex(((u8 *)&gCurrentMap)[3], 0);
            a3 = D_80744748[unused];
            for (; !found && (i < limit); i++) {
                if (gCurrentMap == D_8074475C[i].unk0) {
                    a3 = D_8074475C[i].unk2;
                    t1 = D_8074475C[i].unk4;
                    found = 1;
                }
            }
        }
    }
    if (!found) {
        mapSlotArrayResetAll();
    }
    mapRequestTransition(a3, t1);
    D_80744828 = 0;
}

void mapExecuteVoidTransition(void) {
    s32 targetMap;
    s32 exitIndex;

    if (gCurrentMap != 0x22) {
        mapSlotArrayResetAll();
        targetMap = D_80744734[mapGetHubWorldIndex(D_8076A0AB, 0)];
        exitIndex = 1;
    } else {
        targetMap = gCurrentMap;
        exitIndex = 0;
    }
    flagSet(0x6E, 1, 2, targetMap);
    mapRequestTransition(targetMap, exitIndex);
}

void mapRequestTransition(s32 map, s32 exitIndex) {
    func_806F5378();
    if ((D_807444EC == 6) || (menuIsTransitionActive() == 0)) {
        func_80712F10(&map, &exitIndex);
        if (map != -1) {
            if ((s32) gPlayerCharacterId >= 6) {
                gPlayerCharacterId = playerGetResolvedKongId(0);
            }
            D_8076A0B1 |= 1;
            D_8076AEF2 = (s16) gCurrentMap;
            D_807444E4 = map;
            D_807444E8 = exitIndex;
            D_8076A0B2 = 3;
            screenApplyTransitionFadeType();
            gScreenFadeRate = 1.0f;
            if ((D_807444F8 != 1) && (D_8076AEE0 == 1) && !(D_807FBB68 & 2) && (gCurrentMap != 0x4C)) {
                sfxAllocateChannel(0x2C, 1.0f);
            }
            func_807313BC();
            func_805FF5A0(map);
            if (D_807FBB64 & 1) {
                func_8002920C();
            }
        }
    }
}

void mapRequestTransitionFast(s32 map, s32 exitIndex) {
    func_806F5378();
    D_807FBB60 |= 0x100;
    D_807444E4 = map;
    D_807444E8 = exitIndex;
    D_8076AEF2 = gCurrentMap;
    func_807313BC();
    func_805FF5A0(map);
}

void mapCheckAutoTransition(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (gCurrentMap == D_807447A0[i].unk0) {
            mapRequestTransition(D_807447A0[i].unk4, D_807447A0[i].unk8);
            return;
        }
    }
}

void func_805FF5A0(void) {
    s32 idx = mapFindSlotIndex();

    if (idx != -1) {
        D_8076AEE2 = D_8076A160[idx].unk2;
        D_8076AEE4 = D_8076A160[idx].unk4;
        D_8076AEE8 = D_8076A160[idx].unk8;
        D_8076AEEC = D_8076A160[idx].unkC;
        D_8076AEF0 = D_8076A160[idx].unk10;
    } else {
        D_8076AEE2 = 0;
    }
}

void mapTransitionExitCurrent(s32 map, s32 exitIndex) {
    mapSlotFree(gCurrentMap);
    mapRequestTransition(map, exitIndex);
}

void mapSetTransitionExtraCounter(s8 count) {
    D_80744820 = count;
}

void func_805FF670(void) {
    f32 dist;
    s16 spawnX;
    s16 i;
    f32 offset;
    s32 step;
    s16 spawnZ;

    if (D_80744820 != 0) {
        camStartPath(D_807FBB4C, 2, 5);
        slotQueueUpdate(1, 0, 0);
        i = 0;
        if ((s32) D_80744820 > 0) {
            offset = 20.0f;
            step = 5;
            do {
                dist = (i * 2) + 30;
                spawnX = D_807FBB4C->x - func_80612794(D_807FBB4C->yaw) * dist;
                spawnZ = D_807FBB4C->z - func_80612790(D_807FBB4C->yaw) * dist;
                actorSpawnNodeEntryScaled(
                    0x35,
                    spawnX,
                    D_807FBB4C->y + offset + (f32)(i * step),
                    spawnZ,
                    D_807FBB4C->yaw,
                    1,
                    -1,
                    0
                );
                i++;
            } while (i < D_80744820);
        }
        D_80744820 = 0;
    }
}

s32 mapFindPreviousSavedMap(s32 *outMap, s32 *outExitIndex) {
    s32 found = 0;
    s32 i = 0;

    while (i < 18 && !found) {
        if (D_8076A160[i].unk0 != 0 && (D_8076A160[i].unk2 & 2)) {
            found = 1;
        } else {
            i++;
        }
    }

    if (found) {
        *outMap = D_8076A160[i].unk12;
        *outExitIndex = D_8076A160[i].unk14;
    }
    return found;
}

void mapTransitionToPreviousOrExit(void) {
    s32 targetMap;
    s32 exitIndex;

    if (mapFindPreviousSavedMap(&targetMap, &exitIndex) != 0) {
        mapSlotFree(gCurrentMap);
        mapRequestTransition(targetMap, exitIndex);
    } else if (menuIsTransitionTypeD() != 0) {
        mapRequestTransition(0xF, 0);
    }
}

void mapTransitionToMenuOrPrevious(void) {
    if (menuIsTransitionTypeC() != 0) {
        mapRequestTransition(0x50, 0);
    } else {
        mapTransitionToPreviousOrExit();
    }
}

s32 mapFindSlotByMap(s16 target) {
    s32 i = 0;
    s32 found = 0;
    while (i < 18 && !found) {
        if (D_8076A160[i].unk0 != 0 && D_8076A160[i].unk12 == target) {
            found = 1;
        } else {
            i++;
        }
    }
    return found;
}

typedef struct {
    u8 pad0[0x24];
    u8 rgb[52][3];
} SlotLightColors;



extern s8 D_80750ACC;
extern s32 gMapChunkCount;
extern s32 D_807FD56C;
extern s16 D_807FD570;
void func_806F5378();
void heapRegisterSurvivor(u8 **);
void modelSlotSerializeAll(u8 **, s32 *);
void modelSlotsPackRecords(u8 **, s32 *);
void lightGetColor(f32 *, f32 *, f32 *, s16);
void faultSetMessage(s32, s32, s32, s32);

void func_805FF9AC(s32 map, s32 exitIndex, s32 returnExitIndex, s16 flags) {
    Actor *cam;
    s32 serializedSize;
    s32 i;
    s32 found;
    s32 k;
    f32 r;
    f32 g;
    f32 b;
    s32 pad;
    Struct807FD580 *obj;

    found = 0;
    i = 0;
    while (i < 18 && !found) {
        if (D_8076A160[i].unk0 != 0 && gCurrentMap == D_8076A160[i].unk12) {
            found = 1;
        } else {
            i++;
        }
    }
    if (found) {
        mapSlotFree(gCurrentMap);
    } else {
        found = 0;
        i = 0;
        while (i < 18 && !found) {
            if (D_8076A160[i].unk0 == 0) {
                found = 1;
            } else {
                i++;
            }
        }
        if (!found) {
            faultSetMessage(0xA, 0, 0, 0);
        }
    }
    func_806F5378();
    modelSlotSerializeAll((u8 **)&D_8076A160[i].unk18, &serializedSize);
    heapRegisterSurvivor((u8 **)&D_8076A160[i].unk18);
    modelSlotsPackRecords((u8 **)&D_8076A160[i].unk20, (s32 *)&D_8076A160[i].unk1C);
    if (D_8076A160[i].unk20 != 0) {
        heapRegisterSurvivor((u8 **)&D_8076A160[i].unk20);
    }
    D_8076A160[i].unk2 = flags;
    if (flags & 1) {
        cam = D_807FBB4C;
        D_8076A160[i].unk4 = cam->x;
        D_8076A160[i].unk8 = cam->y;
        D_8076A160[i].unkC = cam->z;
        D_8076A160[i].unk10 = cam->yaw;
    }
    D_8076A160[i].unk12 = gCurrentMap;
    if (flags & 2) {
        D_8076A160[i].unk14 = returnExitIndex;
    }
    for (k = 0; k < gMapChunkCount; k++) {
        lightGetColor(&r, &g, &b, k);
        ((SlotLightColors *)&D_8076A160[i])->rgb[k][0] = (u32)(r * 255.0);
        ((SlotLightColors *)&D_8076A160[i])->rgb[k][1] = (u32)(g * 255.0);
        ((SlotLightColors *)&D_8076A160[i])->rgb[k][2] = (u32)(b * 255.0);
    }
    k = 1;
    D_80750ACC = k;
    obj = (Struct807FD580 *)D_807FBB4C->unk174;
    D_807FD56C = obj->stateFlags;
    if (obj->heldActor != NULL) {
        D_807FD570 = obj->heldActor->actorType;
    } else {
        D_807FD570 = 0;
    }
    D_8076A160[i].unk0 = k;
    mapRequestTransition(map, exitIndex);
}

s32 func_805FFE50(s32 map, s16 recordId, s16 value) {
    s32 i = 0;
    s32 found = 0;
    Struct8076A160 *slot;

    while (!found && i < 18) {
        if (D_8076A160[i].unk12 == map) {
            found = 1;
        } else {
            i++;
        }
    }

    if (!found) {
        return 0;
    }

    slot = &D_8076A160[i];
    modelRecordFindAndSet(slot->unk20, slot->unk1C, recordId, value);
    return 1;
}

void mapSlotFree(s32 map) {
    s32 found = 0;
    s32 i = 0;

    while (i < 18 && !found) {
        if (D_8076A160[i].unk0 != 0 && D_8076A160[i].unk12 == map) {
            found = 1;
        } else {
            i++;
        }
    }

    if (found) {
        Struct8076A160 *slot = &D_8076A160[i];
        heapUnregisterSurvivor(&slot->unk18);
        heapFree((void *)slot->unk18);
        if (slot->unk1C != 0) {
            heapUnregisterSurvivor(&slot->unk20);
            heapFree(slot->unk20);
        }
        slot->unk0 = 0;
        D_807F6010 = 0;
    }
}

void mapSlotArrayResetAll(void) {
    Struct8076A160 *ptr, *end;
    ptr = D_8076A160, end = (Struct8076A160 *)&D_8076AEE0;
    do {
        if (ptr->unk0) {
            heapUnregisterSurvivor(&ptr->unk18);
            heapFree((void *)ptr->unk18);
            if (ptr->unk1C != 0) {
                heapUnregisterSurvivor(&ptr->unk20);
                heapFree(ptr->unk20);
            }
            ptr->unk0 = 0;
        }
        ptr++;
    } while (ptr != end);
}

void mapTransitionToWorldHub(s32 index) {
    mapSlotArrayResetAll();
    mapRequestTransition(D_80744734[index], 1);
}

s32 mapFindSlotIndex(s32 map) {
    Struct8076A160 *ptr;
    s32 i;

    if (*(u8 *)D_8076A160 != 0 && map == D_8076A172) {
        return 0;
    }
    if (D_8076A220 != 0 && map == D_8076A232) {
        return 1;
    }
    i = 2;
    ptr = D_8076A2E0;
loop:
    if (ptr[0].unk0 != 0 && map == ptr[0].unk12) {
        return i;
    }
    if (ptr[1].unk0 != 0 && map == ptr[1].unk12) {
        return i + 1;
    }
    if (ptr[2].unk0 != 0 && map == ptr[2].unk12) {
        return i + 2;
    }
    if (ptr[3].unk0 != 0 && map == ptr[3].unk12) {
        return i + 3;
    }
    i += 4;
    ptr += 4;
    if (i != 18) {
        goto loop;
    }
    return -1;
}

s16 func_80600174(f32 *outX, f32 *outY, f32 *outZ) {
    s32 i;

    for (i = 0; i < 18; i++) {
        if (D_8076A160[i].unk0 != 0 && (D_8076A160[i].unk2 & 1)) {
            *outX = D_8076A160[i].unk4;
            *outY = D_8076A160[i].unk8;
            *outZ = D_8076A160[i].unkC;
            return i;
        }
    }
    return -1;
}

s32 func_80600340(s32 actorType, u8 flags, s32 *outMap) {
    s32 subtableA;
    s32 subtableB;
    f32 posX;
    f32 posY;
    f32 posZ;
    u8 idx;

    idx = func_80600174(&posX, &posY, &posZ);
    if (idx == -1) {
        return -1;
    }
    modelAssetGetSubtables(((Struct8076A160 *)&D_8076A160)[idx].unk18, &subtableA, &subtableB);
    *outMap = ((Struct8076A160 *)&D_8076A160)[idx].unk12;
    return actorListFindClosestTargetIndex(subtableB, actorType, flags, posX, posY, posZ);
}

void func_806003EC(s16 index) {
    D_807FBB64 = D_8074482C[index].unk0;
    D_807FBB68 = D_8074482C[index].unk4;
}

s32 func_8060042C(s16 index) {
    return D_8074482C[index].unk8;
}

u8 func_80600454(s16 id, u8 *outVal) {
    u8 i;
    u8 ret;
    s16 temp;
    s32 a;

    i = 0;
    ret = 0;

    while (D_807565E0[i] != 0 && id != D_807565E0[i]) {
        i++;
    }

    if (D_807565E0[i] != 0) {
        *outVal = D_80756630[i];
        if (i < 13) {
            temp = i + 0x307;
            ret = flagGet(temp, 0) == 0;
            flagSet(temp, 1, 0);
        } else {
            ret = 1;
        }
    }
    return ret;
}

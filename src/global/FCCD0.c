#include "common.h"
#include "actor.h"
#define PROTO_SKIP_mapGetHubWorldIndex // FAKE: callee prototype steer
#include "proto/boot/3D20.h"
#include "proto/global/100180.h"
#include "proto/global/117190.h"
#include "proto/global/119370.h"
#include "proto/global/11BC10.h"
#include "proto/global/135D30.h"
#include "proto/global/15050.h"
#include "proto/global/17B40.h"
#include "proto/global/3C10.h"
#include "proto/global/7130.h"
#include "proto/global/89250.h"
#include "proto/global/CC800.h"
#include "proto/global/F9450.h"
#include "proto/global/FCCD0.h"

extern Actor *gCurrentActor;
extern Actor *gSpawnedActor;
extern Actor *gActivePlayerActor;
extern Actor *gPrimaryPlayerActor;
extern void *gPlayerSlots;
extern u8 gPlayerCount;
extern u8 gCurrentPlayerIndex;
extern u8 gPlayerInventoryTable[][0x5E];
extern s32 gCurrentMap;
extern u8 gCurrentWorldId;
extern u8 gScreenRenderFlags;
extern s16 gScreenWidth;
extern s16 gScreenHeight;
extern u8 gNextGameMode;
extern u8 gGfxBufferIndex;



/* A sprite/label node hanging off a slot's unk28 list. */
typedef struct SlotQueueNode {
    s32 type;
    f32 dirX;
    f32 dirY;
    s32 delay;
    s16 fade;
    u8 pad12[2];
    void *data;
    struct SlotQueueNode *next;
} SlotQueueNode;


/* One queue entry; gSlotQueue holds 15 per player (0x2D0 bytes). */
typedef struct SlotQueueSlot {
    u16 *value;
    u16 shown;
    u8 visible;
    u8 timer;
    s32 x;
    s32 y;
    f32 worldX;
    f32 worldY;
    f32 worldZ;
    u8 pending;
    u8 pad1D[3];
    s32 state;
    s32 showArg;
    SlotQueueNode *nodes;
    u8 displayMode;
    u8 locked;
    u8 pad2E[2];
} SlotQueueSlot;

extern SlotQueueSlot *gSlotQueue;

typedef struct SlotQueueMaskNode {
    s32 flags;
    struct SlotQueueMaskNode *next;
} SlotQueueMaskNode;

extern SlotQueueMaskNode *gSlotQueueMaskList;

s32 slotQueueGetAddress(player)
u8 player;
{
    return (player * 0x2D0) + (s32)gSlotQueue;
}

typedef struct PlayerViewDist {
    u8 pad0[0x284];
    f32 viewDistance;
    u8 pad288[0x68];
} PlayerViewDist;

void func_806F8004(f32 pitch, f32 yaw, f32 *outX, f32 *outY, f32 *outZ) {
    f32 pitchMtx[4][4];
    f32 yawMtx[4][4];
    f32 tz;
    f32 ty;
    f32 tx;
    f32 scale;
    f32 dist;

    dist = ((PlayerViewDist *)gPlayerSlots)[gCurrentPlayerIndex].viewDistance;
    guRotateF(pitchMtx, pitch, 1.0f, 0.0f, 0.0f);
    guMtxXFMF(pitchMtx, 0.0f, 0.0f, -dist, &tx, &ty, &tz);
    guRotateF(yawMtx, yaw, 0.0f, 1.0f, 0.0f);
    guMtxXFMF(yawMtx, tx, ty, tz, outX, outY, outZ);
    scale = -dist / *outZ;
    *outX *= scale;
    *outY *= scale;
    *outZ = -dist;
    *outX = (f32)((f64)*outX * 10.5);
    *outY = (f32)((f64)*outY * 10.5);
    *outZ = (f32)((f64)*outZ * 10.5);
}



void slotQueueGetPosition(s32 slot, f32 *x, f32 *y, f32 *z) {
    if (slot < 0) {
        func_806F8004(16.5f, 0.0f, x, y, z);
    } else if (slot == 8) {
        func_806F8004(1.5 - gSlotQueue[slot].shown * 7, 26.0f, x, y, z);
    } else {
        *x = gSlotQueue[slot].worldX;
        *y = gSlotQueue[slot].worldY;
        *z = gSlotQueue[slot].worldZ;
    }
}






void func_806F8278(u8 player) {
    s32 sum;
    u16 (*p)[0x2F];
    s32 i;
    s32 j;
    s8 n;

    sum = 0;
    p = (u16 (*)[0x2F])((u8 *)gPlayerInventoryTable + (u32)player * 0x306);
    n = 14; // FAKE: variable s8 bound keeps the slt loop test (Q0257)
    for (i = 0; i < n; i++) {
        for (j = 0; j < 5; j++) {
            sum += p[j][i + 0x21];
        }
    }
    gSlotQueue[player * 15 + 9].shown = sum;
}


extern s16 D_80744544;
extern u16 D_80750AC4;
extern u16 D_80750AC8;
#ifndef NON_MATCHING
#endif
extern s32 mapGetHubWorldIndex(); // FAKE: callee prototype steer

/* Initialises the per-player slot queue (15 slots of 0x30 bytes per player): sets each slot's text pointer, size and
 * screen position (func_806F8004). Formatting is load-bearing: the unk8/unkC stores share one line and the dead
 * `if (player && player)` fixes the register choice for the u8 argument. */
void slotQueueInit(s32 reset) {
    u32 j;
    s32 i;
    s16 shownMask;
    u8 *fp;
    u8 world;
    SlotQueueSlot *base;
    u8 *kongInv;
    s32 off;
    s8 flag;
    u8 player;

    shownMask = D_80744544;
    world = mapGetHubWorldIndex(gCurrentWorldId, 1);
    if (gPlayerCount >= 2) {
        shownMask = 0;
    }
    if (reset != 0) {
        gSlotQueue = heapAlloc(gPlayerCount * 0x2D0);
        heapClearBlock(gSlotQueue);
        gSlotQueueMaskList = NULL;
    }
    if (gPlayerCount > 0) {
        fp = (u8 *)gPlayerInventoryTable;
        i = 0;
        do {
            kongInv = (u8 *)(playerGetResolvedKongId(i) * 0x5E);
            kongInv = (u8 *)((s32)fp + (s32)kongInv);
            player = i;
            if (player && player) { // FAKE: dead reference fixes the register for the u8 argument
            }
            base = (SlotQueueSlot *)slotQueueGetAddress(player);
            j = 0;
            off = 0;
            do {
                flag = 0;
                if (reset != 0) {
                    (base + j)->state = 0;
                    (base + j)->timer = 0;
                    (base + j)->showArg = 0;
                    (base + j)->visible = 0;
                    (base + j)->nodes = 0;
                    (base + j)->displayMode = 0;
                }
                if (func_807142D8() != 0) {
                    (base + j)->displayMode = 1;
                }
                switch (j) {
                case 0:
                    (base + j)->value = &((u16 *)(kongInv + 0xA))[world];
                    (base + j)->x = 0x1E; (base + j)->y = 0x26;
                    func_806F8004(15.5f, 26.0f, (f32 *)(off + 0x10 + (s32)base), (f32 *)(off + 0x14 + (s32)base), (f32 *)(off + 0x18 + (s32)base));
                    break;
                case 13:
                    (base + j)->value = NULL;
                    (base + j)->x = 0x122; (base + j)->y = 0x26;
                    func_806F8004(-5.5f, -26.0f, (f32 *)(off + 0x10 + (s32)base), (f32 *)(off + 0x14 + (s32)base), (f32 *)(off + 0x18 + (s32)base));
                    break;
                case 8:
                    (base + j)->value = &((u16 *)(kongInv + 0x42))[world];
                    (base + j)->x = 0x1E; (base + j)->y = 0x48;
                    func_806F8004(1.5f, 26.0f, (f32 *)(off + 0x10 + (s32)base), (f32 *)(off + 0x14 + (s32)base), (f32 *)(off + 0x18 + (s32)base));
                    break;
                case 12:
                    (base + j)->value = NULL;
                    (base + j)->x = 0xC2; (base + j)->y = 0xD0;
                    func_806F8004(-26.5f, 26.0f, (f32 *)(off + 0x10 + (s32)base), (f32 *)(off + 0x14 + (s32)base), (f32 *)(off + 0x18 + (s32)base));
                    break;
                case 10:
                    (base + j)->value = NULL;
                    (base + j)->x = 0x52; (base + j)->y = 0xD0;
                    func_806F8004(-26.5f, 26.0f, (f32 *)(off + 0x10 + (s32)base), (f32 *)(off + 0x14 + (s32)base), (f32 *)(off + 0x18 + (s32)base));
                    break;
                case 9:
                    (base + j)->value = NULL;
                    (base + j)->x = 0x7A; (base + j)->y = 0xD0;
                    break;
                case 5:
                    if (shownMask & 0x20) {
                        *(s16 *)(fp+0x2F6) = slotQueueGetMaxValue(5, i);
                        flag = 1;
                    }
                    (base + j)->value = (u16 *)(fp + 0x2F6);
                    (base + j)->x = 0x122; (base + j)->y = 0x8C;
                    func_806F8004(-5.5f, -19.0f, (f32 *)(off + 0x10 + (s32)base), (f32 *)(off + 0x14 + (s32)base), (f32 *)(off + 0x18 + (s32)base));
                    break;
                case 2:
                    (base + j)->value = (u16 *)(fp + 0x2F0);
                    (base + j)->x = 0x122; (base + j)->y = 0x48;
                    func_806F8004(8.5f, -19.0f, (f32 *)(off + 0x10 + (s32)base), (f32 *)(off + 0x14 + (s32)base), (f32 *)(off + 0x18 + (s32)base));
                    break;
                case 3:
                    if (shownMask & 0x4) {
                        *(s16 *)(fp+0x2F2) = slotQueueGetMaxValue(3, i);
                        flag = 1;
                    }
                    (base + j)->value = (u16 *)(fp + 0x2F2);
                    (base + j)->x = 0x122; (base + j)->y = 0x48;
                    func_806F8004(8.5f, -19.0f, (f32 *)(off + 0x10 + (s32)base), (f32 *)(off + 0x14 + (s32)base), (f32 *)(off + 0x18 + (s32)base));
                    break;
                case 4:
                    if (shownMask & 0x8) {
                        *(s16 *)(fp+0x2F4) = slotQueueGetMaxValue(4, i);
                        flag = 1;
                    }
                    (base + j)->value = (u16 *)(fp + 0x2F4);
                    (base + j)->x = 0x122; (base + j)->y = 0x6A;
                    func_806F8004(1.5f, -19.0f, (f32 *)(off + 0x10 + (s32)base), (f32 *)(off + 0x14 + (s32)base), (f32 *)(off + 0x18 + (s32)base));
                    break;
                case 6:
                    if (shownMask & 0x10) {
                        *(s16 *)(fp+0x2F8) = slotQueueGetMaxValue(6, i);
                        flag = 1;
                    }
                    (base + j)->value = (u16 *)(fp + 0x2F8);
                    (base + j)->x = 0x122; (base + j)->y = 0xD0;
                    func_806F8004(-19.5f, -19.0f, (f32 *)(off + 0x10 + (s32)base), (f32 *)(off + 0x14 + (s32)base), (f32 *)(off + 0x18 + (s32)base));
                    break;
                case 11:
                    (base + j)->value = &D_80750AC4;
                    (base + j)->x = 0x122; (base + j)->y = 0x26;
                    func_806F8004(16.5f, -19.0f, (f32 *)(off + 0x10 + (s32)base), (f32 *)(off + 0x14 + (s32)base), (f32 *)(off + 0x18 + (s32)base));
                    break;
                case 1:
                    if (shownMask & 0x2) {
                        *(s16 *)(kongInv+6) = slotQueueGetMaxValue(1, i);
                        flag = 1;
                    }
                    (base + j)->value = (u16 *)(kongInv + 6);
                    (base + j)->x = 0x122; (base + j)->y = 0x26;
                    func_806F8004(16.5f, -19.0f, (f32 *)(off + 0x10 + (s32)base), (f32 *)(off + 0x14 + (s32)base), (f32 *)(off + 0x18 + (s32)base));
                    break;
                case 7:
                    if (shownMask & 0x40) {
                        *(s16 *)(kongInv+8) = slotQueueGetMaxValue(7, i);
                        flag = 1;
                    }
                    (base + j)->value = (u16 *)(kongInv + 8);
                    (base + j)->x = 0x122; (base + j)->y = 0xAE;
                    func_806F8004(-12.5f, -19.0f, (f32 *)(off + 0x10 + (s32)base), (f32 *)(off + 0x14 + (s32)base), (f32 *)(off + 0x18 + (s32)base));
                    break;
                case 14:
                    (base + j)->value = &D_80750AC8;
                    (base + j)->x = 0x1E; (base + j)->y = 0x26;
                    func_806F8004(15.5f, 26.0f, (f32 *)(off + 0x10 + (s32)base), (f32 *)(off + 0x14 + (s32)base), (f32 *)(off + 0x18 + (s32)base));
                    break;
                }
                (base + j)->locked = flag;
                if (flag & 0xFF) {
                    (base + j)->displayMode = 1;
                }
                off += 0x30;
                if ((base + j)->value != NULL) {
                    (base + j)->shown = *(base + j)->value;
                }
                j++;
            } while (j != 0xF);
            func_806F8278(player);
            i++;
            fp += 0x306;
        } while (i < gPlayerCount);
    }
    if (gCurrentMap == 0x11 || gCurrentMap == 0x52) {
        slotQueueSetDisplayMode(5, 0, 1);
    }
}


void slotQueueSetShownValue(u8 slot, u8 player, s32 value) {
    ((SlotQueueSlot *)slotQueueGetAddress(player & 0xFF))[slot].shown = value;
}


s32 slotQueueGetValue(u8 index, u8 player) {
    u16 value;
    s32 world;
    s32 kong;
    u8 *pa;
    SlotQueueSlot *slot;

    pa = &player; // FAKE: keeps player memory-resident (plain lbu per use)
    value = 0;
    slot = (SlotQueueSlot *)slotQueueGetAddress(player) + index;
    switch (slot->displayMode) {
    case 2:
        break;
    case 0:
        if (slot->value != NULL) {
            if (gCurrentWorldId && gCurrentWorldId) {} // FAKE: dead reference, steers uopt candidate priority
            value = *slot->value;
        } else {
            kong = playerGetResolvedKongId(player);
            world = mapGetHubWorldIndex(gCurrentWorldId, 1);
            if (index != 0xA) {
                if (index == 0xC) {
                    value = flagGridSumRows(0x1D5, world, world, kong);
                }
            } else {
                value = flagGridSumRows(0x225, world, world, kong);
            }
        }
        break;
    case 1:
        value = 0x14;
        break;
    }
    return value;
}

void slotQueueUpdate(s32 slot, u8 show, s32 delay) {
    if ((gPlayerCount < 2) && (func_807142D8() == 0)) {
        if (slot == 8) {
            slotQueueUpdate(9, show, delay + 0xA);
            if (gCurrentMap == 0xF) {
                return;
            }
        }
        gSlotQueue[slot].showArg = show;
        if (gSlotQueue[slot].state == 0) {
            gSlotQueue[slot].timer = delay;
        } else {
            gSlotQueue[slot].timer = 0;
        }
        gSlotQueue[slot].state = 1;
        if (gSlotQueue[slot].visible == 0) {
            gSlotQueue[slot].visible = show != 0;
        }
    }
}


void slotQueueStaggerNodeDelays(s32 slot) {
    s32 delay;
    SlotQueueNode *node;

    if (slot == 8) {
        node = gSlotQueue[slot].nodes;
        delay = 0;
        if (node != NULL) {
            do {
                node->delay = delay;
                node = node->next;
                delay += 2;
            } while (node != NULL);
        }
    }
}


void slotQueueClearFlags(slot, unused)
s32 slot;
u8 unused;
{
    gSlotQueue[slot].timer = 0;
    gSlotQueue[slot].visible = 0;
    if (slot == 8) {
        slotQueueCancel(9, 0);
    }
}


void slotQueueCancel(slot)
s32 slot;
{
    s32 mask;
    SlotQueueMaskNode *node = gSlotQueueMaskList;

    gSlotQueue[slot].pending = 0;
    if (node != NULL) {
        mask = ~(1 << slot);
        do {
            node->flags &= mask;
            node = node->next;
        } while (node != NULL);
    }
    slotQueueClearFlags(slot);
}


void func_806F8DC4(u8 *alpha, s32 count, s32 slot) {
    s32 world;
    s32 kongArg;
    s32 kong;

    world = mapGetHubWorldIndex(gCurrentWorldId, 1);
    kong = playerGetResolvedKongId(0);
    kongArg = kong;
    *alpha = 0x7F;
    if (slot != 8) {
        if (slot != 0xA) {
            if ((slot == 0xC) && (flagGridSumRows(0x1D5, world, world, kongArg) != 0)) {
                *alpha = 0xFF;
            }
        } else if (flagGridSumRows(0x225, world, world, kongArg) != 0) {
            *alpha = 0xFF;
        }
    } else if (count < ((u16 *)&gPlayerInventoryTable[kong][0x42])[world]) {
        *alpha = 0xFF;
    }
}


s32 func_806F8EB4(void) {
    return flagCountRange(0x24D, 0x14, 0);
}

extern u8 D_807FC953[];
extern u8 D_807FC954[];

s32 slotQueueGetMaxValue(s32 slot, s32 player) {
    s32 kong;
    s32 max;
    s32 level;
    u8 bits;
    s32 rest;

    kong = playerGetResolvedKongId(player);
    max = 0x64;
    switch (slot) {
    case 1:
        max = 0x3E7;
        break;
    case 2:
        max = ((1 << D_807FC953[(player * 0x306) + (kong * 0x5E)]) * 0x32) & 0xFFFF;
        break;
    case 3:
        if (gPlayerCount >= 2) {
            max = 0xA;
        } else {
            max = ((1 << D_807FC953[(player * 0x306) + (kong * 0x5E)]) * 0x32) & 0xFFFF;
        }
        break;
    case 4:
        max = ((D_807FC953[(player * 0x306) + (kong * 0x5E)] * 5) + 0x14) & 0xFFFF;
        break;
    case 5:
        if (gPlayerCount >= 2) {
            max = 0xBB8;
        } else if (func_806F6EDC() != 0) {
            max = ((func_806F8EB4() * 0x96) + 0xBB8) & 0xFFFF;
        } else {
            max = 0;
        }
        break;
    case 7:
        if (gPlayerCount >= 2) {
            max = 0x14;
        } else {
            bits = D_807FC954[(player * 0x306) + (kong * 0x5E)];
            level = 1;
            if (bits & 1) {
                rest = bits;
                if (bits) {
                    do {
                        level += 1;
                        rest >>= 1;
                    } while (rest != 0);
                }
                max = (level * 5) & 0xFFFF;
            } else {
                max = 0;
            }
        }
        break;
    case 6:
        if (flagGet(0x179, 0) != 0) {
            max = (func_806F8EB4() + 0xA) & 0xFFFF;
        } else {
            max = 0;
        }
        break;
    case 9:
        max = 0xC8;
        break;
    }
    return max;
}


extern u8 gPlayerCharacterId;

void slotQueueAddValue(s32 slot, u8 player, s16 delta) {
    u8 *pa;
    u8 *kongInv;
    s16 *pad0;
    s32 slots;
    s32 flag;
    s32 total;
    s32 value;
    u16 *counter;
    SlotQueueSlot *entry;
    s32 playerIdx;

    pa = &player;  // FAKE: keeps player memory-resident (plain lbu per use)
    playerIdx = player;
    value = playerGetResolvedKongId(player);
    kongInv = (u8 *)gPlayerInventoryTable + (player * 0x306 + value * 0x5E);
    slots = slotQueueGetAddress(player);
    entry = (SlotQueueSlot *)slots + slot;
    if (((entry->locked == 0) || (delta >= 0)) && (entry->displayMode == 0)) {
        if ((slot != 0xA) && (slot != 0xC)) {
            counter = entry->value;
            if (slots > 0) {}  // FAKE: dead reference, steers uopt candidate priority (spill-slot order)
            if ((*counter + delta) < 0) {
                *counter = 0;
            } else {
                counter = ((SlotQueueSlot *)slots)[slot].value;
                *counter += delta;
                value = slotQueueGetMaxValue(slot, playerIdx);
                counter = ((SlotQueueSlot *)slots)[slot].value;
                if (gCurrentWorldId && gCurrentWorldId) {}  // FAKE: dead reference, steers uopt candidate priority (spill-slot order)
                if (value < *counter) {
                    *counter = value;
                }
                if (((slot * 0x30) == 0x180) && (func_805FEF10(&flag) != 0)) {
                    flagSet(flag, 1, 0);
                }
                if ((delta > 0) && ((slot * 0x30) == 0)) {
                    value = mapGetHubWorldIndex(gCurrentWorldId, 1);
                    total = *(u16 *)(kongInv + 0xA + (value * 2)) + *(u16 *)(kongInv + 0x26 + (value * 2));
                    if ((total >= 0x4B) && ((total - delta) < 0x4B)) {
                        slots = flagGridIndex(0x225, value, (&gPlayerCharacterId)[player]);
                        flagSet(slots, 1, 0);
                        func_80687C48();
                    }
                    if ((total == 0x64) && ((total - delta) < 0x64)) {
                        sfxAllocateChannel(0xAC, 1.0f);
                    }
                }
            }
            if (playerIdx) {}  // FAKE: dead reference, steers uopt candidate priority (spill-slot order)
        }
        if ((slot * 0x30) == 0x180) {
            func_806F8278(player);
        }
    }
}



void bitfieldSetMappedFlag(u16 *bits, s32 map) {
    *bits |= 1 << mapGetHubWorldIndex(map & 0xFF, 1);
}

void bitfieldClearMappedFlag(u16 *bits, s32 map) {
    *bits &= ~(1 << mapGetHubWorldIndex(map & 0xFF, 1));
}


s32 bitfieldHasMappedFlag(u16 bits, s32 map) {
    return (1 << mapGetHubWorldIndex(map & 0xFF, 1)) & bits & 0xFF;
}

typedef struct SpriteScaleInfo {
    u8 pad0[9];
    u8 scale;
    u8 padA[4];
    s16 size;
} SpriteScaleInfo;

typedef struct SlotQueueSprite {
    u8 pad0[0x330];
    SpriteScaleInfo *info;
    u8 pad334[0xC];
    f32 x;
    f32 y;
    u8 pad348[0x16];
    s16 index;
    f32 scaleX;
    f32 scaleY;
} SlotQueueSprite;



void slotQueueNormalizeSpriteScale(SlotQueueSprite *sprite, s32 slot) {
    f32 size;
    f32 scale;

    size = sprite->info->scale * sprite->info->size;
    scale = 32.0f / size;
    if (slot == 9) {
        scale *= 1.2;
    }
    sprite->scaleX *= scale;
    sprite->scaleY *= scale;
}



void slotQueueReleaseSlot(s32 slot) {
    SlotQueueNode **link;
    SlotQueueNode *node;
    SlotQueueNode **next;
    s32 *effect;

    link = &gSlotQueue[slot].nodes;
    gSlotQueue[slot].state = 0;
    if (*link != NULL) {
        do {
            node = *link;
            next = &node->next;
            if (node->type == 1) {
                effect = node->data;
                effectFreeAndUnlink(effect[2]);
                node = *link;
            }
            heapFree(node->data);
            heapFree(*link);
            *link = NULL;
            link = next;
        } while (*next != NULL);
    }
}


void slotQueueReleaseAll(void) {
    s32 i;

    i = 0;
    do {
        slotQueueReleaseSlot(i);
        i++;
    } while (i != 0xF);
}



void slotQueueAllocSpriteNode(SlotQueueNode **link) {
    SlotQueueNode *temp;

    temp = heapAlloc(0x1C);
    *link = temp;
    heapClearBlock(temp);
    (*link)->type = 1;
    (*link)->data = heapAlloc(0xC);
    heapClearBlock((*link)->data);
}

void slotQueueAllocLabelNode(SlotQueueNode **link) {
    SlotQueueNode *temp;

    temp = heapAlloc(0x1C);
    *link = temp;
    heapClearBlock(temp);
    (*link)->type = 0;
    (*link)->data = heapAlloc(0x88);
    heapClearBlock((*link)->data);
}


void effectSetDirection(SlotQueueNode *node, u32 slot) {
    s32 dx;
    s32 dy;

    dx = 0;
    dy = 0;
    node->delay = 0;
    switch (slot) {
    case 0:
    case 13:
    case 14:
        dx = -1;
        break;
    case 9:
    case 10:
    case 12:
        dy = 1;
        break;
    default:
        dx = 1;
        break;
    }
    node->dirX = (f32)(dx * 0x30);
    node->dirY = (f32)(dy * 0x30);
}

typedef struct SlotQueueEffectNode {
    u8 pad0[2];
    s16 phase;
    u8 wave;
    u8 pad5[3];
    void *effect;
} SlotQueueEffectNode;


void effectSpawnSprite(SlotQueueNode *node, s32 slot, f32 x, f32 y, s32 param) {
    s32 pad[2];
    s32 mode;
    SlotQueueEffectNode *effectNode;

    effectNode = node->data;
    mode = 2;
    effectEnableFade();
    effectSetDuration(-1);
    if (slot == 0xE) {
        mode = 1;
    }
    effectSetMode(mode);
    effectSetParam(param);
    effectSetSpeed(node);
    effectSetCallback(effectWaveMotionUpdate);
    effectSetFlags(0x21);
    if (slot == 3) {
        effectSetColor(0xFF, 0, 0, 0xFF);
    }
    effectNode->effect = effectCreateAtPosition(slotQueueGetSpriteAsset(slot), 1.0f, x, y, -10.0f);
    effectNode->phase = 0;
    if (slot == 7) {
        effectNode->wave = 1;
    } else {
        effectNode->wave = 0;
    }
    slotQueueNormalizeSpriteScale(effectNode->effect, slot);
}

extern u8 gPlayerCharacterId;


void slotQueueSpawnNodes(s32 slot) {
    s32 side;
    s32 pad;
    u8 *sprite;
    s32 icon;
    s32 dir;
    SlotQueueNode **link;

    dir = 1;
    icon = -1;
    link = &gSlotQueue[slot].nodes;
    if (gScreenWidth * 0.5 < gSlotQueue[slot].x) {
        dir = -1;
    }
    side = dir;
    slotQueueAllocSpriteNode(link);
    sprite = (*link)->data;
    effectSetDirection(*link, slot);
    effectSpawnSprite(*link, slot, gSlotQueue[slot].x, gSlotQueue[slot].y, 0);
    *sprite = 0xFF;
    (*link)->fade = 0;
    switch (gCurrentMap) {
    case 0x2A:
        if (slot == 0xD) {
            icon = 0x10;
        }
        break;
    case 1:
        if (slot == 0xE) {
            icon = 0x11;
        }
    case 5:
        if ((icon == -1) && (slot == 0xE)) {
            icon = 0x13;
        }
    case 0x19:
        if ((icon == -1) && (slot == 0xE)) {
            icon = 0x12;
        } else if (slot == 1) {
            icon = gPlayerCharacterId + 0x14;
        }
        break;
    }
    if (icon >= 0) {
        link = &(*link)->next;
        slotQueueAllocSpriteNode(link);
        sprite = (*link)->data;
        effectSetDirection(*link, slot);
        effectSpawnSprite(*link, icon, gSlotQueue[slot].x, gSlotQueue[slot].y + 0x20, 0);
        *sprite = 0xFF;
        (*link)->fade = 0;
    }
    link = &(*link)->next;
    slotQueueAllocLabelNode(link);
    effectSetDirection(*link, slot);
    (*link)->fade = 0;
    sprite = (*link)->data;
    *(s32 *)(*link)->data = gSlotQueue[slot].x + side * 0x14;
    *(s32 *)(sprite + 4) = gSlotQueue[slot].y - 0xA;
}


extern f32 D_807FD7A0[];
extern f32 D_807FD7B8[];
extern f32 D_807FD7D0[];

void effectSpriteUpdatePosition(SlotQueueSprite *sprite, s8 *done) {
    f32 *x;
    f32 *scale;
    s32 i;

    i = sprite->index;
    x = &D_807FD7A0[i];
    if (*x == -200.0f) {
        *done = 1;
        return;
    }
    sprite->x = *x;
    scale = &D_807FD7D0[i];
    sprite->y = D_807FD7B8[i];
    sprite->scaleX = *scale;
    sprite->scaleY = *scale;
    *x = -200.0f;
}

typedef struct SlotQueueLabelPos {
    s32 x;
    s32 y;
} SlotQueueLabelPos;

extern void *D_80750518[];

void slotQueueInitEffectSprites(s32 slot) {
    s32 pad;
    SlotQueueNode **link;
    SlotQueueLabelPos *pos;
    s32 i;

    link = &gSlotQueue[slot].nodes;
    slotQueueAllocLabelNode(link);
    effectSetDirection(*link, 0);
    (*link)->fade = 0;
    pos = (*link)->data;
    pos->x = gSlotQueue[slot].x + 0x14;
    pos->y = gSlotQueue[slot].y - 0x14;
    for (i = 0; i < 5; i++) {
        effectEnableFade();
        effectSetDuration(-1);
        effectSetCallback((void (*)(void))effectSpriteUpdatePosition);
        effectSetSpeed((void *)i);
        D_807FD7A0[i] = -100.0f;
        effectCreateAtPosition((s32)D_80750518[i], 1.0f, -200.0f, 0.0f, -10.0f);
    }
}

void slotQueueSpawnSingleNode(s32 slot) {
    SlotQueueNode **link;
    void *sprite;

    link = &gSlotQueue[slot].nodes;
    slotQueueAllocSpriteNode(link);
    sprite = (*link)->data;
    effectSetDirection(*link, slot);
    effectSpawnSprite(*link, slot, gSlotQueue[slot].x, gSlotQueue[slot].y, 0);
    func_806F8DC4(sprite, 0, slot);
    (*link)->fade = 0;
}



typedef struct ViewportRect {
    u8 pad0[4];
    s16 left;
    s16 top;
    s16 right;
    s16 bottom;
} ViewportRect;

extern Gfx D_1000118;
extern Mtx D_2000080;
extern u8 D_807FD7E4;
extern f32 mathSinF(s16);

Gfx *slotQueueDrawLabel(s32 slot, SlotQueueNode *node, Gfx *gfx) {
    s32 *matrix;
    char text[8];
    u8 alpha;
    ViewportRect *viewport;
    f32 scale;
    s32 width;

    matrix = node->data;
    scale = mathSinF(node->fade);
    alpha = (u8)(u32)((f64)scale * 255.0);
    width = 0;
    gSPMatrix(gfx++, &D_2000080, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    guTranslate((Mtx *)((u8 *)matrix + (gGfxBufferIndex << 6) + 8), node->dirX * (1.0f - scale), node->dirY * (1.0f - scale), 0.0f);
    switch (gSlotQueue[slot].displayMode) {
    case 1:
        _sprintf(text, "o");
        break;
    case 2:
        if (gSlotQueue[slot].displayMode == 0) { // FAKE: dead reference
        }
        _sprintf(text, "NA");
        break;
    default:
        _sprintf(text, "%d", (slot * 0x30 == 0xF0) ? (s32)floatCeil((f32)(u32)gSlotQueue[slot].shown * 0.006666667f) : gSlotQueue[slot].shown);
        break;
    }
    gSPMatrix(gfx++, (u8 *)matrix + (gGfxBufferIndex << 6) + 8, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    gDPPipeSync(gfx++);
    gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, alpha);
    D_807FD7E4 = alpha;
    gSPDisplayList(gfx++, &D_1000118);
    gDPSetCombineLERP(gfx++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
    viewport = cameraFindViewportEntry(0);
    gDPSetScissor(gfx++, G_SC_NON_INTERLACE, viewport->left, viewport->top, viewport->right, viewport->bottom);
    if ((f64)gScreenWidth * 0.5 < (f64)gSlotQueue[slot].x) {
        width = textGetStringWidth(0x81, text);
    }
    gfx = textDrawStringVtx(gfx, 0x81, (s16)((matrix[0] - width) * 4), (s16)(matrix[1] * 4), text, 0);
    gSPPopMatrix(gfx++, G_MTX_MODELVIEW);
    gDPPipeSync(gfx++);
    return gfx;
}

extern s16 D_807505AE[];
extern u16 D_807FC992[][0x2F];
extern Gfx D_2000180;

Gfx *slotQueueDrawPlayerLabels(s32 slot, SlotQueueNode *node, Gfx *gfx) {
    s32 active;
    s32 savedU16;
    s32 savedY;
    f32 x;
    f32 y;
    f32 scale;
    s8 valid;
    s32 player;
    s32 i;
    s32 *cursor;
    f64 u;

    cursor = node->data;
    player = mapGetHubWorldIndex(gCurrentWorldId, 1);
    active = playerGetResolvedKongId(0);
    savedU16 = gSlotQueue[slot].shown;
    savedY = cursor[1];
    x = cursor[0] * 4.0;
    y = cursor[1] * 4.0;
    u = 1.0 - mathSinF(node->fade);
    x = x - 4.0 * (6.0 - u * node->dirX);
    y = y + 92.0;
    for (i = 0; i != 5; i++) {
        valid = 1;
        if (i > 0) {
            valid = flagGet(D_807505AE[i], 0);
        }
        if (valid != 0) {
            if (i == active) {
                gSlotQueue[slot].shown = savedU16;
                scale = 2.0f;
            } else {
                gSlotQueue[slot].shown = D_807FC992[i][player];
                scale = 1.5f;
            }
            gfx = slotQueueDrawLabel(slot, node, gfx);
            if (i != active) {
                gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, D_807FD7E4 >> 1);
            }
            D_807FD7A0[i] = x - 10.0 * scale;
            D_807FD7B8[i] = y - 30.0 * scale;
            D_807FD7D0[i] = scale * 1.15;
            y = y + 136.0;
            cursor[1] += 0x22;
        }
    }
    gSlotQueue[slot].shown = savedU16;
    cursor[1] = savedY;
    gSPMatrix(gfx++, &D_2000180, G_MTX_MODELVIEW | G_MTX_NOPUSH | G_MTX_LOAD);
    return gfx;
}


Gfx *slotQueueNodeUpdate(s32 slot, SlotQueueNode *node, s32 index, Gfx *gfx) {
    if (node->type == 0) {
        if (slot != 8) {
            gfx = slotQueueDrawLabel(slot, node, gfx);
        } else {
            gfx = slotQueueDrawPlayerLabels(slot, node, gfx);
        }
    } else if ((slot == 8) || (slot == 0xA) || (slot == 0xC)) {
        func_806F8DC4(node->data, index, slot);
    }
    return gfx;
}




Gfx *slotQueueStateFadeIn(s32 slot, Gfx *gfx) {
    s32 index;
    s32 done;
    s32 count;
    SlotQueueNode *node;

    node = gSlotQueue[slot].nodes;
    done = 0;
    count = 0;
    index = 0;
    if (gSlotQueue[slot].timer != 0) {
        gSlotQueue[slot].timer = gSlotQueue[slot].timer - 1;
        return gfx;
    }
    if (node == NULL) {
        switch (slot) {
        case 8:
            slotQueueInitEffectSprites(slot);
            return gfx;
        case 10:
        case 12:
            slotQueueSpawnSingleNode(slot);
            return gfx;
        default:
            slotQueueSpawnNodes(slot);
            return gfx;
        }
    } else {
        if (node != NULL) {
            do {
                count += 1;
                if (node->delay != 0) {
                    node->delay = node->delay - 1;
                } else {
                    if (node->fade < 0x400) {
                        node->fade = (s32)((f32)node->fade + 102.4f);
                    } else {
                        done += 1;
                    }
                    if (node->fade >= 0x401) {
                        node->fade = 0x400;
                    }
                    gfx = slotQueueNodeUpdate(slot, node, index, gfx);
                }
                if (node->type == 1) {
                    index += 1;
                }
                node = node->next;
            } while (node != NULL);
        }
        if (done == count) {
            if (((slot * 0x30) == 0x180) || ((slot * 0x30) == 0x1B0)) {
                gSlotQueue[slot].timer = 0x5A;
            } else {
                gSlotQueue[slot].timer = 0x1E;
            }
            gSlotQueue[slot].state = 2;
            if (gSlotQueue == 0) {} // FAKE: dead reference
        }
        return gfx;
    }
}

s32 slotQueueGetCountStep(s32 slot) {
    s32 step;

    step = 1;
    if (slot == 5) {
        step = 0x96;
    }
    return step;
}


Gfx *slotQueueStateMoveToTarget(s32 slot, Gfx *gfx) {
    extern s32 slotQueueGetCountStep(); // FAKE: callee prototype steer (K&R call passes the target/current counts)
    s32 n;
    SlotQueueNode *node;
    u8 flag;
    u16 *p;
    s32 x;
    s32 step;
    s32 absd;
    s32 pad;
    s32 tmp;

    node = gSlotQueue[slot].nodes;
    n = 0;
    p = gSlotQueue[slot].value;
    if (p != NULL) {
        flag = *p == gSlotQueue[slot].shown;
    } else {
        flag = 1;
    }
    if (node != NULL) {
        do {
            gfx = slotQueueNodeUpdate(slot, node, n, gfx);
            if (node->type == 1) {
                n += 1;
            }
            node = node->next;
        } while (node != NULL);
    }
    if (flag == 0) {
        if (*gSlotQueue[slot].value == 0) {} // FAKE: hoists the *value load above the null test
        if (gSlotQueue[slot].value != NULL) {
            x = *gSlotQueue[slot].value;
            n = gSlotQueue[slot].shown;
            step = slotQueueGetCountStep(slot, *gSlotQueue[slot].value, gSlotQueue[slot].shown);
            if ((x - n) > 0) {
                absd = (x - n);
            } else {
                absd = -(x - n);
            }
            if (absd < step) {
                if ((x - n) > 0) {
                    tmp = (x - n);
                } else {
                    tmp = -(x - n);
                }
                step = tmp;
            }
            if ((x - n) >= 0) {
                absd = 1;
            } else {
                absd = -1;
            }
            gSlotQueue[slot].shown += absd * step;
        }
        flag = *gSlotQueue[slot].value == gSlotQueue[slot].shown;
    }
    if ((gSlotQueue[slot].timer == 0) && (flag != 0)) {
        gSlotQueue[slot].state = 3;
        slotQueueStaggerNodeDelays(slot);
        if (slot == 8) {
            slotQueueCancel(9, 5);
        }
        return gfx;
    } else if ((gSlotQueue[slot].timer != 0) && (gSlotQueue[slot].visible == 0)) {
        gSlotQueue[slot].timer = gSlotQueue[slot].timer - 1;
    }
    return gfx;
}


Gfx *slotQueueStateFadeOut(s32 slot, Gfx *gfx) {
    s32 index;
    SlotQueueNode *node;
    s32 cnt;
    s32 done;

    node = gSlotQueue[slot].nodes;
    index = 0;
    if (node != NULL) {
        do {
            gfx = slotQueueNodeUpdate(slot, node, index, gfx);
            if (node->type == 1) {
                index += 1;
            }
            node = node->next;
        } while (node != NULL);
    }
    if (gSlotQueue[slot].timer != 0) {
        gSlotQueue[slot].timer = gSlotQueue[slot].timer - 1;
    } else {
        node = gSlotQueue[slot].nodes;
        done = 0;
        cnt = 0;
        if (node != NULL) {
            do {
                cnt += 1;
                if (node->delay != 0) {
                    node->delay = node->delay - 1;
                } else {
                    if (node->fade > 0) {
                        node->fade = (s32)((f32)node->fade - 102.4f);
                    }
                    if (node->fade < 0) {
                        node->fade = 0;
                        done += 1;
                    }
                }
                node = node->next;
            } while (node != NULL);
        }
        if (cnt == done) {
            gSlotQueue[slot].state = 0;
        }
    }
    return gfx;
}


Gfx *slotQueueBuildDisplayList(Gfx *gfx) {
    s32 i;

    if (gPlayerCount >= 2) {
        return gfx;
    }
    gDPPipeSync(gfx++);
    gSPMatrix(gfx++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    for (i = 0; i != 0xF; i++) {
        switch (gSlotQueue[i].state) {
        case 0:
            slotQueueReleaseSlot(i);
            break;
        case 1:
            gfx = slotQueueStateFadeIn(i, gfx);
            break;
        case 2:
            gfx = slotQueueStateMoveToTarget(i, gfx);
            break;
        case 3:
            gfx = slotQueueStateFadeOut(i, gfx);
            break;
        }
    }
    return gfx;
}

extern s32 D_80754288;

void slotQueueSelectPlayerResource(u8 player) {
    s32 resource;

    resource = mapGetHubWorldIndex(gCurrentWorldId, 0);
    gSlotQueue[13].value = &gPlayerInventoryTable[player][resource * 2 + 0x26];
    gSlotQueue[13].shown = *gSlotQueue[13].value;
    D_80754288 = player;
}

extern s32 D_807200A0, D_807201A0, D_80720268, D_8072029C, D_807203B0, D_807203D4, D_807203F8, D_8072041C, D_80720440, D_80720488, D_807204BC, D_80720508, D_8072052C, D_80720558, D_8072057C, D_807205A0, D_807205C4, D_807205E8, D_8072060C, D_807206A8, D_807207BC, D_807207E0, D_80720854, D_80720878, D_80720890, D_807208A8, D_807208C0, D_807208D8, D_807209EC, D_80720A10, D_80720A34, D_80720A58, D_80721200, D_8072121C, D_80721250, D_8072145C, D_807214A0, D_807214B8, D_807214D0, D_807214E8, D_80721500;

void *slotQueueGetSpriteAsset(s32 slot) {
    void *result;
    u32 player;

    result = 0;
    player = playerGetResolvedKongId(0);
    if (slot == 13) {
        player = D_80754288;
    }
    switch (slot) {
    case 0:
    case 13:
        switch (player) {
        case 1:
            result = &D_8072057C;
            break;
        case 0:
            result = &D_807205E8;
            break;
        case 3:
            result = &D_8072060C;
            break;
        case 2:
            result = &D_807205C4;
            break;
        case 4:
        case 5:
            result = &D_807205A0;
            break;
        }
        break;
    case 6:
        result = &D_80720488;
        break;
    case 4:
        result = &D_807204BC;
        break;
    case 2:
    case 3:
        switch (player) {
        case 1:
            result = &D_807200A0;
            break;
        case 0:
            result = &D_807206A8;
            break;
        case 3:
            result = &D_80720854;
            break;
        case 2:
            result = &D_8072029C;
            break;
        case 4:
            result = &D_807201A0;
            break;
        case 5:
            result = &D_80720268;
            break;
        }
        break;
    case 1:
    case 14:
        switch (player) {
        case 1:
            result = &D_807203B0;
            break;
        case 0:
            result = &D_8072041C;
            break;
        case 3:
            result = &D_80720440;
            break;
        case 2:
            result = &D_807203F8;
            break;
        case 4:
        case 5:
            result = &D_807203D4;
            break;
        }
        break;
    case 11:
        result = &D_807207BC;
        break;
    case 7:
        switch (player) {
        case 1:
            result = &D_80720878;
            break;
        case 0:
            result = &D_80720890;
            break;
        case 3:
            result = &D_807208A8;
            break;
        case 2:
            result = &D_807208D8;
            break;
        case 4:
        case 5:
            result = &D_807208C0;
            break;
        }
        break;
    case 5:
        result = &D_80720508;
        break;
    case 8:
        result = &D_8072052C;
        break;
    case 9:
        result = &D_8072052C;
        break;
    case 10:
        result = &D_80720558;
        break;
    case 12:
        switch (player) {
        case 1:
            result = &D_807209EC;
            break;
        case 0:
            result = &D_80720A34;
            break;
        case 3:
            result = &D_80720A58;
            break;
        case 2:
            result = &D_807207E0;
            break;
        case 4:
        case 5:
            result = &D_80720A10;
            break;
        }
        break;
    case 16:
        result = &D_8072145C;
        break;
    case 17:
        result = &D_80721250;
        break;
    case 18:
        result = &D_80721200;
        break;
    case 19:
        result = &D_8072121C;
        break;
    case 20:
        result = &D_807214A0;
        break;
    case 21:
        result = &D_807214B8;
        break;
    case 22:
        result = &D_807214D0;
        break;
    case 23:
        result = &D_807214E8;
        break;
    case 24:
        result = &D_80721500;
        break;
    }
    return result;
}


void slotQueuePushActiveMask(void) {
    s32 i;
    SlotQueueMaskNode **link;
    SlotQueueMaskNode *alloc;

    link = &gSlotQueueMaskList;
    while (*link != NULL) {
        link = &(*link)->next;
    }
    alloc = heapAlloc(8);
    *link = alloc;
    heapClearBlock(alloc);
    for (i = 0; i < 15; i++) {
        if ((gSlotQueue[i].state == 1 || gSlotQueue[i].state == 2) && gSlotQueue[i].visible != 0) {
            (*link)->flags |= 1 << i;
        }
    }
}


void slotQueueClearAllFlags(void) {
    s32 i;

    slotQueuePushActiveMask();
    for (i = 0; i != 15; i++) {
        if (gSlotQueue[i].visible != 0) {
            slotQueueClearFlags(i, 0);
        }
    }
}

void slotQueueReset(void) {
    slotQueuePushActiveMask();
    slotQueueReleaseAll();
}

void slotQueuePopActiveMask(void) {
    SlotQueueMaskNode **link;
    s32 i;

    link = &gSlotQueueMaskList;
    if (*link != NULL) {
        while ((*link)->next != NULL) {
            link = &(*link)->next;
        }
        for (i = 0; i != 15; i++) {
            if ((*link)->flags & (1 << i)) {
                slotQueueUpdate(i, 1, 0);
            }
        }
        heapFree(*link);
        *link = NULL;
    }
}

void slotQueueSetDisplayMode(u8 slot, u8 player, u8 mode) {
    if (gSlotQueue[player * 15 + slot].locked == 0) {
        gSlotQueue[player * 15 + slot].displayMode = mode;
    }
}

u8 slotQueueGetDisplayMode(u8 slot, u8 player) {
    return gSlotQueue[player * 15 + slot].displayMode;
}

s32 func_806FB418(void) {
    s32 sum;
    s32 i;
    s32 j;

    sum = 0;
    for (j = 0; j < 5; j++) {
        for (i = 0; i < 8; i++) {
            sum += ((u16 *)gPlayerInventoryTable[j])[0x21 + i];
        }
    }
    return sum;
}


#include "common.h"
#include "actor.h"
#include "sched.h"
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
extern PlayerStruct *gPlayerSlots;
extern u8 gPlayerCount;
extern u8 gCurrentPlayerIndex;
extern s32 gCurrentMap;
extern u8 gCurrentWorldId;
extern u8 gScreenRenderFlags;
extern s16 gScreenWidth;
extern s16 gScreenHeight;
extern u8 gNextGameMode;
extern u8 gGfxBufferIndex;



/* A sprite (type 1) or label (type 0) node hanging off a slot's nodes list. */
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

/* A sprite node's data (0xC bytes). */
typedef struct SlotQueueEffectNode {
    u8 alpha;
    u8 pad1;
    s16 phase;
    u8 wave;
    u8 pad5[3];
    EffectNode *effect;
} SlotQueueEffectNode;

/* A label node's data (0x88 bytes): screen position plus one translate matrix per gfx buffer. */
typedef struct SlotQueueLabel {
    s32 x;
    s32 y;
    Mtx mtx[2];
} SlotQueueLabel;


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

SlotQueueSlot *slotQueueGetAddress(u8 player) {
    return &gSlotQueue[player * 15];
}

void func_806F8004(f32 pitch, f32 yaw, f32 *outX, f32 *outY, f32 *outZ) {
    f32 pitchMtx[4][4];
    f32 yawMtx[4][4];
    f32 tz;
    f32 ty;
    f32 tx;
    f32 scale;
    f32 dist;

    dist = gPlayerSlots[gCurrentPlayerIndex].nearClip;
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






void slotQueueUpdateGoldenBananaTotal(u8 player) {
    s32 sum;
    PlayerInventory *inv;
    s32 i;
    s32 j;
    s32 count;

    sum = 0;
    inv = &gPlayerInventoryTable[player];
    count = sizeof(inv->kong[0].goldenBananas) / sizeof(inv->kong[0].goldenBananas[0]);
    for (i = 0; i < count; i++) {
        for (j = 0; j < 5; j++) {
            sum += inv->kong[j].goldenBananas[i];
        }
    }
    gSlotQueue[player * 15 + 9].shown = sum;
}


extern s16 D_80744544;
extern u16 D_80750AC4;
extern u16 gTextNumberArg;

/* Initialises the per-player slot queue (15 slots of 0x30 bytes per player): sets each slot's text pointer, size and
 * screen position (func_806F8004). */
void slotQueueInit(s32 reset) {
    s32 j;
    s32 i;
    s16 shownMask;
    PlayerInventory *inv;
    u8 world;
    SlotQueueSlot *base;
    KongInventory *kongInv;
    s32 flag;

    shownMask = D_80744544;
    world = mapGetHubWorldIndex(gCurrentWorldId, 1);
    if (gPlayerCount >= 2) {
        shownMask = 0;
    }
    if (reset != 0) {
        gSlotQueue = heapAlloc(gPlayerCount * (15 * sizeof(SlotQueueSlot)));
        heapClearBlock(gSlotQueue);
        gSlotQueueMaskList = NULL;
    }
    if (gPlayerCount > 0) {
        inv = gPlayerInventoryTable;
        i = 0;
        do {
            kongInv = &inv->kong[playerGetResolvedKongId(i)];
            base = slotQueueGetAddress(i);
            for (j = 0; j < 15; j++) {
                flag = 0;
                if (reset != 0) {
                    base[j].state = 0;
                    base[j].timer = 0;
                    base[j].showArg = 0;
                    base[j].visible = 0;
                    base[j].nodes = NULL;
                    base[j].displayMode = 0;
                }
                if (menuIsTransitionType3Or4() != 0) {
                    base[j].displayMode = 1;
                }
                switch (j) {
                case 0:
                    base[j].value = &kongInv->coloredBananas[world];
                    base[j].x = 0x1E; base[j].y = 0x26; // LAYOUT: one line lets as1 store y (sw +12) before x (sw +8)
                    func_806F8004(15.5f, 26.0f, &base[j].worldX, &base[j].worldY, &base[j].worldZ);
                    break;
                case 13:
                    base[j].value = NULL;
                    base[j].x = 0x122; base[j].y = 0x26; // LAYOUT: one line lets as1 store y (sw +12) before x (sw +8)
                    func_806F8004(-5.5f, -26.0f, &base[j].worldX, &base[j].worldY, &base[j].worldZ);
                    break;
                case 8:
                    base[j].value = &kongInv->goldenBananas[world];
                    base[j].x = 0x1E; base[j].y = 0x48; // LAYOUT: one line lets as1 store y (sw +12) before x (sw +8)
                    func_806F8004(1.5f, 26.0f, &base[j].worldX, &base[j].worldY, &base[j].worldZ);
                    break;
                case 12:
                    base[j].value = NULL;
                    base[j].x = 0xC2; base[j].y = 0xD0; // LAYOUT: one line lets as1 store y (sw +12) before x (sw +8)
                    func_806F8004(-26.5f, 26.0f, &base[j].worldX, &base[j].worldY, &base[j].worldZ);
                    break;
                case 10:
                    base[j].value = NULL;
                    base[j].x = 0x52; base[j].y = 0xD0; // LAYOUT: one line lets as1 store y (sw +12) before x (sw +8)
                    func_806F8004(-26.5f, 26.0f, &base[j].worldX, &base[j].worldY, &base[j].worldZ);
                    break;
                case 9:
                    base[j].value = NULL;
                    base[j].x = 0x7A; base[j].y = 0xD0; // LAYOUT: one line lets as1 store y (sw +12) before x (sw +8)
                    break;
                case 5:
                    if (shownMask & 0x20) {
                        inv->abilityEnergy = slotQueueGetMaxValue(5, i);
                        flag = 1;
                    }
                    base[j].value = &inv->abilityEnergy;
                    base[j].x = 0x122; base[j].y = 0x8C; // LAYOUT: one line lets as1 store y (sw +12) before x (sw +8)
                    func_806F8004(-5.5f, -19.0f, &base[j].worldX, &base[j].worldY, &base[j].worldZ);
                    break;
                case 2:
                    base[j].value = &inv->ammo;
                    base[j].x = 0x122; base[j].y = 0x48; // LAYOUT: one line lets as1 store y (sw +12) before x (sw +8)
                    func_806F8004(8.5f, -19.0f, &base[j].worldX, &base[j].worldY, &base[j].worldZ);
                    break;
                case 3:
                    if (shownMask & 0x4) {
                        inv->homingAmmo = slotQueueGetMaxValue(3, i);
                        flag = 1;
                    }
                    base[j].value = &inv->homingAmmo;
                    base[j].x = 0x122; base[j].y = 0x48; // LAYOUT: one line lets as1 store y (sw +12) before x (sw +8)
                    func_806F8004(8.5f, -19.0f, &base[j].worldX, &base[j].worldY, &base[j].worldZ);
                    break;
                case 4:
                    if (shownMask & 0x8) {
                        inv->throwAmmo = slotQueueGetMaxValue(4, i);
                        flag = 1;
                    }
                    base[j].value = &inv->throwAmmo;
                    base[j].x = 0x122; base[j].y = 0x6A; // LAYOUT: one line lets as1 store y (sw +12) before x (sw +8)
                    func_806F8004(1.5f, -19.0f, &base[j].worldX, &base[j].worldY, &base[j].worldZ);
                    break;
                case 6:
                    if (shownMask & 0x10) {
                        inv->cameraFilm = slotQueueGetMaxValue(6, i);
                        flag = 1;
                    }
                    base[j].value = &inv->cameraFilm;
                    base[j].x = 0x122; base[j].y = 0xD0; // LAYOUT: one line lets as1 store y (sw +12) before x (sw +8)
                    func_806F8004(-19.5f, -19.0f, &base[j].worldX, &base[j].worldY, &base[j].worldZ);
                    break;
                case 11:
                    base[j].value = &D_80750AC4;
                    base[j].x = 0x122; base[j].y = 0x26; // LAYOUT: one line lets as1 store y (sw +12) before x (sw +8)
                    func_806F8004(16.5f, -19.0f, &base[j].worldX, &base[j].worldY, &base[j].worldZ);
                    break;
                case 1:
                    if (shownMask & 0x2) {
                        kongInv->coins = slotQueueGetMaxValue(1, i);
                        flag = 1;
                    }
                    base[j].value = &kongInv->coins;
                    base[j].x = 0x122; base[j].y = 0x26; // LAYOUT: one line lets as1 store y (sw +12) before x (sw +8)
                    func_806F8004(16.5f, -19.0f, &base[j].worldX, &base[j].worldY, &base[j].worldZ);
                    break;
                case 7:
                    if (shownMask & 0x40) {
                        kongInv->instrumentEnergy = slotQueueGetMaxValue(7, i);
                        flag = 1;
                    }
                    base[j].value = &kongInv->instrumentEnergy;
                    base[j].x = 0x122; base[j].y = 0xAE; // LAYOUT: one line lets as1 store y (sw +12) before x (sw +8)
                    func_806F8004(-12.5f, -19.0f, &base[j].worldX, &base[j].worldY, &base[j].worldZ);
                    break;
                case 14:
                    base[j].value = &gTextNumberArg;
                    base[j].x = 0x1E; base[j].y = 0x26; // LAYOUT: one line lets as1 store y (sw +12) before x (sw +8)
                    func_806F8004(15.5f, 26.0f, &base[j].worldX, &base[j].worldY, &base[j].worldZ);
                    break;
                }
                base[j].locked = flag;
                if (base[j].locked) {
                    base[j].displayMode = 1;
                }
                if (base[j].value != NULL) {
                    base[j].shown = *base[j].value;
                }
            }
            slotQueueUpdateGoldenBananaTotal(i);
            i++;
            inv++;
        } while (i < gPlayerCount);
    }
    if (gCurrentMap == 0x11 || gCurrentMap == 0x52) {
        slotQueueSetDisplayMode(5, 0, 1);
    }
}


void slotQueueSetShownValue(u8 slot, u8 player, s32 value) {
    slotQueueGetAddress(player)[slot].shown = value;
}


s32 slotQueueGetValue(u8 index, u8 player) {
    u16 value;
    s32 world;
    s32 kong;
    u16 *counter;
    SlotQueueSlot *slot;

    value = 0;
    slot = slotQueueGetAddress(player) + index;
    switch (slot->displayMode) {
    case 0:
        if (slot->value != NULL) {
            counter = slot->value;
            value = *counter;
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
    case 2:
        break;
    }
    return value;
}

void slotQueueUpdate(s32 slot, u8 show, s32 delay) {
    if ((gPlayerCount < 2) && (menuIsTransitionType3Or4() == 0)) {
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
    s32 kong;

    world = mapGetHubWorldIndex(gCurrentWorldId, 1);
    kong = playerGetResolvedKongId(0);
    *alpha = 0x7F;
    if (slot != 8) {
        if (slot != 0xA) {
            if ((slot == 0xC) && (flagGridSumRows(0x1D5, world, world, kong) != 0)) {
                *alpha = 0xFF;
            }
        } else if (flagGridSumRows(0x225, world, world, kong) != 0) {
            *alpha = 0xFF;
        }
    } else if (count < gPlayerInventoryTable[0].kong[kong].goldenBananas[world]) {
        *alpha = 0xFF;
    }
}


s32 countBananaFairies(void) {
    return flagCountRange(0x24D, 0x14, 0);
}


u16 slotQueueGetMaxValue(s32 slot, s32 player) {
    s32 kong;
    u16 max;
    s32 level;
    s32 bits;
    s32 rest;

    kong = playerGetResolvedKongId(player);
    max = 0x64;
    switch (slot) {
    case 1:
        max = 0x3E7;
        break;
    case 2:
        max = (1 << gPlayerInventoryTable[player].kong[kong].ammoBeltLevel) * 0x32;
        break;
    case 3:
        if (gPlayerCount >= 2) {
            max = 0xA;
        } else {
            max = (1 << gPlayerInventoryTable[player].kong[kong].ammoBeltLevel) * 0x32;
        }
        break;
    case 4:
        max = (gPlayerInventoryTable[player].kong[kong].ammoBeltLevel * 5) + 0x14;
        break;
    case 5:
        if (gPlayerCount >= 2) {
            max = 0xBB8;
        } else if (anyKongUsesAbilityEnergy() != 0) {
            max = (countBananaFairies() * 0x96) + 0xBB8;
        } else {
            max = 0;
        }
        break;
    case 7:
        if (gPlayerCount >= 2) {
            max = 0x14;
        } else {
            bits = gPlayerInventoryTable[player].kong[kong].instrumentFlags;
            level = 1;
            if (bits & 1) {
                rest = bits;
                while (rest != 0) {
                    level += 1;
                    rest >>= 1;
                }
                max = level * 5;
            } else {
                max = 0;
            }
        }
        break;
    case 6:
        if (flagGet(0x179, 0) != 0) {
            max = countBananaFairies() + 0xA;
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


extern u8 gPlayerCharacterId[];

void slotQueueAddValue(s32 slot, u8 player, s16 delta) {
    s32 max;
    KongInventory *kongInv;
    SlotQueueSlot *slots;
    s32 kong;
    s32 flag;
    s32 total;
    s32 world;
    s32 pad;

    kong = playerGetResolvedKongId(player);
    kongInv = &gPlayerInventoryTable[player].kong[kong];
    slots = slotQueueGetAddress(player);
    if (((slots[slot].locked == 0) || (delta >= 0)) && (slots[slot].displayMode == 0)) {
        switch (slot) {
        case 0xA:
        case 0xC:
            break;
        default:
            if ((*slots[slot].value + delta) < 0) {
                *slots[slot].value = 0;
            } else {
                *slots[slot].value += delta;
                max = slotQueueGetMaxValue(slot, player);
                if (max < *slots[slot].value) {
                    *slots[slot].value = max;
                }
                if ((slot == 8) && (func_805FEF10(&flag) != 0)) {
                    flagSet(flag, 1, 0);
                }
                if ((delta > 0) && (slot == 0)) {
                    world = mapGetHubWorldIndex(gCurrentWorldId, 1);
                    total = kongInv->coloredBananas[world] + kongInv->bananasDelivered[world];
                    if ((total >= 0x4B) && ((total - delta) < 0x4B)) {
                        flagSet(flagGridIndex(0x225, world, gPlayerCharacterId[player]), 1, 0);
                        func_80687C48();
                    }
                    if ((total == 0x64) && ((total - delta) < 0x64)) {
                        sfxAllocateChannel(0xAC, 1.0f);
                    }
                }
            }
            break;
        }
        if (slot == 8) {
            slotQueueUpdateGoldenBananaTotal(player);
        }
    }
}



void bitfieldSetMappedFlag(u16 *bits, s32 map) {
    *bits |= 1 << mapGetHubWorldIndex(map, 1);
}

void bitfieldClearMappedFlag(u16 *bits, s32 map) {
    *bits &= ~(1 << mapGetHubWorldIndex(map, 1));
}


u8 bitfieldHasMappedFlag(u16 bits, s32 map) {
    return bits & (1 << mapGetHubWorldIndex(map, 1));
}


void slotQueueNormalizeSpriteScale(EffectNode *effect, s32 slot) {
    f32 size;
    f32 scale;

    size = effect->grid->height * effect->grid->cellH;
    scale = 32.0f / size;
    if (slot == 9) {
        scale *= 1.2;
    }
    effect->scaleX *= scale;
    effect->scaleY *= scale;
}



void slotQueueReleaseSlot(s32 slot) {
    SlotQueueNode **link;
    SlotQueueNode **next;
    SlotQueueEffectNode *effectNode;

    link = &gSlotQueue[slot].nodes;
    gSlotQueue[slot].state = 0;
    while (*link != NULL) {
        next = &(*link)->next;
        if ((*link)->type == 1) {
            effectNode = (*link)->data;
            effectFreeAndUnlink(effectNode->effect);
        }
        heapFree((*link)->data);
        heapFree(*link);
        *link = NULL;
        link = next;
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
    *link = heapAlloc(sizeof(SlotQueueNode));
    heapClearBlock(*link);
    (*link)->type = 1;
    (*link)->data = heapAlloc(sizeof(SlotQueueEffectNode));
    heapClearBlock((*link)->data);
}

void slotQueueAllocLabelNode(SlotQueueNode **link) {
    *link = heapAlloc(sizeof(SlotQueueNode));
    heapClearBlock(*link);
    (*link)->type = 0;
    (*link)->data = heapAlloc(sizeof(SlotQueueLabel));
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
    effectSetSpeed((s32)node);
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


void slotQueueSpawnNodes(s32 slot) {
    s32 pad;
    SlotQueueLabel *label;
    SlotQueueEffectNode *effectNode;
    s32 icon;
    s32 dir;
    SlotQueueNode **link;

    dir = 1;
    icon = -1;
    link = &gSlotQueue[slot].nodes;
    if (gScreenWidth * 0.5 < gSlotQueue[slot].x) {
        dir = -1;
    }
    slotQueueAllocSpriteNode(link);
    effectNode = (*link)->data;
    effectSetDirection(*link, slot);
    effectSpawnSprite(*link, slot, gSlotQueue[slot].x, gSlotQueue[slot].y, 0);
    effectNode->alpha = 0xFF;
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
            icon = gPlayerCharacterId[0] + 0x14;
        }
        break;
    }
    if (icon >= 0) {
        link = &(*link)->next;
        slotQueueAllocSpriteNode(link);
        effectNode = (*link)->data;
        effectSetDirection(*link, slot);
        effectSpawnSprite(*link, icon, gSlotQueue[slot].x, gSlotQueue[slot].y + 0x20, 0);
        effectNode->alpha = 0xFF;
        (*link)->fade = 0;
    }
    link = &(*link)->next;
    slotQueueAllocLabelNode(link);
    effectSetDirection(*link, slot);
    (*link)->fade = 0;
    label = (*link)->data;
    label->x = gSlotQueue[slot].x + dir * 0x14;
    label->y = gSlotQueue[slot].y - 0xA;
}


extern f32 gSlotQueueKongIconX[];
extern f32 gSlotQueueKongIconY[];
extern f32 gSlotQueueKongIconScale[];

void effectSpriteUpdatePosition(EffectNode *effect, u8 *done) {
    f32 *x;
    f32 *scale;
    s32 i;

    i = effect->pair.lo;
    x = &gSlotQueueKongIconX[i];
    if (*x == -200.0f) {
        *done = 1;
        return;
    }
    effect->x = *x;
    scale = &gSlotQueueKongIconScale[i];
    effect->y = gSlotQueueKongIconY[i];
    effect->scaleX = *scale;
    effect->scaleY = *scale;
    *x = -200.0f;
}

extern void *gKongIconSprites[];

void slotQueueInitEffectSprites(s32 slot) {
    s32 pad;
    SlotQueueNode **link;
    SlotQueueLabel *label;
    s32 i;

    link = &gSlotQueue[slot].nodes;
    slotQueueAllocLabelNode(link);
    effectSetDirection(*link, 0);
    (*link)->fade = 0;
    label = (*link)->data;
    label->x = gSlotQueue[slot].x + 0x14;
    label->y = gSlotQueue[slot].y - 0x14;
    for (i = 0; i < 5; i++) {
        effectEnableFade();
        effectSetDuration(-1);
        effectSetCallback(effectSpriteUpdatePosition);
        effectSetSpeed(i);
        gSlotQueueKongIconX[i] = -100.0f;
        effectCreateAtPosition(gKongIconSprites[i], 1.0f, -200.0f, 0.0f, -10.0f);
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


extern Gfx D_1000118;
extern Mtx D_2000080;
extern u8 gSlotQueueLabelAlpha;

Gfx *slotQueueDrawLabel(s32 slot, SlotQueueNode *node, Gfx *gfx) {
    SlotQueueLabel *label;
    u8 text[8];
    u8 alpha;
    G00Entry *viewport;
    f32 scale;
    s32 width;

    label = node->data;
    scale = mathSinF(node->fade);
    alpha = scale * 255.0;
    width = 0;
    gSPMatrix(gfx++, &D_2000080, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    guTranslate(&label->mtx[gGfxBufferIndex], node->dirX * (1.0f - scale), node->dirY * (1.0f - scale), 0.0f);
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
        _sprintf(text, "%d", (slot == 5) ? (s32)floatCeil(gSlotQueue[slot].shown * 0.006666667f) : gSlotQueue[slot].shown);
        break;
    }
    gSPMatrix(gfx++, &label->mtx[gGfxBufferIndex], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    gDPPipeSync(gfx++);
    gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, alpha);
    gSlotQueueLabelAlpha = alpha;
    gSPDisplayList(gfx++, &D_1000118);
    gDPSetCombineLERP(gfx++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
    viewport = cameraFindViewportEntry(0);
    gDPSetScissor(gfx++, G_SC_NON_INTERLACE, viewport->left, viewport->top, viewport->right, viewport->bottom);
    if (gScreenWidth * 0.5 < gSlotQueue[slot].x) {
        width = textGetStringWidth(0x81, text);
    }
    gfx = textDrawStringVtx(gfx, 0x81, (label->x - width) * 4, label->y * 4, text, 0);
    gSPPopMatrix(gfx++, G_MTX_MODELVIEW);
    gDPPipeSync(gfx++);
    return gfx;
}

extern s16 D_807505AE[];
extern Gfx D_2000180;

Gfx *slotQueueDrawPlayerLabels(s32 slot, SlotQueueNode *node, Gfx *gfx) {
    s32 active;
    s32 savedShown;
    s32 savedY;
    f32 x;
    f32 y;
    f32 scale;
    s8 valid;
    s32 world;
    s32 i;
    SlotQueueLabel *label;
    f64 slide;

    label = node->data;
    world = mapGetHubWorldIndex(gCurrentWorldId, 1);
    active = playerGetResolvedKongId(0);
    savedShown = gSlotQueue[slot].shown;
    savedY = label->y;
    x = label->x * 4.0;
    y = label->y * 4.0;
    slide = 1.0 - mathSinF(node->fade);
    x = x - 4.0 * (6.0 - slide * node->dirX);
    y = y + 92.0;
    for (i = 0; i != 5; i++) {
        valid = 1;
        if (i > 0) {
            valid = flagGet(D_807505AE[i], 0);
        }
        if (valid != 0) {
            if (i == active) {
                gSlotQueue[slot].shown = savedShown;
                scale = 2.0f;
            } else {
                gSlotQueue[slot].shown = gPlayerInventoryTable[0].kong[i].goldenBananas[world];
                scale = 1.5f;
            }
            gfx = slotQueueDrawLabel(slot, node, gfx);
            if (i != active) {
                gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, gSlotQueueLabelAlpha >> 1);
            }
            gSlotQueueKongIconX[i] = x - 10.0 * scale;
            gSlotQueueKongIconY[i] = y - 30.0 * scale;
            gSlotQueueKongIconScale[i] = scale * 1.15;
            y = y + 136.0;
            label->y += 0x22;
        }
    }
    gSlotQueue[slot].shown = savedShown;
    label->y = savedY;
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
        gSlotQueue[slot].timer--;
        return gfx;
    }
    if (node == NULL) {
        switch (slot) {
        case 8:
            slotQueueInitEffectSprites(slot);
            break;
        case 10:
        case 12:
            slotQueueSpawnSingleNode(slot);
            break;
        default:
            slotQueueSpawnNodes(slot);
            break;
        }
        return gfx;
    }
    while (node != NULL) {
        count++;
        if (node->delay != 0) {
            node->delay--;
        } else {
            if (node->fade < 0x400) {
                node->fade += 102.4f;
            } else {
                done++;
            }
            if (node->fade > 0x400) {
                node->fade = 0x400;
            }
            gfx = slotQueueNodeUpdate(slot, node, index, gfx);
        }
        if (node->type == 1) {
            index++;
        }
        node = node->next;
    }
    if (done == count) {
        if ((slot == 8) || (slot == 9)) {
            gSlotQueue[slot].timer = 0x5A;
        } else {
            gSlotQueue[slot].timer = 0x1E;
        }
        gSlotQueue[slot].state = 2;
    }
    return gfx;
}

s32 slotQueueGetCountStep(slot)
    s32 slot;
{
    s32 step;

    step = 1;
    if (slot == 5) {
        step = 0x96;
    }
    return step;
}


Gfx *slotQueueStateMoveToTarget(s32 slot, Gfx *gfx) {
    s32 index;
    SlotQueueNode *node;
    u8 reached;
    u16 *value;
    s32 target;
    s32 step;
    s32 shown;
    s32 dist;

    node = gSlotQueue[slot].nodes;
    index = 0;
    value = gSlotQueue[slot].value;
    if (value != NULL) {
        reached = *value == gSlotQueue[slot].shown;
    } else {
        reached = 1;
    }
    while (node != NULL) {
        gfx = slotQueueNodeUpdate(slot, node, index, gfx);
        if (node->type == 1) {
            index++;
        }
        node = node->next;
    }
    if (reached == 0) {
        if (*gSlotQueue[slot].value == 0) {} // FAKE: hoists the *value load above the null test
        if (gSlotQueue[slot].value != NULL) {
            target = *gSlotQueue[slot].value;
            shown = gSlotQueue[slot].shown;
            step = slotQueueGetCountStep(slot, *gSlotQueue[slot].value, gSlotQueue[slot].shown);
            if ((((target - shown) > 0) ? (target - shown) : -(target - shown)) < step) {
                dist = (((target - shown) > 0) ? (target - shown) : -(target - shown));
                step = dist;
            }
            gSlotQueue[slot].shown += (((target - shown) >= 0) ? 1 : -1) * step;
        }
        reached = *gSlotQueue[slot].value == gSlotQueue[slot].shown;
    }
    if ((gSlotQueue[slot].timer == 0) && (reached != 0)) {
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
    s32 world;

    world = mapGetHubWorldIndex(gCurrentWorldId, 0);
    gSlotQueue[13].value = &gPlayerInventoryTable[0].kong[player].bananasDelivered[world];
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
            sum += gPlayerInventoryTable[0].kong[j].goldenBananas[i];
        }
    }
    return sum;
}


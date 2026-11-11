#include "common.h"
#define PROTO_SKIP_resQueueAttachActor // FAKE: callee prototype steer
#include "proto/boot/3D20.h"
#include "proto/global/100180.h"
#include "proto/global/104F0.h"
#include "proto/global/10D2D0.h"
#include "proto/global/112080.h"
#include "proto/global/1295B0.h"
#include "proto/global/12E800.h"
#include "proto/global/135D30.h"
#include "proto/global/19A00.h"
#include "proto/global/201B0.h"
#include "proto/global/2C910.h"
#include "proto/global/35000.h"
#include "proto/global/3C10.h"
#include "proto/global/7CA80.h"
#include "proto/global/90D80.h"
#include "proto/global/C4620.h"
#include "proto/global/CEAE0.h"
#include "proto/global/EFDC0.h"
#include "proto/global/F56F0.h"
#include "proto/global/F600.h"
#include "proto/global/F9450.h"
#include "proto/global/FCCD0.h"
#include "proto/menu/1AF0.h"
#include "sched.h"

typedef struct Struct_80025D14 {
    char pad0[4];
    s16 price;
    char pad6[4];
    u8 unkA;
    s8 itemSlot;
    u8 hubWorld;
    u8 mode;
    u8 step;
    u8 unkF;
    u8 unk10;
    u8 itemLevel;
    u8 unk12;
} Struct_80025D14;

// Shop actors (Cranky/Funky/Candy) and the shop's overlay widget actor: one component.
typedef struct MenuShopActor {
    /* 0x000 */ Actor base;
    /* 0x178 */ Struct_80025D14 *unk178;
} MenuShopActor;


extern u8 gPlayerInventoryTable[][0x5E];
extern u8 gPlayerCharacterId;

s32 menuCheckBitgridOtherSlots(Struct_80025D14 *state, s32 bitOffset) {
    s32 found = 0;
    s32 i;

    for (i = 0; found == 0 && i != 5; i++) {
        if (i != gPlayerCharacterId) {
            found |= gPlayerInventoryTable[i][state->itemSlot] & (1 << (bitOffset + 0x1F));
        }
    }
    return found;
}

#pragma GLOBAL_ASM("asm/menu/nonmatchings/1AF0/D_80033A50.s")

#pragma GLOBAL_ASM("asm/menu/nonmatchings/1AF0/D_80033A78.s")

extern Gfx D_1000118[];
extern Mtx D_20000C0;

Gfx *menuDrawShopCostPrompt(Gfx *dl, MenuShopActor *actor) {
    Struct_80025D14 *st = actor->unk178;
    u8 buf[0x28];

    if (st->mode == 1) {
        gSPDisplayList(dl++, D_1000118);
        gSPMatrix(dl++, &D_20000C0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
        gDPPipeSync(dl++);
        gDPSetCombineLERP(dl++, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0);
        switch (st->step) {
        case 1:
            actor->base.unk15F = 0;
            st->step = 5;
        case 5: {
            s32 diff = 0xFF - actor->base.unk15F;

            actor->base.unk15F += diff >= 9 ? 8 : diff;
            gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, actor->base.unk15F);
            _sprintf(buf, "q %s", textTableGetString(0x24, 0x10, 1));
            dl = textDrawStringVtx(dl, 1, 0x1F4, 0x190, buf, 1);
            _sprintf(buf, "b %s", textTableGetString(0x24, 0x11, 1));
            dl = textDrawStringVtx(dl, 1, 0x1F4, 0x1F4, buf, 1);
            break;
        }
        }
    }
    return dl;
}


typedef struct {
    u8 *text[2];
    u8 alpha;
    char pad9[7];
    Mtx mtx[2];
    s32 timer;
    MenuShopActor *shopActor;
} MenuWidgetState;

extern MenuShopActor *gCurrentActor;

void menuSetBitgridValue(Struct_80025D14 *state, s32 slot) {
    gPlayerInventoryTable[slot][state->itemSlot] = state->itemLevel;
}

void menuSetBitgridBit(Struct_80025D14 *state, s32 slot) {
    u8 *ptr = &gPlayerInventoryTable[slot][state->itemSlot];
    *ptr |= 1 << (state->itemLevel - 1);
}

void menuUpdateAllBitgridSlots(Struct_80025D14 *state, u8 asBit) {
    s32 i = 0;

    do {
        if (asBit) {
            menuSetBitgridBit(state, i);
        } else {
            menuSetBitgridValue(state, i);
        }
        i++;
    } while (i < 5);
}

extern PlayerStruct *gPlayerSlots;
extern u8 D_800334DC[];

void menuApplyPurchase(Struct_80025D14 *state, u8 *inventory) {
    s16 queueItemId = -1;
    u8 hasItem = func_806F6E58(gPlayerCharacterId);

    switch (state->itemSlot) {
    case 2:
    case 4:
        if (state->itemLevel >= 2) {
            menuUpdateAllBitgridSlots(state, 1);
        } else {
            menuSetBitgridBit(state, gPlayerCharacterId);
        }
        break;
    case 1:
    case 3:
        menuUpdateAllBitgridSlots(state, 0);
        break;
    default:
        menuSetBitgridValue(state, gPlayerCharacterId);
        break;
    }
    if (state->itemSlot == 4) {
        u8 v = D_800334DC[state->itemLevel];
        if (gPlayerInventoryTable[8][0xC] < v) {
            gPlayerInventoryTable[8][0xC] = v;
            healthRefill(0);
            gPlayerSlots->unk2E2 |= 0x11;
        }
    }
    switch (state->itemSlot) {
    case 2:
    case 3:
        queueItemId = 2;
        break;
    case 4:
        queueItemId = 7;
        break;
    case 0:
        if (hasItem == 0 && func_806F6E58(gPlayerCharacterId) != 0) {
            queueItemId = 5;
        }
        break;
    }
    slotQueueAddValue(1, 0, -state->price);
    if (queueItemId >= 0) {
        slotQueueAddValue(queueItemId, 0, 0x270F);
    }
    eepromSavePlayerData();
}


extern u16 D_80750AC8;
extern u8 D_807FCC4C;

typedef struct {
    s16 slot;
    s16 level;
    s16 price;
} MenuM1_Entry;
extern MenuM1_Entry D_80033260[][7];
extern MenuM1_Entry D_80033334[][7];
extern MenuM1_Entry D_80033408[][7];
extern u8 gCurrentWorldId;

void menuCheckInventoryItemPurchased(Struct_80025D14 *state, u8 *inventory, s32 isExiting) {
    MenuM1_Entry *tbl;
    s32 found = 0;
    s32 count = 6;
    s32 i;

    if (flagGet(0x1CB, 0) == 0) {
        do {
            count--;
            if (count < 0) {
                break;
            }
        } while (flagGet(count + 0x1C5, 0) == 0);
    }
    count++;
    state->hubWorld = mapGetHubWorldIndex(gCurrentWorldId, 0);
    switch (gCurrentActor->base.actorType) {
    case 0xBD:
        tbl = D_80033260[0];
        break;
    case 0xBF:
        tbl = D_80033334[0];
        break;
    case 0xBE:
        tbl = D_80033408[0];
        break;
    }
    tbl += gPlayerCharacterId * 7;
    for (i = 0; i < count && found == 0; i++) {
        if (tbl[i].slot >= 0) {
            switch (tbl[i].slot) {
            case 2:
            case 4:
                if (!(inventory[tbl[i].slot] & (1 << (tbl[i].level + 0x1F)))) {
                    found = 1;
                }
                break;
            default:
                if (inventory[tbl[i].slot] < tbl[i].level) {
                    found = 1;
                }
                break;
            }
            if (found != 0) {
                state->itemSlot = tbl[i].slot;
                D_80750AC8 = (state->price = tbl[i].price);
                state->itemLevel = tbl[i].level;
            }
        }
    }
    if (found == 0) {
        state->price = 0;
        state->itemSlot = -1;
        D_80750AC8 = state->price;
        if (count >= 7) {
            state->itemSlot = -2;
        }
    }
    state->unk10 = D_807FCC4C;
}


s32 menuGetOptionAvailability(Struct_80025D14 *state, s32 optionIdx) {
    s32 ret = 0;

    state->unkF = 3;
    if (state->itemSlot >= 0) {
        s32 val = slotQueueGetValue(1, 0);
        ret = 2;
        if (val >= state->price) {
            state->unkF = 1;
        } else {
            ret = 3;
        }
    } else if (state->itemSlot == -2) {
        ret = 1;
    }

    if (state->unkA != 0) {
        ret += 4;
    }

    return ret;
}

s32 menuIsSpecialMovePurchased(Struct_80025D14 *state) {
    s32 ret = gCurrentActor->base.actorType == 0xBD;

    if (ret != 0) {
        ret = state->unkA == 0;
        if (ret != 0) {
            return state->itemSlot < 0;
        }
    }
}

void menuResetSubmenuState(Struct_80025D14 *state, s32 *outAvailability) {
    *outAvailability = 0;
    state->unkF = 1;
    state->itemSlot = -1;
}

extern u16 D_800334EC[];
extern u16 D_80033500[];
extern u16 D_80033514[];
extern u16 D_80033528[];
extern u8 D_800334DD[];
void resQueueAttachActor(void *, u16, u8); // FAKE: callee prototype steer
typedef struct {
    u8 hi;
    u8 lo;
} MenuM1_Pair;

void menuFormatShopPurchaseText(Struct_80025D14 *state, void *inventory, s32 hasSecondAction) {
    MenuM1_Pair *pairs;
    u16 textParam1;
    s32 availability;
    u16 a;
    u16 b;
    u16 c;
    u16 d;
    s32 avail;
    u16 v;
    u16 priceOrCount;
    s32 cnt;
    s16 f;

    if (currentActorTestClearFlag() != 0) {
        pairs = NULL;
        availability = menuGetOptionAvailability(state, hasSecondAction);
        currentActorClearFlag();
        state->unk12 = 0;
        state->step++;
        switch (gCurrentActor->base.actorType) {
        case 0xBF:
            a = 3;
            b = 7;
            c = 0xC;
            d = 0xE;
            if (state->itemSlot >= 0) {
                avail = menuCheckBitgridOtherSlots(state, 1);
                if (((u8 *)inventory)[state->itemSlot] & 1) {
                    b = 9;
                    if (D_807FCC4C < D_800334DD[((u8 *)inventory)[state->itemSlot]]) {
                        a = 6;
                        c = 0xD;
                        d = 0xF;
                        state->unk12 = 1;
                    } else {
                        a = 5;
                        b = 8;
                    }
                } else if (avail == 0) {
                    a = 4;
                }
            }
            D_80033500[2] = a;
            D_80033500[3] = b;
            D_80033500[6] = c;
            D_80033500[7] = d;
            pairs = (MenuM1_Pair *)D_80033500;
            textParam1 = 9;
            break;
        case 0xBD:
            v = 0;
            hasSecondAction = 0;
            priceOrCount = D_80750AC8;
            availability = menuGetOptionAvailability(state, hasSecondAction);
            if (availability == 0 || availability == 1) {
                availability = 0;
                priceOrCount = 0xF;
            }
            textParam1 = 8;
            pairs = (MenuM1_Pair *)D_800334EC;
            if (state->unkA == 0) {
                if (flagGet(0x61, 2) != 0) {
                    flagSet(0x61, 0, 2);
                    menuResetSubmenuState(state, &availability);
                    if (flagGet(0x17B, 0) != 0) {
                        v = 0x20;
                    } else if (flagGet(0x62, 2) != 0) {
                        flagSet(0x62, 0, 2);
                        v = 0x22;
                    } else {
                        v = 0x21;
                    }
                } else {
                    cnt = flagCountRange(0x225, 0x28, 0);
                    if (cnt >= 0xF) {
                        menuResetSubmenuState(state, &availability);
                        if (flagGet(0x17B, 0) != 0) {
                            v = 0x20;
                        } else {
                            v = 2;
                            priceOrCount = cnt;
                        }
                    }
                }
            }
            D_80750AC8 = priceOrCount;
            D_800334EC[0] = v;
            break;
        case 0xBE:
            pairs = (MenuM1_Pair *)D_80033514;
            if (state->itemSlot == 3) {
                pairs = (MenuM1_Pair *)D_80033528;
            } else {
                a = 3;
                f = 4;
                if (state->itemSlot >= 0 && (((u8 *)inventory)[state->itemSlot] & 1)) {
                    a = 5;
                    f = 6;
                }
                D_80033514[2] = a;
                D_80033514[3] = f;
            }
            textParam1 = 7;
            break;
        }
        if (hasSecondAction != 0) {
            resQueueAttachActor(&gCurrentActor->base, textParam1, pairs[8].lo);
        }
        resQueueAttachActor(&gCurrentActor->base, textParam1, pairs[availability].lo);
        if (availability == 2 || availability == 3 || availability == 6 || availability == 7) {
            slotQueueInit(0);
            slotQueueUpdate(1, 1, 0);
            slotQueueUpdate(0xE, 1, 0);
        }
    }
}


void menuDispatchSubmenuAction(Struct_80025D14 *state, u8 *inventory, s32 flag) {
    switch (state->step) {
    case 0:
        menuFormatShopPurchaseText(state, inventory, flag);
        break;
    case 1:
        if (!(gCurrentActor->base.flags & 0x02000000)) {
            state->step = 0;
            state->mode = state->unkF;
            camResumePath();
        }
        break;
    }
}


extern Actor *gPrimaryPlayerActor;

s32 menuExitSubmenu(Struct_80025D14 *state, u8 *inventory, s32 flagId) {
    s32 flag = flagGet((s16)flagId, 0) == 0;

    menuCheckInventoryItemPurchased(state, inventory, flag);
    state->mode = 0;
    state->step = 0;
    if (flagGet(0x61, 2) == 0) {
        if (flag != 0) {
            playerWaypointPathStartPacked(gPrimaryPlayerActor, gCurrentActor, 0, 0x1B);
            camStartPath(0, 0, 1);
        } else {
            camStartPath(0, 4, 1);
            playerStateQueueCallback(0x1B, gCurrentActor, 0);
        }
    } else {
        playerStateQueueCallback(0x1B, gCurrentActor, 0);
        camStartPath(0, 0xB, 1);
    }
    currentActorClearFlag();
    gCurrentActor->base.flags |= 0x10000000;
    return flag;
}



void menuTransitionToSubmenu(Struct_80025D14 *state, u8 *inventory) {
    state->unkA = 1;
    camStartPath(0, 0xF, 1);
    currentActorClearFlag();
    menuCheckInventoryItemPurchased(state, inventory, 0);
    state->mode = 0;
    state->step = 0;
    playerStateQueueCallback(0x1B, gCurrentActor, 0);
}

extern s32 gGlobalPauseFlags;


void menuUpdateShopPurchaseStep(Struct_80025D14 *state, u8 *inventory) {
    s32 textParam1;
    s32 textParam2;

    switch (state->step) {
    case 0:
        if (currentActorTestClearFlag() != 0) {
            currentActorClearFlag();
            state->step++;
        }
        break;
    case 1:
    case 5:
        renderCallbacksRegister(menuDrawShopCostPrompt, gCurrentActor, 3);
        break;
    case 10:
        if (menuIsSpecialMovePurchased(state) == 0) {
            slotQueueCancel(1, 0);
            slotQueueCancel(0xE, 0);
            menuApplyPurchase(state, inventory);
            switch (state->itemSlot) {
            case 0:
            case 1:
                playerStateQueueCallback(0x52, 0, 0);
                gGlobalPauseFlags &= ~0x10030;
                gPlayerSlots->actor->flags |= 0x40000000;
                break;
            case 4:
                actorSpawn(0x144, 0);
                playerStateQueueCallback(0x53, 0, 0);
                break;
            case 2:
            case 3:
                actorSpawn(0x144, 0);
                actorScriptStartByIndex(gPlayerSlots->actor, 0x85);
                break;
            }
            camStartPath(gPlayerSlots->actor, 2, 1);
            state->mode = 2;
            state->step = 0;
        } else {
            camStartPath(0, 0xA, 1);
            flagSet(0x61, 1, 2);
            state->step++;
        }
        break;
    case 15:
        textParam1 = -1;
        switch (gCurrentActor->base.actorType) {
        case 0xBD:
            textParam1 = 8;
            if (menuIsSpecialMovePurchased(state) != 0) {
                state->unkA = 1;
                menuTransitionToSubmenu(state, inventory);
                return;
            }
            textParam2 = 0xA;
            break;
        case 0xBF:
            textParam1 = 9;
            textParam2 = 0x11;
            break;
        case 0xBE:
            textParam1 = 7;
            textParam2 = 0x10;
            break;
        }
        slotQueueCancel(1, 0);
        slotQueueCancel(0xE, 0);
        camStartPath(gPlayerSlots->actor, 3, 1);
        state->mode = 3;
        state->step = 0;
        resQueueAttachActor(&gCurrentActor->base, textParam1, textParam2);
        break;
    }
}

extern u16 D_80033A50[][4];
extern u16 D_80033A78[];
extern u16 D_800334E4[];

void menuUpdateShopDialogueStep(Struct_80025D14 *state, void *inventory, s32 flagId) {
    s32 textParam2;
    s32 textParam1;
    s32 extraTextParam;

    switch (state->step) {
    case 0:
        if (currentActorTestClearFlag() != 0) {
            extraTextParam = -1;
            gGlobalPauseFlags |= 0x10030;
            gPlayerSlots->actor->flags &= ~0x40000000;
            textParam1 = 0;
            textParam2 = -1;
            currentActorClearFlag();
            switch (state->itemSlot) {
            case 0:
                textParam2 = D_80033A50[gPlayerCharacterId][((u8 *)inventory)[state->itemSlot]];
            case 1:
                if (textParam2 == -1) {
                    textParam2 = D_80033A78[((u8 *)inventory)[state->itemSlot]];
                }
                textParam1 = 8;
                break;
            case 4:
                if (state->itemLevel == 1) {
                    if (menuCheckBitgridOtherSlots(state, 1) == 0) {
                        extraTextParam = 0x15;
                    }
                    textParam2 = 0x12;
                } else if (D_807FCC4C == state->unk10 + 1) {
                    textParam2 = 0x14;
                } else {
                    textParam2 = 0x13;
                }
                textParam1 = 9;
                break;
            case 2:
                textParam2 = D_800334E4[state->itemLevel];
            case 3:
                if (textParam2 == -1) {
                    D_80750AC8 = slotQueueGetMaxValue(2, 0);
                    textParam2 = 0x15;
                }
                textParam1 = 7;
                break;
            }
            resQueueAttachActor(&gCurrentActor->base, textParam1, textParam2);
            if (extraTextParam >= 0) {
                resQueueAttachActor(&gCurrentActor->base, textParam1, extraTextParam);
            }
            state->step++;
        }
        break;
    case 1:
        if (!(gCurrentActor->base.flags & 0x02000000)) {
            flagSet(flagId, 1, 0);
            camResumePath();
            state->step++;
        }
        break;
    case 2:
        if (currentActorTestClearFlag() != 0) {
            menuTransitionToSubmenu(state, inventory);
        }
        break;
    }
}


void menuUpdateShopExitingStep(Struct_80025D14 *state, u8 *inventory, s32 flagId) {
    s32 slotIndex;
    s32 camPathId;
    s32 textParam1;
    s32 textParam2;
    s32 queueItemId;
    s32 itemSlot;

    switch (state->step) {
    case 0:
        if (!(gCurrentActor->base.flags & 0x02000000)) {
            camResumePath();
            state->step++;
            flagSet(flagId, 1, 0);
        }
        break;
    case 2:
        if (!(gCurrentActor->base.flags & 0x02000000)) {
            slotIndex = -1;
            camResumePath();
            state->step = 4;
            switch (gCurrentActor->base.actorType) {
            case 0xBE:
                slotIndex = 2;
            case 0xBF:
                if (slotIndex < 0) {
                    slotIndex = 7;
                }
                slotQueueUpdate(slotIndex, 0, 0);
                break;
            }
        }
        break;
    case 1:
        if (currentActorTestClearFlag() != 0) {
            camPathId = 1;
            queueItemId = -1;
            itemSlot = -1;
            currentActorClearFlag();
            playerResumeLocomotion(gPrimaryPlayerActor);
            switch (gCurrentActor->base.actorType) {
            case 0xBE:
                textParam1 = 7;
                textParam2 = 0x11;
                queueItemId = 2;
                itemSlot = 2;
            case 0xBF:
                if (queueItemId < 0) {
                    textParam1 = 9;
                    textParam2 = 0x10;
                    queueItemId = 7;
                    itemSlot = 4;
                }
                if (itemSlot >= 0 && (inventory[itemSlot] & 1)) {
                    if (slotQueueGetValue((u8)queueItemId, 0) < slotQueueGetMaxValue(queueItemId, 0)) {
                        resQueueAttachActor(&gCurrentActor->base, textParam1, textParam2);
                        slotQueueAddValue(queueItemId, 0, 0x3E7);
                        state->step = 0;
                        camPathId = 5;
                    }
                }
                break;
            }
            state->step += 2;
            camStartPath(0, (s16)camPathId, 1);
        }
        break;
    case 4:
        if (currentActorTestClearFlag() != 0) {
            currentActorClearFlag();
    case 3:
            mapTransitionToPreviousOrExit();
            state->step = 0xA;
        }
        break;
    }
}


void menuDispatchCurrentMenuAction(Struct_80025D14 *state, u8 *inventory, s32 flagId) {
    s32 flag = flagGet((s16)flagId, 0) == 0;

    switch (state->mode) {
    case 0:
        menuDispatchSubmenuAction(state, inventory, flag);
        break;
    case 1:
        menuUpdateShopPurchaseStep(state, inventory);
        break;
    case 2:
        menuUpdateShopDialogueStep(state, inventory, flagId);
        break;
    case 3:
        menuUpdateShopExitingStep(state, inventory, flagId);
        break;
    }
}

extern s32 gCurrentMap;

void menuUpdateCrankyShopActor(void) {
    s32 i;
    s32 count;
    s32 camPathId;
    Struct_80025D14 *st;
    s32 pad;
    u8 *inventory;
    s32 flag;
    s32 scriptId;

    behaviourFrameBegin();
    if (gCurrentMap == 5) {
        st = gCurrentActor->unk178;
        inventory = gPlayerInventoryTable[gPlayerCharacterId];
        if (!(gCurrentActor->base.flags & 0x10)) {
            if (flagGet(0x180, 0) != 0) {
                gCurrentActor->base.unk155 = 0;
            } else {
                gCurrentActor->base.unk155 = 0xFF;
            }
        }
        if (gCurrentActor->base.unk155 != 0xFF) {
            flag = 0x17F;
            if (mapGetHubWorldIndex(gCurrentWorldId, 0) != 7) {
                flag = 0x177;
            }
            scriptId = 0x26E;
            if (!(gCurrentActor->base.flags & 0x10)) {
                if (menuExitSubmenu(st, inventory, flag) != 0) {
                    scriptId = 0x26F;
                }
                actorScriptStart(&gCurrentActor->base, scriptId);
            }
            menuDispatchCurrentMenuAction(st, inventory, flag);
        } else {
            if (!(gCurrentActor->base.flags & 0x10)) {
                st->hubWorld = 7;
                if (flagGet(0x17F, 0) == 0) {
                    actorScriptStart(&gCurrentActor->base, 0x26E);
                    camStartPath(0, 5, 1);
                    gCurrentActor->base.state = 0;
                    flagSet(0x64, 1, 2);
                } else {
                    count = 0;
                    i = 0;
                    do {
                        count += flagGet(i + 0x182, 0) != 0;
                        i++;
                    } while (i != 4);
                    if (count != 4) {
                        camPathId = 0;
                        gCurrentActor->base.state = 3;
                    } else {
                        camPathId = 6;
                        gCurrentActor->base.state = 4;
                        st->itemSlot = 1;
                        st->price = 0;
                        st->itemLevel = 1;
                        menuApplyPurchase(st, inventory);
                        flagSet(0x180, 1, 0);
                    }
                    playerWaypointPathStartPacked(gPrimaryPlayerActor, gCurrentActor, 0, 0x1B);
                    camStartPath(0, (s16)camPathId, 1);
                    currentActorClearFlag();
                    actorScriptStart(&gCurrentActor->base, 0x26E);
                }
            }
            switch (gCurrentActor->base.state) {
            case 0:
                if (currentActorTestClearFlag() != 0) {
                    resQueueAttachActor(&gCurrentActor->base, 8, 0x1C);
                    gCurrentActor->base.state = 1;
                }
                break;
            case 1:
                if (!(gCurrentActor->base.flags & 0x02000000)) {
                    playerResumeLocomotion(gPrimaryPlayerActor);
                    currentActorClearFlag();
                    camStartPath(0, 1, 1);
                    mapTransitionToPreviousOrExit();
                    gCurrentActor->base.state = 2;
                }
                break;
            case 3:
                if (currentActorTestClearFlag() != 0) {
                    resQueueAttachActor(&gCurrentActor->base, 8, 0x1D);
                    gCurrentActor->base.state = 1;
                }
                break;
            case 4:
                if (currentActorTestClearFlag() != 0) {
                    resQueueAttachActor(&gCurrentActor->base, 8, 0x1E);
                    gCurrentActor->base.state = 5;
                }
                break;
            case 5:
                if (!(gCurrentActor->base.flags & 0x02000000)) {
                    camResumePath();
                    gCurrentActor->base.state = 6;
                }
                break;
            case 6:
                if (currentActorTestClearFlag() != 0) {
                    playerStateQueueCallback(0x52, 0, 0);
                    gGlobalPauseFlags &= 0xFFFEFFCF;
                    gPlayerSlots->actor->flags |= 0x40000000;
                    gCurrentActor->base.state = 7;
                    currentActorClearFlag();
                    camStartPath(gPlayerSlots->actor, 2, 1);
                }
                break;
            case 7:
                if (currentActorTestClearFlag() != 0) {
                    gGlobalPauseFlags |= 0x10030;
                    D_80750AC8 = 0xF;
                    resQueueAttachActor(&gCurrentActor->base, 8, 0x1F);
                    gCurrentActor->base.state = 1;
                }
                break;
            }
        }
    }
    if (gCurrentActor->base.flags & 0x10000000) {
        behaviourFrameBegin();
        actorScriptedCommandUpdate();
    }
    actorUpdateModelMatrix(&gCurrentActor->base, 0);
}

s32 menuDecodeAddressConstant(s32 val) {
    return val + 0x21F44F;
}



extern s32 csCmdExec;

void menuCheckControllerAntiPiracy(void) {
    Struct_80025D14 *st;
    u8 *inventory;
    s32 pad[4];
    s32 *dest;

    behaviourFrameBegin();
    if (gCurrentMap == 0x19) {
        st = gCurrentActor->unk178;
        inventory = gPlayerInventoryTable[gPlayerCharacterId];

        if (!(gCurrentActor->base.flags & 0x10)) {

            s32 *cur = (s32 *)controllerUpdate;
            s32 *end = (s32 *)controllerLatchPad;
            s32 sum = 0;

            if ((u32)cur < (u32)end) {
                do {
                    sum += *cur;
                    cur++;
                } while ((u32)cur < (u32)end);
            }

            if (sum != (s32)0xA1C0EB24) {
                dest = (s32 *)menuDecodeAddressConstant((s32)&csCmdExec + 0xFFDE0BB1);
                *dest = menuDecodeAddressConstant(0x03BE0BB9);
            }
            menuExitSubmenu(st, inventory, 0x175);
        }
        menuDispatchCurrentMenuAction(st, inventory, 0x175);
    }
    if (gCurrentActor->base.flags & 0x10000000) {
        behaviourFrameBegin();
        actorScriptedCommandUpdate();
    }
    actorUpdateModelMatrix(&gCurrentActor->base, 0);
}
void menuUpdateFunkyShopActor(void) {
    behaviourFrameBegin();
    if (gCurrentMap == 1) {
        Struct_80025D14 *st = gCurrentActor->unk178;
        u8 *inventory = gPlayerInventoryTable[gPlayerCharacterId];

        if (!(gCurrentActor->base.flags & 0x10)) {
            menuExitSubmenu(st, inventory, 0x176);
        }
        menuDispatchCurrentMenuAction(st, inventory, 0x176);
    }
    if (gCurrentActor->base.flags & 0x10000000) {
        behaviourFrameBegin();
        actorScriptedCommandUpdate();
    }
    actorUpdateModelMatrix(&gCurrentActor->base, 0);
}


extern Mtx D_2000180;
typedef struct { s16 unk0; s16 font; } Struct_8003353C;
extern Struct_8003353C D_8003353C[];

Gfx *menuDrawTransformedWidgets(Gfx *dl, MenuShopActor *widgetActor) {
    MenuWidgetState *widget = widgetActor->base.customState;
    s32 i;

    gSPDisplayList(dl++, D_1000118);
    gSPMatrix(dl++, &D_2000180, G_MTX_LOAD | G_MTX_PUSH);
    gDPPipeSync(dl++);
    gDPSetCombineLERP(dl++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
    gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, widget->alpha);

    for (i = 0; i < 2; i++) {
        if (widget->text[i] != 0) {
            gSPMatrix(dl++, &widget->mtx[i], G_MTX_LOAD | G_MTX_PUSH);
            dl = textDrawStringVtx(dl, D_8003353C[i].font, 0, 0, widget->text[i], 0x80);
            gSPPopMatrix(dl++, G_MTX_MODELVIEW);
        }
    }
    return dl;
}


typedef struct {
    s32 a[2];
} MenuTextIdPair;
extern MenuTextIdPair D_8003365C[];
extern s32 D_80033544[5][4][2];
extern s32 D_800335E4[4][2];
extern s32 D_80033604[];
extern s32 D_80033618[];
extern s32 D_80033628[];
extern s32 D_80033634[];
extern s32 D_80033648[];
extern s16 D_80033542;

void menuUpdateTransformedWidgets(void) {
    MenuWidgetState *widget = gCurrentActor->base.customState;
    s32 done = 0;
    Struct_80025D14 *st = NULL;
    f32 mA[4][4];
    f32 mB[4][4];
    MenuTextIdPair textIds;
    s32 i;
    s32 lineHeight;
    s32 fadeStep;

    if (widget->shopActor == NULL) {
        widget->shopActor = (MenuShopActor *)spawnNodeActivate(1, 0);
    }
    if (widget->shopActor != NULL) {
        st = widget->shopActor->unk178;
    }
    if (st != NULL) {
        if (!(gCurrentActor->base.flags & 0x10)) {
            textIds = D_8003365C[0];
            guScaleF(mA, 0.6f, 0.6f, 1.0f);
            guTranslateF(mB, 640.0f, 800.0f, 0.0f);
            guMtxCatF(mA, mB, mA);
            guMtxF2L(mA, &widget->mtx[0]);
            lineHeight = textGetFontHeight(D_80033542);
            guTranslateF(mB, 0.0f, (f32)(lineHeight * 4), 0);
            guMtxCatF(mA, mB, mA);
            guMtxF2L(mA, &widget->mtx[1]);
            if (st->itemSlot == 0) {
                for (i = 0; i < 2; i++) {
                    textIds.a[i] = D_80033544[gPlayerCharacterId][st->itemLevel][i];
                }
            } else if (st->itemSlot == 1) {
                for (i = 0; i < 2; i++) {
                    textIds.a[i] = D_800335E4[st->itemLevel][i];
                }
            } else if (st->itemSlot == 2) {
                widget->timer = 0x82;
                if (st->itemLevel >= 2) {
                    textIds.a[0] = D_80033618[st->itemLevel];
                } else {
                    textIds.a[0] = D_80033604[gPlayerCharacterId];
                }
            } else if (st->itemSlot == 3) {
                widget->timer = 0x82;
                textIds.a[0] = D_80033628[st->itemLevel];
            } else if (st->itemSlot == 4) {
                widget->timer = 0x82;
                if (st->itemLevel == 1) {
                    textIds.a[0] = D_80033634[gPlayerCharacterId];
                } else if (st->unk12 == 0) {
                    textIds.a[0] = D_80033648[st->itemLevel];
                } else {
                    textIds.a[0] = 0x32;
                }
            }
            for (i = 0; i < 2; i++) {
                if (textIds.a[i] >= 0) {
                    widget->text[i] = textTableGetString(0x27, textIds.a[i], 0);
                } else {
                    widget->text[i] = 0;
                }
            }
        }
        if (widget->timer != 0) {
            widget->timer--;
            if (widget->timer == 0) {
                done = 1;
            }
        }
        switch (widget->timer) {
        case 0x78:
            gCurrentActor->base.state = 1;
            break;
        case 0x1E:
            gCurrentActor->base.state = 2;
            break;
        }
        switch (gCurrentActor->base.state) {
        case 1:
            fadeStep = (0xFF - widget->alpha > 0x10) ? 0x10 : 0xFF - widget->alpha;
            widget->alpha += fadeStep;
            break;
        case 2:
            lineHeight = (widget->alpha > 0x10) ? 0x10 : widget->alpha;
            widget->alpha -= lineHeight;
            break;
        }
        if (done == 0) {
            if (gCurrentActor->base.state != 0) {
                renderCallbacksRegister(menuDrawTransformedWidgets, gCurrentActor, 3);
            }
            if (gCurrentActor->base.actorType == 0x140) {
                actorUpdateModelMatrix(&gCurrentActor->base, 0);
            }
        } else {
            actorDespawn(&gCurrentActor->base);
        }
    }
}


void menuUpdateOverlayWidgetActor(void) {
    menuUpdateTransformedWidgets();
}

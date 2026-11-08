#include "common.h"
s32 flagGet(s16, s32);

typedef struct {
    char pad0[4];
    s16 unk4;
    char pad6[4];
    u8 unkA;
    s8 unkB;
    u8 unkC;
    u8 unkD;
    u8 unkE;
    u8 unkF;
    u8 unk10;
    u8 unk11;
    u8 unk12;
} Struct_80025D14;

extern u8 D_807FC950[][0x5E];
extern u8 gPlayerCharacterId;

s32 menuCheckBitgridOtherSlots(Struct_80025D14 *state, s32 bitOffset) {
    s32 found = 0;
    s32 i;

    for (i = 0; found == 0 && i != 5; i++) {
        if (i != gPlayerCharacterId) {
            found |= D_807FC950[i][state->unkB] & (1 << (bitOffset + 0x1F));
        }
    }
    return found;
}

#pragma GLOBAL_ASM("asm/menu/nonmatchings/1AF0/D_80033A50.s")

#pragma GLOBAL_ASM("asm/menu/nonmatchings/1AF0/D_80033A78.s")

typedef struct {
    char pad0[0x15F];
    u8 unk15F;
    char pad160[0x178 - 0x160];
    Struct_80025D14 *unk178;
} MenuShopPromptActor;
extern Gfx D_1000118[];
extern Mtx D_20000C0;
Gfx *textDrawStringVtx();
char *textTableGetString(s32, s32, s32);
s32 _sprintf(char *, const char *, ...);

Gfx *menuDrawShopCostPrompt(Gfx *dl, MenuShopPromptActor *actor) {
    Struct_80025D14 *st = actor->unk178;
    char buf[0x28];

    if (st->unkD == 1) {
        gSPDisplayList(dl++, D_1000118);
        gSPMatrix(dl++, &D_20000C0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
        gDPPipeSync(dl++);
        gDPSetCombineLERP(dl++, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0);
        switch (st->unkE) {
        case 1:
            actor->unk15F = 0;
            st->unkE = 5;
        case 5: {
            s32 diff = 0xFF - actor->unk15F;

            actor->unk15F += diff >= 9 ? 8 : diff;
            gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, actor->unk15F);
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


struct Struct_BB40_58;

typedef struct {
    char *unk0[2];
    u8 unk8;
    char pad9[7];
    Mtx unk10[2];
    s32 unk90;
    struct Struct_BB40_58 *unk94;
} MenuWidgetState;

typedef struct Struct_BB40_58 {
    char pad0[0x58];
    s32 unk58;
    char pad5C[4];
    s32 unk60;
    char pad64[0x154 - 0x64];
    u8 unk154;
    u8 unk155;
    char pad156[0x174 - 0x156];
    MenuWidgetState *unk174;
    Struct_80025D14 *unk178;
} Struct_BB40_58;
extern Struct_BB40_58 *gCurrentActor;

extern u8 D_807FC950[][0x5E];

void menuSetBitgridValue(Struct_80025D14 *state, s32 slot) {
    D_807FC950[slot][state->unkB] = state->unk11;
}

void menuSetBitgridBit(Struct_80025D14 *state, s32 slot) {
    u8 *ptr = &D_807FC950[slot][state->unkB];
    *ptr |= 1 << (state->unk11 - 1);
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

typedef struct {
    char pad0[4];
    Struct_BB40_58 *unk4;
    char pad8[0x2E2 - 8];
    u16 unk2E2;
} MenuM1_C924;
extern MenuM1_C924 *gPlayerSlots;
extern u8 D_800334DC[];
u8 func_806F6E58(u8);
void slotQueueAddValue(s32, s32, s16);
void healthRefill(s32);
void eepromSavePlayerData(void);

void menuApplyPurchase(Struct_80025D14 *state, u8 *inventory) {
    s16 queueItemId = -1;
    u8 hasItem = func_806F6E58(gPlayerCharacterId);

    switch (state->unkB) {
    case 2:
    case 4:
        if (state->unk11 >= 2) {
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
    if (state->unkB == 4) {
        u8 v = D_800334DC[state->unk11];
        if (D_807FC950[8][0xC] < v) {
            D_807FC950[8][0xC] = v;
            healthRefill(0);
            gPlayerSlots->unk2E2 |= 0x11;
        }
    }
    switch (state->unkB) {
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
    slotQueueAddValue(1, 0, -state->unk4);
    if (queueItemId >= 0) {
        slotQueueAddValue(queueItemId, 0, 0x270F);
    }
    eepromSavePlayerData();
}


extern u16 D_80750AC8;
extern u8 D_807FCC4C;

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
} MenuM1_Entry;
extern MenuM1_Entry D_80033260[][7];
extern MenuM1_Entry D_80033334[][7];
extern MenuM1_Entry D_80033408[][7];
extern u8 D_8076A0AB;
s32 mapGetHubWorldIndex(s32, s32);

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
    state->unkC = mapGetHubWorldIndex(D_8076A0AB, 0);
    switch (gCurrentActor->unk58) {
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
        if (tbl[i].unk0 >= 0) {
            switch (tbl[i].unk0) {
            case 2:
            case 4:
                if (!(inventory[tbl[i].unk0] & (1 << (tbl[i].unk2 + 0x1F)))) {
                    found = 1;
                }
                break;
            default:
                if (inventory[tbl[i].unk0] < tbl[i].unk2) {
                    found = 1;
                }
                break;
            }
            if (found != 0) {
                state->unkB = tbl[i].unk0;
                D_80750AC8 = (state->unk4 = tbl[i].unk4);
                state->unk11 = tbl[i].unk2;
            }
        }
    }
    if (found == 0) {
        state->unk4 = 0;
        state->unkB = -1;
        D_80750AC8 = state->unk4;
        if (count >= 7) {
            state->unkB = -2;
        }
    }
    state->unk10 = D_807FCC4C;
}

s32 slotQueueGetValue(s32, s32);

s32 menuGetOptionAvailability(Struct_80025D14 *state, s32 optionIdx) {
    s32 ret = 0;

    state->unkF = 3;
    if (state->unkB >= 0) {
        s32 val = slotQueueGetValue(1, 0);
        ret = 2;
        if (val >= state->unk4) {
            state->unkF = 1;
        } else {
            ret = 3;
        }
    } else if (state->unkB == -2) {
        ret = 1;
    }

    if (state->unkA != 0) {
        ret += 4;
    }

    return ret;
}

s32 menuIsSpecialMovePurchased(Struct_80025D14 *state) {
    s32 ret = gCurrentActor->unk58 == 0xBD;

    if (ret != 0) {
        ret = state->unkA == 0;
        if (ret != 0) {
            return state->unkB < 0;
        }
    }
}

void menuResetSubmenuState(Struct_80025D14 *state, s32 *outAvailability) {
    *outAvailability = 0;
    state->unkF = 1;
    state->unkB = -1;
}

extern u16 D_800334EC[];
extern u16 D_80033500[];
extern u16 D_80033514[];
extern u16 D_80033528[];
extern u8 D_800334DD[];
void currentActorClearFlag(void);
s32 currentActorTestClearFlag();
s32 flagSet(s16, s32, s32);
s32 flagCountRange(s16, s32, s32);
void func_8070D8C0(void *, u16, u8);
void slotQueueInit(s32);
void slotQueueUpdate(s32, s32, s32);
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
        state->unkE++;
        switch (gCurrentActor->unk58) {
        case 0xBF:
            a = 3;
            b = 7;
            c = 0xC;
            d = 0xE;
            if (state->unkB >= 0) {
                avail = menuCheckBitgridOtherSlots(state, 1);
                if (((u8 *)inventory)[state->unkB] & 1) {
                    b = 9;
                    if (D_807FCC4C < D_800334DD[((u8 *)inventory)[state->unkB]]) {
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
            if (state->unkB == 3) {
                pairs = (MenuM1_Pair *)D_80033528;
            } else {
                a = 3;
                f = 4;
                if (state->unkB >= 0 && (((u8 *)inventory)[state->unkB] & 1)) {
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
            func_8070D8C0(gCurrentActor, textParam1, pairs[8].lo);
        }
        func_8070D8C0(gCurrentActor, textParam1, pairs[availability].lo);
        if (availability == 2 || availability == 3 || availability == 6 || availability == 7) {
            slotQueueInit(0);
            slotQueueUpdate(1, 1, 0);
            slotQueueUpdate(0xE, 1, 0);
        }
    }
}

void menuFormatShopPurchaseText(Struct_80025D14 *, void *, s32);
void camResumePath(void);

void menuDispatchSubmenuAction(Struct_80025D14 *state, u8 *inventory, s32 flag) {
    switch (state->unkE) {
    case 0:
        menuFormatShopPurchaseText(state, inventory, flag);
        break;
    case 1:
        if (!(gCurrentActor->unk60 & 0x02000000)) {
            state->unkE = 0;
            state->unkD = state->unkF;
            camResumePath();
        }
        break;
    }
}


extern void *D_807FBB4C;
void playerWaypointPathStartPacked(void *, void *, s32, s32);
void camStartPath(void *, s32, s32);
void menuCheckInventoryItemPurchased(Struct_80025D14 *, u8 *, s32);
s32 playerStateQueueCallback(s32, void *, s32);

s32 menuExitSubmenu(Struct_80025D14 *state, u8 *inventory, s32 flagId) {
    s32 flag = flagGet((s16)flagId, 0) == 0;

    menuCheckInventoryItemPurchased(state, inventory, flag);
    state->unkD = 0;
    state->unkE = 0;
    if (flagGet(0x61, 2) == 0) {
        if (flag != 0) {
            playerWaypointPathStartPacked(D_807FBB4C, gCurrentActor, 0, 0x1B);
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
    gCurrentActor->unk60 |= 0x10000000;
    return flag;
}



void menuTransitionToSubmenu(Struct_80025D14 *state, u8 *inventory) {
    state->unkA = 1;
    camStartPath(0, 0xF, 1);
    currentActorClearFlag();
    menuCheckInventoryItemPurchased(state, inventory, 0);
    state->unkD = 0;
    state->unkE = 0;
    playerStateQueueCallback(0x1B, gCurrentActor, 0);
}

extern s32 D_807FBB60;
s32 slotQueueGetMaxValue(s32, s32);

void renderCallbacksRegister(void *, void *, s32);
void slotQueueCancel(s32, s32);
s32 actorSpawn(s32, s32);
void actorScriptStartByIndex(void *, s32);

void menuUpdateShopPurchaseStep(Struct_80025D14 *state, u8 *inventory) {
    s32 textParam1;
    s32 textParam2;

    switch (state->unkE) {
    case 0:
        if (currentActorTestClearFlag() != 0) {
            currentActorClearFlag();
            state->unkE++;
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
            switch (state->unkB) {
            case 0:
            case 1:
                playerStateQueueCallback(0x52, 0, 0);
                D_807FBB60 &= ~0x10030;
                gPlayerSlots->unk4->unk60 |= 0x40000000;
                break;
            case 4:
                actorSpawn(0x144, 0);
                playerStateQueueCallback(0x53, 0, 0);
                break;
            case 2:
            case 3:
                actorSpawn(0x144, 0);
                actorScriptStartByIndex(gPlayerSlots->unk4, 0x85);
                break;
            }
            camStartPath(gPlayerSlots->unk4, 2, 1);
            state->unkD = 2;
            state->unkE = 0;
        } else {
            camStartPath(0, 0xA, 1);
            flagSet(0x61, 1, 2);
            state->unkE++;
        }
        break;
    case 15:
        textParam1 = -1;
        switch (gCurrentActor->unk58) {
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
        camStartPath(gPlayerSlots->unk4, 3, 1);
        state->unkD = 3;
        state->unkE = 0;
        func_8070D8C0(gCurrentActor, textParam1, textParam2);
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

    switch (state->unkE) {
    case 0:
        if (currentActorTestClearFlag() != 0) {
            extraTextParam = -1;
            D_807FBB60 |= 0x10030;
            gPlayerSlots->unk4->unk60 &= ~0x40000000;
            textParam1 = 0;
            textParam2 = -1;
            if (textParam2) { // FAKE: empty guard steers regalloc
            }
            currentActorClearFlag();
            switch (state->unkB) {
            case 0:
                textParam2 = D_80033A50[gPlayerCharacterId][((u8 *)inventory)[state->unkB]];
            case 1:
                if (textParam2 == -1) {
                    textParam2 = D_80033A78[((u8 *)inventory)[state->unkB]];
                }
                textParam1 = 8;
                break;
            case 4:
                if (state->unk11 == 1) {
                    if (menuCheckBitgridOtherSlots(state, 1) == 0) {
                        extraTextParam = 0x15;
                    }
                    textParam2 = 0x12;
                    textParam1 = 9;
                } else {
                    textParam2 = 0x13;
                    if (D_807FCC4C == state->unk10 + 1) {
                        textParam2 = 0x14;
                        textParam1 = 9;
                    } else {
                        textParam1 = 9;
                    }
                }
                break;
            case 2:
                textParam2 = D_800334E4[state->unk11];
            case 3:
                if (textParam2 == -1) {
                    D_80750AC8 = slotQueueGetMaxValue(2, 0);
                    textParam2 = 0x15;
                }
                textParam1 = 7;
                break;
            }
            func_8070D8C0(gCurrentActor, textParam1, textParam2);
            if (extraTextParam >= 0) {
                func_8070D8C0(gCurrentActor, textParam1, extraTextParam);
            }
            state->unkE++;
        }
        break;
    case 1:
        if (!(gCurrentActor->unk60 & 0x02000000)) {
            flagSet(flagId, 1, 0);
            camResumePath();
            state->unkE++;
        }
        break;
    case 2:
        if (currentActorTestClearFlag() != 0) {
            menuTransitionToSubmenu(state, inventory);
        }
        break;
    }
}

void mapTransitionToPreviousOrExit(void);
void playerResumeLocomotion(void *);

void menuUpdateShopExitingStep(Struct_80025D14 *state, u8 *inventory, s32 flagId) {
    s32 x;
    s32 camPathId;
    s32 textParam1;
    s32 textParam2;
    s32 queueItemId;
    s32 v;

    switch (state->unkE) {
    case 0:
        if (!(gCurrentActor->unk60 & 0x02000000)) {
            camResumePath();
            state->unkE++;
            flagSet(flagId, 1, 0);
        }
        break;
    case 2:
        if (!(gCurrentActor->unk60 & 0x02000000)) {
            x = -1;
            camResumePath();
            state->unkE = 4;
            switch (gCurrentActor->unk58) {
            case 0xBE:
                x = 2;
            case 0xBF:
                if (x < 0) {
                    x = 7;
                }
                slotQueueUpdate(x, 0, 0);
                break;
            }
        }
        break;
    case 1:
        if (currentActorTestClearFlag() != 0) {
            camPathId = 1;
            queueItemId = -1;
            v = -1;
            currentActorClearFlag();
            playerResumeLocomotion(D_807FBB4C);
            switch (gCurrentActor->unk58) {
            case 0xBE:
                textParam1 = 7;
                textParam2 = 0x11;
                queueItemId = 2;
                v = 2;
            case 0xBF:
                if (queueItemId < 0) {
                    textParam1 = 9;
                    textParam2 = 0x10;
                    queueItemId = 7;
                    v = 4;
                }
                if (v >= 0 && (inventory[v] & 1)) {
                    if (slotQueueGetValue((u8)queueItemId, 0) < slotQueueGetMaxValue(queueItemId, 0)) {
                        func_8070D8C0(gCurrentActor, textParam1, textParam2);
                        slotQueueAddValue(queueItemId, 0, 0x3E7);
                        state->unkE = 0;
                        camPathId = 5;
                    }
                }
                break;
            }
            state->unkE += 2;
            camStartPath(0, (s16)camPathId, 1);
        }
        break;
    case 4:
        if (currentActorTestClearFlag() != 0) {
            currentActorClearFlag();
    case 3:
            mapTransitionToPreviousOrExit();
            state->unkE = 0xA;
        }
        break;
    }
}

void menuUpdateShopDialogueStep(Struct_80025D14 *, void *, s32);
void menuUpdateShopExitingStep(Struct_80025D14 *, u8 *, s32);

void menuDispatchCurrentMenuAction(Struct_80025D14 *state, u8 *inventory, s32 flagId) {
    s32 flag = flagGet((s16)flagId, 0) == 0;

    switch (state->unkD) {
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
void behaviourFrameBegin(void);
void actorScriptedCommandUpdate(void);
void actorUpdateModelMatrix(void *, s32);
void actorScriptStart(void *, s32);

void menuUpdateCrankyShopActor(void) {
    s32 i;
    s32 n;
    s32 camPathId;
    Struct_80025D14 *st;
    s32 pad;
    u8 *p;
    s32 flag;
    s32 a3;

    behaviourFrameBegin();
    if (gCurrentMap == 5) {
        st = gCurrentActor->unk178;
        p = D_807FC950[gPlayerCharacterId];
        if (!(gCurrentActor->unk60 & 0x10)) {
            if (flagGet(0x180, 0) != 0) {
                gCurrentActor->unk155 = 0;
            } else {
                gCurrentActor->unk155 = 0xFF;
            }
        }
        if (gCurrentActor->unk155 != 0xFF) {
            flag = 0x17F;
            if (mapGetHubWorldIndex(D_8076A0AB, 0) != 7) {
                flag = 0x177;
            }
            a3 = 0x26E;
            if (!(gCurrentActor->unk60 & 0x10)) {
                if (menuExitSubmenu(st, p, flag) != 0) {
                    a3 = 0x26F;
                }
                actorScriptStart(gCurrentActor, a3);
            }
            menuDispatchCurrentMenuAction(st, p, flag);
        } else {
            if (!(gCurrentActor->unk60 & 0x10)) {
                *((u8 *)st + 0xC) = 7;
                if (flagGet(0x17F, 0) == 0) {
                    actorScriptStart(gCurrentActor, 0x26E);
                    camStartPath(0, 5, 1);
                    gCurrentActor->unk154 = 0;
                    flagSet(0x64, 1, 2);
                } else {
                    n = 0;
                    i = 0;
                    do {
                        n += flagGet(i + 0x182, 0) != 0;
                        i++;
                    } while (i != 4);
                    if (n != 4) {
                        camPathId = 0;
                        gCurrentActor->unk154 = 3;
                    } else {
                        camPathId = 6;
                        gCurrentActor->unk154 = 4;
                        st->unkB = 1;
                        st->unk4 = 0;
                        st->unk11 = 1;
                        menuApplyPurchase(st, p);
                        flagSet(0x180, 1, 0);
                    }
                    playerWaypointPathStartPacked(D_807FBB4C, gCurrentActor, 0, 0x1B);
                    camStartPath(0, (s16)camPathId, 1);
                    currentActorClearFlag();
                    actorScriptStart(gCurrentActor, 0x26E);
                }
            }
            switch (gCurrentActor->unk154) {
            case 0:
                if (currentActorTestClearFlag() != 0) {
                    func_8070D8C0(gCurrentActor, 8, 0x1C);
                    gCurrentActor->unk154 = 1;
                }
                break;
            case 1:
                if (!(gCurrentActor->unk60 & 0x02000000)) {
                    playerResumeLocomotion(D_807FBB4C);
                    currentActorClearFlag();
                    camStartPath(0, 1, 1);
                    mapTransitionToPreviousOrExit();
                    gCurrentActor->unk154 = 2;
                }
                break;
            case 3:
                if (currentActorTestClearFlag() != 0) {
                    func_8070D8C0(gCurrentActor, 8, 0x1D);
                    gCurrentActor->unk154 = 1;
                }
                break;
            case 4:
                if (currentActorTestClearFlag() != 0) {
                    func_8070D8C0(gCurrentActor, 8, 0x1E);
                    gCurrentActor->unk154 = 5;
                }
                break;
            case 5:
                if (!(gCurrentActor->unk60 & 0x02000000)) {
                    camResumePath();
                    gCurrentActor->unk154 = 6;
                }
                break;
            case 6:
                if (currentActorTestClearFlag() != 0) {
                    playerStateQueueCallback(0x52, 0, 0);
                    D_807FBB60 &= 0xFFFEFFCF;
                    gPlayerSlots->unk4->unk60 |= 0x40000000;
                    gCurrentActor->unk154 = 7;
                    currentActorClearFlag();
                    camStartPath(gPlayerSlots->unk4, 2, 1);
                }
                break;
            case 7:
                if (currentActorTestClearFlag() != 0) {
                    D_807FBB60 |= 0x10030;
                    D_80750AC8 = 0xF;
                    func_8070D8C0(gCurrentActor, 8, 0x1F);
                    gCurrentActor->unk154 = 1;
                }
                break;
            }
        }
    }
    if (gCurrentActor->unk60 & 0x10000000) {
        behaviourFrameBegin();
        actorScriptedCommandUpdate();
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}

s32 menuDecodeAddressConstant(s32 val) {
    return val + 0x21F44F;
}



extern s32 csCmdExec;
void controllerUpdate(void);
void controllerLatchPad(void);

void menuCheckControllerAntiPiracy(void) {
    Struct_80025D14 *temp;
    u8 *ptr;
    s32 pad[4];
    s32 *dest;

    behaviourFrameBegin();
    if (gCurrentMap == 0x19) {
        temp = gCurrentActor->unk178;
        ptr = D_807FC950[gPlayerCharacterId];

        if (!(gCurrentActor->unk60 & 0x10)) {

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
            menuExitSubmenu(temp, ptr, 0x175);
        }
        menuDispatchCurrentMenuAction(temp, ptr, 0x175);
    }
    if (gCurrentActor->unk60 & 0x10000000) {
        behaviourFrameBegin();
        actorScriptedCommandUpdate();
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}
void menuUpdateFunkyShopActor(void) {
    behaviourFrameBegin();
    if (gCurrentMap == 1) {
        Struct_80025D14 *temp = gCurrentActor->unk178;
        u8 *ptr = D_807FC950[gPlayerCharacterId];

        if (!(gCurrentActor->unk60 & 0x10)) {
            menuExitSubmenu(temp, ptr, 0x176);
        }
        menuDispatchCurrentMenuAction(temp, ptr, 0x176);
    }
    if (gCurrentActor->unk60 & 0x10000000) {
        behaviourFrameBegin();
        actorScriptedCommandUpdate();
    }
    actorUpdateModelMatrix(gCurrentActor, 0);
}


extern Mtx D_2000180;
typedef struct { s16 unk0; s16 unk2; } Struct_8003353C;
extern Struct_8003353C D_8003353C[];

Gfx *menuDrawTransformedWidgets(Gfx *dl, Struct_BB40_58 *widgetActor) {
    MenuWidgetState *fp = widgetActor->unk174;
    s32 i;

    gSPDisplayList(dl++, D_1000118);
    gSPMatrix(dl++, &D_2000180, G_MTX_LOAD | G_MTX_PUSH);
    gDPPipeSync(dl++);
    gDPSetCombineLERP(dl++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
    gDPSetPrimColor(dl++, 0, 0, 0xFF, 0xFF, 0xFF, fp->unk8);

    for (i = 0; i < 2; i++) {
        if (fp->unk0[i] != 0) {
            gSPMatrix(dl++, &fp->unk10[i], G_MTX_LOAD | G_MTX_PUSH);
            dl = textDrawStringVtx(dl, D_8003353C[i].unk2, 0, 0, fp->unk0[i], 0x80);
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
Struct_BB40_58 *spawnNodeActivate(s32, s32);
s32 textGetFontHeight(s32);
void actorDespawn(void *);
void renderCallbacksRegister(void *, void *, s32);

void menuUpdateTransformedWidgets(void) {
    MenuWidgetState *fp = gCurrentActor->unk174;
    s32 done = 0;
    Struct_80025D14 *st = NULL;
    f32 mA[4][4];
    f32 mB[4][4];
    MenuTextIdPair textIds;
    s32 i;
    s32 cnt;
    s32 d;

    if (fp->unk94 == NULL) {
        fp->unk94 = spawnNodeActivate(1, 0);
    }
    if (fp->unk94 != NULL) {
        st = fp->unk94->unk178;
    }
    if (st != NULL) {
        if (!(gCurrentActor->unk60 & 0x10)) {
            textIds = D_8003365C[0];
            guScaleF(mA, 0.6f, 0.6f, 1.0f);
            guTranslateF(mB, 640.0f, 800.0f, 0.0f);
            guMtxCatF(mA, mB, mA);
            guMtxF2L(mA, &fp->unk10[0]);
            cnt = textGetFontHeight(D_80033542);
            guTranslateF(mB, 0.0f, (f32)(cnt * 4), 0);
            guMtxCatF(mA, mB, mA);
            guMtxF2L(mA, &fp->unk10[1]);
            if (st->unkB == 0) {
                for (i = 0; i < 2; i++) {
                    textIds.a[i] = D_80033544[gPlayerCharacterId][st->unk11][i];
                }
            } else if (st->unkB == 1) {
                for (i = 0; i < 2; i++) {
                    textIds.a[i] = D_800335E4[st->unk11][i];
                }
            } else if (st->unkB == 2) {
                fp->unk90 = 0x82;
                if (st->unk11 >= 2) {
                    textIds.a[0] = D_80033618[st->unk11];
                } else {
                    textIds.a[0] = D_80033604[gPlayerCharacterId];
                }
            } else if (st->unkB == 3) {
                fp->unk90 = 0x82;
                textIds.a[0] = D_80033628[st->unk11];
            } else if (st->unkB == 4) {
                fp->unk90 = 0x82;
                if (st->unk11 == 1) {
                    textIds.a[0] = D_80033634[gPlayerCharacterId];
                } else if (st->unk12 == 0) {
                    textIds.a[0] = D_80033648[st->unk11];
                } else {
                    textIds.a[0] = 0x32;
                }
            }
            for (i = 0; i < 2; i++) {
                if (textIds.a[i] >= 0) {
                    fp->unk0[i] = textTableGetString(0x27, textIds.a[i], 0);
                } else {
                    fp->unk0[i] = 0;
                }
            }
        }
        if (fp->unk90 != 0) {
            fp->unk90--;
            if (fp->unk90 == 0) {
                done = 1;
            }
        }
        switch (fp->unk90) {
        case 0x78:
            gCurrentActor->unk154 = 1;
            break;
        case 0x1E:
            gCurrentActor->unk154 = 2;
            break;
        }
        switch (gCurrentActor->unk154) {
        case 1:
            d = (0xFF - fp->unk8 > 0x10) ? 0x10 : 0xFF - fp->unk8;
            fp->unk8 += d;
            break;
        case 2:
            cnt = (fp->unk8 > 0x10) ? 0x10 : fp->unk8;
            fp->unk8 -= cnt;
            break;
        }
        if (done == 0) {
            if (gCurrentActor->unk154 != 0) {
                renderCallbacksRegister(menuDrawTransformedWidgets, gCurrentActor, 3);
            }
            if (gCurrentActor->unk58 == 0x140) {
                actorUpdateModelMatrix(gCurrentActor, 0);
            }
        } else {
            actorDespawn(gCurrentActor);
        }
    }
}

void menuUpdateTransformedWidgets(void);

void menuUpdateOverlayWidgetActor(void) {
    menuUpdateTransformedWidgets();
}

#include "common.h"
#include "proto/global/10130.h"
#include "proto/global/117190.h"
#include "proto/global/131B0.h"
#include "proto/global/15050.h"
#include "proto/global/F56F0.h"
#include "proto/global/F600.h"

extern volatile u8 D_807467C4;
extern s8 D_80746834;

// .bss 0x807ECCD0-0x807ECE00
OSContStatus D_807ECCD0[4];
OSMesg D_807ECCE0[4];
OSMesgQueue D_807ECCF0;
u8 D_807ECD08;
u8 D_807ECD09;
OSContPad D_807ECD10[4];
OSContPad D_807ECD28[4];
u16 D_807ECD40[4];
u16 D_807ECD48[4];
u16 D_807ECD50[4];
OSContPad D_807ECD58;
u8 D_807ECD5E[2];
OSContPad D_807ECD60;
u16 D_807ECD66;
s16 D_807ECD68[4][16];
OSContPad *D_807ECDE8;
OSContPad *D_807ECDEC;
u16 D_807ECDF0;
OSContPad *D_807ECDF4;
u8 D_807ECDF8;
u8 D_807ECDF9;
u8 D_807ECDFA;
u8 D_807ECDFB;
u8 D_807ECDFC[4];


u8 controllerInit(void) {
    osCreateMesgQueue(&D_807ECCF0, D_807ECCE0, 4);
    osSetEventMesg(OS_EVENT_SI, &D_807ECCF0, NULL);
    osContInit(&D_807ECCF0, &D_807ECD09, D_807ECCD0);
    osContSetCh(4);
    if (!(D_807ECD09 & 1)) {
        D_807ECD09 = 0;
    }
    D_807ECD08 = 0;
    D_807ECDE8 = D_807ECD10;
    D_807ECDF4 = D_807ECD28;
    controllerSetActiveMask(0xFF);
    rumbleInit();
    return D_807ECD09;
}

void controllerStartRead(void) {
    controllerWaitRead();
    if (D_807467C4 == 0) {
        D_807ECD08 = 1;
        osContStartReadData(&D_807ECCF0);
    }
}

void controllerWaitRead(void) {
    if (D_807ECD08 != 0) {
        D_80746834 = 2;
        osRecvMesg(&D_807ECCF0, NULL, OS_MESG_BLOCK);
        D_80746834 = 0;
        D_807ECD08 = 0;
    }
}

void controllerSetActiveMask(u8 mask) {
    u8 count;
    s32 i;
    s32 j;

    count = 0;
    D_807ECDF8 = D_807ECD09 & mask;
    for (i = 0; i < 4; i++) {
        D_807ECD48[i] = 0;
        D_807ECD40[i] = 0;
        D_807ECD50[i] = 0;
        D_807ECDFC[i] = 0;
        for (j = 0; j < 16; j++) {
            D_807ECD68[i][j] = 0;
        }
        if (D_807ECDF8 & (1 << i)) {
            D_807ECDFC[count] = i;
            count++;
        }
    }
}

u8 controllerGetPort(s32 arg0) {
    return D_807ECDFC[arg0];
}

void controllerCompactPads(OSContPad *pads) {
    s32 i;
    s32 dst;

    dst = 0;
    for (i = 0; i < 4; i++) {
        if (D_807ECDF8 & (1 << i)) {
            if (dst != i) {
                pads[dst] = pads[i];
            }
            dst++;
        }
    }
}

u8 controllerGetActiveMask(void) {
    return D_807ECDF8;
}

void controllerGetReadData(OSContPad *pad) {
    if (D_807467C4 == 0 && D_807ECD08 != 0) {
        osContGetReadData(pad);
    }
    D_807ECD08 = 0;
}

extern u8 D_807463B8;
extern s32 gFrameCounter;
extern u8 gScreenRenderFlags;

#define CtrlAHeld D_807ECD40
#define CtrlAPressed D_807ECD48
#define CtrlARepeat D_807ECD50

void controllerUpdate(void) {
    s16 timer;
    OSContPad *pad;
    s32 sum;
    s32 buttons;
    u32 compact;
    u32 *p;
    u16 pressed;
    s32 padIdx;
    s32 k;
    u8 mask;
    u32 bit;
    u8 i;
    u32 *end;
    s32 curButtons;

    compact = menuIsTransitionType6();
    D_807ECD60.button = D_807ECD58.button;
    D_807ECD60.stick_x = D_807ECD58.stick_x;
    D_807ECD60.stick_y = D_807ECD58.stick_y;
    D_807ECD58.button = 0;
    D_807ECD58.stick_x = 0;
    D_807ECD58.stick_y = 0;
    if (D_807ECD08 != 0 || D_807467C4 != 0) {
        if (D_807467C4 == 0 && D_807ECD08 != 0) {
            D_80746834 = 3;
            osRecvMesg(&D_807ECCF0, NULL, OS_MESG_BLOCK);
            D_80746834 = 0;
            rumbleUpdate();
        }
        switch (D_807463B8) {
        case 0:
            controllerFilterInput(D_807ECDE8);
            controllerLatchPad(D_807ECDE8);
            break;
        case 2:
            controllerFilterInput(D_807ECDF4);
            controllerLatchPad(D_807ECDF4);
            func_8060B4D4(D_807ECDE8);
            if (D_807ECD09) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            i = 0;
            do {
                if (D_807ECD09 & (1 << i)) {
                    if (D_807ECD48) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    D_807ECDE8[i].button |= D_807ECDF4[i].button & 0x1000;
                }
                i++;
            } while (i < 4);
            break;
        case 3:
            controllerFilterInput(D_807ECDF4);
            controllerLatchPad(D_807ECDF4);
            playerStateWaypointAimUpdate(D_807ECDE8, D_807ECDF4);
            break;
        }
    }
    if (compact != 0) {
        controllerCompactPads(D_807ECDE8);
    }
    sum = 0;
    D_807ECD66 = (D_807ECD58.button ^ D_807ECD60.button) & D_807ECD58.button;
    p = (u32 *)heapTickDeferredFrees;
    end = (u32 *)heapCodeEnd;
    while (p < end) {
        sum += *p;
        p++;
    }
    padIdx = 0;
    if (sum != 0x624C9A6C) {
        gFrameCounter = 0;
    }
    for (i = 0; i < 4; i++) {
        if (compact != 0) {
            mask = D_807ECDF8 & (1 << i);
        } else {
            mask = D_807ECD09 & (1 << i);
            padIdx = i;
        }
        if (i == 0 && D_807463B8 == 2) {
            if (D_807463B8 == D_807463B8) {} // FAKE: retain CFG without a mode value live across blocks
            mask = mask | 1;
        }
        sum = padIdx * 2; // FAKE: byte offset in the checksum local orders the held-address candidate before the pad load
        if (mask != 0) {
            pad = &D_807ECD10[padIdx];
            curButtons = pad->button; // FAKE: preserve the initial button value's allocation web
            pressed = ((*(u16 *)((u8 *)CtrlAHeld + sum)) ^ curButtons) & curButtons;
            (*(u16 *)((u8 *)CtrlAHeld + sum)) = pad->button;
            buttons = curButtons;
            if (D_807463B8 == 0 && (gScreenRenderFlags & 0x11)) {
                pad->button &= 0x1000;
                pad->stick_x = 0;
                pad->stick_y = 0;
                pressed = 0;
                buttons = pad->button;
            }
            CtrlAPressed[padIdx] = pressed;
            for (k = 0; k < 16; k++) {
                bit = 1 << k;
                if (buttons & bit) {
                    timer = --D_807ECD68[padIdx][k];
                    if (timer <= 0) {
                        CtrlARepeat[padIdx] |= bit;
                        D_807ECD68[padIdx][k] = 2;
                    } else if (timer == 11U) { // FAKE: unsigned compare of the s16 timer selects the target branch form
                        CtrlARepeat[padIdx] |= bit;
                    } else {
                        CtrlARepeat[padIdx] &= ~bit;
                    }
                } else {
                    CtrlARepeat[padIdx] &= ~bit;
                    D_807ECD68[padIdx][k] = 12;
                }
            }
            if (compact != 0) {
                padIdx++;
            }
        }
    }
    D_807ECDEC = D_807ECD10;
    D_807ECDF0 = D_807ECD48[0];
}

void controllerLatchPad(OSContPad *pad) {
    D_807ECD58.button = pad->button;
    D_807ECD58.stick_x = pad->stick_x;
    D_807ECD58.stick_y = pad->stick_y;
}

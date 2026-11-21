#include "common.h"
#include "proto/global/10130.h"
#include "proto/global/117190.h"
#include "proto/global/131B0.h"
#include "proto/global/15050.h"
#include "proto/global/F56F0.h"
#include "proto/global/F600.h"

extern volatile u8 gEepromWriteInProgress;
extern s8 D_80746834;

// .bss 0x807ECCD0-0x807ECE00
OSContStatus D_807ECCD0[4];
OSMesg D_807ECCE0[4];
OSMesgQueue D_807ECCF0;
u8 gContReadPending;
u8 gControllerConnectedMask;
OSContPad gControllerPads[4];
OSContPad D_807ECD28[4];
u16 D_807ECD40[4];
u16 gPadPressedButtons[4];
u16 D_807ECD50[4];
OSContPad gContPadCur;
u8 D_807ECD5E[2];
OSContPad gContPadPrev;
u16 gButtonsPressed;
s16 D_807ECD68[4][16];
OSContPad *gInputContPads;
OSContPad *gCurrentContPad;
u16 gContPressedButtons;
OSContPad *D_807ECDF4;
u8 D_807ECDF8;
u8 D_807ECDF9;
u8 D_807ECDFA;
u8 D_807ECDFB;
u8 D_807ECDFC[4];


u8 controllerInit(void) {
    osCreateMesgQueue(&D_807ECCF0, D_807ECCE0, 4);
    osSetEventMesg(OS_EVENT_SI, &D_807ECCF0, NULL);
    osContInit(&D_807ECCF0, &gControllerConnectedMask, D_807ECCD0);
    osContSetCh(4);
    if (!(gControllerConnectedMask & 1)) {
        gControllerConnectedMask = 0;
    }
    gContReadPending = 0;
    gInputContPads = gControllerPads;
    D_807ECDF4 = D_807ECD28;
    controllerSetActiveMask(0xFF);
    rumbleInit();
    return gControllerConnectedMask;
}

void controllerStartRead(void) {
    controllerWaitRead();
    if (gEepromWriteInProgress == 0) {
        gContReadPending = 1;
        osContStartReadData(&D_807ECCF0);
    }
}

void controllerWaitRead(void) {
    if (gContReadPending != 0) {
        D_80746834 = 2;
        osRecvMesg(&D_807ECCF0, NULL, OS_MESG_BLOCK);
        D_80746834 = 0;
        gContReadPending = 0;
    }
}

void controllerSetActiveMask(u8 mask) {
    u8 count;
    s32 i;
    s32 j;

    count = 0;
    D_807ECDF8 = gControllerConnectedMask & mask;
    for (i = 0; i < 4; i++) {
        gPadPressedButtons[i] = 0;
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
    if (gEepromWriteInProgress == 0 && gContReadPending != 0) {
        osContGetReadData(pad);
    }
    gContReadPending = 0;
}

extern u8 gDemoPlaybackState;
extern u8 gScreenRenderFlags;

#define CtrlAHeld D_807ECD40
#define CtrlAPressed gPadPressedButtons
#define CtrlARepeat D_807ECD50

void controllerUpdate(void) {
    OSContPad *pad;
    s32 sum;
    s32 buttons;
    u32 compact;
    u32 *p;
    u16 pressed;
    u16 *pressedOut;
    s32 padIdx;
    s32 k;
    u8 mask;
    u32 bit;
    u8 i;
    u32 *end;
    s32 curButtons;

    compact = menuIsTransitionType6();
    gContPadPrev.button = gContPadCur.button;
    gContPadPrev.stick_x = gContPadCur.stick_x;
    gContPadPrev.stick_y = gContPadCur.stick_y;
    gContPadCur.button = 0;
    gContPadCur.stick_x = 0;
    gContPadCur.stick_y = 0;
    if (gContReadPending != 0 || gEepromWriteInProgress != 0) {
        if (gEepromWriteInProgress == 0 && gContReadPending != 0) {
            D_80746834 = 3;
            osRecvMesg(&D_807ECCF0, NULL, OS_MESG_BLOCK);
            D_80746834 = 0;
            rumbleUpdate();
        }
        switch (gDemoPlaybackState) {
        case 0:
            controllerFilterInput(gInputContPads);
            controllerLatchPad(gInputContPads);
            break;
        case 2:
            controllerFilterInput(D_807ECDF4);
            controllerLatchPad(D_807ECDF4);
            demoPlaybackReadPad(gInputContPads);
            for (i = 0; i < 4; i++) {
                if (gControllerConnectedMask & (1 << i)) {
                    gInputContPads[i].button |= D_807ECDF4[i].button & 0x1000;
                }
            }
            break;
        case 3:
            controllerFilterInput(D_807ECDF4);
            controllerLatchPad(D_807ECDF4);
            playerStateWaypointAimUpdate(gInputContPads, D_807ECDF4);
            break;
        }
    }
    if (compact != 0) {
        controllerCompactPads(gInputContPads);
    }
    sum = 0;
    gButtonsPressed = BUTTONS_PRESSED(gContPadCur.button, gContPadPrev.button);
    p = (u32 *)heapTickDeferredFrees;
    end = (u32 *)heapCodeEnd;
    while (p < end) {
        sum += *p;
        p++;
    }
    if (sum != 0x624C9A6C) {
        gFrameCounter = 0;
    }
    padIdx = 0;
    for (i = 0; i < 4; i++) {
        if (compact != 0) {
            mask = D_807ECDF8 & (1 << i);
        } else {
            mask = gControllerConnectedMask & (1 << i);
            padIdx = i;
        }
        if (i == 0 && gDemoPlaybackState == 2) {
            mask |= 1;
        }
        if (mask != 0) {
            pad = &gControllerPads[padIdx];
            pressedOut = &CtrlAPressed[padIdx];
            curButtons = pad->button;
            buttons = curButtons; pressed = BUTTONS_PRESSED(curButtons, CtrlAHeld[padIdx]); CtrlAHeld[padIdx] = pad->button; // LAYOUT: one line lets as1 put move a3,a2 after sh a2,0(t0) in the bnez delay slot
            if (gDemoPlaybackState == 0 && (gScreenRenderFlags & 0x11)) {
                pad->button &= 0x1000;
                pad->stick_x = 0;
                pad->stick_y = 0;
                pressed = 0;
                buttons = pad->button;
            }
            *pressedOut = pressed;
            for (k = 0; k < 16; k++) {
                bit = 1 << k;
                if (buttons & bit) {
                    D_807ECD68[padIdx][k]--;
                    if (D_807ECD68[padIdx][k] <= 0) {
                        CtrlARepeat[padIdx] |= bit;
                        D_807ECD68[padIdx][k] = 2;
                    } else if (D_807ECD68[padIdx][k] == 11) {
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
    gCurrentContPad = gControllerPads;
    gContPressedButtons = CtrlAPressed[0];
}

void controllerLatchPad(OSContPad *pad) {
    gContPadCur.button = pad->button;
    gContPadCur.stick_x = pad->stick_x;
    gContPadCur.stick_y = pad->stick_y;
}

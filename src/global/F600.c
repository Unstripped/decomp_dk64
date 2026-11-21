#include "common.h"
#include "proto/global/10130.h"
#include "proto/global/117190.h"
#include "proto/global/131B0.h"
#include "proto/global/15050.h"
#include "proto/global/F56F0.h"
#include "proto/global/F600.h"

extern volatile u8 gEepromWriteInProgress;
extern s8 gWaitPointId;

// .bss 0x807ECCD0-0x807ECE00
OSContStatus D_807ECCD0[4];
OSMesg D_807ECCE0[4];
OSMesgQueue gSiMesgQueue;
u8 gContReadPending;
u8 gControllerConnectedMask;
OSContPad gControllerPads[4];
OSContPad D_807ECD28[4];
u16 gPadHeldButtons[4];
u16 gPadPressedButtons[4];
u16 gPadRepeatButtons[4];
OSContPad gContPadCur;
u8 D_807ECD5E[2];
OSContPad gContPadPrev;
u16 gButtonsPressed;
s16 gPadRepeatTimers[4][16];
OSContPad *gInputContPads;
OSContPad *gCurrentContPad;
u16 gContPressedButtons;
OSContPad *gPhysicalContPads;
u8 gControllerActiveMask;
u8 D_807ECDF9;
u8 D_807ECDFA;
u8 D_807ECDFB;
u8 gControllerActivePorts[4];


u8 controllerInit(void) {
    osCreateMesgQueue(&gSiMesgQueue, D_807ECCE0, 4);
    osSetEventMesg(OS_EVENT_SI, &gSiMesgQueue, NULL);
    osContInit(&gSiMesgQueue, &gControllerConnectedMask, D_807ECCD0);
    osContSetCh(4);
    if (!(gControllerConnectedMask & 1)) {
        gControllerConnectedMask = 0;
    }
    gContReadPending = 0;
    gInputContPads = gControllerPads;
    gPhysicalContPads = D_807ECD28;
    controllerSetActiveMask(0xFF);
    rumbleInit();
    return gControllerConnectedMask;
}

void controllerStartRead(void) {
    controllerWaitRead();
    if (gEepromWriteInProgress == 0) {
        gContReadPending = 1;
        osContStartReadData(&gSiMesgQueue);
    }
}

void controllerWaitRead(void) {
    if (gContReadPending != 0) {
        gWaitPointId = 2;
        osRecvMesg(&gSiMesgQueue, NULL, OS_MESG_BLOCK);
        gWaitPointId = 0;
        gContReadPending = 0;
    }
}

void controllerSetActiveMask(u8 mask) {
    u8 count;
    s32 i;
    s32 j;

    count = 0;
    gControllerActiveMask = gControllerConnectedMask & mask;
    for (i = 0; i < 4; i++) {
        gPadPressedButtons[i] = 0;
        gPadHeldButtons[i] = 0;
        gPadRepeatButtons[i] = 0;
        gControllerActivePorts[i] = 0;
        for (j = 0; j < 16; j++) {
            gPadRepeatTimers[i][j] = 0;
        }
        if (gControllerActiveMask & (1 << i)) {
            gControllerActivePorts[count] = i;
            count++;
        }
    }
}

u8 controllerGetPort(s32 arg0) {
    return gControllerActivePorts[arg0];
}

void controllerCompactPads(OSContPad *pads) {
    s32 i;
    s32 dst;

    dst = 0;
    for (i = 0; i < 4; i++) {
        if (gControllerActiveMask & (1 << i)) {
            if (dst != i) {
                pads[dst] = pads[i];
            }
            dst++;
        }
    }
}

u8 controllerGetActiveMask(void) {
    return gControllerActiveMask;
}

void controllerGetReadData(OSContPad *pad) {
    if (gEepromWriteInProgress == 0 && gContReadPending != 0) {
        osContGetReadData(pad);
    }
    gContReadPending = 0;
}

extern u8 gDemoPlaybackState;
extern u8 gScreenRenderFlags;

#define CtrlAHeld gPadHeldButtons
#define CtrlAPressed gPadPressedButtons
#define CtrlARepeat gPadRepeatButtons

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
            gWaitPointId = 3;
            osRecvMesg(&gSiMesgQueue, NULL, OS_MESG_BLOCK);
            gWaitPointId = 0;
            rumbleUpdate();
        }
        switch (gDemoPlaybackState) {
        case 0:
            controllerFilterInput(gInputContPads);
            controllerLatchPad(gInputContPads);
            break;
        case 2:
            controllerFilterInput(gPhysicalContPads);
            controllerLatchPad(gPhysicalContPads);
            demoPlaybackReadPad(gInputContPads);
            for (i = 0; i < 4; i++) {
                if (gControllerConnectedMask & (1 << i)) {
                    gInputContPads[i].button |= gPhysicalContPads[i].button & 0x1000;
                }
            }
            break;
        case 3:
            controllerFilterInput(gPhysicalContPads);
            controllerLatchPad(gPhysicalContPads);
            playerStateWaypointAimUpdate(gInputContPads, gPhysicalContPads);
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
            mask = gControllerActiveMask & (1 << i);
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
                    gPadRepeatTimers[padIdx][k]--;
                    if (gPadRepeatTimers[padIdx][k] <= 0) {
                        CtrlARepeat[padIdx] |= bit;
                        gPadRepeatTimers[padIdx][k] = 2;
                    } else if (gPadRepeatTimers[padIdx][k] == 11) {
                        CtrlARepeat[padIdx] |= bit;
                    } else {
                        CtrlARepeat[padIdx] &= ~bit;
                    }
                } else {
                    CtrlARepeat[padIdx] &= ~bit;
                    gPadRepeatTimers[padIdx][k] = 12;
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

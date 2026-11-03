// controllerUpdate (src/global/F600.c): controllerUpdate (src/global/F600.c): revisit 7 MiscA: stage 5, score full 23 -> 21 (text 21 -> 19, 2 reloc-only D_807ECD62/63 because D_807ECD60 is the C-defined OSContPad). New lever: a HIDDEN LOCAL for the sum-loop end pointer (u32 *end = (u32 *)func_80611844; while (p < end)) fixed 'lui a3 / addiu a0,a3' (the const web in a3 copied to the var in a0); do/for-forms and decl position equal. Remaining: ring lbu t6 vs v0 for D_807463B8 in the i==0 && ==2 test (the FAKE dead test on D_807463B8 makes it a v0 candidate but is needed for s2/s3 = &D_807ECDE8/const 2), pad ptr/button a0,a1 vs target a1,a2 (+ k=0 move hoist). Tried without gain: callee prototype void<->s32 on every callee, typed constants (U suffix), local type widths + decl-order hill-climb (hc4, 16k+40k evals, T 0 and 1.2), pointer locals for Held/Pressed/Repeat/D_807ECD68 walker, buttons/pressed/held spelling grid (277), dead tests on pad/buttons/k/i in the pad block, deadsweep with == 2 forms (10.9k variants).
#include "common.h"

extern u8 D_807463B8;
extern s32 gFrameCounter;
extern u8 D_8076A0B1;
void heapTickDeferredFrees(void);
void func_80611844(void);
s32 func_8071432C(void);
void func_80712944(OSContPad *);
void func_8060B4D4(OSContPad *);
void playerStateWaypointAimUpdate(OSContPad *, OSContPad *);
void rumbleUpdate(void);
void controllerLatchPad(OSContPad *pad);

#define CtrlAHeld ((u16 *)D_807ECD40)
#define CtrlAPressed ((u16 *)D_807ECD48)
#define CtrlARepeat ((u16 *)D_807ECD50)

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

    compact = func_8071432C();
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
            func_80712944(D_807ECDE8);
            controllerLatchPad(D_807ECDE8);
            break;
        case 2:
            func_80712944(D_807ECDF4);
            controllerLatchPad(D_807ECDF4);
            func_8060B4D4(D_807ECDE8);
            if (D_807ECD09) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            i = 0;
            do {
                if (D_807ECD09 & (1U << i)) {
                    if (D_807ECD48) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                    D_807ECDE8[i].button |= D_807ECDF4[i].button & 0x1000;
                }
                i++;
            } while (i < 4);
            break;
        case 3:
            func_80712944(D_807ECDF4);
            controllerLatchPad(D_807ECDF4);
            playerStateWaypointAimUpdate(D_807ECDE8, D_807ECDF4);
            break;
            if (D_807ECDF8 != 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        }
    }
    if (compact != 0) {
        controllerCompactPads(D_807ECDE8);
    }
    sum = 0;
    D_807ECD66 = (D_807ECD58.button ^ D_807ECD60.button) & D_807ECD58.button;
    p = (u32 *)heapTickDeferredFrees;
    end = (u32 *)func_80611844;
    while (p < end) {
        sum += *p;
        p += 1;
    }
    padIdx = 0;
    k = 0; // FAKE: gives k a long live range so uopt colours timer/k/pad like the target (needs the dead read below)
    if (sum != 0x624C9A6C) {
        gFrameCounter = 0;
    }
    for (i = 0; i < 4; i++) {
        if (compact != 0) {
            mask = D_807ECDF8 & (1U << i);
        } else {
            mask = D_807ECD09 & (1U << i);
            padIdx = i;
        }
        if (i == 0 && D_807463B8 == 2) {
            if (D_807463B8) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            mask = mask | 1;
        }
        if (mask != 0) {
            pad = (OSContPad *)((u16 *)D_807ECD10 + padIdx * 3);
            buttons = *(u16 *)pad;
            pressed = (CtrlAHeld[padIdx] ^ pad->button) & pad->button;
            CtrlAHeld[padIdx] = pad->button;
            if (D_807463B8 == 0) {
                if (D_8076A0B1 & 0x11) {
                    pad->button &= 0x1000;
                    pad->stick_x = 0;
                    pad->stick_y = 0;
                    pressed = 0;
                    buttons = *(u16 *)pad;
                }
            }
            CtrlAPressed[padIdx] = pressed;
            for (k = 0; k < 16; k++) {
                bit = 1 << k;
                if ((buttons & bit)) {
                    D_807ECD68[padIdx][k]--;
                    timer = D_807ECD68[padIdx][k];
                    if (timer <= 0) {
                        CtrlARepeat[padIdx] |= bit;
                        D_807ECD68[padIdx][k] = 2;
                    } else if (timer == 11U) {
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
    if (k != 0) {} // FAKE: long live range for k (see k = 0 above)
    D_807ECDEC = D_807ECD10;
    D_807ECDF0 = D_807ECD48[0];
}

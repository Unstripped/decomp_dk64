// controllerUpdate (src/global/F600.c): stage 5 (7 callee-saved + frame 56 match), text diff 22 -> 21 (deadsweep full 24 -> 23: remaining = pad/value/pad-ptr regs a0/a1 vs a1/a2 + hoisted 'move a2,zero', ring lbu v0 vs t6 at the i==0&&D_807463B8==2 test, lui a3/a0 for func_80611844, 2 reloc-only D_807ECD62/63). Leftovers5 Sched: hill-climb (retype locals/decl swap/stmt swap/dead tests/respell, 100k compiles) found u32 compact/bit, s32 sum, 1U<<i, p+=1, swapped independent stores. KEY: the ring lbu v0 is the candidate made by the FAKE 'if (D_807463B8) {}'; without it lbu is t6 (target) but const-2 web adjsave becomes 7.79 > padIdx 7.625 so s2/s3 swap (110 diff). 'mask = mask | 1; if (mask == 0) {}' (dead test AFTER the assign, inside that block) gives lbu t6 + s2/s3 + ori/andi right (86 total, 383 insns) but the t-ring after it shifts (lui t8 vs t6). Trace: pad-ptr web (BB49-51) does not interfere with IV web lr167 (starts BB52) in ours, target needs IV live over the pad window (a0 held); k init 'move a2,zero' is hoisted to BB49 by uopt in ours but stays in BB52 in target. Tried without effect: callee prototype toggles (void/s32/K&R/u8/s16/u32 on func_8071432C, func_80712944, func_8060B4D4, playerStateWaypointAimUpdate, rumbleUpdate, heapTick, func_80611844), 22x2-spelling typed-constant sweep (2U/12U/16U/0x1000U...), end-pointer spellings, 'x = x;' .loc sweep over every local x every point, 'G = G;' ring-step sweep (emits code for volatile-ish u8 global), single+pair dead tests on padIdx/i/k/mask, explicit row pointer local (worse), dead k = 4 before for-k.
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
    while (p < (u32 *)func_80611844) {
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

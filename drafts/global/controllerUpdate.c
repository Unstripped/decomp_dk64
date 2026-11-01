// controllerUpdate (src/global/F600.c): stage 5 (7 callee-saved + frame 56 match; remaining text diff 22 lines: pad/X/pad-ptr regs a0/a1 vs a1/a2 (needs a hidden a0 holder over the pad window, k=a1 vs a2 cascade + hoisted 'move a2,zero'), ring lbu v0 vs t6 at the i==0&&D_807463B8==2 test (switch value candidate lr29 coloured v0), lui a3/a0 for func_80611844, + 2 reloc-only D_807ECD62/63). Levers that moved it 59->22: buttons as separate s32 var from pad->button, 'pad->button &= 0x1000; buttons = pad->button' (value forwarding, no more ucvt loop copy), 'k = 0' before the i loop + dead 'if (k != 0) {}' after (long live range => timer coloured before k, Repeat ptr first), sum loop as while(p<end), 'timer == 11U' typed const (fixes bnel operand order). Tried: deadsweep single-insert sweep (8k), expression dead-test sweep (2160), fake-statement replacement sweep, decl perm, hill-climb 50k compiles.
#include "common.h"

extern u8 D_807463B8;
extern s32 D_8076A064;
extern u8 D_8076A0B1;
void func_80611730(void);
void func_80611844(void);
s32 func_8071432C(void);
void func_80712944(OSContPad *);
void func_8060B4D4(OSContPad *);
void playerStateWaypointAimUpdate(OSContPad *, OSContPad *);
void func_8060EA28(void);
void controllerLatchPad(OSContPad *pad);

#define CtrlAHeld ((u16 *)D_807ECD40)
#define CtrlAPressed ((u16 *)D_807ECD48)
#define CtrlARepeat ((u16 *)D_807ECD50)

void controllerUpdate(void) {
    s16 timer;
    OSContPad *pad;
    s32 padIdx;
    s32 k;
    s32 bit;
    u32 *p;
    u8 mask;
    u8 i;
    u16 pressed;
    u32 sum;
    s32 buttons;
    s32 compact;

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
            func_8060EA28();
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
                if (D_807ECD09 & (1 << i)) {
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
        }
    }
    if (compact != 0) {
        controllerCompactPads(D_807ECDE8);
    }
    D_807ECD66 = (D_807ECD58.button ^ D_807ECD60.button) & D_807ECD58.button;
    sum = 0;
    p = (u32 *)func_80611730;
    while (p < (u32 *)func_80611844) {
        sum += *p;
        p++;
    }
    padIdx = 0;
    k = 0; // FAKE: gives k a long live range so uopt colours timer/k/pad like the target (needs the dead read below)
    if (sum != 0x624C9A6C) {
        D_8076A064 = 0;
    }
    for (i = 0; i < 4; i++) {
        if (compact != 0) {
            mask = D_807ECDF8 & (1 << i);
        } else {
            mask = D_807ECD09 & (1 << i);
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
                    buttons = *(u16 *)pad;
                    pad->stick_x = 0;
                    pressed = 0;
                    pad->stick_y = 0;
                }
            }
            CtrlAPressed[padIdx] = pressed;
            for (k = 0; k < 16; k++) {
                bit = 1 << k;
                if ((buttons & bit) != 0) {
                    D_807ECD68[padIdx][k]--;
                    timer = D_807ECD68[padIdx][k];
                    if (timer <= 0) {
                        D_807ECD68[padIdx][k] = 2;
                        CtrlARepeat[padIdx] |= bit;
                    } else if (timer == 11U) {
                        CtrlARepeat[padIdx] |= bit;
                    } else {
                        CtrlARepeat[padIdx] &= ~bit;
                    }
                } else {
                    D_807ECD68[padIdx][k] = 12;
                    CtrlARepeat[padIdx] &= ~bit;
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

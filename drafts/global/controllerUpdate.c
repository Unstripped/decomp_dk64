// controllerUpdate (src/global/F600.c): stage 5 after the F600 bss carve (D_807ECD60/62/63 shared lui now matches; objects defined in F600.c, u16 D_807ECD40/48/50): same 7 callee-saved (s0-s6) and frame 56 as target with 4 deadsweep FAKEs, text diff is regalloc only. Target colouring: row ptr D_807ECD68+padIdx*32 in s0, i s1, padIdx s2, const 2 in s3, &D09 s4, compact s5, &D_807463B8 s6; &CtrlAPressed[padIdx] in ra, consts 12/11/16 in t5/t4/t3, buttons load in a2 + var in a3 (the 'pressed' pair uses the CSE'd load), pressed in t2 (t1 unused). Mine: const 2 in s0, &D_807ECDF4 (FAKE-held) in s3, row ptr in ra, Pressed ptr t5, consts t4/t3/t2, pressed t1, buttons t0 + copy a3. Needs one more caller-saved id live across the pressed/row window (13 ids busy in the target, 12 here); uopt priority shows target colours Repeat ptr before bit/inner ptr. Tried: deadsweep (single dead stmt: globals+locals, 4 forms; 2-step beam), declaration order (all 132 moves), 20 expression/type rewrites incl. btn reload / bit u32 (80.5 vs 86 score, no match), pointer locals for Held/Pressed/Repeat/row, permuter 1500s (1200->1085). Unparked diff 86 lines (D_807ECD62/63 reloc-only +2/+3 vs sym).
#include "common.h"

extern volatile u8 D_807467C4;
extern s8 D_80746834;
extern OSContStatus D_807ECCD0[4];
extern OSMesg D_807ECCE0[4];
extern OSMesgQueue D_807ECCF0;
extern u8 D_807ECD08;
extern u8 D_807ECD09;
extern OSContPad D_807ECD10[4];
extern OSContPad D_807ECD28[4];
extern u16 D_807ECD40[4];
extern u16 D_807ECD48[4];
extern u16 D_807ECD50[4];
extern OSContPad D_807ECD58;
extern s16 D_807ECD68[4][16];
extern OSContPad *D_807ECDE8;
extern OSContPad *D_807ECDF4;
extern u8 D_807ECDF8;
extern u8 D_807ECDFC[4];

extern OSContPad D_807ECD60;
extern u16 D_807ECD66;
extern OSContPad *D_807ECDEC;
extern u16 D_807ECDF0;
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
    s32 compact;
    u8 i;
    s32 padIdx;
    u8 mask;
    s32 bit;
    s32 k;
    OSContPad *pad;
    u16 pressed;
    u16 buttons;
    s16 timer;
    u32 sum;
    u32 *p;

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
    for (p = (u32 *)func_80611730; p < (u32 *)func_80611844; p++) {
        sum += *p;
    }
    padIdx = 0;
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
            mask |= 1;
        }
        if (mask != 0) {
            pad = (OSContPad *)((u16 *)D_807ECD10 + padIdx * 3);
            buttons = pad->button;
            pressed = (CtrlAHeld[padIdx] ^ buttons) & buttons;
            CtrlAHeld[padIdx] = buttons;
            if (D_807463B8 == 0) {
                if (D_8076A0B1 & 0x11) {
                    pad->button = buttons & 0x1000;
                    buttons &= 0x1000;
                    pad->stick_x = 0;
                    pad->stick_y = 0;
                    pressed = 0;
                    if (D_807ECDF4) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                }
            }
            CtrlAPressed[padIdx] = pressed;
            for (k = 0; k != 16; k++) {
                bit = 1 << k;
                if (buttons & bit) {
                    D_807ECD68[padIdx][k]--;
                    timer = D_807ECD68[padIdx][k];
                    if (timer <= 0) {
                        D_807ECD68[padIdx][k] = 2;
                        CtrlARepeat[padIdx] |= bit;
                    } else if (timer == 11) {
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
    D_807ECDEC = D_807ECD10;
    D_807ECDF0 = CtrlAPressed[0];
}

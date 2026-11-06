// controllerUpdate (src/global/F600.c): stage 5: full=6 text=4 reloc=2 shape=6, 293/293 instructions, frame 0x38. Finisher base c53c3c2b03eef5a5b4f6d2163e341c6b9e83d985. Improved full17 to6: replace mode dead test with D_807463B8 self-comparison so its value no longer spans blocks; compute byte offset using consumed checksum sum in two statements; carry initial button read through padOffset instead of k. Target has three separate mode loads (v0 at 8060AD50, t6 at8060AF60, t8 at8060AFBC), now reproduced. Remaining held address a0 instead of t0 and held-store/button-move ordering. Mode deletion alone regresses to124; self-comparison alone84 due downstream ugen ring; natural 6-byte pad indexing with timer-address alternate gives10. Held-address integer spelling, late button ghosts and boosting padOffset priority regress; corrected-mode as1 scan has no valid single-record repair. Plain-C full-TU fdiff: FAILED Section .text content mismatch (built2112 expected2112). Improved equivalent C parked; default fdiff remains assembly-backed.
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
    s32 padOffset;

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
            if (D_807463B8 == D_807463B8) {} // FAKE: retain CFG without a mode value live across blocks
            mask = mask | 1;
        }
        sum = padIdx * 3;
        sum *= 2;
        if (mask != 0) {
            pad = (OSContPad *)((u8 *)D_807ECD10 + sum);
            padOffset = *(u16 *)pad; // FAKE: carry the initial button copy outside the timer-index web
            buttons = padOffset;
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
    D_807ECDEC = D_807ECD10;
    D_807ECDF0 = D_807ECD48[0];
}

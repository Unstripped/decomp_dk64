// controllerUpdate (src/global/F600.c): stage 5: full=17 text=15 reloc=2 shape=6, 293/293 insns, frame 0x38. Matcher3 base a090b09477a3c98d6222f0269f6cdfd4b4bf7e53. Improved 21->17: hoist padIdx*3 into padOffset before mask test (21->19); route the first button load through k then buttons (19->17), permitting removal of both old k long-live FAKE statements. Pad now a1 as target; remaining held-pointer a0 vs t0, loaded-button t0 vs a2, mode-override temps and store scheduling. Verified OSContPad u16 button/s8 sticks/6-byte stride; protos OK, concrete u8* replay and unused s32 waypoint arg corrections unchanged. Tried pointer/integer/narrow scalar types, overwritten-formal diagnostic (worse), earlier-call pad reuse, lexical scopes/unions, checksum lifetime bridges, zero-valued timer indices, button-candidate coalescing, typed deadsweeps (2100+2121 no improvement), permuter -j2 600s (55757 iterations), two-round as1 scans (final only invalid held-store deletion helps shape). No header edits. Four FAKEs remain instead of five.
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
            if (D_807463B8) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            mask = mask | 1;
        }
        padOffset = padIdx * 3;
        if (mask != 0) {
            pad = (OSContPad *)((u16 *)D_807ECD10 + padOffset);
            k = *(u16 *)pad; // FAKE: carry button read in the timer-index candidate
            buttons = k;
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

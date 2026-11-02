// menuHandleHighScoreNameEntryInput (src/menu/3E10.c): stage 6 (frame 0x30, shape 0 = registers only), harness diff 77 -> 19: v1 local assigned in the >=16 arm, 'v1 == 1 || (D_800339C0 = v1, v1 >= 0x10)' comma store (matches the duplicated A/B stores and slti pair), dead tests on D_80033F61 (pointerize F61, drop the F60 store reload). Remaining: var v0 gets a0 (target v0) because the F61 value becomes a candidate on v0 (target t2 ring temp), F60 value a3 vs a0. 5 hill-climbs (~120k compiles) over ~40 dead/no-code forms, decl order/types, FAKE substitutions: no gain.
typedef struct MenuM8_PosPair {
    s16 unk0;
    s16 unk2;
} MenuM8_PosPair;

extern s8 D_80033F60;
extern s8 D_800339A8;
extern s8 D_80033F61;
extern s8 D_800339C0;
extern u32 gFrameCounter;
extern MenuM8_PosPair D_800339B8[];

void menuHandleHighScoreNameEntryInput(void *arg0, s32 arg1) {
    MenuScreenState *sp2C = *(MenuScreenState **)((u8 *)arg0 + 0x174);
    MenuHighScoreEntry *table;
    s8 v1;
    s32 v0;
    s32 tmp;
    u8 *p;

    if (D_800339A8 == 0) {
        table = D_80744548;
    } else {
        table = D_80744568;
    }

    if (sp2C->unk0 == 0.0f) {
        if (D_80033F60 < 0) {
            if (arg1 & 1) {
                func_807126B0(D_800339B8[D_800339A8].unk0, 0, D_800339B8[D_800339A8].unk2, 3, 3, 1, 3);
                D_80744514 = D_800339A8 + 6;
            }
            if (arg1 & 2) {
                sfxPlayOnFreeSlot(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                sp2C->unk16 = 0;
                sp2C->unk13 = 0xA;
            }
        } else {
            if (arg1 & 0xC) {
                v1 = D_800339C0 + 1;
            } else {
                v1 = 0;
            }
            v0 = 0;
            if (v1 == 1 || (D_800339C0 = v1, v1 >= 0x10)) {
                if (D_80033F61) {}  // FAKE: dead test, steers register colouring / store sinking
                D_800339C0 = v1;
                v0 = arg1;
                if (v1 >= 0x10) {
                    v1 = 0xF;
                    if (&D_80033F61) {}  // FAKE: dead test, steers register colouring / store sinking
                    D_800339C0 = v1;
                    if (!(gFrameCounter & 1)) {
                        v0 = 0;
                    }
                    v1 = v1;  // FAKE: dead test, steers register colouring / store sinking
                }
            }
            if (D_80033F61) {}  // FAKE: dead test, steers register colouring / store sinking
            p = (u8 *)table + D_80033F60 * 6 + D_80033F61 + 2;
            if (v0 & 4) {
                switch (*p) {
                case 0x20:
                    *p = 0x2E;
                    break;
                case 0x2E:
                    *p = 0x5A;
                    break;
                case 0x41:
                    *p = 0x20;
                    break;
                default:
                    *p = *p - 1;
                    break;
                }
            } else if (v0 & 8) {
                switch (*p) {
                case 0x20:
                    *p = 0x41;
                    break;
                case 0x2E:
                    *p = 0x20;
                    break;
                case 0x5A:
                    *p = 0x2E;
                    break;
                default:
                    *p = *p + 1;
                    break;
                }
            }
            if (arg1 & 1) {
                D_80033F61 += 1;
                if (D_80033F61 == 3) {
                    D_80033F60 = -1;
                    func_80030894(sp2C, &D_80720CF0, 0x122, 0xD2, 0.75f, 2, 0);
                    func_80030894(sp2C, &D_80720D14, 0x23, 0xD2, 0.75f, 2, 0);
                    menuSaveHighScores();
                }
            } else if ((arg1 & 2) && D_80033F61 > 0) {
                D_80033F61 -= 1;
            }
        }
    }
    menuUpdateItemTransition(arg0, sp2C, 1);
}

// menuHandleHighScoreNameEntryInput (src/menu/3E10.c): W4Menu + leftovers6 W2IntC: stage 6 (parked NON_MATCHING in menu/3E10.c), deadsweep full=5 text=5 shape=0 (235/235). Left: gFrameCounter load takes v1 (cand; target t8 ring temp) and the 15 for 'v1 = 0xF; D_800339C0 = v1' is a ring 'li t8,15' (target 'li v1,15'): 3 lines (+2 ring renumbering). Decl order s8 v1 / table / u32 v0 / tmp / p, dead 'D_80033F61 && D_80033F61' after the first arm head, 'gFrameCounter == 0' after 'v1 = 0xF'. W2IntC findings: the gFrameCounter dead test is only needed to stop D_800339C0 being pointerized (count 232 without; ANY dead test at that block split gives count 235 but then fc and 15 are both ring temps, t9/t8, +1 ring phase). Tried: v1 type s32/s16/int, v1 merged with p, chained 'D_800339C0 = v1 = 0xF', v1 dead uses after the store, constant-15 dead tests (0xF/15U/>0xF) on 8 symbols at every point with a block-split test, '&G' tests, 900s anneal incl. line joins, permuter 30k iterations (no gain).
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
    s8 v1;
    MenuHighScoreEntry *table;
    u32 v0;
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
                if (D_80033F61 && D_80033F61) {} // FAKE: dead test steers register colouring (frame counter / D_80033F61 candidates)
                D_800339C0 = v1;
                v0 = arg1;
                if (v1 >= 0x10) {
                    v1 = 0xF;
                    if (gFrameCounter == 0) {} // FAKE: dead test steers register colouring (frame counter / D_80033F61 candidates)
                    D_800339C0 = v1;
                    if (!(gFrameCounter & 1)) {
                        v0 = 0;
                    }
                }
            }
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

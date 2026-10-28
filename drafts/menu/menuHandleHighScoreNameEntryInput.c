// menuHandleHighScoreNameEntryInput (src/menu/3E10.c): stage 4 (frame 0x30 + ra only, text structure matches): regalloc. IDO CSEs &D_800339C0 into v1 (lui;addiu;lb 0(v1);sb 0(v1)) while target re-materialises per use (lui at;sb lo(at)) and hoists li at,1 + lui a1,hi(D_80033F61) above the arg1&0xC branch. NM1 harness swept (all >= 109 diff lines vs 122 baseline, none fixes the CSE): dead stmts (&C0!=0, &C0, C0==0, C0&&C0, C0!=C0, C0=C0, (void)&C0, cast cmp) at 5 anchors; 729 combos of C0 access forms (*(u8*)&, *(s8*)(s32)&, (s8*)((u8*)&D_800339A8+0x18), array-cast) across the 3 write/read sites; 40 v1/v0 cnt-logic restructurings (ternary, init0, goto forms, comma-assign in condition, if/else-if, late store); hoisted flag held=arg1&0xC (s32/u8/u32); volatile C0. Best 109 (dead if (C0 && C0) {} before the arg1&0xC test) but it still CSEs the address. Parked NON_MATCHING.
typedef struct MenuM8_PosPair {
    s16 unk0;
    s16 unk2;
} MenuM8_PosPair;

extern s8 D_80033F60;
extern s8 D_800339A8;
extern s8 D_80033F61;
extern s8 D_800339C0;
extern u32 D_8076A064;
extern MenuM8_PosPair D_800339B8[];
void func_807126B0(s16, s32, s16, s8, s32, s32, s32);

void menuHandleHighScoreNameEntryInput(void *arg0, s32 arg1) {
    Menu3R1_Struct174 *sp2C = *(Menu3R1_Struct174 **)((u8 *)arg0 + 0x174);
    Menu3B_Struct_6 *table;
    s8 v1;
    s32 v0;
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
                func_80609140(0x2C9, 0x7FFF, 63.0f, 1.0f, 0, 0);
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
            D_800339C0 = v1;
            if (v1 == 1 || v1 >= 0x10) {
                v0 = arg1;
                if (v1 >= 0x10) {
                    D_800339C0 = 0xF;
                    if (!(D_8076A064 & 1)) {
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

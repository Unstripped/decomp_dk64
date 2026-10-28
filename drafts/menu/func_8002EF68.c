// func_8002EF68 (src/menu/3E10.c): stage 4 (frame 0x30 + ra only, text structure/instr count match): whole diff is regalloc. IDO CSEs &D_800339C0 into a reg (lui v1;addiu v1;lb v0,0(v1);sb x,0(v1)) while orig re-materialises lui at;sb per use (lui v1;lb v1,lo(v1)); that shifts v0/v1/a0-a3 numbering (orig: a0=D_80033F60,a1=&D_80033F61,a2=table,t0=&F60,v1=cnt,v0=masked arg1; mine a1/a2/a3/a0/v0). Also orig hoists li at,1 and lui a1,hi(D_80033F61) above the arg1&0xC branch. Pointer form p=table+F60*6+F61+2 (addiu v1,v1,2 then 0(v1)) is right. s8 cnt local + two stores/slti dup tail mimicked by if(v1==1||v1>=16). Tried: m2c-literal comma form, goto/do-while CFG forms, volatile/absolute-address C0, global-only no local, struct tag; permuter 8 min best 893 (via address-taken v1, rejected).
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

void func_8002EF68(void *arg0, s32 arg1) {
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

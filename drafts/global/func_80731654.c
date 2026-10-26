// func_80731654 (src/global/135D30.c): TEXT identical, reloc only (D_807FDCD0+0xC0 vs D_807FDD90)
typedef struct E2Ent {
    u8 unk0;
    u8 pad1;
    s16 unk2;
    s16 unk4;
    u8 unk6;
    u8 unk7;
} E2Ent;

extern E2Ent D_80755A20[];
extern E2Ent D_807FDCD0[];

u8 func_80731654(s16 arg0, s16 arg1) {
    s32 i;
    s32 n = 0x71;

    for (i = 0; i < n; i++) {
        if (arg0 == D_80755A20[i].unk0 && arg1 == D_80755A20[i].unk2) {
            return D_80755A20[i].unk6;
        }
    }
    for (i = 0; i < 0x18; i++) {
        if (D_807FDCD0[i].unk7 != 0 && arg0 == D_807FDCD0[i].unk0 && arg1 == D_807FDCD0[i].unk2) {
            return D_807FDCD0[i].unk6;
        }
    }
    return 0;
}

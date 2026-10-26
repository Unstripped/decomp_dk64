// func_807314F4 (src/global/135D30.c): TEXT identical, reloc only (D_807FDCD0+0xC0 vs D_807FDD90); local n=0x71 keeps slt vs reg
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
void func_8073129C(s16, u8, u8);

void func_807314F4(s16 arg0, s16 arg1) {
    s32 i;
    s32 n = 0x71;

    for (i = 0; i < n; i++) {
        if (arg0 == D_80755A20[i].unk0 && arg1 == D_80755A20[i].unk2) {
            func_8073129C(D_80755A20[i].unk4, 1, 0);
            return;
        }
    }
    for (i = 0; i < 0x18; i++) {
        if (D_807FDCD0[i].unk7 != 0 && arg0 == D_807FDCD0[i].unk0 && arg1 == D_807FDCD0[i].unk2) {
            func_8073129C(D_807FDCD0[i].unk4, 1, 0);
            D_807FDCD0[i].unk7 = 0;
            return;
        }
    }
}

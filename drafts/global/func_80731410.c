// func_80731410 (src/global/135D30.c): TEXT identical, reloc only (D_807FDCD0+0xC0 vs D_807FDD90); needs 4x unrolled index loop so end sym cannot be D_807FDD90
typedef struct E2Ent {
    u8 unk0;
    u8 pad1;
    s16 unk2;
    s16 unk4;
    u8 unk6;
    u8 unk7;
} E2Ent;

extern E2Ent D_807FDCD0[];

void func_80731410(s16 arg0, s16 arg1, s16 arg2, u8 arg3) {
    s32 i;

    for (i = 0; i < 0x18; i++) {
        if (D_807FDCD0[i].unk7 == 0) {
            D_807FDCD0[i].unk0 = arg0;
            D_807FDCD0[i].unk2 = arg1;
            D_807FDCD0[i].unk4 = arg2;
            D_807FDCD0[i].unk6 = arg3;
            D_807FDCD0[i].unk7 = 1;
            return;
        }
    }
}

// func_807313BC (src/global/135D30.c): TEXT identical, reloc only: end pointer reloc is D_807FDCD0+0xC0 vs expected D_807FDD90; pointer-compare do-while form gets right reloc but addiu order differs
typedef struct E2Ent {
    u8 unk0;
    u8 pad1;
    s16 unk2;
    s16 unk4;
    u8 unk6;
    u8 unk7;
} E2Ent;

extern E2Ent D_807FDCD0[];
s32 func_805FF938(s16);

void func_807313BC(void) {
    s32 i;

    for (i = 0; i < 0x18; i++) {
        if (func_805FF938(D_807FDCD0[i].unk0) == 0) {
            D_807FDCD0[i].unk7 = 0;
        }
    }
}

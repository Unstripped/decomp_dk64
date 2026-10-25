// func_806F1858 (src/global/F56F0.c): Stage 3 behavioral draft; instruction order matches after hoisting table value, but allocator chooses v0/v1 differently.
typedef struct F5APlayerTableEntry {
    u8 unk0;
    u8 unk1;
    s16 unk2;
    s16 unk4;
    s16 unk6;
} F5APlayerTableEntry;

typedef struct F5APlayerState {
    u8 pad0[0x4C];
    s16 unk4C;
    u8 pad4E[0x40];
    u8 unk8E;
    u8 pad8F[2];
    u8 unk91;
} F5APlayerState;

extern F5APlayerState *D_807FD580;
extern u16 D_80752F30[];

void func_806F1858(s32 arg0, F5APlayerTableEntry *arg1, s32 *arg2) {
    s32 temp_v1;
    u16 temp_v0;

    temp_v1 = D_807FD580->unk8E - 0x14;
    if ((temp_v1 >= 0) && ((u32)temp_v1 < 4U)) {
        temp_v0 = D_80752F30[temp_v1];
        arg1[*arg2].unk0 = 0x7F;
        arg1[*arg2].unk1 = 4;
        arg1[*arg2].unk2 = 0;
        arg1[*arg2].unk4 = temp_v0;
        arg1[*arg2].unk6 = 0;
        *arg2 += 1;
    }
}

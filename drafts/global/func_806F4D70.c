// func_806F4D70 (src/global/F9450.c): matched in F9N3 private copy: u16 index plus arg4 transfer local fixes IDO register allocation
typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
} F9N3_FloatTableEntry;

extern F9N3_FloatTableEntry D_807FD740[];
extern s32 D_807FD780[];

void func_806F4D70(u8 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    unsigned short temp_t6;
    F9N3_FloatTableEntry *temp_v0;
    f32 new_var;

    temp_t6 = arg0;
    temp_v0 = &D_807FD740[temp_t6];
    temp_v0->unk0 = arg1;
    new_var = arg4;
    temp_v0->unk4 = arg2;
    temp_v0->unk8 = arg3;
    temp_v0->unkC = new_var;
    D_807FD780[temp_t6] = 0;
}

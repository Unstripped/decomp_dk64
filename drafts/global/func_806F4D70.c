// func_806F4D70 (src/global/F9450.c): stage 5: code size matches; byte parameter homes exactly, but index/pointer register allocation differs
typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
} F9N3_FloatTableEntry;

extern F9N3_FloatTableEntry D_807FD740[];
extern s32 D_807FD780[];

void func_806F4D70(u8 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    s32 temp_t6;
    F9N3_FloatTableEntry *temp_v0;

    temp_t6 = arg0 & 0xFF;
    temp_v0 = &D_807FD740[temp_t6];
    temp_v0->unk0 = arg1;
    temp_v0->unk4 = arg2;
    temp_v0->unk8 = arg3;
    temp_v0->unkC = arg4;
    D_807FD780[temp_t6] = 0;
}

// func_806F8AD4 (src/global/FCCD0.c): stage 2: compiled slot-value switch; call scheduling and frame remain different
typedef struct {
    void *unk0;
    u8 pad4[0x1C];
    s32 unk20;
    s32 unk24;
    void *unk28;
    u8 unk2C;
} Slot;

extern u8 D_8076A0AB;
extern s32 func_806F7FD0(s32);
extern s32 func_805FF030();
s32 func_806C8DE0(s32);
s32 flagGridSumRows(s32, s32, s32, s32);

u16 func_806F8AD4(u8 arg0, u8 arg1) {
    u16 sp26;
    s32 sp1C;
    s32 temp_a1;
    s32 temp_v0;
    u16 *temp_v1;
    u16 var_a2;
    u8 temp_v1_2;

    sp26 = 0;
    var_a2 = sp26;
    temp_v1_2 = ((Slot *)func_806F7FD0(arg1) + arg0)->unk2C;
    switch (temp_v1_2) {
    case 2:
        break;
    case 0:
        temp_v1 = ((Slot *)func_806F7FD0(arg1) + arg0)->unk0;
        if (temp_v1 != NULL) {
            var_a2 = *temp_v1;
        } else {
            sp1C = func_806C8DE0(arg1);
            temp_v0 = func_805FF030(D_8076A0AB, 1);
            temp_a1 = temp_v0;
            if (arg0 != 0xA) {
                if (arg0 == 0xC) {
                    var_a2 = flagGridSumRows(0x1D5, temp_a1, temp_v0, sp1C);
                }
            } else {
                var_a2 = flagGridSumRows(0x225, temp_a1, temp_a1, sp1C);
            }
        }
        break;
    case 1:
        var_a2 = 0x14;
        break;
    }
    return var_a2;
}

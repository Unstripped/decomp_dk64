// func_806FD7A8 (src/global/100180.c): Stage 3: frame and behavior reconstructed; three-argument mapping call retains target frame size, but outer index remains allocated in a0 rather than a2.
typedef struct {
    u8 unk0[3];
    u8 unk3;
    u8 unk4;
    u8 unk5;
} R1F100180_CharInfo;

extern R1F100180_Entry *D_80754A18[];
extern R1F100180_CharInfo D_80754A34[];
void func_806FB914(s16, u8 *, s16);

s16 func_806FD7A8(s16 arg0, s32 arg1) {
    s16 temp_a2;
    u8 var_v1;
    R1F100180_CharInfo *var_a0;

    temp_a2 = arg0;
    arg0 = temp_a2;
    if (arg0 & 0x80) {
        var_a0 = &D_80754A34[(s16) (arg0 ^ 0x80)];
        var_v1 = var_a0->unk5;
    } else if (((u8 *) &arg1)[3] == 0x20) {
        var_a0 = &D_80754A34[temp_a2];
        var_v1 = var_a0->unk3;
    } else {
        func_806FB914(temp_a2, &((u8 *) &arg1)[3], temp_a2);
        var_v1 = ((u8 *) D_80754A18[temp_a2])[((u8 *) &arg1)[3] * 4 + 2];
        var_a0 = &D_80754A34[temp_a2];
    }
    return var_v1 + var_a0->unk4;
}

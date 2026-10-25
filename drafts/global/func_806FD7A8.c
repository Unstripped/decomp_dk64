// func_806FD7A8 (src/global/100180.c): Stage 3: m2c behavior reconstructed, but typed views add an 8-byte frame and change a0/v1 allocation; needs void-pointer field-form recreation.
typedef struct {
    u8 unk0[3];
    u8 unk3;
    u8 unk4;
    u8 unk5;
} R1F100180_CharInfo;

s32 func_806FB914(s16, u8 *, s16);
extern R1F100180_Entry *D_80754A18[];
extern R1F100180_CharInfo D_80754A34[];

s16 func_806FD7A8(s16 arg0, u8 arg1) {
    s16 temp_a0;
    s16 temp_a2;
    u8 var_v1;
    R1F100180_CharInfo *var_a0;

    temp_a2 = arg0;
    if (arg0 & 0x80) {
        var_a0 = &D_80754A34[(s16)(arg0 ^ 0x80)];
        var_v1 = var_a0->unk5;
    } else if (arg1 == 0x20) {
        var_a0 = &D_80754A34[temp_a2];
        var_v1 = var_a0->unk3;
    } else {
        temp_a0 = temp_a2;
        arg0 = temp_a2;
        func_806FB914(temp_a0, &arg1, temp_a2);
        var_v1 = ((u8 *)D_80754A18[arg0])[arg1 * 4 + 2];
        var_a0 = &D_80754A34[arg0];
    }
    return (s16)(var_v1 + var_a0->unk4);
}

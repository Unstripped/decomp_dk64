// func_806F5A48 (src/global/F9450.c): Stage 4: switch values and calls reconstructed; comparison must remain inside loop to retain target s3/s4 lifetimes.
typedef struct {
    u8 pad0[0x58];
    s32 unk58;
} F9N2At58;

extern s16 modelSlotAppend(s32, f32, f32, f32, f32, s32);
extern void modelSlotGetTransformVectors();
extern void func_806F50C8(s16, s16, s16, s32, s32, s32);
extern void func_806F54E0(s32, s16, u8);

void func_806F5A48(u8 arg0, s16 arg1, F9N2At58 *arg2, u16 arg3) {
    s32 sp90;
    s32 sp8C;
    s32 sp88;
    s32 sp84;
    s32 sp80;
    s32 sp7C;
    s32 sp78;
    s32 sp74;
    s16 temp_a0;
    s16 var_s0;
    s16 var_s2;
    s32 temp_s3;
    s32 temp_t4;
    s32 var_s1;
    s32 var_v0;

    temp_s3 = arg3 & 0xFFFF;
    if (D_807FC928 == 1) {
        modelSlotGetTransformVectors(arg1, &sp90, &sp8C, &sp88, &sp84, &sp80, &sp7C, &sp78, &sp74, 1);
    }
    temp_t4 = arg2->unk58;
    var_s2 = 0x91;
    switch (temp_t4) {
    case 3: var_s2 = 0x91; break;
    case 5: var_s2 = 0x15D; break;
    case 4: var_s2 = 0x15E; break;
    case 6:
    case 7: var_s2 = 0x15F; break;
    case 2: var_s2 = 0x160; break;
    }
    var_s0 = 0;
    var_s1 = 0;
    do {
        if (D_807FC928 == 1) {
            temp_a0 = modelSlotAppend(var_s2, sp90, sp8C, sp88, 0.0f, 0);
            var_v0 = temp_s3 == 0x11;
            func_806F50C8(temp_a0, var_s2, var_s0, var_v0, 0, 1);
        } else {
            var_v0 = temp_s3 == 0x11;
            func_806F54E0(arg0, var_s2, (u8) var_v0);
        }
        var_s1++;
        var_s0 += 3;
    } while (var_s1 != 5);
}

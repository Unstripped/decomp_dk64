// func_806F46B0 (src/global/F93B0.c): stage 3: matched loop blocks and instruction count; limit constant is folded and register allocation remains divergent
typedef struct {
    s16 map;
    s8 character;
    u8 pad3;
    s16 value;
} F9N3_MapHeight;

extern s32 D_8076A0A8;
extern F9N3_MapHeight D_80753EA0[];

f32 func_806F46B0(s16 arg0) {
    s16 var_v1;
    s32 temp_v0;
    s32 temp_a1;
    s8 temp_a3;
    F9N3_MapHeight *temp_a0;

    temp_v0 = 13;
    temp_a1 = D_8076A0A8;
    var_v1 = 0;
loop_1:
    temp_a0 = &D_80753EA0[var_v1];
    if ((temp_a1 == temp_a0->map) && ((temp_a3 = temp_a0->character, (arg0 == temp_a3)) || (temp_a3 == -1))) {
        return temp_a0->value;
    }
    var_v1 += 1;
    if (var_v1 < temp_v0) {
        goto loop_1;
    }
    return 20000.0f;
}

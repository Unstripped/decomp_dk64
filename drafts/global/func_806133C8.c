// func_806133C8 (src/global/17B90.c): stage 4; candidate identifies the FD command rewrite and allocation call. Remaining difference: loop-load and callee-save register scheduling.
typedef struct { u32 unk0; u32 unk4; } P17c3Command;
s32 func_8066B0F8(s32, s32, s32, s32);

void func_806133C8(P17c3Command *arg0, P17c3Command *arg1) {
    P17c3Command *var_s0;
    P17c3Command *var_s2;
    s32 temp_v0;

    var_s0 = arg0;
    var_s2 = arg1;
    if (var_s0 != var_s2) {
        temp_v0 = var_s0->unk0;
        do {
            if ((temp_v0 >> 0x18) == 0xFD) {
                temp_v0 = var_s0->unk4;
                if (((u32)(temp_v0 * 0x10) >> 0x1C) == 0) {
                    var_s0->unk4 = func_8066B0F8(0x19, temp_v0, 0, 0);
                }
            }
            var_s0++;
            temp_v0 = var_s0->unk0;
        } while (var_s0 != var_s2);
    }
}

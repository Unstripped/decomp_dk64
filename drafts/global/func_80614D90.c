// func_80614D90 (src/global/19A00.c): stage 2: m2c behavioral starter; remaining command-table type and loop/call regalloc
// Stage 2: m2c behavioral starter; remaining diff: command-table type and loop/call regalloc.
extern ? D_80746BEC;
extern u8 *D_807F5AF0;
extern s32 D_807F5AF4;

void func_80614D90(void *arg0) {
    s32 temp_v0;
    void *temp_s2;

    temp_s2 = arg0->unk4;
    if (temp_s2->unk68 != 0) {
        D_807F5AF4 = 1;
        D_807F5AF0 = temp_s2->unk6C;
        if ((temp_s2->unk78 == 0) && (1 != 0)) {
loop_4:
            temp_v0 = *(&D_80746BEC + (*D_807F5AF0 * 4))(arg0);
            D_807F5AF4 = temp_v0;
            if (temp_s2->unk78 == 0) {
                if (temp_v0 != 0) {
                    goto loop_4;
                }
            }
        }
        temp_s2->unk6C = (u8 *)D_807F5AF0;
        if (temp_s2->unk70 != NULL) {
            D_807F5AF0 = temp_s2->unk74;
            temp_s2->unk70(arg0);
        }
    }
}

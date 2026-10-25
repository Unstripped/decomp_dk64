// func_8071509C (src/global/119370.c): Stage 1 m2c reconstruction: 2-D geometry setup; local views still need concretizing before a matching attempt.
void func_8071509C(void *arg0) {
    s32 var_a3;
    s32 var_t2;
    s32 var_t4;
    s32 var_t5;
    s32 var_v1;
    void *temp_a2;
    void *temp_a2_2;
    void *temp_v0;
    void *var_a2;

    temp_v0 = arg0->unk330;
    var_v1 = 0;
    if (arg0->unk36F == 0) {
        var_t2 = (s32) -(temp_v0->unk9 * temp_v0->unkE) / 2;
    } else {
        var_t2 = (s32) (temp_v0->unk9 * temp_v0->unkE) / 2;
    }
    var_t4 = 0;
    if ((s32) temp_v0->unk9 > 0) {
        do {
            var_a3 = (s32) -(temp_v0->unk8 * temp_v0->unkC) / 2;
            var_t5 = 0;
            if ((s32) temp_v0->unk8 > 0) {
                var_a2 = arg0 + (var_v1 * 0x10) + 0x28;
                do {
                    var_a2->unk0 = (s16) var_a3;
                    var_a2->unk2 = (s16) var_t2;
                    var_a2->unk4 = 0;
                    var_a2->unk8 = 0;
                    var_a2->unkA = 0;
                    var_a2->unk12 = (s16) var_t2;
                    var_a2->unk14 = 0;
                    var_a2->unk10 = (s16) (temp_v0->unkC + var_a3);
                    var_a2->unk1A = 0;
                    var_a2->unk20 = (s16) var_a3;
                    var_a2->unk18 = (s16) (temp_v0->unkC << 5);
                    temp_a2 = var_a2 + 0x20;
                    if (arg0->unk36F == 0) {
                        temp_a2->unk2 = (s16) (temp_v0->unkE + var_t2);
                    } else {
                        temp_a2->unk2 = (s16) (var_t2 - temp_v0->unkE);
                    }
                    temp_a2->unk4 = 0;
                    temp_a2->unk8 = 0;
                    temp_a2_2 = temp_a2 + 0x10;
                    temp_a2_2->unk-6 = (s16) (temp_v0->unkE << 5);
                    temp_a2->unk10 = (s16) (temp_v0->unkC + var_a3);
                    if (arg0->unk36F == 0) {
                        temp_a2_2->unk2 = (s16) (temp_v0->unkE + var_t2);
                    } else {
                        temp_a2_2->unk2 = (s16) (var_t2 - temp_v0->unkE);
                    }
                    temp_a2_2->unk4 = 0;
                    var_t5 += 1;
                    var_v1 = var_v1 + 2 + 1 + 1;
                    temp_a2_2->unk8 = (s16) (temp_v0->unkC << 5);
                    var_a2 = temp_a2_2 + 0x10;
                    var_a2->unk-6 = (s16) (temp_v0->unkE << 5);
                    var_a3 += temp_v0->unkC;
                } while (var_t5 < (s32) temp_v0->unk8);
            }
            var_t4 += 1;
            if (arg0->unk36F == 0) {
                var_t2 += temp_v0->unkE;
            } else {
                var_t2 -= temp_v0->unkE;
            }
        } while (var_t4 < (s32) temp_v0->unk9);
    }
}

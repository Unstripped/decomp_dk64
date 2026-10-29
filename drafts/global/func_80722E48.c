// func_80722E48 (src/global/127B00.c): Fx127A2: stage 4: frame/saved regs match; diff only s2/s3 swap (ptr vs const 10) and a0/v1 swap (cursor vs entry reload)
typedef struct PathPoint {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
} PathPoint;

extern PathPlayback *D_807FDBF8[];

void func_80722E48(s16 *arg0) {
    PathEntry **temp_s1;
    s16 *var_s2;
    PathPoint *var_a0;
    s16 temp_s5;
    s16 temp_s7;
    s16 var_s0;
    s16 var_s4;

    for (var_s4 = 0; var_s4 < 0x1A; var_s4++) {
        D_807FDB90[var_s4] = NULL;
    }
    temp_s7 = *arg0;
    var_s2 = arg0 + 1;
    var_s4 = 0;
    if (temp_s7 > 0) {
        do {
            temp_s5 = *var_s2;
            var_s2 += 1;
            temp_s1 = &D_807FDB90[temp_s5];
            *temp_s1 = func_80610FE8(8);
            (*temp_s1)->unk4 = *var_s2;
            var_s2 += 2;
            (*temp_s1)->unk0 = func_80610FE8(((*temp_s1)->unk4 + 1) * sizeof(PathPoint));
            var_s4 += 1;
            var_s0 = 0;
            var_a0 = (PathPoint *)var_s2;
            while (var_s0 < (*temp_s1)->unk4) {
                ((PathPoint *)(*temp_s1)->unk0)[var_s0] = *var_a0;
                var_s0 += 1;
                var_a0 += 1;
            }
            var_s2 = (s16 *)var_a0;
        } while (var_s4 < temp_s7);
    }
    for (var_s4 = 0; var_s4 < 0x20; var_s4++) {
        D_807FDBF8[var_s4] = NULL;
    }
}

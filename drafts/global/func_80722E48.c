// func_80722E48 (src/global/127B00.c): stage 4: exact 10-byte lhu/sh copy tail; frame and saved-register coloring remain
typedef struct PathEntry { u8 *unk0; s16 unk4; } PathEntry;
typedef struct PathPlayback PathPlayback;
typedef struct PathPoint { s16 unk0; s16 unk2; s16 unk4; s16 unk6; s16 unk8; } PathPoint;
extern PathEntry *D_807FDB90[];
extern PathPlayback *D_807FDBF8[];
void *func_80610FE8(s32);

void func_80722E48(s16 *arg0) {
    PathEntry **temp_s1;
    u8 *var_s2;
    PathPoint *var_a0;
    s16 temp_s5;
    s16 temp_s7;
    s16 var_s0;
    s16 var_s4;
    s16 var_s4_2;
    s32 var_s3;
    s32 temp_s8;

    var_s4 = 0;
    do {
        D_807FDB90[var_s4] = NULL;
        var_s4 += 1;
    } while (var_s4 < 0x1A);
    temp_s7 = *arg0;
    var_s2 = (u8 *)arg0 + 2;
    var_s4_2 = 0;
    temp_s8 = 0xA;
    if (temp_s7 > 0) {
        var_s3 = 0xA;
        do {
            temp_s5 = *(s16 *)var_s2;
            var_s2 += 2;
            temp_s1 = &D_807FDB90[temp_s5];
            *temp_s1 = func_80610FE8(8);
            (*temp_s1)->unk4 = *(s16 *)var_s2;
            var_s2 += 4;
            (*temp_s1)->unk0 = func_80610FE8(((*temp_s1)->unk4 + 1) * temp_s8);
            var_s4_2 += 1;
            var_s0 = 0;
            var_a0 = (PathPoint *)var_s2;
            while (var_s0 < (*temp_s1)->unk4) {
                *(PathPoint *)((*temp_s1)->unk0 + var_s0 * var_s3) = *var_a0;
                var_s0 += 1;
                var_a0 += 1;
            }
            var_s2 = (u8 *)var_a0;
        } while (var_s4_2 < temp_s7);
    }
    var_s4_2 = 0;
    do {
        D_807FDBF8[var_s4_2] = NULL;
        var_s4_2 += 1;
    } while (var_s4_2 < 0x20);
}

// func_80722E48 (src/global/127B00.c): stage 2: typed C compiles but differs in register allocation and aligned 12-byte point copy; target uses 10-byte unaligned LWL/LWR records
typedef struct Uc1Path { u8 *unk0; s16 unk4; } Uc1Path;
typedef struct Uc1Playback Uc1Playback;
typedef struct Uc1PackedPathPoint { s32 unk0; s32 unk4; u16 unk8; } Uc1PackedPathPoint;
extern Uc1Path *D_807FDB90[];
extern Uc1Playback *D_807FDBF8[];
void *func_80610FE8(s32);

void func_80722E48(s16 *arg0) {
    Uc1Path **temp_s1;
    Uc1PackedPathPoint *var_a0;
    s16 temp_s5;
    s16 temp_s7;
    s16 var_s0;
    s16 var_s4;
    s16 var_s4_2;

    var_s4 = 0;
    do {
        D_807FDB90[var_s4] = NULL;
        var_s4 += 1;
    } while (var_s4 < 0x1A);
    temp_s7 = *arg0;
    arg0 += 1;
    var_s4_2 = 0;
    if (temp_s7 > 0) {
        do {
            temp_s5 = *arg0;
            arg0 += 1;
            temp_s1 = &D_807FDB90[temp_s5];
            *temp_s1 = func_80610FE8(8);
            (*temp_s1)->unk4 = *arg0;
            arg0 += 2;
            (*temp_s1)->unk0 = func_80610FE8(((*temp_s1)->unk4 + 1) * 0xA);
            var_s4_2 += 1;
            var_s0 = 0;
            var_a0 = (Uc1PackedPathPoint *)arg0;
            while (var_s0 < (*temp_s1)->unk4) {
                ((Uc1PackedPathPoint *)(*temp_s1)->unk0)[var_s0] = *var_a0;
                var_s0 += 1;
                var_a0 += 1;
            }
            arg0 = (s16 *)var_a0;
        } while (var_s4_2 < temp_s7);
    }
    var_s4_2 = 0;
    do {
        D_807FDBF8[var_s4_2] = NULL;
        var_s4_2 += 1;
    } while (var_s4_2 < 0x20);
}

// func_806F5EB4 (src/global/F9450.c): stage 3; queue scan behavior recovered, but argument homes/copies and table-pointer setup remain different
typedef struct {
    s32 unk0;
    s32 unk4;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    s32 unk10;
} F9N5_QueueSlot;

extern F9N5_QueueSlot *D_80754240;

s32 func_806F5EB4(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 var_a0;
    s32 var_v1;
    F9N5_QueueSlot *var_a1;

    var_a0 = 0 * 0x10;
    var_v1 = 0;
    var_a1 = (F9N5_QueueSlot *) ((u8 *) D_80754240 + var_a0);
loop_1:
    var_a0 += 0x14;
    if ((var_a1->unk10 != 0) && (arg0 == var_a1->unk4) && (arg1 == var_a1->unk0)) {
        var_v1 = 1;
    }
    var_a1 = (F9N5_QueueSlot *) ((u8 *) var_a1 + 0x14);
    if ((var_a0 < 0x4B0) && (var_v1 == 0)) {
        goto loop_1;
    }
    return var_v1;
}

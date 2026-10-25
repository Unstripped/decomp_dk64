// func_806F5DF8 (src/global/F9450.c): stage 3: semantics and loop blocks recovered, but typed slot accesses change initial register choice, pointer CSE, and loop exit shape (target frame/s0 preserved)
typedef struct {
    s32 unk0;
    s32 unk4;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    s32 unk10;
} F9BQueueSlot;

extern u8 *D_80754240;

void func_806F5DF8(s32 arg0, s32 arg1, s16 arg2, s16 arg3, s16 arg4, s32 arg5) {
    s32 var_a0;
    s32 var_v0;
    F9BQueueSlot *temp_v1;

    var_v0 = 0;
    var_a0 = 0 * 0x10;
loop_1:
    temp_v1 = (F9BQueueSlot *) (D_80754240 + var_a0);
    if (temp_v1->unk10 == 0) {
        temp_v1->unk0 = arg1;
        var_v0 = 1;
        ((F9BQueueSlot *) (D_80754240 + var_a0))->unk4 = arg0;
        ((F9BQueueSlot *) (D_80754240 + var_a0))->unk8 = arg2;
        ((F9BQueueSlot *) (D_80754240 + var_a0))->unkA = arg3;
        ((F9BQueueSlot *) (D_80754240 + var_a0))->unkC = arg4;
        ((F9BQueueSlot *) (D_80754240 + var_a0))->unk10 = arg5;
    }
    var_a0 += 0x14;
    if ((var_a0 < 0x4B0) && (var_v0 == 0)) {
        goto loop_1;
    }
}

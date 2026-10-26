// func_80614B34 (src/global/17B90.c): stage 4: typed C has correct instruction count but frame is 0x48 versus target 0x30; remaining diff is local/register allocation and branch scheduling.
s32 animSetSegments(s32 *, s32 *);                  /* extern */
s32 *func_80614C38(s32, void *, void *);            /* extern */

s32 *func_80614B34(s32 *arg0, void *arg1) {
    s32 *sp24;
    s32 *sp20;
    s32 *temp_a1;
    s32 *temp_v0_3;
    s32 *temp_v0_4;
    s32 *var_a2;
    s32 temp_t2;
    s32 var_a0;
    s32 var_v1;
    void *temp_v0;
    void *temp_v0_2;
    void *var_s0;

    temp_v0 = arg1->unk4C;
    var_s0 = arg1->unk0;
    if (temp_v0 != NULL) {
        var_s0 = temp_v0;
    }
    temp_v0_2 = arg1->unk50;
    if (temp_v0_2 != NULL) {
        var_s0 = temp_v0_2;
    }
    temp_v0_3 = func_80614C38(animSetSegments(arg0, arg0), arg1, var_s0);
    sp24 = temp_v0_3;
    *temp_v0_3 = 0xDB060010;
    arg0 = temp_v0_3 + 8;
    temp_a1 = arg0;
    sp24->unk4 = osVirtualToPhysical(arg1->unk8);
    temp_a1->unk0 = 0xDB06000C;
    arg0 = temp_a1 + 8;
    sp20 = temp_a1;
    var_a2 = arg0;
    var_v1 = 0;
    temp_a1->unk4 = osVirtualToPhysical(var_s0->unk0);
    var_a0 = 0;
    if ((s32) var_s0->unk21 > 0) {
        do {
            temp_v0_4 = var_a2;
            temp_v0_4->unk0 = 0xDE000000;
            var_v1 += 1;
            var_a2 += 8;
            temp_t2 = *(var_s0->unk4 + var_a0);
            var_a0 += 4;
            temp_v0_4->unk4 = temp_t2;
        } while (var_v1 < (s32) var_s0->unk21);
    }
    return var_a2;
}

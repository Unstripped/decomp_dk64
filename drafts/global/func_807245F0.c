// func_807245F0 (src/global/1292F0.c): Stage 3: behavioral state view compiled; frame is 0xA0 versus target 0x78, and state-pointer layout/register allocation remains.
void *func_80610FE8(?);                             /* extern */
s32 pathExists(s32);                                 /* extern */
? func_80723CCC(s16, s32, f32, f32 *, f32 *, f32 *, f32 *); /* extern */
? func_80723F88(s16, s32, s32, s32, void *, void *); /* extern */
? func_80724154(s16, s32, s32, s32, void *, void *); /* extern */
s32 pathEntryCount(s16);                             /* extern */
f32 mathAngleBetweenPointsDeg(s32, s32, s32, s32);  /* extern */

void func_807245F0(void *arg0, u8 arg1) {
    s32 sp6C;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    u8 sp47;
    s32 sp40;
    f32 temp_fv0;
    f32 var_fv0;
    f64 temp_ft2;
    f64 temp_fv1;
    s16 temp_a0;
    s32 temp_a0_2;
    s32 temp_a1;
    s32 temp_v1_2;
    s32 var_a1;
    s32 var_v1;
    s8 temp_v1;
    void *temp_v0;
    void *temp_v0_2;
    void *var_s0;

    sp47 = 0;
    temp_v0 = arg0->unk118;
    var_v1 = 0;
    var_s0 = temp_v0;
    if (temp_v0 == NULL) {
        temp_v0_2 = func_80610FE8(0x14);
        temp_v1 = arg0->unkB0;
        arg0->unk118 = temp_v0_2;
        var_s0 = temp_v0_2;
        if ((temp_v1 != -1) && (pathExists(temp_v1 & 0xFF) != 0)) {
            var_s0->unk12 = (s16) arg0->unkB0;
        } else {
            var_s0->unk12 = -1;
        }
        var_s0->unkC = 0;
        var_v1 = 1;
    }
    sp40 = (s32) arg1;
    if ((arg1 != 0) || (var_s0->unkC == 0)) {
        temp_a0 = var_s0->unk12;
        if (temp_a0 == -1) {
            var_s0->unkC = 1U;
            var_s0->unk10 = 0;
            var_s0->unkE = 0;
            return;
        }
        if (var_v1 != 0) {
            func_80723F88(temp_a0, arg0->unk7C, arg0->unk80, arg0->unk84, var_s0 + 4, var_s0 + 8);
        } else {
            func_80724154(temp_a0, arg0->unk7C, arg0->unk80, arg0->unk84, var_s0 + 4, var_s0 + 8);
        }
        temp_fv0 = var_s0->unk8;
        temp_a1 = var_s0->unk4;
        sp68 = temp_fv0;
        sp6C = temp_a1;
        func_80723CCC(var_s0->unk12, temp_a1, temp_fv0, &sp64, &sp60, &sp5C);
        var_a1 = sp6C;
        var_fv0 = (f32) ((f64) sp68 + 0.4);
        temp_fv1 = (f64) var_fv0;
        if (temp_fv1 >= 1.0) {
            var_a1 += 1;
            var_fv0 = (f32) (temp_fv1 - 1.0);
        }
        func_80723CCC(0, (s32) var_s0->unk12, (bitwise f32) var_a1, (bitwise f32 *) var_fv0, &sp58, &sp54, &sp50);
        temp_ft2 = (f64) mathAngleBetweenPointsDeg((s32) sp64, (s32) sp5C, (s32) sp58, (s32) sp50) * 2048.0;
        var_s0->unk10 = 0x23;
        var_s0->unkE = (s16) (((0x1000 - (s32) (temp_ft2 / 3.1415927410125732)) + 0x800) & 0xFFF);
        temp_v1_2 = var_s0->unk4;
        temp_a0_2 = pathEntryCount(var_s0->unk12) - 1;
        if (temp_v1_2 >= temp_a0_2) {
            if (temp_a0_2 == temp_v1_2) {
                sp47 = 1;
            } else {
                sp47 = 1;
            }
            var_s0->unk10 = 0;
        }
        if ((sp47 != 0) && (sp40 == 0)) {
            var_s0->unkC = 1U;
        }
    }
}

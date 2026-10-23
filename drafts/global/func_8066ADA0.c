// func_8066ADA0 (src/global/699B0.c): starter m2c draft (unattempted)
? func_8060B140(s32, s32, s32 *, ?, s32, s32, s32); /* extern */
s32 func_80610FE8(?);                               /* extern */
s32 func_8066B0F8(?, s32, ?, ?);                    /* extern */
extern s32 D_8000DDCC;
extern u8 D_80748E18;
extern s32 D_807F9520;
extern ? D_807F9528;
extern ? D_807F95A8;
extern ? D_807F9628;
extern s32 D_807F9678;
extern s8 D_807F967C;
extern s8 D_807F967D;
extern s32 D_807F9680;
extern s32 D_807FB1A0;
extern s8 D_807FB220;
extern s8 D_807FB221;

void func_8066ADA0(void) {
    s32 sp40;
    ? *var_v0;
    ? *var_v0_2;
    ? *var_v1;
    s32 *var_s1;
    s32 temp_v0;
    s32 var_s0;
    u8 *var_s2;

    sp40 = 0x80;
    temp_v0 = func_80610FE8(0x80);
    D_807F9520 = temp_v0;
    func_8060B140(D_8000DDCC, temp_v0, &sp40, 0, 0, 0, 0);
    var_v0 = &D_807F95A8;
    var_v1 = &D_807F9528;
    do {
        var_v0 += 4;
        var_v1 += 4;
        var_v1->unk-4 = 0;
        var_v0->unk-4 = 0;
    } while ((u32) var_v0 < (u32) &D_807F9628);
    var_v0_2 = &D_807F9628;
    do {
        var_v0_2 += 4;
        var_v0_2->unk-4 = 0;
    } while ((u32) var_v0_2 < (u32) &D_807F9678);
    D_807F9680 = 0;
    D_807F967C = 0;
    D_807F9678 = 0;
    D_807F967D = 0;
    var_s1 = &D_807FB1A0;
    var_s2 = &D_80748E18;
    var_s0 = 0;
    do {
        if (*var_s2 != 0) {
            *var_s1 = func_8066B0F8(0x1A, var_s0, 1, 1);
        } else {
            *var_s1 = 0;
        }
        var_s0 += 1;
        var_s2 += 1;
        var_s1 += 4;
    } while (var_s0 != 0x20);
    D_807FB220 = 0;
    D_807FB221 = 0;
}

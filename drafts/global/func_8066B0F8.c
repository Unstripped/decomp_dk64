// func_8066B0F8 (src/global/699B0.c): starter m2c draft (unattempted)
? func_8060B140(u32, s32, s32 *, ?, s32, s32, s32); /* extern */
s32 func_80610FE8(s32, s32, s32 *);                 /* extern */
? func_8066AEE4(s32, s32);                          /* extern */
? func_8066B4AC(s32, u32, s32);                     /* extern */
? func_8066B4D4(s32, u32, u32 *, s32 *);            /* extern */
u32 func_8066B5C8(s32, u32);                        /* extern */
? func_8066B5F4();                                  /* extern */
? func_8066B8C8(u32, s32, u32, u32);                /* extern */
? func_80732354(?, ?, ?, ?);                        /* extern */
s32 heapAllocFromPool(s32, s32);                    /* extern */
extern ? D_80748E18;
extern OSMesgQueue D_807656D0;
extern s32 D_807F9678;
extern s8 D_807F967C;
extern s32 D_807F9680;
extern ? D_807F9688;
extern ? D_807FA8A0;
extern ? D_807FB1A0;

u32 func_8066B0F8(s32 arg0, u32 arg1, u8 arg2, s32 arg3) {
    u32 sp50;
    s32 sp4C;
    s32 sp40;
    u8 *sp3C;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 var_a1;
    s32 var_v0;
    u32 temp_v0;
    u32 var_s0;
    u8 *temp_t0;
    u8 *var_t0;
    u8 temp_a0;
    void **var_v1;

    func_8066B5F4();
    if (!(arg3 & 0xFF)) {
        if ((arg1 >= 0x80000000U) && (arg1 < 0xA0000000U)) {
            func_8066B8C8(arg1, arg0, 0U, arg1);
            D_807F967C = 0;
            D_807F9678 = 0;
            return arg1;
        }
        temp_v0 = func_8066B5C8(arg0, arg1);
        var_s0 = temp_v0;
        if (temp_v0 != 0) {
            func_8066B8C8(temp_v0, arg0, arg1);
            D_807F967C = 0;
            D_807F9678 = 0;
            goto block_24;
        }
        goto block_6;
    }
block_6:
    func_8066B4D4(arg0, arg1, &sp50, &sp4C);
    if (sp4C == 0) {
        D_807F967C = 0;
        D_807F9678 = 0;
        return 0U;
    }
    temp_t0 = arg0 + &D_80748E18;
    var_a1 = sp4C;
    if (*temp_t0 != 0) {
        var_a1 = *(*(&D_807FB1A0 + (arg0 * 4)) + (arg1 * 4));
    }
    if (D_807F9678 == 0) {
        sp3C = temp_t0;
        var_v0 = func_80610FE8(var_a1, var_a1);
        var_t0 = temp_t0;
    } else {
        sp3C = temp_t0;
        var_v0 = heapAllocFromPool(D_807F9678, var_a1);
        var_t0 = temp_t0;
    }
    var_s0 = (u32) var_v0;
    if (arg2 != 0) {
        if (*var_t0 != 0) {
            temp_v0_2 = func_80610FE8(sp4C, (s32) var_s0, &sp4C);
            sp40 = temp_v0_2;
            func_8060B140(sp50, temp_v0_2, &sp4C, 0, 0, 0, 0);
            func_8066AEE4(sp40, (s32) var_s0);
        } else {
            func_8060B140(sp50, (s32) var_s0, &sp4C, 0, 0, 0, 0);
        }
    } else {
        temp_v0_3 = D_807F9680;
        if (temp_v0_3 == 0xC0) {
            sp3C = var_t0;
            func_80732354(6, 0, 0, 0);
        }
        temp_a0 = *var_t0;
        var_v1 = (temp_v0_3 * 0xC) + &D_807FA8A0;
        var_v1->unk8 = temp_a0;
        if (temp_a0 != 0) {
            var_v1 = (D_807F9680 * 0xC) + &D_807FA8A0;
            var_v1->unk0 = func_80610FE8(sp4C);
            var_v1->unk4 = var_s0;
        } else {
            var_v1->unk4 = var_s0;
            var_v1->unk0 = var_s0;
        }
        osInvalDCache(*var_v1, sp4C);
        osPiStartDma((D_807F9680 * 0x18) + &D_807F9688, 0, 0, sp50, *(&D_807FA8A0 + (D_807F9680 * 0xC)), (u32) sp4C, &D_807656D0);
        D_807F9680 += 1;
    }
    func_8066B4AC(arg0, arg1, (s32) var_s0);
    func_8066B8C8(var_s0, arg0, arg1);
    D_807F967C = 0;
    D_807F9678 = 0;
block_24:
    return var_s0;
}

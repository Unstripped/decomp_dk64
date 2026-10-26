// func_8060B140 (src/global/FE40.c): stage 1: m2c starter; not yet type-resolved
? func_80002790(void **, void **, void *, u8);      /* extern */
void *func_80610FE8(s32);                           /* extern */
? gunzip(void **, void **, void *);                 /* extern */
? heapFree(void *);                                 /* extern */
extern s8 D_80746834;
extern OSMesgQueue D_807655F0;
extern OSIoMesg D_807ECE00;
extern void *D_807ECE18;

void func_8060B140(u32 arg0, void *arg1, s32 *arg2, u8 arg3, u8 arg4, u8 arg5, void *arg6) {
    void *sp5C;
    void *sp58;
    void *sp50;
    s32 var_v1;
    u32 temp_v0_2;
    u32 var_a0;
    u32 var_s0;
    u32 var_s4;
    void *temp_v0;
    void *var_s1;

    var_s4 = arg0;
    sp58 = arg1;
    if ((arg3 != 0) || (arg4 != 0)) {
        if (arg3 & 0x80) {
            sp5C = arg6;
            arg6 += 0x3800;
        } else if (arg6 != NULL) {
            sp5C = (void *)0x80024000;
        } else {
            temp_v0 = func_80610FE8(*arg2);
            sp50 = temp_v0;
            sp5C = temp_v0;
        }
    } else {
        sp5C = arg1;
    }
    osInvalDCache(sp5C, *arg2);
    var_v1 = *arg2;
    var_s0 = 0;
    var_s1 = sp5C;
    var_a0 = (u32) var_v1 >> 0xE;
    if (var_a0 != 0) {
        do {
            osPiStartDma(&D_807ECE00, 0, 0, var_s4, var_s1, 0x4000U, &D_807655F0);
            D_80746834 = 4;
            osRecvMesg(&D_807655F0, NULL, 1);
            D_80746834 = 0;
            var_s0 += 1;
            var_v1 = *arg2;
            var_s4 += 0x4000;
            var_s1 += 0x4000;
            var_a0 = (u32) var_v1 >> 0xE;
        } while (var_s0 < var_a0);
    }
    temp_v0_2 = var_v1 - (var_a0 << 0xE);
    if (temp_v0_2 != 0) {
        osPiStartDma(&D_807ECE00, 0, 0, var_s4, var_s1, temp_v0_2, &D_807655F0);
        D_80746834 = 5;
        osRecvMesg(&D_807655F0, NULL, 1);
        D_80746834 = 0;
    }
    D_807ECE18 = arg6;
    if ((arg6 == NULL) && ((arg5 == 1) || (arg5 == 2))) {
        D_807ECE18 = func_80610FE8(0x4000);
    }
    switch (arg5) {                                 /* irregular */
    case 1:
        if (arg3 != 0) {
            gunzip(&sp5C, &arg1, D_807ECE18);
        }
        if (arg4 != 0) {
            gunzip(&sp5C, &arg1, D_807ECE18);
        }
        break;
    case 2:
        if (arg3 != 0) {
            func_80002790(&sp5C, &arg1, D_807ECE18, arg3);
        }
        if (arg4 != 0) {
            func_80002790(&sp5C, &arg1, D_807ECE18, arg4);
        }
        break;
    }
    if ((arg6 == NULL) && ((arg5 == 1) || (arg5 == 2))) {
        heapFree(D_807ECE18);
    }
    if ((arg3 != 0) || (arg4 != 0)) {
        *arg2 = arg1 - sp58;
        if (arg6 == NULL) {
            heapFree(sp50);
        }
    }
}

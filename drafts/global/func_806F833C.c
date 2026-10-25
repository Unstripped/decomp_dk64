// func_806F833C (src/global/FCCD0.c): Compiling stage-3 draft in private FCCD0.c: 483-insn switch/list initializer; 13504 vs 13488 text bytes after slot struct, f32 callee prototype, stack-local and base+offset restructuring; frame remains 0x90 vs target 0xA0.
u8 func_805FF030(u8, ?);                            /* extern */
s32 func_80610FE8(s32);                             /* extern */
s32 func_806C8DE0(s32);                             /* extern */
void *func_806F7FD0(u8);                            /* extern */
? func_806F8004(?, ?, void *, void *, void *);      /* extern */
? func_806F8278(u8);                                /* extern */
s16 func_806F8EDC(?, s32);                          /* extern */
? func_806FB370(?, ?, ?);                           /* extern */
s32 func_807142D8();                                /* extern */
? heapClearBlock(s32);                              /* extern */
extern s16 D_80744544;
extern u16 D_80750AC4;
extern u16 D_80750AC8;
extern s32 D_80754280;
extern s32 D_80754284;
extern s32 D_8076A0A8;
extern u8 D_8076A0AB;
extern u8 D_807FC928;
extern ? D_807FC950;

void func_806F833C(s32 arg0) {
    u32 sp9C;
    s32 sp98;
    s16 sp96;
    u8 sp8F;
    void *sp84;
    s32 sp78;
    ? *var_fp;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_s4;
    s8 var_s7;
    u16 *temp_v0_18;
    u32 temp_t2;
    u8 temp_v1;
    void *temp_s6;
    void *temp_v0_10;
    void *temp_v0_11;
    void *temp_v0_12;
    void *temp_v0_13;
    void *temp_v0_14;
    void *temp_v0_15;
    void *temp_v0_16;
    void *temp_v0_17;
    void *temp_v0_3;
    void *temp_v0_4;
    void *temp_v0_5;
    void *temp_v0_6;
    void *temp_v0_7;
    void *temp_v0_8;
    void *temp_v0_9;
    void *var_s0;

    sp96 = D_80744544;
    temp_v1 = D_807FC928;
    sp8F = func_805FF030(D_8076A0AB, 1);
    if ((s32) temp_v1 >= 2) {
        sp96 = 0;
    }
    if (arg0 != 0) {
        temp_v0 = func_80610FE8(temp_v1 * 0x2D0);
        D_80754280 = temp_v0;
        heapClearBlock(temp_v0);
        D_80754284 = 0;
    }
    if ((s32) temp_v1 > 0) {
        var_fp = &D_807FC950;
        sp98 = 0;
        do {
            sp84 = var_fp + (func_806C8DE0(sp98) * 0x5E);
            sp78 = (s32) unksp9B;
            temp_v0_3 = func_806F7FD0(unksp9B);
            temp_s6 = temp_v0_3;
            sp9C = 0;
            var_s4 = 0;
            var_s0 = temp_v0_3;
loop_7:
            var_s7 = 0;
            if (arg0 != 0) {
                var_s0->unk20 = 0;
                var_s0->unk7 = 0;
                var_s0->unk24 = 0;
                var_s0->unk6 = 0;
                var_s0->unk28 = 0;
                var_s0->unk2C = 0;
            }
            if (func_807142D8() != 0) {
                var_s0->unk2C = 1;
            }
            switch (sp9C) {
            case 0:
                temp_v0_4 = var_s4 + temp_s6;
                var_s0->unk0 = (u16 *) (sp84 + (sp8F * 2) + 0xA);
                var_s0->unkC = 0x26;
                var_s0->unk8 = 0x1E;
                func_806F8004(0x41780000, 0x41D00000, temp_v0_4 + 0x10, temp_v0_4 + 0x14, temp_v0_4 + 0x18);
                break;
            case 13:
                temp_v0_5 = var_s4 + temp_s6;
                var_s0->unk0 = NULL;
                var_s0->unkC = 0x26;
                var_s0->unk8 = 0x122;
                func_806F8004(0xC0B00000, 0xC1D00000, temp_v0_5 + 0x10, temp_v0_5 + 0x14, temp_v0_5 + 0x18);
                break;
            case 8:
                temp_v0_6 = var_s4 + temp_s6;
                var_s0->unk0 = (u16 *) (sp84 + (sp8F * 2) + 0x42);
                var_s0->unkC = 0x48;
                var_s0->unk8 = 0x1E;
                func_806F8004(0x3FC00000, 0x41D00000, temp_v0_6 + 0x10, temp_v0_6 + 0x14, temp_v0_6 + 0x18);
                break;
            case 12:
                temp_v0_7 = var_s4 + temp_s6;
                var_s0->unk0 = NULL;
                var_s0->unkC = 0xD0;
                var_s0->unk8 = 0xC2;
                func_806F8004(0xC1D40000, 0x41D00000, temp_v0_7 + 0x10, temp_v0_7 + 0x14, temp_v0_7 + 0x18);
                break;
            case 10:
                temp_v0_8 = var_s4 + temp_s6;
                var_s0->unk0 = NULL;
                var_s0->unkC = 0xD0;
                var_s0->unk8 = 0x52;
                func_806F8004(0xC1D40000, 0x41D00000, temp_v0_8 + 0x10, temp_v0_8 + 0x14, temp_v0_8 + 0x18);
                break;
            case 9:
                var_s0->unk0 = NULL;
                var_s0->unkC = 0xD0;
                var_s0->unk8 = 0x7A;
                break;
            case 5:
                temp_v0_9 = var_s4 + temp_s6;
                if (sp96 & 0x20) {
                    var_fp->unk2F6 = func_806F8EDC(5, sp98);
                    var_s7 = 1;
                }
                var_s0->unk0 = (u16 *) (var_fp + 0x2F6);
                var_s0->unkC = 0x8C;
                var_s0->unk8 = 0x122;
                func_806F8004(0xC0B00000, 0xC1980000, temp_v0_9 + 0x10, temp_v0_9 + 0x14, temp_v0_9 + 0x18);
                break;
            case 2:
                temp_v0_10 = var_s4 + temp_s6;
                var_s0->unk0 = (u16 *) (var_fp + 0x2F0);
                var_s0->unkC = 0x48;
                var_s0->unk8 = 0x122;
                func_806F8004(0x41080000, 0xC1980000, temp_v0_10 + 0x10, temp_v0_10 + 0x14, temp_v0_10 + 0x18);
                break;
            case 3:
                temp_v0_11 = var_s4 + temp_s6;
                if (sp96 & 4) {
                    var_fp->unk2F2 = func_806F8EDC(3, sp98);
                    var_s7 = 1;
                }
                var_s0->unk0 = (u16 *) (var_fp + 0x2F2);
                var_s0->unkC = 0x48;
                var_s0->unk8 = 0x122;
                func_806F8004(0x41080000, 0xC1980000, temp_v0_11 + 0x10, temp_v0_11 + 0x14, temp_v0_11 + 0x18);
                break;
            case 4:
                temp_v0_12 = var_s4 + temp_s6;
                if (sp96 & 8) {
                    var_fp->unk2F4 = func_806F8EDC(4, sp98);
                    var_s7 = 1;
                }
                var_s0->unk0 = (u16 *) (var_fp + 0x2F4);
                var_s0->unkC = 0x6A;
                var_s0->unk8 = 0x122;
                func_806F8004(0x3FC00000, 0xC1980000, temp_v0_12 + 0x10, temp_v0_12 + 0x14, temp_v0_12 + 0x18);
                break;
            case 6:
                temp_v0_13 = var_s4 + temp_s6;
                if (sp96 & 0x10) {
                    var_fp->unk2F8 = func_806F8EDC(6, sp98);
                    var_s7 = 1;
                }
                var_s0->unk0 = (u16 *) (var_fp + 0x2F8);
                var_s0->unkC = 0xD0;
                var_s0->unk8 = 0x122;
                func_806F8004(0xC19C0000, 0xC1980000, temp_v0_13 + 0x10, temp_v0_13 + 0x14, temp_v0_13 + 0x18);
                break;
            case 11:
                temp_v0_14 = var_s4 + temp_s6;
                var_s0->unk0 = &D_80750AC4;
                var_s0->unkC = 0x26;
                var_s0->unk8 = 0x122;
                func_806F8004(0x41840000, 0xC1980000, temp_v0_14 + 0x10, temp_v0_14 + 0x14, temp_v0_14 + 0x18);
                break;
            case 1:
                temp_v0_15 = var_s4 + temp_s6;
                if (sp96 & 2) {
                    var_s7 = 1;
                    sp84->unk6 = func_806F8EDC(1, sp98);
                }
                var_s0->unk0 = (u16 *) (sp84 + 6);
                var_s0->unkC = 0x26;
                var_s0->unk8 = 0x122;
                func_806F8004(0x41840000, 0xC1980000, temp_v0_15 + 0x10, temp_v0_15 + 0x14, temp_v0_15 + 0x18);
                break;
            case 7:
                temp_v0_16 = var_s4 + temp_s6;
                if (sp96 & 0x40) {
                    var_s7 = 1;
                    sp84->unk8 = func_806F8EDC(7, sp98);
                }
                var_s0->unk0 = (u16 *) (sp84 + 8);
                var_s0->unkC = 0xAE;
                var_s0->unk8 = 0x122;
                func_806F8004(0xC1480000, 0xC1980000, temp_v0_16 + 0x10, temp_v0_16 + 0x14, temp_v0_16 + 0x18);
                break;
            case 14:
                temp_v0_17 = var_s4 + temp_s6;
                var_s0->unk0 = &D_80750AC8;
                var_s0->unkC = 0x26;
                var_s0->unk8 = 0x1E;
                func_806F8004(0x41780000, 0x41D00000, temp_v0_17 + 0x10, temp_v0_17 + 0x14, temp_v0_17 + 0x18);
                break;
            }
            var_s0->unk2D = var_s7;
            if (var_s7 & 0xFF) {
                var_s0->unk2C = 1;
            }
            temp_v0_18 = var_s0->unk0;
            var_s4 += 0x30;
            if (temp_v0_18 != NULL) {
                var_s0->unk4 = (u16) *temp_v0_18;
            }
            var_s0 += 0x30;
            temp_t2 = sp9C + 1;
            sp9C = temp_t2;
            if (temp_t2 != 0xF) {
                goto loop_7;
            }
            func_806F8278(unksp7B);
            temp_v0_2 = sp98 + 1;
            sp98 = temp_v0_2;
            var_fp += 0x306;
        } while (temp_v0_2 < (s32) D_807FC928);
    }
    if ((D_8076A0A8 == 0x11) || (D_8076A0A8 == 0x52)) {
        func_806FB370(5, 0, 1);
    }
}

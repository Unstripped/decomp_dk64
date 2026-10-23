// func_80671F54 (src/global/70FD0.c): Exact size 120 insns, all stack saves/epilogue match; regalloc off: var_s1 in s5 vs s1, temp_ft0..3 in s1..s4 vs s2..s5
typedef struct M70I_Sub28 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    u8 pad10[5];
    u8 unk15;
    u8 pad16[2];
    s32 unk18;
    s32 unk1C;
} M70I_Sub28;

typedef struct M70I_Struct7C {
    u8 pad0[0x70];
    u8 unk70;
} M70I_Struct7C;

typedef struct M70I_Entry {
    u8 pad0[0x28];
    M70I_Sub28 sub28;
    u8 pad48[0x24];
    u8 unk6C;
    u8 pad6D[0xF];
    M70I_Struct7C *unk7C;
    u8 pad80[0x10];
} M70I_Entry;

s32 func_80673708(s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_80674ADC(s32, s32, s32, s32, s32, s32, s32, s32);
extern s32 D_80747D70;
extern M70I_Entry *D_807F6000;
extern s32 D_807FB53C;
extern u8 D_807FB5FD;

s32 func_80671F54(f32 arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4, s32 arg5) {
    s32 var_s1;
    s32 temp_ft0;
    s32 temp_ft1;
    s32 temp_ft2;
    s32 temp_ft3;
    s32 var_fp;
    s32 var_s6;
    void *temp_s0;
    M70I_Struct7C *temp_v0;
    s32 val;

    var_fp = 0;
    D_807FB5FD = 0;
    var_s6 = 0;
    if (D_80747D70 > 0) {
        var_s1 = 0;
        do {
            temp_s0 = (void *)((u8 *)D_807F6000 + var_s1);
            val = *(s32 *)((u8 *)temp_s0 + 0x40);
            temp_s0 = (void *)((u8 *)temp_s0 + 0x28);
            if (val != 0 && (D_807FB53C != 0xBC || (*(u8 *)((u8 *)D_807F6000 + var_s1 + 0x6C) & 2))) {
                temp_ft0 = arg0;
                temp_ft1 = arg1;
                temp_ft2 = arg2;
                temp_ft3 = arg3;
                if (func_80674ADC(temp_ft0, temp_ft1, temp_ft2, temp_ft3,
                                  *(s32 *)((u8 *)temp_s0 + 0x0),
                                  *(s32 *)((u8 *)temp_s0 + 0x4),
                                  *(s32 *)((u8 *)temp_s0 + 0x8),
                                  *(s32 *)((u8 *)temp_s0 + 0xC)) != 0 &&
                    (*(u8 *)((u8 *)temp_s0 + 0x15) & 1) &&
                    ((temp_v0 = *(M70I_Struct7C **)((u8 *)D_807F6000 + var_s1 + 0x7C)) == NULL || temp_v0->unk70 != 0)) {
                    var_fp = (var_fp | func_80673708(temp_ft0, temp_ft1, temp_ft2, temp_ft3,
                                                     *(s32 *)((u8 *)temp_s0 + 0x18),
                                                     *(s32 *)((u8 *)temp_s0 + 0x1C),
                                                     arg4, arg5)) & 0xFF;
                }
            }
            var_s6++;
            var_s1 += 0x90;
        } while (var_s6 < D_80747D70);
    }
    return var_fp;
}

// func_806175C4 (src/global/19A00.c): text-identical, reloc only: all 107 insns match (CURRENT 0); .rodata bytes identical (0x68: 255.0, 0x70: 0.4381361, 0x78: 55.0, 0x80: 255.0, 0x88: 0.3f); asm has named labels D_807573D8 etc while C uses .rodata+off; / 255 vs 255.0 ternary
typedef struct RvG2_State75C4 {
    u8 pad0[0x34];
    f32 unk34;
} RvG2_State75C4;

void sfxPlayAtPositionPooled(f32, f32, f32, s16, s32, s32, s32, s32, f32, s32);

s32 func_806175C4(Actor *arg0) {
    s16 sp46;
    u8 sp45;
    u8 sp44;
    u8 sp43;
    u8 sp42;
    f32 var_fv1;
    f64 val;

    D_807F5AF0++;
    scriptReadU16((u8 *)&sp46);
    scriptReadU8(&sp43);
    scriptReadU8(&sp42);
    scriptReadU8(&sp45);
    scriptReadU8(&sp44);
    val = (((((f64)((RvG2_State75C4 *)arg0->unk4)->unk34 / 0.4381361) * 200.0) + 55.0) * (f64)sp43) / 255;
    var_fv1 = (val > 255.0) ? 255.0 : val;
    sfxPlayAtPositionPooled(arg0->unk7C, arg0->unk80, arg0->unk84, sp46, (u32)var_fv1, sp42, sp45, sp44, 0.3f, 0);
    return 1;
}

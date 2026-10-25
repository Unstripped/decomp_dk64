// func_806E65BC (src/global/E4090.c): stage 6: only diff vs target is scratch temp numbering after the ang sub (subu t5 vs t6 chain) in then-arm. Tricks: s32 ang loaded at top + 'ang ^= 0' (dead use) raises ang priority so regs v0=ang v1=actor a0=idx a1=ptr match; no s8 temp var (sll/sra); var_a1 = x; var_a1 &= 0xFFF split gives scratch product temps; sign as inline ternary on RHS of table*sign (complex operand ordering); quotient assigned to var_a1 before f64 part. Declaration order ang,var_a1,var_t1 puts sp slot at 24.
typedef struct G27Actor {
    /* 0x000 */ u8 pad0[0xE4];
    /* 0x0E4 */ s16 unkE4;
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ s16 unkE8;
    /* 0x0EA */ u8 padEA[0x155 - 0xEA];
    /* 0x155 */ u8 unk155;
} G27Actor;

#define G27_A ((G27Actor *)D_807FBB40)

extern s16 D_80753B44[];
extern s16 D_80753B54[];
extern s16 D_80753B64[];

void func_806E65BC(void) {
    s32 ang;
    s16 var_a1;
    s16 var_t1;

    ang = G27_A->unkE6;
    var_t1 = 0x10;
    if (D_8074E77C[D_807FC929] == 7) {
        var_t1 = 0x19;
    }
    if (D_807FD610[D_807FC929].unk30 != 0) {
        ang ^= 0;
        G27_A->unkE6 = (ang - (D_807FD610[D_807FC929].unk2E / 2)) & 0xFFF;
        var_a1 = D_80753B54[D_807FD584] * ((D_807FD610[D_807FC929].unk2E >= 0) ? 1 : -1);
        var_a1 &= 0xFFF;
    } else {
        var_a1 = 0;
    }
    func_806DF494(&G27_A->unkE4, var_a1, 0x10);
    if (D_807FD610[D_807FC929].unk2F != 0) {
        var_a1 = (D_80753B44[D_807FD584] * D_807FD610[D_807FC929].unk2F) / 70;
        var_a1 = var_a1 & 0xFFF;
        func_806DF494(&G27_A->unkE8, var_a1, (s16)(s32)((((f64)D_807FD610[D_807FC929].unk2F * 0.125) > 0.0 ? ((f64)D_807FD610[D_807FC929].unk2F * 0.125) : -((f64)D_807FD610[D_807FC929].unk2F * 0.125)) + (f64)var_t1));
        return;
    }
    func_806DF494(&G27_A->unkE8, D_80753B64[D_807FD584], 0x10);
}

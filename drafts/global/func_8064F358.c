// func_8064F358 (src/global/478F0.c): stage 5: same frame/callee-saved, only temp regs: target addu t6,t4(p+sel*0x5E),t5(idx*2) vs mine addu t5,t4(idx*2),v1(sum): 6 lines reg/operand-order. Tried q=p/q+= forms (needed for p in t0), u32/s16 idx, split locals, deadsweep (no gain), permuter 240s -j2 (no <35). D_8074E77C must be 'extern u8 D_8074E77C' scalar (file park declares it) indexed (&D_8074E77C)[D_807FC929].
extern u8 D_8076A0AB;
u8 func_805FF030(u8, u8);
extern u8 D_807FC929;
extern u8 D_807FC950[];
extern u8 D_8074E77C;

u8 func_8064F358(CsState *cs, s16 csId, s16 b, s16 c) {
    u8 *p = D_807FC950 + D_807FC929 * 0x306;
    s32 idx = func_805FF030(D_8076A0AB, 0);
    u8 *q = p;

    q += (&D_8074E77C)[D_807FC929] * 0x5E;
    return *(u16 *)(q + idx * 2 + 0xA) > 0;
}

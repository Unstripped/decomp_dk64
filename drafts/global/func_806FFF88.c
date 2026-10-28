// func_806FFF88 (src/global/103AB0.c): func_806FFF88 (src/global/103AB0.c): Stage 6: exact opcode sequence/frame/s-regs; only 3 scratch t-reg diffs left (loop temps t4,t5,t7 vs expected t5,t6,t2). Needs 'D_80744490 * 7 << 4' spelling; 'return;' after func_806FFF5C() (void callee, v0 untouched). deadsweep no gain.
extern void *D_80744470[];
s32 func_80610FE8(s32);
s16 *func_806FFEAC(s16 *, s32);

s32 func_806FFF88(void) {
    s32 sp34;
    s16 var_s0;
    s16 var_s3;
    s32 var_s1;
    s32 var_s2;

    if (D_807FBB40->unk58 == 0xD9) {
        func_806FFF5C();
        return;
    }
    sp34 = func_80610FE8(0xA000);
    var_s1 = sp34;
    var_s2 = (s32)D_80744470[D_807444FC] + (D_80744490 * 7 << 4) + 0xA0;
    var_s3 = 0;
    do {
        var_s0 = 0;
        do {
            var_s1 = (s32)func_806FFEAC((s16 *)var_s1, (var_s0 << 6) + var_s2);
            var_s0++;
        } while (var_s0 < 5);
        var_s3++;
        var_s2 += D_80744490 << 7;
    } while (var_s3 < 2);
    return sp34;
}

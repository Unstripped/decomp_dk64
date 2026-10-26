// func_80613FB0 (src/global/17B90.c): stage 1: m2c starter recovered from local asm; requires typed controller/table views and C compile
? func_80614014(?, u16, ?, s32);                    /* extern */
extern s32 D_807FBB58;

void func_80613FB0(void *arg0, s32 arg1, ? arg2, s32 arg3) {
    func_80614014(arg2, *(D_807FBB58 + (((((arg1 * 7) + arg0->unk58) - 2) & 0xFFFF) * 2)), arg2, arg3 & 0xFF);
}

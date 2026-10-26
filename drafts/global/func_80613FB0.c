// func_80613FB0 (src/global/17B90.c): stage 4; exact instruction count; remaining diff is integer register allocation and argument preparation scheduling
typedef struct { u8 pad[0x58]; s32 value; } Controller;
extern u16 *D_807FBB58;
void func_80614014(Controller *, u16, f32, u8);
void func_80613FB0(Controller *arg0, s32 arg1, f32 arg2, s32 arg3) {
    func_80614014(arg0, D_807FBB58[((arg1 * 7 + arg0->value - 2) & 0xFFFF)], arg2, arg3 & 0xFF);
}

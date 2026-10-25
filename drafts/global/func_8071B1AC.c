// func_8071B1AC (src/global/11BC10.c): Stage 5: core field updates and calls match, but C literal lowering shares one 0.35f and emits .175 double rather than target three distinct float rodata constants.
typedef struct {
    u8 pad0[0x340];
    f32 unk340;
    f32 unk344;
    f32 unk348;
    u8 pad34C[0x12];
} Ub4ActorView;

void func_8071B1AC(Ub4ActorView *arg0, s8 *arg1) {
    arg0->unk344 = (f32)((f64)arg0->unk344 - ((f64)0.35f * 0.5));
    arg0->unk340 = (f32)(arg0->unk340 + (0.35f * func_80612794(*((s16 *)((u8 *)arg0 + 0x35E)))));
    arg0->unk348 = (f32)(arg0->unk348 + (0.35f * func_80612790(*((s16 *)((u8 *)arg0 + 0x35E)))));
}

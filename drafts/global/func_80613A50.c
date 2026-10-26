// func_80613A50 (src/global/17B90.c): stage 4; exact instruction count; remaining diff is FP/integer register allocation and multiply scheduling
typedef struct { u8 pad[0x14]; f32 a; f32 b; } State;
typedef struct { u8 pad[4]; f32 scale; u8 pad2[0xC]; f32 a; f32 b; } Scale;
typedef struct { State *state; u8 pad[4]; Scale *scale; } Holder;
typedef struct { u8 pad[4]; Holder *holder; } Controller;
void func_80614644(Controller *, State *, f32, s16);
void func_80613A50(Controller *arg0, s8 arg1) {
    s16 count = (s32)((arg0->holder->state->b - arg0->holder->state->a) + 1.0f);
    s16 span = (s32)((arg0->holder->scale->b - arg0->holder->scale->a) + 1.0f);
    func_80614644(arg0, arg0->holder->state, ((arg0->holder->scale->scale * (f32)count) / (f32)span) + (f32)arg1, count);
}

// func_80616E08 (src/global/19A00.c): stage 2: m2c behavioural reconstruction; requires exact D_807FD580 player-index field/view and local allocation, switch jump table and FP conversion tuning.
typedef struct P19ePlayerState { u8 pad0[0x2C0]; u8 unk2C0; } P19ePlayerState;
extern P19ePlayerState *D_807FC924;
void func_806086CC(f32, f32, f32, s16, s32, s32, s32, s32, f32, s32);
s16 func_8060A7C0(s16, Actor *, u8);
void func_8061EF4C(s32, s32, s32, f32, f32, f32, f32, f32);

s32 func_80616E08(Actor *arg0) {
    s16 command, state;
    u8 amount, pitch, priority, type;
    D_807F5AF0++;
    func_80614F4C((u8 *)&command); func_80614F28(&amount); func_80614F4C((u8 *)&state); func_80614F28(&pitch);
    type = ((P19ePlayerState *)((u8 *)D_807FC924 + D_807FD580->unk1F0 * 0x2F0))->unk2C0;
    if (type == 2) { if (command == 1) pitch = (u8)((f64)pitch * 0.5); priority = 10; func_8061EF4C(D_807FD580->unk1F0, 10, 8, arg0->unk7C, arg0->unk80, arg0->unk84, 100.0f, 800.0f); }
    else if (type == 0) { priority = 0xFF; pitch = (u8)((f64)pitch * 0.5); }
    else { switch (arg0->unk58) { case 6: case 7: priority = 0x46; break; case 8: priority = 0x5A; break; case 2: case 4: priority = 0x32; break; default: priority = 0x50; } }
    state = func_8060A7C0(command, arg0, ((P19eActorView *)arg0)->unk17C);
    if ((state == 2) || (state == 8)) amount = 10;
    func_806086CC(arg0->unk7C, arg0->unk80, arg0->unk84, state, pitch, command, amount, priority, 0.3f, 0);
    return 1;
}

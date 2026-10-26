// func_80617238 (src/global/19A00.c): from .scratch/P19e/func_80617238_best.c
typedef struct P19ePlayerState { u8 pad0[0x2C0]; u8 unk2C0; } P19ePlayerState;
extern P19ePlayerState *D_807FC924;
void func_806086CC(f32, f32, f32, s16, s32, s32, s32, s32, f32, s32);

s32 func_80617238(Actor *arg0) {
    s16 command;
    u8 amount, pitch;
    s32 priority;
    amount = 0xFF;
    D_807F5AF0++;
    func_80614F4C((u8 *)&command);
    func_80614F28(&pitch);
    switch (((P19ePlayerState *)((u8 *)D_807FC924 + D_807FD580->unk1F0 * 0x2F0))->unk2C0) {
    case 2: priority = 10; break;
    case 0: priority = 0xFF; amount = (u8)((f64)0xFF * 0.5); break;
    default:
        switch (arg0->unk58) { case 6: case 7: case 8: priority = 0x5A; break; case 2: case 4: priority = 0x32; break; default: priority = 0x50; }
    }
    func_806086CC(arg0->unk7C, arg0->unk80, arg0->unk84, command, amount, 0x7F, pitch, priority, 0.3f, 0);
    return 1;
}

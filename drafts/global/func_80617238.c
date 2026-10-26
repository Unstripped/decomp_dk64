// func_80617238 (src/global/19A00.c): stage 4: typed player-state view and switch/C FP conversion candidate; fdiff retains a 0x48 frame versus target 0x40, different register allocation for player-index arithmetic, and different conversion scheduling.
typedef struct P19c4GlobalState { u8 pad0[0x104]; s32 unk104; u8 pad108[0x9C]; u8 unk1A4; } P19c4GlobalState;
typedef struct P19c4PlayerState { u8 pad0[0x2C0]; u8 unk2C0; } P19c4PlayerState;
extern P19c4PlayerState *D_807FC924;
void func_806086CC(f32, f32, f32, s16, s32, s32, s32, s32, f32, s32);

s32 func_80617238(Actor *arg0) {
    s16 sp3E;
    u8 sp3D;
    u8 sp3B;
    s32 temp_t7;
    s32 var_v0;
    u8 temp_v0;

    sp3B = 0xFF;
    D_807F5AF0++;
    func_80614F4C((u8 *)&sp3E);
    func_80614F28(&sp3D);
    temp_v0 = (D_807FC924 + (((((((P19c4GlobalState *)D_807FD580)->unk1A4 * 4) - ((P19c4GlobalState *)D_807FD580)->unk1A4) * 16) - ((P19c4GlobalState *)D_807FD580)->unk1A4) * 16))->unk2C0;
    if (temp_v0 == 2) {
        var_v0 = 0xA;
    } else if (temp_v0 == 0) {
        var_v0 = 0xFF;
        sp3B = (u8)(u32)((f64)var_v0 * 0.5);
    } else {
        temp_t7 = arg0->unk58;
        switch (temp_t7) {
        case 6:
        case 7:
        case 8:
            var_v0 = 0x5A;
            break;
        case 2:
        case 4:
            var_v0 = 0x32;
            break;
        default:
            var_v0 = 0x50;
            break;
        }
    }
    func_806086CC(arg0->unk7C, arg0->unk80, arg0->unk84, sp3E, (s32)sp3B, 0x7F, (s32)sp3D, var_v0, 0.3f, 0);
    return 1;
}

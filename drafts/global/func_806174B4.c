// func_806174B4 (src/global/19A00.c): stage 4: behavioural m2c draft has correct 0x58 frame and control flow, but byte and float local layout differs (target bytes 0x40/3F/49/43/42/41 and float at 0x38).
void actorGetNodePos(Actor *, s32, f32 *, f32 *, f32 *);
void func_806086CC(f32, f32, f32, s16, s32, s32, s32, s32, f32, s32);

s32 func_806174B4(Actor *arg0) {
    f32 sp54, sp50, sp4C, sp38;
    s16 sp4A;
    u8 sp49, sp43, sp42, sp41, sp40, sp3F;
    D_807F5AF0++;
    func_80614F4C((u8 *)&sp4A);
    func_80614F28(&sp40); func_80614F28(&sp3F); func_80614F28(&sp49); func_80614F28(&sp43);
    func_80614FD8((u8 *)&sp38); func_80614F28(&sp42); func_80614F28(&sp41);
    if (arg0->unk60 & 4) {
        if (sp42 != 0) actorGetNodePos(arg0, sp42, &sp54, &sp50, &sp4C);
        else { sp54 = arg0->unk7C; sp50 = arg0->unk80; sp4C = arg0->unk84; }
        func_806086CC(sp54, sp50, sp4C, sp4A, sp40, sp3F, sp49, sp43, sp38, sp41);
    }
    return 1;
}

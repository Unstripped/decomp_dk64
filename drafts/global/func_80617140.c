// func_80617140 (src/global/19A00.c): stage 3: m2c behavioural draft; adding f64 local grew frame 0x30 to 0x40, while direct-cast form had correct frame but byte locals at 0x2D/2C/2B instead of 0x2B/2A/29.
typedef struct P19eActorCommand {
    u8 pad0[0x78];
    u8 unk78;
} P19eActorCommand;

extern s32 D_807457C8;
void n_alSndpStop(s32);
s16 func_8060A7C0(s16, Actor *, u8);
void sfxPlayFromActorDirect(Actor *, s16, u8, f32, u8, u8);

s32 func_80617140(Actor *arg0) {
    s16 sp2E;
    u8 sp2B;
    u8 sp2A;
    u8 sp29;
    f64 var_ft1;
    s16 temp_v0;

    D_807F5AF0++;
    func_80614F4C((u8 *)&sp2E);
    func_80614F28(&sp2B);
    func_80614F28(&sp2A);
    func_80614F28(&sp29);
    if (D_807457C8 != 0) {
        n_alSndpStop(D_807457C8);
        D_807457C8 = 0;
    }
    temp_v0 = func_8060A7C0(sp2E, arg0, ((P19eActorCommand *)arg0)->unk78);
    if (temp_v0 == 8) {
        sp29 = 4;
    }
    var_ft1 = (f64)sp2A;
    if ((s32)sp2A < 0) {
        var_ft1 += 4294967296.0;
    }
    sfxPlayFromActorDirect(arg0, temp_v0, sp2B, (f32)(var_ft1 / 127.0), sp29, 0x4B);
    return 1;
}

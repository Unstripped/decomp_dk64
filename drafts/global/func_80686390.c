// func_80686390 (src/global/89250.c): stage 4: cleaned names (randomNonNegative, sfxPlayFromActorWithAltitudeCheck, particleInitDefaultState)
void func_80686390(Actor *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    f32 scale;

    if (arg0 != NULL) {
        scale = (arg0->unk4 != NULL) ? (f64)arg0->unk4->unk38 / 0.15 : 1.0;
        if (arg0->unk6A & 4) {
            f32 f;
            f32 limit;

            if (arg0->unkC0 > -10.0f || (arg0->unk6A & arg0->unk6C & 1)) {
                f = 0.0f;
            } else {
                f = arg0->unkA0 - arg0->unk80;
            }
            limit = (arg0->unkAC - arg0->unkA4) * 2;
            f = (f < limit ? f : limit) < 0.0f ? 0.0f : (f < limit ? f : limit);

            if (arg0->unk58 == 0x29 || arg0->unk58 == 0x32) {
                sfxPlayFromActorWithAltitudeCheck(arg0, 0x2C7, 0xFF, 0x7F, 1);
            } else if (f < 10.0f) {
                sfxPlayFromActorWithAltitudeCheck(arg0, 0x10, (u8)((f64)f * 25.5), 0x7F, 1);
            } else if (f < 20.0f) {
                sfxPlayFromActorWithAltitudeCheck(arg0, 0xF, 0xFF, 0x7F, 1);
            } else {
                effectSpawnBurstParticles(arg0);
            }
        }
    } else {
        scale = arg1;
    }
    particleInitDefaultState();
    func_80714CC0(&D_8071FBF4, (f32)((f64)scale * 0.3), arg2, arg3, arg4);
    particleInitDefaultState();
    func_8071496C(2);
    func_80714CC0(&D_8071FBF4, (f32)((f64)scale * 0.05),
        (f32)((randomNonNegative() >> 15) % (u8)(30.0f * scale)) + arg2 - (f32)(u8)(15.0f * scale),
        arg3,
        (f32)((randomNonNegative() >> 15) % (u8)(30.0f * scale)) + arg4 - (f32)(u8)(15.0f * scale));
    particleInitDefaultState();
    func_8071496C(4);
    func_80714CC0(&D_8071FBF4, (f32)((f64)scale * 0.05),
        (f32)((randomNonNegative() >> 15) % (u8)(30.0f * scale)) + arg2 - (f32)(u8)(15.0f * scale),
        arg3,
        (f32)((randomNonNegative() >> 15) % (u8)(30.0f * scale)) + arg4 - (f32)(u8)(15.0f * scale));
}

// func_80686390 (src/global/89250.c): from .scratch/Beh8923B/func_80686390_best.c
void func_80686390(Actor *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    f32 scale;

    if (arg0 != NULL) {
        scale = (((Beh8923B_Actor *)arg0)->unk4 != NULL) ? (f64)((Beh8923B_Actor *)arg0)->unk4->unk38 / 0.15 : 1.0;
        if (((Beh8923B_Actor *)arg0)->unk6A & 4) {
            f32 f;
            f32 limit;

            if (((Beh8923B_Actor *)arg0)->unkC0 > -10.0f || (((Beh8923B_Actor *)arg0)->unk6A & ((Beh8923B_Actor *)arg0)->unk6C & 1)) {
                f = 0.0f;
            } else {
                f = ((Beh8923B_Actor *)arg0)->unkA0 - ((Beh8923B_Actor *)arg0)->unk80;
            }
            limit = (((Beh8923B_Actor *)arg0)->unkAC - ((Beh8923B_Actor *)arg0)->unkA4) * 2;
            f = (f < limit ? f : limit) < 0.0f ? 0.0f : (f < limit ? f : limit);

            if (((Beh8923B_Actor *)arg0)->unk58 == 0x29 || ((Beh8923B_Actor *)arg0)->unk58 == 0x32) {
                func_80608528(arg0, 0x2C7, 0xFF, 0x7F, 1);
            } else if (f < 10.0f) {
                func_80608528(arg0, 0x10, (u8)((f64)f * 25.5), 0x7F, 1);
            } else if (f < 20.0f) {
                func_80608528(arg0, 0xF, 0xFF, 0x7F, 1);
            } else {
                func_8068613C(arg0);
            }
        }
    } else {
        scale = arg1;
    }
    func_80686340();
    func_80714CC0(&D_8071FBF4, (f32)((f64)scale * 0.3), arg2, arg3, arg4);
    func_80686340();
    func_8071496C(2);
    func_80714CC0(&D_8071FBF4, (f32)((f64)scale * 0.05),
        (f32)((func_80611A44() >> 15) % (u8)(30.0f * scale)) + arg2 - (f32)(u8)(15.0f * scale),
        arg3,
        (f32)((func_80611A44() >> 15) % (u8)(30.0f * scale)) + arg4 - (f32)(u8)(15.0f * scale));
    func_80686340();
    func_8071496C(4);
    func_80714CC0(&D_8071FBF4, (f32)((f64)scale * 0.05),
        (f32)((func_80611A44() >> 15) % (u8)(30.0f * scale)) + arg2 - (f32)(u8)(15.0f * scale),
        arg3,
        (f32)((func_80611A44() >> 15) % (u8)(30.0f * scale)) + arg4 - (f32)(u8)(15.0f * scale));
}

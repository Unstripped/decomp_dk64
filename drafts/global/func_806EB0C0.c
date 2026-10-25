// func_806EB0C0 (src/global/EFDC0.c): m2c starter; inferred queued-call view
extern s32 D_807FC924;
extern ? D_807FD6F0;

s32 func_806EB0C0(s16 arg0, void *arg1, s32 arg2) {
    s32 temp_v0;
    void *temp_v1;

    temp_v0 = (arg2 & 0xFF) * 0x2F0;
    temp_v1 = D_807FC924 + temp_v0;
    if (temp_v1->unk29C < arg0) {
        temp_v1->unk29C = arg0;
        (D_807FC924 + temp_v0)->unk2A0 = arg1;
        (D_807FC924 + temp_v0)->unk2A8 = (s32) D_807FD6F0.unk0;
        (D_807FC924 + temp_v0)->unk2AC = (s32) D_807FD6F0.unk4;
        (D_807FC924 + temp_v0)->unk2B0 = (s32) D_807FD6F0.unk8;
        if (arg1 != NULL) {
            (D_807FC924 + temp_v0)->unk2A4 = (s32) arg1->unk54;
        }
        return 1;
    }
    return 0;
}

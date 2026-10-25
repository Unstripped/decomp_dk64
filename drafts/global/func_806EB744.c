// func_806EB744 (src/global/EFDC0.c): m2c starter; player and subactor views needed
? func_80609140(?, ?, ?, ?, s32, s32);              /* extern */
? func_8062217C(void *, ?);                         /* extern */
? func_80627878(void *);                            /* extern */
? func_806F0D68(void *);                            /* extern */
? sfxStopSlotSound(void *, ?);                      /* extern */
extern void *D_807FBB48;
extern s32 D_807FC924;
extern u8 D_807FC929;
extern void *D_807FD580;

void func_806EB744(void) {
    s16 sp2A;
    f32 temp_fv0;
    s16 var_v1;
    s32 temp_t6;
    u8 temp_v0;
    void *temp_s0;
    void *var_a0;

    var_a0 = D_807FD580->unk104;
    temp_s0 = var_a0->unk174;
    temp_v0 = temp_s0->unkEF;
    var_v1 = (s16) (s32) temp_s0->unkB8;
    if (temp_v0 != 0) {
        temp_s0->unkF0 = temp_v0;
        var_v1 = 0x80;
        var_a0 = D_807FD580->unk104;
    }
    sp2A = var_v1;
    func_80627878(var_a0);
    func_8062217C(D_807FD580->unk104, 0);
    temp_t6 = (D_807FC924 + (D_807FC929 * 0x2F0))->unk2A8;
    temp_s0->unkF3 = (s8) temp_t6;
    if ((temp_t6 & 0xFF) == 3) {
        sfxStopSlotSound(D_807FBB48, 0);
        func_80609140(0x26, 0x7FFF, 0x427C0000, 0x3F800000, 0, 0);
        if ((D_807FC924 + (D_807FC929 * 0x2F0))->unk2AC != 0) {
            func_806F0D68(D_807FBB48);
        }
    }
    temp_s0->unkBC = 0x80;
    temp_fv0 = (f32) sp2A;
    D_807FD580->unk104->unkB4 = temp_fv0;
    temp_s0->unkB8 = temp_fv0;
    temp_s0->unkB2 = (s16) (D_807FBB48->unkE6 + 0x800);
    D_807FBB48->unkB8 = 0.0f;
    D_807FBB48->unk6A = (u16) (D_807FBB48->unk6A | 0x2000);
}

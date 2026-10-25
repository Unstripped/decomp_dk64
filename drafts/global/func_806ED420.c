// func_806ED420 (src/global/EFDC0.c): stage 1: m2c reconstruction of landing effect; needs player-state view and s16 table declarations
? func_806CA2AC();                                  /* extern */
? func_8072DB68(?);                                 /* extern */
? sfxPlayFromActorWithAltitudeCheck(void *, ?, ?, ?, s32); /* extern */
extern ? D_8074E77C;
extern ? D_807530B0;
extern void *D_807FBB48;
extern u8 D_807FC929;
extern void *D_807FD580;
extern s16 D_807FD584;

void func_806ED420(void) {
    u8 temp_v0;

    if (D_807FD580->unkD4 == 0) {
        func_806CA2AC();
        func_8072DB68(3);
        temp_v0 = *(&D_8074E77C + D_807FC929);
        if (temp_v0 != 2) {
            if (temp_v0 == 3) {
                sfxPlayFromActorWithAltitudeCheck(D_807FBB48, 0xB9, 0xFF, 0x7F, 0x14);
            }
        } else {
            sfxPlayFromActorWithAltitudeCheck(D_807FBB48, 0xD2, 0xFF, 0x7F, 0x14);
        }
        D_807FD580->unkD4 = (s16) *(&D_807530B0 + (D_807FD584 * 2));
        D_807FBB48->unkB8 = (f32) (D_807FBB48->unkB8 / 2.0f);
    }
}

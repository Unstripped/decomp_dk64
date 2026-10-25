// func_806ED420 (src/global/EFDC0.c): stage 4: all control flow and frame match; division instruction remains strength-reduced
typedef struct EfN5PlayerD4 { u8 pad0[0xD4]; s16 unkD4; } EfN5PlayerD4;
extern s16 D_807530B0[];
s32 sfxPlayFromActorWithAltitudeCheck(Actor *, s16, u8, s16, u8);
void func_806CA2AC(void);

void func_806ED420(void) {
    u8 character;

    if (((EfN5PlayerD4 *)D_807FD580)->unkD4 == 0) {
        func_806CA2AC();
        func_8072DB68(3);
        character = D_8074E77C[D_807FC929];
        if (character != 2) {
            if (character == 3) {
                sfxPlayFromActorWithAltitudeCheck(D_807FBB48, 0xB9, 0xFF, 0x7F, 0x14);
            }
        } else {
            sfxPlayFromActorWithAltitudeCheck(D_807FBB48, 0xD2, 0xFF, 0x7F, 0x14);
        }
        ((EfN5PlayerD4 *)D_807FD580)->unkD4 = D_807530B0[D_807FD584];
        D_807FBB48->unkB8 = D_807FBB48->unkB8 / 2.0f;
    }
}

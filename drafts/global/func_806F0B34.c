// func_806F0B34 (src/global/F56F0.c): Stage 3 switch draft reconstructed from assembly; compiler case layout remains unmatched.
void sfxPlayFromActorWithAltitudeCheck(Actor *, s32, s32, s32, s32);
extern u8 D_807FC929;
extern u8 D_8074E77C[];

void func_806F0B34(Actor *arg0) {
    switch (D_8074E77C[D_807FC929]) {
    case 0:
        sfxPlayFromActorWithAltitudeCheck(arg0, 0x17C, 0xFF, 0x7F, 0x19);
        break;
    case 1:
        sfxPlayFromActorWithAltitudeCheck(arg0, 0x17C, 0xC8, 0xA0, 5);
        break;
    case 2:
        sfxPlayFromActorWithAltitudeCheck(arg0, 0x17C, 0xFF, 0x7F, 5);
        break;
    case 3:
        sfxPlayFromActorWithAltitudeCheck(arg0, 0x185, 0xFF, 0x7F, 0x19);
        break;
    default:
        sfxPlayFromActorWithAltitudeCheck(arg0, 0x18F, 0xFF, 0x7F, 0x19);
        break;
    }
}

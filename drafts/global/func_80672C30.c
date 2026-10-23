// func_80672C30 (src/global/70FD0.c): Closest diff: IDO dead-store eliminates first sh t9,0x6a(a0) and constant folds 0xfff7 & 0xfbff into 0xfbf7
void func_80672C30(M70F_Actor *arg0) {
    u16 temp_t9;
    M70F_ActorSub140 *temp_v0;

    temp_v0 = arg0->unk140;
    arg0->unk110 = 0;
    if (temp_v0 != NULL) {
        temp_v0->unk6C = 0;
        arg0->unk140->unk24 = 0;
    }
    temp_t9 = arg0->unk6A & 0xFFF7;
    arg0->unk6A = temp_t9;
    arg0->unk6A = temp_t9 & 0xFBFF;
    arg0->unk64 |= 0x2000;
}

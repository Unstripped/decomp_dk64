// func_80610044 (src/global/14CF0.c): stage 1: m2c starter; not yet type-resolved
extern ? D_805FB000;
extern ? D_805FB0D0;
extern s8 D_80744460;
extern ? D_80744470;
extern u8 D_807444FC;
extern ? D_807659E8;
extern ? D_80767CD8;
extern ? D_80767CE8;
extern ? D_8076AF20;
extern ? D_8076B320;
extern ? D_807F0570;
extern ? D_807F0588;
extern ? D_807F059C;
extern s32 D_807F05A4;
extern ? D_807F05A8;
extern s32 D_807F0984;
extern OSMesgQueue gScheduler;

void func_80610044(void *arg0, s32 arg1, s32 arg2, u8 arg3, s32 arg4, u8 arg5) {
    s32 sp24;
    s32 temp_t6;
    s32 temp_t9;
    s32 temp_v0;
    void *temp_s0;

    temp_t6 = arg2 & 0xFF;
    if (D_80744460 == 0) {
        temp_s0 = (temp_t6 * 0xC0) + (D_807444FC * 0x60) + &D_807F05A8;
        *(&D_807F059C + temp_t6) = 1;
        temp_v0 = temp_t6 * 4;
        temp_s0->unk10 = 1;
        temp_s0->unk14 = 0;
        temp_s0->unk18 = &D_805FB000;
        temp_s0->unk1C = (s32) (&D_805FB0D0 - &D_805FB000);
        temp_s0->unk20 = (s32) *(&D_807F0570 + temp_v0);
        temp_s0->unk24 = 0x1000;
        temp_s0->unk2C = 0x800;
        temp_s0->unk30 = &D_8076AF20;
        temp_s0->unk34 = 0x400;
        temp_s0->unk28 = (s32) *(&D_807F0588 + temp_v0);
        temp_s0->unk38 = (s32) D_807F05A4;
        temp_s0->unk3C = (s32) (D_807F05A4 + D_807F0984);
        temp_s0->unk40 = arg0;
        temp_s0->unk48 = &D_8076B320;
        temp_s0->unk4C = 0xC00;
        temp_t9 = arg1 * 8;
        temp_s0->unk44 = temp_t9;
        temp_s0->unk0 = 0;
        temp_s0->unk54 = &D_807659E8;
        temp_s0->unk58 = (s32) ((temp_t6 << 0x10) | arg4);
        temp_s0->unk8 = 3;
        if (arg3 != 0) {
            temp_s0->unk8 = (s32) (3 | 0x40);
        }
        temp_s0->unk50 = &D_80767CD8;
        temp_s0->unkC = (s32) *(&D_80744470 + (D_807444FC * 4));
        if (arg5 != 0) {
            osWritebackDCacheAll();
        } else {
            sp24 = temp_t9;
            osWritebackDCache(temp_s0, 0x60);
            osWritebackDCache(arg0, sp24);
            osWritebackDCache((D_807444FC * 0x11B0) + &D_80767CE8, 0x11B0);
        }
        osSendMesg(&gScheduler, temp_s0, 1);
    }
}

// func_80028834 (src/menu/3E10.c): text-identical, reloc only (float literals .rodata+off vs D_80033C68..8C labels); layout needs per-call (void *)(s32)&D_80721444 (a named sp30 pointer grows frame 56->64)
extern s8 D_800337F4;
extern s8 D_800337F8;
extern s8 D_8076A0D1;
extern s8 D_80033F38;
extern s8 D_80033F54;
extern s8 D_80033F55;
extern s8 D_80033F56;
extern s16 D_80033F52;
extern s16 D_800336A4[];
extern f32 D_80033F58;
extern f32 D_80033F5C;
extern u8 D_8072052C;
extern u8 D_80720C34;
extern u8 D_80720CF0;
extern u8 D_80721094;
extern u8 D_807210EC;
extern u8 D_80721170;
extern u8 D_807211D0;
extern u8 D_80721444;
void func_80030894(void *, void *, s32, s32, f32, s32, s32);
s32 func_8060C6B8(s32, s32, u8, s32);
s32 flagGet(s32, s32);

void func_80028834(void *arg0, s32 arg1) {
    s8 *temp_s0 = *(s8 **)((u8 *)arg0 + 0x174);

    D_800337F8 = 0;
    D_800337F4 = 0;
    *(u8 *)((u8 *)D_807FBB4C + 0x154) = 0x85;
    *(u8 *)((u8 *)D_807FBB4C + 0x155) = 0;
    D_80745844 = func_8060C6B8(0x1E, 0, 0, 0);
    menuSetAudioMode();
    temp_s0[0x17] = D_8076A0D1;
    func_80030894(temp_s0, &D_80720C34, 0xA0, 0xD2, 0.75f, 2, 0);
    func_80030894(temp_s0, (void *)(s32)&D_80721444, 0, 0, 1.2f, 2, 0x12);
    func_80030894(temp_s0, (void *)(s32)&D_80721444, 1, 0, 1.2f, 2, 0x12);
    func_80030894(temp_s0, (void *)(s32)&D_80721444, 2, 0, 1.2f, 2, 0x12);
    func_80030894(temp_s0, (void *)(s32)&D_80721444, 3, 0, 1.2f, 2, 0x12);
    func_80030894(temp_s0, (void *)(s32)&D_80721444, 4, 0, 1.2f, 2, 0x12);
    func_80030894(temp_s0, &D_8072052C, 0, 0, 0.6f, 2, 6);
    func_80030894(temp_s0, &D_807211D0, 1, 0, 0.8f, 2, 6);
    if (flagGet(0, 1) == 0) {
        D_80033F38 = 0;
    }
    func_80030894(temp_s0, &D_80721094, 2, 0, 0.8f, 2, 7);
    if (flagGet(0x1C, 1) == 0) {
        D_80033F38 = 0;
    }
    func_80030894(temp_s0, &D_807210EC, 3, 0, 0.6f, 2, 6);
    func_80030894(temp_s0, &D_80721170, 4, 0, 0.6f, 2, 6);
    func_80030894(temp_s0, &D_80720CF0, 0x122, 0xD2, 0.75f, 2, 0);
    D_807FBB4C->unk7C = 700.0f;
    D_807FBB4C->unk80 = 100.0f;
    D_807FBB4C->unk84 = 70.0f;
    D_80033F54 = 0;
    while (D_800336A4[D_80033F54] != -1) {
        D_80033F54++;
    }
    D_80033F52 = 0x1E;
    D_80033F55 = 0;
    D_80033F56 = 0;
    D_80033F5C = 0.0f;
    D_80033F58 = 1.0f;
    D_807FBB60 &= 0xFFFEFFFF;
}

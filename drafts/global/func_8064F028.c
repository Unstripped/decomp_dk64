// func_8064F028 (src/global/478F0.c): text-identical, reloc only: all insns match; only .rodata double reloc (D_80758BD8 17.5 vs .rodata+off). Needs func_8064EE08 defined above (passed to func_8071498C).
s32 actorSpawn(s32, s32);
extern s32 D_8076A0A8;
extern f32 D_807F622C;
extern Actor *D_807FBB44;
extern s8 D_807F6950;
extern s8 D_807F6951;
void func_8064EE08(void *, u8 *);
void camStartPath(void *, s32, s32);
void sfxAllocateChannel(s32, f32);
extern u8 D_80721530[];

void func_8064F028(CsState *cs, s16 csId, s16 b, s16 c) {
    func_807149C8(0xFF, 0xFF, 0xFF, 0x80);
    func_8071498C(func_8064EE08);
    func_807149FC(-1);
    func_807149B8(1);
    func_80714998(2);
    func_80714CC0(D_80721530, 0.0f, D_807F621C, D_807F6220 + 17.5, D_807F6224);
    actorSpawn(0x9C, 0x53);
    D_807FBB44->unk7C = D_807F621C;
    D_807FBB44->unk80 = D_807F6220;
    D_807FBB44->unk84 = D_807F6224;
    D_807FBB44->unkE6 = D_807F622C * 4096.0f / 360.0f;
    if (D_8076A0A8 == 0xB2 || (D_8076A0A8 == 0xAD && b == 4)) {
        D_807FBB44->unkE6 += 0x800;
    }
    camStartPath(D_807FBB44, 0x22, 5);
    sfxAllocateChannel(0xAB, 1.0f);
    func_80609140(0x2EA, 0x7FFF, 63.0f, 1.0f, 0, 0);
    D_807F6951 = b;
    D_807F6950 = 0;
}

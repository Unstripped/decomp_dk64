// func_80690500 (src/global/936B0.c): unattempted starter draft from m2c
void func_8061C6A8(void *, void *, s32, s32, s32, s32, s32, s32, s32, s32, f32);
s32 func_8061CB50(void);
void func_806319C4(void *, s32);
void func_8065A708(f32, f32, s32, s32, f32, f32, f32, s32, s32, s32, s32);
void func_80671C0C(void *, s32, f32 *, f32 *, s32 *);
void func_8068F72C(void *, s32, s32, s32);
void func_8068FF40(u8, void *, s32);
void func_80690190(void *, s32, void *);
void func_806EB0C0(s32, void *, u8);
void func_8070033C(f32, f32, s32, s32, f32, f32, f32, s32, s32, s32);
s32 func_8073110C(s32, s32);
extern u8 D_807444EC;
extern f32 D_80750300;
extern Actor *D_807FBB40;
extern Actor *D_807FBB4C;
extern s32 D_807FC924;

void func_80690500(void) {
    void *sp5C;
    void *sp54;
    s32 sp50;
    void *sp4C;
    u8 sp4B;
    f32 sp44;
    f32 sp40;
    s32 sp3C;
    s32 temp_a1;
    void *temp_a0;
    void *temp_a2;

    temp_a0 = D_807FBB40->unk174;
    temp_a1 = (s32)D_807FBB40->unk178;
    temp_a2 = *(void **)(D_807FC924 + (*(u8 *)((u8 *)temp_a0 + 0x28) * 0x2F0) + 4);
    sp4C = *(void **)(*(u8 **)((u8 *)temp_a2 + 0x104) + 0x174);
    sp4B = D_807FBB40->unk6A & 1;
    *(u8 *)((u8 *)temp_a0 + 0x34) = 2;
    sp5C = temp_a0;
    sp50 = temp_a1;
    sp54 = temp_a2;
    func_80690190(temp_a0, temp_a1, temp_a2);
    if ((D_807444EC == 0) && (*(u8 *)((u8 *)sp4C + 0xF3) != 4)) {
        func_8061C6A8(*(void **)((u8 *)sp54 + 0x104), D_807FBB40, 4, 0x800, 0xA0, 0, 6, 0x12C, 0x8F, 0, 0.2f);
    }
    func_8068F72C(sp5C, sp50, 1, 1);
    func_8068FF40(sp4B, sp5C, sp50);
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unkC4 = D_80750300;
        D_807FBB40->unk144 = 0x3C;
        func_806EB0C0(0x4C, D_807FBB40, *(u8 *)((u8 *)sp54 + 0x1A4));
    }
    if ((func_8061CB50() == 0) || ((func_8061CB50() != 0) && (D_807FBB4C->unk6A & 0x100))) {
        func_80671C0C(D_807FBB40, 1, &sp44, &sp40, &sp3C);
        func_8065A708(sp44, sp40, sp3C, 0, 0.0f, 0.0f, 300.0f, 0, 0xFF, 0xFF, 0xFF);
        if (func_8073110C(0x6B, 2) == 0) {
            if ((func_8061CB50() != 0) && (D_807FBB4C->unk6A & 0x100)) {
                func_80671C0C(D_807FBB40, 2, &sp44, &sp40, &sp3C);
                func_8070033C(sp44, sp40, sp3C, 0, 0.0f, 0.0f, 0.0f, 0xFF, 0xFF, 0xFF);
            }
            if (func_8061CB50() == 0) {
                D_807FBB4C->unk6A = (u16) (D_807FBB4C->unk6A & 0xFEFF);
            }
        }
    }
    func_806319C4(D_807FBB40, 0);
}

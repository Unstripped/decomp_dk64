// func_806C9C1C (src/global/CC800.c): text-identical, reloc only: index loop (i<5, D_80750B34[i]) makes IDO emit end pointer as D_80750B34+0x14 (lui/addiu s2 in target order) but reloc is %lo(D_80750B34+0x14) vs expected D_80750B48. Pointer do-while with &D_80750B48 gives the s0/s2 addiu swap instead.
extern s32 D_80750B34[];
void func_806F91B4(s32, u8, s32);
void func_806F833C(s32);

void func_806C9C1C(s32 arg0) {
    s32 i;

    for (i = 0; i < 5; i++) {
        func_806F91B4(D_80750B34[i], arg0, 0x270F);
    }
    func_806F833C(0);
}

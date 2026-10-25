// func_806BDEC8 (src/global/C2A90.c): text-identical, reloc only (D_8075BBE4 vs .rodata+4)
typedef struct R1C2CB_Sub174 {
    /* 0x000 */ u8 pad0[0x104];
    /* 0x104 */ s32 unk104;
} R1C2CB_Sub174;

typedef struct R1C2CB_ActorC0 {
    /* 0x000 */ u8 pad0[0xC0];
    /* 0x0C0 */ f32 unkC0;
} R1C2CB_ActorC0;

#define R1C2CBC0 ((R1C2CB_ActorC0 *)D_807FBB40)

void func_80614EBC(Actor *, s32);
void func_806319C4(Actor *, s32);
void func_8061C600(s32, Actor *, s32, s32, s32, s32, s32, s32, s32, s32, f32);
void func_8072881C(s32, void *);

void func_806BDEC8(void) {
    R1C2CB_Sub174 *sub = D_807FBB4C->unk174;

    if (func_806BDD90() == 1) {
        D_807FBB40->unk154 = 0x12;
        D_807FBB40->unk155[0] = 0;
    }
    if (D_807FBB40->unk154 == 0x12) {
        switch (D_807FBB40->unk155[0]) {
        case 0:
            R1C2CBC0->unkC0 = 150.0f;
            func_80614EBC(D_807FBB40, 0x28E);
            func_8061C600(sub->unk104, D_807FBB40, 4, 0xE77, 0xFA, 2, 0x32, 0x20, 0x3F, 0x4A, 0.16f);
            D_807FDC90->unk2C = 0x32;
            D_807FBB40->unk155[0]++;
            break;
        case 2:
            if (D_807FDC90->unk2C != 0) {
                D_807FDC90->unk2C--;
            } else {
                func_80614EBC(D_807FBB40, 0x28F);
                D_807FBB40->unk155[0]++;
                D_807FDC90->unk2C = 0x78;
            }
            break;
        case 3:
            if (D_807FDC90->unk2C != 0) {
                D_807FDC90->unk2C--;
            } else if (func_805FF0C8() == 0) {
                D_807FBB40->unk154 = 0;
                D_807FBB40->unk155[0] = 0;
            }
            break;
        }
    }
    func_8072881C(0, D_807FDC90->unk28);
    func_806319C4(D_807FBB40, 0);
}

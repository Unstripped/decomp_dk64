// func_806BE09C (src/global/C2A90.c): TEXT identical except one adjacent addu order (addu v0,t5,t8 vs addu t3,a3,t8) in the unrolled 5-row sum; needs 'if (1){} if (1){}' (>=2) after last case body to get v0/v1 right (hack); D_8075BBE8.. .rodata+off reloc only
typedef struct R1C2CB_Sub174 {
    /* 0x000 */ u8 pad0[0x104];
    /* 0x104 */ s32 unk104;
} R1C2CB_Sub174;

void func_80614EBC(Actor *, s32);
void func_806319C4(Actor *, s32);
void func_8072881C(s32, void *);
void func_806BDD90(void);

typedef struct R1C2CB_S90 {
    /* 0x00 */ u8 pad0[0x2C];
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ s16 unk2E;
    /* 0x30 */ f32 unk30;
} R1C2CB_S90;

typedef struct R1C2CB_ActorEE {
    /* 0x00 */ u8 pad0[0xEE];
    /* 0xEE */ s16 unkEE;
} R1C2CB_ActorEE;

#define R1C2CBS ((R1C2CB_S90 *)D_807FDC90)
#define R1C2CBE ((R1C2CB_ActorEE *)D_807FBB4C)

extern u8 D_8076A0AB;
extern s32 D_8076A064;
extern u8 D_8074E77C;
extern u16 D_807446C0[];
extern u16 D_807FC930[];
extern u8 D_807FC950[][0x5E];
extern void func_8071D0F0(void);

u8 func_805FF030(u8, s32);
s32 func_806F8AD4(s32, s32);
void func_806F8D58(s32, s32);
void func_806F91B4(s32, s32, s32, void *);
void func_8061C518(s32, Actor *, s32, s32, s32, s32, s32, s32, s32, s32, f32);
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
void func_80724E48(s32);
void func_807248B0(Actor *, f32);
void effectSpawnMultiTierRing(f32, s32, f32, f32, f32);
void func_8071498C(void (*)(void));
void func_807149FC(s32);
void func_807149B8(s32);
void func_80714950(void *);
void *func_806FACE8(s32);
void func_80714C08(void *, f32, Actor *, s32, s32);

void func_806BE09C(void) {
    R1C2CB_Sub174 *sub;
    s16 angle;
    u8 idx;
    f32 ratio;
    f32 target;
    u8 *row;
    s32 sum;
    s32 i;

    sub = D_807FBB4C->unk174;
    idx = func_805FF030(D_8076A0AB, 0);
    ratio = (f32)D_807FC930[idx] / (f32)D_807446C0[idx];
    if (func_806BDD90() == 1) {
        R1C2CBS->unk2C = func_806F8AD4(0, 0);
        if (R1C2CBS->unk2C != 0) {
            D_807FBB40->unk154 = 0x12;
            D_807FBB40->unk155[0] = 0;
            R1C2CBS->unk2E = 0x32;
            func_80614EBC(D_807FBB40, 0x28A);
            func_8061C518(sub->unk104, D_807FBB4C, 4, 0x990, 0x5A, -0x2E, 0x3C, 0xA, 0x20, 0, 0.3f);
            angle = mathAngleBetweenPoints2D(D_807FBB40->unk7C, D_807FBB40->unk84, D_807FBB4C->unk7C, D_807FBB4C->unk84);
            D_807FBB4C->unkE6 = angle;
            R1C2CBE->unkEE = D_807FBB4C->unkE6;
        }
    }
    func_80724E48(0);
    if (ratio > 1.0f) {
        ratio = 1.0f;
    }
    target = D_807FDC90->unk30 + (0.44 - D_807FDC90->unk30) * ratio;
    if (!(D_807FBB40->unk60 & 0x10)) {
        func_807248B0(D_807FBB40, target);
    }
    switch (D_807FBB40->unk154) {
    case 0x12:
        func_807248B0(D_807FBB40, (target - D_807FBB40->unk4->unk34) * 0.1 + D_807FBB40->unk4->unk34);
        switch (D_807FBB40->unk155[0]) {
        case 0:
            if (R1C2CBS->unk2E != 0) {
                R1C2CBS->unk2E--;
                if (R1C2CBS->unk2E == 0) {
                    func_8061C518(sub->unk104, D_807FBB40, 4, 0x305, 0x14A, 3, 0x32, 0x7F, 0x5A, 0, 0.03f);
                }
            }
            if (R1C2CBS->unk2C != 0) {
                if (!(D_8076A064 & 3)) {
                    row = D_807FC950[D_8074E77C];
                    R1C2CBS->unk2C--;
                    func_806F91B4(0, 0, -1, D_807FC950);
                    ((u16 *)(row + 0x26))[idx] += 1;
                    sum = 0;
                    for (i = 0; i < 5; i++) {
                        sum += ((u16 *)(D_807FC950[i] + 0x26))[idx];
                    }
                    if (sum >= D_807446C0[idx]) {
                        R1C2CBS->unk2C = 0;
                        func_806F8D58(0, 0);
                    }
                    func_8071498C(func_8071D0F0);
                    func_807149FC(-1);
                    func_807149B8(1);
                    func_80714950(D_807FBB40);
                    func_80714C08(func_806FACE8(0), 0.3f, D_807FBB4C, 4, 0);
                }
            } else if (R1C2CBS->unk2E == 0) {
                R1C2CBS->unk2C = 0x1E;
                D_807FBB40->unk155[0] = 1;
            }
            break;
        case 1:
            if (R1C2CBS->unk2C != 0) {
                R1C2CBS->unk2C--;
            } else {
                func_80614EBC(D_807FBB40, 0x28B);
                D_807FBB40->unk154 = 0x27;
                D_807FBB40->unk155[0] = 0;
            }
            break;
        }
        break;
    case 0x27:
        if (D_807FBB40->unk155[0] == 1) {
            effectSpawnMultiTierRing(4.0f, 1, D_807FBB40->unk7C, D_807FBB40->unk80 + 5.0f, D_807FBB40->unk84);
            D_807FBB40->unk154 = 0x28;
            D_807FBB40->unk155[0] = 0;
            R1C2CBS->unk2C = 0x3C;
        }
        break;
    case 0x28:
        R1C2CBS->unk2C--;
        if (R1C2CBS->unk2C == 0) {
            D_807FBB40->unk154 = 0;
            D_807FBB40->unk155[0] = 0;
            R1C2CBS->unk2E = 0;
        }
        if (1) { } if (1) { }
        break;
    }
    func_8072881C(0, D_807FDC90->unk28);
    func_806319C4(D_807FBB40, 0);
}

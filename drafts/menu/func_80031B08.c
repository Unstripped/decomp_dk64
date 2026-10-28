// func_80031B08 (src/menu/3E10.c): stage 4: same switch/jump table; frame 0x40 vs 0x38: uopt puts &D_807FBB40 in s1 across calls, target keeps it in t1 and rematerialises lui/addiu after each call; also 'li t5,0x400'-style schedule diffs; 74 diff lines of ~335; tail via var_s0 vs D_807FBB40 sweep (10 sites, 2^5 masks) and permuter 270s gave no match
typedef struct Menu10_Sub174 {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    char padC[0x23C - 0xC];
    u16 unk23C;
} Menu10_Sub174;

typedef struct Menu10_Actor {
    char pad0[0x60];
    s32 unk60;
    char pad64[0x7C - 0x64];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0xE6 - 0x88];
    s16 unkE6;
    s16 unkE8;
    char padEA[0x155 - 0xEA];
    u8 unk155;
    char pad156[0x174 - 0x156];
    Menu10_Sub174 *unk174;
} Menu10_Actor;

#define Menu10_A ((Menu10_Actor *)D_807FBB40)

extern f32 D_80033678[];
extern s16 D_80754CE0;
extern u8 D_8071FE64;
void actorUpdateModelMatrix(void *, s32);

void func_80031B08(void) {
    Menu10_Actor *var_s0;
    Menu10_Sub174 *temp_v1;
    s32 var_v0;
    s32 i;

    D_8003369C += 4.5f;
    var_s0 = (Menu10_Actor *)D_807FBB40;
    temp_v1 = var_s0->unk174;
    if (D_8003369C > 0.0f) {
        D_8003369C = 0.0f;
    }
    switch (var_s0->unk155) {
    case 0:
        var_s0->unkE6 = 0x800;
        Menu10_A->unk155 = 1;
        actorScriptStart(D_807FBB40, 0x346);
        func_8061B650(gCamActor);
        var_s0 = Menu10_A;
        D_8003369C = -35.0f;
        break;
    case 1:
        if (D_8003369C == 0.0f) {
            actorScriptStart(var_s0, 0x347);
            Menu10_A->unk155 = 2;
            temp_v1->unk23C = 0;
            var_s0 = Menu10_A;
        }
        break;
    case 2:
        temp_v1->unk23C += 1;
        if (temp_v1->unk23C == 3) {
            func_80609140(0x3C, 0x61A8, 63.0f, 1.0f, 0, 0);
            D_80033F50 = 3;
        }
        var_s0 = Menu10_A;
        break;
    case 3:
        if (**(u16 **)((u8 *)D_807FC924 + 0x298) & 0x8000) {
            if (D_800337F0 == 1) {
                actorScriptStart(var_s0, 0x348);
                Menu10_A->unk155 = 4;
                var_s0 = Menu10_A;
                D_800337F4 = 0x3C;
            } else if (D_800337F0 == -1) {
                func_80609140(0x98, 0x61A8, 63.0f, 1.0f, 0, 0);
                var_s0 = Menu10_A;
            }
        }
        break;
    case 5:
        D_80033F40 = 0.1f;
        D_80033F3C = D_80033F40;
        D_800337F4 = 0;
        temp_v1->unk23C = 0;
        Menu10_A->unk155 = 6;
        var_s0 = Menu10_A;
        break;
    case 6:
    case 7:
    case 8:
        temp_v1->unk23C += 1;
        var_v0 = temp_v1->unk23C;
        if (var_v0 >= 0x3E9) {
            var_v0 = temp_v1->unk23C = 0x3E8;
        }
        if (var_v0 == 8) {
            func_8071495C();
            func_80714CC0(&D_8071FE08, 8.3f, 160.0f, 120.0f, -10.0f);
            func_80609140(0x23, 0x7FFF, 63.0f, 1.0f, 0, 0);
            func_80609140(0x17, 0x7FFF, 63.0f, 1.0f, 0, 0);
            i = 0;
            do {
                func_8071498C(func_80030A90);
                func_8071495C();
                func_80714CC0(&D_8071FE64, 1.8f, 160.0f, 120.0f, -10.0f);
                i += 1;
            } while (i != 5);
            var_v0 = temp_v1->unk23C;
        }
        if (var_v0 >= 0xC) {
            D_807FBB60 &= 0xFFFEFFFF;
        }
        var_s0 = Menu10_A;
        break;
    }
    if (D_80033698 != 0) {
        D_80033698 -= 1;
    }
    if (var_s0->unk155 < 6) {
        if ((f64)D_8003369C > -30.0) {
            D_807FBB60 |= 0x10000;
        } else {
            D_80033698 = 3;
        }
    }
    D_80033738 = 0x14;
    var_s0->unk80 = -D_8003369C;
    D_807FC924->unk210 = var_s0->unk7C;
    D_807FC924->unk214 = (f32)(((f64)D_80033678[D_80033F50] * 50.0) + (f64)(var_s0->unk80 + 13.1f + D_8003369C) - 0.1);
    D_807FC924->unk218 = var_s0->unk84 - 50.0f;
    D_807FC924->unk228 = var_s0->unk7C;
    D_807FC924->unk22C = D_807FC924->unk214;
    D_807FC924->unk230 = 10020.0f;
    D_80754CE0 = (s32)(D_80033678[D_80033F50] * 400.0f);
    actorUpdateModelMatrix(var_s0, 0);
}

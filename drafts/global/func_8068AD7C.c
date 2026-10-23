// func_8068AD7C (src/global/8F4B0.c): Closest diff 1255 (0 mnemonic diffs, identical 0x68 stack frame and instruction count; rodata jump tables byte-identical; loop body has single register shift t0..t9 vs a0..t8 due to a0 allocator choice)
void func_80659620(void *, void *, void *, s32);
void func_80704AFC(f32, f32, f32);
void func_8070B308(s32);
void func_805FF158(s32);
s32 func_8068ABE0(s16);
void func_805FF378();
void func_806F3BEC(void *, s16, s16, s32);
void func_805FF4D8(s16, s16);
void func_805FF9AC(s16, s16, s16, s32);
void func_805FF628(s16, s16);
void func_806C92C4(s16);
void func_805FF898(void);
void func_805FF8F8(void);
void func_805FF660(u8);
s32 func_805FF030(u8, s32);
void func_80600044(s32);
void func_806F397C(void *, s32, s16, s32);
void func_80608528(void *, s16, s32, s32, s32);
void func_80602A94(s16, f32);
void func_80602B60(s16, s32);
void func_807215AC(s32, s32, s32);
void func_80721560(s32, s32, s32, s32, s32, s32);
void func_80653F68(s16);
void func_80659F7C(f32, f32, f32, f32, s32);
void func_80659DB0(f32, f32, f32, s16);
void func_80711BD0(f32, s16, s16, s32);
void func_80711950(f32, s16, s16);
void func_80711F90(f32, s16, f32, s16, f32);
s32 func_80611A44(void);
void func_80659670(f32, f32, f32, s16);
void func_80608DA8(s32, s32, s32, s32, s32);
void func_80711410(f32, s16, f32, s16, f32);
s32 func_807122B4(void);
void func_8066466C(void);
void func_80664D20(void);

extern Actor *D_807FBB40;
extern u8 D_807FBDC4;
extern ActorGlobalState D_807FBB70;
extern s16 D_807FDCBC;
extern s16 D_807FDCB8;
extern s32 D_807FBB60;
extern void *D_807FBB4C;
extern s32 D_8076A0A8;
extern R2F4B_FD580 *D_807FD580;
extern Act8F4_Struct_C924 *D_807FC924;
extern u16 D_80744700[];
extern u8 D_8076A0AB;
extern s32 D_8076A0AC;
extern Actor *D_807FBB48;
extern u8 D_807FC621;
extern u8 D_807FC622;
extern u16 D_807ECD48;
extern u16 D_8076A0A6;
extern u8 D_80750190;
extern u8 D_807FC620;

void func_8068AD7C(void) {
    R2F4B_Actor174 *temp_s1;
    s32 i;
    s32 pad;
    s16 *temp_s0;
    s32 var_s0;
    s32 var_v0;
    s16 temp_a0;
    s16 temp_v0_2;

    temp_s1 = (R2F4B_Actor174 *)D_807FBB40->unk174;
    if (!(D_807FBB40->unk60 & 0x10)) {
        temp_s1->unk0 = 0;
        temp_s1->unk1A = -1;
        temp_s1->unk21 = 0;
        func_80659620(&temp_s1->unkC, &temp_s1->unk10, &temp_s1->unk14, 0);
    }

    for (i = 0; i < D_807FBDC4; i++) {
        temp_s0 = D_807FBB70.unk278[i];
        switch (D_807FBB70.unk258[i]) {
        case 0xFF:
            temp_s1->unk1E = 0;
            temp_s1->unk0 = 0xFF;
            break;
        case 0xF:
            func_80704AFC((f64)temp_s0[0] / 255.0, (f64)temp_s0[1] / 255.0, (f64)temp_s0[2] / 255.0);
            break;
        case 0xE:
            temp_s1->unkC = (f64)temp_s0[0] / 255.0;
            temp_s1->unk10 = (f64)temp_s0[1] / 255.0;
            temp_s1->unk14 = (f64)temp_s0[2] / 255.0;
            temp_s1->unk1A = temp_s0[3];
            break;
        case 0x10:
            temp_s1->unk1C = temp_s0[3];
            temp_s1->unk1E = temp_s1->unk1C;
            break;
        case 0x1:
            if ((D_8076A0A8 != 0x30) || !(D_807FD580->unk1F0 & 0x200000)) {
                temp_s1->unk0 = temp_s0[0];
                temp_s1->unk1A = temp_s0[1];
                temp_s1->unk4 = (f64)(f32)temp_s0[2] / 100.0;
                temp_s1->unk8 = temp_s0[3];
            }
            break;
        case 0x2:
            if ((D_8076A0A8 != 0x30) || !(D_807FD580->unk1F0 & 0x200000)) {
                temp_s1->unk0 = 0xFF;
            }
            break;
        case 0x3:
            if (!(D_807FBB60 & 0x400)) {
                if (temp_s0[2] != 0) {
                    func_8070B308(2);
                    func_805FF158(0);
                }
                temp_a0 = temp_s0[0];
                if (temp_a0 == 0x11) {
                    if (func_8068ABE0(temp_a0) == 0) {
                        func_805FF378(temp_s0[0], temp_s0[1]);
                    }
                } else {
                    func_805FF378(temp_a0, temp_s0[1]);
                }
                func_806F3BEC(D_807FBB4C, D_807FDCB8, D_807FDCBC, 0x46);
            }
            break;
        case 0x15:
            if (!(D_807FBB60 & 0x400)) {
                func_805FF4D8(temp_s0[0], temp_s0[1]);
            }
            break;
        case 0x4:
            if (!(D_807FBB60 & 0x400)) {
                temp_v0_2 = temp_s0[2];
                if (temp_v0_2 != 0) {
                    if (temp_v0_2 == 1) {
                        func_8070B308(2);
                    }
                    func_805FF158(0);
                }
                func_805FF9AC(temp_s0[0], temp_s0[1], 0, 0);
                func_806F3BEC(D_807FBB4C, D_807FDCB8, D_807FDCBC, 0x46);
            }
            break;
        case 0x5:
            if (!(D_807FBB60 & 0x400)) {
                func_805FF628(temp_s0[0], temp_s0[1]);
                func_806F3BEC(D_807FBB4C, D_807FDCB8, D_807FDCBC, 0x46);
            }
            break;
        case 0x6:
            D_807FD580->unk100 = 1;
            func_806C92C4(temp_s0[0]);
            break;
        case 0x7:
            if (!(D_807FBB60 & 0x400)) {
                func_805FF9AC(temp_s0[0], temp_s0[1], temp_s0[2], 2);
                func_806F3BEC(D_807FBB4C, D_807FDCB8, D_807FDCBC, 0x46);
            }
            break;
        case 0x8:
            if (!(D_807FBB60 & 0x400)) {
                func_805FF898();
                func_806F3BEC(D_807FBB4C, D_807FDCB8, D_807FDCBC, 0x46);
            }
            break;
        case 0x19:
            func_805FF8F8();
            break;
        case 0x9:
            func_805FF660(((u8 *)temp_s0)[1]);
            break;
        case 0xA:
            ((R2F4B_Actor174_Player *)((R2F4B_FC924 *)D_807FC924)->unk4->unk174)->unk1F0 |= 0x40000800;
            break;
        case 0xB:
            func_805FF378(D_80744700[func_805FF030(D_8076A0AB, 0)], D_8076A0AC);
            func_806F3BEC(D_807FBB4C, D_807FDCB8, D_807FDCBC, 0x46);
            break;
        case 0xC:
            if (temp_s0[1] != 0) {
                var_v0 = 0;
            } else {
                var_v0 = 0x8000;
            }
            func_806F397C(D_807FBB4C, 0, temp_s0[0] + var_v0, 0);
            break;
        case 0xD:
            if (((Actor *)D_807FBB4C)->unkB8 > 250.0f) {
                func_80608528(D_807FBB4C, temp_s0[0], 0xFF, 0x7F, 0x1E);
            }
            break;
        case 0x16:
            func_80602A94(temp_s0[0], 1.0f);
            break;
        case 0x17:
            func_80602B60(temp_s0[0], 0);
            break;
        case 0x11:
            ((R2F4B_Actor_BB48 *)D_807FBB48)->unkC4 = (f64)temp_s0[0] / 10.0;
            break;
        case 0x12:
            D_807FBB48->unk6A |= 0x200;
            break;
        case 0x13:
            D_807FBB48->unk6A &= ~0x200;
            break;
        case 0x14:
            D_807FC621 = temp_s0[0];
            D_807FC622 = temp_s0[1];
            if (D_807FC622 != 0) {
                func_807215AC(0x35, 0x18, 0x28);
                func_80721560(0x320, 0x82, 0, 0x64, 0x64, 0x64);
            }
            break;
        case 0x18:
            func_80600044(func_805FF030(D_8076A0AB, 0));
            break;
        case 0x1C:
            D_8076A0A6 = D_807ECD48;
            break;
        case 0x1A:
            ((R2F4B_Actor174_Player *)((R2F4B_FC924 *)D_807FC924)->unk4->unk174)->unk1F0 |= 0x80000000;
            break;
        case 0x1B:
            func_80653F68(temp_s0[1]);
            break;
        }
    }

    if (temp_s1->unk1E != 0) {
        temp_s1->unk1E--;
        func_80659F7C(temp_s1->unkC, temp_s1->unk10, temp_s1->unk14, (f32)temp_s1->unk1E / (f32)temp_s1->unk1C, temp_s1->unk1A);
        if (temp_s1->unk1E == 0) {
            func_80659DB0(temp_s1->unkC, temp_s1->unk10, temp_s1->unk14, temp_s1->unk1A);
        }
    }

    switch (temp_s1->unk0) {
    case 0x6:
        func_80711BD0(temp_s1->unk4, temp_s1->unk8, temp_s1->unk1A, 4);
        break;
    case 0x7:
        func_80711BD0(temp_s1->unk4, temp_s1->unk8, temp_s1->unk1A, 5);
        break;
    case 0x5:
        func_80711BD0(temp_s1->unk4, temp_s1->unk8, temp_s1->unk1A, 3);
        break;
    case 0x1:
        func_80711950(temp_s1->unk4, temp_s1->unk8, temp_s1->unk1A);
        break;
    case 0x4:
        func_80711F90(temp_s1->unk4, temp_s1->unk8, 1.0f, temp_s1->unk1A, 4.0f);
        break;
    case 0x3:
        if (((func_80611A44() >> 15) % 50) == 15) {
            D_807FC620 = 1;
        }
        /* fallthrough */
    case 0x2:
        if (temp_s1->unk21 != 0) {
            temp_s1->unk21--;
        }
        if (D_807FC620 != 0) {
            temp_s1->unk18 = 0x28;
            D_807FC620 = 0;
        }
        if (temp_s1->unk18 != 0) {
            if ((temp_s1->unk18 == 0x28) || (((func_80611A44() >> 15) % 10) == 5)) {
                func_80659670(1.0f, 1.0f, 1.0f, temp_s1->unk1A);
                if ((D_80750190 == 0) && (temp_s1->unk21 == 0)) {
                    var_s0 = 0x46;
                    if (D_8076A0A8 == 0x57) {
                        var_s0 = 0x2D;
                    }
                    func_80608DA8(0x9C, (u8)var_s0, 0x7F, 0x1E, (func_80611A44() >> 15) % 3);
                    if (D_8076A0A8 == 0x6F) {
                        temp_s1->unk21 = 0x50;
                    } else {
                        temp_s1->unk21 = 0x32;
                    }
                }
                temp_s1->unk1E = (temp_s1->unk1E >= 5) ? temp_s1->unk1E : 4;
                temp_s1->unk1C = temp_s1->unk1E;
            }
            temp_s1->unk18--;
        }
        func_80711410(temp_s1->unk4, temp_s1->unk8, 1.0f, temp_s1->unk1A, 1.0f);
        break;
    case 0xFF:
        if (func_807122B4() != 0) {
            temp_s1->unk0 = 0;
        }
        break;
    }

    func_8066466C();
    func_80664D20();
    D_807FC621 |= 0x80;
}

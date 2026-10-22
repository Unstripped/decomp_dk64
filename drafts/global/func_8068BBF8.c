// func_8068BBF8 (src/global/8F4B0.c): sparse switch with jtbl_80759EE8 and late_rodata floats; held back by func_8068AD7C asm rodata alignment
void func_80609140(s32, s32, f32, f32, s32, s32);
f32 func_80612794(s16);
void func_8061DBD4(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
s16 func_80665DE0(f32, f32, f32, f32);
f32 func_80665E48(f32, f32, void *, void **, f32, f32);
void func_806C9D20(f32, f32, u8);
extern u8 D_807444EC;
extern s32 D_8076A0A8;
extern Actor *D_807FBB40;
extern Actor *D_807FBB4C;
extern s16 D_807FC624;
extern void *D_807FC924;

void func_8068BBF8(void) {
    void *sp54;
    s16 sp52;
    s16 sp4E;
    f32 sp48;
    f32 sp40;
    f32 sp3C;
    s16 sp3A;
    void *sp34;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 var_fv1;
    s16 temp_a0_3;
    s16 temp_v0;
    s16 temp_v0_2;
    s16 temp_v1_3;
    s16 var_v1;
    s16 var_v1_2;
    u8 temp_v1_2;
    void *temp_a0;
    Actor *temp_a0_2;
    void *temp_v1;

    temp_a0 = D_807FBB40->unk174;
    sp4E = 0;
    sp3A = 0x1E;
    sp40 = 0.08f;
    sp3C = 8.0f;
    temp_v1 = (void *)((*(u8 *)((u8 *)temp_a0 + 0xFB) * 0x2F0) + (u8 *)D_807FC924);
    *(s16 *)((u8 *)temp_v1 + 0x2CC) = D_807FBB40->unkEC;
    D_807FBB40->unkEC = D_807FBB40->unkE4;
    *(s16 *)((u8 *)temp_v1 + 0x2CA) = (s16)(s32)*(f32 *)((u8 *)temp_v1 + 0x214);
    sp34 = temp_v1;
    sp54 = temp_a0;
    sp48 = func_80665E48(*(f32 *)((u8 *)temp_v1 + 0x218), *(f32 *)((u8 *)temp_v1 + 0x210), temp_a0, &D_807FBB40, *(f32 *)((u8 *)temp_v1 + 0x230), *(f32 *)((u8 *)temp_v1 + 0x228));
    temp_fv1 = *(f32 *)((u8 *)temp_v1 + 0x230) - *(f32 *)((u8 *)temp_v1 + 0x218);
    temp_fa1 = *(f32 *)((u8 *)temp_v1 + 0x228) - *(f32 *)((u8 *)temp_v1 + 0x210);
    temp_fa0 = func_80665E48(0.0f, *(f32 *)((u8 *)temp_v1 + 0x214), (void *)sqrtf((temp_fv1 * temp_fv1) + (temp_fa1 * temp_fa1)), *(void **)((u8 *)temp_v1 + 0x22C), 0.0f, 0.0f) + 3.1415927f;
    var_fv1 = temp_fa0;
    if (temp_fa0 > 6.2831855f) {
        var_fv1 = temp_fa0 - 6.2831855f;
    }
    if (var_fv1 > 3.1415927f) {
        var_fv1 = 3.1415927f - (var_fv1 - 3.1415927f);
    }
    *(f32 *)((u8 *)temp_v1 + 0x2D4) = 6.2831855f - sp48;
    *(f32 *)((u8 *)temp_v1 + 0x2D8) = 6.2831855f - var_fv1;
    sp34 = temp_v1;
    func_806C9D20(temp_fa0, 3.1415927f, *(u8 *)((u8 *)sp54 + 0xFB));
    sp52 = func_80665DE0(*(f32 *)((u8 *)temp_v1 + 0x210), *(f32 *)((u8 *)temp_v1 + 0x218), *(f32 *)((u8 *)temp_v1 + 0x228), *(f32 *)((u8 *)temp_v1 + 0x230));
    func_8061DBD4(D_807FBB40, (u8 *)temp_v1 + 0x210, (u8 *)temp_v1 + 0x214, (u8 *)temp_v1 + 0x218, (u8 *)temp_v1 + 0x228, (u8 *)temp_v1 + 0x22C, (u8 *)temp_v1 + 0x230, (u8 *)temp_v1 + 0x240, (u8 *)temp_v1 + 0x244, (u8 *)temp_v1 + 0x248);
    temp_v0 = func_80665DE0(*(f32 *)((u8 *)temp_v1 + 0x210), *(f32 *)((u8 *)temp_v1 + 0x218), *(f32 *)((u8 *)temp_v1 + 0x228), *(f32 *)((u8 *)temp_v1 + 0x230));
    temp_a0_2 = *(Actor **)sp54;
    if (D_807FBB4C == temp_a0_2) {
        if ((D_8076A0A8 == 0x1F) || (D_8076A0A8 == 0x33)) {
            D_807FBB40->unkE4 = (s16)(s32)(func_80612794(D_807FC624) * 100.0f);
            if (D_8076A0A8 == 0x1F) {
                temp_a0_3 = D_807FC624;
                if (temp_a0_3 < 0x1E) {
                    func_80609140(0x15, 0x7FFF, 64.0f, 1.0f, 10, 128);
                }
                if ((temp_a0_3 >= 0x800) && (temp_a0_3 < 0x81E)) {
                    func_80609140(0x14, 0x7FFF, 64.0f, 1.0f, 10, 128);
                }
            }
            D_807FC624 = (D_807FC624 + 0x1E) & 0xFFF;
            return;
        }
        if (D_807444EC != 1) {
            temp_v1_2 = temp_a0_2->unk154;
            switch ((s32)temp_v1_2) {
            case 0x63:
                sp40 = 0.02f;
                sp3C = 15.0f;
            case 0x4F:
            case 0x69:
            case 0x6D:
block_29:
                temp_v1_3 = sp52 - temp_v0;
                if (temp_v1_3 >= 0x801) {
                    sp4E = temp_v1_3 - 0x1000;
                } else {
                    sp4E = temp_v1_3;
                    if (temp_v1_3 < -0x800) {
                        sp4E = temp_v1_3 + 0x1000;
                    }
                }
                break;
            case 0x7:
            case 0x8:
            case 0x9:
            case 0xA:
            case 0xB:
            case 0xF:
            case 0x10:
            case 0x11:
            case 0x12:
            case 0x13:
            case 0x14:
                sp3A = 0x64;
                sp40 = 0.1f;
                goto block_29;
            }
            temp_v0_2 = -sp3A;
            var_v1 = temp_v0_2;
            if (temp_v0_2 < sp4E) {
                var_v1 = sp4E;
            }
            var_v1_2 = sp3A;
            if (var_v1 < sp3A) {
                if (temp_v0_2 < sp4E) {
                    var_v1_2 = sp4E;
                } else {
                    var_v1_2 = temp_v0_2;
                }
            }
            temp_fv0 = (f32)D_807FBB40->unkE4;
            D_807FBB40->unkE4 = (s16)(s32)(((((f32)var_v1_2 * sp3C) - temp_fv0) * sp40) + temp_fv0);
        }
    }
}

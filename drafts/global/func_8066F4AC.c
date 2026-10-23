// func_8066F4AC (src/global/70FD0.c): actor collision detection loop against 0x90-byte global entities, unk8C child nodes and func_80673708 tests
void func_8066C8B0(s32, s32, s32, s32, f32, f32, f32, f32, f32);
void func_8066F84C(s32, void *, s32);
void func_806713E4(void *, s32);
void func_80671880(void *, s32);
s32 func_80673708(s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_80674ADC(s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_806D0964(s32, u8);
extern s32 D_80747D70;
extern s32 D_8076A064;
extern s32 D_807F6000;
extern s8 D_807FB548;
extern u8 D_807FB5FD;
extern u8 D_807FB5FF;
extern s8 D_807FB600;
extern u8 D_807FB601;
extern u8 D_807FB602;
extern u8 D_807FB61C;

u8 func_8066F4AC(M70D_Actor *arg0, s32 arg1, s32 arg2) {
    u8 sp77;
    s32 sp64;
    void *sp60;
    u8 sp5F;
    s32 temp_a3;
    s32 var_s1_2;
    s32 var_s6;
    s32 var_v1;
    u8 var_s1;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v1;
    void *temp_v1_2;
    void *temp_v1_3;
    void *var_s0;
    void *var_v0;

    sp77 = 0;
    var_v0 = arg0->unk140;
    ((M70D_ActorSub140 *)var_v0)->unk0 = 0; // unk6C
    D_807FB548 = 0;
    var_v1 = 0;
    if (D_80747D70 > 0) {
        var_s6 = 0;
        do {
            sp60 = var_v0;
            sp64 = var_v1;
            temp_s2 = (void *)(var_s6 + D_807F6000);
            temp_s2_2 = (void *)((u8 *)temp_s2 + 0x28);
            if (*((u8 *)temp_s2 + 0x3D) & 2) {
                sp64 = var_v1;
                sp60 = var_v0;
                if (func_80674ADC(*(s32 *)var_v0, *(s32 *)((u8 *)var_v0 + 4), *(s32 *)((u8 *)var_v0 + 8), *(s32 *)((u8 *)var_v0 + 0xC), *(s32 *)((u8 *)temp_s2 + 0x28), *(s32 *)((u8 *)temp_s2_2 + 4), *(s32 *)((u8 *)temp_s2_2 + 8), *(s32 *)((u8 *)temp_s2_2 + 0xC)) != 0) {
                    if (!(*((u8 *)temp_s2_2 + 0x15) & 1)) {
                        temp_v0 = (void *)(D_807F6000 + var_s6);
                        func_8066C8B0(sp64, *(s32 *)((u8 *)temp_v0 + 0x24), *(s32 *)temp_v0, *(s32 *)((u8 *)temp_v0 + 4), *(f32 *)((u8 *)temp_v0 + 8), *(f32 *)((u8 *)temp_v0 + 0x10), *(f32 *)((u8 *)temp_v0 + 0x14), *(f32 *)((u8 *)temp_v0 + 0x18), *(f32 *)((u8 *)temp_v0 + 0xC));
                    } else {
                        *(s32 *)((u8 *)temp_s2_2 + 0x10) = D_8076A064;
                    }
                    if (!(arg0->unk5C & 1) || (func_806D0964(**(s32 **)((u8 *)D_807F6000 + var_s6 + 0x24), arg0->unk174->unk1A4) == 0)) {
                        var_s1 = 1;
                        func_80671880(arg0, 0);
                        var_s0 = *(void **)((u8 *)sp60 + 0x8C);
                        D_807FB5FD = 0;
                        sp5F = D_807FB602;
                        temp_v0_2 = (void *)(D_807F6000 + var_s6);
                        temp_v1 = *(void **)((u8 *)temp_v0_2 + 0x7C);
                        if (temp_v1 != NULL) {
                            if (*((u8 *)temp_v1 + 0x6F) != 0) {
                                D_807FB5FD = 1;
                                D_807FB600 = 0;
                            }
                            var_s1 = *((u8 *)*(void **)((u8 *)temp_v0_2 + 0x7C) + 0x70);
                        }
                        if (((D_807FB5FD == 0) || (arg0->unk144 & 0x10)) && (var_s1 != 0)) {
                            D_807FB5FF = 0;
                            var_s1_2 = 0;
                            if (var_s0 != NULL) {
loop_18:
                                if (*((u8 *)var_s0 + 0x26) != 0) {
                                    temp_a3 = *(s32 *)((u8 *)var_s0 + 0x1C);
                                    if ((temp_a3 != 0) && !(*((u8 *)var_s0 + 0x27) & 6)) {
                                        var_s1_2 = (var_s1_2 | func_80673708(*(s32 *)((u8 *)var_s0 + 0x10), *(s32 *)((u8 *)var_s0 + 0x14), *(s32 *)((u8 *)var_s0 + 0x18), temp_a3, *(s32 *)((u8 *)temp_s2_2 + 0x18), *(s32 *)((u8 *)temp_s2_2 + 0x1C), arg1, arg2)) & 0xFF;
                                    }
                                }
                                var_s0 = *(void **)((u8 *)var_s0 + 0x28);
                                if ((var_s0 != NULL) && (D_807FB5FF == 0)) {
                                    goto loop_18;
                                }
                            }
                            sp77 |= var_s1_2;
                            if (D_807FB601 != 0) {
                                temp_v1_2 = *(void **)((u8 *)D_807F6000 + var_s6 + 0x7C);
                                if (temp_v1_2 != NULL) {
                                    *((u8 *)temp_v1_2 + 0x5C) = D_807FB601;
                                    *(s16 *)((u8 *)*(void **)((u8 *)D_807F6000 + var_s6 + 0x7C) + 0x5E) = arg0->unk58;
                                }
                            }
                            if (D_807FB5FF != 0) {
                                func_8066F84C(sp64, arg0, *(s32 *)((u8 *)temp_s2_2 + 0x18));
                            }
                            temp_v1_3 = *(void **)((u8 *)D_807F6000 + var_s6 + 0x7C);
                            if ((temp_v1_3 != NULL) && (*((u8 *)temp_v1_3 + 0x6E) == 0)) {
                                D_807FB602 = sp5F;
                            }
                            if ((var_s1_2 != 0) && (D_807FB5FD == 0) && (D_807FB61C != 0)) {
                                func_806713E4(arg0, 0);
                            }
                        }
                    }
                }
            }
            var_v1 = sp64 + 1;
            var_s6 += 0x90;
            var_v0 = sp60;
        } while (var_v1 < D_80747D70);
    }
    return sp77;
}

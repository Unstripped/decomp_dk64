#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB44;
extern Actor *D_807FBB48;
extern Actor *D_807FBB4C;
extern ActorGlobalState D_807FBB70;
extern u8 D_807FC928;
extern u8 D_807FC929;
extern Struct807FD580 *D_807FD580;
extern s16 D_807FD584;
extern u16 D_807FD63C;

typedef struct G21Actor1A0 {
    /* 0x00 */ u8 pad0[0x8C];
    /* 0x8C */ u8 unk8C;
    /* 0x8D */ u8 pad8D[0x1A3 - 0x8D];
    /* 0x1A3 */ u8 unk1A3;
    /* 0x1A4 */ u8 unk1A4;
} G21Actor1A0;

void func_80614E78(void *, s32);
s32 func_806F8AD4(s32, s32);
void func_806F8BC4(s32, s32, s32);

void func_806DF390(s32 arg0, G21Actor1A0 *arg1, u8 arg2) {
    s32 id;

    id = 0x4A;
    if (arg2) {
        id = 0x4C;
    }
    arg1->unk1A3 = 0;
    func_80614E78((void *)arg0, id);
}

void func_806DF3D0(s32 arg0, G21Actor1A0 *arg1, u8 arg2) {
    s32 id;
    s32 a;

    id = 0x4B;
    a = 2;
    if (func_806F8AD4(3, arg1->unk1A4)) {
        a = 3;
    }
    func_806F8BC4(a, 0, 0);
    if (arg2) {
        id = 0x4D;
    }
    func_80614E78((void *)arg0, id);
}

void func_806DF44C(s32 arg0, G21Actor1A0 *arg1, u8 arg2) {
    if (arg1->unk8C) {
        func_806DF390(arg0, arg1, arg2);
    } else {
        func_806DF3D0(arg0, arg1, arg2);
    }
}

void func_806DF494(s16 *arg0, s16 arg1, s16 arg2) {
    s16 temp_v0;
    s16 var_a2;
    s32 var_t0;
    s16 step;

    arg1 &= 0xFFF;
    temp_v0 = arg1 - *arg0;
    if (temp_v0 != 0) {
        if (temp_v0 > 0) {
            var_a2 = temp_v0;
        } else {
            var_a2 = -temp_v0;
        }
        step = arg2;
        temp_v0 = temp_v0 / var_a2;
        if (var_a2 > 0x800) {
            var_a2 = 0x1000 - var_a2;
            temp_v0 = temp_v0 * -1;
        }
        if (step > 0) {
            var_t0 = step;
        } else {
            var_t0 = -step;
        }
        if (var_a2 < var_t0) {
            *arg0 = arg1;
            return;
        }
        *arg0 = *arg0 + (temp_v0 * step);
        *arg0 &= 0xFFF;
    }
}

void func_806DF5A0(s16 *arg0, s16 arg1, s16 arg2, s16 arg3) {
    s16 temp_v0;
    s16 var_a2;

    arg1 = arg1 & 0xFFF;
    temp_v0 = arg1 - *arg0;
    if (temp_v0 != 0) {
        if (temp_v0 > 0) {
            var_a2 = temp_v0;
        } else {
            var_a2 = -temp_v0;
        }
        temp_v0 = temp_v0 & 0xFFF;
        if (var_a2 > 0x800) {
            var_a2 = 0x1000 - var_a2;
        }
        if (arg2 >= var_a2) {
            *arg0 = arg1;
        } else if (arg3 < temp_v0) {
            *arg0 = *arg0 - arg2;
        } else {
            *arg0 = *arg0 + arg2;
        }
        *arg0 &= 0xFFF;
    }
}

void func_806DF670(s16 *arg0, s16 arg1, s16 arg2) {
    s16 temp_v0;

    temp_v0 = arg1 - *arg0;
    if (temp_v0 != 0) {
        if (((s16) (temp_v0 & 0xFFF) + arg2) >= 0x1000) {
            *arg0 = arg1;
            return;
        }
        *arg0 = (*arg0 + arg2) & 0xFFF;
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806DF6D4.s")

#ifdef NON_MATCHING
u16 func_806DFF34(u16 arg0, u16 *arg1) {
    u16 var_v0;
    u16 var_v1;
    u16 var_a2;

    var_v0 = *arg1;
    var_v1 = 0;
    var_a2 = 0;
    if (var_v0 != 0) {
        do {
            var_v1 |= var_v0;
            arg1++;
            if (var_v0 & arg0) {
                var_a2 |= arg1[0];
            }
            var_v0 = arg1[1];
            arg1++;
        } while (var_v0 != 0);
    }
    return var_a2 | (arg0 & ~var_v1);
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806DFF34.s")
#endif

f32 func_80612790(s16);

f32 func_806DFFA0(f32 arg0, s16 arg1, s16 arg2) {
    return func_80612790(arg2 - arg1) * arg0;
}

typedef struct G21Player {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ f32 unk4;
    /* 0x008 */ u8 pad8[2];
    /* 0x00A */ s16 unkA;
    /* 0x00C */ u8 padC[0x28];
    /* 0x034 */ f32 unk34;
    /* 0x038 */ f32 unk38;
    /* 0x03C */ u8 pad3C[0xC];
    /* 0x048 */ s16 unk48;
    /* 0x04A */ u8 pad4A[0x7E];
    /* 0x0C8 */ s16 unkC8;
    /* 0x0CA */ u8 padCA[0xC];
    /* 0x0D6 */ s16 unkD6;
    /* 0x0D8 */ u8 padD8[0x11C];
    /* 0x1F4 */ s32 unk1F4;
} G21Player;

#define G21_PLAYER ((G21Player *)D_807FD580)

void func_806DFFDC(s16 arg0) {
    f32 temp;

    temp = func_806DFFA0(G21_PLAYER->unk4, G21_PLAYER->unkA, arg0);
    if (temp > 0.0f) {
        G21_PLAYER->unk4 = temp;
    } else {
        G21_PLAYER->unk4 = 0.0f;
    }
    G21_PLAYER->unkA = arg0;
}

void func_806E0050(void) {
    G21_PLAYER->unk4 = 0.0f;
    G21_PLAYER->unkA = D_807FBB40->unkE6;
}

typedef struct G21Table {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ u8 pad10[0x18];
    /* 0x28 */ s16 unk28;
    /* 0x2A */ u16 unk2A;
    /* 0x2C */ u16 unk2C;
    /* 0x2E */ s8 unk2E;
    /* 0x2F */ s8 unk2F;
    /* 0x30 */ u8 unk30;
    /* 0x31 */ u8 pad31[3];
} G21Table; // size = 0x34

extern G21Table D_807FD610[];

void func_806E007C(void) {
    f32 temp_fv1;
    f32 var_fv0;
    G21Table *temp_v1;

    var_fv0 = G21_PLAYER->unk38;
    if (G21_PLAYER->unkC8 == 0) {
        var_fv0 = var_fv0 * 0.5;
    }
    if (G21_PLAYER->unkD6 != 0) {
        var_fv0 = var_fv0 * 0.5;
    }
    temp_v1 = &D_807FD610[D_807FC929];
    if ((temp_v1->unk4 != 0.0f) && !(G21_PLAYER->unk1F4 & 8)) {
        temp_fv1 = G21_PLAYER->unk34;
        G21_PLAYER->unk4 = (temp_v1->unk8 * (var_fv0 - temp_fv1)) + temp_fv1;
        G21_PLAYER->unkA = D_807FD610[D_807FC929].unk28;
        return;
    }
    G21_PLAYER->unk4 = 0.0f;
    G21_PLAYER->unkA = D_807FBB40->unkE6;
}

typedef struct G21ActorEE {
    /* 0x00 */ u8 pad0[0xD8];
    /* 0xD8 */ s16 unkD8;
    /* 0xDA */ s16 unkDA;
    /* 0xDC */ u8 padDC[0xA];
    /* 0xE6 */ s16 unkE6;
    /* 0xE8 */ u8 padE8[2];
    /* 0xEA */ s16 unkEA;
    /* 0xEC */ u8 padEC[2];
    /* 0xEE */ s16 unkEE;
} G21ActorEE;

#define G21_ACTOR_EE ((G21ActorEE *)D_807FBB40)

extern u8 D_807FD618[];

void func_806E0178(void) {
    f32 var_fv0;
    f32 var_fv1;
    s32 temp_v0;

    func_806E007C();
    var_fv1 = *(f32 *)(D_807FD618 + D_807FC929 * 0x34);
    if ((f64)var_fv1 < 0.3) {
        var_fv1 = 0.3f;
    }
    temp_v0 = G21_ACTOR_EE->unkEE - G21_PLAYER->unkA;
    if (temp_v0 > 0) {
        var_fv0 = (f32)temp_v0;
    } else {
        var_fv0 = (f32)-temp_v0;
    }
    if (var_fv0 > 2048.0f) {
        var_fv0 = 4096.0f - var_fv0;
    }
    if (var_fv0 > 400.0f) {
        var_fv0 = 400.0f;
    }
    var_fv0 = var_fv0 * 0.2;
    func_806DF494(&G21_ACTOR_EE->unkEE, G21_PLAYER->unkA, (s16)(s32)(var_fv0 * var_fv1));
}

void func_806E0294(void) {
    f32 var_fv0;
    f32 var_fv1;
    s32 temp_v0;

    func_806E007C();
    var_fv1 = *(f32 *)(D_807FD618 + D_807FC929 * 0x34);
    if ((f64)var_fv1 < 0.3) {
        var_fv1 = 0.3f;
    }
    temp_v0 = G21_ACTOR_EE->unkEE - G21_PLAYER->unkA;
    if (temp_v0 > 0) {
        var_fv0 = (f32)temp_v0;
    } else {
        var_fv0 = (f32)-temp_v0;
    }
    if (var_fv0 > 2048.0f) {
        var_fv0 = 4096.0f - var_fv0;
    }
    if (var_fv0 > 400.0f) {
        var_fv0 = 400.0f;
    }
    var_fv0 = var_fv0 * ((f64)G21_PLAYER->unk48 / 400.0);
    func_806DF494(&D_807FBB40->unkE6, G21_PLAYER->unkA, (s16)(s32)(var_fv0 * var_fv1));
}

extern u8 D_807FD640[];

f32 func_806E03C8(f32 arg0, f32 arg1) {
    f32 var_fv1;
    u8 temp_v0;

    temp_v0 = D_807FD640[D_807FC929 * 0x34];
    if (temp_v0 != 0) {
        temp_v0 = D_807FD640[D_807FC929 * 0x34];
        if (temp_v0 >= 0x47) {
            var_fv1 = 70.0f;
        } else {
            var_fv1 = (s32)temp_v0;
        }
        var_fv1 -= 2.0f;
        var_fv1 /= 68.0f;
        return ((arg1 - arg0) * var_fv1) + arg0;
    }
    return 0.0f;
}

extern u8 D_807FD641[];

f32 func_806E0454(f32 arg0, f32 arg1) {
    f32 var_fv1;
    u8 temp_v0;

    temp_v0 = D_807FD641[D_807FC929 * 0x34];
    if (temp_v0 != 0) {
        temp_v0 = D_807FD641[D_807FC929 * 0x34];
        if (temp_v0 >= 0x47) {
            var_fv1 = 70.0f;
        } else {
            var_fv1 = (s32)temp_v0;
        }
        var_fv1 -= 2.0f;
        var_fv1 /= 68.0f;
        return ((arg1 - arg0) * var_fv1) + arg0;
    }
    return 0.0f;
}

void func_806E04E0(void) {
    f32 temp_fv0;
    f32 var_fv0;
    f32 var_fv1;
    s32 temp_v0;
    G21Table *temp_v1;

    func_806E007C();
    temp_v1 = &D_807FD610[D_807FC929];
    temp_fv0 = temp_v1->unkC;
    if (temp_fv0 > 0.0f) {
        var_fv1 = temp_fv0;
    } else {
        var_fv1 = -temp_fv0;
    }
    if (var_fv1 < 14.0f) {
        var_fv1 = (temp_v1->unk8 * 0.7) + 0.3;
        temp_v0 = D_807FBB40->unkE6 - G21_PLAYER->unkA;
        if (temp_v0 > 0) {
            var_fv0 = (f32)temp_v0;
        } else {
            var_fv0 = (f32)-temp_v0;
        }
        if (var_fv0 > 2048.0f) {
            var_fv0 = 4096.0f - var_fv0;
        }
        if (var_fv0 > 400.0f) {
            var_fv0 = 400.0f;
        }
        var_fv0 = var_fv0 * ((f64)G21_PLAYER->unk48 / 400.0);
        func_806DF494(&D_807FBB40->unkE6, G21_PLAYER->unkA, (s16)(s32)(var_fv0 * var_fv1));
    }
}

void func_806E0654(void) {
    func_806E007C();
    func_806DF494(&D_807FBB40->unkE6, G21_ACTOR_EE->unkEA, G21_PLAYER->unk48);
}

void func_806E0694(void) {
    func_806E007C();
    func_806DF494(&D_807FBB40->unkE6, G21_PLAYER->unkA, G21_PLAYER->unk48);
    G21_PLAYER->unk4 = 0.0f;
}

void func_806E06E8(void) {
    s16 var_a1;

    if (G21_ACTOR_EE->unkDA < 0x3C7) {
        var_a1 = G21_ACTOR_EE->unkD8 + 0x800;
    } else {
        var_a1 = G21_ACTOR_EE->unkEE + 0x800;
    }
    func_806DF494(&D_807FBB40->unkE6, var_a1, G21_PLAYER->unk48 / 4);
    G21_PLAYER->unk4 = 0.0f;
}

void func_806E077C(void) {
    s16 var_a1;

    if (G21_ACTOR_EE->unkDA < 0x3C7) {
        var_a1 = G21_ACTOR_EE->unkD8;
    } else {
        var_a1 = G21_ACTOR_EE->unkEE;
    }
    func_806DF494(&D_807FBB40->unkE6, var_a1, G21_PLAYER->unk48 / 4);
    G21_PLAYER->unk4 = 0.0f;
}

typedef struct G29StickX {
    s8 unk0;
    u8 pad1[0x33];
} G29StickX;

extern G29StickX D_807FD63E[];
extern s8 D_807FD63F;

typedef struct G22Main {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ f32 unk4;
    /* 0x008 */ s16 unk8;
    /* 0x00A */ s16 unkA;
    /* 0x00C */ u8 pad0C[0x2C];
    /* 0x038 */ f32 unk38;
    /* 0x03C */ u8 pad3C[0xC];
    /* 0x048 */ s16 unk48;
    /* 0x04A */ u8 pad4A[0x152];
    /* 0x19C */ s16 unk19C;
    /* 0x19E */ s16 unk19E;
    /* 0x1A0 */ s16 unk1A0;
} G22Main;

typedef struct G22Sub4b {
    /* 0x00 */ u8 pad0[0x10];
    /* 0x10 */ s16 unk10;
} G22Sub4b;

typedef struct G22Sub4 {
    /* 0x00 */ G22Sub4b *unk0;
    /* 0x04 */ u8 pad4[0x60];
    /* 0x64 */ u16 unk64;
} G22Sub4;

typedef struct G22Act {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ G22Sub4 *unk4;
    /* 0x008 */ u8 pad8[0x50];
    /* 0x058 */ s32 unk58;
    /* 0x05C */ u8 pad5C[0x5C];
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ u8 padBC[0x2A];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 padE8[6];
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ u8 padF0[0x64];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
} G22Act;

#define G22_M ((G22Main *)D_807FD580)
#define G22_A ((G22Act *)D_807FBB40)

extern f32 D_80753BA4[];
extern f32 D_80753BC0[];
extern f32 D_80753BDC[];
extern f32 D_80753BF8[];
extern f32 D_80753DC8[];
extern f32 D_80753DE4[];
extern u16 *D_807FBB54;
void func_80614EBC(void *, s32);
void func_80614D00(void *, f32, f32);
void func_8072FE60(f32);
s16 func_806CC14C(s16, s16);
void func_806E1630(void);

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E07F8.s")

void func_806E0BEC(void) {
    f32 var_fv0;
    f32 var_fv1;
    s32 temp_v0;

    func_806E007C();
    if (G22_M->unk4 != 0.0f) {
        var_fv1 = *(f32 *)(D_807FD618 + D_807FC929 * 0x34);
        var_fv1 = var_fv1 * var_fv1;
        if ((f64)var_fv1 < 0.2) {
            var_fv1 = 0.2f;
        }
        temp_v0 = D_807FBB40->unkE6 - G22_M->unkA;
        if (temp_v0 > 0) {
            var_fv0 = (f32)temp_v0;
        } else {
            var_fv0 = (f32)-temp_v0;
        }
        if (var_fv0 > 2048.0f) {
            var_fv0 = 4096.0f - var_fv0;
        }
        if (var_fv0 > 400.0f) {
            var_fv0 = 400.0f;
        }
        var_fv0 = var_fv0 * ((f64)G22_M->unk48 / 400.0);
        func_806DF494(&D_807FBB40->unkE6, G22_M->unkA, (s16)(s32)(var_fv0 * var_fv1));
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E0D40.s")

void func_806E0FAC(void) {
    f32 var_fv0;
    f32 var_fv1;
    s16 temp_a1;
    u16 temp_a1_2;

    func_806E007C();
    if (G22_M->unk4 != 0.0f && !G22_A->unkB8) {
        var_fv1 = *(f32 *)(D_807FD618 + D_807FC929 * 0x34);
        var_fv1 = var_fv1 * var_fv1;
        if ((f64)var_fv1 < 0.2) {
            var_fv1 = 0.2f;
        }
        temp_a1 = G22_M->unkA;
        var_fv0 = (f32)(G22_A->unkE6 - temp_a1);
        if (var_fv0 >= 2048.0f) {
            var_fv0 -= 4096.0f;
        }
        if (var_fv0 <= -2048.0f) {
            var_fv0 += 4096.0f;
        }
        if (var_fv0 > 400.0f) {
            var_fv0 = 400.0f;
        }
        if (var_fv0 < -400.0f) {
            var_fv0 = -400.0f;
        }
        var_fv0 = (f32)((f64)var_fv0 * ((f64)G22_M->unk48 / 400.0));
        var_fv0 = var_fv0 * var_fv1;
        if (var_fv0 > 0.0f) {
            var_fv1 = var_fv0;
        } else {
            var_fv1 = -var_fv0;
        }
        func_806DF494(&G22_A->unkE6, temp_a1, (s16)(s32)var_fv1);
        if (var_fv0 != 0.0f) {
            if (G22_A->unk154 != 0x3C) {
                if (G22_A->unk154 == 0x62) {
                    temp_a1_2 = D_807FBB54[G22_A->unk58 + 0x23C];
                    if (G22_A->unk4->unk64 != temp_a1_2) {
                        func_80614EBC(D_807FBB40, temp_a1_2);
                    }
                    func_80614D00(D_807FBB40, (f32)((f64)var_fv0 / 80.0), 0.0f);
                }
            } else {
                temp_a1_2 = D_807FBB54[G22_A->unk58 + 0x52];
                if (G22_A->unk4->unk64 != temp_a1_2) {
                    func_80614EBC(D_807FBB40, temp_a1_2);
                }
                func_80614D00(D_807FBB40, (f32)((f64)var_fv0 / 80.0), 0.0f);
            }
        }
    } else {
        if (G22_A->unk154 != 0x3C) {
            if (G22_A->unk154 == 0x62) {
                temp_a1_2 = D_807FBB54[G22_A->unk58 + 0x243];
                if (G22_A->unk4->unk64 != temp_a1_2) {
                    func_80614EBC(D_807FBB40, temp_a1_2);
                }
            }
        } else if (G22_A->unk155 == 1) {
            temp_a1_2 = D_807FBB54[G22_A->unk58 + 0x4B];
            if (G22_A->unk4->unk64 != temp_a1_2) {
                func_80614EBC(D_807FBB40, temp_a1_2);
            }
        }
    }
    G22_M->unk4 = 0.0f;
}

void func_806E1334(void) {
    if (((s8 *)&D_807FD63F)[D_807FC929 * 0x34] < 0) {
        G22_M->unk4 = func_806E0454(D_80753BDC[D_807FD584], D_80753BF8[D_807FD584]);
    } else {
        G22_M->unk4 = func_806E0454(D_80753BA4[D_807FD584], D_80753BC0[D_807FD584]);
    }
    if (G22_M->unk4 != 0.0f) {
        G22_M->unk8 = G22_M->unk4 > 0.0f ? 1 : -1;
    } else {
        G22_M->unk8 = 0;
    }
    func_8072FE60(((s8 *)&D_807FD63F)[D_807FC929 * 0x34] / 80.0);
    D_807FBB40->unkE6 += D_807FD63E[D_807FC929].unk0;
    D_807FBB40->unkE6 &= 0xFFF;
    func_806E1630();
}

void func_806E14DC(void) {
    if (((s8 *)&D_807FD63F)[D_807FC929 * 0x34] < 0) {
        G22_M->unk4 = func_806E0454(D_80753BDC[D_807FD584], D_80753BF8[D_807FD584]);
    } else {
        G22_M->unk4 = func_806E0454(D_80753BA4[D_807FD584], D_80753BC0[D_807FD584]);
    }
    if (G22_M->unk4 != 0.0f) {
        G22_M->unk8 = G22_M->unk4 > 0.0f ? 1 : -1;
    } else {
        G22_M->unk8 = 0;
    }
    func_8072FE60(((s8 *)&D_807FD63F)[D_807FC929 * 0x34] / 80.0);
}

void func_806E1630(void) {
    s16 lo;
    s16 sp1C;
    s16 hi;
    s16 cur;
    s32 outside = 0;

    hi = G22_M->unk19E;
    lo = G22_M->unk19C;
    if (lo < hi) {
        cur = D_807FBB40->unkE6;
        if (cur < lo || hi < cur) {
            outside = 1;
        }
    } else {
        cur = D_807FBB40->unkE6;
        if (hi < cur && cur < lo) {
            outside = 1;
        }
    }
    if (outside) {
        sp1C = func_806CC14C(cur, lo);
        if (sp1C < func_806CC14C(D_807FBB40->unkE6, G22_M->unk19E)) {
            D_807FBB40->unkE6 = G22_M->unk19C;
        } else {
            D_807FBB40->unkE6 = G22_M->unk19E;
        }
    }
}

void func_806E1728(void) {
    f32 v = func_806E03C8(D_80753DC8[D_807FD584], D_80753DE4[D_807FD584]);

    if (D_807FD63E[D_807FC929].unk0 < 0) {
        G22_M->unk4 = -v;
        G22_M->unk8 = -1;
    } else {
        G22_M->unk4 = v;
        if (v != 0.0f) {
            G22_M->unk8 = 1;
        } else {
            G22_M->unk8 = 0;
        }
    }
}

void func_806E17F4(void) {
    func_806E007C();
    func_806DF494(&G21_ACTOR_EE->unkEE, G22_M->unkA, G22_M->unk48);
    func_806DF494(&D_807FBB40->unkE6, G21_ACTOR_EE->unkEE, G22_M->unk48);
    func_806DFFDC(D_807FBB40->unkE6);
}

void func_806E1864(void) {
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E186C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E1A50.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E1BA4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E1D38.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E1E54.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E1F8C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E208C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E2140.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E225C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E2B20.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E2C74.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E2CC4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E2DE8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E2E6C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E2EA8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E2ECC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E2F3C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E2FE8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E3040.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E31FC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E330C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E341C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E34D8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E352C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E35D8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E36B4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E380C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E382C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E384C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E3B00.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E3C14.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E3C38.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E3CEC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E3D14.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E3E40.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E41B4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E41EC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E4580.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E4634.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E4740.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E4AD8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E4C6C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E4D14.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E4D84.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E4E88.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E5044.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E521C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E527C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E52D0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E5488.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E560C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E56EC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E5C2C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E5C74.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E5D60.s")

void func_806E5E58(void) {
}

void func_806E5E60(void) {
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E5E68.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E5EA8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E5ED4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E5FA0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E607C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E61D0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E6234.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E6318.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E6368.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E63B8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E64D0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E65BC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E67D8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E6A38.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E6B98.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E6DE8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E6E7C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E6EE0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E6F74.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E6FF0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E7050.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E7088.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E709C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E7230.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E7338.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E7484.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E7568.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E7658.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E770C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E7780.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E78B8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E78E0.s")

void func_806E78F8(void) {
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E7900.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E7B48.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E7C70.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E7DF4.s")

typedef struct G29Anim0 {
    u8 pad0[4];
    f32 unk4;
    u8 pad8[8];
    s16 unk10;
    u8 pad12[0x12];
    f32 unk24;
} G29Anim0;

typedef struct G29Anim {
    G29Anim0 *unk0;
    u8 pad4[0x60];
    u16 unk64;
} G29Anim;

typedef struct G29AnimActor {
    u8 pad0[4];
    G29Anim *unk4;
} G29AnimActor;

typedef struct G29Parent {
    u8 pad0[0x154];
    u8 unk154;
    u8 unk155;
} G29Parent;

typedef struct G29Obj178 {
    u8 unk0;
    u8 unk1;
    u8 pad2[2];
    u8 unk4;
    u8 pad5[3];
    f32 unk8;
    u8 padC[8];
    f32 unk14;
} G29Obj178;

typedef struct G29State {
    u8 pad0[2];
    s16 unk2;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    u8 pad14[0xC];
    s32 unk20;
    u8 pad24[1];
    u8 unk25;
    u8 pad26[3];
    u8 unk29;
    u8 pad2A[6];
    G29Parent *unk30;
    u8 unk34;
    u8 pad35[9];
    u8 unk3E;
    u8 pad3F[3];
    u8 unk42;
    u8 pad43[2];
    u8 unk45;
} G29State;

typedef struct G29Act {
    u8 pad0[0xB8];
    f32 unkB8;
    u8 padBC[0xB8];
    G29State *unk174;
    G29Obj178 *unk178;
} G29Act;

typedef struct G29Main {
    u8 pad0[0x88];
    G29Act *unk88;
    u8 pad8C[0x1B0];
    u16 unk23C;
} G29Main;

typedef G21Table G29Stick;

typedef struct G29BtnA {
    u16 unk0;
    u8 pad2[0x32];
} G29BtnA;

#define G29_M ((G29Main *)D_807FD580)
#define G29_BB48 ((G29AnimActor *)D_807FBB48)
#define G29_BB40 ((G29AnimActor *)D_807FBB40)
#define G29_PAR ((G29Parent *)D_807FBB40)

extern G29BtnA D_807FD63A[];
extern f32 D_80750FF8;
extern f32 D_80750FFC;
extern f32 D_80751000;
s32 func_805FCA64(void);
void renderCallbacksRegister(void *, void *, s32);
void actorDrawAnimatedEffect(s32, void *);
void func_80613C48(void *, s16, f32, f32);
void func_80614D48(void *, f32, f32);
s32 func_8061CB50(void);

void func_806E8244(void) {
    G29State *st;
    G29Stick *c;
    s16 v;

    st = G29_M->unk88->unk174;
    if (func_805FCA64() != 0) {
        renderCallbacksRegister(actorDrawAnimatedEffect, G29_M->unk88, 5);
    }
    v = D_807FBB40->unkE6;
    if (v < 0x200 || v >= 0xE01) {
        st->unk2 = ((G29Stick *)((u8 *)D_807FD610 + D_807FC929 * 0x34))->unk2E;
        c = &D_807FD610[D_807FC929];
    } else if (v >= 0x201 && v < 0x600) {
        s8 t;
        st->unk2 = ((G29Stick *)((u8 *)D_807FD610 + D_807FC929 * 0x34))->unk2F;
        c = ((G29Stick *)((u8 *)D_807FD610 + D_807FC929 * 0x34));
        t = c->unk2E;
        c->unk2E = c->unk2F;
        c->unk2F = t;
    } else if (v >= 0x601 && v < 0xA00) {
        st->unk2 = -((G29Stick *)((u8 *)D_807FD610 + D_807FC929 * 0x34))->unk2E;
        c = ((G29Stick *)((u8 *)D_807FD610 + D_807FC929 * 0x34));
        c->unk2E = -c->unk2E;
        c->unk2F = -c->unk2F;
    } else {
        s8 t;
        st->unk2 = -((G29Stick *)((u8 *)D_807FD610 + D_807FC929 * 0x34))->unk2F;
        c = ((G29Stick *)((u8 *)D_807FD610 + D_807FC929 * 0x34));
        t = c->unk2E;
        c->unk2E = -c->unk2F;
        c->unk2F = -t;
    }
    if (c->unk2E < -0x1E) {
        G29_M->unk23C = 0x28;
        st->unk42 = 1;
    } else if (c->unk2E >= 0x1F) {
        G29_M->unk23C = 0x28;
        st->unk42 = 2;
    } else if (G29_M->unk23C != 0) {
        G29_M->unk23C--;
    } else {
        st->unk42 = 0;
    }
}

void func_806E84A4(void) {
    G29State *st;

    st = G29_M->unk88->unk174;
    st->unk3E = 0x14;
}

void func_806E84C0(void) {
    G29State *st;

    st = G29_M->unk88->unk174;
    st->unk3E = 0x64;
    if (G29_M->unk23C != 0) {
        G29_M->unk23C--;
    }
}

void func_806E84F8(void) {
    G29State *st;

    if (!(D_807FD63A[D_807FC929].unk0 & 0xE000)) {
        st = G29_M->unk88->unk174;
        st->unk3E = 0x32;
    }
}

void func_806E854C(G29State *arg0, s32 arg1, s32 arg2) {
    G29Anim0 *sub;
    s32 n;
    f32 f;
    f32 h;
    f32 cur;

    sub = G29_BB48->unk4->unk0;
    if (arg2 != sub->unk10) {
        if (arg1 == sub->unk10) {
            func_80613C48(D_807FBB48, arg2, 0.0f, 5.0f);
            return;
        }
        if (G29_BB40->unk4->unk0->unk24 >= 0.0f && sub->unk4 > 0.0f) {
            func_80614D48(D_807FBB48, -1.0f, 0.0f);
        }
        if (G29_BB40->unk4->unk0->unk4 == 0.0f) {
            func_80613C48(D_807FBB48, arg2, 0.0f, 5.0f);
        }
    } else {
        cur = arg0->unkC;
        f = (cur > 0.0f) ? cur : -cur;
        h = f - 0.2f;
        n = arg0->unk10 > 1.0 ? 8 : 5;
        cur = sub->unk4;
        f = n * h * 1.25f;
        if (f - 1.0f <= cur && cur <= f + 1.0f) {
            n = 0;
        } else {
            n = f <= cur ? -1 : 1;
        }
        func_80614D48(D_807FBB48, n, 5.0f);
    }
}

void func_806E8724(G29Act *arg0, G29State *arg1) {
    s32 sign;
    s32 t;
    f32 f;
    f32 g;
    f32 x;

    if (arg1->unk45 == 0 && arg1->unk34 == 2) {
        t = D_807FD610[D_807FC929].unk2F < -0x14;
        sign = D_807FD610[D_807FC929].unk2E >= 0 ? 1 : -1;
        f = D_807FD610[D_807FC929].unk30;
        if (f > 80.0f) {
            g = 80.0f;
        } else {
            g = f;
        }
        x = g;
        x *= sign;
        x *= 0.0125f;
        arg1->unkC = x;
        arg1->unkC = x * D_80750FFC;
        if (arg1->unk20 == 0) {
            arg1->unk20 = (arg0->unkB8 < D_80750FF8) & t;
        } else {
            arg1->unk20 = t;
        }
    } else {
        arg1->unk20 = 0;
        arg1->unkC = 0.0f;
    }
}

void func_806E884C(void) {
    G29Act *a;

    a = G29_M->unk88;
    if (a != NULL) {
        func_806E8724(a, a->unk174);
    }
}

void func_806E8880(void) {
    G29Act *a;
    G29State *st;

    a = G29_M->unk88;
    if (a != NULL) {
        st = a->unk174;
        st->unk8 = D_80751000;
    }
}

void func_806E88AC(void) {
    G29Act *a;
    G29State *st;

    a = G29_M->unk88;
    if (a != NULL) {
        st = a->unk174;
        st->unk8 = 0.0f;
    }
}

void func_806E88D8(void) {
    G29Act *a;
    G29State *st;
    s32 sp24;
    s32 a2;
    s32 sp1C;

    a = G29_M->unk88;
    if (a != NULL) {
        if (D_807FBB40->unk58 == 4) {
            sp24 = 0x1C7;
            a2 = 0x1C5;
            sp1C = 0x1C6;
        } else {
            sp24 = 0x53;
            a2 = 0x54;
            sp1C = 0x55;
        }
        st = a->unk174;
        func_806E8724(a, st);
        if (func_8061CB50() == 0 && G29_BB48->unk4->unk64 != 0x3B5) {
            if (st->unkC < 0.2f && st->unkC > -0.2f && sp24 != G29_BB48->unk4->unk0->unk10) {
                if (G29_BB48->unk4->unk0->unk24 >= 0.0f && G29_BB48->unk4->unk0->unk4 > 0.0f) {
                    func_80614D48(D_807FBB48, -1.0f, 5.0f);
                    return;
                }
                if (G29_BB40->unk4->unk0->unk4 == 0.0f) {
                    func_80613C48(D_807FBB48, sp24, 0.0f, 5.0f);
                }
            } else {
                if (st->unkC < -0.2f) {
                    func_806E854C(st, sp24, a2);
                    return;
                }
                if (st->unkC > 0.2f) {
                    func_806E854C(st, sp24, sp1C);
                }
            }
        }
    }
}

void func_806E8A8C(void) {
    G29Act *a;
    G29State *st;

    a = G29_M->unk88;
    if (a != NULL) {
        st = a->unk174;
        if (st->unk45 == 0 && st->unk34 == 2) {
            if (st->unk25 == 0) {
                st->unk4 = 1.1f;
            }
        } else {
            st->unk4 = 0.0f;
        }
    }
}

void func_806E8AF0(void) {
    G29Act *a;
    G29State *st;

    a = G29_M->unk88;
    if (a != NULL) {
        st = a->unk174;
        if (st->unk25 == 0) {
            st->unk4 = 0.0f;
        }
    }
}

void func_806E8B28(void) {
    G29Act *a;
    G29State *st;
    G29Obj178 *o;

    a = G29_M->unk88;
    if (a != NULL) {
        st = a->unk174;
        if (st->unk45 == 0 && st->unk34 == 2) {
            o = a->unk178;
            if (((G29BtnA *)&D_807FD63C)[D_807FC929].unk0 & 0x8000) {
                o->unk4 = 1;
            }
        }
    }
}

void func_806E8BA4(void) {
    G29Act *a;
    G29State *st;

    a = G29_M->unk88;
    if (a != NULL) {
        st = a->unk174;
        if (st->unk45 == 0 && st->unk34 == 2) {
            st->unk10 = 2.0f;
        } else {
            st->unk10 = 1.0f;
        }
    }
}

void func_806E8BFC(void) {
    G29Act *a;
    G29State *st;

    a = G29_M->unk88;
    if (a != NULL) {
        st = a->unk174;
        st->unk10 = 1.0f;
    }
}

void func_806E8C2C(void) {
    G29Act *a;
    G29Obj178 *o;
    s32 v1;
    s32 a0;
    s8 a1;

    a = G29_M->unk88;
    if (a != NULL) {
        if (G29_BB48->unk4->unk0->unk10 != 0x22A) {
            func_80613C48(D_807FBB48, 0x22A, 0.0f, 0.0f);
        }
        if (a->unk174->unk45 == 0 && a->unk174->unk30->unk154 == 2) {
            o = a->unk178;
            a0 = o->unk1;
            v1 = o->unk0;
            a1 = D_807FD63E[D_807FC929].unk0;
            if (a0 == v1 && o->unk4 == 0) {
                if (a1 >= 0x1F && v1 < 2) {
                    o->unk1 = v1 + 1;
                } else if (a1 < -0x1E) {
                    if (v1 > 0) {
                        o->unk1 = v1 - 1;
                    }
                }
                a0 = o->unk1;
                if (a0 != v1) {
                    o->unk4 = 2;
                    o->unk8 = 0.0f;
                }
            }
        }
    }
}

void func_806E8D54(void) {
    G29Act *a;
    G29State *st;
    G29Obj178 *o;

    a = G29_M->unk88;
    if (a != NULL) {
        st = a->unk174;
        if (st->unk34 != 0 && st->unk34 < 3 && st->unk45 == 0) {
            o = a->unk178;
            st->unk4 = o->unk14 + 1.1;
        }
    }
}

void func_806E8DB4(void) {
    G29Act *a;
    G29State *st;
    G29Obj178 *o;

    a = G29_M->unk88;
    if (a != NULL) {
        st = a->unk174;
        if (st->unk34 != 0 && st->unk34 < 3 && st->unk45 == 0) {
            o = a->unk178;
            st->unk4 = o->unk14;
        }
    }
}

void func_806E8E00(void) {
    G29Act *a;
    G29State *st;

    a = G29_M->unk88;
    if (a != NULL) {
        st = a->unk174;
        if (st->unk45 == 0 && st->unk34 == 2 && (((G29BtnA *)&D_807FD63C)[D_807FC929].unk0 & 0x8000)) {
            st->unk29 = 1;
        }
    }
}

void func_806E8E78(void) {
    if (G29_PAR->unk154 == 7 && !(D_807FD63A[D_807FC929].unk0 & 0x10)) {
        func_80614E78(D_807FBB40, 0x7F);
        G29_PAR->unk154 = 8;
        G29_PAR->unk155 = 0;
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E8F04.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E8F68.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E9070.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E918C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E9388.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E93F8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E9468.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E9580.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E9804.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E9874.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E98F8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E9964.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E9A5C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E9ACC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E9B3C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E9BA8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E9CDC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E9CFC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E9D1C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806E9DE0.s")

typedef struct G31State {
    /* 0x00 */ u8 pad0[8];
    /* 0x08 */ u16 unk8;
    /* 0x0A */ u8 pad0A[0xA2];
    /* 0xAC */ u32 unkAC;
    /* 0xB0 */ s16 unkB0;
    /* 0xB2 */ s16 unkB2;
    /* 0xB4 */ f32 unkB4;
    /* 0xB8 */ f32 unkB8;
    /* 0xBC */ s16 unkBC;
    /* 0xBE */ u8 padBE[0x30];
    /* 0xEE */ u8 unkEE;
    /* 0xEF */ u8 unkEF;
    /* 0xF0 */ u8 unkF0;
    /* 0xF1 */ u8 unkF1;
    /* 0xF2 */ u8 padF2;
    /* 0xF3 */ u8 unkF3;
    /* 0xF4 */ u8 padF4[2];
    /* 0xF6 */ u8 unkF6;
    /* 0xF7 */ u8 padF7[5];
    /* 0xFC */ u8 unkFC;
} G31State;

typedef struct G31Player {
    /* 0x000 */ u8 pad0[0x104];
    /* 0x104 */ struct G31Link *unk104;
} G31Player;

typedef struct G31Link {
    /* 0x000 */ u8 pad0[0xB4];
    /* 0x0B4 */ f32 unkB4;
    /* 0x0B8 */ u8 padB8[0xBC];
    /* 0x174 */ G31State *unk174;
} G31Link;

#define G31_PAD(sym, T) (*(T *)((u8 *)&(sym) + D_807FC929 * 0x34))
#define G31_PLAYER ((G31Player *)D_807FD580)

extern s32 D_807FBB64;
void func_806E9D1C();
s32 func_80714608();

void func_806E9ECC(void) {
    G31State *state;

    if ((G31_PAD(D_807FD63C, u16) & 2) && (D_807FBB40->unk6A & 1)) {
        state = G31_PLAYER->unk104->unk174;
        if ((func_80714608(0) == 0) && !(state->unkAC & 0x80000000) && !(D_807FBB64 & 0x80000000)) {
            func_806E9D1C(5, 3, 1);
        }
    }
}

void func_806E9F8C(void) {
    G31State *state;

    if ((G31_PAD(D_807FD63C, u16) & 8) && (D_807FBB40->unk6A & 1)) {
        state = G31_PLAYER->unk104->unk174;
        if ((func_80714608(0) == 0) && !(state->unkAC & 0x80000000) && !(D_807FBB64 & 0x80000000)) {
            func_806E9D1C(5, 3, 1);
        }
    }
}

void func_806EA04C(void) {
    if (G31_PAD(D_807FD63C, u16) & 8) {
        func_806E9D1C(7, 3, 0);
    }
}

#ifdef NON_MATCHING
extern s32 D_807FBB68;
void func_8062217C();
void func_80609140(s32, s32, f32, f32, s32, s32);

void func_806EA0A4(void) {
    G31State *state;
    s32 max;
    s32 cur;

    state = G31_PLAYER->unk104->unk174;
    if ((D_807FBB64 & 1) && !(D_807FBB68 & 2)) {
        max = 2;
    } else {
        max = 3;
    }
    cur = state->unkEF;
    if ((cur != 0) && ((G31_PAD(D_807FD63C, u16) & 0xC) == 4) && ((max == state->unkEE) || (state->unkFC == 0))) {
        state->unkF0 = cur;
        if (cur < max) {
            state->unkEF = cur + 1;
        } else {
            state->unkEF = 1;
        }
        func_8062217C(G31_PLAYER->unk104, state->unkEF, &D_807FD580);
        state->unkEE = state->unkEF;
        if ((state->unkEF != state->unkF0) && ((state->unk8 == 0) || (state->unk8 >= 0x96)) && (state->unkF3 != 2)) {
            func_80609140(0x27, 0x7FFF, 63.0f, 1.0f, 0, 0);
        }
        state->unkF1 = 0xB;
        state->unkF6 = 0xF;
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806EA0A4.s")
#endif

void func_806EA200(void) {
    G31State *state;

    state = G31_PLAYER->unk104->unk174;
    if ((G31_PAD(D_807FD63C, u16) & 2) && (state->unkF1 < 3)) {
        state->unkB0 -= 0x2D;
        state->unkF1 = 0xB;
    }
}

void func_806EA26C(void) {
    G31State *state;

    state = G31_PLAYER->unk104->unk174;
    if ((G31_PAD(D_807FD63C, u16) & 1) && (state->unkF1 < 3)) {
        state->unkB0 += 0x2D;
        state->unkF1 = 0xB;
    }
}


f32 func_806EA2D8(void) {
    return (G31_PAD(D_807FD63A, u16) & 0x2000) ? 0.2 : 1.0;
}

typedef struct G31Cam {
    /* 0x000 */ u8 pad0[0x27C];
    /* 0x27C */ f32 unk27C;
    /* 0x280 */ u8 pad280[0x70];
} G31Cam;

extern G31Cam *D_807FC924;
extern s32 D_8076A0A8;
void sfxPlayActorSound(void *, s32, s32, s32, s32, s32, f32, s32);
void sfxStopSlotSound();

void func_806EA334(void) {
    f32 limit;
    f32 next;
    G31Cam *cam;
    s32 buttons;

    buttons = G31_PAD(D_807FD63A, u16);
    if (!(buttons & 0x2000) && !(buttons & 2) && (D_807FBB40->unk154 == 2)) {
        limit = (D_8076A0A8 == 0x22) ? 15.0 : 13.0;
        cam = (G31Cam *)((u8 *)D_807FC924 + D_807FC929 * 0x2F0);
        next = cam->unk27C - 1.5f;
        if (limit < next) {
            cam->unk27C = next;
            sfxPlayActorSound(D_807FBB40, 0x1F0, 0, 0, 0, 0xFF, 1.0f, -1);
            return;
        }
        cam->unk27C = limit;
        sfxStopSlotSound(D_807FBB40, 0);
    }
}

void func_806EA460(void) {
    f32 next;
    G31Cam *cam;
    s32 buttons;

    buttons = G31_PAD(D_807FD63A, u16);
    if (!(buttons & 0x2000) && !(buttons & 1) && (D_807FBB40->unk154 == 2)) {
        cam = (G31Cam *)((u8 *)D_807FC924 + D_807FC929 * 0x2F0);
        next = cam->unk27C + 1.5f;
        if (next < 45.0) {
            cam->unk27C = next;
            sfxPlayActorSound(D_807FBB40, 0x1F0, 0, 0, 0, 0xFF, 1.0f, -1);
            return;
        }
        cam->unk27C = 45.0f;
        sfxStopSlotSound(D_807FBB40, 0);
    }
}

void func_806EA568(void) {
    u16 buttons;

    buttons = G31_PAD(D_807FD63A, u16) & 3;
    if ((buttons != 2) && (buttons != 1)) {
        sfxStopSlotSound(D_807FBB40, 0);
    }
}

s32 func_806E9580();
void func_806EAB44();

void func_806EA5CC(void) {
    if (func_806E9580()) {
        func_806EAB44(D_807FBB40, 1);
    }
}

void func_806EA600(void) {
    func_806EA568();
    func_806EA5CC();
}

void func_806EA628(void) {
    G31State *state;
    s16 *angle;
    f32 *dist;
    s32 unused;

    if (!(D_807FD580->unk1F0 & 0x8000)) {
        state = G31_PLAYER->unk104->unk174;
        angle = &state->unkB2;
        *angle = (f64)*angle - (((f64)func_806EA2D8() * ((f64)G31_PAD(D_807FD63E, s8) * 0.08) * 4096.0) / 360.0);
        dist = &state->unkB8;
        *dist = ((f64)G31_PAD(D_807FD63F, s8) * 0.04 * func_806EA2D8()) + (f64)*dist;
        *angle &= 0xFFF;
        if ((f32)(state->unkBC + 0x32) < *dist) {
            *dist = state->unkBC + 0x32;
        } else if (*dist < (f32)(state->unkBC - 0x50)) {
            *dist = state->unkBC - 0x50;
        }
        G31_PLAYER->unk104->unkB4 = *dist;
        D_807FBB40->unkE6 = (state->unkB2 + 0x800) & 0xFFF;
    }
}

void func_806EA7E8(void) {
    if ((G31_PAD(D_807FD63C, u16) & 0xC000) == 0x8000) {
        func_806EAB44(D_807FBB40, 0);
    }
}

void func_806EA844(void) {
    if ((G31_PAD(D_807FD63C, u16) & 0xC000) == 0x4000) {
        func_806EAB44(D_807FBB40, 0);
    }
}

void func_806EA8A0(void) {
    if ((G31_PAD(D_807FD63C, u16) & 0xC000) == 0x8000) {
        func_806EAB44(D_807FBB40, 1);
    }
}

void func_806EA8FC(void) {
    if ((G31_PAD(D_807FD63C, u16) & 0xC000) == 0x4000) {
        func_806EAB44(D_807FBB40, 1);
    }
}

void func_806EA958(void) {
    if ((G31_PAD(D_807FD63C, u16) & 0xC) == 8) {
        func_806EAB44(D_807FBB40, 0);
    }
}

void func_806E9874();

void func_806EA9B4(void) {
    if ((D_807FD610[D_807FC929].unk2A & 0x2000) && (D_807FD610[D_807FC929].unk2C & 4)) {
        func_806E9874();
        return;
    }
    if ((D_807FD610[D_807FC929].unk2C & 0xC) == 4) {
        func_806EAB44(D_807FBB40, 0);
    }
}

void func_806EAA44(void) {
    if ((G31_PAD(D_807FD63C, u16) & 0xC) == 8) {
        func_806EAB44(D_807FBB40, 1);
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806EAAA0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806EAB44.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806EAC8C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806EACBC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806EACEC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806EAE04.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806EAE60.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806EAF6C.s")

void func_806EAFEC(void) {
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806EAFF4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/E4090/func_806EB058.s")

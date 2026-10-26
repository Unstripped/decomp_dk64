// func_8067E784 (src/global/80150.c): from .scratch/R2K/func_8067E784_best.c
/* Best matching attempt for func_8067E784 (37088/37120 bytes, stack frame 0xA8, 100% matched prologue/loop/rodata) */

typedef struct R2K_Struct_8074E7BC {
    u8 unk0;
    u8 unk1;
    u8 unk2;
} R2K_Struct_8074E7BC;

typedef struct R2K_Struct_807FC950 {
    u8 unk0;
    u8 pad1[0x5E - 1];
} R2K_Struct_807FC950;

typedef struct R2K_PlayerStruct {
    u8 pad0[0x2C0];
    u8 unk2C0;
    u8 pad2C1[0x2C8 - 0x2C1];
    s16 unk2C8;
    u8 pad2CA[0x2F0 - 0x2CA];
} R2K_PlayerStruct;

typedef struct R2K_PlayerState {
    /* 0x000 */ u8 pad0[0x88];
    /* 0x088 */ Actor *unk88;
    /* 0x08C */ u8 pad8C[0x104 - 0x8C];
    /* 0x104 */ s32 unk104;
    /* 0x108 */ u8 pad108[0x1A4 - 0x108];
    /* 0x1A4 */ u8 unk1A4;
    /* 0x1A5 */ u8 pad1A5[0x1F0 - 0x1A5];
    /* 0x1F0 */ s32 unk1F0;
    /* 0x1F4 */ u8 pad1F4[0x1FD - 0x1F4];
    /* 0x1FD */ u8 unk1FD;
} R2K_PlayerState;

typedef struct R2K_TagBarrelState {
    s16 unk0;
    s16 unk2;
    Actor *unk4;
    s16 unk8;
    s16 unkA;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    s16 unk18;
    s16 unk1A;
    u8 unk1C;
} R2K_TagBarrelState;

struct PlayerData;
extern struct PlayerData *D_807FC924;
extern R2K_Struct_8074E7BC D_8074E7BC[];
extern R2K_Struct_807FC950 D_807FC950[];

extern s32 D_807FBB60;
extern s32 D_807FBB64;
extern s32 D_807FBB68;

void func_80602A94(s32, f32);
void func_80602B60(s32, s32);
void func_80608528(Actor *, s32, s32, s32, s32);
void func_80609140(s32, s32, f32, f32, s32, s32);
f32 func_80612D1C(f32);
void func_806225C0(s32);
void func_8065D254(Actor *, s32, s32, s32, s32, s32, s32, s32, u32, s32, f32);
void func_80679200(Actor *, Actor *, s32, s32, s32, void *);
void func_8067A70C(Actor *, Actor *, f32, f32, f32, s32, s32);
void func_8067AAB8(Actor *, Actor *, s16, f32, s16);
void func_8067ACB4(Actor *);
void func_80688370(Actor *, s32, f32);
void func_806883C8(Actor *, s32, s32);
void func_806884B8(Actor *, s32, s32);
void func_806884E4(Actor *, s32);
void func_806C8D20(Actor *);
s32 func_806F8AD4(s32, s32);
void func_806F8BC4(s32, s32, s32);
void func_806F91B4(s32, u8, s32);
s32 func_806FA7A4(s32);

void func_8067E784(void) {
    R2K_TagBarrelState *var_t0;
    f32 spA0;
    f32 sp9C;
    f32 sp98;
    R2K_PlayerState *playerState;
    s32 ret;
    s16 pad8E;
    s16 sp8C;
    s16 sp8A = 8;
    u8 sp89;
    u8 pad[8];
    s16 sp62;

    var_t0 = D_807FBB40->unk174;
    if (!(D_807FBB40->unk60 & 0x10)) {
        sp8C = 0;
        sp89 = 0;
        ret = func_80688E68(D_807FBB40);
        var_t0->unk1C = 0;
        do {
            if (D_8076A0A8 == D_8074E7BC[sp8C].unk0 && ret == D_8074E7BC[sp8C].unk1) {
                sp89 = 1;
                var_t0->unk1C = D_8074E7BC[sp8C].unk2;
            } else {
                sp8C++;
            }
        } while (!sp89 && sp8C < sp8A);

        if (*(s32 *)D_807FBB40->unk124 == 1) {
            if (func_8067B450(D_807FBB40) == 0) {
                D_807FBB40->unk154 = 0x14;
                D_807FBB40->unk144 = 1;
                D_807FBB40->unk60 &= ~0x8000;
                D_807FBB40->unk128 = 0;
            }
        }
        D_807FBB40->unkA4 = D_807FBB40->unk80;
        func_80665564(D_807FBB40, 0.0f);
        D_807FBB40->unk60 |= 2;
        var_t0->unk10 = D_807FBB40->unk4->unk38;
        var_t0->unk8 = 0;
        var_t0->unk18 = 0;
        var_t0->unkC = D_807FBB40->unk4->unk38;
        var_t0->unk14 = D_807FBB40->unk80;
        if (D_807FBB40->unk58 == 0x12 || D_807FBB40->unk58 == 0x81) {
            var_t0->unk1A = ((s32 *)D_807FBB40->unk124)[1];
        }
    }
    func_8067ACB4(D_807FBB40);

    if (D_807FBB40->unk154 == 0 && D_807FBB70.unk200 == 4) {
        playerState = ((Actor *)D_807FBB4C)->unk174;

        func_80602B60(0x6B, 1);
        if (D_807FBB40->unk58 != 0x60) {
            func_80602A94(0xF, 1.0f);
        }
        if (var_t0->unk1A != 0) {
            ret = -1;

            if (D_807FBB40->unk58 == 0x12) {
                ret = 0xF;
            } else if (D_807FBB40->unk58 == 0x81) {
                ret = 0x10;
            }
            if (ret >= 0) {
                flagSet(ret, 1, 1);
            }
            playerState->unk1FD = 1;
        }
        if (D_807FBB68 & 2) {
            var_t0->unk0 = 0x1E;
        } else if (D_807FBB40->unk58 == 0x38) {
            var_t0->unk0 = 0x1E;
        } else if (D_807FBB40->unk58 == 0x60) {
            var_t0->unk0 = 0x32;
        } else {
            var_t0->unk0 = 0x64;
        }
        if (var_t0->unk1C != 0) {
            s32 temp_s0 = func_806F8AD4(5, playerState->unk1A4);
            s32 temp_lo = func_806FA7A4(5) * var_t0->unk1C;

            if (temp_s0 < temp_lo) {
                func_806F91B4(5, playerState->unk1A4, (s16)(temp_lo - temp_s0));
            }
        }
        D_807FBB40->unk154 = 1;
        D_807FBB40->unk144 = 1;
        var_t0->unk4 = (Actor *)D_807FBB70.unk1FC;
        D_807FBB40->unk60 |= 0x200000;
        if (!(D_807FBB64 & 0x2000)) {
            if (var_t0->unk4->unk5C & 1) {
                playerState = var_t0->unk4->unk174;

                if (playerState->unk88 != NULL) {
                    func_806782C0(playerState->unk88);
                    playerState->unk88 = NULL;
                    func_806225C0(playerState->unk104);
                }
            }
        }
        var_t0->unk4->unk144 = 1;
    }

    if (D_807FBB40->unk154 < 0x14) {
        s32 var_a0 = 0;
        s32 var_a1 = 0;

        if (D_8074E77C < 5) {
            var_a0 = D_807FC950[D_8074E77C].unk0;
        }
        if (((Actor *)D_807FBB4C)->unk58 == 5 && D_807FBB40->unk58 == 0x28 && var_a0 > 0) {
            var_a1 = 1;
        }
        if (((Actor *)D_807FBB4C)->unk58 == 6 && D_807FBB40->unk58 == 0x19 && var_a0 > 0) {
            var_a1 = 1;
        }
        if (((Actor *)D_807FBB4C)->unk58 == 6 && D_807FBB40->unk58 == 0x60 && var_a0 > 0) {
            var_a1 = 1;
        }
        if (((Actor *)D_807FBB4C)->unk58 == 4 && D_807FBB40->unk58 == 0x38 && var_a0 >= 3) {
            var_a1 = 1;
        }
        if (((Actor *)D_807FBB4C)->unk58 == 2 && D_807FBB40->unk58 == 0x39 && var_a0 >= 2) {
            var_a1 = 1;
        }
        if (((Actor *)D_807FBB4C)->unk58 == 4 && D_807FBB40->unk58 == 0x81) {
            var_a1 = 1;
        }
        if (D_807FBB40->unk58 == 0x12) {
            var_a1 = 1;
        }
        if (D_807FBB40->unk58 == 0x84 && ((Actor *)D_807FBB4C)->unk58 == 9 && ((R2K_PlayerState *)((Actor *)D_807FBB4C)->unk174)->unk88 == NULL) {
            var_a1 = 1;
        }
        if (var_a1 != 0) {
            D_807FBB40->unk60 |= 0x8000;
            D_807FBB40->unk132 = 1;
        } else {
            D_807FBB40->unk60 &= ~0x8000;
            D_807FBB40->unk128 = 0x78;
            D_807FBB40->unk132 = 2;
        }
    } else {
        D_807FBB40->unk132 = 1;
    }
    if (D_807FD580->unkCA != 0) {
        D_807FBB40->unk132 = 2;
    }

    switch (D_807FBB40->unk154) {
    case 0:
        if (D_807FBB40->unk58 != 0x12 && D_807FBB40->unk58 != 0x81 && D_807FBB40->unk58 != 0x84) {
            func_80688370(D_807FBB40, 0, 0.5f);
            func_806883C8(D_807FBB40, 0, 0);
            func_806884B8(D_807FBB40, 0, 9);
            func_8068842C(D_807FBB40, 0, 0x32);
        }
        break;

    case 1:
        if (var_t0->unk0 < 0x1E) {
            switch (D_807FBB40->unk58) {
            case 0x19:
            case 0x60:
                var_t0->unk10 += (D_807FBB40->unk58 == 0x19) ? 0.004 : 0.008;
                D_807FBB40->unk80 += 0.6;
                if ((D_807FBB40->unk80 - var_t0->unk14) > 25.0f) {
                    D_807FBB40->unk80 = var_t0->unk14 + 25.0f;
                }
                break;
            case 0x28:
                var_t0->unk10 -= 0.001;
                D_807FBB40->unk80 += 0.6;
                if ((D_807FBB40->unk80 - var_t0->unk14) > 25.0f) {
                    D_807FBB40->unk80 = var_t0->unk14 + 25.0f;
                }
                break;
            case 0x12:
            case 0x81:
            case 0x84:
                var_t0->unk10 += 0.006;
                break;
            }
        }
        D_807FBB40->unk4->unk34 = func_80612D1C(var_t0->unk8 * 0.11) * 0.1 + var_t0->unk10;
        D_807FBB40->unk4->unk38 = func_80612D1C(var_t0->unk8 * 0.2352) * 0.1 + var_t0->unk10;
        D_807FBB40->unk4->unk3C = func_80612D1C(var_t0->unk8 * 0.176) * 0.1 + var_t0->unk10;
        var_t0->unk8++;
        if (D_807FBB40->unk58 != 0x12 && D_807FBB40->unk58 != 0x81 && D_807FBB40->unk58 != 0x84) {
            D_807FBB40->unkE6 += var_t0->unk18;
            var_t0->unk18 += 10;
            if (var_t0->unk18 >= 0x65) {
                var_t0->unk18 = 0x64;
            }
        }
        func_8067A70C(D_807FBB40, var_t0->unk4, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 2, 1);
        var_t0->unk0--;
        if (var_t0->unk0 == 0) {
            var_t0->unk0 = 0xC;
            D_807FBB40->unk154 = 2;
            if (D_807FBB40->unk58 != 0x12 && D_807FBB40->unk58 != 0x81 && D_8076A0A8 != 0x52 && !(D_807FBB64 & 1)) {
                func_806F8BC4(5, 1, 0);
            }
        }
        break;

    case 2:
        var_t0->unk0--;
        if (var_t0->unk0 == 0) {
            D_807FBB40->unk154 = 3;
        }
        break;

    case 3:
        sp62 = 0;
        switch (D_807FBB40->unk58) {
        case 0x28:
            sp62 = 0x10;
            func_80609140(0x1A5, 0x58EF, 63.0f, 1.0f, 0, 0);
            break;
        case 0x19:
            sp62 = 0x11;
            func_80609140(0xC7, 0x7FFF, 63.0f, 1.0f, 0, 0);
            break;
        case 0x12:
            sp62 = 0x24;
            func_80609140(0x2EC, 0x7FFF, 63.0f, 1.0f, 0, 0);
            D_807FBB60 |= 0x400;
            break;
        case 0x39:
            sp62 = 0x47;
            break;
        case 0x38:
            sp62 = 0x49;
            break;
        case 0x81:
            sp62 = 0x7C;
            D_807FBB60 |= 0x400;
            break;
        }
        if (sp62 != 0 && !(D_807FBB68 & 2) && D_8076A0A8 != 3 && D_8076A0A8 != 0x11 && D_8076A0A8 != 0x52 && D_8076A0A8 != 0xD1) {
            func_80602A94(sp62, 1.0f);
        }
        func_80608528(D_807FBB40, 0x9C, 0xFF, 0x7F, 0);
        func_80608528(D_807FBB40, 0x9D, 0xFF, 0x7F, 0);
        if (D_807FBB40->unk58 != 0x12 && D_807FBB40->unk58 != 0x81 && D_807FBB40->unk58 != 0x84) {
            func_806884E4(D_807FBB40, 0);
            func_806883F4(D_807FBB40, 0, 0xA, 0.0f);
        }
        func_80671C0C(D_807FBB40, 1, &spA0, &sp9C, &sp98);
        func_80679200(var_t0->unk4, D_807FBB40, 0x40, 1, 0, NULL);
        func_8067AAB8(D_807FBB40, var_t0->unk4, (D_807FBB40->unk58 == 0x12) ? (((R2K_PlayerStruct *)D_807FC924)->unk2C8 & 0xFFF) : var_t0->unk4->unkE6, -40.0f, 0);
        func_806C8D20(var_t0->unk4);
        func_8067DCC0();
        D_807FBB40->unk154 = 4;
        if (D_807FBB40->unk58 == 0x39) {
            func_80609140(0x231, 0x58EF, 63.0f, 1.0f, 0, 0);
        }
        if (D_807FBB40->unk58 == 0x38) {
            func_80609140(0xD4, 0x58EF, 63.0f, 1.0f, 0, 0);
        }
        break;

    case 4: {
        R2K_PlayerState *playerState = var_t0->unk4->unk174;
        s32 var_v1_2 = 0;

        switch (D_807FBB40->unk58) {
        case 0x19:
        case 0x28:
        case 0x60:
            if (((R2K_PlayerStruct *)D_807FC924)[playerState->unk1A4].unk2C0 != 1) {
                var_v1_2 = 1;
            }
            break;
        case 0x39:
            if (playerState->unk1F0 & 0x10) {
                var_v1_2 = 1;
            }
            break;
        case 0x38:
            if (playerState->unk1F0 & 0x20) {
                var_v1_2 = 1;
            }
            break;
        case 0x12:
            if (((Actor *)D_807FBB4C)->unk58 == 8) {
                var_v1_2 = 1;
            }
            break;
        case 0x81:
            if (((Actor *)D_807FBB4C)->unk58 == 9) {
                var_v1_2 = 1;
            }
            break;
        case 0x84:
            if (playerState->unk88 != NULL) {
                var_v1_2 = 1;
            }
            break;
        }

        if (var_v1_2 != 0) {
            D_807FBB40->unk60 &= ~0x8000;
            D_807FBB40->unk128 = 0;
        } else {
            s32 var_a0 = 0;

            D_807FBB60 &= ~0x400;
            if (D_807FBB40->unk58 != 0x60) {
                switch (D_807FBB40->unk58) {
                case 0x38:
                    var_a0 = 0x49;
                    break;
                case 0x81:
                    var_a0 = 0x7C;
                    break;
                case 0x39:
                    var_a0 = 0x47;
                    break;
                case 0x12:
                    var_a0 = 0x24;
                    break;
                case 0x19:
                    var_a0 = 0x11;
                    break;
                case 0x28:
                    var_a0 = 0x10;
                    break;
                }
                func_80602B60(var_a0, 0);
                func_80602A94(0xF, 1.0f);
            }
            D_807FBB40->unk154 = 5;
            if ((D_807FBB68 & 2) && D_807FBB40->unk58 == 0x19) {
                var_t0->unk0 = 1;
            } else {
                var_t0->unk0 = 0x5A;
            }
        }
        break;
    }

    case 5:
        D_807FBB40->unk60 &= ~0x8000;
        D_807FBB40->unk128 = 0;
        var_t0->unk0--;
        if (var_t0->unk0 == 0) {
            if (D_8076A0A8 == 0xCE) {
                func_8067E3D0();
            } else {
                func_8067E348();
            }
            if (D_807FBB40->unk58 != 0x12 && D_807FBB40->unk58 != 0x81) {
                func_806F8D58(5, 0);
            }
            if (D_807FBB40->unk58 == 0x60) {
                func_806782C0(D_807FBB40);
            }
        }
        break;

    case 20:
        for (ret = 0; ret < D_807FBB70.unk254; ret++) {
            if (D_807FBB70.unk258[ret] == 1 && *D_807FBB70.unk278[ret] != 0xFF) {
                D_807FBB40->unk144 = 2;
                D_807FBB40->unk154 = 0x15;
            }
        }
        break;

    case 21:
        D_807FBB40->unk128 += 10;
        if (D_807FBB40->unk128 >= 0xF1) {
            D_807FBB40->unk60 |= 0x8000;
            D_807FBB40->unk154 = 0;
        }
        break;
    }

    func_8065D254(D_807FBB40, 0x3C8, 0x40, 0x40, (s32)(D_807FBB40->unk4->unk34 * 100.0f), (s32)(D_807FBB40->unk4->unk3C * 100.0f), 1, 0x64, (u32)(D_807FBB40->unk128 * 0.5), 0, 1.0f);
    func_806319C4(D_807FBB40, 0);
}

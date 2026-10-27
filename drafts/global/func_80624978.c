// func_80624978 (src/global/201B0.c): stage 5-6: same frame/insn count, mnemonic stream identical; only regalloc: target dist=v1,wrap=v0,copy a1 (mine dist=v0,wrap=v1,copy a1). Adding s32 near=dist copy fixes regs but frame 0x40 vs 0x38. all decl-order perms tried (17 diff lines). Needs: sw a1/a2 homes ok; limit reused var (no rate temp), if/else for wrap, merged or-chain scale=D_807F5CCC
typedef struct CamC9Tgt {
    /* 0x000 */ u8 pad0[0x58];
    /* 0x058 */ s32 unk58;
    /* 0x05C */ u8 pad5C[0xF8];
    /* 0x154 */ u8 unk154;
} CamC9Tgt;

typedef struct CamC9St {
    /* 0x00 */ CamC9Tgt *unk0;
    /* 0x04 */ u8 pad4[0xA8];
    /* 0xAC */ s32 unkAC;
    /* 0xB0 */ u8 padB0[2];
    /* 0xB2 */ s16 unkB2;
    /* 0xB4 */ u8 padB4[0x3F];
    /* 0xF3 */ u8 unkF3;
} CamC9St;

void func_80624978(CamC9St *arg0, s16 arg1, s16 arg2) {
    s16 diff;
    u16 dist;
    f32 scale;
    f32 limit;
    u16 wrap;

    diff = arg2 - arg0->unkB2;
    dist = diff > 0 ? diff : -diff;
    if (dist >= 0x801) {
        wrap = 0x1000 - dist;
    } else {
        wrap = dist;
    }
    limit = arg1 / 3000.0f * wrap + 5.7f;
    if ((((arg0->unkAC & 4) || arg0->unk0->unk58 == 8) && !(569.0f <= dist && dist <= 3527.0f)) ||
        (D_807FBB64 & 0x8000) || arg0->unk0->unk154 == 0x82) {
        scale = D_807F5CCC;
    } else {
        switch (arg0->unkF3) {
            case 1:
            case 5:
                if (569.0f <= dist && dist <= 3527.0f) {
                    scale = func_80612790((s16)((dist - 569.0f) / 2958.0f * 4096.0f)) * 0.5f + 0.5f;
                } else if (dist < 0x14) {
                    scale = dist / 20.0f;
                } else {
                    scale = 1.0f;
                }
                break;
            case 10:
                scale = 6.0f;
                break;
            case 12:
                scale = 8.0f;
                break;
            case 13:
                scale = 15.0f;
                break;
            default:
                scale = 1.0f;
                break;
        }
    }
    limit = limit * scale;
    if ((f32)dist < limit) {
        limit = dist;
    }
    if (diff != 0) {
        if ((diff > 0 && dist < 0x800) || (diff < 0 && dist >= 0x800)) {
            arg0->unkB2 = arg0->unkB2 + limit;
        } else {
            arg0->unkB2 = arg0->unkB2 - limit;
        }
    }
    arg0->unkB2 &= 0xFFF;
}

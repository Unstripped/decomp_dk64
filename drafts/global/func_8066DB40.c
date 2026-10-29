// func_8066DB40 (src/global/70FD0.c): stage 5-6, parked NON_MATCHING in src: frame 0x80 + all stores match; remaining 7 insn diff = register picks in min/max chains (target a0/v1,v1/v0 vs ours v0/v1,a0): temp locals declared/assigned in 4 blocks, tried all rgs assignments of 8 roles to 4 temps, 4x s64 copy of output words (needed), mul-by-8 order 0..8 in 3 lines, stores order adbcegf. deadsweep: no improvement.
typedef struct Col7BHitIn {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ u8 unk14;
    /* 0x15 */ u8 unk15;
    /* 0x16 */ u8 unk16;
} Col7BHitIn;

typedef struct Col7BHitOut {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ s16 unk26;
} Col7BHitOut;

typedef struct Col7BTriWork {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ s16 unk48;
    /* 0x4A */ u8 pad4A;
    /* 0x4B */ u8 unk4B;
    /* 0x4C */ u8 unk4C;
    /* 0x4D */ u8 unk4D;
    /* 0x4E */ u8 pad4E;
    /* 0x4F */ u8 unk4F;
    /* 0x50 */ u8 unk50;
    /* 0x51 */ u8 unk51;
    /* 0x52 */ u8 pad52[0x58 - 0x52];
} Col7BTriWork;

s32 func_8066DB40(void *arg0, void *arg1) {
#define C7B_IN ((Col7BHitIn *)arg0)
#define C7B_OUT ((Col7BHitOut *)arg1)
    Col7BTriWork sp28;
    s32 pad[2];
    s16 temp_a0;
    s16 temp_v1;
    s16 temp_v0;

    sp28.unk24 = C7B_IN->unk0;
    sp28.unk28 = C7B_IN->unk2;
    sp28.unk2C = C7B_IN->unk4;
    sp28.unk30 = C7B_IN->unk6;
    sp28.unk34 = C7B_IN->unk8;
    sp28.unk38 = C7B_IN->unkA;
    sp28.unk3C = C7B_IN->unkC;
    sp28.unk40 = C7B_IN->unkE;
    sp28.unk44 = C7B_IN->unk10;

    sp28.unk24 *= 8; sp28.unk28 *= 8; sp28.unk2C *= 8;
    sp28.unk30 *= 8; sp28.unk34 *= 8; sp28.unk38 *= 8;
    sp28.unk3C *= 8; sp28.unk40 *= 8; sp28.unk44 *= 8;

    sp28.unk48 = C7B_IN->unk12;
    sp28.unk4C = C7B_IN->unk14;
    sp28.unk4D = 0;
    sp28.unk4F = 0;
    if (C7B_IN->unk16 & 4) {
        sp28.unk51 = 1;
    } else {
        sp28.unk51 = 0;
    }
    sp28.unk50 = C7B_IN->unk15;
    sp28.unk4B = 1;
    func_8066DD34((CollisionBox *)&sp28);

    *(s64 *)&C7B_OUT->unk0 = *(s64 *)&sp28.unk0;
    *(s64 *)&C7B_OUT->unk8 = *(s64 *)&sp28.unk8;
    *(s64 *)&C7B_OUT->unk10 = *(s64 *)&sp28.unk10;
    *(s64 *)&C7B_OUT->unk18 = *(s64 *)&sp28.unk18;
    C7B_OUT->unk20 = sp28.unk20;

temp_a0 = C7B_IN->unk8;
    temp_v1 = C7B_IN->unk2;
    if (temp_v1 < temp_a0) {
        C7B_OUT->unk24 = temp_v1;
    } else {
        C7B_OUT->unk24 = temp_a0;
    }
    temp_v1 = C7B_OUT->unk24;
    temp_a0 = C7B_IN->unkE;
    if (temp_v1 < temp_a0) {
        C7B_OUT->unk24 = temp_v1;
    } else {
        C7B_OUT->unk24 = temp_a0;
    }

    temp_v0 = C7B_IN->unk8;
    temp_v1 = C7B_IN->unk2;
    if (temp_v0 < temp_v1) {
        C7B_OUT->unk26 = temp_v1;
    } else {
        C7B_OUT->unk26 = temp_v0;
    }
    temp_a0 = C7B_IN->unkE;
    temp_v0 = C7B_OUT->unk26;
    if (temp_a0 < temp_v0) {
        C7B_OUT->unk26 = temp_v0;
    } else {
        C7B_OUT->unk26 = temp_a0;
    }

    return 1;
#undef C7B_IN
#undef C7B_OUT
}

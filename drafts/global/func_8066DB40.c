// func_8066DB40 (src/global/70FD0.c): Closest diff 4 insns in vertex 3x3 stores + min/max branch scheduling; frame 0x80 matched
#include "common.h"
#include "actor.h"

typedef struct M70N_CollisionInput {
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
} M70N_CollisionInput;

typedef struct M70N_CollisionOutput {
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
} M70N_CollisionOutput;

typedef struct M70N_TriWork {
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
} M70N_TriWork;

void func_8066DD34(CollisionBox *work);

s32 func_8066DB40(M70N_CollisionInput *arg0, M70N_CollisionOutput *arg1) {
    M70N_TriWork sp28;
    s32 pad[2];
    s16 temp_a0;
    s16 temp_v1;
    s16 temp_v0;

    sp28.unk24 = arg0->unk0;
    sp28.unk28 = arg0->unk2;
    sp28.unk2C = arg0->unk4;
    sp28.unk30 = arg0->unk6;
    sp28.unk34 = arg0->unk8;
    sp28.unk38 = arg0->unkA;
    sp28.unk3C = arg0->unkC;
    sp28.unk40 = arg0->unkE;
    sp28.unk44 = arg0->unk10;

    sp28.unk2C *= 8;
    sp28.unk28 *= 8;
    sp28.unk24 *= 8;
    sp28.unk30 *= 8;
    sp28.unk34 *= 8;
    sp28.unk38 *= 8;
    sp28.unk44 *= 8;
    sp28.unk40 *= 8;
    sp28.unk3C *= 8;

    sp28.unk48 = arg0->unk12;
    sp28.unk4D = 0;
    sp28.unk4F = 0;
    sp28.unk4C = arg0->unk14;
    if (arg0->unk16 & 4) {
        sp28.unk51 = 1;
    } else {
        sp28.unk51 = 0;
    }
    sp28.unk4B = 1;
    sp28.unk50 = arg0->unk15;

    func_8066DD34((CollisionBox *)&sp28);

    arg1->unk0 = sp28.unk0;
    arg1->unk4 = sp28.unk4;
    arg1->unkC = sp28.unkC;
    arg1->unk8 = sp28.unk8;
    arg1->unk14 = sp28.unk14;
    arg1->unk10 = sp28.unk10;
    arg1->unk1C = sp28.unk1C;
    arg1->unk18 = sp28.unk18;
    arg1->unk20 = sp28.unk20;

    temp_a0 = arg0->unk8;
    temp_v1 = arg0->unk2;
    if (temp_v1 < temp_a0) {
        arg1->unk24 = temp_v1;
    } else {
        arg1->unk24 = temp_a0;
    }
    temp_v1 = arg1->unk24;
    temp_v0 = arg0->unkE;
    if (temp_v1 < temp_v0) {
        arg1->unk24 = temp_v1;
    } else {
        arg1->unk24 = temp_v0;
    }

    temp_a0 = arg0->unk8;
    temp_v1 = arg0->unk2;
    if (temp_a0 < temp_v1) {
        arg1->unk26 = temp_v1;
    } else {
        arg1->unk26 = temp_a0;
    }
    temp_v0 = arg0->unkE;
    temp_v1 = arg1->unk26;
    if (temp_v0 < temp_v1) {
        arg1->unk26 = temp_v1;
    } else {
        arg1->unk26 = temp_v0;
    }

    return 1;
}

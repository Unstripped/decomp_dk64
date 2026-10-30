// func_8072D13C (src/global/12E800.c): stage 5: 374 insns (exact size 0x5D8, 413 lines, reloc=0); if (!moved) fixed delay slot nop; register numbering only
typedef struct RvR3_Dc90ViewK {
    /* 0x00 */ u8 pad0[0xA];
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ u8 pad10[0xA];
    /* 0x1A */ u16 unk1A;
    /* 0x1C */ u8 pad1C[4];
    /* 0x20 */ u8 unk20;
    /* 0x21 */ u8 pad21[4];
    /* 0x25 */ u8 unk25;
    /* 0x26 */ u8 pad26[6];
    /* 0x2C */ s16 unk2C;
} RvR3_Dc90ViewK;

typedef struct RvR3_PtB {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 z;
    /* 0x06 */ u8 pad6;
    /* 0x07 */ u8 r;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 pad9;
} RvR3_PtB; // size = 0xA

typedef struct RvR3_DcA0ViewB {
    /* 0x00 */ u8 pad0[0x14];
    /* 0x14 */ u8 *unk14;
} RvR3_DcA0ViewB;

typedef struct RvR3_ActorViewK {
    /* 0x00 */ u8 pad0[0x58];
    /* 0x58 */ s32 unk58;
    /* 0x5C */ u8 pad5C[0x20];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
    /* 0x84 */ f32 unk84;
    /* 0x88 */ f32 unk88;
    /* 0x8C */ u8 pad8C[4];
    /* 0x90 */ f32 unk90;
    /* 0x94 */ u8 pad94[0x52];
    /* 0xE6 */ s16 unkE6;
    /* 0xE8 */ u8 padE8[6];
    /* 0xEE */ s16 unkEE;
    /* 0xF0 */ u8 padF0[0x64];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
} RvR3_ActorViewK;

#define RvR3_DC90K ((RvR3_Dc90ViewK *)D_807FDC90)
#define RvR3_DCA0B ((RvR3_DcA0ViewB *)D_807FDCA0)
#define RvR3_AK ((RvR3_ActorViewK *)D_807FBB40)
#define RvR3_PT(off) ((RvR3_PtB *)(RvR3_DCA0B->unk14 + (off)))

u8 func_8072D13C(u8 arg0, u8 arg1) {
    u8 p1;
    u8 p2;
    u8 p3;
    u8 type;
    s16 x;
    s16 y;
    s16 z;
    u8 moved;
    u8 q1;
    u8 new_var;
    u8 q2;
    u8 key;
    s32 v;
    s32 idx;
    s32 dir;
    s32 off;

    idx = (dir = RvR3_DC90K->unk25);
    dir = dir & 0x80;
    idx = idx & 0x7F;
    key = ((D1Pair *)D1DC98G->unk20)[idx].a;
    type = ((D1Pair *)D1DC98G->unk20)[idx].b;
    off = key * 10;
    x = RvR3_PT(off)->x;
    y = RvR3_PT(off)->y;
    z = RvR3_PT(off)->z;
    moved = ((RvR3_AK->unk7C - x) * (RvR3_AK->unk7C - x) + (RvR3_AK->unk84 - z) * (RvR3_AK->unk84 - z)) < (f32)(RvR3_PT(off)->r * RvR3_PT(off)->r);
    if ((arg1 & 1) && RvR3_AK->unk88 == RvR3_AK->unk7C && RvR3_AK->unk90 == RvR3_AK->unk84) {
        RvR3_DC90K->unk20++;
        if (RvR3_DC90K->unk20++ > 0x10) {
            moved = 1;
            RvR3_DC90K->unk20 = 0;
        }
    } else {
        RvR3_DC90K->unk20 = 0;
    }
    switch (arg0) {
        case 0x49:
            v = idx + 1;
            key = (v < D1DC9CG->unk11) ? v : 0;
            RvR3_AK->unkEE = RvR3_AK->unkE6 = mathAngleBetweenPoints2D(RvR3_PT(((D1Pair *)D1DC98G->unk20)[key].a * 10)->x, RvR3_PT(((D1Pair *)D1DC98G->unk20)[key].a * 10)->z, x, z);
        case 0x42:
        case 0x5B:
            RvR3_DC90K->unkA = x;
            RvR3_DC90K->unkC = y;
            RvR3_DC90K->unkE = z;
            break;
        case 2:
        case 0x26:
        case 0x60:
            if (!moved) {
                RvR3_DC90K->unkA = x;
                RvR3_DC90K->unkC = y;
                RvR3_DC90K->unkE = z;
            } else if (type == 6) {
                RvR3_DC90K->unk25 = RvR3_PT(off)->unk8;
            } else if (idx + 1 < D1DC9CG->unk11) {
                RvR3_DC90K->unk25 = idx + 1;
            } else {
                RvR3_DC90K->unk25 = 0;
            }
            break;
        case 3:
            if (moved) {
                if (dir != 0) {
                    if (idx > 0) {
                        idx = (u8)(idx - 1);
                    } else {
                        idx = (u8)(idx + 1);
                        dir = 0;
                    }
                } else if (idx < D1DC9CG->unk11 - 1) {
                    idx = (u8)(idx + 1);
                } else {
                    idx = (u8)(idx - 1);
                    dir = 0x80;
                }
                RvR3_DC90K->unk25 = dir | idx;
            } else {
                RvR3_DC90K->unkA = x;
                RvR3_DC90K->unkC = y;
                RvR3_DC90K->unkE = z;
            }
            break;
    }
    idx = RvR3_DC90K->unk25 & 0x7F;
    if (moved) {
        RvR3_DC90K->unk1A |= 4;
        switch (type) {
            case 1:
                new_var = ((D1Pair *)D1DC98G->unk20)[idx].a;
                key = new_var;
                RvR3_AK->unkEE = RvR3_AK->unkE6 = func_8072D08C();
                RvR3_AK->unk7C = RvR3_PT(key * 10)->x;
                RvR3_AK->unk80 = RvR3_PT(key * 10)->y;
                RvR3_AK->unk84 = RvR3_PT(key * 10)->z;
                break;
            case 2:
                RvR3_AK->unk154 = 0x26;
                RvR3_AK->unk155 = 0;
                break;
            case 4:
                RvR3_AK->unk154 = 0x19;
                RvR3_AK->unk155 = 0;
                RvR3_DC90K->unk2C = RvR3_PT(off)->unk8;
                break;
            case 5:
                actorSetTargetSpeed(D_807FBB40, RvR3_PT(off)->unk8);
                return moved;
            case 7:
                RvR3_AK->unk154 = 0x3B;
                moved = 0;
                break;
            case 8:
                RvR3_AK->unk154 = 0x13;
                RvR3_AK->unk155 = 0;
                break;
            case 3:
                if (RvR3_AK->unk58 == 0xAF) {
                    RvR3_AK->unk154 = 0x37;
                    RvR3_AK->unk155 = 0;
                }
                D_80744508++;
                RvR3_AK->unk154 = 0x40;
                break;
        }
    } else {
        RvR3_DC90K->unk1A &= 0xFFFB;
    }
    return moved;
}

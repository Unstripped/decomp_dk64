// func_806A5174 (src/global/A8400.c): stage 6: 405 insns, frame 0x80, stack offsets and rodata byte-identical; only temp-register choice differs (raw diff 364 lines, all t/v renames) + jtbl/double reloc form. Same blocks/callee-saved. Best levers found: double literals must be exact truncated values (131.1999969482421875 etc.), clamp = 3-arg macro, 8 declared locals (2 unused between sp74 and sp68) to get frame 0x80.
typedef struct L8bNode {
    /* 0x00 */ u8 pad0[0x2C];
    /* 0x2C */ u8 unk2C;
} L8bNode;

typedef struct L8bData {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ u8 pad4[0x54];
    /* 0x58 */ u32 unk58;
    /* 0x5C */ u8 pad5C[0x20];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
    /* 0x84 */ f32 unk84;
    /* 0x88 */ u8 pad88[0xD6];
    /* 0x15E */ u8 unk15E;
    /* 0x15F */ u8 pad15F[0x1D];
    /* 0x17C */ L8bNode *unk17C;
} L8bData;

typedef struct L8bSub {
    /* 0x00 */ u8 pad0[0x4];
    /* 0x04 */ L8bData *unk4;
    /* 0x08 */ u8 pad8[0x18];
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ u8 pad34[0x8];
    /* 0x3C */ u8 unk3C;
} L8bSub;

typedef struct L8bXform {
    /* 0x00 */ u8 pad0[0x7C];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
} L8bXform;

typedef struct L8bBounds {
    /* 0x000 */ u8 pad0[0x270];
    /* 0x270 */ s16 unk270;
    /* 0x272 */ s16 unk272;
    /* 0x274 */ s16 unk274;
    /* 0x276 */ s16 unk276;
} L8bBounds;

extern u8 *D_807FC924;
extern u8 D_807FC929;
extern s16 D_80744490;

void actorGetNodePos(void *, s32, f32 *, f32 *, f32 *);
s32 func_80613448(void *);
s32 func_80626F8C(f32, f32, f32, f32 *, f32 *, s32, f32, s32);

#define L8B_CUR ((L8bBounds *) (D_807FC924 + (D_807FC929 * 0x2F0)))
#define L8B_CLAMP(x, l, h) ((x) < (l) ? (l) : ((h) < (x) ? (h) : (x)))

void func_806A5174(Actor *arg0, L8bSub *arg1, f32 arg2) {
    f32 sp7C;
    f32 sp78;
    s32 sp74;
    f32 lo;
    f32 hi;
    f32 sp68;
    f32 sp64;
    f32 sp60;

    sp74 = 0;
    switch (arg1->unk4->unk58) {
    case 0x22:
    case 0x2E:
    case 0x7C:
    case 0x7D:
    case 0x7E:
    case 0x7F:
    case 0xDA:
    case 0x100:
        arg1->unk3C = 1;
        arg1->unk24 = (f32) L8B_CUR->unk274;
        arg1->unk28 = (f32) L8B_CUR->unk276;
        break;
    case 0xFE:
        sp74 = arg1->unk4->unk17C->unk2C;
        break;
    default:
        if (arg1->unk4->unk0 != 0) {
            switch (func_80613448(arg1->unk4)) {
            case 0x11:
            case 0x12:
            case 0x1D:
            case 0x1F:
            case 0x2E:
            case 0x3D:
            case 0x45:
            case 0x5E:
            case 0x62:
                sp74 = 1;
                break;
            case 0x13:
            case 0x17:
            case 0x3E:
            case 0x56:
            case 0x65:
                sp74 = 2;
                break;
            case 0x35:
                sp74 = 3;
                break;
            case 0x1:
            case 0x2:
            case 0x3:
            case 0x4:
            case 0x5:
            case 0x6:
            case 0x7:
            case 0x8:
            case 0xA:
            case 0xB:
            case 0xC:
            case 0xD:
            case 0xE:
            case 0xF:
            case 0x10:
                sp74 = 6;
                break;
            case 0x18:
                sp74 = 9;
                break;
            }
        }
        break;
    }
    if ((arg1->unk4->unk0 == 0) && (arg1->unk3C == 0)) {
        arg1->unk3C = 1;
        arg1->unk24 = (f32) L8B_CUR->unk270;
        arg1->unk28 = (f32) L8B_CUR->unk272;
    }
    if (arg1->unk3C == 0) {
        if (sp74 == 0) {
            sp68 = arg1->unk4->unk7C;
            sp64 = arg1->unk4->unk80 + 1.5 * arg1->unk4->unk15E;
            sp60 = arg1->unk4->unk84;
        } else {
            actorGetNodePos(arg1->unk4, sp74, &sp68, &sp64, &sp60);
        }
        if (func_80626F8C(sp68, sp64, sp60, &sp7C, &sp78, 0, 1.0f, D_807FC929) != 0) {
            sp7C = arg1->unk24;
            sp78 = arg1->unk28;
        }
        sp7C = L8B_CLAMP(sp7C, (f32) (L8B_CUR->unk270 - 0x64), (f32) (L8B_CUR->unk274 + 0x64));
        sp78 = L8B_CLAMP(sp78, (f32) (L8B_CUR->unk272 - 0x64), (f32) (L8B_CUR->unk276 + 0x64));
        arg1->unk24 = sp7C;
        arg1->unk28 = sp78;
    }
    sp7C = arg1->unk24;
    sp78 = arg1->unk28;
    if (((f32) D_80744490 * 0.5f) < sp7C) {
        sp7C = sp7C - 131.1999969482421875;
    } else {
        sp7C = sp7C + 131.1999969482421875;
    }
    if (sp78 > 60.7999992370605469) {
        sp78 = sp78 - 60.7999992370605469;
    }
    sp7C = (f32) L8B_CLAMP((f64) sp7C, (f64) L8B_CUR->unk270 + 91.1999969482421875 + 5.0,
                           (f64) L8B_CUR->unk274 - 96.1999969482421875);
    sp78 = (f32) L8B_CLAMP((f64) sp78, (f64) L8B_CUR->unk272 + 60.7999992370605469 + 5.0,
                           (f64) L8B_CUR->unk276 - 65.7999992370605469);
    arg1->unk2C = ((sp7C - arg1->unk2C) * arg2) + arg1->unk2C;
    arg1->unk30 = ((sp78 - arg1->unk30) * arg2) + arg1->unk30;
    ((L8bXform *) arg0)->unk7C = (((arg1->unk2C - arg1->unk24) * arg1->unk20) + arg1->unk24);
    ((L8bXform *) arg0)->unk80 = (((arg1->unk30 - arg1->unk28) * arg1->unk20) + arg1->unk28);
}

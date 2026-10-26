// func_8072C918 (src/global/12E800.c): stage 4: compiles, 19056/19120 bytes (16 insns short), frame 0x60 vs 0x58; register assignment matches target (dist t1, ang t2, st t3, near t4, ret v0, type a3 not yet) but spill slots/home layout differ (target homes: st 0x54 dist 0x50 type 0x4E sp4D 0x4D ang 0x4A near 0x40 bb40-temp 0x3C; mine temp slots 0x24/0x34/0x5c). Key trick: the target keeps ang=|DC90->unk8 - actor->unkEE| live (spilled around both early calls) although nothing reads it: an empty 'if (ang != 0) {}' before the switch reproduces that (plain unused ang gets deleted). Also ret (s32, raw v0, used in case 0x23 compares) + type (u8 copy). func_80726164 is (Actor*, s16 x, s16 y, s16 z, void *D_807FDCA0). permuter unusable (late_rodata).
typedef struct C1Sub4 {
    /* 0x00 */ u8 pad0[0x64];
    /* 0x64 */ u16 unk64;
    /* 0x66 */ u8 pad66[0x2];
} C1Sub4; // size = 0x68

typedef struct C1Act {
    /* 0x00 */ u8 pad0[0x4];
    /* 0x04 */ C1Sub4 *unk4;
    /* 0x08 */ u8 pad8[0x58];
    /* 0x60 */ u32 unk60;
    /* 0x64 */ u8 pad64[0x6];
    /* 0x6A */ u16 unk6A;
    /* 0x6C */ u8 pad6C[0x10];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
    /* 0x84 */ f32 unk84;
    /* 0x88 */ u8 pad88[0x66];
    /* 0xEE */ s16 unkEE;
    /* 0xF0 */ u8 padF0[0x64];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 pad155[0x1F];
    /* 0x174 */ D1S174 *unk174;
    /* 0x178 */ s16 *unk178;
} C1Act;

typedef struct C1Dc90 {
    /* 0x00 */ u8 pad0[0x8];
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ u8 pad10[0xA];
    /* 0x1A */ u16 unk1A;
    /* 0x1C */ u8 pad1C[0x4];
    /* 0x20 */ u8 unk20;
    /* 0x21 */ u8 pad21[0x5];
    /* 0x26 */ s16 unk26;
    /* 0x28 */ u8 pad28[0xE];
    /* 0x36 */ u8 unk36;
    /* 0x37 */ u8 pad37[0x1];
} C1Dc90;

typedef struct C1Dc98 {
    /* 0x00 */ u8 pad0[0x26];
    /* 0x26 */ s16 unk26;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ u8 pad2A[0x1C];
    /* 0x46 */ u16 unk46;
} C1Dc98;

typedef struct C1Dc9c {
    /* 0x00 */ u8 pad0[0xC];
    /* 0x0C */ u8 unkC;
    /* 0x0D */ u8 unkD;
    /* 0x0E */ u8 padE[0x2];
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 pad11[0x3];
} C1Dc9c;

#define C1B40 ((C1Act *)D_807FBB40)
#define C1D90 ((C1Dc90 *)D_807FDC90)
#define C1D98 ((C1Dc98 *)D_807FDC98)
#define C1D9C ((C1Dc9c *)D_807FDC9C)

s32 func_80726164(Actor *, s16, s16, s16, void *);
s32 func_8072DE10(u16);
void func_8072DE44(s32);

void func_8072C918(s32 arg0, s32 arg1, s32 arg2) {
    D1S174 *st;
    s32 dist;
    s32 near;
    s16 ang;
    u8 sp4D;
    u8 type;
    s32 ret;
    f32 dx;
    f32 dy;
    f32 dz;
    s16 a;
    s16 b;
    u8 c;

    st = D_807FDC94->unk174;
    dx = D_807FBB40->unk7C - D_807FDC94->unk7C;
    dy = D_807FBB40->unk80 - D_807FDC94->unk80;
    dz = D_807FBB40->unk84 - D_807FDC94->unk84;
    dist = (s32)((dx * dx) + (dy * dy) + (dz * dz));
    near = dist < arg0;
    if (near == 0) {
        near = (C1D98->unk46 & 4) != 0;
    }
    a = C1D90->unk8;
    b = C1B40->unkEE;
    if (a < b) {
        ang = b - a;
    } else {
        ang = a - b;
    }
    if ((func_80726164(D_807FBB40, D_807FDC94->unk7C, D_807FDC94->unk80, D_807FDC94->unk84, D_807FDCA0) != 0) && !(C1D98->unk46 & 0x2000) && !(st->unk1F0 & 0x8000)) {
        C1D90->unk1A |= 0x400;
    } else {
        C1D90->unk1A &= 0xFBFF;
    }
    ret = func_8072C670(dist < 0x1388, &sp4D);
    type = ret;
    if (ang != 0) {
    }
    switch (C1B40->unk154) {
        case 1:
        case 2:
        case 3:
            if (C1D98->unk26 == C1B40->unk4->unk64) {
                func_80614EBC(D_807FBB40, C1D98->unk28);
            }
            if (C1D9C->unkC != C1D90->unk26) {
                func_8072B324(D_807FBB40, C1D9C->unkC);
            }
        case 4:
        case 0x11:
        case 0x19:
            if ((near & 0xFF) && (C1B40->unk60 & 0x100) && (sp4D != 0) && (C1D90->unk1A & 0x400)) {
                if (C1D90->unk1A & 0x800) {
                    if (func_8072DE10(0x2710) != 0) {
                        func_8072B59C(type, C1D9C->unkD, arg2);
                        return;
                    }
                }
                if (!(C1D90->unk1A & 0x800)) {
                    func_8072B59C(type, C1D9C->unkD, arg2);
                    return;
                }
            }
            break;
        case 0x34:
            if (dist < *C1B40->unk178) {
                func_8072B59C(0x24, 0, arg1);
                return;
            }
        case 0x23:
            if ((C1D90->unk36 != ret) && ((sp4D == 0) || (ret >= 7))) {
                func_8072C870(type, C1D9C->unkD, arg2);
                return;
            }
            if (near & 0xFF) {
                if (!(C1D90->unk1A & 0x400)) {
                    c = C1D9C->unkC;
                    func_8072B59C(0x35, (s16)(s32)(c * 0.667), arg1);
                    C1D90->unk20 = 0x3C;
                    C1D90->unkA = D_807FDC94->unk88;
                    C1D90->unkC = D_807FDC94->unk8C;
                    C1D90->unkE = D_807FDC94->unk90;
                    return;
                }
                c = C1D9C->unkD;
                if (C1D90->unk26 < c) {
                    func_8072B59C(type, c, arg2);
                    return;
                }
            } else {
                func_8072B59C(C1D9C->unk10, C1D9C->unkC, arg1);
                return;
            }
            break;
        case 0x33:
            if ((!(near & 0xFF) || !(C1D90->unk1A & 0x400)) && (C1B40->unk6A & 1)) {
                func_8072B59C(C1D9C->unk10, C1D9C->unkC, arg1);
                return;
            }
            break;
        case 7:
            dz = D_807FBB40->unk84 - C1D90->unkE;
            dx = D_807FBB40->unk7C - C1D90->unkA;
            if (((dz * dz) + (dx * dx)) < 400.0f) {
                if (!(C1D90->unk1A & 0x80)) {
                    func_8072DE44(C1D98->unk28);
                } else {
                    func_8072C870(7, C1D9C->unkD, arg2);
                }
            }
        case 0x10:
            if (C1D90->unk36 != type) {
                func_8072C870(type, C1D9C->unkD, arg2);
            }
            if (near & 0xFF) {
                if (!(C1D90->unk1A & 0x400)) {
                    func_8072B59C(C1D9C->unk10, C1D9C->unkC, arg1);
                    return;
                }
            } else {
                func_8072B59C(C1D9C->unk10, C1D9C->unkC, arg1);
                return;
            }
            break;
        case 0x35:
            if (C1D90->unk1A & 0x400) {
                func_8072B59C(type, C1D9C->unkD, arg2);
                return;
            }
            c = C1D90->unk20;
            C1D90->unk20 = c - 1;
            if (c == 0) {
                func_8072B59C(C1D9C->unk10, C1D9C->unkC, arg1);
            }
            break;
    }
}

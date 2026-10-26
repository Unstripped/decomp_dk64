// func_8072C918 (src/global/12E800.c): stage 6, ONE diff instruction left (+ reloc-only jtbl_8075FE10 / .rodata+off literal): case 0x23 'beq t5,v0' (target) vs 'beq v0,t5' (mine) operand order, independent of source operand order/structure. 'near = (C1D90->unk20-- == 0); if (near) {...}' (reusing near for the flag) fixed the sltiu t4 diff. Same size 19120, frame 0x58, every slot equal. Tried for the beq: swaps, casts, nested/else forms, dead reads, callee s32 retyping (59C/870/B324/614EBC), u8 local copy of unk36, no-ret variants.
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
    u8 pad0;
    u8 type;
    u8 sp4D;
    s16 ang;
    u32 ret;
    s32 near;
    C1Act *me;

    st = D_807FDC94->unk174;
    me = C1B40;
#define SQ(x) ((x) * (x))
    dist = (s32)(SQ(me->unk7C - D_807FDC94->unk7C) + SQ(me->unk80 - D_807FDC94->unk80) + SQ(me->unk84 - D_807FDC94->unk84));
    near = dist < arg0;
    if (near == 0) {
        near = (C1D98->unk46 & 4) != 0;
    }
    if (C1D90->unk8 < me->unkEE) {
        ang = me->unkEE - C1D90->unk8;
    } else {
        ang = C1D90->unk8 - me->unkEE;
    }
    if ((func_80726164((Actor *)me, D_807FDC94->unk7C, D_807FDC94->unk80, D_807FDC94->unk84, D_807FDCA0) != 0) && !(C1D98->unk46 & 0x2000) && !(st->unk1F0 & 0x8000)) {
        C1D90->unk1A |= 0x400;
    } else {
        C1D90->unk1A &= 0xFBFF;
    }
    ret = func_8072C670(dist < 0x1388, &sp4D);
    type = ret;
    if (ang != 0) {
    }
    if (near == 5) {
    }
    if (dist == 3) {
    }
    switch (C1B40->unk154) {
        case 1:
        case 2:
        case 3:
            if (C1B40->unk4->unk64 == C1D98->unk26) {
                func_80614EBC(D_807FBB40, C1D98->unk28);
            }
            if (C1D90->unk26 != C1D9C->unkC) {
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
            me = (C1Act *)C1B40->unk178;
            if (dist < *(s16 *)me) {
                func_8072B59C(0x24, 0, arg1);
                return;
            }
        case 0x23:
            if ((ret != C1D90->unk36) && ((sp4D == 0) || ((s32)ret >= 7))) {
                func_8072C870(type, C1D9C->unkD, arg2);
                return;
            }
            if (near & 0xFF) {
                if (!(C1D90->unk1A & 0x400)) {
                    func_8072B59C(0x35, (s16)(s32)(C1D9C->unkC * 0.667), arg1);
                    C1D90->unk20 = 0x3C;
                    C1D90->unkA = D_807FDC94->unk88;
                    C1D90->unkC = D_807FDC94->unk8C;
                    C1D90->unkE = D_807FDC94->unk90;
                    return;
                }
                if (C1D90->unk26 < C1D9C->unkD) {
                    func_8072B59C(type, C1D9C->unkD, arg2);
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
            if ((SQ(D_807FBB40->unk84 - C1D90->unkE) + SQ(D_807FBB40->unk7C - C1D90->unkA)) < 400.0f) {
                if (!(C1D90->unk1A & 0x80)) {
                    func_8072DE44(C1D98->unk28);
                } else {
                    func_8072C870(7, C1D9C->unkD, arg2);
                }
            }
        case 0x10:
            if (type != C1D90->unk36) {
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
            near = (C1D90->unk20-- == 0);
            if (near) {
                func_8072B59C(C1D9C->unk10, C1D9C->unkC, arg1);
            }
            break;
    }
}

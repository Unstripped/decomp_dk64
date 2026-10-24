// func_806BA240 (src/global/BDEE0.c): NM2: 6 insns regalloc: u8 temp v1 vs t5. Needs s32 actorGetNodePos + (node ^ 0) == 1. kind=x;node=kind gives t5 but frame 0x60.
typedef struct R1DView {
    /* 0x000 */ u8 pad0[0xC0];
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ u8 padC4[0x2C];
    /* 0x0F0 */ s16 unkF0;
    /* 0x0F2 */ u8 padF2[0x42];
    /* 0x134 */ s16 unk134;
    /* 0x136 */ u8 pad136[0x42];
    /* 0x178 */ s16 *unk178;
} R1DView;

typedef struct R1DView90 {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ Actor *unk4;
    /* 0x08 */ u8 pad8[0xE];
    /* 0x16 */ s16 unk16;
    /* 0x18 */ u8 pad18[2];
    /* 0x1A */ u16 unk1A;
    /* 0x1C */ u16 unk1C;
} R1DView90;

#define R1DA ((R1DView *)D_807FBB40)
#define R1D90 ((R1DView90 *)D_807FDC90)

extern s32 D_807FDCA0;
extern Actor *D_807FDC94;
extern void *D_807FDC9C;
s32 func_80611A44(void);
void func_80614EBC(Actor *, s32);
void func_80714CC0(void *, f32, f32, f32, f32);
s32 actorGetNodePos(Actor *, s32, f32 *, f32 *, f32 *);
void func_806BA130(void);
s32 func_806B9EB4(u8, u8, f32, f32, f32);

typedef struct R1DNode {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ u8 pad8[8];
    /* 0x10 */ s16 unk10;
} R1DNode;

typedef struct R1DSub4 {
    /* 0x00 */ R1DNode *unk0;
    /* 0x04 */ u8 pad4[0x60];
    /* 0x64 */ u16 unk64;
} R1DSub4;

typedef struct R1DViewTgt {
    /* 0x000 */ u8 pad0[0x134];
    /* 0x134 */ s16 unk134;
} R1DViewTgt;

typedef struct R1DViewA0 {
    /* 0x00 */ u8 pad0[0x1C];
    /* 0x1C */ Actor *unk1C;
    /* 0x20 */ u8 unk20;
} R1DViewA0;

#define R1DA0 ((R1DViewA0 *)D_807FDCA0)

extern u8 *D_807FC924;
extern u8 D_8071FB34[];
void func_80609140(s32, s32, f32, f32, s32, s32);
void func_80613C48(void *, s16, f32, f32);
s32 func_806EB0C0(s32, void *, s32);
s32 func_8072DCF4(void *, void *, s32);

s32 func_806BA240(u8 arg0, s16 arg1) {
    s16 *p;
    Actor *tgt;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    u8 kind;
    R1DSub4 *sub;
    s32 var;
    s32 node;

    p = R1DA->unk178;
    tgt = R1DA0->unk1C;
    if (tgt != NULL && tgt->unk154 == 0x23 && R1DA0->unk20 < 10) {
        if (D_807FBB40->unk154 != 0x15 && D_807FBB40->unk154 != 0x17) {
            D_807FBB40->unk5C = 0x80;
            D_807FBB40->unk154 = 0x15;
            D_807FBB40->unk155[0] = 0;
            func_80614EBC(D_807FBB40, 0);
            D_807FBB40->unk132 = 2;
            p[3] = D_807FBB40->unk7C;
            p[4] = D_807FBB40->unk84;
        }
    }
    if (D_807FBB40->unk154 == 0x15 && (tgt == NULL || tgt->unk154 != 0x23)) {
        func_806BA130();
    }
    if (D_807FBB40->unk154 == 0x15) {
        kind = D_807FDC9C->unkA;
        node = D_807FDC9C->unkA;
        if (node == 5 || node == 7) {
            sub = (R1DSub4 *)tgt->unk4;
            if ((sub->unk64 == 0x21E || sub->unk64 == 0x21F) && sub->unk0->unk4 >= 4.0f && sub->unk0->unk4 <= 12.0f) {
                D_807FBB40->unk132 = 4;
            } else {
                D_807FBB40->unk132 = 2;
            }
        }
        if ((node ^ 0) == 1) { /* ^ 0 flips bnel operand order */
            D_807FBB40->unk132 = 8;
        }
        if (R1DA->unkF0 != 0) {
            R1DA->unkF0 = R1DA->unkF0 - 1;
        }
        if (tgt->unk155[0] != 0) {
            if (tgt->unk155[0] == 1 && D_807FBD70 == 2 && func_8072DCF4(tgt, D_807FBB4C, 0x1F40) != 0) {
                if (D_807FC924[0x2C0] == 1) {
                    func_806EB0C0(0x32, D_807FBB40, 0);
                } else {
                    if (((func_80611A44() >> 15) % 1000) >= 0x1F5) {
                        var = 0x21F;
                    } else {
                        var = 0x21E;
                    }
                    func_80614EBC(tgt, var);
                    tgt->unk155[0] = 2;
                }
            } else if (D_807FBD70 == 4) {
                R1D90->unk16 = ((R1DSub4 *)D_807FDC94->unk4)->unk0->unk10;
                D_807FBB40->unk60 |= 0x20000000;
                if (R1DA->unkF0 == 0) {
                    R1DA->unkF0 = 0x28;
                    func_80714CC0(D_8071FB34, 2.0f, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84);
                    func_80609140(0x1CA, 0x7FFF, 63.0f, 1.0f, 0, 0);
                    func_80614EBC(tgt, 0x220);
                    tgt->unk155[0] = 2;
                    ((R1DViewTgt *)tgt)->unk134 = ((R1DViewTgt *)tgt)->unk134 - 1;
                    if (((R1DViewTgt *)tgt)->unk134 == 0) {
                        tgt->unk154 = 0x37;
                        tgt->unk155[0] = 0;
                    }
                }
            }
        }
        R1DA0->unk20 = R1DA0->unk20 + 1;
        actorGetNodePos(tgt, node, &sp4C, &sp48, &sp44);
        if (R1D90->unk1A & 0x80) {
            s16 sv0;
            s16 sv1;

            if (!(R1D90->unk1C & 0x80)) {
                R1DA->unkC0 = 300.0f;
            }
            if (R1DA->unkC0 > 0.0f) {
                return 0;
            }
            D_807FBB40->unk144 = 0x24;
            if (arg1 != 0) {
                func_80613C48(D_807FBB40, arg1, 0.0f, 4.0f);
            }
            sv0 = p[0];
            sv1 = p[1];
            p[0] = sv0 + (-sv0) * 0.1;
            p[1] = sv1 + (-sv1) * 0.1;
            if (node < 0xB) {
                D_807FBB40->unkE6 = tgt->unkE6;
            }
            D_807FBB40->unk7C = sp4C;
            D_807FBB40->unk84 = sp44;
            D_807FBB40->unk80 = sp48;
            if (func_806B9EB4(kind, arg0, sp4C, sp48, sp44) != 0) {
                return 1;
            }
        }
    }
    return 0;
}

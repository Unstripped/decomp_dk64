// func_80027728 (src/jetpac/3480.c): func_80027728 (src/jetpac/3480.c): stage 5/6 park: frame+regs match; text size equal after perm. Fixes found: (*new_var)=&D_8002F050,(*new_var2)=&D_8002F054 locals set before 'if (unk38==0)' reproduce lui at order in the 8-arg func_80027250 call; unk14=0.8f before unk38=2 (permuter); s32 new_var4=*new_var3(&D_8002F06C). Left: t7/v0 for D_8002F06C load in 'unk8 = ...' expr (lw v0 vs lw t7), 2 insns of mul.d/add.s operand order, and later-fn pressure (sw a1,0x6c(sp) in func_800286D0 region is other fn) | C1g: only diff left is the D_8002F06C load colour ($v0 vs $t7 CSE temp). With `new_var3 = &D_8002F06C` and first use `(f32)*new_var3` (second use direct `D_8002F06C`, no new_var4) the ints match (ring $t7) but the add.s operand order flips and FP ring follows (39 diff lines): the earlier `(f32)D_8002F06C` in the func_80027250 args makes its VN older. Tried no-op (s32) casts on either use, *(s32*)&D alias forms, pointer deref in the early use (changes code size), assoc/order variants: none flip it back. uopt: the named local/direct global is a coloured candidate ($2); unnamed via pointer is a ring temp.
typedef struct {
    u8 pad0[8];
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    u8 unk18;
    u8 unk19;
    u8 unk1A;
    u8 pad1B;
    s32 unk1C;
    u8 pad20[4];
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    s32 unk30;
    s32 unk34;
    s32 unk38;
    s32 unk3C;
    s32 unk40;
} J3Item;

typedef struct {
    u8 pad0[4];
    s32 unk4;
    u8 pad8[4];
    s32 unkC;
    s32 unk10;
    u8 pad14[0x144 - 0x14];
    s32 unk144;
} J3Inner;

s32 jetpacCheckLedgeCollision(f32, f32, f32, f32, s32);
s32 func_80027330(f32);
extern s32 D_8002F064;
extern f32 D_8002F050;
extern f32 D_8002F054;
extern f32 D_8002F058;
extern f32 D_8002F05C;
extern s32 D_8002F06C;
extern s32 D_8002F070;
extern s32 D_8002F074;
extern s32 D_8002F078;
void flagSet(s32, s32, s32);
void func_80024E70(s32);
void func_80027D64(void *);
void func_80028340();

void func_80027728(J3Item *arg0) {
    J3Inner *inner = (J3Inner *)((u8 *)&D_8002EC30 + D_8002EC30.unk344 * 0x194 + 0x1C);
    f32 *new_var;
    f32 *new_var2;
    s32 *new_var3;
    s32 new_var4;

    if (arg0->unk1C == 0) {
        return;
    }
    if (inner->unkC >= 8) {
        return;
    }
    if (arg0->unk34 < 0x14) {
        arg0->unk34 = arg0->unk34 + 1;
        return;
    }
    if (arg0->unk1C == 1) {
        arg0->unk1C = 2;
    }
    new_var = &D_8002F050;
    new_var2 = &D_8002F054;
    new_var3 = &D_8002F06C;
    if (arg0->unk38 == 0) {
        if (arg0->unk14 > 0.0f && D_8002F064 != 4) {
            f32 x = arg0->unk8;
            s32 hit = jetpacCheckLedgeCollision((f32)arg0->unk24 + x + arg0->unk10, (f32)arg0->unk28 + arg0->unkC + arg0->unk14,
                                                (f32)arg0->unk2C + x + arg0->unk10, (f32)arg0->unk30 + arg0->unkC + arg0->unk14, 0);
            if (hit >= 0) {
                arg0->unkC = *(f32 *)((u8 *)&D_8002EC30 + hit * 0x34 + 0x354) - 16.0f;
                arg0->unk14 = 0.0f;
            } else {
                arg0->unkC = arg0->unkC + arg0->unk14;
            }
        }
        if (D_8002F064 == 3) {
            if (func_80027250(arg0->unk8 + (f32)arg0->unk24, arg0->unkC + (f32)arg0->unk28, arg0->unk8 + (f32)arg0->unk2C, arg0->unkC + (f32)arg0->unk30,
                              (*new_var) + (f32)D_8002F06C, (*new_var2) + (f32)D_8002F070, (*new_var) + (f32)D_8002F074,
                              (*new_var2) + (f32)D_8002F078)) {
                arg0->unk38 = 1;
                inner->unk4 += arg0->unk3C;
                func_80024E70(4);
            }
        }
    }
    if (arg0->unk38 == 1) {
        if (D_8002F064 == 4) {
            arg0->unk38 = 0;
            arg0->unk14 = 0.8f;
        } else {
            new_var4 = *new_var3;
            arg0->unk8 = (D_8002F050 - (f32)2 * D_8002F058 + (f32)new_var4) + (D_8002F074 - D_8002F06C - arg0->unk2C + arg0->unk24) * 0.5;
            arg0->unkC = D_8002F054 - D_8002F05C + (f32)D_8002F078 - (f32)arg0->unk30;
            if (func_80027330(arg0->unk8)) {
                arg0->unk8 = 168.0f;
                arg0->unk14 = 0.8f;
                arg0->unk38 = 2;
            }
        }
    }
    if (arg0->unk38 == 2) {
        arg0->unkC = arg0->unkC + arg0->unk14;
        if (inner->unkC < 2) {
            f32 lim = (f32)(0x98 - (inner->unkC << 4));
            if (lim <= arg0->unkC) {
                arg0->unkC = lim;
                inner->unkC = inner->unkC + 1;
                func_80024E70(2);
                if (inner->unkC < 2) {
                    inner->unk10 = inner->unk10 - 1;
                } else {
                    func_80028340(inner);
                }
            }
        } else if (168.0f <= arg0->unkC) {
            inner->unkC = inner->unkC + 1;
            func_80024E70(2);
            if (inner->unkC < 8) {
                func_80028340(inner);
            } else {
                arg0->unk1C = 0;
            }
        }
    }
}

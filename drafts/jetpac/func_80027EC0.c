// func_80027EC0 (src/jetpac/3480.c): func_80027EC0 (src/jetpac/3480.c): stage 5 park: same new_var/new_var2 call fix as 80027728 gets the lui at order right; remaining: li t5,2 placement + 'sw via a0 vs s0' at 'unk34+1' early return, and v0/v1 swap in switch cases 1/3/4 (v,t8/t4 temp numbering). Tried: switch (field), per-case scoped v/idx (all 16 combos), 't' for unk144, ++ forms - none improved | C1g: diff 74 lines (many are branch shifts from +4 size). (1) switch cases 1 and 3/4: target colours the CSE'd load of inner->unk144 (used by `v = unk34 - unk144` and `arg0->unk34 = inner->unk144`) $v0 and v $v1; ours reverse = v coloured first (v has many refs, uopt -l 6: candidate 103 v assigned before CSE load). Renaming v per case (v6/v/w, idx for case 6) changes nothing; extra decl order no effect. (2) `li t5,2` constant hoist and delay-slot fill at the early `unk34 + 1` return: target puts li t5,2 in the block before the slt (then the `beqz` delay is `addiu t3`), ours after; empty-if dummies (`if (x == 2) {}`, before or inside) only grow the diff (210+). Variants of the early return (unk34++, += 1, inverted if) identical.
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

void func_80027EC0(J3Item *arg0) {
    J3Inner *inner = (J3Inner *)((u8 *)&D_8002EC30 + D_8002EC30.unk344 * 0x194 + 0x1C);
    s32 v;
    s32 idx;
    f32 *new_var;
    f32 *new_var2;

    if (inner->unkC == 0) {
        return;
    }
    if (arg0->unk34 < inner->unk144) {
        arg0->unk34 = arg0->unk34 + 1;
        return;
    }
    if (arg0->unk1C == 1) {
        arg0->unk1C = 2;
    }
    new_var = &D_8002F050;
    new_var2 = &D_8002F054;
    if (arg0->unk38 == 0) {
        if (arg0->unk14 > 0.0f) {
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
        if (*(s32 *)((u8 *)&D_8002EC30 + 0x78C) == 2 && D_8002F064 == 3) {
            if (func_80027250(arg0->unk8 + (f32)arg0->unk24, arg0->unkC + (f32)arg0->unk28, arg0->unk8 + (f32)arg0->unk2C, arg0->unkC + (f32)arg0->unk30,
                              (*new_var) + (f32)D_8002F06C, (*new_var2) + (f32)D_8002F070, (*new_var) + (f32)D_8002F074,
                              (*new_var2) + (f32)D_8002F078)) {
                if (arg0->unk40 == 6) {
                    flagSet(0x62, 1, 2);
                }
                inner->unk4 += arg0->unk3C;
                func_80024E70(3);
                func_80027D64(inner);
                return;
            }
        }
    }

    switch (arg0->unk40) {
    case 6:
        arg0->unk34++;
        v = arg0->unk34 - inner->unk144;
        if (v >= 0x97) {
            func_80027D64(inner);
            return;
        }
        v = v % 24;
        if (v < 12) {
            arg0->unk1A = 0xFF;
            arg0->unk18 = 0;
            arg0->unk19 = 0;
        } else if (v < 24) {
            arg0->unk18 = 0xFF;
            arg0->unk19 = 0xFF;
            arg0->unk1A = 0;
        }
        break;
    case 1:
        arg0->unk34++;
        v = arg0->unk34 - inner->unk144;
        if (v >= 0x1C) {
            v -= 0x1C;
            arg0->unk34 = inner->unk144;
        }
        if (v < 0x1C) {
            idx = v / 4 + 1;
            if (idx & 1) {
                arg0->unk1A = 0xFF;
            } else {
                arg0->unk1A = 0;
            }
            if (idx & 2) {
                arg0->unk18 = 0xFF;
            } else {
                arg0->unk18 = 0;
            }
            if (idx & 4) {
                arg0->unk19 = 0xFF;
            } else {
                arg0->unk19 = 0;
            }
        }
        break;
    case 2:
        arg0->unk18 = 0xFF;
        arg0->unk19 = 0xFF;
        arg0->unk1A = 0;
        break;
    case 5:
        arg0->unk19 = 0xFF;
        arg0->unk18 = 0;
        arg0->unk1A = 0;
        break;
    case 3:
    case 4:
        arg0->unk34++;
        v = arg0->unk34 - inner->unk144;
        if (v >= 0x18) {
            v -= 0x18;
            arg0->unk34 = inner->unk144;
        }
        if (v < 12) {
            arg0->unk18 = 0;
            arg0->unk19 = 0;
            arg0->unk1A = 0;
        } else if (v < 24) {
            arg0->unk18 = 0;
            arg0->unk19 = 0xFF;
            arg0->unk1A = 0xFF;
        }
        break;
    }
}

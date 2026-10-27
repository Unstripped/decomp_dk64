// func_8002601C (src/critter/0.c): stage 5 parked NON_MATCHING: 160/160 insns, block structure + beqzl/sb delay slots identical; remaining diff regalloc only: D_807FBB48 ptr a1 (target a2), half-sum a2 (a1), andi/sltu temps a2/a1 (t5/a3), dx/dz FP f12/f14 (f14/f16), temp ring t9,t3 vs t7,t8 at head. Fixes found: dd must reuse an existing local (dist = dx*dx+dz*dz) to avoid uopt sinking it into the flag branch; f=(pl<py+half); if(f) f=..; f=(u8)f!=0; if(f){f=0;if(c)f=1;}; py/pl inline. Tried decl-order shuffle(300), stmt perms, dummies, permuter(unreliable: direct vs baseline score mismatch).
extern void *D_80029BA4;

#define CR58 (*(u8 **)((u8 *)arg0 + 0x58))
void func_8002601C(void *arg0) {
    u8 *m;
    f32 lim;
    f32 fv0;
    f32 dx;
    f32 dz;
    f32 dist;
    f32 ddy;
    s16 half;
    s32 f;

    fv0 = 0.0f;
    lim = (f32)(*(s32 *)(CR58 + 0x18) + 0x1DE84);
    if (D_807444FC != CR58[0x24]) {
        half = (*(s16 *)(CR58 + 0x10) + *(s16 *)(CR58 + 0xC)) >> 1;
        dx = (f32)*(s16 *)(CR58 + 0) - *(f32 *)(D_807FBB48 + 0x7C);
        dz = (f32)*(s16 *)(CR58 + 4) - *(f32 *)(D_807FBB48 + 0x84);
        dist = dx * dx + dz * dz;
        fv0 = 0.0f;
        f = *(s16 *)((u8 *)D_80029BA4 + 2) < (*(s16 *)(CR58 + 2)) + half;
        if (f) {
            f = (*(s16 *)(CR58 + 2)) - half < *(s16 *)((u8 *)D_80029BA4 + 2);
        }
        f = (u8)f != 0;
        if (f) {
            f = 0;
            if (dist < (f32)*(s32 *)(CR58 + 0x18)) {
                f = 1;
            }
        }
        CR58[0x25] = f;
        CR58[0x24] = D_807444FC;
        m = D_807FC924 + D_807FC929 * 0x2F0;
        dz = (f32)*(s16 *)(CR58 + 4) - *(f32 *)(m + 0x218);
        dx = (f32)*(s16 *)(CR58 + 0) - *(f32 *)(m + 0x210);
        ddy = (f32)*(s16 *)(CR58 + 2) - *(f32 *)(m + 0x214);
        dist = dz * dz + (dx * dx + ddy * ddy);
        *(f32 *)(CR58 + 0x20) = dist;
        if (dist < lim) {
            fv0 = (lim - dist) * 0.000051020408f;
            if (fv0 > 1.0f) {
                fv0 = 1.0f;
            }
        }
        CR58[0x26] = (u32)(255.0f * fv0);
    }
    if (*(f32 *)(CR58 + 0x20) < lim) {
        ((u8 *)arg0)[0x1E1] |= 1;
    } else {
        ((u8 *)arg0)[0x1E1] &= ~1;
    }
}
#undef CR58

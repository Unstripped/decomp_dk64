// func_8002601C (src/critter/0.c): stage 5 (parked NON_MATCHING in src copy): 159 vs 160 insns, same frame/regs set; diff = scheduling at head (dd mul/add sunk into near-branch, lui/lw order), a3 reuse for flag var, missing beqzl/sb delay-slot (store duplicated into delay slots). near flag as s32 f=(pl<..)&&(..); g=(u8)f!=0; if(g){g=0;if(dd<lim)g=1;} store g. Tried statement perms, u8/s32/s8 var types, && forms, permuter.
extern u8 *D_807FBB48;
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
    f32 dd;
    s16 half;
    s16 py;
    s16 pl;
    s32 f;
    s32 g;

    fv0 = 0.0f;
    lim = (f32)(*(s32 *)(CR58 + 0x18) + 0x1DE84);
    if (D_807444FC != CR58[0x24]) {
        dx = (f32)*(s16 *)(CR58 + 0) - *(f32 *)(D_807FBB48 + 0x7C);
        dz = (f32)*(s16 *)(CR58 + 4) - *(f32 *)(D_807FBB48 + 0x84);
        half = (*(s16 *)(CR58 + 0x10) + *(s16 *)(CR58 + 0xC)) >> 1;
        py = *(s16 *)(CR58 + 2);
        pl = *(s16 *)((u8 *)D_80029BA4 + 2);
        dd = dx * dx;
        dd += dz * dz;
        fv0 = 0.0f;
        f = pl < py + half;
        if (f) {
            f = py - half < pl;
        }
        g = (u8)f != 0;
        if (g) {
            g = 0;
            if (dd < (f32)*(s32 *)(CR58 + 0x18)) {
                g = 1;
            }
        }
        CR58[0x25] = g;
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

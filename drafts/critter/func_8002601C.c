// func_8002601C (src/critter/0.c): stage 5 improved (fdiff 2620 -> 300; permuter 2646 -> 300 found it): reuse dx for the first-block distance: 'dx = dx*dx + dz*dz;' then compare dx (pins the sum before the flag code like the target and drops the separate-temp scheduling; int regs a1/a2/a3 now match). Left: first block target dx=$f14,dz=$f16,dist=$f12 vs ours dx=f12,dz=f14,dist=f12-reuse; second block target dist=$f12,dz=f14,dx=f16,ddy=f18 vs ours dist=f18,dz=f12.. (target colours dist FIRST in both blocks = one high-priority web; ours dist is the last-coloured); int ring at 0x2108 (lui t3/t9 vs t9/t4). Tried: dummy dist uses (&&, <, !) pin but colour dist last and shift ints, decl order of f32 locals (no effect), separate vars per block, 24 role permutations of dx/dz/dist/ddy in block 1 (best 285), dummy uses before block 2 (removed before alloc).
extern u8 D_807444FC;
extern u8 *D_807FC924;
extern u8 D_807FC929;
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
    s16 half;
    s32 f;

    fv0 = 0.0f;
    lim = (f32)(*(s32 *)(CR58 + 0x18) + 0x1DE84);
    if (D_807444FC != CR58[0x24]) {
        half = (*(s16 *)(CR58 + 0x10) + *(s16 *)(CR58 + 0xC)) >> 1;
        dx = (f32)*(s16 *)(CR58 + 0) - *(f32 *)(D_807FBB48 + 0x7C);
        dz = (f32)*(s16 *)(CR58 + 4) - *(f32 *)(D_807FBB48 + 0x84);
        dx = dx * dx + dz * dz;
        fv0 = 0.0f;
        f = *(s16 *)((u8 *)D_80029BA4 + 2) < (*(s16 *)(CR58 + 2)) + half;
        if (f) {
            f = (*(s16 *)(CR58 + 2)) - half < *(s16 *)((u8 *)D_80029BA4 + 2);
        }
        f = (u8)f != 0;
        if (f) {
            f = 0;
            if (dx < (f32)*(s32 *)(CR58 + 0x18)) {
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

// func_80658134 (src/global/55B20.c): TEXT OK (fdiff, own bss differs): text-identical to target when 55B20.c DEFINES 'f32 D_807F6C88[12];' (bss owned by the TU; as1 shares 'lui at' between the 12 stores of the unrolled 4-iteration loop D[k*3+0..2] = unk0/unk10/unk20[k]) -- needs a .bss carve 0x807F6C88-0x807F6CB8 (remove D_807F6C88..D_807F6CB4 from asm/global/data/165D50_807F5D30.bss.s, add yaml bss subsegment + symbol_addrs as in commit 9222546). Reloc-only diff: target uses D_807F6CxC symbols with addend 0, ours D_807F6C88+off. Prototyped (s32,f32,f32,f32); locals decl order k,n2,n1; n1=n2=0 as statements; no src temp. Parked NON_MATCHING in copy.
typedef struct {
    /* 0x00 */ f32 unk0[4];
    /* 0x10 */ f32 unk10[4];
    /* 0x20 */ f32 unk20[4];
} MapGridVectors;

extern MapGridVectors *D_807F6C14;
// NEEDS .bss carve: 55B20.c must DEFINE f32 D_807F6C88[12] (0x807F6C88-0x807F6CB8, 48 bytes), so as1 shares 'lui at' between the unrolled-loop stores.
f32 D_807F6C88[12];
extern f32 D_807F6E68[];
extern f32 D_807F6F58[];
extern f32 D_807F6D78[];

void func_806582F8(f32 *, f32 *, s32, s32 *, s32);

s32 func_80658134(s32 arg0, f32 arg1, f32 arg2, f32 arg3)
{
    s32 k;
    s32 n2;
    s32 n1;

    n1 = 0;
    n2 = 0;
    for (k = 0; k < 4; k++) {
        D_807F6C88[k * 3] = D_807F6C14[arg0].unk0[k];
        D_807F6C88[k * 3 + 1] = D_807F6C14[arg0].unk10[k];
        D_807F6C88[k * 3 + 2] = D_807F6C14[arg0].unk20[k];
    }
    func_806582F8(D_807F6C88, D_807F6E68, 4, &n2, 0);
    if (n2 == 0) {
        return 0;
    }
    func_806582F8(D_807F6E68, D_807F6F58, n2, &n1, 1);
    if (n1 == 0) {
        return 0;
    }
    func_806582F8(D_807F6F58, D_807F6E68, n1, &n2, 2);
    if (n2 == 0) {
        return 0;
    }
    func_806582F8(D_807F6E68, D_807F6F58, n2, &n1, 3);
    if (n1 == 0) {
        return 0;
    }
    func_806582F8(D_807F6F58, D_807F6D78, n1, &n2, 4);
    if (n2 < 3) {
        n2 = 0;
    }
    return n2;
}

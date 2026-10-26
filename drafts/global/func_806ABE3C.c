// func_806ABE3C (src/global/ACDC0.c): R3ACDC0 stage 6: text identical except sum-loop init direction (orig addiu a1,t6 / move a2,a1; mine addiu a2,t6 / move a1,a2) and reloc names (orig splat D_807FC828/D_807FC836/D_80750535; start/end via D_807FC82A -/+ because using D_807FC828/D_807FC836 directly shares the address into t0/s3). KEY QUIRK: init and 'do {' on ONE source line (p = X; do {) fixes the lui/addiu emission order of the loops; also 'e = D_807FC950; k = 0; do { n += ...' on one line.
typedef struct ACDC0CountEntry {
    /* 0x00 */ u8 pad0[0x42];
    /* 0x42 */ u16 unk42[14];
} ACDC0CountEntry; // size = 0x5E

extern s16 D_807FC828;
extern s16 D_807FC82A;
extern s16 D_807FC82C;
extern s16 D_807FC82E;
extern s16 D_807FC830;
extern s16 D_807FC832;
extern s16 D_807FC834;
extern s16 D_807FC836;
extern s16 D_807FC838;
extern ACDC0CountEntry D_807FC950[];
extern ACDC0CountEntry D_807FCB26[];
extern s16 D_80744710[];
extern s16 D_80744720[];
extern s16 D_807505B2[];
extern s16 D_807505B8[];
extern s16 D_807505CC[];
extern u8 D_80750530;
extern u8 D_80750531[];
s32 flagGet(s16, s32);
s32 flagCountRange(s32, s32, s32);

void func_806ABE3C(void) {
    s16 *p;
    s16 *p0;
    ACDC0CountEntry *e;
    s32 n;
    s32 i;
    s32 k;
    s32 m;

    p0 = (s16 *)((u8 *)&D_807FC82A - 2); do {
        *p0++ = 0;
    } while (p0 < (s16 *)((u8 *)&D_807FC82A + 10));
    n = 0;
    e = D_807FC950; k = 0; do { n += e->unk42[0]; n += e->unk42[1];
        for (i = 2; i < 14; i++) {
            n += D_807FC950[k].unk42[i];
        }
        e++;
        k++;
    } while (e < D_807FCB26);
    D_807FC828 = n;
    n = 0;
    p = D_80744710; do {
        if (flagGet(*p, 0) != 0) {
            n++;
        }
        p++;
    } while (p < D_80744720);
    D_807FC82C = n;
    D_807FC832 = flagCountRange(0x24D, 0x14, 0);
    D_807FC82E = flagCountRange(0x225, 0x28, 0);
    m = 0;
    p = D_807505B8; do {
        if (*p >= 0 && flagGet(*p, 0) != 0) {
            m++;
        }
        p++;
    } while (p < D_807505CC);
    D_807FC82A = m;
    D_807FC834 = flagGet(0x84, 0);
    D_807FC830 = flagGet(0x17B, 0);
    D_807FC836 = flagCountRange(0x1FD, 0x28, 0);
    D_80750530 = 1;
    for (i = 0; i < 4; i++) {
        D_80750531[i] = flagGet(D_807505B2[i - 1], 0);
    }
    D_807FC838 = 1;
}

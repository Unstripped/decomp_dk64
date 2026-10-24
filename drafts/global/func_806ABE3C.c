// func_806ABE3C (src/global/ACDC0.c): stage 5 (24 diff lines, regalloc/order only): distinct address exprs defeat CSE (loop 1 via &D_807FC82A-2/+10 so scalar stores keep 'lui at'); loop 4 as for(i=0;i<4;i++) D_80750531[i]=f(D_807505B2[i-1]) matches; remaining: sum loop (expected a1 + 'move a2,a1' with t6 hi temp), s1/s2 addiu init order in loops 2/3, move s0,zero placement. Parked NON_MATCHING
typedef struct M1CountEntry {
    /* 0x00 */ u8 pad0[0x42];
    /* 0x42 */ u16 unk42[14];
} M1CountEntry; // size = 0x5E

extern s16 D_807FC828;
extern s16 D_807FC82A;
extern s16 D_807FC82C;
extern s16 D_807FC82E;
extern s16 D_807FC830;
extern s16 D_807FC832;
extern s16 D_807FC834;
extern s16 D_807FC836;
extern s16 D_807FC838;
extern M1CountEntry D_807FC950[];
extern M1CountEntry D_807FCB26[];
extern s16 D_80744710[];
extern s16 D_80744720[];
extern s16 D_807505B2[];
extern s16 D_807505B8[];
extern s16 D_807505CC[];
extern u8 D_80750530;
extern u8 D_80750531[];
s32 func_8073110C(s16, s32);
s32 func_80731AA8(s32, s32, s32);

void func_806ABE3C(void) {
    s16 *p;
    s16 *p0;
    s16 *q;
    M1CountEntry *e;
    s32 n;
    s32 i;
    u8 *u;

    p0 = (s16 *)((u8 *)&D_807FC82A - 2);
    do {
        *p0++ = 0;
    } while (p0 < (s16 *)((u8 *)&D_807FC82A + 10));
    n = 0;
    e = D_807FC950;
    do {
        n += e->unk42[0] + e->unk42[1];
        for (i = 2; i < 14; i++) {
            n += e->unk42[i];
        }
        e++;
    } while (e < D_807FCB26);
    D_807FC828 = n;
    n = 0;
    p = D_80744710;
    do {
        if (func_8073110C(*p, 0) != 0) {
            n++;
        }
        p++;
    } while (p < D_80744720);
    D_807FC82C = n;
    D_807FC832 = func_80731AA8(0x24D, 0x14, 0);
    D_807FC82E = func_80731AA8(0x225, 0x28, 0);
    n = 0;
    p = D_807505B8;
    do {
        if (*p >= 0 && func_8073110C(*p, 0) != 0) {
            n++;
        }
        p++;
    } while (p < D_807505CC);
    D_807FC82A = n;
    D_807FC834 = func_8073110C(0x84, 0);
    D_807FC830 = func_8073110C(0x17B, 0);
    D_807FC836 = func_80731AA8(0x1FD, 0x28, 0);
    D_80750530 = 1;
    for (i = 0; i < 4; i++) {
        D_80750531[i] = func_8073110C(D_807505B2[i - 1], 0);
    }
    D_807FC838 = 1;
}

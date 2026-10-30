// func_8060D14C (src/global/104F0.c): stage 4: frame 0x38, exact registers s0-s4/fs0/ra match; inlined offset eliminated post-loop checksum regalloc diff; remaining diff is single instruction scheduling of move s0, zero before vs after hoisted addiu s3/s4
#include <ultra64.h>
extern OSMesgQueue D_807ECCF0;
extern s32 D_807EDEAC;
extern s32 _strcasecmp(char *, char *);
extern char *D_807467C0;
extern s8 D_807467C4;
extern s8 D_807467CC;
extern u8 D_807ED6A8[];
extern s8 D_80744460;
extern s16 D_807ECEA0[];
extern void sleepMilliseconds(f32);
extern void func_8060D0A8(void);
extern void func_8060CB9C(void);

void func_8060D14C(void) {
    s32 var_s0;
    s32 var_s2;
    u8 *var_s1;

    var_s2 = 0;
    var_s1 = D_807ED6A8;
    if (D_807EDEAC != 2) {
        func_8060D0A8();
        D_807467CC = 1;
        return;
    }
    D_807467C4 = 1;
    var_s0 = 0;
    do {
        var_s2 |= osEepromRead(&D_807ECCF0, (u8)var_s0, var_s1);
        sleepMilliseconds(15.0f);
        var_s0 += 1;
        if (D_80744460 != 0) {
            D_807467C4 = 0;
            return;
        }
        var_s1 += 8;
    } while ((var_s0 < 0x100) && (var_s2 == 0));
    D_807467C4 = 0;
    D_807467CC = 1;
    if (var_s2 == 0) {
        var_s2 = _strcasecmp((char *)D_807ED6A8 + ((((((((((D_807ECEA0[0] + 0x6B7) & ~0x3F) + 0x27) & ~7) * 4) + 0x3F) & ~0x3F) + 0x207) & ~7) / 8), D_807467C0);
    }
    if (var_s2 != 0) {
        func_8060D0A8();
    }
    func_8060CB9C();
}

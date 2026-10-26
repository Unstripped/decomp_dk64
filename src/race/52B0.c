#include "common.h"

extern s32 D_8002FC5C[];
void func_8002CAC8(s32, void *, s32);
void func_8002D0B0(void);
s32 func_8002E8EC(s32, s32, s32);

void func_800292B0(s32 arg0, u8 *arg1) {
    func_8002CAC8(arg0, arg1, *(s32 *)(arg1 + 0x174));
}

extern u8 D_807FC928;
extern void *D_807FBB40;
extern void *D_807FBB44;
void func_8002BBD0(void *, s32);
void actorSpawn(s32, s32);
void func_8002BC2C(void *, s32, void *, void *);
void *spawnNodeSpawnById(s32, s32, s32, s32, s32, s32, s32);
void func_8002BCB0(void *, s32, void *, void *);
void actorInitFromSpawnPoint(void *, void *);

void func_800292D0(u8 *arg0) {
    u8 *sp5C;
    u8 *sp58;
    u8 *sp54;
    s32 var_s1;
    s32 var_s0;
    s32 var_s5;

    var_s5 = D_807FC928;
    var_s1 = 0;
    sp5C = *(u8 **)(arg0 + 0x174);
    if (var_s5 == 1) {
        var_s5++;
    }
    func_8002BBD0(arg0, var_s5);
    for (var_s0 = 0; var_s0 < D_807FC928; var_s0++) {
        actorSpawn(0x133, 0x9F);
        sp54 = (u8 *)D_807FBB44;
        sp58 = *(u8 **)(sp54 + 0x174);
        sp58[0x27] = 0;
        func_8002BC2C(arg0, var_s1, sp54, sp58);
        var_s1++;
        sp58[0x28] = var_s0;
    }
    var_s0 = 0;
    if (D_807FC928 == 1) {
        sp54 = spawnNodeSpawnById(1, 0, 0, 0, 0, 0, 0);
        sp58 = *(u8 **)(sp54 + 0x178);
        sp58[0x27] = 1;
        func_8002BC2C(arg0, var_s1, sp54, sp58);
        func_8002BCB0(arg0, 0, *(void **)(sp54 + 0x180), (u8 *)*(void **)(sp54 + 0x180) + 4);
        sp5C[0x25] = 1;
    } else {
        sp5C[0x25] = 0;
    }
    if (var_s5 > 0) {
        do {
            func_8002BCB0(arg0, var_s0, &sp54, &sp58);
            sp58[0x36] = var_s0;
            *(void **)(sp58 + 0x30) = arg0;
            if (sp58[0x27] == 0) {
                actorInitFromSpawnPoint(sp54, sp58);
            }
            var_s0++;
        } while (var_s0 != var_s5);
    }
    sp5C[0x26] = 0;
}

void func_80029488(void) {
    func_8002D0B0();
}
#pragma GLOBAL_ASM("asm/race/nonmatchings/52B0/func_800294A8.s")

#pragma GLOBAL_ASM("asm/race/nonmatchings/52B0/func_8002978C.s")

#pragma GLOBAL_ASM("asm/race/nonmatchings/52B0/func_80029F88.s")

s32 func_8002A080(s32 arg0, s32 arg1) {
    return D_8002FC5C[func_8002E8EC(arg0, arg1, 10)];
}

#pragma GLOBAL_ASM("asm/race/nonmatchings/52B0/func_8002A0AC.s")

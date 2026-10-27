#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB4C;

extern Actor *D_807FBB44;
extern s16 D_80744710[];
extern s8 D_807506A4;
extern s8 D_80750660;
extern u8 D_807FC8D0;

s32 flagGet(s16, s32);
s32 actorSpawn();
f32 func_80612790(s16);
f32 func_80612794(s16);

typedef struct R1C0C1Sub174 {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s8 unk2;
    /* 0x04 */ Actor *unk4;
} R1C0C1Sub174;

#define R1C0C1_SPAWNED_146 (((R1C0C1Spawned *)D_807FBB44)->unk146)
typedef struct R1C0C1Spawned {
    /* 0x000 */ u8 pad0[0x146];
    /* 0x146 */ s16 unk146;
} R1C0C1Spawned;

void func_806BD170(void) {
    Actor *sp54;
    s16 i;
    s16 sp50;
    s16 count;
    s16 pos;
    R1C0C1Sub174 *sub;

    sp50 = -1;
    i = 0;
    count = 0;
    for (; i < 8; i++) {
        if (flagGet(i + 0x1BC, 0) == 0) {
            actorSpawn(0x14E, 0xCD);
            D_807FBB44->unk12A = 0x7D0;
            D_807FBB44->unk60 |= 0x800400;
            pos = i * 0x200 + 0x104;
            D_807FBB44->unk60 &= 0xFFFF7FFF;
            D_807FBB44->unk16A = 0xFF;
            D_807FBB44->unk16B = 0xFF;
            D_807FBB44->unk16C = 0xFF;
            D_807FBB44->unk128 = 0xFF;
            D_807FBB44->unk7C = func_80612794(pos) * 270.0f + D_807FBB40->unk7C;
            D_807FBB44->unk84 = func_80612790(pos) * 270.0f + D_807FBB40->unk84;
            D_807FBB44->unk80 = 100.0f;
            D_807FBB44->unkE6 = pos;
            R1C0C1_SPAWNED_146 = 0;
            D_807FBB44->unk154 = 0;
            sub = D_807FBB44->unk174;
            sub->unk0 = 0;
            sub->unk4 = D_807FBB40;
            sub->unk2 = i;
            if (flagGet(D_80744710[i], 0) != 0) {
                sp50 = i;
                sp54 = D_807FBB44;
                sp54->unk154 = 5;
                count++;
            }
        }
    }
    D_807506A4 = 0;
    if (flagGet(0x1BB, 0) == 0) {
        sp50 = -1;
    }
    if (D_80750660 == 0 && sp50 != -1) {
        ((R1C0C1Spawned *)sp54)->unk146 = 1;
        sp54->unk154 = 1;
        D_80750660 = 1;
        D_807FC8D0 = sp50;
    }
}

#ifdef NON_MATCHING
extern s16 D_8076A0A6;
extern s8 D_807506B4;
extern s8 D_807506A8[];
extern f32 D_807FC8D4;
extern s32 D_807F5D10;

s32 func_806BDD2C(void);
void func_8067B238(void *, void *, f32);
s32 actorScriptStart(void *, s32);
void actorUpdateModelMatrix(void *, s32);
s32 func_8061CC40(void *, s32, s32);
s32 currentActorTestClearFlag();
s32 func_8061CB50(void);
void func_8061F0B0(s32, s32, s32);
s32 sfxAllocateChannel(s32, f32);
s16 func_80609140(s16, s32, f32, f32, u8, u8);
void flagSet(s16, s32, s32);

typedef struct NmBD3E4Ptr178 {
    /* 0x00 */ Actor *unk0;
} NmBD3E4Ptr178;

typedef struct NmBD3E4Sub4 {
    /* 0x00 */ u8 pad0[0x64];
    /* 0x64 */ u16 unk64;
} NmBD3E4Sub4;

typedef struct NmBD3E4Act178 {
    /* 0x000 */ u8 pad0[0x178];
    /* 0x178 */ NmBD3E4Ptr178 *unk178;
} NmBD3E4Act178;

void func_806BD3E4(void) {
    NmBD3E4Ptr178 *sp34 = ((NmBD3E4Act178 *)D_807FBB40)->unk178;
    f32 dx;
    f32 dz;
    u8 sp2B;
    u16 sp28;
    s16 v3 = D_8076A0A6;
    s16 idx;
    s8 *cnt = &D_807506B4;
    s8 n;

    if (!(D_807FBB40->unk60 & 0x10)) {
        if (func_806BDD2C() != 0) {
            D_807FBB40->unk154 = 0x40;
            return;
        }
        D_807FBB40->unk12A = 0x7D0;
        D_807FBB40->unk60 |= 0x400;
        v3 = 0;
        D_807506B4 = 0; actorSpawn(0x73, 0xC4, &D_807FBB40);
        func_8067B238(D_807FBB44, D_807FBB40, D_807FBB40->unk4->unk38);
        D_807FBB44->unk64 |= 0x20;
        D_807FBB44->unk60 |= 0x400;
        D_807FBB44->unk12A = 0x7D0;
        sp34->unk0 = D_807FBB44;
        D_807FC8D4 = 1000.0f;
        func_806BD170();
        D_807FBB40->unk154 = 0;
        if (D_80750660 != 0) {
            D_80750660 = 0;
        }
        if (flagGet(0x1BB, 0) == 0) {
            D_807FBB40->unk154 = 1;
        }
    }
    idx = -1;
    if (v3 != 0) {
        idx = 0;
        while (!(v3 & 1)) {
            v3 >>= 1;
            idx++;
        }
    }
    dx = D_807FBB40->unk7C - D_807FBB4C->unk7C;
    dz = D_807FBB40->unk84 - D_807FBB4C->unk84;
    sp28 = 0;
    D_807FC8D4 = dx * dx + dz * dz;
    switch (D_807FBB40->unk154) {
        case 1:
            actorScriptStart(D_807FBB40, 0x2EF);
            D_807FBB40->unk154 = 2;
            func_8061CC40(D_807FBB4C, 2, 1);
            break;
        case 2:
            if (currentActorTestClearFlag() != 0) {
                sfxAllocateChannel(0x7D, 1.0f);
                actorScriptStart(D_807FBB40, 0x2F1);
                D_807FBB40->unk154 = 3;
                D_807FBB40->unk155[0] = 0;
            }
            break;
        case 3:
            if (D_807FBB40->unk155[0] & 1) {
                D_807FBB40->unk155[0]++;
                sp2B = 0xF; sp28 = 0x28;
            }
            break;
    }
    if (func_8061CB50() == 0) {
        if (((NmBD3E4Sub4 *)D_807FBB40->unk4)->unk64 != 0x2F0) {
            actorScriptStart(D_807FBB40, 0x2F0);
        }
    }
    if (sp28) {
        func_8061F0B0(D_807F5D10, sp2B, sp28);
    }
    if (idx >= 0) {
        n = *cnt;
        if (idx == D_807506A8[n]) {
            n++;
            D_807506B4 = n;
            if (D_807506A8[n] == -1) {
                func_80609140(0x1DA, 0x7FFF, 63.0f, 1.0f, 5, 0);
                flagSet(0x28, 1, 1);
                flagSet(0x26, 1, 1);
                D_807506B4 = -1;
            }
        } else {
            D_807506B4 = 0;
        }
    }
    D_8076A0A6 = 0;
    actorUpdateModelMatrix(D_807FBB40, 0);
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/C1E70/func_806BD3E4.s")
#endif

extern f32 D_807FC8D4;

s32 func_806BDD2C(void);
s32 actorScriptStart(void *, s32);
void actorUpdateModelMatrix(void *, s32);
s32 func_8061CC40(void *, s32, s32);
s32 func_8061CB50(void);
s32 sfxAllocateChannel(s32, f32);
s16 func_80609140(s16, s32, f32, f32, u8, u8);
void flagSet(s16, s32, s32);

typedef struct R1C0C1Ptr178 {
    /* 0x00 */ Actor *unk0;
} R1C0C1Ptr178;

typedef struct R1C0C1Act178 {
    /* 0x000 */ u8 pad0[0x178];
    /* 0x178 */ R1C0C1Ptr178 *unk178;
} R1C0C1Act178;

typedef struct R1C0C1Blob8 {
    /* 0x00 */ s8 b[8];
} R1C0C1Blob8;

extern s16 D_80750664[];
extern s16 D_80750684[];
extern R1C0C1Blob8 D_807506B8;
extern u8 D_80720A7C;

void sfxStopChannel(s32, s32);
void func_8063DA40(s32, s32);
void func_8061CB08(void);
void func_80712524(s32, s32);
void func_80714950(s32);
void func_8071498C(void (*)(void));
void func_8071AADC(void);
void func_807149C8(s32, s32, s32, s32);
void func_80714CC0(void *, f32, f32, f32, f32);
f32 func_806119FC(void);

void func_806BD7B0(void) {
    R1C0C1Sub174 *st = D_807FBB40->unk174;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    R1C0C1Ptr178 *p;
    s32 limit;
    R1C0C1Blob8 sp30;

    switch (D_807FBB40->unk154) {
        case 5:
            if (D_807506A4 != 0 && func_8061CB50() == 0) {
                st->unk0++;
                if (st->unk0 >= 0x29) {
                    D_807506A4 = 0;
                    D_807FBB40->unk154 = 1;
                }
            } else {
                st->unk0 = 0;
            }
            break;
        case 1:
            st->unk0 = 0;
            D_807FBB40->unk154 = 2;
            break;
        case 2:
            if (D_807FC8D4 < 160000.0) {
                D_807FBB40->unk154 = 3;
                st->unk0 = 0;
                sfxAllocateChannel(0x3B, 1.0f);
                func_80609140(0x258, 0x7FFF, 63.0f, 1.0f, 5, 0);
                func_8061CC40(D_807FBB40, 0, 1);
                actorScriptStart(D_807FBB40, 0x291);
                D_807FBB40->unk155[0] = 0;
                ((R1C0C1Spawned *)D_807FBB40)->unk146 = 1;
            }
            break;
        case 3:
            if (D_807FBB40->unk155[0] == 1) {
                D_807FBB40->unk155[0]++;
            } else if (D_807FBB40->unk155[0] == 2) {
                sfxStopChannel(0x3B, 1);
                D_807FBB40->unk128 -= 8;
                if (D_807FBB40->unk128 <= 0) {
                    D_807FBB40->unk128 = 0;
                    st->unk0++;
                    if (st->unk0 == 1) {
                        func_80609140(0x1F6, 0x7FFF, 63.0f, 1.0f, 5, 0);
                    }
                    if (st->unk0 >= 0xB) {
                        sp30 = D_807506B8;
                        D_807FBB40->unk154 = 4;
                        sfxAllocateChannel(0x7D, 1.0f);
                        actorScriptStart(st->unk4, D_80750684[st->unk2]);
                        st->unk0 = 0;
                        st->unk4->unk154 = 3;
                        st->unk4->unk155[0] = 0;
                        func_8061CC40(0, 1, 1);
                        func_8063DA40(sp30.b[st->unk2], 2);
                    }
                }
                if (D_807FBB40->unk128 < 0x80) {
                    D_807FBB40->unk80 -= 6.0;
                }
            } else {
                func_80714950(0x10064);
                func_8071498C(func_8071AADC);
                func_807149C8(0xFF, 0xFF, 0xFF, 0xFF);
                sp48 = func_806119FC() * 30.0 + D_807FBB40->unk7C;
                sp44 = func_806119FC() * 30.0 + (D_807FBB40->unk80 + 20.0);
                sp40 = func_806119FC() * 30.0 + D_807FBB40->unk84;
                func_80714CC0(&D_80720A7C, 1.2f, sp48, sp44, sp40);
            }
            break;
        case 4:
            if (func_806BDD2C() != 0) {
                p = ((R1C0C1Act178 *)st->unk4)->unk178;
                p->unk0->unk80 += 5.0;
                if (st->unk0 == 0x10E) {
                    flagSet(0x315, 1, 0);
                    func_80712524(D_80750664[14], D_80750664[15]);
                }
            }
            limit = 0xB4;
            if (st->unk2 == 2 || st->unk2 == 7) {
                if (func_806BDD2C() == 0) {
                    limit = 0x5A;
                }
            }
            st->unk0++;
            if (limit == st->unk0) {
                if (st->unk2 == 2 || st->unk2 == 7) {
                    flagSet(st->unk2 + 0x1BC, 1, 0);
                    if (func_806BDD2C() == 0) {
                        func_8061CB08();
                        sfxStopChannel(0x7D, 1);
                        D_807506A4 = 1;
                    }
                } else {
                    func_80712524(D_80750664[st->unk2 * 2], D_80750664[st->unk2 * 2 + 1]);
                }
            }
            break;
        case 0:
            break;
    }
    D_807FBB40->unk15E = 0x28;
    actorUpdateModelMatrix(D_807FBB40, 0);
}

s32 func_806BDD2C(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (flagGet(i + 0x1BC, 0) == 0) {
            return 0;
        }
    }
    return 1;
}

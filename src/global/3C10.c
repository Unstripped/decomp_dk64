#include "common.h"
#include "sched.h"

typedef struct {
    u8 unk0;
    u8 pad1;
    s16 unk2;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    s16 unk10;
    s16 unk12;
    u8 unk14;
    u8 pad15[3];
    s32 unk18;
    void *unk1C;
    void *unk20;
    u8 pad24[0xC0 - 0x24];
} Struct8076A160;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Struct807447A0;

typedef struct {
    u8 pad0[0x7C];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xE6 - 0x88];
    s16 unkE6;
} Struct807FBB4C;

typedef struct {
    u16 unk0;
    u16 unk2;
    u8 unk4;
} Struct8074475C;

/* Extern variables */
extern u8 D_807444EC;
extern u8 D_807444F8;
extern s32 D_807444E4;
extern s32 D_807444E8;
extern u8 D_807445E0[];
extern u16 D_807446C0[];
extern s32 D_80744720[];
extern u16 D_80744734[];
extern u16 D_80744736[];
extern u16 D_80744748[];
extern Struct8074475C D_8074475C[11];
extern Struct807447A0 D_807447A0[];
extern u8 D_80744820;
extern u8 D_80744824;
extern u8 D_80744828;
extern Struct807447A0 D_8074482C[];
extern u8 D_8074E77C;
extern u8 D_807565E0[];
extern u8 D_80756630[];
extern s32 D_80767CC4;
extern s32 D_8076A0A8;
extern u8 D_8076A0AB;
extern u8 D_8076A0B1;
extern s8 D_8076A0B2;
extern Struct8076A160 D_8076A160[18];
extern s16 D_8076A172;
extern u8 D_8076A220;
extern s16 D_8076A232;
extern Struct8076A160 D_8076A2E0[];
extern u8 D_8076AEE0;
extern s16 D_8076AEE2;
extern f32 D_8076AEE4;
extern f32 D_8076AEE8;
extern f32 D_8076AEEC;
extern s16 D_8076AEF0;
extern s16 D_8076AEF2;
extern u16 D_8076AEF4;
extern u8 D_8076AEF6;
extern s16 D_8076AF00[];
extern s32 D_8076AF10;
extern u8 D_8076AF14;
extern s32 D_807F6010;
extern Struct807FBB4C *D_807FBB4C;
extern s32 D_807FBB60;
extern s32 D_807FBB64;
extern s32 D_807FBB68;
extern u16 D_807FC930[];
extern f32 D_807FD88C;

/* Function declarations */
s32 func_805FEF74(s32 arg0);
u8 func_805FF000(u8 arg0);
s32 func_805FF018(u8 arg0, s32 arg1);
u8 func_805FF030(u8 arg0, u8 arg1);
u8 func_805FF0C8(void);
void func_805FF118(void);
void func_805FF158(u8 arg0);
void func_805FF168(void);
void func_805FF188(s16 arg0, u8 arg1);
void func_805FF1B0(s32 arg0);
void func_805FF2F4(void);
void func_805FF378(s32 arg0, s32 arg1);
void func_805FF4D8(s32 arg0, s32 arg1);
void func_805FF544(void);
void func_805FF5A0();
void func_805FF628(s32 arg0, s32 arg1);
void func_805FF660(s8 arg0);
void func_805FF670(void);
s32 func_805FF800(s32 *arg0, s32 *arg1);
void func_805FF898(void);
void func_805FF8F8(void);
s32 func_805FF938(s16 target);
s32 func_805FFE50(s32 arg0, s16 arg1, s16 arg2);
void func_805FFEF8(s32 arg0);
void func_805FFFC8(void);
s32 func_80600080();
s16 func_80600174(f32 *, f32 *, f32 *);
s32 func_80600340(s32 arg0, u8 arg1, s32 *arg2);
void func_80631F58(s32, s32 *, s32 *);
void func_806003EC(s16 arg0);
s32 func_8060042C(s16 arg0);
u8 func_80600454(s16 arg0, u8 *arg1);
s32 func_80600530(void);
void frameTimingReset(s32 arg0);

/* External functions */
void func_8002920C(void);
void sfxAllocateChannel(s32, f32);
void func_80611614(void *);
f32 func_80612790(s16);
f32 func_80612794(s16);
void func_8061CC40(void *, s32, s32);
void func_8063BEC0(void *, void *, s16, s16);
s32 func_80689C20(s32, s32, u8, f32, f32, f32);
void actorSpawnNodeEntryScaled(s32, f32, f32, f32, s32, s32, s32, s32);
u8 func_806C8DE0(s32);
void func_806F5378(void);
void func_806F8BC4(s32, s32, s32);
s32 func_80712798(void);
void func_80712F10(s32 *, s32 *);
s32 func_807143E8(void);
s32 func_8071441C(void);
s32 func_8073110C(s32, s32);
void func_8073129C();
void func_807313BC(void);
void heapFree(void *);

#pragma GLOBAL_ASM("asm/global/nonmatchings/3C10/func_805FEF10.s")

s32 func_805FEF74(s32 arg0) {
    s32 i;

    if (arg0 == D_80744734[0]) {
        return 1;
    }
    for (i = 0; i < 8; i++) {
        if (arg0 == D_80744736[i]) {
            return 1;
        }
    }
    return 0;
}

u8 func_805FF000(u8 arg0) {
    return D_807445E0[arg0];
}

s32 func_805FF018(u8 arg0, s32 arg1) {
    s32 ret = D_80744720[arg1];
    return ret;
}

u8 func_805FF030(u8 arg0, u8 arg1) {
    u8 val;
    s32 sp28;
    s32 sp24;
    s32 pad;

    sp28 = arg0;
    val = D_807445E0[sp28];
    if (val == 0xD || val == 9) {
        if (func_805FF800(&sp28, &sp24)) {
            val = D_807445E0[sp28];
        }
    }
    if (arg1 != 0) {
        if (func_805FEF74(sp28)) {
            val = 7;
        }
    }
    return val;
}

u8 func_805FF0C8(void) {
    s32 index = func_805FF030(D_8076A0AB, 0);
    return D_807FC930[index] >= D_807446C0[index];
}

void func_805FF118(void) {
    s32 i;
    for (i = 0; i < 18; i++) {
        D_8076A160[i].unk0 = 0;
    }
}

void func_805FF158(u8 arg0) {
    D_80744824 = arg0;
}

void func_805FF168(void) {
    D_8076AEE0 = D_80744824;
    D_80744824 = 1;
}

void func_805FF188(s16 arg0, u8 arg1) {
    D_80744828 = 1;
    D_8076AEF4 = arg0;
    D_8076AEF6 = arg1;
}

void func_805FF1B0(s32 arg0) {
    u16 pad;
    u16 a3;
    s32 limit;
    s32 i;
    u16 t1;
    u8 found;

    limit = 11;
    i = 0;
    t1 = 0;
    found = 0;

    if (D_80744828 != 0) {
        a3 = D_8076AEF4;
        t1 = D_8076AEF6;
    } else {
        if (func_805FEF74(D_8076A0A8) != 0) {
            a3 = ((u16 *)&D_8076A0A8)[1];
        } else {
            arg0 = func_805FF030(((u8 *)&D_8076A0A8)[3], 0);
            a3 = D_80744748[arg0];
            for (; !found && (i < limit); i++) {
                if (D_8076A0A8 == D_8074475C[i].unk0) {
                    a3 = D_8074475C[i].unk2;
                    t1 = D_8074475C[i].unk4;
                    found = 1;
                }
            }
        }
    }
    if (!found) {
        func_805FFFC8();
    }
    func_805FF378(a3, t1);
    D_80744828 = 0;
}

void func_805FF2F4(void) {
    s32 sp1C;
    s32 sp18;

    if (D_8076A0A8 != 0x22) {
        func_805FFFC8();
        sp1C = D_80744734[func_805FF030(D_8076A0AB, 0)];
        sp18 = 1;
    } else {
        sp1C = D_8076A0A8;
        sp18 = 0;
    }
    func_8073129C(0x6E, 1, 2, sp1C);
    func_805FF378(sp1C, sp18);
}

void func_805FF378(s32 arg0, s32 arg1) {
    func_806F5378();
    if ((D_807444EC == 6) || (func_80712798() == 0)) {
        func_80712F10(&arg0, &arg1);
        if (arg0 != -1) {
            if ((s32) D_8074E77C >= 6) {
                D_8074E77C = func_806C8DE0(0);
            }
            D_8076A0B1 |= 1;
            D_8076AEF2 = (s16) D_8076A0A8;
            D_807444E4 = arg0;
            D_807444E8 = arg1;
            D_8076A0B2 = 3;
            func_805FF168();
            D_807FD88C = 1.0f;
            if ((D_807444F8 != 1) && (D_8076AEE0 == 1) && !(D_807FBB68 & 2) && (D_8076A0A8 != 0x4C)) {
                sfxAllocateChannel(0x2C, 1.0f);
            }
            func_807313BC();
            func_805FF5A0(arg0);
            if (D_807FBB64 & 1) {
                func_8002920C();
            }
        }
    }
}

void func_805FF4D8(s32 arg0, s32 arg1) {
    func_806F5378();
    D_807FBB60 |= 0x100;
    D_807444E4 = arg0;
    D_807444E8 = arg1;
    D_8076AEF2 = D_8076A0A8;
    func_807313BC();
    func_805FF5A0(arg0);
}

void func_805FF544(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (D_8076A0A8 == D_807447A0[i].unk0) {
            func_805FF378(D_807447A0[i].unk4, D_807447A0[i].unk8);
            return;
        }
    }
}

void func_805FF5A0(void) {
    s32 idx = func_80600080();

    if (idx != -1) {
        D_8076AEE2 = D_8076A160[idx].unk2;
        D_8076AEE4 = D_8076A160[idx].unk4;
        D_8076AEE8 = D_8076A160[idx].unk8;
        D_8076AEEC = D_8076A160[idx].unkC;
        D_8076AEF0 = D_8076A160[idx].unk10;
    } else {
        D_8076AEE2 = 0;
    }
}

void func_805FF628(s32 arg0, s32 arg1) {
    func_805FFEF8(D_8076A0A8);
    func_805FF378(arg0, arg1);
}

void func_805FF660(s8 arg0) {
    D_80744820 = arg0;
}

void func_805FF670(void) {
    f32 temp_fs0;
    s16 temp_s2;
    s16 var_s1;
    f32 offset;
    s32 step;
    s16 temp_f0;

    if (D_80744820 != 0) {
        func_8061CC40(D_807FBB4C, 2, 5);
        func_806F8BC4(1, 0, 0);
        var_s1 = 0;
        if ((s32) D_80744820 > 0) {
            offset = 20.0f;
            step = 5;
            do {
                temp_fs0 = (var_s1 * 2) + 30;
                temp_s2 = D_807FBB4C->unk7C - func_80612794(D_807FBB4C->unkE6) * temp_fs0;
                temp_f0 = D_807FBB4C->unk84 - func_80612790(D_807FBB4C->unkE6) * temp_fs0;
                actorSpawnNodeEntryScaled(
                    0x35,
                    temp_s2,
                    D_807FBB4C->unk80 + offset + (f32)(var_s1 * step),
                    temp_f0,
                    D_807FBB4C->unkE6,
                    1,
                    -1,
                    0
                );
                var_s1++;
            } while (var_s1 < D_80744820);
        }
        D_80744820 = 0;
    }
}

s32 func_805FF800(s32 *arg0, s32 *arg1) {
    s32 found = 0;
    s32 i = 0;

    while (i < 18 && !found) {
        if (D_8076A160[i].unk0 != 0 && (D_8076A160[i].unk2 & 2)) {
            found = 1;
        } else {
            i++;
        }
    }

    if (found) {
        *arg0 = D_8076A160[i].unk12;
        *arg1 = D_8076A160[i].unk14;
    }
    return found;
}

void func_805FF898(void) {
    s32 sp1C;
    s32 sp18;

    if (func_805FF800(&sp1C, &sp18) != 0) {
        func_805FFEF8(D_8076A0A8);
        func_805FF378(sp1C, sp18);
    } else if (func_807143E8() != 0) {
        func_805FF378(0xF, 0);
    }
}

void func_805FF8F8(void) {
    if (func_8071441C() != 0) {
        func_805FF378(0x50, 0);
    } else {
        func_805FF898();
    }
}

s32 func_805FF938(s16 target) {
    s32 i = 0;
    s32 found = 0;
    while (i < 18 && !found) {
        if (D_8076A160[i].unk0 != 0 && D_8076A160[i].unk12 == target) {
            found = 1;
        } else {
            i++;
        }
    }
    return found;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/3C10/func_805FF9AC.s")

s32 func_805FFE50(s32 arg0, s16 arg1, s16 arg2) {
    s32 i = 0;
    s32 found = 0;
    Struct8076A160 *slot;

    while (!found && i < 18) {
        if (D_8076A160[i].unk12 == arg0) {
            found = 1;
        } else {
            i++;
        }
    }

    if (!found) {
        return 0;
    }

    slot = &D_8076A160[i];
    func_8063BEC0(slot->unk20, slot->unk1C, arg1, arg2);
    return 1;
}

void func_805FFEF8(s32 arg0) {
    s32 found = 0;
    s32 i = 0;

    while (i < 18 && !found) {
        if (D_8076A160[i].unk0 != 0 && D_8076A160[i].unk12 == arg0) {
            found = 1;
        } else {
            i++;
        }
    }

    if (found) {
        Struct8076A160 *slot = &D_8076A160[i];
        func_80611614(&slot->unk18);
        heapFree((void *)slot->unk18);
        if (slot->unk1C != 0) {
            func_80611614(&slot->unk20);
            heapFree(slot->unk20);
        }
        slot->unk0 = 0;
        D_807F6010 = 0;
    }
}

void func_805FFFC8(void) {
    Struct8076A160 *ptr, *end;
    ptr = D_8076A160, end = (Struct8076A160 *)&D_8076AEE0;
    do {
        if (ptr->unk0) {
            func_80611614(&ptr->unk18);
            heapFree((void *)ptr->unk18);
            if (ptr->unk1C != 0) {
                func_80611614(&ptr->unk20);
                heapFree(ptr->unk20);
            }
            ptr->unk0 = 0;
        }
        ptr++;
    } while (ptr != end);
}

void func_80600044(s32 arg0) {
    func_805FFFC8();
    func_805FF378(D_80744734[arg0], 1);
}

s32 func_80600080(s32 arg0) {
    Struct8076A160 *ptr;
    s32 i;

    if (*(u8 *)D_8076A160 != 0 && arg0 == D_8076A172) {
        return 0;
    }
    if (D_8076A220 != 0 && arg0 == D_8076A232) {
        return 1;
    }
    i = 2;
    ptr = D_8076A2E0;
loop:
    if (ptr[0].unk0 != 0 && arg0 == ptr[0].unk12) {
        return i;
    }
    if (ptr[1].unk0 != 0 && arg0 == ptr[1].unk12) {
        return i + 1;
    }
    if (ptr[2].unk0 != 0 && arg0 == ptr[2].unk12) {
        return i + 2;
    }
    if (ptr[3].unk0 != 0 && arg0 == ptr[3].unk12) {
        return i + 3;
    }
    i += 4;
    ptr += 4;
    if (i != 18) {
        goto loop;
    }
    return -1;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/3C10/func_80600174.s")

s32 func_80600340(s32 arg0, u8 arg1, s32 *arg2) {
    s32 sp3C;
    s32 sp38;
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    u8 idx;

    idx = func_80600174(&sp34, &sp30, &sp2C);
    if (idx == -1) {
        return -1;
    }
    func_80631F58(((Struct8076A160 *)&D_8076A160)[idx].unk18, &sp3C, &sp38);
    *arg2 = ((Struct8076A160 *)&D_8076A160)[idx].unk12;
    return func_80689C20(sp38, arg0, arg1, sp34, sp30, sp2C);
}

void func_806003EC(s16 arg0) {
    D_807FBB64 = D_8074482C[arg0].unk0;
    D_807FBB68 = D_8074482C[arg0].unk4;
}

s32 func_8060042C(s16 arg0) {
    return D_8074482C[arg0].unk8;
}

u8 func_80600454(s16 arg0, u8 *arg1) {
    u8 i;
    u8 ret;
    s16 temp;
    s32 a;

    i = 0;
    ret = 0;

    while (D_807565E0[i] != 0 && arg0 != D_807565E0[i]) {
        i++;
    }

    if (D_807565E0[i] != 0) {
        *arg1 = D_80756630[i];
        if (i < 13) {
            temp = i + 0x307;
            ret = func_8073110C(temp, 0) == 0;
            func_8073129C(temp, 1, 0);
        } else {
            ret = 1;
        }
    }
    return ret;
}

s32 func_80600530(void) {
    s32 i;
    s32 found;

    i = 0;
    found = 0;
    while (!found && i < 8) {
        if (D_8076A0A8 == D_80744734[i]) {
            found = 1;
        } else {
            i++;
        }
    }
    if (!found) {
        i = 0;
    }
    return i;
}

void frameTimingReset(s32 arg0) {
    s32 i;

    for (i = 0; i < 8; i++) {
        D_8076AF00[i] = 2;
    }

    D_8076AF10 = D_80767CC4;
    switch (arg0) {
    case 0x6:
    case 0x1B:
    case 0x27:
    case 0x28:
    case 0x37:
    case 0x4C:
    case 0x6A:
    case 0x98:
    case 0x99:
    case 0xAC:
    case 0xD0:
        D_8076AF14 = 0;
        break;
    default:
        D_8076AF14 = 1;
        break;
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/3C10/frameTimingUpdate.s")

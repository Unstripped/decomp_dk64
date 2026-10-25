#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB44;
extern Actor *D_807FBB48;
extern Actor *D_807FBB4C;
extern ActorGlobalState D_807FBB70;
extern u8 D_807FC928;
extern u8 D_807FC929;
extern Struct807FD580 *D_807FD580;
extern s16 D_807FD584;
extern u16 D_807FD63C;

extern s16 D_807FC930[];

void func_806C7B00(void) {
    s16 i;

    for (i = 0; i < 0xE; i++) {
        D_807FC930[i] = 0;
    }
}

extern u8 D_8074E77C[];

typedef struct G00Row {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ s32 unk4;
    /* 0x8 */ s32 unk8;
    /* 0xC */ s32 unkC;
} G00Row;

extern G00Row D_8075C410[];

s32 func_806C7B34(void) {
    return D_8075C410[D_8074E77C[0]].unk0;
}

typedef struct G00SpawnSub {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ Actor *unk4;
    /* 0x8 */ u8 unk8;
} G00SpawnSub;

s32 actorSpawn(s32, s32);
void func_8067B238(Actor *, Actor *, f32);

void func_806C7B50(s32 arg0, u8 arg1, Actor *arg2) {
    G00SpawnSub *sub;

    actorSpawn(arg0, 0x82);
    func_8067B238(D_807FBB44, arg2, 0.15f);
    sub = D_807FBB44->unk174;
    sub->unk4 = arg2;
    sub->unk8 = arg1;
}

void func_806C7BAC(s32 arg0, Actor *arg1) {
    G00SpawnSub *sub;

    actorSpawn(0x25, 0x8C);
    func_8067B238(D_807FBB44, D_807FBB48, 0.15f);
    sub = D_807FBB44->unk174;
    sub->unk0 = arg0;
    sub->unk4 = arg1;
}

extern u8 D_80750AB4;
extern u8 D_80750AB8;
extern u8 D_80750AC0;

typedef struct G00Sub6 {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ s16 unk4;
} G00Sub6;

typedef struct G00Block {
    /* 0x000 */ u8 unk0;
    /* 0x001 */ u8 pad1[3];
    /* 0x004 */ Actor *unk4;
    /* 0x008 */ u8 pad8[0x208];
    /* 0x210 */ f32 unk210;
    /* 0x214 */ f32 unk214;
    /* 0x218 */ f32 unk218;
    /* 0x21C */ f32 unk21C;
    /* 0x220 */ f32 unk220;
    /* 0x224 */ f32 unk224;
    /* 0x228 */ f32 unk228;
    /* 0x22C */ f32 unk22C;
    /* 0x230 */ f32 unk230;
    /* 0x234 */ u8 pad234[0xC];
    /* 0x240 */ f32 unk240;
    /* 0x244 */ f32 unk244;
    /* 0x248 */ f32 unk248;
    /* 0x24C */ u8 pad24C[0x24];
    /* 0x270 */ s16 unk270;
    /* 0x272 */ s16 unk272;
    /* 0x274 */ s16 unk274;
    /* 0x276 */ s16 unk276;
    /* 0x278 */ s16 unk278;
    /* 0x27A */ s16 unk27A;
    /* 0x27C */ f32 unk27C;
    /* 0x280 */ f32 unk280;
    /* 0x284 */ f32 unk284;
    /* 0x288 */ f32 unk288;
    /* 0x28C */ u8 pad28C[4];
    /* 0x290 */ s16 unk290;
    /* 0x292 */ u8 pad292[2];
    /* 0x294 */ G00Sub6 *unk294;
    /* 0x298 */ s16 *unk298;
    /* 0x29C */ s16 unk29C;
    /* 0x29E */ u8 pad29E[0x22];
    /* 0x2C0 */ u8 unk2C0;
    /* 0x2C1 */ u8 unk2C1;
    /* 0x2C2 */ u8 pad2C2[0x1A];
    /* 0x2DC */ u8 unk2DC[0xE];
    /* 0x2EA */ u8 unk2EA;
    /* 0x2EB */ u8 unk2EB;
    /* 0x2EC */ u8 pad2EC[4];
} G00Block; // size = 0x2F0

extern G00Block *D_807FC924;

void func_806C7C10(void) {
    D_807FC928 = D_80750AC0;
    D_807FC924 = 0;
    if (D_807FC928 >= 2) {
        switch (D_80750AB8) {
        case 0:
            D_80750AB4 = D_807FC928;
            break;
        case 1:
            D_80750AB4 = 1;
            break;
        }
    } else {
        D_80750AB4 = 1;
        D_80750AB8 = 0;
    }
}

typedef struct G00Entry {
    /* 0x0 */ u8 unk0;
    /* 0x1 */ u8 unk1;
    /* 0x2 */ u8 unk2;
    /* 0x3 */ u8 unk3;
    /* 0x4 */ s16 unk4;
    /* 0x6 */ s16 unk6;
    /* 0x8 */ s16 unk8;
    /* 0xA */ s16 unkA;
} G00Entry;

extern G00Entry D_80750948[];
extern u8 D_80750ABC;

G00Entry *func_806C7C94(u8 arg0) {
    u8 i;
    s32 found;

    i = 0;
    found = 0;
    do {
        if (D_807FC928 == D_80750948[i].unk0 && D_80750AB8 == D_80750948[i].unk1 && arg0 == D_80750948[i].unk3 &&
            (D_80750948[i].unk2 & D_80750ABC)) {
            found = 1;
        } else {
            i++;
        }
    } while (found == 0);
    return &D_80750948[i];
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/CC800/func_806C7D40.s")

extern u16 D_807FD570;

typedef struct G00View1F0 {
    /* 0x000 */ u8 pad0[0x1F0];
    /* 0x1F0 */ s32 unk1F0;
} G00View1F0;

f32 func_80612790(s16);
f32 func_80612794(s16);
void func_80689114(s16, f32, f32, f32, s32, f32, Actor *);

void func_806C80E4(void) {
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    f32 var2;

    if (D_807FD570 == 0x55) {
        sp28 = 20.0f;
    } else {
        sp28 = 0.0f;
    }
    sp30 = func_80612794(D_807FBB4C->unkE6) * sp28;
    var2 = func_80612790(D_807FBB4C->unkE6) * sp28;
    func_80689114((s16)D_807FD570, D_807FBB4C->unk7C + sp30, (f32)((f64)D_807FBB4C->unk80 + 7.0),
                  D_807FBB4C->unk84 + var2, 0, 1.0f, D_807FBB4C);
    ((G00View1F0 *)D_807FBB4C->unk174)->unk1F0 |= 0x01000000;
}

void func_806C81DC(s16 arg0, s16 arg1) {
    G00Block *p;

    p = D_807FC924;
    p->unk27A = arg1 - arg0;
    p->unk272 = arg0;
    p->unk276 = arg1;
    p->unk280 = (f32)p->unk278 / (f32)p->unk27A;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/CC800/func_806C8220.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CC800/func_806C850C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CC800/func_806C8984.s")

void func_806C8D20(Actor *arg0) {
    arg0->unk144 = 0x3C;
}

extern f32 D_8075C4B0;
extern u8 D_8075C417;
extern s32 D_8075C420;
extern u8 D_8075C427;
extern G00Row D_8075C430[];

u8 func_806C8D2C(s16 arg0) {
    G00Row *p;

    if (arg0 == D_8075C410[0].unk0) {
        return D_8075C417;
    }
    p = D_8075C430;
    if (arg0 == D_8075C420) {
        return D_8075C427;
    }
loop:
    if (arg0 == p[0].unk0) {
        return *((u8 *)&p[0].unk4 + 3);
    }
    if (arg0 == p[1].unk0) {
        return *((u8 *)&p[1].unk4 + 3);
    }
    if (arg0 == p[2].unk0) {
        return *((u8 *)&p[2].unk4 + 3);
    }
    if (arg0 == p[3].unk0) {
        return *((u8 *)&p[3].unk4 + 3);
    }
    p += 4;
    if (p != (G00Row *)&D_8075C4B0) {
        goto loop;
    }
    return 0;
}

typedef struct G00View1EE {
    /* 0x000 */ u8 pad0[0x1EE];
    /* 0x1EE */ s16 unk1EE;
} G00View1EE;

s32 func_806C8DE0(s32 arg0) {
    s32 var_v1;
    Actor *p;
    G00View1EE *q;

    var_v1 = D_8074E77C[arg0];
    if (var_v1 == 6 || var_v1 == 7) {
        p = D_807FC924[arg0].unk4;
        q = ((G00View1EE **)&p->unk174)[arg0];
        var_v1 = func_806C8D2C(q->unk1EE);
    }
    return var_v1;
}

void func_806C8F8C(void *);

#pragma GLOBAL_ASM("asm/global/nonmatchings/CC800/func_806C8E58.s")

typedef struct G00View8C {
    /* 0x00 */ u8 pad0[0x8C];
    /* 0x8C */ u8 unk8C;
} G00View8C;

void func_806C9C80();
void timerQueueAdd(void *, s32, s32, s32, s32);

void func_806C8EE8(void) {
    D_8074E77C[D_807FC929]++;
    D_8074E77C[D_807FC929] %= 8;
    ((G00View8C *)D_807FD580)->unk8C = 0;
    func_806C8F8C(&D_8075C410[D_8074E77C[D_807FC929]]);
    timerQueueAdd(func_806C9C80, 0x14, D_807FC929, 0, 0);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/CC800/func_806C8F8C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CC800/func_806C90C4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CC800/func_806C92C4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CC800/func_806C9304.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CC800/func_806C93E4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CC800/func_806C9434.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CC800/func_806C95D0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CC800/func_806C9658.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CC800/func_806C96C4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CC800/func_806C9830.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CC800/func_806C9974.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CC800/func_806C9AE0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CC800/func_806C9C1C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CC800/func_806C9C80.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CC800/func_806C9D20.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CC800/func_806C9D7C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CC800/D_8075C410.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CC800/D_8075C414.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CC800/D_8075C420.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CC800/D_8075C430.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CC800/D_8075C4B0.s")

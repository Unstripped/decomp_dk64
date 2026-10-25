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

typedef struct G01Sub4 {
    /* 0x00 */ u8 pad0[0x1C];
    /* 0x1C */ u8 *unk1C;
    /* 0x20 */ u8 *unk20;
    /* 0x24 */ u8 *unk24;
} G01Sub4;

typedef struct G01Sub104 {
    /* 0x000 */ u8 pad0[0x15F];
    /* 0x15F */ u8 unk15F;
} G01Sub104;

typedef struct G01Ctl {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ f32 unk4;
    /* 0x008 */ u8 pad8[0x48];
    /* 0x050 */ s16 unk50;
    /* 0x052 */ u8 pad52[0xB2];
    /* 0x104 */ G01Sub104 *unk104;
    /* 0x108 */ u8 pad108[0x9C];
    /* 0x1A4 */ u8 unk1A4;
    /* 0x1A5 */ u8 pad1A5[0x1B];
    /* 0x1C0 */ f32 unk1C0[3];
    /* 0x1CC */ f32 unk1CC[3];
    /* 0x1D8 */ u8 pad1D8[0x18];
    /* 0x1F0 */ u32 unk1F0;
    /* 0x1F4 */ u8 pad1F4[0xC];
    /* 0x200 */ s16 unk200;
    /* 0x202 */ u8 pad202[0x4E];
    /* 0x250 */ s32 unk250;
} G01Ctl;

typedef struct G01Act {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ G01Sub4 *unk4;
    /* 0x008 */ u8 pad8[0x50];
    /* 0x058 */ s32 unk58;
    /* 0x05C */ u8 pad5C[4];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u8 pad64[6];
    /* 0x06A */ u16 unk6A;
    /* 0x06C */ u8 pad6C[0x10];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x18];
    /* 0x0A0 */ f32 unkA0;
    /* 0x0A4 */ u8 padA4[8];
    /* 0x0AC */ f32 unkAC;
    /* 0x0B0 */ u8 padB0[8];
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ u8 padBC[0x28];
    /* 0x0E4 */ s16 unkE4;
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ s16 unkE8;
    /* 0x0EA */ u8 padEA[4];
    /* 0x0EE */ s16 unkEE;
    /* 0x0F0 */ u8 padF0[0x50];
    /* 0x140 */ ActorSub140 *unk140;
    /* 0x144 */ u8 pad144[0x10];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[0x1E];
    /* 0x174 */ G01Ctl *unk174;
    /* 0x178 */ void *unk178;
} G01Act;

typedef struct G01Pos {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ s16 unk4;
    /* 0x6 */ u8 unk6;
    /* 0x7 */ u8 unk7;
    /* 0x8 */ u8 unk8;
    /* 0x9 */ u8 unk9;
} G01Pos;

#define G01A ((G01Act *)D_807FBB48)

void func_806C8220(s32, void *, s32);
void func_806F833C(s32);

#ifdef NON_MATCHING
typedef struct G01Arg8F8C {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ u8 pad8[2];
    /* 0x0A */ u16 unkA;
    /* 0x0C */ u32 unkC;
} G01Arg8F8C;

void func_806136B4(Actor *, void *);
void actorSub140Free(ActorSub140 *);
void func_806134B4(Actor *, u16);
ActorSub140 *func_80665F24(Actor *);
void *func_80610FE8(s32);

void func_806C8F8C(void *arg) {
    G01Arg8F8C *arg0 = arg;

    G01A->unk58 = arg0->unk0;
    D_807FD584 = arg0->unk4;
    func_806136B4(D_807FBB48, arg0);
    actorSub140Free(G01A->unk140);
    func_806134B4(D_807FBB48, arg0->unkA);
    G01A->unk140 = func_80665F24(D_807FBB48);
    G01A->unk60 &= ~0x1000;
    G01A->unk60 |= arg0->unkC;
    G01A->unk4->unk1C = func_80610FE8(0x100);
    *G01A->unk4->unk1C = 0;
    G01A->unk4->unk20 = func_80610FE8(0x100);
    *G01A->unk4->unk20 = 0xFF;
    G01A->unk4->unk24 = func_80610FE8(0x100);
    *G01A->unk4->unk24 = 0xFF;
    func_806C8220(1, G01A->unk178, G01A->unk58);
    func_806F833C(0);
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/CC800/func_806C8F8C.s")
#endif

extern s16 D_8076AEE2;
#ifdef NON_MATCHING
extern s32 D_807FBB60;
extern s8 D_80770DC9;
G01Pos *func_806C96C4(s32);
void func_80614D00(Actor *, f32, f32);
void func_8067ACB4(Actor *);
void func_80614E78(Actor *, s32);
void func_806F39E8(Actor *, void *, s32);

void func_806C90C4(s32 arg0) {
    G01Ctl *sp24 = G01A->unk174;
    G01Pos *p = func_806C96C4(arg0);

    D_8076AEE2 = 0;
    D_807FBB60 &= ~0x400;
    switch (p->unk8) {
    case 2:
        G01A->unk154 = 0x4F;
        G01A->unk155 = 3;
        func_80614D00(D_807FBB48, 0.5f, 0.0f);
        sp24->unk50 = 1;
        G01A->unk6A |= 4;
        func_8067ACB4(D_807FBB48);
        func_80614E78(D_807FBB48, 0x34);
        /* fallthrough */
    case 0:
        G01A->unkAC = -10000.0f;
        G01A->unk7C = p->unk0;
        G01A->unk80 = G01A->unkA0 = p->unk2;
        G01A->unk84 = p->unk4;
        G01A->unkE6 = (p->unk6 / 255.0) * 4095.0;
        G01A->unkEE = G01A->unkE6;
        break;
    case 1:
        func_806F39E8(D_807FBB48, p, 0x32);
        break;
    }
    G01A->unk6A &= 0xFDFF;
    if ((s32)p->unk7 <= 0) {
        sp24->unk104->unk15F = 1;
    } else {
        sp24->unk104->unk15F = p->unk7;
    }
    if (p->unk9 & 1) {
        D_80770DC9 = 1;
    }
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/CC800/func_806C90C4.s")
#endif

void func_806C9434(s32);
void actorClearMovementFlags(void *);

void func_806C92C4(s32 arg0) {
    actorClearMovementFlags(D_807FBB48);
    func_806C9434(arg0);
    D_807FBB48->unk9C = D_807FBB48->unk80;
}

typedef struct G01Player {
    /* 0x000 */ u8 pad0[0x210];
    /* 0x210 */ f32 unk210;
    /* 0x214 */ f32 unk214;
    /* 0x218 */ f32 unk218;
    /* 0x21C */ f32 unk21C;
    /* 0x220 */ f32 unk220;
    /* 0x224 */ f32 unk224;
    /* 0x228 */ f32 unk228;
    /* 0x22C */ f32 unk22C;
    /* 0x230 */ f32 unk230;
    /* 0x234 */ f32 unk234;
    /* 0x238 */ f32 unk238;
    /* 0x23C */ f32 unk23C;
    /* 0x240 */ u8 pad240[0x60];
    /* 0x2A0 */ Actor *unk2A0;
    /* 0x2A4 */ u8 pad2A4[0x1C];
    /* 0x2C0 */ u8 unk2C0;
    /* 0x2C1 */ u8 pad2C1[0x2F];
} G01Player;

typedef struct G01Sub4f {
    /* 0x00 */ u8 pad0[0x34];
    /* 0x34 */ f32 unk34[3];
} G01Sub4f;

void func_806D0468(void *, s32, void *, void *);

void func_806C9304(Actor *arg0, G01Ctl *arg1) {
    s32 i;

    if (((G01Player *)D_807FC924)[arg1->unk1A4].unk2C0 != 1) {
        func_806D0468(D_807FBB48, 1, arg0, arg1);
    }
    if (((G01Sub4f *)arg0->unk4)->unk34[0] != arg1->unk1C0[0]) {
        for (i = 0; i < 3; i++) {
            arg1->unk1CC[i] = arg1->unk1C0[i];
            ((G01Sub4f *)arg0->unk4)->unk34[i] = arg1->unk1C0[i];
        }
    }
}

void func_806F12FC(void);

void func_806C93E4(Actor *arg0, Struct807FD580 *arg1) {
    func_806F12FC();
    arg1->unk1F0 &= ~0x30;
    arg0->unk60 |= 0x8000;
    arg0->unk128 = 0xFF;
}

extern u8 D_807FC950[][0x5E];
void func_800268DC(Actor *, void *, void *);
void sfxStopSlotSound(Actor *, u8);
void func_80709464(u8);
s32 func_8061CB50(void);
void func_8061EA78(void);
void func_8061EB04(Actor *, u8);
void func_806C8D20(Actor *);
void func_806CFF9C(Actor *);
void func_806C90C4(s32);

void func_806C9434(s32 arg0) {
    G01Ctl *ctl = G01A->unk174;
    s32 pad[1];
    void *sp34 = G01A->unk178;
    s32 pad2[1];
    void *sp2C;
    u8 i;

    func_806C8DE0(ctl->unk1A4);
    sp2C = &D_807FC950[0][ctl->unk1A4 * 0x306];
    ctl->unk250 = 0x78;
    i = 0;
    do {
        sfxStopSlotSound(D_807FBB48, i);
        i++;
    } while (i < 2);
    func_806C90C4(arg0);
    func_806C8220(0, sp34, G01A->unk58);
    func_80709464(ctl->unk1A4);
    G01A->unkB8 = 0.0f;
    ctl->unk1F0 &= 0xF7FFFF5F;
    ctl->unk200 = 0;
    ctl->unk4 = 0.0f;
    if (D_807FC928 >= 2) {
        func_800268DC(D_807FBB48, ctl, sp2C);
    }
    func_806C9304(D_807FBB48, ctl);
    if (func_8061CB50() == 0) {
        if (D_807FC928 >= 2 && D_80750AB8 == 1) {
            func_8061EA78();
        } else {
            func_8061EB04(D_807FBB48, ctl->unk1A4);
        }
    }
    func_806C8D20(D_807FBB48);
    func_806CFF9C(D_807FBB48);
    G01A->unkE8 = 0;
    G01A->unkE4 = 0;
}

extern G01Pos *D_807FC900;
extern u8 D_807FC904;
extern G01Pos D_807FC908;
extern G01Pos D_807FD574;
void *func_8066B0F8(s32, s32, s32, s32);
u32 assetGetCachedSizeOrResolve(s32, s32);
void func_806C9658(s32);

void func_806C95D0(s32 arg0) {
    D_807FC900 = func_8066B0F8(0x17, arg0, 1, 1);
    D_807FC904 = assetGetCachedSizeOrResolve(0x17, arg0) / 10U;
    func_806C9658(arg0);
    D_807FC908.unk6 = 0;
    D_807FC908.unk0 = D_807FD574.unk0;
    D_807FC908.unk2 = D_807FD574.unk2;
    D_807FC908.unk4 = D_807FD574.unk4;
}

s32 func_8073110C(s32, s32);

void func_806C9658(s32 arg0) {
    if (arg0 == 0x1E) {
        if (func_8073110C(0xA0, 0) != 0) {
            D_807FC900[18].unk2 = 0x65D;
            D_807FC900[23].unk2 = 0x65D;
        } else {
            D_807FC900[18].unk2 = 0x626;
            D_807FC900[23].unk2 = 0x626;
        }
    }
}

extern f32 D_8076AEE4;
extern f32 D_8076AEE8;
extern f32 D_8076AEEC;
extern s16 D_8076AEF0;
extern G01Pos D_807FC918;

G01Pos *func_806C96C4(s32 arg0) {
    if (D_8076AEE2 & 1) {
        D_807FC918.unk0 = D_8076AEE4;
        D_807FC918.unk2 = D_8076AEE8;
        D_807FC918.unk4 = D_8076AEEC;
        D_807FC918.unk6 = (D_8076AEF0 / 4095.0) * 360.0;
        return &D_807FC918;
    }
    if (D_807FC904 == 0) {
        return &D_807FC908;
    }
    if (arg0 >= D_807FC904) {
        return D_807FC900;
    }
    return &D_807FC900[arg0];
}

extern s32 D_807FBB64;
#ifdef NON_MATCHING
void func_800268C0();

s8 func_806C9830(s32 arg0, Actor *arg1) {
    Actor *p;
    s8 v = arg0;

    if (D_807FC928 >= 2) {
        p = ((G01Player *)D_807FC924)[((G01Act *)arg1)->unk174->unk1A4].unk2A0;
        if (p != NULL) {
            if (p->unk5C & 1) {
                v = -1;
                if (D_807FBB64 & 0x04000000) {
                    func_800268C0(1, arg1, v);
                }
            } else if (p->unk5C & 4) {
                if (p->unk58 == 0x29 || p->unk58 == 0xAB) {
                    v = -3;
                    if (D_807FBB64 & 0x04000000) {
                        func_800268C0(2, arg1, v);
                    }
                } else {
                    v = -2;
                    if (D_807FBB64 & 0x04000000) {
                        func_800268C0(1, arg1, v);
                    }
                }
            } else if (D_807FBB64 & 0x04000000) {
                func_800268C0(1, arg1, v);
            }
        }
    }
    return v;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/CC800/func_806C9830.s")
#endif

typedef struct G01Ent {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ u8 unk2;
    /* 0x03 */ u8 pad3[0x5B];
} G01Ent;

typedef struct G01Slot {
    /* 0x000 */ G01Ent ent[6];
    /* 0x234 */ u8 pad234[0xC7];
    /* 0x2FB */ s8 unk2FB;
    /* 0x2FC */ u8 unk2FC;
    /* 0x2FD */ s8 unk2FD;
    /* 0x2FE */ u8 pad2FE[8];
} G01Slot;

typedef struct G01PlayerFlags {
    /* 0x000 */ u8 pad0[0x2E2];
    /* 0x2E2 */ u16 unk2E2;
} G01PlayerFlags;

extern s32 D_807552EC;
void func_80026E20(u8, s8);
void func_8060E7EC(u8, s32, s32, s8);

s32 func_806C9974(arg0, arg1)
u8 arg0;
s8 arg1;
{
    G01PlayerFlags *pl;

    pl = (G01PlayerFlags *)&D_807FC924[arg0];
    pl->unk2E2 |= 0x11;
    if (D_807FC928 >= 2 && arg1 < 0 && D_807552EC == 1) {
        func_80026E20(arg0, arg1);
    }
    if (arg1 < 0) {
        func_8060E7EC(arg0, 0xFF, 5, arg1);
    }
    if (!(D_807FBB64 & 0x800)) {
        ((G01Slot *)D_807FC950)[arg0].unk2FD += arg1;
    }
    if (((G01Slot *)D_807FC950)[arg0].unk2FD + ((G01Slot *)D_807FC950)[arg0].unk2FB <= 0) {
        pl->unk2E2 |= 0xC0;
        return 1;
    }
    return 0;
}

#ifdef NON_MATCHING
extern s32 D_807552E4;
extern s8 D_80750ACC;
extern s32 D_807FD56C;
void func_806C7B00();

void func_806C9AE0(void) {
    G01Slot *p = (G01Slot *)D_807FC950;
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        bzero(p, 0x306);
        if (D_80750AC0 >= 2) {
            if (D_807552E4 == 1) {
                for (j = 0; j < 6; j++) {
                    p->ent[j].unk2 = 7;
                }
            }
            for (j = 0; j < 6; j++) {
                p->ent[j].unk1 = 1;
            }
        }
        p->unk2FC = 1;
        func_80709464(i);
        p++;
    }
    func_806C7B00();
    D_80750ACC = 0;
    D_807FD56C = 0;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/CC800/func_806C9AE0.s")
#endif

void func_806C9C1C(s32);

#ifdef NON_MATCHING
extern s32 D_80750B34[];
extern s32 D_80750B48;
void func_806F91B4(s32, u8, s32);

void func_806C9C1C(s32 arg0) {
    s32 *p = D_80750B34;

    do {
        func_806F91B4(*p, arg0, 0x270F);
    } while (++p != &D_80750B48);
    func_806F833C(0);
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/CC800/func_806C9C1C.s")
#endif

void func_8073129C(s32, s32, s32);

void func_806C9C80(s32 arg0, s32 arg1, s32 arg2) {
    s32 idx = func_806C8DE0(arg0);
    u8 *p = &D_807FC950[0][arg0 * 0x306 + idx * 0x5E];

    p[2] = 7;
    p[4] = 0xF;
    p[1] = 3;
    p[0] = 3;
    func_8073129C(0x179, 1, 0);
    func_806C9C1C(arg0);
}

void func_806C9D20(u8 arg0) {
    G01Player *p = (G01Player *)&D_807FC924[arg0];

    p->unk21C = p->unk210;
    p->unk220 = p->unk214;
    p->unk224 = p->unk218;
    p->unk234 = p->unk228;
    p->unk238 = p->unk22C;
    p->unk23C = p->unk230;
}

#ifdef NON_MATCHING
typedef struct G01Row {
    /* 0x00 */ u8 pad0[0x42];
    /* 0x42 */ u16 unk42[8];
    /* 0x52 */ u8 pad52[0xC];
} G01Row;

s32 func_806C9D7C(void) {
    G01Row *row = (G01Row *)D_807FC950[D_8074E77C[0]];
    s32 i;
    s32 v;

    i = 0;
    do {
        v = row->unk42[i] > 0;
        i++;
    } while (i < 8 && !v);
    return v;
}
#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/CC800/func_806C9D7C.s")
#endif

#pragma GLOBAL_ASM("asm/global/nonmatchings/CC800/D_8075C410.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CC800/D_8075C414.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CC800/D_8075C420.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CC800/D_8075C430.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CC800/D_8075C4B0.s")

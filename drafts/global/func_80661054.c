// func_80661054 (src/global/63EC0.c): Exact size 0x78 stack and control flow, ~8 regalloc diffs (v0 vs a2 in anti-piracy, t1 vs t5 in loop)
#include "common.h"

typedef struct R1D63EC0_SubNode {
    u8 pad[0x64];
    u8 val;
    u8 pad65;
    u8 unk66;
} R1D63EC0_SubNode;

typedef struct R1D63EC0_Node {
    R1D63EC0_SubNode *sub;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    u8 pad10[0x3A];
    u8 unk4A;
    u8 unk4B;
    u8 pad4C[4];
    struct R1D63EC0_Node *next;
} R1D63EC0_Node;

typedef struct R1D63EC0_Entry {
    void (*fn0)();
    void (*fn1)();
    void (*fn2)(R1D63EC0_Node *);
    void *res0;
    void *res1;
    u32 flags;
} R1D63EC0_Entry;

extern R1D63EC0_Node *D_807F93C0;
extern R1D63EC0_Entry D_80748A90[];
s32 func_806119A0(void);
u32 func_8066104C(s32);
extern s8 D_80746834;
extern OSMesgQueue D_807655F0;
extern OSIoMesg D_807ECE00;

void func_80661054(void) {
    u32 sp60[6];
    u32 *s1;
    R1D63EC0_Node *s0;
    u32 s2;

    s1 = sp60;
    s0 = D_807F93C0;
    if ((u32)s1 & 7) {
        s1++;
    }
    s2 = func_8066104C(-0xF81);
    osWritebackDCache(s1, 0x10);
    osPiStartDma(&D_807ECE00, 0, 0, s2, s1, 0x10, &D_807655F0);
    D_80746834 = 6;
    osRecvMesg(&D_807655F0, NULL, 1);
    D_80746834 = 0;
    osInvalDCache(s1, 0x10);
    {
        u32 t0 = s1[0];
        u32 t2 = s1[1];
        u32 t1 = t0 - 0x3E0EF0F0;
        u32 t3 = t2 - 0x3E0EF0F0;
        s1[0] = t1;
        s1[1] = t3;
        if (t1 != 0x3050A14A || t3 != 0xBCFCF506) {
            s1 = (u32 *)func_806119A0();
            s2 = func_806119A0();
            osPiStartDma(&D_807ECE00, 0, 0, (u32)s1 & 0xFFFF, (void *)((s2 & 0xFFFFE) + 0x80500000), (func_806119A0() & 0xFF) + 0x100, &D_807655F0);
        }
    }
    if (s0 != NULL) {
        do {
            if (s0->unk8 != s0->unk4) {
                if (s0->unk4 < s0->unk8) {
                    s0->unk4 += s0->unkC;
                    if (s0->unk8 < s0->unk4) {
                        s0->unk4 = s0->unk8;
                    }
                } else {
                    s0->unk4 -= s0->unkC;
                    if (s0->unk4 < s0->unk8) {
                        s0->unk4 = s0->unk8;
                    }
                }
            }
            D_80748A90[s0->sub->unk66].fn2(s0);
            s0 = s0->next;
        } while (s0 != NULL);
    }
}

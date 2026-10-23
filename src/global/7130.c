#include "common.h"
#include "actor.h"

extern u16 D_80745658[];

u8 func_80602430(arg0)
s16 arg0;
{
    return (D_80745658[arg0] & 6) >> 1;
}

u8 func_8060245C(arg0)
s16 arg0;
{
    return (D_80745658[arg0] & 0x78) >> 3;
}

extern u8 D_80745654;
void func_80602488(arg0)
u8 arg0;
{
    D_80745654 = arg0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/7130/func_80602498.s")

void func_80602498(void);
void func_806025AC(u8 arg0, u8 arg1, u8 arg2) {
    func_80602498();
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/7130/func_806025D4.s")

extern s16 D_807458DC[];
extern f32 D_807458F4[];
extern s16 D_80745924[];
extern s32 D_8074593C[][12];

void func_80602A94(s32 arg0, f32 arg1) {
    u8 v0;
    u8 i;
    s32 v1;

    v0 = func_8060245C((s16)arg0);
    if (arg0 != 0) {
        v1 = D_807458DC[v0];
        if (arg0 == v1 && (D_80745658[arg0] & 0x200) == 0) {
            return;
        }
        D_807458DC[v0] = arg0;
        D_807458F4[v0] = arg1;
        D_80745924[v0] = 0;
        for (i = 0; i < 4; i++) {
            D_8074593C[i][v0] = 0;
        }
    }
}

extern u8 D_80770560[];
extern ALCSPlayer *gSeqPlayers[];
void func_80602B60(arg0, arg1)
s32 arg0;
u8 arg1;
{
    u8 v1 = func_8060245C((s16)arg0);
    u8 v0 = func_80602430((s16)arg0);
    if (arg0 != 0 && arg0 == D_807458DC[v1]) {
        D_807458DC[v1] = 0;
        D_80745924[v1] = 0;
        if (arg1 != 0) {
            if (arg0 == D_80770560[v0]) {
                alSeqpStop((ALSeqPlayer *)gSeqPlayers[v0]);
            }
        }
    }
}

void func_80602C0C(void) {
    u8 i;
    for (i = 0; i < 12; i++) {
        if (D_807458DC[i] != 0) {
            func_80602B60(D_807458DC[i], 1);
        }
    }
}


void func_8060A60C();

void func_80602C6C(arg0, arg1)
s32 arg0;
s32 arg1;
{
    u8 v1 = func_80602430((s16)arg0);
    if ((arg0 == D_807458DC[func_8060245C((s16)arg0)]) && (arg0 == D_80770560[v1])) {
        func_8060A60C(v1, arg1);
    }
}



void func_80602CE0(arg0, arg1, arg2)
s32 arg0;
s32 arg1;
u8 arg2;
{
    s16 a = arg0;
    s32 temp = func_8060245C(a);
    if (arg0 == D_807458DC[temp]) {
        D_8074593C[arg2][temp] = arg1;
    }
}

extern f32 D_80770568[];

f32 func_80602D4C(arg0)
s32 arg0;
{
    s16 a = arg0;
    u8 v0 = func_80602430(a);
    if (arg0 == D_80770560[v0]) {
        if (alCSPGetState(gSeqPlayers[v0]) == 1) {
            return D_80770568[v0];
        }
    }
    return 0.0f;
}

void func_80602DC4(s32 arg0, f32 arg1) {
    u8 v1 = func_80602430((s16)arg0);
    if ((arg0 == D_807458DC[func_8060245C((s16)arg0)]) && (arg0 == D_80770560[v1])) {
        alCSPSetTempo(gSeqPlayers[v1], (s32)((s32)alCSPGetSeq(gSeqPlayers[v1]) * arg1));
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/7130/func_80602E6C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7130/func_80603340.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7130/func_80603450.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7130/func_806049CC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7130/func_80604BE8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7130/func_80604C80.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7130/func_80604CBC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7130/func_80604D70.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7130/func_80605044.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7130/func_80605314.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7130/func_80605380.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7130/func_80605510.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7130/func_806057F8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7130/func_80608528.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7130/func_806085DC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7130/func_8060866C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7130/func_806086CC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7130/func_80608DA8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7130/func_80609140.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7130/func_8060956C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7130/func_80609B80.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7130/func_8060A1B0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7130/func_8060A398.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7130/func_8060A4D0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7130/func_8060A500.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7130/func_8060A60C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7130/func_8060A634.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7130/func_8060A670.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/7130/func_8060A6A0.s")

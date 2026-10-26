#include "common.h"
#include "actor.h"

extern Actor *D_807FBB44;

typedef struct {
    u8 r;
    u8 g;
    u8 b;
} M2CColour;

const M2CColour D_80757F70[8] = {
    { 0xFF, 0xFF, 0xFF },
    { 0xC8, 0x00, 0x32 },
    { 0xDC, 0xC8, 0x00 },
    { 0x32, 0xC8, 0x00 },
    { 0xCA, 0x5B, 0xFF },
    { 0x00, 0x96, 0xFF },
    { 0x32, 0x32, 0xFA },
    { 0x00, 0x00, 0x00 },
};

void func_80627C10(u8 arg0) {
    D_807FBB44->unk16A = D_80757F70[arg0].r;
    D_807FBB44->unk16B = D_80757F70[arg0].g;
    D_807FBB44->unk16C = D_80757F70[arg0].b;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/2C910/func_80627C5C.s")

extern Actor *D_807FBB4C;
Actor *spawnNodeActivate(s16, s32);

Actor *func_80627EA8(s16 arg0) {
    Actor *v;

    if (arg0 != 0) {
        v = spawnNodeActivate(arg0, 0);
    }
    if ((arg0 == 0) || (v == 0)) {
        v = D_807FBB4C;
    }
    return v;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/2C910/func_80627F04.s")

extern Actor *D_807FBB40;

s32 func_80629148(void) {
    s32 r = 0;

    if (D_807FBB40->unk6A & 0x100) {
        D_807FBB40->unk6A &= 0xFEFF;
        r = 1;
    }
    return r;
}

void func_80629174(void) {
    D_807FBB40->unk6A &= 0xFEFF;
}

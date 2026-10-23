// func_80666428 (src/global/6AD90.c): 419 insns vs 425 insns, 96% matched; regalloc near-miss: IDO spills arg0 to 0x68(sp) instead of allocating callee-saved s0 (0x28(sp)) due to branch frequency estimation in switch/if
#include "common.h"
#include "actor.h"

typedef struct R5M_Actor174 {
    u8 pad0[0x1F0];
    u32 unk1F0;
} R5M_Actor174;

typedef struct R5M_Actor {
    u8 pad0[0x5C];
    u16 unk5C;
    u8 pad5E[6];
    u32 unk64;
    u16 pad68;
    u16 unk6A;
    u16 unk6C;
    u8 pad6E[0x36];
    f32 unkA4;
    f32 unkA8;
    u8 padAC[0x24];
    u8 unkD0;
    u8 unkD1;
    u8 padD2[6];
    s16 unkD8;
    s16 unkDA;
    u8 padDC[0x30];
    s16 unk10C;
    u8 pad10E[2];
    u8 unk110;
    u8 pad111[0x63];
    R5M_Actor174 *unk174;
} R5M_Actor;

u8 func_80667180(f32, f32, f32 *, s32);
s32 func_80666FC8(f32, f32, f32, u8);
u8 func_8062BCC8(R5M_Actor *, f32, f32, f32, f32 *);
s32 func_8066A08C(R5M_Actor *, f32, f32, f32, f32 *);
void func_8067A7EC(R5M_Actor *, s32, s32, s32, f32, s32, u8);
void func_806663F8(void);
extern f32 D_807F9460;
extern u8 D_807F9464;
extern f32 D_807F9468;
extern u8 D_807F946C;
extern u8 D_807F946D;
extern u8 D_807F946E;
extern s32 D_807F9470;
extern s32 D_807F9474;
extern s32 D_807F9478;
extern f32 D_807F947C;
extern s32 D_807F9480;
extern u8 D_807F9484;
extern f32 D_807F948C;
extern s16 D_807F9490;
extern s16 D_807F9492;
extern s16 D_807F9494;
extern s16 D_807F9498;
extern s16 D_807F949A;
extern s16 D_807F949C;
extern u8 D_807F949E;
extern u8 D_807F949F;
extern u8 D_807F94A0;
extern s16 D_807F94A2;
extern s16 D_807F94A4;
extern u8 D_807F94AA;
extern u8 D_807F94AB;
extern u8 D_807F94AC;
extern u8 D_807F94AD;
extern u8 D_807F94B2;
extern u8 D_807F94B4;
extern u8 D_807F94B6;
extern R5M_Actor174 *D_807F94B8;
extern u8 D_807F9510;
extern u8 D_807F951D;

s32 func_80666428(Actor *arg0, f32 arg1, f32 arg2, f32 arg3, u8 *arg4, f32 *arg5, u8 *arg6, f32 *arg7, u8 arg8) {
    u8 sp5F;
    u8 sp5E;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    u8 sp4D;
    f32 sp40;
    s32 sp3C;
    s32 sp38;
    s32 sp34;
    u8 val2;

    D_807F946E = 0;
    if (D_807F94B4 == 1) {
        func_806663F8();
        *arg4 = 0;
        *arg6 = 0;
        D_807F94B4 = 0;
        return 0;
    }
    if (arg0 != NULL) {
        ((R5M_Actor *)arg0)->unk110 = 0;
        ((R5M_Actor *)arg0)->unk10C = -1;
        ((R5M_Actor *)arg0)->unk6A &= 0xFBF1;
        D_807F94B6 = 0;
        D_807F9464 = 0;
        D_807F946C = 0;
        D_807F946D = arg8;
        ((R5M_Actor *)arg0)->unk64 &= ~0x40;
        if (((R5M_Actor *)arg0)->unk5C & 1) {
            D_807F94B8 = ((R5M_Actor *)arg0)->unk174;
            D_807F94B8->unk1F0 &= ~0x6000;
        }
    }
    D_807F951D = 0;
    D_807F94AB = 0;
    D_807F94AC = 0;
    D_807F94AD = 0;
    func_806663F8();
    D_807F94B2 = 0;
    D_807F9484 = 0;
    D_807F9510 = 0;
    sp58 = arg2;
    sp5F = func_80667180(arg1, arg3, &sp58, (s32)arg0);
    if ((sp5F != 0) && (arg0 != NULL)) {
        ((R5M_Actor *)arg0)->unkA8 = sp58;
        ((R5M_Actor *)arg0)->unkD0 = D_807F949E;
    }
    val2 = 0;
    if (D_807F94B4 != 2) {
        sp54 = 99999.0f;
        sp5E = func_8062BCC8((R5M_Actor *)arg0, arg1, arg3, arg2, &sp54);
        sp50 = 99999.0f;
        val2 = func_8066A08C((R5M_Actor *)arg0, arg1, arg3, arg2, &sp50) & 0xFF;
    } else {
        sp5E = 0;
    }
    sp3C = (sp5E * 2) & 0xFF;
    sp38 = (val2 * 4) & 0xFF;
    sp34 = sp5F;
    switch ((sp5F + sp3C + sp38) & 0xFF) {
    case 0:
        sp4D = 0;
        break;
    case 1:
        sp4D = 1;
        break;
    case 2:
        sp4D = 2;
        break;
    case 3:
        sp4D = 2;
        if (func_80666FC8(sp54, sp58, (f32)((f64)arg2 + 4.0), 0) != 0) {
            sp4D = 1;
        }
        break;
    case 4:
        sp4D = 3;
        break;
    case 5:
        sp4D = 3;
        if (func_80666FC8(sp50, sp58, (f32)((f64)arg2 + 4.0), 0) != 0) {
            sp4D = 1;
        }
        break;
    case 6:
        sp4D = 3;
        if (func_80666FC8(sp50, sp54, (f32)((f64)arg2 + 4.0), 0) != 0) {
            sp4D = 2;
        }
        break;
    case 7:
        sp40 = (f32)((f64)arg2 + 4.0);
        if (func_80666FC8(sp54, sp58, sp40, 0) != 0) {
            sp4D = 3;
            if (func_80666FC8(sp50, sp58, sp40, 0) != 0) {
                sp4D = 1;
            }
        } else {
            sp4D = 2;
            if (func_80666FC8(sp54, sp50, sp40, 0) != 0) {
                sp4D = 3;
            }
        }
        break;
    }
    switch (sp4D) {
    default:
        D_807F94AA = 0;
        break;
    case 1:
        if (arg0 != NULL) {
            ((R5M_Actor *)arg0)->unkD1 = D_807F949E;
            ((R5M_Actor *)arg0)->unkDA = D_807F9498;
            ((R5M_Actor *)arg0)->unkD8 = D_807F9490;
            ((R5M_Actor *)arg0)->unkA4 = sp58;
            if ((D_807F94B6 != 0) && (((R5M_Actor *)arg0)->unk6C & 1)) {
                ((R5M_Actor *)arg0)->unk6A |= 0x400;
            }
        }
        D_807F94A4 = D_807F9498;
        D_807F94A2 = D_807F9490;
        D_807F948C = sp58;
        D_807F94AA = D_807F94AB;
        D_807F951D = 1;
        break;
    case 2:
        if (arg0 != NULL) {
            ((R5M_Actor *)arg0)->unkD1 = D_807F949F;
            ((R5M_Actor *)arg0)->unkDA = D_807F949A;
            ((R5M_Actor *)arg0)->unkD8 = D_807F9492;
            ((R5M_Actor *)arg0)->unkA4 = sp54;
            if (((R5M_Actor *)arg0)->unk6C & 1) {
                ((R5M_Actor *)arg0)->unk110 = 1;
            }
        }
        D_807F94A4 = D_807F949A;
        D_807F94A2 = D_807F9492;
        D_807F948C = sp54;
        D_807F94AA = D_807F94AC;
        D_807F951D = 2;
        break;
    case 3:
        if (arg0 != NULL) {
            ((R5M_Actor *)arg0)->unkD1 = D_807F94A0;
            ((R5M_Actor *)arg0)->unkDA = D_807F949C;
            ((R5M_Actor *)arg0)->unkD8 = D_807F9494;
            ((R5M_Actor *)arg0)->unkA4 = sp50;
            if (((R5M_Actor *)arg0)->unk6C & 1) {
                func_8067A7EC((R5M_Actor *)arg0, D_807F9470, D_807F9474, D_807F9478, D_807F947C, D_807F9480, D_807F94B2);
                ((R5M_Actor *)arg0)->unk6A |= 8;
            }
        }
        D_807F94A4 = D_807F949C;
        D_807F94A2 = D_807F9494;
        D_807F948C = sp50;
        D_807F94AA = D_807F94AD;
        D_807F951D = 3;
        break;
    }
    *arg4 = D_807F9464;
    *arg5 = D_807F9460;
    *arg6 = D_807F946C;
    *arg7 = D_807F9468;
    D_807F94B4 = 0;
    return (sp34 | sp3C | sp38) & 0xFF;
}

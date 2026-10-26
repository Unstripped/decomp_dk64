#include "common.h"
#include "actor.h"

typedef struct ModelSlot {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ u8 padC[0x14];
    /* 0x20 */ void *unk20;
    /* 0x24 */ u8 *unk24;
    /* 0x28 */ u8 pad28[0x4C];
    /* 0x74 */ void *unk74;
    /* 0x78 */ u8 *unk78;
    /* 0x7C */ void *unk7C;
    /* 0x80 */ u8 pad80[4];
    /* 0x84 */ s16 unk84;
    /* 0x86 */ s16 unk86;
    /* 0x88 */ u8 pad88[4];
    /* 0x8C */ u8 unk8C;
    /* 0x8D */ u8 pad8D[3];
} ModelSlot; /* 0x90, indexed by hashTableLookup() */

extern ModelSlot *D_807F6000;

extern void *D_807FC924;
extern u8 D_807FC929;
extern s32 D_8076A064;
extern s32 D_8076A0A8;
extern u8 D_807444FC;

s32 hashTableLookup(s32);
void heapFree(void *);
void *func_80610FE8(s32);
void assetFreeBuffer(void *, s32, s32);

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80631B80.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80631B8C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80631BCC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80631C20.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80631C3C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80631D8C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80631EB8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80631F58.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80631FAC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80632084.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_806323C0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_8063253C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_8063254C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80632630.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80632860.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80632E10.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80632E74.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80632F20.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80632F74.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80632FCC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_806330C4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_806333F8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80633570.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_806335B0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_8063367C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_8063373C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_806338B4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_806338F4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_8063393C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80633A1C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80633D30.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80633DC0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80634768.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_806348B4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80634908.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_8063495C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_806349FC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80634CC8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80634D14.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80634D64.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80634E10.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80634EA4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80634EDC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80634F14.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80634FA0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80635018.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80635098.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80635114.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80635214.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_8063524C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80635468.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80635548.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80635588.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_806355DC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_806357F8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_806358E8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80635EF0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80636014.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80636074.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80636164.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80636210.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_806362C4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80636380.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_8063643C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80636448.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_806364C4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_806365D0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80636784.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_806368F0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80636A44.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80636A8C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80636AE8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80636B50.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80636C00.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80636D38.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80636EFC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80636FFC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80637B6C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_806392BC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_806398E4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80639968.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80639C04.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80639CD0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80639F1C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_80639FC0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_8063A38C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_8063A848.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_8063A8C4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_8063A968.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_8063B4A4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_8063B4C0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_8063B758.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_8063B8D8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_8063BBB0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_8063BEC0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_8063BF34.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_8063C1EC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_8063C248.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_8063C2A8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/36880/func_8063C328.s")

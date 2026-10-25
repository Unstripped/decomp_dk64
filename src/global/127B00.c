#include "common.h"
#include "actor.h"

void *func_80610FE8(s32);
typedef struct Uc1Path {
    u8 *unk0;
    s16 unk4;
} Uc1Path;

typedef struct Uc1Playback {
    s32 unk0;
    u8 *unk4;
    s16 unk8;
    u8 padA[2];
    f32 unkC;
    s16 unk10;
    u8 pad12[2];
    u8 unk14;
    u8 unk15;
    u8 unk16;
    u8 pad17;
    s32 unk18;
    s32 unk1C;
    u8 unk20;
    u8 unk21;
} Uc1Playback;

extern Uc1Path *D_807FDB90[];

#pragma GLOBAL_ASM("asm/global/nonmatchings/127B00/func_80722E00.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/127B00/func_80722E48.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/127B00/func_80722FEC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/127B00/func_80723020.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/127B00/func_80723284.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/127B00/func_807232B8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/127B00/func_807232EC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/127B00/func_80723320.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/127B00/func_8072334C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/127B00/func_80723380.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/127B00/func_807233B4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/127B00/func_80723428.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/127B00/func_80723484.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/127B00/func_807238D4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/127B00/func_80723C98.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/127B00/func_80723CCC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/127B00/func_80723F88.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/127B00/func_80724154.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/127B00/func_80724308.s")

s16 func_807245D8(s32 arg0) {
    return D_807FDB90[arg0]->unk4;
}

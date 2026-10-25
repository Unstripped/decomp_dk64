#include "common.h"
#include "actor.h"

void *func_80610FE8(s32);
typedef struct PathEntry {
    u8 *unk0;
    s16 unk4;
} PathEntry;


typedef struct PathPlayback {
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
} PathPlayback;

extern PathEntry *D_807FDB90[];


void assetFreeBuffer(s32, s32, s32);
s32 func_8066B0F8(s32, s32, s32, s32);
void func_80722E48(s16 *);

void pathFreeAsset(s32 arg0) {
    s32 sp1C;
    s32 temp_v0;

    temp_v0 = func_8066B0F8(0xF, arg0, 1, 1);
    sp1C = temp_v0;
    func_80722E48((s16 *) temp_v0);
    assetFreeBuffer(sp1C, 0x47, 0x27);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/127B00/func_80722E48.s")

s32 pathExists(u8 arg0) {
    if (D_807FDB90[arg0] != NULL) {
        return 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/127B00/func_80723020.s")
extern PathPlayback *D_807FDBF8[];


void func_80723284(s32 arg0, u8 arg1) {
    PathPlayback *temp_v0;

    if (arg0 != -1) {
        temp_v0 = D_807FDBF8[arg0];
        if (temp_v0 != NULL) {
            temp_v0->unk20 = arg1;
        }
    }
}

void func_807232B8(s32 arg0, u8 arg1) {
    PathPlayback *temp_v0;

    if (arg0 != -1) {
        temp_v0 = D_807FDBF8[arg0];
        if (temp_v0 != NULL) {
            temp_v0->unk16 = arg1;
        }
    }
}

void func_807232EC(s32 arg0, u8 arg1) {
    PathPlayback *temp_v0;

    if (arg0 != -1) {
        temp_v0 = D_807FDBF8[arg0];
        if (temp_v0 != NULL) {
            temp_v0->unk15 = arg1;
        }
    }
}

void func_80723320(s32 arg0, s32 arg1) {
    PathPlayback *temp_v0;

    if (arg0 != -1) {
        temp_v0 = D_807FDBF8[arg0];
        if (temp_v0 != NULL) {
            temp_v0->unk18 = arg1;
        }
    }
}

void func_8072334C(s32 arg0, u8 arg1) {
    PathPlayback *temp_v0;

    if (arg0 != -1) {
        temp_v0 = D_807FDBF8[arg0];
        if (temp_v0 != NULL) {
            temp_v0->unk21 = arg1;
        }
    }
}

void func_80723380(s32 arg0, u8 arg1) {
    PathPlayback *temp_v0;

    if (arg0 != -1) {
        temp_v0 = D_807FDBF8[arg0];
        if (temp_v0 != NULL) {
            temp_v0->unk14 = arg1;
        }
    }
}

void func_80723428(s32);

void pathPlaybackStopForActor(s32 arg0) {
    PathPlayback **var_s1;
    PathPlayback *temp_v0;
    s32 var_s0;

    var_s1 = D_807FDBF8;
    var_s0 = 0;
    do {
        temp_v0 = *var_s1;
        if ((temp_v0 != NULL) && (arg0 == temp_v0->unk0)) {
            func_80723428(var_s0);
        }
        var_s0 += 1;
        var_s1 += 1;
    } while (var_s0 != 0x20);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/127B00/func_80723428.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/127B00/func_80723484.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/127B00/func_807238D4.s")

u8 func_80723C98(s32 arg0) {
    PathPlayback *temp_v1;

    if ((arg0 == -1) || ((temp_v1 = D_807FDBF8[arg0]) == NULL)) {
        return 0;
    }
    return temp_v1->unk21;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/127B00/func_80723CCC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/127B00/func_80723F88.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/127B00/func_80724154.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/127B00/func_80724308.s")

s16 pathEntryCount(s32 arg0) {
    return D_807FDB90[arg0]->unk4;
}

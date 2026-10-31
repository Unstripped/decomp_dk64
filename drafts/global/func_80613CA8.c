// func_80613CA8 (src/global/17B90.c): stage 5: frame 0x38, 2 saved regs s0/s1 match target (improved from starter frame 0x30/3 saved regs); first 80+ instructions match 1:1; remaining diff is float zero regalloc in unk40/resource paths and store reordering
#include "common.h"

typedef struct {
    f32 unk0;
    u16 unk4;
    u8 pad6[0xC];
    u8 unk12;
} RvT2_Resource;

typedef struct {
    RvT2_Resource *unk0;
    f32 unk4;
    f32 unk8;
    s16 unkC;
    s16 unkE;
    s16 unk10;
    u8 pad12[2];
    f32 unk14;
    f32 unk18;
    s16 unk1C;
    u8 pad1E[6];
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
} RvT2_Slot;

typedef struct {
    RvT2_Slot *unk0;
    RvT2_Slot *unk4;
    RvT2_Slot *unk8;
    RvT2_Slot *unkC;
    f32 unk10;
    u8 pad14[0x14];
    s16 unk28;
    s16 unk2A;
    u8 pad2C[0x14];
    f32 unk40;
    f32 unk44;
    f32 unk48;
    u8 pad4C[0x2C];
    s32 unk78;
    s32 unk7C;
    f32 unk80;
} RvT2_AnimData;

typedef struct {
    void *unk0;
    RvT2_AnimData *unk4;
} RvT2_ControllerStateView;

void func_80613944();
void *func_80614130(s32 id);
void func_80614644();

void func_80613CA8(RvT2_ControllerStateView *arg0, s16 arg1, f32 arg2, f32 arg3) {
    void *pad;
    RvT2_AnimData *anim;
    RvT2_Slot *slot0;
    RvT2_Slot *slot4;
    RvT2_Slot *slot8;
    RvT2_Slot *slotC;
    RvT2_Resource *resource;
    f32 temp_f;
    s16 temp_s;

    anim = (RvT2_AnimData *)arg0->unk4;
    slot0 = anim->unk0;
    slot8 = anim->unk8;
    slot4 = anim->unk4;
    slotC = anim->unkC;

    if (slot8->unk0 != NULL) {
        func_80613944(arg0, slot8);
    }
    if (slotC->unk0 != NULL) {
        func_80613944(arg0, slotC);
    }

    if ((arg1 & 0x4000) == 0x4000) {
        arg1 -= 0x4000;
        if (slot4->unk0 != NULL) {
            slotC->unk0 = func_80614130(slot4->unk10);
            slotC->unk4 = slot4->unk4;
            slotC->unk8 = slot4->unk8;
            slotC->unkC = slot4->unkC;
            slotC->unkE = slot4->unkE;
            slotC->unk10 = slot4->unk10;
            slotC->unk1C = slot4->unk1C;
            slotC->unk14 = slot4->unk14;
            slotC->unk18 = slot4->unk18;
            slotC->unk34 = slot4->unk34;
            slotC->unk24 = slot4->unk24;
            slotC->unk2C = slot4->unk2C;
            slotC->unk28 = slot4->unk28;
            slotC->unk30 = slot4->unk30;
            anim->unk2A = anim->unk28;
        } else {
            anim->unk2A = 0;
        }
    }

    if (arg3 > 0.0f) {
        temp_f = anim->unk48;
        if (temp_f > 0.0f) {
            anim->unk40 = temp_f;
        } else {
            anim->unk40 = -temp_f;
        }
        if (anim->unk40 < arg3) {
            anim->unk44 = arg3;
        } else {
            anim->unk44 = anim->unk40;
        }
        anim->unk10 = (anim->unk44 - anim->unk40) / anim->unk44;
    } else {
        if (slot0->unk0 != NULL) {
            func_80613944(arg0, slot0);
        }
        if (slot4->unk0 != NULL) {
            func_80613944(arg0, slot4);
        }
    }

    resource = func_80614130(arg1);
    if (resource != NULL) {
        slot8->unk0 = resource;
        slot8->unk10 = arg1;
        slot8->unk1C = resource->unk4;
        slot8->unk14 = 0.0f;
        slot8->unk34 = 0.0f;
        slot8->unk18 = (f32)(resource->unk12 - 1);
        slot8->unk24 = resource->unk0;
        slot8->unk2C = resource->unk0;
        slot8->unk28 = resource->unk0;
        slot8->unk30 = 0.0f;
    } else {
        slot8->unk0 = NULL;
        slot8->unk10 = -1;
        slot8->unk1C = 0;
        slot8->unk14 = 0.0f;
        slot8->unk18 = 0.0f;
        slot8->unk34 = 0.0f;
        slot8->unk24 = 0.0f;
        slot8->unk2C = 0.0f;
        slot8->unk28 = 0.0f;
        slot8->unk30 = 0.0f;
    }

    anim->unk78 = 0;
    anim->unk7C = 0;
    anim->unk80 = 0.0f;
    temp_s = anim->unk2A;
    anim->unkC = slot4;
    anim->unk0 = slot8;
    anim->unk4 = slotC;
    anim->unk8 = slot0;
    anim->unk2A = ((u8 *)&anim->unk28)[1];
    anim->unk28 = temp_s;

    func_80614644(arg0, slot8, arg2);
}

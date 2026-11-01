// func_806358E8 (src/global/36880.c): stage 4 (NM36A2): s0-s4 + frame 0x80 match; 43056 vs 43024 bytes, 72-line diff. Parked NON_MATCHING in OlB copy. Needs file proto s32 mapPurgeNodeList(s32,s16*,u8). Recipe: off=arg0*0x90 var set before the arg9 block (OLB_SL=D_807F6000+off); blocks 2-4 via v1 and p=v1->unk20; player loop index as shift chain macro PLY(i) (i*0x2F0 gives multu+li 752 hoist); bbox arg (u8*)(off+(s32)D_807F6000+0x54); deadsweep: 'if (i==0){}' after the XZ call in the case-1 loop (7->5 s-regs) + 'if (gPlayerSlots==0){}'. Remaining: D_807F6000 value reload lives in a2 (target t0), loop i copied via v1 (target s0 direct). s32 toggles of collisionTransformNode/actorUpdateEntryCoordinates, more deadsweep rounds (incl arg10/11/13/sp76): no gain.
// context: file-level ModelSlot *D_807F6000, ModelSlotVectors, ModelVertTable decls come from 36880.c
typedef struct OlB_Tgt {
    /* 0x00 */ u8 pad0[0x7C];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
    /* 0x84 */ f32 unk84;
} OlB_Tgt;

typedef struct OlB_Player {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 pad1[3];
    /* 0x04 */ OlB_Tgt *unk4;
    /* 0x08 */ u8 pad8[0x2E8];
} OlB_Player;

typedef struct OlB_Kind {
    /* 0x00 */ u8 pad0[0x67];
    /* 0x67 */ u8 unk67;
    /* 0x68 */ s16 unk68;
    /* 0x6A */ s16 unk6A;
    /* 0x6C */ s16 unk6C;
} OlB_Kind;

typedef struct OlB_Meta {
    /* 0x00 */ u8 pad0[0x1E];
    /* 0x1E */ s16 unk1E;
} OlB_Meta;

typedef struct OlB_SlotG {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ ModelSlotVectors *unk20;
    /* 0x24 */ OlB_Meta *unk24;
    /* 0x28 */ u8 pad28[0x54];
    /* 0x7C */ OlB_Kind *unk7C;
    /* 0x80 */ u8 pad80[6];
    /* 0x86 */ s16 unk86;
    /* 0x88 */ s16 unk88;
    /* 0x8A */ s16 unk8A;
    /* 0x8C */ u8 pad8C[4];
} OlB_SlotG;

extern u8 gPlayerCount;
s32 activeActorBoxOverlapTest(f32, f32, f32, s16, s16, s16, u16);
s32 collisionCheckBoundingBoxXZ(void *, f32, f32);
s32 collisionCheckBoundingBoxY(void *, f32);
void collisionTransformNode(s32, void *, f32, f32, f32, f32, f32, f32, f32);
void modelSlotBuildTriangleBufferThunk(s32, void *, f32, f32, f32, f32, f32, f32, f32);
void actorUpdateEntryCoordinates(s16, f32, f32, f32, f32, f32);

#define PLY(i) ((OlB_Player *)((u8 *)gPlayerSlots + ((((((i) << 2) - (i)) << 4) - (i)) << 4)))
#define OLB_SL0 ((OlB_SlotG *)((u8 *)D_807F6000 + arg0 * 0x90))
#define OLB_SL ((OlB_SlotG *)((u8 *)D_807F6000 + off))

void func_806358E8(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, u8 arg9, u8 arg10, u8 arg11, u8 arg12, u8 arg13) {
    OlB_SlotG *v1;
    ModelSlotVectors *p;
    s16 sp76;
    u8 flag;
    u8 i;
    s32 off;

    flag = 0;
    if (arg13 == 1) {
        arg0 = hashTableLookup(arg0);
    }
    if (arg12) {
        OLB_SL0->unk1C = arg8;
        v1 = OLB_SL0;
        switch (v1->unk86) {
            case 2:
                p = v1->unk20;
                p->unk10 = arg8;
                break;
            case 1:
                p = v1->unk20;
                p->unk1C = arg8;
                break;
        }
    }
    off = arg0 * 0x90;
    if (arg9) {
        OLB_SL->unk0 = arg1;
        OLB_SL->unk4 = arg2;
        OLB_SL->unk8 = arg3;
        v1 = OLB_SL;
        switch (v1->unk86) {
            case 2:
                p = v1->unk20;
                p->unk0 = arg1;
                p->unk4 = arg2;
                p->unk8 = arg3;
                break;
            case 1:
                p = v1->unk20;
                p->unk0 = arg1;
                p->unk4 = arg2;
                p->unk8 = arg3;
                break;
        }
    }
    if (arg10) {
        OLB_SL->unk10 = arg4;
        OLB_SL->unk14 = arg5;
        OLB_SL->unk18 = arg6;
        v1 = OLB_SL;
        if (v1->unk86 == 1) {
            p = v1->unk20;
            p->unk10 = arg4;
            p->unk14 = arg5;
            p->unk18 = arg6;
        }
    }
    if (arg11) {
        OLB_SL->unkC = arg7;
        v1 = OLB_SL;
        switch (v1->unk86) {
            case 2:
                p = v1->unk20;
                p->unkC = arg7;
                break;
            case 1:
                p = v1->unk20;
                p->unkC = arg7;
                break;
        }
    }
    if ((arg9 || arg12) && mapPurgeNodeList((s32)OLB_SL->unk20, &sp76, 0)) {
        v1 = OLB_SL;
        renderEntryAddOrUpdate(0, ((u8 *)v1)[0x87], v1->unk20, v1->unk0, v1->unk4, v1->unk8, v1->unk24->unk1E, v1->unk88, 0, sp76, 2);
    }
    v1 = OLB_SL;
    if (arg9 || arg12 || arg10) {
        actorUpdateEntryCoordinates(v1->unk88, v1->unk0, v1->unk4, v1->unk8, v1->unkC, v1->unk14);
        v1 = OLB_SL;
    }
    if (v1->unk7C != NULL) {
        switch (v1->unk7C->unk67) {
            case 0:
                flag = 1;
                break;
            case 2:
                if (gPlayerSlots != 0) {
                    i = 0;
                    if (gPlayerCount > 0) {
                        do {
                            if (PLY(i)->unk0 != 0) {
                                s32 hit = collisionCheckBoundingBoxY((u8 *)(off + (s32)D_807F6000 + 0x54), PLY(i)->unk4->unk80) != 0;
                                if (hit != 0) {
                                    hit = collisionCheckBoundingBoxXZ((u8 *)(off + (s32)D_807F6000 + 0x54), PLY(i)->unk4->unk7C, PLY(i)->unk4->unk84) != 0;
                                }
                                flag |= hit;
                            }
                            i++;
                        } while (i < gPlayerCount);
                        v1 = OLB_SL;
                    }
                }
                break;
            case 1:
                if (gPlayerSlots != 0) {
                    i = 0;
                    if (gPlayerCount > 0) {
                        do {
                            if (PLY(i)->unk0 != 0) {
                                flag |= collisionCheckBoundingBoxXZ((u8 *)(off + (s32)D_807F6000 + 0x54), PLY(i)->unk4->unk7C, PLY(i)->unk4->unk84);
                                if (i == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                            }
                            if (gPlayerSlots == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                            i++;
                        } while (i < gPlayerCount);
                        v1 = OLB_SL;
                    }
                }
                break;
            case 3:
            case 4:
                if (gPlayerSlots != 0) {
                    flag = activeActorBoxOverlapTest(v1->unk0, v1->unk4, v1->unk8, v1->unk7C->unk68, v1->unk7C->unk6A, v1->unk7C->unk6C, v1->unk7C->unk67 == 3 ? 0xEF : 1);
                    v1 = OLB_SL;
                }
                break;
        }
    }
    if (flag != 0) {
        collisionTransformNode(arg0, v1->unk24, v1->unk0, v1->unk4, v1->unk8, v1->unk10, v1->unk14, v1->unk18, v1->unkC);
        v1 = OLB_SL;
        modelSlotBuildTriangleBufferThunk(arg0, v1->unk24, v1->unk0, v1->unk4, v1->unk8, v1->unk10, v1->unk14, v1->unk18, v1->unkC);
        v1 = OLB_SL;
    }
    modelSlotBuildVertPosList(arg0, (ModelVertTable *)v1->unk24, v1->unk0, v1->unk4, v1->unk8, v1->unk10, v1->unk14, v1->unk18, v1->unkC, 1);
    v1 = OLB_SL;
    modelSlotBuildNodePosList(arg0, (ModelVertTable *)v1->unk24, v1->unk0, v1->unk4, v1->unk8, v1->unk10, v1->unk14, v1->unk18, v1->unkC, 1);
}

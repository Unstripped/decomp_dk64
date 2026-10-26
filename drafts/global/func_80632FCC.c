// func_80632FCC (src/global/36880.c): stage 4: frame 0x48 + dst@0x30 match with padA[5] (+off local); diffs: f32/s16 stack slots 4 low (target has 4B home gap between dst and sp28 and one word below sp26/24; pad arrays cost 8B so unreachable), regalloc type in v1 vs a0/pointer t3 vs v1. Learned: declared+surviving reg locals reserve 4B homes in declaration order; off local gives base+off addu order; ternary vs if/else for u8 narrowing.
s32 collisionCheckGroundAtPoint(f32, f32, f32 *);

typedef struct R36880bCoordDst {
    /* 0x00 */ u8 pad0[0x20];
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
} R36880bCoordDst;

typedef struct R36880bSlotObj {
    /* 0x00 */ u8 pad0[0x54];
    /* 0x54 */ R36880bCoordDst *unk54;
    /* 0x58 */ u8 pad58[0x64];
    /* 0xBC */ R36880bCoordDst *unkBC;
} R36880bSlotObj;

void collisionGetCoords(s16 *, s16 *);

void func_80632FCC(s16 arg0, u8 arg1) {
    s32 padA[5];
    R36880bCoordDst *dst;
    f32 sp28;
    s16 sp26;
    s16 sp24;
    s32 off;

    if (arg1 == 1) {
        arg0 = hashTableLookup(arg0);
    }
    off = arg0 * sizeof(ModelSlot);
    sp28 = ((ModelSlot *)((u8 *)D_807F6000 + off))->unk4 + 20.0f;
    if (collisionCheckGroundAtPoint(((ModelSlot *)((u8 *)D_807F6000 + off))->unk0, ((ModelSlot *)((u8 *)D_807F6000 + off))->unk8, &sp28) != 0) {
        collisionGetCoords(&sp26, &sp24);
        switch (((ModelSlot *)((u8 *)D_807F6000 + off))->unk24[0x1C]) {
            case 1:
                dst = ((R36880bSlotObj *)((ModelSlot *)((u8 *)D_807F6000 + off))->unk20)->unkBC;
                break;
            case 2:
                dst = ((R36880bSlotObj *)((ModelSlot *)((u8 *)D_807F6000 + off))->unk20)->unk54;
                break;
        }
        if (dst != NULL) {
            dst->unk20 = sp26;
            dst->unk22 = sp24;
        }
    }
}

// modelSlotResolveAssetTextures (src/global/36880.c): Model 2026-11-03 (leftovers7): stage 4 park, count-exact 121/121, frame 72, s0/s1 right, deadsweep full 41 (was 54), shape 7, ALL sp offsets equal the target. KEY: declaration order [seg,obj,seg2(volatile),flags,pad,sp30,node,res,sp24,sp20] puts every home at the target slot (seg2 0x3C, count 0x30, node 0x2C, res 0x28, sp24 0x24, sp20 0x20); the old order was 8 bytes off (54 -> 43). Then separate pointer-copy locals: pad (calls 1,3,4) instead of flags/seg->unkA0 (-> 41; flags no longer doubles as the pointer copy, now s32; call-1 'lw a0,160(s0)' direct as in target). Remaining 41: obj 'lw v0,36(a0)...move s1,v0' (target) vs 'lw s1' (no spelling: obj store via expression first, expression in condition, statement orders all tried; E=arg0->unk24 is killed by the obj->unk8 store in our build, target keeps it); flags a3 vs v0; ring numbering; commutative addu a1,a0,t1 vs t1,a0 in call 2; target sb t8,43(sp) vs sb v1. Non-volatile arg2 gives 'andi a3,a2,0xff; sb a3,83(sp)' (51): arg2 stays memory-resident in the target only if a3 is unavailable to it (flags would have to be a3), then the lbu t5,83(sp) hoist above beqzl also appears; volatile blocks that hoist. Tried: sibling-style head/mid/start/len/count locals (3 s-regs: node coloured s0; one extra block anywhere makes node uncoloured and frame 72), asset-copy var for the else arm, 100k-eval annealing of dead tests / ordering / operand-order toggles / pointer-copy variable choices.
s32 dlResolveNodeTextures(DisplayListCmd *, DisplayListCmd *, ModelSegmentNode *, u8);

s32 modelSlotResolveAssetTextures(arg0, arg1, arg2)
ModelSlot *arg0;
u8 arg1;
volatile u8 arg2; // FAKE: keeps arg2 memory-resident (target reloads it with lbu 0x53(sp) at every use)
{
    ModelSegmentData *seg;
    ModelSlotObjHeader *obj;
    ModelSegmentData *volatile seg2; // FAKE: keeps a memory copy of seg (target reloads it from 0x3C(sp) in the else branch)
    s32 flags;
    s32 pad;
    u32 sp30;
    ModelSegmentNode *node;
    u8 res;
    s32 sp24;
    s32 sp20;
    if (0) {
        &node; // FAKE: node must be stack resident
    }
    seg = ((ModelSlotSegOwner *)arg0)->unk20;
    obj = (ModelSlotObjHeader *)arg0->unk24;
    seg2 = seg;
    obj->unk8 = gFrameCounter;
    flags = arg0->unk8C;
    if (arg0->unk20 && arg0->unk20) {} // FAKE: dead test steers uopt colouring
    if (!(flags & 0x20)) {
        if (!(obj->unk0 & 0x10) || arg2 != 0) {
            arg0->unk8C = flags | 0x20;
            obj->unk3C += 1;
            if (obj->unk1C == 1) {
                node = (ModelSegmentNode *)((ModelSlotSegOwner *)arg0)->unk20->unkB8;
                sp24 = ((seg->unkA8 - seg->unkA0) >> 3) * 8;
                sp30 = (seg->unkB0 - seg->unkA8) >> 3;
                pad = seg->unkA0; // FAKE: reuses the pad word as the CSE'd pointer (steers uopt colouring)
                res = dlResolveNodeTextures((DisplayListCmd *)pad, (DisplayListCmd *)(pad + sp24), node, arg2);
                sp20 = sp30 * 8;
                if (res && res) {} // FAKE: dead test steers uopt colouring
                sp30 = seg->unkA8; // FAKE: reuses dead sp30 as the CSE'd pointer (steers uopt colouring)
                res |= dlResolveNodeTextures((DisplayListCmd *)sp30, (DisplayListCmd *)(sp30 + sp20), node, arg2);
                if (node != 0) {
                    pad = seg->unkA4; // FAKE: reuses the pad word as the CSE'd pointer (steers uopt colouring)
                    res |= dlResolveNodeTextures((DisplayListCmd *)pad, (DisplayListCmd *)(pad + sp24), node, arg2);
                    pad = seg->unkAC; // FAKE: reuses the pad word as the CSE'd pointer (steers uopt colouring)
                    res |= dlResolveNodeTextures((DisplayListCmd *)pad, (DisplayListCmd *)(pad + sp20), node, arg2);
                    if (seg->unkA0 == 0) {} // FAKE: dead test steers uopt colouring
                }
                if (res != 0) {
                    obj->unk0 &= ~0x10;
                }
            } else {
                if (((ModelType2Obj *)seg2)->unk50 != 0 || arg1 != 0) {
                    modelSlotLoadAssetTextures((u8 *)obj, (ModelSlotAsset *)seg2);
                } else {
                    modelSlotClearAssetTextures((s32)obj, (u8 *)seg2);
                }
            }
        }
    }
}

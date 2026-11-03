// modelSlotResolveAssetTextures (src/global/36880.c): W2Frame 2026-11-03 (revisit 7 wave 2): stage 4 park, count-exact 121, frame 72, s0/s1 right, deadsweep full 39 (was 41), shape 10. NEW vs stored: dropped 'volatile arg2' FAKE (K&R 'u8 arg2' plain) and the flags local (reads arg0->unk8C directly; compound |= 0x20), split obj in two webs: 'p = arg0->unk24; p->unk8 = gFrameCounter; obj = (T*)((u32)p | 0)' (declared in flags' home slot so homes stay at the target slots): reproduces the target's 'lw E; sw 8(E); move s1,E' piece split (count 120 -> 121). Remaining: p coloured v1/flags v0 (target E v0, flags a3), arg2 coloured a3 with 'andi a3,a2,0xff / sb a3,83(sp)' (target keeps arg2 memory-resident: lbu 0x53(sp) at every use, needs flags=a3 so a3 is not free for arg2: v0/v1/a2 would need ghost webs), then the t-ring is shifted by one after the first block. Tried: ANSI header (needs the decl at ~583 changed; same 39), K&R s32 arg2+(u8) casts, 128 x 3 x 2 grids of which obj-use sites read p vs obj, ghost locals (pad/sp20/sp24/sp30 = X; if (X) {}) at every position, dead-test anneal (15k evals, no gain), E=arg0->unk24 expression spellings (A/B/C store forms: E is killed by the sw in every spelling, target keeps it).
s32 dlResolveNodeTextures(DisplayListCmd *, DisplayListCmd *, ModelSegmentNode *, u8);

s32 modelSlotResolveAssetTextures(arg0, arg1, arg2)
ModelSlot *arg0;
u8 arg1;
u8 arg2;
{
    ModelSegmentData *seg;
    ModelSlotObjHeader *obj;
    ModelSegmentData *volatile seg2; // FAKE: keeps a memory copy of seg (target reloads it from 0x3C(sp) in the else branch)
    ModelSlotObjHeader *p; // FAKE-adjacent: pointer copy used for the first store/test (steers uopt pieces)
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
    p = (ModelSlotObjHeader *)arg0->unk24;
    seg2 = seg;
    p->unk8 = gFrameCounter;
    obj = (ModelSlotObjHeader *)((u32)p | 0); // FAKE: blocks copy propagation
    if (arg0->unk20 && arg0->unk20) {} // FAKE: dead test steers uopt colouring
    if (!(arg0->unk8C & 0x20)) {
        if (!(obj->unk0 & 0x10) || arg2 != 0) {
            arg0->unk8C |= 0x20;
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

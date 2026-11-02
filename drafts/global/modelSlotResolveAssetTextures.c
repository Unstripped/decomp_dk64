// modelSlotResolveAssetTextures (src/global/36880.c): Model 2026-11-02 (rev6): stage 3, 63 diff lines (unchanged), 124 vs 121 insns, frame 72 and s0/s1 exact with the volatile arg2 + volatile seg2 + '&node' FAKE draft. Tried: natural K&R/ANSI no-volatile bodies (node/tail coloured s2/s3, frame 80-96), obj/flags as expression vs local, seg/asset/obj decl-order + unused pad locals (homes go top-down from 0x44; target homes seg=3rd 0x3C, sp30=6th, node 7th, res 8th, sp24 9th, sp20 10th => two extra declared locals between seg and sp30; pads did not reproduce), mid/start/len/count block (modelSlotsStepSegmentCommands spelling) vs direct, 3^4 grid of per-call-site local cmd/u32 spellings, random structure search 10k evals, annealed dead tests (best 63 same as before), deadsweep sweeps. Remaining diff: target obj lives v0 early then 'move s1,v0' and flags in a3 (ours lbu v0 + move v1,v0); unkA0/unkA4/unkAC loaded straight into a0 (ours v0/t0 + move a0) = the 3 extra insns; sp24 stored at home 0x24 (ours spill 0x2C).
s32 dlResolveNodeTextures(DisplayListCmd *, DisplayListCmd *, ModelSegmentNode *, u8);

s32 modelSlotResolveAssetTextures(arg0, arg1, arg2)
ModelSlot *arg0;
u8 arg1;
volatile u8 arg2;
{
    ModelSegmentData *seg;
    ModelSlotObjHeader *obj;
    ModelSegmentData *volatile seg2; // FAKE: keeps a memory copy of seg (target reloads it from 0x3C(sp) in the else branch)
    u32 sp30;
    ModelSegmentNode *node;
    u8 flags;
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
    if (!(flags & 0x20)) {
        if (!(obj->unk0 & 0x10) || arg2 != 0) {
            arg0->unk8C = flags | 0x20;
            obj->unk3C += 1;
            if (obj->unk1C == 1) {
                node = (ModelSegmentNode *)((ModelSlotSegOwner *)arg0)->unk20->unkB8;
                sp24 = ((seg->unkA8 - seg->unkA0) >> 3) * 8;
                sp30 = (seg->unkB0 - seg->unkA8) >> 3;
                res = dlResolveNodeTextures((DisplayListCmd *)seg->unkA0, (DisplayListCmd *)(seg->unkA0 + sp24), node, arg2);
                sp20 = sp30 * 8;
                res |= dlResolveNodeTextures((DisplayListCmd *)seg->unkA8, (DisplayListCmd *)(seg->unkA8 + sp20), node, arg2);
                if (node != 0) {
                    res |= dlResolveNodeTextures((DisplayListCmd *)seg->unkA4, (DisplayListCmd *)(seg->unkA4 + sp24), node, arg2);
                    res |= dlResolveNodeTextures((DisplayListCmd *)seg->unkAC, (DisplayListCmd *)(seg->unkAC + sp20), node, arg2);
                    res = res | 0;  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
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

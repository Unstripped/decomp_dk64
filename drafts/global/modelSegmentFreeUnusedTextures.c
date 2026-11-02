// modelSegmentFreeUnusedTextures (src/global/36880.c): stage 4, 33 diff lines (was 87; parked in copy). direct seg->unkA0/A8 reads (no mid/start locals), flag form 's3==NULL&&bit ? 0:1', hill-climb no-code defs head|0 tail*1 flag*1 gave head/tail coloured v1/t0 with save-around-calls. Remaining: flag u8 coloured t1 (saved 51(sp)) vs target uncoloured memory flag (sb zero,51(sp); lbu at use) shifting spill slots by 4; head/tail slots 60/56 vs 56/52
void modelSegmentFreeUnusedTextures(ModelSlot *arg0, void *arg1, ModelChainOwner *arg2) {
    u32 head, tail;
    DisplayListTextureNode *s3;
    u8 flag;
    ModelSegmentData *seg;

    seg = (ModelSegmentData *)arg2;
    s3 = seg->unkB8;
    head = (seg->unkA8 - seg->unkA0) >> 3;
    tail = (seg->unkB0 - seg->unkA8) >> 3;
    if (s3 == NULL && (arg0->unk8C & 0x20)) {
        flag = 0;
    } else {
        flag = 1;
        tail = tail * 1;  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    }
    flag = flag * 1;  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    head = head | 0;  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    if (arg0->unk8C & 0x20) {
        if (flag != 0) {
            ((DisplayListFreeCounter *)arg1)->unk3C -= 1;
            dlFreeUnusedTextures(seg->unkA0, seg->unkA0 + head * 8, (s32)seg->unkB8, 0, 0);
            dlFreeUnusedTextures(seg->unkA8, seg->unkA8 + tail * 8, (s32)seg->unkB8, 1, 0);
            s3 = seg->unkB8;
        } else {
            displayListFreeQueueAdd(seg->unkA0, seg->unkA0 + head * 8, seg->unkA8, seg->unkA8 + tail * 8, (s32)arg1);
            s3 = seg->unkB8;
        }
    }
    if (s3 != NULL) {
        dlFreeUnusedTextures(seg->unkA4, seg->unkA4 + head * 8, (s32)s3, 0, 0);
        dlFreeUnusedTextures(seg->unkAC, seg->unkAC + tail * 8, (s32)seg->unkB8, 1, 0);
        heapFreeDeferred((void *)seg->unkA4);
        heapFreeDeferred((void *)seg->unkAC);
    }
    if (flag != 0) {
        assetFreeBuffer(arg1, 0xAF7, 7);
    }
    heapFreeDeferred(arg2);
}

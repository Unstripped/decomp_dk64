// modelSegmentFreeUnusedTextures (src/global/36880.c): stage 4, frame 0x40 matches target (via narrow u8 head, tail packing with volatile u8 flag), saved s0=seg, s1=mid; remaining diff is s2/s3 callee-saved allocation vs spilling start to 0x38(sp) and dead-statement placement
void modelSegmentFreeUnusedTextures(ModelSlot *arg0, void *arg1, ModelChainOwner *arg2) {
    u32 mid, start;
    DisplayListTextureNode *s3;
    u8 head, tail;
    volatile u8 flag;
    ModelSegmentData *seg;

    seg = (ModelSegmentData *)arg2;
    mid = seg->unkA8;
    start = seg->unkA0;
    if (mid == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    s3 = seg->unkB8;
    head = (mid - start) >> 3;
    if (head && head) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    tail = (seg->unkB0 - mid) >> 3;
    if (s3 != NULL || !(arg0->unk8C & 0x20)) {
        flag = 1;
    } else {
        flag = 0;
    }
    if (arg0->unk8C & 0x20) {
        if (flag != 0) {
            ((DisplayListFreeCounter *)arg1)->unk3C -= 1;
            dlFreeUnusedTextures(start, start + head * 8, (s32)seg->unkB8, 0, 0);
            if (tail && tail) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            dlFreeUnusedTextures(mid, mid + tail * 8, (s32)seg->unkB8, 1, 0);
            s3 = seg->unkB8;
        } else {
            displayListFreeQueueAdd(start, start + head * 8, mid, mid + tail * 8, (s32)arg1);
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

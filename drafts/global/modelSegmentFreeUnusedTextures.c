// modelSegmentFreeUnusedTextures (src/global/36880.c): stage 4-: saved set s0-s3 now matches (needs node reassigned in BOTH arms, start/mid reassigned in the flag arm as start=seg->unkA0/mid=seg->unkA8, volatile u8 flag), frame 0x50 vs 0x40; callee-saved order wrong (mid s0,start s1,seg s2 vs target seg s0,mid s1,start s2: reassigning start/mid raises their adjsave above seg's) and head/tail stay stack-resident (-ve save) vs target v1/t0 spilled around calls
void modelSegmentFreeUnusedTextures(ModelSlot *arg0, void *arg1, ModelChainOwner *arg2) {
    ModelSegmentData *seg;
    u32 mid;
    u32 start;
    DisplayListTextureNode *s3;
    u32 head;
    u32 tail;
    u8 flag;

    seg = (ModelSegmentData *)arg2;
    mid = seg->unkA8;
    start = seg->unkA0;
    s3 = seg->unkB8;
    head = (mid - start) >> 3;
    tail = (seg->unkB0 - mid) >> 3;
    if (s3 != NULL || !(arg0->unk8C & 0x20)) {
        flag = 1;
    } else {
        flag = 0;
    }
    if (arg0->unk8C & 0x20) {
        if (flag != 0) {
            ((DisplayListFreeCounter *)arg1)->unk3C -= 1;
            start = seg->unkA0;
            dlFreeUnusedTextures(start, start + head * 8, (s32)seg->unkB8, 0, 0);
            mid = seg->unkA8;
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

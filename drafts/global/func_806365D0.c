// func_806365D0 (src/global/36880.c): stage 3: frame 0x40 matches target; callee-saved s0-s2 vs target s0-s3; identified start/mid locals for unkA0/unkA8 matching call args and De Morgan branch structure 'if (s3 != NULL || !(arg0->unk8C & 0x20))' matching target bnez/beqz
typedef struct DisplayListCmd {
    /* 0x0 */ u32 unk0;
    /* 0x4 */ s32 unk4;
} DisplayListCmd;

typedef struct DisplayListTextureNode {
    /* 0x00 */ void *unk0;
    /* 0x04 */ void *unk4;
    /* 0x08 */ u8 pad8[4];
    /* 0x0C */ void *unkC;
    /* 0x10 */ void *unk10;
    /* 0x14 */ u8 pad14[4];
    /* 0x18 */ void *unk18;
    /* 0x1C */ void *unk1C;
    /* 0x20 */ u8 pad20[4];
    /* 0x24 */ void *unk24;
    /* 0x28 */ void *unk28;
    /* 0x2C */ u8 pad2C[0xA8];
    /* 0xD4 */ struct DisplayListTextureNode *unkD4;
} DisplayListTextureNode;

typedef struct ModelSegmentData {
    /* 0x00 */ u8 pad0[0xA0];
    /* 0xA0 */ u32 unkA0;
    /* 0xA4 */ u32 unkA4;
    /* 0xA8 */ u32 unkA8;
    /* 0xAC */ u32 unkAC;
    /* 0xB0 */ u32 unkB0;
    /* 0xB4 */ s16 unkB4;
    /* 0xB6 */ s16 unkB6;
    /* 0xB8 */ DisplayListTextureNode *unkB8;
    /* 0xBC */ s32 unkBC;
    /* 0xC0 */ u8 padC0[3];
    /* 0xC3 */ u8 unkC3;
} ModelSegmentData;

void dlFreeUnusedTextures(s32, s32, s32, s32, s32);
void heapFreeDeferred(void *);
void displayListFreeQueueAdd(s32, s32, s32, s32, s32);

typedef struct ModelChainOwner ModelChainOwner;
typedef struct DisplayListFreeCounter {
    /* 0x00 */ u8 pad0[0x3C];
    /* 0x3C */ s16 unk3C;
} DisplayListFreeCounter;

void func_806365D0(ModelSlot *arg0, void *arg1, ModelChainOwner *arg2) {
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
            dlFreeUnusedTextures(start, start + head * 8, (s32)seg->unkB8, 0, 0);
            dlFreeUnusedTextures(mid, mid + tail * 8, (s32)seg->unkB8, 1, 0);
        } else {
            displayListFreeQueueAdd(start, start + head * 8, mid, mid + tail * 8, (s32)arg1);
        }
        s3 = seg->unkB8;
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

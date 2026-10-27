// func_80636AE8 (src/global/36880.c): stage 6: matches except regs (A8 temp in v0 vs target v1, B0 t8 vs t7, 2nd-call a0 pattern); 4-arg K&R call to renderReplaceSegment6Commands kept, locals head,seg,mid,count in this order give the 0x28 frame and slots.
typedef struct R36880eLink {
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
    /* 0xD4 */ struct R36880eLink *unkD4;
} R36880eLink;

typedef struct R36880eSeg {
    /* 0x00 */ u8 pad0[0xA0];
    /* 0xA0 */ u32 unkA0;
    /* 0xA4 */ u32 unkA4;
    /* 0xA8 */ u32 unkA8;
    /* 0xAC */ u32 unkAC;
    /* 0xB0 */ u32 unkB0;
    /* 0xB4 */ s16 unkB4;
    /* 0xB6 */ s16 unkB6;
    /* 0xB8 */ R36880eLink *unkB8;
    /* 0xBC */ s32 unkBC;
    /* 0xC0 */ u8 padC0[3];
    /* 0xC3 */ u8 unkC3;
} R36880eSeg;

typedef struct R36880eSegOwner {
    /* 0x00 */ u8 pad0[0x20];
    /* 0x20 */ R36880eSeg *unk20;
} R36880eSegOwner;

void renderReplaceSegment6Commands();

void func_80636AE8(void *arg0) {
    u32 head;
    R36880eSeg *seg;
    u32 mid;
    u32 count;

    seg = ((R36880eSegOwner *)arg0)->unk20;
    mid = seg->unkA8;
    head = (mid - seg->unkA0) >> 3;
    count = (seg->unkB0 - mid) >> 3;
    renderReplaceSegment6Commands(seg->unkA0, seg->unkA0 + head * 8, seg, seg->unkB0 - mid);
    renderReplaceSegment6Commands(seg->unkA8, seg->unkA8 + count * 8, seg, count);
}

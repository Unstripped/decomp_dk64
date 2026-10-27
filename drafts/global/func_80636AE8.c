// func_80636AE8 (src/global/36880.c): stage 6 (NM36A): all insns/regs identical except scratch temps: target B0=t7, head srl=t8 (count srl t9); mine B0=t8, head srl=t7. 'head = seg->unkA0; head = (mid - head) >> 3;' raises head priority (fixes mid=v1/sub=v0). Statement order [count,head] gives B0=t7,count srl=t8,head srl=t9. Needs B0 load emitted before head srl but count srl last: count multi-def (count=B0-mid; count>>=3) gives that order but count gets s0; len temp var gets sunk/spilled (frame +8). Permuter 900s no improvement.
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
    head = seg->unkA0;
    head = (mid - head) >> 3;
    count = (seg->unkB0 - mid) >> 3;
    renderReplaceSegment6Commands(seg->unkA0, seg->unkA0 + head * 8, seg, seg->unkB0 - mid);
    renderReplaceSegment6Commands(seg->unkA8, seg->unkA8 + count * 8, seg, count);
}

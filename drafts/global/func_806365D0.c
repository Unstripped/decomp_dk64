// func_806365D0 (src/global/36880.c): stage 3: frame 0x58 vs 0x40; target keeps A8/A0/B8 in s1/s2/s3 and head/tail in v1/t0 with stack spill only around calls (sb 0x33 flag); mine spills more and loses s3. C is behaviourally the m2c structure.
typedef struct R36880eCmd {
    /* 0x0 */ u32 unk0;
    /* 0x4 */ s32 unk4;
} R36880eCmd;

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

void func_80636784(R36880eCmd *, R36880eCmd *, R36880eLink *, u8, u8);
void heapFreeDeferred(void *);
void func_80636448(s32, s32, s32, s32, s32);

typedef struct R36880eObjB {
    /* 0x00 */ u8 pad0[0x3C];
    /* 0x3C */ s16 unk3C;
} R36880eObjB;

void func_806365D0(ModelSlot *arg0, R36880eObjB *arg1, R36880eSeg *arg2) {
    u32 sp38;
    u32 sp34;
    u8 sp33;
    u32 head;
    u32 tail;
    u32 s1;
    u32 s2;
    R36880eLink *s3;

    s1 = arg2->unkA8;
    s2 = arg2->unkA0;
    s3 = arg2->unkB8;
    head = (s1 - s2) >> 3;
    tail = (arg2->unkB0 - s1) >> 3;
    if (s3 == NULL && (arg0->unk8C & 0x20)) {
        sp33 = 0;
    } else {
        sp33 = 1;
    }
    if (arg0->unk8C & 0x20) {
        if (sp33 != 0) {
            arg1->unk3C -= 1;
            func_80636784((R36880eCmd *)arg2->unkA0, (R36880eCmd *)(arg2->unkA0 + head * 8), arg2->unkB8, 0, 0);
            func_80636784((R36880eCmd *)arg2->unkA8, (R36880eCmd *)(arg2->unkA8 + tail * 8), arg2->unkB8, 1, 0);
        } else {
            func_80636448(s2, s2 + head * 8, s1, s1 + tail * 8, (s32)arg1);
        }
        s3 = arg2->unkB8;
    }
    if (s3 != NULL) {
        func_80636784((R36880eCmd *)arg2->unkA4, (R36880eCmd *)(arg2->unkA4 + head * 8), s3, 0, 0);
        func_80636784((R36880eCmd *)arg2->unkAC, (R36880eCmd *)(arg2->unkAC + tail * 8), arg2->unkB8, 1, 0);
        heapFreeDeferred((void *)arg2->unkA4);
        heapFreeDeferred((void *)arg2->unkAC);
    }
    if (sp33 != 0) {
        assetFreeBuffer(arg1, 0xAF7, 7);
    }
    heapFreeDeferred(arg2);
}

// func_806365D0 (src/global/36880.c): stage 3+ (NM36A2): frame 0x40 and local homes now match (4 locals in order s3(R36880eLink*), head, tail, flag(u8): homes 0x3C/0x38/0x34/0x30 as target; arg2 typed R36880dOwner* per file prototype with SEG macro cast; func_80636784 is the file's (s32 x5) proto). Remaining: callee-saved set (target s0-s3: s1=A8,s2=A0,s3=B8 temps, s0=arg2; mine only s0) and head/tail should be colored v1/t0 with split spills around calls (mine stores them straight to homes). Using s3 var in all call args colors it (s1) but A8/A0 temps stay in v0/v1. Variant with explicit s1/s2/s3 vars gives s0-s2 but frame 0x48 (6 homes).
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

void func_80636784(s32, s32, s32, s32, s32);
void heapFreeDeferred(void *);
void func_80636448(s32, s32, s32, s32, s32);

typedef struct R36880dOwner R36880dOwner;
typedef struct R36880dCount {
    /* 0x00 */ u8 pad0[0x3C];
    /* 0x3C */ s16 unk3C;
} R36880dCount;

#define SEG ((R36880eSeg *)arg2)
void func_806365D0(ModelSlot *arg0, void *arg1, R36880dOwner *arg2) {
    R36880eLink *s3;
    u32 head;
    u32 tail;
    u8 flag;

    s3 = SEG->unkB8;
    head = (SEG->unkA8 - SEG->unkA0) >> 3;
    tail = (SEG->unkB0 - SEG->unkA8) >> 3;
    if (s3 == NULL && (arg0->unk8C & 0x20)) {
        flag = 0;
    } else {
        flag = 1;
    }
    if (arg0->unk8C & 0x20) {
        if (flag != 0) {
            ((R36880dCount *)arg1)->unk3C -= 1;
            func_80636784(SEG->unkA0, SEG->unkA0 + head * 8, (s32)SEG->unkB8, 0, 0);
            func_80636784(SEG->unkA8, SEG->unkA8 + tail * 8, (s32)SEG->unkB8, 1, 0);
        } else {
            func_80636448(SEG->unkA0, SEG->unkA0 + head * 8, SEG->unkA8, SEG->unkA8 + tail * 8, (s32)arg1);
        }
        s3 = SEG->unkB8;
    }
    if (s3 != NULL) {
        func_80636784(SEG->unkA4, SEG->unkA4 + head * 8, (s32)s3, 0, 0);
        func_80636784(SEG->unkAC, SEG->unkAC + tail * 8, (s32)SEG->unkB8, 1, 0);
        heapFreeDeferred((void *)SEG->unkA4);
        heapFreeDeferred((void *)SEG->unkAC);
    }
    if (flag != 0) {
        assetFreeBuffer(arg1, 0xAF7, 7);
    }
    heapFreeDeferred(arg2);
}
#undef SEG

// func_8063B8D8 (src/global/36880.c): stage 5 (parked NON_MATCHING in src copy): 1 hunk / 2 insns left: target 'sll s7,t6,4; addiu s7,s7,8' (size var in place) vs mine 'sll t6,t6,4; addiu s7,t6,8'. Fixed by: if (!D_807F66F0) {} before *arg1 store (kills &D_807F66F0 CSE into s5), p++ as separate statement in loop1 (if (*p) {} ... p++), (u8 *)D_807F6000[hashTableLookup(..)].unk7C + 0x14 index form in loop2, and joining 'size=..; p=..; do{..}while; size+=call' onto ONE source line (scheduling of addiu s1). Tried: size split/u32/order variants, 3*16 forms, permuter 540s+240s (best 10 = same-line joins).
typedef struct R36880fOut {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ u8 pad10[8];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ s16 unk2A;
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ u8 unk2E;
    /* 0x2F */ u8 unk2F;
} R36880fOut; /* 0x30 */

typedef struct R36880fSlot {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ u8 *unk20;
    /* 0x24 */ u8 pad24[0x58];
    /* 0x7C */ u8 *unk7C;
    /* 0x80 */ u8 pad80[4];
    /* 0x84 */ s16 unk84;
    /* 0x86 */ s16 unk86;
    /* 0x88 */ s16 pad88;
    /* 0x8A */ s16 unk8A;
    /* 0x8C */ u8 pad8C[4];
} R36880fSlot; /* 0x90 */

extern u8 *D_807F6010;
extern u8 D_807F66F0[];
extern u8 D_807F6902;
s32 actorListGetSerializedSize(void);
void actorListSerialize(void *);

#define R36880F_SLOT ((R36880fSlot *)((u8 *)D_807F6000 + i * 0x90))

void func_8063B8D8(u8 **arg0, s32 *arg1) {
    s32 count;
    s32 size;
    u8 *p;
    s32 i;
    R36880fOut *out;
    u8 *dst;

    count = 0;
    if (D_807F6010 != NULL) {
        heapFree(D_807F6010);
    }
    size = D_80747D70 * 0x30 + 8; p = D_807F66F0; do { if (*p) { size += 0x24; count++; } p++; } while (p < &D_807F6902); size += actorListGetSerializedSize();
    D_807F6010 = func_80610FE8(size);
    *(s32 *)D_807F6010 = D_80747D70;
    out = (R36880fOut *)(D_807F6010 + 4);
    for (i = 0; i < D_80747D70; i++, out++) {
        out->unk0 = R36880F_SLOT->unk0;
        out->unk4 = R36880F_SLOT->unk4;
        out->unk8 = R36880F_SLOT->unk8;
        out->unkC = R36880F_SLOT->unkC;
        out->unk18 = R36880F_SLOT->unk10;
        out->unk1C = R36880F_SLOT->unk14;
        out->unk20 = R36880F_SLOT->unk18;
        out->unk28 = R36880F_SLOT->unk84;
        out->unk2C = R36880F_SLOT->unk86;
        out->unk24 = R36880F_SLOT->unk1C;
        out->unk2A = R36880F_SLOT->unk8A;
        switch (out->unk2C) {
        case 2:
            out->unk2F = R36880F_SLOT->unk20[0x4E];
            out->unk2E = R36880F_SLOT->unk20[0x5B];
            break;
        case 1:
            out->unk2F = 0;
            out->unk2E = R36880F_SLOT->unk20[0xC3];
            break;
        }
    }
    *(s32 *)out = count;
    dst = (u8 *)out + 4;
    for (i = 0, p = D_807F66F0; i != 0x212; i++, p++) {
        if (*p != 0) {
            *(s32 *)dst = i;
            memcpy(dst + 4, (u8 *)D_807F6000[hashTableLookup(D_807F6240[i])].unk7C + 0x14, 0x20);
            dst += 0x24;
        }
    }
    actorListSerialize(dst);
    *arg0 = D_807F6010;
    if (!D_807F66F0) {
    }
    *arg1 = size;
}

#undef R36880F_SLOT

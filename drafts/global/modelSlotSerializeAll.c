// modelSlotSerializeAll (src/global/36880.c): Stage 5, 2 insns: target 'sll s7,t6,4; addiu s7,s7,8' (product assigned in place to size's reg, +8 as separate op) vs ours 'sll t6,t6,4; addiu s7,t6,8'. uopt folds size=D*0x30; size+=8 into one tree in every form: inline, sep stmts, size=D then size*=0x30, 8-first, (0,x) wrappers on D/0x30/8/product, u32/u8*/s64 size, sz2 temp (10), x*3 then *16 (142), deadsweep with all locals (no gain). Needs a statement boundary uopt cannot fold across.
typedef struct ModelSlotSerializedOut {
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
} ModelSlotSerializedOut; /* 0x30 */

typedef struct ModelSlotSerializeView {
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
} ModelSlotSerializeView; /* 0x90 */

extern u8 *D_807F6010;
extern u8 D_807F66F0[];
extern u8 D_807F6902;
s32 actorListGetSerializedSize(void);
void actorListSerialize(void *);

#define MODEL_SLOT_SERIALIZE_ENTRY ((ModelSlotSerializeView *)((u8 *)D_807F6000 + i * 0x90))

void modelSlotSerializeAll(u8 **arg0, s32 *arg1) {
    s32 count;
    s32 size;
    u8 *p;
    s32 i;
    ModelSlotSerializedOut *out;
    u8 *dst;

    count = 0;
    if (D_807F6010 != NULL) {
        heapFree(D_807F6010);
    }
    size = D_80747D70 * 0x30 + 8; p = D_807F66F0; do { if (*p) { size += 0x24; count++; } p++; } while (p < &D_807F6902); size += actorListGetSerializedSize();
    D_807F6010 = heapAlloc(size);
    *(s32 *)D_807F6010 = D_80747D70;
    out = (ModelSlotSerializedOut *)(D_807F6010 + 4);
    for (i = 0; i < D_80747D70; i++, out++) {
        out->unk0 = MODEL_SLOT_SERIALIZE_ENTRY->unk0;
        out->unk4 = MODEL_SLOT_SERIALIZE_ENTRY->unk4;
        out->unk8 = MODEL_SLOT_SERIALIZE_ENTRY->unk8;
        out->unkC = MODEL_SLOT_SERIALIZE_ENTRY->unkC;
        out->unk18 = MODEL_SLOT_SERIALIZE_ENTRY->unk10;
        out->unk1C = MODEL_SLOT_SERIALIZE_ENTRY->unk14;
        out->unk20 = MODEL_SLOT_SERIALIZE_ENTRY->unk18;
        out->unk28 = MODEL_SLOT_SERIALIZE_ENTRY->unk84;
        out->unk2C = MODEL_SLOT_SERIALIZE_ENTRY->unk86;
        out->unk24 = MODEL_SLOT_SERIALIZE_ENTRY->unk1C;
        out->unk2A = MODEL_SLOT_SERIALIZE_ENTRY->unk8A;
        switch (out->unk2C) {
        case 2:
            out->unk2F = MODEL_SLOT_SERIALIZE_ENTRY->unk20[0x4E];
            out->unk2E = MODEL_SLOT_SERIALIZE_ENTRY->unk20[0x5B];
            break;
        case 1:
            out->unk2F = 0;
            out->unk2E = MODEL_SLOT_SERIALIZE_ENTRY->unk20[0xC3];
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

#undef MODEL_SLOT_SERIALIZE_ENTRY

// func_8065FEB8 (src/global/63EC0.c): regalloc diff in scissor word loading
typedef struct R1C_SubStruct {
    u8 pad[0x50];
    s16 unk50;
    u8 pad2[0x67 - 0x52];
    u8 unk67;
} R1C_SubStruct;

typedef struct R1C_Water {
    R1C_SubStruct *unk0;
    u8 pad[0x40 - 4];
    s16 unk40;
    s16 unk42;
    s16 unk44;
    s16 unk46;
} R1C_Water;

typedef struct R1C_Struct1C8 {
    u8 pad[0x68];
    s32 unk68;
    s32 unk6C;
    s32 unk70;
    s32 unk74;
} R1C_Struct1C8;

extern s32 D_807F6C18;

Gfx *func_8065FEB8(Gfx *gdl, R1C_Water *water) {
    s32 w0, w1;
    s32 index;
    s32 offset;
    R1C_Struct1C8 *entry;
    Gfx *out;

    gDPPipeSync(gdl++);
    if (water->unk0->unk67 == 1) {
        index = water->unk0->unk50;
        offset = (((((index << 3) - index) << 3) + index) << 3);
        entry = (R1C_Struct1C8 *)(D_807F6C18 + offset);
        out = gdl++;
        w0 = ((s32)(entry->unk6C * 4.0f) & 0xFFF) | 0xED000000;
        w0 |= ((s32)(entry->unk68 * 4.0f) & 0xFFF) << 12;
        out->words.w0 = w0;
        entry = (R1C_Struct1C8 *)(D_807F6C18 + offset);
        w1 = (s32)(entry->unk74 * 4.0f) & 0xFFF;
        w1 |= ((s32)(entry->unk70 * 4.0f) & 0xFFF) << 12;
        out->words.w1 = w1;
        return gdl;
    }
    out = gdl++;
    out->words.w0 = ((((s32)(water->unk40 * 4.0f) & 0xFFF) << 12) | 0xED000000) | ((s32)(water->unk42 * 4.0f) & 0xFFF);
    out->words.w1 = (((s32)(water->unk44 * 4.0f) & 0xFFF) << 12) | ((s32)(water->unk46 * 4.0f) & 0xFFF);
    return gdl;
}

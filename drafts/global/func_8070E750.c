// func_8070E750 (src/global/112080.c): stage 4: direct table traversal has exact 0x30 frame; stack-home layout and scratch-register allocation differ
extern void *func_80610FE8(s32);
extern void *func_8070DDDC(s32, s32);
extern u8 D_807550C8;

typedef struct R112cTextValue {
    char *text;
    u16 length;
} R112cTextValue;

typedef struct R112cTextChoice {
    void *unk0;
    R112cTextValue *value;
} R112cTextChoice;

typedef struct R112cTextResource {
    u8 pad0[8];
    R112cTextChoice *choices;
} R112cTextResource;

typedef struct R112cTextEntry {
    void *unk0;
    R112cTextResource *resource;
} R112cTextEntry;

typedef struct R112cTextTable {
    void *unk0;
    R112cTextEntry *entries;
    u8 pad8[4];
    s32 offset;
} R112cTextTable;

s32 func_8070E750(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp20;
    s32 sp1C;
    s32 sp18;
    R112cTextTable *temp_v0;
    u16 temp_a3;

    temp_v0 = func_8070DDDC(arg0 & 0xFFFF, 1);
    sp20 = (s32) (temp_v0->entries[arg1].resource->choices + D_807550C8)->value->text + temp_v0->offset;
    temp_a3 = (temp_v0->entries[arg1].resource->choices + D_807550C8)->value->length;
    sp1C = temp_a3;
    sp18 = (s32) func_80610FE8(sp1C + 1);
    if (arg2 & 1) {
        heapFreeDeferred(sp18);
    }
    memcpy(sp18, sp20, sp1C);
    *(u8 *) (sp18 + sp1C) = 0;
    return sp18;
}

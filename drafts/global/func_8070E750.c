// func_8070E750 (src/global/112080.c): stage 3: compatible s32 three-argument result prototype; correct allocator/copy flow, but typed accesses add 0x18 frame bytes
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
    s32 temp_v0_2;
    s32 var_a0;
    u16 temp_a3;
    R112cTextResource *temp_a1;
    R112cTextChoice *temp_a2;
    R112cTextTable *temp_v0;
    R112cTextValue *temp_v1;

    temp_v0 = func_8070DDDC(arg0 & 0xFFFF, 1);
    temp_a1 = temp_v0->entries[arg1].resource;
    temp_a2 = temp_a1->choices + D_807550C8;
    temp_v1 = temp_a2->value;
    sp20 = (s32) temp_v1->text + temp_v0->offset;
    temp_a3 = temp_v1->length;
    sp1C = temp_a3;
    temp_v0_2 = (s32) func_80610FE8(temp_a3 + 1);
    var_a0 = temp_v0_2;
    if (arg2 & 1) {
        sp18 = temp_v0_2;
        heapFreeDeferred(var_a0);
        var_a0 = sp18;
    }
    sp18 = var_a0;
    memcpy(var_a0, sp20, sp1C);
    *(u8 *) (sp18 + sp1C) = 0;
    return sp18;
}

// func_8070E750 (src/global/112080.c): Stage 4 exact flow/frame candidate; source, length, and destination stack homes remain 0x24/0x18/0x2C instead of target 0x20/0x1C/0x18. Permuter search running.
typedef struct P112bTextValue {
    char *text;
    u16 length;
} P112bTextValue;

typedef struct P112bTextChoice {
    void *unk0;
    P112bTextValue *value;
} P112bTextChoice;

typedef struct P112bTextResource {
    u8 pad0[8];
    P112bTextChoice *choices;
} P112bTextResource;

typedef struct P112bTextEntry {
    void *unk0;
    P112bTextResource *resource;
} P112bTextEntry;

typedef struct P112bTextTable {
    void *unk0;
    P112bTextEntry *entries;
    u8 pad8[4];
    s32 offset;
} P112bTextTable;

extern void *func_80610FE8(s32);
extern void *func_8070DDDC(s32, s32);
extern u8 D_807550C8;
extern void heapFreeDeferred(void *);

s32 func_8070E750(s32 arg0, s32 arg1, s32 arg2) {
    s32 destination;
    s32 length;
    s32 source;
    P112bTextTable *table;
    u16 textLength;

    table = func_8070DDDC(arg0 & 0xFFFF, 1);
    source = (s32)(table->entries[arg1].resource->choices + D_807550C8)->value->text + table->offset;
    textLength = (table->entries[arg1].resource->choices + D_807550C8)->value->length;
    length = textLength;
    destination = (s32)func_80610FE8(length + 1);
    if (arg2 & 1) {
        heapFreeDeferred(destination);
    }
    memcpy(destination, source, length);
    *(u8 *)(destination + length) = 0;
    return destination;
}

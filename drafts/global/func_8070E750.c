// func_8070E750 (src/global/112080.c): Stage 4: exact frame and flow; local order and pointer/int forms leave source/length/destination homes at 0x24/0x18/0x2C instead of target 0x20/0x1C/0x18.
extern void *func_80610FE8(s32);
extern void *func_8070DDDC(s32, s32);
extern u8 D_807550C8;
extern void heapFreeDeferred(void *);

typedef struct N112TextValue {
    char *text;
    u16 length;
} N112TextValue;

typedef struct N112TextChoice {
    void *unk0;
    N112TextValue *value;
} N112TextChoice;

typedef struct N112TextResource {
    u8 pad0[8];
    N112TextChoice *choices;
} N112TextResource;

typedef struct N112TextEntry {
    void *unk0;
    N112TextResource *resource;
} N112TextEntry;

typedef struct N112TextTable {
    void *unk0;
    N112TextEntry *entries;
    u8 pad8[4];
    s32 offset;
} N112TextTable;

s32 func_8070E750(s32 arg0, s32 arg1, s32 arg2) {
    s32 destination;
    s32 length;
    s32 source;
    N112TextTable *table;
    u16 text_length;

    table = func_8070DDDC(arg0 & 0xFFFF, 1);
    source = (s32)(table->entries[arg1].resource->choices + D_807550C8)->value->text + table->offset;
    text_length = (table->entries[arg1].resource->choices + D_807550C8)->value->length;
    length = text_length;
    destination = (s32)func_80610FE8(length + 1);
    if (arg2 & 1) {
        heapFreeDeferred(destination);
    }
    memcpy(destination, source, length);
    *(u8 *)(destination + length) = 0;
    return destination;
}

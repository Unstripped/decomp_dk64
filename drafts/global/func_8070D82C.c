// func_8070D82C (src/global/112080.c): matched in isolation: tail-entry append with K&R-sized parameter homes
typedef struct S112dEntry {
    u16 id;
    u8 count;
    u8 pad3;
    struct S112dEntry *next;
} S112dEntry;

typedef struct S112dContainer {
    u8 pad0[4];
    Actor *actor;
    S112dEntry *entries;
} S112dContainer;

void func_8070D82C(S112dContainer *arg0, u16 arg1, u8 arg2) {
    S112dEntry **entry;

    entry = &arg0->entries;
    while (*entry != NULL) {
        entry = &(*entry)->next;
    }
    *entry = func_80610FE8(8);
    (*entry)->id = arg1;
    (*entry)->count = arg2;
    (*entry)->next = NULL;
    if (arg0->actor->unk154 == 4) {
        arg0->actor->unk154 = 0;
    }
}

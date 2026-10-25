// func_8070D82C (src/global/112080.c): stage 2: compilable structural reconstruction; instruction scheduling and local types remain.
typedef struct M112aEntry { u16 id; u8 count; u8 pad3; struct M112aEntry *next; } M112aEntry;
typedef struct M112aContainer { u8 pad0[4]; Actor *actor; M112aEntry *entries; } M112aContainer;
extern void *func_80610FE8(s32);
void func_8070D82C(M112aContainer *arg0, s32 arg1, u8 arg2) { M112aEntry **entry = &arg0->entries; while (*entry != NULL) entry = &(*entry)->next; *entry = func_80610FE8(8); (*entry)->id = arg1; (*entry)->count = arg2; (*entry)->next = NULL; if (arg0->actor->unk154 == 4) arg0->actor->unk154 = 0; }

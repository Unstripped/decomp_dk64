// func_8070D654 (src/global/112080.c): stage 2: compilable structural reconstruction; instruction scheduling and local types remain.
typedef struct M112aItemList { u8 count; u8 pad1[3]; void *items; } M112aItemList;
typedef struct M112aVariantList { u8 count; u8 pad1[3]; void *items; } M112aVariantList;
extern void *func_80610FE8(s32); void func_8070D568(M112aItemList *, s32 *);
void func_8070D654(M112aVariantList *arg0, s32 *arg1) { s32 i; M112aItemList *item = func_80610FE8(arg0->count * 8); arg0->items = item; for (i = 0; i < arg0->count; i++) { func_8070D568(item, arg1); item = (M112aItemList *)((u8 *)item + 8); } }

// func_8070D568 (src/global/112080.c): stage 2: compilable structural reconstruction; instruction scheduling and local types remain.
typedef struct M112aItem { u8 flags; u8 pad1[3]; u8 *data; u8 tail[8]; } M112aItem;
typedef struct M112aItemList { u8 count; u8 pad1[3]; M112aItem *items; } M112aItemList;
extern void *func_80610FE8(s32);
void func_8070D380(s32, void *, s32 *); void func_8070D464(void *, s32 *);
void func_8070D568(M112aItemList *arg0, s32 *arg1) { s32 i; M112aItem *item; func_8070D380(1, arg0, arg1); item = func_80610FE8(arg0->count * 16); arg0->items = item; for (i = 0; i < arg0->count; i++, item++) { func_8070D380(1, item, arg1); if (item->flags & 4) { item->data = func_80610FE8(4); func_8070D380(4, item->data, arg1); } else item->data = NULL; func_8070D464(item, arg1); func_8070D380(4, item->tail, arg1); } }

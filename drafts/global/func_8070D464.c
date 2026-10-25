// func_8070D464 (src/global/112080.c): stage 2: compilable structural reconstruction; instruction scheduling and local types remain.
typedef struct M112aRecord { u8 count; u8 pad1[3]; u8 *data; } M112aRecord;
typedef struct M112aVariant { u8 flags; u8 pad1[7]; M112aRecord *data; } M112aVariant;
extern void *func_80610FE8(s32);
void func_8070D380(s32, void *, s32 *); void func_8070D3CC(M112aRecord *, s32 *);
void func_8070D464(M112aVariant *arg0, s32 *arg1) { s32 i; M112aRecord *data; if (arg0->flags & 1) { data = func_80610FE8(8); arg0->data = data; for (i = 0; i != 1; i++) { func_8070D3CC(data, arg1); data = (M112aRecord *)((u8 *)data + 8); } return; } if (arg0->flags & 2) { data = func_80610FE8(8); arg0->data = data; func_8070D380(1, data, arg1); data->data = func_80610FE8(data->count * 4); for (i = 0; i < data->count; i++) func_8070D380(4, data->data + i * 4, arg1); } }

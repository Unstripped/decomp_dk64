// func_8070D3CC (src/global/112080.c): stage 2: compilable structural reconstruction; instruction scheduling and local types remain.
typedef struct M112aRecord { u8 count; u8 pad1[3]; u8 *data; } M112aRecord;
extern void *func_80610FE8(s32);
void func_8070D380(s32, void *, s32 *);
void func_8070D3CC(M112aRecord *arg0, s32 *arg1) { s32 i; u8 *data; func_8070D380(1, arg0, arg1); data = func_80610FE8(arg0->count * 8); arg0->data = data; for (i = 0; i < arg0->count; i++) { func_8070D380(8, data, arg1); data += 8; } }

// func_8070D6D8 (src/global/112080.c): stage 2: compilable structural reconstruction; instruction scheduling and local types remain.
typedef struct M112aHeader { u8 count; u8 pad1[3]; void *items; u16 length; u8 padA[2]; u8 *payload; } M112aHeader;
extern void *func_80610FE8(s32); void func_8070D380(s32, void *, s32 *); void func_8070D654(void *, s32 *);
M112aHeader *func_8070D6D8(s32 arg0) { M112aHeader *header = func_80610FE8(0x10); func_8070D380(1, header, &arg0); func_8070D654(header, &arg0); func_8070D380(2, &header->length, &arg0); header->payload = func_80610FE8(header->length); memcpy(header->payload, (void *)arg0, header->length); return header; }

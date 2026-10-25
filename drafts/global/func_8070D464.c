// func_8070D464 (src/global/112080.c): Stage 2: recovered both flag branches and allocation/list loops; closest candidate differs in allocator argument preservation and register allocation.
typedef struct S112a2Record {
    u8 count;
    u8 pad1[3];
    u8 *data;
} S112a2Record;

typedef struct S112a2Variant {
    u8 flags;
    u8 pad1[7];
    S112a2Record *data;
} S112a2Variant;

extern void *func_80610FE8(s32);
void func_8070D380(s32, void *, s32 *);
void func_8070D3CC(S112a2Record *, s32 *);

void func_8070D464(S112a2Variant *arg0, s32 *arg1) {
    s32 i;
    S112a2Record *data;

    if (arg0->flags & 1) {
        data = func_80610FE8(8);
        arg0->data = data;
        for (i = 0; i != 1; i++) {
            func_8070D3CC(data, arg1);
            data = (S112a2Record *)((u8 *)data + 8);
        }
        return;
    }
    if (arg0->flags & 2) {
        data = func_80610FE8(8);
        arg0->data = data;
        func_8070D380(1, data, arg1);
        data->data = func_80610FE8(data->count * 4);
        for (i = 0; i < data->count; i++) {
            func_8070D380(4, data->data + i * 4, arg1);
        }
    }
}

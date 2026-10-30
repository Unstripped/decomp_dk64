// func_8070D464 (src/global/112080.c): Stage 2 starter; correct broad allocation and branch structure, but callee-save and argument register allocation differ.
typedef struct P112bRecord {
    u8 count;
    u8 pad1[3];
    u8 *data;
} P112bRecord;

typedef struct P112bVariant {
    u8 flags;
    u8 pad1[7];
    P112bRecord *data;
} P112bVariant;

void func_8070D464(void *arg0, s32 *arg1) {
    s32 i;
    P112bRecord *data;
    u8 *payload;

    if (((P112bVariant *)arg0)->flags & 1) {
        data = ((P112bVariant *)arg0)->data = heapAlloc(8);
        for (i = 0; i != 1; i++) {
            func_8070D3CC(data, arg1);
            data = (P112bRecord *)((u8 *)data + 8);
        }
        return;
    }
    if ((((P112bVariant *)arg0)->flags & 2) == 0) {
        return;
    }
    data = ((P112bVariant *)arg0)->data = heapAlloc(8);
    func_8070D380(1, data, arg1);
    payload = data->data = heapAlloc(data->count * 4);
    for (i = 0; i < data->count; i++) {
        func_8070D380(4, payload, arg1);
        payload += 4;
    }
}

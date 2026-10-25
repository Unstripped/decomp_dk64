// func_8070D464 (src/global/112080.c): stage 2: branch structure and allocation chains recovered; argument/callee-save allocation remains
// stage 2: branch structure and allocation chains recovered; argument/callee-save allocation remains
typedef struct S112dVariant {
    u8 flags;
    u8 pad1[7];
    S112a2Record *data;
} S112dVariant;

void func_8070D464(void *arg0, s32 *arg1) {
    s32 i;
    S112a2Record *data;
    u8 *payload;

    if (((S112dVariant *)arg0)->flags & 1) {
        data = ((S112dVariant *)arg0)->data = func_80610FE8(8);
        for (i = 0; i != 1; i++) {
            func_8070D3CC(data, arg1);
            data = (S112a2Record *)((u8 *)data + 8);
        }
        return;
    }
    if ((((S112dVariant *)arg0)->flags & 2) == 0) {
        return;
    }
    data = ((S112dVariant *)arg0)->data = func_80610FE8(8);
    func_8070D380(1, data, arg1);
    payload = data->data = func_80610FE8(data->count * 4);
    for (i = 0; i < data->count; i++) {
        func_8070D380(4, payload, arg1);
        payload += 4;
    }
}

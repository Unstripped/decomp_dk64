// func_80715A3C (src/global/119370.c): stage 4: 135 instruction diff; only commutative base register choices and category temporary allocation remain
typedef struct Ua2RouteEntry {
    s32 value;
    s32 column;
} Ua2RouteEntry;

s32 func_8066B0F8(s32, s16, s32, s32);

void func_80715A3C(s16 *arg0, u8 arg1, u8 *arg2, s32 arg3, s32 arg4, s32 *arg5) {
    s32 category;
    s32 i;
    s32 index;
    s32 value;
    s32 *out;
    Ua2RouteEntry *entry;

    i = 0;
    if (arg3 > 0) {
        out = arg5;
        index = arg3 * arg4;
        entry = (Ua2RouteEntry *)(arg2 + (index * 8));
        do {
            if (entry->column == -1) {
                if (arg1) {
                    category = 0x19;
                } else {
                    category = 7;
                }
                value = func_8066B0F8(category, arg0[index + i], 0, 0);
                *out = value;
                entry->value = value;
            } else {
                *out = entry->value;
            }
            i += 1;
            out += 1;
            entry += 1;
            entry[-1].column = arg4;
        } while (i != arg3);
    }
}

// func_806F4528 (src/global/F56F0.c): from .scratch/F56C/func_806F4528_best.c
typedef struct {
    s16 halves[9];
} F5N4RawEntry;

void *heapAlloc(s32);

void func_806F4528(void *arg0) {
    u8 *next;
    u8 *destination;
    u8 *source;
    F5N4ListEntry *entry;
    s16 outer;
    s16 inner;

    if (arg0 != NULL) {
        D_80753E90->unk0 = *(s16 *)arg0;
        source = (u8 *)arg0 + 2;
        D_80753E90->unk4 = heapAlloc((D_80753E90->unk0 * 8) + 8);
        entry = D_80753E90->unk4;
        for (outer = 0; outer < D_80753E90->unk0; outer++) {
            entry->unk0 = *(s16 *)source;
            next = source + 2;
            for (inner = 0; inner < entry->unk0; inner++) {
                if (inner == 0) {
                    entry->unk4 = heapAlloc(entry->unk0 * 0x12);
                    destination = entry->unk4;
                } else {
                    destination += 0x12;
                }
                *(F5N4RawEntry *)destination = *(F5N4RawEntry *)next;
                next += 0x12;
            }
            source = next;
            entry++;
        }
    } else {
        D_80753E90->unk0 = 0;
    }
}

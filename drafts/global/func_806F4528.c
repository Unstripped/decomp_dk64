// func_806F4528 (src/global/F56F0.c): Stage 4: reconstructed nested counts, allocation, and inlined 18-byte copy. Packed byte-array assignment reaches the target lwl/lwr/swl/swr core; remaining mismatch is frame/register allocation and final halfword copy form.
typedef struct {
    s16 unk0;
    u8 pad2[2];
    void *unk4;
} F5N4ListEntry;

typedef struct {
    s16 unk0;
    u8 pad2[2];
    F5N4ListEntry *unk4;
} F5N4List;

typedef struct {
    u8 bytes[0x12];
} F5N4RawEntry;

extern F5N4List *D_80753E90;
void *heapAlloc(s32);

void func_806F4528(void *arg0) {
    u8 *source;
    u8 *destination;
    F5N4ListEntry *entry;
    s16 outer;
    s16 inner;

    if (arg0 != NULL) {
        D_80753E90->unk0 = *(s16 *)arg0;
        source = (u8 *)arg0 + 2;
        D_80753E90->unk4 = heapAlloc((D_80753E90->unk0 * 8) + 8);
        entry = D_80753E90->unk4;
        for (outer = 0; outer < D_80753E90->unk0; outer++, entry++) {
            entry->unk0 = *(s16 *)source;
            source += 2;
            if (entry->unk0 > 0) {
                destination = entry->unk4;
                for (inner = 0; inner < entry->unk0; inner++) {
                    if (inner == 0) {
                        destination = heapAlloc(entry->unk0 * 0x12);
                        entry->unk4 = destination;
                    }
                    *(F5N4RawEntry *)destination = *(F5N4RawEntry *)source;
                    source += 0x12;
                    destination += 0x12;
                }
            }
        }
    } else {
        D_80753E90->unk0 = 0;
    }
}

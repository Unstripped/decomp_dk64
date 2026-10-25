// func_80709ACC (src/global/10E1D0.c): stage 2: behavioural extrema loop; IDO unrolls inner loop unlike target
typedef struct R1F10E1D0a_SortEntry { s32 unk0, unk4, unk8; u8 padC[0x10]; } R1F10E1D0a_SortEntry;
typedef struct R1F10E1D0a_SortView { s32 unk0, unk4, unk8; R1F10E1D0a_SortEntry *unkC; s32 unk10, unk14; s32 *unk18, *unk1C, *unk20; } R1F10E1D0a_SortView;
s32 func_80709ACC(R1F10E1D0a_SortView *arg0) {
    R1F10E1D0a_SortEntry *entry; s32 min, max, count, row = 0, index = 0;
    if (*arg0->unk18 != 0) do {
        count = *arg0->unk18; entry = (R1F10E1D0a_SortEntry *)((u8 *)arg0->unkC + index); max = min = entry->unk0;
        for (row = 0; row < count; row++, index += 0x1C, entry++) {
            if (entry->unk0 > max) max = entry->unk0; else if (entry->unk0 < min) min = entry->unk0;
            if (entry->unk4 > max) max = entry->unk4; else if (entry->unk4 < min) min = entry->unk4;
            if (entry->unk8 > max) max = entry->unk8; else if (entry->unk8 < min) min = entry->unk8;
        }
        *(s32 *)((u8 *)arg0->unk20 + row) = min;
        *(s32 *)((u8 *)arg0->unk1C + row) = max;
        row += 4;
    } while (*(s32 *)((u8 *)arg0->unk18 + row));
    return 1;
}

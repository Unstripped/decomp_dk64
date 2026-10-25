// func_806F18F4 (src/global/F56F0.c): Stage 5: instruction shape and table bounds match; state index/value live ranges are v0/v1-swapped. Tried declaration reordering, direct table assignment, temporary splitting, and uopt trace.
void func_806F18F4(s32 arg0, F5BSlot *arg1, s32 *arg2) {
    s32 tableIndex;
    u16 angle;

    tableIndex = F5B_PLAYER_STATE->unk8E - 0x16;
    if ((tableIndex >= 0) && ((u32)tableIndex < 4U)) {
        angle = D_80752F38[tableIndex];
        arg1[*arg2].unk0 = 0x7F;
        arg1[*arg2].unk1 = 1;
        arg1[*arg2].unk2 = 0;
        arg1[*arg2].unk4 = angle;
        arg1[*arg2].unk6 = 0;
        *arg2 += 1;
    }
}

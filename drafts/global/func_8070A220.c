// func_8070A220 (src/global/10E1D0.c): no note
void func_8070A220(void *arg0, void *arg1, s32 arg2) {
    s32 *entries = *(s32 **)((u8 *)arg1 + 8);
    s32 offset = 0;
    while (*(s32 *)((u8 *)entries + offset) != 0) {
        s32 start = *(s32 *)((u8 *)entries + offset + 8);
        s32 end = *(s32 *)((u8 *)entries + offset + 0xC);
        if (arg2 >= start) {
            if (end < arg2) arg2 = end;
            if (*(s32 *)((u8 *)entries + offset) == 2) *(f32 *)((u8 *)arg0 + 8) = *(f32 *)((u8 *)arg0 + 8);
        }
        offset += 0x1C;
    }
}

// func_80712574 (src/global/117190.c): Closest C mirrors state/timer loop; frame and temporary placement remain off
void func_80712574(void) {
    s32 found = 0;
    u8 index = 0;
    u16 *entry;
    u64 time;
    s32 duration;

    D_80755340.unk10 = 1;
    D_80755340.unk11 = 0;
    time = osGetTime();
    D_80755340.unk0 = time;
    D_80755340.unk4 = time;
    duration = func_80712548() * 60;
    D_80755340.unkC = duration;
    entry = D_80755358;
    do {
        if (*entry < duration) {
            D_80755340.unk11 = index;
            found = 1;
        }
        index++;
        entry++;
    } while ((index < 10) && (found == 0));
}

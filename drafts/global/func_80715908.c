// func_80715908 (src/global/119370.c): TEXT OK: destructor/unlinker. Deliberately pass &sp3F - 8 to reproduce target output-status stack address sp+0x3F; fdiff reports relocation-only own-data mismatch.
void func_80630588(s32, s32, s32, void *);
void func_8062D26C(void *);
void heapFreeDeferred(void *);

void func_80715908(Ua1Effect *effect) {
    u8 sp3F;
    s32 temp_a0;
    s32 i;
    Ua1Effect *previous;
    Ua1Effect *next;
    Ua1Effect *buffer;

    if (effect->mode == 0) {
        if (effect->flags & 4) {
            func_80630588(0, (s32)effect, 4, &sp3F - 8);
        } else {
            func_8062D26C(effect);
        }
    } else {
        func_80630588(0, (s32)effect, 3, &sp3F - 8);
    }
    temp_a0 = (s32)effect->allocation;
    if (temp_a0 != 0) {
        heapFreeDeferred((void *)temp_a0);
    }
    i = 0;
    buffer = effect;
    while (i < effect->itemCount) {
        heapFreeDeferred(((void **)buffer)[0]);
        heapFreeDeferred(((void **)buffer)[1]);
        i += 1;
        buffer = (Ua1Effect *)((u8 *)buffer + 8);
    }
    if (osCicId != 0x17D9) {
        osSetTime((s64)(s32)func_806119A0());
    }
    previous = effect->previous;
    next = effect->next;
    heapFreeDeferred(effect);
    if (previous != NULL) {
        previous->next = next;
    } else {
        D_807FDB04 = next;
    }
    if (next != NULL) {
        next->previous = previous;
    } else {
        D_807FDB08 = previous;
    }
}

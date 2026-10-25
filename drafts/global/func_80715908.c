// func_80715908 (src/global/119370.c): Stage 3: entire stream matches except stack frame/local pointer placement; 0x50/sp+0x47 versus target 0x48/sp+0x3F.
void func_80630588(s32, s32, s32, void *);
void func_8062D26C(void *);
void heapFreeDeferred(void *);

void func_80715908(Ua1Effect *effect) {
    s32 sp3C[3];
    s32 i;
    Ua1Effect *previous;
    Ua1Effect *next;
    Ua1Effect *buffer;

    if (effect->mode == 0) {
        if (effect->flags & 4) {
            func_80630588(0, (s32)effect, 4, (u8 *)sp3C + 3);
        } else {
            func_8062D26C(effect);
        }
    } else {
        func_80630588(0, (s32)effect, 3, (u8 *)sp3C + 3);
    }
    if (effect->allocation != NULL) {
        heapFreeDeferred(effect->allocation);
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

// func_80715908 (src/global/119370.c): stage 2: full control flow and stack frame match; call setup and local byte placement remain
typedef struct Ua2Effect {
    u8 pad0[0x20];
    u8 itemCount;
    u8 pad21[0x317];
    s32 resource;
    u8 pad33C[0x33];
    u8 mode;
    u8 pad370[0x14];
    void *allocation;
    u8 pad388[4];
    u16 flags;
    u8 pad38E[0xA];
    struct Ua2Effect *previous;
    struct Ua2Effect *next;
} Ua2Effect;

extern Ua2Effect *D_807FDB04;
extern Ua2Effect *D_807FDB08;
void func_8062D26C(Ua2Effect *, Ua2Effect *, s32);
void func_80630588(void *, Ua2Effect *, s32, u8 *);
void heapFreeDeferred(void *);
u32 func_806119A0(void);

void func_80715908(Ua2Effect *effect) {
    u8 sp3F;
    s32 temp_v0;
    s32 var_s1;
    void *temp_a0;
    Ua2Effect *temp_s0;
    Ua2Effect *temp_s1;
    void **var_s0;

    if (effect->mode == 0) {
        if (effect->flags & 4) {
            func_80630588(NULL, effect, 4, &sp3F);
        } else {
            func_8062D26C(effect, effect, 4);
        }
    } else {
        func_80630588(NULL, effect, 3, &sp3F);
    }
    temp_a0 = effect->allocation;
    if (temp_a0 != NULL) {
        heapFreeDeferred(temp_a0);
    }
    var_s1 = 0;
    var_s0 = (void **)effect;
    if ((s32)effect->itemCount > 0) {
        do {
            heapFreeDeferred(var_s0[0]);
            heapFreeDeferred(var_s0[1]);
            var_s1 += 1;
            var_s0 += 2;
        } while (var_s1 < (s32)effect->itemCount);
    }
    if (osCicId != 0x17D9) {
        temp_v0 = func_806119A0();
        osSetTime((u64)(s32)temp_v0);
    }
    temp_s0 = effect->previous;
    temp_s1 = effect->next;
    heapFreeDeferred(effect);
    if (temp_s0 != NULL) {
        temp_s0->next = temp_s1;
    } else {
        D_807FDB04 = temp_s1;
    }
    if (temp_s1 != NULL) {
        temp_s1->previous = temp_s0;
    } else {
        D_807FDB08 = temp_s0;
    }
}

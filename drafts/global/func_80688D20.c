// func_80688D20 (src/global/8D3E0.c): regalloc and stack: sp27 at 0x27 vs 0x2f, loop count-- delay slot
typedef struct ActD3A_EntryC0 {
    void *ptr;
    char pad[0xBC];
} ActD3A_EntryC0;

extern ActD3A_EntryC0 D_8076A178[];
s32 func_80600080(s32);
void func_80631F58(void *, void *, void *);

void func_80688D20(s16 arg0, s16 arg1, s16 arg2, f32 arg3) {
    s32 pad[2];
    void *sp34;
    void *sp30;
    u8 found;
    s32 temp_v0;
    s32 count;
    ActD3A_Sub38 *item;

    found = 0;
    temp_v0 = func_80600080(arg0);
    if (temp_v0 != -1) {
        func_80631F58(D_8076A178[temp_v0].ptr, &sp34, &sp30);
        count = *(s32 *)sp30;
        item = (ActD3A_Sub38 *)((s32 *)sp30 + 1);
        sp30 = item;
        if (count != 0) {
            do {
                if (item->unk34 == arg1) {
                    item->unk10[arg2] = arg3;
                    found = 1;
                }
                count--;
                item++;
            } while (count != 0 && !found);
        }
    }
}

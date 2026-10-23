// func_80688D20 (src/global/8D3E0.c): 5 insns diff: stack slot 0x27 vs 0x2F, and t3/t4/t5 vs t2/t3/t4 in loop. Loop delay slot and control flow match.
typedef struct R3D3A_EntryC0 {
    void *ptr;
    char pad[0xBC];
} R3D3A_EntryC0;

extern R3D3A_EntryC0 D_8076A178[];
s32 func_80600080(s32);
void func_80631F58(void *, void *, void *);

void func_80688D20(s16 arg0, s16 arg1, s16 arg2, f32 arg3) {
    s32 pad[2];
    void *sp34;
    void *sp30;
    u8 found;
    s32 temp_v0;
    s32 count;
    ActorListRecord *item;

    found = 0;
    temp_v0 = func_80600080(arg0);
    if (temp_v0 != -1) {
        func_80631F58(D_8076A178[temp_v0].ptr, &sp34, &sp30);
        count = *(s32 *)sp30;
        item = (ActorListRecord *)((s32 *)sp30 + 1);
        sp30 = item;
        if (count != 0) {
            do {
                if (item->unk34 == arg1) {
                    ((f32 *)item->unk10)[arg2] = arg3;
                    found = 1;
                }
                count--;
                item++;
            } while (count != 0 && !found);
        }
    }
}

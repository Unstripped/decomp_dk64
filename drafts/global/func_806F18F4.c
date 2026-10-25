// func_806F18F4 (src/global/F56F0.c): stage 5: valid typed reconstruction; exact size/order. Tested alternate declaration ordering, but allocator retains state index in v0 and angle in v1; target swaps them.
typedef struct {
    u8 unk0;
    u8 unk1;
    s16 unk2;
    s16 unk4;
    s16 unk6;
} F5BSlot;

typedef struct {
    u8 pad0[0x8E];
    u8 unk8E;
} F5BPlayerState;

extern void *D_807FD580;
extern u16 D_80752F38[];

void func_806F18F4(s32 arg0, F5BSlot *arg1, s32 *arg2) {
    s32 tableIndex;
    u16 angle;

    tableIndex = ((F5BPlayerState *) D_807FD580)->unk8E - 0x16;
    if ((tableIndex >= 0) && ((u32) tableIndex < 4U)) {
        angle = D_80752F38[tableIndex];
        arg1[*arg2].unk0 = 0x7F;
        arg1[*arg2].unk1 = 1;
        arg1[*arg2].unk2 = 0;
        arg1[*arg2].unk4 = angle;
        arg1[*arg2].unk6 = 0;
        *arg2 += 1;
    }
}

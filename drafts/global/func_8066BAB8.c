// func_8066BAB8 (src/global/6AD90.c): 0-insn delta (35/35), home-slot stores match; regalloc around next_tail (/, /)
typedef struct R2EQueueItem {
    s32 unk0;
    s32 unk4;
    u16 unk8;
    u8 unkA;
} R2EQueueItem;

void func_8066BAB8(arg0, arg1, arg2)
s32 arg0;
u8 arg1;
u16 arg2;
{
    R2EQueueItem *item = &D_807FB228[D_807FB221];
    s32 time = D_8076A064;
    u8 next_tail = D_807FB221 + 1;

    item->unk4 = arg0;
    item->unkA = arg1;
    item->unk8 = arg2;
    D_807FB221 = next_tail;
    item->unk0 = time;

    if (next_tail == 0x40) {
        D_807FB221 = 0;
        next_tail = 0;
    }

    if (next_tail == D_807FB220) {
        if (++D_807FB220 == 0x40) {
            D_807FB220 = 0;
        }
    }
}

// func_8066BAB8 (src/global/699B0.c): from .scratch/R2E/func_8066BAB8_best.c
void func_8066BAB8(arg0, arg1, arg2)
s32 arg0;
u8 arg1;
u16 arg2;
{
    QueueItem *item = &D_807FB228[D_807FB221];
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

    if (D_807FB220 == next_tail) {
        u8 next_head = D_807FB220 + 1;
        D_807FB220 = next_head;
        if (next_head == 0x40) {
            D_807FB220 = 0;
        }
    }
}

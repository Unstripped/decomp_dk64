// func_806FBB58 (src/global/100180.c): Matched: preserve the allocation result through a pointer-to-global store and pass that assigned result to heapClearBlock; this forces the target v1 address materialization.
s32 func_80610FE8(s32);
void heapClearBlock(s32);
extern void *D_807FD7F0;
extern u8 *D_807FD7F4;

void func_806FBB58(void) {
    s32 allocation;
    s32 *allocation_slot;
    s32 temp_v0;
    u8 **heap_buffer;

    D_807FD7F0 = func_80610FE8(0xAC);
    temp_v0 = func_80610FE8(0x2B);
    heap_buffer = &D_807FD7F4;
    allocation_slot = (s32 *)heap_buffer;
    allocation = (*allocation_slot = temp_v0);
    heapClearBlock(allocation);
}

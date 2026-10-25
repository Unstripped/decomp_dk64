// func_806FBB58 (src/global/100180.c): Stage 4: exact except D_807FD7F4 store emits lui at; sw lo instead of lui v1; addiu; sw 0.
s32 func_80610FE8(s32);
void heapClearBlock(s32);
extern s32 D_807FD7F0;
extern s32 D_807FD7F4;

void func_806FBB58(void) {
    s32 *temp_v1;
    s32 temp_v0;

    D_807FD7F0 = func_80610FE8(0xAC);
    temp_v0 = func_80610FE8(0x2B);
    temp_v1 = &D_807FD7F4;
    *temp_v1 = temp_v0;
    heapClearBlock(temp_v0);
}

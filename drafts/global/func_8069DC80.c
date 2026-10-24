// func_8069DC80 (src/global/9DD70.c): stage 6: same instruction multiset; target keeps arg1 in s0 and spills idx at 0x20, mine homes arg1 (0x2c) and spills idx at 0x1c
extern Actor *D_807FBB40;
void *func_806FBB9C(s16);
void *func_80610FE8(s32);
void heapFreeDeferred(void *);
void animSetLoopLimit(void *, s32, s16);
void animSetSpeed(void *, s32, f32);
void animSetNodeItem(void *, s32, s16, s32);
void func_8069DC10(s32 *, s32 *, u8);

s32 func_8069DC80(u8 arg0, void *arg1, u8 arg2, u8 arg3, u8 arg4) {
    s32 *temp;
    s32 *buf;

    temp = func_806FBB9C(arg0 + arg3);
    if (arg1 != NULL) {
        heapFreeDeferred(arg1);
    }
    buf = func_80610FE8(arg4 << 7);
    func_8069DC10(buf, temp, arg4);
    animSetLoopLimit(D_807FBB40, arg2, -1);
    animSetSpeed(D_807FBB40, arg2, 0.0f);
    animSetNodeItem(D_807FBB40, arg2, 0, (s32)buf);
    return (s32)buf;
}

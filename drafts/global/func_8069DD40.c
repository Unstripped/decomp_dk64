// func_8069DD40 (src/global/9DD70.c): stage 6: identical except three register names (actor v0 vs v1, t/unk swapped t0 vs v1); needs a dummy local for the 0x50 frame
extern Actor *D_807FBB40;
extern void *D_807FD580;
extern u8 D_8076A0AB;
extern u16 D_807FC930[];
extern u16 D_807446C0[];
s32 func_805FF030(s32, s32);
void func_8063DA40(s32, s32);
void func_806319C4(Actor *, s32);
s32 func_8069DC80(u8, void *, u8, u8, u8);

void func_8069DD40(void) {
    Actor *actor;
    s32 *model;
    s32 dummy;
    s32 unk;
    s32 t;
    u16 val;

    actor = D_807FBB40;
    model = (s32 *)actor->unk174;
    if (!(actor->unk60 & 0x10) || (*(u32 *)((u8 *)D_807FD580 + 0x1F0) & 0x20000)) {
        t = func_805FF030(D_8076A0AB, 0);
        if (t >= 8) {
            t = 0;
        }
        unk = t << 1;
        val = *(u16 *)((u8 *)D_807FC930 + unk);
        model[0] = func_8069DC80(0x21, (void *)model[0], 0, val / 100, 0x20);
        model[1] = func_8069DC80(0x21, (void *)model[1], 1, val % 100 / 10, 0x20);
        model[2] = func_8069DC80(0x21, (void *)model[2], 2, val % 10, 0x20);
        D_807FBB40->unk16A = 0xFF;
        D_807FBB40->unk16B = 0xFF;
        D_807FBB40->unk16C = 0xFF;
        D_807FBB40->unk60 |= 0x800000;
        *(u32 *)((u8 *)D_807FD580 + 0x1F0) &= ~0x20000;
        if (val >= *(u16 *)((u8 *)D_807446C0 + unk)) {
            D_807FBB40->unk60 &= ~0x8000;
            D_807FBB40->unk128 = 0;
            D_807FBB40->unk144 = 1;
            func_8063DA40(8, 2);
            func_8063DA40(9, 10);
            func_8063DA40(10, 10);
            func_8063DA40(11, 10);
            func_8063DA40(13, 10);
            func_8063DA40(12, 10);
        }
    }
    func_806319C4(D_807FBB40, 0);
}

// func_806EF830 (src/global/EFDC0.c): stage 6: identical control flow and instruction count; only final D_807FD580/unk88/unk174 register allocation differs
typedef struct {
    u8 pad0[0x88];
    Actor *unk88;
} EfDTransitionState;

extern void func_8061B610(void *);

void func_806EF830(void) {
    if ((D_807FBB48->unk154 == 0x36) || (D_807FBB48->unk154 == 0x39) ||
        (D_807FBB48->unk154 == 0x3A) || (D_807FBB48->unk154 == 0x71) ||
        (D_807FBB48->unk154 == 0x73) || (D_807FBB48->unk154 == 0x74)) {
        return;
    }
    func_806CA2AC();
    D_807FBB48->unk60 &= 0xFFFF7FFF;
    func_80614E78(D_807FBB48, 0x27);
    D_807FBB48->unk154 = 0x39;
    D_807FBB48->unk155[0] = 0;
    ((u8 *)D_807FD580)[0x11C] = 0x19;
    func_8061B610(((void **)D_807FD580)[0x41]);
    if ((D_8076A0A8 != 0x52) && (D_8076A0A8 != 0xE)) {
        func_806C9974(D_807FC929, -0x40);
    } else {
        ((u8 *)((EfDTransitionState *)D_807FD580)->unk88->unk174)[0x45] = 1;
    }
}

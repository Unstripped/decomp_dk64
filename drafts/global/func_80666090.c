// func_80666090 (src/global/6AD90.c): func_80666090 (src/global/6AD90.c): stage 5, 9 text rows, shape 0 (registers only): loop addu operand order reversed vs target (target 'addu t8,v0,t7' base+(a3-s1) and 'addu a1,s1,a0' s1+*a3; ours complex first) plus t1/a0/t2 temp swaps. Named 'off' local replaces the pad5C FAKE (frame 0x60 ok). Tried (NM3): 756 statement permutations of loop head, 96 w-local forms, 6000 random decl orders, local+global deadsweep, nine-& hack: none flips the addu order.
typedef struct {
    u8 pad0[4];
    u32 unk4;
    u8 pad8;
    u8 unk9;
    u8 padA[0xE];
    s16 unk18;
    s16 unk1A;
} Col6AAssetHeader;

typedef struct {
    u32 unk0;
    u32 unk4;
    u32 unk8;
    u32 unkC;
    u32 unk10;
} Col6ABufferEntry;

struct CollisionBufferEntry;
extern struct CollisionBufferEntry *D_807F9514;
extern s32 D_807F9518;
extern u8 D_807F951C;
extern s32 D_8076A0A8;
extern u8 D_807F94B4;
void *func_80610FE8(s32);
void *assetLoad(s32, s32, s32, s32);
s32 assetGetSize(s32, s32);
void assetSetImmediateFree(void);
void assetFreeBuffer(void *, s32, s32);
void gunzip(void *, void *, void *);
void heapFree(void *);

void func_80666090(Col6AAssetHeader *arg0) {
    s32 off;
    void *sp58;
    void *sp54;
    void *sp50;
    u8 *var_s1;
    u8 *a3;
    u8 *a1;
    u8 *a2;
    s32 base;
    s32 i;
    void *sp34;

    D_807F9514 = (struct CollisionBufferEntry *)func_80610FE8(0x11A8);
    D_807F9518 = (u32)(arg0->unk18 * arg0->unk1A);
    var_s1 = (u8 *)assetLoad(3, D_8076A0A8, 1, 0);
    D_807F951C = 0;
    if (arg0->unk9 & 2) {
        sp58 = var_s1;
        var_s1 = func_80610FE8(arg0->unk4);
        sp34 = func_80610FE8(0x2400);
        sp54 = var_s1;
        sp50 = sp58;
        gunzip(&sp50, &sp54, sp34);
        heapFree(sp34);
        assetSetImmediateFree();
        assetFreeBuffer(sp58, 0x9D, 0x3A);
        D_807F951C = 1;
    }
    base = assetGetSize(3, D_8076A0A8);
    a3 = var_s1 + 4;
    for (i = 0; i < D_807F9518; i++) {
        ((Col6ABufferEntry *)D_807F9514)[i].unk8 = 0;
        if (D_807F9514 && D_807F9514) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        a2 = a3 + 4;
        off = a3 - var_s1;
        ((Col6ABufferEntry *)D_807F9514)[i].unkC = base + off + 4;
        a1 = var_s1 + *(u32 *)a3;
        a3 = a1;
        if (D_807F951C) {
            ((Col6ABufferEntry *)D_807F9514)[i].unk0 = (u32)a2;
            ((Col6ABufferEntry *)D_807F9514)[i].unk4 = (u32)a1;
        } else {
            ((Col6ABufferEntry *)D_807F9514)[i].unk0 = 0;
            ((Col6ABufferEntry *)D_807F9514)[i].unk4 = 0;
        }
        ((Col6ABufferEntry *)D_807F9514)[i].unk10 = a1 - a2;
    }
    if (!D_807F951C) {
        assetSetImmediateFree();
        assetFreeBuffer(var_s1, 0xC3, 0x3A);
    }
    D_807F94B4 = 0;
}

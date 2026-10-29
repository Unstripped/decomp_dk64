// func_80666090 (src/global/6AD90.c): STAGE 4 (frame 0x60, s0-s3 saved, address caching in s0/s2/s3 reached by direct global access, parked NON_MATCHING in src copy): remaining ~10 text rows = temp regs in loop (second E[i] ptr load uses a0 vs expected t1; lw *a3 t2 vs a0; addu a1 operand order). Needs pad5C/pad30 used locals for frame, one deadsweep 'if (D_807F9514 && D_807F9514) {}' in loop; permuter 55 vs 65 only.
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
void *func_8066B0F8(s32, s32, s32, s32);
s32 assetGetSize(s32, s32);
void assetSetImmediateFree(void);
void assetFreeBuffer(void *, s32, s32);
void gunzip(void *, void *, void *);
void heapFree(void *);

void func_80666090(Col6AAssetHeader *arg0) {
    s32 pad5C;
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
    s32 pad30;

    pad5C = pad30; // FAKE: reading a pad local makes uopt reserve its stack slot (frame 0x60)
    D_807F9514 = (struct CollisionBufferEntry *)func_80610FE8(0x11A8);
    D_807F9518 = (u32)(arg0->unk18 * arg0->unk1A);
    var_s1 = (u8 *)func_8066B0F8(3, D_8076A0A8, 1, 0);
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
        ((Col6ABufferEntry *)D_807F9514)[i].unkC = base + (a3 - var_s1) + 4;
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

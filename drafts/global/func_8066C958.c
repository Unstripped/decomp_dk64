// func_8066C958 (src/global/70FD0.c): Stage 5: frame 0x68, saved s0-s2 and stack slots (sp60/5C/58/38/30) match with the dummy pad between sp38 and sp30 (w1 layout); remaining diff is loop register naming/scheduling: target keeps v1 for 's0+s1' and a2/a3 for ptr/counter, mine hoists 's0+s1' into the beqz delay slot (uopt PRE) and permutes a0/a2/a3/t0
typedef struct Col7A_C958Arg {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ u8 pad4[5];
    /* 0x09 */ u8 unk9;
    /* 0x0A */ u8 padA[6];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
} Col7A_C958Arg;

typedef struct Col7A_C958Cache {
    /* 0x00 */ void *unk0;
    /* 0x04 */ u8 *unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
} Col7A_C958Cache;

extern s32 D_8076A0A8;
extern s32 D_807FB530;

void *func_8066B0F8(s32, s32, s32, s32);
s32 assetGetSize(s32, s32);
void assetSetImmediateFree(void);
void assetFreeBuffer(void *, s32, s32);
void gunzip(void *, void *, void *);

void func_8066C958(Col7A_C958Arg *arg0) {
    u8 *var_s0;
    void *sp60;
    void *sp5C;
    void *sp58;
    s32 *var_a2;
    u8 *var_v1;
    u8 *temp_a0;
    s32 temp_lo;
    s32 var_a3;
    s32 var_s1;
    s32 elem_size;
    s32 sp38;
    s32 d1;
    void *sp30;

    var_s1 = 4;
    var_s0 = func_8066B0F8(2, D_8076A0A8, 1, 0);
    D_807FB549 = 0;
    if (arg0->unk9 & 1) {
        sp60 = var_s0;
        var_s0 = func_80610FE8(arg0->unk0);
        sp30 = func_80610FE8(0x2400);
        sp5C = var_s0;
        sp58 = sp60;
        gunzip(&sp58, &sp5C, sp30);
        heapFree(sp30);
        assetSetImmediateFree();
        assetFreeBuffer(sp60, 0x14C, 0xA);
        D_807FB549 = 1;
    }
    sp38 = assetGetSize(2, D_8076A0A8);
    if (D_8076A0A8 && D_8076A0A8) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    if (D_807FB534 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    D_807FB530 = *(s32 *)var_s0;
    D_807FB534 = func_80610FE8(0x1518);
    temp_lo = arg0->unk10 * arg0->unk12;
    var_a2 = (s32 *)(var_s0 + 4);
    var_a3 = 0;
    elem_size = 24;
    D_807FB538 = temp_lo;
    if (temp_lo > 0) {
        do {
            temp_a0 = var_s0 + var_s1 + 4;
            var_s1 = *var_a2;
            if (D_807FB549 != 0) {
                ((Col7A_C958Cache *)D_807FB534)[var_a3].unk4 = temp_a0;
            } else {
                ((Col7A_C958Cache *)D_807FB534)[var_a3].unk4 = NULL;
            }
            ((Col7A_C958Cache *)D_807FB534)[var_a3].unk0 = NULL;
            var_v1 = var_s0 + var_s1;
            ((Col7A_C958Cache *)D_807FB534)[var_a3].unkC = sp38 + (temp_a0 - var_s0);
            ((Col7A_C958Cache *)D_807FB534)[var_a3].unk10 = var_v1 - temp_a0;
            var_a2 = (s32 *)var_v1;
            ((Col7A_C958Cache *)D_807FB534)[var_a3].unk8 = 0;
            ((Col7A_C958Cache *)D_807FB534)[var_a3].unk14 = (var_v1 - temp_a0) / elem_size;
            var_a3++;
        } while (var_a3 < D_807FB538);
    }
    if (D_807FB549 == 0) {
        assetSetImmediateFree();
        assetFreeBuffer(var_s0, 0x17C, 0xA);
    }
}

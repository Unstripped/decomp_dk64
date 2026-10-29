// func_80709890 (src/global/10E1D0.c): stage 6 (NM6 base unchanged, 15 diff lines, regs only; NM9 diagnosis): in uopt -l 5 the loop walker p (cand M -20, merged loops 1+3) has intrinsic forbidden [v0,v1] because its def block holds the call-return v0 (R) and the loaded-value temp (M -28, adj 22) takes v1 first; target has p=v0, loaded=v1, unk8/unkC/unk18 = a0/a1/a3. A dead 'if (arg0 && arg0) {}' after the 3rd call (new bb) frees v0 (loaded temp then takes v0 and p v1: swapped) and a dead 'if (p) {}' before the loop-3 walker raises p priority -> p=v0, loaded=v1 (matches) but score 20 (unk18 stays in a reg, 28 const to a1). Searched: deadsweep (-extra all), random dead-stmt SA 1400s from base and from that variant, loop forms, p/r separate vars, reordering the 3rd call store, moving k&&k: none below 15. Untested: one walker variable shared by all three loops (priority sum) with p+=7 stride form.
typedef struct EaEntry {
    u32 unk0;
    u8 pad[0x18];
} EaEntry;

typedef struct EaBlockB {
    u32 *unk0;
    s32 *unk4;
    u8 *unk8;
} EaBlockB;

typedef struct EaBlockA {
    s32 unk0;
    s32 unk4;
    u8 *unk8;
    u8 *unkC;
    void *unk10;
    void *unk14;
    u32 *unk18;
    s32 *unk1C;
    s32 *unk20;
} EaBlockA;

void *func_80610FE8(s32);

s32 func_80709890(EaBlockA *arg0, EaBlockA **arg1, EaBlockB **arg2, s32 **arg3) {
    s32 count;
    s32 k;
    s32 sum;
    EaBlockB *b;
    u32 *p;
    EaEntry *q;

    if (arg0 == NULL) {
        return 0;
    }
    if (arg1 == NULL) {
        return 0;
    }
    D_807FD9B4 = func_80610FE8(0x708);
    if (k && k) {}
    arg0->unk10 = func_80610FE8(arg0->unk0 * 0x10);
    arg0->unk14 = func_80610FE8(arg0->unk0 * 0x10);
    arg0->unk8 = (u8 *)arg0 + 0x2C;
    arg0->unkC = arg0->unk8 + arg0->unk0 * 0xC;
    arg0->unk18 = (u32 *)(arg0->unkC + arg0->unk4 * 0x1C);
    count = 1;
    p = arg0->unk18;
    while (*p++ != 0) {
        count++;
    }
    arg0->unk20 = (s32 *)arg0->unk18 + count;
    arg0->unk1C = arg0->unk20 + count;
    *arg1 = arg0;
    if (arg2 != NULL) {
        b = (EaBlockB *)(arg0->unk1C + count);
        b->unk8 = (u8 *)(b + 1);
        q = (EaEntry *)b->unk8;
        if (D_807FD9B4 && D_807FD9B4) {}
        count = 1;
        while ((q++)->unk0 != 0) {
            count++;
        }
        b->unk0 = (u32 *)(b->unk8 + count * 0x1C);
        k = 1;
        p = b->unk0;
        while (*p++ != -1) {
            k++;
        }
        b->unk4 = (s32 *)((u8 *)b->unk0 + k * 4);
        count = 0;
        sum = 0;
        if (b->unk0[0] != -1) {
            do {
                b->unk4[count] = (s32)b->unk4 + k * 4 + sum * 2;
                sum += b->unk0[count];
                count++;
            } while (b->unk0[count] != -1);
        }
        *arg2 = b;
    }
    if (arg3 != NULL) {
        if (arg2 == NULL) {
            *arg3 = arg0->unk1C + count;
        } else {
            *arg3 = b->unk4 + count;
        }
    }
    return 1;
}

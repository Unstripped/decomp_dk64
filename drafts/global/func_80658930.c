// func_80658930 (src/global/55B20.c): only diff: target hoists &D_807F70B8 to s6 and spills n to 0x46; draft rematerialises base and colours n to s8 (uopt colouring tie-break)
// func_80658930: loop body matches the target instruction-for-instruction; only
// (a) the target keeps &D_807F70B8 in $s6 (LICM hoist) while this draft rematerialises
// it inside the loop, and (b) the target spills n to its stack slot 0x46 while this
// draft colours n to $s8. Both are one uopt colouring tie-break apart.
typedef struct M55P7Node {
    /* 0x00 */ u8 *unk0;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ u8 pad6[0x2];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 padC[0x2];
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ u8 unk14[0x20];
    /* 0x34 */ s8 unk34;
    /* 0x35 */ u8 pad35;
    /* 0x36 */ u8 unk36[0x20];
    /* 0x56 */ s8 unk56;
    /* 0x57 */ u8 pad57;
    /* 0x58 */ u8 unk58[0x10];
    /* 0x68 */ s8 unk68;
} M55P7Node;

extern u8 *D_807F70B8[];
void *heapAlloc(s32);
void func_80651708(s32);

void func_80658930(u8 *arg0) {
    s32 *w;
    s32 *end;
    u8 **base;
    s16 n;
    s32 i;
    s16 idx;
    u8 *p;

    end = (s32 *)&D_807F7138;
    w = (s32 *)D_807F70B8;
    do {
        *w++ = 0;
    } while (w < end);
    base = D_807F70B8;
    if (arg0 == NULL) {
        return;
    }
    n = *(s16 *)arg0;
    p = arg0 + 2;
    for (i = 0; i < n; i++) {
        idx = *(s16 *)p;
        p += 2;
        base[idx] = heapAlloc(0x6C);
        ((M55P7Node *)base[idx])->unk10 = 0x7FFF;
        ((M55P7Node *)base[idx])->unk12 = -0x8000;
        ((M55P7Node *)base[idx])->unk8 = 0;
        ((M55P7Node *)base[idx])->unk4 = *(s16 *)(p - 2);
        ((M55P7Node *)base[idx])->unk0 = heapAlloc((u32)((M55P7Node *)base[idx])->unk4 * 6);
        memcpy(((M55P7Node *)base[idx])->unk0,
               p,
               (u32)((M55P7Node *)base[idx])->unk4 * 6);
        p += ((u32)((M55P7Node *)base[idx])->unk4 * 6 / 2) * 2;
        ((M55P7Node *)base[idx])->unkE = *(s16 *)p;
        ((M55P7Node *)base[idx])->unk34 = (s8)*(s16 *)(p + 2);
        p += 4;
        memcpy(((M55P7Node *)base[idx])->unk14, p, 0x20);
        ((M55P7Node *)base[idx])->unk56 = (s8)*(s16 *)(p + 0x20);
        p += 0x22;
        memcpy(((M55P7Node *)base[idx])->unk36, p, 0x20);
        ((M55P7Node *)base[idx])->unk68 = (s8)*(s16 *)(p + 0x20);
        p += 0x22;
        memcpy(((M55P7Node *)base[idx])->unk58, p, 0x10);
        p += 0x10;
        func_80651708(idx);
    }
}

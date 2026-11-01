// mapNodeAssetParse (src/global/55B20.c): leftovers5 MapA: stage 6 (parked NON_MATCHING), full=2 unchanged (li s8,-32768 must be the first preheader record: target [li s8 | la s6, sh n | li s7, li s4], ours [la s6, sh n | li s8, li s7, li s4]; the three li's are emitted in descending register order after the code-motion hoisted la/sh, so -0x8000 would have to be hoisted by code motion before the la). Tried (MapA): 12880 random 1-3 dead compare insertions (13 constants x 6 ops x 8 vars, random positions): floor stays 2, 569 variants at 2, none at 0-1.
extern s16 D_807F7138;
extern void *D_807F70B8[];
void mapFaceBuildTriangleFan(s32);
typedef struct S55fNodeData {
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
} S55fNodeData;

#define S55fNodeSlot(i) (*(S55fNodeData **)((s32)D_807F70B8 + (i) * 4))
void mapNodeAssetParse(u8 *arg0) {
    s32 *w;
    s32 *end;
    s16 n;
    s32 i;
    s16 idx;
    u8 *p;
    s32 slot;

    w = (s32 *)D_807F70B8; end = (s32 *)&D_807F7138; // FAKE: same-line statements steer lui/addiu scheduling
    do {
        *w++ = 0;
    } while (w < end);
    if (arg0 == NULL) {
        return;
    }
    n = *(s16 *)arg0;
    p = arg0 + 2;
    for (i = 0; i < n; i++) {
        idx = *(s16 *)p;
        p += 2;
        S55fNodeSlot(idx) = heapAlloc(0x6C);
        S55fNodeSlot(idx)->unk10 = 0x7FFF;
        S55fNodeSlot(idx)->unk12 = -0x8000;
        S55fNodeSlot(idx)->unk8 = 0;
        S55fNodeSlot(idx)->unk4 = *(s16 *)p;
        p += 2;
        slot = (s32)D_807F70B8 + idx * 4;
        (*(S55fNodeData **)slot)->unk0 = heapAlloc((u32)(*(S55fNodeData **)slot)->unk4 * 6);
        memcpy((*(S55fNodeData **)slot)->unk0, p, (u32)(*(S55fNodeData **)slot)->unk4 * 6);
        p += ((u32)(*(S55fNodeData **)slot)->unk4 * 6 / 2) * 2;
        (*(S55fNodeData **)slot)->unkE = *(s16 *)p;
        (*(S55fNodeData **)slot)->unk34 = (s8)*(s16 *)(p + 2);
        p += 4;
        memcpy((*(S55fNodeData **)slot)->unk14, p, 0x20);
        (*(S55fNodeData **)slot)->unk56 = (s8)*(s16 *)(p + 0x20);
        p += 0x22;
        memcpy((*(S55fNodeData **)slot)->unk36, p, 0x20);
        (*(S55fNodeData **)slot)->unk68 = (s8)*(s16 *)(p + 0x20);
        p += 0x22;
        memcpy((*(S55fNodeData **)slot)->unk58, p, 0x10);
        p += 0x10;
        mapFaceBuildTriangleFan(idx);
    }
}
#undef S55fNodeSlot

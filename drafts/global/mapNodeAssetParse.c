// mapNodeAssetParse (src/global/55B20.c): W2SchedA: stage 6, full=2 unchanged. Re-tried: decl-order x assignment-order x var-set grid for lo/hi/tbl vars (3-var variants shape 14, lo-only 7, none 2), constant spelling grid (-0x8000/(s16)-0x8000/~0x7FFF... x 0x7FFF/32767/...: all 2), dead tests of -0x8000 against n/i/idx/slot/w/end/p at every statement boundary (3000 variants: all >= 2), earlier placement of 'lo = -0x8000;' (function top, before w=, before arg0 check: const-propagated, 2), annealing from the lo variant (12k evals) falls back to 2. Observation: target puts 'li s8' BEFORE the blez (as1 moves it into the blez delay slot), i.e. its web is inserted in the loop-GUARD block while la/sh/li s7/li s4 are in the preheader proper; a source-level 'lo' var reproduces that placement but a var always outranks const webs in colouring (adjsave 7.75 vs 3.67/3.33). || PREVIOUS: mapNodeAssetParse (src/global/55B20.c): W3SchedA: stage 6 (parked NON_MATCHING), full=2 unchanged: li s8,-32768 must be the first preheader record (target stream [li fp | la s6, sh n | li s7, li s4] = allocator inserts consts in reverse colouring order and la too; ours code-motion hoists la first). as1probe: any stream with li fp before la (or right after 'move s5,zero') matches exactly. NEW: a real var 'i = 0; lo = -0x8000; for (; i < n; i++) { ...unk12 = lo; ...; lo = lo | 0; }' (s32 lo, in-loop no-code def blocks const-prop) puts li in the blez delay slot exactly (shape 0) but lo (adjsave 7.75 = i) is coloured before la (3.67)/0x7FFF (3.33): regs rotate s6/s7/s8 (7 lines); need lo adjsave < 3.33 (dead nested tests, hi/tbl vars, other no-op placements, 1872 deadsweep forms did not lower it). Also tried: casts/operand order of the table address, array/ixa spellings (all worse), (s16)0x8000 spellings (fold).
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

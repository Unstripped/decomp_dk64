// mapNodeAssetParse (src/global/55B20.c): mapNodeAssetParse (src/global/55B20.c): stage 6 (parked NON_MATCHING), full=2: as1 stream is [la s6, sh n,70(sp), li s8=-32768, li s7, li s4] but target is [li s8 (blez delay slot), la, sh, li s7, li s4]. W3Near 2026-11-01 (stream-level: .scratch/W3Near/n1..n4.py): permuting the 5 preheader records at the as1 level gives an EXACT match for 7 orders, all with li -32768 before the lui s6 (or sh,li,la); as1 puts the FIRST post-branch instruction in the delay slot, so the original ugen stream had li s8 first (li s8 live from BB5 start, or in BB4 before blez). Source-level levers tried this round (no change): 12 spellings of the -0x8000 store constant (typed/cast/~0x7FFF/0x8000), a named lo local (s32/s16/u16/s8 = only changes frame/regs), two defs, if/else defs, for-init comma def; 2520 dead compares before the loop ((s32|u32)arg0/p/w/end/i/n/D_807F70B8/D_807F7138 x {==,!=,<,>} x 5 constant spellings x 6 anchors): best stays 2, none puts li before lui s6; compares on n move n to a saved reg (full 42). Descending-register emission of hoisted li (s8,s7,s4) is consistent with swap experiment (7FFF first in source -> li s7 first). Untried: a genuine second use of -0x8000 that costs no code.
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

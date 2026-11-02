// renderEntryListSortByDistance (src/global/35000.c): renderEntryListSortByDistance (src/global/35000.c): renderEntryListSortByDistance (src/global/35000.c): stage 5, 5 -> 1 insn diff. 'cur->unk18 = cur->unk18;' (FAKE) inside 'if (node != NULL) {' before 'node->unk18 = cur->unk18;' advances the ugen t-ring one step: final inserted==0 block now t7,t8,t9 exact; the self-store emits one extra 'sw t5,24(a1)'. Tried (no gain): x=x / x=x&MASK / |0 / *1 / shift chains / pointer casts on every local and field at every statement boundary, junk locals (s32/u8/s16/u16), inserted type+mask variants, while/for loop forms, tmp copies of cur->unk18, field-spelling (raw *(T*)(base+off)) grid, permuter 12k iterations (best stays 30), deadsweep sweeps. Self-stores elsewhere (before overwritten store) are dead-store-eliminated with no ring effect. || W3IntC 2026-11-02 (still 1 insn: extra 'sw t5,24(a1)' from the self-store FAKE; without FAKE 5 = last inserted==0 block t6,t7,t8 vs target t7,t8,t9, hole is one t-ring step between block-1 (t4,t5) and that block). Tried: ~60k evals: random grids + 2 annealers (40-60 dead forms: x=x, |0, &0xFF, *1, ^0, +0, &0xFFFFFFFF, if(x){} on locals/fields, junk locals j1/j2/j3 incl. const-defs) at every statement boundary; all 15 x 3 valid statement permutations of the two merge blocks; 'inserted' as s32/u8/s8/u16/s16/u32; 15 spellings of 'inserted = 1' (!x, ++, ==0, +=1, cmp). Only real-code forms (inserted & 0xFF) reach t7,t8,t9 (2 diff: extra andi t6/move a2,t6).
typedef struct RenderEntry RenderEntry;
struct RenderEntry {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ RenderEntry *unk14;
    /* 0x18 */ RenderEntry *unk18;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ u8 unk22;
    /* 0x23 */ u8 unk23;
    /* 0x24 */ u8 unk24;
    /* 0x25 */ u8 pad25[3];
};

RenderEntry *renderEntryListSortByDistance(RenderEntry *arg0, f32 arg1, f32 arg2, f32 arg3, RenderEntry **arg4) {
    RenderEntry *node;
    f32 dx;
    f32 dy;
    f32 dz;
    RenderEntry *head;
    RenderEntry *cur;
    RenderEntry *ins;
    RenderEntry *base;
    s32 inserted;
    f32 dist;
    f32 cmpB;

    dist = 0.0f;
    node = arg0;
    head = arg0;
    *arg4 = NULL;
    base = arg0;
    if (base != NULL) {
        do {
            dx = node->unk4 - arg1;
            dy = node->unk8 - arg2;
            dz = node->unkC - arg3;
            if (node->unk10 != -1.0) {
                node->unk10 = sqrtf(dx * dx + dy * dy + dz * dz);
            }
            node = node->unk14;
        } while (node != NULL);
    }
    if (base != NULL) {
        if (base->unk10 < base->unk1C || base->unk1C == -2) {
            *arg4 = base;
            if (base->unk1C == -2) {
                dist = 9999.0f;
            } else {
                dist = base->unk10;
            }
        }
        cur = base->unk14;
        if (cur != NULL) {
            do {
                inserted = 0;
                if ((dist < cur->unk10 && cur->unk10 < cur->unk1C) || cur->unk1C == -2) {
                    *arg4 = cur;
                    if (cur->unk1C == -2) {
                        dist = 9999.0f;
                    } else {
                        dist = cur->unk10;
                    }
                }
                dz = (f32)((cur->unk1C < cur->unk10) ? 9999.0 : cur->unk10);
                ins = cur->unk18;
                if (ins != NULL) {
                    do {
                        cmpB = (f32)((ins->unk1C < ins->unk10) ? 9999.0 : ins->unk10);
                        if (dz <= cmpB || cur->unk1C == -2) {
                            inserted = 1;
                            if (ins != cur->unk18) {
                                cur->unk18->unk14 = cur->unk14;
                                node = cur->unk14;
                                if (node != NULL) {
                                    cur->unk18 = cur->unk18; // FAKE: advances the ugen t-ring one step (extra sw left)
                                    node->unk18 = cur->unk18;
                                }
                                node = ins->unk14;
                                ins->unk14 = cur;
                                cur->unk14 = node;
                                if (node != NULL) {
                                    node->unk18 = cur;
                                }
                                cur->unk18 = ins;
                            }
                        }
                        ins = ins->unk18;
                    } while (ins != NULL && inserted == 0);
                }
                if (inserted == 0) {
                    cur->unk18->unk14 = cur->unk14;
                    if (cur->unk14 != NULL) {
                        cur->unk14->unk18 = cur->unk18;
                    }
                    cur->unk18 = NULL;
                    cur->unk14 = head;
                    head->unk18 = cur;
                    head = cur;
                }
                cur = cur->unk14;
            } while (cur != NULL);
        }
    }
    return head;
}

// func_80625C30 (src/global/201B0.c): stage 5: semantics decoded (min/max bounds, 400-grid snap, insertion sort of {idx,key} pairs by key then entry.unk18, group table). Only diff: 7 fewer insns - target has extra index copies (move s2,s0 before sll in loop1; move a0,t5 / move a0,t6 in sort loop; load order key before idx). Tried j copies, pointer-arith, off var, for/break loop.
typedef struct CamE3Pair {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 unk2;
} CamE3Pair;

typedef struct CamE3Ent {
    /* 0x00 */ u8 pad0[0x18];
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 pad19[3];
} CamE3Ent; // size = 0x1C

typedef struct CamE3Path {
    /* 0x00 */ u8 pad0[0xC0];
    /* 0xC0 */ s16 unkC0;
    /* 0xC2 */ u8 padC2[2];
    /* 0xC4 */ CamE3Ent *unkC4;
} CamE3Path;

void *heapAlloc(s32);
void heapFree(void *);

#define CAME3_PATH ((CamE3Path *)D_807476FC)
#define CAME3_SORT ((CamE3Pair *)D_80747704)
#define CAME3_GROUP ((CamE3Pair *)D_807476C0)

void func_80625C30(void) {
    s16 i;
    s16 j;
    s16 k;
    s16 key;
    s16 idx;

    func_80625B3C(&D_807F5CD2, &D_807F5CD6, &D_807F5CD4);
    D_807F5CD6 = D_807F5CD6 / 400 * 400 + 400;
    D_807F5CD2 = D_807F5CD2 / 400 * 400;
    D_807F5CD8 = (D_807F5CD6 - D_807F5CD2) / 400;
    D_807F5CD4 = D_807F5CD4 / 400 * 400;
    if (D_80747704 != NULL) {
        heapFree(D_80747704);
    }
    D_80747704 = heapAlloc(CAME3_PATH->unkC0 * 4 + 4);
    for (i = 0; i < CAME3_PATH->unkC0; i++) {
        CAME3_SORT[i].unk0 = i;
        CAME3_SORT[i].unk2 = func_80625A80(i);
    }
    for (i = 1; i < CAME3_PATH->unkC0; i++) {
        key = CAME3_SORT[i].unk2;
        idx = CAME3_SORT[i].unk0;
        j = i;
        while (j > 0 &&
               (key < CAME3_SORT[j - 1].unk2 ||
                (key == CAME3_SORT[j - 1].unk2 &&
                 CAME3_PATH->unkC4[CAME3_SORT[j - 1].unk0].unk18 < CAME3_PATH->unkC4[CAME3_SORT[j].unk0].unk18))) {
            CAME3_SORT[j].unk0 = CAME3_SORT[j - 1].unk0;
            CAME3_SORT[j].unk2 = CAME3_SORT[j - 1].unk2;
            j--;
        }
        if (j != i) {
            CAME3_SORT[j].unk0 = idx;
            CAME3_SORT[j].unk2 = key;
        }
    }
    D_807F5CDA = 1;
    for (i = CAME3_PATH->unkC0 - 1; i > 0; i--) {
        if (CAME3_SORT[i].unk2 != CAME3_SORT[i - 1].unk2) {
            D_807F5CDA++;
        }
    }
    if (D_807476C0 != NULL) {
        heapFree(D_807476C0);
    }
    D_807476C0 = heapAlloc(D_807F5CDA * 4 + 4);
    CAME3_GROUP[0].unk0 = CAME3_SORT[0].unk2;
    CAME3_GROUP[0].unk2 = 0;
    k = 1;
    for (i = 1; i < CAME3_PATH->unkC0; i++) {
        if (CAME3_SORT[i].unk2 != CAME3_SORT[i - 1].unk2) {
            CAME3_GROUP[k].unk0 = CAME3_SORT[i].unk2;
            CAME3_GROUP[k].unk2 = i;
            k++;
        }
    }
    CAME3_GROUP[k].unk0 = -1;
    CAME3_GROUP[k].unk2 = CAME3_PATH->unkC0;
}

// func_8072E868 (src/global/1332B0.c): regalloc only (score 910): dead 'if (0) {}' after 'e = D_80755A14->entries;' fixes e/j s2/s1; left: loop1 limit v1/value a0 (mine a0/v1), hook fn-ptr v0 (mine v1), flag scheduling. Permuter hints: flag reuse as k + 'j++; j--' (575 but leaves addiu 0).
#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern ActorGlobalState D_807FBB70;

typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ u8 unkC;
    /* 0x0D */ u8 unkD;
    /* 0x0E */ u8 unkE;
    /* 0x0F */ u8 padF;
    /* 0x10 */ struct { s16 unk0; u8 unk2[8]; } subs[4];
    /* 0x38 */ u8 unk38;
    /* 0x39 */ u8 unk39;
} F1Entry; // size = 0x3A

typedef struct {
    /* 0x00 */ s16 count;
    /* 0x04 */ F1Entry *entries;
} F1Table;

extern F1Table *D_80755A14;
void *heapAlloc(s32);

extern F1Table *D_80755A14;
typedef struct {
    /* 0x00 */ u8 pad0[2];
    /* 0x02 */ s16 unk2;
    /* 0x04 */ u8 pad4[3];
    /* 0x07 */ u8 unk7;
    /* 0x08 */ Actor *unk8;
    /* 0x0C */ s32 (*unkC)(void);
} F1Hook; // size = 0x10

extern F1Hook D_807557A0[];
void *assetLoad(s32, s32, s32, s32);
s32 assetFreeBuffer(void *, s32, s32);
s32 actorFindActiveByType(s16, Actor **);


extern u8 D_807FBDC4;
extern s16 D_807FDCB8;
extern s16 D_807FDCBA;
extern s16 D_807FDCBC;
void func_8067AB20(void *, void *, s32, s32, void *, s32);
s32 volumeTriggerUpdate(F1Entry *);
s32 volumeTriggerSetEnabled(s32, u8);

void func_8072E868(void) {
    s32 ua0;
    s32 ua1;
    s32 i;
    F1Entry *e;
    s16 *ptr;
    s32 j;
    s32 flag;
    s32 k;

    for (k = 0; k < D_807FBDC4; k++) {
        ptr = D_807FBB70.unk278[k];
        switch (D_807FBB70.unk258[k]) {
            case 1:
                volumeTriggerSetEnabled(*ptr, 1);
                break;
            case 2:
                volumeTriggerSetEnabled(*ptr, 0);
                break;
        }
    }
    e = D_80755A14->entries;
    if (0) {
    }
    for (i = 0; i < D_80755A14->count; i++, e++) {
        if (volumeTriggerUpdate(e)) {
            for (j = 0; j < e->unkE; j++) {
                if (D_807557A0[e->subs[j].unk0].unkC == NULL || D_807557A0[e->subs[j].unk0].unkC()) {
                    flag = 0;
                    if ((u16)D_807557A0[e->subs[j].unk0].unk2 == 0xA) {
                        flag = 1;
                    }
                    func_8067AB20(D_807FBB40, D_807557A0[e->subs[j].unk0].unk8, 0x01000000, D_807557A0[e->subs[j].unk0].unk7, e->subs[j].unk2, flag);
                    D_807FDCB8 = e->unk0;
                    D_807FDCBA = e->unk2;
                    D_807FDCBC = e->unk4;
                }
            }
        }
    }
}

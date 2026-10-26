// func_8072EC94 (src/global/1332B0.c): // func_8072EC94 (src/global/1332B0.c): regalloc only: target found=v0,e=v1,table=a2,i=a3,count=t0; ours e=v0,table=v1,found=a2. uopt priority order must be found>e>table; tried decl orders, loop forms, types, extra uses of found. Permuter no valid hit.
#include "common.h"
#include "actor.h"

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
void *func_80610FE8(s32);

extern F1Table *D_80755A14;

s32 func_8072EC94(s32 arg0, u8 arg1) {
    F1Entry *e = D_80755A14->entries;
    s32 found = 0;
    s32 i;

    for (i = 0; i < D_80755A14->count && !found; i++, e++) {
        if (arg0 == e->unkA) {
            e->unk39 = arg1;
            found = 1;
        }
    }
    return found;
}

// func_8072ECFC (src/global/1332B0.c): // func_8072ECFC (src/global/1332B0.c): regalloc only (same as EC94): target table=t0,found=v0,e=v1,i=t1,count=t2; ours table=v1,e=v0,found=t0 + trailing move v0,t0. arg0 is s32 (a0 compared unextended), arg1-3 s16.
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

s32 func_8072ECFC(s32 arg0, s16 arg1, s16 arg2, s16 arg3) {
    F1Entry *e = D_80755A14->entries;
    s32 found = 0;
    s32 i;

    for (i = 0; i < D_80755A14->count && !found; i++, e++) {
        if (arg0 == e->unkA) {
            e->unk0 = arg1;
            e->unk2 = arg2;
            e->unk4 = arg3;
            found = 1;
        }
    }
    return found;
}

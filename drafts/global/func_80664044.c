// func_80664044 (src/global/68AA0.c): Stage 5/6: frame 0x48 + callee-saved set s0-s6 match; remaining 13 text diffs: P=D_807F9420 value lives in v0 (expected a3), entry add operand order (s2,P vs P,s2), compare order bne a2,v0 vs bne v0,a2, j=0/found=0 placement vs bne. deadsweep `if (D_807F9420 == 0) {}` took 30 -> 13 (fixes s4/s5/s6 arg/&D regalloc swap). Tried: j=0 hoisted before if, entry = D+i, while(1)/for forms, s8/u8 j/found, decl order, operand order, 12 more deadsweep forms; permuter 4 min no gain.
#include "common.h"
#include "actor.h"

typedef struct ActorTargetEntry {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    u8 unk6;
    union {
        struct {
            s8 unk7;
            s8 pad8[4];
        } s;
        s8 unk7_arr[5];
    } u;
} ActorTargetEntry;

extern ActorTargetEntry *D_807F9420;
extern s16 D_807F9424;

typedef struct ColSmall_Sched {
    u8 pad0[0x290];
    s16 unk290;
} ColSmall_Sched;

extern ColSmall_Sched *D_807FC924;

f32 sfxUpdateDistanceVolumeAndPan(f32, f32, f32, u8, u8, f32);

void func_80664044(u8 arg0, u8 arg1, u8 arg2, f32 arg3) {
    ActorTargetEntry *entry;
    s32 i;
    s32 j;
    s32 found;

    for (i = 0; i < D_807F9424; i++) {
        entry = &D_807F9420[i];
        if (entry->unk6 == arg0) {
            if (D_807F9420 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            j = 0;
            found = 0;
            do {
                if (D_807F9420[i].u.unk7_arr[j] == D_807FC924->unk290) {
                    found = 1;
                }
                j++;
                if (j >= 5 || found) {
                    break;
                }
            } while (D_807F9420[i].u.unk7_arr[j] != -1);

            if (found) {
                sfxUpdateDistanceVolumeAndPan(entry->unk0, entry->unk2, entry->unk4, arg1, arg2, arg3);
            }
        }
    }
}

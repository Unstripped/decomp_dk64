// func_8072E7DC (src/global/1332B0.c): // func_8072E7DC (src/global/1332B0.c): regalloc only: count in a2/ptr a1/actor a0/arg a3 vs target count a0/actor a1/ptr a2/arg t0; target keeps unfolded 'sll t7,zero,3' for ptr init (i*8 with i=0). Tried do/while vs while/for, i init forms, count local.
#include "common.h"
#include "actor.h"

typedef struct {
    /* 0x0 */ Actor *actor;
    /* 0x4 */ s32 unk4;
} F1ActorEntry;

extern F1ActorEntry gActiveActors[];
extern u16 gActiveActorCount;

s32 func_8072E7DC(s16 arg0, Actor **arg1) {
    s32 found = 0;
    s32 i = 0;
    Actor *actor;

    if (gActiveActorCount > 0) {
        do {
            actor = gActiveActors[i].actor;
            if (actor->unk58 == arg0) {
                found = 1;
            } else {
                i++;
            }
        } while (!found && i < gActiveActorCount);
    }
    *arg1 = actor;
    return found;
}

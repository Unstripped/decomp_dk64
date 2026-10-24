#include "common.h"
#include "actor.h"

#pragma GLOBAL_ASM("asm/global/nonmatchings/A7710/func_806A2A10.s")

void func_806A2B08(Actor *actor) {
    actor->unk154 = 2;
    actor->unk155[0] = 0;
    actor->unk128 = 0xFF;
}

void func_806A2B20(Actor *actor) {
    if (actor != NULL) {
        actor->unk154 = 1;
        actor->unk155[0] = 0;
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/A7710/func_806A2B38.s")

void func_806A2B80(Actor *actor) {
    actor->unk154 = 3;
    actor->unk155[0] = 0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/A7710/func_806A2B90.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/A7710/func_806A2E30.s")

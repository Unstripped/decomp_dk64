// func_80697988 (src/global/9BF30.c): stage 6: structure matches, 214/217 insns; remaining diff: D_807FBB40 is loaded into a1 then 'move s0,a1' (expected loads straight into s0) and the (temp>32.0) clip folds to li 32 where expected emits trunc.w.d of the comparison's double 32.0; regression attempts: pure macro form hoists &D_807FBB40 into s1 (v2/v3, 212), macro RMW 221; also try removing all cross-call liveness of the actor pointer
typedef struct M9B_ActorState {
    s16 unk0;
    u8 pad2;
    u8 pad3;
    u8 *unk4;
    f32 unk8;
    f32 unkC;
    u8 unk10;
    u8 unk11;
} M9B_ActorState;

extern Actor *D_807FBB40;
Gfx *func_80697230(Gfx *, Actor *);
f32 func_80612790(s16);
f32 func_80612794(s16);
void sfxPlayActorSound(Actor *, s32, s32, s32, s32, s32, f32, s32);
void actorDespawn(Actor *);
void heapFree(void *);
void projectileSpawnActor107(u8, u8, f32, f32, u8, u8);
void renderCallbacksRegister(void *, void *, u8);

#define ACTOR2 ((Actor *)D_807FBB40)

void func_80697988(void) {
    M9B_ActorState *sub;
    Actor *actor;
    f64 temp;

    actor = D_807FBB40;
    sub = actor->unk174;
    if (!(actor->unk60 & 0x10)) {
        *(s16 *)((u8 *)actor + 0xEE) = actor->unk15F;
        sub->unk4 = func_80610FE8(0x1000);
        actor = D_807FBB40;
        if (actor->unk15F != 0) {
            actor->unk144 = 0x24;
            actor = D_807FBB40;
        }
        if (sub->unk11 == 1) {
            sfxPlayActorSound(actor, 0x128, 1, 1, 0, 0xFF, 0.2f, 0);
            sfxPlayActorSound(D_807FBB40, 0x139, 0x3C, 1, 1, 0xFF, 1.0f, 0);
            actor = D_807FBB40;
        }
    }
    if (sub->unk11 != 0) {
        if (sub->unk11 == 1) {
            actor = D_807FBB40;
            actor->unk7C = actor->unk7C + (sub->unkC * func_80612794(actor->unkE6));
            actor = D_807FBB40;
            actor->unk84 = actor->unk84 + (sub->unkC * func_80612790(actor->unkE6));
            actor = D_807FBB40;
            if (actor->unk15F != 0) {
                actor->unk15F -= 1;
            } else if (actor->unk168 == 0x20) {
                actor->unk168 = 0x10;
                sub->unk10 = 0;
            } else if (sub->unk10 >= 0x10) {
                heapFree(sub->unk4);
                actorDespawn(actor);
            }
        }
    } else {
        if (actor->unk15F != 0) {
            sub->unk8 += sub->unkC;
            temp = (f64)sub->unk8 * 0.3;
            if (temp > 32.0) {
                sub->unk0 = 32.0;
            } else {
                sub->unk0 = temp;
            }
        } else {
            sub->unk8 = sub->unk8 + (f32)((actor->unk168 - sub->unk10) + 0x10)
                * (sub->unkC * 0.0625);
        }
        actor = D_807FBB40;
        if ((sub->unk10 - actor->unk168) >= 0x10) {
            u8 count;

            count = actor->unk15F;
            actor->unk15F = count - 1;
            if (count) {
                projectileSpawnActor107(0, sub->unk0, sub->unk8, sub->unkC, 0, 0x10);
                if (ACTOR2->unk15F == 0) {
                    ACTOR2->unk168 = 0x10;
                } else {
                    sub->unk10 = 0;
                }
            } else {
                heapFree(sub->unk4);
                actorDespawn(actor);
            }
        }
    }
    renderCallbacksRegister(func_80697230, ACTOR2, 1);
}

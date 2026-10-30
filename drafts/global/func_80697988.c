// func_80697988 (src/global/9BF30.c): stage 6, size 0x368 (218 vs 217), 162-line asm-differ; remaining: (a) sub->unk11 lands in v0 where the target has a0 (both dispatch loads), (b) both 'mul.s' in the unk11==1 block come out with swapped commutative operands ($f0 first vs sub->unkC first), (c) the unk11==1 despawn wants a fresh lui/lw of D_807FBB40 instead of move a1,s0 + sw 48(sp), (d) 1 extra insn. Wins found: block A must use the D_807FBB40 macro (a local gets an a1->s0 copy per load); block B needs a local re-assigned after calls; 'max = 32.0' f64 local is what makes the (temp > 32.0) clip emit trunc.w.d of the comparison's double 32.0 instead of li 32; ACTOR2->unk7C/unk84 '+=' halves the diff (compound assignment), '=' + 'x + y' is worse
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
    f64 max;

    sub = ACTOR2->unk174;
    if (!(ACTOR2->unk60 & 0x10)) {
        *(s16 *)((u8 *)ACTOR2 + 0xEE) = ACTOR2->unk15F;
        sub->unk4 = heapAlloc(0x1000);
        if (ACTOR2->unk15F != 0) {
            ACTOR2->unk144 = 0x24;
        }
        if (sub->unk11 == 1) {
            sfxPlayActorSound(ACTOR2, 0x128, 1, 1, 0, 0xFF, 0.2f, 0);
            sfxPlayActorSound(ACTOR2, 0x139, 0x3C, 1, 1, 0xFF, 1.0f, 0);
        }
    }
    if (sub->unk11 != 0) {
        if (sub->unk11 == 1) {
            ACTOR2->unk7C += sub->unkC * func_80612794(ACTOR2->unkE6);
            ACTOR2->unk84 += sub->unkC * func_80612790(ACTOR2->unkE6);
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
        if (ACTOR2->unk15F != 0) {
            sub->unk8 += sub->unkC;
            temp = (f64)sub->unk8 * 0.3;
            max = 32.0;
            if (temp > 32.0) {
                sub->unk0 = max;
            } else {
                sub->unk0 = temp;
            }
        } else {
            sub->unk8 = sub->unk8 + (f32)((ACTOR2->unk168 - sub->unk10) + 0x10)
                * (sub->unkC * 0.0625);
        }
        if ((sub->unk10 - ACTOR2->unk168) >= 0x10) {
            u8 count;

            count = ACTOR2->unk15F;
            ACTOR2->unk15F = count - 1;
            if (count) {
                projectileSpawnActor107(0, sub->unk0, sub->unk8, sub->unkC, 0, 0x10);
                if (ACTOR2->unk15F == 0) {
                    ACTOR2->unk168 = 0x10;
                } else {
                    sub->unk10 = 0;
                }
            } else {
                heapFree(sub->unk4);
                actorDespawn(ACTOR2);
            }
        }
    }
    renderCallbacksRegister(func_80697230, ACTOR2, 1);
}

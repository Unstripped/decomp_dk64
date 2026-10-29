// func_806789E4 (src/global/7CA80.c): stage 4: 72 insns, frame 0x30, s0-s4/ra match; pointer clearing hoists D_807FBFE0 into v1 (12 insns) vs target 12 insns direct off at via %hi/%lo of D_807FBFE4/8
extern s32 (*D_8074C0A0[])(void);
extern u16 D_807FBB3C;
void func_80678CC8(Actor *);
void actorGlobalCallbacksDispatchAndFree();
void func_80678BBC(Actor *);
void func_80678B04(void);

void func_806789E4(void) {
    u16 i;
    Actor *actor;

    D_807FBFE0[1] = NULL;
    D_807FBFE0[0] = NULL;
    D_807FBFE0[2] = NULL;
    D_807FBFE0[3] = NULL;
    for (i = D_807FBB3C = 0; i < gActiveActorCount; i = (D_807FBB3C = ++i)) {
        actor = gActiveActors[i].actor;
        D_807FBB40 = actor;
        if (actor->unk64 & 2) {
            func_80678BBC(actor);
            D_8074C0A0[D_807FBB40->unk58]();
            func_80678CC8(D_807FBB40);
            actor = D_807FBB40;
        }
        if (actor->unk4 != NULL) {
            func_80614A64(actor);
        }
        i = D_807FBB3C;
    }
    actorGlobalCallbacksDispatchAndFree(1);
    func_80678B04();
}

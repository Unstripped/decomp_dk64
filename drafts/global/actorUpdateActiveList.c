// actorUpdateActiveList (src/global/7CA80.c): stage 5: 82 insns, frame 0x40, s0-s8/ra match, natural C (removed deadsweep), regalloc only (v0/v1 swap between i and gActiveActorCount)
extern void (*D_8074C0A0[])(void);
void func_80678BBC(Actor *);
void func_80678CC8(Actor *);
extern u16 D_807FBB3C;

void actorUpdateActiveList(u8 arg0) {
    u16 i;

    D_807FBB3C = 0;
    for (i = 0; i < gActiveActorCount; D_807FBB3C = ++i) {
        Actor *actor = gActiveActors[i].actor;
        D_807FBE08 = 0;
        D_807FBB40 = actor;
        if (arg0 == 1) {
            if (!(actor->unk60 & 0x100000)) {
                goto update;
            }
        }
        if (arg0 != 2 || !(D_807FBB40->unk60 & 0x100000)) {
            continue;
        }
update:
        func_80678BBC(D_807FBB40);
        D_8074C0A0[D_807FBB40->unk58]();
        func_80678CC8(D_807FBB40);
        i = D_807FBB3C;
    }
}

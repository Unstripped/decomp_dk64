// func_8067889C (src/global/7CA80.c): stage 5: 82 insns, frame 0x40, s0-s8/ra match, shape 0, score 19; regalloc only (v0/v1 swap between i and gActiveActorCount)
extern s32 (*D_8074C0A0[])(void);
void func_80678CC8(Actor *);
void func_80678BBC(Actor *);
extern u16 D_807FBB3C;

void func_8067889C(u8 arg0) {
    u16 i;

    for (i = D_807FBB3C = 0; i < gActiveActorCount; i = (D_807FBB3C = ++i)) {
        Actor *actor;
        if (D_8074C0A0 != 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        if (arg0 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        if (D_807FBB3C) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        if (D_807FBE08 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        actor = gActiveActors[i].actor;
        D_807FBE08 = 0;
        D_807FBB40 = actor;
        if (1 == arg0) {
            if (D_807FBB40 && D_807FBB40) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            if (!(actor->unk60 & 0x100000)) {
                goto update;
            }
        }
        if ((2 != arg0) || !(D_807FBB40->unk60 & 0x100000)) {
            continue;
        }
update:
        func_80678BBC(D_807FBB40);
        D_8074C0A0[D_807FBB40->unk58]();
        func_80678CC8(D_807FBB40);
        i = D_807FBB3C;
    }
    if (D_8074C0A0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
}

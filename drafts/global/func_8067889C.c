// func_8067889C (src/global/7CA80.c): stage 4: frame 0x40, s0-s7/fp match, register permutation between D_807FBB3C and arg0
extern void (*D_8074C0A0[])(void);
extern u16 D_807FBB3C;
void func_80678CC8(Actor *);

void func_8067889C(arg0)
u8 arg0;
{
    u16 i;
    Actor *actor;

    i = D_807FBB3C = 0;
    if (i < gActiveActorCount) {
        do {
            actor = gActiveActors[i].actor;
            D_807FBE08 = 0;
            D_807FBB40 = actor;
            if (1 == arg0) {
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
        } while ((D_807FBB3C = ++i) < gActiveActorCount);
    }
}

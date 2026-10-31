// func_806789E4 (src/global/7CA80.c): same as Reset: text 0-diff lines when TU defines D_807FBFE0[4] (bss carve 0x807FBFE0-0x807FBFF0); clearing loop is for (j=0;j<4;j++); main loop i = ++D_807FBB3C
extern u16 D_807FBB3C;
extern void (*D_8074C0A0[])(void);
void func_80678CC8(Actor *);
void func_80678BBC(Actor *);
void actorGlobalCallbacksDispatchAndFree();
void func_80678B04(void);

ActorCallbackNode *D_807FBFE0[4];
void func_806789E4(void) {
    s32 i;
    s32 j;

    for (j = 0; j < 4; j++) {
        D_807FBFE0[j] = NULL;
    }
    for (i = D_807FBB3C = 0; i < gActiveActorCount; i = ++D_807FBB3C) {
        D_807FBB40 = gActiveActors[i].actor;
        if (D_807FBB40->unk64 & 2) {
            func_80678BBC(D_807FBB40);
            D_8074C0A0[D_807FBB40->unk58]();
            func_80678CC8(D_807FBB40);
        }
        if (D_807FBB40->unk4 != NULL) {
            func_80614A64(D_807FBB40);
        }
    }
    actorGlobalCallbacksDispatchAndFree(1);
    func_80678B04();
}

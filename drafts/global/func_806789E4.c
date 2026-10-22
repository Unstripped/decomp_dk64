// func_806789E4 (src/global/7CA80.c): from .scratch/R3B/func_806789E4_best.c
extern void (*D_8074C0A0[])(void);
extern u16 D_807FBB3C;
extern ActorCallbackNode *D_807FBFE4;
extern ActorCallbackNode *D_807FBFE8;
extern ActorCallbackNode *D_807FBFEC;
void func_80678CC8(Actor *);
void func_806790F4(s32);

typedef struct R3B_Actor9E4 {
    u8 pad[0x64];
    u32 unk64;
} R3B_Actor9E4;

void func_806789E4(void) {
    u16 i;
    Actor *actor;

    D_807FBFE4 = NULL;
    (&D_807FBFE4)[-1] = NULL;
    D_807FBFE8 = NULL;
    (&D_807FBFE8)[1] = NULL;
    i = 0;
    D_807FBB3C = i;
    if (i < D_807FBB34) {
        do {
            actor = D_807FB930[i].actor;
            D_807FBB40 = actor;
            if (((R3B_Actor9E4 *)actor)->unk64 & 2) {
                func_80678BBC(actor);
                D_8074C0A0[D_807FBB40->unk58]();
                func_80678CC8(D_807FBB40);
                actor = D_807FBB40;
            }
            if (actor->unk4 != NULL) {
                func_80614A64(actor);
            }
            i = D_807FBB3C;
        } while ((D_807FBB3C = ++i) < D_807FBB34);
    }
    func_806790F4(1);
    func_80678B04();
}

// func_80618EE8 (src/global/19A00.c): stage 4: same frame/calls/data accesses; remaining register allocation differs (target holds D_807FBB44 address in v1 and temporary pointer in v0, candidate uses v0/a0)
typedef int s32;
typedef short s16;
typedef unsigned char u8;
typedef struct Actor Actor;
typedef struct P19e4ActorState {
    u8 pad0[0x34];
    s32 unk34;
} P19e4ActorState;
typedef struct P19e4ActorView {
    u8 pad0[0x58];
    s32 unk58;
    u8 pad5C[0x88];
    s16 unkE4;
    s16 unkE6;
    s16 unkE8;
    u8 padEA[4];
    s16 unkEE;
    u8 padF0[0x3C];
    s16 unk12C;
    u8 pad12E[0x46];
    u8 *unk174;
} P19e4ActorView;

void actorSpawn(s32, s16);
void func_80614F28(u8 *);
void func_8067B238(Actor *, Actor *, s32);
extern s16 D_80746E10[];
extern Actor *D_807FBB44;

void func_80618EE8(Actor *arg0) {
    actorSpawn(0x135, D_80746E10[((P19e4ActorView *)arg0)->unk58]);
    func_8067B238(D_807FBB44, arg0, ((P19e4ActorState *)arg0->unk4)->unk34);
    ((P19e4ActorView *)D_807FBB44)->unkE8 = ((P19e4ActorView *)arg0)->unkE8;
    ((P19e4ActorView *)D_807FBB44)->unkE4 = ((P19e4ActorView *)arg0)->unkE4;
    func_80614F28(((P19e4ActorView *)D_807FBB44)->unk174 + 6);
}

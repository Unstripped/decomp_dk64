// func_8070D8C0 (src/global/112080.c): stage 2: compilable structural reconstruction; instruction scheduling and local types remain.
typedef struct M112aLink { void *key; Actor *actor; void *entries; struct M112aLink *next; } M112aLink;
typedef struct M112aActorState { u8 pad0[0x54]; s32 value; } M112aActorState;
extern u8 D_807550CC; M112aLink *func_8070D754(void *); void func_8070D82C(void *, s32, u8);
void func_8070D8C0(Actor *arg0, s32 arg1, u8 arg2) { M112aLink *node = func_8070D754(arg0); ((M112aActorState *)node->actor->unk174)->value = D_807550CC; D_807550CC = 0; func_8070D82C(node, arg1, arg2); arg0->unk60 |= 0x2000000; }

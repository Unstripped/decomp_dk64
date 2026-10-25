// func_8070D8C0 (src/global/112080.c): stage 5: complete wrapper; only global-address/local register allocation remains
typedef struct S112dLink {
    void *key;
    Actor *actor;
    void *entries;
    struct S112dLink *next;
} S112dLink;

typedef struct S112dActorValueState {
    u8 pad0[0x54];
    u8 value;
} S112dActorValueState;

typedef struct S112dEntry {
    u16 id;
    u8 count;
    u8 pad3;
    struct S112dEntry *next;
} S112dEntry;

typedef struct S112dContainer {
    u8 pad0[4];
    Actor *actor;
    S112dEntry *entries;
} S112dContainer;

extern u8 D_807550CC;
extern void *func_8070D754(void *);
void func_8070D82C(S112dContainer *, u16, u8);

void func_8070D8C0(Actor *arg0, s32 arg1, u8 arg2) {
    S112dLink *node;
    u8 *value;

    node = func_8070D754(arg0);
    value = (u8 *)&D_807550CC;
    ((S112dActorValueState *)node->actor->unk174)->value = *value;
    *value = 0;
    func_8070D82C((S112dContainer *)node, arg1, arg2);
    arg0->unk60 |= 0x2000000;
}

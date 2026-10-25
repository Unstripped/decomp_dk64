// func_8070D754 (src/global/112080.c): stage 5: exact instruction shape except D_807FBB44 address and final state pointer register allocation
// stage 5: exact instruction shape except D_807FBB44 address and final state pointer register allocation
typedef struct S112dLink {
    void *key;
    Actor *actor;
    void *entries;
    struct S112dLink *next;
} S112dLink;

typedef struct S112dActorKeyState {
    u8 pad0[4];
    void *key;
} S112dActorKeyState;

extern void *D_807550C4;
extern void heapClearBlock(void *);
extern void actorSpawn(s32, s32, void *);

void *func_8070D754(void *arg0) {
    S112dLink **link;

    link = (S112dLink **)&D_807550C4;
    if ((*link != NULL) && ((*link)->key != arg0)) {
        do {
            link = &(*link)->next;
        } while ((*link != NULL) && ((*link)->key != arg0));
    }
    if (*link == NULL) {
        *link = func_80610FE8(0x10);
        heapClearBlock(*link);
        (*link)->key = arg0;
        actorSpawn(0x12B, 0, arg0);
        D_807FBB44->unk154 = 0;
        (*link)->actor = D_807FBB44;
        ((S112dActorKeyState *)D_807FBB44->unk174)->key = arg0;
    }
    return *link;
}

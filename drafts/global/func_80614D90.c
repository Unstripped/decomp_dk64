// func_80614D90 (src/global/19A00.c): stage 4; closest diff 450 (permuter): saved-register assignment and loop scheduling remain. Attempts: stored m2c reconstruction; typed state/table layout; do-while loop; truthy versus NULL guard; 600-second permuter search.
typedef int s32;
typedef unsigned char u8;
typedef struct Actor { void *unk4; } Actor;
typedef s32 (*Perm2bD90Command)(Actor *);
typedef struct Perm2bD90State {
    u8 pad0[0x68];
    u8 *unk68;
    u8 *unk6C;
    void (*unk70)(Actor *);
    u8 *unk74;
    s32 unk78;
} Perm2bD90State;
extern u8 *D_807F5AF0;
extern s32 D_807F5AF4;
extern Perm2bD90Command D_80746BEC[];

void func_80614D90(Actor *arg0) {
    s32 result;
    Perm2bD90State *state;

    state = (Perm2bD90State *)arg0->unk4;
    if (state->unk68) {
        D_807F5AF4 = 1;
        D_807F5AF0 = state->unk6C;
        if (state->unk78 == 0) {
            do {
                result = D_80746BEC[*D_807F5AF0](arg0);
                D_807F5AF4 = result;
            } while ((state->unk78 == 0) && (result != 0));
        }
        state->unk6C = D_807F5AF0;
        if (state->unk70 != NULL) {
            D_807F5AF0 = state->unk74;
            state->unk70(arg0);
        }
    }
}

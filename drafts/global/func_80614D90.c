// func_80614D90 (src/global/19A00.c): stage 4: clean typed state; 0x30 frame matches, loop entry guard and s0-s4 regalloc diff
typedef s32 (*RvG_ScriptCommand)(Actor *);
extern RvG_ScriptCommand D_80746BEC[];

typedef struct RvG_ScriptState {
    u8 pad0[0x68];
    u8 *unk68;
    u8 *unk6C;
    void (*unk70)(Actor *);
    u8 *unk74;
    s32 unk78;
} RvG_ScriptState;

void func_80614D90(Actor *arg0) {
    s32 result;
    RvG_ScriptState *state;

    result = 1;
    state = (RvG_ScriptState *)arg0->unk4;
    if (state->unk68 != NULL) {
        D_807F5AF4 = 1;
        D_807F5AF0 = state->unk6C;
        while ((state->unk78 == 0) && (result != 0)) {
            result = D_80746BEC[*D_807F5AF0](arg0);
            D_807F5AF4 = result;
        }
        state->unk6C = D_807F5AF0;
        if (state->unk70 != NULL) {
            D_807F5AF0 = state->unk74;
            state->unk70(arg0);
        }
    }
}

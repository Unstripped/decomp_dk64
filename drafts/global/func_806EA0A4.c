// func_806EA0A4 (src/global/E4090.c): Stage 6: only diff is target 'or a1,a0,zero; slt at,v0,a1' vs mine 'slt at,v0,a0' (uopt copy of max into a1 never emitted). Tried u8/s32/u16 max+cur, lim/arg1 copies (copy-propagated away), K&R params (homes a0/a1 -> wrong), ternary, operand swaps, permuter 570s (best score 10 = same move). Uses s32 cur, state->unkEF != unkF0 operand order.
extern Struct807FD580 *D_807FD580;
extern u8 D_807FC929;
extern u16 D_807FD63C;
extern s32 D_807FBB64;
extern s32 D_807FBB68;
void func_8062217C();
void func_80609140(s32, s32, f32, f32, s32, s32);

typedef struct G31State {
    /* 0x00 */ u8 pad0[8];
    /* 0x08 */ u16 unk8;
    /* 0x0A */ u8 pad0A[0xA2];
    /* 0xAC */ u32 unkAC;
    /* 0xB0 */ s16 unkB0;
    /* 0xB2 */ s16 unkB2;
    /* 0xB4 */ f32 unkB4;
    /* 0xB8 */ f32 unkB8;
    /* 0xBC */ s16 unkBC;
    /* 0xBE */ u8 padBE[0x30];
    /* 0xEE */ u8 unkEE;
    /* 0xEF */ u8 unkEF;
    /* 0xF0 */ u8 unkF0;
    /* 0xF1 */ u8 unkF1;
    /* 0xF2 */ u8 padF2;
    /* 0xF3 */ u8 unkF3;
    /* 0xF4 */ u8 padF4[2];
    /* 0xF6 */ u8 unkF6;
    /* 0xF7 */ u8 padF7[5];
    /* 0xFC */ u8 unkFC;
} G31State;

typedef struct G31Player {
    /* 0x000 */ u8 pad0[0x104];
    /* 0x104 */ struct G31Link *unk104;
} G31Player;

typedef struct G31Link {
    /* 0x000 */ u8 pad0[0xB4];
    /* 0x0B4 */ f32 unkB4;
    /* 0x0B8 */ u8 padB8[0xBC];
    /* 0x174 */ G31State *unk174;
} G31Link;

#define G31_PAD(sym, T) (*(T *)((u8 *)&(sym) + D_807FC929 * 0x34))
#define G31_PLAYER ((G31Player *)D_807FD580)

void func_806EA0A4(void) {
    G31State *state;
    s32 max;
    s32 cur;

    state = G31_PLAYER->unk104->unk174;
    if ((D_807FBB64 & 1) && !(D_807FBB68 & 2)) {
        max = 2;
    } else {
        max = 3;
    }
    cur = state->unkEF;
    if ((cur != 0) && ((G31_PAD(D_807FD63C, u16) & 0xC) == 4) && ((max == state->unkEE) || (state->unkFC == 0))) {
        state->unkF0 = cur;
        if (cur < max) {
            state->unkEF = cur + 1;
        } else {
            state->unkEF = 1;
        }
        func_8062217C(G31_PLAYER->unk104, state->unkEF, &D_807FD580);
        state->unkEE = state->unkEF;
        if ((state->unkEF != state->unkF0) && ((state->unk8 == 0) || (state->unk8 >= 0x96)) && (state->unkF3 != 2)) {
            func_80609140(0x27, 0x7FFF, 63.0f, 1.0f, 0, 0);
        }
        state->unkF1 = 0xB;
        state->unkF6 = 0xF;
    }
}

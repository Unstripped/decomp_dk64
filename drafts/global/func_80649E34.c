// func_80649E34 (src/global/478F0.c): from .scratch/CsB8/func_80649E34_best.c
extern s16 D_807F6240[];
extern s16 D_807481F4[];
extern s16 D_807481F6[];
extern u8 D_80748212[];
void func_8064199C(void *, s16, s16);

typedef struct CsB8E34State {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ s32 unk4;
} CsB8E34State;

void func_80649E34(CsState *cs, s16 csId, s16 b, s16 c) {
    CsB8E34State *st;
    s32 found;
    s16 *p;
    u8 v;

    if (*(CsB8E34State **)cs == NULL) {
        st = func_80610FE8(8);
        *(CsB8E34State **)cs = st;
        st->unk0 = 0;
        st->unk4 = 0;
    }
    st = *(CsB8E34State **)cs;
    found = 0;
    p = D_807481F4;
    v = *((u8 *)cs + 0x49);
    if (v != st->unk4) {
        do {
            if (*p == v) {
                found = 1;
            } else {
                p++;
            }
        } while (found == 0);
        if ((u32)p < (u32)D_80748212) {
            func_806418E8(p[1], 0xA, 0);
            func_8064199C(((CsB8Slot *)D_807F6000)[hashTableLookup(D_807F6240[p[1]])].unk7C, 0, 0);
        }
        if ((u32)p >= (u32)D_807481F6) {
            func_806418E8(p[-1], 0x14, 0);
        }
        st->unk4 = v;
    }
}

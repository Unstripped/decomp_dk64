// func_80649FC0 (src/global/478F0.c): CsB9: text-identical, reloc only: D_807445B4 vs D_807445B0+0x4 (u64 D_807445B0). cs timer (CsB9Timer u64 last/duration/left/fired). Needs CsState*; unk4B[0] used.
typedef struct CsB9Timer {
    /* 0x00 */ u64 last;
    /* 0x08 */ s64 duration;
    /* 0x10 */ s64 left;
    /* 0x18 */ s64 fired;
} CsB9Timer; /* 0x20 */
extern u64 D_807445B0;
extern u64 osGetTime(void);
void heapFreeDeferred(void *);
void renderCallbacksRegister(void *, void *, s32);
void func_8068DBA4(void);

void func_80649FC0(CsState *cs, s16 csId, s16 b, s16 c) {
    CsB9Timer *t;
    u64 elapsed;

    if (*(CsB9Timer **)cs == NULL) {
        *(CsB9Timer **)cs = func_80610FE8(0x20);
        t = *(CsB9Timer **)cs;
        t->last = osGetTime();
        t->duration = b;
        t->left = 0;
        t->fired = 0;
    }
    t = *(CsB9Timer **)cs;
    t->last += D_807445B0;
    elapsed = (osGetTime() - t->last) * 64;
    t->left = t->duration - elapsed / 3000 / 1000000;
    if (t->fired == 0 && (u64)t->left < (u64)(s64)c) {
        t->fired = 1;
        cs->unk4B[0] = 0x14;
    }
    if (t->left == 0) {
        heapFreeDeferred(*(CsB9Timer **)cs);
        cs->unk4B[0] = 0x1E;
        *(CsB9Timer **)cs = NULL;
    }
    renderCallbacksRegister(func_8068DBA4, t, 5);
}

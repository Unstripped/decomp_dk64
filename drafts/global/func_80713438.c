// func_80713438 (src/global/117190.c): stage 5 (parked NON_MATCHING in 117190.c): instruction stream, frame 0x38 and slots identical; only register allocation differs: ours puts Gfx pointer temps in v0/v1 (target t0/t1), 4.0f in f12 (target f0), x in f8 (target f2 var). Needs 2.0f (not 2.0) so x*0.5*2.0f stays mul.d; R117D_WRITE_GFX(arg0++) like func_8071338C; y=418.0f local keeps mul.s unfolded; new_var2 s16 precompute on same line as first gfx write; deadsweep fakes on sp28/y; locals order sp34,sp30,y,sp28,new_var2,temp_ft4,temp_a0.
extern s16 D_80744490;
s32 heapAlloc(s32);
void heapFreeDeferred(void *);
s32 textGetStringWidth(s16, s32);
s32 strlen(char *);
s32 _sprintf(char *, const char *, ...);

void func_80713438(Gfx *arg0, u8 arg1) {
    s32 sp34;
    s32 sp30;
    f32 y;
    f32 sp28;
    s16 new_var2;
    f64 temp_ft4;
    s32 temp_a0;

    sp30 = (s32) func_8070E750(0xC, 1, 1);
    temp_a0 = strlen((char *) sp30) + 2;
    sp28 = (f32) ((f64) D_80744490 * 0.5 * 2.0f);
    y = 418.0f;
    sp34 = heapAlloc(temp_a0);
    heapFreeDeferred((void *) sp34);
    _sprintf((char *) sp34, "%c%s", 0x63, sp30);
    temp_ft4 = (f64) textGetStringWidth(1, sp34);
    temp_ft4 = 0.5 * temp_ft4;
    new_var2 = (s16) ((s32) (((f32) (((f64) sp28) - temp_ft4)) * 4.0f)); R117D_WRITE_GFX(arg0++, 0xE200001C, 0x504240);
    if (sp28 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    R117D_WRITE_GFX(arg0++, 0xFA000000, arg1);
    R117D_WRITE_GFX(arg0++, 0xFCFF97FF, 0xFF2CFE7F);
    if (y && y) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    textDrawStringVtx(arg0, 1, new_var2, (s16) ((s32) (y * 4.0f)), (void *) sp34, 4);
}

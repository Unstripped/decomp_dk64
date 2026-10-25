// func_80714060 (src/global/117190.c): Stage 2: recovered render path, security text, and both switch dispatches; nested guards and explicit no-op cases required, but s0/frame allocation and dispatch scheduling remain.
extern s8 D_807552E0;
extern s32 D_8076A064;
void func_8061CC40(s32, s16, s32);
void func_80713C8C(void);
Gfx *func_807138CC(Gfx *);
Gfx *func_80713B40(Gfx *);
Gfx *func_80713DFC(Gfx *);
Gfx *hudDrawScaledText(Gfx *, s16, s16, f32, void *);
s32 _sprintf(char *, const char *, ...);

Gfx *func_80714060(Gfx *arg0) {
    Gfx *var_s0 = arg0;
    char buffer[40];

    if ((D_80755338 != 0) && (D_8076A064 == 1)) {
        D_80755338 = 0;
        if (D_8075533C >= 0) {
            func_8061CC40(0, (s16)D_8075533C, 1);
        }
    }
    if (D_807552E0 != 0) {
        var_s0 = func_807132DC(var_s0);
        _sprintf(buffer, "SECURITY %d", D_807552E0);
        var_s0 = hudDrawScaledText(var_s0, 0x280, 0x1E0, 1.0f, buffer);
    }
    D_807552E0 = 0;
    R117D_WRITE_GFX(var_s0++, 0xE7000000, 0);
    if (D_80755334 < 0x5A) {
        D_80755334++;
    }
    if ((func_80712628() != 0) && (D_80755314 != 6)) {
        func_8071261C();
    }
    if (D_8075531C != 0) {
        if (D_80755318 == D_80755314) {
            if (D_80755314 < 0xF) {
                D_8075531C--;
                switch (D_80755314) {
                case 0:
                case 1: func_80713270(); break;
                case 2: func_8071321C(); break;
                case 3: func_80712FC8(); break;
                case 6: func_80713C8C(); break;
                case 7:
                case 9: func_80713168(); break;
                case 11: func_807130D4(); break;
                case 14: func_80713088(); break;
                }
            }
        }
    }
    switch (D_80755314) {
    case 0:
    case 1: return (Gfx *)func_8071375C((s32)var_s0);
    case 2: return func_807138A4(var_s0);
    case 3: return func_807138CC(var_s0);
    case 5: return (Gfx *)func_80713EA8((s32)var_s0);
    case 6: return func_80713DFC(var_s0);
    case 7:
    case 9: return func_80713B40(var_s0);
    }
    return var_s0;
}

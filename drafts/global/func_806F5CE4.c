// func_806F5CE4 (src/global/F9450.c): Stage 3: unrolled membership scan has target-like dynamic index; compiler still emits absolute loads.
extern s32 D_80754264;
extern s32 D_80754268;

s32 func_806F5CE4(arg0)
s32 arg0;
{
    s32 i;

    if (arg0 == D_80754264) {
        return 1;
    }
    if (arg0 == D_80754268) {
        return 1;
    }
    for (i = 2; i < 6; i++) {
        if (arg0 == (&D_80754264)[i]) {
            return 1;
        }
    }
    return 0;
}

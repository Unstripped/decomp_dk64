// func_8062DB70 (src/global/2F550.c): Stage 5. Scheduling only: target stores D[0],D[2],D[1], reloads D[2],arg2 before muls; all 6 statement orders tried, 12-20 diff rows.
extern f32 D_807F5E50[];

void func_8062DB70(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    D_807F5E50[0] = arg3 - arg0;
    D_807F5E50[2] = arg5 - arg2;
    D_807F5E50[1] = arg4 - arg1;
    D_807F5E50[3] = -((D_807F5E50[2] * arg2) + ((D_807F5E50[0] * arg0) + (D_807F5E50[1] * arg1)));
}

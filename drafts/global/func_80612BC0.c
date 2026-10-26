// func_80612BC0 (src/global/17540.c): stage 2: code matches; remaining local rodata relocation
f32 func_80612D10(f32);
f32 func_80612D1C(f32);
void func_80612BC0(f32 (*arg0)[4], f32 arg1) {
    f32 sine;
    f32 cosine;
    arg1 *= 0.01745329238f;
    sine = func_80612D1C(arg1);
    cosine = func_80612D10(arg1);
    guMtxIdentF(arg0);
    arg0[1][2] = sine;
    arg0[2][1] = -sine;
    arg0[1][1] = cosine;
    arg0[2][2] = cosine;
}

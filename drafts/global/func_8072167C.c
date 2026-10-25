// func_8072167C (src/global/126260.c): Text-identical C; final private-copy relocation gate remained mismatched.
extern s16 D_80755680;
extern f32 D_80755684;
extern f32 D_80755688;
extern f32 D_8075568C;

void func_8072167C(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    D_80755680 = (s16) (s32) ((f64) D_80755680 + ((f64) (arg3 - D_80755680) * 0.1));
    D_80755684 = (f32) ((f64) D_80755684 + ((f64) ((f32) arg0 - D_80755684) * 0.1));
    D_80755688 = (f32) ((f64) D_80755688 + ((f64) ((f32) arg1 - D_80755688) * 0.1));
    D_8075568C = (f32) ((f64) D_8075568C + ((f64) ((f32) arg2 - D_8075568C) * 0.1));
}

// ultralib defines __libm_qnan_f in assembly (gu/libm_vals.s); sinf.c and cosf.c read it as `extern float` through guint.h.
const union {
    unsigned int i;
    float f;
} __libm_qnan_f = { 0x7F810000 };

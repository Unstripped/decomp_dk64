// func_8063C6D8 (src/global/41090.c): text-identical, reloc only: expected refs rodata double as D_807584F0, ours .rodata+off (0.439 literal). ROM-identical, orchestrator to paste.
extern f32 D_807F6170;
extern f32 D_807F6174;

void func_8063C6D8(void) {
    D_807F6170 -= 1.0;
    if (D_807F6170 < 0.0) {
        D_807F6170 = 255.0f;
    }
    D_807F6174 -= 0.439;
    if (D_807F6174 < 0.0) {
        D_807F6174 = 255.0f;
    }
}

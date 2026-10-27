// func_8062F3A0 (src/global/2F550.c): from .scratch/NM2F2/func_8062F3A0_best.c
typedef struct R2F550a2Cmd {
    u32 unk0;
    u32 unk4;
} R2F550a2Cmd;

s32 func_8066B0F8(s32, s32, s32, s32);

void func_8062F3A0(R2F550a2Cmd *arg0, R2F550a2Cmd *arg1) {
    R2F550a2Cmd *p;
    u32 w;

    for (p = arg0; p != arg1; p++) {
        w = p->unk0;
        if ((w >> 24) == (0, 0xFD)) {
            if (((p->unk4 << 4) >> 28) == 0) {
                p->unk4 = func_8066B0F8(0x19, p->unk4, 1, 0);
            }
        }
    }
}

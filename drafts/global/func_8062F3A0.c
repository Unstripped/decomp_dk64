// func_8062F3A0 (src/global/2F550.c): stage 5: target keeps arg1 in s1 and constant 0xFD in s2, loads p->unk0 and p->unk4 into v0 (move a1,v0 in delay slot, srl/bnez, no likely branch) with the load hoisted into the back-edge delay slot; ours has arg1 in s2, 0xFD in s1, loads into t6/a1 and uses bnezl. unk4 must be u32 (srl).
typedef struct R2F550a2Cmd {
    u32 unk0;
    u32 unk4;
} R2F550a2Cmd;

s32 func_8066B0F8(s32, s32, s32, s32);

void func_8062F3A0(R2F550a2Cmd *arg0, R2F550a2Cmd *arg1) {
    R2F550a2Cmd *p;
    u32 t;

    p = arg0;
    if (p != arg1) {
        do {
            if ((p->unk0 >> 24) == 0xFD) {
                t = p->unk4;
                if (((t << 4) >> 28) == 0) {
                    p->unk4 = func_8066B0F8(0x19, t, 1, 0);
                }
            }
            p++;
        } while (p != arg1);
    }
}

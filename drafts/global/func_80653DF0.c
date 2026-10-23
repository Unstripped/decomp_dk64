// func_80653DF0 (src/global/55B20.c): stage 6 regalloc: frame 0x30 exact, logic/insn order matches; target ranks the 0xFD constant above arg1 (s2=0xFD,s3=arg1,s4=arg2ext) and loads the word into v0 then moves to a1; permuter best 296
extern s32 func_8066B0F8(s32, s32, s32, s32);

void *func_80653DF0(u8 *arg0, u8 *arg1, s16 arg2) {
    s32 count;
    u8 *p;
    s32 temp_v0;

    p = arg0;
    count = 0;
    if ((p != arg1) && (arg2 > 0)) {
        do {
            if ((*(u32 *)p >> 0x18) == 0xFD) {
                temp_v0 = *(s32 *)(p + 4);
                if (((u32)(temp_v0 * 0x10) >> 0x1C) == 0) {
                    *(s32 *)(p + 4) = func_8066B0F8(0x19, temp_v0, 0, 0);
                    count++;
                }
            }
            p += 8;
        } while ((p != arg1) && (count < arg2));
    }
    return p;
}

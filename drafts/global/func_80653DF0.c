// func_80653DF0 (src/global/55B20.c): stage6 (S55c): prologue now matches (use arg0 directly, no p copy, keep zero/ count=zero) + deadsweep 'if (arg0 && arg0) {}' fixes bnez/join. Remaining 2 lines: bnel t7,s2 vs s2,t7 (const operand order, unaffected by op var/cast/!=/swap) and lw v0 + move a1,v0 in delay vs lw a1 direct (tried u32/ptr temp, re-read, casts, bitfield struct => lbu)
extern s32 assetLoad(s32, s32, s32, s32);

u8 *func_80653DF0(u8 *arg0, u8 *arg1, s16 arg2) {
    s32 count;
    s32 temp_v0;
    s32 zero;
    u32 tag;

    zero = 0;
    count = zero;
    if ((arg0 != arg1) && (arg2 > zero)) {
        do {
            tag = *(u32 *)arg0;
            if ((tag >> 0x18) == 0xFD) {
                temp_v0 = *(s32 *)(arg0 + 4);
                if (((u32)(temp_v0 * 0x10) >> 0x1C) == zero) {
                    *(s32 *)(arg0 + 4) = assetLoad(0x19, temp_v0, zero, zero);
                    count++;
                }
                if (arg0 && arg0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                if (zero) {
                }
            }
            arg0 += 8;
        } while ((arg0 != arg1) && (count < arg2));
    }
    return arg0;
}

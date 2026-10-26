// func_8060BBE0 (src/global/104F0.c): stage 3: full bitfield reader loop compiled; remaining diff is target argument-home stores and loop register allocation. Tried compact typed loop.
s32 func_8060BBE0(s32 arg0, s32 arg1) {
    u32 *ptr;
    u32 data;
    u32 result;
    u8 remaining;
    u8 bit;
    u8 start;
    u8 shift;

    arg0 &= 0xFFFF;
    remaining = arg1 & 0xFF;
    bit = arg0 & 0x1F;
    start = bit;
    shift = 0;
    result = 0;
    data = 0;
    ptr = (u32 *)D_807ECEA8 + (arg0 >> 5);
    while (remaining != 0) {
        data |= 1 << bit;
        bit = (bit + 1) & 0xFF;
        remaining = (remaining - 1) & 0xFF;
        if ((bit >= 0x20) || (remaining == 0)) {
            result |= ((*ptr & data) >> start) << shift;
            ptr++;
            bit = 0;
            data = 0;
            start = 0;
            shift = -(remaining - (arg1 & 0xFF)) & 0xFF;
        }
    }
    return result;
}

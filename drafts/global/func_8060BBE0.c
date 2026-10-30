// func_8060BBE0 (src/global/104F0.c): stage 5: frame 0 exact, callee-saved empty exact; diff is only a1/t3 regalloc swap in bitfield reader
s32 func_8060BBE0(arg0, arg1)
unsigned short arg0;
unsigned char arg1;
{
    u32 *ptr;
    u32 data;
    u32 result;
    u8 start;
    u8 bit;
    u8 shift;
    u8 rem;

    result = 0;
    start = arg0 & 0x1F;
    shift = 0;
    bit = arg0 & 0x1F;
    data = 0;
    rem = arg1;
    ptr = (u32 *)D_807ECEA8 + (arg0 >> 5);
    if (rem) {
        do {
            data |= 1 << bit;
            bit++;
            rem--;
            if ((bit >= 0x20) || !rem) {
                result |= ((*ptr & data) >> start) << shift;
                bit = 0;
                ptr++;
                data = 0;
                start = 0;
                shift = -(rem - arg1);
            }
        } while (rem);
    }
    return result;
}

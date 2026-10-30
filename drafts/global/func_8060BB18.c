// func_8060BB18 (src/global/104F0.c): stage 3: K&R narrow params (u32 arg0, u16 arg1, u8 arg2), diff is missing s0 save / 8-byte frame in leaf
void func_8060BB18(arg0, arg1, arg2)
u32 arg0;
unsigned short arg1;
unsigned char arg2;
{
    u32 *ptr;
    u8 bit;
    u32 mask;
    u32 val;

    bit = arg1 & 0x1F;
    mask = -1;
    val = 0;
    ptr = (u32 *)D_807ECEA8 + (arg1 >> 5);
    if (arg2) {
        do {
            mask ^= 1 << bit;
            val |= (arg0 & 1) << bit;
            bit++;
            arg2--;
            arg0 >>= 1;
            if ((bit >= 0x20) || !arg2) {
                *ptr = (*ptr & mask) | val;
                ptr++;
                bit = 0;
                val = 0;
                mask = -1;
            }
        } while (arg2);
    }
}

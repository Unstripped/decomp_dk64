// func_8060BB18 (src/global/104F0.c): stage 3: verified leaf with no jal; target saves s0 to 0x4(sp) for arg0 in 8-byte frame, while IDO leaf codegen allocates only temps for frame 0
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

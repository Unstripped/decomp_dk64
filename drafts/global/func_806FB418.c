// func_806FB418 (src/global/FCCD0.c): stage 4: exact control flow and instruction sequence; allocation differs
extern u8 D_807FCB26;

s32 func_806FB418(void) {
    u8 *row;
    u16 *values;
    s32 i;
    s32 sum;

    sum = 0;
    row = (u8 *)D_807FC950;
    do {
        values = (u16 *)row;
        for (i = 0; i != 8; i += 4) {
            sum += values[0x21];
            sum += values[0x22];
            sum += values[0x23];
            sum += values[0x24];
            values += 4;
        }
        row += 0x5E;
    } while (row != &D_807FCB26);
    return sum;
}

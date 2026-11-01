// eepromReadChecksumBit (src/global/104F0.c): stage 6: 31/32 insns match, frame 0x28 exact, single diff addiu a1,sp,0x26 vs 0x23 (or bit-identical 32/32 if func_8060B9D0 u16)
extern u8 D_807467C8;
extern s32 func_8060B9D0();
extern s32 eepromReadBitfield(s32, s32);
extern void eepromGetSectorOffset();
extern s32 func_8071432C(void);

u8 eepromReadChecksumBit(u16 arg0, u8 arg1) {
    u8 result;
    u8 output;
    u16 value;

    result = 0;
    if (func_8071432C() != 0) {
        eepromGetSectorOffset(&value, &output, 0, 0, arg1, func_8060B9D0(D_807467C8));
        result = eepromReadBitfield((value + arg0) & 0xFFFF, 1);
    }
    return result;
}

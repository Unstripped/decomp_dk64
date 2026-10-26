// func_80611A44 (src/global/166A0.c): stage 2; m2c body has the exact jal/mask instruction sequence once the RNG function is matched; blocked only by preceding RNG size mismatch in whole-file fdiff.
s32 func_806119A0(void);

s32 func_80611A44(void) {
    return func_806119A0() & 0x7FFFFFFF;
}

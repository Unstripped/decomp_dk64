// func_80611A44 (src/global/166A0.c): stage 2: m2c candidate; requires matched RNG return prototype.
s32 func_806119A0();                                /* extern */

s32 func_80611A44(void) {
    return func_806119A0() & 0x7FFFFFFF;
}

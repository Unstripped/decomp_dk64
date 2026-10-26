// func_80732930 (src/global/137630.c): stage 5: only diff: loop tail 'srl t7,a0,1; move a0,t7; andi t8,a0,0xff; move a0,t8' vs target in-place 'srl a0,a0,1; andi a0,a0,0xff' (+8 bytes). float locals base@4(sp), result@0(sp) order and rest match.
f32 func_80732930(u8 n) {
    f32 base = 1.030992985f;
    f32 result = 1.0f;

    while (n != 0) {
        if (n & 1) {
            result = result * base;
        }
        base = base * base;
        n >>= 1;
    }
    return result;
}

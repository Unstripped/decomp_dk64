// func_8061522C (src/global/19A00.c): stage 4; permuter best score 38; remaining diff: local byte offsets and masked-result scheduling. Attempts: m2c baseline, min/max/value layout, value-first layout, unused padding local, three-byte aggregate layout, permuter run.
s32 func_8061522C(Actor *arg0) {
    s32 random;
    int byteValue;
    struct {
        u8 max;
        u8 min;
        u8 pad;
    } values;
    s32 value;

    D_807F5AF0++;
    func_80614F28(&values.min);
    func_80614F28(&values.max);
    value = ((((random = func_80611A44()) >> 15) % 32767) % ((values.max - values.min) + 1)) + values.min;
    byteValue = value & 0xFF;
    if ((value ^ 0) & 0xFF) {
        ((P19aState *)arg0->unk4)->unk7C = byteValue - 1;
        ((P19aState *)arg0->unk4)->flags |= 2;
        return 0;
    }
    return 1;
}

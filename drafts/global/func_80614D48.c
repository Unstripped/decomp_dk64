// func_80614D48 (src/global/19A00.c): stage 2: m2c behavioral starter; remaining state view types/register allocation
// Stage 2: m2c behavioral starter; remaining diff: field-view types/register allocation.
void func_80614D48(void *arg0, f32 arg1, f32 arg2) {
    void *temp_v0;

    temp_v0 = *arg0->unk4;
    if (arg2 > 0.0f) {
        temp_v0->unk34 = arg2;
        temp_v0->unk2C = arg1;
        temp_v0->unk30 = 0.0f;
        temp_v0->unk28 = (f32) temp_v0->unk24;
        return;
    }
    temp_v0->unk24 = arg1;
    temp_v0->unk34 = 0.0f;
}

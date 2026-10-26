// func_80614D00 (src/global/19A00.c): stage 4: typed state candidate compiled; body matches f32 ABI shape, but unit callers retain integer-bit ABI declaration
// Stage 2: m2c behavioral starter; remaining diff: field-view types/register allocation.
void func_80614D00(void *arg0, f32 arg1, f32 arg2) {
    void *temp_v0;

    temp_v0 = arg0->unk4;
    if (arg2 > 0.0f) {
        temp_v0->unk58 = arg2;
        temp_v0->unk50 = arg1;
        temp_v0->unk54 = 0.0f;
        temp_v0->unk4C = (f32) temp_v0->unk48;
        return;
    }
    temp_v0->unk48 = arg1;
    temp_v0->unk58 = 0.0f;
}

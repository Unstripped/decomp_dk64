// func_8070C990 (src/global/110F00.c): stage 6: exact instruction order; independent divisions receive / in the opposite order
// func_8070C990: exact instructions except the two independent divisions receive $f0/$f2 in the opposite order.
void func_8070CCC4();

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
} M110bMtxF;

void func_8070C990(M110bMtxF *arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 temp_fv0;
    f32 temp_fv1;

    func_8070CCC4(arg0);
    temp_fv1 = arg1 / arg3;
    arg0->unk0 = temp_fv1;
    arg0->unk14 = temp_fv1;
    temp_fv0 = arg2 / arg3;
    arg0->unk4 = temp_fv0;
    arg0->unk10 = -temp_fv0;
}

// func_80717100 (src/global/11BC10.c): stage 5: structure/dataflow complete (test-on-field, post-if re-sync, CSE-to-temp propagation); only ugen temp-ring offset remains: angle temp t5 vs target t7 (+2 ring positions from the first allocation onward)
typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
} Fx11BAMotion10;

void func_80717100(RotatingEffectActorView *arg0, void *arg1) {
    Fx11BAMotion10 *var_v1;

    if (arg0->unk384 == NULL) {
        arg0->unk384 = func_80610FE8(0xA);
        var_v1 = arg0->unk384;
        var_v1->unk0 = (s16) ((randomNonNegative() >> 15) % 0xFFF);
        var_v1->unk2 = arg0->unk35C;
        var_v1->unk4 = arg0->unk35C >> 16;
        var_v1->unk6 = arg0->unk340;
        var_v1->unk8 = arg0->unk348;
    }
    var_v1 = arg0->unk384;
    var_v1->unk0 = var_v1->unk4 + var_v1->unk0;
    arg0->unk340 = func_80612794(var_v1->unk0) * var_v1->unk2 + var_v1->unk6;
    arg0->unk348 = func_80612790(var_v1->unk0) * var_v1->unk2 + var_v1->unk8;
}

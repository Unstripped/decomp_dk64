// func_80717814 (src/global/11BC10.c): stage 5: explicit cached actor and motion locals reproduce target frame and callee-saved set; s0/s1 assignment and likely branch-delay allocation differ
typedef struct {
    s16 unk0;
    s16 unk2;
} Ub1bMotion4;

void func_80717814(Ub1ActorView *arg0, void *arg1) {
    Ub1ActorView *var_s0;
    Ub1bMotion4 *var_v1;

    var_v1 = arg0->unk384;
    var_s0 = arg0;
    if (var_v1 == NULL) {
        var_v1 = func_80610FE8(4);
        var_s0->unk384 = var_v1;
        var_v1->unk0 = (func_80611A44() >> 15) % 4095;
        var_v1->unk2 = ((func_80611A44() >> 15) % 10) + 2;
    }
    var_s0->unk340 += 0.2 * var_s0->unk35C * func_80612794(var_v1->unk0);
    var_s0->unk344 += 0.2 * var_s0->unk35C * func_80612790(var_v1->unk0);
    var_v1->unk0 += 0x46;
    var_s0->unk35C += var_v1->unk2;
}

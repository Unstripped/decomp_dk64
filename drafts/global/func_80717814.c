// func_80717814 (src/global/11BC10.c): stage 4: behavior and control flow recovered; target keeps motion pointer in s1 while this version spills and grows frame
typedef struct {
    s16 unk0;
    s16 unk2;
} Ub1Motion4;

typedef struct {
    u8 pad0[0x340];
    f32 unk340;
    f32 unk344;
    u8 pad348[0x14];
    s32 unk35C;
    u8 pad360[0x24];
    Ub1Motion4 *unk384;
} Ub1ActorView;

void *func_80610FE8(s32);
s32 func_80611A44(void);
f32 func_80612790(s16);
f32 func_80612794(s16);

void func_80717814(Ub1ActorView *arg0, void *arg1) {
    Ub1Motion4 *temp_v0;
    Ub1Motion4 *var_v1;

    var_v1 = arg0->unk384;
    if (var_v1 == NULL) {
        temp_v0 = func_80610FE8(4);
        arg0->unk384 = temp_v0;
        temp_v0->unk0 = (func_80611A44() >> 15) % 4095;
        temp_v0->unk2 = ((func_80611A44() >> 15) % 10) + 2;
        var_v1 = arg0->unk384;
    }
    arg0->unk340 += 0.2 * arg0->unk35C * func_80612794(var_v1->unk0);
    arg0->unk344 += 0.2 * arg0->unk35C * func_80612790(var_v1->unk0);
    var_v1->unk0 += 0x46;
    arg0->unk35C += var_v1->unk2;
}

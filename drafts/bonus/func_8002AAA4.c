// func_8002AAA4 (src/bonus/2690.c): from .scratch/BonusC/func_8002AAA4_best.c
typedef struct {
    char pad[4];
    u8 unk4;
} BonusC_AAA4_T;

void func_8002AAA4(void) {
    Struct_AAA4_174 *sp64;
    Actor_AAA4_Target *temp_v1;
    f32 dx;
    f32 dz;
    s32 sp54;
    Struct_4_Unk0 *sp50;
    Struct_4 *temp_v0;
    BonusC_AAA4_T *new_var;
    s32 i;

    sp64 = (Struct_AAA4_174 *)D_807FBB40->unk174;
    temp_v0 = D_807FBB40->unk4;
    sp50 = temp_v0->unk0;
    if (!(D_807FBB40->unk60 & 0x10)) {
        actorScriptStart(D_807FBB40, 0x239);
        D_807FBB40->unk144 = 0x24;
        temp_v0 = D_807FBB40->unk4;
    }
    sp54 = temp_v0->unk64;
    if (sp54 == 0x239) {
        for (i = 0; i < gActiveActorCount; i++) {
            temp_v1 = gActiveActors[i].actor;
            if (temp_v1->unk58 == 0x149) {
                dx = temp_v1->unk7C - D_807FBB40->unk7C;
                dz = temp_v1->unk80 - D_807FBB40->unk80;
                if (dx < 5.0 && dx > -5.0 && dz < 20.0f && dz > -20.0) {
                    new_var = (BonusC_AAA4_T *)temp_v1->unk174;
                    new_var->unk4 = 8;
                    actorScriptStart(D_807FBB40, 0x23B);
                }
            }
        }
    }
    if ((sp54 == 0x239 || sp54 == 0x23B || (sp54 == 0x238 && sp50 != NULL && sp50->unk4 > 48.0f)) && D_807FBB85 == 1) {
        actorScriptStart(D_807FBB40, 0x23C);
        sp64->unk6 = ((func_806119A0() & 7) + 6) * D_8002D900;
    }
    if (sp54 == 0x23A) {
        sp64->unk6 -= 1;
        if (sp64->unk6 == 0) {
            actorScriptStart(D_807FBB40, 0x238);
        }
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

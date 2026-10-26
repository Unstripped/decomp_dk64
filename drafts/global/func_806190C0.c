// func_806190C0 (src/global/19A00.c): stage 3: behavioral m2c translation compiles; frame is 0x60 vs target 0x50, with unsigned conversion and local stack layout remaining.
typedef struct { u8 pad0[0x35C]; s32 unk35C; } P19LEffectView;
extern u8 D_80750AD0;
extern void *D_80746B80[];
extern void (*D_80746BD4[])(void);
P19LEffectView *func_80714CC0(void *, f32, f32, f32, f32);
void func_8071D94C(Actor *, P19LEffectView *, u8 *);
void effectFreeAndUnlink(void *, void *);

void func_806190C0(Actor *arg0) {
    u16 sp4E, sp4C, sp46;
    u8 sp4B, sp4A, sp49, sp48, sp2F;
    f32 sp40, sp3C, sp38, sp34, var_ft1;
    P19LEffectView *sp30, *temp_v0, *var_a1;
    s32 temp_hi;
    func_80614F4C((u8 *)&sp4E);
    func_80614F4C((u8 *)&sp4C);
    func_80614F28(&sp4B); func_80614F28(&sp4A); func_80614F28(&sp49); func_80614F28(&sp48);
    func_80614F4C((u8 *)&sp46);
    if (D_80750AD0 == 0) {
        var_ft1 = (f32)sp4C;
        if ((s32)sp4C < 0) var_ft1 += 4294967296.0f;
        sp40 = var_ft1 * 0.00048828125f;
        func_807149B8(1); func_80714998(sp4B); func_807149FC((s16)sp46);
        if (sp4A == 0) { sp3C = arg0->unk7C; sp38 = arg0->unk80; sp34 = arg0->unk84; }
        else actorGetNodePos(arg0, sp4A, &sp3C, &sp38, &sp34);
        sp38 += (f32)(s8)sp49 * sp40;
        if (sp48 != 0) func_8071498C(D_80746BD4[sp48]);
        temp_v0 = func_80714CC0(D_80746B80[sp4E], sp40, sp3C, sp38, sp34); var_a1 = temp_v0; sp2F = 0;
        switch (sp48) {
            case 1: sp30 = var_a1; func_8071D94C(arg0, var_a1, &sp2F); var_a1 = sp30; break;
            case 2: temp_v0->unk35C = 1; break;
            case 4: sp30 = var_a1; temp_hi = (func_80611A44(1, var_a1, sp48) >> 15) % 50; var_a1->unk35C = -50 - temp_hi; break;
        }
        if (sp2F != 0) effectFreeAndUnlink(var_a1, var_a1);
    }
}

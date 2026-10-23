// func_80665564 (src/global/699B0.c): Near-match (339 insns); control flow, math, and rodata match; stack frame size 0x68 vs 0x60 due to local declaration spill ordering.
typedef struct R2A_Actor5564 {
    char pad0[0x4];
    ActorSub4 *unk4;
    char pad8[0x54];
    u16 unk5C;
    char pad5E[2];
    u32 unk60;
    char pad64[0x6];
    u16 unk6A;
    u16 unk6C;
    char pad6E[0x12];
    f32 unk80;
    char pad84[0x8];
    f32 unk8C;
    char pad90[0x14];
    f32 unkA4;
    char padA8[0xC];
    f32 unkB4;
    char padB8[0x8];
    f32 unkC0;
    char padC4[0xD];
    u8 unkD1;
    char padD2[6];
    s16 unkD8;
    s16 unkDA;
    s16 unkDC;
    s16 unkDE;
    f32 unkE0;
} R2A_Actor5564;

typedef struct {
    s16 unk0;
    char pad2[0x24];
    s16 unk26;
} R2A_StructD580;

typedef struct {
    s16 unk0;
    u8 unk2;
    u8 unk3;
    u8 pad4[2];
    u8 unk6;
    u8 pad7[3];
} R2A_Entry8D40;

extern R2A_Entry8D40 D_80748D40[];
extern R2A_Entry8D40 D_80748DA4;
extern R2A_StructD580 *D_807FD580;
extern Actor *D_807FBB40;
extern s32 D_8076A0A8;

void func_80666290(Actor *, u8 *, f32 *, u8 *, void *, s32);
void func_806D09E8(Actor *);
s16 func_806CC10C(s16, s16);

void func_80665564(R2A_Actor5564 *arg0, f32 arg1) {
    f32 sp5C;
    u8 sp5B;
    f32 sp54;
    u8 sp53;
    f32 temp_fa0;
    f32 temp_fv0;
    f32 var_fv0;
    f32 var_fv1;
    s16 var_t0;
    s16 var_a1;
    R2A_Entry8D40 *var_t1;
    s16 var_a2;
    s16 diff;

    func_80666290((Actor *)arg0, &sp5B, &sp5C, &sp53, &sp54, 0);
    if (arg0->unk5C & 1) {
        func_806D09E8((Actor *)arg0);
    }
    temp_fa0 = arg0->unkA4;
    temp_fv0 = arg0->unk80 - temp_fa0;
    arg0->unk6A &= ~1;
    arg0->unkB4 = temp_fv0 - arg1;
    if ((temp_fv0 <= arg1) || ((arg0->unk6C & 1) && (arg0->unkC0 < 0.0f))) {
        if ((D_807FBB40->unk6A & 0x200) || (D_8076A0A8 == 0x27) || (D_8076A0A8 == 0x6F) || (D_8076A0A8 == 0xB9)) {
            if ((f64)arg0->unkB4 < 0.5) {
                if (arg0->unk4 != NULL) {
                    var_fv1 = arg0->unk4->unk38;
                } else {
                    var_fv1 = 0.15f;
                }
                arg0->unk80 = temp_fa0 + arg1;
                arg0->unkB4 = 0.0f;
                arg0->unk6A |= 1;
                arg0->unkC0 = (temp_fa0 + arg1 - arg0->unk8C) * (f32)(40.0 / ((f64)var_fv1 * 6.66666667));
            }
        } else if (arg0->unkB4 < 5.0f) {
            arg0->unkB4 = 0.0f;
            arg0->unk80 = temp_fa0 + arg1;
            arg0->unk6A |= 1;
            if (arg0->unkC0 < -10.0f) {
                arg0->unkC0 = -10.0f;
            }
        }
    }
    D_80748E04 = 0;
    if (sp5B && !(arg0->unk6A & 1) && (D_80748E00 == 0)) {
        if (arg0->unkC0 > 0.0f) {
            arg0->unkC0 = 0.0f;
        }
        arg0->unk80 = (f64)sp5C + (f64)arg0->unkC0 * 0.025;
        D_80748E04 = 1;
    }
    D_80748E00 = 0;
    var_fv0 = (arg0->unk60 & 0x40000) ? 0.2 : 1.0;
    var_t0 = (arg0->unk6A & 1) ? arg0->unkDA : 0x400;
    var_a1 = arg0->unkD8;
    var_t1 = &D_80748D40[arg0->unkD1];
    switch (D_8076A0A8) {
    case 0x52:
        D_807FD580->unk26 = 0x14;
        /* fallthrough */
    case 0xE:
        if (arg0->unk6A & 0x200) {
            var_t1 = &D_80748DA4;
        }
        break;
    }
    if (arg0->unkDE >= 0x3F4) {
        arg0->unkDC = var_a1;
    }
    if (var_t0 >= 0x3F4) {
        var_a1 = arg0->unkDC;
    }
    var_a2 = (s16)((var_t1->unk6 << 12) / 360);
    if (var_a2 < var_t0) {
        var_a2 = var_t0;
    }
    diff = func_806CC10C(arg0->unkDC, var_a1);
    if (((diff > 0) ? diff : -diff) >= 0x6AB) {
        if (arg0->unkDE >= 0x3C8) {
            arg0->unkDE = 0x400;
            arg0->unkDC = var_a1;
        } else {
            arg0->unkDE += (s32)((f32)func_806CC10C(arg0->unkDE, 0x400) * var_fv0);
            arg0->unkDE &= 0xFFF;
        }
    } else {
        arg0->unkDC += (s32)((f32)diff * var_fv0);
        arg0->unkDC &= 0xFFF;
        arg0->unkDE += (s32)((f32)func_806CC10C(arg0->unkDE, var_a2) * var_fv0);
        arg0->unkDE &= 0xFFF;
    }
    var_a2 = (s16)((((arg0->unk6A & 0x20) ? var_t1->unk2 : var_t1->unk3) << 12) / 360);
    if (var_a2 < var_t0) {
        arg0->unkE0 = 0.0f;
    } else {
        arg0->unkE0 = (f32)((0x400 - var_t0) / var_t1->unk0);
    }
}

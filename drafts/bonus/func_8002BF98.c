// func_8002BF98 (src/bonus/2690.c): stage 5: same frame 0x88/saved regs/insn count; only diff is FP colouring in case 0: ctrly(f18)<->delta(f12) swap (4 insns: mul.s f18/f12, sub.s f12/f18, 2 uses). uopt order: E(f2) > ctrly > fa1,ft4 ilods > delta(sp78, adjsave 2.0 vs 3.0); target needs delta>fa1>ft4>ctrly. Tried: role permutations of 5 float names (all 50 diff lines), register kw, copy/inline/two-step, extra uses, lightAdd/lightSetColor via vars, ctrl local ptr (CSE), orders. Tricks kept: &D_807FC924[D_807FC929] (t ring), shared p ptr for both unk2A loops (s1), doubles 0.0/1.0 for BB15 zero stores/unk0 clamp (splits const webs, makes call2 0.0f web colour f0), no named u8 switch var, ctrlx var reused for projectile z/tail unk10 (f2), unused float slot keeps frame 0x88, sp5A named s16.
typedef struct LargeB4Actor LargeB4Actor;
typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    s16 unk1C;
    s16 unk1E;
    s16 unk20;
    u8 unk22;
    u8 unk23;
    u8 unk24;
    u8 pad25;
    s16 unk26;
    s16 unk28;
    s8 unk2A[1];
} LargeB4Sub;

struct LargeB4Actor {
    char pad0[4];
    Struct_4 *unk4;
    char pad8[0x58];
    s32 unk60;
    char pad64[0x18];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0x94];
    LargeB4Actor *unk11C;
    char pad120[0x24];
    u8 unk144;
    char pad145[0xF];
    u8 unk154;
    u8 unk155;
    char pad156[0x1E];
    LargeB4Sub *unk174;
};

typedef struct {
    char pad0[4];
    s16 unk4;
    char pad6[2];
    f32 unk8;
    s16 unkC;
} LargeB4Spawn;

typedef struct {
    char pad0[0x210];
    f32 unk210;
    f32 unk214;
    f32 unk218;
    char pad21C[0x7C];
    u16 *unk298;
    char pad29C[0x2C];
    s16 unk2C8;
    char pad2CA[0x26];
} LargeB4Player;

typedef struct {
    char pad0[2];
    s8 unk2;
    s8 unk3;
} LargeB4Ctrl;

extern void *D_807FBB4C;
extern LargeB4Player *D_807FC924;
extern LargeB4Ctrl *D_807ECDEC;
void lightSetColor(f32, f32, f32, s32);
void lightAdd(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32);
Gfx *func_8002CC08(Gfx *, Actor_BB44 *);

#define LB4A ((LargeB4Actor *)D_807FBB40)
#define LB4C ((LargeB4Actor *)D_807FBB4C)
void func_8002BF98(void) {
    f32 sp84;
    f32 fv0;
    f32 sp7C;
    f32 sp78;
    f32 sp74;
    f32 fv1;
    f32 ft5;
    LargeB4Sub *temp_s5 = LB4A->unk174;
    LargeB4Spawn *temp_s0;
    s32 i;
    s8 *p;
    s16 sp5A;

    if (!(LB4A->unk60 & 0x10)) {
        LB4C->unk154 = 0x77;
        LB4C->unk155 = 0;
        LB4C->unk144 = 1;
        temp_s5->unk0 = 1.0f;
        temp_s5->unk4 = LB4A->unk7C;
        temp_s5->unk8 = LB4A->unk84;
        switch (D_8076A0A8) {
            case 0x67:
                temp_s5->unk28 = 4;
                D_8002D90C = 1.0f;
                break;
            case 0x8A:
                temp_s5->unk28 = 6;
                D_8002D90C = 1.3f;
                break;
            case 0x8B:
                temp_s5->unk28 = 8;
                D_8002D90C = 1.6f;
                break;
            case 0x8C:
                temp_s5->unk28 = 0xA;
                D_8002D90C = 1.9f;
                break;
        }
        temp_s5->unk24 = 0;
        temp_s5->unk26 = temp_s5->unk28;
        temp_s5->unk20 = 0x3C;
        temp_s5->unk23 = func_806FDB8C(1, func_8070E750(0x1A, 2, 1), 8, 0.0f, 0.0f, 0.0f);
        func_806FDAB8(temp_s5->unk23, 0.0f);
        LB4A->unk4->unk34 = 0.33f;
        LB4A->unk4->unk38 = 0.33f;
        LB4A->unk4->unk3C = 0.33f;
        camSetTarget(*(void **)((u8 *)D_807FD580 + 0x104), D_807FBB40, 4, 0x800, 0x1A, 0, 0x1F, 0x15, 0x10, 0, 0.05f);
        camStartPath(0, 0, 1);
        LB4A->unk154 = 3;
        temp_s5->unk14 = 0.0;
        temp_s5->unk18 = 0.0;
        temp_s5->unkC = 0.0;
        temp_s5->unk10 = 0.0;
        temp_s5->unk0 = 1.0;
        i = 0;
        p = (s8 *)temp_s5;
        do {
            i++;
            p[0x2A] = 1;
            p++;
        } while (i != 1);
    }
    for (i = 0, p = (s8 *)temp_s5; i < 1; i++, p++) {
        if (p[0x2A] > 0) {
            p[0x2A] = p[0x2A] - 1;
            if (p[0x2A] == 0 && actorSpawn(0x14B, 0x21) != 0) {
                temp_s0 = (LargeB4Spawn *)D_807FBB44->unk174;
                *(void **)temp_s0 = D_807FBB40;
                temp_s0->unkC = 2;
                temp_s0->unkC = (func_806119A0() & 0x3F) + 0xF;
                temp_s0->unk4 = func_806119A0() & 0xF;
                temp_s0->unk8 = func_806119FC() * 40.0 + 15.0;
                sp5A = temp_s0->unk4 * 0xC8 - 0x578;
                D_807FBB44->unk7C = func_80612794(sp5A) * temp_s0->unk8 + temp_s5->unk4;
                D_807FBB44->unk80 = D_807FBB40->unk80;
                D_807FBB44->unk84 = func_80612790(sp5A) * temp_s0->unk8 + temp_s5->unk8;
            }
        }
    }
    temp_s5->unk1C += 0x19;
    if (LB4A->unk154 == 0 || LB4A->unk154 == 1) {
        temp_s5->unk0 = temp_s5->unk0 - 0.03333333333333333;
        if (temp_s5->unk0 < 0.0) {
            temp_s5->unk0 = 0.0;
        }
    } else {
        temp_s5->unk0 = temp_s5->unk0 + 0.03333333333333333;
        if (temp_s5->unk0 > 1.0) {
            temp_s5->unk0 = 1.0;
        }
    }
    lightSetColor(temp_s5->unk0, temp_s5->unk0, temp_s5->unk0, -1);
    switch (LB4A->unk154) {
        case 0: {
            sp84 = func_80612794((&D_807FC924[D_807FC929])->unk2C8);
            fv0 = func_80612790((&D_807FC924[D_807FC929])->unk2C8);
            sp74 = D_807ECDEC->unk2 * 0.06f;
            ft5 = D_807ECDEC->unk3 * 0.06f;
            sp78 = ((sp74 * fv0) - (ft5 * sp84)) - temp_s5->unk14;
            temp_s5->unk14 = temp_s5->unk14 + sp78 * 0.155f;
            temp_s5->unk18 = temp_s5->unk18 + ((sp74 * sp84 + ft5 * fv0) - temp_s5->unk18) * 0.25f;
            temp_s5->unkC = temp_s5->unkC + temp_s5->unk14;
            temp_s5->unk10 = temp_s5->unk10 - temp_s5->unk18;
            if (temp_s5->unk26 == 0) {
                LB4A->unk154 = 5;
            }
            if (LB4A->unk11C->unk154 == 5) {
                LB4A->unk154 = 6;
            }
            if (temp_s5->unk1E > 0) {
                temp_s5->unk1E = temp_s5->unk1E - 1;
            }
            if (temp_s5->unk1E <= 0 && (*(&D_807FC924[D_807FC929])->unk298 & 0xE000)) {
                func_80609140(0x59, 0x7FFF, 63.0f, 1.0, 0x1E, 0);
                sp7C = func_80612794(D_807FC924->unk2C8) * 30.0f + D_807FC924->unk210;
                sp78 = D_807FC924->unk214 - 25.0f;
                sp74 = func_80612790(D_807FC924->unk2C8) * 30.0f + D_807FC924->unk218;
                projectileSetTargetCoords(sp7C, sp78, sp74);
                projectileAimAndSpawn(0x23, 1, 0.8f, LB4A->unk7C, LB4A->unk80, LB4A->unk84, 625.0f, D_807FBB40);
                temp_s5->unk1E = 0x1E;
            }
            break;
        }
        case 3:
            if (D_807444EC != 1) {
                LB4A->unk154 = 4;
                func_806A2A10(0xDC, 0x2A, *((u8 *)temp_s5 + 0x21));
                func_8070D8C0(D_807FBB40, 0, 0xC);
            }
            break;
        case 4:
            if (!(LB4A->unk60 & 0x02000000)) {
                LB4A->unk154 = 0;
                actorSetStateTwo(LB4A->unk11C);
                sfxAllocateChannel(8, 1.0);
            }
            break;
        case 5:
        case 6:
            if (LB4A->unk154 == 6) {
                func_800265C0(0, 1);
            } else {
                func_800264E0(0, 0);
            }
            camStartPath(0, 1, 0x11);
            LB4A->unk154 = 7;
            break;
    }
    sp7C = temp_s5->unkC;
    sp74 = temp_s5->unk10;
    fv0 = sqrtf(sp7C * sp7C + sp74 * sp74);
    if (fv0 > 110.0f) {
        sp78 = 110.0f / fv0;
        temp_s5->unkC = sp7C * sp78;
        temp_s5->unk10 = sp74 * sp78;
    }
    LB4A->unk7C = func_80612794(temp_s5->unk1C) * 5.0 + (temp_s5->unk4 + temp_s5->unkC);
    LB4A->unk84 = func_80612790((s16)(temp_s5->unk1C * 2)) * 2.0 + (temp_s5->unk8 + temp_s5->unk10);
    LB4C->unk7C = temp_s5->unk4 + temp_s5->unkC * 0.5f;
    LB4C->unk80 = LB4A->unk80;
    LB4C->unk84 = temp_s5->unk8 + temp_s5->unk10 * 0.5f;
    renderCallbacksRegister(func_8002CC08, D_807FBB40, 3);
    lightAdd(LB4A->unk7C, LB4A->unk80 + 25.0, LB4A->unk84, LB4A->unk7C, LB4A->unk80, LB4A->unk84, 25.0f, 1, 0xFF, 0xFF, 0xFF);
}

// func_8002CB18 (src/menu/3E10.c): MenuA 2026-11-03: stage 5, COUNT-EXACT (335), full=5 shape=4 (unchanged, parked in copy). Re-derived: remaining diff = 'li t5,1' hoist + 'sb t5,79(sp)' placed between 'lw t6,0(s0)' and 'lbu t0,340(t6)' (ours li t8, sb after lbu). Diagnosis from cc-ugen listing (as1probe keep -> t.s): the PRE reload (lw A; lbu A->unk154) is attributed to the dead-test line 'if (Menu6B_A->unk154 != 0) {}' so it sits BEFORE the sp4F store in ucode; target has li, sb, then reload under the last statement (target const ring t5 allocated before the reload t6, join lui t7). NATURAL body (no casts, no FAKEs, 'sp4F = 1;' as last then-statement) gives shape=0 full=72: then-block li/sb/reload EXACT, only ring/colour remain (join lui t9 vs t7; A->unk154 candidate). Natural + 'if (temp_s1->unk0 == 0) {}' after sp4F=1 fixes the join ring (full 19) but A->unk154 candidate becomes v1 (target t0) and reload ring moves (lbu t8). 18k-eval dead-test hill-climb from the natural body (hc_cb: 1-6 dead tests, 9 exprs x 4 forms x all positions) bottoms at 19; permutations of the 4 FAKE lines (24), placement grid of the 4 FAKEs over 6 slots (1296), line-join subsets up to 6 (6.5k) and deadsweep c1..c8 variants: none < 5. Untried: a steering that recolours the A->unk154 candidate t0 without a reference BEFORE the sp4F store (e.g. via the compare/selector locals sel, m8).
typedef struct MenuModelScale {
    char pad0[0x34];
    f32 unk34;
    f32 unk38;
    f32 unk3C;
} MenuModelScale;
typedef struct Menu6B_Actor {
    char pad0[4];
    MenuModelScale *unk4;
    char pad8[0x60 - 8];
    u32 unk60;
    char pad64[0x7C - 0x64];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0x154 - 0x88];
    u8 unk154;
    u8 unk155;
    char pad156[0x174 - 0x156];
    void *unk174;
    char pad178[4];
    s16 *unk17C;
} Menu6B_Actor;
typedef struct Menu6B_Sub174 {
    Menu6B_Actor *unk0;
    s32 unk4;
    s8 unk8;
} Menu6B_Sub174;
typedef struct Menu6B_Pair {
    f32 a;
    f32 b;
} Menu6B_Pair;
#define Menu6B_A ((Menu6B_Actor *)D_807FBB40)
#define Menu6B_N ((Menu6B_Actor *)D_807FBB44)
extern s32 D_800338B4[];
extern Menu6B_Pair D_80033894[];
void actorDespawn(void *);
void actorUpdateModelMatrix(void *, s32);
void func_806BF920(void);
void func_806F0C18(void *);
void actorConfigApplyAnimFrameByType(void *, s32, s32);

void func_8002CB18(void) {
    s32 temp_s1_2;
    Menu6B_Pair *row;
    f32 *sp5C;
    s32 sel;
    f32 sp54;
    f32 sp50;
    s8 sp4F;
    s8 m8;
    s16 idx;
    s16 *sp38;
    Menu6B_Sub174 *temp_s1;

    temp_s1 = Menu6B_A->unk174;
    sp5C = temp_s1->unk0->unk174;
    sp4F = 0;
    func_806BF920();
    if (!(Menu6B_A->unk60 & 0x10)) {
        Menu6B_A->unk4->unk34 = 2.0f * Menu6B_A->unk4->unk34;
        Menu6B_A->unk4->unk38 = 2.0f * Menu6B_A->unk4->unk38;
        Menu6B_A->unk4->unk3C = 2.0f * Menu6B_A->unk4->unk3C;
        m8 = temp_s1->unk8;
        actorScriptStart(Menu6B_A, D_800338B4[(s16)(m8 * 6) + (Menu6B_A->unk155 & 0xF)]);
        func_806F0C18(Menu6B_A);
        Menu6B_A->unk60 |= 0x1000;
        temp_s1->unk4 = D_8076A100[Menu6B_A->unk154 & 0xF];
        actorConfigApplyAnimFrameByType(Menu6B_A, Menu6B_A->unk155 + 2, D_8076A100[Menu6B_A->unk154 & 0xF]);
    }
    sel = Menu6B_A->unk154;
    if (!(Menu6B_A->unk154 & 0x80)) {
        if (temp_s1->unk4 != D_8076A100[Menu6B_A->unk154]) {
            actorConfigApplyAnimFrameByType(Menu6B_A, Menu6B_A->unk155 + 2, D_8076A100[Menu6B_A->unk154]);
            temp_s1->unk4 = D_8076A100[Menu6B_A->unk154];
        }
        idx = D_8076A0E4[Menu6B_A->unk154] & 0x7F;
        if (idx != Menu6B_A->unk155) {
            sp38 = &D_8003386C[idx];
            actorSpawn(0x151, *sp38);
            {
                s16 *q = Menu6B_N->unk17C;
                *q = *sp38;
            }
            Menu6B_N->unk154 = (u8)Menu6B_A->unk154; // FAKE: no-op narrowing cast, burns one ugen t-ring temp
            Menu6B_N->unk155 = (s16)idx; // FAKE: no-op narrowing cast, burns one ugen t-ring temp
            {
                Menu6_Sub174 *sub = Menu6B_N->unk174;
                sub->unk0 = temp_s1->unk0;
            }
            if (Menu6B_A->unk154 != 0) {} // FAKE: extra reference of the unk154 value; recolours the shared A->unk154 candidate (t0) and the PRE reload position
            sp4F = 1 | 0; // FAKE: no-code spelling of the constant (steers the sp4F store colour)
            if (temp_s1->unk4 != 0) {} // FAKE: dead test; one ugen ring step before the join block (t7 lui)
            sp4F = sp4F | 0; // FAKE: no-code def of sp4F (ring/colour steer)
                    }
        row = &D_80033894[Menu6B_A->unk154];
        func_800317E8((MenuScreenState *)sp5C, row->a, row->b, &sp54, &sp50, 2, 0, 1.8f);
        Menu6B_A->unk7C = D_807FBB4C->unk7C + (sp54 - 160.0f);
        Menu6B_A->unk80 = (D_807FBB4C->unk80 - (sp50 - 120.0f)) - 20.0f;
        Menu6B_A->unk84 = D_807FBB4C->unk84 - 300.0f;
        if (D_8076A0E4[Menu6B_A->unk154] & 0x80) {
            Menu6B_A->unk60 &= ~4;
        } else {
            Menu6B_A->unk60 |= 4;
        }
    } else {
        idx = D_80033F24[sel & 0xF];
        temp_s1_2 = 0x140 / D_80033878;
        func_800317E8((MenuScreenState *)sp5C, 160.0f, 150.0f, &sp54, &sp50, 2, 0, 1.8f);
        sp54 = (idx * temp_s1_2 + (temp_s1_2 >> 1)) - 0xA0;
        sp54 = sp54 * 0.78;
        Menu6B_A->unk7C = D_807FBB4C->unk7C + sp54;
        Menu6B_A->unk80 = (D_807FBB4C->unk80 - (sp50 - 120.0f)) + 16.0f;
        Menu6B_A->unk84 = D_807FBB4C->unk84 - 300.0f;
    }
    if (*sp5C > 1.0f) {
        sp4F = 1;
    }
    if (sp4F != 0) {
        actorDespawn(Menu6B_A);
    }
    actorUpdateModelMatrix(Menu6B_A, 0);
}

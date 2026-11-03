// func_8002CB18 (src/menu/3E10.c): MenuA 2026-11-03 (revisit 8): park unchanged full=5 shape=4 count-exact 335, but its first FAKE cast 'Menu6B_N->unk154 = (u8)A->unk154' is redundant (removed, still 5). KEY new base: drop FAKEs 'if (A->unk154 != 0) {}', 'if (temp_s1->unk4 != 0) {}', 'sp4F = sp4F | 0' and write plain 'sp4F = 1;' -> the whole arm (li t5 hoisted into the lw/sh stall, sb t5 between lw t6 and lbu t0) matches by itself; only the t-ring is one step off at the else arm (lui t9 vs t8, cascade 72 lines). Changing the remaining FAKE cast to 'Menu6B_N->unk155 = (u16)idx;' (not (s16)) on that base gives full=12 shape=0 count-exact (any (s16)/(u16)/(u8) chain ending in (u16) or (u8) ties): only left diff = idx's post-call reload is a ring temp (lh t2,76(sp)) instead of v0 (target lh v0,76(sp)); (s16)idx keeps v0 but loses the ring step. Both bases: exhaustive single dead test (114 forms x 62 positions), single/pair RHS cast wrappers on all 23 sites, 17 dead-test forms on idx/(u16)idx, idx type grid (s16 only works), 24k-eval hill-climbs: nothing < 12 on the u16 base / < 5 on the stored one. Self-store 'temp_s1->unk0 = temp_s1->unk0;' burns the ring step exactly (full 6-8) but emits lw/sw (+2 insns).
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
            Menu6B_N->unk154 = Menu6B_A->unk154;
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

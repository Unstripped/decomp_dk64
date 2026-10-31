// func_8002CB18 (src/menu/3E10.c): stage 5 (parked NON_MATCHING): harness diff 22 lines, shape(register-masked)=0: frame 0x68 + all slots match, ONLY ugen t-reg ring differs. Wins this round: drop dead 's32 a2' local + dead stmts (a2 compare/assign replaced by D_8076A100[Menu6B_A->unk154] twice) and use block-scope 's16 *q = Menu6B_N->unk17C; *q = *sp38;' (gives target's lw a0,380(t6); sh t8,0(a0)). Remaining: target caches Menu6B_N->unk174 in a1 (lw a1,372(t3); sw t4,0(a1)) so the following li gets t5 and the ring after is 1 lower; a 13th local (sub ptr) pushes frame to 112; removing sel/row/m8 to make room breaks slots (t_sel: sub ring right but sp5C slot 88 not 92, 75 diff). deadsweep (idx sel sp5C temp_s1 q), &0xFF/&0xFFFF/+0 masks, decl-order perms: no gain.
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
void actorScriptStart(void *, s32);
void actorDespawn(void *);
void actorUpdateModelMatrix(void *, s32);
void func_806BF920(void);
void func_806F0C18(void *);
void func_8068A4C8(void *, s32, s32);

void func_8002CB18(void) {
    s32 temp_s1_2;
    Menu6B_Pair *row;
    f32 *sp5C;
    s32 sel;
    f32 sp54;
    f32 sp50;
    s8 sp4F;
    s16 idx;
    s16 *sp38;
    Menu6B_Sub174 *temp_s1;
    s8 m8;

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
        func_8068A4C8(Menu6B_A, Menu6B_A->unk155 + 2, D_8076A100[Menu6B_A->unk154 & 0xF]);
    }
    sel = Menu6B_A->unk154;
    if (!(Menu6B_A->unk154 & 0x80)) {
        if (temp_s1->unk4 != D_8076A100[Menu6B_A->unk154]) {
            func_8068A4C8(Menu6B_A, Menu6B_A->unk155 + 2, D_8076A100[Menu6B_A->unk154]);
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
            Menu6B_N->unk155 = idx;
            *(Menu6B_Actor **)Menu6B_N->unk174 = temp_s1->unk0;
            sp4F = 1;
        }
        row = &D_80033894[Menu6B_A->unk154];
        func_800317E8(sp5C, row->a, row->b, &sp54, &sp50, 2, 0, 1.8f);
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
        func_800317E8(sp5C, 160.0f, 150.0f, &sp54, &sp50, 2, 0, 1.8f);
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

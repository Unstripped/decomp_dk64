// func_8002CB18 (src/menu/3E10.c): stage 5 (parked NON_MATCHING): frame 0x68, sp5C=92/&sp50=80/&sp54=84/idx 76/spill a2 56 and all hoisted lui/lbu structure now match the target (harness diff 154 -> 47 lines, rest is the t-reg ring). Remaining: 'lw t5,4(s1); beq t5,a2; nop' (mine 'lw t5,4(s1); beql a2,t5' + hoisted 'lbu v1,341(a0)' from the dead 'if (Menu6B_A->unk155 == 0) {}'/'temp_s1->unk4' dead stmts that promote temp_s1 to s1; without them temp_s1 is spilled and the diff is 150+), then one t-reg ring shift. NM4 harness (reduced TU, exhaustive dead stmt 'if (G && G)/(G==0)/(G)/(G!=0)' after every statement for sel/idx/a2/sp5C/temp_s1->fieldN/Menu6B_A->fieldN, 3 rounds beam 3, adjacent-swap sweep, 4000+6000 random decl-order perms with 0-3 pad locals, hill-climb 2900 iters). Found: (1) idx = D_80033F24[sel & 0xF] BEFORE temp_s1_2 = 0x140 / D_80033878 (fixes the hoisted lui t9/v0 and li 320 placement); (2) m8 = temp_s1->unk8 named s8 local before actorScriptStart(...(s16)(m8*6)...) gives 'lb v1,8(s1)'; (3) decl order temp_s1_2,row,sp5C,sel,sp54,sp50,sp4F,idx,a2,sp38,temp_s1,m8 gives the exact target stack layout (sp5C 92, sp50 80); (4) dead 'if (temp_s1->unk4 == 0) {}'-style stmts raise temp_s1 use count so it gets s1.
extern u8 D_80033878;
extern u8 D_80033F24[];
struct Menu3B_Struct_BB40;
extern struct Menu3B_Struct_BB40 *D_807FBB40;
typedef struct Menu6B_Vec {
    char pad0[0x34];
    f32 unk34;
    f32 unk38;
    f32 unk3C;
} Menu6B_Vec;
typedef struct Menu6B_Actor {
    char pad0[4];
    Menu6B_Vec *unk4;
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
    s32 a2;
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
        if (temp_s1->unk4 != a2) {
            func_8068A4C8(Menu6B_A, Menu6B_A->unk155 + 2, a2);
            temp_s1->unk4 = D_8076A100[Menu6B_A->unk154];
        if (Menu6B_A->unk155 == 0) {}
        a2 = D_8076A100[Menu6B_A->unk154];
        }
        if (temp_s1->unk8 != 0) {}
        idx = D_8076A0E4[Menu6B_A->unk154] & 0x7F;
        if (idx != Menu6B_A->unk155) {
            sp38 = &D_8003386C[idx];
            actorSpawn(0x151, *sp38);
            *Menu6B_N->unk17C = *sp38;
            Menu6B_N->unk154 = Menu6B_A->unk154;
            Menu6B_N->unk155 = idx;
            *(Menu6B_Actor **)Menu6B_N->unk174 = temp_s1->unk0;
            sp4F = 1;
        }
        row = &D_80033894[Menu6B_A->unk154];
        func_800317E8(sp5C, row->a, row->b, &sp54, &sp50, 2, 0, 1.8f);
        Menu6B_A->unk7C = D_807FBB4C->unk7C + (sp54 - 160.0f);
        if (temp_s1->unk4 != 0) {}
        Menu6B_A->unk80 = (D_807FBB4C->unk80 - (sp50 - 120.0f)) - 20.0f;
        if (temp_s1->unk8 == 0) {}
        Menu6B_A->unk84 = D_807FBB4C->unk84 - 300.0f;
        if (sp5C && sp5C) {}
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
        if (D_80033894) {}
    }
    if (*sp5C > 1.0f) {
        sp4F = 1;
    }
    if (sp4F != 0) {
        actorDespawn(Menu6B_A);
    }
    actorUpdateModelMatrix(Menu6B_A, 0);
}

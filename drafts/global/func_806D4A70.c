// func_806D4A70 (src/global/D5E10.c): Stage 6 regalloc only: target hoists 'lui v1,%hi(D_807FD580)' into the switch head (P in v1, selector v0); mine puts P in v0 (lui after case-0 label). Uses G08_A40 view (G08Actor unk6A/unkC0/unkC4/unkEE/unk155). Tried u8/s32 sel, if-chain, unused P local, permuter 280s (best 340/346).
typedef struct G12Player {
    /* 0x00 */ u8 pad0[0x38];
    /* 0x38 */ f32 unk38;
    /* 0x3C */ u8 pad3C[2];
    /* 0x3E */ s16 unk3E;
    /* 0x40 */ s16 unk40;
} G12Player;

#define G12_P ((G12Player *)D_807FD580)

void func_806F142C();

void func_806D4A70(void) {
    switch (G08_A40->unk155) {
    case 0:
        if (G12_P->unk3E != 0) {
            func_806CC14C(G08_A40->unkEE, G12_P->unk40);
            func_806CD424(G12_P->unk40, 50.0f, G12_P->unk38);
            G12_P->unk3E--;
        }
        func_806CC8B8();
        if (G08_A40->unkC0 <= -15.0f) {
            G08_A40->unkC0 = -15.0f;
            G08_A40->unk155++;
        }
        func_806DF6D4(0x24);
        if (G08_A40->unk6A & 1) {
            func_806F142C(D_807FBB40);
        }
        break;
    case 1:
        func_806DF6D4(0x24);
        if (G12_P->unk3E != 0) {
            func_806CC14C(G08_A40->unkEE, G12_P->unk40);
            func_806CD424(G12_P->unk40, 30.0f, G12_P->unk38);
            G12_P->unk3E--;
        }
        func_806CC8F0();
        if (G08_A40->unk6A & 1) {
            func_806F142C(D_807FBB40);
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 1, 0xFF, 0x7F, 0x1E);
        }
        break;
    case 2:
        G08_A40->unkC4 = -4.0f;
        func_806DF6D4(0x24);
        func_806CC8B8();
        if (G08_A40->unk6A & 1) {
            func_806F142C(D_807FBB40);
        }
        break;
    }
    func_806319C4(D_807FBB40, 0);
}

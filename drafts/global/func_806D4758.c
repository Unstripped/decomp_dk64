// func_806D4758 (src/global/D5E10.c): stage 6, text-identical only when func_806CC14C is declared void in D5E10.c; func_806D332C uses its s32 return, so one declaration cannot serve both (needs another regalloc trick for the D_807FD580 candidate)
// needs the G11Actor/G11Player views and G11_A/G11_P macros from src/global/D5E10.c
void func_806CC14C(s16, s16);

void func_806D4758(void) {
    s32 sel = G11_A->unk155;
    switch (sel) {
        case 0:
            if (G11_P->unk3E != 0) {
                func_806CC14C(G11_A->unkEE, G11_P->unk40);
                func_806CD424(G11_P->unk40, 50.0f, G11_P->unk38);
                G11_P->unk3E--;
            }
            func_806DF6D4(0x23);
            if (D_8074E77C[D_807FC929] == 2) {
                G11_P->unk4 = G11_P->unk4 * 0.63;
            }
            func_806CC8B8();
            break;
        case 1:
            func_806DF6D4(0x23);
            sel = D_8074E77C[D_807FC929];
            if (sel == 0 || sel == 2) {
                G11_P->unk4 = G11_P->unk4 * 0.63;
            }
            func_806CFE7C();
            func_806D3608();
            func_806CC8B8();
            break;
        case 2:
            func_806CC8B8();
            if (func_806DF6D4(0x31) == 0 && G11_A->unkB8 < G11_P->unk4) {
                func_806CFF9C(D_807FBB40);
            }
            break;
    }
    func_806319C4(D_807FBB40, 0);
}

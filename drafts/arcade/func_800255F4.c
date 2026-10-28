// func_800255F4 (src/arcade/0.c): TEXT-IDENTICAL, reloc only: the three 'lb ...,3(v1)' after D_807ECDE8 loads are %lo(D_807F0003) relocs in the splat asm (splat mis-symbolisation); instruction stream equals the C below. Use tools/drafts.py paste + ROM hash.
void func_8060C8AC(s32);
void func_800255F4(Gfx **arg0) {
    Gfx *sp2C;

    sp2C = *arg0;
    func_800259D0(&sp2C);
    arcadeRenderEntities(&sp2C);
    if ((D_807ECD48 & 0x800) || ((s8)D_807ECDE8[3] >= 0x1F && D_8004C70C < 0x1F)) {
        D_8004A768--;
    }
    if ((D_807ECD48 & 0x400) || ((s8)D_807ECDE8[3] < -0x1E && D_8004C70C >= -0x1E)) {
        D_8004A768++;
    }
    if (D_8004A768 >= 3) {
        D_8004A768 = 0;
    }
    if (D_8004A768 < 0) {
        D_8004A768 = 2;
    }
    D_8004C70C = (s8)D_807ECDE8[3];
    if (D_807ECD48 & 0x1000) {
        arcadeClearEntitiesByType1C();
        D_8004C724 = 5;
    }
    if (D_807ECD48 & 0xC000) {
        switch (D_8004A768) {
        case 0:
            arcadeClearEntitiesByType1C();
            D_8004C724 = 5;
            break;
        case 1:
            if (D_8004A744 == 0) {
                func_8060C8AC(2);
                arcadeLoadHighScores();
                arcadeSaveHighScores();
                if (D_8004A760 < D_8004A748) {
                    D_8004A760 = D_8004A748;
                }
                D_8004A744 = 1;
            }
            break;
        case 2:
            arcadeExit();
            break;
        }
    }
    *arg0 = sp2C;
}

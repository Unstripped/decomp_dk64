// func_806FACE8 (src/global/FCCD0.c): Stage 1 complete selector mapping compiles in private copy; direct nested switches reproduce the target structure but block ordering and a 4-byte local-slot difference remain.
// Behavioural stage-1 reconstruction; selector maps text mode and current player to text asset addresses.
extern s32 D_807200A0, D_807201A0, D_80720268, D_8072029C, D_807203B0, D_807203D4, D_807203F8, D_8072041C, D_80720440, D_80720488, D_807204BC, D_80720508, D_8072052C, D_80720558, D_8072057C, D_807205A0, D_807205C4, D_807205E8, D_8072060C, D_807206A8, D_807207BC, D_807207E0, D_80720854, D_80720878, D_80720890, D_807208A8, D_807208C0, D_807208D8, D_807209EC, D_80720A10, D_80720A34, D_80720A58, D_80721200, D_8072121C, D_80721250, D_8072145C, D_807214A0, D_807214B8, D_807214D0, D_807214E8, D_80721500, D_80754288;

s32 func_806FACE8(s32 type) {
    s32 player = func_806C8DE0(0);
    static s32 *const group0[] = { &D_807205E8, &D_8072057C, &D_807205C4, &D_8072060C, &D_807205A0, &D_807205A0 };
    static s32 *const group1[] = { &D_8072041C, &D_807203B0, &D_807203F8, &D_80720440, &D_807203D4, &D_807203D4 };
    static s32 *const group2[] = { &D_807206A8, &D_807200A0, &D_8072029C, &D_80720854, &D_807201A0, &D_80720268 };
    static s32 *const group7[] = { &D_80720890, &D_80720878, &D_807208D8, &D_807208A8, &D_807208C0, &D_807208C0 };
    static s32 *const group12[] = { &D_80720A34, &D_807209EC, &D_80720A58, &D_80720A10, &D_807207E0, &D_807207E0 };

    if (type == 13) player = D_80754288;
    switch (type) {
    case 0: case 14: return (player < 6) ? (s32)group0[player] : 0;
    case 1: return (player < 6) ? (s32)group1[player] : 0;
    case 2: case 3: return (player < 6) ? (s32)group2[player] : 0;
    case 4: return (s32)&D_807204BC;
    case 5: return (s32)&D_80720508;
    case 6: return (s32)&D_80720488;
    case 7: return (player < 6) ? (s32)group7[player] : 0;
    case 8: case 9: return (s32)&D_8072052C;
    case 10: return (s32)&D_80720558;
    case 11: return (s32)&D_807207BC;
    case 12: return (player < 6) ? (s32)group12[player] : 0;
    case 15: return (s32)&D_8072145C;
    case 16: return (s32)&D_80721250;
    case 17: return (s32)&D_80721200;
    case 18: return (s32)&D_8072121C;
    case 19: return (s32)&D_807214A0;
    case 20: return (s32)&D_807214B8;
    case 21: return (s32)&D_807214D0;
    case 22: return (s32)&D_807214E8;
    case 23: return (s32)&D_80721500;
    }
    return 0;
}

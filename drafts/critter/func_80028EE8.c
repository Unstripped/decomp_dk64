// func_80028EE8 (src/critter/4840.c): C1 stage 4 (parked NON_MATCHING): frame 0x30 ok; arg4 (s16) reused as loop var, arg5 u16, sp24 named s32, locals order s0,sp2A,sp24. Remaining: D_8002A1C4 address not CSE'd in entry block (target: lui v1/addiu v1/lw a1,0(v1); else-branch uses a0 for &D_807FBB44 and v1 for &D_8002A1C4 store); sp24 spill at 0x20 vs target 0x24; call must cast (TextData*)s0,(char*)(D_8002A1C0+sp24).
void func_80028EE8(u8 arg0, s32 arg1, s16 arg2, u8 arg3, s16 arg4, u16 arg5) {
    u8 *s0;
    s16 sp2A;
    s32 sp24;

    sp24 = arg3 << 5;
    sp2A = (D_80744490 - func_806FBD5C(arg0, D_8002A1C0 + sp24)) * 2;
    if (D_8002A1C4 != NULL) {
        s0 = D_8002A1C4->unk174;
        heapFree(*(void **)(s0 + 8));
        heapFree(*(void **)(s0 + 4));
    } else {
        actorSpawn(0x10A, 0);
        s0 = D_807FBB44->unk174;
        *(s16 *)s0 = arg2 * 4;
        D_8002A1C4 = D_807FBB44;
        D_807FBB44->unkEC = 0;
    }
    D_8002A1C4->unk7C = (f32)func_800288A8((TextData *)s0, (char *)(D_8002A1C0 + sp24), sp2A);
    D_8002A1C4->unkEE = 0;
    D_8002A1C4->unk168 = arg5 + 0xE;
    _strcpy((char *)s0 + 0x820, (char *)(D_8002A1C0 + sp24));
    arg4 = 1;
    do {
        s0[0x810 + arg4] = 0;
        arg4++;
    } while (arg4 < 0x10);
    s0[0x810] = 0xC;
}

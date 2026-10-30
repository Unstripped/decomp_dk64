// func_8069A750 (src/global/9DD70.c): stage 2: target keeps (beq v0,2,latch; nop; beq v0,3,latch; nop; latch) - both tests survive, both go to the loop latch, no back-branch. Typed list view ((S9B_ActorList*)&D_807FBB70)->unk7C[i] fixes the base reloc/IV regs. Test-retaining forms found: nested for(;;){if(x==2||x==3)break;} (not equivalent: infinite wait) and 'if (x==2 ? 1 : x==3) ;' (36 lines, only the x==2 test kept as bne+b). ~200 variants (empty/continue/switch/goto/do-while0/dead stores/ternaries/expr statements) delete both tests or give a wrong shape
extern u8 D_807FBBA9;

typedef struct {
    u8 pad0[0x7C];
    Actor *unk7C[4];
} S9B_ActorList;

s32 func_8069A750(void) {
    s32 i;

    for (i = 0; i < D_807FBBA9; i++) {
        if (((S9B_ActorList *)&D_807FBB70)->unk7C[i]->unk58 == 2 ? 1 : ((S9B_ActorList *)&D_807FBB70)->unk7C[i]->unk58 == 3) ;
    }
    if (D_807FBB40->unk58 == 0x1F) {
        return 0;
    }
    return 0;
}

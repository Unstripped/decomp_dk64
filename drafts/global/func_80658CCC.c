// func_80658CCC (src/global/55B20.c): TEXT-IDENTICAL, reloc only: indexed for(i<10) over ((MapSearchEntry*)&D_807F7290)[i] makes uopt build the IV/end ptr (end reloc = D_807F7290+0xC8 vs splat's D_807F7358 label); pointer do-while forms differ only in preheader hoist order. Orchestrator: paste + ROM gate.
extern s32 zbufferReadDepth(s16, s16);
extern s32 zbufferDepthToDistance(s32);

void func_80658CCC(void) {
    s32 i;

    for (i = 0; i < 10; i++) {
        if (((MapSearchEntry *)&D_807F7290)[i].unk10 != 0) {
            if (D_8076A064 == ((MapSearchEntry *)&D_807F7290)[i].unkC) {
                if ((f32)zbufferDepthToDistance((s16)zbufferReadDepth(((MapSearchEntry *)&D_807F7290)[i].unk4, ((MapSearchEntry *)&D_807F7290)[i].unk6)) <= (f32)((MapSearchEntry *)&D_807F7290)[i].unk8) {
                    ((MapSearchEntry *)&D_807F7290)[i].unk11 = 1;
                } else {
                    ((MapSearchEntry *)&D_807F7290)[i].unk11 = 0;
                }
            }
        }
        if ((u32)(D_8076A064 - ((MapSearchEntry *)&D_807F7290)[i].unkC) >= 3) {
            ((MapSearchEntry *)&D_807F7290)[i].unk10 = 0;
        }
    }
}

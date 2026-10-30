// func_80653804 (src/global/55B20.c): stage 4 (S55c): frame 0xC8 + callee-saved set match; score 202->136 by statement order fs4=arg2; fs3=arg1; then fs5/sp38/fs1/fs2 (e3). Remaining: arg1 spilled to home (sw a1,204(sp)) with arg2 in f14 -- target moves BOTH args first (mtc1 a1,f14; mtc1 a2,f20) and loads lh unk2,unk4,unk10,unkE before unk0/unkC; arg2 candidate 'not colored, not splittable' in uopt trace; f64 callee coloring still rotated (fs5=f22 vs f30). inline (f64)arg1/arg2 uses balloon frame to 0x148. decl-order permutations of the f64 locals (60 random) and deadsweep give nothing legitimate
s32 func_80653804(void *arg0, f32 arg1, f32 arg2) {
    f64 lead0;
    f64 lead1;
    f64 lead2;
    f64 lead3;
    f64 spA0;
    f64 sp98;
    f64 sp90;
    f64 sp88;
    f64 pad2;
    f64 pad3;
    f64 pad4;
    f64 pad5;
    f64 pad6;
    f64 pad7;
    f64 pad8;
    f64 sp38;
    f64 fs1;
    f64 fs2;
    f64 fs3;
    f64 fs4;
    f64 fs5;
    f64 ft4;
    f64 ft5;
    f64 fa0;
    f64 fa1;
    f64 fv0;
    f64 fv1;
    f64 fs0;
    s32 sgn1;
    s32 sgn2;
    s32 flag;
    s32 i;

    fs4 = arg2;
    fs3 = arg1;
    fs5 = ((MapCollisionNode *)arg0)->unk0;
    sp38 = ((MapCollisionNode *)arg0)->unkC;
    fs1 = (fs5 + ((f64)(((MapCollisionNode *)arg0)->unk4 + ((MapCollisionNode *)arg0)->unk2) * 0.5)) * 0.5;
    fs2 = (sp38 + ((f64)(((MapCollisionNode *)arg0)->unk10 + ((MapCollisionNode *)arg0)->unkE) * 0.5)) * 0.5;
    ft5 = sp88;
    ft4 = sp90;
    fa1 = sp98;
    fa0 = spA0;
    flag = 0;
    i = 0;
    do {
        switch (i) {
        default:
            fv0 = (fs3 - ft4) * fa1;
            fv1 = (fs4 - ft5) * fa0;
            fs0 = ((fs1 - ft4) * fa1) - ((fs2 - ft5) * fa0);
            break;
        case 0:
            ft4 = fs5;
            ft5 = sp38;
            fa1 = (f64)(((MapCollisionNode *)arg0)->unkE - ((MapCollisionNode *)arg0)->unkC);
            fa0 = (f64)(((MapCollisionNode *)arg0)->unk2 - ((MapCollisionNode *)arg0)->unk0);
            fv0 = (fs3 - fs5) * fa1;
            fv1 = (fs4 - ft5) * fa0;
            fs0 = ((fs1 - fs5) * fa1) - ((fs2 - ft5) * fa0);
            break;
        case 1:
            ft4 = fs5;
            ft5 = sp38;
            fa1 = (f64)(((MapCollisionNode *)arg0)->unk10 - ((MapCollisionNode *)arg0)->unkC);
            fa0 = (f64)(((MapCollisionNode *)arg0)->unk4 - ((MapCollisionNode *)arg0)->unk0);
            fv0 = (fs3 - fs5) * fa1;
            fv1 = (fs4 - ft5) * fa0;
            fs0 = ((fs1 - fs5) * fa1) - ((fs2 - ft5) * fa0);
            break;
        case 2:
            ft4 = (f64)((MapCollisionNode *)arg0)->unk2;
            ft5 = (f64)((MapCollisionNode *)arg0)->unkE;
            fa0 = (f64)(((MapCollisionNode *)arg0)->unk4 - ((MapCollisionNode *)arg0)->unk2);
            fa1 = (f64)(((MapCollisionNode *)arg0)->unk10 - ((MapCollisionNode *)arg0)->unkE);
            fv0 = (fs3 - ft4) * fa1;
            fv1 = (fs4 - ft5) * fa0;
            fs0 = ((fs1 - ft4) * fa1) - ((fs2 - ft5) * fa0);
            break;
        }
        i++;
        sgn1 = -1;
        if (fv1 <= fv0) {
            sgn1 = 1;
        }
        sgn2 = -1;
        if (fs0 >= 0.0) {
            sgn2 = 1;
        }
        if (sgn2 != sgn1) {
            flag = 1;
        }
    } while (i != 3);
    sp88 = ft5;
    sp90 = ft4;
    sp98 = fa1;
    spA0 = fa0;
    return (flag == 0) & 0xFF;
}

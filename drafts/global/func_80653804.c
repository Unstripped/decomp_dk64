// func_80653804 (src/global/55B20.c): stage 4: behaviour complete; 4 uninit f64 locals (sp88/sp90/sp98/spA0) copied in/out and one sp38 t1 holder; frame 0xD8 vs 0xC8 = 2 extra spilled f64 temps above spA0 (slot offsets of spA0/sp98/sp90/sp88 @0xA0/0x98/0x90/0x88 and sp38@0x38 already match); identical asm to func_80654FEC
typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ u8 pad6[6];
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ u8 pad12[2];
} M55P3Tri;

s32 func_80653804(void *arg0, f32 arg1, f32 arg2) {
    f64 lead0;
    f64 lead1;
    f64 lead2;
    f64 lead3;
    f64 spA0;
    f64 sp98;
    f64 sp90;
    f64 sp88;
    f64 pad0;
    f64 pad1;
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

    fs3 = arg1;
    fs4 = arg2;
    fs5 = ((M55P3Tri *)arg0)->unk0;
    sp38 = ((M55P3Tri *)arg0)->unkC;
    fs1 = (fs5 + ((f64)(((M55P3Tri *)arg0)->unk4 + ((M55P3Tri *)arg0)->unk2) * 0.5)) * 0.5;
    fs2 = (sp38 + ((f64)(((M55P3Tri *)arg0)->unk10 + ((M55P3Tri *)arg0)->unkE) * 0.5)) * 0.5;
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
            fa1 = (f64)(((M55P3Tri *)arg0)->unkE - ((M55P3Tri *)arg0)->unkC);
            fa0 = (f64)(((M55P3Tri *)arg0)->unk2 - ((M55P3Tri *)arg0)->unk0);
            fv0 = (fs3 - fs5) * fa1;
            fv1 = (fs4 - ft5) * fa0;
            fs0 = ((fs1 - fs5) * fa1) - ((fs2 - ft5) * fa0);
            break;
        case 1:
            ft4 = fs5;
            ft5 = sp38;
            fa1 = (f64)(((M55P3Tri *)arg0)->unk10 - ((M55P3Tri *)arg0)->unkC);
            fa0 = (f64)(((M55P3Tri *)arg0)->unk4 - ((M55P3Tri *)arg0)->unk0);
            fv0 = (fs3 - fs5) * fa1;
            fv1 = (fs4 - ft5) * fa0;
            fs0 = ((fs1 - fs5) * fa1) - ((fs2 - ft5) * fa0);
            break;
        case 2:
            ft4 = (f64)((M55P3Tri *)arg0)->unk2;
            ft5 = (f64)((M55P3Tri *)arg0)->unkE;
            fa0 = (f64)(((M55P3Tri *)arg0)->unk4 - ((M55P3Tri *)arg0)->unk2);
            fa1 = (f64)(((M55P3Tri *)arg0)->unk10 - ((M55P3Tri *)arg0)->unkE);
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

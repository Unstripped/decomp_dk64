// func_806AC07C (src/global/ACDC0.c): stage 4: frame 0x58 ok, switch/cases structurally close (type/item/t copies match); remaining: item ptr a2 vs v1/a3 head regs, t=0.0f mtc1 vs mov.s, (s16) arg 'sra t; move a0' pattern, D_8076A064 temp v0, ~50 insn diffs, text 16B short
typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
} L7_Item;

typedef struct {
    f32 unk0;
    f32 unk4;
    u8 pad8[4];
    s16 tbl[4];
    u8 pad14;
    s8 unk15;
} L7_Src;

typedef struct {
    u8 pad0[0x340];
    f32 unk340;
    f32 unk344;
    u8 pad348[0x35C - 0x348];
    L7_Src *unk35C;
    f32 unk360;
    f32 unk364;
    u8 pad368[2];
    u8 unk36A;
    u8 unk36B;
    u8 unk36C;
    u8 unk36D;
    u8 pad36E[0x384 - 0x36E];
    L7_Item *unk384;
} L7_Hud;

f32 func_806119FC(void);
f32 func_80612790(s16);
f32 func_80612794(s16);
extern f32 D_807FC808;
extern f32 D_807FC840[];
extern f32 D_807FC868[];
extern f32 D_807FC890[];
extern s8 D_80750530[];
extern u8 D_8075054C[][4];
extern s32 D_8076A064;

void func_806AC07C(L7_Hud *arg0, s8 *arg1) {
    L7_Src *src;
    L7_Item *item;
    f32 t;
    f32 sc;
    s32 type;
    s32 sp40;
    s32 tmp;
    s16 ang;
    s32 i;

    src = arg0->unk35C;
    if (arg0->unk384 != NULL) {
        t = src->unk0;
        item = arg0->unk384;
        sp40 = (f64)src->tbl[(s32)item->unk4] * 4.0;
        type = (s32)arg0->unk384->unk0;
        switch (type) {
        case 0:
        case 4:
        case 11:
        case 12:
            t = 1.0 - src->unk0;
            if (t < 0.0f) {
                t = 0.0f;
            }
            if (t > 1.0f) {
                t = 1.0f;
            }
            arg0->unk36D = (s32)(t * 255.0f);
            if (type == 4) {
                arg0->unk360 = (f64)(item->unk10 * t) * 4.0;
                arg0->unk364 = arg0->unk360;
            }
            arg0->unk340 = item->unk8;
            arg0->unk344 = item->unkC + (f32)sp40;
            if (type == 0xB) {
                arg0->unk340 = 600.0 - D_807FC808;
            }
            if (type == 0xC) {
                arg0->unk340 = D_807FC808 + 680.0;
            }
            t = 0.0f;
            break;
        case 1:
        case 2:
        case 7:
            if (type != 1) {
                t += src->unk4;
            }
            if (type == 7) {
                arg0->unk364 = (f64)func_80612794((D_8076A064 * 0x78) & 0xFFF) * 0.35 + item->unk18;
            }
            arg0->unk340 = item->unk10 * t + item->unk8;
            arg0->unk344 = item->unk14 * t + item->unkC + (f32)sp40;
            break;
        case 3:
        case 5:
        case 8:
        case 15:
            t = 1.0 - src->unk0;
            if (t < 0.0f) {
                t = 0.0f;
            }
            if (t > 1.0f) {
                t = 1.0f;
            }
            sc = 180.0f;
            ang = (s32)((f64)item->unk8 * 0.25) - src->tbl[2];
            if (type != 3) {
                sc = 240.0f;
            }
            sc = sc * t;
            arg0->unk360 = (f64)(item->unk10 * t) * 4.0;
            arg0->unk364 = arg0->unk360;
            t = 0.0f;
            arg0->unk340 = (f64)(func_80612794(ang) * sc) + 640.0;
            arg0->unk344 = (480.0 - (f64)(func_80612790(ang) * sc)) + (f64)sp40;
            if (type == 8) {
                arg0->unk344 = arg0->unk344 + func_80612794((D_8076A064 * 0x78) & 0xFFF) * 10.0f;
            }
            if (type == 0xF) {
                arg0->unk364 = arg0->unk364 * (1.0 + (f64)func_80612794((D_8076A064 * 0x78) & 0xFFF) * 0.2);
            }
            if (type == 5 || type == 8 || type == 0xF) {
                i = 0xFF - (s32)(((f64)arg0->unk344 - 240.0) * 1.5);
                if (i < 0x5F) {
                    i = 0x5F;
                }
                if (i >= 0x100) {
                    i = 0xFF;
                }
                arg0->unk36A = i;
                arg0->unk36B = i;
                arg0->unk36C = i;
            }
            break;
        case 6:
            if ((item->unk14 - item->unk1C) * (item->unk14 - item->unk1C) + (item->unk10 - item->unk18) * (item->unk10 - item->unk18) < 400.0f) {
                item->unk24 = (f64)item->unk24 - 1.0;
                if ((f64)item->unk24 < 0.0) {
                    item->unk20 = (f64)item->unk20 + (1000.0 + (f64)func_806119FC() * 2000.0);
                    tmp = (s32)item->unk20 & 0xFFF;
                    item->unk20 = tmp;
                    sc = ((f64)func_806119FC() * 40.0 + 20.0) * 4.0;
                    ang = tmp;
                    item->unk18 = (f64)func_80612794(ang) * ((f64)sc * 0.8);
                    item->unk1C = func_80612790(ang) * sc;
                    if ((f64)func_806119FC() < 0.25) {
                        item->unk24 = (f64)func_806119FC() * 40.0 + 15.0;
                    } else {
                        item->unk24 = 0.0f;
                    }
                }
            }
            sc = (f64)(item->unk18 - item->unk10) * 0.1;
            if (sc < -8.0) {
                sc = -8.0f;
            }
            if (sc > 8.0) {
                sc = 8.0f;
            }
            item->unk10 = item->unk10 + sc;
            sc = (f64)(item->unk1C - item->unk14) * 0.1;
            if (sc < -8.0) {
                sc = -8.0f;
            }
            if (sc > 8.0) {
                sc = 8.0f;
            }
            item->unk14 = item->unk14 + sc;
            arg0->unk340 = item->unk10 + item->unk8;
            sc = func_80612794((D_8076A064 * 0x78) & 0xFFF);
            arg0->unk344 = sc * 10.0f + (item->unkC + item->unk14 + (f32)sp40 + 960.0f * t);
            t = 0.0f;
            break;
        case 10:
            i = (s32)item->unk8;
            arg0->unk340 = D_807FC840[i];
            arg0->unk344 = D_807FC868[i];
            arg0->unk360 = D_807FC890[i];
            arg0->unk364 = D_807FC890[i];
            D_807FC840[i] = -200.0f;
            D_807FC868[i] = -200.0f;
            if (i >= 5) {
                i -= 5;
            }
            if (D_80750530[i] == 0) {
                arg0->unk36A = D_8075054C[i][0];
                arg0->unk36B = D_8075054C[i][1];
                arg0->unk36C = D_8075054C[i][2];
            }
            break;
        }
        if (src->unk15 != (s32)item->unk4 && (sp40 < -0x3C0 || sp40 >= 0x3C1)) {
            *arg1 = 1;
        }
        if (t > 1.0f || src->unk0 > 1.0f) {
            *arg1 = 1;
        }
    }
}

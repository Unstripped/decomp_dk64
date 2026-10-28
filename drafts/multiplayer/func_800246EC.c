// func_800246EC (src/multiplayer/0.c): stage 5 (frame 0xB0, 12 saves, f20/f22 match; harness diff 134 lines of 203 = regalloc cascade + scheduling). Remaining: arg1 in s8 / &spAE in s7 (target s7/fp), D_807FC928 count in t8 not a3, sc address (i*0x306+D_807FC950) computed after the D_80750AB8 branch instead of before it, extra addiu s2 / mtc1 a2,f22 ordering in the Gfx header, alpha clamp shape (target: slti; bnez; andi v1; b; li v1,255 = if/else with default kept; mine drops the else store). Matched: header words via gSPSetOtherMode(L,3,29,0x404240)+gDPSetCombine(0xFFFFFF,0xFFFCF279)+gSPMatrix+gDPSetTextureFilter(POINT)+gDPSetTexturePersp(NONE); rem = sc - half*2 (not sc%2); sc via two vars tmp(s32 lb)/sc clamp; locals needed to hit 0xB0: drop rem and the s16 t temp (frame grows 8 with 2 extra locals). Permuter 25 min: no gain.
typedef struct MpA_246_Act {
    char pad[0x128];
    s16 unk128;
} MpA_246_Act;

typedef struct MpA_246_Plr {
    u8 unk0;
    char pad1[3];
    MpA_246_Act *unk4;
    char pad2[0x2EA - 8];
    u8 unk2EA;
    char pad3[0x2F0 - 0x2EB];
} MpA_246_Plr;

typedef struct MpA_246_Sc {
    char pad[0x2FB];
    s8 unk2FB;
    char pad2[0x306 - 0x2FC];
} MpA_246_Sc;

Gfx *func_800246EC(Gfx *glistp, void *arg1v, f32 arg2) {
#define arg1 ((Struct_800246EC_Arg1_MpLow *)arg1v)
    s16 spAE;
    s32 i;
    s32 nxt;
    s32 off;
    s32 sc;
    s32 tmp;
    s32 half;
    s16 y;
    u8 alpha;
    Struct_800246EC_Sub_MpLow *sub;
    MpA_246_Plr *plr;
    Struct_800246EC_Arg1_MpLow *p;

    gDPPipeSync(glistp++);
    gSPDisplayList(glistp++, &D_1000118);
    gSPSetOtherMode(glistp++, G_SETOTHERMODE_L, 3, 29, 0x404240);
    gDPSetCombine(glistp++, 0xFFFFFF, 0xFFFCF279);
    gSPMatrix(glistp++, &D_20000C0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gDPSetTextureFilter(glistp++, G_TF_POINT);
    gDPSetTexturePersp(glistp++, G_TP_NONE);
    i = 0;
    if ((s32) D_807FC928 > 0) {
        p = arg1;
        off = 0;
        do {
            sub = p->unk20[0];
            alpha = 0xFF;
            plr = (MpA_246_Plr *)(D_807FC924 + off);
            if (plr->unk2EA != 0) {
                alpha = plr->unk4->unk128 & 0xFF;
                if (plr->unk4->unk128 >= 0x100) {
                    alpha = 0xFF;
                }
            }
            if (plr->unk0 == 0 || alpha == 0) {
                nxt = i + 1;
            } else {
                gDPSetPrimColor(glistp++, 0, 0, 255, 255, 255, alpha);
                if (D_80750AB8 == 0) {
                    nxt = i + 1;
                    spAE = sub->unk8 - 0x30;
                } else {
                    nxt = i + 1;
                    spAE = (s16) ((f32) nxt * arg2 - 20.0);
                }
                tmp = ((MpA_246_Sc *)D_807FC950)[i].unk2FB;
                y = sub->unk6 + 8;
                if (tmp < 0) {
                    sc = 0;
                } else {
                    sc = tmp;
                }
                half = sc / 2;
                if (half != 0) {
                    glistp = mpDrawGlyph(glistp, &spAE, y, arg1->unk44, half);
                }
                tmp = sc - half * 2;
                if (tmp != 0) {
                    glistp = mpDrawGlyph(glistp, &spAE, y, arg1->unk48, tmp);
                }
            }
            i = nxt;
            p = (void *)((u8 *)p + 4);
            off += 0x2F0;
        } while (nxt < (s32) D_807FC928);
    }
    return glistp;
}
#undef arg1

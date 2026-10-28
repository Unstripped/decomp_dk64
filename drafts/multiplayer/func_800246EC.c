// func_800246EC (src/multiplayer/0.c): stage 5 (frame 0xB0, 12 saves match; harness 124 diff lines of 203, skeleton (opcode-only) diff 35). Best form: s32 alpha=0xFF default + s16 t named local, alpha=t&0xFF; if(t>=0x100) alpha=0xFF; tmp (s32 lb) / sc clamp split; rem=sc-half*2; tmp loaded before the D_80750AB8 arms (puts the i*0x306 chain before the branch like target). Remaining: arg1 in s8/&spAE s7 (target s7/fp: adjsave arg1 3.0 < &spAE 3.33, extra arg1 reads did not help), lb v0,2FB(a0) issued before the arms in mine (target after join, only the address chain before), alpha uses a0/v0 where target uses v1/a0 and has a 'b' after slti/bnez/andi, header scheduling (addiu s2 / mtc1 a2,f22 order). Tried without gain: p/off derived IVs, g44/g48 early reads, s16 casts, if/else clamp forms, u8 alpha. Permuter 25 min: nothing.
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
    s32 alpha;
    s16 t;
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
                t = plr->unk4->unk128;
                alpha = t & 0xFF;
                if (t >= 0x100) {
                    alpha = 0xFF;
                }
            }
            if (plr->unk0 == 0 || alpha == 0) {
                nxt = i + 1;
            } else {
                gDPSetPrimColor(glistp++, 0, 0, 255, 255, 255, alpha);
                tmp = ((MpA_246_Sc *)D_807FC950)[i].unk2FB;
                if (D_80750AB8 == 0) {
                    nxt = i + 1;
                    spAE = sub->unk8 - 0x30;
                } else {
                    nxt = i + 1;
                    spAE = (s16) ((f32) nxt * arg2 - 20.0);
                }
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

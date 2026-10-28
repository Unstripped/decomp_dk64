// func_800246EC (src/multiplayer/0.c): stage 4 (parked NON_MATCHING in src; frame 0xB0 now matches). Changes vs old draft: dropped named s16 t (read plr->unk4->unk128 inline) -> frame 184 -> 176 (locals p/off/t/plr: removing any one fixes it, they saturate); alpha clamp 'alpha=Z&0xFF; if (Z>=0x100) alpha=0xFF; else alpha=Z&0xFF;' reproduces target 'slti/bnez/andi/b/li 255' exactly with v1/a0 regs. Remaining: glistp s3/nxt s2 swapped vs target (uopt: with the else block glistp adjsave 11.5 < nxt 12.5, target glistp > nxt) and arg1 s8/&spAE s7 swap (3.0 vs 3.33); header sched (mtc1 a2,f22 earlier, addiu s2 order); i*0x306 chain computed before D_80750AB8 branch but lb after join (target) vs ours chain+lb after/before; 'slt at,s3,a3' vs placement. Tried: named ptr/sc cast for chain, pa pointer for &spAE (+8 frame), no-p/no-off (loses off IV), decl perms (no effect), nxt top hoist.
#include "common.h"

typedef struct Struct_800246EC_Sub_MpLow {
    char pad[0x6];
    s16 unk6;
    s16 unk8;
} Struct_800246EC_Sub_MpLow;

typedef struct Struct_800246EC_Arg1_MpLow {
    char pad[0x20];
    Struct_800246EC_Sub_MpLow *unk20[4];
    char pad2[0x14];
    void *unk44;
    void *unk48;
} Struct_800246EC_Arg1_MpLow;

extern u8 D_80750AB8;
extern u8 D_1000118[];
extern u8 D_20000C0[];
extern u8 D_807FC950[];
extern u8 D_807FC928;
extern u8 *D_807FC924;
Gfx *mpDrawGlyph(Gfx *glistp, s16 *arg1, s16 arg2, void *arg3, s32 arg4);

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
                } else {
                    alpha = plr->unk4->unk128 & 0xFF;
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

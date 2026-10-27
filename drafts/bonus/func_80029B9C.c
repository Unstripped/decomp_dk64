// func_80029B9C (src/bonus/2690.c): Stage 4: frame 0x40 + callee-saved set match; only diff is $v0/$v1 swap of the unk178/unk174 CSE temps (target v1=unk178,v0=unk174; ours reversed) and the t-reg/stack slot spill order that follows. uopt priority: E178 temp adjsave 3.0 (p0,p1 stores) beats E174 1.5 so it takes $v0. Making the cond read arg1->unk174 (merging E174) fixes the order but arg1 then loses its $s0 promotion (frame 0x38). Tried: init/decl orders of p0/p1/p2, chained assigns, p1=p0, cond via arg1/p2, no actor var, permuter 20min.
typedef struct {
    char pad0[3];
    u8 unk3;
    char pad4[2];
    char unk6[2];
    char unk8[2];
    s16 unkA;
} BonusC_9B9C_A;

typedef struct {
    char pad0[0x11];
    u8 unk11;
    char unk12[2];
    char unk14[2];
    s16 unk16;
} BonusC_9B9C_B;

typedef struct {
    char pad0[0x25];
    u8 unk25;
    char unk26[2];
    char unk28[2];
    s16 unk2A;
} BonusC_9B9C_C;

Gfx *func_80029B9C(Gfx *gdl, Actor_BB44 *arg1) {
    Actor_BB44 *actor;
    BonusC_9B9C_B *p0 = arg1->unk178;
    BonusC_9B9C_A *p1 = arg1->unk178;
    BonusC_9B9C_C *p2 = (void *)arg1->unk174;

    actor = arg1;

    if (actor->unk58 != 0x7E && actor->unk154 == 0 && ((u8 *)actor->unk174)[0x26] != 0) {
        gdl = func_80026690();
    }
    gSPDisplayList(gdl++, &D_1000118);
    gDPPipeSync(gdl++);
    gDPSetPrimColor(gdl++, 0, 0, 200, 200, 200, 255);
    gDPSetCombineMode(gdl++, G_CC_MODULATEIDECALA_PRIM, G_CC_MODULATEIDECALA_PRIM);
    gDPSetRenderMode(gdl++, G_RM_TEX_EDGE, G_RM_TEX_EDGE2);
    gSPMatrix(gdl++, &D_2000180, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    switch (actor->unk58) {
    case 0x7D:
        if (actor->unk154 != 3) {
            gdl = func_8068DC54(func_806FE078(gdl, p0->unk11, 8, 30.0f, 36.0f, 0.0f, 1.5f), 0x26, 0x32, p0->unk14, p0->unk16, p0->unk12);
        }
        break;
    case 0x7C:
        if (actor->unk154 != 3) {
            gdl = func_8068DC54(func_806FE078(gdl, p1->unk3, 8, 30.0f, 36.0f, 0.0f, 1.5f), 0x26, 0x32, p1->unk8, p1->unkA, p1->unk6);
        }
        break;
    case 0x7E:
        switch (actor->unk154) {
        case 7:
            break;
        case 0:
        case 1:
        case 2:
            gdl = func_8068DC54(func_806FE078(gdl, p2->unk25, 8, 30.0f, 36.0f, 0.0f, 1.5f), 0x26, 0x32, p2->unk28, p2->unk2A, p2->unk26);
            break;
        }
        break;
    }
    return gdl;
}

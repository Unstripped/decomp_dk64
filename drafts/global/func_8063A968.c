// func_8063A968 (src/global/36880.c): stage 5 (NM36C): real gbi macros (gDPPipeSync/SetCycleType/gSPClearGeometryMode/SetGeometryMode/gSPTexture/gDPSetRenderMode(G_RM_AA_ZB_XLU_DECAL)/gDPSetCombineMode(G_CC_MODULATERGBA_PRIM)/gDPSetPrimColor/gSPMatrix(MODELVIEW|MUL|PUSH)/gSPVertex/gSP2Triangles/gSPPopMatrix) + v=(Vtx*)(sp1A8[0]*16+(0,(u8*)vtxs)) cut diff 282->7 rows. Remaining: beql operand order (sp1BC vs unk0) and 3 spill slots 4 bytes low (a1 0x70, _g 0x8C/0x90 vs 0x74/0x94/0x90 target): target = one fewer home above + one extra word below the a1 temp (frame 0x1C0 both).
typedef struct R36880iNode {
    /* 0x00 */ u32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 unk9;
    /* 0x0A */ u8 unkA;
    /* 0x0B */ u8 unkB;
    /* 0x0C */ u8 padC[4];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ u8 pad24[2];
    /* 0x26 */ s16 unk26;
    /* 0x28 */ u8 pad28[7];
    /* 0x2F */ u8 unk2F;
    /* 0x30 */ u8 unk30;
    /* 0x31 */ u8 pad31[3];
    /* 0x34 */ struct R36880iNode *unk34;
} R36880iNode;

u32 osVirtualToPhysical(void *);

Gfx *func_8063A968(Gfx *arg0, R36880iNode *arg1) {
    s32 sp1BC[1];
    Vtx *vtxs;
    Mtx *mtxs;
    s32 n;
    R36880iNode *p;
    s32 sp1A8[1];
    s32 sp1A4;
    f32 sp164[4][4];
    f32 sp124[4][4];
    Vtx *v;
    s32 flag;

    sp1BC[0] = 0;
    sp1A8[0] = 0;
    sp1A4 = 0;
    flag = 1;

    if (arg1 != NULL) {
        gDPPipeSync(arg0++);
        gDPSetCycleType(arg0++, G_CYC_1CYCLE);
        gSPClearGeometryMode(arg0++, -1);
        gSPSetGeometryMode(arg0++, G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH);
        gSPTexture(arg0++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
        gDPSetRenderMode(arg0++, G_RM_AA_ZB_XLU_DECAL, G_RM_AA_ZB_XLU_DECAL2);
        gDPSetCombineMode(arg0++, G_CC_MODULATERGBA_PRIM, G_CC_MODULATERGBA_PRIM);
        n = 0;
        p = arg1;
        if (p != NULL) {
            do {
                p = p->unk34;
                n++;
            } while (p != NULL);
        }
        vtxs = func_80610FE8(n << 6);
        heapFreeDeferred(vtxs);
        mtxs = func_80610FE8(n << 6);
        heapFreeDeferred(mtxs);
    }
    if (arg1 != NULL) {
        v = (Vtx *)(sp1A8[0] * 16 + (0, (u8 *)vtxs));
        do {
            gDPPipeSync(arg0++);
            gDPSetPrimColor(arg0++, 0, 0, 0, 0, 0, arg1->unk2F);
            if (arg1->unk30 != 0 && flag == 0) {
                gSPSetGeometryMode(arg0++, G_ZBUFFER);
                gDPSetRenderMode(arg0++, G_RM_AA_ZB_XLU_DECAL, G_RM_AA_ZB_XLU_DECAL2);
                flag = 1;
            }
            if (arg1->unk30 == 0 && flag != 0) {
                gSPClearGeometryMode(arg0++, G_ZBUFFER);
                gDPSetRenderMode(arg0++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
                flag = 0;
            }
            if (arg1->unk0 != sp1BC[0]) {
                switch (arg1->unkB) {
                case 0:
                    gDPLoadTextureBlock_4b(arg0++, arg1->unk0 + 0x80000000, arg1->unkA, arg1->unk8, arg1->unk9, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                    break;
                case 1:
                    gDPLoadTextureBlock(arg0++, arg1->unk0 + 0x80000000, arg1->unkA, G_IM_SIZ_8b, arg1->unk8, arg1->unk9, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                    break;
                case 2:
                    gDPLoadTextureBlock(arg0++, arg1->unk0 + 0x80000000, arg1->unkA, G_IM_SIZ_16b, arg1->unk8, arg1->unk9, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                    break;
                }
                sp1BC[0] = arg1->unk0;
            }
            v[0].v.tc[0] = 0;
            v[0].v.tc[1] = 0;
            v[1].v.tc[0] = arg1->unk8 << 5;
            v[1].v.tc[1] = 0;
            v[2].v.tc[0] = arg1->unk8 << 5;
            v[2].v.tc[1] = arg1->unk9 << 5;
            v[3].v.tc[0] = 0;
            v[3].v.tc[1] = arg1->unk9 << 5;
            v[0].v.ob[1] = 0;
            v[1].v.ob[1] = 0;
            v[2].v.ob[1] = 0;
            v[3].v.ob[1] = 0;
            v[0].v.ob[0] = -arg1->unk10;
            v[0].v.ob[2] = -arg1->unk12;
            v[1].v.ob[0] = arg1->unk10;
            v[1].v.ob[2] = -arg1->unk12;
            v[2].v.ob[0] = arg1->unk10;
            v[2].v.ob[2] = arg1->unk12;
            v[3].v.ob[0] = -arg1->unk10;
            v[3].v.ob[2] = arg1->unk12;
            guScaleF(sp164, arg1->unk4, 1.0f, arg1->unk4);
            guRotateF(sp124, (f32)arg1->unk26, 0.0f, 1.0f, 0.0f);
            guMtxCatF(sp164, sp124, sp164);
            if (arg1->unk22 < 0x3E8) {
                guRotateF(sp124, -((f64)arg1->unk20 / 4095.0 * 360.0), 0.0f, 1.0f, 0.0f);
                guMtxCatF(sp164, sp124, sp164);
            }
            guRotateF(sp124, 90.0 - (f64)arg1->unk22 / 4095.0 * 360.0, 1.0f, 0.0f, 0.0f);
            guMtxCatF(sp164, sp124, sp164);
            if (arg1->unk22 < 0x3E8) {
                guRotateF(sp124, (f64)arg1->unk20 / 4095.0 * 360.0, 0.0f, 1.0f, 0.0f);
                guMtxCatF(sp164, sp124, sp164);
            }
            guTranslateF(sp124, arg1->unk14, arg1->unk18, arg1->unk1C);
            guMtxCatF(sp164, sp124, sp164);
            guMtxF2L(sp164, &mtxs[sp1A4]);
            gSPMatrix(arg0++, osVirtualToPhysical(&mtxs[sp1A4]), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
            sp1A4++;
            gSPVertex(arg0++, osVirtualToPhysical(&vtxs[sp1A8[0]]), 4, 0);
            gSP2Triangles(arg0++, 0, 1, 2, 0, 0, 2, 3, 0);
            gSPPopMatrix(arg0++, G_MTX_MODELVIEW);
            sp1A8[0] += 4;
            v += 4;
            arg1 = arg1->unk34;
        } while (arg1 != NULL);
    }
    gDPPipeSync(arg0++);
    return arg0;
}

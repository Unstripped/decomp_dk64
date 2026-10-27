// func_8062CA70 (src/global/2F550.c): Stage 5 (NM2F). Draft now compiles against the current file: D_807F5DE8 s32 (cast at use), func_8062EDA8 via forward struct R2F550a2Cmd prototype; later R2F550bMapView typedef must be moved above (or dropped) when this goes in. Remaining diff unchanged: fp regs (target x=f20,y=f22,z=f24; mine x=f24) and target hoists consts 3/1/2 into t0-t2 (live range split with re-li after calls; in mine those candidates are 'not colored (-ve save)' in uopt trace), spill 0x54 vs 0x50. Tried combined null/3 check, if-chain vs switch for arg2->unk1, permuter 600s (3664->3025, only cosmetic mutations).
typedef struct R2F550bMapView {
    u8 pad0[0x1C];
    void *unk1C[21];
    s16 unk70[12];
    s16 unk88[18];
    u8 unkAC[13];
    u8 unkB9[12];
    u8 unkC5;
} R2F550bMapView;

typedef struct R2F550bLeaf {
    u8 pad0[8];
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    u8 pad1C[0x52];
    s16 unk6E;
} R2F550bLeaf;

extern s32 D_807F5E64;
extern s32 D_807F5DE8;
extern void *D_807F5DEC;
extern s32 D_807F5FFC;

Gfx *func_8062CEA8(Gfx *, R2F550bMapView *, u8);
Gfx *mapChunksRender(Gfx *, R2F550bObj *, f32, f32, f32, s32);
Gfx *fogRender(Gfx *);
struct R2F550a2Cmd;
struct R2F550a2Cmd *func_8062EDA8(struct R2F550a2Cmd *, u8);
Gfx *func_8063A968(Gfx *, s32);
Gfx *func_8065D994(Gfx *, s16);

#define R2F550bLEAF(o) ((R2F550bLeaf *)(o))

Gfx *func_8062CA70(Gfx *gfx, R2F550bObj *arg1, R2F550bTree *arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6) {
    Gfx *sp84;
    for (;;) {
        if (arg1 == NULL) {
            return gfx;
        }
        if (arg2->unk1 == 3) {
            return gfx;
        }
        switch (arg1->unkB8) {
            case 2:
                gfx = mapChunksRender(gfx, arg1, arg3, arg4, arg5, arg6);
                return gfx;
            case 1:
                D_807F5E64 += R2F550bLEAF(arg1)->unk6E;
                if (arg6 & 0x10) {
                    gSPSegment(gfx++, 6, osVirtualToPhysical((void *)D_807F5DE8));
                    gSPSegment(gfx++, 7, osVirtualToPhysical(D_807F5DEC));
                    gfx = func_8062CEA8(gfx, (R2F550bMapView *)arg1, 1);
                    gfx = fogRender(gfx);
                    gfx = (Gfx *)func_8062EDA8((struct R2F550a2Cmd *)gfx, 0xFF);
                    if (R2F550bLEAF(arg1)->unk8 != -1) {
                        gSPDisplayList(gfx++, osVirtualToPhysical((void *)R2F550bLEAF(arg1)->unk8));
                    }
                    if (R2F550bLEAF(arg1)->unkC != -1) {
                        gSPDisplayList(gfx++, osVirtualToPhysical((void *)R2F550bLEAF(arg1)->unkC));
                    }
                    if (R2F550bLEAF(arg1)->unk14 != -1) {
                        gSPDisplayList(gfx++, osVirtualToPhysical((void *)R2F550bLEAF(arg1)->unk14));
                    }
                    if (R2F550bLEAF(arg1)->unk10 != -1) {
                        gSPDisplayList(gfx++, osVirtualToPhysical((void *)R2F550bLEAF(arg1)->unk10));
                    }
                    if (R2F550bLEAF(arg1)->unk18 != -1) {
                        gSPDisplayList(gfx++, osVirtualToPhysical((void *)R2F550bLEAF(arg1)->unk18));
                    }
                    gfx = func_8062CEA8(gfx, (R2F550bMapView *)arg1, 2);
                }
                gfx = func_8063A968(gfx, arg2->unk8);
                gfx = func_8065D994(gfx, -1);
                D_807F6009 = 0xFF;
                gfx = func_80630B70(gfx, (s32)arg2->unk4, arg3, arg4, arg5, arg6, -1, 0);
                if (arg6 & 0x10) {
                    gSPSegment(gfx++, 6, osVirtualToPhysical((void *)D_807F5DE8));
                    gSPSegment(gfx++, 7, osVirtualToPhysical(D_807F5DEC));
                    gfx = func_8062CEA8(gfx, (R2F550bMapView *)arg1, 3);
                    gDPPipeSync(gfx++);
                }
                gfx = func_80630B70(gfx, D_807F5FFC, arg3, arg4, arg5, arg6, -1, 0);
                return gfx;
            case 0:
                switch (arg2->unk1) {
                    case 1:
                    case 2:
                        if (arg2->unk0 == 0) {
                            arg1 = arg1->unk0;
                            arg2 = arg2->unkC;
                        } else {
                            arg1 = arg1->unk4;
                            arg2 = arg2->unk10;
                        }
                        continue;
                    case 0:
                        if (arg2->unk0 != 0) {
                            gfx = func_8062CA70(gfx, arg1->unk0, arg2->unkC, arg3, arg4, arg5, arg6);
                            arg1 = arg1->unk4;
                            arg2 = arg2->unk10;
                        } else {
                            gfx = func_8062CA70(gfx, arg1->unk4, arg2->unk10, arg3, arg4, arg5, arg6);
                            arg1 = arg1->unk0;
                            arg2 = arg2->unkC;
                        }
                        continue;
                    default:
                        return gfx;
                }
            default:
                return gfx;
        }
    }
}

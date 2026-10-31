// func_8062C29C (src/global/2F550.c): Stage 5 (QS3, parked NON_MATCHING in 2F550.c). Same frame 0xE0/saved set; text diff starts only at the gDPSetTileSize words (206 diff lines, rest is t-reg cascade): target loads 468 into t9 / 464 into t7 and schedules andi,andi,sll,or(at),or; mine t3/t4 and andi,or(at),andi,sll,or; w1 target does lrs andi+sll before lrt andi. u64 no-op mask on uls/lrs is the only thing that changes it (others no effect: casts s32/u32/f64, per-operand masks 2^4, mask on shifted terms/whole word/F2 const, operand/assoc order (uopt canonicalises), hand-written _g form, locals for words, dummy statements/dead loads before, s32 field type; permuter 570s from this base: no gain). First-load t-reg (t3 vs t9) independent of all source forms tried.
typedef struct L8062C29CPlayer {
    u8 pad0[4];
    void *unk4;
    Mtx unk8[2];
    Mtx unk88[2];
    u8 pad108[0x80];
    u16 unk188;
    u8 pad18A[6];
    u8 unk190[2][0x20];
    u32 unk1D0[2][4];
    Gfx unk1F0[2][2];
    u8 pad210[0x40];
    s16 unk250[2][8];
    s16 unk270;
    s16 unk272;
    s16 unk274;
    s16 unk276;
    u8 pad278[0x78];
} L8062C29CPlayer;

#define L8062C29CP (((L8062C29CPlayer *)D_807FC924)[D_807FC929])
#define L8062C29CF(x) (*(f32 *)&(x))

extern s32 D_807F5E64;
extern f32 D_807F5FB4;
extern f32 D_807F5FB0;
extern f32 D_807F5FAC;
extern f32 D_807F5FA8;
extern f32 D_807F5FE0;
extern f32 D_807F5FDC;
extern u8 D_807F5E68[];
extern struct MapDistributeEntry *D_807F5FF0;
extern s32 D_807F5DE8;
extern void *D_807F5DEC;
extern s32 D_807FBB60;
extern Mtx D_2000180;

f32 cosApprox(f32);
void planeFromTwoPoints(f32, f32, f32, f32, f32, f32);
void func_8062A944(f32, f32, f32);
void frustumOrientPolyNormals(f32, f32, f32, PlanePoly *, f32 *);
void mapTreeFrameUpdate(MapBspNode *, MapVisNode *, struct MapDistributeEntry *, f32, f32, f32, u8, u8, u8);
Gfx *func_80722294(Gfx *, void *, s16);
Gfx *gfxDrawPlayerViewBackground(Gfx *, s16);
Gfx *fogApply(Gfx *);
void mapSetClipBounds();
Gfx *mapTreeRender(Gfx *, MapBspNode *, MapVisNode *, f32, f32, f32, s32);
void viewportSetFromRect(s16 *, s32, s32, s32, s32);

Gfx *func_8062C29C(Gfx *gfx, s32 arg1, s32 arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9) {
    Gfx *dl;
    s32 pad2[1];
    s32 pad[24];

    dl = &L8062C29CP.unk1F0[D_807444FC][0];
    D_807F5E64 = 0;
    D_807F5FB4 = arg7;
    D_807F5FB0 = arg8;
    D_807F5FAC = arg9;
    D_807F5FA8 = D_807F5FAC;
    D_807F5FE0 = cosApprox(arg7 * 0.01745329238f);
    D_807F5FE0 = (D_807F5FE0 - D_807F5FDC) * 3.0 + D_807F5FDC;
    planeFromTwoPoints(L8062C29CF(arg1), L8062C29CF(arg2), L8062C29CF(arg3), arg4, arg5, arg6);
    func_8062A944(D_807F5FB4, D_807F5FB0, D_807F5FA8);
    frustumCornersTransformByInverse(&L8062C29CP.unk8[D_807444FC]);
    frustumOrientPolyNormals(L8062C29CF(arg1), L8062C29CF(arg2), L8062C29CF(arg3), (PlanePoly *)D_807F5E68, D_807F5E20);
    mapTreeFrameUpdate(D_807F5DE4, D_807F5E60, D_807F5FF0, L8062C29CF(arg1), L8062C29CF(arg2), L8062C29CF(arg3), 0, !D_807F5FEC, D_80750AB4 >= 2);
    gSPSegment(gfx++, 6, osVirtualToPhysical((void *)D_807F5DE8));
    gSPSegment(gfx++, 7, osVirtualToPhysical(D_807F5DEC));
    gfx = func_80722294(gfx, L8062C29CP.unk4, D_807FC929);
    gSPSegment(gfx++, 5, osVirtualToPhysical(dl));
    gDPSetTileSize(dl++, 0, (L8062C29CP.unk1D0[D_807444FC][0] & 0xFFFFFFFFFFFFFFFFu), L8062C29CP.unk1D0[D_807444FC][1], // FAKE: u64 mask no-op steers load order
                   (L8062C29CP.unk1D0[D_807444FC][0] + 0x7C) & 0xFFFFFFFFFFFFFFFFu, L8062C29CP.unk1D0[D_807444FC][1] + 0x7C); // FAKE: u64 mask no-op steers load order
    gSPEndDisplayList(dl++);
    viewportSetFromRect(L8062C29CP.unk250[D_807444FC], L8062C29CP.unk270, L8062C29CP.unk272, L8062C29CP.unk274, L8062C29CP.unk276);
    gSPPerspNormalize(gfx++, L8062C29CP.unk188);
    gSPViewport(gfx++, osVirtualToPhysical(&L8062C29CP.unk250[D_807444FC]));
    gDPSetScissor(gfx++, G_SC_NON_INTERLACE, L8062C29CP.unk270, L8062C29CP.unk272, L8062C29CP.unk274, L8062C29CP.unk276);
    gSPLookAtX(gfx++, osVirtualToPhysical(&L8062C29CP.unk190[D_807444FC]));
    gSPLookAtY(gfx++, osVirtualToPhysical(&L8062C29CP.unk190[D_807444FC]) + 0x10);
    mapSetClipBounds(L8062C29CP.unk270, L8062C29CP.unk272, L8062C29CP.unk274, L8062C29CP.unk276);
    gfx = gfxDrawPlayerViewBackground(fogApply(gfx), D_807FC929);
    gSPMatrix(gfx++, osVirtualToPhysical(&L8062C29CP.unk88[D_807444FC]), G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(gfx++, osVirtualToPhysical(&L8062C29CP.unk8[D_807444FC]), G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);
    gSPMatrix(gfx++, &D_2000180, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gfx = mapTreeRender(gfx, D_807F5DE4, D_807F5E60, L8062C29CF(arg1), L8062C29CF(arg2), L8062C29CF(arg3), D_807FBB60);
    gDPPipeSync(gfx++);
    return gfx;
}

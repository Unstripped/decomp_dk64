// func_806FEF7C (src/global/103AB0.c): Stage 5: 4 instruction scheduling difference in paired Gfx word materialization/stores; all remaining code and D_8075DE70 relocation match.
typedef struct {
    u8 unk0[0x1A4];
    u8 unk1A4;
} R1F103AB0aState;

s32 func_806FEDB0(s32, u8);
Gfx *func_8068C5A8(Gfx *, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, f32);
extern f32 D_8075DE70;

void func_806FEF7C(s32 arg0, Actor *arg1) {
    Gfx *glist;

    glist = (Gfx *)func_806FEDB0(arg0, ((R1F103AB0aState *)arg1->unk174)->unk1A4);
    glist->words.w0 = 0xE200001C;
    glist->words.w1 = 0x504340;
    glist[1].words.w0 = 0xFA000000;
    glist[1].words.w1 = 0xFF;
    func_8068C5A8(glist + 2, 0x3C, 3, 1, 0x40, 0x40, 0xA0, 0x78, 5.0f, 5.0f, 0, D_8075DE70);
}

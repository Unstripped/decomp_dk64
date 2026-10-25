// func_807007B8 (src/global/103AB0.c): Stage 5: compiled display-list and trail renderer reconstruction; command-store scheduling remains divergent.
typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    s32 unkC;
} R2F103AB0dTrailPoint;

extern u8 D_80754BC0;
extern R2F103AB0dTrailPoint D_807FD808[2];
extern u8 D_807FD838[2][3];
extern s32 D_807444FC;
extern u8 D_2000180;
extern Gfx *func_8070068C(Gfx *);
extern Gfx *func_80701098(Gfx *, f32, f32, f32, s32, u8);

#define WRITE_GFX(pkt, _w0, _w1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = (_w0); _g->words.w1 = (_w1); }

Gfx *func_807007B8(Gfx *arg0) {
    s16 i;
    u8 age;
    R2F103AB0dTrailPoint *point;
    Gfx *dl;

    dl = arg0;
    if (D_80754BC0 != 0) {
        WRITE_GFX(dl++, 0xE7000000, 0);
        dl = func_8070068C(dl);
        WRITE_GFX(dl++, 0xDA380003, (u32)&D_2000180);
        WRITE_GFX(dl++, 0xE7000000, 0);
        WRITE_GFX(dl++, 0xD9000000, 0);
        WRITE_GFX(dl++, 0xD9FFFFFF, 0x200004);
        WRITE_GFX(dl++, 0xE3000A01, 0);
        WRITE_GFX(dl++, 0xE3000C00, 0x80000);
        WRITE_GFX(dl++, 0xE3001201, 0x2000);
        WRITE_GFX(dl++, 0xD7000002, 0x80008000);
        WRITE_GFX(dl++, 0xFC119623, 0xFF2FFFFF);
        WRITE_GFX(dl++, 0xE200001C, 0x504340);
        WRITE_GFX(dl++, 0xE3001801, 0xC0);
        WRITE_GFX(dl++, 0xE3001A01, 0x30);
        for (i = 0; i < (s32)D_80754BC0; i++) {
            point = &D_807FD808[i];
            age = D_807FD838[D_807444FC ^ 1][i];
            if (age != 0) {
                D_807FD838[D_807444FC ^ 1][i] = age - 1;
                dl = func_80701098(dl, point->unk0, point->unk4, point->unk8, point->unkC, age);
            }
        }
        WRITE_GFX(dl++, 0xE3001801, 0);
        WRITE_GFX(dl++, 0xE3001A01, 0);
    }
    return dl;
}

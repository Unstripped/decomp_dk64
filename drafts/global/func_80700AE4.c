// func_80700AE4 (src/global/103AB0.c): Stage 6: compiled tile query reconstruction; local copy slot and register allocation remain divergent.
typedef struct { s32 unk0; u32 unk4; s32 unk8; s32 unkC; s32 unk10; s32 unk14; s32 unk18; s32 unk1C; s32 unk20; s32 unk24; s32 unk28; s32 unk2C; s32 unk30; s32 unk34; s32 unk38; s32 unk3C; } R2F103AB0dTileCopy;
typedef struct { u8 unk0[0x270]; s16 unk270; s16 unk272; s16 unk274; s16 unk276; } R2F103AB0dPlayerView;
extern R2F103AB0dTileCopy D_80754BC4;
extern s32 D_8076A060;
extern void *D_807FC924;
extern s16 D_80744490;
#define R2F103AB0dPlayer ((R2F103AB0dPlayerView *)D_807FC924)
s32 func_80700AE4(s16 arg0, s16 arg1) {
    f64 pad;
    R2F103AB0dTileCopy tileCopy;
    u16 tile;
    s32 *tileInfo;
    u16 *map;
    tileCopy = D_80754BC4;
    map = (u16 *)D_8076A060;
    if ((arg0 < R2F103AB0dPlayer->unk270) || (R2F103AB0dPlayer->unk274 < arg0) || (arg1 < R2F103AB0dPlayer->unk272) || (R2F103AB0dPlayer->unk276 < arg1)) return 0xFFFF;
    tile = *(u16 *)((u8 *)map + (((D_80744490 * arg1) + arg0) * 2));
    tileInfo = (s32 *)&tileCopy + (((tile >> 0xD) & 7) * 2);
    return ((u32)(tileInfo[1] + (((tile >> 2) & 0x7FF) << tileInfo[0])) >> 3) & 0xFFFF;
}

// jetpacDrawLedges (src/jetpac/3480.c): stage 6 (11 diff lines, down from 13): prologue addiu/move s8,s3 order matched; remaining diff is prologue lui t6 vs v0 (1 ugen temp consumed shifts ring in loop from t8/t9/t0 to t9/t0/t1) and sw zero,0x10(sp) order at call 1
void jetpacGridAddTiledSprite(void *, s32, s32, void *, s32);
extern void *D_8002DE68;
extern void *D_8002DE80;
extern void *D_8002DE98;
extern u8 D_8002EF90[];
extern u8 D_8002F060[];

void jetpacDrawLedges(void) {
    u8 *color_fp; u8 *color; void *de80; u8 *base; JetpacLedge *ledge;
    color_fp = (u8 *)(s32)D_8002EF90; color = color_fp; de80 = &D_8002DE80; base = (u8 *)&jetpacGame; ledge = jetpacLedges; do {
        s32 x = (s32)*(f32 *)(base + 0x350);
        s32 y = (s32)*(f32 *)(base + 0x354);
        JetpacLedge *cur = ledge;
        s32 j;

        jetpacGridAddTiledSprite(&D_8002DE68, x, y, color_fp, 0);
        j = 0;
        x += 8;
        if (cur->unk30 > 0) {
            do {
                jetpacGridAddTiledSprite(de80, x, y, color, 0);
                j++;
                x += 8;
            } while (j < cur->unk30);
        }
        jetpacGridAddTiledSprite(&D_8002DE98, x, y, color, 0);
        base += 0x34;
        ledge++;
        color_fp += 0x34;
    } while ((color += 0x34) != D_8002F060);
}

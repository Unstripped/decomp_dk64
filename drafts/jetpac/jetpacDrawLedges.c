// jetpacDrawLedges (src/jetpac/3480.c): stage 6: 13 diff lines (frame/size/regs identical). lui s5,s6,s7 order matches via one-line join; (u8*)(s32)D_8002EF90 matches prologue sw order; remaining diff is prologue lui t6 vs v0 (1 temp consumed shifts ring in loop from t8/t9/t0 to t9/t0/t1) and sw zero,0x10(sp) order
typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    u8 color[4];
    u8 pad14[8];
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    u8 pad2C[4];
    s32 unk30;
} JetpacLedge;

typedef struct {
    u8 pad0[0x1C];
    u8 pad1C[0x350 - 0x1C];
    JetpacLedge ledges[4];
    u8 pad420[0x78C - 0x420];
    s32 unk78C;
} JetpacGlobal;

extern JetpacGlobal jetpacGame;
extern JetpacLedge jetpacLedges[];
void jetpacGridAddTiledSprite(void *, s32, s32, void *, s32);
extern void *D_8002DE68;
extern void *D_8002DE80;
extern void *D_8002DE98;
extern u8 D_8002EF90[];
extern u8 D_8002F060[];

void jetpacDrawLedges(void) {
    u8 *color_fp = (u8 *)(s32)D_8002EF90;
    u8 *color = color_fp;
    void *de80 = &D_8002DE80;
    u8 *base = (u8 *)&jetpacGame; JetpacLedge *ledge = jetpacLedges; do {
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

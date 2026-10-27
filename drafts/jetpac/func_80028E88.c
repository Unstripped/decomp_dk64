// func_80028E88 (src/jetpac/3480.c): stage 6 park: loop end now matches (while ((color += 0x34) != D_8002F060) after base/ledge/fp incs; 'u8 *base=..; JetpacLedge *ledge=..;' on one line) and t-regs only +1 off. Left: prologue 'lui v0' vs 'lui t6' for D_8002EF90 (move s8,s3 after the hoisted addius in target), s5/s6/s7 lui order (target s5,s6,s7; ours s6,s7,s5), 'sw zero,0x10(sp)' after 'move a3,s8'. Tried decl orders x joins, color/color_fp from global or copy, for-loop headers, permuter
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
extern JetpacLedge D_8002EF80[];
extern s32 D_8002EC30[];
void func_80025700(void *, s32, s32, void *, s32);
extern void *D_8002DE68;
extern void *D_8002DE80;
extern void *D_8002DE98;
extern u8 D_8002EF90[];
extern u8 D_8002F060[];

void func_80028E88(void) {
    u8 *color_fp = D_8002EF90;
    u8 *color = color_fp;
    void *de80 = &D_8002DE80;
    u8 *base = (u8 *)&D_8002EC30; JetpacLedge *ledge = D_8002EF80;

    do {
        s32 x = (s32)*(f32 *)(base + 0x350);
        s32 y = (s32)*(f32 *)(base + 0x354);
        JetpacLedge *cur = ledge;
        s32 j;

        func_80025700(&D_8002DE68, x, y, color_fp, 0);
        j = 0;
        x += 8;
        if (cur->unk30 > 0) {
            do {
                func_80025700(de80, x, y, color, 0);
                j++;
                x += 8;
            } while (j < cur->unk30);
        }
        func_80025700(&D_8002DE98, x, y, color, 0);
        base += 0x34;
        ledge++;
        color_fp += 0x34;
    } while ((color += 0x34) != D_8002F060);
}

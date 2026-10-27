// func_80028E88 (src/jetpac/3480.c): stage 6: 17 -> 13 diff lines (size/frame/regs identical). Fixed by joining 'u8 *base=..; JetpacLedge *ledge=..; do {' on ONE source line (lui s5,s6,s7 order now matches) and '(u8 *)(s32)D_8002EF90' no-op cast. Left: prologue 'lui v0; addiu s3,v0' vs target 'lui t6 ... sw s8 ... addiu s3,t6' (one $t consumed: loop t8/t9/t0 vs t9/t0/t1), 'move s8,s3' after the three hoisted addiu (ours before), 'sw zero,0x10(sp)' after 'move a3,s8' (ours before). Tried: 46 line-join masks, decl orders, color_fp copy after the inits, dummy if(!x){}, casts on base/ledge, permuter 250s (only the line join)
void func_80028E88(void) {
    u8 *color_fp = (u8 *)(s32)D_8002EF90;
    u8 *color = color_fp;
    void *de80 = &D_8002DE80;
    u8 *base = (u8 *)&D_8002EC30; JetpacLedge *ledge = D_8002EF80; do {
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

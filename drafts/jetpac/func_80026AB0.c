// func_80026AB0 (src/jetpac/1A60.c): stage 6 park (C unchanged): only $t numbering after the D_8002F080 load: target F068 t9 / x-chain mfc1 t3,andi t4 / idx*24 chain t5,t6; ours F068 t7 / t3,t4 / t0,t1 (branch1 offset by 2, final F094 t5 vs t7). Tried: cached s32* for F068/F080, sprite ptr local, base-table ptr, s16/u16/s8 temp for (s32)x (s16 shifts mfc1 to t5 but wrong), flip local, join statements on one line (all 14 pairs), decl/stmt order, !F080, permuter 2x (only whitespace/dead-assign)
extern f32 D_8002F054;
extern u8 D_8002F060[];
extern s32 D_8002F064;
extern s32 D_8002F068;
extern s32 D_8002F080;
extern JetpacExplosion D_8002F08C;
extern s32 D_8002F094;
extern JetpacSprite D_8002C330;
extern JetpacSprite D_8002C348[];
extern JetpacSprite D_8002C3A8[];

void func_80026AB0(void) {
    f32 x;
    f32 y;
    u8 *color;
    s32 pad;
    s32 idx;
    s32 draw;

    pad = 0;
    draw = 1;
    if (D_8002F064 >= 2) {
        if (*(s32 *)&D_8002F060[4] == 4 && D_8002F094 >= 8) {
            draw = 0;
        }
        idx = func_80025B70((JetpacActor *)&D_8002F050);
        x = *(f32 *)&D_8002F050;
        y = D_8002F054;
        if (draw != 0) {
            color = D_8002F060;
            if (D_8002F080 == 0) {
                func_80025700(&D_8002C3A8[idx], (s32)(f32)((s32)x & 0xFFFE), (s32)y, (s32)color, D_8002F068);
            } else {
                func_80025700(&D_8002C330, (s32)x, (s32)y, (s32)color, D_8002F068);
                if (D_8002F068 == 0) {
                    if (idx == 4) {
                        x -= 1.0f;
                    }
                    x -= 3.0f;
                } else {
                    if (idx == 4) {
                        x += 1.0f;
                    }
                    x += 10.0f;
                }
                func_80025700(&D_8002C348[idx], (s32)x, (s32)(y + 18.0f), (s32)color, D_8002F068);
            }
        }
        if (D_8002F094 < 14) {
            func_80025A60(&D_8002F08C);
        }
    }
}

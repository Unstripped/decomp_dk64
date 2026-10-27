// func_80026AB0 (src/jetpac/1A60.c): stage 5-6: frame/stack/callee-saved/insn count identical; only  temp numbering differs after the D_8002F080 load (target sll t5/lui t9 ... vs t0/t7) and float regs. Needed trick: 2nd D_8002F064 read as *(s32*)&D_8002F060[4] (stops uopt CSE of the double load; unprototyped D_8002F064 twice gets CSE'd). dummy 'pad' local fixes stack slots; color=D_8002F060 local; permuter only found noise (short new_var)
extern JetpacState D_8002F050;
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

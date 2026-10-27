// func_80025700 (src/jetpac/1460.c): stage 5: frame 0x50 and s-reg set/order now match (s0..s7,fp; ya local + 'if (!ya) {}' after the inner loop + 'if (!yEnd) {}' at the inner-loop tail raise yEnd's priority above arg4/ptr so it gets s5); h declared 2nd (frame 0x50; h 3rd+ grows it). Remaining: target reloads h from sp+0x48 at 'yEnd = h' (we CSE it to move s5,t3), which shifts temp numbering; 'move s4,a1' order. volatile h fixes the reload but breaks the guard delay slot (blezl). Inline h/w exprs, y=arg2 copy, &h, decl-order search (300 samples) did not help.
typedef struct {
    s32 unk0;
    u8 pad4[6];
    s16 unkA;
    s16 unkC;
    u8 padE[2];
    s16 unk10;
    s16 unk12;
    u8 pad14[4];
} J1aSprite;

extern J1aSprite D_80042BD0[][256];
extern u8 D_807444FC;
void func_800254B8(JetpacSprite *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_80025700(JetpacSprite *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 ya;
    s32 h;
    J1aSprite *dst;
    s32 w;
    s32 x;
    s32 dy;
    s32 yEnd;
    s32 dx;
    s32 xEnd;

    w = ((J1aSprite *)arg0)->unkA - 1;
    h = ((J1aSprite *)arg0)->unkC - 1;
    x = arg1;

    if (D_80045BD0 < 0x100) {
        if (arg1 < 0) {
            x = arg1 + 0x100;
        }
        dy = 0;
        yEnd = arg2;
        if (h > 0) {
            do {
                yEnd = ((yEnd + 8) & 0xFFF8) - arg2;
                dx = 0;
                xEnd = x;
                if (yEnd >= h) {
                    yEnd = h;
                }
                if (w > 0) {
                    do {
                        if (D_80045BD0 >= 0x100) {
                            return;
                        }
                        dst = &D_80042BD0[D_807444FC][D_80045BD0++];
                        *dst = *(J1aSprite *)arg0;
                        xEnd = ((xEnd + 8) & 0xFFF8) - x;
                        if (xEnd >= w) {
                            xEnd = w;
                        }
                        if (arg4 != 0) {
                            dst->unk10 = dst->unk10 + w - xEnd;
                        } else {
                            dst->unk10 = dst->unk10 + dx;
                        }
                        dst->unk12 = dst->unk12 + dy;
                        dst->unkA = xEnd - dx + 1;
                        dst->unkC = yEnd - dy + 1;
                        ya = arg2 + dy;
                        func_800254B8((JetpacSprite *)dst, (x + dx >= 0x100) ? x + dx - 0x100 : x + dx, ya, arg3, arg4);
                        dx = xEnd;
                        xEnd = xEnd + x;
                        if (!yEnd) {
                        }
                    } while (dx < w);
                    if (!ya) {
                    }
                }
                dy = yEnd;
                yEnd = yEnd + arg2;
            } while (dy < h);
        }
    }
}

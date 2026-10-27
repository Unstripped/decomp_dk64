// func_80025700 (src/jetpac/1460.c): stage 5, parked NON_MATCHING: 54 -> 10 diff lines. Split compound assigns (yEnd += 8; yEnd &= 0xFFF8; yEnd -= arg2; same for xEnd) gives in-place addiu s5/s0 like target (permuter find). Remaining: target reloads h with lw s5,72(sp) at 'yEnd = h' (ours move s5,t2: h's register segment covers the assign block), move s4,a1 before move s8,a2, D_80045BD0++ sw order, a1/a2 temp for dst->unkC. Tried: harr[1], struct field, hh copy, &h/*&h/hp, volatile at the site, ternary/!(<)/<= forms, h multi-def, x->arg1, ya in call args, dummy ifs in the assign block.
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
                yEnd += 8;
                yEnd &= 0xFFF8;
                yEnd -= arg2;
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
                        xEnd += 8;
                        xEnd &= 0xFFF8;
                        xEnd -= x;
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

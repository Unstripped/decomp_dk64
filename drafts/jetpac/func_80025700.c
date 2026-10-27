// func_80025700 (src/jetpac/1460.c): stage 6: ONE instruction-pair left (5 diff lines): target has 'addiu t8,v0,1; sw t8,0(s7)' (D_80045BD0++) before 'lw t9,80(sp)' and the lbu-derived sll; ours places them after. Everything else matches (arg1 in-place, xd local, h dummies before+after yEnd = h, w dummies).
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
    s32 xd;
    J1aSprite *dst;
    s32 w;
    s32 dy;
    s32 yEnd;
    s32 dx;
    s32 xEnd;

    w = ((J1aSprite *)arg0)->unkA - 1;
    h = ((J1aSprite *)arg0)->unkC - 1;

    if (D_80045BD0 < 0x100) {
        if (arg1 < 0) {
            arg1 += 0x100;
        }
        dy = 0;
        yEnd = arg2;
        if (h > 0) {
            do {
                yEnd += 8;
                yEnd &= 0xFFF8;
                yEnd -= arg2;
                dx = 0;
                xEnd = arg1;
                if (yEnd >= h) {
                    if (!h) {
                    }
                    yEnd = h;
                    if (!h) {
                    }
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
                        xEnd -= arg1;
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
                        xd = arg1 + dx;
                        if (xd >= 0x100) {
                            xd -= 0x100;
                        }
                        func_800254B8((JetpacSprite *)dst, xd, ya, arg3, arg4);
                        dx = xEnd;
                        xEnd = xEnd + arg1;
                        if (!w) {
                        }
                        if (!w) {
                        }
                    } while (dx < w);
                    if (!ya) {
                    }
                    if (!yEnd) {
                    }
                }
                dy = yEnd;
                yEnd = yEnd + arg2;
            } while (dy < h);
        }
    }
}

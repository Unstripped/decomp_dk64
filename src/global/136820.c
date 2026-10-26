#include "common.h"

extern s32 D_807FEF80;
extern s32 D_807FEF78;
extern u16 D_807FEF84;
extern u16 D_807FEF86;
extern s32 D_807FEF70;
extern s32 D_807FEF74;

void faultFontInit(s32 a0, s32 a1, s32 a2) {
    D_807FEF80 = a0;
    D_807FEF78 = 2;
    D_807FEF84 = 0xFFFF;
    D_807FEF86 = 1;
    D_807FEF70 = a1;
    D_807FEF74 = a2;
}

void faultFontSetColorMode(s32 a0) {
    if (a0 == 0) {
        D_807FEF84 = 0xFFFF;
    } else {
        D_807FEF84 = 0xF801;
    }
}

extern u8 D_8074450C;
extern s16 D_80744490;
extern u8 D_80756130[];

void faultDrawGlyph(u8 c) {
    u8 *glyph;
    u16 *dst;
    s32 row;
    s32 i;
    s32 bit;
    s32 j;

    glyph = D_80756130 + (c - 33) * 6;
    dst = (D_807FEF70 + 3) * D_8074450C * 4 + (u16 *)D_807FEF80 + D_80744490 * (D_807FEF74 + 3) * D_8074450C * 6;
    for (row = 0; row != 6; row++, glyph++) {
        for (i = 0; i < D_8074450C * D_807FEF78; i++) {
            for (bit = 3; bit >= 0; bit--) {
                for (j = 0; j < D_8074450C * D_807FEF78; j++) {
                    if (*glyph & (1 << bit)) {
                        *dst = D_807FEF84;
                    } else {
                        *dst = D_807FEF86;
                    }
                    dst++;
                }
            }
            dst += D_80744490 - D_807FEF78 * 4 * D_8074450C;
        }
    }
}

#include "compiler/ido/stdarg.h"

extern s32 D_807FEF7C;
int vsprintf(u8 *buf, const u8 *fmt, va_list ap);

void faultPrintf(const char *fmt, ...) {
    u8 *p;
    u8 buf[0x80];
    u8 c;
    s32 x;

    vsprintf(buf, (const u8 *)fmt, (va_list)(&fmt + 1));
    p = buf;
    c = *p++;
    if (0) {
    }
    while (c) {
        switch (c) {
            case 32:
                D_807FEF70 += D_807FEF78;
                break;
            case 9:
                D_807FEF70 = D_807FEF70 / 8;
                D_807FEF70 = D_807FEF70 + 1;
                D_807FEF70 = D_807FEF70 * 8;
                break;
            case 10:
                D_807FEF70 = D_807FEF7C;
                D_807FEF74 += D_807FEF78;
                break;
            default:
                faultDrawGlyph(c);
                D_807FEF70 += D_807FEF78;
                break;
        }
        c = *p++;
    }
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/136820/D_8075FFF0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/136820/D_80760004.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/136820/D_80760018.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/136820/D_80760028.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/136820/D_80760038.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/136820/D_80760048.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/136820/D_80760054.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/136820/D_80760064.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/136820/D_80760078.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/136820/D_8076008C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/136820/D_807600A0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/136820/D_807600B4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/136820/D_807600CC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/136820/D_807600E0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/136820/D_807600F8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/136820/D_8076010C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/136820/D_80760124.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/136820/D_8076013C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/136820/D_80760150.s")

typedef struct {
    s32 unk0;
    s32 unk4;
} Ga136820Entry;

extern s32 D_807FF018;
extern Ga136820Entry D_807FEF88[];
extern s32 D_807563B8;
extern u8 D_807FF01C;
extern s32 D_807FF020;
extern s32 D_807FF024;
extern s32 D_807FF028;
#ifdef NON_MATCHING
extern char *D_80756360[];
void faultUnwindStack(OSThread *a0);

void faultDrawRegs(OSThread *a0) {
    s32 y;
    s32 x;
    s32 j;
    __OSThreadContext *ctx;

    D_807FEF78 = 2;
    D_807FEF84 = 0xFFFF;
    D_807FEF86 = 1;
    ctx = &a0->context;
    for (y = 0, x = 0; y != 24; y += 6, x += 18) {
        D_807FEF7C = x;
        D_807FEF70 = x;
        D_807FEF74 = y;
        faultPrintf("DK 64\n");
        faultPrintf("%X\n", (s32)ctx->pc);
        faultPrintf("%X\n", (s32)ctx->ra);
        if (D_807563B8 >= 4) {
            for (j = 0; j < D_807FF018; j++) {
                faultPrintf("%X\n", D_807FEF88[j].unk0);
            }
        }
    }
    if (D_807FF01C != 0) {
        faultPrintf("%s %x %x %x", D_80756360[D_807FF01C], D_807FF020, D_807FF024, D_807FF028);
    }
    if (D_807563B8 < 4) {
        D_807563B8++;
    }
    if (D_807563B8 == 4) {
        faultUnwindStack(a0);
    }
}

#else

#pragma GLOBAL_ASM("asm/global/nonmatchings/136820/faultDrawRegs.s")
#endif

s32 unwindDecodeLoadRa(s32 a0, s32 *a1, s32 *a2) {
    if ((a0 & 0xFFFF0000) == 0x8FBF0000) {
        *a2 = *(s32 *)((u8 *)a1 + (s16)(a0 & 0xFFFF));
        return 1;
    }
    return 0;
}

s32 unwindDecodeAddiuSp(s32 a0, s32 *a1) {
    if ((a0 & 0xFFFF0000) == 0x27BD0000) {
        s32 v = *a1;
        v += (s16)(a0 & 0xFFFF);
        *a1 = v;
        return 1;
    }
    return 0;
}

s32 unwindDecodeJrRa(u32 a0, s32 *a1, s32 a2, s32 *a3) {
    if ((a0 & 0x3FFFFFF) == 0x3E00008) {
        unwindDecodeAddiuSp(**(s32 **)a3, a1);
        if (D_807FF018 != 0 && a2 == D_807FEF88[D_807FF018 - 1].unk0) {
            D_807FEF88[D_807FF018 - 1].unk4++;
        } else {
            D_807FEF88[D_807FF018].unk0 = a2;
            D_807FEF88[D_807FF018].unk4 = 1;
            D_807FF018++;
        }
        *a3 = a2;
        return 1;
    }
    return 0;
}

void faultUnwindStack(OSThread *a0) {
    s32 x1;
    s32 *pc;
    s32 r;
    s32 sp;
    s32 ra;
    s32 insn;
    s32 done;

    pc = (s32 *)a0->context.pc;
    sp = a0->context.sp;
    ra = a0->context.ra;
    D_807FF018 = 0;
    done = 0;
    while (pc != 0 && D_807FF018 < 18 && !done) {
        insn = *pc++;
        r = unwindDecodeJrRa(insn, &sp, ra, (s32 *)&pc);
        if (r == 0) {
            r = unwindDecodeLoadRa(insn, (s32 *)sp, &ra);
        }
        if (r == 0) {
            unwindDecodeAddiuSp(insn, &sp);
        }
        done = D_807FF018 != 0 ? D_807FEF88[D_807FF018 - 1].unk4 >= 16 : 0;
    }
    D_807563B8++;
}

extern OSMesgQueue D_807FEF58;

extern s32 D_80744470[];
extern u8 D_807563B4;
void faultDrawRegs(OSThread *a0);

void faultThreadMain(void *arg) {
    OSMesg msg;
    OSThread *thread;
    s32 i;
    s32 x;

    osSetEventMesg(12, &D_807FEF58, (OSMesg)0x10);
    for (;;) {
        while (1) {
            osRecvMesg(&D_807FEF58, &msg, 1);
            if (D_807563B4 != 0) {
                break;
            }
        }
        thread = (OSThread *)__osGetCurrFaultedThread();
        if (thread != 0) {
            for (;;) {
                for (i = 0; i < 2; i++) {
                    osViBlack(0);
                    D_807FEF80 = D_80744470[i];
                    faultDrawRegs(thread);
                    faultDrawRegs(thread);
                }
            }
        }
    }
}

void func_8061D4E4(s32);

void faultSetMessage(u8 a0, s32 a1, s32 a2, s32 a3) {
    D_807FF01C = a0;
    D_807FF020 = a1;
    D_807FF024 = a2;
    D_807FF028 = a3;
    func_8061D4E4(0);
}

extern OSMesg D_807FEF50;
extern OSThread D_807FDDA0;
extern u8 D_807563B0;
void faultThreadMain(void *);

void faultThreadInit(void) {
    __osSetFpcCsr(__osGetFpcCsr() | 0x400);
    osCreateMesgQueue(&D_807FEF58, &D_807FEF50, 1);
    osCreateThread(&D_807FDDA0, 8, faultThreadMain, 0, &D_807FEF50, 0x32);
    osStartThread(&D_807FDDA0);
    D_807563B0 = 1;
}

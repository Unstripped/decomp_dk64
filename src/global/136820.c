#include "common.h"
#include "PR/os_internal_error.h"
#include "proto/boot/3D20.h"
#include "proto/global/136820.h"
#include "proto/global/201B0.h"


extern s32 gFaultFramebuffer;
extern s32 gFaultCharScale;
extern u16 gFaultFgColor;
extern u16 gFaultBgColor;
extern s32 gFaultCursorX;
extern s32 gFaultCursorY;

void faultFontInit(s32 a0, s32 a1, s32 a2) {
    gFaultFramebuffer = a0;
    gFaultCharScale = 2;
    gFaultFgColor = 0xFFFF;
    gFaultBgColor = 1;
    gFaultCursorX = a1;
    gFaultCursorY = a2;
}

void faultFontSetColorMode(s32 a0) {
    if (a0 == 0) {
        gFaultFgColor = 0xFFFF;
    } else {
        gFaultFgColor = 0xF801;
    }
}

extern u8 gHiResScale;
extern s16 gScreenWidth;
extern u8 D_80756130[];

void faultDrawGlyph(u8 c) {
    u8 *glyph;
    u16 *dst;
    s32 row;
    s32 i;
    s32 bit;
    s32 j;

    glyph = D_80756130 + (c - 33) * 6;
    dst = (gFaultCursorX + 3) * gHiResScale * 4 + (u16 *)gFaultFramebuffer + gScreenWidth * (gFaultCursorY + 3) * gHiResScale * 6;
    for (row = 0; row != 6; row++, glyph++) {
        for (i = 0; i < gHiResScale * gFaultCharScale; i++) {
            for (bit = 3; bit >= 0; bit--) {
                for (j = 0; j < gHiResScale * gFaultCharScale; j++) {
                    if (*glyph & (1 << bit)) {
                        *dst = gFaultFgColor;
                    } else {
                        *dst = gFaultBgColor;
                    }
                    dst++;
                }
            }
            dst += gScreenWidth - gFaultCharScale * 4 * gHiResScale;
        }
    }
}

#include "compiler/ido/stdarg.h"

extern s32 gFaultLineStartX;

void faultPrintf(const char *fmt, ...) {
    u8 *p;
    u8 buf[0x80];
    u8 c;
    s32 pad;

    vsprintf(buf, (const u8 *)fmt, (va_list)(&fmt + 1));
    p = buf;
    c = *p++;
    while (c) {
        switch (c) {
            case 32:
                gFaultCursorX += gFaultCharScale;
                break;
            case 9:
                gFaultCursorX = gFaultCursorX / 8;
                gFaultCursorX = gFaultCursorX + 1;
                gFaultCursorX = gFaultCursorX * 8;
                break;
            case 10:
                gFaultCursorX = gFaultLineStartX;
                gFaultCursorY += gFaultCharScale;
                break;
            default:
                faultDrawGlyph(c);
                gFaultCursorX += gFaultCharScale;
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

extern s32 gFaultStackTraceCount;
extern Ga136820Entry gFaultStackTrace[];
extern s32 gFaultDrawCount;
extern u8 gFaultMessageId;
extern s32 gFaultMessageArg0;
extern s32 gFaultMessageArg1;
extern s32 gFaultMessageArg2;
extern char *gFaultMessageStrings[];

void faultDrawRegs(OSThread *thread) {
    s32 y;
    s32 x;
    s32 j;
    __OSThreadContext *ctx;

    gFaultCharScale = 2;
    gFaultFgColor = 0xFFFF;
    gFaultBgColor = 1;
    ctx = &thread->context;
    for (y = 0, x = 0; y != 24; y += 6, x += 18) {
        gFaultCursorX = gFaultLineStartX = x;
        gFaultCursorY = y;
        faultPrintf("DK 64\n");
        faultPrintf("%X\n", ctx->pc);
        faultPrintf("%X\n", ((s32 *)&ctx->ra)[1]); // FAKE: low-word read of the u64 ra avoids the ucvt temps that shift gFaultDrawCount from t0 to t2
        if (gFaultDrawCount >= 4) {
            for (j = 0; j < gFaultStackTraceCount; j++) {
                faultPrintf("%X\n", gFaultStackTrace[j].unk0);
            }
        }
    }
    if (gFaultMessageId != 0) {
        faultPrintf("%s %x %x %x", gFaultMessageStrings[gFaultMessageId], gFaultMessageArg0, gFaultMessageArg1, gFaultMessageArg2);
    }
    if (gFaultDrawCount < 4) {
        gFaultDrawCount++;
    }
    if (gFaultDrawCount == 4) {
        faultUnwindStack(thread);
    }
}

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

s32 unwindDecodeJrRa(u32 a0, s32 *a1, s32 a2, s32 **a3) {
    if ((a0 & 0x3FFFFFF) == 0x3E00008) {
        unwindDecodeAddiuSp(**a3, a1);
        if (gFaultStackTraceCount != 0 && a2 == gFaultStackTrace[gFaultStackTraceCount - 1].unk0) {
            gFaultStackTrace[gFaultStackTraceCount - 1].unk4++;
        } else {
            gFaultStackTrace[gFaultStackTraceCount].unk0 = a2;
            gFaultStackTrace[gFaultStackTraceCount].unk4 = 1;
            gFaultStackTraceCount++;
        }
        *a3 = (s32 *)a2;
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
    gFaultStackTraceCount = 0;
    done = 0;
    while (pc != 0 && gFaultStackTraceCount < 18 && !done) {
        insn = *pc++;
        r = unwindDecodeJrRa(insn, &sp, ra, &pc);
        if (r == 0) {
            r = unwindDecodeLoadRa(insn, (s32 *)sp, &ra);
        }
        if (r == 0) {
            unwindDecodeAddiuSp(insn, &sp);
        }
        done = gFaultStackTraceCount != 0 ? gFaultStackTrace[gFaultStackTraceCount - 1].unk4 >= 16 : 0;
    }
    gFaultDrawCount++;
}

extern OSMesgQueue D_807FEF58;

extern s32 gFramebuffers[];
extern u8 D_807563B4;

void faultThreadMain(void *arg) {
    OSMesg msg;
    OSThread *thread;
    s32 i;
    s32 pad;

    osSetEventMesg(12, &D_807FEF58, (OSMesg)0x10);
    for (;;) {
        while (1) {
            osRecvMesg(&D_807FEF58, &msg, 1);
            if (D_807563B4 != 0) {
                break;
            }
        }
        thread = __osGetCurrFaultedThread();
        if (thread != 0) {
            for (;;) {
                for (i = 0; i < 2; i++) {
                    osViBlack(0);
                    gFaultFramebuffer = gFramebuffers[i];
                    faultDrawRegs(thread);
                    faultDrawRegs(thread);
                }
            }
        }
    }
}


void faultSetMessage(u8 a0, u32 a1, s32 a2, s32 a3) {
    gFaultMessageId = a0;
    gFaultMessageArg0 = a1;
    gFaultMessageArg1 = a2;
    gFaultMessageArg2 = a3;
    camEndPath(0);
}

extern OSMesg D_807FEF50;
extern OSThread D_807FDDA0;
extern u8 D_807563B0;

void faultThreadInit(void) {
    __osSetFpcCsr(__osGetFpcCsr() | 0x400);
    osCreateMesgQueue(&D_807FEF58, &D_807FEF50, 1);
    osCreateThread(&D_807FDDA0, 8, faultThreadMain, 0, &D_807FEF50, 0x32);
    osStartThread(&D_807FDDA0);
    D_807563B0 = 1;
}

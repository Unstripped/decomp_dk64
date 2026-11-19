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

void faultFontInit(s32 framebuffer, s32 x, s32 y) {
    gFaultFramebuffer = framebuffer;
    gFaultCharScale = 2;
    gFaultFgColor = 0xFFFF;
    gFaultBgColor = 1;
    gFaultCursorX = x;
    gFaultCursorY = y;
}

void faultFontSetColorMode(s32 mode) {
    if (mode == 0) {
        gFaultFgColor = 0xFFFF;
    } else {
        gFaultFgColor = 0xF801;
    }
}

extern u8 gHiResScale;
extern s16 gScreenWidth;

// Fault-screen font: 6 rows per glyph from '!' (data_inc.us.txt, tools/data_inc.py).
u8 sFaultFontGlyphs[0x230] = {
#include "global/sFaultFontGlyphs.inc.c"
};

void faultDrawGlyph(u8 c) {
    u8 *glyph;
    u16 *dst;
    s32 row;
    s32 i;
    s32 bit;
    s32 j;

    glyph = sFaultFontGlyphs + (c - 33) * 6;
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

const char D_8075FFF0[20] = "CLIP ARRAY OVERFLOW";
const char D_80760004[20] = "MAIN STACK OVERFLOW";
const char D_80760018[13] = "DFS OVERFLOW";
const char D_80760028[14] = "OUT OF MEMORY";
const char D_80760038[15] = "DATABASE ERROR";
const char D_80760048[10] = "DMA ERROR";
const char D_80760054[13] = "LOOKUP ERROR";
const char D_80760064[17] = "TOO MANY OBJECTS";
const char D_80760078[17] = "KILL SOUND ERROR";
const char D_8076008C[19] = "STORED STATE ERROR";
const char D_807600A0[18] = "MATRIX COPY ERROR";
const char D_807600B4[23] = "DELAYED KILLS OVERFLOW";
const char D_807600CC[20] = "LOCK STACK OVERFLOW";
const char D_807600E0[23] = "POSTFUNCTIONS OVERFLOW";
const char D_807600F8[17] = "SIGNALS OVERFLOW";
const char D_8076010C[22] = "SORT LIST EARLY ERROR";
const char D_80760124[21] = "SORT LIST LATE ERROR";
const char D_8076013C[19] = "DISPLAY LIST ERROR";
const char D_80760150[22] = "OBJECT EXIST OVERFLOW";

// faultPrintf message per gFaultMessageId (entry 0 is not a string).
const char *gFaultMessageStrings[20] = {
    (const char *)0x08000000, D_8075FFF0, D_80760004, D_80760018,
    D_80760028, D_80760038, D_80760048, D_80760054,
    D_80760064, D_80760078, D_8076008C, D_807600A0,
    D_807600B4, D_807600CC, D_807600E0, D_807600F8,
    D_8076010C, D_80760124, D_8076013C, D_80760150,
};
u8 gFaultThreadStarted = 0;
u8 gFaultScreenEnabled = 0;
s32 gFaultDrawCount = 0;

// One unwound frame of the fault-screen stack trace: a return address and how often it repeated.
typedef struct FaultStackEntry {
    s32 ra;
    s32 count;
} FaultStackEntry;

extern s32 gFaultStackTraceCount;
extern FaultStackEntry gFaultStackTrace[];
extern u8 gFaultMessageId;
extern s32 gFaultMessageArg0;
extern s32 gFaultMessageArg1;
extern s32 gFaultMessageArg2;

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
                faultPrintf("%X\n", gFaultStackTrace[j].ra);
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

s32 unwindDecodeLoadRa(s32 insn, s32 *sp, s32 *ra) {
    if ((insn & 0xFFFF0000) == 0x8FBF0000) {
        *ra = *(s32 *)((u8 *)sp + (s16)(insn & 0xFFFF));
        return 1;
    }
    return 0;
}

s32 unwindDecodeAddiuSp(s32 insn, s32 *sp) {
    if ((insn & 0xFFFF0000) == 0x27BD0000) {
        s32 v = *sp;
        v += (s16)(insn & 0xFFFF);
        *sp = v;
        return 1;
    }
    return 0;
}

s32 unwindDecodeJrRa(u32 insn, s32 *sp, s32 ra, s32 **pc) {
    if ((insn & 0x3FFFFFF) == 0x3E00008) {
        unwindDecodeAddiuSp(**pc, sp);
        if (gFaultStackTraceCount != 0 && ra == gFaultStackTrace[gFaultStackTraceCount - 1].ra) {
            gFaultStackTrace[gFaultStackTraceCount - 1].count++;
        } else {
            gFaultStackTrace[gFaultStackTraceCount].ra = ra;
            gFaultStackTrace[gFaultStackTraceCount].count = 1;
            gFaultStackTraceCount++;
        }
        *pc = (s32 *)ra;
        return 1;
    }
    return 0;
}

void faultUnwindStack(OSThread *thread) {
    s32 pad;
    s32 *pc;
    s32 r;
    s32 sp;
    s32 ra;
    s32 insn;
    s32 done;

    pc = (s32 *)thread->context.pc;
    sp = thread->context.sp;
    ra = thread->context.ra;
    gFaultStackTraceCount = 0;
    done = 0;
    while (pc != NULL && gFaultStackTraceCount < 18 && !done) {
        insn = *pc++;
        r = unwindDecodeJrRa(insn, &sp, ra, &pc);
        if (r == 0) {
            r = unwindDecodeLoadRa(insn, (s32 *)sp, &ra);
        }
        if (r == 0) {
            unwindDecodeAddiuSp(insn, &sp);
        }
        done = gFaultStackTraceCount != 0 ? gFaultStackTrace[gFaultStackTraceCount - 1].count >= 16 : 0;
    }
    gFaultDrawCount++;
}

extern OSMesgQueue sFaultMesgQueue;

extern s32 gFramebuffers[];

void faultThreadMain(void *arg) {
    OSMesg msg;
    OSThread *thread;
    s32 i;
    s32 pad;

    osSetEventMesg(OS_EVENT_FAULT, &sFaultMesgQueue, (OSMesg)0x10);
    for (;;) {
        while (1) {
            osRecvMesg(&sFaultMesgQueue, &msg, OS_MESG_BLOCK);
            if (gFaultScreenEnabled != 0) {
                break;
            }
        }
        thread = __osGetCurrFaultedThread();
        if (thread != NULL) {
            for (;;) {
                for (i = 0; i < 2; i++) {
                    osViBlack(FALSE);
                    gFaultFramebuffer = gFramebuffers[i];
                    faultDrawRegs(thread);
                    faultDrawRegs(thread);
                }
            }
        }
    }
}


void faultSetMessage(u8 id, u32 msgArg0, s32 msgArg1, s32 msgArg2) {
    gFaultMessageId = id;
    gFaultMessageArg0 = msgArg0;
    gFaultMessageArg1 = msgArg1;
    gFaultMessageArg2 = msgArg2;
    camEndPath(0);
}

extern OSMesg sFaultMesg;
extern OSThread sFaultThread;

void faultThreadInit(void) {
    __osSetFpcCsr(__osGetFpcCsr() | FPCSR_EZ);
    osCreateMesgQueue(&sFaultMesgQueue, &sFaultMesg, 1);
    osCreateThread(&sFaultThread, 8, faultThreadMain, 0, &sFaultMesg, 0x32);
    osStartThread(&sFaultThread);
    gFaultThreadStarted = 1;
}

#include "common.h"
#include "segment.h"
#include "boot.h"
#include "proto/boot/1630.h"
#include "proto/boot/30E0.h"

extern u8 *sNoExpPakStackBase;
extern OSMesgQueue sNoExpPakViMesgQueue;
extern OSMesg sNoExpPakViMesgBuf[];

u32 D_8000DE80[2] = { 0 }; // unreferenced
// gzip stream of the 64x64 image noExpPakThread unpacks; ROM-extracted (data_inc.us.txt).
u8 sNoExpPakImageGz[0xE81] = {
#include "boot/sNoExpPakImageGz.inc.c"
};


void noExpPakScreen(void) {
    sNoExpPakStackBase = (u8 *)0x80130000;
    osCreateThread(&sNoExpPakThread, 2, noExpPakThread, NULL, sNoExpPakStackBase + 0x3E80, 10);
    osStartThread(&sNoExpPakThread);
    while (1) {
    }
}

void noExpPakThread(void *arg) {
    s32 i;
    s32 x;
    s32 y;
    u16 *textFb;
    u16 *imageFb;
    s32 pad[2]; /* unused: reserve their stack slots */
    u16 *fb[2] = { (u16 *)0x80200000, (u16 *)0x80100000 };
    s16 delay[2] = { 120, 60 };
    s8 cur = 1;
    u8 *src = sNoExpPakImageGz;
    u8 *dst = (u8 *)0x80280000;
    u32 unused[3] = { OS_VI_PAL_LPF1, OS_VI_NTSC_LPN1, OS_VI_MPAL_LPN1 }; // the triple main's bootMainThread indexes

    gunzip(&src, &dst, (void *)0x80180000);
    textFb = (u16 *)0x80200000;
    imageFb = (u16 *)0x80100000;
    for (i = 0; i < 320 * 240; i++) {
        textFb[i] = 0;
        imageFb[i] = 0;
    }
    for (y = 0; y < 64; y++) {
        for (x = 0; x < 64; x++) {
            ((u16 *)0x80109600)[y * 320 + 128 + x] = ((s16 *)0x80280000)[((63 - y) << 6) + x];
        }
    }
    osWritebackDCache(imageFb, 320 * 240 * 2);
    osCreateMesgQueue(&sNoExpPakViMesgQueue, sNoExpPakViMesgBuf, 5);
    osViSetEvent(&sNoExpPakViMesgQueue, NULL, 1);
    if (osTvType == 0) {
        while (1) {
        }
    }
    noExpPakDrawScreen();
    noExpPakDrawText(textFb);
    x = 0;
    while (1) {
        osRecvMesg(&sNoExpPakViMesgQueue, NULL, OS_MESG_BLOCK);
        x++;
        if (x >= delay[cur]) {
            osViSwapBuffer(fb[cur]);
            osViBlack(0);
            cur = 1 - cur;
            x = 0;
        }
    }
}

// .data after noExpPakThread's three local templates (IDO emits .data in definition order).
u8 sNoExpPakTextLine1[0x1C] = "       Nhf EXPANSION PAK}";
u8 sNoExpPakTextLine2[0x18] = "          NOT INSTALLED";
u8 sNoExpPakTextLine3[0x20] = "THE Nhf EXPANSION PAK ACCESSORY";
u8 sNoExpPakTextLine4[0x24] = "MUST BE INSTALLED IN THE Nhf~ FOR";
u8 sNoExpPakTextLine5[0x24] = "THIS GAME[ SEE THE Nhf EXPANSION";
u8 sNoExpPakTextLine6[0x1C] = "   PAK INSTRUCTION BOOKLET[";

void noExpPakDrawScreen(void) {
    s32 i;
    s32 *hdr;
    s32 pad0;
    u8 *src;
    u8 *dst;
    s32 pad1;
    s32 pad2;
    s32 pad3; /* pad0..pad3: unused, reserve stack slots */

    if (osTvType == 0) {
        /* one-line loop body: IDO schedules the unrolled stores differently otherwise */
        for (i = 0; i < 320 * 240; i++) ((u16 *)0x80100000)[i] = 0;
    } else {
        hdr = (s32 *)0x80280000;
        dmaSegment11(0x38, 0x10, hdr);
        dmaSegment11(hdr[0] + 0x4C, 0x10, hdr);
        dmaSegment11(hdr[0], hdr[1] - hdr[0], hdr);
        src = (u8 *)hdr;
        dst = (u8 *)0x80380000;
        gunzip(&src, &dst, (void *)0x803C0000);
        noExpPakDrawText((u16 *)0x80100000);
    }
}

void noExpPakDrawText(u16 *buf) {
    if (osTvType != 0) {
        bootDrawString(buf, 0x15, 0x8C, sNoExpPakTextLine1);
        bootDrawString(buf, 0x15, 0x96, sNoExpPakTextLine2);
        bootDrawString(buf, 0x15, 0xAA, sNoExpPakTextLine3);
        bootDrawString(buf, 0x15, 0xB4, sNoExpPakTextLine4);
        bootDrawString(buf, 0x15, 0xBE, sNoExpPakTextLine5);
        bootDrawString(buf, 0x15, 0xC8, sNoExpPakTextLine6);
    }
}

void bootDrawString(u16 *buf, s32 x, s32 y, const u8 *str) {
    const u8 *p;

    if (*str != 0) {
        p = str;
        do {
            if (*p != ' ') {
                bootDrawGlyph(buf, x, y, *p);
            } else {
                x -= 2;
            }
            x += 9;
            p++;
        } while (*p != 0);
    }
    osWritebackDCache(buf, 320 * 240 * 2);
}

void bootDrawGlyph(u16 *buf, s32 x, s32 y, u8 c) {
    u8 *font;
    u8 mask;

    font = (u8 *)0x8037FEFC; /* assigned first: changes IDO's register choice */
    if (c > 0x78) {
        c += 2;
    }
    buf += y * 320 + x;
    font += c * 4;
    for (y = 0; y < 8; y++) {
        mask = 0xF0;
        for (x = 0; x < 8; x++) {
            if (font[x >> 1] & mask) {
                *buf = 0xFFFF;
            } else {
                *buf = 1;
            }
            buf++;
            mask = ~mask;
        }
        font += 0x100;
        buf += 312;
    }
}

void dmaSegment11(s32 offset, s32 size, void *dst) {
    while ((size & 0xF) != 0) {
        size++;
    }
    osWritebackDCache(dst, size);
    __osPiRawStartDma(0, gSegmentTable[11].romStart + offset, dst, size);
    do {
    } while (osPiGetStatus() & 1);
    osInvalDCache(dst, size);
}

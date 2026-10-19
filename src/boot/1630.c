#include "common.h"

typedef struct {
    u32 romStart;
    u32 romEnd;
    u32 vramStart;
    u32 vramEnd;
    u32 bssStart;
    u32 bssEnd;
} SegmentTableEntry;

extern OSThread D_800138C0;
extern u8 *D_80013A70;
extern OSMesgQueue D_80013A78;
extern OSMesg D_80013A90[];
extern SegmentTableEntry gSegmentTable[];

typedef struct {
    u16 *buf[2];
} FbPair;

typedef struct {
    s16 ticks[2];
} VsyncDelays;

typedef struct {
    u32 w[3];
} Words3;

extern u8 D_8000DE88[];
extern FbPair D_8000ED0C;
extern VsyncDelays D_8000ED14;
extern Words3 D_8000ED18;
extern u8 D_8000ED24[];
extern u8 D_8000ED40[];
extern u8 D_8000ED58[];
extern u8 D_8000ED78[];
extern u8 D_8000ED9C[];
extern u8 D_8000EDC0[];

void gunzip(void *, void *, u32);
void noExpPakThread(void *);
void noExpPakDrawScreen(void);
void noExpPakDrawText(u16 *);
void bootDrawString(u16 *, s32, s32, const u8 *);
void bootDrawGlyph(u16 *, s32, s32, u8);
void dmaSegment11(s32, s32, void *);

void noExpPakScreen(void) {
    D_80013A70 = (u8 *)0x80130000;
    osCreateThread(&D_800138C0, 2, noExpPakThread, NULL, D_80013A70 + 0x3E80, 10);
    osStartThread(&D_800138C0);
    while (1) {
    }
}

void noExpPakThread(void *arg) {
    s32 count;
    s32 i;
    s32 x;
    s32 y;
    u16 *a;
    u16 *b;
    s32 pad; /* unused: reserves its stack slot */
    FbPair fb = D_8000ED0C;
    VsyncDelays delay = D_8000ED14;
    s8 cur = 1;
    void *src = D_8000DE88;
    void *dst = (void *)0x80280000;
    Words3 unused = D_8000ED18;

    gunzip(&src, &dst, 0x80180000);
    a = (u16 *)0x80200000;
    b = (u16 *)0x80100000;
    for (i = 0; i < 320 * 240; i++) {
        a[i] = 0;
        b[i] = 0;
    }
    for (y = 0; y < 64; y++) {
        for (x = 0; x < 64; x++) {
            ((u16 *)0x80109600)[y * 320 + 128 + x] = ((s16 *)0x80280000)[((63 - y) << 6) + x];
        }
        x = 0; /* dead store: keeps IDO from unrolling the copy loop */
    }
    osWritebackDCache((void *)0x80100000, 320 * 240 * 2);
    osCreateMesgQueue(&D_80013A78, D_80013A90, 5);
    osViSetEvent(&D_80013A78, NULL, 1);
    if (osTvType == 0) {
        while (1) {
        }
    }
    noExpPakDrawScreen();
    noExpPakDrawText((u16 *)0x80200000);
    count = 0;
    while (1) {
        osRecvMesg(&D_80013A78, NULL, OS_MESG_BLOCK);
        count++;
        if (count >= delay.ticks[cur]) {
            osViSwapBuffer(fb.buf[cur]);
            osViBlack(0);
            cur = 1 - cur;
            count = 0;
        }
    }
}

void noExpPakDrawScreen(void) {
    s32 i;
    s32 *hdr;
    s32 pad0;
    void *src;
    void *dst;
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
        src = hdr;
        dst = (void *)0x80380000;
        gunzip(&src, &dst, 0x803C0000);
        noExpPakDrawText((u16 *)0x80100000);
    }
}

void noExpPakDrawText(u16 *buf) {
    if (osTvType != 0) {
        bootDrawString(buf, 0x15, 0x8C, D_8000ED24);
        bootDrawString(buf, 0x15, 0x96, D_8000ED40);
        bootDrawString(buf, 0x15, 0xAA, D_8000ED58);
        bootDrawString(buf, 0x15, 0xB4, D_8000ED78);
        bootDrawString(buf, 0x15, 0xBE, D_8000ED9C);
        bootDrawString(buf, 0x15, 0xC8, D_8000EDC0);
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

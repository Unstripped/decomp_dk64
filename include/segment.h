#ifndef SEGMENT_H
#define SEGMENT_H

#include "common.h"

// ROM/VRAM/BSS bounds of one code segment: boot main() fills the table, loadOverlay
// and the boot DMA helpers read it.
typedef struct SegmentTableEntry {
    /* 0x00 */ u32 romStart;
    /* 0x04 */ u32 romEnd;
    /* 0x08 */ u32 vramStart;
    /* 0x0C */ u32 vramEnd;
    /* 0x10 */ u32 bssStart;
    /* 0x14 */ u32 bssEnd;
} SegmentTableEntry; // size = 0x18

extern SegmentTableEntry gSegmentTable[18];

#endif

// camInitZones (src/global/201B0.c): W2IntD: stage 5/6 exact count 338, score 195 -> 25 (shape 0): remaining = first heapAlloc leaf (lh a0 vs ring t6 + P t6 vs t5), group-count candidate v1 vs a0, loop-4 pointer v0 vs t0 + ring phase. Levers: dead read 'if (CAM_ZONE_SORT[0].unk2 && ..) {}' after heapFree burns ONE ring temp (195->63), insertion-sort stmt order key/idx/val (43->39), loop-3 compare spelled gCamZoneSorted[i*2+1] != [(i-1)*2+1] (39->36), if (gCamZoneGroupCount) {} FAKE (36->25). ring leaf a0 at first alloc: ugen puts the first arg-tree leaf in a0 whenever free; target uses ring t6/t7 (no spelling found: sz local, casts, k local, tree shapes all tried).
typedef unsigned char u8;
typedef short s16;
typedef int s32;

typedef struct CamZoneEntry {
    /* 0x00 */ u8 pad0[0x18];
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 pad19[3];
} CamZoneEntry;

typedef struct CamZonePair {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 unk2;
} CamZonePair;

typedef struct CamPathZoneEntries {
    /* 0x00 */ u8 pad0[0xC0];
    /* 0xC0 */ s16 unkC0;
    /* 0xC2 */ u8 padC2[2];
    /* 0xC4 */ CamZoneEntry *unkC4;
} CamPathZoneEntries;

typedef struct CamPathData CamPathData;

extern CamPathData *gCamActivePaths;
extern s16 *gCamZoneSorted;
extern s16 *gCamZoneGroups;
extern s16 gCamZoneGroupCount;
extern s16 gCamZoneMinX;
extern s16 gCamZoneMaxX;
extern s16 gCamZoneMinZ;
extern s16 gCamZoneGridWidth;

void camGetZoneBounds(s16 *, s16 *, s16 *);
s16 camGetZoneCell(s32);
void *heapAlloc(s32);
void heapFree(void *);

#define CAM_ZONE_GROUP ((CamZonePair *)gCamZoneGroups)
#define CAM_ZONE_SORT ((CamZonePair *)gCamZoneSorted)
#define CAM_ZONE_ENTRIES_PATH ((CamPathZoneEntries *)gCamActivePaths)

void camInitZones(void) {
    s16 i;
    s16 j;
    s16 k;
    s16 key;
    s16 idx;
    s16 val;

    camGetZoneBounds(&gCamZoneMinX, &gCamZoneMaxX, &gCamZoneMinZ);
    gCamZoneMaxX = gCamZoneMaxX / 400 * 400 + 400;
    gCamZoneMinX = gCamZoneMinX / 400 * 400;
    gCamZoneGridWidth = (gCamZoneMaxX - gCamZoneMinX) / 400;
    gCamZoneMinZ = gCamZoneMinZ / 400 * 400;
    if (gCamZoneSorted != NULL) {
        heapFree(gCamZoneSorted);
        if (CAM_ZONE_SORT[0].unk2 && CAM_ZONE_SORT[0].unk2) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    }
    gCamZoneSorted = heapAlloc((CAM_ZONE_ENTRIES_PATH->unkC0 * 4) + 4);
    for (i = 0; i < CAM_ZONE_ENTRIES_PATH->unkC0; i++) {
        gCamZoneSorted[i * 2] = i;
        gCamZoneSorted[i * 2 + 1] = camGetZoneCell(i);
    }
    for (i = 1; i < CAM_ZONE_ENTRIES_PATH->unkC0; i++) {
        key = gCamZoneSorted[i * 2 + 1];
        idx = gCamZoneSorted[i * 2];
        val = gCamZoneSorted[i * 2 + 1];
        j = i;
        while (j > 0 &&
               (key < gCamZoneSorted[(j - 1) * 2 + 1] ||
                (key == gCamZoneSorted[(j - 1) * 2 + 1] &&
                 CAM_ZONE_ENTRIES_PATH->unkC4[gCamZoneSorted[(j - 1) * 2]].unk18 < CAM_ZONE_ENTRIES_PATH->unkC4[gCamZoneSorted[j * 2]].unk18))) {
            gCamZoneSorted[j * 2] = gCamZoneSorted[(j - 1) * 2];
            gCamZoneSorted[j * 2 + 1] = gCamZoneSorted[(j - 1) * 2 + 1];
            j--;
        }
        if (j != i) {
            gCamZoneSorted[j * 2] = idx;
            gCamZoneSorted[j * 2 + 1] = val;
        }
    }
    gCamZoneGroupCount = 1;
    for (i = CAM_ZONE_ENTRIES_PATH->unkC0 - 1; i > 0; i--) {
        if (gCamZoneSorted[i * 2 + 1] != gCamZoneSorted[(i - 1) * 2 + 1]) {
            gCamZoneGroupCount++;
        }
    }
    if (gCamZoneGroups != NULL) {
        if (CAM_ZONE_SORT[0].unk2 && CAM_ZONE_SORT[0].unk2) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        heapFree(gCamZoneGroups);
    }
    if (gCamZoneGroupCount) {}  // FAKE: dead read, makes the count a coloured candidate (v1) before the group alloc
    gCamZoneGroups = heapAlloc(gCamZoneGroupCount * 4 + 4);
    CAM_ZONE_GROUP[0].unk0 = CAM_ZONE_SORT[0].unk2;
    CAM_ZONE_GROUP[0].unk2 = 0;
    k = 1;
    for (i = 1; i < CAM_ZONE_ENTRIES_PATH->unkC0; i++) {
        if (CAM_ZONE_SORT[i].unk2 != CAM_ZONE_SORT[i - 1].unk2) {
            CAM_ZONE_GROUP[k].unk0 = CAM_ZONE_SORT[i].unk2;
            if (CAM_ZONE_ENTRIES_PATH->unkC0 && CAM_ZONE_ENTRIES_PATH->unkC0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            CAM_ZONE_GROUP[k].unk2 = i;
            k++;
        }
    }
    CAM_ZONE_GROUP[k].unk0 = -1;
    CAM_ZONE_GROUP[k].unk2 = CAM_ZONE_ENTRIES_PATH->unkC0;
}

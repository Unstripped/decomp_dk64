// camInitZones (src/global/201B0.c): stage 5: exact 312 vs 312 insns (reloc=0 shape=0), gCamZoneSorted s16 array indexing in loops 1-2 matches loop index copies, separate val/key variables match double sign-extension, remaining diff only regalloc
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
    }
    gCamZoneSorted = heapAlloc((CAM_ZONE_ENTRIES_PATH->unkC0 * 4) + 4);
    for (i = 0; i < CAM_ZONE_ENTRIES_PATH->unkC0; i++) {
        gCamZoneSorted[i * 2] = i;
        gCamZoneSorted[i * 2 + 1] = camGetZoneCell(i);
    }
    for (i = 1; i < CAM_ZONE_ENTRIES_PATH->unkC0; i++) {
        key = gCamZoneSorted[i * 2 + 1];
        val = gCamZoneSorted[i * 2 + 1];
        idx = gCamZoneSorted[i * 2];
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
        if (CAM_ZONE_SORT[i].unk2 != CAM_ZONE_SORT[i - 1].unk2) {
            gCamZoneGroupCount++;
        }
    }
    if (gCamZoneGroups != NULL) {
        heapFree(gCamZoneGroups);
    }
    gCamZoneGroups = heapAlloc(gCamZoneGroupCount * 4 + 4);
    CAM_ZONE_GROUP[0].unk0 = CAM_ZONE_SORT[0].unk2;
    CAM_ZONE_GROUP[0].unk2 = 0;
    k = 1;
    for (i = 1; i < CAM_ZONE_ENTRIES_PATH->unkC0; i++) {
        if (CAM_ZONE_SORT[i].unk2 != CAM_ZONE_SORT[i - 1].unk2) {
            CAM_ZONE_GROUP[k].unk0 = CAM_ZONE_SORT[i].unk2;
            CAM_ZONE_GROUP[k].unk2 = i;
            k++;
        }
    }
    CAM_ZONE_GROUP[k].unk0 = -1;
    CAM_ZONE_GROUP[k].unk2 = CAM_ZONE_ENTRIES_PATH->unkC0;
}

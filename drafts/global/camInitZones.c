// camInitZones (src/global/201B0.c): camInitZones (src/global/201B0.c): revisit 7 MiscA: stage 6, deadsweep score 25 -> 1 (text 1: only 'lhu t6' vs target 'lh t6' in the first heapAlloc arg; no dead-test FAKE left). Levers: (1) (((u16)P->unkC0 & 0xFFFF) * 4) + 4 -- the and-mask tree makes the lhu leaf a ring temp (t6) instead of ugen's a0 'first leaf of a unary parm chain' (as1 deletes the redundant andi after lhu); fixed the whole ring phase so all 3 old FAKEs became unnecessary. (2) group-build loop compare/stores through flat gCamZoneSorted[i*2+1] plus a hidden local assigned in the condition: if ((val = S[i*2+1]) != S[(i-1)*2+1]) G[k].unk0 = val; (key/idx/val/j all equal) fixed the v0/v1/a0 colouring. Not found: a spelling keeping signed lh with a ring leaf (tried casts, new locals of every type, in-expression assigns, callee proto widths u32/s32, raw/struct spellings, dead tests, 10 binary-op no-ops).
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
    gCamZoneSorted = heapAlloc((((u16)CAM_ZONE_ENTRIES_PATH->unkC0 & 0xFFFF) * 4) + 4);  // FAKE: binary and-tree puts the lhu leaf in a ring temp (t6) instead of a0 (the original is lh)
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
        heapFree(gCamZoneGroups);
    }
    gCamZoneGroups = heapAlloc(gCamZoneGroupCount * 4 + 4);
    CAM_ZONE_GROUP[0].unk0 = CAM_ZONE_SORT[0].unk2;
    CAM_ZONE_GROUP[0].unk2 = 0;
    k = 1;
    for (i = 1; i < CAM_ZONE_ENTRIES_PATH->unkC0; i++) {
        if ((val = gCamZoneSorted[i * 2 + 1]) != gCamZoneSorted[(i - 1) * 2 + 1]) {
            CAM_ZONE_GROUP[k].unk0 = val;
            CAM_ZONE_GROUP[k].unk2 = i;
            k++;
        }
    }
    CAM_ZONE_GROUP[k].unk0 = -1;
    CAM_ZONE_GROUP[k].unk2 = CAM_ZONE_ENTRIES_PATH->unkC0;
}

// camInitZones (src/global/201B0.c): stage 5: 13 insns short (299 vs 312); target has index copies move s2,s0 in loop1, move a0,t5 and a0,t6 in insertion sort loop; tested struct copy, s32 locals, macro cleanup
typedef struct OlG_CamZonePair {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 unk2;
} OlG_CamZonePair;

typedef struct OlG_CamPathZoneEntries {
    /* 0x00 */ u8 pad0[0xC0];
    /* 0xC0 */ s16 unkC0;
    /* 0xC2 */ u8 padC2[2];
    /* 0xC4 */ CamZoneEntry *unkC4;
} OlG_CamPathZoneEntries;

void *heapAlloc(s32);
void heapFree(void *);

#define OlG_CAM_ZONE_GROUP ((OlG_CamZonePair *)gCamZoneGroups)
#define OlG_CAM_ZONE_SORT ((OlG_CamZonePair *)gCamZoneSorted)
#define CAM_ZONE_ENTRIES_PATH ((OlG_CamPathZoneEntries *)gCamActivePaths)

void camInitZones(void) {
    s16 i;
    s16 j;
    s16 k;
    s16 key;
    s16 idx;

    camGetZoneBounds(&gCamZoneMinX, &gCamZoneMaxX, &gCamZoneMinZ);
    gCamZoneMaxX = gCamZoneMaxX / 400 * 400 + 400;
    gCamZoneMinX = gCamZoneMinX / 400 * 400;
    gCamZoneGridWidth = (gCamZoneMaxX - gCamZoneMinX) / 400;
    gCamZoneMinZ = gCamZoneMinZ / 400 * 400;
    if (gCamZoneSorted != NULL) {
        heapFree(gCamZoneSorted);
    }
    gCamZoneSorted = heapAlloc(CAM_ZONE_ENTRIES_PATH->unkC0 * 4 + 4);
    for (i = 0; i < CAM_ZONE_ENTRIES_PATH->unkC0; i++) {
        OlG_CAM_ZONE_SORT[i].unk0 = i;
        OlG_CAM_ZONE_SORT[i].unk2 = camGetZoneCell(i);
    }
    for (i = 1; i < CAM_ZONE_ENTRIES_PATH->unkC0; i++) {
        key = OlG_CAM_ZONE_SORT[i].unk2;
        idx = OlG_CAM_ZONE_SORT[i].unk0;
        j = i;
        while (j > 0 &&
               (key < OlG_CAM_ZONE_SORT[j - 1].unk2 ||
                (key == OlG_CAM_ZONE_SORT[j - 1].unk2 &&
                 CAM_ZONE_ENTRIES_PATH->unkC4[OlG_CAM_ZONE_SORT[j - 1].unk0].unk18 < CAM_ZONE_ENTRIES_PATH->unkC4[OlG_CAM_ZONE_SORT[j].unk0].unk18))) {
            OlG_CAM_ZONE_SORT[j].unk0 = OlG_CAM_ZONE_SORT[j - 1].unk0;
            OlG_CAM_ZONE_SORT[j].unk2 = OlG_CAM_ZONE_SORT[j - 1].unk2;
            j--;
        }
        if (j != i) {
            OlG_CAM_ZONE_SORT[j].unk0 = idx;
            OlG_CAM_ZONE_SORT[j].unk2 = key;
        }
    }
    gCamZoneGroupCount = 1;
    for (i = CAM_ZONE_ENTRIES_PATH->unkC0 - 1; i > 0; i--) {
        if (OlG_CAM_ZONE_SORT[i].unk2 != OlG_CAM_ZONE_SORT[i - 1].unk2) {
            gCamZoneGroupCount++;
        }
    }
    if (gCamZoneGroups != NULL) {
        heapFree(gCamZoneGroups);
    }
    gCamZoneGroups = heapAlloc(gCamZoneGroupCount * 4 + 4);
    OlG_CAM_ZONE_GROUP[0].unk0 = OlG_CAM_ZONE_SORT[0].unk2;
    OlG_CAM_ZONE_GROUP[0].unk2 = 0;
    k = 1;
    for (i = 1; i < CAM_ZONE_ENTRIES_PATH->unkC0; i++) {
        if (OlG_CAM_ZONE_SORT[i].unk2 != OlG_CAM_ZONE_SORT[i - 1].unk2) {
            OlG_CAM_ZONE_GROUP[k].unk0 = OlG_CAM_ZONE_SORT[i].unk2;
            OlG_CAM_ZONE_GROUP[k].unk2 = i;
            k++;
        }
    }
    OlG_CAM_ZONE_GROUP[k].unk0 = -1;
    OlG_CAM_ZONE_GROUP[k].unk2 = CAM_ZONE_ENTRIES_PATH->unkC0;
}

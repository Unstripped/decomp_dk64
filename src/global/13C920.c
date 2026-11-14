#include "common.h"
#include "proto/global/13C920.h"

extern u8 gAudioSurroundEnabled;
extern u8 gAudioMonoEnabled;
extern u8 D_807FF0F2;
extern u8 gAuxBusStereo[];
extern u8 gAuxBusInvertCoefs[];
extern u8 gAuxBusOutputMode[];

void configureCSPOutputMode(u8 mode) {
    s32 i;

    gAudioSurroundEnabled = 0;
    gAudioMonoEnabled = 0;
    D_807FF0F2 = 0;
    switch (mode) {
        case 1:
            gAudioMonoEnabled = 1;
            break;
        case 3:
            D_807FF0F2 = 1;
            break;
        case 4:
            gAudioSurroundEnabled = 1;
            break;
    }
    for (i = 0; i < 2; i++) {
        updateCSPOutputChannelMode(i, 0);
    }
}

void updateCSPOutputChannelMode(s32 chan, s32 outputMode) {
    if (outputMode == 0) {
        outputMode = gAuxBusOutputMode[chan];
    }
    gAuxBusStereo[chan] = 0;
    gAuxBusInvertCoefs[chan] = 0;
    switch (outputMode) {
        case 2:
            if (gAudioSurroundEnabled != 0) {
                gAuxBusInvertCoefs[chan] = 1;
            }
            break;
        case 3:
            if (gAudioSurroundEnabled != 0) {
                gAuxBusStereo[chan] = 1;
            }
            break;
        case 4:
            if (gAudioMonoEnabled == 0) {
                gAuxBusStereo[chan] = 1;
            }
            break;
        case 5:
            if (gAudioMonoEnabled == 0) {
                gAuxBusStereo[chan] = 1;
                gAuxBusInvertCoefs[chan] = 1;
            }
            break;
    }
    gAuxBusOutputMode[chan] = outputMode;
}

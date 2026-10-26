// func_8060C8AC (src/global/104F0.c): stage 3: reduced m2c temps to one loop index plus shared source/destination pointers; closest frame is 0x48 versus target 0x40. All substantive loads/calls/copies match; remaining differences are the extra frame slot, u8 call-argument masks, and branch scheduling around configuration loops.
typedef struct P104L3Config {
    s16 value;
    u8 byte2;
    u8 byte3;
    u8 byte4;
    u8 byte5;
} P104L3Config;

extern void func_8060C648(s32, s32, s32, s32, s32);
extern s32 D_807467EC[];
extern P104L3Config D_80744548[];
extern P104L3Config D_80744568[];

const u8 D_80757044[] = "\0dAAA\0\0ZAAA\0\0PAAA\0\0FAAA\0\0<AAA\0";
const u8 D_80757064[] = "\0dAAA\0\0ZAAA\0\0PAAA\0\0FAAA\0\0<AAA\0";

void func_8060C8AC(u8 arg0) {
    s32 i;
    const P104L3Config *source;
    P104L3Config *destination;

    if (arg0 & 1) {
        func_8060C648(0x11, 0, 0, 0, 0);
    }
    if (arg0 & 2) {
        for (i = 0; i != 5; i++) {
            func_8060C648(0x15, 0, i & 0xFF, 0, D_807467EC[i]);
            func_8060C648(0x12, 0, i & 0xFF, 0, 0x20);
            func_8060C648(0x13, 0, i & 0xFF, 0, 0x20);
            func_8060C648(0x14, 0, i & 0xFF, 0, 0x20);
        }
    }
    if (arg0 & 4) {
        source = (const P104L3Config *) D_80757044;
        destination = D_80744548;
        for (i = 0; i != 5; i++, source++, destination++) {
            func_8060C648(0x19, 0, i & 0xFF, 0, source->value);
            func_8060C648(0x16, 0, i & 0xFF, 0, source->byte2);
            func_8060C648(0x17, 0, i & 0xFF, 0, source->byte3);
            func_8060C648(0x18, 0, i & 0xFF, 0, source->byte4);
            *destination = *source;
        }
    }
    if (arg0 & 8) {
        source = (const P104L3Config *) D_80757064;
        destination = D_80744568;
        for (i = 0; i != 5; i++, source++, destination++) {
            func_8060C648(0x1D, 0, i & 0xFF, 0, source->value);
            func_8060C648(0x1A, 0, i & 0xFF, 0, source->byte2);
            func_8060C648(0x1B, 0, i & 0xFF, 0, source->byte3);
            func_8060C648(0x1C, 0, i & 0xFF, 0, source->byte4);
            *destination = *source;
        }
    }
    if (arg0 & 0x10) {
        func_8060C648(0x1E, 0, 0, 0, 0);
    }
    if (arg0 & 0x20) {
        func_8060C648(0x1F, 0, 0, 0, 0);
    }
}

// func_8060C8AC (src/global/104F0.c): stage 3: m2c-shaped configuration with C string literals and typed 6-byte records; remaining diff is 0x70 stack frame versus target 0x40 plus counter/pointer register allocation and redundant u8 argument masks.
typedef struct P104L2_ConfigEntry {
    s16 unk0;
    u8 unk2;
    u8 unk3;
    u8 unk4;
    u8 unk5;
} P104L2_ConfigEntry;

extern void func_8060C648(s32, s32, s32, s32, s32);
extern s32 D_807467EC;
extern P104L2_ConfigEntry D_80744548[];
extern P104L2_ConfigEntry D_80744568[];

const u8 D_80757044[] = "\0dAAA\0\0ZAAA\0\0PAAA\0\0FAAA\0\0<AAA\0";
const u8 D_80757064[] = "\0dAAA\0\0ZAAA\0\0PAAA\0\0FAAA\0\0<AAA\0";

void func_8060C8AC(s32 arg0) {
    s32 sp38;
    const P104L2_ConfigEntry *var_s1_2;
    const P104L2_ConfigEntry *var_s1_3;
    P104L2_ConfigEntry *var_s3;
    P104L2_ConfigEntry *var_s3_2;
    s32 *var_s1;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_s0_3;
    s32 temp_t6;
    s32 var_s2;
    s32 var_s2_2;
    s32 var_s2_3;

    temp_t6 = arg0 & 0xFF;
    sp38 = temp_t6;
    if (temp_t6 & 1) {
        func_8060C648(0x11, 0, 0, 0, 0);
    }
    var_s1 = &D_807467EC;
    var_s2 = 0;
    if (sp38 & 2) {
        do {
            temp_s0 = var_s2 & 0xFF;
            func_8060C648(0x15, 0, temp_s0 & 0xFF, 0, *var_s1);
            func_8060C648(0x12, 0, temp_s0 & 0xFF, 0, 0x20);
            func_8060C648(0x13, 0, temp_s0 & 0xFF, 0, 0x20);
            func_8060C648(0x14, 0, temp_s0 & 0xFF, 0, 0x20);
            var_s2 += 1;
            var_s1 += 1;
        } while (var_s2 != 5);
    }
    var_s2_2 = 0;
    if (sp38 & 4) {
        var_s3 = D_80744548;
        var_s1_2 = (const P104L2_ConfigEntry *) D_80757044;
        do {
            temp_s0_2 = var_s2_2 & 0xFF;
            func_8060C648(0x19, 0, temp_s0_2 & 0xFF, 0, (s32) var_s1_2->unk0);
            func_8060C648(0x16, 0, temp_s0_2 & 0xFF, 0, (s32) var_s1_2->unk2);
            func_8060C648(0x17, 0, temp_s0_2 & 0xFF, 0, (s32) var_s1_2->unk3);
            func_8060C648(0x18, 0, temp_s0_2 & 0xFF, 0, (s32) var_s1_2->unk4);
            *var_s3 = *var_s1_2;
            var_s2_2 += 1;
            var_s1_2++;
            var_s3++;
        } while (var_s2_2 != 5);
    }
    var_s1_3 = (const P104L2_ConfigEntry *) D_80757064;
    var_s2_3 = 0;
    if (sp38 & 8) {
        var_s3_2 = D_80744568;
        do {
            temp_s0_3 = var_s2_3 & 0xFF;
            func_8060C648(0x1D, 0, temp_s0_3 & 0xFF, 0, (s32) var_s1_3->unk0);
            func_8060C648(0x1A, 0, temp_s0_3 & 0xFF, 0, (s32) var_s1_3->unk2);
            func_8060C648(0x1B, 0, temp_s0_3 & 0xFF, 0, (s32) var_s1_3->unk3);
            func_8060C648(0x1C, 0, temp_s0_3 & 0xFF, 0, (s32) var_s1_3->unk4);
            *var_s3_2 = *var_s1_3;
            var_s2_3 += 1;
            var_s1_3++;
            var_s3_2++;
        } while (var_s2_3 != 5);
    }
    if (sp38 & 0x10) {
        func_8060C648(0x1E, 0, 0, 0, 0);
    }
    if (sp38 & 0x20) {
        func_8060C648(0x1F, 0, 0, 0, 0);
    }
}

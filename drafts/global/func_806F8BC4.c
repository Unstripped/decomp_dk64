// func_806F8BC4 (src/global/FCCD0.c): stage 6 candidate: compiled slot update closely aligns
typedef struct {
    void *unk0;
    u8 pad4[0x1C];
    s32 unk20;
    s32 unk24;
    void *unk28;
    u8 unk2C;
} Slot;

extern void *D_80754280;
extern u8 D_807FC928;
extern s32 D_8076A0A8;

void func_806F8BC4(s32 arg0, u8 arg1, s32 arg2) {
    Slot *temp_v0;

    if ((D_807FC928 < 2) && (func_807142D8() == 0)) {
        if (arg0 == 8) {
            func_806F8BC4(9, arg1, arg2 + 0xA);
            if (D_8076A0A8 == 0xF) {
                return;
            }
        }
        ((Slot *)D_80754280)[arg0].unk24 = arg1;
        temp_v0 = &((Slot *)D_80754280)[arg0];
        if (temp_v0->unk20 == 0) {
            temp_v0->pad4[3] = arg2;
        } else {
            temp_v0->pad4[3] = 0;
        }
        ((Slot *)D_80754280)[arg0].unk20 = 1;
        temp_v0 = &((Slot *)D_80754280)[arg0];
        if (temp_v0->pad4[2] == 0) {
            temp_v0->pad4[2] = arg1 != 0;
        }
    }
}

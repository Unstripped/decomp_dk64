// actorMapModelsSetup (src/global/8D3E0.c): Stage 5: 99% matched, 1-insn delay slot scheduling diff (sll vs move s1, zero)
extern s16 D_8076A0AA;
extern u8 D_8076A0AB;
extern s32 D_807F6010;
extern s32 D_807F6C28;

typedef struct {
    u8 pad0[0x18];
    s32 unk18;
    void *unk1C;
    void *unk20;
    u8 pad24[0xC0 - 0x24];
} ModelAssetEntry160;
extern ModelAssetEntry160 D_8076A160[];

s32 func_80600080(s32);
u16 modelTypeCountBeforeMap(u8);
void modelAssetGetSubtables(s32, s32 *, s32 **);
void modelSlotsLoadMap(s32, s32, u8, u16, s32);
void csTimerQueueFire(s16);
void actorListSpawnFromRecords(s32 *);
void modelSlotsApplyRecords(void *, void *);
void lightSetColor(f32, f32, f32, s16);
s32 func_805FF030(u8, s32);
void func_80688A6C(void);
s32 func_806C7B34(void);

void actorMapModelsSetup(s32 arg0, u8 arg1, u8 arg2) {
    s32 sp5C;
    s32 *sp58;
    s32 sp54;
    s32 pad;
    u16 sp4E;
    s32 flag;

    flag = 0;
    func_80688A6C();
    sp54 = func_80600080(D_8076A0A8);
    if (sp54 == -1) {
        switch (arg1) {
        case 0:
            D_807F6010 = arg0;
            sp4E = modelTypeCountBeforeMap(D_8076A0AB);
            flag = 1;
            break;
        case 1:
            arg0 = D_807F6010;
            break;
        }
    } else {
        D_807F6010 = arg0;
        arg0 = D_8076A160[sp54].unk18;
    }
    modelAssetGetSubtables(arg0, &sp5C, &sp58);
    if (arg2 != 0) {
        arg0 = 0;
    } else {
        arg0 = func_806C7B34();
    }
    modelSlotsLoadMap(sp5C, arg0, (u8)flag, sp4E, func_805FF030(D_8076A0AB, 1));
    csTimerQueueFire(D_8076A0AA);
    actorListSpawnFromRecords(sp58);
    if (sp54 != -1) {
        if (D_8076A160[sp54].unk20 != NULL) {
            modelSlotsApplyRecords(D_8076A160[sp54].unk20, D_8076A160[sp54].unk1C);
        }
        if (D_807F6C28 > 0) {
            arg0 = (s32)&D_8076A160[sp54];
            flag = 0;
            do {
                lightSetColor((f32)((f64)(u32)((u8 *)arg0)[0x24] / 255.0),
                              (f32)((f64)(u32)((u8 *)arg0)[0x25] / 255.0),
                              (f32)((f64)(u32)((u8 *)arg0)[0x26] / 255.0),
                              flag);
                flag++;
                arg0 += 3;
            } while (flag < D_807F6C28);
        }
    }
}

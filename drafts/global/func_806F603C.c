// func_806F603C (src/global/F9450.c): Stage 4: queue-slot layout and control flow match; initial decrement pointer allocation and reload remain unresolved.
typedef union {
    s32 unk4;
    struct {
        s16 unk4High;
        s16 unk6;
    } halves;
} F9N2QueueWord;

typedef struct {
    s32 unk0;
    F9N2QueueWord unk4Word;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    s32 unk10;
} F9N2QueueSlot;

extern void actorSpawnNodeEntryScaled(s16, f32, f32, f32, s32, s32, s32, s32);
extern s16 modelSlotAppend(s32, f32, f32, f32, f32, s32);
extern s16 func_80686E40(f32, f32, f32, s32);
extern void func_806F50C8(s16, s16, s16, s32, s32, s32);
extern s32 func_8071432C(void);
extern u8 *D_80754240;
extern s32 D_807FBB60;

void func_806F603C(void) {
    F9N2QueueSlot *temp_s0;
    F9N2QueueSlot *var_s0;
    s32 temp_v0;
    s32 var_s1;
    s32 var_v0;

    if (func_8071432C() != 0) {
        var_s1 = 0;
        if (!(D_807FBB60 & 2)) {
            do {
                temp_s0 = (F9N2QueueSlot *) (D_80754240 + var_s1);
                temp_v0 = temp_s0->unk10;
                if (temp_v0 != 0) {
                    temp_s0->unk10 = temp_v0 - 1;
                    var_s0 = (F9N2QueueSlot *) (D_80754240 + var_s1);
                    var_v0 = var_s0->unk10;
                    if (var_v0 == 5) {
                        func_80686E40((f32) var_s0->unk8, (f32) var_s0->unkA, (f32) var_s0->unkC, 7);
                        var_s0 = (F9N2QueueSlot *) (D_80754240 + var_s1);
                        var_v0 = var_s0->unk10;
                    }
                    if (var_v0 == 0) {
                        if (var_s0->unk0 != 0) {
                            actorSpawnNodeEntryScaled(var_s0->unk4Word.halves.unk6, (f32) var_s0->unk8, (f32) var_s0->unkA, (f32) var_s0->unkC, 0, 0x19, -1, 0);
                        } else {
                            func_806F50C8(modelSlotAppend(var_s0->unk4Word.unk4, (f32) var_s0->unk8, (f32) var_s0->unkA, (f32) var_s0->unkC, 0.0f, 0), var_s0->unk4Word.halves.unk6, 0, 1, 0, 0);
                        }
                    }
                }
                var_s1 += 0x14;
            } while (var_s1 != 0x4B0);
        }
    }
}

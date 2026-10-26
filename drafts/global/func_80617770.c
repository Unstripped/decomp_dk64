// func_80617770 (src/global/19A00.c): stage 4: typed C establishes the full control flow and calls. Remaining diff: candidate has a 0x60-byte frame and saves s0/s1 versus target 0x40 and s0 only; the target emits dynamic FPU 0xFF * 0.5 conversion while this candidate folds the constant; register allocation and stack spills differ.
typedef struct P19c3SoundActor {
    u8 pad0[0x58];
    s32 unk58;
    u8 pad5C[0x20];
    f32 unk7C;
    f32 unk80;
    s32 unk84;
} P19c3SoundActor;

typedef struct P19c3AudioState {
    u8 pad0[0xC4];
    s32 unkC4;
    u8 padC8[0xDC];
    u8 unk1A4;
} P19c3AudioState;

extern s16 *D_807FBB5C;
extern u8 *D_807FC924;
void n_alSndpStop(s32, s16);
void func_80609B80(f32, f32, s16, s32, s16, s32, s32, s32, s32, f32);

void func_80617770(Actor *arg0, s16 arg1, u8 arg2) {
    u8 sp3C;
    f64 temp_ft3;
    s16 var_a1;
    s32 temp_a0;
    s32 temp_ft4;
    s32 temp_v0_2;
    s32 var_v0;
    s32 var_v1;
    u8 temp_v0;

    var_a1 = D_807FBB5C[(((arg1 * 7) + ((P19c3SoundActor *)arg0)->unk58 - 2) & 0xFFFF)];
    var_v1 = 0xFF;
    if (var_a1 == 0) {
        temp_a0 = ((P19c3AudioState *)D_807FD580)->unkC4;
        if (temp_a0 != 0) {
            sp3C = 0xFF;
            arg1 = var_a1;
            n_alSndpStop(temp_a0, var_a1);
            var_v1 = 0xFF;
            var_a1 = arg1;
        }
    }
    temp_v0 = D_807FC924[(((P19c3AudioState *)D_807FD580)->unk1A4 * 0x2F0) + 0x2C0];
    if (temp_v0 == 2) {
        var_v0 = 0xA;
    } else if (temp_v0 == 0) {
        var_v0 = 0x50;
        temp_ft3 = (f64)0xFF * 0.5;
        temp_ft4 = (s32)temp_ft3;
        var_v1 = temp_ft4 & 0xFF;
    } else {
        temp_v0_2 = ((P19c3SoundActor *)arg0)->unk58;
        if ((temp_v0_2 == 2) || (temp_v0_2 == 4)) {
            var_v0 = 0x32;
        } else {
            var_v0 = 0x3C;
        }
    }
    func_80609B80(((P19c3SoundActor *)arg0)->unk7C, ((P19c3SoundActor *)arg0)->unk80, var_a1, ((P19c3SoundActor *)arg0)->unk84, var_a1, var_v1, 0x7F, (s32)arg2, var_v0, 0.3f);
}

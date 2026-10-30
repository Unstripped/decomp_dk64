// func_80617770 (src/global/19A00.c): stage 4: 0x40/0x48 frame, s0 saved, dynamic 0xFF * 0.5 FP conversion reproduced; remaining diff is uninitialized pitch register allocation in branch
typedef struct RvH_SoundState {
    u8 pad0[0xC4];
    s32 unkC4;
    u8 padC8[0xDC];
    u8 unk1A4;
} RvH_SoundState;

typedef struct RvH_PlayerState7770 {
    u8 pad0[0x2C0];
    u8 unk2C0;
} RvH_PlayerState7770;

extern s16 *D_807FBB5C;
extern u8 *D_807FC924;
void n_alSndpStop(s32);
void sfxPlayAtPositionForPlayer(f32, f32, f32, s16, s32, s32, s32, s32, f32);

void func_80617770(Actor *arg0, s16 arg1, u8 arg2) {
    u8 var_v1;
    s32 pitch;
    s32 temp_v0;

    arg1 = D_807FBB5C[(arg1 * 7 + arg0->unk58 - 2) & 0xFFFF];
    var_v1 = 0xFF;
    if (arg1 == 0) {
        if (((RvH_SoundState *)D_807FD580)->unkC4 != 0) {
            n_alSndpStop(((RvH_SoundState *)D_807FD580)->unkC4);
        }
    }
    temp_v0 = ((RvH_PlayerState7770 *)(D_807FC924 + ((RvH_SoundState *)D_807FD580)->unk1A4 * 0x2F0))->unk2C0;
    if (temp_v0 == 2) {
        pitch = 0x7F;
        temp_v0 = 10;
    } else if (temp_v0 == 0) {
        temp_v0 = 80;
        var_v1 = (u8)((f64)var_v1 * 0.5);
    } else {
        if (arg0->unk58 == 2 || arg0->unk58 == 4) {
            temp_v0 = 50;
        } else {
            temp_v0 = 60;
        }
    }
    sfxPlayAtPositionForPlayer(arg0->unk7C, arg0->unk80, arg0->unk84, arg1, var_v1, pitch, arg2, temp_v0, 0.3f);
}

// scriptOpPlaySoundAndShake (src/global/19A00.c): stage 4: 0x50 frame, s0/ra saved, slots 0x4E,0x4D,0x4A,0x49,0x48 match, FP conversion 100% matched, diff 16 lines (as1 branch delay scheduling)
struct PlayerSoundStruct;
extern struct PlayerSoundStruct *gPlayerSlots;

typedef struct PlayerSoundView {
    u8 pad0[0x2C0];
    u8 unk2C0;
    u8 pad2C1[0x2F0 - 0x2C1];
} PlayerSoundView;

typedef struct GlobalSoundState {
    u8 pad0[0x104];
    s32 unk104;
    u8 pad108[0x9C];
    u8 unk1A4;
} GlobalSoundState;

typedef struct ActorSoundPosView {
    u8 pad0[0x78];
    u8 unk78;
    u8 pad79[3];
    s32 unk7C;
    f32 unk80;
    f32 unk84;
} ActorSoundPosView;

void sfxPlayAtPositionPooled(f32, f32, f32, s16, s32, s32, s32, s32, f32, s32);
void camStartShakeFromPoint(s32, u8, u16, s32, f32, f32, f32, f32);
s16 func_8060A7C0(s16, Actor *, u8);

s32 scriptOpPlaySoundAndShake(Actor *arg0) {
    s16 sp4E;
    u8 sp4D;
    s16 sp4A;
    u8 sp49;
    u8 var_v1;
    u8 pad;

    D_807F5AF0++;
    scriptReadU16((u8 *)&sp4E);
    scriptReadU8(&sp4D);
    scriptReadU16((u8 *)&sp4A);
    scriptReadU8(&sp49);
    if (((PlayerSoundView *)gPlayerSlots)[((GlobalSoundState *)gActivePlayerState)->unk1A4].unk2C0 == 2) {
        var_v1 = 0xA;
        if (sp4E == 1) {
            sp4D = (u32)((f64)(u32)sp4D * 0.5);
        }
        camStartShakeFromPoint(((GlobalSoundState *)gActivePlayerState)->unk104, 0xA, 8, ((ActorSoundPosView *)arg0)->unk7C, ((ActorSoundPosView *)arg0)->unk80, ((ActorSoundPosView *)arg0)->unk84, 100.0f, 800.0f);
    } else if (((PlayerSoundView *)gPlayerSlots)[((GlobalSoundState *)gActivePlayerState)->unk1A4].unk2C0 == 0) {
        var_v1 = 0xFF;
        sp4D = (u32)((f64)(u32)sp4D * 0.5);
    } else {
        switch (arg0->unk58) {
        case 6:
        case 7:
            var_v1 = 0x46;
            break;
        case 8:
            var_v1 = 0x5A;
            break;
        case 2:
        case 4:
            var_v1 = 0x32;
            break;
        default:
            var_v1 = 0x50;
            break;
        }
    }
    sp4E = func_8060A7C0(sp4E, arg0, ((ActorSoundPosView *)arg0)->unk78);
    if ((sp4E == 2) || (sp4E == 8)) {
        sp49 = 0xA;
    }
    sfxPlayAtPositionPooled(arg0->unk7C, arg0->unk80, arg0->unk84, sp4E, (s32)sp4D, (s32)sp4A, (s32)sp49, (s32)var_v1, 0.3f, 0);
    return 1;
}

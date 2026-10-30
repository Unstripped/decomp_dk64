// func_80616E08 (src/global/19A00.c): stage 4: 0x50 frame matches, s0/ra saved, stack slots (0x4E, 0x4D, 0x4A, 0x49, 0x48) match; remaining diff is FP conversion schedule
struct RvG_PlayerStruct;
extern struct RvG_PlayerStruct *D_807FC924;

typedef struct RvH_PlayerView6E08 {
    u8 pad0[0x2C0];
    u8 unk2C0;
    u8 pad2C1[0x2F0 - 0x2C1];
} RvH_PlayerView6E08;

typedef struct RvH_State6E08 {
    u8 pad0[0x104];
    s32 unk104;
    u8 pad108[0x9C];
    u8 unk1A4;
} RvH_State6E08;

typedef struct RvH_ActorSoundView6E08 {
    u8 pad0[0x78];
    u8 unk78;
    u8 pad79[3];
    s32 unk7C;
    f32 unk80;
    f32 unk84;
} RvH_ActorSoundView6E08;

void sfxPlayAtPositionPooled(f32, f32, f32, s16, s32, s32, s32, s32, f32, s32);
void camStartShakeFromPoint(s32, u8, u16, s32, f32, f32, f32, f32);
s16 func_8060A7C0(s16, Actor *, u8);

s32 func_80616E08(Actor *arg0) {
    s16 sp4E;
    u8 sp4D;
    s16 sp4A;
    u8 sp49;
    u8 var_v1;
    u8 sp48;

    D_807F5AF0++;
    scriptReadU16((u8 *)&sp4E);
    scriptReadU8(&sp4D);
    scriptReadU16((u8 *)&sp4A);
    scriptReadU8(&sp49);
    if (((RvH_PlayerView6E08 *)D_807FC924)[((RvH_State6E08 *)D_807FD580)->unk1A4].unk2C0 == 2) {
        if (sp4E == 1) {
            sp4D = (u32)((f64)(u32)sp4D * 0.5);
        }
        sp48 = 0xA;
        camStartShakeFromPoint(((RvH_State6E08 *)D_807FD580)->unk104, 0xA, 8, ((RvH_ActorSoundView6E08 *)arg0)->unk7C, ((RvH_ActorSoundView6E08 *)arg0)->unk80, ((RvH_ActorSoundView6E08 *)arg0)->unk84, 100.0f, 800.0f);
        var_v1 = 0xA;
    } else if (((RvH_PlayerView6E08 *)D_807FC924)[((RvH_State6E08 *)D_807FD580)->unk1A4].unk2C0 == 0) {
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
    sp48 = var_v1;
    sp4E = func_8060A7C0(sp4E, arg0, ((RvH_ActorSoundView6E08 *)arg0)->unk78);
    if ((sp4E == 2) || (sp4E == 8)) {
        sp49 = 0xA;
    }
    sfxPlayAtPositionPooled(arg0->unk7C, arg0->unk80, arg0->unk84, sp4E, (s32)sp4D, (s32)sp4A, (s32)sp49, (s32)var_v1, 0.3f, 0);
    return 1;
}

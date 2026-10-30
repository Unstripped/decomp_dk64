// func_80616E08 (src/global/19A00.c): stage 4: cleaned types, removed f64 locals, matching control flow and jump table; remaining diff is branch/schedule in FP conversions
typedef struct RvH_PlayerState { u8 pad0[0x2C0]; u8 unk2C0; } RvH_PlayerState;
typedef struct RvH_State6E08 {
    u8 pad0[0x104];
    s32 unk104;
    u8 pad108[0x9C];
    u8 unk1A4;
} RvH_State6E08;

typedef struct RvH_ActorSoundView { u8 pad0[0x78]; u8 unk78; } RvH_ActorSoundView;
extern u8 *D_807FC924;
void sfxPlayAtPositionPooled(f32, f32, f32, s16, s32, s32, s32, s32, f32, s32);
void camStartShakeFromPoint(s32, u8, u16, s32, f32, f32, f32, f32);
s16 func_8060A7C0(s16, Actor *, u8);

s32 func_80616E08(Actor *arg0) {
    s16 sp4E;
    u8 sp4D;
    s16 sp4A;
    u8 sp49;
    u8 sp48;
    s16 temp_v0;
    s32 temp_t8;
    u8 temp_v1;
    u8 var_v1;

    D_807F5AF0++;
    scriptReadU16((u8 *)&sp4E);
    scriptReadU8(&sp4D);
    scriptReadU16((u8 *)&sp4A);
    scriptReadU8(&sp49);
    temp_v1 = ((RvH_PlayerState *)(D_807FC924 + ((RvH_State6E08 *)D_807FD580)->unk1A4 * 0x2F0))->unk2C0;
    if (temp_v1 == 2) {
        if (sp4E == 1) {
            sp4D = (u32)((f64)sp4D * 0.5);
        }
        sp48 = 0xA;
        camStartShakeFromPoint(((RvH_State6E08 *)D_807FD580)->unk104, 0xA, 8, arg0->unk7C, arg0->unk80, arg0->unk84, 100.0f, 800.0f);
        var_v1 = 0xA;
    } else if (temp_v1 == 0) {
        var_v1 = 0xFF;
        sp4D = (u32)((f64)sp4D * 0.5);
    } else {
        temp_t8 = arg0->unk58;
        switch (temp_t8) {
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
    temp_v0 = func_8060A7C0(sp4E, arg0, ((RvH_ActorSoundView *)arg0)->unk78);
    sp4E = temp_v0;
    if ((temp_v0 == 2) || (temp_v0 == 8)) {
        sp49 = 0xA;
    }
    sfxPlayAtPositionPooled(arg0->unk7C, arg0->unk80, arg0->unk84, sp4E, (s32)sp4D, (s32)sp4A, (s32)sp49, (s32)var_v1, 0.3f, 0);
    return 1;
}

// func_806836D0 (src/global/80150.c): Stage 4: frame 0x50 matches; var_s0 reused; diff is s2 saved reg vs s1/s0 reuse
typedef struct KaN4_Pad {
    u8 pad0[0x2C];
    u16 unk2C;
    s8 unk2E;
    s8 unk2F;
    s8 unk30;
} KaN4_Pad;
extern KaN4_Pad D_807FD610;

typedef struct KaN4_PlayerData {
    u8 pad0[0x2E2];
    u16 unk2E2;
} KaN4_PlayerData;

typedef struct KaN4_TagBarrelData {
    Actor *unk0;
    u16 unk4;
    s8 unk6;
    s8 unk7;
    Actor *unk8[5];
    Actor *unk1C;
    s8 unk20;
    u8 pad21;
    s16 unk22;
    f32 unk24;
    s16 unk28;
    u8 pad2A[2];
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    s16 unk38;
    u8 pad3A[2];
    u32 unk3C;
} KaN4_TagBarrelData;

typedef struct KaN4_KongSub {
    u8 pad0[0x8C];
    u8 unk8C;
    u8 pad8D[0x104 - 0x8D];
    Actor *unk104;
    u8 pad108[0x1F0 - 0x108];
    u32 unk1F0;
} KaN4_KongSub;

typedef struct KaN4_ActorKong {
    u8 pad0[0x12C];
    s32 unk12C;
} KaN4_ActorKong;

extern s32 D_8074E848[];
extern s32 D_807FBB60;

s32 func_805FCA64(void);
s32 screenWipeGetState(void);
void screenWipeStart(s32);
void healthRefill(s32);
void sfxStopChannel(s32, s32);
void camRestoreYaw(Actor *);
void camResetPlayer(Actor *, s32);
void func_806C8E58(s16);
void func_80609140(s32, s32, f32, f32, s32, s32);
void lightSetColor(f32, f32, f32, s32);
void sfxSetChannelParam(s32, s32, s32);
struct KaB3_TagBarrelData;

void func_806836D0(struct KaB3_TagBarrelData *arg0_in) {
    KaN4_TagBarrelData *arg0 = (KaN4_TagBarrelData *)arg0_in;
    s32 pad[4];
    volatile u16 sp4A;
    Actor *sp34;
    KaN4_KongSub *sp30;
    s32 sp28;
    s32 var_s0;
    s32 temp_t3;

    var_s0 = arg0->unk4;
    sp4A = var_s0;
    if (var_s0 != 0) {
        arg0->unk4 = var_s0 - 1;
        func_80682AB4(arg0);
        var_s0 = arg0->unk4;
    }
    arg0->unk3C++;
    if (var_s0 == 0 && func_805FCA64() != 0) {
        temp_t3 = arg0->unk3C >= 9001;
        var_s0 = ((Actor *)arg0->unk8[arg0->unk6])->unk58 == 0x13C;
        if (((D_807FD610.unk30 >= 0x29) && !temp_t3) || !var_s0) {
            arg0->unk4 = 20;
            if (((Actor *)arg0->unk8[arg0->unk6])->unk58 == 0x13C) {
                func_80682DF4(arg0->unk8[arg0->unk6], (u16 *)((Actor *)arg0->unk8[arg0->unk6])->unk174, 0x8C);
            }
            arg0->unk7 = arg0->unk6;
            if (var_s0) {
                if (D_807FD610.unk2E < 0) {
                    arg0->unk20 = -1;
                } else {
                    arg0->unk20 = 1;
                }
            }
            arg0->unk6 += arg0->unk20;
            if (arg0->unk6 < 0) {
                arg0->unk6 = 4;
            } else if (arg0->unk6 >= 5) {
                arg0->unk6 = 0;
            }
            if (((Actor *)arg0->unk8[arg0->unk6])->unk58 == 0x13C) {
                func_80682DF4(arg0->unk8[arg0->unk6], (u16 *)((Actor *)arg0->unk8[arg0->unk6])->unk174, 0x8B);
            }
        } else {
            if (!temp_t3 && sp4A != 0) {
                sfxSetChannelParam(0x65, 0x7E - D_8074E848[arg0->unk6], 3);
                sfxSetChannelParam(0x65, D_8074E848[arg0->unk6], 2);
                return;
            }
            if (((temp_t3 && var_s0) || (D_807FD610.unk2C & 0xE000)) && screenWipeGetState() == 0) {
                if (var_s0) {
                    sp34 = arg0->unk0;
                    sp30 = sp34->unk174;
                    sp28 = ((KaN4_ActorKong *)sp34)->unk12C;
                    if (sp28 == -1) {
                        sp28 = 0;
                    }
                    lightSetColor(arg0->unk2C, arg0->unk30, arg0->unk34, sp28);
                    D_807FBB60 |= 0x30030;
                    sfxStopChannel(0x48, 0);
                    sfxStopChannel(0x6B, 0);
                    sfxStopChannel(0x49, 0);
                    sfxStopChannel(0x47, 0);
                    sfxStopChannel(0x65, 0);
                    actorDespawn(arg0->unk1C);
                    arg0->unk1C = NULL;
                    for (sp28 = 0; sp28 < 5; sp28++) {
                        actorDespawn(arg0->unk8[sp28]);
                        arg0->unk8[sp28] = NULL;
                    }
                    D_807FBB40->unk154 = 2;
                    D_807FBB40->unk155[0] = 0;
                    arg0->unk4 = 30;
                    sp30->unk1F0 &= ~0x20000000;
                    var_s0 = ((R2FKongAction *)D_8074E814)[arg0->unk6].unk2;
                    func_806C8E58(var_s0);
                    func_806F09F0(sp34, var_s0);
                    *(u8 *)((u8 *)sp30 + 0x8C) = 0;
                    sp34->unkE6 = arg0->unk38;
                    camRestoreYaw(sp30->unk104);
                    camResetPlayer(sp34, 0);
                    screenWipeStart(3);
                    healthRefill(0);
                    ((KaN4_PlayerData *)D_807FC924)->unk2E2 |= 0x11;
                    return;
                }
                func_80609140(0x98, 0x7FFF, 63.0f, 1.0f, 0, 0);
            }
        }
    }
}

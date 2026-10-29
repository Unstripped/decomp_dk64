// func_806836D0 (src/global/80150.c): stage 4: 0x50 frame matches, s0/s1/ra saved set matches, diff in regalloc reuse of s0 across live ranges
typedef struct KaB3_Pad {
    u8 pad0[0x2C];
    u16 unk2C;
    s8 unk2E;
    s8 unk2F;
    s8 unk30;
} KaB3_Pad;
extern KaB3_Pad D_807FD610;

typedef struct KaB3_PlayerData {
    u8 pad0[0x2E2];
    u16 unk2E2;
} KaB3_PlayerData;

s32 func_805FCA64(void);
s32 screenWipeGetState(void);
void screenWipeStart(s32);
void healthRefill(s32);
void sfxStopChannel(s32, s32);
void camRestoreYaw(Actor *);
void camResetPlayer(Actor *, s32);
void func_806C8E58(s16);
void func_80609140(s32, s32, f32, f32, s32, s32);

void func_806836D0(KaB3_TagBarrelData *arg0) {
    s32 pad4C;
    volatile u16 sp4A;
    u8 pad38[0x12];
    Actor *sp34;
    KaB3_KongSub *sp30;
    s32 sp28;
    Actor *curKong;
    s32 kongIndex;
    s32 isUnlocked;
    s32 timerExpired;

    sp4A = arg0->unk4;
    if (sp4A != 0) {
        arg0->unk4--;
        func_80682AB4(arg0);
    }
    arg0->unk3C++;
    if (arg0->unk4 == 0 && func_805FCA64() != 0) {
        kongIndex = arg0->unk6;
        curKong = arg0->unk8[kongIndex];
        timerExpired = arg0->unk3C >= 9001;
        isUnlocked = curKong->unk58 == 0x13C;

        if ((D_807FD610.unk30 >= 0x29 && !timerExpired) || !isUnlocked) {
            arg0->unk4 = 20;
            if (curKong->unk58 == 0x13C) {
                func_80682DF4(curKong, (u16 *)curKong->unk174, 0x8C);
            }
            arg0->unk7 = arg0->unk6;
            if (isUnlocked) {
                arg0->unk20 = (D_807FD610.unk2E < 0) ? -1 : 1;
            }
            arg0->unk6 += arg0->unk20;
            if (arg0->unk6 < 0) {
                arg0->unk6 = 4;
            } else if (arg0->unk6 >= 5) {
                arg0->unk6 = 0;
            }
            curKong = arg0->unk8[arg0->unk6];
            if (curKong->unk58 == 0x13C) {
                func_80682DF4(curKong, (u16 *)curKong->unk174, 0x8B);
            }
        } else {
            if (!timerExpired && sp4A != 0) {
                sfxSetChannelParam(0x65, 0x7E - D_8074E848[kongIndex], 3);
                sfxSetChannelParam(0x65, D_8074E848[arg0->unk6], 2);
                return;
            }
            if (((timerExpired && isUnlocked) || (D_807FD610.unk2C & 0xE000)) && screenWipeGetState() == 0) {
                if (isUnlocked) {
                    sp34 = arg0->unk0;
                    sp30 = sp34->unk174;
                    sp28 = ((KaB3_ActorKong *)sp34)->unk12C;
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
                    func_806C8E58(((R2FKongAction *)D_8074E814)[arg0->unk6].unk2);
                    func_806F09F0(sp34, ((R2FKongAction *)D_8074E814)[arg0->unk6].unk2);
                    *(u8 *)((u8 *)sp30 + 0x8C) = 0;
                    sp34->unkE6 = arg0->unk38;
                    camRestoreYaw(sp30->unk104);
                    camResetPlayer(sp34, 0);
                    screenWipeStart(3);
                    healthRefill(0);
                    ((KaB3_PlayerData *)D_807FC924)->unk2E2 |= 0x11;
                    return;
                }
                func_80609140(0x98, 0x7FFF, 63.0f, 1.0f, 0, 0);
            }
        }
    }
}

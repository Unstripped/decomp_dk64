// func_806833DC (src/global/80150.c): Stage 5: 0x40 frame matches, s0/ra callee-saved match, diff only spill slot offset of sp28 (0x28 vs 0x2c); resolved sp34/sp30 slots via arg0 macro and direct unk0 call args
typedef struct KaN3_TagBarrelData {
    /* 0x00 */ Actor *unk0;
    /* 0x04 */ u16 unk4;
    /* 0x06 */ s8 unk6;
    /* 0x07 */ s8 unk7;
    /* 0x08 */ Actor *unk8[5];
    /* 0x1C */ Actor *unk1C;
    /* 0x20 */ s8 unk20;
    /* 0x21 */ u8 pad21;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ u8 pad2A[2];
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ s16 unk38;
    /* 0x3A */ u8 pad3A[2];
    /* 0x3C */ u32 unk3C;
} KaN3_TagBarrelData;

typedef struct KaN3_KongSub {
    u8 pad0[0x104];
    Actor *unk104;
    u8 pad108[0x1F0 - 0x108];
    s32 unk1F0;
} KaN3_KongSub;

typedef struct KaN3_ActorKong {
    u8 pad0[0x5A];
    s16 unk5A;
    u8 pad5C[0x12C - 0x5C];
    s16 unk12C;
} KaN3_ActorKong;

struct KaB3_TagBarrelData;
extern s32 D_8074E848[];
extern s32 D_807FBB60;

s32 camIsCutsceneActive(void);
void func_806C93E4(Actor *, void *);
void func_806C9304(Actor *, void *);
void lightGetColor(f32 *, f32 *, f32 *, s16);
void lightSetColor(f32, f32, f32, s32);
void sfxAllocateChannel(s32, f32);
void sfxSetChannelParam(s32, s32, s32);
void camSaveYaw(Actor *);
void func_8060DEC8(void);
void func_8061B650(Actor *);
void slotQueueClearAllFlags(void);

void func_806833DC(struct KaB3_TagBarrelData *arg0_in) {
#define arg0 ((KaN3_TagBarrelData *)arg0_in)
    s32 pad3C;
    s32 pad38;
    Actor *sp34;
    KaN3_KongSub *sp30;
    s32 sp28;

    switch (D_807FBB40->unk155[0]) {
    case 0xB:
        if (camIsCutsceneActive() == 0) {
            D_807FBB40->unk144 = 2;
            D_807FBB40->unk155[0] = 0;
        }
        break;
    case 0:
    case 0xA:
        if (D_807FBB70.unk200 == 4) {
            arg0->unk0 = (Actor *)D_807FBB70.unk1FC;
            arg0->unk0->unk144 = 1;
            ((KaN3_KongSub *)arg0->unk0->unk174)->unk1F0 |= 0x20000000;
            D_807FBB40->unk155[0] = 1;
            arg0->unk4 = 2;
            arg0->unk3C = 0;
        }
        break;
    case 1:
        if (arg0->unk4 != 0) {
            arg0->unk4--;
        } else {
            sp34 = arg0->unk0;
            sp28 = ((KaN3_ActorKong *)sp34)->unk12C;
            sp30 = sp34->unk174;
            if (sp28 == -1) {
                sp28 = 0;
            }
            func_806C93E4(arg0->unk0, sp30);
            func_806C9304(arg0->unk0, sp30);
            lightGetColor(&arg0->unk2C, &arg0->unk30, &arg0->unk34, (s16)sp28);
            lightSetColor(1.0f, 1.0f, 1.0f, (s16)sp28);
            D_807FBB40->unkE6 = arg0->unk22;
            D_807FBB40->unk144 = 1;
            sp28 = ((KaN3_ActorKong *)sp34)->unk5A;
            D_807FBB60 &= 0xFFFCFFCF;
            arg0->unk6 = 0;
            if (sp28 != ((R2FKongAction *)D_8074E814)[arg0->unk6].unk2) {
                do {
                    arg0->unk6++;
                } while (sp28 != ((R2FKongAction *)D_8074E814)[arg0->unk6].unk2);
            }
            arg0->unk7 = arg0->unk6;
            if (D_8076A0A8 != 0x11) {
                sfxAllocateChannel(0x65, 1.0f);
                sfxSetChannelParam(0x65, 0x7E - D_8074E848[arg0->unk6], 1);
            }
            flagSet(func_805FF018(D_807FBB40->unk58, arg0->unk6), 1, 0);
            tagBarrelSpawnKongs((R2FStruct_80682E38 *)arg0);
            camSaveYaw(sp30->unk104);
            arg0->unk38 = sp34->unkE6;
            sp34->unkE6 = D_807FBB40->unkE6;
            func_8060DEC8();
            camStartPath(D_807FBB40, 0xE, 0xC);
            func_8061B650(sp30->unk104);
            slotQueueClearAllFlags();
            D_807FBB40->unk154 = 1;
            D_807FBB40->unk155[0] = 0;
        }
        break;
    }
#undef arg0
}

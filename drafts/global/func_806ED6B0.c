// func_806ED6B0 (src/global/EFDC0.c): Stage 6 candidate has matching instructions; only switch-table relocation labels differ from target.
typedef struct EfL1PlayerState {
    u8 pad0[0x10];
    s16 unk10;
    s16 unk12;
    s16 unk14;
    u8 pad16[0x22];
    f32 unk38;
    u8 pad3C[0x14];
    s16 unk50;
    u8 pad52[0x1A];
    f32 unk6C;
    s16 unk70;
    u8 pad72[2];
    f32 unk74;
    u8 pad78[0x14];
    u8 unk8C;
    u8 pad8D[0x161];
    s16 unk1EE;
    s32 unk1F0;
    s32 unk1F4;
} EfL1PlayerState;

typedef struct EfL1Actor {
    u8 pad0[0x58];
    u32 unk58;
    u8 pad5C[4];
    s32 unk60;
    u8 pad64[6];
    u16 unk6A;
    u8 pad6C[0x14];
    f32 unk80;
    u8 pad84[0x28];
    f32 unkAC;
    u8 padB0[8];
    f32 unkB8;
    f32 unkBC;
    f32 unkC0;
    u8 padC4[0x22];
    s16 unkE6;
    u8 padE8[6];
    s16 unkEE;
    u8 padF0[0x38];
    s16 unk128;
    u8 pad12A[0x2A];
    u8 unk154;
    u8 unk155;
} EfL1Actor;

typedef struct EfL1CamBlock {
    u8 pad0[0x2A0];
    EfL1Actor *unk2A0;
    u8 pad2A4[0x4C];
} EfL1CamBlock;

typedef struct EfL1Global568 {
    u8 pad0[2];
    u8 unk2;
} EfL1Global568;

#define EfL1PS ((EfL1PlayerState *)D_807FD580)
#define EfL1Cam ((EfL1CamBlock *)D_807FC924)
#define EfL1G568 ((EfL1Global568 *)D_807FD568)
#define EfL1A40 ((EfL1Actor *)D_807FBB40)
#define EfL1A48 ((EfL1Actor *)D_807FBB48)

extern void *D_807FD568;
Actor *actorFindByType(s32);
void actorSpawnChildActor(Actor *);
void func_8068696C(Actor *);
void func_806C8D20(Actor *);
s32 func_806C8DE0(s32);
void func_806C8E58(s16);
void func_806CFE7C(void);
void func_806CFECC(void);
void func_806CFF1C(Actor *);
void func_806D0468(Actor *, s32);
void func_806ED508(u16);
void func_806ED5C0(Actor *);
void func_806F0D68(Actor *);

void func_806ED6B0(void) {
    u8 flag;
    s32 selector;
    s32 value;

    flag = 0;
    EfL1A48->unkB8 = EfL1PS->unk6C;
    EfL1A48->unkEE = EfL1PS->unk70;
    EfL1A48->unkE6 = EfL1PS->unk70;
    EfL1A48->unkC0 = EfL1PS->unk74;
    func_80614D00(D_807FBB48, 1.0f, 0.0f);
    if (EfL1Cam[D_807FC929].unk2A0 == NULL) {
        EfL1A48->unk154 = 0x44;
        EfL1A48->unk155 = 0;
        func_80614E78(D_807FBB48, 0x22);
        EfL1PS->unk50 = 0x14;
        func_806CFE7C();
    } else {
        switch (EfL1Cam[D_807FC929].unk2A0->unk58) {
        case 0x17:
        case 0xA7:
            EfL1A48->unk154 = 0x45;
            EfL1A48->unk155 = 0;
            func_80614E78(D_807FBB48, 0x22);
            EfL1PS->unk50 = 0x14;
            func_806CFE7C();
            break;
        case 0x11:
            EfL1A48->unk154 = 0x44;
            EfL1A48->unk155 = 0;
            func_80614E78(D_807FBB48, 0x22);
            EfL1PS->unk50 = 0x14;
            func_806CFE7C();
            break;
        case 0x1C:
        case 0x6B:
        case 0x86:
            if (actorFindByType(0x25) != NULL) {
                EfL1A48->unk154 = 0x63;
                EfL1A48->unk155 = 0;
                func_80614EBC(D_807FBB48, 0x7D);
                EfL1A48->unkB8 = 0.0f;
                EfL1PS->unk38 = 300.0f;
                flag = 1;
                func_806F8BC4(5, 1, 0);
                break;
            }
        case 0x62:
        case 0x88:
        case 0x89:
            func_806C8D20(D_807FBB48);
            func_806CFF1C(D_807FBB40);
            func_806CFE7C();
            break;
        case 0x19:
        case 0x28:
        case 0x60:
            if (EfL1Cam[D_807FC929].unk2A0->unk58 == 0x28) {
                selector = 2;
            } else {
                selector = 0;
            }
            func_806D0468(D_807FBB48, selector & 0xFF);
            if (EfL1A48->unk58 == 6) {
                EfL1A48->unk60 &= 0xFFFF7FFF;
            } else {
                EfL1A48->unk60 |= 0x8000;
            }
            func_806CFF9C(D_807FBB48);
            break;
        case 0x39:
            EfL1PS->unk1F0 |= 0x10;
            EfL1A48->unk60 &= 0xFFFF7FFF;
            EfL1A48->unk128 = 0x7F;
            func_8068696C(D_807FBB48);
            func_806CFF1C(D_807FBB40);
            func_806CFE7C();
            break;
        case 0x38:
            EfL1PS->unk1F0 |= 0x20;
            EfL1A48->unk154 = 0x41;
            EfL1A48->unk155 = 0;
            func_80614EBC(D_807FBB48, 0x156);
            EfL1A48->unkB8 = 0.0f;
            EfL1PS->unk50 = 4;
            func_806CFECC();
            break;
        case 0x31:
            EfL1A48->unk154 = 0x63;
            EfL1A48->unk155 = 0;
            func_80614EBC(D_807FBB48, 0x7D);
            EfL1A48->unkB8 = 0.0f;
            EfL1PS->unk38 = 300.0f;
            break;
        case 0x12:
        case 0x81:
            EfL1PS->unk1EE = EfL1A48->unk58;
            if (EfL1Cam[D_807FC929].unk2A0->unk58 == 0x12) {
                func_806C8E58(8);
                EfL1A48->unk154 = 0xC;
                EfL1A48->unk155 = 0;
                func_80614E78(D_807FBB48, 9);
                EfL1A48->unkB8 = 0.0f;
            } else {
                func_806C8E58(9);
                if (EfL1A48->unkAC < EfL1A48->unk80) {
                    EfL1A48->unk154 = 0x82;
                    EfL1A48->unk155 = 0;
                } else {
                    EfL1A48->unk154 = 0x7F;
                    EfL1A48->unk155 = 0;
                }
                func_80614EBC(D_807FBB48, 0x317);
                EfL1A48->unkB8 = 100.0f;
            }
            EfL1PS->unk50 = 4;
            func_806CFECC();
            func_806ED508(*(u16 *)((u8 *)EfL1Cam[D_807FC929].unk2A0 + 0x5A));
            break;
        case 0x84:
            value = func_806C8DE0(D_807FC929);
            if (value != D_8074E77C[D_807FC929]) {
                func_806C8E58((s16)(value + 2));
            }
            actorSpawnChildActor(D_807FBB48);
            break;
        }
    }
    if (((EfL1Cam[D_807FC929].unk2A0 != NULL) && (EfL1Cam[D_807FC929].unk2A0->unk58 == 0x31)) || (flag != 0)) {
        if (EfL1G568->unk2 & 1) {
            if (EfL1PS->unk8C != 0) {
                EfL1PS->unk1F4 |= 4;
            } else {
                EfL1PS->unk1F4 &= ~4;
            }
            EfL1PS->unk8C = 1;
            func_806F0D68(D_807FBB48);
        }
    } else {
        func_806F0C18(D_807FBB40);
    }
    if (EfL1Cam[D_807FC929].unk2A0 != NULL) {
        func_806ED5C0((Actor *)EfL1Cam[D_807FC929].unk2A0);
    }
    if ((EfL1A48->unk6A & 4) && (EfL1Cam[D_807FC929].unk2A0->unk58 != 0x81)) {
        EfL1PS->unk12 = D_807539EC[D_807FD584];
        EfL1PS->unk14 = EfL1A40->unkE6;
        EfL1PS->unk10 = (s16)((f64)D_807539DC[D_807FD584] * 0.5);
        EfL1A40->unk154 = 0x4F;
        EfL1A40->unk155 = 1;
        if (EfL1A40->unkC0 > 0.0f) {
            EfL1A40->unkC0 = 0.0f;
        }
        func_80614E78(D_807FBB40, 0x36);
        func_80613AF8(D_807FBB40, 0x31, 0.0f, 8.0f);
        func_80614D00(D_807FBB40, 0.5f, 0.0f);
    }
}

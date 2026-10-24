// func_8069AB74 (src/global/9DD70.c): 287/289 insns; frame 0x78 vs 0x70 (unreproduced dead local slots 0x60-0x68, 0x40-0x53) and lightAdd 3rd/4th float args passed raw in a2/a3; needs narrow-param/home-slot quirk
typedef struct {
    s16 unk0;
    u8 pad2[2];
    f32 unk4;
} M1BossTimer;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    f32 unk10;
    f32 unk14;
} M1BossNode;

extern u8 D_807FBD70;
extern s32 D_8076A0A8;
extern s16 D_807503A0;
void func_80613C48(Actor *, s32, s32, s32);
void func_80614EBC(Actor *, s32);
void func_80614D00(Actor *, s32, f32);
void lightSetFovAngles(f32, f32);
void lightSetFlags(u8);
void lightSetTargetId(s16);
void actorGetNodePos(void *, s32, f32 *, f32 *, f32 *);
void lightAdd(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32);

void func_8069AB74(void) {
    f32 sp74;
    f32 sp70;
    f32 sp6C;
    u16 sp5E;
    u16 sp5C;
    u16 sp5A;
    M1BossTimer *sp54;

    sp54 = (M1BossTimer *)D_807FBB40->unk174;
    if (!(D_807FBB40->unk60 & 0x10)) {
        func_80613C48(D_807FBB40, 0x402, 0, 0x3F800000);
        if (D_8076A0A8 == 6) {
            func_80614EBC(D_807FBB40, 0x297);
        }
        D_807FBB40->unk60 |= 0x400;
        sp54->unk0 = 0;
        sp54->unk4 = 1.0f;
    }
    func_80614D00(D_807FBB40, ((M1BossNode *)D_807FBB40->unk124)->unk0, 1.0f);
    if (D_807FBD70 == 4) {
        sp54->unk0 = D_807503A0;
        sp54->unk4 = 0.0f;
    }
    if (sp54->unk0 == 0) {
        sp5E = ((M1BossNode *)D_807FBB40->unk124)->unk4;
        sp5C = ((M1BossNode *)D_807FBB40->unk124)->unk8;
        sp5A = ((M1BossNode *)D_807FBB40->unk124)->unkC;
        sp5E = (u16)(u32)((f64)(u32)sp5E * (f64)sp54->unk4);
        sp5C = (u16)(u32)((f64)(u32)sp5C * (f64)sp54->unk4);
        sp5A = (u16)(u32)((f64)(u32)sp5A * (f64)sp54->unk4);
        sp54->unk4 = (f32)((f64)sp54->unk4 + 0.05);
        if (sp54->unk4 > 1.0) {
            sp54->unk4 = 1.0f;
        }
        if (D_807FBB40->unk60 & 0x10) {
            if ((f64)((M1BossNode *)D_807FBB40->unk124)->unk10 != 0.0 || (f64)((M1BossNode *)D_807FBB40->unk124)->unk14 != 0.0) {
                lightSetFovAngles(((M1BossNode *)D_807FBB40->unk124)->unk10, ((M1BossNode *)D_807FBB40->unk124)->unk14);
            }
            lightSetFlags(2);
            lightSetTargetId(D_807FBB40->unk12C);
            actorGetNodePos(D_807FBB40, 2, &sp6C, &sp70, &sp74);
            lightAdd((f32)((f64)D_807FBB40->unk7C + 0.3), D_807FBB40->unk80, D_807FBB40->unk84, sp6C, sp70, sp74, 0.0f, 1, sp5E, sp5C, sp5A);
        }
    } else {
        sp54->unk0 = sp54->unk0 - 1;
    }
    func_806319C4(D_807FBB40, 0);
}

// func_8069B010 (src/global/9DD70.c): stage 1: hand-typed m2c skeleton, compiles; frame 0x70 vs 0x50, actor ptr a2 vs s0, local 0x6c vs 0x4c; needs temp locals inlined into expressions
// real prototypes/casts. Compiles; frame 0x70 vs 0x50 (m2c temporaries as locals),
// actor pointer in a2 vs s0. Needs expressions inlined + real struct types.
typedef struct M1B010Cam {
    u8 pad0[0x210];
    f32 unk210;
    f32 unk214;
    f32 unk218;
    u8 pad21C[0xC];
    f32 unk228;
    f32 unk22C;
    f32 unk230;
} M1B010Cam;

extern Actor *D_807FBB40;
extern Actor *D_807FBB4C;
extern s32 D_807FC924;
typedef struct {
    u8 pad0[0xEC];
    s16 unkEC;
    u8 padEE[0x66];
    u8 unk154;
    u8 pad155[0xA];
    u8 unk15F;
} M1B010Sub;
#define M1B010_CAM ((M1B010Cam *)D_807FC924)
extern s32 D_8076A0A8;
extern u8 D_807FBD70;
extern s16 D_80750378;
extern s32 D_8076A068;
extern u8 D_8071FE08[];
extern u8 D_80720E14[];
void func_8071EEE0(void);

void actorSetCollisionRadius(Actor *, f32);
void func_8067ACB4(Actor *);
void func_8065D254(Actor *, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32);
void actorUpdateModelMatrix(Actor *, s32);
void func_80613C48(Actor *, s16, f32, f32);
void actorAppendCallback(Actor *, s32, s32, u8, s32, void *);
void actorAppendModelNode(Actor *, f32, f32, f32, f32, s32);
void actorAppendModelSubNode(Actor *, f32, f32, f32, s32);
void actorDespawn(Actor *);
void collisionCheckActorFloor(Actor *, f32, f32, f32, f32 *);
void lightAdd(f32, f32, f32, f32, f32, f32, f32, u8, u8, u8, u8);
void sfxPlayFromActorWithAltitudeCheck(Actor *, s16, u8, s16, u8);
void func_8071498C(void (*)(void));
void func_807149B8(s32);
void func_807149FC(s32);
s32 func_80714C08(void *, f32, Actor *, s32, s32);
void func_80714CC0(void *, f32, f32, f32, f32);
f32 mathAngleBetweenPointsDeg(s32, s32, s32, s32);

void func_8069B010(void) {
    u32 *sp4C;
    f32 sp44;
    f32 temp_fa1;
    f32 temp_ft5;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 var_fa0;
    f32 var_ft4;
    u8 temp_v1;
    Actor *temp_s0;
    Actor *temp_s0_2;
    M1B010Sub *temp_v0;

    temp_s0 = D_807FBB40;
    sp4C = (u32 *)(u32)temp_s0->unk174;
    if (!(temp_s0->unk60 & 0x10)) {
        temp_s0->unk6A = (u16) (temp_s0->unk6A & 0xFFFE);
        D_807FBB40->unk144 = 2;
        actorSetCollisionRadius(D_807FBB40, 60.0f);
        actorAppendModelNode(D_807FBB40, 0.0f, 0.0f, 0.0f, 60.0f, -1);
        actorAppendModelSubNode(D_807FBB40, 0.0f, 0.0f, 0.0f, -1);
        func_807149FC(-1);
        func_807149B8(1);
        func_8071498C(func_8071EEE0);
        func_80714C08(D_80720E14, 0.9f, D_807FBB40, 1, 2);
        *(u32 *)sp4C = D_8076A068;
        D_807FBB40->unk60 = (s32) (D_807FBB40->unk60 | 0x80000);
        collisionCheckActorFloor(D_807FBB40, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, (f32 *)((u8 *)D_807FBB40 + 0xA4));
    }
    func_8067ACB4(temp_s0);
    func_8065D254(D_807FBB40, 0x3C8, 0x40, 0x40, 0x1E, 0x1E, 1, 0x4B, 0x78, 0, 1.0f);
    temp_s0_2 = D_807FBB40;
    temp_v0 = (M1B010Sub *)(u32)temp_s0_2->unk11C;
    if (temp_v0 != NULL) {
        temp_v1 = temp_v0->unk154;
        if ((temp_v1 != 2) && (temp_v1 != 0x26)) {
            actorDespawn(temp_s0_2);
            return;
        }
        if (temp_v0->unk15F == temp_s0_2->unk15F) {
            var_fa0 = temp_s0_2->unk7C;
            var_ft4 = temp_s0_2->unk84;
            temp_fa1 = D_807FBB4C->unk7C;
            temp_ft5 = D_807FBB4C->unk84;
            temp_fv0 = var_fa0 - temp_fa1;
            temp_fv1 = var_ft4 - temp_ft5;
            if (((temp_fv0 * temp_fv0) + (temp_fv1 * temp_fv1)) > 900.0f) {
                sp44 = mathAngleBetweenPointsDeg((s32) var_fa0, (s32) temp_fa1, (s32) var_ft4, (s32) temp_ft5);
                ((M1B010Sub *)(u32)D_807FBB40->unk11C)->unkEC = (s16) (sp44 - mathAngleBetweenPointsDeg((s32) M1B010_CAM->unk228, (s32) M1B010_CAM->unk230, (s32) M1B010_CAM->unk210, (s32) M1B010_CAM->unk218));
                var_fa0 = D_807FBB40->unk7C;
                var_ft4 = D_807FBB40->unk84;
            }
            lightAdd(var_fa0, temp_s0_2->unk80, var_ft4, 0.0f, 0.0f, 0.0f, 100.0f, 0, 0xFF, 0xFF, 0);
        }
        if (D_807FBD70 == 9) {
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x1CE, 0xFF, 0x7F, 0x1E);
            func_80714CC0(D_8071FE08, 1.0f, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84);
            actorAppendCallback((void *)(u32)D_807FBB40->unk11C, D_807FBB40, 0x02000000, D_807FBB40->unk15F, 0, 0);
            actorDespawn(D_807FBB40);
        }
        if ((D_8076A0A8 != 0x48) && (D_8076A0A8 != 0x11) && ((u32) (*sp4C + D_80750378) < (u32) *&D_8076A068)) {
            actorAppendCallback((void *)(u32)D_807FBB40->unk11C, D_807FBB40, 0x02000000, 0xFFU, 0, 0);
            actorDespawn(D_807FBB40);
        }
    } else {
        actorDespawn(temp_s0_2);
    }
}

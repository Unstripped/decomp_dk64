// func_80618104 (src/global/19A00.c): stage 4: frame and instruction count match; remaining diff is stack slots (locals +0x10) and register allocation.
typedef struct { u8 pad0[0x1A4]; u8 unk1A4; } P19LNodeState;
typedef struct { u8 pad0[0x210]; f32 unk210; u8 pad214[4]; f32 unk218; u8 pad21C[0xC]; f32 unk228; u8 pad22C[4]; f32 unk230; u8 pad234[0xBC]; } P19LPlayerView;
typedef struct { u8 pad0[2]; u8 unk2; } P19LProjectileView;
extern f32 D_80753E48[];
extern s16 D_80753E64[];
extern Actor *D_807FBB48;
extern P19LPlayerView *D_807FC924;
extern u8 D_807FC929;
extern P19LProjectileView *D_807FD568;
extern s16 D_807FD584;
void slotQueueUpdate(s32, s32, s32);
s32 func_806F8AD4(s32, u8);
void func_806F91B4(s32, u8, s32);
s32 func_8067ACDC(Actor *, s32, s32);
s32 func_80671E00(f32, f32, f32, f32, s16 *, s16 *, s32, s32);
s32 func_806725E4(s16, s16, s16, s32);
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
void projectileSetSpawnFlag(void);
void projectileGetTargetCoords(Actor *, s32);
void projectileSpawnNodeEntry(s32, u8, f32, s16, f32, f32, Actor *);

void func_80618104(Actor *arg0) {
    f32 sp50;
    P19LNodeState *sp44;
    s16 sp40;
    s16 sp3E;
    f32 var_fv0;
    f32 temp_fv0;
    f32 temp_fv1;
    s16 var_a2;
    P19LPlayerView *temp_v0;

    sp44 = arg0->unk174;
    slotQueueUpdate(4, 0, 0);
    if ((func_806F8AD4(4, sp44->unk1A4) != 0) && (func_8067ACDC(arg0, 4, 0) < D_80753E64[D_807FD584])) {
        func_806F91B4(4, sp44->unk1A4, -1);
        sp50 = (f32)((f64)arg0->unk4->unk38 * 2.6666667064030967);
        switch (arg0->unk58) {
            case 2:
            case 6:
            case 7: var_fv0 = 30.0f; break;
            case 3:
            case 5: var_fv0 = 20.0f; break;
            default: var_fv0 = 30.0f; break;
        }
        if (func_80671E00(arg0->unk7C, (f32)((f64)arg0->unk80 + 30.0), arg0->unk84, var_fv0, &sp40, &sp3E, 1, 0) != 0) {
            if (arg0->unk154 == 2) {
                temp_v0 = &D_807FC924[D_807FC929];
                var_a2 = mathAngleBetweenPoints2D(temp_v0->unk228, temp_v0->unk230, temp_v0->unk210, temp_v0->unk218);
            } else {
                var_a2 = arg0->unkE6;
            }
            if (func_806725E4(sp40, sp3E, var_a2, 0) == 0) projectileSetSpawnFlag();
        }
        if (arg0->unk154 == 2) {
            projectileGetTargetCoords(D_807FBB48, 6);
            temp_fv0 = D_807FC924[D_807FC929].unk230 - D_807FC924[D_807FC929].unk218;
            temp_fv1 = D_807FC924[D_807FC929].unk228 - D_807FC924[D_807FC929].unk210;
            sqrtf((temp_fv0 * temp_fv0) + (temp_fv1 * temp_fv1));
            projectileSpawnNodeEntry(0x29, D_807FD568->unk2, sp50, mathAngleBetweenPoints2D(D_807FC924[D_807FC929].unk228, D_807FC924[D_807FC929].unk230, D_807FC924[D_807FC929].unk210, D_807FC924[D_807FC929].unk218), D_80753E48[D_807FD584], 0.0f, arg0);
            return;
        }
        projectileGetTargetCoords(arg0, 7);
        projectileSpawnNodeEntry(0x29, D_807FD568->unk2, sp50, arg0->unkE6, D_80753E48[D_807FD584], 0.0f, arg0);
    }
}

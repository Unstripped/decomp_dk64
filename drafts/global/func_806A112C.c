// func_806A112C (src/global/A2F10.c): stage 5: instruction-identical (shape=0, 42 diff lines), only t-register numbering differs in the spawn loop body (ours lw t1,0(s1)/lw t0,0(s5)/lw t2,372(t1) vs target t0/t1/v1: unk174 pointer is a v1 web there; a named local sub2=spawned->unk174 gets v1 and t0/t1 right but then ring shifts by one (mflo t5 vs t6)). Fixed: n=0; animSetChannelFrames(..,D_807503D4[n],D_807503E0[n++]) puts li s2,1 in the jal delay slot

s32 assetLoad(s32, s32, s32, s32);
void func_80724D28(s32, s32);
f32 func_80612794(s16);
f32 func_80612790(s16);
void actorSetUniformScale(Actor *, f32);
extern u8 D_807503D4[];
extern u8 D_807503E0[];

#define ATTACHED_ACTOR_SPAWNED ((AttachedActor *) D_807FBB44)

void func_806A112C(void) {
    SubStateView *sub;
    s16 i;
    u8 n;
    f32 d;
    f32 val;

    sub = ATTACHED_ACTOR->unk174;
    if (!(ATTACHED_ACTOR->unk60 & 0x10)) {
        ATTACHED_ACTOR->unk60 |= 0x400;
        func_80724D28(0, 7);
        for (i = 0; i < 7; i++) {
            ((u8 *) ATTACHED_ACTOR->unk4->unk24)[i * 0x10] = i;
            ((u8 *) ATTACHED_ACTOR->unk4->unk24)[i * 0x10 + 1] = 0xFF;
        }
        if (ATTACHED_ACTOR->unk15F == 0) {
            val = (f32) ((f64) ATTACHED_ACTOR->unk4->unk38 / 0.15);
            sub->unk0 = assetLoad(0x13, 6, 1, 1);
            n = 0;
            animSetChannelFrames(D_807FBB40, D_807503D4[n], D_807503E0[n++]);
            d = 75.0f * val;
            for (i = 1; i < 12; i++) {
                actorSpawn(0x94, 0xE1);
                ATTACHED_ACTOR_SPAWNED->unk174->unk0 = sub->unk0;
                ATTACHED_ACTOR_SPAWNED->unk15F = i;
                ATTACHED_ACTOR_SPAWNED->unkE6 = ATTACHED_ACTOR->unkE6 + ((i / 3) << 10);
                ATTACHED_ACTOR_SPAWNED->unk7C = ATTACHED_ACTOR->unk7C -
                    func_80612794(ATTACHED_ACTOR_SPAWNED->unkE6) * d;
                ATTACHED_ACTOR_SPAWNED->unk80 = ATTACHED_ACTOR->unk80 +
                    (f32) ((u8) (i % 3) * 17);
                ATTACHED_ACTOR_SPAWNED->unk84 = ATTACHED_ACTOR->unk84 -
                    func_80612790(ATTACHED_ACTOR_SPAWNED->unkE6) * d;
                actorSetUniformScale(D_807FBB44, ATTACHED_ACTOR->unk4->unk38);
                animSetChannelFrames(D_807FBB44, D_807503D4[n], D_807503E0[n++]);
            }
            ATTACHED_ACTOR->unk7C -= d * func_80612794(ATTACHED_ACTOR->unkE6);
            ATTACHED_ACTOR->unk84 -= d * func_80612790(ATTACHED_ACTOR->unkE6);
        }
    }
    switch (ATTACHED_ACTOR->unk154) {
    case 1:
        ATTACHED_ACTOR->unk168++;
        if (ATTACHED_ACTOR->unk168 == 7) {
            ATTACHED_ACTOR->unk154++;
            ATTACHED_ACTOR->unk168 = 0;
        }
        break;
    case 2:
        actorSetNodeValuesForFrame((MatrixArray *) sub);
        ATTACHED_ACTOR->unk168++;
        if (ATTACHED_ACTOR->unk168 == 11) {
            ATTACHED_ACTOR->unk154++;
        }
        break;
    case 3:
        actorSetNodeValuesForFrame((MatrixArray *) sub);
        ATTACHED_ACTOR->unk168++;
        if (ATTACHED_ACTOR->unk168 >= 52) {
            ATTACHED_ACTOR->unk168 = ((randomNonNegative() >> 15) % 1000) % 3;
            ATTACHED_ACTOR->unk154 = 0;
        }
        break;
    case 10:
        ATTACHED_ACTOR->unk168 = 11;
        actorSetNodeValuesForFrame((MatrixArray *) sub);
        break;
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

// func_806A112C (src/global/A2F10.c): stage 5: 274 insns both, frame 0x48, same callee-saved set (s0-s5, f20) and same basic blocks; remaining diff: lw a0,0(s3) takes the func_806A0F78 jal delay slot in ours where the target puts 'li s2,1' (n=1) there, plus scratch temp numbering swaps (t0/t1, t4/t5) in the switch. Key fixes vs old draft: unk15F==0 guard around the spawn block, unk60 |= 0x400, func_8066B0F8 takes 4 args (no val), f32 val spilled at 0x38 + local d = 75.0f*val in f20, unkE6 = parent->unkE6 + (i/3)<<10 (mfhi->mflo), unk80 offset needs (u8)(i%3)*17 (andi 0xff), func_80612794/90 take s16, tail uses d*func() (operand order)
s32 func_8066B0F8(s32, s32, s32, s32);
void func_80724D28(s32, s32);
f32 func_80612794(s16);
f32 func_80612790(s16);
void actorSetUniformScale(Actor *, f32);
void func_806A0F78(void *, u8, u8);
void func_806A10BC(M5_A2F10Mat *);
s32 func_80611A44(void);
void func_806319C4(void *, s32);
s32 actorSpawn(s32, s32);
extern u8 D_807503D4[];
extern u8 D_807503E0[];

#define M5_A2F10_ACTOR ((M5_A2F10Actor *) D_807FBB40)
#define M5_A2F10_SPAWNED ((M5_A2F10Actor *) D_807FBB44)

void func_806A112C(void) {
    M5_A2F10Sub *sub;
    s16 i;
    u8 n;
    f32 d;
    f32 val;

    sub = M5_A2F10_ACTOR->unk174;
    if (!(M5_A2F10_ACTOR->unk60 & 0x10)) {
        M5_A2F10_ACTOR->unk60 |= 0x400;
        func_80724D28(0, 7);
        for (i = 0; i < 7; i++) {
            ((u8 *) M5_A2F10_ACTOR->unk4->unk24)[i * 0x10] = i;
            ((u8 *) M5_A2F10_ACTOR->unk4->unk24)[i * 0x10 + 1] = 0xFF;
        }
        if (M5_A2F10_ACTOR->unk15F == 0) {
            val = (f32) ((f64) M5_A2F10_ACTOR->unk4->unk38 / 0.15);
            sub->unk0 = func_8066B0F8(0x13, 6, 1, 1);
            func_806A0F78(D_807FBB40, D_807503D4[0], D_807503E0[0]);
            n = 1;
            d = 75.0f * val;
            for (i = 1; i < 12; i++) {
                actorSpawn(0x94, 0xE1);
                M5_A2F10_SPAWNED->unk174->unk0 = sub->unk0;
                M5_A2F10_SPAWNED->unk15F = i;
                M5_A2F10_SPAWNED->unkE6 = M5_A2F10_ACTOR->unkE6 + ((i / 3) << 10);
                M5_A2F10_SPAWNED->unk7C = M5_A2F10_ACTOR->unk7C -
                    func_80612794(M5_A2F10_SPAWNED->unkE6) * d;
                M5_A2F10_SPAWNED->unk80 = M5_A2F10_ACTOR->unk80 +
                    (f32) ((u8) (i % 3) * 17);
                M5_A2F10_SPAWNED->unk84 = M5_A2F10_ACTOR->unk84 -
                    func_80612790(M5_A2F10_SPAWNED->unkE6) * d;
                actorSetUniformScale(D_807FBB44, M5_A2F10_ACTOR->unk4->unk38);
                func_806A0F78(D_807FBB44, D_807503D4[n], D_807503E0[n++]);
            }
            M5_A2F10_ACTOR->unk7C -= d * func_80612794(M5_A2F10_ACTOR->unkE6);
            M5_A2F10_ACTOR->unk84 -= d * func_80612790(M5_A2F10_ACTOR->unkE6);
        }
    }
    switch (M5_A2F10_ACTOR->unk154) {
    case 1:
        M5_A2F10_ACTOR->unk168++;
        if (M5_A2F10_ACTOR->unk168 == 7) {
            M5_A2F10_ACTOR->unk154++;
            M5_A2F10_ACTOR->unk168 = 0;
        }
        break;
    case 2:
        func_806A10BC((M5_A2F10Mat *) sub);
        M5_A2F10_ACTOR->unk168++;
        if (M5_A2F10_ACTOR->unk168 == 11) {
            M5_A2F10_ACTOR->unk154++;
        }
        break;
    case 3:
        func_806A10BC((M5_A2F10Mat *) sub);
        M5_A2F10_ACTOR->unk168++;
        if (M5_A2F10_ACTOR->unk168 >= 52) {
            M5_A2F10_ACTOR->unk168 = ((func_80611A44() >> 15) % 1000) % 3;
            M5_A2F10_ACTOR->unk154 = 0;
        }
        break;
    case 10:
        M5_A2F10_ACTOR->unk168 = 11;
        func_806A10BC((M5_A2F10Mat *) sub);
        break;
    }
    func_806319C4(D_807FBB40, 0);
}

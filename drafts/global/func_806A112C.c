// func_806A112C (src/global/A2F10.c): stage 3: full control flow reconstructed (init 4-byte/0x10-stride loop, spawn loop i=1..11 with 75.0f*(f64)unk38/0.15, switch 1/2/3/0xA); frame 0x58 vs 0x48, IDO keeps 75.0f*val in f20, hoists spawned/val differently; needs regalloc pass
void func_80724D28(s32, s32);
s32 func_8066B0F8(s32, s32, s32, s32, f32);
f32 func_80612794(s32);
f32 func_80612790(s32);
void func_807248B0(Actor *, f32);
extern u8 D_807503D4[];
extern u8 D_807503E0[];

void func_806A112C(void) {
    s16 i;
    u8 n;
    f32 val;
    Actor *spawned;

    if (!(M5_A2F10_ACTOR->unk60 & 0x10)) {
        func_80724D28(0, 7);
        for (i = 0; i < 7; i++) {
            ((u8 *) M5_A2F10_ACTOR->unk4->unk24)[i * 0x10] = i;
            ((u8 *) M5_A2F10_ACTOR->unk4->unk24)[i * 0x10 + 1] = 0xFF;
        }
        val = (f32) ((f64) M5_A2F10_ACTOR->unk4->unk38 / 0.15);
        M5_A2F10_ACTOR->unk174->unk0 = func_8066B0F8(0x13, 6, 1, 1, val);
        func_806A0F78(D_807FBB40, D_807503D4[0], D_807503E0[0]);
        n = 1;
        for (i = 1; i < 12; i++) {
            spawned = (Actor *) actorSpawn(0x94, 0xE1);
            ((M5_A2F10Sub *) spawned->unk174)->unk0 = M5_A2F10_ACTOR->unk174->unk0;
            spawned->unk15F = i;
            M5_A2F10_ACTOR->unkE6 += (i % 3) << 10;
            spawned->unk7C = M5_A2F10_ACTOR->unk7C - func_80612794(spawned->unkE6) * (75.0f * val);
            spawned->unk80 = M5_A2F10_ACTOR->unk80 + (f32) ((i % 3) * 17);
            spawned->unk84 = M5_A2F10_ACTOR->unk84 - func_80612790(spawned->unkE6) * (75.0f * val);
            func_807248B0(spawned, M5_A2F10_ACTOR->unk4->unk38);
            func_806A0F78(spawned, D_807503D4[n], D_807503E0[n++]);
        }
        M5_A2F10_ACTOR->unk7C -= func_80612794(M5_A2F10_ACTOR->unkE6) * (75.0f * val);
        M5_A2F10_ACTOR->unk84 -= func_80612790(M5_A2F10_ACTOR->unkE6) * (75.0f * val);
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
        func_806A10BC((M5_A2F10Mat *) M5_A2F10_ACTOR->unk174);
        M5_A2F10_ACTOR->unk168++;
        if (M5_A2F10_ACTOR->unk168 == 11) {
            M5_A2F10_ACTOR->unk154++;
        }
        break;
    case 3:
        func_806A10BC((M5_A2F10Mat *) M5_A2F10_ACTOR->unk174);
        M5_A2F10_ACTOR->unk168++;
        if (M5_A2F10_ACTOR->unk168 >= 52) {
            M5_A2F10_ACTOR->unk168 = ((func_80611A44() >> 15) % 1000) % 3;
            M5_A2F10_ACTOR->unk154 = 0;
        }
        break;
    case 10:
        M5_A2F10_ACTOR->unk168 = 11;
        func_806A10BC((M5_A2F10Mat *) M5_A2F10_ACTOR->unk174);
        break;
    }
    func_806319C4(D_807FBB40, 0);
}

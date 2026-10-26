// func_8069E088 (src/global/9DD70.c): stage 6: identical except one dead 'li a0,1' (target materialises constant 1 before the unk154<0x1E test); best shape is a u8 temp + explicit reload inside the if (gives the target's late 'move v0,v1' in the beqz delay slot); 235 vs 236 insns. Tried: +1/+=1/++ (field and temp), 1+x, (u8) casts, s32/u32 temps, ternary/if-else phi, reordering, hoisted add, permuter 200s.
void func_80613C48(Actor *, s16, f32, f32);
s32 flagGet(s32, s32);
void flagSet(s32, s32, s32);
void func_8070E8DC(void);
s32 func_80600530(void);
void func_8070D8C0(Actor *, s32, u8);
void actorDespawn(Actor *);
void func_806319C4(Actor *, s32);

extern s8 D_807F6951;
extern s8 D_807F6950;

void func_8069E088(void) {
    s16 unk;
    u8 unk154;

    if (!(D_807FBB40->unk60 & 0x10)) {
        func_80613C48(D_807FBB40, 0x5ED, 0.0f, 0.0f);
    }
    D_807FBB40->unk15E = 0x14;
    unk154 = D_807FBB40->unk154;
    if (unk154 < 0x1E) {
        D_807FBB40->unk154 = unk154 + 1;
        unk154 = D_807FBB40->unk154;
    }
    if (D_807FBB40->unk154 == 0x1E) {
        unk = 0;
        D_807FBB40->unk154 = 0x64;
        func_8070E8DC();
        if (flagGet(0x178, 0) == 0) {
            flagSet(0x178, 1, 0);
        } else {
            unk = func_80600530() * 5 + D_807F6951 + 1;
        }
        func_8070D8C0(D_807FBB40, 0x29, unk);
    }
    if (D_807F6950 != 0) {
        actorDespawn(D_807FBB40);
    }
    D_807FBB40->unk4->unk34 = 0.0f;
    D_807FBB40->unk4->unk38 = 0.0f;
    D_807FBB40->unk4->unk3C = 0.0f;
    func_806319C4(D_807FBB40, 0);
}

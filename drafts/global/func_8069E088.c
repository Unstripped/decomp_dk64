// func_8069E088 (src/global/9DD70.c): stage 6: mine hoists &D_807FBB40 into s1 (extra saved reg) and keeps unk in a slot; target recomputes the address in t0 and keeps unk in s0
extern Actor *D_807FBB40;
void func_80613C48(Actor *, s32, f32, f32);
s32 func_8073110C(s32, s32);
void func_8073129C(s32, s32, s32);
void func_8070E8DC(void);
s32 func_80600530(void);
void func_8070D8C0(Actor *, s32, u8);
extern s8 D_807F6951;
extern s8 D_807F6950;
void actorDespawn(Actor *);
void func_806319C4(Actor *, s32);

void func_8069E088(void) {
    Actor *actor;
    s16 unk;

    actor = D_807FBB40;
    if (!(actor->unk60 & 0x10)) {
        func_80613C48(actor, 0x5ED, 0.0f, 0.0f);
        actor = D_807FBB40;
    }
    actor->unk15E = 0x14;
    actor = D_807FBB40;
    if (actor->unk154 < 0x1E) {
        actor->unk154++;
        actor = D_807FBB40;
    }
    if (actor->unk154 == 0x1E) {
        unk = 0;
        actor->unk154 = 0x64;
        func_8070E8DC();
        if (func_8073110C(0x178, 0) == 0) {
            func_8073129C(0x178, 1, 0);
        } else {
            unk = func_80600530() * 5 + D_807F6951 + 1;
        }
        func_8070D8C0(D_807FBB40, 0x29, unk);
        actor = D_807FBB40;
    }
    if (D_807F6950 != 0) {
        actorDespawn(actor);
        actor = D_807FBB40;
    }
    actor->unk4->unk34 = 0.0f;
    D_807FBB40->unk4->unk38 = 0.0f;
    D_807FBB40->unk4->unk3C = 0.0f;
    func_806319C4(D_807FBB40, 0);
}

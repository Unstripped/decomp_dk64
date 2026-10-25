// func_806EB744 (src/global/EFDC0.c): Stage 4: correct frame and subactor layout; global-load register allocation remains.
typedef struct EfN2SubActor {
    u8 pad0[0xB2];
    s16 unkB2;
    f32 unkB4;
    f32 unkB8;
    s16 unkBC;
    u8 padBE[0x31];
    u8 unkEF;
    u8 unkF0;
    u8 padF1[2];
    s8 unkF3;
} EfN2SubActor;

typedef struct EfN2TargetActor {
    u8 pad0[0xB4];
    f32 unkB4;
} EfN2TargetActor;

void func_80627878(void *);
void func_8062217C(void *, s32);
void func_806F0D68(Actor *);
void sfxStopSlotSound(Actor *, u8);

void func_806EB744(void) {
    s16 speed;
    EfN2SubActor *subactor;
    Actor *actor;
    s32 state;
    u8 type;

    actor = EfA_P->unk104;
    subactor = actor->unk174;
    type = subactor->unkEF;
    speed = subactor->unkB8;
    if (type != 0) {
        subactor->unkF0 = type;
        speed = 0x80;
        actor = EfA_P->unk104;
    }
    func_80627878(actor);
    func_8062217C(EfA_P->unk104, 0);
    state = EfA_Q[D_807FC929].unk2A8;
    subactor->unkF3 = state;
    if ((u8)state == 3) {
        sfxStopSlotSound(D_807FBB48, 0);
        func_80609140(0x26, 0x7FFF, 63.0f, 1.0f, 0, 0);
        if (EfA_Q[D_807FC929].unk2AC != 0) {
            func_806F0D68(D_807FBB48);
        }
    }
    subactor->unkBC = 0x80;
    ((EfN2TargetActor *)EfA_P->unk104)->unkB4 = speed;
    subactor->unkB8 = speed;
    subactor->unkB2 = D_807FBB48->unkE6 + 0x800;
    D_807FBB48->unkB8 = 0.0f;
    D_807FBB48->unk6A |= 0x2000;
}

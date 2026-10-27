// func_8069E210 (src/global/A2F10.c): stage 6: 0x280 same size; tail reload now matches (lui s0,%hi; lw s0,%lo) via local Actor **p = &D_807FBB40 / actor = *p; remaining diff is scratch temp allocation only (expected v0/v1/t0.., ours t2..), instruction sequence otherwise identical
extern Actor *D_807FBB40;
extern ActorGlobalState D_807FBB70;

typedef struct M4Sub4 {
    /* 0x00 */ void *unk0;
} M4Sub4;

typedef struct M4Sub4Inner {
    /* 0x00 */ u8 pad0[0x24];
    /* 0x24 */ f32 unk24;
} M4Sub4Inner;

void func_80613C48(Actor *, s16, f32, f32);
void func_80613CA8(Actor *, s16, f32, f32);
void func_80614D00(Actor *, f32, f32);
s32 actorListFindIdByActor(Actor *);
void actorUpdateModelMatrix(void *, s32);

void func_8069E210(void) {
    Actor *actor;
    Actor **p;
    s16 i;

    actor = D_807FBB40;
    p = &D_807FBB40;
    if (!(actor->unk60 & 0x10)) {
        actor->unk60 &= ~4;
        func_80613C48(D_807FBB40, 0x407, 0.0f, 0.0f);
        func_80614D00(D_807FBB40, 0.0f, 0.0f);
        actor = D_807FBB40;
    }
    for (i = 0; i < D_807FBB70.unk254; i++) {
        if (*D_807FBB70.unk278[i] == 0) {
            actor->unk60 |= 4;
            func_80613CA8(D_807FBB40, 0x407, 0.0f, 0.0f);
            func_80614D00(D_807FBB40, 1.0f, 0.0f);
            switch (actorListFindIdByActor(D_807FBB40)) {
            case 5:
                func_80609140(0x1D7, 0x7FFF, 63.0f, 1.0f, 0x1E, 0);
                break;
            case 6:
                func_80609140(0x1D8, 0x7FFF, 63.0f, 1.0f, 0x1E, 0);
                break;
            case 7:
                func_80609140(0x1D9, 0x7FFF, 63.0f, 1.0f, 0, 0);
                break;
            case 8:
                func_80609140(0x1DA, 0x7FFF, 63.0f, 1.0f, 2, 0);
                break;
            case 9:
                func_80609140(0x1DB, 0x7FFF, 63.0f, 1.0f, 0x1E, 0);
                break;
            case 10:
                func_80609140(0x1DC, 0x7FFF, 63.0f, 1.0f, 0x1E, 0);
                break;
            }
            actor = D_807FBB40;
        }
    }
    if (0.0f == ((M4Sub4Inner *)((M4Sub4 *)actor->unk4)->unk0)->unk24) {
        actor->unk60 &= ~4;
        actor = *p;
    }

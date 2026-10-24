// func_806A1FD8 (src/global/A6280.c): stage 5: basic blocks, calls and saved regs (s0-s3,f20) all match; frame 0x78 vs 0x68 (IDO reserves 2-3 extra unused slots, likely from the chained unk114->items[i] deref / double temp); found spill 0x5f vs 0x5b, count spill 0x64 matches; cast (f32)(f64)sp50+10.0 must stay double math
typedef struct M6Sub174 {
    s16 unk0;
    u8 pad2[2];
    f32 unk4;
    f32 unk8;
} M6Sub174;

typedef struct M6ActorView {
    u8 pad0[0x130];
    u8 unk130;
    u8 unk131;
} M6ActorView;

extern Actor *D_807FBB4C;
extern s32 D_8071FF18;

void actorDespawn(Actor *);
s16 actorListFindIdByActor(Actor *);
s32 actorListLookupEntry(u16);
s32 actorTableContains();
s32 func_8073110C(s16, s32);
void actorGetNodePos(Actor *, s32, f32 *, f32 *, f32 *);
void func_80714998(s32);
void func_807149B8(s32);
void func_8071498C(void *);
void func_80714950(s32);
void func_807149C8(s32, s32, s32, s32);
s32 func_80714CC0(void *, f32, f32, f32, f32);
void func_80717D4C(void);
void func_806A5DF0(s32, f32, f32, f32, s32, s32, s32, s32);
void sfxAllocateChannel(s32, f32);
void sfxPlayFromActorWithAltitudeCheck(Actor *, s32, s32, s32, s32);

void func_806A1FD8(void) {
    M6Sub174 *sub;
    ActorList *list;
    Actor *act;
    s32 count;
    s32 i;
    u8 found;
    s32 node;
    f32 sp54;
    f32 sp50;
    f32 sp4C;

    sub = D_807FBB40->unk174;
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk64 |= 8;
        sub->unk0 = 0;
        sub->unk4 = 0.0f;
        sub->unk8 = D_807FBB40->unk80;
        ((M6ActorView *)D_807FBB40)->unk130 = 0x46;
        ((M6ActorView *)D_807FBB40)->unk131 = 0x14;
        if (func_8073110C(actorListLookupEntry(actorListFindIdByActor(D_807FBB40)), 0) != 0) {
            actorDespawn(D_807FBB40);
        }
    }
    if (D_807FBB4C->unk154 == 0x2D && D_807FBB4C->unk155 != 0) {
        found = 0;
        list = D_807FBB40->unk114;
        if (list != NULL) {
            count = list->count;
            i = 0;
            if (count != 0) {
                do {
                    act = (Actor *)D_807FBB40->unk114->items[i];
                    if (actorTableContains(act) != 0 && act == D_807FBB4C) {
                        found = 1;
                    }
                    count--;
                    i++;
                } while (count != 0 && found == 0);
            }
        }
        if (found != 0) {
            node = 1;
            if (sub->unk0 == 0) {
                do {
                    func_80714998(2);
                    func_807149B8(1);
                    func_8071498C(&func_80717D4C);
                    func_80714950(-0x64);
                    func_807149C8(0x64, 0x46, 0x1E, 0xFF);
                    actorGetNodePos(D_807FBB40, node, &sp54, &sp50, &sp4C);
                    func_80714CC0(&D_8071FF18, 2.0f, sp54, sp50 + 10.0, sp4C);
                    node++;
                } while (node != 9);
                sub->unk0 = 0xF;
                sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x1C1, 0xFF, 0x7F, 1);
            }
        }
    }
    if (sub->unk0 >= 2) {
        sub->unk0--;
    }
    if (sub->unk0 == 2) {
        func_806A5DF0(0x8C, D_807FBB40->unk7C, D_807FBB40->unk80 + 10.0f, D_807FBB40->unk84, 0, 1, actorListLookupEntry(actorListFindIdByActor(D_807FBB40)), 0);
    }
    if (sub->unk0 < 0xA && sub->unk0 != 0) {
        sub->unk4 = sub->unk4 + 1.0;
        if (sub->unk4 > 20.0) {
            sfxAllocateChannel(0x90, 1.0f);
            actorDespawn(D_807FBB40);
        }
    }
    D_807FBB40->unk80 -= sub->unk4;
    func_806319C4(D_807FBB40, 0);
    D_807FBB40->unk80 = sub->unk8;
}

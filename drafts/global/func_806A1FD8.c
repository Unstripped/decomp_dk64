// func_806A1FD8 (src/global/A6280.c): stage 6: score 10 - 212/212 instrs identical (incl. sll s1,zero,2) except frame 0x70 vs 0x68 (one unused 8-byte slot at 0x68). All stack slots match: sp50/sp54/sp4C 0x4C/50/54, found 0x5B, count 0x64. NEEDED: local decl order sub,act,count,i,node,found and 'do { i = 0; } while (0);' for i (plain i=0 emits move s1,zero and grows frame). list local must not be cached; unk155 is an array -> unk155[0]
extern Actor *D_807FBB40;
extern Actor *D_807FBB4C;

typedef struct A6R2Av {
    u8 pad0[0x130];
    u8 unk130;
    u8 unk131;
    u8 pad132[0x178 - 0x132];
    void *unk178;
} A6R2Av;

typedef struct A6R2Sub174 {
    s16 unk0;
    u8 pad2[2];
    f32 unk4;
    f32 unk8;
} A6R2Sub174;

extern s32 D_8071FF18;

void actorDespawn(Actor *);
s16 actorListFindIdByActor(Actor *);
s32 actorListLookupEntry(u16);
s32 actorTableContains();
void actorGetNodePos(Actor *, s32, f32 *, f32 *, f32 *);
void func_80717D4C(void);
void func_806A5DF0(s32, f32, f32, f32, s32, s32, s32, s32);
void sfxAllocateChannel(s32, f32);
void sfxPlayFromActorWithAltitudeCheck(Actor *, s32, s32, s32, s32);

void func_806A1FD8(void) {
    A6R2Sub174 *sub;
    Actor *act;
    s32 count;
    s32 i;
    s32 node;
    u8 found;
    f32 sp54;
    f32 sp50;
    f32 sp4C;

    sub = D_807FBB40->unk174;
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk64 |= 8;
        sub->unk0 = 0;
        sub->unk4 = 0.0f;
        sub->unk8 = D_807FBB40->unk80;
        ((A6R2Av *)D_807FBB40)->unk130 = 0x46;
        ((A6R2Av *)D_807FBB40)->unk131 = 0x14;
        if (flagGet(actorListLookupEntry(actorListFindIdByActor(D_807FBB40)), 0) != 0) {
            actorDespawn(D_807FBB40);
        }
    }
    if (D_807FBB4C->unk154 == 0x2D && D_807FBB4C->unk155[0] != 0) {
        found = 0;
        if (D_807FBB40->unk114 != NULL) {
            count = D_807FBB40->unk114->count;
            do { i = 0; } while (0);
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
    actorUpdateModelMatrix(D_807FBB40, 0);
    D_807FBB40->unk80 = sub->unk8;
}

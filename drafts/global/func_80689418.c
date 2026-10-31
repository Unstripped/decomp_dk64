// func_80689418 (src/global/8D3E0.c): stage 5 (near-miss): frame 0x80 matches (correct local var types/scopes), deadsweep full=72 text=72 shape=35
typedef struct ActorListSpawnEntry {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ char unk4[4];
    /* 0x08 */ s16 unk8;
    /* 0x0A */ char unkA[2];
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ char unk14[0x1C];
} ActorListSpawnEntry;
extern ActorListSpawnEntry D_8074E8B0[];

typedef struct ActorListNodeInternal {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ char unk24[0x20];
    /* 0x44 */ Actor *unk44;
    /* 0x48 */ u8 unk48;
    /* 0x49 */ u8 unk49;
    /* 0x4A */ s16 unk4A;
    /* 0x4C */ u8 unk4C;
    /* 0x4D */ char unk4D[3];
    /* 0x50 */ s32 unk50;
    /* 0x54 */ f32 unk54;
    /* 0x58 */ s16 unk58;
    /* 0x5A */ s16 unk5A;
    /* 0x5C */ s32 (*unk5C)(struct ActorListNodeInternal *);
    /* 0x60 */ s32 (*unk60)(struct ActorListNodeInternal *);
    /* 0x64 */ char unk64[4];
    /* 0x68 */ struct ActorListNodeInternal *next;
} ActorListNodeInternal;

typedef struct ActorListSpawnInfo {
    s16 unk0;
    s16 unk2;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    s16 unk1A;
    s16 unk1C;
    s32 unk20;
} ActorListSpawnInfo;

void actorDeregisterActive(Actor *);
void actorRegisterActive(Actor *);
s32 actorSpawnFromInfo(ActorListSpawnInfo *);
s32 func_80612E90();
void controllerAnimFreeSub(Actor *, s32);
void func_8068A1B8(void);
extern Actor *D_807FBB44;

void func_80689418(void) {
    ActorListSpawnInfo spawnInfo;
    Actor *actor;
    ActorListNodeInternal *node;
    ActorListSpawnEntry *entry;
    s32 found;
    s32 i;
    s16 target;

    node = (ActorListNodeInternal *)D_807FC400;
    if (node != NULL) {
        do {
            if (node->unk48 != 0) {
                if (node->unk60(node) != 0) {
                    actor = node->unk44;
                    if (!(actor->unk60 & 0x200000)) {
                        actorDeregisterActive(actor);
                        node->unk48 = 0;
                        node->unk10 = actor->unk7C;
                        node->unk14 = actor->unk80;
                        node->unk18 = actor->unk84;
                        node->unk4A = *(s16 *)&actor->unk12C[0];
                        controllerAnimFreeSub(node->unk44, 0);
                        controllerAnimFreeSub(node->unk44, 1);
                        controllerAnimFreeSub(node->unk44, 2);
                    }
                }
            } else if (node->unk5C(node) != 0) {
                actor = node->unk44;
                found = 0;
                i = 0;
                if (actor == NULL) {
                    target = node->unk00 + 0x10;
                    entry = &D_8074E8B0[i];
                    do {
                        if (target == entry->unk0) {
                            found = 1;
                        } else {
                            entry++;
                        }
                        i++;
                    } while (!found && i < 0x80);

                    spawnInfo.unk0 = target;
                    spawnInfo.unk4 = D_8074E8B0[i].unk2;
                    spawnInfo.unk8 = (s32)D_8074E8B0[i].unk4;
                    spawnInfo.unkC = node->unk04;
                    spawnInfo.unk10 = node->unk08;
                    spawnInfo.unk14 = node->unk0C;
                    spawnInfo.unk18 = node->unk1C;
                    spawnInfo.unk1A = 0;
                    spawnInfo.unk1C = (s32)node->unk24;
                    if (actorSpawnFromInfo(&spawnInfo) != 0) {
                        node->unk48 = 1;
                        node->unk44 = D_807FBB44;
                        D_807FBB44->unk11C = node->unk50;
                        if (D_807FBB44->unk4 != NULL) {
                            D_807FBB44->unk4->unk34 = (f32)(node->unk20 * 0.15);
                            D_807FBB44->unk4->unk38 = (f32)(node->unk20 * 0.15);
                            D_807FBB44->unk4->unk3C = (f32)(node->unk20 * 0.15);
                        }
                    }
                } else if (node->unk48 == 0) {
                    if (node->unk58 != 0) {
                        *(s32 *)node->unk44 = func_80612E90(actor, node->unk58, 0);
                        actor = node->unk44;
                    }
                    actorRegisterActive(actor);
                    node->unk48 = 1;
                }
            }
            node = node->next;
        } while (node != NULL);
    }
    func_8068A1B8();
}

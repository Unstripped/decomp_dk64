// func_806F73A0 (src/global/F9450.c): stage 5 (parked NON_MATCHING in F94D copy): same 9 s-regs + frame 0x98, 459 vs 460 insns, i@0x90 cursor@0x58 ok. 2 deadsweep FAKEs: D_807FC924==0 after player load (fixes actor/tbl s1/s2 swap; side effect t6->v0 on the D_807FC924 load) and D_807FC928&&D_807FC928 in sub->unk1 block. Remaining: sfx arg (x&0xFF)&0xFF makes uopt emit 'andi s0,s6,0xff; andi a0,s0,0xff' before func_806F54E0 (target single andi a0,s6), flag chain lacks 'move v0,a0 / b' layout, modelSlotAppend/func_806F50C8 arg schedule, preheader addiu s3/v1 order, FP temp ring f10/f16/f18
typedef struct F9N7_Slot {
    u8 pad0[0x7C];
    u8 *unk7C;
    u8 pad80[0xC];
    u8 unk8C;
    u8 pad8D[3];
} F9N7_Slot;

extern F9N7_Slot *D_807F6000;
s32 hashTableLookup();
extern s32 D_807FBB60;
extern s32 D_807FBB64;
extern s32 camDistance3D(s32, s32, s32, s32, s32, s32);
s16 csModelSlotGetTableIndex(s16);
void playerStateHandleSoundEffects(s16, s32);
extern s16 modelSlotAppend(s32, f32, f32, f32, f32, u8);
extern void func_806F50C8(s16, s16, s16, u8, u8, u8);

typedef struct {
    u8 pad0[4];
    Actor *unk4;
    u8 pad8[0x2E8];
} F94D_Block;

typedef struct {
    s16 unk0;
    u8 pad2[0xA];
    s16 unkC;
    s16 unkE;
    s16 unk10;
    s16 unk12;
} F94D_Entry;

typedef struct F94D_Node {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    struct F94D_Node *unk10;
} F94D_Node;

typedef struct {
    u8 pad0;
    u8 unk1;
    u8 pad2[8];
    s16 unkA;
    u8 padC[0x80];
    u8 unk8C;
    u8 pad8D[0x1D7];
    s32 unk264;
} F94D_Sub;

typedef struct {
    Actor *unk0;
    s32 unk4;
} F94D_ActiveEntry;

extern u16 gActiveActorCount;
extern F94D_ActiveEntry gActiveActors[];
extern u8 D_80754238[];
extern s16 D_8076A0AA;
void actorDespawn(void *);
void func_806CFF9C(void *);
void func_806F0D68(void *);
void func_80731410(s16, s16, s16, u8);
u8 func_8073198C(s16);
void modelFlagsApplyState(s16, s16, u8 *);

void func_806F73A0(u8 arg0) {
    Actor *player;
    s32 i;
    F94D_Sub *playerSub;
    F94D_Entry *entry;
    Actor *actor;
    F94D_Sub *sub;
    F94D_Node *node;
    s32 found;
    s32 flag;
    u32 temp_a0;
    s16 slot;
    s16 tblIdx;

    player = ((F94D_Block *) D_807FC924)[arg0 & 0xFF].unk4;  // FAKE: & 0xFF reads arg0 as one ucvt candidate (s6), not the u8 param home
    if (D_807FC924 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    playerSub = player->unk174;
    if (D_807FCC4B[(arg0 & 0xFF) * 0x306] > 0) {  // FAKE: & 0xFF reads arg0 as one ucvt candidate (s6), not the u8 param home
        entry = (F94D_Entry *) &D_80753EF0;
        do {
            if (entry->unkE != 0) {
                for (i = 0; i < gActiveActorCount; i++) {
                    {
                        actor = gActiveActors[i].unk0;
                        if ((D_807FBB60 & 0x10000) && (entry->unkE == actor->unk58) && ((entry->unkC == 0) || (entry->unkC == player->unk58))) {
                            node = (F94D_Node *) D_807FD780[arg0 & 0xFF];  // FAKE: & 0xFF reads arg0 as one ucvt candidate (s6), not the u8 param home
                            found = (f32) camDistance3D((s32) actor->unk7C, (s32) ((f32) entry->unk10 + actor->unk80), (s32) actor->unk84, (s32) D_807FD740[arg0 & 0xFF].unk0, (s32) D_807FD740[arg0 & 0xFF].unk4, (s32) D_807FD740[arg0 & 0xFF].unk8) < ((f32) entry->unk12 + D_807FD740[arg0 & 0xFF].unkC) - 1.0f;  // FAKE: & 0xFF reads arg0 as one ucvt candidate (s6), not the u8 param home
                            while ((found == 0) && (node != NULL)) {
                                found = (f32) camDistance3D((s32) actor->unk7C, (s32) ((f32) entry->unk10 + actor->unk80), (s32) actor->unk84, (s32) node->unk0, (s32) node->unk4, (s32) node->unk8) < ((f32) entry->unk12 + node->unkC) - 1.0f;
                                node = node->unk10;
                            }
                            if ((actor->unk154 == 0x64) || (found != 0)) {
                                if ((D_807FBB64 & 0x10000) && (func_806F5C30(actor->unk58) != 0)) {
                                    func_806F5F2C(actor->unk58, 0x258, (s16) (s32) actor->unk7C, (s16) (s32) actor->unk80, (s32) actor->unk84);
                                }
                                sub = actor->unk174;
                                if (sub->unk1 != 0) {
                                    if (D_807FC928 && D_807FC928) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                                    if (D_807FC928 >= 2) {
                                        switch ((u32) actor->unk58) {
                                        case 0x7A:
                                            playerStateHandleSoundEffects(0x1D2, (arg0 & 0xFF) & 0xFF);  // FAKE: (x & 0xFF) & 0xFF keeps the andi after arg0 stays in s6
                                            func_806F54E0(arg0 & 0xFF, 0x1D2, 0);  // FAKE: & 0xFF reads arg0 as one ucvt candidate (s6), not the u8 param home
                                            break;
                                        case 0x79:
                                            playerStateHandleSoundEffects(0x8E, (arg0 & 0xFF) & 0xFF);  // FAKE: (x & 0xFF) & 0xFF keeps the andi after arg0 stays in s6
                                            playerSub->unk264 = 0;
                                            break;
                                        case 0x2F:
                                            playerStateHandleSoundEffects(0x57, (arg0 & 0xFF) & 0xFF);  // FAKE: (x & 0xFF) & 0xFF keeps the andi after arg0 stays in s6
                                            func_806F54E0(arg0 & 0xFF, 0x57, 0);  // FAKE: & 0xFF reads arg0 as one ucvt candidate (s6), not the u8 param home
                                            break;
                                        case 0x77:
                                            playerStateHandleSoundEffects(0x1D0, (arg0 & 0xFF) & 0xFF);  // FAKE: (x & 0xFF) & 0xFF keeps the andi after arg0 stays in s6
                                            playerSub->unk264 = 1;
                                            break;
                                        case 0x78:
                                            playerStateHandleSoundEffects(0x1CF, (arg0 & 0xFF) & 0xFF);  // FAKE: (x & 0xFF) & 0xFF keeps the andi after arg0 stays in s6
                                            playerSub->unk264 = 2;
                                            break;
                                        case 0x33:
                                            playerStateHandleSoundEffects(0x8F, (arg0 & 0xFF) & 0xFF);  // FAKE: (x & 0xFF) & 0xFF keeps the andi after arg0 stays in s6
                                            if ((func_80714608(0) != 0) && (((F94D_Sub *) player->unk174)->unk8C == 0)) {
                                                func_806F0D68(player);
                                                func_806CFF9C(player);
                                            }
                                            break;
                                        case 0x34:
                                            playerStateHandleSoundEffects(0x56, (arg0 & 0xFF) & 0xFF);  // FAKE: (x & 0xFF) & 0xFF keeps the andi after arg0 stays in s6
                                            playerSub->unk264 = 3;
                                            break;
                                        case 0x76:
                                            playerStateHandleSoundEffects(0x1D1, (arg0 & 0xFF) & 0xFF);  // FAKE: (x & 0xFF) & 0xFF keeps the andi after arg0 stays in s6
                                            playerSub->unk264 = 4;
                                            break;
                                        }
                                    } else {
                                        temp_a0 = actor->unk58;
                                        flag = 1;
                                        if ((actor->unk58 != 0x2F) && (actor->unk58 != 0x48) && (actor->unk58 != 0x56)) {
                                            flag = 0;
                                        }
                                        slot = modelSlotAppend(entry->unk0, actor->unk7C, func_806F7378(temp_a0) + actor->unk80, actor->unk84, 0.0f, 0);
                                        tblIdx = csModelSlotGetTableIndex(slot);
                                        func_80731410(D_8076A0AA, tblIdx, sub->unkA, func_8073198C(sub->unkA));
                                        tblIdx = csModelSlotGetTableIndex(slot);
                                        modelFlagsApplyState(D_8076A0AA, tblIdx, &D_807F6000[hashTableLookup(slot)].unk8C);
                                        func_806F50C8(slot, entry->unk0, 0, 1, 0, flag);
                                        actor->unk11C = 0;
                                    }
                                    actorDespawn(actor);
                                }
                            }
                        }
                    }
                }
            }
            entry++;
        } while ((u8 *) entry != D_80754238);
    }
}

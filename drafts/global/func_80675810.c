// func_80675810 (src/global/7A510.c): func_80675810 (src/global/7A510.c): stage 5, frame 0x30 + control flow match, ~90 diff lines: s2/s1 (arg1 temp), s0/s4 (i) and D_807FBB70 base reg (target s0 const lui, ours s1/re-lui at every access) swapped; tried i as pointer/loop-index forms, tbl[i] form, removal of dead-stmt fake
typedef struct KaN5_ActorSub174_810 {
    u8 pad0[0xD4];
    s16 unkD4;
} KaN5_ActorSub174_810;

typedef struct KaN5_Actor810 {
    u8 pad0[0x54];
    s32 unk54;
    union {
        s32 unk58;
        struct {
            s16 unk58_half;
            s16 unk5A;
        };
    };
    u16 unk5C;
    u8 pad5E[2];
    u32 unk60;
    u32 unk64;
    u8 pad68[0xB4];
    struct KaN5_Actor810 *unk11C;
    u8 pad120[0x12];
    s16 unk132;
    s16 unk134;
    s16 unk136;
    u8 pad138[0x3C];
    KaN5_ActorSub174_810 *unk174;
} KaN5_Actor810;

typedef struct KaN5_Arg1_Elem {
    u8 pad0[0x18];
    s32 unk18;
} KaN5_Arg1_Elem;

typedef struct KaN5_Arg1 {
    u8 pad0[0x8];
    KaN5_Actor810 *unk8;
    u8 padC[4];
    KaN5_Arg1_Elem *unk10;
} KaN5_Arg1;

typedef struct KaN5_80675810_Entry {
    s16 unk0;
    s16 unk2;
    s32 (*unk4)(KaN5_Actor810 *, KaN5_Actor810 *, KaN5_Arg1 *);
    u8 unk8;
    u8 unk9;
    u8 unkA;
    u8 unkB;
} KaN5_80675810_Entry;

struct CollisionTableEntry;
struct Beh798_Actor;

typedef struct KaN5_8074C604 {
    struct CollisionTableEntry *unk0;
    u8 pad4[4];
} KaN5_8074C604;

typedef struct Beh798_8074C608 {
    u8 unk0;
    u8 pad[7];
} Beh798_8074C608;

extern KaN5_8074C604 D_8074C604[];
extern Beh798_8074C608 D_8074C608[];
extern ActorGlobalState D_807FBB70;

s32 actorTableContains(void *);
void func_80675D70(s32);
s32 actorCollisionFindTableEntry(struct CollisionTableEntry *, s16, s16);
s32 func_80676220(s16);
void actorApplyDamage(struct Beh798_Actor *, struct Beh798_Actor *);
void func_80675AFC();

void func_80675810(KaN5_Actor810 *arg0, KaN5_Arg1 *arg1) {
    KaN5_80675810_Entry *entry;
    s32 done;
    KaN5_Actor810 *temp_s2;
    s32 res;
    struct CollisionTableEntry *entries;
    u8 var_v1;
    s32 i;

    temp_s2 = arg1->unk8;
    done = 0;
    i = 0;
    if (actorTableContains(temp_s2) && arg1->unk10->unk18 == temp_s2->unk54) {
        entries = D_8074C604[arg0->unk58].unk0;
        if (entries == NULL) {
            if (temp_s2->unk60 & 0x20000) {
                func_80675D70((s32)temp_s2);
            }
        } else {
            res = actorCollisionFindTableEntry(entries, temp_s2->unk5A, temp_s2->unk5C);
            if ((temp_s2->unk60 & 0x80000) || (arg0->unk60 & 0x80000)) {
                if (arg0 == temp_s2->unk11C || temp_s2 == arg0->unk11C) {
                    return;
                }
            }
            if (res == 0) {
                if (temp_s2->unk60 & 0x20000) {
                    func_80675D70((s32)temp_s2);
                }
            } else {
                do {
                    entry = &((KaN5_80675810_Entry *)res)[i];
                    if ((entry->unk0 & arg0->unk132) && (entry->unk2 & temp_s2->unk132)) {
                        var_v1 = 1;
                        if (entry->unk4 != NULL) {
                            var_v1 = entry->unk4(arg0, temp_s2, arg1);
                        }
                        if (var_v1) {
                            if (D_8074C604) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                            if (D_807FBB70.unk200 < entry->unk8) {
                                D_807FBB70.unk1FC = (s32)temp_s2;
                                D_807FBB70.unk200 = entry->unk8;
                            }
                            if (D_807FBB70.unk201 < 0xF) {
                                D_807FBB70.unk204[D_807FBB70.unk201] = (s32)temp_s2;
                                D_807FBB70.unk244[D_807FBB70.unk201] = entry->unk9;
                                D_807FBB70.unk201++;
                                if (temp_s2->unk5C & 1) {
                                    if (temp_s2->unk174->unkD4 != 0) {
                                        if (D_8074C608[arg0->unk58].unk0 != 0) {
                                            u8 t = D_807FBB70.unk244[D_807FBB70.unk201 - 1];
                                            if (t == 5 || t == 0xF) {
                                                D_807FBB70.unk201--;
                                            }
                                        }
                                    }
                                    if ((arg0->unk5C & 2) && func_80676220(arg0->unk5A)) {
                                        temp_s2->unk64 |= 0x1000;
                                    }
                                }
                            }
                            if (entry->unkA == 0 || entry->unkA == 2) {
                                done = 1;
                            }
                        }
                    }
                    if (entry->unkA == 0) {
                        done = 1;
                    }
                    i++;
                } while (!done);
                if (arg0->unk60 & 0x20000000) {
                    D_807FBB70.unk200 = 1;
                }
                if (D_807FBB70.unk200 == 6 || D_807FBB70.unk200 == 7) {
                    actorApplyDamage((struct Beh798_Actor *)arg0, (struct Beh798_Actor *)temp_s2);
                }
                func_80675AFC((void *)arg0, (void *)temp_s2);
            }
        }
    }
}

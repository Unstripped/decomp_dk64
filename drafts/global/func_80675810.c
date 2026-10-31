// func_80675810 (src/global/7A510.c): W3A stage 6, 2-insn text diff: missing post-loop re-materialisation 'lui s0; addiu s0,s0,D_807FBB70' (target holds a SEPARATE piece of the lda web after the loop; ours keeps one s0 web through loop+post-loop) and the following 'move a0,s3' placement. Loop body matches since D_807FBB70.unk200 = ((u8 *)res)[i * 12 + 8] (not entry->unk8: a const-offset global store whose RHS ilod is CSE-equal to an earlier IV-pointer load becomes a var-form store = 'lui at; sb 512(at)'; a differently-shaped address avoids it). Tried for the split: loop shape, post-loop spellings, locals/types, callee void/s32, dead if/goto-label/&D reads, permuter 500s, deadsweep (no gain). A label or if (0) {} between the post-loop store-if and compare-if splits the web but gives lui v1 for the compare only; with a split before the store IV/i swap regs (lda adjsave 11.2 < IV 11.22).
typedef struct W2Col_ActorSub174_810 {
    u8 pad0[0xD4];
    s16 unkD4;
} W2Col_ActorSub174_810;

typedef struct W2Col_Actor810 {
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
    struct W2Col_Actor810 *unk11C;
    u8 pad120[0x12];
    s16 unk132;
    s16 unk134;
    s16 unk136;
    u8 pad138[0x3C];
    W2Col_ActorSub174_810 *unk174;
} W2Col_Actor810;

typedef struct W2Col_Arg1_Elem {
    u8 pad0[0x18];
    s32 unk18;
} W2Col_Arg1_Elem;

typedef struct W2Col_Arg1 {
    u8 pad0[0x8];
    W2Col_Actor810 *unk8;
    u8 padC[4];
    W2Col_Arg1_Elem *unk10;
} W2Col_Arg1;

typedef struct W2Col_80675810_Entry {
    s16 unk0;
    s16 unk2;
    s32 (*unk4)(W2Col_Actor810 *, W2Col_Actor810 *, W2Col_Arg1 *);
    u8 unk8;
    u8 unk9;
    u8 unkA;
    u8 unkB;
} W2Col_80675810_Entry;

struct CollisionTableEntry;
struct Beh798_Actor;
typedef struct W2Col_8074C604 {
    struct CollisionTableEntry *unk0;
    u8 pad4[4];
} W2Col_8074C604;

extern W2Col_8074C604 D_8074C604[];
struct Beh798_8074C608;
extern struct Beh798_8074C608 D_8074C608[];
extern ActorGlobalState D_807FBB70;

s32 actorTableContains(void *);
void func_80675D70(s32);
s32 actorCollisionFindTableEntry(struct CollisionTableEntry *, s16, s16);
s32 func_80676220(s16);
void actorApplyDamage(struct Beh798_Actor *, struct Beh798_Actor *);
void func_80675AFC();

void func_80675810(W2Col_Actor810 *arg0, W2Col_Arg1 *arg1) {
    W2Col_80675810_Entry *entry;
    s32 done;
    W2Col_Actor810 *temp_s2;
    s32 res;
    struct CollisionTableEntry *entries;
    u8 var_v1;
    s32 i;
    W2Col_ActorSub174_810 *sub;
    u8 tv0;
    u8 tv1;

    temp_s2 = arg1->unk8;
    i = 0;
    done = 0;
    if (actorTableContains(temp_s2) && temp_s2->unk54 == arg1->unk10->unk18) {
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
                    entry = &((W2Col_80675810_Entry *)res)[i];
                    if ((entry->unk0 & arg0->unk132) && (entry->unk2 & temp_s2->unk132)) {
                        if (D_8074C604) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                        if (entry->unk4 != NULL) {
                            var_v1 = entry->unk4(arg0, temp_s2, arg1);
                        } else {
                            var_v1 = 1;
                        }
                        if (var_v1) {
                            tv0 = entry->unk8;
                            tv1 = D_807FBB70.unk200;
                            if (tv1 < tv0) {
                                D_807FBB70.unk1FC = (s32)temp_s2;
                                D_807FBB70.unk200 = ((u8 *)res)[i * 12 + 8];
                            }
                            if (D_807FBB70.unk201 < 0xF) {
                                D_807FBB70.unk204[D_807FBB70.unk201] = (s32)temp_s2;
                                D_807FBB70.unk244[D_807FBB70.unk201] = entry->unk9;
                                D_807FBB70.unk201++;
                                if (temp_s2->unk5C & 1) {
                                    sub = temp_s2->unk174;
                                    if (sub->unkD4 != 0) {
                                        if (((u8 *)D_8074C608)[arg0->unk58 * 8] != 0) {
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

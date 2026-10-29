// func_80675810 (src/global/7A510.c): stage 5: matches control flow and frame 0x30, remaining diff regalloc and D_807FBB70 / loop index reuse
typedef struct KaC1_ActorSub174_810 {
    u8 pad0[0xD4];
    s16 unkD4;
} KaC1_ActorSub174_810;

typedef struct KaC1_Actor810 {
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
    struct KaC1_Actor810 *unk11C;
    u8 pad120[0x12];
    s16 unk132;
    s16 unk134;
    s16 unk136;
    u8 pad138[0x3C];
    KaC1_ActorSub174_810 *unk174;
} KaC1_Actor810;

typedef struct KaC1_Arg1_Elem {
    u8 pad0[0x18];
    s32 unk18;
} KaC1_Arg1_Elem;

typedef struct KaC1_Arg1 {
    u8 pad0[0x8];
    KaC1_Actor810 *unk8;
    u8 padC[4];
    KaC1_Arg1_Elem *unk10;
} KaC1_Arg1;

typedef struct KaC1_80675810_Entry {
    s16 unk0;
    s16 unk2;
    s32 (*unk4)(KaC1_Actor810 *, KaC1_Actor810 *, KaC1_Arg1 *);
    u8 unk8;
    u8 unk9;
    u8 unkA;
    u8 unkB;
} KaC1_80675810_Entry;

typedef struct KaC1_Entry {
    s16 unk0;
    s32 unk4;
} KaC1_Entry;

typedef struct KaC1_8074C604 {
    KaC1_Entry *unk0;
    u8 pad4[4];
} KaC1_8074C604;

typedef struct Beh798_8074C608 {
    u8 unk0;
    u8 pad[7];
} Beh798_8074C608;

struct Beh798_Actor;
struct KaC1_ActorAFC;

extern KaC1_8074C604 D_8074C604[];
extern Beh798_8074C608 D_8074C608[];
extern ActorGlobalState D_807FBB70;

s32 actorTableContains(void *);
void func_80675D70(s32);
s32 func_80675E3C(KaC1_Entry *, s16, s16);
s32 func_80676220(s16);
void actorApplyDamage(struct Beh798_Actor *, struct Beh798_Actor *);
void func_80675AFC(struct KaC1_ActorAFC *, struct KaC1_ActorAFC *);

void func_80675810(KaC1_Actor810 *arg0, KaC1_Arg1 *arg1) {
    ActorGlobalState *state;
    KaC1_80675810_Entry *entry;
    s32 done;
    KaC1_Actor810 *temp_s2;
    s32 res;
    KaC1_Entry *entries;
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
            res = func_80675E3C(entries, temp_s2->unk5A, temp_s2->unk5C);
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
                state = &D_807FBB70;
                entry = &((KaC1_80675810_Entry *)res)[i];
                do {
                    if ((entry->unk0 & arg0->unk132) && (entry->unk2 & temp_s2->unk132)) {
                        var_v1 = 1;
                        if (entry->unk4 != NULL) {
                            var_v1 = entry->unk4(arg0, temp_s2, arg1);
                        }
                        if (var_v1) {
                            if (state->unk200 < entry->unk8) {
                                state->unk1FC = (s32)temp_s2;
                                state->unk200 = entry->unk8;
                            }
                            if (state->unk201 < 0xF) {
                                state->unk204[state->unk201] = (s32)temp_s2;
                                state->unk244[state->unk201] = entry->unk9;
                                state->unk201++;
                                if (temp_s2->unk5C & 1) {
                                    if (temp_s2->unk174->unkD4 != 0) {
                                        if (D_8074C608[arg0->unk58].unk0 != 0) {
                                            u8 t = state->unk244[state->unk201 - 1];
                                            if (t == 5 || t == 0xF) {
                                                state->unk201--;
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
                    entry++;
                } while (!done);
                if (arg0->unk60 & 0x20000000) {
                    state->unk200 = 1;
                }
                if (state->unk200 == 6 || state->unk200 == 7) {
                    actorApplyDamage((struct Beh798_Actor *)arg0, (struct Beh798_Actor *)temp_s2);
                }
                func_80675AFC((struct KaC1_ActorAFC *)arg0, (struct KaC1_ActorAFC *)temp_s2);
            }
        }
    }
}

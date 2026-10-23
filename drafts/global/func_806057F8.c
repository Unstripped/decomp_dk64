// func_806057F8 (src/global/7130.c): from .scratch/Aud7130L3/func_806057F8_best.c

typedef struct Aud7130L3_SubActor {
    char pad0[0x90];
    f32 unk90;
    char pad94[0x66];
    u8 unkFA;
} Aud7130L3_SubActor;

typedef struct Aud7130L3_SubActorWrap {
    char pad0[0x174];
    Aud7130L3_SubActor *unk174;
} Aud7130L3_SubActorWrap;

typedef struct Aud7130L3_PlayerCtx {
    char pad0[0x104];
    Aud7130L3_SubActorWrap *unk104;
} Aud7130L3_PlayerCtx;

typedef struct Aud7130L3_AudPlayerWrap {
    char pad0[0x174];
    Aud7130L3_PlayerCtx *unk174;
} Aud7130L3_AudPlayerWrap;

typedef struct Aud7130L3_CollisionSubNode {
    char pad0[0x10];
    s16 unk10;
    s16 unk12;
} Aud7130L3_CollisionSubNode;

typedef struct Aud7130L3_CollisionModel {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    char padC[0x70];
    Aud7130L3_CollisionSubNode *unk7C;
    char pad80[0x10];
} Aud7130L3_CollisionModel;

typedef struct Aud7130L3_Actor {
    char pad0[4];
    void *unk4;
    char pad8[0x50];
    s32 unk58;
    char pad5C[0x16];
    s16 unk72;
    s16 unk74;
    char pad76[6];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0x1C];
    f32 unkA4;
    char padA8[0x10];
    f32 unkB8;
    char padBC[0x2A];
    s16 unkE6;
    char padE8[0x4C];
    s16 unk134;
} Aud7130L3_Actor;

struct Aud7130B_Struct807F6000;
extern struct Aud7130B_Struct807F6000 *D_807F6000;
extern Aud7130L3_PlayerCtx *D_807FD580;
extern s32 D_8076D1F8;
extern s32 D_8076D1FC;
extern s32 D_807FBB60;
extern f32 D_80770688[];
extern f32 D_80770DE4;
extern f32 D_80770F38;
extern f32 D_80770590;
extern f32 D_80770594;
extern u8 D_807FC928;

void actorGetNodePos(Actor *, s8, f32 *, f32 *, f32 *);
void func_80602B60();
f32 func_80603340(f32, f32, f32, u8, u8, f32);
void func_806049CC(s32);
void func_80605314(Actor *, u8);
void func_80605380(s16);
s16 func_80609140(s16, s32, f32, f32, u8, u8);
u32 func_806119A0(void);
f32 func_80612790(s16);
f32 func_80612794(s16);
f32 func_80612D1C(f32);
void func_806335B0(s16, s32, s8, f32 *, f32 *, f32 *);
void func_80650D8C(s16, s32, s16 *, void *, void *);
s32 func_80659470(s16);
void func_80737AC4(s32, s32, ...);
void n_alSndpAllocate(s32, s16, s32, s32, f32, s32, s32 *);
void n_alSndpDeallocate(s32);

void func_806057F8(void) {
    extern struct Aud7130B_Struct807F6000 *D_807F6000;
    extern u8 D_807FC928;
    f32 sp158;
    f32 sp154;
    f32 sp150;
    f32 spF8[22];
    f32 spF4;
    f32 spF0;
    u8 spE6;
    s16 spE4;
    s32 spD0;
    s16 spCE;
    u8 spC8;
    u8 spC7;
    s32 spB8;
    s16 *spB4;
    s32 spB0;
    s32 sp9C;
    s32 *sp98;
    f32 var_fs0;
    f32 var_fs2;
    f32 var_ft4;
    f32 var_fa0;
    f32 var_fv1;
    Aud7130L3_Actor *var_s4;
    s32 var_s6;
    s32 var_s2;
    s32 var_s1;

    var_s4 = NULL;
    var_s6 = 0;
    do {
        spB8 = var_s6 * 2;
        spB4 = &D_80770710[var_s6];
        spB0 = *spB4;
        if (spB0 == 0x88) {
            D_80770DE8 = 0.0f;
            D_80770DEC = 0.0f;
            D_80770DF0 = 0.0f;
            var_s2 = D_80770740[var_s6] - 1;
            D_80770DF4 = 0.0f;
            spE6 = 0;
            if (var_s2 >= 0) {
                do {
                    s16 ent = D_807707A0[var_s6][var_s2];
                    spD0 = func_80659470(D_807705F8[ent]);
                    func_80603340(((Aud7130L3_CollisionModel *)D_807F6000)[spD0].unk0, ((Aud7130L3_CollisionModel *)D_807F6000)[spD0].unk4, ((Aud7130L3_CollisionModel *)D_807F6000)[spD0].unk8, 0xFF, 0x50, 0.5f);
                    spF8[var_s2] = D_80770DE4;
                    func_80605380(ent);
                    var_s2--;
                    ((Aud7130L3_CollisionModel *)D_807F6000)[spD0].unk7C->unk12 = -1;
                } while (var_s2 >= 0);
            }
            if (D_80770DE8 > 32767.0f) {
                D_80770DE8 = 32767.0f;
            }
            if (D_80770DEC > 32767.0f) {
                D_80770DEC = 32767.0f;
            }
            var_fs2 = D_80770DE8 + D_80770DEC;
            if (D_80770DEC < D_80770DE8) {
                if (D_80770DE8 > 0.0f) {
                    D_80770DDC = (f32)(127.0 - (((f64)D_80770DEC * 63.5) / (f64)D_80770DE8));
                } else {
                    D_80770DDC = 0.0f;
                }
            } else if (D_80770DEC > 0.0f) {
                D_80770DDC = (f32)(((f64)D_80770DE8 * 63.5) / (f64)D_80770DEC);
            } else {
                D_80770DDC = 0.0f;
            }
            if (var_fs2 > 32767.0f) {
                var_fs2 = 32767.0f;
            }
            if (var_fs2 < 0.0f) {
                var_fs2 = 0.0f;
            }
            if (D_80770DF0 < D_80770DF4) {
                spE6 = 0x80;
            }
            func_80609140(0x88, (s32)var_fs2, D_80770DDC, 1.0f, 5, spE6);
        } else {
            sp9C = var_s6 * 4;
            sp98 = &D_80745848[var_s6];
            var_s1 = *sp98;
            if (var_s1 != 0) {
                if (spB0 == 0) {
                    if (D_807706E0[var_s6] != 0) {
                        D_807706E0[var_s6]--;
                    } else {
                        n_alSndpDeallocate(var_s1);
                        D_80770770[var_s6] = 0;
                        D_807706E0[var_s6] = 10;
                        var_s1 = *sp98;
                    }
                }
            } else if (spB0 != 0) {
                if (spB0 == 0x128 || spB0 == 0x306) {
                    if (D_80770CC8[var_s6] == 0) {
                        n_alSndpAllocate(D_8076D1F8, (s16)spB0, 0, 0x3F, D_80770C18[var_s6], 0, sp98);
                        D_80770CC8[var_s6] = 1;
                    } else {
                        func_80605314(D_807705A0[((u8 *)D_807707A0)[var_s6 * 44 + 1]], 0);
                    }
                    var_s1 = *sp98;
                } else if (spB0 < 0x800) {
                    n_alSndpAllocate(D_8076D1F8, (s16)spB0, 0, 0x3F, D_80770C18[var_s6], 0, sp98);
                    var_s1 = *sp98;
                } else {
                    n_alSndpAllocate(D_8076D1FC, (s16)(spB0 - 0x7FF), 0, 0x3F, D_80770C18[var_s6], 0, sp98);
                    var_s1 = *sp98;
                }
            }
            if (var_s1 != 0) {
                s16 actor_idx = D_807707A0[var_s6][0];
                if (actor_idx != -1 && (D_807705A0[actor_idx] != NULL || D_807705F8[actor_idx] != -1)) {
                    D_80770DE8 = 0.0f;
                    D_80770DEC = 0.0f;
                    spE4 = 0;
                    var_s2 = 0;
                    spB0 = *spB4;
                    if (spB0 >= 0xFD && spB0 < 0x142) {
                        var_fs0 = (f32)D_807460AE[spB0][1];
                    } else {
                        var_fs0 = 0.3f;
                    }
                    if (D_80770740[var_s6] > 0) {
                        do {
                            if (D_807705F8[D_807707A0[var_s6][0]] != -1) {
                                var_s4 = NULL;
                                if (*spB4 == 0x12B) {
                                    s16 ent = D_807707A0[var_s6][var_s2];
                                    spD0 = func_80659470(D_807705F8[ent]);
                                    func_80603340(((Aud7130L3_CollisionModel *)D_807F6000)[spD0].unk0, ((Aud7130L3_CollisionModel *)D_807F6000)[spD0].unk4 + 320.0f, ((Aud7130L3_CollisionModel *)D_807F6000)[spD0].unk8, 0xFF, D_80770788[ent], var_fs0);
                                } else {
                                    s8 unk = D_80770CF8[var_s6];
                                    if (unk > 0) {
                                        s16 ent = D_807707A0[var_s6][var_s2];
                                        func_806335B0(D_807705F8[ent], 1, unk, &sp158, &sp154, &sp150);
                                        func_80603340(sp158, sp154, sp150, 0xFF, D_80770788[ent], var_fs0);
                                    } else if (unk < 0) {
                                        D_80770DE8 = 32767.0f;
                                        D_80770DEC = 32767.0f;
                                        D_80770DF0 = 32767.0f;
                                        D_80770DF4 = 32767.0f;
                                    } else {
                                        s16 ent = D_807707A0[var_s6][var_s2];
                                        spD0 = func_80659470(D_807705F8[ent]);
                                        func_80603340(((Aud7130L3_CollisionModel *)D_807F6000)[spD0].unk0, ((Aud7130L3_CollisionModel *)D_807F6000)[spD0].unk4, ((Aud7130L3_CollisionModel *)D_807F6000)[spD0].unk8, 0xFF, D_80770788[ent], var_fs0);
                                    }
                                }
                            } else {
                                s16 ent = D_807707A0[var_s6][var_s2];
                                s8 unk = D_80770CF8[var_s6];
                                var_s4 = (Aud7130L3_Actor *)D_807705A0[ent];
                                if (unk > 0) {
                                    actorGetNodePos((Actor *)var_s4, unk, &sp158, &sp154, &sp150);
                                    func_80603340(sp158, sp154, sp150, 0xFF, D_80770788[ent], var_fs0);
                                } else if (unk < 0) {
                                    D_80770DE8 = 32767.0f;
                                    D_80770DEC = 32767.0f;
                                    D_80770DF0 = 32767.0f;
                                    D_80770DF4 = 32767.0f;
                                } else if (*spB4 == 0x139 && D_807706F8[var_s6] != 0) {
                                    sp154 = var_s4->unk80;
                                    sp158 = var_s4->unk7C;
                                    sp150 = var_s4->unk84;
                                    func_80603340(sp158, sp154, sp150, 0xFF, D_80770788[ent], var_fs0);
                                    sp158 = (f32)(((f64)func_80612790(var_s4->unkE6) * 300.0) + (f64)var_s4->unk7C);
                                    sp150 = (f32)((f64)var_s4->unk84 - ((f64)func_80612794(var_s4->unkE6) * 300.0));
                                    func_80603340(sp158, sp154, sp150, 0xFF, D_80770788[ent], var_fs0);
                                    sp158 = (f32)((f64)var_s4->unk7C - ((f64)func_80612790(var_s4->unkE6) * 300.0));
                                    sp150 = (f32)(((f64)func_80612794(var_s4->unkE6) * 300.0) + (f64)var_s4->unk84);
                                    func_80603340(sp158, sp154, sp150, 0xFF, D_80770788[ent], var_fs0);
                                } else {
                                    func_80603340(var_s4->unk7C, var_s4->unk80, var_s4->unk84, 0xFF, D_80770788[ent], var_fs0);
                                }
                            }
                            spF8[var_s2] = D_80770DE4;
                            var_s2++;
                        } while (var_s2 < D_80770740[var_s6]);
                        spB0 = *spB4;
                    }
                    if (D_80770DE8 > 32767.0f) {
                        D_80770DE8 = 32767.0f;
                    }
                    if (D_80770DEC > 32767.0f) {
                        D_80770DEC = 32767.0f;
                    }
                    var_fs2 = D_80770DE8 + D_80770DEC;
                    if (D_80770DEC < D_80770DE8) {
                        if (D_80770DE8 > 0.0f) {
                            D_80770DDC = (f32)(127.0 - (((f64)D_80770DEC * 63.5) / (f64)D_80770DE8));
                        } else {
                            D_80770DDC = 0.0f;
                        }
                    } else if (D_80770DEC > 0.0f) {
                        D_80770DDC = (f32)(((f64)D_80770DE8 * 63.5) / (f64)D_80770DEC);
                    } else {
                        D_80770DDC = 0.0f;
                    }
                    if (var_fs2 > 32767.0f) {
                        var_fs2 = 32767.0f;
                    }
                    if (var_fs2 < 0.0f) {
                        var_fs2 = 0.0f;
                    }
                    var_fs2 = (f32)((f64)var_fs2 * ((f64)D_80770CE0[var_s6] / 255.0));
                    if ((D_807FBB60 & 2) || !(D_807FBB60 & 0x10)) {
                        var_fs2 = 0.0f;
                    } else {
                        switch (spB0) {
                        case 0x12F:
                            var_fs2 = (f32)((f64)var_fs2 * ((f64)D_80770BC0[var_s6] / 9.0));
                            spE4 = (s16)(s32)((f64)D_80770BC0[var_s6] * 1.3);
                            break;
                        case 0x12B:
                            func_80650D8C((s16)spD0, 1, &spCE, &spC8, &spC7);
                            var_fs0 = func_80612D1C((f32)(((f64)spCE / 27.0) * 3.1415927410125732));
                            var_fs2 *= var_fs0;
                            D_80770B68[var_s6] = var_fs0;
                            D_80770C18[var_s6] = (f32)(((f64)var_fs0 * 0.4) + 0.8);
                            spB0 = *spB4;
                            break;
                        case 0x113:
                            if (D_80770B68[var_s6] == 0.0f) {
                                var_fs2 = 0.0f;
                            } else {
                                D_80770C18[var_s6] = D_80770B68[var_s6];
                            }
                            break;
                        case 0x111:
                            D_80770BC0[var_s6] += 1.0f;
                            if (D_80770BC0[var_s6] > 30.0f) {
                                D_80770C18[var_s6] = (f32)(1.0 - (((f64)D_80770BC0[var_s6] - 30.0) / 30.0));
                            }
                            if (D_80770BC0[var_s6] == 40.0f) {
                                func_80605380(D_807707A0[var_s6][0]);
                                ((Aud7130L3_CollisionModel *)D_807F6000)[spD0].unk7C->unk10 = -1;
                                spB0 = *spB4;
                            }
                            break;
                        case 0x11F:
                            if (D_807706F8[var_s6] != 0) {
                                f32 s_temp = func_80612D1C((f32)((f64)D_80770BC0[var_s6] * 0.027925));
                                D_80770C18[var_s6] = (f32)(((f64)func_80612D1C((f32)(((f64)D_80770BC0[var_s6] * 0.261799) - 1.570795)) * 0.1) + (0.2 * (f64)s_temp) + 0.6);
                                D_80770BC0[var_s6] += 1.0f;
                                if (D_80770788[D_807707A0[var_s6][0]] == 0) {
                                    D_80770DDC = 63.0f;
                                    D_80770DF4 = 100.0f;
                                    D_80770DF0 = 0.0f;
                                }
                            } else {
                                f32 s_temp = func_80612D1C((f32)((f64)D_80770BC0[var_s6] * 0.027925));
                                f32 cur_bc0 = D_80770BC0[var_s6];
                                D_80770C18[var_s6] = (f32)(((f64)func_80612D1C((f32)(((f64)cur_bc0 * 0.261799) - 1.570795)) * 0.1) + (0.5 * (f64)s_temp) + 0.6);
                                var_fa0 = (f32)(1.0 - (((f64)cur_bc0 - 90.0) / 20.0));
                                D_80770B68[var_s6] = var_fa0;
                                if (var_fa0 > 1.0f) {
                                    D_80770B68[var_s6] = 1.0f;
                                }
                                if (D_80770B68[var_s6] < 0.0f) {
                                    D_80770B68[var_s6] = 0.0f;
                                }
                                var_fs0 = var_fs2 * D_80770B68[var_s6];
                                D_80770B68[var_s6] = cur_bc0 / 20.0f;
                                if (D_80770B68[var_s6] >= 1.0f) {
                                    D_80770B68[var_s6] = 1.0f;
                                }
                                D_80770BC0[var_s6] = cur_bc0 + 1.0f;
                                var_fs2 = var_fs0 * D_80770B68[var_s6];
                                if ((f64)D_80770C18[var_s6] <= 0.2) {
                                    D_80770C18[var_s6] = 0.2f;
                                }
                                if (D_80770BC0[var_s6] == 110.0f) {
                                    s16 first_ent = D_807707A0[var_s6][0];
                                    if (D_807705F8[first_ent] != -1) {
                                        func_80605380(first_ent);
                                        ((Aud7130L3_CollisionModel *)D_807F6000)[spD0].unk7C->unk10 = -1;
                                    } else {
                                        func_80605314((Actor *)var_s4, 0);
                                        func_80602B60(0x3B, 0);
                                    }
                                }
                            }
                            spB0 = *spB4;
                            break;
                        case 0x131:
                            if (var_s4->unk58 == 0xB9) {
                                D_80770770[var_s6] = 8;
                                D_80770C18[var_s6] = (f32)(((f64)var_s4->unk72 / 80.0) + 1.0);
                                var_fs2 *= 1.0f / D_80770C18[var_s6];
                            } else {
                                s32 best_idx = 0;
                                D_80770B68[var_s6] = 0.0f;
                                D_80770C18[var_s6] = 200.0f;
                                if (D_80770740[var_s6] > 0) {
                                    do {
                                        Aud7130L3_Actor *a = (Aud7130L3_Actor *)D_807705A0[D_807707A0[var_s6][best_idx]];
                                        if ((f32)a->unk72 < D_80770C18[var_s6]) {
                                            D_80770C18[var_s6] = (f32)a->unk72;
                                            D_80770B68[var_s6] = (f32)best_idx;
                                        }
                                        best_idx++;
                                    } while (best_idx < D_80770740[var_s6]);
                                }
                                {
                                    Aud7130L3_Actor *a = (Aud7130L3_Actor *)D_807705A0[D_807707A0[var_s6][(s16)(s32)D_80770B68[var_s6]]];
                                    s32 diff = a->unk72 - 0x78;
                                    s32 abs_diff = (diff > 0) ? diff : -diff;
                                    D_80770C18[var_s6] = (f32)(2.0 - ((f64)abs_diff / 120.0));
                                    if ((f64)D_80770C18[var_s6] <= 0.2) {
                                        D_80770C18[var_s6] = 0.2f;
                                    }
                                    D_80770B68[var_s6] = (f32)((f64)a->unk74 / 20.0);
                                    if (D_80770B68[var_s6] > 1.0f) {
                                        D_80770B68[var_s6] = 1.0f;
                                    }
                                    if (D_80770B68[var_s6] < 0.0f) {
                                        D_80770B68[var_s6] = 0.0f;
                                    }
                                    var_fs2 *= D_80770B68[var_s6];
                                }
                            }
                            break;
                        case 0x10E:
                            if (var_s4->unk58 == 0x139) {
                                if (D_80770BC0[var_s6] <= 0.0f) {
                                    D_80770BC0[var_s6] = (f32)((((f64)(u32)func_806119A0() / 4294967295.0) * 2.0) + 2.0);
                                    D_80770B68[var_s6] = (f32)(((0.925 + (0.15 * ((f64)(u32)func_806119A0() / 4294967295.0))) - (f64)D_80770C18[var_s6]) / (f64)D_80770BC0[var_s6]);
                                    spB0 = *spB4;
                                } else {
                                    D_80770BC0[var_s6] -= 1.0f;
                                }
                                var_fs2 = (f32)((f64)var_fs2 * 0.5);
                                break;
                            }
                            if (var_s4->unk58 == 2) {
                                if (D_80770BC0[var_s6] <= 0.0f) {
                                    D_80770BC0[var_s6] = (f32)((((f64)(u32)func_806119A0() / 4294967295.0) * 2.0) + 2.0);
                                    D_80770B68[var_s6] = (f32)(((1.2 + (0.15 * ((f64)(u32)func_806119A0() / 4294967295.0))) - (f64)D_80770C18[var_s6]) / (f64)D_80770BC0[var_s6]);
                                    spB0 = *spB4;
                                } else {
                                    D_80770BC0[var_s6] -= 1.0f;
                                }
                                spE4 = 0xE;
                                var_fs2 = (f32)((f64)var_fs2 * 0.9);
                                break;
                            }
                            /* fallthrough */
                        case 0x108:
                        case 0x10F:
                            if (D_80770BC0[var_s6] <= 0.0f) {
                                D_80770BC0[var_s6] -= 1.0f;
                                if (spB0 == 0x108) {
                                    s16 u134 = var_s4->unk134;
                                    if (u134 != 0 && u134 != 1) {
                                        if (u134 != 2) {
                                            if (u134 == 3) {
                                                D_80770BC0[var_s6] = (f32)((((f64)(u32)func_806119A0() / 4294967295.0) * 2.0) + 3.0);
                                                D_80770B68[var_s6] = (f32)(((0.95 + (0.1 * ((f64)(u32)func_806119A0() / 4294967295.0))) - (f64)D_80770C18[var_s6]) / (f64)D_80770BC0[var_s6]);
                                                spB0 = *spB4;
                                            }
                                        } else {
                                            D_80770BC0[var_s6] = (f32)((((f64)(u32)func_806119A0() / 4294967295.0) * 2.0) + 2.0);
                                            D_80770B68[var_s6] = (f32)(((0.85 + (0.5 * ((f64)(u32)func_806119A0() / 4294967295.0))) - (f64)D_80770C18[var_s6]) / (f64)D_80770BC0[var_s6]);
                                            spB0 = *spB4;
                                        }
                                    } else {
                                        D_80770BC0[var_s6] = (f32)((((f64)(u32)func_806119A0() / 4294967295.0) * 1.0) + 2.0);
                                        D_80770B68[var_s6] = (f32)(((0.9 + (0.5 * ((f64)(u32)func_806119A0() / 4294967295.0))) - (f64)D_80770C18[var_s6]) / (f64)D_80770BC0[var_s6]);
                                        spB0 = *spB4;
                                    }
                                } else {
                                    D_80770BC0[var_s6] = (f32)((((f64)(u32)func_806119A0() / 4294967295.0) * 2.0) + 2.0);
                                    D_80770B68[var_s6] = (f32)(((((f64)D_80770C70[var_s6] - 0.075) + (0.15 * ((f64)(u32)func_806119A0() / 4294967295.0))) - (f64)D_80770C18[var_s6]) / (f64)D_80770BC0[var_s6]);
                                    spB0 = *spB4;
                                }
                            } else {
                                D_80770BC0[var_s6] -= 1.0f;
                            }
                            D_80770C18[var_s6] += D_80770B68[var_s6];
                            if (D_80770740[var_s6] >= 2) {
                                var_fa0 = 10000.0f;
                                var_s2 = 0;
                                var_fv1 = 10000.0f;
                                if (D_80770740[var_s6] > 0) {
                                    do {
                                        f32 dist = spF8[var_s2++];
                                        if (dist < var_fv1) {
                                            var_fa0 = var_fv1;
                                            var_fv1 = dist;
                                        } else if (dist < var_fa0) {
                                            var_fa0 = dist;
                                        }
                                    } while (var_s2 < D_80770740[var_s6]);
                                }
                                spF0 = var_fv1;
                                spF4 = var_fa0;
                                spE4 = (s16)(s32)(14.0 - ((f64)(var_fa0 - var_fv1) / 20.0));
                                if (spE4 < 0) {
                                    spE4 = 0;
                                }
                                D_80770DDC = (f32)((((f64)D_80770DDC - 63.5) * (1.0 + ((f64)spE4 / 15.0))) + 63.5);
                                if (D_80770DDC > 127.0f) {
                                    D_80770DDC = 127.0f;
                                }
                                if (D_80770DDC < 0.0f) {
                                    D_80770DDC = 0.0f;
                                }
                            }
                            if (spE4 != D_80770770[var_s6]) {
                                D_80770770[var_s6] = (u8)spE4;
                            }
                            break;
                        case 0x104:
                            if (D_80770BC0[var_s6] < 30.0f) {
                                D_80770BC0[var_s6] += 1.0f;
                                D_80770C18[var_s6] = (f32)((f64)D_80770C18[var_s6] * 1.02);
                            }
                            break;
                        case 0x118:
                            if (var_s4->unk58 != 0x139) {
                                if (D_80770BC0[var_s6] >= 2.0f) {
                                    D_80770BC0[var_s6] += 1.0f;
                                    D_80770BC0[var_s6] = (f32)(u32)func_806119A0();
                                    if (D_80770DF0 < D_80770DF4) {
                                        spE6 |= 0x80;
                                    }
                                    func_80609140((s16)((func_806119A0() & 3) + 0x90), (s32)var_fs2, D_80770DDC, 1.0f, 0x1E, (s32)spE6);
                                    D_80770BC0[var_s6] = 0.0f;
                                    spB0 = *spB4;
                                } else {
                                    D_80770BC0[var_s6] += 1.0f;
                                }
                            }
                            D_80770C18[var_s6] = (f32)((f64)D_80770C18[var_s6] * 0.99);
                            break;
                        case 0x219:
                            if (D_80770BC0[var_s6] <= 0.0f) {
                                D_80770BC0[var_s6] = (f32)((((f64)(u32)func_806119A0() / 4294967295.0) * 6.0) + 2.0);
                                D_80770B68[var_s6] = (f32)(((0.84089 + (0.21857 * ((f64)(u32)func_806119A0() / 4294967295.0))) - (f64)D_80770C18[var_s6]) / (f64)D_80770BC0[var_s6]);
                                spB0 = *spB4;
                            } else {
                                D_80770BC0[var_s6] -= 1.0f;
                            }
                            D_80770C18[var_s6] += D_80770B68[var_s6];
                            break;
                        case 0x132:
                            if (D_80770BC0[var_s6] <= 0.0f) {
                                D_80770BC0[var_s6] = (f32)((((f64)(u32)func_806119A0() / 4294967295.0) * 6.0) + 2.0);
                                D_80770B68[var_s6] = (f32)(((0.8 + (0.2 * ((f64)(u32)func_806119A0() / 4294967295.0))) - (f64)D_80770C18[var_s6]) / (f64)D_80770BC0[var_s6]);
                                spB0 = *spB4;
                            } else {
                                D_80770BC0[var_s6] -= 1.0f;
                            }
                            D_80770C18[var_s6] += D_80770B68[var_s6];
                            break;
                        case 0x116:
                            if (D_80770BC0[var_s6] > 0.0f) {
                                f32 temp_fa1 = D_80770C18[var_s6];
                                D_80770BC0[var_s6] -= 1.0f;
                                D_80770C18[var_s6] = temp_fa1 + ((D_80770B68[var_s6] - temp_fa1) / D_80770BC0[var_s6]);
                            }
                            D_80770DE8 = (f32)(2.0 * ((f64)D_80770C18[var_s6] - 0.2));
                            if ((f64)D_80770DE8 > 1.0) {
                                D_80770DE8 = 1.0f;
                            }
                            if (D_80770DE8 < 0.0f) {
                                D_80770DE8 = 0.0f;
                            }
                            var_fs2 *= D_80770DE8;
                            break;
                        case 0x107:
                        case 0x12E:
                            if (D_80770BC0[var_s6] > 0.0f) {
                                f32 temp_fa1 = D_80770C18[var_s6];
                                D_80770BC0[var_s6] -= 1.0f;
                                D_80770C18[var_s6] = temp_fa1 + ((D_80770B68[var_s6] - temp_fa1) / D_80770BC0[var_s6]);
                            }
                            var_fs2 *= (f32)var_s4->unk74;
                            break;
                        case 0x115:
                            if (D_80770BC0[var_s6] > 0.0f) {
                                f32 temp_fa1 = D_80770C18[var_s6];
                                D_80770BC0[var_s6] -= 1.0f;
                                D_80770C18[var_s6] = temp_fa1 + ((D_80770B68[var_s6] - temp_fa1) / D_80770BC0[var_s6]);
                            }
                            D_80770DE8 = (f32)(1.0 - (((f64)D_80770C18[var_s6] - 1.0) * 0.9));
                            if ((f64)D_80770DE8 > 1.0) {
                                D_80770DE8 = 1.0f;
                            }
                            if (D_80770DE8 < 0.0f) {
                                D_80770DE8 = 0.0f;
                            }
                            var_fs2 *= D_80770DE8;
                            break;
                        case 0x12D:
                            if (D_80770BC0[var_s6] > 0.0f) {
                                f32 temp_fa1 = D_80770C18[var_s6];
                                D_80770BC0[var_s6] -= 1.0f;
                                D_80770C18[var_s6] = temp_fa1 + ((D_80770B68[var_s6] - temp_fa1) / D_80770BC0[var_s6]);
                            }
                            D_80770DE8 = (f32)(1.0 - ((f64)(D_80770C18[var_s6] - 1.0f) * 0.9));
                            if ((f64)D_80770DE8 > 1.0) {
                                D_80770DE8 = 1.0f;
                            }
                            if (D_80770DE8 < 0.0f) {
                                D_80770DE8 = 0.0f;
                            }
                            var_fs2 *= D_80770DE8;
                            break;
                        case 0x12C:
                            var_fs2 *= D_80770B68[var_s6];
                            break;
                        case 0x122:
                            D_80770590 = (f32)((f64)var_s4->unkB8 / 600.0);
                            if ((f64)D_80770590 > 0.8) {
                                D_80770590 = 0.8f;
                            }
                            var_fs2 *= D_80770590;
                            break;
                        default:
                            if (D_80770BC0[var_s6] > 0.0f) {
                                f32 temp_fa1 = D_80770C18[var_s6];
                                D_80770BC0[var_s6] -= 1.0f;
                                D_80770C18[var_s6] = temp_fa1 + ((D_80770B68[var_s6] - temp_fa1) / D_80770BC0[var_s6]);
                            }
                            break;
                        }
                    }
                    switch (spB0) {
                    case 0x119:
                        var_ft4 = 1.0f;
                        var_fs2 = D_80770C18[var_s6] * 32767.0f;
                        D_80770DDC = 63.0f;
                        break;
                    case 0xFD:
                    case 0x108:
                    case 0x10E:
                        if (var_s4->unk58 == 0x139) {
                            if (D_80770DE4 < D_80770688[var_s6]) {
                                var_fa0 = D_80770688[var_s6] - D_80770DE4;
                            } else {
                                var_fa0 = -(D_80770688[var_s6] - D_80770DE4);
                            }
                            if (var_fa0 < 20.0f) {
                                f32 f_temp = (f32)(((f64)(D_80770688[var_s6] - D_80770DE4) / 30.0) + 1.0);
                                if ((f64)f_temp > 1.18) {
                                    f_temp = 1.18f;
                                }
                                if ((f64)f_temp < 0.85) {
                                    f_temp = 0.85f;
                                }
                                var_ft4 = D_80770C18[var_s6] * (f_temp * f_temp);
                            } else {
                                var_ft4 = D_80770C18[var_s6];
                            }
                            D_80770688[var_s6] = D_80770DE4;
                            break;
                        }
                        /* fallthrough */
                    case 0x13F:
                    case 0x140:
                    case 0x141:
                        {
                            f32 f_temp = (f32)(((f64)(D_80770688[var_s6] - D_80770DE4) / 900.0) + 1.0);
                            if ((f64)f_temp > 1.18) {
                                f_temp = 1.0f;
                            }
                            if ((f64)f_temp < 0.85) {
                                f_temp = 1.0f;
                            }
                            D_80770688[var_s6] = D_80770DE4;
                            var_ft4 = D_80770C18[var_s6] * (f_temp * f_temp);
                        }
                        break;
                    case 0x107:
                    case 0x10F:
                    case 0x114:
                    case 0x12E:
                    case 0x130:
                        if (D_80770DE4 < D_80770688[var_s6]) {
                            var_fa0 = D_80770688[var_s6] - D_80770DE4;
                        } else {
                            var_fa0 = -(D_80770688[var_s6] - D_80770DE4);
                        }
                        if (var_fa0 < 20.0f) {
                            f32 f_temp = (f32)(((f64)(D_80770688[var_s6] - D_80770DE4) / 100.0) + 1.0);
                            if ((f64)f_temp > 1.18) {
                                f_temp = 1.18f;
                            }
                            if ((f64)f_temp < 0.85) {
                                f_temp = 0.85f;
                            }
                            D_80770688[var_s6] = D_80770DE4;
                            var_ft4 = D_80770C18[var_s6] * (f_temp * f_temp);
                        } else {
                            D_80770688[var_s6] = D_80770DE4;
                            var_ft4 = D_80770C18[var_s6];
                        }
                        break;
                    default:
                        var_ft4 = D_80770C18[var_s6];
                        break;
                    }
                    D_80770F38 = var_ft4;
                    if (spB0 == 0x10D) {
                        if (D_8076A0A8 != 0xE && D_8076A0A8 != 0x52) {
                            f32 cur_fv0 = D_80770590;
                            if (D_80770594 != var_s4->unkB8) {
                                f32 temp_ft3 = (D_80770594 * 32767.0f) / 200.0f;
                                D_80770F38 = temp_ft3;
                                cur_fv0 = (f32)((f64)cur_fv0 + ((f64)(temp_ft3 - cur_fv0) * 0.3));
                                D_80770590 = cur_fv0;
                            } else {
                                if (cur_fv0 > 5000.0f) {
                                    cur_fv0 -= 350.0f;
                                    if (cur_fv0 < 5000.0f) {
                                        cur_fv0 = 5000.0f;
                                    }
                                    D_80770590 = cur_fv0;
                                } else if (cur_fv0 < 5000.0f) {
                                    cur_fv0 += 350.0f;
                                    if (cur_fv0 > 5000.0f) {
                                        cur_fv0 = 5000.0f;
                                    }
                                    D_80770590 = cur_fv0;
                                }
                            }
                            var_fs2 = (f32)((f64)var_fs2 * ((f64)cur_fv0 / 32767.0));
                            if ((var_s4->unk80 - var_s4->unkA4) > 5.0f) {
                                var_fs2 = 0.0f;
                            }
                            D_80770594 = var_s4->unkB8;
                            D_80770F38 = (f32)((f64)(var_s4->unkB8 / 150.0f) + 0.5) * D_80770C18[var_s6];
                        } else {
                            D_80770590 = (f32)((f64)var_s4->unkB8 / 600.0);
                            if ((f64)D_80770590 > 0.8) {
                                D_80770590 = 0.8f;
                            }
                            var_fs2 *= D_80770590;
                            if ((var_s4->unk80 - var_s4->unkA4) > 5.0f) {
                                var_fs2 = 0.0f;
                            }
                            D_80770594 = var_s4->unkB8;
                            D_80770F38 = (f32)((f64)(var_s4->unkB8 / 550.0f) + 0.5);
                        }
                    }
                    if (var_s4 != NULL) {
                        if (var_s4->unk72 != 0 && spB0 != 0x131 && var_s4->unk72 != *(s16 *)((u8 *)*(void **)var_s4->unk4 + 0x10)) {
                            func_80605314((Actor *)var_s4, 0);
                        }
                    }
                    var_ft4 = D_80770F38;
                    if (var_fs2 > 32767.0f) {
                        var_fs2 = 32767.0f;
                    }
                    if (D_80745838 != 0 && (*spB4 == 0x101 || *spB4 == 0x126)) {
                        f32 double_fs2 = var_fs2 * 2.0f;
                        var_ft4 = (f32)((f64)var_ft4 * 0.9);
                        if (double_fs2 > 32767.0f) {
                            var_fs2 = 32767.0f;
                        } else {
                            var_fs2 = double_fs2;
                        }
                    }
                    if (spE4 != 0) {
                        spE6 = spE4 * 8;
                    } else {
                        spE6 = 0;
                    }
                    if (D_80770DF0 < D_80770DF4) {
                        spE6 |= 0x80;
                    }
                    D_80770F38 = var_ft4;
                    if ((f64)var_ft4 < 0.17) {
                        D_80770F38 = 0.17f;
                    }
                    func_80737AC4(*sp98, 0x100, spE6);
                    if (var_fs2 != (f32)D_80770D10[var_s6]) {
                        if (D_80770D10[var_s6] != -1) {
                            if ((f32)D_80770D10[var_s6] < var_fs2) {
                                f32 ramp = (f32)(D_80770D10[var_s6] + 0x1F40);
                                if (ramp < var_fs2) {
                                    var_fs2 = ramp;
                                }
                            } else {
                                f32 ramp = (f32)(D_80770D10[var_s6] - 0x1F40);
                                if (var_fs2 < ramp) {
                                    var_fs2 = ramp;
                                }
                            }
                        }
                        D_80770D10[var_s6] = (s16)(s32)var_fs2;
                        func_80737AC4(*sp98, 8, (u8)(s32)var_fs2);
                    }
                    var_fa0 = (s16)(s32)D_80770DDC;
                    if ((s16)(s32)D_80770DDC != D_80770D40[var_s6]) {
                        if (D_80770D40[var_s6] != -1) {
                            s16 cur_d40 = D_80770D40[var_s6];
                            if (cur_d40 < (s16)(s32)D_80770DDC) {
                                s16 step = cur_d40 + 8;
                                if (step < (s16)(s32)D_80770DDC) {
                                    var_fa0 = step;
                                }
                            } else if (var_fa0 < cur_d40 - 8) {
                                var_fa0 = cur_d40 - 8;
                            }
                        }
                        D_80770D40[var_s6] = (s16)var_fa0;
                        func_80737AC4(*sp98, 4, (u8)(s16)var_fa0);
                    }
                    if (D_80770F38 != D_80770D70[var_s6]) {
                        D_80770D70[var_s6] = D_80770F38;
                        func_80737AC4(*sp98, 0x10, *(s32 *)&D_80770F38);
                    }
                }
            }
        }
        var_s6 = (var_s6 + 1) & 0xFF;
    } while (var_s6 < 22);

    {
        AudPlayer *p = D_807FC924;
        Aud7130L3_AudPlayerWrap *pw = (Aud7130L3_AudPlayerWrap *)p->pad1;
        D_807FD580 = pw->unk174;
        {
            Aud7130L3_SubActor *sub = D_807FD580->unk104->unk174;
            if (sub->unkFA != 0 && p->unk214 < (sub->unk90 + 3.0f) && D_80745838 == 0 && (s32)D_807FC928 < 2) {
                D_80745838 = 1;
                func_806049CC(0);
                func_806049CC(1);
            }
            if ((sub->unkFA == 0 || (sub->unk90 + 3.0f) < p->unk214) && D_80745838 == 1) {
                D_80745838 = 0;
                func_806049CC(0);
                func_806049CC(1);
            }
        }
    }
}

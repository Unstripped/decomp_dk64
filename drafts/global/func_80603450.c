// func_80603450 (src/global/7130.c): Stage 6 (L603450 m11): frame 0xE8 and saved regs match, 1376 vs 1375 insns, ~27 differing insns: unkD loaded into a0 (target lbu v0 + move a0,v0), 058E candidate copy 'move a0,v0'/beqz a0/hoisted 'move s0,zero' near pan/vol, spill slot 160(sp) vs 156, &D_8077058C hoisted in tail (target 3 separate lui), D_80745BDC[..][1] vs D_80745BDD reloc-only. FAKEs: dead reads of D_8077058E (pan/vol block), D_80770DC8, D_8077058D at function end.
typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    u8 unkA;
    u8 unkB;
    u8 unkC;
    u8 unkD;
} AmbientEmitter;

typedef struct {
    s16 unk0;
    u8 unk2;
    u8 unk3;
    f32 unk4;
    f32 unk8;
} AmbientAudioParam;

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    u8 unk6;
    u8 unk7;
} LevelSoundEmitter;

typedef struct {
    char pad[0x104];
    struct SoundCtxSub104 *unk104;
    char pad108[0xE8];
    u32 unk1F0;
} SoundContextD580;

extern AmbientEmitter D_80745F74[];
extern AmbientEmitter D_80745FD8[];
extern AmbientEmitter D_80746010[];
extern AmbientEmitter D_8074603C[];
extern AmbientEmitter D_80746074[];
extern AmbientEmitter D_807460AC[];
extern AmbientEmitter D_807460E4[];
extern AmbientEmitter D_80746170[];
extern AmbientEmitter D_807461E0[];
extern AmbientEmitter D_80746244[];
extern AmbientEmitter D_8074627C[];

extern AmbientAudioParam D_80745B28[];
extern u8 D_80745BDC[][4];

extern u32 D_80767CC0;
extern s32 D_8076D1F8;
extern s32 D_8076D1FC;
extern s32 D_807457DC;
extern u8 D_80745838;
extern u8 D_8077058C[];
extern u8 D_8077058D;
extern u8 D_8077058E;
extern u8 D_80770DC8;
extern u8 D_80770DCA;
extern u8 D_80770DCB;
extern f32 D_80770DCC;
extern f32 D_80770DD0;
extern f32 D_80770DD4;
extern u8 D_80770DD9;
s32 D_80770DF8[16];
u32 D_80770E38[16];
f32 D_80770E78[16];
f32 D_80770EB8[16];
f32 D_80770EF8[16];
extern u32 D_807FBB60;
extern SoundContextD580 *D_807FD580;

s32 func_8062F388(LevelSoundEmitter **);
void actorTargetEntriesUpdateSfx(s32, s32, s32, f32);
s32 flagGet(s32, s32);
void n_alSndpPostEvent(s32, s32, ...);
f32 func_80611BB4(f32, f32);
void n_alSndpPlay(s32, s16, s32, s32, f32, s32, s32 *);
void n_alSndpStop(s32);
void seqSetVolumeInstant(s32, f32);

void func_80603450(void) {
    s8 spE7;
    s8 spE6;
    u8 spE5;
    s32 n;
    s32 var_s1;
    s16 s2;
    s16 s0;
    f32 var_fs1;
    f32 var_fs0;
    f32 spCC;
    s32 spC8;
    s16 spC4;
    AmbientEmitter *spC0;
    LevelSoundEmitter *spBC;

    spE7 = -1;
    spE5 = 0;

    switch (D_8076A0A8) {
    case 7:
        var_s1 = 7;
        spC0 = D_80745F74;
        break;
    case 0x26:
        var_s1 = 4;
        spC0 = D_80745FD8;
        break;
    case 0x1E:
        var_s1 = 3;
        spC0 = D_80746010;
        break;
    case 0x27:
        var_s1 = 4;
        spC0 = D_8074603C;
        break;
    case 0x1A:
        var_s1 = 4;
        spC0 = D_80746074;
        break;
    case 0xE:
        var_s1 = 4;
        spC0 = D_807460AC;
        break;
    case 0x1B:
        var_s1 = 10;
        spC0 = D_807460E4;
        break;
    case 0x37:
        var_s1 = 7;
        spC0 = D_807461E0;
        break;
    case 0x22:
        var_s1 = 4;
        spC0 = D_80746244;
        break;
    case 0xB0:
        var_s1 = 3;
        spC0 = D_8074627C;
        break;
    case 0x30:
        spC0 = D_80746170;
        var_s1 = 8;
        if (D_807FD580->unk1F0 & 0x100000) {
            sfxStopChannel(0x44, 0);
            if (sfxGetChannelVolume(0x44) < 0.1) {
                sfxAllocateChannel(0x46, 1.0f);
            }
        } else {
            sfxStopChannel(0x46, 0);
            if (sfxGetChannelVolume(0x46) < 0.1) {
                sfxAllocateChannel(0x44, 1.0f);
            }
        }
        break;
    default:
        var_s1 = 0;
        break;
    }

    if (var_s1 != 0 && *(u8 *)&D_80745650 != 0 && D_80745654 == 0) {
        D_80770DD4 = 1000000.0f;
        var_fs1 = 0.0f;
        s0 = 0;
        n = var_s1;
        if (var_s1 > 0) {
            do {
                AmbientEmitter *entry = (AmbientEmitter *)((s32)spC0 + s0 * 14);
                f32 dx = D_807FC924->unk210 - (f32)entry->unk0;
                f32 dz = D_807FC924->unk218 - (f32)entry->unk4;
                if (entry->unk6 == -1) {
                    D_80770DE4 = sqrtf(dx * dx + dz * dz);
                    if (D_80770DE4 < (f32)(entry->unk8 - 20)) {
                        sfxAllocateChannel(entry->unkB, 1.0f);
                    } else if (D_80770DE4 > (f32)entry->unk8) {
                        sfxStopChannel(entry->unkB, 0);
                    }
                } else {
                    f32 dy = D_807FC924->unk214 - (f32)entry->unk2;
                    D_80770DE4 = sqrtf(dx * dx + dy * dy + dz * dz);
                    if (s0 == 0 || D_80770DE4 < D_80770DD4) {
                        spE7 = s0;
                        D_80770DD4 = D_80770DE4;
                        var_fs0 = ((f64)func_80611BB4(dx, dz) * 4096.0) / 6.2831854820251465 - (f64)entry->unk6;
                    }
                }
                s0++;
                D_80770DE8 = 32767.0f - (D_80770DE4 - 50.0f) * 120.0f;
                if (D_80770DE8 > 32767.0f) {
                    D_80770DE8 = 32767.0f;
                }
                if (D_80770DE8 < 0.0f) {
                    D_80770DE8 = 0.0f;
                }
                var_fs1 += D_80770DE8;
            } while (s0 < n);
        }
        D_80770DE4 = D_80770DD4;
        if (spE7 >= 0 && D_80770DE4 < (f32)spC0[spE7].unk8) {
            if (spC0[spE7].unk6 >= 0x1001) {
                D_80770DC9 = spC0[spE7].unk6 & 1;
            } else {
                if (var_fs0 > 2048.0f) {
                    var_fs0 -= 4096.0f;
                }
                if (var_fs0 < -2048.0f) {
                    var_fs0 += 4096.0f;
                }
                if (var_fs0 < 1024.0f && var_fs0 > -1024.0f) {
                    if (D_80770DCB != 0) {
                        D_80770DC9 = 1;
                    }
                } else {
                    D_80770DCB = 1;
                    D_80770DC9 = 0;
                    sfxAllocateChannel(spC0[spE7].unkC, 1.0f);
                }
            }
            if (D_80770DC9 != 0) {
                D_80770DC8 = spC0[spE7].unkA;
            } else {
                D_80770DC8 = 0;
            }
            D_80770DD9 = spC0[spE7].unkB;
        } else {
            D_80770DCB = 0;
        }
        if (D_80745838 != 0) {
            var_fs1 = 0.0f;
        } else if (D_80770DC9 != 0) {
            var_fs1 = 32767.0f;
        } else {
            if (var_fs1 > 32767.0f) {
                var_fs1 = 32767.0f;
            }
            if (var_fs1 < 500.0f) {
                var_fs1 = 0.0f;
            }
        }
        if (D_80770DD8[1] == 0xFF) {
            D_80770DD8[1] = spC0[spE7].unkB;
            D_80770DC8 = spC0[spE7].unkA;
            if (D_80770DC9 == 0) {
                sfxAllocateChannel(spC0[spE7].unkC, 1.0f);
            }
        }
        if (D_80770DC9 != 0 && D_80770DD8[1] != 0) {
            sfxAllocateChannel(D_80770DD8[1], 1.0f);
        } else if (D_80745838 != 0) {
            seqSetTargetVolume(0, 1.0f);
        } else {
            sfxStopChannel(D_80770DD8[1], 0);
        }
        D_80770DCA = D_80770DC9;
        if (var_fs1 != 0.0f) {
            if (spC0[spE7].unkD != 0) {
                sfxAllocateChannel(spC0[spE7].unkD, 1.0f);
            }
        }
        if (D_80770560[2] == 0x26) {
            seqSetVolumeInstant(2, (f32)((f64)var_fs1 / 32767.0));
        }
        var_fs1 = ((var_fs1 - 28384.0f) * 100.0f) / 4383.0f;
        if (var_fs1 < 0.0f) {
            var_fs1 = 0.0f;
        }
        var_fs1 = (f32)((f64)(u32)D_80745BDC[D_8076A0A8][1] + (((255.0 - (f64)(u32)D_80745BDC[D_8076A0A8][1]) * ((f64)(u32)D_80770DC8 / 127.0) * (f64)var_fs1) / 255.0));
        D_8077058E = (u8)(u32)var_fs1;
    } else {
        D_8077058E = D_80745BDC[D_8076A0A8][1];
    }

    if (D_80745838 != 0) {
        D_8077058E = 0xFF;
    }

    if (D_8077058E != D_8077058D) {
        var_fs0 = (f32)(((f64)(u32)D_8077058E * 0.3) / 255.0);
        var_fs1 = (f32)((((f64)(u32)D_8077058E * 0.35) / 255.0) + 1.0);
        if (D_8077058E) {} // FAKE: deadsweep
        if (D_8076A0A8 == 0xE) {
            if (D_8077058E != 0) {
                seqSetVolumeInstant(0, 1.0f);
            } else {
                seqSetVolumeInstant(0, 0.6f);
            }
            alCSPSetChlPanVolume(gSeqPlayers[0], var_fs0, var_fs1);
        }
        for (s0 = 0; s0 < 4; s0++) {
            if (D_80745658[D_80770560[s0]] & 1) {
                alCSPSetChlPanVolume(gSeqPlayers[s0], var_fs0, var_fs1);
            } else {
                alCSPSetChlPanVolume(gSeqPlayers[s0], 0.0f, 1.0f);
            }
        }
        D_8077058D = D_8077058E;
    }

    spC8 = func_8062F388(&spBC);
    for (s2 = 0; s2 < 15; s2++) {
        D_80770DE8 = 0.0f;
        D_80770DEC = 0.0f;
        D_80770DF0 = 0.0f;
        D_80770DF4 = 0.0f;
        if ((D_807FBB60 & 2) || !(D_807FBB60 & 0x10)) {
            var_fs1 = 0.0f;
        } else {
            if (s2 == 11 && flagGet(0x302, 0)) {
                var_fs1 = 0.0f;
            } else if (s2 == 13 && flagGet(0x4C, 0)) {
                var_fs1 = 0.0f;
            } else {
                if (s2 == 1) {
                    actorTargetEntriesUpdateSfx(1, 0xFF, 0xC8, 0.3f);
                }
                for (s0 = spC8 - 1; s0 >= 0; s0--) {
                    if (s2 + 1 == spBC[s0].unk7) {
                        sfxUpdateDistanceVolumeAndPan((f32)spBC[s0].unk0, (f32)spBC[s0].unk2, (f32)spBC[s0].unk4,
                            (u8)((spBC[s0].unk6 * D_80745B28[s2].unk2) / 255.0),
                            D_80745B28[s2].unk3, D_80745B28[s2].unk4);
                    }
                }
                var_fs1 = D_80770DE8 + D_80770DEC;
                if (var_fs1 > 32767.0f) {
                    var_fs1 = 32767.0f;
                }
                if (var_fs1 < 500.0f) {
                    var_fs1 = 0.0f;
                }
            }
        }
        if (D_80745B28[s2].unk0 == 0x1E) {
            var_fs1 = (f32)((f64)var_fs1 * 0.6);
            if ((D_80767CC0 / 12U) != D_80770E38[s2]) {
                D_80770E38[s2] = (D_80767CC0 / 12U);
                if (var_fs1 > 10.0f) {
                    n_alSndpPlay(D_8076D1F8, D_80745B28[s2].unk0, (u16)var_fs1, 0x3F, 0.4f, 0, &D_80770DF8[s2]);
                    D_80770EB8[s2] = var_fs1 + 1.0f;
                    D_80770EF8[s2] = 300.0f;
                }
            }
        }
        if (var_fs1 != D_80770EB8[s2] || D_80770DF8[s2] == 0) {
            if (var_fs1 > 10.0f) {
                if (D_80770DF8[s2] == 0) {
                    spC4 = D_80745B28[s2].unk0;
                    if (spC4 < 0x800) {
                        n_alSndpPlay(D_8076D1F8, spC4, (u16)var_fs1, 0x3F, D_80745B28[s2].unk8, 0, &D_80770DF8[s2]);
                    } else {
                        n_alSndpPlay(D_8076D1FC, spC4 - 0x7FF, (u16)var_fs1, 0x3F, D_80745B28[s2].unk8, 0, &D_80770DF8[s2]);
                    }
                    D_80770E78[s2] = 0.0f;
                    D_80770EF8[s2] = 255.0f;
                }
                if (D_80770DF8[s2] != 0) {
                    n_alSndpPostEvent(D_80770DF8[s2], 8, (s32)var_fs1);
                }
                if (D_80770DF0 < D_80770DF4) {
                    spE5 = 0x80;
                }
                if (D_80770DF8[s2] != 0) {
                    n_alSndpPostEvent(D_80770DF8[s2], 0x100, (s32)spE5);
                }
            } else if (D_80770DF8[s2] != 0) {
                n_alSndpStop(D_80770DF8[s2]);
            }
            D_80770EB8[s2] = var_fs1;
        }
        if (D_80770DF8[s2] != 0) {
            if (D_80770DE8 > 32767.0f) {
                D_80770DE8 = 32767.0f;
            }
            if (D_80770DEC > 32767.0f) {
                D_80770DEC = 32767.0f;
            }
            if (D_80770DEC < D_80770DE8) {
                if (D_80770DE8 > 0.0f) {
                    var_fs0 = (f32)(127.0 - (((f64)D_80770DEC * 63.5) / (f64)D_80770DE8));
                } else {
                    var_fs0 = 0.0f;
                }
            } else if (D_80770DEC > 0.0f) {
                var_fs0 = (f32)(((f64)D_80770DE8 * 63.5) / (f64)D_80770DEC);
            } else {
                var_fs0 = 0.0f;
            }
            if (D_80745838 != 0) {
                spCC = (f32)((f64)D_80745B28[s2].unk8 * 0.5);
            } else if (D_80770DC9 != 0 && D_80745B28[s2].unk0 == 0x106) {
                spCC = (f32)(1.0 / (((f64)D_80770DD4 / 800.0) + 1.0));
            } else {
                spCC = D_80745B28[s2].unk8;
            }
            if (var_fs0 != D_80770EF8[s2]) {
                if (D_80770EF8[s2] != 255.0f) {
                    if (D_80770EF8[s2] < var_fs0) {
                        if (D_80770EF8[s2] + 8.0f < var_fs0) {
                            var_fs0 = D_80770EF8[s2] + 8.0f;
                        }
                    } else {
                        if (var_fs0 < D_80770EF8[s2] - 8.0f) {
                            var_fs0 = D_80770EF8[s2] - 8.0f;
                        }
                    }
                }
                n_alSndpPostEvent(D_80770DF8[s2], 4, (s32)var_fs0);
                D_80770EF8[s2] = var_fs0;
            }
            if (spCC != D_80770E78[s2]) {
                n_alSndpPostEvent(D_80770DF8[s2], 0x10, *(s32 *)&spCC);
                D_80770E78[s2] = spCC;
            }
        }
    }

    if ((D_807FBB60 & 2) || !(D_807FBB60 & 0x10)) {
        D_8077058C[0] = 0;
    }
    if (D_8077058C[0] != 0) {
        if (D_807457DC == 0) {
            n_alSndpPlay(D_8076D1F8, 0x125, 0, 0x3F, 1.0f, 0, &D_807457DC);
        }
        if (D_807457DC != 0) {
            n_alSndpPostEvent(D_807457DC, 8, (s32)(((f64)(u32)D_8077058C[0] * 10767.0) / 255.0));
            spCC = (f32)(1.0 - (((f64)(u32)D_8077058E * 0.5) / 255));
            if (D_80770DC9 & (D_80770DD4 < 1000.0f)) {
                var_fs0 = mathAngleBetweenPointsRad(D_807FC924->unk210, D_807FC924->unk218, (f32)spC0[spE7].unk0, (f32)spC0[spE7].unk4) - D_807FC924->unk2C4;
                if (var_fs0 < 0.0f) {
                    var_fs0 += 6.2831855f;
                }
                if (var_fs0 > 1.5707964f && (f64)var_fs0 < 4.71238911151886) {
                    D_80770DD0 = 128.0f;
                } else {
                    D_80770DD0 = 0.0f;
                }
                D_80770DCC = (f32)((f64)(1.0f - sinApprox(var_fs0)) * 63.5);
            } else {
                D_80770DCC = 64.0f;
            }
            n_alSndpPostEvent(D_807457DC, 0x10, *(s32 *)&spCC);
            n_alSndpPostEvent(D_807457DC, 0x100, (s32)D_80770DD0);
            n_alSndpPostEvent(D_807457DC, 4, (s32)D_80770DCC);
        }
    } else if (D_807457DC != 0) {
        n_alSndpStop(D_807457DC);
    }
    if (D_80770DC8) {} // FAKE: keeps address un-hoisted
    if (D_8077058D) {} // FAKE: keeps address un-hoisted
}

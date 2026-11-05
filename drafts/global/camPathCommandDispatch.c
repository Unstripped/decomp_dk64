// camPathCommandDispatch (src/global/2C910.c): L1169 (focused 2026-11-05): stage 4, count-exact 1169, frame 0xA8, s0+ra; full 262 (deadsweep score), masked diff (regs+sp offsets masked) 6 vs 39 for the previous 201 body (commit 35789027). Structural fixes: no D_807FBB48/4C dead tests; `a = ...; spA0[0] = a;` FIRST (gives the target's `sra t7; move s0,t7; sh t7` entry); case 0x11 `screenWipeStart((arg1 >> 16) & 0xFF)` (target `andi a0,a1,0xff` reads the cross-block `arg1 >> 16` candidate in a1); case 0x27 `s16 node = a` (an s16 local read from a register narrows per use and is never CSE'd across the calls: kills the (s16)a spill sw t8,64/lw s0,64); case 0x2F `t = sv[3]; if (t) f(t, (s16)sv[0])` with csModelStateSetFirstByte declared K&R (target passes the lw'd word unnarrowed: the test's load is reused in a0).
// Remaining: (1) entry colouring: target loads arg1 into ring t8 (uncoloured, one load with two consumers) and arg2 into t5; every spelling tried colours them a0/a2 (bb1 piece adjsave 1.0 = 2 uses - 1 reload); `arg1 >>= 16` (R1 form, no FAKE, full 265) makes arg1 a whole-range isvar coloured a3 with `move a3,a1` at entry instead. (2) frame: sv[] lands at 0x58 (Mmt 104 + 2 temploc slots); target has b/c/d at 0x44/0x3C/0x38 and x at 0x48: under scalars b stays at its home only when its operand param is modified after the def (`arg1 >>= 16`), c/d become temploc isops; d then gets coloured t1 (target reloads it) and cvtl(b) gets call-saved in 0x27 (target `lh 0x46` x4). The if/else form of the f64 ?: temporaries (declared f64 vol/pan) removes the cfe f64 vregs from the Mmt.
#define M3_OFF(p, T, o) (*(T *)((u8 *)(p) + (o)))

extern u8 D_807457E4[];
extern u16 D_80747750[];
extern s8 D_8075536C;
extern s8 D_8076AEE0;
extern s16 D_8076AEF2;
extern s32 D_8076D1F8;
extern s32 D_8076D1FC;
extern s32 gCamActor;
extern u8 D_807F5D6C[];
extern u8 D_807F5D70[];
extern s16 D_807F5D7C;
extern void *D_807FBB48;
extern s32 D_807FBB68;
extern void *gPlayerSlots;
extern f32 gScreenFadeRate;

void actorClearMovementFlags(void *);
s32 actorFindActiveByType(s16, void *);
void actorScriptStart(void *, s32);
s32 actorSpawn(s32, s32);
void commandSetFlags(s8, s8);
void commandSetParameters(s16, s16, s16, u8, u8, u8);
void effectNodeSetTargetPosition(s32, f32, f32, f32);
void func_80028EE8(s32, s32, s32, s32, s32, s32, s32, s32);
void func_805FF378(s32, s32);
void func_805FF8F8(void);
s16 sfxPlayAtPositionPooled(f32, f32, f32, s16, u8, s16, u8, u8, f32, u8);
void controllerAnimSetState(void *, s16, f32, f32);
void controllerStepMotionWindows(void *);
void func_80614A64(void *);
void scriptSetActorRampTarget(void *, f32, f32);
u8 camCueTimerIsRunning(void);
s32 camSetFlags(s32, s32);
void camPausePath(void);
void camSetPathLookAhead(s16);
void camSetPathLookActor(void *, s16);
void camSetPath(u8);
void camLoopPathStep(u8, u8);
void camSetRollBlend(s16, s16, u16);
void camStartShake(s32, u8, u16);
void screenWipeStart();
void actorUpdateModelMatrix(void *, u8);
void csModelStateSetFirstByte();
void func_80641874(s16, s16);
void func_8067A69C(s32, void *, f32, f32, u8, u8);
void func_8067AB20(s32, void *, s32, u8, void *, u8);
void actorCopyPoseAndScale(void *, void *, f32);
void func_80687C48(void);
void func_806C8E58(s16);
void playerResumeLocomotion(void *);
void func_806F0C18(void *);
void playerWaypointPathStartPacked(s32, s32, s16, s16);
void func_8070B308(u8);
void func_8070D8C0(void *, s32, u8);
void func_8070E8DC(s8);
void func_80712524(s32, s32);
void func_8071268C(void);
void func_807127F4(s32);
void func_80712830(void *, s32);
void func_80713EB0(s32, s32, s32);
void func_80724994(u8, s16, s16, s16, s16);
void zoneEntrySpawnEffect(s16, s16, s16, s16);
void func_80729AA4(u8);
void mapChunkEffectSetFlag(s16, s16, u8, u8);
s32 mathAngleBetweenPoints2D(f32, f32, f32, f32);
void *n_alSndpPlay(void *, s16, u16, u8, f32, u8, void *);
void n_alSndpStop(s32);
s32 playerStateQueueCallback(s16, void *, u8);
void sfxAllocateChannel(s32, f32);
void sfxPlayActorSound(void *, s16, u8, u8, u8, u8, f32, s8);
void sfxSetMode(s32);
void sfxStopChannel(s32, s32);
void sfxStopSlotSound(void *, u8);
void *spawnNodeSpawnById(s16, s16, s16, s16, s16, s16, s16);
void spawnNodesSetActorStateByFlag(u16, u8);
void zoneEntryGetPosition(u8, u8, f32 *, f32 *, f32 *);

void camPathCommandDispatch(u32 arg0, u32 arg1, u32 arg2) {
    s16 spA0[4];
    void *sp9C;
    void *sp98;
    void *sp94;
    void *q;
    void *p;
    void *r;
    f32 sp84;
    f32 sp80;
    f32 sp7C;
    s16 sp72;
    s32 a;
    s16 node;
    s32 t;
    s32 sv[5];

    sp9C = M3_OFF(D_807FBB4C, void *, 0x174);
    actorFindActiveByType(0xC, &sp94);
    a = (s16)(arg1 >> 16);
    spA0[0] = a;
    if (1) {  // FAKE: block barrier: keeps the arg2 halves in their own uopt block (prologue order; full 529 -> 262)
        sv[3] = (s16)arg1;
        spA0[1] = sv[3];
        sv[1] = (s16)(arg2 >> 16);
        spA0[2] = sv[1];
        sv[0] = (s16)arg2;
    }
    spA0[3] = sv[0];
    switch (arg0 & 0xFF) {
        case 0x45:
            spawnNodesSetActorStateByFlag(2, 0x40);
            return;
        case 0x42:
            textSpawnSubtitle(a & 0xFF, (s16)(sv[3] != 0 ? sv[3] : 0x5A), (u8)sv[1]);
            return;
        case 0x41:
            func_805FF8F8();
            return;
        case 0x3D:
            func_805FF378(D_8076AEF2, 0);
            return;
        case 0x3E:
            func_805FF378(0x22, 0xC);
            return;
        case 0x40:
            func_807127F4(0);
            return;
        case 0x36:
            func_806C8E58(a + 2);
            func_806F0C18(D_807FBB4C);
            return;
        case 0x33:
            p = M3_OFF(actorFromSpawnNodeOrDefault(a), void *, 0x17C);
            M3_OFF(p, u8, 0x30) = 0xFE;
            M3_OFF(p, u8, 0x33) = sv[3];
            M3_OFF(p, u8, 0x22) = sv[1];
            M3_OFF(p, u8, 0x32) = sv[0];
            M3_OFF(p, u8, 0x31) = 1;
            return;
        case 0x34:
            M3_OFF(M3_OFF(actorFromSpawnNodeOrDefault(a), void *, 0x17C), u8, 0x30) = 0xFF;
            return;
        case 0x0:
            M3_OFF(sp9C, s16, 0x70) = M3_OFF(D_807FBB4C, s16, 0xE6);
            M3_OFF(sp9C, f32, 0x74) = sv[3];
            M3_OFF(sp9C, f32, 0x6C) = a;
            playerStateQueueCallback(0x17, 0, 0);
            return;
        case 0x1:
            func_80028EE8((sv[1] + 6) & 0xFF, 0, 0xC8, a & 0xFF, 0, sv[3] + 0x28, 0x64, 0xFF);
            return;
        case 0x2:
            M3_OFF(sp9C, s32, 0x1F0) |= 8;
            return;
        case 0x3:
            M3_OFF(sp9C, s32, 0x1F0) &= ~8;
            return;
        case 0x24:
            func_80724994(1, a, (s16)sv[3], (s16)sv[1], sv[0]);
            return;
        case 0x5:
            spawnNodeSpawnById(a, 0, 0, 0, 0, 0, 0);
            return;
        case 0x4:
            if (a != 0) {
                func_80724994(3, a, sv[3], (s16)sv[1], sv[0]);
                return;
            }
            if (sv[3] == 2) {
                M3_OFF(M3_OFF(M3_OFF(D_807FBB48, void *, 4), void *, 0), s16, 0x10) = -1;
                actorScriptStart(D_807FBB48, D_80747750[sv[1]]);
                if (sv[0] != 0) {
                    scriptSetActorRampTarget(D_807FBB48, sv[0] / 100.0, 0);
                    return;
                }
            }
        default:
            return;
        case 0x6:
            camSetPathLookActor(spawnNodeActivate(a, 0), sv[3]);
            return;
        case 0x7:
            camLoopPathStep(a, (u8)sv[3]);
            return;
        case 0x2D:
            camSetPathLookAhead(a);
            return;
        case 0x2E:
            M3_OFF(actorFromSpawnNodeOrDefault(a), u8, 0x15E) = sv[3];
            return;
        case 0x25:
            playerWaypointPathStartPacked((s32)D_807FBB4C, 0, a, 0);
            return;
        case 0x26:
            func_80641874(a, sv[3]);
            return;
        case 0x27:
            node = a;
            sv[4] = (u8)sv[1];
            mapChunkEffectSetFlag(node, (s16)sv[3], 0, (u8)sv[1]);
            mapChunkEffectSetFlag(node, (s16)sv[3], 1, sv[4]);
            mapChunkEffectSetFlag(node, sv[3], 2, sv[4]);
            mapChunkEffectSetFlag(node, (s16)sv[3], 3, sv[4]);
            return;
        case 0x8:
            camSetPath(a);
            return;
        case 0x2B:
            func_8070B308(a);
            return;
        case 0x9:
            camSetRollBlend(a, sv[3], sv[1]);
            return;
        case 0x10:
            camStartShake(gCamActor, sv[3], a);
            return;
        case 0xA:
            if (a != 0) {
                p = spawnNodeActivate(a, 0);
                if (sv[3] != 0) {
                    M3_OFF(p, s32, 0x60) |= 4;
                    return;
                }
                M3_OFF(p, s32, 0x60) &= ~4;
                return;
            }
            sp72 = 1;
            p = spawnNodeActivate(sp72++, 0);
            if (p != NULL) {
                do {
                    if (sv[3] != 0) {
                        M3_OFF(p, s32, 0x60) |= 4;
                    } else {
                        M3_OFF(p, s32, 0x60) &= ~4;
                    }
                    p = spawnNodeActivate(sp72++, 0);
                } while (p != NULL);
                return;
            }
            break;
        case 0xB:
            zoneEntrySpawnEffect(a, sv[3], sv[1], (s16)sv[0]);
            return;
        case 0x11:
            screenWipeStart((arg1 >> 16) & 0xFF);
            return;
        case 0xC:
            func_8067AB20(gCamActor, sp94, 0x01000000, 1, spA0, 0);
            return;
        case 0xD:
            func_8067AB20(gCamActor, sp94, 0x01000000, 0x10, spA0, 0);
            spA0[3] = -1;
            func_8067AB20(gCamActor, sp94, 0x01000000, 0xE, spA0, 0);
            return;
        case 0x12:
            func_8067AB20(gCamActor, sp94, 0x01000000, 0x14, spA0, 0);
            return;
        case 0x31:
            if (sv[0] != 0) {
                commandSetParameters(0x320, 0x82, 0, 0x64, 0x64, 0x64);
                commandSetFlags(1, 1);
                return;
            }
            commandSetParameters(0x320, 0x82, 0, a, sv[3], sv[1]);
            commandSetFlags(1, 0);
            return;
        case 0x32:
            effectNodeSetTargetPosition(a, sv[3], sv[1], sv[0] * 0.01);
            return;
        case 0xE:
            func_80729AA4(a);
            return;
        case 0x16:
            sp98 = spawnNodeActivate(a, 0);
            if (sp98 != NULL) {
                if (D_807FBB68 & 2) {
                    actorCopyPoseAndScale(D_807FBB4C, sp98, M3_OFF(M3_OFF(sp98, void *, 4), f32, 0x38));
                } else {
                    actorCopyPoseAndScale(D_807FBB4C, sp98, 0.15f);
                    M3_OFF(gPlayerSlots, u8, 0x2C0) = 1;
                }
                playerResumeLocomotion(D_807FBB4C);
                M3_OFF(D_807FBB4C, s32, 0x60) |= 4;
                M3_OFF(sp98, u8, 0x154) = 0x40;
                return;
            }
            break;
        case 0x20:
            p = spawnNodeActivate(a, 0);
            if (p != NULL) {
                actorCopyPoseAndScale(p, D_807FBB4C, M3_OFF(M3_OFF(D_807FBB4C, void *, 4), f32, 0x38));
                M3_OFF(D_807FBB4C, u8, 0x154) = 0x77;
                M3_OFF(D_807FBB4C, u8, 0x155) = 0;
                return;
            }
            break;
        case 0x29:
            if (camCueTimerIsRunning() == 0) {
                func_80712524(a, sv[3]);
                return;
            }
            break;
        case 0x43:
            if (camCueTimerIsRunning() == 0) {
                D_8075536C = sv[1];
                func_80712524(a, sv[3]);
                return;
            }
            break;
        case 0x3F:
            func_80713EB0(a, sv[3], sv[1]);
            return;
        case 0x2A:
            p = spawnNodeActivate(a, 0);
            if (p != NULL) {
                M3_OFF(p, u8, 0x154) = 0x3C;
                return;
            }
            break;
        case 0x28:
            sp98 = spawnNodeActivate(a, 0);
            if (sp98 != NULL) {
                q = spawnNodeActivate((s16)sv[3], 0);
                if (q != NULL) {
                                        actorCopyPoseAndScale(sp98, q, M3_OFF(M3_OFF(q, void *, 4), f32, 0x38));
                    controllerAnimSetState(sp98, M3_OFF(M3_OFF(M3_OFF(q, void *, 4), void *, 0), s16, 0x10), M3_OFF(M3_OFF(M3_OFF(q, void *, 4), void *, 0), f32, 4), 0.0f);
                    controllerStepMotionWindows(sp98);
                    M3_OFF(sp98, s32, 0x60) |= 4;
                    M3_OFF(q, s32, 0x60) &= ~4;
                    return;
                }
            }
            break;
        case 0x13:
            if (a != 0) {
                sp98 = spawnNodeActivate(a, 0);
            } else {
                actorClearMovementFlags(sp98 = D_807FBB4C);
            }
            zoneEntryGetPosition(sv[3], sv[1], &M3_OFF(sp98, f32, 0x7C), &M3_OFF(sp98, f32, 0x80), &M3_OFF(sp98, f32, 0x84));
            func_8067A69C(0, sp98, M3_OFF(sp98, f32, 0x7C), M3_OFF(sp98, f32, 0x84), 2, 1);
            {
                s32 t = (sv[0] << 12) / 360;
                M3_OFF(sp98, s16, 0xEE) = t;
                M3_OFF(sp98, s16, 0xE6) = t;
            }
            M3_OFF(sp98, f32, 0x9C) = M3_OFF(sp98, f32, 0x80);
            actorUpdateModelMatrix(sp98, 0);
            func_80614A64(sp98);
            return;
        case 0x14:
            if (a >= 0) {
                if (a != 0) {
                    sp98 = spawnNodeActivate(a, 0);
                } else {
                    sp98 = D_807FBB4C;
                }
                D_807F5D7C = sfxPlayAtPositionPooled(M3_OFF(sp98, f32, 0x7C), M3_OFF(sp98, f32, 0x80), M3_OFF(sp98, f32, 0x84), sv[3], (u32)(sv[1] != 0 ? (f64)sv[1] : 127.5), sv[0] != 0 ? sv[0] : 0x7F, 0, 0, 0.0f, 0);
                return;
            }
            if (sv[3] < 0x800) {
                n_alSndpPlay((void *)D_8076D1F8, sv[3], (u32)(sv[1] != 0 ? ((f64)sv[1] / 255.0) * 32767.0 : 16383.5), 0x3F, sv[0] != 0 ? (f64)sv[0] / 127.0 : 1.0, 0, (u8 *)D_807F5D6C + -(a * 4));
                return;
            }
            n_alSndpPlay((void *)D_8076D1FC, (s16)(sv[3] - 0x7FF), (u32)(sv[1] != 0 ? ((f64)sv[1] / 255.0) * 32767.0 : 16383.5), 0x3F, sv[0] != 0 ? (f64)sv[0] / 127.0 : 1.0, 0, (u8 *)D_807F5D6C + -(a * 4));
            return;
        case 0x19:
            q = (void *)(a > 0 ? a : -a);
            if ((s32)q <= 0) {
                sp72 = 0;
            } else {
                q = (void *)(a > 0 ? a : -a);
                sp72 = (s32)q - 1;
            }
            n_alSndpStop(*(s32 *)(D_807F5D70 + sp72 * 4));
            return;
        case 0x1A:
            n_alSndpStop(*(s32 *)(D_807457E4 + D_807F5D7C * 4));
            return;
        case 0x38:
            if (a != 0) {
                sp98 = spawnNodeActivate(a, 0);
            } else {
                sp98 = D_807FBB4C;
            }
            sfxPlayActorSound(sp98, (s16)sv[3], 0, 1, 0, sv[1] != 0 ? sv[1] : 0xFF, 1.0f, sv[0]);
            return;
        case 0x37:
            if (a != 0) {
                sp98 = spawnNodeActivate(a, 0);
            } else {
                sp98 = D_807FBB4C;
            }
            sfxStopSlotSound(sp98, 0);
            return;
        case 0x1B:
            sfxStopChannel(a, 0);
            return;
        case 0x44:
            sfxSetMode(a & 0xFF);
            return;
        case 0x3C:
            p = M3_OFF(spawnNodeActivate(1, 0), void *, 0x17C);
            M3_OFF(p, u8, 0xD) |= a;
            return;
        case 0x3B:
            M3_OFF(actorFromSpawnNodeOrDefault(a), s16, 0x146) = sv[3];
            return;
        case 0x1C:
            M3_OFF(actorFromSpawnNodeOrDefault(a), s16, 0xE6) = M3_OFF(gPlayerSlots, s16, 0x2C8) & 0xFFF;
            return;
        case 0x30:
            p = actorFromSpawnNodeOrDefault(a);
            if (sv[3] >= 0) {
                M3_OFF(p, u8, 0x16A) = sv[3];
                M3_OFF(p, s32, 0x60) |= 0x800000;
                M3_OFF(p, u8, 0x16B) = sv[1];
                M3_OFF(p, u8, 0x16C) = sv[0];
                return;
            }
            M3_OFF(p, s32, 0x60) &= 0xFF7FFFFF;
            return;
        case 0x2C:
            sp98 = actorFromSpawnNodeOrDefault(a);
            zoneEntryGetPosition(sv[3], (u8)sv[1], &sp84, &sp80, &sp7C);
            M3_OFF(sp98, s16, 0xE6) = mathAngleBetweenPoints2D(sp84, sp7C, M3_OFF(sp98, f32, 0x7C), M3_OFF(sp98, f32, 0x84));
            return;
        case 0x2F:
            csModelStateSetFirstByte((s16)a, (s16)sv[0]);
            t = sv[3];
            if (t != 0) {
                csModelStateSetFirstByte(t, (s16)sv[0]);
            }
            if (sv[1] != 0) {
                csModelStateSetFirstByte((s16)sv[1], (s16)sv[0]);
                return;
            }
            break;
        case 0x15:
            csModelStateSetFirstByte((s16)a, (s16)sv[3]);
            return;
        case 0x17:
            sfxAllocateChannel(a, sv[3] != 0 ? (f64)sv[3] / 255.0 : 1.0);
            return;
        case 0x18:
            func_8070E8DC(1);
            /* fallthrough */
        case 0x39:
            func_8070D8C0(actorFromSpawnNodeOrDefault(a), (u16)sv[3], (u8)sv[1]);
            return;
        case 0x1E:
            actorSpawn(0x108, 0x1D);
            M3_OFF(D_807FBB44, s16, 0xF0) = sv[1];
            func_8070D8C0(D_807FBB44, a & 0xFFFF, (u8)sv[3]);
            return;
        case 0x1D:
            camPausePath();
            return;
        case 0x21:
            camSetFlags(gCamActor, 0x8000);
            return;
        case 0x22:
            if (a != 0) {
                func_805FF378(a, sv[3]);
                return;
            }
            func_80712830(D_807FBB4C, 0);
            return;
        case 0x23:
            D_8076AEE0 = a;
            gScreenFadeRate = sv[3] / 100.0;
            return;
        case 0x3A:
            func_8071268C();
            return;
        case 0x35:
            if (a == 0) {
                func_80687C48();
            }
            break;
    }
}

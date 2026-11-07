// camPathCommandDispatch (src/global/2C910.c): stage 4: full=172 text=172 reloc=0 shape=96 (unchanged park C); R13_sonnet_xhigh_7: no match, NEW ROUTE for the frame, not yet scoring. (1) The 5 words 0x38..0x4B are uopt spilltemps ITEMS, not declared homes: arg-position ?: (cases 0x42/0x14/0x38/0x17, ABS twice in 0x19) force cfe hidden int/f64 temps that always sit below every declared local, so nothing declared can be lowest. Items: T1=(s16)arg1 @0x44, T2=(s16)(arg2>>16) @0x3C, T3=(s16)arg2 @0x38, (u8)T2 of case 0x27 @0x48 (reuses E_u's slot: disjoint region), 0x40 unaccessed; needs bit order E_u(ushr arg1,16 -> a1) < T1 < E_a(a -> s0) < T2 < T3 and U=5 words, Mmt 92. (2) Same expressions inline in the cases (no sv array/node/t/if(1) barrier) and bb1 `a=(s16)((u32)arg1>>16); spA0[0]=a; b=(s16)arg1; spA0[1]=b; b=(s16)((u32)arg2>>16); spA0[2]=b; b=(s16)arg2; spA0[3]=b;` (ONE reused s32 b) = .scratch/R13_sonnet_xhigh_7/camPathCommandDispatch_e11_route.c: frame 0xA8, 1361 insns (target 1365), T1/T2/T3 land on 0x44/0x3C/0x38, regs-masked shape 46 (park 96) but full 490 (entry colouring + ring). It has E_u<E_a<T1 so U=6 (0x4C..0x38): u8 item at 0x4C not 0x48, sp72 at 0x76 not 0x72; keeping `a` a variable (E_a not an item) would give U=5. Other deltas: s16-param sites need cvtl ON TOP of the item (named var + (s16) cast gives lh; inline (s16)(s16)x is folded by cfe -> lw); case 0x27 repeats (s16)T1/(s16)a/(u8)T2: target recomputes the first two, spills only (u8)T2 (park C already has that shape). The parked array form is structurally EXACT (regs+sp offsets masked diff 6, bb1 schedule only), so any new route must keep shape2<=6. (3) Entry, uopt source derivation (uoptreg2.c compute_save/cupcosts/globalcolor): post-call arg piece total=(loads-1 reglod)*freq/units; 2 loads in one unit -> adj 1.0 > best 0 -> coloured a0/a2; needs total<=best: loads<=1 or a call crossing inside the piece. Tried, no effect: address-taken params (still coloured t3/t4), volatile, s16/u16/u32 types, bb1 statement permutations (24), `if(1)` barrier, inner scope (cfe emits no bgnb: all locals stay `block 15`, so find_replacements' curblk test cannot be used), single-use pieces via locals. Ring: target ring is t1..t9 (uopt colours only t0 besides v0/v1/a1/a3/s0). | Prior: stage 4: full=172 text=172 reloc=0 shape=96 (unchanged); R12_fable_2: derived the two open rules, no spelling beat 172. (1) Entry args: uopt splits each param's live range at the call; the post-call piece has load_count 2 (ushr + cvtl) in one block, adjsave=(2-1)/1=1 > caller-saved cost 0, so it is assigned the lowest free register (a0/a2); the target's t8/t5 ring loads need load_count<=1 or every caller-saved reg forbidden in bb1; u32/K&R/volatile/struct-by-value params, &param reads (give lh), x^0 sharing, register, dead param reassignment (gives a1/a2, a becomes a plain var, full 180) all keep the colouring. (2) Frame: spilltemps (uoptreg2.c:873) gives EVERY coloureditem (bits 9 ushr->a1 and 11 a->s0) a slot below cfe's Mmt in bit order (2 slots = 0x38/0x3C), and cfe puts every hidden temp (?: results, nested-call bases/args, inner-block t) below all declared locals in any scope (tests fA/fB/fF-fJ), so a declared array can never reach 0x38; the five words also cannot be uopt expression temps: a (s16) of a temp or of an uncoloured vreg scalar is carried across calls (sw/lh pairs in cases 0x27/0x2F, v2b/v10/v12), while the target reloads lh 0x46/0x3A each time, i.e. non-vreg memory. Open: which construct yields non-vreg words below the 2 slots. | stage 4: full=172 text=172 reloc=0 shape=96; R11_camPathCommandDispatch: verified frame 0xA8 exact; stack derivation shows sv[0..4] at 0x58..0x68 instead of target 0x38..0x48 because CFE allocates hidden temporary homes for ternary expressions (? :) below declared locals, pushing the array 0x20 bytes higher; target uses scalar lh/lbu inside spilled word homes rather than array indexing. Exact park form restored. | Prior: StackGroup stage4; Base d495328bf722a26c83c592a497693f5a487e9132; full172 text172 reloc0 shape96, count1365 normalized lines/frame0xA8 exact. Declaration swap node/sp72 fixes counter home7A->72 (176->172). sv homes58/5C/64 still target38/3C/44; hidden CFE conditional homes are after array. Dead double initializer failed523 and reverted. Active fdiff text+reloc mismatch; parked plain OK/non-matching compile OK. Full map .scratch/StackGroup/camPathCommandDispatch.md.
#define Matcher14_OFF(p, T, o) (*(T *)((u8 *)(p) + (o)))

extern u8 D_807457E4[];
extern u16 D_80747750[];
extern s8 D_8075536C;
extern s8 D_8076AEE0;
extern s16 D_8076AEF2;
extern s32 D_8076D1F8;
extern s32 D_8076D1FC;
extern void *gCamActor;
extern u8 D_807F5D6C[];
extern u8 D_807F5D70[];
extern s16 D_807F5D7C;
extern Actor *D_807FBB48;
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

void camPathCommandDispatch(s32 arg0, s32 arg1, s32 arg2) {
    s16 spA0[4];
    void *sp9C;
    void *sp98;
    void *sp94;
    void *q;
    void *p;
    void *r; // FAKE: reserves the original local-frame slot.
    f32 sp84;
    f32 sp80;
    f32 sp7C;
    s16 node;
    s32 a;
    s16 sp72;
    s32 t;
    s32 sv[5];

    sp9C = Matcher14_OFF(D_807FBB4C, void *, 0x174);
    actorFindActiveByType(0xC, &sp94);
    a = (s16)((u32)arg1 >> 16);
    spA0[0] = a;
    if (1) {  // FAKE: block barrier: keeps the arg2 halves in their own uopt block (prologue order; full 529 -> 262)
        sv[3] = (s16)arg1;
        spA0[1] = sv[3];
        sv[1] = (s16)((u32)arg2 >> 16);
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
            p = Matcher14_OFF(actorFromSpawnNodeOrDefault(a), void *, 0x17C);
            Matcher14_OFF(p, u8, 0x30) = 0xFE;
            Matcher14_OFF(p, u8, 0x33) = sv[3];
            Matcher14_OFF(p, u8, 0x22) = sv[1];
            Matcher14_OFF(p, u8, 0x32) = sv[0];
            Matcher14_OFF(p, u8, 0x31) = 1;
            return;
        case 0x34:
            Matcher14_OFF(Matcher14_OFF(actorFromSpawnNodeOrDefault(a), void *, 0x17C), u8, 0x30) = 0xFF;
            return;
        case 0x0:
            Matcher14_OFF(sp9C, s16, 0x70) = Matcher14_OFF(D_807FBB4C, s16, 0xE6);
            Matcher14_OFF(sp9C, f32, 0x74) = sv[3];
            Matcher14_OFF(sp9C, f32, 0x6C) = a;
            playerStateQueueCallback(0x17, 0, 0);
            return;
        case 0x1:
            func_80028EE8((sv[1] + 6) & 0xFF, 0, 0xC8, a & 0xFF, 0, sv[3] + 0x28, 0x64, 0xFF);
            return;
        case 0x2:
            Matcher14_OFF(sp9C, s32, 0x1F0) |= 8;
            return;
        case 0x3:
            Matcher14_OFF(sp9C, s32, 0x1F0) &= ~8;
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
                Matcher14_OFF(Matcher14_OFF(Matcher14_OFF(D_807FBB48, void *, 4), void *, 0), s16, 0x10) = -1;
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
            Matcher14_OFF(actorFromSpawnNodeOrDefault(a), u8, 0x15E) = sv[3];
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
            camStartShake((s32)gCamActor, sv[3], a);
            return;
        case 0xA:
            if (a != 0) {
                p = spawnNodeActivate(a, 0);
                if (sv[3] != 0) {
                    Matcher14_OFF(p, s32, 0x60) |= 4;
                    return;
                }
                Matcher14_OFF(p, s32, 0x60) &= ~4;
                return;
            }
            sp72 = 1;
            p = spawnNodeActivate(sp72++, 0);
            if (p != NULL) {
                do {
                    if (sv[3] != 0) {
                        Matcher14_OFF(p, s32, 0x60) |= 4;
                    } else {
                        Matcher14_OFF(p, s32, 0x60) &= ~4;
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
            screenWipeStart(((u32)arg1 >> 16) & 0xFF);
            return;
        case 0xC:
            func_8067AB20((s32)gCamActor, sp94, 0x01000000, 1, spA0, 0);
            return;
        case 0xD:
            func_8067AB20((s32)gCamActor, sp94, 0x01000000, 0x10, spA0, 0);
            spA0[3] = -1;
            func_8067AB20((s32)gCamActor, sp94, 0x01000000, 0xE, spA0, 0);
            return;
        case 0x12:
            func_8067AB20((s32)gCamActor, sp94, 0x01000000, 0x14, spA0, 0);
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
                    actorCopyPoseAndScale(D_807FBB4C, sp98, Matcher14_OFF(Matcher14_OFF(sp98, void *, 4), f32, 0x38));
                } else {
                    actorCopyPoseAndScale(D_807FBB4C, sp98, 0.15f);
                    Matcher14_OFF(gPlayerSlots, u8, 0x2C0) = 1;
                }
                playerResumeLocomotion(D_807FBB4C);
                Matcher14_OFF(D_807FBB4C, s32, 0x60) |= 4;
                Matcher14_OFF(sp98, u8, 0x154) = 0x40;
                return;
            }
            break;
        case 0x20:
            p = spawnNodeActivate(a, 0);
            if (p != NULL) {
                actorCopyPoseAndScale(p, D_807FBB4C, Matcher14_OFF(Matcher14_OFF(D_807FBB4C, void *, 4), f32, 0x38));
                Matcher14_OFF(D_807FBB4C, u8, 0x154) = 0x77;
                Matcher14_OFF(D_807FBB4C, u8, 0x155) = 0;
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
                Matcher14_OFF(p, u8, 0x154) = 0x3C;
                return;
            }
            break;
        case 0x28:
            sp98 = spawnNodeActivate(a, 0);
            if (sp98 != NULL) {
                q = spawnNodeActivate((s16)sv[3], 0);
                if (q != NULL) {
                                        actorCopyPoseAndScale(sp98, q, Matcher14_OFF(Matcher14_OFF(q, void *, 4), f32, 0x38));
                    controllerAnimSetState(sp98, Matcher14_OFF(Matcher14_OFF(Matcher14_OFF(q, void *, 4), void *, 0), s16, 0x10), Matcher14_OFF(Matcher14_OFF(Matcher14_OFF(q, void *, 4), void *, 0), f32, 4), 0.0f);
                    controllerStepMotionWindows(sp98);
                    Matcher14_OFF(sp98, s32, 0x60) |= 4;
                    Matcher14_OFF(q, s32, 0x60) &= ~4;
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
            zoneEntryGetPosition(sv[3], sv[1], &Matcher14_OFF(sp98, f32, 0x7C), &Matcher14_OFF(sp98, f32, 0x80), &Matcher14_OFF(sp98, f32, 0x84));
            func_8067A69C(0, sp98, Matcher14_OFF(sp98, f32, 0x7C), Matcher14_OFF(sp98, f32, 0x84), 2, 1);
            {
                s32 t = (sv[0] << 12) / 360;
                Matcher14_OFF(sp98, s16, 0xEE) = t;
                Matcher14_OFF(sp98, s16, 0xE6) = t;
            }
            Matcher14_OFF(sp98, f32, 0x9C) = Matcher14_OFF(sp98, f32, 0x80);
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
                D_807F5D7C = sfxPlayAtPositionPooled(Matcher14_OFF(sp98, f32, 0x7C), Matcher14_OFF(sp98, f32, 0x80), Matcher14_OFF(sp98, f32, 0x84), sv[3], (u32)(sv[1] != 0 ? (f64)sv[1] : 127.5), sv[0] != 0 ? sv[0] : 0x7F, 0, 0, 0.0f, 0);
                return;
            }
            if (sv[3] < 0x800) {
                n_alSndpPlay((void *)D_8076D1F8, sv[3], (u32)(sv[1] != 0 ? ((f64)sv[1] / 255.0) * 32767.0 : 16383.5), 0x3F, sv[0] != 0 ? (f64)sv[0] / 127.0 : 1.0, 0, (u8 *)D_807F5D6C + -(a * 4));
                return;
            }
            n_alSndpPlay((void *)D_8076D1FC, (s16)(sv[3] - 0x7FF), (u32)(sv[1] != 0 ? ((f64)sv[1] / 255.0) * 32767.0 : 16383.5), 0x3F, sv[0] != 0 ? (f64)sv[0] / 127.0 : 1.0, 0, (u8 *)D_807F5D6C + -(a * 4));
            return;
        case 0x19:
            arg2 = (u32)(a > 0 ? a : -a); // FAKE: unsigned expression keeps the absolute-value temporary's allocation.
            if ((s32)arg2 <= 0) {
                sp72 = 0;
            } else {
                arg2 = (u32)(a > 0 ? a : -a); // FAKE: unsigned expression keeps the absolute-value temporary's allocation.
                sp72 = (s32)arg2 - 1;
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

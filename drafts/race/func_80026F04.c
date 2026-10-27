// func_80026F04 (src/race/1770.c): stage 5 (parked NON_MATCHING in copy; frame 0x80, callee-saved s0-s2 and all stack homes match; text 1 insn short). Remaining diff: (1) fp register coloring in the tail func_806F4D70/4DC0 block: target colors sp58=f0,sp50=f2,off=f12,sp54=f14, ours off=f0,sp58=f2,sp50=f12 (fp candidates colour in decl/IL order; off declared before sp58 forces off first; moving off last or reordering if/else did not help); (2) one CSE spill slot 0x44 vs 0x40. Fixes found: t = 300.0f reuse of the f32 t local for both 300.0f multiplies puts sv (s16 angle) in s0 (was memory); all arm locals (o,o2,f,t,off) declared at function level in order len,sp78,s1,sv,off,f,o,o2,i,sp58,sp54,sp50 reproduce stack homes; off = 10.0 (double literal) and f != 0 (int zero) stop all-function fp-constant merging; f = 1.5f * f + 1.5f; kind chain via two pointer locals and u16 read twice.
extern s32 *D_807F5FD4;
extern void *D_807FBB40;
void racePlayCheckpointSfx(u8 *, u8, f32);
void func_80026B20(u8 *);
void func_80026CA8(void);
void func_80026D2C(f32);
void func_80026EE4(void *, u8 *);
f32 func_80612794(s16);
void sfxPlayActorSound(void *, s32, s32, s32, s32, s32, f32, s32);
extern u8 D_807FBD70;
extern void *D_807FBB4C;
s32 raceGetPrevWaypointIndex(s32, s32);
void func_80026354(void *, void *, s32);
void actorUpdateModelMatrix(void *, s32);
void func_806086CC(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);
s32 func_807142D8(void);
s32 flagGet(s32, s32);
void playerStateQueueCallback(s32, void *, u8);
void func_806F397C(void *, void *, s32, s32);
void actorClearNodeFlag(void *, s32);
void func_8072DB68(s32);
void slotQueueUpdate(s32, s32, s32);
void slotQueueCancel(s32, s32);
f32 func_8002D2C0(void *);
void func_806F4D70(u8, f32, f32, f32, f32);
void func_806F4DC0(u8, f32, f32, f32, f32);
void func_8068ECF4(s32, s32);
void sfxStopSlotSound(void *, s32);
void renderCallbacksRegister(void *, void *, s32);

void func_80026F04(void) {
    s32 len;
    u8 *sp78;
    u8 *s1;
    s16 sv;
    f32 off;
    f32 f;
    u8 *o;
    u8 *o2;
    s32 i;
    f32 sp58;
    f32 sp54;
    f32 sp50;

    s1 = *(u8 **)((u8 *)D_807FBB40 + 0x174);
    sp78 = *(u8 **)((u8 *)D_807FBB40 + 0x178);
    if (!(*(s32 *)((u8 *)D_807FBB40 + 0x60) & 0x10)) {
        len = (D_807F5FD4[sp78[0] + 1] - D_807F5FD4[sp78[0]]) / 12;
        s1[0x2A] = 3;
        *(u8 *)((u8 *)D_807FBB40 + 0x144) = 0x3C;
        *(u16 *)(sp78 + 2) = raceGetPrevWaypointIndex(len, 0);
        func_80026354(sp78, s1, 1);
        if (func_807142D8() != 0 || flagGet(0x12, 2) != 0) {
            playerStateQueueCallback(0x4B, D_807FBB40, s1[0x28]);
        } else {
            func_806F397C(D_807FBB4C, D_807FBB40, 0, 0x4B);
        }
        actorClearNodeFlag(D_807FBB40, 2);
        func_80026CA8();
    }
    if (D_807FBD70 == 5 && sp78[0x39] == 0) {
        if (s1[0x34] == 2) {
            func_8072DB68(3);
        }
        sp78[0x39] = 0x1E;
    }
    if (s1[0x35] == 0) {
        if (s1[0x34] == 1) {
            slotQueueUpdate(0xB, 1, 0);
            s1[0x35]++;
        } else if (s1[0x34] == 5) {
            slotQueueCancel(0xB, 0);
            s1[0x35]++;
        }
    }
    if (s1[0x34] == 1) {
        o = *(u8 **)(s1 + 0x30);
        o2 = *(u8 **)(o + 0x174);
        if (*(u16 *)(o2 + 0x1C) == 8 || *(u16 *)(o2 + 0x1C) == 0x13) {
            func_806086CC(*(f32 *)((u8 *)D_807FBB40 + 0x7C), *(f32 *)((u8 *)D_807FBB40 + 0x80), *(f32 *)((u8 *)D_807FBB40 + 0x84), 0x187, 0xFF, 0x7F, 0, 0, 0.3f, 0);
        }
        func_80026D2C(s1[0x26] * 1.5);
    } else if (s1[0x34] < 5) {
        sv = 0;
        if (s1[0x26] != 0) {
            f = func_8002D2C0(s1);
            if (f != 0) {
                f = 1.5f * f + 1.5f;
                racePlayCheckpointSfx(sp78, 0x1E, f);
            }
            s1[0x26] = 0;
        }
        if (sp78[0x39] != 0) {
            f32 t = sp78[0x39];
            if (t > 10.0f) {
                sv = (s32)((t - 10.0f) * 204.8f);
                t = 300.0f;
                *(f32 *)(sp78 + 0x20) = func_80612794(sv) * t;
                *(f32 *)(sp78 + 0x24) = func_80612794(sv * 2) * t;
            } else {
                *(f32 *)(sp78 + 0x20) = 0.0f;
                *(f32 *)(sp78 + 0x24) = 0.0f;
            }
        }
        func_80026354(sp78, s1, 1);
        *(f32 *)((u8 *)D_807FBB40 + 0x80) += 20.0f * func_80612794((s32)(sv * 0.5f));
        func_80026D2C(*(f32 *)((u8 *)D_807FBB40 + 0xB8));
    } else if (s1[0x34] == 5) {
        *(s32 *)((u8 *)D_807FBB40 + 0x60) &= ~4;
        *(f32 *)((u8 *)D_807FBB40 + 0xB8) = 0.0f;
        for (i = 0; i != 2; i++) {
            if (*(s16 *)((u8 *)D_807FBB40 + i * 2 + 0x6E) != -1) {
                sfxStopSlotSound(D_807FBB40, i & 0xFF);
            }
        }
    }
    if (s1[0x29] != 0) {
        func_80026B20(s1);
    }
    if (s1[0x34] < 5) {
        if (s1[0x34] == 2) {
            off = 10.0;
        } else {
            off = -200.0f;
        }
        sp58 = *(f32 *)((u8 *)D_807FBB40 + 0x7C);
        sp50 = *(f32 *)((u8 *)D_807FBB40 + 0x84);
        sp54 = *(f32 *)((u8 *)D_807FBB40 + 0x80) + off;
        func_806F4D70(s1[0x28], sp58, sp54, sp50, 12.0f);
        func_806F4DC0(s1[0x28], (sp58 + *(f32 *)((u8 *)D_807FBB40 + 0x88)) * 0.5, sp54, (sp50 + *(f32 *)((u8 *)D_807FBB40 + 0x90)) * 0.5, 12.0f);
    }
    if (*(s32 *)((u8 *)D_807FBB40 + 0x60) & 4) {
        func_8068ECF4(1, 0xC8);
        func_8068ECF4(2, 0xC8);
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
    if (s1[0x34] > 0 && s1[0x34] < 5) {
        renderCallbacksRegister(func_80026EE4, D_807FBB40, 3);
    }
}

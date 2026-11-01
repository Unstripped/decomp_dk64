// func_8002AED8 (src/bonus/2690.c): func_8002AED8 (src/bonus/2690.c): stage 6, 5 text diff lines (deadsweep score full=5 text=5 shape=0; was ~12): ONLY regs differ: const 80.0f web gets f12 (target f2) and k=80.0f/d expr cand 315 gets f2 (target f16). Needs in the copy: proto controllerApplyMotionWindow(void *, void *, f32) (src/bonus/2690.c:203, was s32; func_8002BE44 still scores 0 with it) + BonusDBE44Anim.unk4 f32, and the LargeB4Player/LargeB4Ctrl/D_807FBB4C/gPlayerSlots/D_807ECDEC/lightSetColor/lightAdd block HOISTED above func_8002AED8 (moved from above func_8002BF98); callees bonusEndLose(0,1)/bonusEndWin(0,0) (not func_800265C0/800264E0). Trace: colour idx 25=f2 26=f12 27=f14 28=f16; 315 (adj 3.0) coloured before const 367 (adj 0.5) and takes 25; target needs 315 forbidden {25,26,27} like sp6C cand 174 (f16, its forb comes from bb38 webs 168/176/186 = fv1/t->unk10/t->unk14 loads) - i.e. k must interfere with them or 367 colour first AND f12/f14 be taken. Tried this unit (no gain): fp-field dead tests (> 0.0f, < 80.0f, == 80.0f on t->unk*/fs0/fs1/sp6C/sp68->unk4/LB5->unk*; deadsweep 11040 variants), sp6C reuse for k / d (5, same), 384 spellings of the tail (fs0/fs1 order, sum order, 80<d, k decl split, mul/div operand order, store order), function-level k (in padz slot) with dead tests after the later calls (k gets f2 + spill, 6-13), k at function scope extra slot (+8 frame).
typedef struct {
    char pad0[0x210];
    f32 unk210;
    f32 unk214;
    f32 unk218;
    char pad21C[0x7C];
    u16 *unk298;
    char pad29C[0x2C];
    s16 unk2C8;
    char pad2CA[0x26];
} LargeB4Player;

typedef struct {
    char pad0[2];
    s8 unk2;
    s8 unk3;
} LargeB4Ctrl;

extern Actor *D_807FBB4C;
extern LargeB4Player *gPlayerSlots;
extern LargeB4Ctrl *D_807ECDEC;
void lightSetColor(f32, f32, f32, s32);
void lightAdd(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32);
typedef struct {
    char pad0[4];
    f32 unk4;
    char pad8[0x1C];
    f32 unk24;
} LargeB5Anim;

typedef struct {
    LargeB5Anim *unk0;
    char pad4[0x30];
    f32 unk34;
    f32 unk38;
    f32 unk3C;
} LargeB5Model;

typedef struct LargeB5Actor {
    char pad0[4];
    LargeB5Model *unk4;
    char pad8[0x58];
    s32 unk60;
    char pad64[0x18];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0x5E];
    s16 unkE6;
    s16 unkE8;
    char padEA[0x32];
    struct LargeB5Actor *unk11C;
    char pad120[0x34];
    u8 unk154;
    u8 unk155;
    char pad156[0x1E];
    struct LargeB5State *unk174;
} LargeB5Actor;

typedef struct LargeB5State {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    s16 unk18;
    char pad1A[2];
    f32 unk1C;
    char pad20[2];
    s16 unk22;
    char pad24;
    u8 unk25;
    u8 unk26;
    char pad27;
    s16 unk28;
    s16 unk2A;
    s8 unk2C;
    s8 unk2D[1];
} LargeB5State;

typedef struct {
    void *unk0;
    f32 unk4;
    f32 unk8;
    char padC[2];
    s16 unkE;
} LargeB5Proj;

#define LB5 ((LargeB5Actor *)D_807FBB40)

void func_8002AED8(void) {
    s32 pad0[4];
    f32 fs0;
    f32 fs1;
    f32 sp6C;
    LargeB5Anim *sp68 = LB5->unk4->unk0;
    LargeB5State *t = LB5->unk174;
    s32 i;
    u8 c;
    s32 padz;
    LargeB5Proj *p0;
    s16 sp52;

    if (!(LB5->unk60 & 0x10)) {
        D_807FBB4C->unk154 = 0x77;
        D_807FBB4C->unk155[0] = 0;
        t->unk0 = LB5->unk7C + 10.0;
        t->unk4 = LB5->unk84 + 8.0;
        LB5->unk80 = LB5->unk80 + 50.0;
        switch (gCurrentMap) {
        case 0x66:
            t->unk2A = 4;
            break;
        case 0x94:
            t->unk2A = 6;
            break;
        case 0x95:
            t->unk2A = 8;
            break;
        case 0x96:
            t->unk2A = 0xA;
            break;
        }
        t->unk26 = 0;
        t->unk22 = 0x3C;
        t->unk28 = t->unk2A;
        fs0 = 1 * 0.0f;
        c = gfxResourceCreate(1, textTableGetString(0x1A, 2, 1), 8, fs0, fs0, fs0);
        t->unk25 = c;
        func_806FDAB8(c, fs0);
        lightSetColor(1.0f, 1.0f, 1.0f, -1);
        LB5->unkE8 = 0;
        LB5->unkE6 = 0x800;
        func_80613C48(D_807FBB40, 0x5FB, 0.0f, 0.0f);
        LB5->unk4->unk34 = 0.2f;
        LB5->unk4->unk38 = 0.2f;
        LB5->unk4->unk3C = 0.2f;
        camStartPath(0, 0, 1);
        LB5->unk154 = 3;
        t->unk1C = 0.0f;
        t->unk10 = 0.0f;
        t->unk14 = 0.0f;
        t->unk8 = 0.0f;
        t->unkC = 0.0f;
        actorSpawn(0x14C, 0x55);
        p0 = (LargeB5Proj *)D_807FBB44->unk174;
        p0->unk0 = D_807FBB40;
        t->unk2C = 0x3C;
        i = 0;
        do {
            t->unk2D[i] = 1;
            i++;
        } while (i != 1);
    }
    for (i = 0; i < 1; i++) {
        if (t->unk2D[i] > 0) {
            t->unk2D[i] -= 1;
            if (t->unk2D[i] == 0 && actorSpawn(0x14A, 0x53) != 0) {
                LargeB5Proj *s0 = (LargeB5Proj *)D_807FBB44->unk174;

                s0->unk0 = D_807FBB40;
                s0->unk4 = D_807FBB44->unk7C;
                s0->unk8 = D_807FBB44->unk84;
                s0->unkE = 2;
                sp52 = mathAngleBetweenPoints2D(t->unk0, t->unk4, LB5->unk7C, LB5->unk84) + 0x800;
                s0->unk4 = func_80612794(sp52) * 70.0 + t->unk0;
                s0->unk8 = func_80612790(sp52) * 70.0 + t->unk4;
                if (t->unk2C == 0) {
                    D_807FBB44->unk7C = s0->unk4;
                    D_807FBB44->unk80 = LB5->unk80 - 30.0;
                    D_807FBB44->unk84 = s0->unk8;
                } else {
                    D_807FBB44->unk7C = t->unk0 - 30.0;
                    D_807FBB44->unk84 = t->unk0;
                    D_807FBB44->unk80 = LB5->unk80 - 30.0;
                }
            }
        }
    }
    if (t->unk2C != 0) {
        t->unk2C -= 1;
    }
    t->unk18 += 0x19;
    if (LB5->unk154 < 2) {
        f32 fv0;
        f32 fv1;

        fs1 = func_80612794(gPlayerSlots[gCurrentPlayerIndex].unk2C8);
        fv0 = func_80612790(gPlayerSlots[gCurrentPlayerIndex].unk2C8);
        fs0 = D_807ECDEC->unk2 * 0.04f;
        fv1 = D_807ECDEC->unk3 * 0.04f;

        sp6C = t->unk10;
        sp6C = (fs0 * fv0 - fv1 * fs1) - sp6C;
        t->unk10 += sp6C * 0.125f;
        t->unk14 += ((fs0 * fs1 + fv1 * fv0) - t->unk14) * 0.25f;
        t->unk8 += t->unk10;
        t->unkC -= t->unk14;
    }
    switch (LB5->unk154) {
    case 0: {
        f32 prev = t->unk1C;

        t->unk1C += (-sp6C * 4.0f - t->unk1C) * 0.125f;
        if (t->unk1C < 0.0f) {
            if (t->unk1C < -8.0f) {
                t->unk1C = -8.0f;
            }
            if (prev >= 0.0f) {
                func_80613C48(D_807FBB40, 0x5FC, 0.0f, 0.0f);
            }
            if (sp68 != NULL) {
                controllerApplyMotionWindow(D_807FBB40, sp68, -t->unk1C);
            }
        } else {
            if (t->unk1C > 8.0f) {
                t->unk1C = 8.0f;
            }
            if (prev < 0.0f) {
                func_80613C48(D_807FBB40, 0x5FB, 0.0f, 0.0f);
            }
            if (sp68 != NULL) {
                controllerApplyMotionWindow(D_807FBB40, sp68, t->unk1C);
            }
        }
        if (t->unk28 == 0) {
            LB5->unk154 = 5;
        }
        if (LB5->unk11C->unk154 == 5) {
            LB5->unk154 = 6;
        }
        if (LB5->unk154 == 0 && (*gPlayerSlots[gCurrentPlayerIndex].unk298 & 0xE000)) {
            sfxPlayOnFreeSlot(0x25, 0x7FFF, 63.0f, 0.51f, 0, 0);
            func_80613C48(D_807FBB40, 0x5FD, 0.0f, 1.0f);
            LB5->unk154 = 1;
        }
        break;
    }
    case 1:
    case 2:
        if (sp68->unk4 > 10.0f && sp68->unk4 < 14.0f) {
            LB5->unk154 = 2;
        } else {
            LB5->unk154 = 1;
        }
        if (sp68->unk24 == 0.0f) {
            func_80613C48(D_807FBB40, 0x5FC, 0.0f, 1.0f);
            LB5->unk154 = 0;
            t->unk1C = 0.0f;
        }
        break;
    case 3:
        if (D_807444EC != 1) {
            LB5->unk154 = 4;
            hudSpawnCountdownTimer(0xDC, 0x2A, ((u8 *)&t->unk22)[1]);
            func_8070D8C0(D_807FBB40, 0, 0xA);
        }
        break;
    case 4:
        if (!(LB5->unk60 & 0x2000000)) {
            LB5->unk154 = 0;
            actorSetStateTwo(LB5->unk11C);
            sfxAllocateChannel(8, 1.0f);
        }
        break;
    case 5:
    case 6:
        if (LB5->unk154 == 6) {
            bonusEndLose(0, 1);
        } else {
            bonusEndWin(0, 0);
        }
        camStartPath(0, 1, 0x11);
        LB5->unk154 = 7;
        break;
    }
    {
        f32 d;

        fs0 = t->unk8 * 0.85;
        fs1 = t->unkC - 40.0;
        d = sqrtf(fs0 * fs0 + fs1 * fs1);

        if (d > 80.0f) {
            f32 k = 80.0f / d;

            t->unk8 = (fs0 * k) / 0.85;
            t->unkC = (fs1 * k) + 40.0;
        }
    }
    LB5->unk7C = func_80612794(t->unk18) * 5.0 + (t->unk0 + t->unk8 * 0.8);
    LB5->unk84 = 2.0 * func_80612790((s16)(t->unk18 * 2)) + (t->unk4 + t->unkC * 0.9);
    D_807FBB4C->unk7C = t->unk0 + t->unk8 * 0.5f;
    D_807FBB4C->unk80 = LB5->unk80;
    D_807FBB4C->unk84 = t->unk4 + t->unkC * 0.5f;
    renderCallbacksRegister(func_80029B9C, D_807FBB40, 3);
    actorUpdateModelMatrix(D_807FBB40, 0);
}

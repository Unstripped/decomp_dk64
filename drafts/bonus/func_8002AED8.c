// func_8002AED8 (src/bonus/2690.c): stage 6 (frame 0x88, callee-saved set, 658 insns match; only 3 FP regs in the tail: 80.0f const f12 vs target f2, k=80.0f/d f2 vs target f16; 25 diff lines). uopt_trace: k (CSE udiv, adjsave 3.0) colours before the const (0.5, +0.5/extra use; 6 dummy uses make const win but then k gets f12, not f16). Target k=f16 needs f2/f12/f14 unavailable to k: appending 3 nested field loads to BB90 reserves f2,f12,f14 for ugen temps (k=f16) but const then gets f18, never f2 (const would need to escape the reservation k is under). Tried, all still 25: inline/named/block/fn-scope k, 80.0f<d, 80 int, k=sp6C/d reuse, lim var (also 1*80.0f), comma/cast/f64/f32 intermediates, ~700 role/copy permutations of fv0/fv1/prev/d/k/u/v/sp6C, ~1000 dummy if(x){} uses (d,k,fs0,fs1,const compares,struct fields), permuter 3 earlier + 15 min. Needs func_80614644(void*,void*,f32) proto at line ~238 and BonusDBE44Anim.unk4 f32 (func_8002BE44 still matches).
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

typedef struct {
    char pad0[0x298];
    u16 *unk298;
    char pad29C[0x2C8 - 0x29C];
    s16 unk2C8;
    char pad2CA[0x2F0 - 0x2CA];
} LargeB5Player;

typedef struct {
    char pad0[2];
    s8 unk2;
    s8 unk3;
} LargeB5Axis;

extern LargeB5Actor *D_807FBB4C;
extern LargeB5Player *D_807FC924;
extern LargeB5Axis *D_807ECDEC;
void lightSetColor(f32, f32, f32, s32);
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
        D_807FBB4C->unk155 = 0;
        t->unk0 = LB5->unk7C + 10.0;
        t->unk4 = LB5->unk84 + 8.0;
        LB5->unk80 = LB5->unk80 + 50.0;
        switch (D_8076A0A8) {
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

        fs1 = func_80612794(D_807FC924[D_807FC929].unk2C8);
        fv0 = func_80612790(D_807FC924[D_807FC929].unk2C8);
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
                func_80614644(D_807FBB40, sp68, -t->unk1C);
            }
        } else {
            if (t->unk1C > 8.0f) {
                t->unk1C = 8.0f;
            }
            if (prev < 0.0f) {
                func_80613C48(D_807FBB40, 0x5FB, 0.0f, 0.0f);
            }
            if (sp68 != NULL) {
                func_80614644(D_807FBB40, sp68, t->unk1C);
            }
        }
        if (t->unk28 == 0) {
            LB5->unk154 = 5;
        }
        if (LB5->unk11C->unk154 == 5) {
            LB5->unk154 = 6;
        }
        if (LB5->unk154 == 0 && (*D_807FC924[D_807FC929].unk298 & 0xE000)) {
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
            func_800265C0(0, 1);
        } else {
            func_800264E0(0, 0);
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

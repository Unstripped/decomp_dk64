// func_8002A0AC (src/race/52B0.c): stage 5 (parked NON_MATCHING in RaceC copy): same frame 0x58/size; only diff = (idx*10 index) v1 in-place: target 'sll v1,a1,2; addu v1,v1,a1; sll v1,v1,1' vs ours sll t1,v1,1 + move v1,t1, shifting later temp regs t-numbers by 1. Tried ixa s16 [idx*5], struct size 10 (multu: const 10 shared with D_80750AC8=0xA), explicit shifts, vars; permuter no legit gain. switch: default arm first + goto tail; int vs s32 no effect
typedef struct {
    u8 pad0[0x4];
    f32 unk4;
    u8 pad8[0x10 - 0x8];
    f32 unk10;
    u8 pad14[0x1C - 0x14];
    u16 unk1C;
    u8 pad1E[0x25 - 0x1E];
    u8 unk25;
    u8 unk26;
    u8 pad27;
    u8 unk28;
    u8 pad29[0x30 - 0x29];
    void *unk30;
    u8 unk34;
    u8 unk35;
    u8 pad36[0x44 - 0x36];
    u8 unk44;
    u8 pad45[0x104 - 0x45];
    s32 unk104;
} RaceC_State;

typedef struct {
    void *unk0;
    s32 unk4;
    u8 unk8;
    u8 pad9;
    u16 unkA;
} RaceC_Target;

typedef struct {
    u8 pad0[0x10];
    s16 unk10;
    u8 pad12[0xB8 - 0x12];
    f32 unkB8;
} RaceC_Obj;

typedef struct {
    RaceC_Obj *unk0;
    u8 pad4[0x64 - 0x4];
    u16 unk64;
} RaceC_Sub;

typedef struct {
    u8 pad0[0x4];
    RaceC_Sub *unk4;
    u8 pad8[0x60 - 0x8];
    u32 unk60;
    u8 pad64[0x6A - 0x64];
    u16 unk6A;
    u8 pad6C[0x6E - 0x6C];
    s16 unk6E[2];
    u8 pad72[0x7C - 0x72];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 pad88[0xB8 - 0x88];
    f32 unkB8;
    u8 padBC[0xE4 - 0xBC];
    s16 unkE4;
    u8 padE6[0xE8 - 0xE6];
    s16 unkE8;
    u8 padEA[0x12A - 0xEA];
    s16 unk12A;
    u8 pad12C[0x144 - 0x12C];
    u8 unk144;
    u8 pad145[0x174 - 0x145];
    RaceC_State *unk174;
    s32 unk178;
    s32 unk17C;
    RaceC_Target *unk180;
} RaceC_Actor;

extern void *D_807FBB40;
#define RC_A ((RaceC_Actor *)D_807FBB40)
void func_8068F72C(void *, s32, s32, s32);
void actorUpdateModelMatrix(void *, s32);
void func_80614D00(void *, f32, f32);
void func_80029F88(void *, void *, f32, f32, f32);
s32 func_8002A080(s32, s32);
typedef struct {
    u8 pad0[0x25];
    u8 unk25;
} RaceC_DC90;

typedef struct {
    u8 pad0[0x20];
    u8 *unk20;
} RaceC_DC98;

typedef struct {
    u8 pad0[0x11];
    u8 unk11;
} RaceC_DC9C;

typedef struct {
    u8 pad0[0x14];
    s16 *unk14;
} RaceC_DCA0;

extern RaceC_DC90 *D_807FDC90;
extern RaceC_DC98 *D_807FDC98;
extern RaceC_DC9C *D_807FDC9C;
extern RaceC_DCA0 *D_807FDCA0;
extern s16 D_80750AC8;
extern u8 D_8002FC20[];
extern u8 D_8002FC50[];
extern f32 D_8002FC30;
void behaviourFrameBegin(void);
void camRequestPathLength(void);
s32 camStartPath(void *, s32, s32);
void camResumePath(void);
void currentActorClearFlag(void);
s32 currentActorTestClearFlag(void);
s32 flagGet(s32, s32);
void flagSet(s32, s32, s32);
f32 func_8002978C(void);
void func_8002DE78(void *, s32, void *, void *);
void func_8002E644(void *);
void func_805FF544(void);
void func_8063DA40(s32, s32);
void func_8070D8C0(void *, s32, s32);
void func_8072881C(s32, void *);
void hudSpawnTextScreen(s32);
void playerStateQueueCallback(s32, s32, s32);
void actorScriptStart(void *, s32);

void func_8002A0AC(void) {
    RaceC_State *s0;
    s32 sp50;
    RaceC_Target *sp4C;
    f32 sp48;
    f64 dv;
    RaceC_State *sp3C;
    RaceC_Actor *tmp;
    s32 sp34;
    s32 idx;
    s32 sp2C;
    s32 v;
    f32 fv1;

    s0 = (RaceC_State *)RC_A->unk178;
    sp50 = RC_A->unk17C;
    sp4C = RC_A->unk180;
    sp48 = 0.0f;
    behaviourFrameBegin();
    if (!(RC_A->unk60 & 0x10)) {
        tmp = s0->unk30;
        sp3C = tmp->unk174;
        s0->unk10 = 1.0f;
        RC_A->unk60 &= 0xFFFDFFFE;
        RC_A->unk12A = 0x5DC;
        func_8002DE78(sp4C, 5, D_8002FC20, D_8002FC50);
        s0->unk34 = 0;
        camRequestPathLength();
        v = camStartPath(D_807FBB40, 1, 1) - 0x3C;
        sp3C->unk1C = v;
        sp4C->unkA = v;
        s0->unk4 = 1.0f;
        D_807FDC90->unk25 = D_807FDC9C->unk11 - 5;
        idx = D_807FDC98->unk20[D_807FDC90->unk25 * 2];
        RC_A->unk7C = D_807FDCA0->unk14[idx * 5];
        RC_A->unk80 = D_807FDCA0->unk14[idx * 5 + 1];
        RC_A->unk84 = D_807FDCA0->unk14[idx * 5 + 2];
        D_80750AC8 = 0xA;
    }
    if (sp4C->unkA != 0) {
        sp4C->unkA -= 1;
    }
    if (s0->unk34 < 5) {
        sp48 = func_8002978C();
        if (s0->unk34 == 2) {
            func_8002E644(sp4C);
        } else if (s0->unk34 == 4 && sp4C->unk8 == 0) {
            sp4C->unk8 = 1;
            if (flagGet(0xA5, 0) == 0) {
                camStartPath(sp4C->unk0, 0, 1);
                currentActorClearFlag();
            } else {
                func_805FF544();
            }
        }
        func_8068F72C(s0, sp50, 0, 0);
    } else if (s0->unk34 == 5) {
        switch (s0->unk35) {
        case 0:
            if (flagGet(0xA5, 0) == 0) {
                playerStateQueueCallback(0x55, 0, 0);
                RC_A->unkE4 = 0;
                RC_A->unkE8 = 0;
                actorScriptStart(D_807FBB40, 0x29A);
            }
            s0->unk35 += 1;
            break;
        case 1:
            if (currentActorTestClearFlag() != 0) {
                sp34 = sp4C->unk4;
                currentActorClearFlag();
                func_8070D8C0(D_807FBB40, 0x12, func_8002A080((s32)s0, sp34) & 0xFF);
                s0->unk35 += 1;
            }
            break;
        case 2:
            if (!(RC_A->unk60 & 0x02000000)) {
                camResumePath();
                s0->unk35 += 1;
            }
            break;
        case 3:
            if (currentActorTestClearFlag() != 0) {
                sp2C = func_8002A080((s32)s0, sp4C->unk4);
                currentActorClearFlag();
                if (sp2C == 0) {
                    func_8063DA40(0x3B, 0xA);
                    flagSet(0xA5, 1, 0);
                } else {
                    hudSpawnTextScreen(1);
                    s0->unk35 += 1;
                }
                s0->unk35 += 1;
            }
            break;
        case 4:
            if (currentActorTestClearFlag() != 0) {
                currentActorClearFlag();
                func_805FF544();
                s0->unk35 += 1;
            }
            break;
        }
    }
    switch (RC_A->unk4->unk64) {
    default:
        v = RC_A->unk4->unk0->unk10;
        goto tail;
    case 0x29E:
    case 0x2A2:
        fv1 = RC_A->unkB8 * 0.0025f;
        fv1 = fv1 < 0.1 ? 0.1 : fv1;
        func_80614D00(D_807FBB40, fv1, 10.0f);
        break;
    case 0x2A0:
        v = RC_A->unk4->unk0->unk10;
        if (v == 0x4A7) {
            func_80029F88(D_807FBB40, s0, RC_A->unkB8 - ((RaceC_Actor *)sp4C->unk0)->unkB8, (sp48 - D_8002FC30) * 40.0f, 23.0f);
            break;
        }
    tail:
        if (v != 0x49B) {
            func_80614D00(D_807FBB40, 1.0f, 10.0f);
        }
        break;
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
    func_8072881C(0, (u8 *)D_807FDC90 + 0x28);
}

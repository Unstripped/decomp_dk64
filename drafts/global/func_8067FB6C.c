// func_8067FB6C (src/global/80150.c): from .scratch/R3D/func_8067FB6C_best.c
// func_8067FB6C best draft (matches instruction count and length, diff score 1030 / minor regalloc)

typedef struct R2I_Actor124 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} R2I_Actor124;

typedef struct R2I_Actor174_104 {
    u8 pad0[0x104];
    s32 unk104;
} R2I_Actor174_104;

typedef struct R2I_SubFB6C {
    Actor *unk0;
    u32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    s16 unk18;
    u8 unk1A;
    u8 unk1B;
    u8 unk1C;
} R2I_SubFB6C;

typedef struct R2I_Actor {
    u8 pad0[0xEE];
    s16 unkEE;
} R2I_Actor;

extern Actor *D_807FBB48;
extern s32 D_807FBB68;
extern s32 D_8071FBC8;
extern u16 D_807FD63C;
void func_806FF01C();

void func_80608528(Actor *, s32, s32, s32, s32);
f32 func_80612790(s16);
f32 func_80612794(s16);
f32 func_80612D1C(f32);
void func_80613194(Actor *, s32);
void func_80613214(Actor *);
void func_8061C2F0(s32, f32, f32, f32, f32, f32, f32, s32);
void func_8061C6A8(s32, Actor *, s32, s32, s32, s32, s32, s32, s32, s32, f32);
s32 func_8061CB50(void);
void func_80667110(f32, f32, f32 *);
void func_80679200(Actor *, Actor *, s32, s32, s32, s32);
void func_80679290(Actor *, Actor *, s32, s32, s32, s32, s32);
void func_8067A70C(Actor *, Actor *, f32, f32, f32, u8, u8);
void func_8067AAB8(Actor *, Actor *, s16, f32, s16);
void func_8068C350(void *, void *, s32);
void func_80714C08(void *, f32, Actor *, s32, s32);

void func_8067FB6C(void) {
    f64 pad;
    f32 sp5C;
    f32 sp58;
    s32 sp54;
    s32 pad2;
    s16 sp4E;
    R2I_SubFB6C *sub;
    s32 var_v0;
    f32 var_fa1;
    s16 i;

    sub = D_807FBB40->unk174;
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk12A = 0x320;
        D_807FBB40->unk12C[4] = 0x14;
        D_807FBB40->unk12C[5] = 0x14;
        sub->unkC = 90.0f;
        sub->unk8 = D_807FBB40->unk80;
        sub->unk14 = (f64)((R2I_Actor124 *)D_807FBB40->unk124)->unk0 / 200.0;
        sub->unk10 = ((R2I_Actor124 *)D_807FBB40->unk124)->unk4;
        sub->unk4 = ((f64)sub->unk14 != 0.0) ? (4.71238899230957031 / (f64)sub->unk14) : (f64)0;
        sub->unk1C = ((R2I_Actor124 *)D_807FBB40->unk124)->unk8;
        sub->unk18 = D_807FBB40->unkE6;
        D_807FBB40->unkA4 = 99999.0f;
        func_80667110(D_807FBB40->unk7C, D_807FBB40->unk84, &D_807FBB40->unkA4);
        if (sub->unk1C == 3) {
            D_807FBB40->unk132 = 2;
        } else {
            D_807FBB40->unk132 = 1;
        }
        if (((R2I_Actor124 *)D_807FBB40->unk124)->unkC == 1) {
            D_807FBB40->unk154 = 0x14;
            D_807FBB40->unk144 = 1;
            D_807FBB40->unk60 &= ~0x8000;
            D_807FBB40->unk128 = 0;
        }
    }
    if (D_807FBB70.unk200 == 4) {
        sub->unk0 = (Actor *)D_807FBB70.unk1FC;
        D_807FBB40->unk154 = 1;
        D_807FBB40->unk144 = 1;
        D_807FBB40->unk60 |= 0x400;
        sub->unk1B = 2;
        if (sub->unk1C == 3) {
            sub->unk1A = 1;
        } else {
            sub->unk1A = 2;
        }
    }
    switch (D_807FBB40->unk154) {
    case 0:
        func_8067FAC8();
        break;
    case 1:
        D_807FBB40->unk60 |= 0x8000;
        switch (sub->unk1C) {
        case 0:
        case 4:
            if (sub->unk1C == 0) {
                D_807FBB40->unk80 = func_80612D1C((f32)sub->unk4 * sub->unk14) * sub->unk10 + (sub->unk8 + sub->unk10);
            } else {
                D_807FBB40->unk80 = func_80612D1C((f32)sub->unk4 * sub->unk14) * sub->unk10 + sub->unk8;
            }
            func_8067A70C(D_807FBB40, sub->unk0, D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 2, 1);
            sp4E = D_807FBB40->unkE6;
            sub->unk4++;
            break;
        case 2:
            D_807FBB40->unkE6 = (D_807FBB40->unkE6 + (s32)(sub->unk14 * 200.0f)) & 0xFFF;
            sp4E = (D_807FBB40->unkE6 + (s32)(sub->unk14 * 200.0f)) & 0xFFF;
            break;
        case 1:
            D_807FBB40->unkE6 = ((s32)(func_80612D1C((f32)sub->unk4 * sub->unk14) * ((sub->unk10 * 4096.0f) / 360.0f)) + sub->unk18) & 0xFFF;
            sub->unk4++;
            sp4E = ((s32)(func_80612D1C((f32)sub->unk4 * sub->unk14) * ((sub->unk10 * 4096.0f) / 360.0f)) + sub->unk18) & 0xFFF;
            break;
        case 3:
            sp4E = D_807FBB40->unkE6;
            break;
        }
        sp5C = func_80612794(sp4E) * 50.0f;
        sp58 = func_80612790(sp4E) * 50.0f;
        if (sub->unk1B == 1) {
            func_80613194(D_807FBB40, 0x75);
        }
        if (sub->unk1B) {
            sub->unk1B--;
        }
        if (sub->unk1A) {
            sub->unk1A--;
        }
        if (((D_807FD63C & 0xE000) || sub->unk1C == 3) && sub->unk1A == 0) {
            R2I_Actor174_104 *temp_s0_2;
            func_80608528(D_807FBB40, 0x18, 0xFF, 0x7F, 1);
            temp_s0_2 = sub->unk0->unk174;
            func_80613214(D_807FBB40);
            if (!(D_807FBB68 & 2)) {
                if (sub->unk1C == 3) {
                    var_v0 = 0x64;
                } else {
                    var_v0 = 0x32;
                }
                func_8061C6A8(temp_s0_2->unk104, sub->unk0, 4, 0x800, var_v0, 0, 0, 0x1E, 0x14, 0x50, 0.3f);
            }
            D_807FBB48->unkE6 = D_807FBB40->unkE6;
            ((R2I_Actor *)D_807FBB48)->unkEE = D_807FBB40->unkE6;
            func_80679200(sub->unk0, D_807FBB40, 0x40, 1, 0, 0);
            if (D_807FBB68 & 2) {
                var_v0 = 0x1F4;
            } else {
                var_v0 = 0x2BC;
            }
            func_8067AAB8(D_807FBB40, sub->unk0, D_807FBB40->unkE6, 0.0f, var_v0);
            func_80679290(D_807FBB40, D_807FBB40, 0x800, 2, 0, 0, 0xA);
            func_80714998(2);
            func_80714C08(&D_8071FBC8, 1.6f, D_807FBB40, 1, 2);
            D_807FBB40->unk60 &= ~0x400;
            D_807FBB40->unk154 = 2;
            D_807FBB40->unk155[0] = 0x1E;
        } else {
            sp54 = ((R2I_Actor174_104 *)sub->unk0->unk174)->unk104;
            switch (sub->unk1C) {
            case 0:
                var_fa1 = func_80612D1C((f32)sub->unk4 * sub->unk14) * sub->unk10 + (sub->unk8 + sub->unk10);
                break;
            case 4:
                var_fa1 = func_80612D1C((f32)sub->unk4 * sub->unk14) * sub->unk10 + sub->unk8;
                break;
            default:
                var_fa1 = D_807FBB40->unk80;
                break;
            }
            if (D_807FBB68 & 2) {
                var_v0 = 0;
            } else {
                var_v0 = 1;
            }
            func_8061C2F0(
                sp54,
                (f64)D_807FBB40->unk7C - (f64)sp5C / 5.0,
                var_fa1,
                (f64)D_807FBB40->unk84 - (f64)sp58 / 5.0,
                D_807FBB40->unk7C + sp5C,
                var_fa1,
                D_807FBB40->unk84 + sp58,
                var_v0
            );
            if (func_8061CB50() == 0) {
                func_8068C350(func_806FF01C, D_807FBB4C, 3);
            }
        }
        break;
    case 2:
        func_8067FAC8();
        D_807FBB40->unk155[0]--;
        if (D_807FBB40->unk155[0] == 0) {
            D_807FBB40->unk80 = sub->unk8;
            sub->unk4 = ((f64)sub->unk14 != 0.0) ? (4.71238899230957031 / (f64)sub->unk14) : (f64)0;
            D_807FBB40->unkE6 = sub->unk18;
            D_807FBB40->unk154 = 0;
        }
        break;
    case 20:
        for (i = 0; i < D_807FBB70.unk254; i++) {
            if (D_807FBB70.unk258[i] == 1 && *D_807FBB70.unk278[i] == 0) {
                D_807FBB40->unk144 = 2;
                D_807FBB40->unk154 = 0x15;
            }
        }
        break;
    case 21:
        D_807FBB40->unk128 += 10;
        if (D_807FBB40->unk128 >= 0xF1) {
            D_807FBB40->unk60 |= 0x8000;
            D_807FBB40->unk154 = 0;
        }
        break;
    }
    if (D_8076A0A8 == 0xCB) {
        D_807FBB40->unk60 |= 0x400;
    }
    guRotateF((float (*)[4])&D_807FBB40->unk08[4], sub->unkC, 1.0f, 0, 0.0f);
    actorUpdateModelMatrix(D_807FBB40, 1);
}

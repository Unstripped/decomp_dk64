// func_806BE8BC (src/global/C2A90.c): Stage 6: text identical except switch selector (u8 unk155 lbu) in v0/v1 instead of a1 at both 0x1F/0x28 switches; jtbl reloc .rodata vs jtbl_8075BC04 is a GLOBAL_ASM artefact. Base 949e5b0.
typedef struct LgBE8Sub4 {
    /* 0x00 */ u8 pad0[0x64];
    /* 0x64 */ u16 unk64;
} LgBE8Sub4;

typedef struct LgBE8A {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ LgBE8Sub4 *unk4;
    /* 0x008 */ u8 pad8[0x58];
    /* 0x060 */ u32 unk60;
    /* 0x064 */ u8 pad64[0x18];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x1C];
    /* 0x0A4 */ f32 unkA4;
    /* 0x0A8 */ u8 padA8[0x18];
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ u8 padC4[0x22];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 padE8[0x40];
    /* 0x128 */ s16 unk128;
    /* 0x12A */ u8 pad12A[0x2A];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[9];
    /* 0x15F */ u8 unk15F;
    /* 0x160 */ u8 pad160[8];
    /* 0x168 */ s16 unk168;
} LgBE8A;

typedef struct LgBE8S90 {
    /* 0x00 */ u8 pad0[0xA];
    /* 0x0A */ s16 unkA;
    /* 0x0C */ u8 padC[2];
    /* 0x0E */ s16 unkE;
    /* 0x10 */ u8 pad10[0xA];
    /* 0x1A */ u16 unk1A;
    /* 0x1C */ u8 pad1C[0xC];
    /* 0x28 */ u8 unk28[4];
} LgBE8S90;

typedef struct LgBE8G {
    /* 0x000 */ u8 pad0[0x1F4];
    /* 0x1F4 */ s32 unk1F4;
    /* 0x1F8 */ u8 pad1F8[0x47];
    /* 0x23F */ u8 unk23F;
} LgBE8G;

typedef struct LgBE8S9C {
    /* 0x00 */ u8 pad0[0xD];
    /* 0x0D */ u8 unkD;
} LgBE8S9C;

#define LgBA ((LgBE8A *)D_807FBB40)
#define LgBB ((LgBE8A *)D_807FBB4C)
#define LgBG ((LgBE8G *)D_807FD580)
#define LgBS ((LgBE8S90 *)D_807FDC90)
#define LgB9C ((LgBE8S9C *)D_807FDC9C)

extern u8 D_807506C0[];
extern s32 D_8076A064;
extern void *D_807F5D10;
extern s32 D_807FBB64;

void effectSpawnSmoke(s32);
void actorClearMovementFlags(void *);
void hudSpawnTextScreen(s32);
extern ActorGlobalState D_807FBB70;
void func_80614EBC(Actor *, s32);
void func_8061CAD8(void);
void func_8061CB08(void);
s32 func_8061CC40(Actor *, s32, s32);
void func_8061F510(s32, s32);
void func_8062217C(void *, s32);
s32 func_80629148();
void func_806319C4(Actor *, s32);
void func_8063DA40(s32, s32);
void func_80641874(s32, s32);
void func_806BE674(s32);
void func_806BE6F0(void);
void actorDrawAnimatedEffect(void);
void func_8070D8C0(Actor *, s32, s32);
void func_8070E8DC(s32);
void func_80724CA4(s32, s32);
void func_80724E48(s32);
void func_80726EE0(s32);
s32 func_8072881C(s32, void *, void *);
void func_80728950(s32);
void func_807289B0(s32, s32);
void func_80729B00(void);
void func_8072A450(void);
void func_8072AB74(s32, f32, f32, s32, f32);
void func_8072B324(Actor *, s32);
s32 func_8072D13C(u8, s32);
void func_8072DC7C(s32);
void func_8072EC94(s32, s32);
s32 func_8073110C(s32, s32);
void func_8073129C(s32, s32, s32);
void renderCallbacksRegister(void *, void *, s32);
void sfxAllocateChannel(s32, f32);
void sfxStopChannel(s32, s32);
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
s32 func_80611A44(void);
void actorSpawnNodeEntryScaled(s32, f32, f32, f32, s32, s32, s32, s32);

void func_806BE8BC(void) {
    u8 sp37;
    s16 i;
    s16 j;
    s16 ang;
    u8 sel;

    sp37 = func_8073110C(0xF8, 0);
    func_80729B00();
    if (D_807FD580->unk1F0 & 0x100000) {
        LgBA->unk154 = 0x40;
        return;
    }
    if (!(LgBA->unk60 & 0x10)) {
        func_80724CA4(2, 1);
        D_807FDC98->unk46 |= 0x20;
        func_80614EBC(D_807FBB40, 0x306);
        func_80728950(0);
        LgBA->unk154 = 0x1E;
        LgBA->unk155 = 0;
        LgBA->unk15F = 0;
    }
    switch (LgBA->unk154) {
        case 0x26:
            func_80614EBC(D_807FBB40, 0x307);
            LgBA->unk154 = 0x27;
            LgBA->unk155 = 0;
            break;
        case 0x1E:
            effectSpawnSmoke(1);
            if (LgBA->unk128 < 0xFF) {
                LgBA->unk128 += 5;
            }
            if (func_80629148() != 0) {
                func_8063DA40(0x1F, 3);
                actorClearMovementFlags(D_807FBB4C);
                func_80726EE0(1);
                D_807FDC98->unk46 |= 4;
                func_806BE674(1);
                func_807289B0(0, 0);
                if (sp37 != 0) {
                    func_80641874(0x17, 0x14);
                    func_8070D8C0(D_807FBB40, 0x14, 1);
                } else {
                    func_8070D8C0(D_807FBB40, 0x14, 0);
                }
                func_80614EBC(D_807FBB40, 0x309);
                LgBA->unk154 = 0x1F;
                LgBA->unk155 = 0;
            }
            break;
        case 0x1F:
            sel = LgBA->unk155;
            switch (sel) {
                case 0:
                    if (func_80629148() != 0) {
                        func_8061CAD8();
                        func_8061CAD8();
                        LgBA->unk155++;
                        LgBA->unk168 = 0x78;
                    }
                    break;
                case 1:
                    renderCallbacksRegister(func_806BE6F0, D_807FBB40, 3);
                    break;
                case 2:
                    sfxAllocateChannel(0xA9, 1.0f);
                    D_807FBB64 |= 4;
                    func_8061CB08();
                    func_8062217C(D_807F5D10, 3);
                    func_80614EBC(D_807FBB40, 0x302);
                    func_8072B324(D_807FBB40, (s32)((sp37 ? 1.5 : 1.0) * (u32)LgB9C->unkD));
                    LgBA->unk154 = 2;
                    LgBA->unk155 = 0;
                    func_8061F510(1, 0xA);
                    LgBG->unk1F4 |= 0x40;
                    break;
            }
            break;
        case 0x27:
            if (LgBA->unk155 == 0) {
                sfxStopChannel(0xA9, 0);
                LgBA->unk60 &= ~0x8000;
                LgBA->unk128 = 0xFF;
                func_806BE674(0);
                func_8061CC40(D_807FBB40, 0xF, 5);
                LgBA->unkE6 = mathAngleBetweenPoints2D(LgBB->unk7C, LgBB->unk84, LgBA->unk7C, LgBA->unk84);
                func_8070D8C0(D_807FBB40, 0x14, 4);
                LgBA->unk154 = 0x37;
                LgBA->unk155 = 0;
                LgBA->unk80 = LgBA->unkA4;
            }
            break;
        case 0x28:
            sel = LgBA->unk155;
            switch (sel) {
                case 0:
                    sfxStopChannel(0xA9, 0);
                    LgBA->unk60 &= ~0x8000;
                    LgBA->unk128 = 0xFF;
                    func_806BE674(0);
                    func_8061CC40(D_807FBB40, 0x1F, 1);
                    LgBA->unkE6 = mathAngleBetweenPoints2D(LgBB->unk7C, LgBB->unk84, LgBA->unk7C, LgBA->unk84);
                    func_80614EBC(D_807FBB40, 0x308);
                    func_8070E8DC(1);
                    if (sp37 != 0) {
                        func_8070D8C0(D_807FBB40, 0x14, 3);
                    } else {
                        func_8070D8C0(D_807FBB40, 0x14, 2);
                    }
                    LgBA->unk155 = 1;
                    LgBA->unk80 = LgBA->unkA4;
                    break;
                case 1:
                    if (func_80629148() != 0) {
                        if (sp37 != 0) {
                            func_8063DA40(0x57, 0xA);
                            LgBS->unk1A |= 0x8000;
                        } else {
                            ang = LgBA->unkE6 - 0x12C;
                            sfxAllocateChannel(0x2F, 1.0f);
                            for (j = 0; j < 3; j++, ang += 0x12C) {
                                actorSpawnNodeEntryScaled(0x35, LgBA->unk7C, LgBA->unk80, LgBA->unk84, ang, 0x63, -1, 0);
                            }
                        }
                        func_8073129C(0xF8, 1, 0);
                        LgBA->unk154 = 0x37;
                        LgBA->unk155 = 0;
                        LgBA->unk80 = LgBA->unkA4;
                    }
                    break;
            }
            break;
        case 0x37:
            if (!(LgBA->unk60 & 0x2000000)) {
                func_8072DC7C(2);
                if (LgBA->unk155 != 0) {
                    D_807FBB64 &= ~4;
                    LgBG->unk23F = 2;
                    func_8061F510(1, 0);
                    LgBG->unk1F4 &= ~0x40;
                    func_8072EC94(0x16, 0);
                    func_80726EE0(2);
                    if (LgBS->unk1A & 0x8000) {
                        LgBA->unk154 = 0x40;
                    } else {
                        if (LgBA->unk4->unk64 != 0x308) {
                            hudSpawnTextScreen(2);
                        }
                        func_8063DA40(0x1F, 1);
                        LgBA->unk154 = 0x3C;
                    }
                }
            }
            break;
        case 0x13:
            func_80614EBC(D_807FBB40, 0x305);
            LgBA->unkC0 = 200.0f;
            LgBA->unk154 = 2;
            LgBA->unk155 = 0;
        default:
            if (LgBA->unk15F < 0x10U) {
                renderCallbacksRegister(actorDrawAnimatedEffect, D_807FBB40, 3);
            }
            if (((func_80611A44() >> 0xF) % 1000) >= 0x3DF && LgBA->unk4->unk64 == 0x302) {
                s32 a1;
                if (D_8076A064 & 1) {
                    a1 = 0x303;
                } else {
                    a1 = 0x304;
                }
                func_80614EBC(D_807FBB40, a1);
            }
            if (D_807FBB70.unk0 != 0) {
                if (D_807FBB70.unk1[0] >= D_807506C0[LgBA->unk15F] && LgBA->unk15F < 0x10U) {
                    if (D_807FBB70.unk1[0] != D_807506C0[LgBA->unk15F]) {
                        func_80614EBC(D_807FBB40, 0x301);
                        LgBA->unk154 = 0x27;
                        LgBA->unk155 = 0;
                    } else {
                        LgBA->unk15F++;
                        if (LgBA->unk15F >= 0x10U) {
                            func_8072EC94(0x16, 1);
                        }
                    }
                }
            }
            for (i = 0; i < D_807FBB70.unk254; i++) {
                if (D_807FBB70.unk258[i] == 3) {
                    LgBA->unk154 = 0x28;
                    LgBA->unk155 = 0;
                }
            }
            func_8072881C(0, LgBS->unk28, &D_807FBB70);
            func_8072AB74(LgBA->unk154, LgBS->unkA, LgBS->unkE, 0x10, 0.0f);
            func_8072D13C(LgBA->unk154, 0);
            break;
    }
    if (LgBA->unk4->unk64 == 0x301 || LgBA->unk4->unk64 == 0x302) {
        func_80724E48(0);
    }
    func_8072A450();
    func_806319C4(D_807FBB40, 0);
}

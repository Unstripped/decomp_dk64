// func_806B54BC (src/global/B7490.c): Stage 4: frame 0x70 and s0/s1/s2 (&D_807FBB40 hoisted) ok when no temp_s0 local is declared (use D_807FBB40-> everywhere; compiler caches it in s0). 375 insns vs 373. Remaining: var_v0 lands in v1 (target v0), sp68/64/60/5C stack slot offsets +4 (target has one more 4-byte slot above sp68 and one below sp5C; temp_ft0 duplicate of sp5C causes extra store), clamp of temp_ft4 to +-8.0 should use (f64)sp64 compares without extra f64 local (var_fv0 local adds 8 bytes to frame).
typedef struct M6ActorX {
    /* 0x000 */ u8 pad0[0x6E];
    /* 0x06E */ s16 unk6E;
    /* 0x070 */ u8 pad70[0x50];
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ f32 unkC4;
    /* 0x0C8 */ u8 padC8[0x1E];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ s16 unkE8;
    /* 0x0EA */ u8 padEA[2];
    /* 0x0EC */ s16 unkEC;
    /* 0x0EE */ u8 padEE[0x46];
    /* 0x134 */ s16 unk134;
    /* 0x136 */ u8 pad136[0x1E];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[0x22];
    /* 0x178 */ s16 *unk178;
} M6ActorX;

typedef struct M6State98 {
    /* 0x00 */ u8 pad0[0x46];
    /* 0x46 */ u16 unk46;
} M6State98;

typedef struct M6State178 {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
} M6State178;

extern Actor *D_807FBB40;
extern ActorGlobalState D_807FBB70;
extern M6State90 *D_807FDC90;
extern Actor *D_807FDC94;
extern M6State98 *D_807FDC98;
extern M6State9C *D_807FDC9C;
extern u32 D_8076A064;
void func_80729B00(void);
void func_806319C4(void *, s32);
void func_8072881C();
extern u16 D_80744508;
extern Actor *D_807FBB4C;
void func_80614EBC(void *, s32);
void sfxPlayActorSound(Actor *, s32, s32, s32, s32, s32, f32, s32);
void sfxStopSlotSound(Actor *, s32);
void func_8072B7CC(s32);
s32 func_80611A44();
s32 func_806119A0(void);
f32 func_806119FC(void);
f32 func_80612790(s16);
f32 func_80612794(s16);
s32 func_806CC10C(s16, s16);
void func_80724B5C(s32, s32, f32 *, f32 *, f32 *);
s32 func_8073110C(s32, s32);
void func_8063DA40(s32, s32);
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
void sfxPlayFromActorWithAltitudeCheck(Actor *, s32, s32, s32, s32);

void func_806B54BC(void) {
    f32 sp68;
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    f32 temp_ft0;
    f32 temp_ft4;
    s16 D_807FBB40_3;
    M6State178 *temp_s1;
    u8 var_v0;

    temp_s1 = (M6State178 *) ((M6ActorX *) D_807FBB40)->unk178;
    func_80729B00();
    if ((D_807FBB40->unk154 != 0x40) && (D_807FBB40->unk154 != 0x37) && ((D_807FBB70.unk200 == 9) || (D_807FBB70.unk15 != 0))) {
        sfxStopSlotSound(D_807FBB40, 0);
        func_80614EBC(D_807FBB40, 0x331);
        D_807FBB40->unk154 = 0x37;
        D_807FBB40->unk155[0] = 0;
        sfxPlayFromActorWithAltitudeCheck(D_807FBB4C, 0x16, 0xFF, 0x7F, 0x1E);
    }
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FDC98->unk46 = D_807FDC98->unk46 | 0x20;
        D_807FDC98->unk46 = D_807FDC98->unk46 & 0xFFF7;
        D_807FBB40->unkB8 = 40.0f;
        D_807FBB40->unk154 = 0x23;
        D_807FBB40->unk155[0] = 0;
        ((M6ActorX *) D_807FBB40)->unkEC = ((func_80611A44() >> 15) % 7) + 0xF;
        temp_s1->unk0 = D_807FBB40->unk7C;
        temp_s1->unk4 = D_807FBB40->unk80;
        temp_s1->unk8 = D_807FBB40->unk84;
        temp_s1->unk10 = 1;
        temp_s1->unkC = D_807FBB40->unk80;
        temp_s1->unk12 = (func_806119A0() & 0xFF) + 0x78;
    }
    var_v0 = D_807FBB40->unk154;
    if ((var_v0 != 0x37) && (((M6ActorX *) D_807FBB40)->unk6E == -1)) {
        sfxPlayActorSound(D_807FBB40, 0x10E, 0, 0, 0, 0xFF, 1.0f, 0);
        var_v0 = D_807FBB40->unk154;
    }
    switch (var_v0) {
    case 0x26:
        temp_s1->unk0 = D_807FBB4C->unk7C;
        temp_s1->unk4 = D_807FBB4C->unk80;
        temp_s1->unk8 = D_807FBB4C->unk84;
        temp_s1->unk12 = (func_806119A0() & 0xFF) + 0x78;
    case 0x23:
        ((M6ActorX *) D_807FBB40)->unkE6 = ((M6ActorX *) D_807FBB40)->unkE6 - (func_806CC10C(mathAngleBetweenPoints2D(D_807FBB40->unk7C, D_807FBB40->unk84, temp_s1->unk0, temp_s1->unk8) + 0x800, ((M6ActorX *) D_807FBB40)->unkE6) >> 4);
        temp_s1->unk10 = temp_s1->unk10 - 1;
        if (temp_s1->unk10 <= 0) {
            func_80724B5C(1, 0, &sp68, &sp64, &sp60);
            temp_s1->unk10 = (func_806119A0() & 0x3F) + 0xF;
            D_807FBB40_3 = mathAngleBetweenPoints2D(sp68, sp60, temp_s1->unk0, temp_s1->unk8);
            D_807FBB40_3 = D_807FBB40_3 + ((func_806119A0() & 7) << 8) + 0x400;
            temp_ft0 = (f32) ((f64) func_806119FC() * 180.0);
            sp5C = temp_ft0;
            temp_s1->unk4 = temp_s1->unkC;
            temp_s1->unk0 = (func_80612794(D_807FBB40_3) * sp5C) + sp68;
            temp_s1->unk8 = (func_80612790(D_807FBB40_3) * temp_ft0) + sp60;
            D_807FBB40->unk154 = 0x23;
        }
        if (D_807FBB40->unk154 == 0x23) {
            temp_s1->unk12 = temp_s1->unk12 - 1;
            if (temp_s1->unk12 <= 0) {
                temp_s1->unk10 = 0x3C;
                D_807FBB40->unk154 = 0x26;
            }
        }
        temp_ft4 = (f32) ((f64) (temp_s1->unk4 - D_807FBB40->unk80) * 0.0625);
        sp64 = temp_ft4;
        if ((f64) temp_ft4 > 8.0) {
            sp64 = 8.0f;
        }
        if ((f64) sp64 < -8.0) {
            sp64 = -8.0f;
        }
        D_807FBB40->unk7C = (f32) ((f64) D_807FBB40->unk7C + ((f64) func_80612794(((M6ActorX *) D_807FBB40)->unkE6) * 8.0));
        D_807FBB40->unk80 = D_807FBB40->unk80 + sp64;
        D_807FBB40->unk84 = (f32) ((f64) D_807FBB40->unk84 + ((f64) func_80612790(((M6ActorX *) D_807FBB40)->unkE6) * 8.0));
        break;
    case 0x37:
        D_807FBB40->unk60 = D_807FBB40->unk60 & 0xFFFF7FFF;
        D_807FBB40->unk128 = D_807FBB40->unk128 - 8;
        D_807FBB40->unk80 = (f32) ((f64) D_807FBB40->unk80 - 10.0);
        if (D_807FBB40->unk128 < 0) {
            D_807FBB40->unk128 = 0;
            D_807FBB40->unk154 = 0x40;
            D_807FBB40->unk155[0] = 0;
            D_807FBB40->unk144 = 1;
            if (D_8076A0A8 == 0xA7) {
                D_80744508 = D_80744508 + 1;
                if ((D_80744508 == 5) && (func_8073110C(0x15F, 0) == 0)) {
                    func_8063DA40(4, 0xA);
                }
            }
        }
        break;
    default:
        func_8072B7CC(0x32F);
        break;
    }
    func_806319C4(D_807FBB40, 0);
}

// func_806E225C (src/global/E4090.c): text-identical, reloc only: all 561 insns equal expected; only diffs are .rodata+off vs jtbl_8075D154/D_8075D16C/D_8075D170/D_8075D174/jtbl_8075D178 relocs. Needs K&R def (arg0,arg1 u8), s32 func_806F8AD4(u8,u8) prototype (file has (s32,s32)), s32 func_80714C08 return; arg0 must be tested as !arg0/arg0 (not ==0/!=0) to avoid a CSE spill; dz/dx f32 pads fix frame 0x70. Stage 6 reached.
// Needs (not in this file yet): s32 func_806F8AD4(u8, u8) (currently (s32, s32) at top of E4090.c).
s32 func_806F8AD4(u8, u8);
void func_806F8BC4(s32, s32, s32);
f32 func_80611BB4(f32, f32);
f32 sqrtf(f32);
extern struct G31Cam *D_807FC924;

typedef struct LE40Player {
    /* 0x000 */ u8 pad0[0x8E];
    /* 0x08E */ u8 unk8E;
    /* 0x08F */ u8 unk8F;
    /* 0x090 */ u8 unk90;
    /* 0x091 */ u8 unk91;
    /* 0x092 */ u8 pad92[0x104 - 0x92];
    /* 0x104 */ s32 unk104;
    /* 0x108 */ u8 pad108[0x1A4 - 0x108];
    /* 0x1A4 */ u8 unk1A4;
} LE40Player;

#define LE40_S ((LE40Player *)D_807FD580)
#define LE40_PAD(sym, T) (*(T *)((u8 *)&(sym) + D_807FC929 * 0x34))

extern u8 D_8071FBC8;
extern u8 D_807200D4;
extern f32 D_80753E2C[];
extern u8 *D_807FD568;
void func_8071A8B0(void);
s32 mathAngleBetweenPoints2D(f32, f32, f32, f32);
void projectileGetTargetCoords(void *, s32);
void projectileSetSpawnFlag(void);
void projectileSetTargetCoords(f32, f32, f32);
void projectileSpawnNodeEntry(s32, s32, f32, s16, f32, f32, void *);
void func_8060E7EC(u8, u8, s32);
void func_8061F0B0(s32, s32, s32);
s32 func_80672630(void *, s32, s32);
void func_80714950(s32);
s32 func_80714C08(void *, f32, Actor *, s32, s32);
f32 func_80612D10(f32);
f32 func_80612D1C(f32);
u8 func_806E2B20(void *);
void func_806E2C74(Actor *);
s32 actorIsActiveType2B(Actor *);
s32 func_80609140(s32, s32, f32, f32, s32, s32);
void sfxPlayFromActorWithAltitudeCheck(void *, s32, s32, s32, s32);
extern s16 D_80753E64[];
s32 func_80714608(s32);
s32 func_8067ACDC(void *, s32, s32);
void func_806F0C18(void *);
void func_806CFF9C(Actor *);
void func_806F91B4(s32, s32, s32);
void func_807149B8(s32);
void func_8071498C(void *);

typedef struct LE40Obj {
    /* 0x000 */ u8 pad0[0x210];
    /* 0x210 */ f32 unk210;
    /* 0x214 */ f32 unk214;
    /* 0x218 */ f32 unk218;
    /* 0x21C */ u8 pad21C[0xC];
    /* 0x228 */ f32 unk228;
    /* 0x22C */ f32 unk22C;
    /* 0x230 */ f32 unk230;
} LE40Obj;

#define LE40_OBJ ((LE40Obj *)((u8 *)D_807FC924 + D_807FC929 * 0x2F0))

void func_806E225C(arg0, arg1)
u8 arg0;
u8 arg1;
{
    s16 spawnId;
    f32 scale;
    u16 sfx;
    u8 vol;
    f32 dz;
    f32 dx;
    f32 ang2;
    f32 sp54;
    f32 sp50;
    s32 flags;
    s32 sel;
    s16 ang;
    s32 hasFlag;

    if ((LE40_PAD(D_807FD63C, u16) & 0x4000) || arg1) {
        flags = D_807FD568[2];
        if ((flags & 2) && func_806F8AD4(3, D_807FC929)) {
            sel = 3;
        } else {
            flags &= ~2;
            sel = 2;
        }
        if (!arg0) {
            flags &= ~4;
        }
        func_806F8BC4(sel, 0, 0);
        if (func_806F8AD4((u8)sel, D_807FC929)) {
            if (func_8067ACDC(D_807FBB40, 4, (s32)actorIsActiveType2B) < D_80753E64[D_807FD584]) {
                hasFlag = flags & 2;
                func_806F91B4(sel, D_807FC929, -1);
                if (!arg0) {
                    s32 v = LE40_S->unk8F + 1;
                    if (v >= 0x15) {
                        LE40_S->unk8F = 0x14;
                    } else {
                        LE40_S->unk8F = v;
                    }
                }
                func_8060E7EC(LE40_S->unk1A4, 0xFF, 3);
                switch (D_807FBB40->unk58) {
                    case 7:
                        spawnId = 0xAB;
                        scale = 0.5f;
                        LE40_S->unk8E = 0x1A;
                        sfx = 0x2A5;
                        vol = 5;
                        if (!arg0) {
                            func_8061F0B0(LE40_S->unk104, 7, 7);
                        }
                        break;
                    case 6:
                        spawnId = 0x26;
                        scale = 0.5f;
                        LE40_S->unk8E = 0x1A;
                        sfx = 0x2A5;
                        vol = 5;
                        if (!arg0) {
                            func_8061F0B0(LE40_S->unk104, 7, 7);
                        }
                        break;
                    case 4:
                        sfx = 0x77;
                        vol = 2;
                        spawnId = 0x2A;
                        scale = 0.5f;
                        break;
                    case 5:
                        spawnId = 0x2B;
                        scale = 0.36f;
                        sfx = 0xEF;
                        vol = 0;
                        LE40_S->unk8E = 4;
                        break;
                    case 2:
                        spawnId = 0x30;
                        scale = 0.3f;
                        sfx = 0x7B;
                        vol = 5;
                        LE40_S->unk8E = 0x1A;
                        break;
                    default:
                        spawnId = 0x24;
                        scale = 0.3f;
                        sfx = 0x7A;
                        vol = 5;
                        LE40_S->unk8E = 0x1A;
                        break;
                }
                if (arg0) {
                    func_80609140((s16)sfx, 0x7FFF, 63.0f, 1.0f, vol, 0);
                } else {
                    sfxPlayFromActorWithAltitudeCheck(D_807FBB40, (s16)sfx, 0xFF, 0x7F, vol);
                }
                if (hasFlag != 0) {
                    if (arg0) {
                        func_80609140(0x1EE, 0x7FFF, 63.0f, 1.0f, 0x1E, 0);
                    } else {
                        sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x1EE, 0xFF, 0x7F, 0xA);
                    }
                }
                LE40_S->unk91 = LE40_S->unk90;
                if (arg0) {
                    ang = mathAngleBetweenPoints2D(LE40_OBJ->unk228, LE40_OBJ->unk230, LE40_OBJ->unk210, LE40_OBJ->unk218);
                } else {
                    ang = D_807FBB40->unkE6;
                }
                if (D_807FBB40->unk58 == 4) {
                    if ((!arg0 && func_806E2B20(D_807FBB40)) || func_80672630(D_807FBB40, ang, 0) == 0) {
                        projectileSetSpawnFlag();
                    }
                } else if (func_80672630(D_807FBB40, ang, 0) == 0) {
                    projectileSetSpawnFlag();
                }
                if (arg0) {
                    ang2 = LE40_OBJ->unk218;
                    projectileSetTargetCoords(LE40_OBJ->unk210, LE40_OBJ->unk214, ang2);
                    dz = LE40_OBJ->unk230 - LE40_OBJ->unk218;
                    dx = LE40_OBJ->unk228 - LE40_OBJ->unk210;
                    ang2 = func_80611BB4(LE40_OBJ->unk22C - LE40_OBJ->unk214, sqrtf(dz * dz + dx * dx));
                    sp50 = D_80753E2C[D_807FD584] * func_80612D1C(ang2);
                    sp54 = D_80753E2C[D_807FD584] * func_80612D10(ang2);
                    projectileSpawnNodeEntry(spawnId, (s16)flags, scale,
                                             mathAngleBetweenPoints2D(LE40_OBJ->unk228, LE40_OBJ->unk230, LE40_OBJ->unk210, LE40_OBJ->unk218),
                                             sp54, sp50, D_807FBB48);
                } else {
                    if ((D_807FBB40->unk58 == 2 || D_807FBB40->unk58 == 3 || D_807FBB40->unk58 == 6 || D_807FBB40->unk58 == 7)) {
                        func_807149B8(1);
                        func_80714950(0x50);
                        func_8071498C(func_8071A8B0);
                        func_80714C08(&D_807200D4, 0.5f, D_807FBB48, LE40_S->unk90 + 9, 2);
                        if (D_807FBB40->unk58 == 6 || D_807FBB40->unk58 == 7) {
                            func_807149B8(1);
                            func_80714950(0x50);
                            func_8071498C(func_8071A8B0);
                            func_80714C08(&D_8071FBC8, 0.5f, D_807FBB48, 9, 2);
                        }
                    }
                    projectileGetTargetCoords(D_807FBB48, LE40_S->unk90 + 9);
                    projectileSpawnNodeEntry(spawnId, (s16)flags, scale, D_807FBB48->unkE6, D_80753E2C[D_807FD584], 0.0f, D_807FBB48);
                }
                if ((func_80714608(0) != 0) && (func_806F8AD4((u8)sel, D_807FC929) == 0)) {
                    func_806F0C18(D_807FBB40);
                    func_806CFF9C(D_807FBB40);
                }
                func_806E2C74(D_807FBB40);
            }
        } else {
            switch (D_807FBB40->unk58) {
                case 6:
                case 7:
                    sfx = 0x190;
                    vol = 5;
                    break;
                case 4:
                    sfx = 0x77;
                    vol = 2;
                    break;
                case 5:
                    sfx = 0x7C;
                    vol = 0;
                    break;
                case 2:
                    sfx = 0xB0;
                    vol = 0xA;
                    LE40_S->unk8E = 0x1A;
                    break;
                default:
                    sfx = 0x83;
                    vol = 5;
                    break;
            }
            if (arg0) {
                func_80609140((s16)sfx, 0x7FFF, 63.0f, 1.0f, vol, 0);
                return;
            }
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, (s16)sfx, 0xFF, 0x7F, vol);
        }
    }
}

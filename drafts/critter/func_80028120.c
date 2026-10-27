// func_80028120 (src/critter/3340.c): stage 5-6: size/frame(0x68)/stack slots/jump table/rodata identical; only float scratch numbering differs (78 diff lines): target keeps case-1 'radius' (rand*65.0, also case-2 k=3/dist, one shared f32) coloured f2 (fv1, swc1 in jal delay), mine uncoloured (uopt adjsave<0, scratch f8/f10). Matched via: angleTmp s32 local (lh 0x4A(sp) idiom), (s16)angleTmp for sin/cos args, v/t shared (t=(t-0.5)*2.5 clamp), unused f32 v + k + near + angleTmp decl order for slots, case 0xB: break for 12-entry jtbl, store order unk4,unk0,unk14,unk1C. Tried: radius/k merge, register, block-scope, decl order, permuter (noise)
typedef struct J1b2Data {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
} J1b2Data;

typedef struct J1b2Sub {
    char pad0[4];
    f32 unk4;
} J1b2Sub;

typedef struct J1b2Actor {
    char pad0[4];
    J1b2Sub **unk4;
    char pad8[0x60 - 8];
    s32 unk60;
    char pad64[0x7C - 0x64];
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    char pad88[0xE6 - 0x88];
    s16 unkE6;
    char padE8[0x154 - 0xE8];
    u8 unk154;
    char pad155[0x15E - 0x155];
    u8 unk15E;
    char pad15F[0x160 - 0x15F];
    u32 unk160;
    char pad164[0x174 - 0x164];
    J1b2Data *unk174;
} J1b2Actor;

#define J1b2A ((J1b2Actor *)D_807FBB40)

extern u16 D_807ECD48;
extern u8 D_807FBD70;
s32 camIsCutsceneActive(void);
f32 func_806119FC(void);
f32 func_80612790(s16);
f32 func_80612794(s16);
s16 mathAngleBetweenPoints2D(f32, f32, f32, f32);
s32 func_806CC10C(s16, s16);
void func_8065D254(Actor_3340 *, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32);
void func_80665564(Actor_3340 *, s32);
u8 func_8072881C(u8, u32 *);
f32 sqrtf(f32);

void func_80028120(void) {
    f32 dx;
    f32 dz;
    f32 k;
    f32 v;
    f32 t;
    f32 w;
    s32 near;
    s32 angleTmp;
    J1b2Data *d;
    J1b2Sub *sub;

    d = J1b2A->unk174;
    sub = *J1b2A->unk4;
    if (!(J1b2A->unk60 & 0x10)) {
        J1b2A->unk154 = 0x78;
        if (flagGet(0x189, 0) != 0) {
            if (flagGet(0x23, 1) == 0) {
                J1b2A->unk154 = 1;
            } else if (flagGet(0x18A, 0) == 0) {
                if (flagGet(0x24, 1) != 0) {
                    J1b2A->unk154 = 0xA;
                } else {
                    J1b2A->unk154 = 0x64;
                }
            }
            actorScriptStart(D_807FBB40, 0x43B);
        } else {
            J1b2A->unk154 = 0;
        }
        d->unk20 = J1b2A->unk7C;
        d->unk24 = J1b2A->unk80;
        d->unk28 = J1b2A->unk84;
        d->unk4 = 0.028571429f;
        d->unk0 = 2.0f;
        d->unk14 = d->unk20;
        d->unk1C = d->unk28;
    }
    dx = J1b2A->unk7C - ((J1b2Actor *)D_807FBB4C)->unk7C;
    dz = J1b2A->unk84 - ((J1b2Actor *)D_807FBB4C)->unk84;
    if (J1b2A->unk154 != 1) {
        J1b2A->unkE6 = J1b2A->unkE6 - (func_806CC10C(mathAngleBetweenPoints2D(((J1b2Actor *)D_807FBB4C)->unk7C, ((J1b2Actor *)D_807FBB4C)->unk84, J1b2A->unk7C, J1b2A->unk84), J1b2A->unkE6) >> 3);
    }
    J1b2A->unk15E = 0xF;
    switch (J1b2A->unk154) {
    case 0:
        if (flagGet(0x189, 0) != 0) {
            actorScriptStart(D_807FBB40, 0x43B);
            J1b2A->unk154 = 1;
        }
        break;
    case 0x64:
        near = (dx * dx) + (dz * dz) < 2500.0f;
        if (near != 0 && (D_807ECD48 & 0x8000)) {
            camStartPath(D_807FBB40, 4, 1);
            currentActorClearFlag();
            J1b2A->unk154 = 0x65;
        }
        if (flagGet(0x24, 1) != 0) {
            J1b2A->unk154 = 0xA;
        }
        break;
    case 0x65:
        if (camIsCutsceneActive() == 0) {
            J1b2A->unk154 = 0x64;
        }
        break;
    case 1: {
        t = sub->unk4 / 19.0;
        if (t < d->unk0) {
            d->unk8 = J1b2A->unk7C;
            d->unkC = d->unk24;
            d->unk10 = J1b2A->unk84;
            angleTmp = (s32)(func_806119FC() * 4096.0);
            k = func_806119FC() * 65.0;
            d->unk14 = (func_80612790((s16)angleTmp) * k) + d->unk20;
            d->unk18 = d->unk24;
            d->unk1C = (func_80612794((s16)angleTmp) * k) + d->unk28;
        }
        d->unk0 = t;
        t = (t - 0.5) * 2.5;
        if (t > 1.0) {
            t = 1.0f;
        }
        if (t < 0.0) {
            t = 0.0f;
        }
        J1b2A->unk7C = d->unk8 + (t * (d->unk14 - d->unk8));
        J1b2A->unk84 = d->unk10 + (t * (d->unk1C - d->unk10));
        if (D_807FBD70 == 4) {
            actorScriptStart(D_807FBB40, 0x43C);
            J1b2A->unk154 = 2;
            d->unk0 = 0.0f;
        }
        break;
    }
    case 2:
        d->unk0 = d->unk0 + 1.0;
        if (d->unk0 > 49.0) {
            camStartPath(D_807FBB40, 2, 1);
            currentActorClearFlag();
            d->unk0 = 0.0f;
            J1b2A->unk154 = 0x64;
        } else if (d->unk0 < 20.0) {
            f64 dist;

            dist = sqrtf((dx * dx) + (dz * dz));
            if (dist > 1.0) {
                k = 3.0 / dist;
                J1b2A->unk7C = J1b2A->unk7C + (dx * k);
                J1b2A->unk84 = J1b2A->unk84 + (dz * k);
            }
        }
        break;
    case 0xA:
        near = (dx * dx) + (dz * dz) < 2500.0f;
        if (near != 0) {
            J1b2A->unk154 = 0xB;
            camStartPath(D_807FBB40, 3, 1);
        }
        break;
    case 0xB:
        break;
    }
    func_8072881C(0, &J1b2A->unk160);
    if (J1b2A->unk154 == 0) {
        J1b2A->unk60 = J1b2A->unk60 & ~4;
    } else {
        J1b2A->unk60 = J1b2A->unk60 | 4;
        func_80665564(D_807FBB40, 0);
        func_8065D254(D_807FBB40, 0x3C8, 0x40, 0x40, 0x23, 0xF, 1, 0x4B, 0x78, J1b2A->unkE6, 1.0f);
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

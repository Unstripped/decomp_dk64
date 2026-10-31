// func_806809F0 (src/global/80150.c): W2Loop stage 5 (1 insn diff). Matches except sub-call arg: func_807149B8(1) in coord block emits 'move a0,t0' (target 'li a0,1'). Needs protos: sfxPlayFromActorWithAltitudeCheck(Actor*,s32,s32,s32,u8) (5th u8: arg joins v0 const-1 web) and func_806C7BAC(void*,Actor*) (call w/o (s32) cast fixes lui a0 vs v0). func_807149B8(u16) would fix the last line but breaks tagBarrelDespawnEffects (andi). Key levers: first loop is switch(*unk278[i]){case 2:..;default:break;} (LFTR to pointer walk only with 2-way switch); ptr local 's16 *ptr' in pad8C slot; kong s16 local replacing pad0[2]; temp_f=(0.15-x)/0.13 then (s32)(temp_f*400.0f); if/else for sp8A; sub->unkD -= 1; FAKE if(D_8076A0A8==0){} after sub=.
typedef struct Lg809_TagBarrelState {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ u8 unkC;
    /* 0x0D */ u8 unkD;
    /* 0x0E */ u8 unkE;
} Lg809_TagBarrelState;

typedef struct Lg809_ActorSpawnParams {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 pad0C[0xC];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
} Lg809_ActorSpawnParams;

typedef struct Lg809_Vec3f {
    f32 x;
    f32 y;
    f32 z;
} Lg809_Vec3f;

typedef struct Lg809_PlayerState {
    u8 pad0[0xBC];
    s16 unkBC;
    s16 unkBE;
    u8 padC0[0x1A3 - 0xC0];
    u8 unk1A3;
} Lg809_PlayerState;

extern Lg809_Vec3f D_8074E7D4;
extern u8 D_8076A0B1;
extern u8 D_807FBD70;
extern u8 D_807FBDC4;
extern u8 D_8071FC58[];
extern s32 func_80716FB4;
void effectOrbitXZUpdate();

s32 func_8073195C(s16);
void actorListSetPosByActor(Actor *, f32, f32, f32);
void *actorFindByType(s32);
void actorSetCustomFloat(Actor *, s16, f32);
void func_805FF9AC(s16, s16, s16, s16);
void actorSetCustomInt(Actor *, s16, s32);
void actorSpawnNodeEntryScaled(s32, f32, f32, f32, s32, s32, s32, s32);

extern s16 D_80750390;
void func_80714A28(s32);
void sfxAllocateChannel(s32, f32);
void func_806C7BAC(void *, Actor *);

void func_806809F0(void) {
    s16 kong;
    s16 pad0;
    f32 coord[3];
    s32 i;
    Lg809_Vec3f sp90;
    s16 *ptr;
    s16 sp8A;
    f32 dist;
    u8 sp83;
    Lg809_TagBarrelState *sub;
    f32 temp_f;
    u32 val;
    f32 temp_f2;
    s16 angle;
    f32 yOffset;

    sub = (Lg809_TagBarrelState *)D_807FBB40->unk174;
    if (D_8076A0A8 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    sp90 = D_8074E7D4;
    sp83 = 0;
    if (!(D_807FBB40->unk60 & 0x10)) {
        temp_f = (f64)D_807FBB40->unk4->unk34 / 0.15;
        D_807FBB40->unkA4 = D_807FBB40->unk80;
        actorUpdateFloorContactAndTilt(D_807FBB40, 0.0f);
        D_807FBB40->unk110 = 0;
        D_807FBB40->unk60 |= 2;
        sub->unk0 = D_807FBB40->unk80;
        sub->unk4 = 0;
        sub->unk6 = ((Lg809_ActorSpawnParams *)D_807FBB40->unk124)->unk0;
        sub->unkA = ((Lg809_ActorSpawnParams *)D_807FBB40->unk124)->unk8;
        sub->unkE = 0;
        if (D_807FBB40->unk58 == 0x1C) {
            if (flagGet(func_8073195C(sub->unkA), 0)) {
                actorDespawn(D_807FBB40);
            }
        }
        D_807FBB40->unk132 = 1;
        if (((Lg809_ActorSpawnParams *)D_807FBB40->unk124)->unk1C == 1.0 || ((Lg809_ActorSpawnParams *)D_807FBB40->unk124)->unk1C == 2.0) {
            D_807FBB40->unk154 = 0xA;
            sub->unkD = 0x14;
            D_807FBB40->unk4->unk34 = 0.02f;
            D_807FBB40->unk4->unk38 = 0.02f;
            D_807FBB40->unk4->unk3C = 0.02f;
            if (((Lg809_ActorSpawnParams *)D_807FBB40->unk124)->unk1C == 2.0) {
                sub->unkC = 1;
            } else {
                sub->unkC = 0;
            }
        } else if (((Lg809_ActorSpawnParams *)D_807FBB40->unk124)->unk4 == 1) {
            D_807FBB40->unk154 = 0x14;
            D_807FBB40->unk144 = 1;
            D_807FBB40->unk60 &= ~0x8000;
            D_807FBB40->unk128 = 0;
        } else {
            D_807FBB40->unk154 = 0;
        }
        temp_f = (f64)temp_f - 1.0;
        if ((f64)temp_f < 0.0) {
            temp_f = 0.0f;
        }
        val = (u32)(80.0f * temp_f + 20.0f);
        D_807FBB40->unk12C[4] = val;
        D_807FBB40->unk12C[5] = val;
    }
    for (i = 0; i < D_807FBDC4; i++) {
        ptr = D_807FBB70.unk278[i];
        switch (*ptr) {
            case 2:
                sub->unkE = 0x8C;
                break;
            default:
                break;
        }
    }
    if (sub->unkE != 0) {
        sub->unkE--;
        sub->unk0 = (f64)sub->unk0 + 1.0;
        actorListSetPosByActor(D_807FBB40, D_807FBB40->unk7C, sub->unk0, D_807FBB40->unk84);
    }
    if (D_807FBB40->unk154 != 0x14 && D_807FBB40->unk154 != 0x15) {
        tagBarrelCheckPlayerCollision();
    }
    if (D_8076A0A8 == 0xAA) {
        if (D_807FBB40->unk154 != 0xA && D_807FBB40->unk154 != 0xB && D_807FBB40->unk154 != 0xC && D_807FBB40->unk154 != 0x1E) {
            if (((R2FStructD580 *)D_807FD580)->unk1F0 & 0x40) {
                D_807FBB40->unk144 = 2;
                D_807FBB40->unk60 |= 0x8000;
            } else {
                sp83 = 1;
                D_807FBB40->unk144 = 1;
                D_807FBB40->unk60 &= ~0x8000;
                D_807FBB40->unk128 = 0;
            }
        }
    }
    if ((D_807FBB40->unk60 & 0x100) && (D_807FBB40->unk154 == 0 || D_807FBB40->unk154 == 1 || (D_807FBB40->unk154 >= 0xA && D_807FBB40->unk154 < 0xD)) && sp83 == 0) {
        dist = (D_807FC924->unk218 - D_807FBB40->unk84) * (D_807FC924->unk218 - D_807FBB40->unk84) +
               ((D_807FC924->unk210 - D_807FBB40->unk7C) * (D_807FC924->unk210 - D_807FBB40->unk7C) +
                (D_807FC924->unk214 - D_807FBB40->unk80) * (D_807FC924->unk214 - D_807FBB40->unk80));
        if (dist < 40000.0f) {
            temp_f2 = (f64)D_807FBB40->unk4->unk34 / 0.15;
            coord[2] = ((f64)((randomNonNegative() >> 15) % (s32)(30.0f * temp_f2)) - (15.0 * (f64)temp_f2)) + D_807FBB40->unk7C;
            coord[1] = ((f64)((randomNonNegative() >> 15) % (s32)(30.0f * temp_f2)) - (15.0 * (f64)temp_f2)) + D_807FBB40->unk80;
            coord[0] = ((f64)((randomNonNegative() >> 15) % (s32)(30.0f * temp_f2)) - (15.0 * (f64)temp_f2)) + D_807FBB40->unk84;
            func_807149B8(1);
            func_80714A28(4);
            if (D_807FBB40->unk154 == 0) {
                func_8071498C(&func_80716FB4);
                func_80714CC0(D_8071FC58, 0.5f, coord[2], coord[1], coord[0]);
            } else {
                func_80714950((s32)(D_807FBB40->unk4->unk34 * 100.0f) + (sub->unk8 << 16));
                func_8071498C(effectOrbitXZUpdate);
                func_80714CC0(D_8071FC58, 0.5f, D_807FBB40->unk7C, coord[1], D_807FBB40->unk84);
            }
        }
    }
    func_8067ACB4(D_807FBB40);
    switch (D_807FBB40->unk154) {
    case 0:
        if (D_807FBD70 == 4) {
            D_807FBB40->unk154 = 1;
            D_807FBB40->unk144 = 1;
            sub->unk8 = 0;
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x261, 0xFF, 0x64, 1);
            camStartPath(NULL, 0x1F, 5);
            if (actorFindByType(0x25) != NULL) {
                actorSetCustomFloat(D_807FBB40, 6, 1.0f);
            } else {
                actorSetCustomFloat(D_807FBB40, 6, 0.0f);
            }
        } else {
            for (i = 0; i < D_807FBDC4; i++) {
                if (D_807FBB70.unk258[i] == 1 && *D_807FBB70.unk278[i] == 1) {
                    D_807FBB40->unk154 = 0x14;
                    D_807FBB40->unk144 = 1;
                    D_807FBB40->unk60 &= ~0x8000;
                    D_807FBB40->unk128 = 0;
                }
            }
        }
        break;
    case 1:
        sub->unk8 += 0x1E;
        if (sub->unk8 >= 0x191) {
            sub->unk8 = 0x190;
        }
        D_807FBB40->unkE6 += sub->unk8;
        if (sub->unk8 >= 0xC9) {
            D_807FBB40->unk4->unk34 = (f64)D_807FBB40->unk4->unk34 - 0.005;
            D_807FBB40->unk4->unk38 = (f64)D_807FBB40->unk4->unk38 - 0.005;
            D_807FBB40->unk4->unk3C = (f64)D_807FBB40->unk4->unk3C - 0.005;
            if ((f64)D_807FBB40->unk4->unk34 < 0.02) {
                D_807FBB40->unk154 = 2;
            }
        }
        break;
    case 2:
        actorSetCustomFloat(D_807FBB40, 7, 1.0f);
        if (!(D_8076A0B1 & 1) || D_807FBB40->unk58 != 0x6B) {
            func_805FF9AC(sub->unk6, 0, 0, 3);
        }
        actorDespawn(D_807FBB40);
        break;
    case 10:
        if (sub->unkD != 0) {
            sub->unkD -= 1;
        }
        if (sub->unkD == 5) {
            D_807FBB40->unk144 = 1;
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x262, 0xFF, 0x64, 1);
        }
        if (sub->unkD == 0) {
            D_807FBB40->unk4->unk34 = (f64)D_807FBB40->unk4->unk34 + 0.005;
            D_807FBB40->unk4->unk38 = (f64)D_807FBB40->unk4->unk38 + 0.005;
            D_807FBB40->unk4->unk3C = (f64)D_807FBB40->unk4->unk3C + 0.005;
            if ((f64)D_807FBB40->unk4->unk34 >= 0.15) {
                D_807FBB40->unk154 = 0xB;
            }
            temp_f = (0.15 - (f64)D_807FBB40->unk4->unk34) / 0.13;
            sub->unk8 = (s32)(temp_f * 400.0f);
            D_807FBB40->unkE6 += sub->unk8;
        }
        break;
    case 11:
        sub->unkD = 0x32;
        sub->unk8 = 0;
        actorAppendCallback(D_807FBB4C, (s32)D_807FBB40, 0x40, 1, 0, 0);
        if (((Lg809_ActorSpawnParams *)D_807FBB40->unk124)->unk18 == 1.0) {
            angle = D_80750390;
        } else {
            angle = 0xB4;
        }
        func_8067AAB8((s32)D_807FBB40, D_807FBB4C, (s16)((D_807FBB40->unkE6 + 0x800) & 0xFFF), (f32)angle, 0);
        if (((Lg809_ActorSpawnParams *)D_807FBB40->unk124)->unk18 == 1.0) {
            Lg809_PlayerState *playerState = ((Actor *)D_807FBB4C)->unk174;
            func_806C7BAC(D_807FBB4C, 0);
            playerState->unk1A3 = 1;
            playerState->unkBC = 0x31;
            playerState->unkBE = -1;
            sfxAllocateChannel(0x48, 1.0f);
        }
        actorSetCustomFloat(D_807FBB40, 1, 0.0f);
        actorSetCustomInt(D_807FBB40, 7, 0);
        if (sub->unkC != 0) {
            D_807FBB40->unk154 = 0xC;
            if (tagBarrelGetKongType() == 2) {
                camStartPath(D_807FBB4C, 0x26, 5);
            }
        } else {
            D_807FBB40->unk132 = 1;
            D_807FBB40->unk154 = 0x1E;
        }
        break;
    case 12:
        sub->unkD--;
        if (sub->unkD < 0x28) {
            sp90.x = ((f64)(u32)((randomLcgNext() / 1000) % 50) - 25.0) / 5.0;
            sp90.y = ((f64)(u32)((randomLcgNext() / 1000) % 50) - 25.0) / 5.0;
            sp90.z = ((f64)(u32)((randomLcgNext() / 1000) % 50) - 25.0) / 5.0;
        }
        if (sub->unkD == 0) {
            tagBarrelDespawnEffects();
            if (sub->unkA != 0) {
                sp8A = func_8073195C(sub->unkA);
            } else {
                sp8A = -1;
            }
            kong = tagBarrelGetKongType();
            switch (D_8076A0A8) {
            case 0xBC:
                flagSet(0x28, 1, 2);
                break;
            case 0xBA:
                flagSet(0x32, 1, 2);
                break;
            default:
                yOffset = -8.0f;
                if (D_8076A0A8 == 0xAD) {
                    yOffset = -10.0f;
                }
                actorSpawnNodeEntryScaled(0x2D, D_807FBB40->unk7C, D_807FBB40->unk80 + yOffset, D_807FBB40->unk84, 0, kong, sp8A, 0);
                sfxAllocateChannel(0x14, 1.0f);
                actorDespawn(D_807FBB40);
                break;
            }
        }
        break;
    case 20:
        for (i = 0; i < D_807FBDC4; i++) {
            if (D_807FBB70.unk258[i] == 1 && *D_807FBB70.unk278[i] == 0) {
                D_807FBB40->unk144 = 2;
                D_807FBB40->unk154 = 0x15;
                sfxAllocateChannel(0x28, 1.0f);
            }
        }
        break;
    case 21:
        D_807FBB40->unk128 += 0xA;
        if (D_807FBB40->unk128 >= 0xF1) {
            D_807FBB40->unk60 |= 0x8000;
            D_807FBB40->unk154 = 0;
        }
        break;
    case 30:
        sub->unkD--;
        if (sub->unkD == 0) {
            D_807FBB40->unk144 = 2;
            D_807FBB40->unk154 = 0;
        }
        break;
    }
    if (D_807FBB40->unk154 != 0x14) {
        func_8065D254(D_807FBB40, 0x3C8, 0x40, 0x40, 0xC, 0xC, 1, 0x64, 0x78, 0, 1.0f);
    }
    D_807FBB40->unkE6 += 0x50;
    D_807FBB40->unk80 = (func_80612794(sub->unk4) * 5.0) + (f64)sub->unk0;
    sub->unk4 += 0x3C;
    guTranslateF((f32 (*)[4])((u8 *)D_807FBB40 + 0xC), sp90.x, sp90.y, sp90.z);
    actorUpdateModelMatrix(D_807FBB40, 1);
}

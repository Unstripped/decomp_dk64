// func_80681E18 (src/global/80150.c): Stage 5: frame 0x58 and s0/ra match; exact 368 insns, shape=3; diff is caller-saved regalloc (/ for var_v1, / for 1, / for &D_807FBB70)
typedef struct KaN4_80681E18 {
    s16 unk0;
    s16 pad2;
    Actor *unk4;
} KaN4_80681E18;

typedef struct KaN4_ActorD580 {
    u8 pad0[0x1A3];
    u8 unk1A3;
} KaN4_ActorD580;

extern u8 D_807FC950[][0x5E];
extern s16 D_80750390;
extern s32 D_807FBB68;

s32 collisionCheckGroundAtPoint(f32, f32, f32 *);
s32 sfxAllocateChannel(s32, f32);
void func_8065D254(Actor *, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32);
void sfxPlayFromActorWithAltitudeCheck(Actor *, s32, s32, s32, s32);
void func_806F8BC4(s32, u8, s32);
void actorAppendCallback(Actor *, s32, s32, u8, s32, void *);
void func_8067AAB8(s32, Actor *, s16, f32, s16);
void func_806C7BAC(s32, Actor *);

void func_80681E18(void) {
    KaN4_80681E18 *var_v1;
    s32 pad[3];

    var_v1 = (KaN4_80681E18 *)D_807FBB40->unk174;
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unkA4 = 99999.0f;
        collisionCheckGroundAtPoint(D_807FBB40->unk7C, D_807FBB40->unk84, &D_807FBB40->unkA4);
        if (1 == *(s32 *)D_807FBB40->unk124) {
            if (func_8067B450(D_807FBB40) == 0) {
                D_807FBB40->unk154 = 0x14;
                D_807FBB40->unk144 = 1;
                D_807FBB40->unk60 &= ~0x8000;
                D_807FBB40->unk128 = 0;
            }
        }
    }
    if ((D_807FBB40->unk154 == 0) && (D_807FBB70.unk200 == 4)) {
        var_v1->unk0 = 0xA;
        D_807FBB40->unk154 = 1;
        D_807FBB40->unk144 = 1;
        var_v1->unk4 = (Actor *)D_807FBB70.unk1FC;
        D_807FBB40->unk60 |= 0x200000;
        if ((D_8076A0A8 == 0x11) || (D_8076A0A8 == 0xC9) || (D_8076A0A8 == 0xCC)) {
        } else {
            sfxAllocateChannel(0x48, 1.0f);
        }
    }
    switch (D_807FBB40->unk154) {
    case 0: {
        s32 sp44;
        if (D_8074E77C < 5) {
            sp44 = D_807FC950[D_8074E77C][0];
        }
        if (((Actor *)D_807FBB4C)->unk58 == 3 && sp44 >= 2) {
            D_807FBB40->unk60 |= 0x8000;
            D_807FBB40->unk132 = 1;
        } else {
            D_807FBB40->unk60 &= ~0x8000;
            D_807FBB40->unk128 = 0x78;
            D_807FBB40->unk132 = 2;
        }
        func_8065D254(D_807FBB40, 0x3C8, 0x40, 0x40, 0xC, 0xC, 1, 0x64, 0x78, 0, 1.0f);
        break;
    }
    case 1:
        var_v1->unk0--;
        if (var_v1->unk0 == 0) {
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x1C6, 0xFF, 0x7F, 0);
            D_807FBB40->unk154 = 2;
            func_806F8BC4(5, (D_807FBB68 & 2) ? 0 : 1, 0);
        }
        break;
    case 2:
        func_8067DCC0();
        D_807FBB40->unk60 &= ~0x8000;
        D_807FBB40->unk128 = 0;
        actorAppendCallback(var_v1->unk4, (s32)D_807FBB40, 0x40, 1, 0, 0);
        func_8067AAB8((s32)D_807FBB40, var_v1->unk4, var_v1->unk4->unkE6, (f32) D_80750390, 0);
        func_806C7BAC((s32)var_v1->unk4, D_807FBB40);
        ((KaN4_ActorD580 *)D_807FD580)->unk1A3 = 1;
        D_807FBB40->unk154 = 3;
        break;
    case 3:
        if (D_807FBB70.unk0 != 0) {
            D_807FBB40->unk60 |= 0x8000;
            D_807FBB40->unk144 = 2;
            D_807FBB40->unk60 &= ~0x200000;
            D_807FBB40->unk154 = 0;
        }
        break;
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
        break;
    case 20: {
        s16 i;
        if (D_807FBB70.unk254 > 0) {
            i = 0;
            do {
                if (D_807FBB70.unk258[i++] == 1) {
                    D_807FBB40->unk144 = 2;
                    D_807FBB40->unk154 = 0x15;
                }
            } while (i < D_807FBB70.unk254);
        }
        break;
    }
    case 21:
        D_807FBB40->unk128 += 10;
        if (D_807FBB40->unk128 >= 0xF1) {
            D_807FBB40->unk60 |= 0x8000;
            D_807FBB40->unk154 = 0;
        }
        break;
    }
    actorUpdateModelMatrix(D_807FBB40, 0);
}

// func_806A664C (src/global/AA960.c): stage 6: full structural match (474 instrs, same frame/saves); only temp-register assignment differs by one (expected state in t0, mine v1; all temps shifted). Tried: state decl order, init-at-decl, block-scoped v, int-vs-float zeros at modelNode/subNode, u8 cast for sfx arg, case 0 break. s16 func_80672A70 to match src.
typedef struct L9bState174 {
    /* 0x0 */ u8 unk0;
    /* 0x1 */ u8 unk1;
    /* 0x2 */ u8 pad2[2];
    /* 0x4 */ u8 *unk4;
    /* 0x8 */ u16 unk8;
    /* 0xA */ s16 unkA;
} L9bState174;

typedef struct L9bConfig124 {
    /* 0x0 */ f32 unk0;
    /* 0x4 */ f32 unk4;
    /* 0x8 */ f32 unk8;
} L9bConfig124;

extern ActorGlobalState D_807FBB70;
extern s16 D_8075038C;
void func_8067ACB4(Actor *);
s32 func_806725A0(Actor *, s16);
s16 func_80672A70(s16, s16);
void actorApplyVelocity(Actor *);
void func_80665564(Actor *, f32);
void actorAppendModelNode(Actor *, f32, f32, f32, f32, s32);
void actorAppendModelSubNode(Actor *, f32, f32, f32, s32);
void func_8066EB40(Actor *, f32);
u32 func_806119A0(void);
s32 func_8061CB50(void);
s32 func_806F5C30(s32);
void func_806F5F2C(s32, s32, s16, s16, s32);
void sfxPlayFromActorWithAltitudeCheck(void *, s32, s32, s32, s32);
void actorDespawn(void *);

void func_806A664C(f32 arg0) {
    L9bState174 *state = D_807FBB40->unk174;
    s32 v;

    if (D_807FBB68 & 0x10) {
        arg0 *= 2.0f;
    }
    if (!(D_807FBB40->unk60 & 0x10)) {
        D_807FBB40->unk154 = (u8)(s32)((L9bConfig124 *)D_807FBB40->unk124)->unk0;
        *(s16 *)((u8 *)D_807FBB40 + 0xEE) = (s16)(s32)((L9bConfig124 *)D_807FBB40->unk124)->unk4;
        D_807FBB40->unkE6 = *(s16 *)((u8 *)D_807FBB40 + 0xEE);
        actorAppendModelSubNode(D_807FBB40, 0.0f, 0.0f, 0.0f, -1);
        state->unk0 = 0;
        state->unk1 = 0;
        state->unkA = (s16)(s32)((L9bConfig124 *)D_807FBB40->unk124)->unk8;
        *(s16 *)((u8 *)D_807FBB40 + 0xFA) = 0x270F;
    }
    if (D_807FBB70.unk0 != 0) {
        D_807FBB40->unk154 = D_807FBB70.unk1[0];
    }
    func_8067ACB4(D_807FBB40);
    if (D_807FBB40->unkFC != 0) {
        if (func_806725A0(D_807FBB40, *(s16 *)((u8 *)D_807FBB40 + 0xEE)) == 0) {
            s32 temp;

            temp = func_80672A70(D_807FBB40->unkF4, D_807FBB40->unkF6);
            *(s16 *)((u8 *)D_807FBB40 + 0xEE) = temp + (temp - ((*(s16 *)((u8 *)D_807FBB40 + 0xEE) + 0x800) & 0xFFF));
        }
    }
    switch (D_807FBB40->unk154) {
    case 0:
        break;
    case 1:
        D_807FBB40->unk144 = 0x1C;
        func_8066EB40(D_807FBB40, 60.0f);
        actorAppendModelNode(D_807FBB40, 0.0f, 0.0f, 0.0f, 50.0f, -1);
        actorAppendModelSubNode(D_807FBB40, 0.0f, 0.0f, 0.0f, -1);
        *(f32 *)((u8 *)D_807FBB40 + 0xC0) = (f32)((f64)((func_806119A0() / 10000) % 200) * 0.5 + 220.0 - 50.0);
        if (!(D_807FBB64 & 0x4000) && (((u32)D_807FBB40->unk58 < 0x4B) || ((u32)D_807FBB40->unk58 >= 0x50))) {
            D_807FBB40->unkB8 = 30.0f;
        }
        D_807FBB40->unk154++;
    case 2:
        actorApplyVelocity(D_807FBB40);
        func_80665564(D_807FBB40, arg0);
        *(f32 *)((u8 *)D_807FBB40 + 0xC0) -= 20.0f;
        if (*(f32 *)((u8 *)D_807FBB40 + 0xC0) < (f32)D_8075038C) {
            *(f32 *)((u8 *)D_807FBB40 + 0xC0) = (f32)D_8075038C;
        }
        if ((D_807FBB40->unk6A & 1) && !(D_807FBB40->unk6C & 1)) {
            switch (state->unk0) {
            case 0:
                if (D_807FBB40->unk15F != 1) {
                    state->unk1 = 1;
                }
                *(f32 *)((u8 *)D_807FBB40 + 0xC0) = 150.0f;
                break;
            case 1:
                *(f32 *)((u8 *)D_807FBB40 + 0xC0) = 100.0f;
                break;
            case 2:
                *(f32 *)((u8 *)D_807FBB40 + 0xC0) = 50.0f;
                break;
            case 3:
                D_807FBB40->unkB8 = 0.0f;
                *(f32 *)((u8 *)D_807FBB40 + 0xC0) = 0.0f;
                if (D_807FBB40->unk58 == 0x8C) {
                    state->unk1 = 1;
                }
                if (D_807FBB40->unk58 != 0x6E && D_807FBB40->unk58 != 0x8C && !(D_807FBB64 & 0x4000) && D_807FBB40->unk15F != 2) {
                    state->unk8 = 0x64;
                    D_807FBB40->unk154 = 3;
                } else {
                    D_807FBB40->unk154 = 0x64;
                }
                break;
            }
            switch (D_807FBB40->unk58) {
            case 0x34:
                sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0xF5, (u8)(*(f32 *)((u8 *)D_807FBB40 + 0xC0) + 105.0f), 0x7F, 0x1E);
                break;
            case 0x36:
                if (state->unk0 == 0) {
                    sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x1D1, 0xFF, 0x7F, 0xA);
                }
                break;
            default:
                sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 1, (u8)(*(f32 *)((u8 *)D_807FBB40 + 0xC0) + 105.0f), 0x7F, 0x14);
                break;
            }
            state->unk0++;
        }
        break;
    case 3:
        if (func_8061CB50() == 0) {
            state->unk8--;
        }
        if (state->unk8 == 0) {
            D_807FBB40->unk154 = 4;
        }
        break;
    case 4:
        state->unk4[0x36D] -= 5;
        if ((s32)state->unk4[0x36D] < 0xA) {
            if ((D_807FBB64 & 0x10000) && func_806F5C30(D_807FBB40->unk58) != 0) {
                func_806F5F2C(D_807FBB40->unk58, 0x258, (s16)(s32)D_807FBB40->unk7C, (s16)(s32)D_807FBB40->unk80, (s32)D_807FBB40->unk84);
            }
            actorDespawn(D_807FBB40);
        }
        break;
    case 25:
        state->unk8 = 0x64;
        D_807FBB40->unk154 = 3;
        state->unk1 = 1;
        break;
    }
}

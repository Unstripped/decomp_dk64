// func_806BA93C (src/global/BDEE0.c): Stage 6, same size/frame/stack layout, all insns identical except regalloc: v0<->v1 swapped on D_807FBB70/D_807FDC90 address+value temps and dir/unk2 load, and operand order of 3 multu (sgn*arg0, sgn*unk2C: target puts s0 first). K&R def u8 params; if(A&&B) return early form; dir via if/else; two sign vars; one extra local (s16 a) needed for frame (0xE8); zero args to guTranslateF as 0.0f. Permuter useless (K&R/brace parse mangled base).
typedef struct L4Sub178 {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ u16 unk4;
} L4Sub178;

typedef struct L4View {
    /* 0x000 */ u8 pad0[0xC];
    /* 0x00C */ f32 unkC[4][4];
    /* 0x04C */ u8 pad4C[0x108];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[0x22];
    /* 0x178 */ L4Sub178 *unk178;
} L4View;
#define L4A ((L4View *)D_807FBB40)

void sfxPlayFromActorWithAltitudeCheck(void *, s32, s32, s32, s32);
void func_8072D714(s32, s32);
void func_806BA76C(f32);
void func_806BA8C8(void);
s32 func_806BA240();
s32 func_8072AB74(u8, f32, f32, s32, f32);
f32 func_80612D10(f32);
f32 func_80612790(s16);
f32 func_80612794(s16);
void func_806086CC(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);
void func_80612BC0(f32 (*)[4], f32);
void func_80612C30(f32 (*)[4], f32);
void func_80612CA0(f32 (*)[4], f32);
s16 func_806CC190(s16, s16, f32);
void func_806319C4(Actor *, s32);

void func_806BA93C(arg0, arg1, arg2)
u8 arg0;
u8 arg1;
u8 arg2;
{
    L4Sub178 *s1;
    f32 spA4[4][4];
    f32 sp64[4][4];
    s32 sgn;
    s32 dir;
    f32 sp58;
    s16 a;

    s1 = L4A->unk178;
    if (D_807FDC9C->unkA && func_806BA240(0x64, 0)) {
        return;
    }
    {
        if ((D_807FBB70.unk200 == 9 || D_807FBB70.unk15 != 0) && D_807FBB40->unk154 != 0x37) {
            sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x1CA, 0xFF, 0x7F, 0x32);
            func_8072D714(D_807FBB70.unk1FC, 0);
            D_807FDC90->unk2C = 0xA6;
            s1->unk4 = 0x32;
        }
        func_806BA76C(D_807FBB40->unkB8 * 5.0f);
        switch (D_807FBB40->unk154) {
        case 4:
            s1->unk0 = s1->unk0 + (-s1->unk0) * 0.3;
            break;
        case 0x37:
            func_8072AB74(0x37, 0.0f, 0.0f, 0x12, 0.0f);
            if (L4A->unk155 == 0) {
                D_807FDC90->unk2C += s1->unk4;
                if (D_807FDC90->unk2C == 0x196 || D_807FDC90->unk2C == 0x244 || D_807FDC90->unk2C == 0x307 || D_807FDC90->unk2C == 0x3B1 || D_807FDC90->unk2C == 0x45C || D_807FDC90->unk2C == 0x508) {
                    sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x17D, 0x9B, (s16)(s1->unk4 + 0x5A), 0);
                }
                s1->unk4--;
                if (s1->unk4 < 2) {
                    L4A->unk155++;
                    s1->unk4 = 0;
                    D_807FDC90->unk30 = 0.0f;
                }
            }
            break;
        }
        if (s1->unk0 >= 0x801) {
            sp58 = sqrtf((1.0 - func_80612D10(0.7853982f)) * (2 * (f32)(arg0 * 2) * (f32)(arg0 * 2)));
            if (s1->unk2) {
                dir = 1;
            } else {
                dir = -1;
            }
            s1->unk0 -= 0x800;
            s1->unk2 ^= 1;
            a = dir << 8;
            D_807FBB40->unk7C += D_807FBB40->unk4->unk38 * sp58 * func_80612794(D_807FBB40->unkE6 + a);
            D_807FBB40->unk84 += D_807FBB40->unk4->unk38 * sp58 * func_80612790(D_807FBB40->unkE6 + a);
            func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x1B1, 0xFF, 0x7F, 0xA, 0x3C, 0.3f, 0);
        }
        func_806BA8C8();
        if (s1->unk2) {
            sgn = -1;
        } else {
            sgn = 1;
        }
        guTranslateF(spA4, sgn * arg0, 0.0f, 0.0f);
        func_80612CA0(sp64, func_80612794(s1->unk0) * (f32)(sgn * arg1));
        guMtxCatF(spA4, sp64, spA4);
        if (D_807FBB40->unk154 == 0x37) {
            func_80612C30(sp64, (f32)(sgn * D_807FDC90->unk2C));
        } else {
            func_80612C30(sp64, func_80612794(s1->unk0 - 0x400) * (f32)(-sgn * 0x2D));
        }
        guMtxCatF(spA4, sp64, spA4);
        if (D_807FBB40->unk154 == 0x37) {
            switch (L4A->unk155) {
            case 1:
                D_807FDC90->unk2C = func_806CC190((D_807FDC90->unk2C << 12) / 0x168, 0, 3.0f) * 0x168 / 4096;
                s1->unk0 = s1->unk0 + (-s1->unk0) * 0.3;
                guTranslateF(sp64, 0.0f, 0.0f, (f32)-arg2);
                guMtxCatF(spA4, sp64, spA4);
                func_80612BC0(sp64, (f32)s1->unk4);
                guMtxCatF(spA4, sp64, spA4);
                guTranslateF(sp64, 0.0f, 0.0f, (f32)arg2);
                D_807FDC90->unk30 += 2.0f;
                s1->unk4 = (f32)s1->unk4 + D_807FDC90->unk30;
                if (s1->unk4 >= 0x5B) {
                    s1->unk4 = 0x5A;
                    if (D_807FDC90->unk30 < 3.0f) {
                        L4A->unk155++;
                    } else {
                        func_806086CC(D_807FBB40->unk7C, D_807FBB40->unk80, D_807FBB40->unk84, 0x1B1, (u32)(D_807FDC90->unk30 * 255.0f / 20.0f), (s32)(D_807FDC90->unk30 + 100.0f), 0, 0x3C, 0.3f, 0);
                        D_807FDC90->unk30 = -(D_807FDC90->unk30 * 0.5);
                    }
                }
                break;
            case 2:
                guTranslateF(sp64, 0.0f, 0.0f, (f32)-arg2);
                guMtxCatF(spA4, sp64, spA4);
                func_80612BC0(sp64, 90.0f);
                guMtxCatF(spA4, sp64, spA4);
                guTranslateF(sp64, 0.0f, 0.0f, (f32)arg2);
                break;
            }
            guMtxCatF(spA4, sp64, spA4);
        }
        guTranslateF(sp64, (f32)(-sgn * arg0), 0.0f, 0.0f);
        guMtxCatF(spA4, sp64, L4A->unkC);
        func_806319C4(D_807FBB40, 1);
    }
}

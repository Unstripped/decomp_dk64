// func_80643C0C (src/global/478F0.c): stage 4-5: only diff is missing 'move a0,v1' (p=v1 and a separate copy q=a0 used for n=*q / *q=n+1; *p=0 uses v1) so regs shift by one temp; uopt copy-prop eliminates q=p. Tried: q copy, split alloc var, expr form cs->unk0, multi-purpose var (keeps copy but coalesces n), deadsweep, permuter (450 floor).
void func_80714950(s32);
void func_8071498C(void *);
void func_807149B8(s32);
void func_807149C8(s32, s32, s32, s32);
void func_807149FC(s32);
s32 func_80714CC0(void *, f32, f32, f32, f32);
extern u32 D_8076A064;
void lightAdd(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32);

typedef struct {
    s32 *unk0;
    u8 pad4[0x45];
    u8 unk49;
} CsB1LightView;

void *func_80610FE8(s32);
extern u8 D_807201D4[];
void func_80717CE8();

void func_80643C0C(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 *p;
    s32 *q;
    s32 n;
    f64 t;
    f32 f;

    p = ((CsB1LightView *)cs)->unk0;
    if (p == NULL) {
        q = func_80610FE8(8);
        p = q;
        ((CsB1LightView *)cs)->unk0 = q;
    }
    if (b == 1) {
        *p = 0;
    }
    n = *p;
    *p = n + 1;
    t = (f32)(70 - n) / 70.0f;
    if (t > 0.5) {
        f = 1.0 - 2.0 * (t - 0.5);
    } else {
        f = 2.0 * t;
    }
    lightAdd(D_807F621C, D_807F6220, D_807F6224, 0.0f, 0.0f, 0.0f, 200.0f * f, 0, 0xFF,
             (u32)((-80.0f * f) + 255.0f), (u32)((-205.0f * f) + 255.0f));
    if (t > 0.6 && (D_8076A064 % 6) == 0) {
        func_807149FC(2);
        func_807149B8(1);
        func_80714950(-0x190);
        func_807149C8(0xFF, 0xFF, 0xFF, 1);
        func_8071498C(func_80717CE8);
        func_80714CC0(D_807201D4, 1.2f, D_807F621C, D_807F6220 + 30.0, D_807F6224);
    }
    if (t < 0.1) {
        ((CsB1LightView *)cs)->unk49 = 1;
    }
}

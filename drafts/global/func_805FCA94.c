// func_805FCA94 (src/global/450.c): Stage 6, text-IDENTICAL to expected (deadsweep text=0); only diff is the function's own rodata (4 double literals 0.04,0.05,0.4,0.1 land in .rodata of 450 TU, expected asm names them D_80756590..A8): needs the 450 .rodata carve + ROM gate. Keys: no local v (S0V[i] direct so uopt PRE-reloads D_807FC924 per arm), 'Actor *pa = pl->unk104' local (candidate in v1), 's32 *cc = D_807445CC' local read via cc[0] (stops lda promotion to s5, gives per-arm lui), 'fov += c * sinApprox()' compound assignment (fixes fp operand order), one FAKE dead if after aspect call
extern u8 D_80750AB4;
f32 func_806276AC(void);
void func_8062754C(f32);
f32 sinApprox(f32);

typedef struct {
    u8 pad0[0x90];
    f32 unk90;
    u8 pad94[0xFA - 0x94];
    u8 unkFA;
} Sched0Held;

typedef struct {
    u8 pad0[0x104];
    Actor *unk104;
    u8 pad108[0x1F0 - 0x108];
    s32 unk1F0;
} Sched0PlayerData;

typedef struct {
    u8 unk0;
    u8 pad1[3];
    Actor *unk4;
    Mtx unk8[2];
    Mtx unk88[2];
    u8 pad108[0x188 - 0x108];
    u16 unk188;
    u8 pad18A[6];
    LookAt unk190[2];
    Hilite unk1D0[2];
    u8 pad1F0[0x210 - 0x1F0];
    f32 unk210;
    f32 unk214;
    f32 unk218;
    u8 pad21C[4];
    f32 unk220;
    u8 pad224[4];
    f32 unk228;
    f32 unk22C;
    f32 unk230;
    u8 pad234[0xC];
    f32 unk240;
    f32 unk244;
    f32 unk248;
    u8 pad24C[0x27C - 0x24C];
    f32 unk27C;
    f32 unk280;
    f32 unk284;
    f32 unk288;
    u8 pad28C[0x2F0 - 0x28C];
} Sched0View;

#define S0V ((Sched0View *)D_807FC924)
#define S0DIFF(a, b) (((b) < (a)) ? ((a) - (b)) : -((a) - (b)))

void func_805FCA94(void *arg0) {
    Actor *pa;
    Sched0PlayerData *pl;
    Sched0Held *held;
    s32 i;
    f32 fov;
    f32 aspect;
    f32 offs;
    s32 *cc;

    aspect = func_8062A850();
    if (D_807445CC && D_807445CC) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    if (D_807FC928 >= 2 && D_80750AB8 == 1) {
        func_8062754C(func_806276AC());
    }
    for (i = 0; i < D_80750AB4; i++) {
        if (S0V[i].unk0 != 0) {
            if (S0DIFF(S0V[i].unk210, S0V[i].unk228) < 0.5 && S0DIFF(S0V[i].unk218, S0V[i].unk230) < 0.5) {
                offs = 1.0f;
            } else {
                offs = 0.0f;
            }
            guLookAtHilite(&S0V[i].unk8[D_807444FC], &S0V[i].unk190[D_807444FC], &S0V[i].unk1D0[D_807444FC],
                           S0V[i].unk210 + offs, S0V[i].unk214, S0V[i].unk218 + offs,
                           S0V[i].unk228, S0V[i].unk22C, S0V[i].unk230,
                           S0V[i].unk240, S0V[i].unk244, S0V[i].unk248,
                           D_807444CC, D_807444D0, D_807444D4,
                           D_807444D8, D_807444DC, func_807444E0,
                           0x20, 0x20);
            fov = S0V[i].unk280;
            cc = D_807445CC;
            pl = (Sched0PlayerData *)S0V[i].unk4->unk174;
            pa = pl->unk104;
            held = (Sched0Held *)pa->unk174;
            if (pl->unk1F0 & 0x100) {
                fov += 0.5 * sinApprox(cc[0] * 0.1);
            } else if (pl->unk1F0 & 0x2000000) {
                fov += 0.05 * sinApprox(cc[0] * 0.4);
            } else if (held->unkFA != 0 && S0V[i].unk220 < held->unk90 + 3.0f) {
                fov += 0.04 * sinApprox(cc[0] * 0.1);
            }
            guPerspective(&S0V[i].unk88[D_807444FC], (u16 *)(i * 0x2F0 + (s32)D_807FC924 + 0x188), S0V[i].unk27C, fov * aspect, S0V[i].unk284, S0V[i].unk288, 1.0f);  // FAKE: operand order (i*0x2F0 first) keeps this address from CSE with the S0V[i] address
        }
    }
    if (S0DIFF(S0V->unk210, S0V->unk228) < 0.5 && S0DIFF(S0V->unk218, S0V->unk230) < 0.5) {
        offs = 1.0f;
    } else {
        offs = 0.0f;
    }
    guPerspective((Mtx *)arg0, &D_8076A09C, S0V->unk27C, fov * aspect, S0V->unk284, S0V->unk288, 1.0f);
    guLookAt((Mtx *)((u8 *)arg0 + 0x200), S0V->unk210 + offs, S0V->unk214, S0V->unk218 + offs,
             S0V->unk228, S0V->unk22C, S0V->unk230,
             S0V->unk240, S0V->unk244, S0V->unk248);
    D_807445CC[0]++;
}

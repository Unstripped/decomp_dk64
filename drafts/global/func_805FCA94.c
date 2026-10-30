// func_805FCA94 (src/global/0.c): Stage 6 (frame 0xC0, s0-s4 + f20-f30 saved set match; parked NON_MATCHING in src copy, equivalent C). Remaining: s2/s3/s4 order (exp s2=i,s3=&D_807444FC,s4=&D_807FC924; mine i=s4), extra 'lw a2,D_807445CC' preload from the deadsweep stmt (exp loads CC per branch), 'move s0,v1' after each v=&S0V[i] reload (exp addu s0 direct), FP scratch numbering (add.s f18 vs f4). 0.04/0.05/0.4/0.1 must be C literals (doubles hoisted as values into f24-f30): rodata D_80756590..A8 lives in 14C450.data.s, needs a 0.c rodata carve. The D_807445CC address web (s5) is only killed by the FAKE if(CC&&CC) stmts. Permuter 80k iters 3270->1845, nothing near 0; direct S0V[i] in-loop (no v) was worse.
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
} Sched0View;

#define S0V ((Sched0View *)D_807FC924)
#define S0DIFF(a, b) (((b) < (a)) ? ((a) - (b)) : -((a) - (b)))

void func_805FCA94(void *arg0) {
    Sched0View *v;
    Sched0PlayerData *pl;
    Sched0Held *held;
    s32 i;
    f32 fov;
    f32 aspect;
    f32 offs;

    if (D_807445CC[0] && D_807445CC[0]) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    aspect = func_8062A850();
    if (D_807FC928 >= 2 && D_80750AB8 == 1) {
        func_8062754C(func_806276AC());
    }
    for (i = 0; i < D_80750AB4; i++) {
        v = &S0V[i];
        if (v->unk0 != 0) {
            if (S0DIFF(v->unk210, v->unk228) < 0.5 && S0DIFF(v->unk218, v->unk230) < 0.5) {
                offs = 1.0f;
            } else {
                offs = 0.0f;
            }
            guLookAtHilite(&v->unk8[D_807444FC], &v->unk190[D_807444FC], &v->unk1D0[D_807444FC],
                           v->unk210 + offs, v->unk214, v->unk218 + offs,
                           v->unk228, v->unk22C, v->unk230,
                           v->unk240, v->unk244, v->unk248,
                           D_807444CC, D_807444D0, D_807444D4,
                           D_807444D8, D_807444DC, func_807444E0,
                           0x20, 0x20);
            v = &S0V[i];
            if (D_807445CC[0] && D_807445CC[0]) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            fov = v->unk280;
            pl = (Sched0PlayerData *)v->unk4->unk174;
            held = (Sched0Held *)pl->unk104->unk174;
            if (pl->unk1F0 & 0x100) {
                if (D_807444FC && D_807444FC) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                fov = fov + 0.5 * sinApprox(D_807445CC[0] * 0.1);
                v = &S0V[i];
            } else if (pl->unk1F0 & 0x2000000) {
                fov = fov + 0.05 * sinApprox(D_807445CC[0] * 0.4);
                v = &S0V[i];
            } else if (held->unkFA != 0 && v->unk220 < held->unk90 + 3.0f) {
                fov = fov + 0.04 * sinApprox(D_807445CC[0] * 0.1);
                v = &S0V[i];
                if (D_807444FC == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            }
            guPerspective(&v->unk88[D_807444FC], &S0V[i].unk188, v->unk27C, fov * aspect, v->unk284, v->unk288, 1.0f);
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

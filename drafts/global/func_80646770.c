// func_80646770 (src/global/478F0.c): stage 6: text size+frame+callee-saved set identical, all s-regs match; diff = temp regs only (p-ptr part a1 vs v1, cnt a2 vs a1, loop t0/t1 vs t1/t2). Tried hit/start types, loop forms, pl local (helps), nv temp+do{}while(0) (permuter), deadsweep
typedef struct CsB0Point3f {
    f32 x, y, z;
} CsB0Point3f;

typedef struct CsB4Player210 {
    /* 0x000 */ u8 pad0[0x210];
    /* 0x210 */ f32 x;
    /* 0x214 */ f32 y;
    /* 0x218 */ f32 z;
} CsB4Player210;

extern CsB0Point3f **D_807F5FD4;
extern f32 D_807480F0;
extern u8 D_80720BC4[];
void func_8071E3EC(void);
s32 func_80714CC0(void *, f32, f32, f32, f32);
f32 sqrtf(f32);

void func_80646770(s32 **slot, s16 csId, s16 b, s16 c) {
    s32 *p;
    s32 cnt;
    s32 start;
    s32 hit;
    CsB0Point3f *v;
    CsB4Player210 *pl;
    f32 dx;
    f32 nv;
    f32 dy;
    f32 dz;

    hit = 0;
    if (*slot == NULL) {
        *slot = func_80610FE8(4);
        **slot = 0;
    }
    p = *slot;
    start = *p;
    cnt = D_807F5FD4[1] - D_807F5FD4[0];
    *p = start + 1;
    if (cnt == *p) {
        *p = 0;
        do {
        } while (0);
    }
    if (start != *p) {
        do {
            pl = (CsB4Player210 *)D_807FC924;
            v = D_807F5FD4[0] + *p;
            nv = pl->z - v->z;
            dx = pl->x - v->x;
            dz = nv;
            dy = pl->y - v->y;
            if (sqrtf(dz * dz + (dx * dx + dy * dy)) < D_807480F0) {
                hit = 1;
                func_807149B8(1);
                func_80714998(3);
                func_80714950(0);
                func_8071498C(func_8071E3EC);
                func_807149A8(0x320);
                v = D_807F5FD4[0] + *p;
                func_80714CC0(D_80720BC4, 2.5f, v->x, v->y, v->z);
            } else {
                *p += 1;
                if (cnt == *p) {
                    *p = 0;
                }
            }
        } while (hit == 0 && start != *p);
    }
}

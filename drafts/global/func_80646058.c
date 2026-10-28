// func_80646058 (src/global/478F0.c): stage 4 (frame 0x88, s0 only, 455/456 insns). Remaining diff ~17 insn lines: start lives in a1 until loop in target (ours t2 + early sw 0x84(sp)); li a0,1 / li t8,1 order in hit block; spill slot of func_8071E3EC cb 0x3c vs 0x44; ok=1 scheduling + missing `b` before join (target b L; li v1,1). Uses dead stmts if(D_80720BC4){} / if(D_807480F4&&D_807480F4){}, hit/&hit trick (u8 hit coloured to a reg otherwise).
typedef struct CsB46State {
    /* 0x00 */ s32 idx;
    /* 0x04 */ s32 timer;
    /* 0x08 */ s32 active;
    /* 0x0C */ s32 delay;
    /* 0x10 */ s32 count;
    /* 0x14 */ s32 flag14;
    /* 0x18 */ s32 flag18;
    /* 0x1C */ s32 flag1C;
} CsB46State;

typedef struct CsB46Player {
    /* 0x000 */ u8 pad0[0x210];
    /* 0x210 */ f32 x;
    /* 0x214 */ f32 y;
    /* 0x218 */ f32 z;
} CsB46Player;

typedef struct CsB46Sub4 {
    /* 0x00 */ u8 pad0[0x64];
    /* 0x64 */ u16 unk64;
} CsB46Sub4;

typedef struct CsB46Act {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ CsB46Sub4 *unk4;
    /* 0x008 */ u8 pad8[0x7C - 8];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x12C - 0x88];
    /* 0x12C */ s16 unk12C;
    /* 0x12E */ u8 pad12E[0x154 - 0x12E];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
} CsB46Act;

extern u32 D_807FBB60;
extern u8 D_80748108;
extern s32 D_807480F4;
extern s32 D_807480F8;
extern s32 D_807480FC;
extern s32 D_80748100;
extern f32 D_80748104;
extern s32 D_8074810C;
extern s32 D_80748110;
extern s32 D_80748114;
extern f32 D_807480F0;
f32 sqrtf(f32);
s32 flagGet(s32, s32);
void flagSet(s32, s32, s32);
void sfxStopChannel(s32, s32);
void sfxAllocateChannel(s32, f32);
void camStartPath(s32, s32, s32);
void actorListSpawnNodeEntry(s16, f32, f32, f32, s16, f32, s32, void *);
CsB46Act *spawnNodeActivate(s16, u16);

#define CsB46A ((CsB46Act *)D_807FBB4C)

void func_80646058(CsState *cs, s16 csId, s16 b, s16 c) {
    s32 start;
    u8 hit;
    CsB46State *p;
    CsB46Player *pl;
    f32 t;
    CsB0Point3f *v;
    CsB46Act *a;
    u8 ok;
    CsB46State *n;
    s32 s;
    f32 u;
    u32 pad0;
    u32 pad1;
    f32 vec[3];
    u8 *hp = &hit;

    hit = 0;
    if (*(CsB46State **)cs == NULL) {
        n = func_80610FE8(0x1C);
        *(CsB46State **)cs = n;
        n->idx = 0;
        n->timer = D_807480F4;
        n->active = 0;
        n->delay = 0;
        n->count = 0;
        n->flag14 = 0;
        n->flag18 = 0;
        n->flag1C = 0;
    }
    p = *(CsB46State **)cs;
    if (b == 0) {
        if (D_80748108 != 0) {
            return;
        }
        if (p->active != 0 && p->flag14 == 0) {
            return;
        }
        start = p->idx;
        p->idx = start + 1;
        if (p->idx == 0x36) {
            p->idx = 0;
        }
        if (start == p->idx) {
            return;
        }
        do {
            if (D_80720BC4) {}
            pl = (CsB46Player *)D_807FC924;
            v = D_807F5FD4[0] + p->idx;
            if (sqrtf((pl->z - v->z) * (pl->z - v->z) + ((pl->x - v->x) * (pl->x - v->x) + (pl->y - v->y) * (pl->y - v->y))) < D_807480F0) {
                if (D_807480F4 && D_807480F4) {}
                hit = 1;
                func_807149B8(1);
                func_80714998(3);
                func_80714950(0);
                func_8071498C(func_8071E3EC);
                func_807149A8(0x320);
                v = D_807F5FD4[0] + p->idx;
                func_80714CC0(D_80720BC4, 2.5f, v->x, v->y, v->z);
            } else {
                p->idx++;
                if (p->idx == 0x36) {
                    p->idx = 0;
                }
            }
        } while (hit == 0 && start != p->idx);
        return;
    }
    if ((~D_807FBB60 & 0x10) || CsB46A->unk154 == 0x63) {
        if (p->timer < 200) {
            p->timer = D_807480F4;
        }
        sfxStopChannel(0x54, 0);
        p->active = 0;
        return;
    }
    if (p->active != 0) {
        if (p->delay == 0) {
            if (p->flag14 != 0) {
                t = (randomNonNegative() >> 15) % 800 - 400.0;
                u = (randomNonNegative() >> 15) % 800 - 400.0;
                actorListSpawnNodeEntry(0x5C, 1820.0f + t, 500.0f, 3614.0f + u, 0, D_80748104, 0, vec);
            } else {
                t = (randomNonNegative() >> 15) % D_8074810C - D_8074810C * 0.5;
                u = (randomNonNegative() >> 15) % D_8074810C - D_8074810C * 0.5;
                actorListSpawnNodeEntry(0x5C, CsB46A->unk7C + t, CsB46A->unk80 + (f32)D_80748100, CsB46A->unk84 + u, 0, D_80748104, 0, vec);
            }
            if (p->flag14) {
                p->delay = D_80748114;
            } else {
                p->delay = D_807480FC;
            }
            p->count--;
            if (p->count == 0) {
                if (flagGet(0x12B, 0) == 0) {
                    p->timer = 0x50;
                } else {
                    p->timer = D_807480F4;
                    sfxStopChannel(0x54, 0);
                }
                p->active = 0;
                p->flag14 = 0;
                flagSet(0x12B, 1, 0);
            }
        } else {
            p->delay--;
        }
        if (p->flag14 != 0) {
            return;
        }
        if (CsB46A->unk154 == 0x63) {
            return;
        }
        s = CsB46A->unk12C;
        if (s == 0 || s == 7 || s == 2 || s == 3) {
            sfxStopChannel(0x54, 0);
            p->timer = D_807480F4;
            p->active = 0;
        }
    } else {
        if (p->flag18 == 0 && flagGet(0x12C, 0)) {
            p->flag18 = 1;
        }
        ok = 1;
        if (CsB46A->unk12C == 0xD) {
            ok = 0;
            a = spawnNodeActivate(0x1F, 0);
            if (a != NULL && a->unk154 == 0x27 && a->unk4->unk64 == 0x362 && a->unk155 == 2) {
                p->timer = 0x65;
                ok = 1;
            }
        }
        if (ok == 0 && p->flag1C == 0) {
            return;
        }
        if (p->flag18 != 0) {
            return;
        }
        s = CsB46A->unk12C;
        if (s == 0) {
            return;
        }
        if (s == 7 || s == 2 || s == 3) {
            return;
        }
        p->flag1C = 1;
        p->timer--;
        if (p->timer == 0x64) {
            if (flagGet(0x12C, 0) == 0) {
                sfxAllocateChannel(0x54, 1.0f);
            }
        }
        if (p->timer == 0x32) {
            if (flagGet(0x12B, 0) == 0) {
                camStartPath(0, 0x17, 1);
                p->flag14 = 1;
            }
        }
        if (p->timer == 0) {
            p->active = 1;
            p->flag1C = 0;
            p->count = p->flag14 ? D_80748110 : D_807480F8;
            p->delay = 0;
        }
    }
}

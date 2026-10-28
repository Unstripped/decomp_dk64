// func_806496B0 (src/global/478F0.c): stage 5: frame 0xD8 matches, same callee-saved set; 38 diff lines remain: early FP ring/load order in preheader (lwc1 f30,0x228 earlier in target), loop mul.s/lwc1 scheduling, q field store order. Key: ex/ez/xs/px/zo/py/xo/pz/sinA must be volatile f32 locals (memory resident); non-volatile locals p,obj,q before flag, ang,i,t after; negCos = -p->unk228 single def early gives right FP s-reg order. parked NON_MATCHING in copy
extern f32 D_807F622C;
extern u8 D_80720A7C[];
extern void *D_8074E880[];
void func_80609140(s32, s32, f32, f32, s32, s32);
f32 func_806119FC(void);
s32 randomNonNegative(void);
void func_8071F8E4(void);

typedef struct CsB8Cam {
    /* 0x000 */ u8 pad0[0x220];
    /* 0x220 */ f32 unk220;
    /* 0x224 */ f32 unk224;
    /* 0x228 */ f32 unk228;
    /* 0x22C */ f32 unk22C;
    /* 0x230 */ f32 unk230;
    /* 0x234 */ f32 unk234;
} CsB8Cam;

typedef struct CsB8Obj {
    /* 0x000 */ u8 pad0[0x384];
    /* 0x384 */ void *unk384;
} CsB8Obj;

typedef struct CsB8Part {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
} CsB8Part;

void func_806496B0(CsState *cs, s16 csId, s16 b, s16 c) {
    CsB8Cam *p;
    CsB8Obj *obj;
    CsB8Part *q;
    s32 flag;
    s16 ang;
    s32 i;
    f32 t;
    volatile f32 sinA;
    volatile f32 ex;
    volatile f32 ez;
    f32 negCos;
    volatile f32 xs;
    volatile f32 px;
    volatile f32 zo;
    volatile f32 py;
    volatile f32 xo;
    volatile f32 pz;
    void (*cb)(void);

    ang = D_807F622C * 4096.0f / 360.0f;
    if (c == 2) {
        func_807149B8(0);
        func_80714CC0(D_80720A7C, 0.5f, func_806119FC() * 35.0 + D_807F621C - 15.0, func_806119FC() * 35.0 + D_807F6220, func_806119FC() * 35.0 + D_807F6224 - 15.0);
        return;
    }
    p = (CsB8Cam *)D_807FC924->unk4->unk174;
    p->unk22C = D_807F621C;
    p->unk230 = D_807F6220 + 15.0;
    p->unk234 = D_807F6224;
    p->unk220 = func_80612794(ang);
    p->unk224 = ang;
    p->unk228 = func_80612790(ang);
    if (c == 0) {
        flag = 1;
        func_80609140(0xF2, 0x5DC0, 63.0f, 1.0f, 0, 0);
    } else {
        flag = 0;
        func_80609140(0x2EB, 0x7D00, 63.0f, 0.6f, 0, 0);
    }
    sinA = p->unk220;
    negCos = -p->unk228;
    pz = D_807F6224;
    px = D_807F621C;
    py = D_807F6220 + 15.0;
    ex = p->unk220 * 50.0 + px;
    ang = 0;
    cb = func_8071F8E4;
    ez = p->unk228 * 50.0 + pz;
    for (i = 0; i != 4; i++) {
        t = func_80612790(ang) * 100.0;
        xs = t * negCos + ex;
        xo = t * sinA + ez;
        zo = func_80612794(ang) * 100.0 + py;
        ang += 0x400;
        func_807149FC(-1);
        func_807149B8(0);
        func_8071498C(cb);
        obj = (CsB8Obj *)func_80714CC0(D_8074E880[((randomNonNegative() >> 15) % 1000) % 3], 1.8f, px, py, pz);
        q = func_80610FE8(0x28);
        obj->unk384 = q;
        q->unk4 = 0.0f;
        q->unk0 = (randomNonNegative() >> 15) % 5 + 10;
        q->unk8 = xs;
        q->unkC = zo;
        q->unk10 = xo;
        q->unk14 = px - xs;
        q->unk18 = py - zo;
        q->unk20 = 0.0f;
        q->unk1C = pz - xo;
        if (flag != 0) {
            q->unk24 = 0.09090909f;
        } else {
            q->unk24 = 0.033333335f;
        }
    }
}

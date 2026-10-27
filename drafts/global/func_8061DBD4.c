// func_8061DBD4 (src/global/201B0.c): stage 6: code matches except uopt temp stack slot (sp74 CSE temp at 0x68 vs target 0x74; frame/size/locals/regs otherwise identical) + reloc-only naming (D_807476CC/D_807576xx/jtbl labels vs .rodata+off, u64 D_807476C8 pair). Locals needed: st,done,w,t0,X,len,f64 d,sp84,sp80,fs,u64 now; ratio+cos temps share fs; chain assign order st->x = *argN = cam->y; sqrt operand order; case order 10,12,11,14,13,6; D_807444EC switch; (d = 0.0f != X->unkB4 ? 0.3 : 0.1). Tried: now/fs/pad decl orders, block-scope now, explicit sp74 local.
typedef struct CamELX {
    /* 0x00 */ u8 pad0[0x60];
    /* 0x60 */ s32 unk60;
    /* 0x64 */ u8 pad64[0x18];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
    /* 0x84 */ f32 unk84;
    /* 0x88 */ u8 pad88[0x1C];
    /* 0xA4 */ f32 unkA4;
    /* 0xA8 */ u8 padA8[4];
    /* 0xAC */ f32 unkAC;
    /* 0xB0 */ u8 padB0[4];
    /* 0xB4 */ f32 unkB4;
    /* 0xB8 */ u8 padB8[0x2E];
    /* 0xE6 */ s16 unkE6;
    /* 0xE8 */ s16 unkE8;
    /* 0xEA */ u8 padEA[0x6A];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[8];
    /* 0x15E */ u8 unk15E;
} CamELX;

typedef struct CamELState {
    /* 0x00 */ CamELX *unk0;
    /* 0x04 */ u8 pad4[0xC];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ u8 pad12[0x26];
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ u8 pad44[0x28];
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ f32 unk70;
    /* 0x74 */ u8 pad74[4];
    /* 0x78 */ f32 unk78;
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
    /* 0x84 */ f32 unk84;
    /* 0x88 */ f32 unk88;
    /* 0x8C */ f32 unk8C;
    /* 0x90 */ u8 pad90[4];
    /* 0x94 */ f32 unk94;
    /* 0x98 */ u8 pad98[6];
    /* 0x9E */ s16 unk9E;
    /* 0xA0 */ f32 unkA0;
    /* 0xA4 */ f32 unkA4;
    /* 0xA8 */ u8 padA8[4];
    /* 0xAC */ s32 unkAC;
    /* 0xB0 */ u8 padB0[2];
    /* 0xB2 */ s16 unkB2;
    /* 0xB4 */ u8 padB4[4];
    /* 0xB8 */ f32 unkB8;
    /* 0xBC */ u8 padBC[4];
    /* 0xC0 */ s32 unkC0;
    /* 0xC4 */ u8 padC4[8];
    /* 0xCC */ f32 unkCC;
    /* 0xD0 */ f32 unkD0;
    /* 0xD4 */ f32 unkD4;
    /* 0xD8 */ f32 unkD8;
    /* 0xDC */ f32 unkDC;
    /* 0xE0 */ f32 unkE0;
    /* 0xE4 */ u8 padE4[0xD];
    /* 0xF1 */ u8 unkF1;
    /* 0xF2 */ u8 unkF2;
    /* 0xF3 */ u8 unkF3;
    /* 0xF4 */ u8 padF4;
    /* 0xF5 */ u8 unkF5;
    /* 0xF6 */ u8 unkF6;
    /* 0xF7 */ u8 unkF7;
} CamELState;

typedef struct CamELCam {
    /* 0x00 */ u8 pad0[0x7C];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
    /* 0x84 */ f32 unk84;
    /* 0x88 */ u8 pad88[0x2C];
    /* 0xB4 */ f32 unkB4;
    /* 0xB8 */ u8 padB8[0x2C];
    /* 0xE4 */ s16 unkE4;
    /* 0xE6 */ u8 padE6[2];
    /* 0xE8 */ s16 unkE8;
    /* 0xEA */ u8 padEA[2];
    /* 0xEC */ s16 unkEC;
    /* 0xEE */ u8 padEE[0x86];
    /* 0x174 */ CamELState *unk174;
} CamELCam;

typedef struct CamELList {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ u8 pad2[2];
    /* 0x4 */ s16 *unk4;
    /* 0x8 */ u16 *unk8;
} CamELList; // size = 0xC

typedef struct CamELMap {
    /* 0x00 */ u8 pad0[0xBC];
    /* 0xBC */ s16 unkBC;
} CamELMap;

struct CamECam;
struct CamE2Player;
extern u32 D_80744478;

s16 func_806CC190(s16, s16, f32);
s32 func_807142D8(void);
void sfxAllocateChannel(u16, f32);
void func_80602498(void);
void func_80627F04(s32, s32, s32);
void func_80627490(f32 *, f32 *, f32, f32, f32, f32, f32, f32);
void func_80625320(struct CamE2Player *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *);
void func_80625994(struct CamE2Player *, f32, f32 *, f32 *, f32 *);
f32 cosApprox(f32);

#define CAMEL ((CamELCam *)arg0)
#define CAMEL_PATH_NODE (D_807476FC->unkD8[D_807F5CF2])
#define CAMEL_W(i) (((s32 *)&CAMEL_PATH_NODE.u)[i])
#define CAMEL_LIST (((CamELList *)D_807476FC->unkD0)[D_807476F4])

void func_8061DBD4(struct CamECam *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 *arg4, f32 *arg5, f32 *arg6, f32 *arg7,
                   f32 *arg8, f32 *arg9) {
    CamELState *st = CAMEL->unk174;
    s32 done;
    s32 *w;
    u16 t0;
    CamELX *X = st->unk0;
    f32 len;
    f64 d;
    f32 sp84;
    f32 sp80;
    f32 fs;
    u64 now;

    D_807F5CD0 = X->unkAC - X->unkA4;
    st->unk9E = func_806CC190(st->unk9E, X->unkE6, 4.0f);
    if ((X->unk60 & 0x200) && !(st->unkAC & 0x100)) {
        actorGetNodePos(X, 8, &st->unkD8, &st->unkDC, &st->unkE0);
    } else {
        st->unkD8 = X->unk7C;
        st->unkDC = X->unk80;
        st->unkE0 = X->unk84;
    }
    len = sqrtf((X->unk84 - st->unkD4) * (X->unk84 - st->unkD4) +
                ((X->unk7C - st->unkCC) * (X->unk7C - st->unkCC) + (X->unk80 - st->unkD0) * (X->unk80 - st->unkD0)));
    st->unk10 = (len * 40.0f) * (D_80744478 * 0.5);
    if (st->unkF1 != 0) {
        st->unkF1--;
    }
    if (st->unkF5 != 0) {
        st->unkF5--;
    }
    if (st->unkF6 != 0) {
        st->unkF6--;
    }
    if (st->unkF7 != 0) {
        st->unkF7--;
    }
    func_8061D060((CamDState *)st);
    func_8061D1FC((CamDActor *)arg0);
    CAMEL->unkE8 = func_806CC190(CAMEL->unkE8, X->unkE8, 20.0f);
    func_8061C0FC((CamAA8 *)st);
    switch (D_807444EC) {
    case 0:
        if (!(st->unkAC & 0x100)) {
            if (0.0f < D_807FD88C) {
                if (func_807142D8() == 0) {
                    return;
                }
            }
            if (st->unkF3 == 9) {
                return;
            }
            if (X->unk154 == 0x54 && X->unk155 < 3) {
                return;
            }
            if (X->unk154 == 0x52 && X->unk155 < 8) {
                return;
            }
            if (X->unk154 == 0x53 && X->unk155 < 3) {
                return;
            }
            if (X->unk154 == 0x42) {
                if (((CamELMap *)D_807FD580)->unkBC != 0x11 && ((CamELMap *)D_807FD580)->unkBC != 0x60 &&
                    ((CamELMap *)D_807FD580)->unkBC != 0x49) {
                    return;
                }
            }
            if (X->unk154 == 0x43) {
                return;
            }
        }
        func_8061D6A8((CamDState *)st);
        if (st->unkAC & 0x80000000) {
            func_8061C39C((CamActor *)arg0);
        } else {
            func_80622B24((CamActor *)arg0, &CAMEL->unk7C, &CAMEL->unk80, &CAMEL->unk84, &st->unk78, &st->unk7C,
                          &st->unk80, (CamActor *)X);
            if ((D_807FBB60 & 0x2000) || (st->unkAC & 0x100000)) {
                if (st->unkAC & 0x100000) {
                    st->unkAC &= ~0x100000;
                    st->unk84 = *arg1 = CAMEL->unk7C = st->unk38;
                    st->unk88 = *arg2 = CAMEL->unk80 = st->unk3C;
                    st->unk8C = *arg3 = CAMEL->unk84 = st->unk40;
                    func_80602498();
                } else {
                    st->unk84 = *arg1 = CAMEL->unk7C;
                    st->unk88 = *arg2 = CAMEL->unk80;
                    st->unk8C = *arg3 = CAMEL->unk84;
                }
                *arg4 = st->unk78;
                *arg5 = st->unk7C;
                *arg6 = st->unk80;
                D_807FBB60 ^= 0x2000;
            } else {
                func_80625320((struct CamE2Player *)arg0, arg1, arg2, arg3, arg4, arg5, arg6);
            }
        }
        break;
    case 1:
        now = osGetTime();
        D_807476C8 = now - D_807476D0;
        D_807476D0 = now;
        if (func_8061B4B0() != 0) {
            func_8061B4E4();
        }
        func_8061B7E0((CamActor *)arg0, (CamState *)st, *arg1, *arg3);
        if (D_807F5CF4 & 0x40) {
            func_8061B660((CamState *)st, arg1, arg2, arg3, 0.2f, 0.1f, 50.0f, 40.0f);
        } else {
            if (D_807476E4 != 0) {
                D_807476E4--;
                fs = (f32)D_807476E4 / (f32)D_807476E8;
                CAMEL->unkE4 = D_807476E0 + (D_807476DC - D_807476E0) * fs;
            }
            D_807476F0++;
            do {
                done = 0;
                if (D_807F5CEC == 0) {
                    func_8061D898();
                    D_807F5CF0++;
                    if (CAMEL_LIST.unk0 < D_807F5CF0) {
                        if (D_807F5CF4 & 0x10) {
                            if (!(D_807FBB4C->unk6A & 0x100)) {
                                D_807FBB4C->unk6A |= 0x100;
                            }
                        } else {
                            func_8061D4E4((CamDActor *)arg0);
                        }
                    } else {
                        t0 = CAMEL_LIST.unk8[D_807F5CF0 - 1];
                        w = (s32 *)&CAMEL_PATH_NODE.u;
                        switch (CAMEL_PATH_NODE.unk1) {
                            case 10:
                            case 15:
                            case 16:
                            case 17:
                                D_807FBB60 |= 0x2000;
                                break;
                            case 12:
                                sfxAllocateChannel(*(u16 *)w, 1.0f);
                                if (D_807F5CEC == 0) {
                                    func_8061D898();
                                    D_807F5CEC = 0;
                                    done = 1;
                                }
                                break;
                            case 11:
                                if (D_807F5CF4 & 4) {
                                    D_807476FC = &D_807F5B10;
                                }
                                func_8061D4E4((CamDActor *)arg0);
                                st->unkAC &= ~0x40000;
                                if (st->unkF3 != 0xB && st->unkF3 != 3) {
                                    st->unk6C = st->unk70 = D_807FBB4C->unk80;
                                    len = sqrtf((*arg1 - D_807FBB4C->unk7C) * (*arg1 - D_807FBB4C->unk7C) +
                                                (*arg3 - D_807FBB4C->unk84) * (*arg3 - D_807FBB4C->unk84));
                                    st->unkA4 = st->unkA0 = len;
                                    st->unkB2 = mathAngleBetweenPoints2D(D_807FBB4C->unk7C, D_807FBB4C->unk84, *arg1, *arg3);
                                    CAMEL->unkB4 = st->unkB8 = *arg2 - D_807FBB4C->unk80;
                                    st->unk84 = *arg1;
                                    st->unk88 = *arg2;
                                    st->unk8C = *arg3;
                                    *arg4 = *arg1 + (*arg4 - *arg1) * 0.1;
                                    *arg5 = *arg2 + (*arg5 - *arg2) * 0.1;
                                    *arg6 = *arg3 + (*arg6 - *arg3) * 0.1;
                                    st->unk78 = *arg4;
                                    st->unk7C = *arg5;
                                    st->unk80 = *arg6;
                                    if (D_807FBB64 & 1) {
                                        func_8062217C((CamActor *)arg0, 2);
                                    } else {
                                        func_80622334((CamActor *)arg0, (s16)st->unkA0);
                                    }
                                    st->unk94 = st->unkA0 / 3.0;
                                    func_8061F164((CamState *)st, 0x1E);
                                    st->unkF3 = 1;
                                    D_807FBB60 &= ~0x2000;
                                    func_8061D6A8((CamDState *)st);
                                }
                                break;
                            case 14:
                                timerQueueAdd(func_8061DA14, t0 + 0x80000000, 0, 0, 0);
                                func_8061D898();
                                D_807F5CEC = 0;
                                done = 1;
                                break;
                            case 13:
                                if (t0 != 0) {
                                    timerQueueAdd(func_80627F04, t0 + 0x80000000, w[0], w[1], w[2]);
                                } else {
                                    func_80627F04(w[0], w[1], w[2]);
                                }
                                func_8061D898();
                                D_807F5CEC = 0;
                                done = 1;
                                break;
                            case 6:
                                D_807F5CEE = t0;
                                func_8061D898();
                                D_807F5CEC = 0;
                                done = 1;
                                break;
                        }
                    }
                }
            } while (done != 0);
            if (D_807444EC != 0) {
                D_807F5CFC = ((s16 *)CAMEL_LIST.unk8)[D_807F5CF0 - 1];
                if (D_807F5CFC != 1.0f) {
                    D_807F5D00 = (f32)(D_807F5CEC - 1) / (D_807F5CFC - 1.0f);
                } else {
                    D_807F5D00 = 0.0f;
                }
                if (D_807F5CEC > 0) {
                    D_807F5CEC--;
                }
                switch (CAMEL_PATH_NODE.unk1) {
                    case 4:
                    case 5:
                        ((CamELX *)D_807F5D0C)->unk7C = ((CamELX *)D_807F5CE8)->unk7C;
                        ((CamELX *)D_807F5D0C)->unk80 = ((CamELX *)D_807F5CE8)->unk80;
                        ((CamELX *)D_807F5D0C)->unk84 = ((CamELX *)D_807F5CE8)->unk84;
                        if (((CamELX *)D_807F5CE8)->unk15E >= 0x15) {
                            ((CamELX *)D_807F5D0C)->unk15E = 0x14;
                        } else {
                            ((CamELX *)D_807F5D0C)->unk15E = ((CamELX *)D_807F5CE8)->unk15E;
                        }
                        ((CamELX *)D_807F5D0C)->unkE6 = ((CamELX *)D_807F5CE8)->unkE6;
                        func_80622B24((CamActor *)arg0, arg1, arg2, arg3, &st->unk78, &st->unk7C, &st->unk80,
                                      (CamActor *)D_807F5D0C);
                        *arg4 = st->unk78;
                        *arg5 = st->unk7C;
                        *arg6 = st->unk80;
                        break;
                    case 8:
                    case 12:
                        break;
                    default:
                        D_807476A4 = 0.3f;
                        func_80622B24((CamActor *)arg0, arg1, arg2, arg3, &st->unk78, &st->unk7C, &st->unk80,
                                      (CamActor *)D_807F5CE8);
                        if (CAMEL_PATH_NODE.unk1 != 7 && CAMEL_PATH_NODE.unk1 != 0xF && CAMEL_PATH_NODE.unk1 != 0x11) {
                            d = (0.0f != ((CamELX *)D_807F5CE8)->unkB4) ? 0.3 : 0.1;
                            func_80625994((struct CamE2Player *)arg0, d, arg4, arg5, arg6);
                        }
                        if ((D_807FBB60 & 0x2000) || CAMEL_PATH_NODE.unk1 == 7 || CAMEL_PATH_NODE.unk1 == 0xF ||
                            CAMEL_PATH_NODE.unk1 == 0x11) {
                            D_807FBB60 &= ~0x2000;
                            *arg4 = st->unk78;
                            *arg5 = st->unk7C;
                            *arg6 = st->unk80;
                        }
                        break;
                }
                if (st->unkF2 != 0) {
                    func_8061EDA0((CamState *)st, arg1, arg2, arg3, st->unkC0, 0);
                }
            }
        }
    }
    st->unkAC &= 0x7FFDAF0F;
    if (D_807FBB64 & 0x8000) {
        st->unkAC |= 4;
    } else if (!(st->unkAC & 0x10000)) {
        st->unkAC &= ~4;
    }
    if (st->unkF2 != 0) {
        func_8061EDA0((CamState *)st, arg4, arg5, arg6, (s32)(st->unkC0 * 0.333), 1);
    }
    if (!(st->unkAC & 0x100)) {
        func_80627490(&sp84, &sp80, *arg4, *arg5, *arg6, *arg1, *arg2, *arg3);
        fs = cosApprox(sp80);
        *arg8 = func_80612790(CAMEL->unkE4);
        *arg7 = func_80612794(CAMEL->unkE4) * cosApprox(sp84) * fs;
        *arg9 = func_80612794(CAMEL->unkE4) * sinApprox(sp84) * fs;
        CAMEL->unkEC = CAMEL->unkE4;
    }
    st->unkCC = X->unk7C;
    st->unkD0 = X->unk80;
    st->unkD4 = X->unk84;
}

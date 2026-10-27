// func_8061F53C (src/global/201B0.c): stage 5 (parked NON_MATCHING in .scratch/CamCL/201B0_final.c): same size 1102 insns/frame 0x118/stack slots/all s-regs; remaining diff = i*4 CSE temp coalesced via 'move s2,t9' + lh a1 not in jal delay slot; extra 'move t0,a0' (path var copy; dropping the var instead hoists lui/addiu of renderBonusTargetMarker above bne). Needs top-block: none; prototypes agree with file.
typedef struct CamLEnt {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ u8 unk16;
    /* 0x17 */ u8 unk17;
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 unk19;
    /* 0x1A */ u8 unk1A;
    /* 0x1B */ u8 unk1B;
} CamLEnt; // size = 0x1C

typedef struct CamLPath {
    /* 0x00 */ u8 pad0[0xC4];
    /* 0xC4 */ CamLEnt *unkC4;
    /* 0xC8 */ s8 *unkC8;
} CamLPath;

typedef struct CamLVec3s {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
    /* 0x4 */ s16 z;
} CamLVec3s;

typedef struct CamLPair {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 unk2;
} CamLPair;

typedef struct CamLTgtSub {
    /* 0x000 */ u8 pad0[0x10C];
    /* 0x10C */ s8 unk10C;
} CamLTgtSub;

typedef struct CamLTgt {
    /* 0x000 */ u8 pad0[0x7C];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x5E];
    /* 0x0E6 */ s16 unkE6;
    /* 0x0E8 */ u8 padE8[0x44];
    /* 0x12C */ s16 unk12C;
    /* 0x12E */ u8 pad12E[0x26];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
    /* 0x156 */ u8 pad156[0x1E];
    /* 0x174 */ CamLTgtSub *unk174;
} CamLTgt;

typedef struct CamLSt {
    /* 0x00 */ CamLTgt *unk0;
    /* 0x04 */ u8 pad4[0x68];
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ u8 pad70[0x34];
    /* 0xA4 */ f32 unkA4;
    /* 0xA8 */ u8 padA8[4];
    /* 0xAC */ s32 unkAC;
    /* 0xB0 */ u8 padB0[2];
    /* 0xB2 */ s16 unkB2;
    /* 0xB4 */ u8 padB4[4];
    /* 0xB8 */ f32 unkB8;
    /* 0xBC */ u8 padBC[8];
    /* 0xC4 */ s16 unkC4;
    /* 0xC6 */ s16 unkC6;
    /* 0xC8 */ s16 unkC8;
    /* 0xCA */ s16 unkCA;
    /* 0xCC */ u8 padCC[0x20];
    /* 0xEC */ u8 unkEC;
    /* 0xED */ u8 unkED;
    /* 0xEE */ u8 padEE[3];
    /* 0xF1 */ u8 unkF1;
    /* 0xF2 */ u8 padF2;
    /* 0xF3 */ u8 unkF3;
    /* 0xF4 */ u8 padF4[5];
    /* 0xF9 */ u8 unkF9;
    /* 0xFA */ u8 padFA[3];
    /* 0xFD */ u8 unkFD;
} CamLSt;

typedef struct CamLAct {
    /* 0x00 */ u8 pad0[0xB4];
    /* 0xB4 */ f32 unkB4;
} CamLAct;

extern f32 D_807FD888;
s32 func_806259FC(s16, s16);

#define CAML_GROUP ((CamLPair *)D_807476C0)
#define CAML_SORT ((CamLPair *)D_80747704)
#define CAML_PATH ((CamLPath *)D_807476FC)

s32 func_8061F53C(CamActor *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 *arg4, f32 *arg5, f32 *arg6) {
    CamLEnt *e;
    s16 ret;
    u8 type0;
    u8 spread;
    s32 rad;
    s16 weight;
    s16 i;
    f32 distSq;
    CamLSt *st;
    CamLTgt *tgt;
    f32 x;
    f32 z;
    f32 y;
    s16 cell;
    s16 k;
    CamLEnt *best;
    s16 bestIdx;
    s16 padA;
    u8 type;
    u8 hadFlag;
    u8 mode;
    u8 bestType0;
    u8 handled;
    s16 pos[3];
    u8 padB1;
    u8 padB2;
    u8 padB3;
    u8 linkId;
    s16 ang0;
    s16 ang1;
    s16 dist0;
    s32 ang2;
    f32 factor;
    f32 outX;
    f32 outY;
    f32 outZ;
    CamLPath *path;

    st = (CamLSt *)arg0->unk174;
    tgt = st->unk0;
    e = (CamLEnt *)tgt->unk174;
    x = tgt->unk7C;
    y = tgt->unk80 + ((CamLTgtSub *)e)->unk10C;
    z = tgt->unk84;
    weight = 0;
    bestIdx = 0;
    handled = 0;
    linkId = 0xFF;
    if (st->unkAC & 0x2000) {
        hadFlag = 1;
    } else {
        hadFlag = 0;
    }
    st->unkAC &= ~0x2000;
    cell = (s32)(z - D_807F5CD4) / 400 * D_807F5CD8 + (s32)(x - D_807F5CD2) / 400;
    if (cell < 0) {
        return 0;
    }
    if (D_807F5CDA > 0) {
        i = 0;
        do {
            if (func_806259FC(cell, D_807476C0[i * 2]) != 0) {
                k = D_807476C0[i * 2 + 1];
                if (k < D_807476C0[i * 2 + 3]) {
                    do {
                        e = &CAML_PATH->unkC4[D_80747704[k * 2]];
                        spread = e->unk1A;
                        pos[0] = e->unk10;
                        pos[1] = e->unk12;
                        pos[2] = e->unk14;
                        rad = (e->unk19 * 4) & 0xFFFF;
                        mode = e->unk1B;
                        path = CAML_PATH;
                        type0 = e->unk16;
                        if (e->unk16 == 5) {
                            linkId = e->unk0;
                            e = &CAML_PATH->unkC4[e->unk0];
                        }
                        type = e->unk16;
                        if (k == st->unkC4 && type == 8) {
                            if (e->unk18 >= 0xF) {
                                rad = (rad * (e->unk18 - 0xD)) & 0xFFFF;
                            }
                        }
                        if (mode != 0) {
                            if (mode == 1 || mode == 2) {
                                distSq = (z - pos[2]) * (z - pos[2]) + (x - pos[0]) * (x - pos[0]);
                            }
                        } else {
                            distSq = (x - pos[0]) * (x - pos[0]) + (y - pos[1]) * (y - pos[1]) + (z - pos[2]) * (z - pos[2]);
                        }
                        if (tgt->unk12C == path->unkC8[D_80747704[k * 2]] || type == 8 ||
                            path->unkC8[D_80747704[k * 2]] == -1) {
                            if ((mode == 2 && distSq < (f32)(rad * rad) && weight < e->unk18 && !((s16)(s32)y < pos[1]) &&
                                 pos[1] + spread * 2 >= (s16)(s32)y) ||
                                (mode != 2 && distSq < (f32)(rad * rad) && weight < e->unk18)) {
                                switch (type) {
                                    case 4:
                                        handled = 1;
                                        if (k != st->unkC6) {
                                            func_806224CC(arg0, (CamActor *)tgt);
                                        }
                                        st->unkC6 = k;
                                        st->unkC4 = -1;
                                        break;
                                    case 0:
                                        handled = 1;
                                        if (k != st->unkC6) {
                                            func_8061F4B0((u8 *)e);
                                        }
                                        st->unkC6 = k;
                                        break;
                                    case 1:
                                    case 2:
                                    case 3:
                                    case 7:
                                    case 8:
                                    case 9:
                                        if (e->unk17 & 0x20) {
                                            if (!(st->unkAC & 0x40000)) {
                                                break;
                                            }
                                        }
                                        if (e->unk17 & 0x10) {
                                            if (!((tgt->unk154 == 0x54 && tgt->unk155 >= 3) ||
                                                  (tgt->unk154 == 0x52 && tgt->unk155 >= 8) ||
                                                  (tgt->unk154 == 0x53 && tgt->unk155 >= 3))) {
                                                break;
                                            }
                                        }
                                        if ((e->unk17 & 2) && (e->unk17 & 4)) {
                                            break;
                                        }
                                        if (e->unk17 & 8) {
                                            if (e->unk17 & 4) {
                                                break;
                                            }
                                            if (D_807FD888 == 0.0f) {
                                                break;
                                            }
                                        }
                                        if (!(st->unkAC & 2) && !(e->unk17 & 1)) {
                                            if (!(D_8076A064 & 8) && D_807FC928 == 1) {
                                                renderCallbacksRegister(renderBonusTargetMarker, arg0, 3);
                                            }
                                            break;
                                        }
                                        if (!(e->unk17 & 0x38) && D_807FC928 == 1) {
                                            renderCallbacksRegister(renderBonusTargetMarker, arg0, 3);
                                        }
                                    default:
                                        best = e;
                                        bestIdx = k;
                                        weight = (s16)e->unk18;
                                        st->unkEC = e->unk17;
                                        bestType0 = type0;
                                        break;
                                }
                            }
                        }
                        k++;
                    } while (k < D_807476C0[i * 2 + 3]);
                }
            }
            i++;
        } while (i < D_807F5CDA);
    }
    if (weight != 0) {
        ret = 1;
        if (bestType0 != 5) {
            linkId = 0xFF;
        }
        type = best->unk16;
        if (bestIdx != st->unkC4 || st->unkF3 != 2) {
            switch (type) {
            case 8:
                ang0 = mathAngleBetweenPoints2D(best->unk0, best->unk4, best->unk6, best->unkA);
                if (D_807476A8 > 10.0f) {
                    ang1 = mathAngleBetweenPoints2D(tgt->unk7C, tgt->unk84, *arg1, *arg3);
                } else {
                    ang1 = st->unkB2;
                }
                ang2 = ang0 + 0x800;
                dist0 = mathAngleDistance(ang1, ang0);
                if (dist0 < mathAngleDistance(ang1, ang2)) {
                    st->unkB2 = ang0;
                } else {
                    st->unkB2 = ang2;
                }
                break;
            case 9:
                ang0 = mathAngleBetweenPoints2D(tgt->unk7C, tgt->unk84, best->unk0, best->unk4);
                ang1 = mathAngleBetweenPoints2D(tgt->unk7C, tgt->unk84, best->unk6, best->unkA);
                dist0 = mathAngleDistance(ang0, st->unkB2);
                if (dist0 < mathAngleDistance(ang1, st->unkB2)) {
                    st->unkF9 = 0;
                } else {
                    st->unkF9 = 1;
                }
                break;
            }
        }
        switch (type) {
            case 7:
                if (tgt->unk154 != 0x20) {
                    ang1 = mathAngleBetweenPoints2D(best->unk10, best->unk14, tgt->unk7C, tgt->unk84);
                    *arg1 = best->unk10 - func_80612794(ang1) * best->unk0;
                    *arg3 = best->unk14 - func_80612790(ang1) * best->unk0;
                    *arg2 = st->unk6C + ((CamLAct *)arg0)->unkB4;
                    st->unkC8 = 0;
                    st->unkCA = 0;
                }
                break;
            case 6:
                if (hadFlag == 0) {
                    st->unkF1 = 0xB;
                }
                ret = 0;
                st->unkAC = st->unkAC | (((u8 *)best)[2] | 0x2000);
                if (((u8 *)best)[0] != 0) {
                    st->unkA4 = ((u8 *)best)[0];
                    st->unkB8 = ((u8 *)best)[1];
                }
                break;
            case 1:
                *arg1 = best->unk0;
                *arg2 = best->unk2;
                *arg3 = best->unk4;
                st->unkC8 = best->unk6;
                st->unkCA = best->unk8;
                break;
            case 9:
                *arg1 = ((CamLEnt *)((s16 *)best + st->unkF9 * 3))->unk0;
                *arg2 = ((CamLEnt *)((s16 *)best + st->unkF9 * 3))->unk2;
                *arg3 = ((CamLEnt *)((s16 *)best + st->unkF9 * 3))->unk4;
                st->unkC8 = 0;
                st->unkCA = 0;
                break;
            case 2:
                func_8061F2B8(x, y, z, best->unk0, best->unk2, best->unk4, best->unk6, best->unk8, best->unkA, arg1, arg2, arg3);
                st->unkC8 = best->unkC;
                st->unkCA = best->unkE;
                break;
            case 8:
                func_8062133C(arg0, (CamActor *)tgt, &outX, &outY, &outZ, -1.0f);
                func_8061F2B8(outX, outY, outZ, best->unk0, best->unk2, best->unk4, best->unk6, best->unk8, best->unkA, arg1, arg2, arg3);
                st->unkC8 = 0;
                st->unkCA = 0;
                break;
            case 3:
                st->unkC8 = best->unk8;
                st->unkCA = best->unkA;
                factor = best->unk6 / sqrtf((z - best->unk4) * (z - best->unk4) + ((x - best->unk0) * (x - best->unk0) + (y - best->unk2) * (y - best->unk2)));
                factor = factor > 1.0 ? 1.0 : factor;
                *arg1 = (best->unk0 - x) * factor + x;
                *arg2 = (best->unk2 - st->unk6C) * factor + st->unk6C;
                *arg3 = (best->unk4 - z) * factor + z;
                break;
        }
        if (!(st->unkAC & 0x8000) && ret != 0 && (bestIdx != st->unkC4 || st->unkF3 != 2) &&
            (linkId == 0xFF || (linkId != 0xFF && (st->unkFD != linkId || st->unkF3 != 2) && !(D_807FBB60 & 0x2000)))) {
            if (D_807463B8 == 3) {
                D_807FBB60 |= 0x2000;
            } else if (!(st->unkAC & 0x100)) {
                func_8061F18C(arg0, *arg1, *arg2, *arg3);
            }
        }
        if ((st->unkAC & 0x8000) || D_807FD888 > 27.0f || (best->unk17 & 0x38)) {
            D_807FBB60 |= 0x2000;
            st->unkAC &= 0xFFFF7FFF;
        }
        if (handled == 0) {
            st->unkC6 = -1;
        }
        st->unkFD = linkId;
        st->unkC4 = bestIdx;
        st->unkED = type;
        return ret;
    }
    if (st->unkAC & 0x40000) {
        func_80620628(arg0, 0.0f, st->unkB2, 0);
    }
    if (hadFlag != 0 && !(st->unkAC & 0x2000)) {
        func_80622334(arg0, D_807476A8);
    }
    if (st->unkF3 == 2) {
        if (st->unkEC & 0xA) {
            CAML_PATH->unkC4[CAML_SORT[st->unkC4].unk0].unk17 |= 4;
        }
        if (st->unkED != 8 || mathAngleDistance(st->unkB2, tgt->unkE6) >= 0x400) {
            st->unkB2 = mathAngleBetweenPoints2D(tgt->unk7C, tgt->unk84, *arg1, *arg3);
        }
        if (D_807476A8 > 150.0f) {
            func_8061B840((CamAV *)st, 0xF);
        }
    }
    if (handled == 0) {
        st->unkC6 = -1;
    }
    st->unkC4 = -1;
    st->unkEC = 0;
    st->unkFD = 0xFF;
    st->unkAC &= ~2;
    return 0;
}

#include "common.h"
#include "actor.h"

void *func_80610FE8(s32);
typedef struct PathEntry {
    u8 *unk0;
    s16 unk4;
} PathEntry;


typedef struct PathPlayback {
    s32 unk0;
    u8 *unk4;
    s16 unk8;
    u8 padA[2];
    f32 unkC;
    s16 unk10;
    u8 pad12[2];
    u8 unk14;
    u8 unk15;
    u8 unk16;
    u8 pad17;
    s32 unk18;
    s32 unk1C;
    u8 unk20;
    u8 unk21;
} PathPlayback;

extern PathEntry *D_807FDB90[];


void assetFreeBuffer(s32, s32, s32);
s32 assetLoad(s32, s32, s32, s32);
void func_80722E48(s16 *);

void pathFreeAsset(s32 arg0) {
    s32 sp1C;
    s32 temp_v0;

    temp_v0 = assetLoad(0xF, arg0, 1, 1);
    sp1C = temp_v0;
    func_80722E48((s16 *) temp_v0);
    assetFreeBuffer(sp1C, 0x47, 0x27);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/127B00/func_80722E48.s")

s32 pathExists(u8 arg0) {
    if (D_807FDB90[arg0] != NULL) {
        return 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/127B00/func_80723020.s")
extern PathPlayback *D_807FDBF8[];


void func_80723284(s32 arg0, u8 arg1) {
    PathPlayback *temp_v0;

    if (arg0 != -1) {
        temp_v0 = D_807FDBF8[arg0];
        if (temp_v0 != NULL) {
            temp_v0->unk20 = arg1;
        }
    }
}

void func_807232B8(s32 arg0, u8 arg1) {
    PathPlayback *temp_v0;

    if (arg0 != -1) {
        temp_v0 = D_807FDBF8[arg0];
        if (temp_v0 != NULL) {
            temp_v0->unk16 = arg1;
        }
    }
}

void func_807232EC(s32 arg0, u8 arg1) {
    PathPlayback *temp_v0;

    if (arg0 != -1) {
        temp_v0 = D_807FDBF8[arg0];
        if (temp_v0 != NULL) {
            temp_v0->unk15 = arg1;
        }
    }
}

void func_80723320(s32 arg0, s32 arg1) {
    PathPlayback *temp_v0;

    if (arg0 != -1) {
        temp_v0 = D_807FDBF8[arg0];
        if (temp_v0 != NULL) {
            temp_v0->unk18 = arg1;
        }
    }
}

void func_8072334C(s32 arg0, u8 arg1) {
    PathPlayback *temp_v0;

    if (arg0 != -1) {
        temp_v0 = D_807FDBF8[arg0];
        if (temp_v0 != NULL) {
            temp_v0->unk21 = arg1;
        }
    }
}

void func_80723380(s32 arg0, u8 arg1) {
    PathPlayback *temp_v0;

    if (arg0 != -1) {
        temp_v0 = D_807FDBF8[arg0];
        if (temp_v0 != NULL) {
            temp_v0->unk14 = arg1;
        }
    }
}

void func_80723428(s32);

void pathPlaybackStopForActor(s32 arg0) {
    PathPlayback **var_s1;
    PathPlayback *temp_v0;
    s32 var_s0;

    var_s1 = D_807FDBF8;
    var_s0 = 0;
    do {
        temp_v0 = *var_s1;
        if ((temp_v0 != NULL) && (arg0 == temp_v0->unk0)) {
            func_80723428(var_s0);
        }
        var_s0 += 1;
        var_s1 += 1;
    } while (var_s0 != 0x20);
}

#pragma GLOBAL_ASM("asm/global/nonmatchings/127B00/func_80723428.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/127B00/func_80723484.s")

typedef struct Fx127BPoint {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
} Fx127BPoint;

#define FX127B_PT(e) ((Fx127BPoint *)(e)->unk0)

typedef struct Fx127BPlayback {
    s32 unk0;
    PathEntry path;
    f32 unkC;
    s32 unk10;
    u8 pad14[2];
    u8 unk16;
} Fx127BPlayback;

f32 splineEvalCubic(f64, f32, f32, f32, f32);
void splineSetBasisTension(f32);
f32 func_80724308(s32, f32, f32, f32, s32, f32);

void func_807238D4(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    u8 ids[4];
    Fx127BPlayback *p;
    PathEntry *e;

    if (arg0 != -1) {
        if (D_807FDBF8[arg0] != NULL) {
            splineSetBasisTension(0.5f);
            p = (Fx127BPlayback *)D_807FDBF8[arg0];
            e = &p->path;
            if (p->unk16 == 0) {
                if (p->unk10 - 1 < 0) {
                    ids[0] = 0;
                } else {
                    ids[0] = p->unk10 - 1;
                }
                if (p->unk10 + 1 >= e->unk4) {
                    ids[2] = e->unk4 - 1;
                } else {
                    ids[2] = p->unk10 + 1;
                }
                if (p->unk10 + 2 >= e->unk4) {
                    ids[3] = e->unk4 - 1;
                } else {
                    ids[3] = p->unk10 + 2;
                }
            } else {
                if (p->unk10 - 1 < 0) {
                    ids[0] = e->unk4 - 1;
                } else {
                    ids[0] = p->unk10 - 1;
                }
                if (p->unk10 + 1 >= e->unk4) {
                    ids[2] = (p->unk10 + 1) % e->unk4;
                } else {
                    ids[2] = p->unk10 + 1;
                }
                if (p->unk10 + 2 >= e->unk4) {
                    ids[3] = (p->unk10 + 2) % e->unk4;
                } else {
                    ids[3] = p->unk10 + 2;
                }
            }
            ids[1] = p->unk10;
            *arg1 = splineEvalCubic(p->unkC, FX127B_PT(e)[ids[0]].unk2, FX127B_PT(e)[ids[1]].unk2, FX127B_PT(e)[ids[2]].unk2, FX127B_PT(e)[ids[3]].unk2);
            *arg2 = splineEvalCubic(p->unkC, FX127B_PT(e)[ids[0]].unk4, FX127B_PT(e)[ids[1]].unk4, FX127B_PT(e)[ids[2]].unk4, FX127B_PT(e)[ids[3]].unk4);
            *arg3 = splineEvalCubic(p->unkC, FX127B_PT(e)[ids[0]].unk6, FX127B_PT(e)[ids[1]].unk6, FX127B_PT(e)[ids[2]].unk6, FX127B_PT(e)[ids[3]].unk6);
        }
    }
}

u8 func_80723C98(s32 arg0) {
    PathPlayback *temp_v1;

    if ((arg0 == -1) || ((temp_v1 = D_807FDBF8[arg0]) == NULL)) {
        return 0;
    }
    return temp_v1->unk21;
}

void func_80723CCC(s32 arg0, s32 arg1, f32 arg2, f32 *arg3, f32 *arg4, f32 *arg5) {
    u8 ids[4];
    PathEntry *e;

    splineSetBasisTension(0.5f);
    e = D_807FDB90[arg0];
    if (arg1 >= e->unk4) {
        arg1 = e->unk4 - 1;
    }
    if (arg1 - 1 < 0) {
        ids[0] = 0;
    } else {
        ids[0] = arg1 - 1;
    }
    ids[1] = arg1;
    if (arg1 + 1 >= e->unk4) {
        ids[2] = e->unk4 - 1;
    } else {
        ids[2] = arg1 + 1;
    }
    if (arg1 + 2 >= e->unk4) {
        ids[3] = e->unk4 - 1;
    } else {
        ids[3] = arg1 + 2;
    }
    *arg3 = splineEvalCubic(arg2, FX127B_PT(e)[ids[0]].unk2, FX127B_PT(e)[ids[1]].unk2, FX127B_PT(e)[ids[2]].unk2, FX127B_PT(e)[ids[3]].unk2);
    *arg4 = splineEvalCubic(arg2, FX127B_PT(e)[ids[0]].unk4, FX127B_PT(e)[ids[1]].unk4, FX127B_PT(e)[ids[2]].unk4, FX127B_PT(e)[ids[3]].unk4);
    *arg5 = splineEvalCubic(arg2, FX127B_PT(e)[ids[0]].unk6, FX127B_PT(e)[ids[1]].unk6, FX127B_PT(e)[ids[2]].unk6, FX127B_PT(e)[ids[3]].unk6);
}

void func_80723F88(s32 arg0, f32 arg1, f32 arg2, f32 arg3, s32 *arg4, f32 *arg5) {
    f32 best;
    f32 frac;
    f32 d;
    s32 bestIdx;
    s32 i;
    s32 end;

    best = 999999.0f;
    frac = 0.0f;
    splineSetBasisTension(0.5f);
    for (i = 0; i < D_807FDB90[arg0]->unk4; i++) {
        d = func_80724308(arg0, arg1, arg2, arg3, i, 0.0f);
        if (d < best) {
            bestIdx = i;
            *arg4 = i;
            *arg5 = 0.0f;
            best = d;
        }
    }
    end = bestIdx;
    if (bestIdx - 1 < 0) {
        i = 0;
    } else {
        i = bestIdx - 1;
    }
    end++;
    goto fake_label; fake_label: ; // FAKE: block boundary before refinement loop (register/scheduling steer)
    while (i <= end) {
        d = func_80724308(arg0, arg1, arg2, arg3, i, frac);
        if (d < best) {
            *arg4 = i;
            *arg5 = frac;
            best = d;
        }
        frac = frac + 0.005;
        if (frac >= 1.0) {
            frac = frac - 1.0;
            i++;
        }
    }
}

void func_80724154(s32 arg0, f32 arg1, f32 arg2, f32 arg3, s32 *arg4, f32 *arg5) {
    f32 best;
    f32 frac;
    f32 d;
    s32 idx;
    s32 i;

    best = 999999.0f;
    idx = *arg4;
    frac = *arg5 - 0.5;
    i = 20;
    if (frac < 0.0) {
        if (idx > 0) {
            idx -= 1;
            frac += 1.0f;
        } else {
            frac = 0.0f;
        }
    }
    while (i--) {
        d = func_80724308(arg0, arg1, arg2, arg3, idx, frac);
        if (d < best) {
            *arg4 = idx;
            *arg5 = frac;
            best = d;
        }
        frac = frac + 0.05;
        if (frac >= 1.0f && idx < D_807FDB90[arg0]->unk4) {
            idx += 1;
            frac -= 1.0f;
        } else if (frac >= 1.0f) {
            frac = 1.0f;
        }
    }
}

f32 func_80724308(s32 arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4, f32 arg5) {
    u8 ids[4];
    PathEntry *e;
    f32 sx;
    f32 sy;
    f32 sz;

    e = D_807FDB90[arg0];
    if (arg4 >= e->unk4) {
        arg4 = e->unk4 - 1;
    }
    if (arg4 - 1 < 0) {
        ids[0] = 0;
    } else {
        ids[0] = arg4 - 1;
    }
    ids[1] = arg4;
    if (arg4 + 1 >= e->unk4) {
        ids[2] = e->unk4 - 1;
    } else {
        ids[2] = arg4 + 1;
    }
    if (arg4 + 2 >= e->unk4) {
        ids[3] = e->unk4 - 1;
    } else {
        ids[3] = arg4 + 2;
    }
    sx = splineEvalCubic(arg5, FX127B_PT(e)[ids[0]].unk2, FX127B_PT(e)[ids[1]].unk2, FX127B_PT(e)[ids[2]].unk2, FX127B_PT(e)[ids[3]].unk2);
    sy = splineEvalCubic(arg5, FX127B_PT(e)[ids[0]].unk0, FX127B_PT(e)[ids[1]].unk0, FX127B_PT(e)[ids[2]].unk0, FX127B_PT(e)[ids[3]].unk0);
    sz = splineEvalCubic(arg5, FX127B_PT(e)[ids[0]].unk6, FX127B_PT(e)[ids[1]].unk6, FX127B_PT(e)[ids[2]].unk6, FX127B_PT(e)[ids[3]].unk6);
    return sqrtf((arg1 - sx) * (arg1 - sx) + (arg2 - sy) * (arg2 - sy) + (arg3 - sz) * (arg3 - sz));
}

s16 pathEntryCount(s32 arg0) {
    return D_807FDB90[arg0]->unk4;
}

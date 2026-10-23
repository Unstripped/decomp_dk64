// func_80653804 (src/global/55B20.c): stage 2: full behaviour reconstructed from asm (identical asm to func_80654FEC); frame 0x88 vs 0xC8: target has 18 f64 slots (0x38..0xC8) of which only 0x38(sp38=t1), 0x88,0x90,0x98,0xA0 (4 uninitialised locals copied in/out) are referenced; needs ~8 more live f64 temps to force the slots. Also prologue field-load order differs
typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ u8 pad6[6];
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ u8 pad12[2];
} M55P3Box;

s32 func_80653684(void *arg0, f32 arg1, f32 arg2) {
    f32 temp_fa1;
    f32 temp_fv1;
    f32 var_fv0;
    f32 var_fv0_2;
    f32 var_fv0_3;
    f32 var_fv0_4;
    s16 temp_a1;
    s16 temp_a2;
    s16 temp_v1;
    s16 temp_v0;
    M55P3Box *box;

    box = arg0;
    temp_v1 = box->unk2;
    temp_v0 = box->unk0;
    if (temp_v0 < temp_v1) {
        var_fv0 = (f32) temp_v0;
    } else {
        var_fv0 = (f32) temp_v1;
    }
    temp_fv1 = (f32) box->unk4;
    if (!(var_fv0 < temp_fv1)) {
        var_fv0 = temp_fv1;
    }
    if (arg1 < var_fv0) {
        return 0;
    }
    temp_a1 = box->unkC;
    temp_a2 = box->unkE;
    if (temp_a1 < temp_a2) {
        var_fv0_2 = (f32) temp_a1;
    } else {
        var_fv0_2 = (f32) temp_a2;
    }
    temp_fa1 = (f32) box->unk10;
    if (!(var_fv0_2 < temp_fa1)) {
        var_fv0_2 = temp_fa1;
    }
    if (arg2 < var_fv0_2) {
        return 0;
    }
    if (temp_v1 < temp_v0) {
        var_fv0_3 = (f32) temp_v0;
    } else {
        var_fv0_3 = (f32) temp_v1;
    }
    if (!(temp_fv1 < var_fv0_3)) {
        var_fv0_3 = temp_fv1;
    }
    if (var_fv0_3 < arg1) {
        return temp_v1 * 0;
    }
    if (temp_a2 < temp_a1) {
        var_fv0_4 = (f32) temp_a1;
    } else {
        var_fv0_4 = (f32) temp_a2;
    }
    if (!(temp_fa1 < var_fv0_4)) {
        var_fv0_4 = temp_fa1;
    }
    if (var_fv0_4 < arg2) {
        return 0;
    }
    return 1;
}

typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ u8 pad6[6];
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ u8 pad12[2];
} M55P3Tri;

s32 func_80653804(void *arg0, f32 arg1, f32 arg2) {
    f64 fv0;
    f64 fv1;
    f64 fs0;
    f64 ft0;
    f64 spA0;
    f64 sp98;
    f64 sp90;
    f64 sp88;
    f64 fs1;
    f64 fs2;
    f64 ft4;
    f64 ft5;
    f64 fa0;
    f64 fa1;
    f64 fs3;
    f64 fs4;
    f64 fs5;
    f64 sp38;
    s32 sgn1;
    s32 sgn2;
    s32 flag;
    s32 i;

    fs3 = arg1;
    fs4 = arg2;
    fs5 = ((M55P3Tri *)arg0)->unk0;
    sp38 = ((M55P3Tri *)arg0)->unkC;
    fs1 = (fs5 + ((f64)(((M55P3Tri *)arg0)->unk4 + ((M55P3Tri *)arg0)->unk2) * 0.5)) * 0.5;
    fs2 = (sp38 + ((f64)(((M55P3Tri *)arg0)->unk10 + ((M55P3Tri *)arg0)->unkE) * 0.5)) * 0.5;
    ft5 = sp88;
    ft4 = sp90;
    fa1 = sp98;
    fa0 = spA0;
    flag = 0;
    i = 0;
    do {
        switch (i) {
        default:
            fv0 = (fs3 - ft4) * fa1;
            fv1 = (fs4 - ft5) * fa0;
            fs0 = ((fs1 - ft4) * fa1) - ((fs2 - ft5) * fa0);
            break;
        case 0:
            ft4 = fs5;
            ft5 = sp38;
            fa1 = (f64)(((M55P3Tri *)arg0)->unkE - ((M55P3Tri *)arg0)->unkC);
            fa0 = (f64)(((M55P3Tri *)arg0)->unk2 - ((M55P3Tri *)arg0)->unk0);
            fv0 = (fs3 - fs5) * fa1;
            fv1 = (fs4 - ft5) * fa0;
            fs0 = ((fs1 - fs5) * fa1) - ((fs2 - ft5) * fa0);
            break;
        case 1:
            ft4 = fs5;
            ft5 = sp38;
            fa1 = (f64)(((M55P3Tri *)arg0)->unk10 - ((M55P3Tri *)arg0)->unkC);
            fa0 = (f64)(((M55P3Tri *)arg0)->unk4 - ((M55P3Tri *)arg0)->unk0);
            fv0 = (fs3 - fs5) * fa1;
            fv1 = (fs4 - ft5) * fa0;
            fs0 = ((fs1 - fs5) * fa1) - ((fs2 - ft5) * fa0);
            break;
        case 2:
            ft4 = (f64)((M55P3Tri *)arg0)->unk2;
            ft5 = (f64)((M55P3Tri *)arg0)->unkE;
            fa0 = (f64)(((M55P3Tri *)arg0)->unk4 - ((M55P3Tri *)arg0)->unk2);
            fa1 = (f64)(((M55P3Tri *)arg0)->unk10 - ((M55P3Tri *)arg0)->unkE);
            fv0 = (fs3 - ft4) * fa1;
            fv1 = (fs4 - ft5) * fa0;
            fs0 = ((fs1 - ft4) * fa1) - ((fs2 - ft5) * fa0);
            break;
        }
        i++;
        sgn1 = -1;
        if (fv1 <= fv0) {
            sgn1 = 1;
        }
        sgn2 = -1;
        if (fs0 >= 0.0) {
            sgn2 = 1;
        }
        if (sgn2 != sgn1) {
            flag = 1;
        }
    } while (i != 3);
    sp88 = ft5;
    sp90 = ft4;
    sp98 = fa1;
    spA0 = fa0;
    return (flag == 0) & 0xFF;
}




typedef struct {
    /* 0x000 */ u8 pad0[4];
    /* 0x004 */ void *unk4;
    /* 0x008 */ u8 pad8[0x270 - 0x8];
    /* 0x270 */ s16 unk270;
    /* 0x272 */ s16 unk272;
    /* 0x274 */ s16 unk274;
    /* 0x276 */ s16 unk276;
    /* 0x278 */ s16 unk278;
    /* 0x27A */ s16 unk27A;
    /* 0x27C */ u8 pad27C[0x288 - 0x27C];
    /* 0x288 */ f32 unk288;
    /* 0x28C */ u8 pad28C[4];
    /* 0x290 */ s16 unk290;
    /* 0x292 */ u8 pad292[0x2F0 - 0x292];
} M55P3Player;

extern M55P3Player *D_807FC924;
extern u8 D_807FC929;

void func_80653A70(s16 arg0) {
    D_807F6C18[arg0].unk0 = 1;
    D_807F6C18[arg0].unk1 |= 1 << D_807FC929;
    D_807F6C18[arg0].unk68 = D_807FC924[D_807FC929].unk270;
    D_807F6C18[arg0].unk6C = D_807FC924[D_807FC929].unk272;
    D_807F6C18[arg0].unk70 = D_807FC924[D_807FC929].unk274;
    D_807F6C18[arg0].unk74 = D_807FC924[D_807FC929].unk276;
}


void func_80653B70(s8 arg0) {
    D_807F70AB = arg0;
}

void func_8062AD28(f32, f32, f32, void *, void *);
void func_8062AC68(Mtx *);
void func_8062A944(f32, f32, f32);
void mapUpdateFogDistance(f32 *, s16);
void func_806521F8();
void func_80653A70(s16);
void func_806547A8(f32, f32, f32);
void func_80654380(f32, f32, f32);
void func_80654A2C(f32, f32, f32);
void func_80656F14(s16, s32, s16, s16, s16, s16, f32, f32, f32);
void func_8065F678(f32, f32, f32, u8);
void actorCalculateTargetDistancesAndAngles(f32, f32, f32);
void func_80655410(f32, f32, f32);
extern u8 D_807F5E20[];
extern u8 D_807F5E68[];
extern u8 D_807444FC;
extern f32 D_807F5FB4;
extern f32 D_807F5FB0;
extern u8 D_807F6C08;

void func_80653B80(f32 arg0, f32 arg1, f32 arg2) {
    D_807FC924[D_807FC929].unk290 = func_806531B8(arg0, arg1, arg2, D_807FC924[D_807FC929].unk290);
    if (D_807F70AB != 0) {
        D_807FC924[D_807FC929].unk290 = *(s16 *)((u8 *)D_807FC924[D_807FC929].unk4 + 0x12C);
    }
    mapUpdateFogDistance(&D_807FC924[D_807FC929].unk288, D_807FC924[D_807FC929].unk290);
    D_807F7138 = (s16)(s32)D_807FC924[D_807FC929].unk288;
    func_8062A944(D_807F5FB4, D_807F5FB0, (f32)D_807F7138);
    func_8062AC68((Mtx *)((u8 *)D_807FC924 + D_807FC929 * 0x2F0 + (D_807444FC << 6) + 8));
    func_8062AD28(arg0, arg1, arg2, &D_807F5E68, &D_807F5E20);
    func_806521F8();
    func_80653A70(D_807FC924[D_807FC929].unk290);
    func_806547A8(arg0, arg1, arg2);
    D_807F6C80 = 0;
    D_807F6C08 = 0;
    func_80656F14(D_807FC924[D_807FC929].unk290, 0, D_807FC924[D_807FC929].unk270, D_807FC924[D_807FC929].unk272, D_807FC924[D_807FC929].unk274, D_807FC924[D_807FC929].unk276, arg0, arg1, arg2);
    func_80654380(arg0, arg1, arg2);
    func_8065F678(arg0, arg1, arg2, D_807FC929);
    actorCalculateTargetDistancesAndAngles(arg0, arg1, arg2);
    func_80655410(arg0, arg1, arg2);
}

extern s32 func_8066B0F8(s32, s32, s32, s32);

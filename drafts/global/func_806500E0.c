// func_806500E0 (src/global/54150.c): stage 5: structure matches (u8->f32 bgez convert, 300.0 double divide, min(D_80744478,4)*0.5 f64 path, unkF state machine, div/mod guards) but block order differs: target lays the unkF==0 and unkF==1 bodies out-of-line (beqzl unkF==0 -> body0, beql unkF==1 -> body1, jr ra inline) while IDO here makes body0 the fallthrough; head scheduling loads p[2] after the (f32)p[1] conversion
typedef struct M54C_Anim {
    u8 *unk0;
    f32 unk4;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    u8 unkE;
    u8 unkF;
    u8 unk10;
    s8 unk11;
    u8 unk12;
    u8 unk13;
} M54C_Anim;

extern u32 D_80744478;

void func_806500E0(void *arg0raw) {
    M54C_Anim *arg0;
    u8 *node;
    u8 *p;
    u32 limit;
    u8 a;
    f32 f;
    f32 frac;
    f32 out;
    s32 i;

    arg0 = arg0raw;
    node = arg0->unk0;
    f = arg0->unk4;
    p = node + arg0->unk11;
    a = p[1];
    frac = (f32)a;
    frac += (f32)(p[2] - a) * f;
    out = (f32)arg0->unkC * (f32)(frac / 300.0);
    if (D_80744478 < 4) {
        limit = D_80744478;
    } else {
        limit = 4;
    }
    if (arg0->unk12 & 1) {
        out = (f64)out * ((f64)limit * 0.5);
    }
    if (arg0->unkF == 0) {
        arg0->unk4 = f + out;
        i = arg0->unk4;
        arg0->unk11 += i;
        arg0->unk4 -= (f32)i;
        if (arg0->unk11 < *(u8 *)node - 1) {
            return;
        }
        arg0->unk8 += arg0->unk11 / (*(u8 *)node - 1);
        if (arg0->unk8 < arg0->unkA || arg0->unkA == -1) {
            if (arg0->unk10 == 0) {
                arg0->unk11 = arg0->unk11 % (*(u8 *)node - 1);
            } else if (arg0->unk10 == 1) {
                if (arg0->unk11 / (*(u8 *)node - 1) != 0) {
                    arg0->unkF = 1;
                    arg0->unk11 = *(u8 *)node - 2;
                    arg0->unk4 = 1.0f;
                }
            }
        } else {
            arg0->unk4 = 1.0f;
            arg0->unkE = 0;
            arg0->unk11 = *(u8 *)node - 2;
            if (arg0->unk10 == 1) {
                arg0->unkF = 1;
            }
        }
        return;
    }
    if (arg0->unkF == 1) {
        arg0->unk4 = f - out;
        if (arg0->unk4 < 0.0) {
            i = (s32)arg0->unk4 - 1;
            arg0->unk11 += i;
            arg0->unk4 -= (f32)i;
        }
        if (arg0->unk11 < 0) {
            arg0->unk8 += (-arg0->unk11) / *(u8 *)node + 1;
            if (arg0->unk8 < arg0->unkA || arg0->unkA == -1) {
                if (arg0->unk10 == 0) {
                    arg0->unk11 = (-arg0->unk11) % (*(u8 *)node - 1);
                    if (arg0->unk11 != 0) {
                        arg0->unk11 = *(u8 *)node - arg0->unk11 - 1;
                    }
                } else if (arg0->unk10 == 1) {
                    if ((-arg0->unk11) / *(u8 *)node + 1 != 0) {
                        arg0->unkF = 0;
                        arg0->unk11 = 0;
                        arg0->unk4 = 0.0f;
                    }
                }
            } else {
                if (arg0->unk10 == 1) {
                    arg0->unkF = 0;
                    arg0->unk4 = 0.0f;
                }
                arg0->unk11 = 0;
                arg0->unkE = 0;
            }
            return;
        }
        return;
    }
}

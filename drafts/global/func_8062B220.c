// func_8062B220 (src/global/2F550.c): stage 6: same size (110) and frame (0x20); only register allocation differs (target int vars v0=z0,v1=z1,a1=y2,a2=y0,a3=z2,t0=y1,t1=x0,t2=x1,t3=x2 and fp fv0=y2,fv1=y0,fa0=y1,fa1=z2,ft4=z0,ft5=z1,fs0=x2,fs1=x0,fs2=x1; ours permutes them). Start from the m2c-shaped body; permuter (score 4995 -> 270) found the s16 *v pointer and new_var2 copy.
typedef struct R2F550aPoly {
    /* 0x00 */ s16 v[12];
    /* 0x18 */ u8 type;
    /* 0x19 */ u8 pad19[7];
    /* 0x20 */ f64 a;
    /* 0x28 */ f64 b;
    /* 0x30 */ f64 c;
    /* 0x38 */ f64 d;
} R2F550aPoly; /* 0x40 */

void func_8062B220(R2F550aPoly *arg0) {
    s16 temp_v1;
    s16 temp_v0;
    f64 temp_fa0;
    f64 temp_ft4;
    f64 temp_fs2;
    s16 temp_a2;
    f64 temp_fv1;
    s16 temp_a1;
    f64 temp_fs1;
    s16 temp_t2;
    f64 temp_fs0;
    s16 temp_t0;
    s16 temp_a3;
    s16 *new_var;
    s16 temp_t3;
    s16 temp_t1;
    f64 new_var2;
    f64 temp_fa1;
    f64 temp_fv0;
    f64 temp_ft5;

    temp_t0 = arg0->v[4];
    new_var = arg0->v;
    temp_a3 = new_var[8];
    temp_a1 = arg0->v[7];
    temp_v1 = arg0->v[5];
    temp_a2 = new_var[1];
    temp_v0 = new_var[2];
    temp_fa0 = (f64) temp_t0;
    temp_fv0 = (f64) temp_a1;
    temp_t3 = new_var[6];
    temp_t2 = new_var[3];
    temp_t1 = arg0->v[0];
    temp_fv1 = (f64) temp_a2;
    temp_fa1 = (f64) temp_a3;
    arg0->a = (f64) (((f64) (temp_v0 - temp_v1) * temp_fv0) + ((temp_fv1 * (f64) (temp_v1 - temp_a3)) + (temp_fa0 * (f64) (temp_a3 - temp_v0))));
    temp_ft5 = (f64) temp_v1;
    temp_ft4 = (f64) temp_v0;
    temp_fs0 = (f64) temp_t3;
    arg0->b = (f64) (((f64) (temp_t1 - temp_t2) * temp_fa1) + ((temp_ft4 * (f64) (temp_t2 - temp_t3)) + (temp_ft5 * (f64) (temp_t3 - temp_t1))));
    new_var2 = temp_fs0;
    temp_fs2 = (f64) temp_t2;
    temp_fs1 = (f64) temp_t1;
    arg0->c = (f64) (((f64) (temp_a2 - temp_t0) * new_var2) + ((temp_fs1 * (f64) (temp_t0 - temp_a1)) + (temp_fs2 * (f64) (temp_a1 - temp_a2))));
    arg0->d = (f64) -((((temp_fv1 * temp_ft5) - (temp_ft4 * temp_fa0)) * new_var2) + ((temp_fs1 * ((temp_fa0 * temp_fa1) - (temp_fv0 * temp_ft5))) + (temp_fs2 * ((temp_fv0 * temp_ft4) - (temp_fv1 * temp_fa1)))));
}

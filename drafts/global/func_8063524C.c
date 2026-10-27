// func_8063524C (src/global/36880.c): stage 4: frame 0x30 and sp slots match (locals out,q,data,i,j,sum), insn count close; diff regalloc/scheduling: target keeps vertex offset v0=(t0+a2)<<4 un-strength-reduced for x/y/z/s stores and uses IV a3 only for the two .t stores (unkA/unk1A via (unk1C+i*4)[j].t form gives that but moves out to a2); out must be a1, q t3, i t4, sum t1, k a2. Also prologue order (mtc1/lw). Permuter 3314->2320 only.
void *func_80610FE8(s32);

typedef struct R36880bVtx {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 z;
    /* 0x06 */ s16 pad6;
    /* 0x08 */ s16 s;
    /* 0x0A */ s16 t;
    /* 0x0C */ u8 pad[4];
} R36880bVtx;

typedef struct R36880bQuad {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ s16 x[4];
    /* 0x0C */ s16 y[4];
    /* 0x14 */ s16 z[4];
    /* 0x1C */ s16 uv[4][2];
    /* 0x2C */ u8 rgba[4];
} R36880bQuad;

typedef struct R36880bOut {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ u8 pad14[8];
    /* 0x1C */ R36880bVtx *unk1C;
    /* 0x20 */ u8 unk20;
    /* 0x21 */ u8 pad21[0x23];
    /* 0x44 */ u8 rgba[4];
    /* 0x48 */ s16 unk48;
} R36880bOut;

typedef struct R36880bParent {
    /* 0x00 */ u8 pad0[0x20];
    /* 0x20 */ R36880bOut *unk20;
    /* 0x24 */ u8 *unk24;
} R36880bParent;

void func_8063524C(R36880bParent *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8) {
    R36880bOut *out;
    R36880bQuad *q;
    u8 *data;
    s32 i;
    s32 j;
    s16 sum;

    data = arg0->unk24;
    out = arg0->unk20;
    out->unk0 = arg1;
    out->unk4 = arg2;
    q = (R36880bQuad *)(*(s32 *)(data + 0x70) + (s32)data + 4);
    out->unk8 = arg3;
    out->unkC = arg7;
    out->unk10 = arg8;
    out->unk20 = *(s32 *)(*(s32 *)(data + 0x70) + (s32)data);
    sum = 0;
    out->unk1C = func_80610FE8(out->unk20 << 6);
    for (i = 0; i < out->unk20; i++) {
        out->rgba[0] = q->rgba[0];
        out->rgba[1] = q->rgba[1];
        out->rgba[2] = q->rgba[2];
        out->rgba[3] = q->rgba[3];
        for (j = 0; j != 4; j += 2) {
            out->unk1C[i * 4 + j].x = q->x[j];
            out->unk1C[i * 4 + j].y = q->y[j];
            out->unk1C[i * 4 + j].z = q->z[j];
            out->unk1C[i * 4 + j].s = q->uv[j][0];
            out->unk1C[i * 4 + j].t = q->uv[j][1];
            sum += q->y[j];
            out->unk1C[i * 4 + j + 1].x = q->x[j + 1];
            out->unk1C[i * 4 + j + 1].y = q->y[j + 1];
            out->unk1C[i * 4 + j + 1].z = q->z[j + 1];
            out->unk1C[i * 4 + j + 1].s = q->uv[j + 1][0];
            out->unk1C[i * 4 + j + 1].t = q->uv[j + 1][1];
            sum += q->y[j + 1];
        }
        q++;
    }
    out->unk48 = sum / (out->unk20 * 4);
}

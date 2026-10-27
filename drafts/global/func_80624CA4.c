// func_80624CA4 (src/global/201B0.c): stage 5: same size/frame/callee set. Remaining diff: s32 float->int temp in case 3/11 is mfc1 v0 in target, t0 in mine (shifts later ugen t regs by one); FP temp regs f4/f18 swapped in k-block/base blends; k + (1.0-k)*cnt/30 mul/add operand order flipped
// func_80624CA4: stage 5; see note
typedef struct CamB2XState {
    /* 0x000 */ u8 pad0[0x1F0];
    /* 0x1F0 */ s32 unk1F0;
} CamB2XState;

typedef struct CamB2Player {
    /* 0x00 */ u8 pad0[0x58];
    /* 0x58 */ s32 unk58;
    /* 0x5C */ u8 pad5C[0xE];
    /* 0x6A */ u16 unk6A;
    /* 0x6C */ u8 pad6C[0x10];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ u8 pad80[4];
    /* 0x84 */ f32 unk84;
    /* 0x88 */ u8 pad88[0x30];
    /* 0xB8 */ f32 unkB8;
    /* 0xBC */ u8 padBC[0x54];
    /* 0x110 */ u8 unk110;
    /* 0x111 */ u8 pad111[0x43];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 pad155[0x1F];
    /* 0x174 */ struct CamB2Cam *unk174;
} CamB2Player;

typedef struct CamB2Cam {
    /* 0x00 */ CamB2Player *unk0;
    /* 0x04 */ u8 pad4[0xC];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ u8 pad12[0x32];
    /* 0x44 */ CamBTarget unk44;
    /* 0x60 */ u8 pad60[0x24];
    /* 0x84 */ f32 unk84;
    /* 0x88 */ u8 pad88[4];
    /* 0x8C */ f32 unk8C;
    /* 0x90 */ u8 pad90[0x1C];
    /* 0xAC */ s32 unkAC;
    /* 0xB0 */ s16 unkB0;
    /* 0xB2 */ u8 padB2[0x36];
    /* 0xE8 */ s16 unkE8;
    /* 0xEA */ s16 unkEA;
    /* 0xEC */ u8 padEC[5];
    /* 0xF1 */ u8 unkF1;
    /* 0xF2 */ u8 padF2;
    /* 0xF3 */ u8 unkF3;
    /* 0xF4 */ u8 padF4[2];
    /* 0xF6 */ u8 unkF6;
    /* 0xF7 */ u8 unkF7;
    /* 0xF8 */ u8 unkF8;
} CamB2Cam;

struct CamE2Player;

void func_80624CA4(struct CamE2Player *arg0) {
    CamB2Cam *st = ((CamB2Player *)arg0)->unk174;
    CamB2Player *X = st->unk0;
    CamB2XState *xs = (CamB2XState *)X->unk174;
    CamBTarget *tgt = &st->unk44;
    f32 scale;
    f32 k;
    f32 base;
    s32 dist;
    f64 m;
    f64 m2;
    f32 dz;
    f32 dx;

    switch (st->unkF3) {
        case 6:
        case 9:
            D_807476A0 = 1.0f;
            D_807476A4 = 1.0f;
            break;
        case 4:
        case 8:
            D_807476A0 = tgt->unk18;
            D_807476A4 = tgt->unk18;
            break;
        case 3:
        case 11:
            if (X->unk110 == 1) {
                dz = X->unk84 - st->unk8C;
                dx = X->unk7C - st->unk84;
                dist = dz * dz + dx * dx;
                m = dist * 0.001;
                m2 = (m > 1.0) ? 1.0 : m;
                D_807476A0 = m2 * -0.8 + 1.0;
            } else {
                D_807476A0 = 0.2f;
            }
            D_807476A4 = 0.3f;
            break;
        case 2:
            D_807476A0 = 0.3f;
            if (X->unk154 == 0x62) {
                D_807476A4 = 0.05f;
            } else if (!(st->unkAC & 0x80)) {
                D_807476A4 = 0.3f;
            }
            break;
        case 1:
            if (st->unkB0 != 0 || st->unkF1 != 0 || D_8076A0A8 == 0x27 || st->unkF6 != 0) {
                D_807476A0 = 0.3f;
                D_807476A4 = 0.3f;
            } else if (st->unkF7 != 0) {
                D_807476A0 = 0.2f;
                D_807476A4 = 0.2f;
            } else if ((st->unkAC & 4) || X->unk58 == 8) {
                D_807476A0 = 0.1f;
                D_807476A4 = 0.2f;
            } else if (X->unk154 == 0x22) {
                D_807476A0 = 0.4f;
                D_807476A4 = 0.2f;
            } else if (X->unk154 == 0xE || X->unk154 == 0x59) {
                D_807476A0 = 0.1f;
                D_807476A4 = 0.08f;
            } else {
                base = 0.03f;
                if (((CamB2Player *)arg0)->unkB8 != 0.0f) {
                    k = st->unk10 / ((CamB2Player *)arg0)->unkB8;
                } else {
                    k = 0.0f;
                }
                k = (k / 20.0 > 1.0) ? 1.0 : k / 20.0;
                if (st->unkF8 != 0) {
                    k = ((u32)(--st->unkF8) / 30.0) * (1.0 - k) + k;
                }
                if ((xs->unk1F0 << 8) < 0 || X->unk154 == 0x1E || X->unk154 == 0x1C || X->unk154 == 0x20 || X->unk154 == 0x1B || X->unk154 == 0x1A || X->unk154 == 0x6E || X->unk154 == 0x3E) {
                    if (!(X->unk6A & 1)) {
                        base = 0.3f;
                    }
                }
                D_807476A0 = base + (0.6 - base) * k;
                D_807476A4 = base + (0.4 - base) * k;
            }
            break;
        case 7:
            D_807476A0 = 0.05f;
            D_807476A4 = 0.05f;
            break;
        case 5:
            D_807476A0 = 0.2f;
            D_807476A4 = 0.2f;
            break;
        case 10:
            D_807476A0 = 0.3f;
            D_807476A4 = 0.3f;
            break;
        case 12:
            D_807476A0 = 0.6f;
            D_807476A4 = 0.6f;
            break;
        case 13:
            D_807476A0 = 0.2f;
            D_807476A4 = 0.2f;
            break;
    }
    if (st->unkE8 != 0) {
        switch (st->unkF3) {
            case 3:
            case 6:
            case 7:
            case 8:
            case 9:
            case 11:
                scale = 1.0f;
                break;
            case 1:
            case 4:
            case 5:
            case 10:
            case 12:
            case 13:
                scale = func_80612794((s16)((1.0 - (f32)st->unkE8 / (f32)st->unkEA) * 1024.0)) * 0.8 + 0.2;
                break;
            case 2:
                scale = func_80612794((s16)((1.0 - (f32)st->unkE8 / (f32)st->unkEA) * 1024.0)) * 0.9 + 0.1;
                break;
        }
        st->unkE8--;
        D_807476A0 *= scale;
        D_807476A4 *= scale;
    }
}

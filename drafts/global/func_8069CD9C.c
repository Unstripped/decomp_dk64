// func_8069CD9C (src/global/9DD70.c): stage 6: identical size/blocks; only FP scheduling+reg rotation of the dx/dz/dy distance block (sub order dx,dy,dz vs target dx,dz,dy) and one rodata %lo addend; identify 3-string truncated-float 'dist' block
extern Actor *D_807FBB40;
void func_8069B908(void);

typedef struct M2_CamState {
    u8 pad0[0x210];
    f32 unk210;
    f32 unk214;
    f32 unk218;
} M2_CamState;

extern M2_CamState *D_807FC924;

void func_8069CD9C(void) {
    f32 frac;
    f32 dx;
    f32 dz;
    f32 dy;
    f32 dist;
    u32 val;

    if (!(D_807FBB40->unk60 & 0x10)) {
        frac = D_807FBB40->unk4->unk34 / 0.15;
        frac = frac - 1.0;
        if (frac < 0.0) {
            frac = 0.0f;
        }
        val = (u32)(80.0f * frac);
        D_807FBB40->unk12C[4] = val;
        D_807FBB40->unk12C[5] = val;
        D_807FBB40->unk12A = 0x2BC;
    }
    dx = D_807FBB40->unk7C - D_807FC924->unk210;
    dz = D_807FBB40->unk84 - D_807FC924->unk218;
    dy = D_807FBB40->unk80 - D_807FC924->unk214;
    dist = dx * dx + dy * dy;
    if (dz * dz + dist < 18000.0) {
        D_807FBB40->unk60 |= 0x400;
    } else {
        D_807FBB40->unk60 &= ~0x400;
    }
    func_8069B908();
}

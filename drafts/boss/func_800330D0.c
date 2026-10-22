// func_800330D0 (src/boss/F0D0.c): from .scratch/Boss3D/func_800330D0_best.c
typedef struct {
    u8 pad0[0x14];
    u8 unk14;
    u8 unk15;
    u8 unk16;
} BossE_F0D0_Sub14;

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    u8 pad6[4];
} BossE_F0D0_FDCA0_Sub;

typedef struct {
    u8 pad0[0x14];
    BossE_F0D0_FDCA0_Sub *unk14;
} BossE_F0D0_FDCA0;

extern BossE_F0D0_Actor *D_807FBB40;
extern BossE_F0D0_Actor *D_807FBB4C;
extern BossE_F0D0_FDCA0 *D_807FDCA0;
extern s32 D_80035B80;
s32 func_80611A44(void);

u8 func_800330D0(BossE_F0D0_Sub14 *arg0, u8 *arg1) {
    s32 min_dist;
    s32 dists[16];
    s32 dist;
    u8 i;
    s8 diff_row;
    s8 diff_col;
    u8 val;
    u8 start_val;

    val = arg1[0];
    min_dist = 0x98967F;
    i = 0;
    start_val = val;
    do {
        dist = (s32)(((f32)D_807FDCA0->unk14[i].unk4 - D_807FBB4C->unk84) * ((f32)D_807FDCA0->unk14[i].unk4 - D_807FBB4C->unk84) +
                     ((f32)D_807FDCA0->unk14[i].unk0 - D_807FBB4C->unk7C) * ((f32)D_807FDCA0->unk14[i].unk0 - D_807FBB4C->unk7C));
        dists[i] = dist;
        if (dist < min_dist) {
            arg1[3] = i;
            min_dist = dist;
        }
        i++;
    } while (i < 16);

    if (D_807FBB4C->unk80 < D_807FBB40->unk80 - 10.0f) {
        s32 center_nodes = D_80035B80;
        return ((u8 *)&center_nodes)[(func_80611A44() >> 15) % 4];
    }

    diff_row = (s8)((s32)arg1[0] / 4 - (s32)arg1[3] / 4);
    diff_col = (s8)((s32)arg1[0] % 4 - (s32)arg1[3] % 4);

    if (diff_row > 0) {
        val -= 4;
    } else if (diff_row < 0) {
        val += 4;
    } else if (diff_col > 0) {
        val -= 1;
    } else if (diff_col < 0) {
        val += 1;
    }

    if (val != start_val) {
        if (arg0->unk14 < 3) {
            return val;
        }
        if (arg1[2] == val) {
            return val;
        }
    }

    if (dists[(start_val - 1) & 0xFF] < dists[(start_val + 1) & 0xFF] && (start_val & 3) != 0) {
        start_val -= 1;
    } else if (dists[(start_val + 1) & 0xFF] < dists[(start_val - 1) & 0xFF] && (start_val & 3) != 3) {
        start_val += 1;
    }

    if (dists[(start_val - 4) & 0xFF] < dists[(start_val + 4) & 0xFF] && start_val >= 4) {
        start_val -= 4;
    } else if (dists[(start_val + 4) & 0xFF] < dists[(start_val - 4) & 0xFF] && start_val < 12) {
        start_val += 4;
    }

    return start_val;
}

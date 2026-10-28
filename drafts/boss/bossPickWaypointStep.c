// bossPickWaypointStep (src/boss/F0D0.c): stage 6: text identical except operand order of ONE beq (beq t7,t2 expected vs beq t2,t7: arg1[2]==val compare in guard); parked NON_MATCHING in BsB copy; early return unk14>=3, 'if (val==arg1[2]||val==start_val){...}', dists idx &0xF, start_val--/++, u8 center[4]={5,6,9,10}, for loop, x-first sum
typedef struct {
    u8 pad0[0x14];
    u8 unk14;
} BossE_F0D0_Sub14;
// (also needs the file's BossE_F0D0_Actor / FDCA0 structs, D_807FBB40/4C/DCA0 externs and randomNonNegative)

u8 bossPickWaypointStep(BossE_F0D0_Sub14 *arg0, u8 *arg1) {
    s32 min_dist;
    s32 dists[16];
    u8 i;
    s8 diff_row;
    s8 diff_col;
    u8 val;
    u8 start_val;

    val = arg1[0];
    min_dist = 0x98967F;
    start_val = val;
    for (i = 0; i < 16; i++) {
        dists[i] = (s32)(((f32)D_807FDCA0->unk14[i].unk0 - D_807FBB4C->unk7C) * ((f32)D_807FDCA0->unk14[i].unk0 - D_807FBB4C->unk7C) + ((f32)D_807FDCA0->unk14[i].unk4 - D_807FBB4C->unk84) * ((f32)D_807FDCA0->unk14[i].unk4 - D_807FBB4C->unk84));
        if (dists[i] < min_dist) {
            min_dist = dists[i];
            arg1[3] = i;
        }
    }

    if (D_807FBB4C->unk80 < D_807FBB40->unk80 - 10.0f) {
        u8 center[4] = {5, 6, 9, 10};
        return center[(randomNonNegative() >> 15) % 4];
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

    if (arg0->unk14 >= 3) {
        return val;
    }
    if (val == arg1[2] || val == start_val) {
        if (diff_row != 0 || val == start_val) {
            if (dists[(start_val - 1) & 0xF] < dists[(start_val + 1) & 0xF] && (start_val & 3) != 0) {
                start_val--;
            } else if (dists[(start_val + 1) & 0xF] < dists[(start_val - 1) & 0xF] && (start_val & 3) != 3) {
                start_val++;
            }
        }

        if ((diff_row == 0 && diff_col != 0) || val == start_val) {
            if (dists[(start_val - 4) & 0xF] < dists[(start_val + 4) & 0xF] && start_val >= 4) {
                return start_val - 4;
            } else if (dists[(start_val + 4) & 0xF] < dists[(start_val - 4) & 0xF] && start_val < 12) {
                start_val += 4;
            }
        }

        return start_val;
    }
    return val;
}

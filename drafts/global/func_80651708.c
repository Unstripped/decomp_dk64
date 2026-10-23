// func_80651708 (src/global/55B20.c): stage 6: frame 0x20 and spill slots 0x18/0x1c now match target; remaining diff is pure register rotation in the copy loop (target temp_lo=a0, var_a1_2=a1, const6=t0, dst-addr=t1; mine a1/a0/t1) and lh a0,4(v1) vs lh t0,4(v1). Key: no var_a0 variable (use var_v1->unk4 directly) and no temp_t3 local - that is what drops the frame from 0x28 to 0x20.
typedef struct R2P1bCellEntry {
    /* 0x00 */ u8 *unk0;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ u8 pad6[0x2];
    /* 0x08 */ u8 *unk8;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ u8 padE[0x2];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
} R2P1bCellEntry;

extern R2P1bCellEntry *D_807F70B8[];
void heapFree(void *);

void func_80651708(s32 arg0) {
    R2P1bCellEntry *var_v1;
    s32 var_a1;
    s32 var_a2;
    s32 var_a3;
    s32 var_v0;
    s32 temp_lo;
    s32 var_a1_2;
    u8 *var_a0_2;

    var_v1 = D_807F70B8[arg0];
    if (var_v1->unk8 != 0) {
        heapFree(var_v1->unk8);
    }
    var_a1 = var_v1->unk4 - 2;
    if (var_a1 < 0) {
        var_a1 = 0;
    }
    if (var_a1 != 0) {
        var_v1->unk8 = func_80610FE8(var_a1 * 0x12);
        var_v1->unkC = var_a1;
        if (var_v1->unk4 >= 3) {
            var_a3 = 1;
            var_a2 = 2;
            var_v0 = 0x24;
            var_a1_2 = 0xC;
            do {
                temp_lo = var_a3 * 6;
                var_a3 = var_a2;
                *(s16 *)(var_v1->unk8 + var_v0 - 0x24) = *(s16 *)(var_v1->unk0 + 0);
                var_a2 += 1;
                *(s16 *)(var_v1->unk8 + var_v0 - 0x1E) = *(s16 *)(var_v1->unk0 + 2);
                *(s16 *)(var_v1->unk8 + var_v0 - 0x18) = *(s16 *)(var_v1->unk0 + 4);
                *(s16 *)(var_v1->unk8 + var_v0 - 0x22) = *(s16 *)(var_v1->unk0 + temp_lo);
                *(s16 *)(var_v1->unk8 + var_v0 - 0x1C) = *(s16 *)(var_v1->unk0 + temp_lo + 2);
                *(s16 *)(var_v1->unk8 + var_v0 - 0x16) = *(s16 *)(var_v1->unk0 + temp_lo + 4);
                *(s16 *)(var_v1->unk8 + var_v0 - 0x20) = *(s16 *)(var_v1->unk0 + var_a1_2);
                *(s16 *)(var_v1->unk8 + var_v0 - 0x1A) = *(s16 *)(var_v1->unk0 + var_a1_2 + 2);
                var_v0 += 0x12;
                *(s16 *)((var_v1->unk8 + var_v0) - 0x14) = *(s16 *)(var_v1->unk0 + var_a1_2 + 4);
                var_a1_2 += 6;
            } while (var_a2 < var_v1->unk4);
        }
    }
    var_v1->unk12 = -0x8000;
    var_v1->unk10 = 0x7FFF;
    var_a2 = 0;
    if (var_v1->unk4 > 0) {
        var_a0_2 = var_v1->unk0;
        do {
            if (var_v1->unk12 < *(s16 *)(var_a0_2 + 2)) {
                var_v1->unk12 = *(s16 *)(var_a0_2 + 2);
            }
            if (*(s16 *)(var_a0_2 + 2) < var_v1->unk10) {
                var_v1->unk10 = *(s16 *)(var_a0_2 + 2);
            }
            var_a2 += 1;
            var_a0_2 += 6;
        } while (var_a2 < var_v1->unk4);
    }
}

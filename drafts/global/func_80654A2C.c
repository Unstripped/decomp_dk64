// func_80654A2C (src/global/55B20.c): stage6: whole function identical except one insn: target 'addiu s1,s2,0x36' (&trig->unk36) vs built 'addiu s1,v1,0x36' (same value, other copy); key fix found: zero loop must be D_807F70B0[j].unk18 form (j*0x1C), not an accumulated off; 'found = 1' goes after the inner if
typedef struct M55P4Cell {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    u8 pad6[0x12];
    u8 unk18;
    u8 unk19;
    u8 pad1A[2];
} M55P4Cell;

typedef struct M55P4Trigger {
    s16 unk0[10];
    s16 unk14[16];
    u8 unk34;
    s16 unk36[16];
    u8 unk56;
} M55P4Trigger;

extern s32 D_807F70AC;
extern s32 D_807F70B0;
extern void *D_807F70B8[];
extern u8 D_807F7048[];
extern u8 D_807F7058;

void func_80654BC0(s32, u8);

void func_80654A2C(f32 arg0, f32 arg1, f32 arg2) {
    s32 i;
    s32 j;
    s32 off;
    s32 done;
    s16 *val;
    M55P4Trigger *trig;
    u8 idx;

    done = 0;
    i = 0;
    while (i < D_807F7058) {
        idx = D_807F7048[i];
        if (D_807F70B8[idx] != 0) {
            trig = (M55P4Trigger *)D_807F70B8[idx];
            if (!done) {
                if (trig->unk56 != 0) {
                    done = 1;
                    val = trig->unk36;
                    for (j = 0; j < D_807F70AC; j++) {
                        *((u8 *)D_807F70B0 + j * 0x1C + 0x18) = 0;
                    }
                    for (j = 0; j < trig->unk56; j++) {
                        func_80654BC0(*val, 1);
                        val++;
                    }
                } else {
                    val = trig->unk14;
                    for (j = 0; j < trig->unk34; j++) {
                        func_80654BC0(*val, 0);
                        val++;
                    }
                }
            }
        }
        i++;
    }
}

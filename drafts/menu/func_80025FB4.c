// func_80025FB4 (src/menu/1AF0.c): NON_MATCHING parked, stage 6. Same frame/callee-saved set; only ugen temp-reg numbering in the 2/4 case block (lh t4 vs t6 ...) and 1 operand order remain (addu a1,v1,a2 fixed with direct tbl[i] indexing). Tried: e ptr vs tbl[i], t var, switch/if, unused locals, line joins, permuter 420s.
extern u16 D_80750AC8;
extern u8 D_807FCC4C;
typedef struct {
    char pad0[4];
    s16 unk4;
    char pad6[5];
    s8 unkB;
    u8 unkC;
    char padD[3];
    u8 unk10;
    s8 unk11;
} MenuM1_State;
typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
} MenuM1_Entry;
extern MenuM1_Entry D_80033260[][7];
extern MenuM1_Entry D_80033334[][7];
extern MenuM1_Entry D_80033408[][7];
extern u8 D_8076A0AB;
s32 func_805FF030(s32, s32);

#define M1S ((MenuM1_State *)arg0)
#define M1A ((u8 *)arg1)
void func_80025FB4(void *arg0, void *arg1, s32 arg2) {
    MenuM1_Entry *tbl;
    MenuM1_Entry *e;
    s32 found = 0;
    s32 count = 6;
    s32 i;

    if (flagGet(0x1CB, 0) == 0) {
        do {
            count--;
            if (count < 0) {
                break;
            }
        } while (flagGet(count + 0x1C5, 0) == 0);
    }
    count++;
    M1S->unkC = func_805FF030(D_8076A0AB, 0);
    switch (D_807FBB40->unk58) {
    case 0xBD:
        tbl = D_80033260[0];
        break;
    case 0xBF:
        tbl = D_80033334[0];
        break;
    case 0xBE:
        tbl = D_80033408[0];
        break;
    }
    tbl += D_8074E77C * 7;
    for (i = 0; i < count && found == 0; i++) {
        if (tbl[i].unk0 >= 0) {
            switch (tbl[i].unk0) {
            case 2:
            case 4:
                if (!((1 << (tbl[i].unk2 + 0x1F)) & M1A[tbl[i].unk0])) {
                    found = 1;
                }
                break;
            default:
                if (M1A[tbl[i].unk0] < tbl[i].unk2) {
                    found = 1;
                }
                break;
            }
            if (found != 0) {
                M1S->unkB = tbl[i].unk0;
                D_80750AC8 = (M1S->unk4 = tbl[i].unk4);
                M1S->unk11 = tbl[i].unk2;
            }
        }
    }
    if (found == 0) {
        M1S->unk4 = 0;
        M1S->unkB = -1;
        D_80750AC8 = M1S->unk4;
        if (count >= 7) {
            M1S->unkB = -2;
        }
    }
    M1S->unk10 = D_807FCC4C;
}

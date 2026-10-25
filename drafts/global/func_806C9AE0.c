// func_806C9AE0 (src/global/CC800.c): G01 stage 6 near-miss: andi a0 hoisted by uopt; sb not copied into likely delay slots
typedef struct G01Ent {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ u8 unk2;
    /* 0x03 */ u8 pad3[0x5B];
} G01Ent;

typedef struct G01Slot {
    /* 0x000 */ G01Ent ent[6];
    /* 0x234 */ u8 pad234[0xC7];
    /* 0x2FB */ s8 unk2FB;
    /* 0x2FC */ u8 unk2FC;
    /* 0x2FD */ s8 unk2FD;
    /* 0x2FE */ u8 pad2FE[8];
} G01Slot;

extern u8 D_807FC950[][0x5E];
extern u8 D_80750AC0;
extern s32 D_807552E4;
extern s8 D_80750ACC;
extern s32 D_807FD56C;
void func_80709464(u8);
void func_806C7B00();

/* stage 6: only difference is the join block: target keeps `andi a0,s4,0xff` in the jal delay slot and copies
 * `sb s0,0x2FC(s2)` into the branch-likely delay slots of the preceding branches; ours hoists the andi to the loop head
 * (uopt code motion) so the sb ends in the jal delay slot and the branches get nop. Unrolled j loops (6 iterations) match. */
void func_806C9AE0(void) {
    G01Slot *p = (G01Slot *)D_807FC950;
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        bzero(p, 0x306);
        if (D_80750AC0 >= 2) {
            if (D_807552E4 == 1) {
                for (j = 0; j < 6; j++) {
                    p->ent[j].unk2 = 7;
                }
            }
            for (j = 0; j < 6; j++) {
                p->ent[j].unk1 = 1;
            }
        }
        p->unk2FC = 1;
        func_80709464(i);
        p++;
    }
    func_806C7B00();
    D_80750ACC = 0;
    D_807FD56C = 0;
}

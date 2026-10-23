// func_806547A8 (src/global/55B20.c): stage4: frame 0x60 vs 0x88, fewer spills/callee-saved regs (target spills &D_807F70B8 and keeps zone in s0+copies to v0); behaviourally equivalent draft
typedef struct M55P4Tri {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    s16 unk10;
} M55P4Tri;

typedef struct M55P4Zone {
    u8 pad0[8];
    s32 unk8;
    s16 unkC;
    s16 unkE;
    s16 unk10;
    s16 unk12;
    u8 pad14[0x44];
    s16 unk58[8];
    u8 unk68;
} M55P4Zone;

extern s32 D_807F70AC;
extern u8 D_807F7048[];
extern u8 D_807F7058;
extern M55P4Zone *D_807F70B8[];
extern u8 D_807F7060[];
extern u8 D_807F7070;

f32 func_80654CCC(M55P4Tri *, f32, f32);
s32 func_80654E84(M55P4Tri *, f32, f32);
s32 func_80654FEC(M55P4Tri *, f32, f32);

void func_806547A8(f32 arg0, f32 arg1, f32 arg2) {
    M55P4Zone **p;
    M55P4Zone *zone;
    M55P4Tri *node;
    s32 i;
    s32 j;
    s32 k;
    s32 n;
    s32 found;
    u8 *q;
    f32 h;

    D_807F7058 = 0;
    D_807F7070 = 0;
    p = D_807F70B8;
    for (i = 0; i != 0x20; i++) {
        zone = *p;
        if (zone != NULL && (f32)zone->unk10 <= arg1 && arg1 <= (f32)(zone->unk12 + zone->unkE)) {
            node = (M55P4Tri *)((u8 *)zone->unk8);
            for (j = 0; j < zone->unkC; j++, node++) {
                if (func_80654E84(node, arg0, arg2) != 0 && func_80654FEC(node, arg0, arg2) != 0) {
                    h = func_80654CCC(node, arg0, arg2);
                    if (h <= arg1 && arg1 <= (f32)zone->unkE + h) {
                        k = 0;
                        if (D_807F7058 != 0x10) {
                            D_807F7048[D_807F7058] = i;
                            D_807F7058++;
                        }
                        for (; k < zone->unk68; k++) {
                            found = 0;
                            n = 0;
                            q = D_807F7060;
                            while (!found && n < D_807F7070) {
                                if (*q == zone->unk58[k]) {
                                    found = 1;
                                } else {
                                    n++;
                                    q++;
                                }
                            }
                            if (!found && n != 0x10) {
                                D_807F7060[D_807F7070] = zone->unk58[k];
                                D_807F7070++;
                            }
                        }
                    }
                }
            }
        }
        p++;
    }
}

// func_80026C9C (src/critter/0.c): stage 5 (score 2133): frame/loop shape OK; diff = s-reg assignment (target arg0=s5,tbl=s3,const0x18=s4; ours const=s3,arg0=s4,tbl=s5; uopt adjsave tbl 3.67 < const 5 < ...) and target hoists lbu D_8074E77C into beqz delay slot, computes tbl first. s16 idx, 20-byte struct copy via C0cBlk5 matches the lw at/sw pairs. Local decl order irrelevant (all 120 perms 2133). Param must be void* (decl func_80026C9C(void*)) in the parked build.
extern u8 D_8074E77C;
extern u8 D_80029BAC[];
void critterDispatchAll(u8 *);
typedef struct {
    s32 w[5];
} C0cBlk5;

void func_80026C9C(u8 *arg0) {
    s32 i;
    u8 *p;
    u8 *tbl;
    u8 *e;
    s16 idx;

    if (arg0 != NULL) {
        p = *(u8 **)(arg0 + 4);
        *(s16 *)D_80029BA4 = (s16)(s32) * (f32 *)(D_807FBB48 + 0x7C);
        tbl = D_80029BAC + D_8074E77C * 0x78;
        i = 0;
        *(s16 *)((u8 *)D_80029BA4 + 4) = (s16)(s32) * (f32 *)(D_807FBB48 + 0x84);
        if ((s32)arg0[0] > 0) {
            do {
                idx = *p;
                if (idx > 0) {
                    idx = idx - 1;
                }
                e = tbl + idx * 0x18;
                *(s16 *)((u8 *)D_80029BA4 + 2) = (s16)(s32)(*(f32 *)(D_807FBB48 + 0x80) + (f32) * (s16 *)(e + 0x14));
                *(C0cBlk5 *)((u8 *)D_80029BA4 + 8) = *(C0cBlk5 *)e;
                critterDispatchAll(p);
                i++;
                p += 0xC;
            } while (i < (s32)arg0[0]);
        }
    }
}

// func_8063B4C0 (src/global/36880.c): stage 3: frame -0x38 vs target -0x58: target allocs $ra to 'allow' and spills idx(sh v0,0x46)/tbl-CSE(sw 0x34)/obj(0x54); mine gives ra to idx. loop matches with u8 i, i++ before use, switch order 2,0,4,3/6,5. Decl-order shuffles (40) no help.
typedef struct R36880fSrc {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ u8 pad10[0xE];
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ u8 pad20[4];
    /* 0x24 */ u8 unk24;
} R36880fSrc;

typedef struct R36880fEntry {
    /* 0x0 */ s16 id;
    /* 0x2 */ s16 key;
    /* 0x4 */ u8 done;
    /* 0x5 */ u8 pad5;
} R36880fEntry;

extern u8 D_80750AB4;
extern u8 D_807F7140;
extern R36880fEntry D_807F6030[];
extern s16 D_807F60B0[];
void func_8063E078(s32);
void func_8063E0D4(s32, s16);

void func_8063B4C0(R36880fSrc *arg0, u8 arg1) {
    u8 *obj;
    u8 allow;
    s32 pad1;
    s32 pad2;
    s16 idx;
    s32 pad3;
    s32 pad4;
    s32 pad5;
    u8 i;
    R36880fEntry *e;
    u8 *p;
    u8 flag;
    f32 *px;
    f32 *py;
    f32 *pz;
    f32 best;

    if (arg0->unk24 == 1) {
        allow = 1;
        idx = hashTableLookup(arg0->unk1E);
        obj = ((ModelSlot *)((u8 *)D_807F6000 + idx * 0x90))->unk7C;
        if (obj != NULL) {
            switch (obj[0x54]) {
            case 2:
                allow = 0;
                break;
            case 0:
                allow = arg1;
                break;
            case 4:
                allow = arg1;
            case 3:
            case 6:
                best = 1e8f;
                for (i = 0; i < D_80750AB4;) {
                    p = (u8 *)D_807FC924 + i * 0x2F0;
                    i++;
                    if (*p != 0) {
                        if (obj[0x54] == 6) {
                            px = (f32 *)(*(u8 **)(p + 4) + 0x7C);
                            py = (f32 *)(*(u8 **)(p + 4) + 0x80);
                            pz = (f32 *)(*(u8 **)(p + 4) + 0x84);
                        } else {
                            px = (f32 *)(p + 0x21C);
                            py = (f32 *)(p + 0x220);
                            pz = (f32 *)(p + 0x224);
                        }
                        if ((*pz - arg0->unkC) * (*pz - arg0->unkC) + ((*px - arg0->unk4) * (*px - arg0->unk4) + (*py - arg0->unk8) * (*py - arg0->unk8)) < best) {
                            best = (*pz - arg0->unkC) * (*pz - arg0->unkC) + ((*px - arg0->unk4) * (*px - arg0->unk4) + (*py - arg0->unk8) * (*py - arg0->unk8));
                        }
                    }
                }
                flag = 0;
                if (best < (f32)*(s32 *)(obj + 0x58)) {
                    flag = 1;
                }
                allow = allow & flag;
                break;
            case 5:
                if (D_807F6028 == 0x14) {
                    return;
                }
                allow = 0;
                e = &D_807F6030[D_807F6028];
                e->id = arg0->unk1E;
                D_807F6028++;
                e->done = 0;
                e->key = *(s32 *)(obj + 0x58);
                break;
            }
            if (allow != 0) {
                D_807F7140++;
                if (D_807F60A8 != 0x46) {
                    D_807F60B0[D_807F60A8] = *(s16 *)((u8 *)D_807F6000 + idx * 0x90 + 0x8A);
                    D_807F60A8++;
                    func_8063E078((s32)obj);
                    func_8063E0D4((s32)obj, arg0->unk1E);
                }
            }
        }
    }
}

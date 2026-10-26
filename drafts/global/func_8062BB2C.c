// func_8062BB2C (src/global/2F550.c): stage 3-4 (frame 0x30 ok, callee-saved set s0-s5 vs target s0-s4): structure matches (for(;;){if(!a0)return;} then switch(kind){2,1,0} with inner switch(type)). Diff = uopt hoists const 3 into s5 (target keeps li at,3; only s3=1,s4=2), arg0/arg1 regs swapped (arg1 adjsave 25.86 > arg0 25.25 so tree gets s0), list-loop andi a1,s2,0xff vs hoisted andi s3, 'andi t8,s2,0xff;move s2,t8' vs 'move t8,s2;andi s2,t8', one extra andi a2 in type1/2 path. Tried: if-chains, switch, goto top, s32/K&R arg2, local copies, permuter 240s (best 1125 vs 2130, garbage).
typedef struct R2F550bObj {
    struct R2F550bObj *unk0;
    struct R2F550bObj *unk4;
    u8 pad8[0xC];
    struct R2F550bObj *unk14;
    u8 pad18[6];
    s16 unk1E;
    u8 pad20[4];
    u8 unk24;
    u8 pad25[0x93];
    u8 unkB8;
} R2F550bObj;

typedef struct R2F550bTree {
    u8 unk0;
    u8 unk1;
    u8 pad2[2];
    R2F550bObj *unk4;
    s32 unk8;
    struct R2F550bTree *unkC;
    struct R2F550bTree *unk10;
} R2F550bTree;

void func_8062BB2C(R2F550bObj *, R2F550bTree *, u8);

void func_8063B4C0(R2F550bObj *, s32);
void func_80652B04(void);

void func_8062BB2C(R2F550bObj *arg0, R2F550bTree *arg1, u8 arg2) {
    R2F550bObj *next;

    for (;;) {
        if (arg0 == NULL) {
            return;
        }
        if (arg1->unk1 == 3) {
            arg2 = 0;
            func_8062BB2C(arg0->unk0, arg1->unkC, arg2);
            arg0 = arg0->unk4;
            arg1 = arg1->unk10;
            continue;
        }
        switch (arg0->unkB8) {
            case 2:
                func_80652B04();
                return;
            case 1:
                arg0 = arg1->unk4;
                while (arg0 != NULL) {
                    next = arg0->unk14;
                    func_8063B4C0(arg0, arg2 & 0xFF);
                    arg0 = next;
                }
                return;
            case 0:
                switch (arg1->unk1) {
                    case 1:
                    case 2: {
                        u8 t = arg2;
                        arg2 = 0;
                        if (arg1->unk0 != 0) {
                            func_8062BB2C(arg0->unk4, arg1->unk10, t);
                            arg0 = arg0->unk0;
                            arg1 = arg1->unkC;
                        } else {
                            func_8062BB2C(arg0->unk0, arg1->unkC, t);
                            arg0 = arg0->unk4;
                            arg1 = arg1->unk10;
                        }
                        continue;
                    }
                    case 0:
                        if (arg1->unk0 != 0) {
                            func_8062BB2C(arg0->unk0, arg1->unkC, arg2);
                            arg2 = arg2 & 0xFF;
                            arg0 = arg0->unk4;
                            arg1 = arg1->unk10;
                            continue;
                        }
                        func_8062BB2C(arg0->unk4, arg1->unk10, arg2);
                        arg0 = arg0->unk0;
                        arg2 = arg2 & 0xFF;
                        arg1 = arg1->unkC;
                        break;
                    default:
                        return;
                }
                break;
            default:
                return;
        }
    }
}

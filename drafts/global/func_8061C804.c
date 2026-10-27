// func_8061C804 (src/global/201B0.c): stage 5: frame/saved regs/stack slots/prologue match; remaining diff only ugen/uopt regs: expected idx=lh v0, pt=a0 (addu a0,t0,t1 base first), mine idx=t0,pt=v0 (addu v0,t1,t2)
// func_8061C804: stage 5, only uopt candidate/register diff (see note)
typedef struct CamBPlayer {
    /* 0x000 */ u8 pad0[0x210];
    /* 0x210 */ f32 unk210;
    /* 0x214 */ f32 unk214;
    /* 0x218 */ f32 unk218;
    /* 0x21C */ u8 pad21C[0xC];
    /* 0x228 */ f32 unk228;
    /* 0x22C */ f32 unk22C;
    /* 0x230 */ f32 unk230;
    /* 0x234 */ u8 pad234[0xBC];
} CamBPlayer; // size = 0x2F0

typedef struct CamBPt {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ u32 unk4;
    /* 0x08 */ u32 unk8;
    /* 0x0C */ u8 padC[8];
} CamBPt; // size = 0x14

typedef struct CamBList {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ u8 pad2[2];
    /* 0x4 */ s16 *unk4;
    /* 0x8 */ s16 *unk8;
} CamBList; // size = 0xC

typedef struct CamBPathData {
    /* 0x00 */ u8 pad0[0xD0];
    /* 0xD0 */ CamBList *unkD0;
    /* 0xD4 */ u8 padD4[4];
    /* 0xD8 */ CamBPt *unkD8;
} CamBPathData;

#define CAMB_PATH ((CamBPathData *)D_807476FC)

extern void *D_807F5D10;
extern s16 D_807F5D04;
extern s16 D_807F5D06;
extern s16 D_807F5D08;
extern s16 D_807F5D0A;
void func_8061D898(void);
void func_80622B24(CamActor *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, CamActor *);

s16 func_8061C804(s16 arg0) {
    s16 total;
    s16 path;
    s16 i;
    u8 type;
    u8 found;
    s16 count;
    s16 saved;
    s32 first;
    f32 sp94;
    f32 sp90;
    f32 sp8C;
    f32 sp88;
    f32 sp84;
    f32 sp80;
    CamBPt *pt;

    total = 0;
    first = 0;
    path = arg0;
    do {
        found = 0;
        count = CAMB_PATH->unkD0[path].unk0;
        for (i = 0; i < count; i++) {
            pt = &CAMB_PATH->unkD8[CAMB_PATH->unkD0[path].unk4[i]];
            type = pt->unk1;
            switch (type) {
                case 6:
                    break;
                case 0xD:
                    if ((pt->unk4 & 0xFF) == 8) {
                        path = pt->unk8 >> 16;
                        found = 1;
                    }
                    break;
                case 0xE:
                    break;
                default:
                    if (first == 0) {
                        saved = ((CamActor *)D_807F5CE8)->unk168;
                        first = 1;
                        sp94 = ((CamBPlayer *)D_807FC924)->unk210;
                        sp90 = ((CamBPlayer *)D_807FC924)->unk214;
                        sp8C = ((CamBPlayer *)D_807FC924)->unk218;
                        sp88 = ((CamBPlayer *)D_807FC924)->unk228;
                        sp84 = ((CamBPlayer *)D_807FC924)->unk22C;
                        sp80 = ((CamBPlayer *)D_807FC924)->unk230;
                        D_807F5CFC = 1.0f;
                        D_807F5D00 = 0.0f;
                        D_807476F4 = path;
                        D_807F5CF0 = i;
                        func_8061D898();
                        func_80622B24(D_807F5D10, &sp94, &sp90, &sp8C, &sp88, &sp84, &sp80, D_807F5CE8);
                        D_807F5CF0 = 0;
                        D_807476F4 = arg0;
                        D_807F5D04 = sp94;
                        D_807F5D06 = sp90;
                        D_807F5D08 = sp8C;
                        D_807F5D0A = mathAngleBetweenPoints2D(sp88, sp80, sp94, sp8C);
                        D_807F5CF4 |= 0x20;
                        D_807F5CEC = 0;
                        ((CamActor *)D_807F5CE8)->unk168 = saved;
                    }
                    total += CAMB_PATH->unkD0[path].unk8[i];
                    break;
            }
        }
    } while (found);
    return total;
}

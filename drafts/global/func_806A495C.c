// func_806A495C (src/global/A8400.c): stage 4: frame 0x38 vs 0x40 (expected spills the slot pointer across the func_80714CC0 call), s0/s1 assignment swapped
void func_8071495C(void);
void func_80714998(s32);
void func_807149B8(s32);
void func_807149FC(s32);
void func_80714A68(s16, s16, s16, s16);
void *func_80714CC0(void *, f32, f32, f32, f32);
extern void *D_80755390[];

typedef struct M7Model {
    /* 0x000 */ u8 pad0[0x340];
    /* 0x340 */ f32 unk340;
    /* 0x344 */ f32 unk344;
    /* 0x348 */ u8 pad348[0x18];
    /* 0x360 */ f32 unk360;
    /* 0x364 */ u8 pad364[9];
    /* 0x36D */ u8 unk36D;
    /* 0x36E */ u8 pad36E[0x20];
    /* 0x38E */ s16 unk38E;
    /* 0x390 */ s16 unk390;
    /* 0x392 */ s16 unk392;
    /* 0x394 */ s16 unk394;
} M7Model;

typedef struct M7ModelSlot {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u8 unk2;
    /* 0x03 */ u8 pad3;
    /* 0x04 */ M7Model *unk4;
} M7ModelSlot;

typedef struct M7Sprite {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ u8 pad2[1];
    /* 0x03 */ u8 unk3;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ u8 padC[4];
    /* 0x10 */ M7ModelSlot unk10;
} M7Sprite;

typedef struct M7Vector {
    /* 0x00 */ u8 pad0[0x18];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ u8 pad1C[0x28];
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48;
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ f32 unk50;
} M7Vector;

void func_806A495C(M7Sprite *arg0, M7Vector *arg1, M7Vector *arg2) {
    f32 sp38;
    f32 sp34;
    f32 sp30;
    M7Model *model;

    sp38 = (f32) arg0->unk0 * 0.5f;
    sp34 = arg0->unk4;
    sp30 = arg0->unk8;
    if (arg0->unk10.unk4 == NULL) {
        func_807149FC(-1);
        func_807149B8(0);
        func_8071495C();
        func_80714998(2);
        func_80714A68((s16) (s32) arg2->unk44, (s16) (s32) arg2->unk48, (s16) (s32) arg2->unk4C,
                      (s16) (s32) arg2->unk50);
        model = func_80714CC0(D_80755390[arg0->unk10.unk0], 1.0f, arg2->unk44, arg2->unk48, 1.0f);
        arg0->unk10.unk4 = model;
        if (arg0->unk10.unk2 != 0) {
            model->unk360 *= -1.0f;
        }
    }
    arg0->unk10.unk4->unk340 = (f32) ((arg2->unk44 + (sp34 + sp38)) * 4.0);
    arg0->unk10.unk4->unk344 = (f32) ((arg2->unk48 + (sp30 + (arg1->unk18 * 0.5f))) * 4.0);
    arg0->unk10.unk4->unk36D = arg0->unk3;
    arg0->unk10.unk4->unk38E = (s16) (s32) arg2->unk44;
    arg0->unk10.unk4->unk390 = (s16) (s32) arg2->unk48;
    arg0->unk10.unk4->unk392 = (s16) (s32) arg2->unk4C;
    arg0->unk10.unk4->unk394 = (s16) (s32) arg2->unk50;
}

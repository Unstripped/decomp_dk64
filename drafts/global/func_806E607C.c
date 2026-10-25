// func_806E607C (src/global/E4090.c): Stage 5: one redundant 'move a1,zero' in the func_806261CC (bit 0x10000 set) arm; target hoists a1=0 once into the block before 'sll t9,t8,15' and f1 reuses it. Tried if/else vs early returns, u8/s16/int/K&R prototypes, int return types, local zero var, permuter 700s: no change. Text otherwise identical (parked NON_MATCHING in E4090.c).
/* Needs from E4090.c: D_807FD580, D_807FBB40, D_807FBB64, D_807FC928, D_807FD63C, G25_PAD, G25_A (G25Actor.unkE6). */
typedef struct G26Obj {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ s32 unk4;
    /* 0x08 */ u8 pad8[0xAC - 0x8];
    /* 0xAC */ u32 unkAC;
    /* 0xB0 */ u8 padB0[2];
    /* 0xB2 */ s16 unkB2;
    /* 0xB4 */ f32 unkB4;
    /* 0xB8 */ f32 unkB8;
    /* 0xBC */ u8 padBC[0xF1 - 0xBC];
    /* 0xF1 */ u8 unkF1;
    /* 0xF2 */ u8 padF2;
    /* 0xF3 */ u8 unkF3;
    /* 0xF4 */ u8 padF4;
    /* 0xF5 */ u8 unkF5;
} G26Obj;

typedef struct G26Holder {
    /* 0x000 */ u8 pad0[0xB4];
    /* 0x0B4 */ f32 unkB4;
    /* 0x0B8 */ u8 padB8[0x174 - 0xB8];
    /* 0x174 */ G26Obj *unk174;
} G26Holder;

typedef struct G26Player {
    /* 0x000 */ u8 pad0[0x104];
    /* 0x104 */ G26Holder *unk104;
    /* 0x108 */ u8 pad108[0x1CC - 0x108];
    /* 0x1CC */ f32 unk1CC;
} G26Player;

#define G26_P ((G26Player *)D_807FD580)
extern u8 D_80750AB8;
void func_806261CC(void *, s32);
void func_80626110(void *, s32, s32);

void func_806E607C(void) {
    G26Obj *obj;

    obj = G26_P->unk104->unk174;
    obj->unkAC |= 4;
    if (G25_PAD(D_807FD63C, u16) & 0x10) {
        if ((D_807FBB64 & 1) || ((D_807FC928 >= 2) && (D_80750AB8 == 0))) {
            if (obj->unkAC & 0x10000) {
                func_806261CC(G26_P->unk104, 0);
                return;
            }
            func_80626110(G26_P->unk104, 0, 0);
            return;
        }
        if (!(obj->unkAC & 0x4000)) {
            obj->unkAC ^= 2;
            if ((obj->unkF1 < 3) && (obj->unkF5 == 0) && (obj->unkF3 != 2)) {
                obj->unkF1 = 0x14;
                obj->unkB2 = G25_A->unkE6;
                G26_P->unk104->unkB4 = obj->unkB8;
                obj->unkF5 = 0xA;
            }
        }
    }
}

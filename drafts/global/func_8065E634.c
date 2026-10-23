// func_8065E634 (src/global/61AA0.c): all 122 insns matched except node stack slot at 0x3C vs 0x30
#include <ultra64.h>

void *func_80610FE8(s32);
s32 func_8065EA98(s32, s16, u8);

typedef struct R2A_Node {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    s32 unkC;
    s32 unk10;
    struct R2A_Node *hash_next;
    struct R2A_Node *hash_prev;
    struct R2A_Node *list_next;
    struct R2A_Node *list_prev;
    s16 unk24;
    s16 unk26;
    u8 unk28;
    s8 unk29;
} R2A_Node;

extern R2A_Node *D_807F8EC0[];
extern R2A_Node *D_807F9050;
extern R2A_Node *D_807F9054;
extern s32 D_8076A064;
extern s32 *D_8076A0B4;
extern s32 *D_8076A0B8;
extern s32 *D_8076A0BC;
extern u8 D_807F78C0;
extern s32 D_807F905C;
extern u16 D_807F9060;

void *func_8065E634(s32 arg0, s32 arg1, s16 arg2, u8 arg3, s32 arg4, u8 arg5) {
    R2A_Node *sp30;
    s32 sp20;
    s32 sp1C;
    void *sp18;
    R2A_Node **bucket;
    R2A_Node *head;

    sp20 = arg0 << 6;
    sp1C = sp20 + (arg4 * 0x10) + 0x30;
    sp30 = func_80610FE8(sp1C);

    bucket = &D_807F8EC0[func_8065EA98(arg0, arg2, arg3)];
    head = *bucket;
    *bucket = sp30;
    sp30->hash_next = head;
    if (head != NULL) {
        head->hash_prev = sp30;
    }
    sp30->hash_prev = NULL;

    sp18 = (u8 *)sp30 + 0x30;
    sp30->unk0 = *(f32 *)((u8 *)D_8076A0B4 + arg1 * 4);
    sp30->unk4 = *(f32 *)((u8 *)D_8076A0B8 + arg1 * 4);
    sp30->unk8 = *(f32 *)((u8 *)D_8076A0BC + arg1 * 4);
    sp30->unk24 = arg2;
    sp30->unk29 = arg0;
    sp30->unk28 = arg3;
    memcpy(sp18, &D_807F78C0, sp20);
    sp30->unkC = D_8076A064;
    sp30->unk26 = arg4;
    D_807F905C += sp1C;
    D_807F9060++;
    sp30->unk10 = sp1C;

    if (arg5 == 0) {
        sp30->list_next = D_807F9050;
        if (D_807F9050 != NULL) {
            D_807F9050->list_prev = sp30;
        }
        sp30->list_prev = NULL;
        D_807F9050 = sp30;
        if (D_807F9054 == NULL) {
            D_807F9054 = sp30;
        }
    } else {
        sp30->list_prev = D_807F9054;
        if (D_807F9054 != NULL) {
            D_807F9054->list_next = sp30;
        }
        sp30->list_next = NULL;
        D_807F9054 = sp30;
        if (D_807F9050 == NULL) {
            D_807F9050 = sp30;
        }
    }

    return (u8 *)sp18 + (arg0 << 6);
}

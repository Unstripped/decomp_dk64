// func_8065F678 (src/global/63EC0.c): near-miss: loop body submatrix and call argument evaluation
typedef struct R1B63810_Struct_6C18 {
    u8 unk0;
    u8 pad1[2];
    u8 unk3;
    u8 pad4[0x64];
    s32 unk68;
    s32 unk6C;
    s32 unk70;
    s32 unk74;
    u8 pad78[0x150];
} R1B63810_Struct_6C18;

typedef struct R1B63810_Target {
    u8 pad0[0xC];
    f32 unkC;
    f32 unk10;
    u8 pad14[0x10];
    f32 unk24;
    f32 unk28;
    u8 pad2C[0x18];
    s16 unk44;
    s16 unk46;
    s16 unk48;
    s16 unk4A;
    s16 unk4C;
    s16 unk4E;
    s16 unk50[11];
    u8 unk66;
    u8 unk67;
    u8 unk68;
    u8 pad69[3];
} R1B63810_Target;

typedef struct R1B63810_Node {
    R1B63810_Target *target;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 x;
    f32 y;
    f32 z;
    s32 unk1C[4];
    void *unk20;
    void *unk24;
    void *unk28;
    s16 unk2C;
    u8 pad2E[2];
    s32 unk30;
    s32 unk34;
    s32 unk38;
    s32 unk3C;
    s16 unk40;
    s16 unk42;
    s16 unk44;
    s16 unk46;
    s16 unk48;
    u8 unk4A;
    u8 unk4B;
    u8 unk4C;
    u8 unk4D;
    u8 pad4E[2];
    struct R1B63810_Node *next;
} R1B63810_Node;

s32 func_8062DBDC(s16, s16, s16, s16, s32, s32, f32, f32, f32, f32, void *);
void func_8062FF10(void *, f32 (*)[4]);
void func_8065F964(R1B63810_Node *, f32, f32, f32, s32, void *, void *);
s32 func_8065FB04(R1B63810_Target *);
void func_80660520(s32, void *);
void func_80660830(s32, void *);
void func_80660D38(s32, void *);
void guMtxL2F(f32 (*)[4], void *);

extern u8 D_807444FC;
extern f32 D_807F5FAC;
extern R1B63810_Struct_6C18 *D_807F6C18;
extern R1B63810_Node *D_807F93C0;
extern u8 *D_807FC924;

void func_8065F678(f32 arg0, f32 arg1, f32 arg2, s32 arg3) {
    u8 sp120[0x88];
    u8 sp98[0x40];
    f32 spD8[4][4];
    u8 *var_s1;
    f32 temp_fs0;
    f32 temp_fs1;
    s32 temp_s6 = arg3 & 0xFF;
    s32 var_s5 = 0;
    R1B63810_Node *node = D_807F93C0;

    if (node != NULL) {
        do {
            if (func_8065FB04(node->target) != 0 && !(node->unk4C & 1)) {
                R1B63810_Target *target = node->target;
                temp_fs1 = target->unk10 + target->unkC;
                temp_fs0 = (f32)target->unk4E + node->unk4;
                if (target->unk67 == 1) {
                    var_s1 = (u8 *)&D_807F6C18[target->unk50[0]] + 0x88;
                } else {
                    var_s1 = sp120;
                    if (var_s5 == 0) {
                        var_s5 = 1;
                        guMtxL2F(spD8, D_807FC924 + (temp_s6 * 0x2F0) + (D_807444FC << 6) + 8);
                        func_8062FF10(sp98, spD8);
                    }
                    func_8065F964(node, arg0, arg1, arg2, temp_s6, sp98, sp120);
                }
                if (func_8062DBDC(target->unk46, (s32)(temp_fs0 - temp_fs1), target->unk48, target->unk4A,
                                  (s32)(temp_fs0 + temp_fs1), target->unk4C, arg0, arg1, arg2, D_807F5FAC, var_s1) != 0 || node->unk4D != 0) {
                    if ((f64)target->unk24 != 0.0 || (f64)target->unk28 != 0.0) {
                        func_80660D38(node->unk1C[D_807444FC], node);
                    }
                    if ((f64)target->unkC != 0.0 || (f64)target->unk10 != 0.0) {
                        func_80660520(node->unk1C[D_807444FC], node);
                    }
                    func_80660830(node->unk1C[D_807444FC], node);
                    node->unk4C |= 1;
                }
            }
            node = node->next;
        } while (node != NULL);
    }
}

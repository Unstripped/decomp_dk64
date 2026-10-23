// func_8065E138 (src/global/61AA0.c): 318/319 insns; inner loop structure matched, D_807F78C0 array indexing hoisted vs loop preheader register allocation difference
typedef struct {
    float unk0;
    float unk4;
    float unk8;
    float unkC;
    float unk10;
    float unk14;
    float unk18;
    float unk1C;
    float unk20;
    float unk24;
    float unk28;
    float unk2C;
    float unk30;
    float unk34;
    short unk38;
    short unk3A;
    short unk3C;
    unsigned char unk3E;
    unsigned char pad3F;
} SubEntry;

typedef struct Node {
    float unk0;
    float unk4;
    float unk8;
    int unkC;
    int unk10;
    struct Node *hash_next;
    struct Node *unk18;
    struct Node *next;
    struct Node *prev;
    short unk24;
    short unk26;
    unsigned char unk28;
    unsigned char unk29;
    unsigned char pad2A[6];
    SubEntry sub[1];
} Node;

extern int D_8076A064;
extern float *D_8076A0B4;
extern float *D_8076A0B8;
extern float *D_8076A0BC;
extern SubEntry D_807F78C0[];
extern Node *D_807F8EC0[];
extern Node *D_807F9050;
extern Node *D_807F9054;
extern short D_807F9058;
extern short D_807F905A;
int func_8065EA98(int, short, unsigned char);

#define DIFF(a, b) (((b) < (a)) ? ((a) - (b)) : -((a) - (b)))

void *func_8065E138(arg0, arg1, arg2, arg3)
int arg0;
int arg1;
short arg2;
unsigned char arg3;
{
    Node *node;
    int var_t0;
    int var_a1;
    int var_a0;

    D_807F9058++;
    node = D_807F8EC0[func_8065EA98(arg0, arg2, arg3)];
    while (node != NULL) {
        if (arg0 == node->unk29 && arg2 == node->unk24 && arg3 == node->unk28) {
            if (node->unk0 == D_8076A0B4[arg1] && node->unk4 == D_8076A0B8[arg1]) {
                var_t0 = 0;
                if (node->unk8 == D_8076A0BC[arg1]) {
                    var_a1 = 0;
                    if (arg0 > 0) {
                        do {
                            var_a1 = 1;
                            if (arg0 > 0) {
                                SubEntry *sub_node = (SubEntry *)((char *)node + (var_t0 << 6) + 0x30);
                                var_a0 = 0;
                                do {
                                    var_a0++;
                                    if (D_807F78C0[var_a0 - 1].unk3E == 1) {
                                        if (sub_node->unk38 == D_807F78C0[var_a0 - 1].unk38 &&
                                            sub_node->unk3A == D_807F78C0[var_a0 - 1].unk3A &&
                                            sub_node->unk3C == D_807F78C0[var_a0 - 1].unk3C &&
                                            (double)DIFF(D_807F78C0[var_a0 - 1].unkC, sub_node->unkC) < 0.05 &&
                                            (double)DIFF(D_807F78C0[var_a0 - 1].unk10, sub_node->unk10) < 0.05 &&
                                            (double)DIFF(D_807F78C0[var_a0 - 1].unk14, sub_node->unk14) < 0.05 &&
                                            (double)DIFF(D_807F78C0[var_a0 - 1].unk2C, sub_node->unk2C) < 0.05 &&
                                            (double)DIFF(D_807F78C0[var_a0 - 1].unk30, sub_node->unk30) < 0.05 &&
                                            (double)DIFF(D_807F78C0[var_a0 - 1].unk34, sub_node->unk34) < 0.05 &&
                                            sub_node->unk0 == D_807F78C0[var_a0 - 1].unk0 &&
                                            sub_node->unk4 == D_807F78C0[var_a0 - 1].unk4) {
                                            var_a1 = 0;
                                        }
                                    } else if (sub_node->unk38 == D_807F78C0[var_a0 - 1].unk38 &&
                                               sub_node->unk3A == D_807F78C0[var_a0 - 1].unk3A &&
                                               sub_node->unk3C == D_807F78C0[var_a0 - 1].unk3C &&
                                               (double)DIFF(D_807F78C0[var_a0 - 1].unk2C, sub_node->unk2C) < 0.05 &&
                                               (double)DIFF(D_807F78C0[var_a0 - 1].unk30, sub_node->unk30) < 0.05 &&
                                               (double)DIFF(D_807F78C0[var_a0 - 1].unk34, sub_node->unk34) < 0.05 &&
                                               sub_node->unk1C == D_807F78C0[var_a0 - 1].unk1C) {
                                        var_a1 = 0;
                                    }
                                } while (var_a1 != 0 && var_a0 < arg0);
                            }
                            if (var_a1 != 0) break;
                            var_t0++;
                        } while (var_t0 < arg0);
                    }
                    if (var_a1 == 0) {
                        SubEntry *sub = node->sub;
                        node->unkC = D_8076A064;
                        D_807F905A++;
                        if (node->prev != NULL) {
                            if (node->next == NULL) {
                                D_807F9054 = node->prev;
                            }
                            node->prev->next = node->next;
                            if (node->next != NULL) {
                                node->next->prev = node->prev;
                            }
                            D_807F9050->prev = node;
                            node->prev = NULL;
                            node->next = D_807F9050;
                            D_807F9050 = node;
                        }
                        return &sub[arg0];
                    }
                }
            }
        }
        node = node->hash_next;
    }
    return 0;
}

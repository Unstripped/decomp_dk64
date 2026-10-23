// func_8066AF40 (src/global/699B0.c): near-miss: lbu unk8 vs sb 0(s2) store order and s0/s2/s4 lo order
typedef struct {
    void *unk0;
    void *unk4;
    u8 unk8;
} R1D_StructA8A0;
extern R1D_StructA8A0 D_807FA8A0[];
extern s8 D_80746834;
extern OSMesgQueue D_807656D0;
extern s32 D_807F9680;
extern void *D_80748E14;
void func_8066AEE4(void *, void *);
void heapFree(void *);

void func_8066AF40(void) {
    R1D_StructA8A0 *item;
    s32 i;

    i = 0;
    if (D_807F9680 > 0) {
        item = D_807FA8A0;
        do {
            D_80746834 = 7;
            osRecvMesg(&D_807656D0, NULL, 1);
            D_80746834 = 0;
            if (item->unk8 != 0) {
                func_8066AEE4(item->unk0, item->unk4);
            }
            item++;
        } while (++i < D_807F9680);
    }
    if (D_80748E14 != NULL) {
        heapFree(D_80748E14);
        D_80748E14 = NULL;
    }
    D_807F9680 = 0;
}

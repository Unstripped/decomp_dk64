// func_806F5270 (src/global/F9450.c): stage 3: cleanup list loops recovered; target's pointer lifetime keeps a 0x28 frame while draft uses 0x50
typedef struct F9N3_CleanupListNode {
    u8 pad0[0x18];
    struct F9N3_CleanupListNode *next;
} F9N3_CleanupListNode;
typedef struct F9N3_CleanupNode {
    u8 pad0[0x18];
    struct F9N3_CleanupNode *next;
} F9N3_CleanupNode;
typedef struct F9N3_LinkedNode {
    u8 pad0[0x1C];
    struct F9N3_LinkedNode *next;
} F9N3_LinkedNode;

extern F9N3_CleanupListNode **D_80754244;
extern s16 D_807FD720;
extern F9N3_CleanupNode *D_807FD72C;
extern F9N3_LinkedNode *D_807FD730;
void heapFree(void *);
void func_806F95C8(void);

void func_806F5270(void) {
    s32 var_s2;
    s32 var_s3;
    F9N3_CleanupListNode *temp_s0;
    F9N3_CleanupListNode *var_s1;
    F9N3_CleanupNode *temp_s0_2;
    F9N3_CleanupNode *var_s1_2;
    F9N3_LinkedNode *temp_s1;
    F9N3_LinkedNode *var_s0;
    F9N3_CleanupListNode **temp_a0;

    temp_a0 = D_80754244;
    if (temp_a0 != NULL) {
        var_s2 = 0;
        var_s3 = 0;
        if (D_807FD720 > 0) {
            do {
                var_s1 = *(F9N3_CleanupListNode **) ((u8 *) temp_a0 + var_s3);
                if (var_s1 != NULL) {
                    do {
                        temp_s0 = var_s1->next;
                        heapFree(var_s1);
                        var_s1 = temp_s0;
                    } while (temp_s0 != NULL);
                }
                var_s2 += 1;
                var_s3 += 4;
            } while (var_s2 < D_807FD720);
        }
        heapFree(temp_a0);
        D_80754244 = NULL;
    }
    var_s1_2 = D_807FD72C;
    if (var_s1_2 != NULL) {
        do {
            temp_s0_2 = var_s1_2->next;
            heapFree(var_s1_2);
            var_s1_2 = temp_s0_2;
        } while (temp_s0_2 != NULL);
    }
    if (D_807FD730 != NULL) {
        var_s0 = D_807FD730;
        if (D_807FD730 != NULL) {
            do {
                temp_s1 = var_s0->next;
                heapFree(var_s0);
                var_s0 = temp_s1;
            } while (temp_s1 != NULL);
        }
        D_807FD730 = NULL;
    }
    func_806F95C8();
}

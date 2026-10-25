// func_8070DD44 (src/global/112080.c): stage 3: correct queue unlink/decrement flow, but CFE retains node pointer in a0 and saves s0 before global load
extern s32 D_807550C0;

typedef struct R112cQueueNode {
    u8 pad0[2];
    u8 unk2;
    u8 pad3[5];
    u8 unk8;
    u8 pad9[3];
    struct R112cQueueNode *unkC;
} R112cQueueNode;

void func_8070DD44(void) {
    u8 temp_v1;
    void **var_s0;
    void *var_v0;

    var_s0 = (void **) &D_807550C0;
    if (D_807550C0 != 0) {
        var_v0 = (void *) D_807550C0;
        do {
            if (((R112cQueueNode *) var_v0)->unk8 == 1) {
                temp_v1 = ((R112cQueueNode *) var_v0)->unk2;
                if (temp_v1 != 0) {
                    ((R112cQueueNode *) var_v0)->unk2 = temp_v1 - 1;
                    var_v0 = *var_s0;
                }
            }
            if (((R112cQueueNode *) var_v0)->unk2 == 0) {
                *var_s0 = ((R112cQueueNode *) var_v0)->unkC;
                func_8070DD18((M112bRecordListHolder *) var_v0);
            } else {
                var_s0 = (void **) &((R112cQueueNode *) var_v0)->unkC;
            }
            var_v0 = *var_s0;
        } while (var_v0 != NULL);
    }
}

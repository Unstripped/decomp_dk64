// func_80614C38 (src/global/17B90.c): stage 4; 5 fdiff attempts. Frame/save set and code size exact. Remaining allocation/scheduling: byte index stays v0 rather than target v1, preventing target's branch-delay sll reuse; tried s32/narrow types, declaration order, precomputed shifted index, and explicit shift-count temp.
typedef struct P17c2SegmentNode {
    void *unk0;
    void *unk4;
    u8 unk8;
    u8 pad9[3];
    struct P17c2SegmentNode *unkC;
} P17c2SegmentNode;

typedef struct {
    u8 pad0[0x14];
    P17c2SegmentNode *unk14;
} P17c2Display;

typedef struct {
    u8 pad0[0x146];
    u16 unk146;
} P17c2RenderActor;

u32 *func_80614C38(u32 *arg0, P17c2RenderActor *arg1, P17c2Display *arg2) {
    u32 *temp_s2;
    u32 *var_s1;
    u16 temp_s4;
    u8 temp_v1;
    s32 temp_v0;
    u32 temp_t2;
    u32 var_v0;
    P17c2SegmentNode *var_s0;

    var_s0 = arg2->unk14;
    var_s1 = arg0;
    temp_s4 = arg1->unk146;
    if (var_s0 != NULL) {
        do {
            temp_v1 = var_s0->unk8;
            temp_s2 = var_s1;
            temp_v0 = temp_v1 - 7;
            temp_t2 = temp_v1 * 4;
            if (((s32) temp_s4 >> (temp_v0 & 0xFF)) & 1) {
                var_s1[0] = ((temp_v1 * 4) & 0xFFFF) | 0xDB060000;
                var_s1 += 2;
                var_v0 = osVirtualToPhysical(var_s0->unk0);
            } else {
                temp_s2[0] = (temp_t2 & 0xFFFF) | 0xDB060000;
                var_s1 += 2;
                var_v0 = osVirtualToPhysical(var_s0->unk4);
            }
            temp_s2[1] = var_v0;
            var_s0 = var_s0->unkC;
        } while (var_s0 != NULL);
    }
    return var_s1;
}

// actorListFindClosestTargetIndex (src/global/8D3E0.c): Stage 4+: frame 0x18, 109 insns, whole body identical except 3 branch operand orders (bnel target,arg1[j] vs expected arg1[j],target) in the unrolled j loop. Levers: inner j loop 'for (j=0;j<arg2;j++)' (2x unroll needs target expr inside the loop, not a hoisted var), item=&((rec*)(list+1))[i] with a second pointer alias 'list=arg0' (permuter), unk32+0x10U stops x-16==y rewrite. Tried named dx/dy/dz, target vars, cmp orders, j/i types: no operand flip.
s32 actorListFindClosestTargetIndex(s32 *arg0, s16 *arg1, u8 arg2, f32 arg3, f32 arg4, f32 arg5) {
    s32 total = *arg0;
    s32 bestIndex = -1;
    f32 minDistance = 9999999.0f;
    s32 i;
    s32 j;
    ActorListRecord *item;
    s32 *list;
    f32 dist;

    list = arg0; // FAKE: second pointer to the list moves the item/j colours (permuter find)
    for (i = 0; i < total; i++) {
        item = &((ActorListRecord *)(list + 1))[i];
        for (j = 0; j < arg2; j++) {
            if (arg1[j] == item->unk32 + 0x10U) { // FAKE: unsigned 0x10U keeps IDO from rewriting the compare to x - 16 == y
                dist = ((item->unk08 - arg5) * (item->unk08 - arg5)) + (((item->unk00 - arg3) * (item->unk00 - arg3)) + ((item->unk04 - arg4) * (item->unk04 - arg4)));
                if (dist < minDistance) {
                    minDistance = dist;
                    bestIndex = item->unk34;
                }
            }
        }
    }
    return bestIndex;
}

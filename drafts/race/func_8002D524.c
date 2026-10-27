// func_8002D524 (src/race/7BD0.c): stage 3: instruction stream/branches match (bubble sort + position pass) but frame is 0x78 vs 0x70 and RacePair tmp lands at sp+0x70 vs sp+0x50 (target = 6 named locals before tmp, 1 after; with exactly 7 named locals incl. t/i/j/cnt/swap the frame matches, e.g. t,list,base,cnt,i,j,swap with p/q unnamed, but then uopt strength-reduces base[j-1]/base[j] into an IV); also s0/s1 swapped (i vs list pointer, target list=s0 i=s1; list defined late fixes that but moves the lw t2/move s0,t2 hoist). decl-order sweeps never change the frame; 3 permuter rounds stuck.
void func_8002D524(void) {
    RacePair tmp;
    RaceUnknown174 *t;
    RacePair *list;
    RacePair *base;
    RacePair *p;
    RacePair *q;
    u8 cnt;
    s32 i;
    s32 j;
    s32 swap;

    t = D_807FBB40->unk174;
    cnt = 0;
    list = base = t->unk20;
    for (i = t->unk1E - 1; i >= 0; i--) {
        for (j = 1; j <= i; j++) {
            p = &base[j - 1];
            q = &base[j];
            swap = 0;
            if (p->unk4->unk45 != 0 && q->unk4->unk45 == 0) {
                swap = 1;
            } else {
                q = &base[j];
                if (p->unk4->unk37 < q->unk4->unk37) {
                    swap = 1;
                } else if (p->unk4->unk37 == q->unk4->unk37) {
                    if (p->unk4->unk3A < q->unk4->unk3A) {
                        swap = 1;
                    } else if (p->unk4->unk3A == q->unk4->unk3A && q->unk4->unk40 < p->unk4->unk40) {
                        swap = 1;
                    }
                }
            }
            if (swap != 0) {
                tmp = *p;
                *p = *q;
                *q = tmp;
            }
        }
    }
    for (i = 0; i < t->unk1E; i++, list++) {
        list->unk4->unk36 = i;
        if (list->unk4->unk45 != 0 || (list->unk4->unk34 == 2 && t->unk24 < list->unk4->unk37)) {
            func_8002D148(list, 3);
            cnt++;
        }
    }
    if (cnt >= t->unk1E - 1) {
        func_8002D224(3);
        func_8002D40C();
        t->unk1C = 0;
    }
}

// func_80728300 (src/global/1295B0.c): stage 3-4: text size matches (21072) after 's32 t = *src++; cnt = t; store t' read idiom; remaining diff = s-reg allocation: mine puts src/p pointers in s-regs (frame 0x58, uses s8) while target keeps them in t0/a3 (spilled around calls; frame 0x60, s0-s7 only: rec s0,j s1,cnt s2,prev s3,same s4,6 s5,0xA s6,i s7) and shifts for cnt*6 instead of multu s6. Needs C1Node: u8 unk11, u8(*unk20)[2], f32 unk3C.


typedef struct C1S6 {
    s16 v[3];
} C1S6;

typedef struct C1S10 {
    s16 v[5];
} C1S10;

typedef struct C1S22 {
    s16 v[11];
} C1S22;

typedef struct C1Rec24 {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ u8 padA[2];
    /* 0x0C */ C1S6 *unkC;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ u8 pad12[2];
    /* 0x14 */ C1S10 *unk14;
    /* 0x18 */ s8 unk18;
    /* 0x19 */ s8 unk19;
    /* 0x1A */ u8 pad1A[0xA];
} C1Rec24; // size = 0x24

typedef struct C1Rec24List {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ u8 pad2[2];
    /* 0x4 */ C1Rec24 *unk4;
} C1Rec24List;

void *func_80610FE8(s32);
void heapClearBlock(void *);

void func_80728300(s16 *arg0, C1Rec24List *arg1, C1NodeList *arg2) {
    s16 *src;
    s16 *p;
    C1Rec24 *rec;
    C1Node *node;
    s16 i;
    s16 j;
    s16 cnt;
    s16 prev;
    s32 same;
    void *mem;
    s32 t;

    src = arg0;
    if (src != NULL) {
        t = *src++;
        cnt = t;
        arg1->unk0 = t;
    } else {
        arg1->unk0 = 0;
        cnt = arg1->unk0;
    }
    rec = func_80610FE8(cnt * 0x24);
    arg1->unk4 = rec;
    for (i = 0; i < arg1->unk0; i++) {
        same = 1;
        j = 0;
        if (i != 0) {
            rec++;
        }
        rec->unk0 = 0x7FFF;
        rec->unk4 = -0x8000;
        rec->unk2 = rec->unk0;
        rec->unk6 = rec->unk4;
        if (src != NULL) {
            t = *src++;
            cnt = t;
            rec->unk8 = t;
        } else {
            rec->unk8 = 0;
            cnt = rec->unk8;
        }
        p = src;
        if (cnt != 0) {
            rec->unkC = func_80610FE8(cnt * 6);
        }
        if (cnt > 0) {
            do {
                rec->unkC[j] = *(C1S6 *)p;
                p += 3;
                rec->unk0 = (rec->unk0 < rec->unkC[j].v[0]) ? rec->unk0 : rec->unkC[j].v[0];
                rec->unk2 = (rec->unk2 < rec->unkC[j].v[2]) ? rec->unk2 : rec->unkC[j].v[2];
                rec->unk4 = (rec->unkC[j].v[0] < rec->unk4) ? rec->unk4 : rec->unkC[j].v[0];
                rec->unk6 = (rec->unkC[j].v[2] < rec->unk6) ? rec->unk6 : rec->unkC[j].v[2];
                if (j == 0) {
                    prev = rec->unkC[j].v[1];
                } else {
                    if (prev != rec->unkC[j].v[1]) {
                        same = 0;
                    }
                    prev = rec->unkC[j].v[1];
                }
                j++;
            } while (j < cnt);
            j = 0;
        }
        src = p;
        if (src != NULL) {
            t = *src++;
            cnt = t;
            rec->unk10 = t;
        } else {
            rec->unk10 = 0;
            cnt = rec->unk10;
        }
        p = src;
        if (cnt != 0) {
            rec->unk14 = func_80610FE8(cnt * 0xA);
        }
        if (cnt > 0) {
            do {
                rec->unk14[j] = *(C1S10 *)p;
                j++;
                p += 5;
            } while (j < cnt);
        }
        src = p;
        if (src != NULL) {
            rec->unk18 = *src;
            src += 2;
            rec->unk19 = src[-1];
            if (same != 0) {
                rec->unk19 = 1;
            }
        }
    }
    i = 0;
    if (src != NULL) {
        t = *src++;
        cnt = t;
        arg2->count = t;
    } else {
        arg2->count = 0;
        cnt = 0;
    }
    mem = func_80610FE8(cnt * 0x48);
    arg2->nodes = mem;
    heapClearBlock(mem);
    p = src;
    node = arg2->nodes;
    for (; i < arg2->count; i++) {
        j = 0;
        if (i != 0) {
            node++;
        }
        *(C1S22 *)node = *(C1S22 *)p;
        p += 11;
        node->unk42 = node->unk12;
        node->unk44 = node->unk0;
        node->unk18 = 0;
        node->unk46 = 0;
        node->unk24 = 0;
        node->unk43 = 0;
        node->unk3C = 0.0f;
        node->unk40 = func_806531B8((f32)node->unk4, (f32)node->unk6, (f32)node->unk8, 0);
        node->unk20 = func_80610FE8(node->unk11 * 2);
        src = p;
        if (node->unk11 > 0) {
            do {
                node->unk20[j][0] = ((u8 *)src)[0];
                node->unk20[j][1] = ((u8 *)src)[1];
                j++;
                src += 1;
            } while (j < node->unk11);
        }
        p = src;
        func_8072827C((C1Holder *)node);
    }
}

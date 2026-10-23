// func_80658930 (src/global/55B20.c): stage 2/4: loop body reconstructed (memset D_807F70B8..D_807F7138, then per-entry alloc 0x6C, fields 0x10=0x7FFF/0x12=-0x8000/0x8=0/0x4 from stream +0x20/+0x36/+0x58 memcpys, unkE, sb 0x34/0x56/0x68, func_80651708); remaining: memset pre-test rotation, n kept in stack slot 0x46 not s8, saved-reg numbering
extern u8 *D_807F70B8[];

typedef struct M55P7Node {
    /* 0x00 */ u8 *unk0;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ u8 pad6[0x2];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u8 padC[0x2];
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ u8 unk14[0x20];
    /* 0x34 */ s8 unk34;
    /* 0x36 */ u8 unk36[0x20];
    /* 0x56 */ s8 unk56;
    /* 0x58 */ u8 unk58[0x10];
    /* 0x68 */ s8 unk68;
} M55P7Node;

void *func_80610FE8(s32);
void func_80651708(s32);

void func_80658930(u8 *arg0) {
    M55P7Node *node;
    s32 *w;
    u8 *p;
    s16 n;
    s16 i;
    s16 idx;
    s32 size;

    for (w = (s32 *)D_807F70B8; (u8 *)w < (u8 *)&D_807F7138; w++) {
        *w = 0;
    }
    if (arg0 == NULL) {
        return;
    }
    n = *(s16 *)arg0;
    p = arg0 + 2;
    for (i = 0; i < n; i++) {
        idx = *(s16 *)p;
        p += 2;
        D_807F70B8[idx] = (u8 *)func_80610FE8(0x6C);
        ((M55P7Node *)D_807F70B8[idx])->unk10 = 0x7FFF;
        ((M55P7Node *)D_807F70B8[idx])->unk12 = -0x8000;
        ((M55P7Node *)D_807F70B8[idx])->unk8 = 0;
        ((M55P7Node *)D_807F70B8[idx])->unk4 = *(s16 *)(p - 2);
        size = ((M55P7Node *)D_807F70B8[idx])->unk4 * 6;
        ((M55P7Node *)D_807F70B8[idx])->unk0 = func_80610FE8(size);
        memcpy(((M55P7Node *)D_807F70B8[idx])->unk0, p, size);
        size = ((M55P7Node *)D_807F70B8[idx])->unk4 * 6;
        p += (size / 2) * 2;
        ((M55P7Node *)D_807F70B8[idx])->unkE = *(s16 *)p;
        p += 4;
        memcpy(((M55P7Node *)D_807F70B8[idx])->unk14, p, 0x20);
        ((M55P7Node *)D_807F70B8[idx])->unk34 = (s8)*(s16 *)(p + 0x20);
        p += 0x22;
        memcpy(((M55P7Node *)D_807F70B8[idx])->unk36, p, 0x20);
        ((M55P7Node *)D_807F70B8[idx])->unk56 = (s8)*(s16 *)(p + 0x20);
        p += 0x22;
        memcpy(((M55P7Node *)D_807F70B8[idx])->unk58, p, 0x10);
        p += 0x10;
        func_80651708(idx);
    }
}

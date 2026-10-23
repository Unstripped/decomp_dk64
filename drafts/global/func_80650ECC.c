// func_80650ECC (src/global/55B20.c): stage 4-5: statement sequence identical (515/527 insns); uopt caches &D_807F70AC in s0 and spills arg0 (target keeps arg0 in s7, frame 0xED8 vs my 0xEE8); needs regalloc/decl hunt
typedef struct M50ECCMapData {
    /* 0x00 */ u8 pad0[0xC];
    /* 0x0C */ s16 unkC;
    /* 0x0E */ u8 padE[0x26];
    /* 0x34 */ s32 unk34;
    /* 0x38 */ u8 pad38[0x20];
    /* 0x58 */ s32 unk58;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ s32 unk60;
    /* 0x64 */ s32 unk64;
    /* 0x68 */ s32 unk68;
    /* 0x6C */ s32 unk6C;
    /* 0x70 */ s32 unk70;
} M50ECCMapData;

typedef struct M50ECCReloc {
    /* 0x0 */ u8 pad0[8];
    /* 0x8 */ s32 unk8;
    /* 0xC */ s32 unkC;
} M50ECCReloc;

extern s32 D_807F5DE8;
extern s32 D_807F70AC;
extern u8 D_807F70AB;
extern s16 D_807F7138;
extern u8 D_807F713A;
extern u8 D_807F7079;
extern u8 D_807F707A[];
extern u8 D_807F70AA;
extern Mtx *D_807F7074;
extern u8 *D_807F6C0C;
extern s32 D_807F6C10;
extern u8 *D_807F6C14;
extern u8 *D_807F6C24;
extern struct M55P2SearchEntry *D_807F70B0;
extern struct M55P2BoxEntry *D_807F70B4;

void *func_80610FE8(s32);
void lightSetTargetColor(f32, f32, f32, s16);
void lightCopyTargetColors(s16);
void func_80651904(s32, s32, void *, s32 *, s32, s32);
void func_80651C2C(s32, void *);

void func_80650ECC(M50ECCMapData *arg0) {
    u8 *q;
    u8 *p;
    s32 base;
    u8 buf[0xE54];
    s32 count;
    s32 i;
    s32 j;
    s32 total;
    s32 val;
    s32 off;
    s32 colOff;
    u8 *w;
    u8 *w4;

    D_807F70AC = 0;
    D_807F713A = 0;
    D_807F70AB = 0;
    if (D_807F6C28 != 0) {
        D_807F7138 = arg0->unkC;
        D_807F7074 = func_80610FE8(0x40);
        guScale(D_807F7074, 1.0f / 3.0f, 1.0f / 3.0f, 1.0f / 3.0f);
        off = arg0->unk58;
        D_807F70AC = *(s32 *)((u8 *)arg0 + off);
        D_807F70B0 = (struct M55P2SearchEntry *)((u8 *)arg0 + off + 4);
        off = arg0->unk5C;
        D_807F70B4 = (struct M55P2BoxEntry *)((u8 *)arg0 + off + 4);
        off = arg0->unk60;
        D_807F6C14 = (u8 *)arg0 + off;
        base = arg0->unk34;
        w = (u8 *)arg0 + arg0->unk64;
        p = (u8 *)arg0 + arg0->unk68;
        off = arg0->unk6C;
        D_807F6C20 = *(s32 *)((u8 *)arg0 + off);
        D_807F6C1C = (u8 *)arg0 + off + 4;
        D_807F6C2C = func_80610FE8(D_807F6C20);
        off = arg0->unk70;
        D_807F6C10 = *(s32 *)((u8 *)arg0 + off);
        D_807F6C0C = (u8 *)arg0 + off + 4;
        for (i = 0; i < D_807F6C10; i++) {
            if (((M50ECCReloc *)D_807F6C0C)[i].unk8 != -1) {
                ((M50ECCReloc *)D_807F6C0C)[i].unk8 += (s32)arg0 + base;
            }
            if (((M50ECCReloc *)D_807F6C0C)[i].unkC != -1) {
                ((M50ECCReloc *)D_807F6C0C)[i].unkC += (s32)arg0 + base;
            }
        }
        D_807F6C18 = func_80610FE8(D_807F6C28 * 0x1C8);
        w4 = w + 4;
        i = 0;
        if (D_807F6C28 > 0) {
            colOff = 0;
            do {
                count = 0;
                D_807F6C18[i].unk0 = 0;
                D_807F6C18[i].unk1 = 0;
                D_807F6C18[i].unk14 = 0;
                D_807F6C18[i].unk1C = 0;
                D_807F6C18[i].unk24 = 0;
                D_807F6C18[i].unk7 = 4;
                D_807F6C18[i].unk54 = *(s32 *)(p + 0x2C) + D_807F5DE8;
                D_807F6C18[i].unk58 = D_807F6C18[i].unk54;
                lightSetTargetColor(p[0] / 255.0, p[1] / 255.0, p[2] / 255.0, (s16)i);
                lightCopyTargetColors((s16)i);
                D_807F6C18[i].unk6 = p[3];
                p += 0xC;
                D_807F6C18[i].unk5 = p[-8];
                D_807F6C18[i].unk3 = *(s32 *)(p - 4);
                val = *(s32 *)p;
                if (val != -1) {
                    val += (s32)arg0 + base;
                    *(s32 *)p = val;
                }
                p += 8;
                D_807F6C18[i].unk2C = val;
                D_807F6C18[i].unk3C = *(s32 *)(p - 4);
                total = D_807F6C18[i].unk3C;
                if (D_807F6C18[i].unk5 == 2) {
                    D_807F713A = 1;
                    func_80651904(D_807F6C18[i].unk2C, D_807F6C18[i].unk3C, buf, &count, 0, i);
                }
                val = *(s32 *)p;
                if (val != -1) {
                    val += (s32)arg0 + base;
                    *(s32 *)p = val;
                }
                p += 8;
                D_807F6C18[i].unk30 = val;
                D_807F6C18[i].unk40 = *(s32 *)(p - 4);
                total += D_807F6C18[i].unk40;
                if (D_807F6C18[i].unk5 == 2) {
                    func_80651904(D_807F6C18[i].unk30, D_807F6C18[i].unk40, buf, &count, 1, i);
                }
                val = *(s32 *)p;
                if (val != -1) {
                    val += (s32)arg0 + base;
                    *(s32 *)p = val;
                }
                p += 8;
                D_807F6C18[i].unk34 = val;
                D_807F6C18[i].unk44 = *(s32 *)(p - 4);
                total += D_807F6C18[i].unk44;
                if (D_807F6C18[i].unk5 == 2) {
                    func_80651904(D_807F6C18[i].unk34, D_807F6C18[i].unk44, buf, &count, 2, i);
                }
                val = *(s32 *)p;
                if (val != -1) {
                    val += (s32)arg0 + base;
                    *(s32 *)p = val;
                }
                p += 8;
                D_807F6C18[i].unk38 = val;
                D_807F6C18[i].unk48 = *(s32 *)(p - 4);
                total += D_807F6C18[i].unk48;
                D_807F6C18[i].unk8 = D_807F6C18[i].unk2C + ((total >> 3) << 3);
                D_807F6C18[i].unkC = D_807F6C18[i].unk2C;
                D_807F6C18[i].unk10 = D_807F6C18[i].unk8;
                if (D_807F6C18[i].unk5 == 2) {
                    func_80651904(D_807F6C18[i].unk38, D_807F6C18[i].unk48, buf, &count, 3, i);
                }
                D_807F6C18[i].unk5C = *(s32 *)(p + 4);
                p += 8;
                D_807F6C18[i].unk60 = 0;
                D_807F6C18[i].unk64 = 0;
                D_807F6C18[i].unk78 = *(s32 *)(w4 + colOff) + (s32)w;
                D_807F6C18[i].unk7C = *(s32 *)(w4 + colOff + 0xC) + (s32)w;
                D_807F6C18[i].unk80 = *(s16 *)(w4 + colOff + 4);
                D_807F6C18[i].unk82 = *(s16 *)(w4 + colOff + 6);
                D_807F6C18[i].unk84 = *(s16 *)(w4 + colOff + 8);
                D_807F6C18[i].unk86 = *(s16 *)(w4 + colOff + 0xA);
                D_807F6C18[i].unk28 = -1;
                if (count != 0) {
                    D_807F6C18[i].unk4C = func_80610FE8(count * 0x24);
                    memcpy(D_807F6C18[i].unk4C, buf, count * 0x24);
                    j = 0;
                    for (j = 0; j < count; j++) {
                        ((u8 *)D_807F6C18[i].unk4C)[j * 0x24 + 2] = 0xFF;
                    }
                }
                D_807F6C18[i].unk50 = count;
                colOff += 0xC;
                i++;
            } while (i < D_807F6C28);
        }
        D_807F6C24 = func_80610FE8(D_807F6C20 / 2 * 0x30);
        for (i = 0; i < D_807F6C20 / 2; i++) {
            func_80651C2C(i, D_807F6C24 + i * 0x30);
        }
        D_807F7079 = 1;
        D_807F7078[0] = 1;
        q = D_807F707A;
        do {
            *q++ = 1;
            *q++ = 1;
            *q++ = 1;
            *q++ = 1;
        } while (q != &D_807F70AA);
        D_807F70AA = 0;
    } else {
        D_807F6C18 = NULL;
    }
}

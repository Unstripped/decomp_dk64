// camLoadPathData (src/global/201B0.c): func_806264DC/camLoadPathData (src/global/201B0.c): stage 5: 466 vs 466 insns, frame+saved set match, deadsweep score 64 -> 2 (text 2): only addiu s2,s2,2 vs move s3,t1 order in the unkD0 loop (m=*hdr++;k=m). Levers: heapAlloc((u32)cnt) (callee defined u32), separate zone-loop pointer zp replacing a pad local (splits s from case-4/5 pointer, fixes s0/s1 swap), u=&unkD8[i].u first without pt local, one k=k FAKE
typedef struct CamPathSeg {
    /* 0x00 */ s16 a[3];
    /* 0x06 */ s16 b[3];
    /* 0x0C */ s16 c[3];
} CamPathSeg; // size = 0x12

typedef struct CamPathZoneRaw {
    /* 0x00 */ s16 v[14];
} CamPathZoneRaw; // size = 0x1C

typedef struct CamPathKeyPosLookRaw {
    /* 0x00 */ s16 v[7];
} CamPathKeyPosLookRaw; // size = 0xE

typedef struct CamPathKeyPosRaw {
    /* 0x00 */ s16 v[4];
} CamPathKeyPosRaw; // size = 0x8

typedef struct CamPathHeadRaw {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 pad2;
    /* 0x04 */ CamPathSeg *unk4;
} CamPathHeadRaw; // size = 0x8

typedef struct CamPathStepListLoad {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 pad2;
    /* 0x4 */ s16 *unk4;
    /* 0x8 */ s16 *unk8;
} CamPathStepListLoad; // size = 0xC

typedef struct CamPathLoad {
    /* 0x00 */ CamPathHeadRaw heads[24];
    /* 0xC0 */ s16 unkC0;
    /* 0xC2 */ s16 padC2;
    /* 0xC4 */ CamPathZoneRaw *unkC4;
    /* 0xC8 */ s8 *unkC8;
    /* 0xCC */ s16 unkCC;
    /* 0xCE */ s16 padCE;
    /* 0xD0 */ CamPathStepListLoad *unkD0;
    /* 0xD4 */ s16 unkD4;
    /* 0xD6 */ s16 padD6;
    /* 0xD8 */ CamPathPoint *unkD8;
} CamPathLoad;

void *heapAlloc(s32);
void heapClearBlock(void *);
void camCopyVec3s(s16 *, s16 *);

#define CAM_LOAD_SRC ((s16 *)arg0)
#define CAM_LOAD_PATH ((CamPathLoad *)arg1)

void camLoadPathData(arg0, arg1, arg2) void *arg0; CamPathData *arg1; volatile u8 arg2; {
    s16 i;
    s16 j;
    s16 cnt;
    s16 *hdr;
    u8 *data;
    CamPathHeadRaw *h;
    CamPathSeg *dst;
    CamPathPoint *pt;
    s16 *s;
    u8 *rd;
    s32 padf1;
    s32 padf2;
    s32 padf3;
    s32 padf4;
    s32 padf5;
    CamPathSeg buf;
    CamPathPointSpline *u;
    s16 m;
    s16 k;
    s32 padg1;
    s32 padg2;
    s16 *zp;
    s32 skip;

    hdr = CAM_LOAD_SRC;
    data = arg0 != NULL ? (u8 *)arg0 + 0x30 : NULL;
    for (i = 0; i < 0x18; i++) {
        h = &CAM_LOAD_PATH->heads[i];
        cnt = h->unk0 = hdr != NULL ? *hdr++ : 0;
        if (arg2 != 0) {
            h->unk4 = heapAlloc(cnt * 0x12U);
            for (j = 0; j < cnt; j++) {
                dst = &h->unk4[j];
                buf = *(CamPathSeg *)data;
                data += 0x12;
                camCopyVec3s(dst->a, buf.a);
                camCopyVec3s(dst->c, buf.c);
                camCopyVec3s(dst->b, buf.b);
            }
        }
    }
    hdr = (s16 *)data;
    cnt = CAM_LOAD_PATH->unkC0 = hdr != NULL ? *hdr++ : 0;
    if (arg2 != 0) {
        CAM_LOAD_PATH->unkC8 = heapAlloc((u32)cnt);
        CAM_LOAD_PATH->unkC4 = heapAlloc(cnt * 0x1CU);
        zp = hdr;
        for (i = 0; i < cnt; i++) {
            CAM_LOAD_PATH->unkC8[i] = mapChunkFindByPosition(zp[8], zp[9], zp[10], 0);
            zp += 0xE;
            CAM_LOAD_PATH->unkC4[i] = *(CamPathZoneRaw *)(zp - 0xE);
        }
        hdr = zp;
    }
    i = 0;
    cnt = CAM_LOAD_PATH->unkCC = hdr != NULL ? *hdr++ : 0;
    CAM_LOAD_PATH->unkD0 = heapAlloc(cnt * 0xCU);
    for (i = 0; i < cnt; i++) {
        m = *hdr++;
        k = m;

        CAM_LOAD_PATH->unkD0[i].unk0 = m;
        k = k;  // FAKE: steers uopt register order
        CAM_LOAD_PATH->unkD0[i].unk4 = heapAlloc(m * 2);
        CAM_LOAD_PATH->unkD0[i].unk8 = heapAlloc(m * 2);
        for (j = 0; j < k; j++) {
            CAM_LOAD_PATH->unkD0[i].unk4[j] = *hdr++;
            CAM_LOAD_PATH->unkD0[i].unk8[j] = *hdr++;
        }
    }
    i = 0;
    cnt = CAM_LOAD_PATH->unkD4 = hdr != NULL ? *hdr++ : 0;
    CAM_LOAD_PATH->unkD8 = heapAlloc(0x6400);
    heapClearBlock(CAM_LOAD_PATH->unkD8);
    rd = (u8 *)hdr;
    if (cnt != 0) {
        do {
            skip = 0;
            u = (CamPathPointSpline *)&CAM_LOAD_PATH->unkD8[i].u;
            CAM_LOAD_PATH->unkD8[i].unk1 = rd[1];
            CAM_LOAD_PATH->unkD8[i].unk0 = rd[0];
            switch (CAM_LOAD_PATH->unkD8[i].unk1) {
                case 13:
                    rd = camCopyPathPayload(rd, u, 0xC);
                    break;
                case 12:
                    rd = camCopyPathPayload(rd, u, 2);
                    break;
                case 10:
                case 15:
                case 16:
                    rd = camCopyPathPayload(rd, u, 0xE);
                    break;
                case 1:
                    rd = camCopyPathPayload(rd, u, 6);
                    break;
                case 2:
                    rd = camCopyPathPayload(rd, u, 8);
                    break;
                case 3:
                    rd = camCopyPathPayload(rd, u, 0xC);
                    break;
                case 4:
                    s = (s16 *)(rd + 0x20);
                    j = 0;
                    u->unk0 = *(s16 *)(rd + 4);
                    u->unk4 = heapAlloc(u->unk0 * 0xEU);
                    for (; j < u->unk0; j++) {
                        ((CamPathKeyPosLookRaw *)u->unk4)[j] = *(CamPathKeyPosLookRaw *)s;
                        s += 7;
                    }
                    rd = (u8 *)s;
                    break;
                case 5:
                    s = (s16 *)(rd + 0x14);
                    j = 0;
                    u->unk0 = *(s16 *)(rd + 4);
                    u->unk4 = heapAlloc(u->unk0 * 8U);
                    for (; j < u->unk0; j++) {
                        ((CamPathKeyPosRaw *)u->unk4)[j] = *(CamPathKeyPosRaw *)s;
                        s += 4;
                    }
                    rd = (u8 *)s;
                    break;
                default:
                    rd = camCopyPathPayload(rd, u, 0);
                    skip = 1;
                    break;
            }
            if (skip == 0) {
                cnt--;
            }
            i++;
        } while (cnt != 0);
    }
}

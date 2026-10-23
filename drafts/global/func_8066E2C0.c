// func_8066E2C0 (src/global/70FD0.c): Closest diff 25 insns: frame 0x98, all loops and logic matched, inner register allocation diffs in Part 3 and Part 4
#include "common.h"
#include "actor.h"

typedef struct M70N_ModelNode {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ u8 pad10[0x20 - 0x10];
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ u8 unk26;
    /* 0x27 */ u8 unk27;
    /* 0x28 */ struct M70N_ModelNode *next;
} M70N_ModelNode;

typedef struct M70N_ModelSubNode {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ u8 padC[0xC];
    /* 0x18 */ s32 unk18;
    /* 0x1C */ struct M70N_ModelSubNode *next;
} M70N_ModelSubNode;

typedef struct M70N_Sub140Item2C {
    /* 0x00 */ f32 v[3][3];
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ u8 unk2A;
    /* 0x2B */ u8 pad2B;
} M70N_Sub140Item2C;

typedef struct M70N_Sub140Item58 {
    /* 0x00 */ f32 v[3][3];
    /* 0x24 */ u8 pad24[0x48 - 0x24];
    /* 0x48 */ s32 unk48;
    /* 0x4C */ s32 unk4C;
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s16 unk54;
    /* 0x56 */ u8 unk56;
    /* 0x57 */ u8 pad57;
} M70N_Sub140Item58;

ActorSub140 *func_8066E72C(f32, f32, f32, f32, f32, f32, s32, s32, s32);

ActorSub140 *func_8066E2C0(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6, s32 arg7, s32 arg8, u8 *arg9) {
    register ActorSub140 *sub140;
    register void *s2;
    register s32 s3;
    register s32 i;
    register s32 one;
    s32 pad[11];
    void *sp54;
    s32 pad50;
    void *sp4C;
    s32 pad48;
    u8 *a3;
    M70N_ModelNode *node;
    M70N_ModelSubNode *subnode;

    sub140 = func_8066E72C(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
    if (arg9 != NULL) {
        s3 = *(s32 *)arg9;
        arg9 += 4;
        s2 = &sub140->unk8C;
        i = 0;
        if (s3 > 0) {
            one = 1;
            do {
                node = (M70N_ModelNode *)func_80610FE8(sizeof(M70N_ModelNode));
                node->next = NULL;
                node->unk0 = *(f32 *)arg9;
                node->unk4 = *((f32 *)arg9 + 1);
                node->unk8 = *((f32 *)arg9 + 2);
                node->unkC = *((f32 *)arg9 + 3);
                node->unk20 = *((s32 *)arg9 + 4);
                node->unk26 = one;
                node->unk24 = 0;
                node->unk27 = 0;
                arg9 += 0x14;
                *(void **)s2 = node;
                s2 = &node->next;
                i++;
            } while (i != s3);
            i = 0;
        }

        s3 = *(s32 *)arg9;
        one = 1;
        arg9 += 4;
        if (s3 > 0) {
            s2 = &sub140->unk90;
            do {
                subnode = (M70N_ModelSubNode *)func_80610FE8(sizeof(M70N_ModelSubNode));
                subnode->next = NULL;
                subnode->unk0 = *(f32 *)arg9;
                subnode->unk4 = *((f32 *)arg9 + 1);
                subnode->unk8 = *((f32 *)arg9 + 2);
                subnode->unk18 = *((s32 *)arg9 + 3);
                arg9 += 0x10;
                *(void **)s2 = subnode;
                s2 = &subnode->next;
                i++;
            } while (i != s3);
            i = 0;
        }

        s2 = (void *)*(s32 *)arg9;
        arg9 += 4;
        sub140->unk9C = (s32)s2;
        if (s2 != NULL) {
            sub140->unkA0 = func_80610FE8((s32)s2 * sizeof(M70N_Sub140Item2C));
            sub140->unkA4 = (s32)func_80610FE8((s32)s2 * sizeof(M70N_Sub140Item58));
            sub140->unkA8 = sub140->unkA4;
            sp4C = sub140->unkA0;
        }
        if ((s32)s2 > 0) {
            a3 = (u8 *)sp4C;
            do {
                f32 *src = (f32 *)arg9;
                s32 k = 0;
                s32 j = 0;
                f32 *dst = (f32 *)a3;
                u8 *t0 = arg9;
                do {
                    *dst++ = src[0];
                    j++;
                    k += 3;
                    src += 3;
                    dst[2] = src[-2];
                    dst[5] = src[-1];
                } while (j != 3);
                *(s16 *)(a3 + 0x28) = *(s32 *)(t0 + (k * 4));
                *(s32 *)(a3 + 0x24) = *(s32 *)(t0 + ((k + 1) * 4));
                *(u8 *)(a3 + 0x2A) = one;
                arg9 += 0x2C;
                a3 += 0x2C;
            } while (++i != (s32)s2);
            i = 0;
        }

        s2 = (void *)*(s32 *)arg9;
        arg9 += 4;
        sub140->unk94 = (s32)s2;
        if (s2 != NULL) {
            sub140->unk98 = func_80610FE8((s32)s2 * sizeof(M70N_Sub140Item58));
            sp54 = sub140->unk98;
        }
        if ((s32)s2 > 0) {
            a3 = (u8 *)sp54;
            do {
                f32 *src = (f32 *)arg9;
                s32 k = 0;
                s32 j = 0;
                f32 *dst = (f32 *)a3;
                u8 *t0 = arg9;
                do {
                    *dst++ = src[0];
                    j++;
                    k += 3;
                    src += 3;
                    dst[2] = src[-2];
                    dst[5] = src[-1];
                } while (j != 3);
                *(s16 *)(a3 + 0x54) = *(s32 *)(t0 + (k * 4));
                *(s32 *)(a3 + 0x48) = *(s32 *)(t0 + ((k + 1) * 4));
                *(s32 *)(a3 + 0x4C) = *(s32 *)(t0 + ((k + 2) * 4));
                *(s32 *)(a3 + 0x50) = *(s32 *)(t0 + ((k + 3) * 4));
                *(u8 *)(a3 + 0x56) = one;
                arg9 += 0x34;
                a3 += 0x58;
            } while (++i != (s32)s2);
        }
    }
    return sub140;
}

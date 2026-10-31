// func_8066E2C0 (src/global/70FD0.c): stage 4, 20-line text diff once actorSub140Alloc returns ActorSub140* (plain jal); only copy-loop reg roles (target src=v0,k=v1,j=a0,dst=a1). pure-index loop gives natural IVs but dst=v0,src=v1,k=a1
typedef struct ActorSphereNodeSrc {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ u8 pad10[0x20 - 0x10];
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ u8 unk26;
    /* 0x27 */ u8 unk27;
    /* 0x28 */ struct ActorSphereNodeSrc *next;
} ActorSphereNodeSrc;

typedef struct ActorPointNode {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ u8 padC[0xC];
    /* 0x18 */ s32 unk18;
    /* 0x1C */ struct ActorPointNode *next;
} ActorPointNode;

typedef ActorSub140 *(*ActorSub140AllocFn)(f32, f32, f32, f32, f32, f32, s32, s32, s32);

ActorSub140 *func_8066E2C0(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6, s32 arg7, s32 arg8, u8 *arg9) {
    register ActorSub140 *sub140;
    register void *s2;
    register s32 s3;
    register s32 i;
    register s32 one;
    s32 pad[10];
    void *tmp;
    void *sp54;
    s32 pad50;
    u8 *a3;
    ActorSphereNodeSrc *node;
    ActorPointNode *subnode;

    sub140 = ((ActorSub140AllocFn)actorSub140Alloc)(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
    if (arg9 != NULL) {
        s3 = *(s32 *)arg9;
        arg9 += 4;
        s2 = &sub140->unk8C;
        i = 0;
        if (s3 > 0) {
            one = 1;
            do {
                node = (ActorSphereNodeSrc *)heapAlloc(sizeof(ActorSphereNodeSrc));
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
                subnode = (ActorPointNode *)heapAlloc(sizeof(ActorPointNode));
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
            sub140->unkA0 = (a3 = heapAlloc((s32)s2 * sizeof(ActorSub140SrcTri)));
            sub140->unkA4 = (s32)heapAlloc((s32)s2 * sizeof(ActorSub140Tri));
            sub140->unkA8 = sub140->unkA4;
        }
        if ((s32)s2 > 0) {
            do {
                s32 k = 0;
                f32 *t0 = (f32 *)arg9;
                s32 j = 0;
                f32 *src = (f32 *)arg9;
                f32 *dst = (f32 *)a3;
                do {
                    *dst++ = src[0];
                    j++;
                    k += 3;
                    src += 3;
                    dst[2] = src[-2];
                    dst[5] = src[-1];
                } while (j != 3);
                *(s16 *)(a3 + 0x28) = *(s32 *)(t0 + k);
                *(s32 *)(a3 + 0x24) = *(s32 *)(t0 + (k + 1));
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
            tmp = heapAlloc((s32)s2 * sizeof(ActorSub140Tri));
            sub140->unk98 = tmp;
            sp54 = tmp;
        }
        if ((s32)s2 > 0) {
            a3 = (u8 *)sp54;
            do {
                s32 k = 0;
                f32 *t0 = (f32 *)arg9;
                s32 j = 0;
                f32 *src = (f32 *)arg9;
                f32 *dst = (f32 *)a3;
                do {
                    *dst++ = src[0];
                    j++;
                    k += 3;
                    src += 3;
                    dst[2] = src[-2];
                    dst[5] = src[-1];
                } while (j != 3);
                *(s16 *)(a3 + 0x54) = *(s32 *)(t0 + k);
                *(s32 *)(a3 + 0x48) = *(s32 *)(t0 + (k + 1));
                *(s32 *)(a3 + 0x4C) = *(s32 *)(t0 + (k + 2));
                *(s32 *)(a3 + 0x50) = *(s32 *)(t0 + (k + 3));
                *(u8 *)(a3 + 0x56) = one;
                arg9 += 0x34;
                a3 += 0x58;
            } while (++i != (s32)s2);
        }
    }
    return sub140;
}

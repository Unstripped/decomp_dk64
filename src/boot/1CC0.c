#include "common.h"

struct huft {
    u8 e;
    u8 b;
    union {
        u16 n;
        struct huft *t;
    } v;
};

extern struct huft *huftPool;
extern u32 bb;
extern u32 bk;
extern u32 hufts;
extern u8 *inbuf;
extern u8 *slide;
extern u32 inptr;
extern u32 outcnt;

extern u8 border[];
extern u8 D_8000EDF3;
extern u16 cplens[];
extern u8 cplext[];
extern u16 cpdist[];
extern u8 cpdext[];
extern u16 mask_bits[];
extern int lbits;
extern int dbits;

#define NEEDBITS(n)                                      \
    while (k < (n)) {                                    \
        b |= ((u32)inbuf[inptr++]) << k;       \
        k += 8;                                          \
    }
#define DUMPBITS(n) \
    b >>= (n);      \
    k -= (n);

int huft_build(u32 *b, u32 n, u32 s, u16 *d, u8 *e, struct huft **t, int *m) {
    u32 a;
    u32 c[17];
    u32 f;
    int g;
    int h;
    u32 i;
    u32 j;
    int k;
    int l;
    u32 *p;
    struct huft *q;
    struct huft r;
    struct huft *u[16];
    u32 v[288];
    int w;
    u32 x[17];
    u32 *xp;
    int y;
    u32 z;

    bzero(c, sizeof(c));
    p = b;
    i = n;
    do {
        c[*p]++;
        p++;
    } while (--i);
    if (c[0] == n) {
        *t = NULL;
        *m = 0;
        return 0;
    }

    l = *m;
    for (j = 1; j <= 16; j++) {
        if (c[j]) {
            break;
        }
    }
    k = j;
    if ((u32)l < j) {
        l = j;
    }
    for (i = 16; i; i--) {
        if (c[i]) {
            break;
        }
    }
    g = i;
    if ((u32)l > i) {
        l = i;
    }
    *m = l;

    for (y = 1 << j; j < i; j++, y <<= 1) {
        y -= c[j];
    }
    y -= c[i];
    c[i] += y;

    x[1] = j = 0;
    p = c + 1;
    xp = x + 2;
    while (--i) {
        *xp++ = (j += *p++);
    }

    p = b;
    i = 0;
    do {
        if ((j = *p++) != 0) {
            v[x[j]++] = i;
        }
    } while (++i < n);

    x[0] = i = 0;
    p = v;
    h = -1;
    w = -l;
    u[0] = NULL;
    q = NULL;
    z = 0;

    for (; k <= g; k++) {
        a = c[k];
        while (a--) {
            while (k > w + l) {
                h++;
                w += l;

                z = (z = g - w) > (u32)l ? l : z;
                if ((f = 1 << (j = k - w)) > a + 1) {
                    f -= a + 1;
                    xp = c + k;
                    while (++j < z) {
                        if ((f <<= 1) <= *++xp) {
                            break;
                        }
                        f -= *xp;
                    }
                }
                z = 1 << j;

                q = huftPool + hufts;
                hufts += z + 1;
                *t = q + 1;
                *(t = &q->v.t) = NULL;
                u[h] = ++q;

                if (h) {
                    x[h] = i;
                    r.b = l;
                    r.e = 16 + j;
                    r.v.t = q;
                    j = i >> (w - l);
                    u[h - 1][j] = r;
                }
            }

            r.b = k - w;
            if (p >= v + n) {
                r.e = 99;
            } else if (*p < s) {
                r.e = *p < 256 ? 16 : 15;
                r.v.n = *p;
                p++;
            } else {
                r.e = e[*p - s];
                r.v.n = d[*p++ - s];
            }

            f = 1 << (k - w);
            for (j = i >> w; j < z; j += f) {
                q[j] = r;
            }

            for (j = 1 << (k - 1); i & j; j >>= 1) {
                i ^= j;
            }
            i ^= j;

            while ((i & ((1 << w) - 1)) != x[h]) {
                h--;
                w -= l;
            }
        }
    }

    return y != 0 && g != 1;
}

int inflate_codes(struct huft *tl, struct huft *td, int bl, int bd) {
    u32 e;
    u32 n;
    u32 d;
    u32 w;
    u32 k;
    u32 b;
    u32 ml;
    u32 md;
    struct huft *t;

    b = bb;
    k = bk;
    w = outcnt;
    ml = mask_bits[bl];
    md = mask_bits[bd];
    for (;;) {
        NEEDBITS((u32)bl)
        if ((e = (t = tl + ((u32)b & ml))->e) > 16) {
            do {
                e -= 16;
                DUMPBITS(t->b)
                NEEDBITS(e)
            } while ((e = (t = t->v.t + ((u32)b & mask_bits[e]))->e) > 16);
        }
        DUMPBITS(t->b)
        if (e == 16) {
            slide[w++] = t->v.n;
        } else {
            if (e == 15) {
                break;
            }
            NEEDBITS(e)
            n = t->v.n + ((u32)b & mask_bits[e]);
            DUMPBITS(e)
            NEEDBITS((u32)bd)
            if ((e = (t = td + ((u32)b & md))->e) > 16) {
                do {
                    e -= 16;
                    DUMPBITS(t->b)
                    NEEDBITS(e)
                } while ((e = (t = t->v.t + ((u32)b & mask_bits[e]))->e) > 16);
            }
            DUMPBITS(t->b)
            NEEDBITS(e)
            d = w - t->v.n - ((u32)b & mask_bits[e]);
            DUMPBITS(e)
            do {
                e = n;
                n = 0;
                do {
                    slide[w++] = slide[d++];
                } while (--e);
            } while (n);
        }
    }
    outcnt = w;
    bb = b;
    bk = k;
    return 0;
}

int inflate_stored(void) {
    u32 n;
    u32 w;
    u32 k;
    u32 b;

    b = bb;
    k = bk;
    w = outcnt;

    n = k & 7;
    DUMPBITS(n)

    NEEDBITS(16)
    n = b & 0xFFFF;
    DUMPBITS(16)
    NEEDBITS(16)
    DUMPBITS(16)

    while (n--) {
        NEEDBITS(8)
        slide[w++] = b;
        DUMPBITS(8)
    }

    outcnt = w;
    bb = b;
    bk = k;
    return 0;
}

int inflate_fixed(void) {
    int i;
    struct huft *tl;
    struct huft *td;
    int bl;
    int bd;
    u32 l[288];

    for (i = 0; i < 144; i++) {
        l[i] = 8;
    }
    for (; i < 256; i++) {
        l[i] = 9;
    }
    for (; i < 280; i++) {
        l[i] = 7;
    }
    for (; i < 288; i++) {
        l[i] = 8;
    }
    bl = 7;
    huft_build(l, 288, 257, cplens, cplext, &tl, &bl);

    for (i = 0; i < 30; i++) {
        l[i] = 5;
    }
    bd = 5;
    huft_build(l, 30, 0, cpdist, cpdext, &td, &bd);

    inflate_codes(tl, td, bl, bd);
    return 0;
}

int inflate_dynamic(void) {
    int i;
    u32 j;
    u32 l;
    u32 m;
    u32 n;
    struct huft *tl;
    struct huft *td;
    int bl;
    int bd;
    u32 nb;
    u32 nl;
    u32 nd;
    u32 k;
    u32 b;
    u32 ll[316];

    b = bb;
    k = bk;

    NEEDBITS(5)
    nl = 257 + ((u32)b & 0x1F);
    DUMPBITS(5)
    NEEDBITS(5)
    nd = 1 + ((u32)b & 0x1F);
    DUMPBITS(5)
    NEEDBITS(4)
    nb = 4 + ((u32)b & 0xF);
    DUMPBITS(4)

    for (j = 0; j < nb; j++) {
        NEEDBITS(3)
        ll[border[j]] = (u32)b & 7;
        DUMPBITS(3)
    }
    /* border + 19 is reached through the splat label D_8000EDF3 */
    if (j < 19) {
        do {
            ll[border[j]] = 0;
            j++;
        } while (&border[j] < &D_8000EDF3);
    }

    bl = 7;
    huft_build(ll, 19, 19, NULL, NULL, &tl, &bl);

    n = nl + nd;
    m = mask_bits[bl];
    i = l = 0;
    while ((u32)i < n) {
        NEEDBITS((u32)bl)
        td = tl + ((u32)b & m);
        j = td->b;
        DUMPBITS(j)
        j = td->v.n;
        if (j < 16) {
            ll[i++] = l = j;
        } else if (j == 16) {
            NEEDBITS(2)
            j = 3 + ((u32)b & 3);
            DUMPBITS(2)
            while (j--) {
                ll[i++] = l;
            }
        } else if (j == 17) {
            NEEDBITS(3)
            j = 3 + ((u32)b & 7);
            DUMPBITS(3)
            while (j--) {
                ll[i++] = 0;
            }
            l = 0;
        } else {
            NEEDBITS(7)
            j = 11 + ((u32)b & 0x7F);
            DUMPBITS(7)
            while (j--) {
                ll[i++] = 0;
            }
            l = 0;
        }
    }

    bb = b;
    bk = k;

    bl = lbits;
    huft_build(ll, nl, 257, cplens, cplext, &tl, &bl);
    bd = dbits;
    huft_build(ll + nl, nd, 0, cpdist, cpdext, &td, &bd);

    inflate_codes(tl, td, bl, bd);
    return 0;
}

int inflate_block(int *e) {
    u32 t;
    u32 b;
    u32 k;

    b = bb;
    k = bk;

    NEEDBITS(1)
    *e = (int)b & 1;
    DUMPBITS(1)

    NEEDBITS(2)
    t = (u32)b & 3;
    DUMPBITS(2)

    bb = b;
    bk = k;

    if (t == 2) {
        return inflate_dynamic();
    }
    if (t == 0) {
        return inflate_stored();
    }
    if (t == 1) {
        return inflate_fixed();
    }
    return 2;
}

int inflate(void) {
    int e;
    int r;
    u32 h;

    outcnt = 0;
    bk = 0;
    bb = 0;

    h = 0;
    do {
        hufts = 0;
        if ((r = inflate_block(&e)) != 0) {
            return r;
        }
        if (h < hufts) {
            h = hufts;
        }
    } while (!e);

    while (bk >= 8) {
        bk -= 8;
        inptr--;
    }
    inptr += 8;

    return 0;
}

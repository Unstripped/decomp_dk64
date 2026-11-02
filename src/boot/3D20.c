#include "common.h"
#include "compiler/ido/stdarg.h"

unsigned long long __ull_div(unsigned long long, unsigned long long);
unsigned long long __ull_rem(unsigned long long, unsigned long long);
int vsprintf(unsigned char *buf, const unsigned char *fmt, va_list ap);

unsigned char digitsLower[] = "0123456789abcdefghijklmnopqrstuvwxyz";
unsigned char digitsUpper[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

unsigned char *_itoa(unsigned long long val, unsigned char *end, unsigned int base, int upper) {
    unsigned char *table;
    unsigned char *p;

    if (upper != 0) {
        table = digitsUpper;
    } else {
        table = digitsLower;
    }
    p = end;
    while (val > 0) {
        p--;
        *p = table[val % base];
        val /= base;
    }
    return p;
}

int _sprintf(unsigned char *buf, const unsigned char *fmt, ...) {
    va_list ap;

    va_start(ap, fmt);
    return vsprintf(buf, fmt, ap);
}

#ifdef NON_MATCHING
unsigned int strlen(unsigned char *s);

int vsprintf(unsigned char *buf, const unsigned char *fmt, va_list ap) {
    const unsigned char *f;
    int elen;
    int count;
    unsigned char neg;
    unsigned char ll;
    unsigned char plus;
    unsigned char sh;
    unsigned char space;
    unsigned char alt;
    unsigned char fneg;
    unsigned char pad;
    int width;
    int prec;
    unsigned char minus;
    unsigned char conv;
    int base;
    unsigned int d;
    unsigned long long uv;
    long long sv;
    unsigned char *p;
    unsigned char nbuf[0x80];
    unsigned char *end;
    double fv;
    unsigned short lg;
    double scale;
    double fscale;
    union {
        double d;
        char b;
    } value;
    unsigned int len;
    int exp;
    double rnd;
    int c;
    int i;
    int fillx[12]; // FAKE: frame pad (original locals unknown; keeps frame 440 and the base spill at 404)
    double tmp;
    int nd;

    f = fmt;
    count = 0;
    while (*f != 0) {
        c = *f;
        if (*f != '%') {
            while (*f != '%' && *f != 0) {
                count++;
                *buf++ = *f;
                f++;
                c = *f;
            }
        } else {
            c = *++f;
            if (c == '%') {
                count++;
                *buf++ = '%';
                c = *++f;
            } else {
                alt = 0;
                minus = 0;
                plus = 0;
                space = 0;
                pad = ' ';
                width = 0;
                prec = -1;
                ll = 0;
                lg = 0;
                sh = 0;
                while (c == ' ' || c == '+' || c == '-' || c == '#' || c == '0') {
                    f++;
                    switch (c) {
                    case ' ':
                        space = 1;
                        break;
                    case '+':
                        plus = 1;
                        break;
                    case '-':
                        minus = 1;
                        break;
                    case '#':
                        alt = 1;
                        break;
                    case '0':
                        pad = '0';
                        break;
                    }
                    c = *f;
                }
                if (minus) {
                    pad = ' ';
                }
                if (c == '*') {
                    width = va_arg(ap, int);
                    if (width < 0) {
                        width = -width;
                        minus = 1;
                    }
                    c = *++f;
                } else {
                    while (c >= '0' && c <= '9') {
                        width = width * 10 + c - '0';
                        c = *++f;
                    }
                }
                if (c == '.') {
                    c = *++f;
                    if (c == '*') {
                        prec = va_arg(ap, int);
                        if (prec < 0) {
                            prec = -1;
                        }
                        c = *++f;
                    } else if (c >= '0' && c <= '9') {
                        prec = 0;
                        while (c >= '0' && c <= '9') {
                            prec = prec * 10 + c - '0';
                            c = *++f;
                        }
                    }
                }
                while (c == 'h' || c == 'l' || c == 'L' || c == 'Z' || c == 'q') {
                    f++;
                    switch (c) {
                    case 'h':
                        sh = 1;
                        break;
                    case 'l':
                        if (lg) {
                            ll = 1;
                        } else {
                            lg = 1;
                        }
                        break;
                    case 'L':
                        ll = 1;
                        break;
                    case 'Z':
                        lg = 1;
                        break;
                    case 'q':
                        ll = 1;
                        break;
                    }
                    c = *f;
                }
                conv = *f;
                f++;
                switch (conv) {
                case 'd':
                case 'i':
                    base = 10;
                    end = &nbuf[0x7F];
                    if (ll) {
                        sv = va_arg(ap, long long);
                    } else if (lg) {
                        sv = va_arg(ap, int);
                    } else if (!sh) {
                        sv = va_arg(ap, int);
                    } else {
                        sv = (short)va_arg(ap, int);
                    }
                    neg = sv < 0;
                    if (neg) {
                        uv = -sv;
                    } else {
                        uv = sv;
                    }
                    goto numout;
                case 'u':
                    base = 10;
                    plus = 0;
                    space = 0;
                    neg = 0;
                    end = &nbuf[0x7F];
                    goto ufetch;
                case 'o':
                    base = 8;
                    plus = 0;
                    space = 0;
                    neg = 0;
                    end = &nbuf[0x7F];
                    goto ufetch;
                case 'x':
                case 'X':
                    base = 16;
                    plus = 0;
                    space = 0;
                    neg = 0;
                    end = &nbuf[0x7F];
                ufetch:
                    if (ll) {
                        uv = va_arg(ap, unsigned long long);
                    } else if (lg) {
                        uv = va_arg(ap, unsigned int);
                    } else if (!sh) {
                        uv = va_arg(ap, unsigned int);
                    } else {
                        uv = (unsigned short)va_arg(ap, unsigned int);
                    }
                numout:
                    if (prec >= 0) {
                        pad = ' ';
                    }
                    if (prec == -1) {
                        prec = 1;
                    }
                    p = _itoa(uv, &nbuf[0x80], base, conv == 'X') - 1;
                    nd = end - p;
                    width -= nd;
                    prec -= nd;
                    if (alt && base == 8 && prec <= 0) {
                        *p-- = '0';
                        width--;
                    }
                    if (prec > 0) {
                        width -= prec;
                        while (prec-- > 0) {
                            *p-- = '0';
                        }
                    }
                    p++;
                    if (alt && base == 16) {
                        width -= 2;
                    }
                    if (neg || plus || space) {
                        width--;
                    }
                    if (!minus && pad == ' ') {
                        for (; width-- > 0;) {
                            count++;
                            *buf++ = ' ';
                        }
                    }
                    if (neg) {
                        count++;
                        *buf++ = '-';
                    } else if (plus) {
                        count++;
                        *buf++ = '+';
                    } else if (space) {
                        count++;
                        *buf++ = ' ';
                    }
                    if (alt && base == 16) {
                        *buf++ = '0';
                        count += 2;
                        *buf++ = conv;
                    }
                    if (!minus && pad == '0') {
                        for (; width-- > 0;) {
                            count++;
                            *buf++ = '0';
                        }
                    }
                    while (p <= end) {
                        count++;
                        *buf++ = *p++;
                    }
                    if (minus) {
                        for (; width-- > 0;) {
                            count++;
                            *buf++ = ' ';
                        }
                    }
                    c = *f;
                    break;
                case 'e':
                case 'E':
                    fneg = 0;
                    if (prec < 0) {
                        prec = 6;
                    }
                    if (sh) {
                        value.d = va_arg(ap, float);
                    } else {
                        value.d = va_arg(ap, double);
                    }
                    if (value.b < 0) {
                        fneg = 1;
                        value.d = -value.d;
                    }
                    if (value.d == 0.0) {
                        exp = 0;
                        scale = 1.0;
                    } else if (value.d < 1.0) {
                        exp = 0;
                        scale = 1.0;
                        while (value.d < scale) {
                            scale /= 10.0;
                            exp--;
                        }
                    }
                    if (value.d >= 1.0) {
                        exp = 0;
                        scale = 1.0;
                        tmp = 10.0;
                        while (tmp <= value.d) {
                            scale = tmp;
                            tmp *= 10.0;
                            exp++;
                        }
                    }
                    rnd = scale * 0.5;
                    for (i = prec; i > 0; i--) {
                        rnd /= 10.0;
                    }
                    value.d = value.d + rnd;
                    if (scale * 10.0 <= value.d) {
                        scale *= 10.0;
                        exp++;
                    }
                    elen = (fneg || plus || space) + (prec > 0 || alt) + prec + (exp >= 100) + 5;
                    if (!minus && pad == ' ') {
                        for (; elen < width--;) {
                            if (fneg == 0) {}  // FAKE: keeps fneg in a1 (not ra)
                            count++;
                            *buf++ = pad;
                        }
                    }
                    if (fneg) {
                        count++;
                        *buf++ = '-';
                    } else if (plus) {
                        count++;
                        *buf++ = '+';
                    } else if (space) {
                        count++;
                        *buf++ = ' ';
                    }
                    if (!minus && pad == '0') {
                        for (; elen < width--;) {
                            count++;
                            *buf++ = pad;
                        }
                    }
                    d = '0';
                    if (scale <= value.d) {
                        do {
                            if (fneg && fneg) {}  // FAKE: keeps fneg in a1 (not ra)
                            d++;
                            value.d -= scale;
                        } while (scale <= value.d);
                    }
                    count++;
                    *buf++ = d;
                    scale /= 10.0;
                    if (prec > 0 || alt) {
                        count++;
                        *buf++ = '.';
                    }
                    if (prec > 0) {
                        do {
                            d = '0';
                            count++;
                            prec--;
                            if (scale <= value.d) {
                                do {
                                    d++;
                                    value.d -= scale;
                                } while (scale <= value.d);
                            }
                            *buf++ = d;
                            scale /= 10.0;
                        } while (prec > 0);
                    }
                    count++;
                    *buf++ = conv;
                    if (exp < 0) {
                        exp = -exp;
                        *buf++ = '-';
                    } else {
                        if (space && space) {}  // FAKE: steers e-arm colouring
                        *buf++ = '+';
                    }
                    count++;
                    if (conv) {}  // FAKE: steers e-arm colouring
                    if (exp >= 100) {
                        *buf++ = exp / 100 + '0';
                        count++;
                    }
                    *buf++ = exp / 10 % 10 + '0';
                    count += 2;
                    *buf++ = exp % 10 + '0';
                    if (minus) {
                        for (; elen < width--;) {
                            count++;
                            *buf++ = ' ';
                        }
                    }
                    c = *f;
                    break;
                case 'g':
                case 'G':
                    c = *f;
                    break;
                case 'f':
                    rnd = 1.0;
                    fneg = 0;
                    tmp = 10.0;
                    if (prec < 0) {
                        prec = 6;
                    }
                    for (i = 0; i < prec; i++) {
                        rnd /= 10.0;
                    }
                    if (sh) {
                        fv = va_arg(ap, float);
                    } else {
                        fv = va_arg(ap, double);
                        if (sh != 0) {}  // FAKE: steers f-arm colouring
                    }
                    if (fv < 0.0) {
                        fneg = 1;
                        fv = -fv;
                    }
                    fv += rnd * 0.5;
                    nd = 1;
                    fscale = 1.0;
                    while (tmp <= fv) {
                        fscale = tmp;
                        tmp *= 10.0;
                        nd++;
                    }
                    elen = (fneg || plus || space) + (prec > 0 || alt) + nd + prec;
                    if (!minus && pad == ' ') {
                        for (; elen < width--;) {
                            count++;
                            *buf++ = pad;
                        }
                    }
                    if (fneg) {
                        count++;
                        *buf++ = '-';
                    } else if (plus) {
                        count++;
                        *buf++ = '+';
                    } else if (space) {
                        count++;
                        *buf++ = ' ';
                    }
                    if (!minus && pad == '0') {
                        for (; elen < width--;) {
                            count++;
                            *buf++ = pad;
                        }
                    }
                    do {
                        d = '0';
                        if (fscale <= fv) {
                            do {
                                d++;
                                fv -= fscale;
                            } while (fscale <= fv);
                        }
                        count++;
                        *buf++ = d;
                        fscale /= 10.0;
                    } while (fscale >= 1.0);
                    if (prec > 0 || alt) {
                        count++;
                        *buf++ = '.';
                    }
                    if (prec > 0) {
                        do {
                            d = '0';
                            count++;
                            prec--;
                            if (fscale <= fv) {
                                do {
                                    d++;
                                    fv -= fscale;
                                } while (fscale <= fv);
                            }
                            *buf++ = d;
                            fscale /= 10.0;
                        } while (prec > 0);
                    }
                    if (minus) {
                        for (; elen < width--;) {
                            count++;
                            *buf++ = ' ';
                        }
                    }
                    c = *f;
                    break;
                case 'c':
                    uv = va_arg(ap, int);
                    if (!minus) {
                        while (--width > 0) {
                            count++;
                            *buf++ = pad;
                        }
                    }
                    count++;
                    *buf++ = uv;
                    if (minus) {
                        while (--width > 0) {
                            count++;
                            *buf++ = ' ';
                        }
                    }
                    c = *f;
                    break;
                case 's':
                    p = va_arg(ap, unsigned char *);
                    if (p == 0) {
                        if (prec == -1 || prec >= 6) {
                            p = (unsigned char *)"(null)";
                            len = 6;
                        } else {
                            p = (unsigned char *)"";
                            len = 0;
                        }
                    } else {
                        len = strlen(p);
                    }
                    if (prec != -1 && prec < len) {
                        len = prec;
                    }
                    width -= len;
                    if (!minus) {
                        for (; width-- > 0;) {
                            count++;
                            *buf++ = ' ';
                        }
                    }
                    for (; len-- > 0;) {
                        count++;
                        *buf++ = *p++;
                    }
                    if (minus) {
                        for (; width-- > 0;) {
                            count++;
                            *buf++ = ' ';
                        }
                    }
                    c = *f;
                    break;
                case 'p':
                    p = va_arg(ap, unsigned char *);
                    if (p) {
                        conv = 'x';
                        uv = (unsigned int)p;
                        base = 16;
                        alt = 1;
                        neg = 0;
                        end = &nbuf[0x7F];
                        goto numout;
                    } else {
                        unsigned char *s;
                        width -= 5;
                        if (!minus) {
                            for (; width-- > 0;) {
                                count++;
                                *buf++ = ' ';
                            }
                        }
                        for (s = (unsigned char *)"(nil)"; *s != 0; s++) {
                            *buf++ = *s;
                            count++;
                        }
                        if (minus) {
                            for (; width-- > 0;) {
                                count++;
                                *buf++ = ' ';
                            }
                        }
                    }
                    c = *f;
                    break;
                case 'n':
                    if (ll) {
                        *va_arg(ap, long long *) = count;
                    } else if (lg) {
                        *va_arg(ap, int *) = count;
                    } else if (!sh) {
                        *va_arg(ap, int *) = count;
                    } else {
                        *va_arg(ap, short *) = count;
                    }
                    c = *f;
                    break;
                default:
                    c = *f;
                    break;
                }
            }
        }
    }
    *buf = 0;
    return count;
}
#else

#pragma GLOBAL_ASM("asm/nonmatchings/3D20/vsprintf.s")
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/3D20/D_80010360.s")

#pragma GLOBAL_ASM("asm/nonmatchings/3D20/D_80010364.s")

#pragma GLOBAL_ASM("asm/nonmatchings/3D20/D_8001036C.s")

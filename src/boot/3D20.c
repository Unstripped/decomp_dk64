#include "common.h"
#include "compiler/ido/stdarg.h"

unsigned long long __ull_div(unsigned long long, unsigned long long);
unsigned long long __ull_rem(unsigned long long, unsigned long long);
int vsprintf(unsigned char *buf, const unsigned char *fmt, va_list ap);

unsigned char digitsLower[] = "0123456789abcdefghijklmnopqrstuvwxyz";
unsigned char digitsUpper[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

const unsigned char D_80010360[4] = "";
const unsigned char D_80010364[8] = "(null)";
const unsigned char D_8001036C[8] = "(nil)";

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
    int d;
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
    int i2;
    int *q1;
    int fillx[4]; // FAKE: frame pad (original locals unknown; keeps frame 440 and the base spill at 404)
    double tmp;
    double etmp;
    double ernd;
    int nd;
    unsigned char fneg2;
    unsigned char *np;

    count = 0;
    f = fmt;
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
            if ((c ^ 0) == '%') { // FAKE: operand order of the compare
                c = *++f; // LAYOUT: as1 increment order of f/count/buf
                count++;
                *buf++ = '%';
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
                    goto ufetch;
                case 'o':
                    base = 8;
                    plus = 0;
                    space = 0;
                    neg = 0;
                    goto ufetch;
                case 'x':
                case 'X':
                    base = 16;
                    plus = 0;
                    space = 0;
                    neg = 0;
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
                    end = &nbuf[0x7F];
                    if (prec >= 0) {
                        pad = ' ';
                    }
                    if (prec == -1) {
                        prec = 1;
                    }
                    np = _itoa(uv, &nbuf[0x80], base, conv == 'X') - 1;
                    nd = end - np;
                    width -= nd;
                    prec -= nd;
                    if (alt && base == 8 && prec <= 0) {
                        *np-- = '0';
                        width--;
                    }
                    if (prec > 0) {
                        width -= prec;
                        while (prec-- > 0) {
                            *np-- = '0';
                        }
                    }
                    np++;
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
                        for (; width-- > 0;) { count++; *buf++ = '0'; if (width == 0) {} // FAKE: splits the loop body so the '0' const is not hoisted/coloured (ring temp like the original); LAYOUT: one line
                        }
                    }
                    while (np <= end) {
                        count++;
                        *buf++ = *np++;
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
                    fneg2 = 0;
                    if (prec < 0) {
                        prec = 6;
                    }
                    if (sh) {
                        value.d = va_arg(ap, float);
                    } else {
                        value.d = va_arg(ap, double);
                    }
                    if (value.b < 0) {
                        fneg2 = 1;
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
                        etmp = 10.0;
                        while (etmp <= value.d) {
                            scale = etmp;
                            etmp *= 10.0;
                            exp++;
                        }
                    }
                    ernd = scale * 0.5;
                    for (d = prec; d > 0; d--) {
                        ernd /= 10.0;
                    }
                    value.d = value.d + ernd;
                    if (scale * 10.0 <= value.d) {
                        scale *= 10.0;
                        exp++;
                    }
                    elen = (fneg2 || plus || space) + (prec > 0 || alt) + prec + (exp >= 100) + 5;
                    if (!minus && pad == ' ') {
                        for (; elen < width--;) {
                            count++;
                            *buf++ = pad;
                        }
                    }
                    if (fneg2) {
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
                        d = width; // FAKE
                        for (; elen < width--;) {
                            if (pad == 0) {}  // FAKE: steers e-arm colouring
                            count++;
                            *buf++ = pad;
                        }
                        if (d) {} // FAKE
                    }
                    d = '0';
                    if (scale <= value.d) {
                        do {
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
                    if (exp < 0) { exp = -exp; count++; *buf++ = '-'; } else { if (space && space) {} count++; *buf++ = '+'; } // LAYOUT: one-line if/else drops the else .loc; FAKE: dead space test steers the exp/10 hoist
                    if (exp >= 100) {
                        d = exp / 100 + '0';
                        *buf = d;
                        count++;
                        buf++;
                        if (d) {} // FAKE
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
                    for (i2 = 0; i2 < prec; i2++) {
                        rnd /= 10.0;
                    }
                    if (sh) {
                        fv = va_arg(ap, float);
                    } else {
                        fv = va_arg(ap, double);
                    }
                    if (fv < 0.0) {
                        fneg = 1;
                        fv = -fv;
                    }
                    fv += rnd * 0.5;
                    i2 = 1;
                    fscale = 1.0;
                    while (tmp <= fv) {
                        fscale = tmp;
                        tmp *= 10.0;
                        i2++;
                    }
                    elen = (fneg || plus || space) + (prec > 0 || alt) + i2 + prec;
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
                            p = (unsigned char *)D_80010364;
                            len = 6;
                        } else {
                            p = (unsigned char *)D_80010360;
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
                    q1 = va_arg(ap, int *);
                    if (q1) {
                        base = 16;
                        conv = 'x';
                        alt = 1;
                        uv = (unsigned int)q1;
                        neg = 0;
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
                        s = (unsigned char *)D_8001036C;
                        while (*s != 0) {
                            count++;
                            *buf++ = *s;
                            s++;
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
                        q1 = va_arg(ap, int *);
                        *(long long *)q1 = count;
                    } else if (lg) {
                        q1 = va_arg(ap, int *);
                        *q1 = count;
                    } else if (!sh) {
                        q1 = va_arg(ap, int *);
                        *q1 = count;
                    } else {
                        q1 = va_arg(ap, int *);
                        *(short *)q1 = count;
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

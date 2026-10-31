// vsprintf (src/boot/3D20.c): stage 4 (frame 440, same callee-saved set, 1168 vs 1189 insns, 951 exact). Remaining: conv (u8) not colored (target s4 shared with prec>0 temp; mine s2/uncolored -> lbu conv from 410(sp) before _itoa), fneg in ra instead of a1, e/f arm FP temps f12 vs f0, delay-slot sched. Tried: decl-order hill climb, loop forms, c types, scale/tmp/fscale doubles. Parked in copy under NON_MATCHING
unsigned int strlen(unsigned char *s);

int vsprintf(unsigned char *buf, const unsigned char *fmt, va_list ap) {
    const unsigned char *f;
    unsigned short c;
    int count;
    unsigned char minus;
    unsigned char plus;
    unsigned char space;
    unsigned char alt;
    unsigned char ll;
    unsigned char lg;
    unsigned char sh;
    unsigned char pad;
    int width;
    int prec;
    unsigned char fneg;
    unsigned char conv;
    unsigned char neg;
    unsigned char fill1;
    unsigned char fill2;
    unsigned char fill3;
    unsigned char fill4;
    int base;
    unsigned long long uv;
    long long sv;
    unsigned char *p;
    unsigned char nbuf[0x80];
    unsigned char *end;
    double fv;
    double rnd;
    double scale;
    double tmp;
    union {
        double d;
        char b;
    } value;
    unsigned int len;
    int exp;
    double fscale;
    int nd;
    int d;
    int i;
    int elen;
    int sign;
    int dot;
    int fillx[10];

    f = fmt;
    count = 0;
    c = *f;
    while ((unsigned char)c != 0) { // FAKE: no-op narrowing shifts the ugen temp ring by one
        if (c != '%') {
            while (c != '%' && c != 0) {
                count++;
                *buf++ = c;
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
                conv = c;
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
                        *buf++ = conv;
                        count += 2;
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
                    sign = fneg || plus || space;
                    dot = prec > 0 || alt;
                    elen = dot + sign + prec + (exp >= 100) + 5;
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
                    if (exp < 0) {
                        exp = -exp;
                        *buf++ = '-';
                    } else {
                        *buf++ = '+';
                    }
                    count++;
                    if (exp >= 100) {
                        count++;
                        *buf++ = exp / 100 + '0';
                    }
                    *buf++ = exp / 10 % 10 + '0';
                    *buf++ = exp % 10 + '0';
                    count += 2;
                    if (minus) {
                        for (; elen < width--;) {
                            count++;
                            *buf++ = ' ';
                        }
                    }
                    break;
                case 'g':
                case 'G':
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
                    sign = fneg || plus || space;
                    dot = prec > 0 || alt;
                    elen = dot + sign + nd + prec;
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
                    for (; len-- != 0;) {
                        count++;
                        *buf++ = *p++;
                    }
                    if (minus) {
                        for (; width-- > 0;) {
                            count++;
                            *buf++ = ' ';
                        }
                    }
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
                            count++;
                            *buf++ = *s;
                        }
                        if (minus) {
                            for (; width-- > 0;) {
                                count++;
                                *buf++ = ' ';
                            }
                        }
                    }
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
                    break;
                }
                c = *f;
            }
        }
    }
    *buf = 0;
    return count;
}

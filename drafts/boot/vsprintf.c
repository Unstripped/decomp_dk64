// vsprintf (src/boot/3D20.c): stage 4 PARKED, count EXACT (1218 insns + 3 trailing pad nops; nm -S 1221 is the TU-end padding artefact: objdump line counts equal 1289/1289), frame 440, callee-saved set match; deadsweep full 161 -> 80 (shape 29 -> 18). Levers: separate locals per arm (q1 = va_arg ptr of the 'n' and 'p' arms, etmp/ernd e-arm vs tmp/rnd f-arm, i2 = f-arm counter AND nd, base reused as the e-arm rnd-loop counter), fillx pad 12 -> 5 (int i kept unreferenced: removing it changes the frame), 'p' arm store order base,conv,alt,uv,neg,end, count=0 before f=fmt, c=*++f before count++/*buf++='%' with (c ^ 0)==% FAKE, (nil) loop as while{count++; *buf++=*s; s++}, one count++/*buf++ order flip, e-arm FAKEs reduced to 3 dead tests (pad/space/conv). f-arm now exact except fneg a3 vs a1. Remaining: uopt hoists the const def d='0' (li v0,48) to the e-arm entry so v0 is blocked: fneg a1->ra, (fneg!=0) v0->a2, exp>=100 a2->a3, loop temps v0/v1/a0 shift (~60 of 80 lines); numout p web a0/a1 swap (7); zero-pad loop const 48 coloured v0 vs ring t7 + ring t7/t9 for &nbuf[0x7F] (9); 'p' arm ra/b order (2). Tried without effect: typed constants (48U/(uchar)), while vs if+do-while, do{}while(0)/if(1) wrappers, dead stores before d/i2/nd, d/elen/fneg splits, fneg->neg, d typed int/char/loop counter, deadsweep sweep (3162 variants), 8.5k-eval dead-test hill-climbs x3, decl-order moves of every local, count++/*buf++ pair flips, all int/u8 rename-in-region pairs, FAKE variable substitution.
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
    int i2;
    int *q1;
    int fillx[5]; // FAKE: frame pad (original locals unknown; keeps frame 440 and the base spill at 404)
    double tmp;
    double etmp;
    double ernd;
    int nd;

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
                        etmp = 10.0;
                        while (etmp <= value.d) {
                            scale = etmp;
                            etmp *= 10.0;
                            exp++;
                        }
                    }
                    ernd = scale * 0.5;
                    for (base = prec; base > 0; base--) {
                        ernd /= 10.0;
                    }
                    value.d = value.d + ernd;
                    if (scale * 10.0 <= value.d) {
                        scale *= 10.0;
                        exp++;
                    }
                    elen = (fneg || plus || space) + (prec > 0 || alt) + prec + (exp >= 100) + 5;
                    if (!minus && pad == ' ') {
                        for (; elen < width--;) {
                            if (pad == 0) {}  // FAKE: steers e-arm colouring
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
                        if (space && space) {}  // FAKE: steers e-arm colouring
                        *buf++ = '+';
                    }
                    count++;
                    if (conv) {}  // FAKE: steers e-arm colouring
                    if (exp >= 100) {
                        count++;
                        *buf++ = exp / 100 + '0';
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
                    q1 = va_arg(ap, int *);
                    if (q1) {
                        base = 16;
                        conv = 'x';
                        alt = 1;
                        uv = (unsigned int)q1;
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
                        s = (unsigned char *)"(nil)";
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

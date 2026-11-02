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


#pragma GLOBAL_ASM("asm/nonmatchings/3D20/vsprintf.s")

#pragma GLOBAL_ASM("asm/nonmatchings/3D20/D_80010360.s")

#pragma GLOBAL_ASM("asm/nonmatchings/3D20/D_80010364.s")

#pragma GLOBAL_ASM("asm/nonmatchings/3D20/D_8001036C.s")

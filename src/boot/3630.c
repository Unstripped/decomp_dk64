#include "common.h"

extern u8 *strtokSavePtr;

u8 *_strchr(u8 *s, s32 c);
u8 *_strpbrk(u8 *s, u8 *set);
u32 strlen(u8 *s);

u8 *_strcpy(u8 *dst, u8 *src) {
    u8 *ret = dst;

    while ((*dst++ = *src++)) {
    }
    return ret;
}

u8 *_strncpy(u8 *dst, u8 *src, u32 n) {
    u8 *ret = dst;

    while (n-- && (*dst++ = *src++)) {
    }
    if (n == 0) {
        *dst = 0;
    }
    return ret;
}

u8 *_strcat(u8 *dst, u8 *src) {
    u8 *ret = dst;

    while (*dst != 0) {
        dst++;
    }
    while ((*dst++ = *src++)) {
    }
    return ret;
}

s32 _strcasecmp(u8 *a, u8 *b) {
    u8 ca;
    u8 cb;

    while (*a != 0 || *b != 0) {
        ca = *a;
        if (ca >= 0x61 && ca < 0x7B) {
            ca -= 0x20;
        }
        cb = *b;
        if (cb >= 0x61 && cb < 0x7B) {
            cb -= 0x20;
        }
        if (ca < cb) {
            return -1;
        }
        if (cb < ca) {
            return 1;
        }
        a++;
        b++;
    }
    return 0;
}

s32 _strncasecmp(u8 *a, u8 *b, s32 n) {
    u8 ca;
    u8 cb;

    while ((*a != 0 || *b != 0) && n != 0) {
        ca = *a;
        if (ca >= 0x61 && ca < 0x7B) {
            ca -= 0x20;
        }
        cb = *b;
        if (cb >= 0x61 && cb < 0x7B) {
            cb -= 0x20;
        }
        if (ca < cb) {
            return -1;
        }
        if (cb < ca) {
            return 1;
        }
        a++;
        b++;
        n--;
    }
    return 0;
}

u32 _strcspn(u8 *s, u8 *set) {
    u32 n = 0;
    u8 c;

    while (*s != 0) {
        c = *s;
        if (_strchr(set, c) != 0) {
            return n;
        }
        s++;
        n++;
    }
    return n;
}

u32 _strspn(u8 *s, u8 *set) {
    u32 n = 0;
    u8 c;

    while (*s != 0) {
        c = *s;
        if (_strchr(set, c) != 0) {
            s++;
        } else {
            return n;
        }
        n++;
    }
    return n;
}

u8 *_strpbrk(u8 *s, u8 *set) {
    u8 *best = _strchr(s, *set);
    u8 c;
    u8 *p;

    while (*set != 0) {
        c = *set;
        set++;
        p = _strchr(s, c);
        if (p != 0) {
            if (p < best || best == 0) {
                best = p;
            }
        }
    }
    return best;
}

u8 *_strtok(u8 *str, u8 *delim) {
    u8 *token;
    u8 *p;
    u8 *x;

    if (str != 0) {
        strtokSavePtr = str;
    }

    p = strtokSavePtr;
    token = p;

    if (p == 0) {
        return 0;
    }

    p = _strpbrk(p, delim);
    if (p != 0) {
        *p++ = 0;
        x = _strchr(delim, *p);
        strtokSavePtr = p;
        while (x != 0) {
            p++;
            x = _strchr(delim, *p);
        }
        strtokSavePtr = p;
        return token;
    }

    strtokSavePtr = p;
    return token;
}

void *_memset(u8 *dst, s32 c, u32 n) {
    u8 *p = dst;

    while (n-- > 0) {
        *p++ = c;
    }
    return dst;
}

u8 *_strchr(u8 *s, s32 c) {
    if (s == 0) {
        return 0;
    }
    while (*s != 0) {
        if ((u8)c == *s) {
            return s;
        }
        s++;
    }
    return 0;
}

u32 strlen(u8 *s) {
    u32 len = 0;

    if (s == 0) {
        return 0;
    }
    while (*s != 0) {
        len++;
        s++;
    }
    return len;
}

u8 *_strstr(u8 *hay, u8 *needle) {
    s32 len = strlen(needle);
    s32 i = 0;

    if (hay == 0 || needle == 0) {
        return 0;
    }
    while (i < len && *hay != 0) {
        if (hay[i] == needle[i]) {
            i++;
        } else {
            i = 0;
            hay++;
        }
    }
    if (i != len) {
        hay = 0;
    }
    return hay;
}

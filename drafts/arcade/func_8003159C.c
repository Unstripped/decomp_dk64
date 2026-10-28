// func_8003159C (src/arcade/0.c): Stage 6 text-identical, reloc only: all 329 objdump lines equal to expected except string literals reloc as .rodata+off instead of D_8004A840..D_8004A8EC (rodata bytes identical). Needs char buf[0x50] with 'char *p = buf' (permuter find) used for every _sprintf/arcadeDrawString arg, locals order i,g,buf, _sprintf declared s32 _sprintf(s32,const char*,...) so (s32)p CSEs; D_8004A82C = u8[5][3] names, D_8004BCEC = byte at entity0+0x1C.
s32 _sprintf(s32, const char *, ...);
extern u8 D_8004A82C[5][3];
extern u8 D_8004BCEC;

void func_8003159C(Gfx **arg0) {
    s32 i;
    Gfx *g;
    char buf[0x50];
    char *p;

    g = *arg0;
    p = buf;
    if (D_8004C724 == 3) {
        arcadeSetTextColor(0, 0xFF, 0xFF, 0xFF);
        arcadeSetTextPosition(0x78, 0x3B);
        _sprintf((s32)p, "NAME %.3s", D_8004A774);
        arcadeDrawString(&g, (s32)p);
        arcadeSetTextPosition(0xA0, 0x41);
        _sprintf((s32)p, "---");
        arcadeDrawString(&g, (s32)p);
        if (D_8004C6DC < 0x708) {
            arcadeSetTextPosition(0x60, 0x7B);
            _sprintf((s32)p, "REGI TIME <%02d>", 0x1E - D_8004C6DC / 0x3C);
        } else {
            arcadeSetTextPosition(0x40, 0x7B);
            _sprintf((s32)p, "YOUR NAME WAS");
            arcadeDrawString(&g, (s32)p);
            arcadeSetTextPosition(0xB0, 0x7B);
            _sprintf((s32)p, "REGISTERED.");
        }
        arcadeDrawString(&g, (s32)p);
        arcadeSetTextColor(0xFF, 0, 0, 0xFF);
        arcadeSetTextPosition(0x58, 0x2B);
        _sprintf((s32)p, "NAME REGISTRATION");
        arcadeDrawString(&g, (s32)p);
        arcadeSetTextColor(0, 0xFF, 0, 0xFF);
        arcadeSetTextPosition(0x58, 0x4B);
        _sprintf((s32)p, "A B C D E F G H I J");
        arcadeDrawString(&g, (s32)p);
        arcadeSetTextPosition(0x58, 0x5B);
        _sprintf((s32)p, "K L M N O P Q R S T");
        arcadeDrawString(&g, (s32)p);
        arcadeSetTextPosition(0x58, 0x6B);
        _sprintf((s32)p, "U V W X Y Z . -");
        arcadeDrawString(&g, (s32)p);
        arcadeSetTextPosition(0xD4, 0x6B);
        _sprintf((s32)p, "ba");
        arcadeDrawString(&g, (s32)p);
    }
    arcadeSetTextColor(0xFF, 0, 0, 0xFF);
    for (i = 0; i < 5; i++) {
        if (i == 3) {
            arcadeSetTextColor(0xFF, 0xFF, 0, 0xFF);
        }
        arcadeSetTextPosition(0x38, 0x8B + i * 0x10);
        if (i == D_8004BCEC && (D_8004C6DC & 0x20) && D_8004C724 == 3) {
            _sprintf((s32)p, "%.3s", D_8004A82C[i]);
        } else {
            _sprintf((s32)p, "%.3s  %06d  %.3s", D_8004A82C[i], D_8004A74C[i], D_8004A778[i]);
        }
        arcadeDrawString(&g, (s32)p);
    }
    arcadeSetTextColor(0, 0xFF, 0, 0xFF);
    arcadeSetTextPosition(0xB8, 0xDB);
    _sprintf((s32)p, "CREDIT 00");
    arcadeDrawString(&g, (s32)p);
    *arg0 = g;
}

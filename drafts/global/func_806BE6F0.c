// func_806BE6F0 (src/global/C2A90.c): only s0/s1 swap (n vs gdl priority) + flag in a0 vs s0; v sb/lbu spill matches with s32 n, decl order v,buf,n, if(v>=4) n=3 else n=v
s16 func_80609140(s16, s32, f32, f32, u8, u8);
s32 _sprintf(char *, const char *, ...);
s32 func_806FBD5C();
Gfx *func_806FC530(Gfx *, s32, s16, s16, void *, s32);
Gfx *func_8070068C(Gfx *);
s32 func_8070E750(s32, s32, s32);
extern Gfx D_1000118;

Gfx *func_806BE6F0(Gfx *gdl, Actor *arg1) {
    u8 v;
    char buf[3];
    s32 n;

    v = arg1->unk168 / 30;
    if (v) {
        if (v >= 4) {
            n = 3;
        } else {
            n = v;
        }
        _sprintf(buf, "%d", n);
    } else {
        _sprintf(buf, (char *)func_8070E750(0x26, 9, 1));
    }
    if (arg1->unk168 % 30 == 0) {
        if (v != 0) {
            if (v >= 2) {
                n = 0x75;
            } else {
                n = 0x74;
            }
            func_80609140(n, 0x7FFF, 64.0f, 1.0f, 0, 0x80);
        }
    }
    gSPDisplayList(gdl++, &D_1000118);
    gDPPipeSync(gdl++);
    gDPSetCombineMode(gdl++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetPrimColor(gdl++, 0, 0, 255, 255, 255, 255);
    gdl = func_8070068C(gdl);
    gdl = func_806FC530(gdl, 1, (s16)((0x140 - func_806FBD5C(1, buf)) << 1), 0xAA, buf, 1);
    if (arg1->unk168-- == 0) {
        arg1->unk155[0]++;
    }
    return gdl;
}

// func_80027BE8 (src/jetpac/3480.c): stage 5: diff 71 -> 49 lines. 'if (!arg1) {} if (!inner) {}' at the inner-loop top colours arg1 (fp-class s-reg) and keeps inner in a reg; remaining: the &D_8002F3C0 hoist (lui/addiu s8) still beats const 2 (adjsave 0, uncoloured: li at,2 in the i != 2 compare) and the s-reg numbering shifts (target s3=arg0 fp=arg1 s7=inner s6=x s2=y s1=p s5=2 s4=8, no hoist). volatile / array / cast forms of D_8002F3C0 do not remove the hoist; extra 'if (i == 2) {}' uses make it worse.
typedef struct {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} J3Color;

extern s32 D_8002DCE8;
extern s32 D_8002F3C0;
f32 jetpacRoundFloat(f32);

void func_80027BE8(JetpacItem *arg0, s32 arg1) {
    s32 x;
    s32 y;
    JetpacInner *inner;
    J3Color sp58;
    s32 i;
    JetpacSprite **p;

    *(s32 *)&sp58 = D_8002DCE8;
    inner = (JetpacInner *)((u8 *)&D_8002EC30 + D_8002EC30.unk344 * 0x194 + 0x1C);
    if (arg0->unk1C >= 2) {
        x = (s32)arg0->unk8;
        y = (s32)jetpacRoundFloat(arg0->unkC);
        if (arg1 < 3) {
            p = arg0->sprites;
            for (i = 0; i != 2; i++, p++, y += 8) {
                if (!arg1) {
                }
                if (!inner) {
                }
                if ((inner->unkC < 8 && inner->unkC + arg1 * 2 + i >= 8) || (inner->unkC == 8 && (D_8002F3C0 & 0x10))) {
                    sp58.g = 0;
                }
                if (*p != NULL) {
                    func_80025700(*p, x, y, &sp58, *(s32 *)((u8 *)arg0 + 0x20));
                }
            }
        } else {
            func_80025700(arg0->sprites[0], x, y, (u8 *)arg0 + 0x18, *(s32 *)((u8 *)arg0 + 0x20));
        }
    }
}

// func_80701098 (src/global/103AB0.c): Stage 5: text identical (pos 0) in NON_MATCHING build, frame 0x1c0 ok; only the 2 struct-return temps (vec3fScale/Add nested) sit at sp+0xC0/0xCC instead of 0xC4/0xD0 (4 bytes low: one home above temps must become a compiler temp). Rodata reloc names only.
typedef struct {
    u8 unk0[0x21C];
    Ab2Vec3 unk21C;
    u8 unk228[0xC];
    Ab2Vec3 unk234;
} L5Cam;

typedef struct {
    f32 unk0;
    f32 unk4;
    u8 unk8;
    u8 unk9;
    u8 unkA;
    u8 unkB;
    s8 unkC;
    u8 pad[3];
} L5Sprite;

extern L5Sprite D_80754AF0[];
void vec3fSet(f32 *, f32, f32, f32);
Ab2Vec3 vec3fSub(Ab2Vec3, Ab2Vec3);
Ab2Vec3 vec3fAdd(Ab2Vec3, Ab2Vec3);
Ab2Vec3 vec3fScale(Ab2Vec3, f32);
f32 vec3fDot(Ab2Vec3, Ab2Vec3);
Gfx *func_80703374(Gfx *, u8, u8, u8, u8);

Gfx *func_80701098(Gfx *dl, Ab2TrailPoint pt, u8 arg2) {
    Ab2Vec3 sp1B4;
    Ab2Vec3 sp1A8;
    Ab2Vec3 sp19C;
    Ab2Vec3 sp190;
    Ab2Vec3 sp184;
    Ab2Vec3 sp178;
    Ab2Vec3 sp16C;
    Ab2Vec3 sp160;
    Ab2Vec3 padX[7];
    f32 sp108;
    f32 padY[4];
    f32 spF4;
    f32 spF0;
    f32 fs0;
    f32 fs2;
    f32 fs3;
    s16 i;

    spF0 = (f32)((f64)arg2 / 5.0);
    vec3fSet(&sp160.x, pt.unk0, pt.unk4, pt.unk8);
    vec3fSet(&sp178.x, ((L5Cam *)D_807FC924)->unk21C.x, ((L5Cam *)D_807FC924)->unk21C.y, ((L5Cam *)D_807FC924)->unk21C.z);
    vec3fSet(&sp16C.x, ((L5Cam *)D_807FC924)->unk234.x, ((L5Cam *)D_807FC924)->unk234.y, ((L5Cam *)D_807FC924)->unk234.z);
    vec3fNormalize(&sp19C.x, vec3fSub(sp16C, sp178));
    sp1B4 = vec3fAdd(sp178, vec3fScale(sp19C, 5000.0f));
    vec3fNormalize(&sp190.x, vec3fSub(sp160, sp178));
    fs0 = (f64)vec3fDot(sp190, sp19C) < 1e-05 ? 1e-05 : vec3fDot(sp190, sp19C);
    sp160 = vec3fAdd(sp178, vec3fScale(vec3fScale(sp190, 5000.0f), 1.0f / fs0));
    sp1A8 = vec3fSub(sp160, sp1B4);
    if (fs0 < 0.0f) {
        return dl;
    }
    for (i = 0; i < 12; i++) {
        fs3 = ((f64)fs0 < 0.75 ? 0.0 : (f64)fs0 - 0.75) * 4.0;
        fs2 = (f64)fs3 < 0.85 ? 0.85 : (f64)fs3;
        switch (i) {
        case 11:
            sp108 = 640.0f;
            spF4 = 480.0f;
            fs3 = ((f64)fs0 < 0.9 ? 0.0 : (f64)fs0 - 0.9) * 10.0;
            fs2 = (f64)fs3 < 0.85 ? 0.85 : (f64)fs3;
            
            break;
        case 0:
        case 12:
            fs3 = ((f64)fs0 < 0.25 ? 0.0 : (f64)fs0 - 0.25) * 1.333;
            fs2 = (f64)fs3 < 0.85 ? 0.85 : (f64)fs3;
            camProjectToScreen(sp160.x, sp160.y, sp160.z, &sp108, &spF4, 0, 4.0f, 0);
            
            break;
        default:
            
            sp184 = vec3fAdd(sp1B4, vec3fScale(sp1A8, D_80754AF0[i].unk4));
            camProjectToScreen(sp184.x, sp184.y, sp184.z, &sp108, &spF4, 0, 4.0f, 0);
            break;
        }
        gDPPipeSync(dl++);
        gDPSetPrimColor(dl++, 0, 0, (u32)(((f64)pt.unkC / 255.0) * D_80754AF0[i].unk8 * fs2), (u32)(((f64)pt.unkD / 255.0) * D_80754AF0[i].unk9 * fs2), (u32)(((f64)pt.unkE / 255.0) * D_80754AF0[i].unkA * fs2), (u32)((f32)D_80754AF0[i].unkB * fs3 * spF0));
        dl = func_8068C5A8(dl, (D_80754AF0[i].unkC + 0x4D) & 0xFFFF, 3, 1, 0x40, 0x40, (s32)sp108, (s32)spF4, D_80754AF0[i].unk0 * 4.0f * spF0, D_80754AF0[i].unk0 * 4.0f * spF0, 0, 0.0f);
    }
    dl->words.w0 = 0xE7000000; dl->words.w1 = 0;
    dl++;
    if ((f64)fs0 > 0.97) {
        dl = func_80703374(dl, pt.unkC, pt.unkD, pt.unkE, (u32)(((f64)fs0 - 0.97) * 33.0 * 128.0));
        dl->words.w0 = 0xD7000002; dl->words.w1 = 0x80008000;
        dl[1].words.w0 = 0xFC119623; dl[1].words.w1 = 0xFF2FFFFF;
        dl += 2;
    }

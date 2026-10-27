// func_80026DC8 (src/jetpac/1A60.c): stage 5-6: frame 0x70 and insn count identical; diff = register rotation only (target G=EC30 base in v1, 0xFF in a2, post-call &tmpl in v0; mine v0/v1/a2) plus swc/sw store order (li t3/t4 hoist for unk24/unk28: target stores 0x448 before 0x444). Local 'g' pointer declared before tmpl gives the stack slot 0x1c. uopt trace: candidate &tmpl (sp+0x18) forbidden v0/v1/a0/a1 in mine; tried pad/volatile/decl-init/perm, no fix
extern JetpacState D_8002F050;
extern JetpacActor D_8002F09C[];
typedef struct {
    u8 pad0[0x420];
    f32 x;
    f32 y;
    f32 vx;
    f32 vy;
    u8 color[4];
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    s32 unk30;
    u8 pad454[0x464 - 0x454];
    s32 unk44;
    u8 tint[4];
} J1bGameView;

extern JetpacActor D_8002C518;
extern s32 D_8002F084;
extern s32 D_8002F088;

void func_80026DC8(void) {
    J1bGameView *g = (J1bGameView *)&D_8002EC30;
    JetpacActor tmpl;

    tmpl = D_8002C518;
    g->vx = 0.0f;
    g->vy = 0.0f;
    g->color[0] = 0xFF;
    g->color[1] = 0xFF;
    g->color[2] = 0xFF;
    g->color[3] = 1;
    g->unk14 = 1;
    g->unk2C = 0;
    g->unk18 = 0;
    g->unk44 = 14;
    g->tint[0] = 0xFF;
    g->tint[3] = 1;
    g->unk20 = 0;
    g->unk1C = 0;
    g->unk24 = 0x10;
    g->unk28 = 0x18;
    g->unk30 = 1;
    g->x = 126.0f;
    g->y = 160.0f;
    func_80025BB8((JetpacActor *)&D_8002F050, 0);
    D_8002F084 = 3;
    D_8002F088 = 4;
    D_8002F09C[0] = tmpl;
    D_8002F09C[1] = tmpl;
    D_8002F09C[2] = tmpl;
    D_8002F09C[3] = tmpl;
}

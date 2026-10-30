// func_806134B4 (src/global/17B90.c): stage 3: semantic starter compiles; target uses four saved registers and a 0x28 frame versus draft's five and 0x30; direct work-pointer reload/store order remains.
typedef struct { void *unk0; f32 unk4; f32 unk8; u8 padC[4]; s16 unk10; u8 pad12[2]; f32 unk14; f32 unk18; u16 unk1C; u8 pad1E[6]; f32 unk24; f32 unk28; f32 unk2C; f32 unk30; f32 unk34; } P17LSlot;
typedef struct { void *unk0; P17LSlot *unk4; P17LSlot *unk8; P17LSlot *unkC; f32 unk10; Mtx *unk14; Mtx *unk18; void *unk1C; void *unk20; void *unk24; u8 pad28[0xC]; f32 unk34; f32 unk38; f32 unk3C; u8 pad40[4]; f32 unk44; f32 unk48; u8 pad4C[0xC]; f32 unk58; u8 pad5C[8]; s16 unk64; u8 pad66[2]; s32 unk68; u8 pad6C[4]; s32 unk70; u8 pad74[4]; s32 unk78; s32 unk7C; f32 unk80; s32 unk84; s32 unk88; } P17LAnim;
typedef struct { void *unk0; P17LAnim *unk4; u8 pad8[4]; f32 unkC[4][4]; s32 unk4C; s32 unk50; } P17LController;
void *heapAlloc(s32);
s32 func_806134B4(P17LController *arg0, s32 arg1) {
    P17LAnim *anim; P17LSlot *slot; void *resource; s32 i; s32 count;
    count = arg1 & 0xFFFF;
    resource = func_80612E90(arg0, count, 0);
    if (resource == NULL) return 0;
    arg0->unk0 = resource; arg0->unk4C = 0; arg0->unk50 = 0;
    anim = heapAlloc((*(u8 *)((u8 *)resource + 0x20) << 7) + 0x170); arg0->unk4 = anim;
    anim->unk0 = (u8 *)anim + 0x90; anim->unk4 = (P17LSlot *)((u8 *)anim + 0xC8); anim->unk8 = (P17LSlot *)((u8 *)anim + 0x100); anim->unkC = (P17LSlot *)((u8 *)anim + 0x138); anim->unk14 = (Mtx *)((u8 *)anim + 0x170); anim->unk18 = anim->unk14 + *(u8 *)((u8 *)resource + 0x20);
    for (i = 0; i < *(u8 *)((u8 *)resource + 0x20); i++) { guMtxIdent(anim->unk14 + i); guMtxIdent(anim->unk18 + i); }
    guMtxIdentF(arg0->unkC); anim->unk1C = NULL; anim->unk20 = NULL; anim->unk24 = NULL; anim->unk34 = 0.15f; anim->unk38 = 0.15f; anim->unk3C = 0.15f;
    slot = anim->unk0; slot->unk4 = 0.0f; slot->unk8 = 0.0f; slot->unk0 = NULL; slot->unk10 = -1; slot->unk1C = 0; slot->unk14 = 0.0f; slot->unk18 = 0.0f; slot->unk24 = 1.0f; slot->unk34 = 0.0f;
    anim->unk4->unk0 = NULL; anim->unk4->unk34 = 0.0f; anim->unk8->unk0 = NULL; anim->unk8->unk34 = 0.0f; anim->unkC->unk0 = NULL; anim->unkC->unk34 = 0.0f; anim->unk68 = 0; anim->unk64 = 0; anim->unk70 = 0; anim->unk78 = 0; anim->unk7C = 0; anim->unk84 = 0; anim->unk88 = 0; anim->unk10 = 0.0f; anim->unk44 = 0.0f; anim->unk58 = 0.0f; anim->unk48 = 1.0f; anim->unk80 = 0.0f;
    return 1;
}

// func_806F386C (src/global/F56F0.c): Stage 3: verified setup semantics with the required func_806F386C(u8, s32, s32, s16, s32) ABI. Remaining mismatch is temporary/register scheduling around list indexing and actor-extra bit clear.
typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    u8 pad6[0xC];
    s16 unk12;
    u8 pad14[2];
    s16 unk16;
} F5N4Coord;

typedef struct {
    s16 unk0;
    u8 pad2[2];
    void *unk4;
} F5N4ListEntry;

typedef struct {
    s16 unk0;
    u8 pad2[2];
    F5N4ListEntry *unk4;
} F5N4List;

typedef struct {
    u8 pad0[0x1F0];
    s32 unk1F0;
} F5N4ActorExtra;

extern u8 D_807463B8;
extern F5N4List *D_80753E90;
extern u8 D_8076A0B1;
extern F5N4ListEntry *D_807FD708;
extern F5N4Coord *D_807FD70C;
extern s32 D_807FD710;
extern s16 D_807FD714;
extern s16 D_807FD718;
extern s32 D_807FD71C;

void func_806F386C(u8 arg0, s32 arg1, s32 arg2, s16 arg3, s32 arg4) {
    s32 temp_t6;
    F5N4ListEntry *temp_t5;
    F5N4ActorExtra *temp_v0;

    temp_t6 = arg0 & 0xFF;
    temp_v0 = (F5N4ActorExtra *)((Actor *)arg1)->unk174;
    if (D_80753E90->unk0 >= temp_t6) {
        D_807463B8 = 3;
        D_8076A0B1 |= 0x10;
        D_807FD710 = arg1;
        temp_v0->unk1F0 &= ~1;
        D_807FD714 = 0;
        temp_t5 = D_80753E90->unk4 + temp_t6;
        D_807FD708 = temp_t5;
        D_807FD70C = temp_t5->unk4;
        D_807FD718 = arg3;
        D_807FD71C = arg2;
        if (arg4 == 0) {
            func_806F37BC((Actor *)arg1, D_807FD70C);
        }
    }
}

// func_8002AB80 (src/menu/3E10.c): text-identical, reloc only: end bound is D_8076A0E8+0x18 vs expected D_8076A100 (ptr-based forms break loop shape)
extern s8 D_8076A0D6;
extern s8 D_8076A100[];
extern s8 D_8076A0E4[];
extern s8 D_8076A0E8[][4];
extern u8 D_80720CF0;
extern u8 D_80720D14;
extern u8 D_80720C34;
typedef struct Menu3A_Struct174 {
    f32 unk0;
    f32 unk4;
    char pad[0xB];
    s8 unk13;
    char pad2[2];
    s8 unk16;
    s8 unk17;
} Menu3A_Struct174;
void func_80030894(void *, void *, s32, s32, f32, s32, s32);
void menuAssignPlayerControllerSlot(s32, s32);
void menuReleasePlayerControllerSlot(s32);

void func_8002AB80(void *arg0, s32 arg1) {
    Menu3A_Struct174 *temp_s0 = *(Menu3A_Struct174 **)((u8 *)arg0 + 0x174);
    s32 i;
    s32 j;

    temp_s0->unk17 = D_8076A0D6;
    func_80030894(temp_s0, &D_80720CF0, 0x122, 0xD2, 0.75f, 2, 0);
    func_80030894(temp_s0, &D_80720D14, 0x23, 0xD2, 0.75f, 2, 0);
    func_80030894(temp_s0, &D_80720C34, 0xA0, 0x78, 0.75f, 2, 4);
    for (i = 0; i < 6; i++) {
        j = 0;
        do {
            D_8076A0E8[i][j] = -1;
            j++;
        } while (j < 4);
    }
    for (i = 0; i < 4; i++) {
        if (i == 0) {
            menuAssignPlayerControllerSlot(i, i);
        } else {
            D_8076A0E4[i] = -0x80;
            menuReleasePlayerControllerSlot(i);
        }
    }
}

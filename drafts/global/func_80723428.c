// func_80723428 (src/global/127B00.c): stage 4: 0x20 frame conflicts with required sp+0x1C pointer home slot
typedef struct Uc1Playback Uc1Playback;
extern Uc1Playback *D_807FDBF8[];
void heapFree(s32, s32);

void func_80723428(s32 arg0) {
    s32 *temp_v0;
    s32 pad;

    if ((arg0 == -1) || (D_807FDBF8[arg0] != NULL)) {
        temp_v0 = (s32 *)&D_807FDBF8[arg0];
        heapFree(*temp_v0, arg0);
        *temp_v0 = 0;
    }
}

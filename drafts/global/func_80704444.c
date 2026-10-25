// func_80704444 (src/global/103AB0.c): stage 6; target differs only in shifted-result temporary registers; 600-second permuter best score 10 used unreadable nested masks and did not reproduce a readable match
typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    u8 unk6[2];
    s16 unk8;
    s16 unkA;
} R1F103AB0cView;

void func_80704444(R1F103AB0cView *arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, u8 arg5) {
    arg0->unk0 = arg1;
    arg0->unk2 = arg2;
    arg0->unk4 = 0x3E8;
    arg0->unk8 = (s16)(arg3 << arg5);
    arg0->unkA = (s16)(arg4 << arg5);
}

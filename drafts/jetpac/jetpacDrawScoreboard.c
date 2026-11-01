// jetpacDrawScoreboard (src/jetpac/0.c): stage 6: 2 insns swapped (text 2): preheader order 'lui s1, lui s3, addiu s1, addiu s3' (target FIFO) vs ours 'addiu s3 then s1' (LIFO). ugen input is la s1; addu s5; li s4; la s3. Tested all 120 permutations of preheader records in t.G, while/do-while/for loop headers, and replacing D_8002EC4C with jetpacGame.players (diff 3 with base %hi).
typedef struct {
    u8 pad0[0x1C];
    u8 pad1C[0x8];
    s32 lives;
    u8 pad28[0x194 - 0x24];
} JetpacPlayer;

extern JetpacPlayer D_8002EC4C[];
extern s32 D_8002BA6C;
extern s32 D_8002EF74;
extern s32 D_8002EC50;
extern s32 D_8002EC48;
extern s32 D_8002EDE4;

s32 jetpacIsSpawnDelay(void);
void jetpacSetupTextRdp(s32);
void jetpacSetTextColor(s32, s32, s32, s32);
void jetpacDrawString(s32, char *, s32, s32, s32);
s32 _sprintf(char *, char *, ...);

void jetpacDrawScoreboard(s32 arg0) {
    char buf[0x50];
    s32 mask;
    s32 i;
    s32 pad;

    mask = jetpacIsSpawnDelay() & D_8002BA6C;
    jetpacSetupTextRdp(arg0);
    jetpacSetTextColor(0xFF, 0xFF, 0xFF, 0xFF);
    jetpacDrawString(arg0, "1UP", 0x38, 0x18, mask != 0 && D_8002EF74 == 0);
    for (i = 0; i < 2; i++) {
        if (D_8002EC4C[i].lives > 0) {
            _sprintf(buf, "%d!", D_8002EC4C[i].lives);
            jetpacDrawString(arg0, buf, i * 0x70 + 0x60, 0x18, 0);
        }
    }
    jetpacDrawString(arg0, "2UP", 0xF8, 0x18, mask != 0 && D_8002EF74 == 1);
    jetpacSetTextColor(0, 0xFF, 0xFF, 0xFF);
    jetpacDrawString(arg0, "HI", 0x98, 0x18, 0);
    jetpacSetTextColor(0xFF, 0xFF, 0, 0xFF);
    _sprintf(buf, "%06d", D_8002EC50);
    jetpacDrawString(arg0, buf, 0x28, 0x20, 0);
    _sprintf(buf, "%06d", D_8002EC48);
    jetpacDrawString(arg0, buf, 0x88, 0x20, 0);
    _sprintf(buf, "%06d", D_8002EDE4);
    jetpacDrawString(arg0, buf, 0xE8, 0x20, 0);
}

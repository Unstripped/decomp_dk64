// Stage 6: all target instructions match except two immediate-materialization scheduling swaps
// for the 0xE200001C / 0x00504340 command. gDPSetOtherMode schedules exactly but emits EF,
// while the literal E2 source below emits the correct word but schedules the two ORIs oppositely.
void func_806FEF7C(Gfx *arg0, Actor *arg1) {
    Gfx *glist;

    glist = func_806FEDB0(arg0, ((R1F103AB0aState *)arg1->unk174)->unk1A4);
    {
        Gfx *gfx = glist++;
        gfx->words.w0 = _SHIFTL(0xE2, 24, 8) | _SHIFTL(0x1C, 0, 24);
        gfx->words.w1 = 0x504340;
    }
    gDPSetPrimColor(glist++, 0, 0, 0, 0, 0, 0xFF);
    func_8068C5A8(glist, 0x3C, 3, 1, 0x40, 0x40, 0xA0, 0x78, 5.0f, 5.0f, 0, D_8075DE70);
}

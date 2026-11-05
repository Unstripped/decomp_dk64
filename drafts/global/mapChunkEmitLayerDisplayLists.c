// mapChunkEmitLayerDisplayLists (src/global/55B20.c): stage 6 park unchanged, full=2 (only lui a2 vs lui v0 for D_807F70B0). 2026-11-04 focus: hypothesis: a2 is excluded for entry (a3) and bound (t1) by the forbidden set or a cupcosts preference penalty (uoptreg2.c 1878, 2093-2110), not by an occupant; target has no a2 code in the loop. FAKE3 removed -> arg2 promoted to fp (full 82). Invisible ghost: `if (gMapChunks[arg1].unk5) {}` inside the do-loop (full 6, ghost adjsave 36.7 -> a0) or after it (full 10, 6.7 -> t0); needs adjsave in [10,15) -> no single/pair placement found. Natural lever found: REUSE PARAM arg0 as the entry pointer (graphhead param precolour forbids a0-a2 for it): order `found = 0; node = D; arg0 = &entries[i]` in nested `if (unk4[arg2] != -1)` + combined `node->unk18 && unk2 & 1<<arg2` gives entry a3, chunk t0 (full 37); left: bound a2 (target t1) and switch top (uadd(arg0,8) coloured v0, cases use it instead of s0). A local initialised from arg0 does not work. Body of that route: .scratch only, regenerate from this note.
s32 mapChunkEmitLayerDisplayLists(arg0, arg1, arg2)
u32 *arg0;
s32 arg1;
u8 arg2;
{
    MapChunkEffectEntry *entry;
    struct MapCell *node;
    Gfx *gfx;
    s32 i;
    s32 found;

    gfx = (Gfx *)arg0;
    if (arg0 == 0) {} // FAKE: rs
    gDPPipeSync(gfx++);
    if (((MapChunkEffect *)gMapChunks)[arg1].unk5 != 2) {
        switch (arg2) {
        case 0:
            gSPDisplayList(gfx++, osVirtualToPhysical((void *)((MapChunkEffect *)gMapChunks)[arg1].unk2C));
            break;
        case 1:
            gSPDisplayList(gfx++, osVirtualToPhysical((void *)((MapChunkEffect *)gMapChunks)[arg1].unk30));
            break;
        case 2:
            gSPDisplayList(gfx++, osVirtualToPhysical((void *)((MapChunkEffect *)gMapChunks)[arg1].unk34));
            break;
        case 3:
            gSPDisplayList(gfx++, osVirtualToPhysical((void *)((MapChunkEffect *)gMapChunks)[arg1].unk38));
            break;
        }
    } else {
        for (i = 0; i < ((MapChunkEffect *)gMapChunks)[arg1].unk50; i++) {
            gfx = (Gfx *)((u32)gfx | 0); // FAKE: extra gfx reference (raises its colouring priority above the packet pointers)
            if (((MapChunkEffectEntry *)((MapChunkEffect *)gMapChunks)[arg1].unk4C)[i].unk4[arg2] == -1) {
                continue;
            }
            found = 0;
            node = (struct MapCell *)D_807F70B0; do { // LAYOUT: joined onto the do line (keeps lh a0 before lw v0)
                if (node->unk2 == ((MapChunkEffectEntry *)((MapChunkEffect *)gMapChunks)[arg1].unk4C)[i].unk0) {
                    found = 1;
                } else {
                    node++;
                }
            } while (found == 0);
            if (D_807F70B0 == 0) {} // FAKE: shares the node load's hi constant; that candidate takes a2 ahead of the entry pointer (target a3)
            if (node->unk18 == 0) {
                continue;
            }
            if ((((MapChunkEffectEntry *)((MapChunkEffect *)gMapChunks)[arg1].unk4C)[i].unk2 & (1 << arg2)) == 0) {
                continue;
            }
            gSPSegment(gfx++, 6, osVirtualToPhysical((void *)((MapChunkEffectEntry *)((MapChunkEffect *)gMapChunks)[arg1].unk4C)[i].unk14[arg2]));
            gDPPipeSync(gfx++);
            gSPDisplayList(gfx++, osVirtualToPhysical((void *)((MapChunkEffectEntry *)((MapChunkEffect *)gMapChunks)[arg1].unk4C)[i].unk4[arg2]));
            gDPPipeSync(gfx++);
        }
    }
    return (s32)gfx;
}

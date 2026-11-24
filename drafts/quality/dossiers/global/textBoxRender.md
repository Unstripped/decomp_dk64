# textBoxRender (global, src/global/A8400_text_box.c)
## Sites
global:806A4284:other:d5a412 other: hand-expanded G_SETSCISSOR word (line 214) written uly-first over the named fields boxTop/boxLeft, boxBottom/boxRight, so cfe emits the | chain uly term first and the target loads 0x48(s2) before 0x44(s2) (0xfd4/0xfd8) and 0x50 before 0x4C (0x1010/0x1014); the stock macro over named fields gives ulx first.
## Attempts
2026-11-17 PolishglobalA8400 claude-opus-5-5:xhigh: named-field gDPSetScissor -> fdiff 1; (&state->boxLeft)[0..3] -> fdiff 0 (pun); f32 box[4] header -> objdiff OK; anonymous union -> OK, cfe W838/649; refused director turn 162.
2026-11-24 pilot2 intent CleantextBoxRender claude-opus-5-5: H1 rebuilt on 7561b3cc (shadow resqueue.h box[4], all A8400 users, stock gDPSetScissor) -> whole-object fdiff 0, 112080 stand-in fdiff 0, cwarn 0, uninit 0 (.scratch/CleantextBoxRender/h1/).
2026-11-24 pilot2 intent CleantextBoxRender claude-opus-5-5: H3 gDPSetScissorFrac named * 4.0f -> full=53 shape=8 (= named macro); H3 on box[k] -> fdiff 0.
2026-11-24 pilot2 intent CleantextBoxRender claude-opus-5-5: H4 block-scoped f32 locals -> full=169 shape=94.
2026-11-24 pilot2 intent CleantextBoxRender claude-opus-5-5: nested struct { f32 left, top, right, bottom; } box -> fdiff 1; hand uly-first words with rect[k] -> full=63, with box[k] -> fdiff 1; named hand word in macro order -> full=53.
2026-11-24 pilot2 intent CleantextBoxRender claude-opus-5-5: local half -> frame -> fdiff 0 (kept).
## Untried ideas
H1b anonymous union (measured 2026-11-17, cfe W838/649: refused) and H2 pun (measured, refused): none left without the header ruling.
## Evidence
0xfc8-0x100c: lui at,0xed00; lwc1 $f6,72(s2) (uly) before lwc1 $f10,68(s2) (ulx); andi t5 (uly) | at, then andi/sll 12 (ulx); w1 0x1010-0x1044 same with 80 before 76.
textBoxUpdateRows 0x17f8-0x18bc: clamps 0x44/0x48/0x4C/0x50 against rect 0x270/0x272/0x274/0x276 (lh 624/626/628/630) in index order.
cfe t.B (as1probe ucode --cfe): named fields -> ulx<<12, 0xED000000, ior, uly, ior; constant-index (&state->boxLeft)[k] -> uly, 0xED000000, ulx<<12, ior, ior.
63EC0 control pair: gMapChunks[index].clip* at 0xd48 (108 before 104, uly first) vs water->scissor* at 0xe00 (64 before 66, ulx first), both stock macros.

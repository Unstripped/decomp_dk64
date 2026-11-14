# jetpacGridAddTiledSprite (jetpac, src/jetpac/1460.c)
## Sites
jetpac:80025700:other:880470 other: count increment stored through *(s32 *)(u32)&jetpacTiledSpriteCount so ugen emits no .noalias $23,$sp for the store and as1 keeps the sprite param reload lw t9,80(sp) after sw t8,0(s7) (KEPT)
## Attempts
2026-11-12 r25 CleanJetpac1460 opus-5-5:medium: ++ / += / = +1 / [count++] / *& read (4 rows each), as1probe scan (delete .noalias record 99), permute (120), reconstruct
2026-11-14 HackjetpacGridAddTiledSprite opus-5-5:high: as1probe scan 85-115 (only the .noalias delete), snapshot n at the test / before / after dst (4-19), copy before increment (50), early-return spellings (4-12)
## Untried ideas
none natural: every la-derived base gets the .noalias record (Q0503)
## Evidence
ugen record 99 `.noalias $23,$sp` after the inner early-return block; target order: addiu t8,v0,1; sw t8,0(s7); lw t9,80(sp); lw at,0(t9) (struct copy of *sprite).

# jetpacRocketItemUpdate (jetpac, src/jetpac/3480.c)
## Sites
- jetpac:80027728:other:1a6f29: REMOVED. Every jetman field is read through `player = &jetpacPlayer.player`.
- jetpac:80027728:other:f1221c: REMOVED. The JetW2FpABox view is now `player->boxX1`.
## Attempts
- 2026-11-14 U HackjetpacRocketItemUpdate opus:high:
  - all fields via player: text 7, the rest reloc-only (RELOC-EQUIV OK)
  - pointer + split labels: 44; direct names: 112; mixed: 72
## Evidence
- 18 LO16-immediate-only word differences against jetpacPlayer+offset, i.e. the split labels.

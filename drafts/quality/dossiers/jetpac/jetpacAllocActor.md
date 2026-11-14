# jetpacAllocActor (jetpac, src/jetpac/4FC0.c)
## Sites
- jetpac:800292C4:other:d52731: REMOVED. The pre-check template copy is now a declaration initialiser (the target performs the copy before the test).
## Attempts
- rounds 6/20 (opus:low): diagnose, permute (best=0 re-created the pre-check copy).
- 2026-11-14 U HackjetpacAllocActor opus:high (variants.py try full=):
  - actor and templateActor both as initialisers (call, then copy): 0 (applied)
  - template initialiser only: 67
  - template declared first: 70
  - `*actor = D_8002E914` after the test, 3 declaration orders: 53
## Evidence
- 0x314-0x36c: word-copy loop D_8002E914 -> sp+0x20, before `bnez v0,0x378` at 0x368.
- 0x378-0x3ac: copy sp+0x20 -> *actor.

# Names queue (continue-unit names stream)

Accepted proposals waiting for the next names window (`.omp/skills/continue-unit/names.md`). The lead appends after
the "Check"; the window that applies a line deletes it. Format:
`- [field|global|func] <seg or include/h.h> <Record|-> <old> -> <new> | <evidence, file:line> | <worker>`;
`held:` lines keep an item out until new evidence arrives.

## Queue

## Held
- held: [global] global D_80753C84 -> gKongPathRespawnTimers, D_80753CA4 -> gKongPathCheckRespawnTimers (worker: tentative) | per-kong s16 tables stored to respawnTimer every frame of playerStateAttachedCallbackFall/CheckFall while proxPathFollowerStep runs | PolishglobalD5E10c (2026-11-24)

# raceGetWaypointSegmentFraction (race, src/race/36B0.c)

## Sites
- 85cf24: the embedded dead store `(e2 = sum) / d2`. KEPT.
  - e2 and d2 are memory-homed. The store/reload at 0x1b0/0x1b4 is ugen re-reading the value of the embedded assignment from e2's home.

## Attempts
- 2026-11-14 U HackraceGetWaypointSegmentFraction: 13-60 lines (see the ledger).

## Untried ideas
- What made the float locals memory-homed in the original (d2 at 80 stored but kept in $f6).

## Evidence
- Target 0x188 `swc1 $f6,80(sp)` (d2 home, never reloaded); 0x1b0/0x1b4 `swc1 $f10,76(sp)` / `lwc1 $f4,76(sp)`; 0x190/0x194 y-term store/reload at 60(sp).
